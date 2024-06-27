export module fbc.Effect;

import fbc.BaseContent;
import fbc.EffectData;
import fbc.GameObject;
import fbc.FUtil;
import fbc.Variable;
import std;

export namespace fbc {
	export class Effect {
	public:
		Effect(EffectData& data): data(data) {}
		virtual ~Effect() {}

		const EffectData& data;

		virtual str getText();
		virtual void refresh();

		virtual str getSubText() = 0;
		virtual void use(GameObject* target) = 0;
	protected:
		Effect* parent;
		GameObject* source;
		uptr<Variable> variable;
		vec<uptr<Effect>> childEffects;
	};
}