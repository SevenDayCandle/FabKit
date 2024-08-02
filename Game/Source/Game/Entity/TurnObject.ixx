export module fbc.TurnObject;

import fbc.IDrawable;

namespace fbc {
	export class TurnObject {
	public:
		TurnObject() {}
		TurnObject(TurnObject&& other) = default;
		virtual ~TurnObject() = default;

		virtual IDrawable& getImagePortrait() const = 0;
		virtual bool onTurnBegin() = 0;
		virtual void onTurnEnd() = 0;
	};
}