export module fbc.gameLanguage;

import fbc.futil;
import fbc.keyedItem;

export namespace fbc {
	export struct GameLanguage : KeyedItem<GameLanguage> {
		GameLanguage(strv key): KeyedItem(key) {}
	};

	export namespace lang {
		export const GameLanguage ENG{ "ENG" };
		export const GameLanguage DEU{ "DEU" };
		export const GameLanguage FRA{ "FRA" };
		export const GameLanguage ITA{ "ITA" };
		export const GameLanguage JPN{ "JPN" };
		export const GameLanguage KOR{ "KOR" };
		export const GameLanguage SPA{ "SPA" };
		export const GameLanguage ZHS{ "ZHS" };
		export const GameLanguage ZHT{ "ZHT" };
	}
}