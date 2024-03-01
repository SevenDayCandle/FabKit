export module fbc.gameLanguage;

import fbc.futil;

export namespace fbc::loc {
	export enum GameLanguage {
		ENG,
		ZHS,
		ZHT
	};

	str langToStr(GameLanguage lang) {
		switch (lang) {
		case ZHS:
			return "zhs";
		case ZHT:
			return "zht";
		}
		return "eng";
	}
}