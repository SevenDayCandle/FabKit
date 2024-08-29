module;

import fbc.Action;
import fbc.CardRenderable;
import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.CombatSquareRenderable;
import fbc.CombatTurnRenderable;
import fbc.Creature;
import fbc.CreatureRenderable;
import fbc.GameRun;
import fbc.RelativeHitbox;
import fbc.UIButton;
import fbc.UIDisposeVFX;
import fbc.UITransformVFX;
import fbc.VFXAction;

module fbc.CombatScreen;

namespace fbc {

	void CombatScreen::onPlayerTurnBegin(const CombatTurn* turn)
	{
		endTurnButton.setEnabled(true);
		Creature* occupant = dynamic_cast<Creature*>(&turn->source);
		if (occupant) {
			int i = 0;
			for (const uptr<Card>& card : occupant->getHand()) {
				auto res = cardUIMap.find(card.get());
				if (res == cardUIMap.end()) {
					createCardRender(*card, CARD_HAND_POS_X + i * CARD_W, CARD_HAND_POS_Y);
				}
				++i;
			}
		}
	}

	void CombatScreen::onPlayerTurnEnd(const CombatTurn* turn)
	{
		endTurnButton.setInteractable(false).setEnabled(false);
		for (auto& entry : cardUIMap) {
			removeCardRender(entry.second);
		}
		cardUIMap.clear();
	}

	void CombatScreen::onTurnAdded(const CombatTurn& turn)
	{
		createTurnRender(turn);
	}

	void CombatScreen::onTurnChanged(ref_view<const mset<CombatTurn>> turns)
	{
		int i = 0;
		for (const CombatTurn& turn : turns) {
			auto res = turnUIMap.find(&turn);
			if (res != turnUIMap.end()) {
				CombatTurnRenderable* item = res->second;
				addVfxNew<UITransformVFX>(*item)
					.setMove(0, i * TILE_SIZE);
			}
			++i;
		}

	}

	void CombatScreen::onTurnRemoved(const CombatTurn* turn)
	{
		auto res = turnUIMap.find(turn);
		if (res != turnUIMap.end()) {
			uptr<CombatTurnRenderable> item = turnUI.extract(res->second);
			if (item) {
				addVfxNew<UIDisposeVFX>(move(item));
			}
		}
		turnUIMap.erase(turn);
	}

	CardRenderable& CombatScreen::createCardRender(const Card& card, float tOffX, float tOffY, float sOffX, float sOffY) {
		CardRenderable& render = cardUI.addNew<CardRenderable>(*cardUI.hb, card, sOffX, sOffY);
		cardUIMap.emplace(&card, &render);
		addVfxNew<UITransformVFX>(render)
			.setFade(0, 1)
			.setMove(tOffX, tOffY);
		return render;
	}

	CombatTurnRenderable& CombatScreen::createTurnRender(const CombatTurn& turn)
	{
		CombatTurnRenderable& render = turnUI.addNew<CombatTurnRenderable>(turnUI.relhb(0, (turnUI.size() + 1) * TILE_SIZE, TURN_W, TILE_SIZE), turn);
		turnUIMap.emplace(&turn, &render);
		addVfxNew<UITransformVFX>(render)
			.setFade(0,1);
		return render;
	}

	CreatureRenderable& CombatScreen::createOccupantRender(const OccupantObject& occupant) {
		CombatSquare* square = occupant.currentSquare;
		float offX = 0;
		float offY = 0;
		if (square) {
			offX = square->col * TILE_SIZE;
			offY = square->row * TILE_SIZE;
		}
		return fieldUI.addNew<CreatureRenderable>(fieldUI.relhb(offX, offY, TILE_SIZE, TILE_SIZE), occupant);
	}

	void CombatScreen::open()
	{
		GameRun* run = GameRun::current.get();
		instance = run->getCombatInstance();
		instance->viewSubscriber = this;
		endTurnButton.setInteractable(false).setEnabled(false);
		endTurnButton.setOnClick([this](UIButton& w) {
			instance->endCurrentTurn();
			w.setInteractable(false);
		});
		// Add buttons for each square
		for (const CombatSquare& square : instance->getSquares()) {
			fieldUI.addNew<CombatSquareRenderable>(fieldUI.relhb(square.col * TILE_SIZE, square.row * TILE_SIZE, TILE_SIZE, TILE_SIZE), square);
		}
		// Add images for each creature
		for (const OccupantObject* occupant : instance->getOccupants()) {
			if (occupant) {
				createOccupantRender(*occupant);
			}
		}
		// Add images for each turn
		for (const CombatTurn& turn : instance->getTurns()) {
			createTurnRender(turn);
		}
	}

	void CombatScreen::removeCardRender(Card* card) {
		auto res = cardUIMap.find(card);
		if (res != cardUIMap.end()) {
			removeCardRender(res->second);
		}
		cardUIMap.erase(card);
	}

	void CombatScreen::removeCardRender(CardRenderable* card) {
		uptr<CardRenderable> item = cardUI.extract(card);
		if (item) {
			addVfxNew<UIDisposeVFX>(move(item))
				.setScale(0)
				.setMoveRelative(0, -10);
		}
	}

	void CombatScreen::updateImpl()
	{
		instance->update();

		CombatTurn* currentTurn = instance->getCurrentTurn();
		Action* currentAction = instance->getCurrentAction();
		bool allowInteraction = currentTurn && !currentTurn->isDone;
		endTurnButton.setInteractable(allowInteraction);
		// TODO disallow moving/cards when actions are going on

		UIScreen::updateImpl();
	}
}