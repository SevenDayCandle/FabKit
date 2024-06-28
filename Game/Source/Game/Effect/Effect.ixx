export module fbc.Effect;

import fbc.BaseContent;
import fbc.EffectData;
import fbc.FieldObject;
import fbc.GameObject;
import fbc.FUtil;
import fbc.Variable;
import std;

namespace fbc {
	export class Effect {
	public:
		Effect(EffectData& data): data(data) {}
		virtual ~Effect() {}

		const EffectData& data;

		virtual str getText();
		virtual void refresh();

		virtual str getSubText() = 0;
		virtual void use(GameObject* source, FieldObject* target) = 0;
	protected:
		Effect* parent;
		GameObject* owner;
		uptr<Variable> variable;
		vec<uptr<Effect>> childEffects;
	};
}