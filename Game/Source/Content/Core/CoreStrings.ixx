export module fbc.coreStrings;

import fbc.baseContent;
import fbc.baseStrings;
import fbc.coreConfig;
import fbc.futil;
import raylib;

export namespace fbc {
	export class CoreStrings : public BaseStrings {
	public:
		CoreStrings(BaseContent& cnt) : BaseStrings(cnt) {}
	};
}