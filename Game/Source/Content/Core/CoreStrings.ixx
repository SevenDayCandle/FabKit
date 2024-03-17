export module fbc.coreStrings;

import fbc.baseContent;
import fbc.baseStrings;
import fbc.coreConfig;
import fbc.futil;
import raylib;

export namespace fbc {
	export class CoreStrings : public fbc::BaseStrings {
	public:
		CoreStrings(fbc::BaseContent& cnt) : fbc::BaseStrings(cnt) {}
	};
}