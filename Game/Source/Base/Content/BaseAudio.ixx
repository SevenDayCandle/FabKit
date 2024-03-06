export module fbc.baseAudio;

import fbc.futil;

export namespace fbc::content {
	export class BaseAudio {
		BaseAudio(const str& ID) : ID(ID) {}
		virtual ~BaseAudio() {}

		const str ID;
	};
}