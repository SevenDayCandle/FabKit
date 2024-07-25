export module fbc.ItemListing;

import fbc.FUtil;

namespace fbc {
	export struct ItemListing {
		str id;
		int count = 1;
		int upgrades = 0;
	};
}