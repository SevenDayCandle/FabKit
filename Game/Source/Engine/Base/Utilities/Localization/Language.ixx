export module fbc.language;

import fbc.futil;
import fbc.keyedItem;

export namespace fbc {
	export struct Language : KeyedItem<Language> {
		Language(strv key): KeyedItem(key) {}
	};

	export namespace lang {
		export const Language ENG{ "ENG" };
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