export module fbc.BaseAudio;

import fbc.futil;
import fbc.BaseContent;

export namespace fbc {
	export class BaseAudio {
		BaseAudio(const BaseContent& content) : content(content) {}
		virtual ~BaseAudio() {}

		const BaseContent& content;

		virtual void initialize() {};
		virtual void postInitialize() {}
	};
}