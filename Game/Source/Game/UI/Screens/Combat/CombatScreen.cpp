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
import fbc.UIGrid;
import fbc.UIDisposeVFX;
import fbc.UIRecolorVFX;
import fbc.UITransformVFX;
import fbc.VFXAction;
import sdl.SDLRunner;

module fbc.CombatScreen;

namespace fbc {

	void CombatScreen::onPlayerTurnBegin(const CombatTurn* turn)
	{
		endTurnButton.setEnabled(true);
		Creature* creature = dynamic_cast<Creature*>(&turn->source);
		if (creature) {
			activeOccupant = creature;
			int i = 0;
			for (const uptr<Card>& card : creature->getHand()) {
				auto res = cardUIMap.find(card.get());
				if (res == cardUIMap.end()) {
					createCardRender(*card, i * CARD_W, 0);
				}
				++i;
			}
		}
		else {
			activeOccupant = dynamic_cast<OccupantObject*>(&turn->source);
		}
	}

	void CombatScreen::onPlayerTurnEnd(const CombatTurn* turn)
	{
		activeOccupant = nullptr;
		endTurnButton.setInteractable(false).setEnabled(false);
		for (auto& entry : cardUIMap) {
			removeCardRender(entry.second);
		}
		selectCardRender(nullptr);
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

	CardRenderable& CombatScreen::createCardRender(const Card& card, float tOffX, float sOffX, float sOffY) {
		CardRenderable& render = cardUI.addNew<CardRenderable>(*cardUI.hb, card, sOffX, sOffY);
		cardUIMap.emplace(&card, &render);
		addVfxNew<UITransformVFX>(render)
			.setFade(0, 1)
			.setMove(tOffX, 0);
		render.setOnClick([this](CardRenderable& card) {selectCardRender(&card);});
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
		return creatureUI.addNew<CreatureRenderable>(creatureUI.relhb(offX, offY, TILE_SIZE, TILE_SIZE), occupant);
	}

	void CombatScreen::clearHighlights() {
		for (CombatSquareRenderable& square : fieldUI) {
			square.valid = false;
			recolorSquare(square, sdl::COLOR_STANDARD);
		}
	}

	void CombatScreen::clearSelectedPath() {
		this->selectedPath.clear();

	}

	void CombatScreen::previewMovement(CombatSquare* source, const sdl::Color& color, int movementRange) {
		instance->fillDistances(source);
		this->targetSizeX = 0;
		this->targetSizeY = 0;
		for (CombatSquareRenderable& square : fieldUI) {
			square.valid = square.square.sDist <= movementRange;
			recolorSquare(square, square.valid ? color : sdl::COLOR_STANDARD);
		}
	}

	void CombatScreen::previewTargeting(CombatSquare* source, const sdl::Color& color, int highlightRangeBegin, int highlightRangeEnd, int targetSizeX, int targetSizeY) {
		this->targetSizeX = targetSizeX;
		this->targetSizeY = targetSizeY;
		for (CombatSquareRenderable& square : fieldUI) {
			int lineDistance = source ? square.square.getLineDistance(*source) : 0;
			square.valid = lineDistance <= highlightRangeEnd && lineDistance >= highlightRangeBegin;
			recolorSquare(square, square.valid ? color : sdl::COLOR_STANDARD);
		}
	}

	void CombatScreen::hoverSquareUpdate(CombatSquareRenderable* newHovered) {
		if (this->hovered != newHovered) {
			this->hovered = newHovered;
			if (newHovered && newHovered->valid) {
				if (targetSizeX > 0 && targetSizeY > 0) {
					int minCol = newHovered->square.col - targetSizeX / 2;
					int minRow = newHovered->square.row - targetSizeY / 2;
					int maxCol = minCol + targetSizeX;
					int maxRow = minRow + targetSizeY;
					for (CombatSquareRenderable& square : fieldUI) {
						const sdl::Color& target = square.square.col >= minCol && square.square.col < maxCol && square.square.row >= minRow && square.square.row < maxRow ? *hoverColor : *square.originalColor;
						if (target != square.color) {
							addVfxNew<UIRecolorVFX>(square, target);
						}
					}
				}
				else {
					for (CombatSquareRenderable& square : fieldUI) {
						const sdl::Color& target = &square == newHovered ? *hoverColor : *square.originalColor;
						if (target != square.color) {
							addVfxNew<UIRecolorVFX>(square, target);
						}
					}
				}
			}
			else {
				for (CombatSquareRenderable& square : fieldUI) {
					if (*square.originalColor != square.color) {
						addVfxNew<UIRecolorVFX>(square, *square.originalColor);
					}
				}
			}
		}
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
		fieldUI.setHbOffsetSize(instance->getFieldColumns() * TILE_SIZE, instance->getFieldRows() * TILE_SIZE);
		for (const CombatSquare& square : instance->getSquares()) {
			fieldUI.addNew<CombatSquareRenderable>(fieldUI.relhb(square.col * TILE_SIZE, square.row * TILE_SIZE, TILE_SIZE, TILE_SIZE), square)
				.setOnClick([this](CombatSquareRenderable& card) {selectSquare(&card); });
		}
		// Add images for each creature
		creatureUI.setHbOffsetSize(fieldUI.hb->getOffSizeX(), fieldUI.hb->getOffSizeY());
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

	void CombatScreen::recolorSquare(CombatSquareRenderable& square, const sdl::Color& color) {
		square.originalColor = &color;
		if (square.color != color) {
			addVfxNew<UIRecolorVFX>(square, color);
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

	// Reset the highlights to the default state for the turn (i.e. if you are not hovering over anything or clicking on anything)
	// If it is currently the turn of an actor and it is awaiting input, highlight movable squares. Otherwise, clear highlights
	void CombatScreen::resetHighlights() {
		if (activeOccupant) {
			previewMovement(activeOccupant->currentSquare, sdl::COLOR_SKY, activeOccupant->getMovement());
		}
		else {
			clearHighlights();
		}
	}

	void CombatScreen::selectCardRender(CardRenderable* card) {
		selectedCard = card;
		if (selectedCard) {
			if (activeOccupant) {
				previewTargeting(activeOccupant->currentSquare, sdl::COLOR_GOLD, card->card.targetRangeBegin(), card->card.targetRangeEnd(), card->card.targetSizeX(), card->card.targetSizeY());
			}
		}
		else {
			resetHighlights();
		}
	}

	void CombatScreen::selectSquare(CombatSquareRenderable* square) {
		if (square && square->valid) {
			// When clicking on a square while a card is selected, play the card on the square
			if (selectedCard) {

			}
			// When clicking on a square at the end of a highlighted path, move to that square
			else if (!this->selectedPath.empty() && this->selectedPath.back() == &square->square && activeOccupant) {

			}
			// Otherwise, highlight the path to be taken
			else {
				setSelectedPath(instance->findShortestPath(&square->square));
			}
		}
	}

	void CombatScreen::setSelectedPath(vec<const CombatSquare*>&& squares) {
		this->selectedPath = squares;
		// TODO draw arrows over the selected path squares
	}

	void CombatScreen::updateImpl()
	{
		instance->update();

		CombatTurn* currentTurn = instance->getCurrentTurn();
		Action* currentAction = instance->getCurrentAction();
		bool allowInteraction = currentTurn && !currentTurn->isDone && !currentAction;
		endTurnButton.setInteractable(allowInteraction);

		bool cHovered = false;
		for (CardRenderable& card : cardUI) {
			card.setInteractable(allowInteraction);
			if (card.isHovered()) {
				cHovered = true;
			}
		}

		// When hovering over a square, highlight squares. Otherwise, unhighlight them
		bool sqHovered = false;
		for (CombatSquareRenderable& sq : fieldUI) {
			sq.setInteractable(allowInteraction);
			if (sq.isHovered()) {
				sqHovered = true;
				hoverSquareUpdate(&sq);
			}
		}
		if (!sqHovered) {
			hoverSquareUpdate(nullptr);
		}

		// TODO disallow moving when actions are going on

		// When clicking a non-card, unselect the card
		if (sdl::runner::mouseIsLeftJustClicked() && !cHovered && !sqHovered) {
			selectCardRender(nullptr);
		}


		UIScreen::updateImpl();
	}
}