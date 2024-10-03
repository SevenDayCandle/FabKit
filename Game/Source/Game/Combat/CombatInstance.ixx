export module fbc.CombatInstance;

import fbc.Action;
import fbc.CallbackVFX;
import fbc.Card;
import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.CreatureMoveAction;
import fbc.EncounterCreatureEntry;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.PileType;
import fbc.RunEncounter;
import fbc.SavedCreatureEntry;
import fbc.SequentialAction;
import fbc.TurnObject;
import std;

namespace fbc {
	export constexpr int DEFAULT_ROUND_LENGTH = 100;
	constexpr arr<int, 4> DIR_X = { -1, 1, 0, 0 };
	constexpr arr<int, 4> DIR_Y = { 0, 0, -1, 1 };

	export class CombatInstance {
	public:
		struct IViewSubscriber {
			virtual ~IViewSubscriber() = default;

			virtual uptr<CallbackVFX> cardMoveVFX(const Card* card, const OccupantObject* owner, const PileType& type) { return uptr<CallbackVFX>(); }
			virtual uptr<CallbackVFX> creatureMoveVFX(const OccupantObject* occupant, const CombatSquare* target) { return uptr<CallbackVFX>(); }
			virtual void onPlayerTurnBegin(const CombatTurn* turn) {}
			virtual void onPlayerTurnEnd(const CombatTurn* turn) {}
			virtual void onTurnAdded(const CombatTurn& turn) {}
			virtual void onTurnChanged(ref_view<const mset<CombatTurn>> turns) {}
			virtual void onTurnRemoved(const CombatTurn* turn) {}
		};
		CombatInstance() {}

		IViewSubscriber* viewSubscriber;

		inline auto getOccupants() { return std::views::transform(occupants, [](uptr<OccupantObject>& item) {return item.get(); }); }
		inline bool hasAction() const { return currentAction != nullptr; }
		inline bool isCompleted() const { return completed; }
		inline CombatSquare* getDistanceSource() const { return distanceSource; }
		inline CombatTurn* getCurrentTurn() const { return currentTurn; }
		inline Action* getCurrentAction() const { return currentAction; }
		inline int getCurrentRound() const { return totalActionTime / roundTime; }
		inline int getFieldColumns() const { return fieldColumns; }
		inline int getFieldRows() const { return fieldRows; }
		inline int getTotalActionTime() const { return totalActionTime; }
		inline ref_view<const mset<CombatTurn>> getTurns() const { return std::views::all(turns); }
		inline ref_view<const vec<CombatSquare>> getSquares() const { return std::views::all(squares); }
		template <c_ext<Action> T> inline T& queueAction(uptr<T>&& action) {
			T& ref = *action;
			queueActionImpl(move(action));
			return ref;
		}
		template <c_ext<Action> T, typename... Args> requires std::constructible_from<T, Args&&...> inline T& queueActionNew(Args&&... args) { return queueActionGet(make_unique<T>(forward<Args>(args)...)); };

		bool modifyTurnOrder(const TurnObject& target, int diff);
		bool nextTurn();
		bool update();
		CombatSquare* getSquare(int col, int row);
		CreatureMoveAction& queueOccupantMove(OccupantObject* occupant, CombatSquare* target);
		int getDistanceTo(CombatSquare* square);
		OccupantObject* getCurrentActor() const;
		SequentialAction& queueOccupantPath(OccupantObject* occupant, vec<CombatSquare*> path);
		vec<const CombatSquare*> findShortestPath(const CombatSquare* targ);
		void endCombat();
		void endCurrentTurn();
		void fillDistances(CombatSquare* source);
		void initialize(RunEncounter& encounter, vec<SavedCreatureEntry>& runCreatures, int playerFaction);
		void queueActionImpl(uptr<Action>&& action);
		void queueCompleteTurn();
		void queueTurn(TurnObject& source, int actionValue);
	private:
		bool completed;
		CombatSquare* distanceSource;
		CombatTurn* currentTurn;
		deque<uptr<Action>> actionQueue;
		Action* currentAction;
		mset<CombatTurn> turns;
		int fieldColumns = 1;
		int fieldRows = 1;
		int roundTime = DEFAULT_ROUND_LENGTH;
		int totalActionTime = 0;
		vec<CombatSquare> squares;
		vec<uptr<OccupantObject>> occupants;

		inline int getSquareIndex(int col, int row) const { return col + fieldColumns * row; }

		int getSquareIndexAllowRandom(int col, int row);
	};
}