export module fbc.gameLanguage;

import fbc.futil;
import fbc.keyedItem;

export namespace fbc {
	export struct GameLanguage : keyed_item<GameLanguage> {
		GameLanguage(strv key): keyed_item(key) {}
	};

	export namespace lang {
		export const GameLanguage ENG{ "ENG" };
		export const GameLanguage FRA{ "FRA" };
		export const GameLanguage SPA{ "SPA" };
		export const GameLanguage ZHS{ "ZHS" };
		export const GameLanguage ZHT{ "ZHT" };
	}
}