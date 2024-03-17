export module fbc.gameLanguage;

import fbc.futil;

export namespace fbc {
	export enum GameLanguage {
		ENG,
		ZHS,
		ZHT
	};

	str langToStr(GameLanguage lang) {
		switch (lang) {
		case ZHS:
			return "ZHS";
		case ZHT:
			return "ZHT";
		}
		return "ENG";
	}
}