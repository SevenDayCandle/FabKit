export module fbc.Language;

import fbc.FUtil;
import fbc.KeyedItem;

export namespace fbc {
	export struct Language : public KeyedItem<Language> {
		Language(strv key): KeyedItem(key) {}
	};

	export namespace lang {
		export constexpr strv ENG_DEFAULT = "ENG";

		export const Language ENG{ ENG_DEFAULT };
		export const Language DEU{ "DEU" };
		export const Language FRA{ "FRA" };
		export const Language ITA{ "ITA" };
		export const Language JPN{ "JPN" };
		export const Language KOR{ "KOR" };
		export const Language SPA{ "SPA" };
		export const Language ZHS{ "ZHS" };
		export const Language ZHT{ "ZHT" };
	}
}