export module fbc.GenericTip;

import fbc.FUtil;
import fbc.IOverlay;
import std;

namespace fbc {
	export class GenericTip : public IOverlay{
	public:
		GenericTip() {}
		virtual ~GenericTip() = default;

		inline virtual void update() override {}
	};
}