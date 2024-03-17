export module fbc.baseAudio;

import fbc.futil;
import fbc.baseContent;

export namespace fbc {
	export class BaseAudio {
		BaseAudio(const BaseContent& content) : content(content) {}
		virtual ~BaseAudio() {}

		const BaseContent& content;

		virtual void initialize() {};
		virtual void postInitialize() {}
	};
}