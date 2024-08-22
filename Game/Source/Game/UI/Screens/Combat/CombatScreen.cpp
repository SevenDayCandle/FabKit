module;

import fbc.Action;
import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.CombatSquareRenderable;
import fbc.CombatTurnRenderable;
import fbc.CreatureRenderable;
import fbc.GameRun;
import fbc.HitboxBatchMoveSmoothVFX;
import fbc.RelativeHitbox;
import fbc.UIButton;
import fbc.UIFadeOutDriftVFX;
import fbc.VFXAction;

module fbc.CombatScreen;

namespace fbc {

	void CombatScreen::onPlayerTurnBegin(const CombatTurn* turn)
	{
		endTurnButton.setEnabled(true);
	}

	void CombatScreen::onPlayerTurnEnd(const CombatTurn* turn)
	{
		endTurnButton.setInteractable(false).setEnabled(false);
	}

	void CombatScreen::onTurnAdded(const CombatTurn& turn)
	{
		createTurnRender(turn);
	}

	void CombatScreen::onTurnChanged(ref_view<const mset<CombatTurn>> turns)
	{
		int i = 0;
		vec<HitboxBatchMoveSmoothVFX::Entry> entries;
		for (const CombatTurn& turn : turns) {
			auto res = turnUIMap.find(&turn);
			if (res != turnUIMap.end()) {
				CombatTurnRenderable* item = res->second;
				entries.push_back({ item->hb.get(), 0.0, i * TILE_SIZE});
				++i;
			}
		}
		instance->queueAction(make_unique<VFXAction>(win, make_unique<HitboxBatchMoveSmoothVFX>(win, entries)));
	}

	void CombatScreen::onTurnRemoved(const CombatTurn* turn)
	{
		auto res = turnUIMap.find(turn);
		if (res != turnUIMap.end()) {
			uptr<CombatTurnRenderable> item = turnUI.extract(res->second);
			if (item) {
				addVFX(make_unique<UIFadeOutDriftVFX>(win, move(item), 0, -10));
			}
		}
		turnUIMap.erase(turn);
	}

	void CombatScreen::createOccupantRender(const OccupantObject* occupant)
	{
		if (occupant) {
			const OccupantObject& occRef = *occupant;
			CombatSquare* square = occupant->currentSquare;
			float offX = 0;
			float offY = 0;
			if (square) {
				offX = square->col * TILE_SIZE;
				offY = square->row * TILE_SIZE;
			}
			fieldUI.addNew<CreatureRenderable>(RelativeHitbox::make(*fieldUI.hb, offX, offY, TILE_SIZE, TILE_SIZE), occRef);
		}
	}

	void CombatScreen::createTurnRender(const CombatTurn& turn)
	{
		CombatTurnRenderable& render = turnUI.addNew<CombatTurnRenderable>(RelativeHitbox::make(*turnUI.hb, 0, turnUI.size() * TILE_SIZE, TURN_W, TILE_SIZE), turn);
		turnUIMap.emplace(&turn, &render);
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
			fieldUI.addNew<CombatSquareRenderable>(RelativeHitbox::make(*fieldUI.hb, square.col * TILE_SIZE, square.row * TILE_SIZE, TILE_SIZE, TILE_SIZE), square);
		}
		// Add images for each creature
		for (const OccupantObject* occupant : instance->getOccupants()) {
			createOccupantRender(occupant);
		}
		// Add images for each turn
		for (const CombatTurn& turn : instance->getTurns()) {
			createTurnRender(turn);
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