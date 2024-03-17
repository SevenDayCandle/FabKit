export module fbc.baseContent;

import fbc.futil;

export namespace fbc {

	export class BaseContent {
	public:
		BaseContent(const strv& ID, const str& contentFolder): ID(ID), contentFolder(contentFolder) {}
		virtual ~BaseContent() {}

		const str ID;
		const str contentFolder;

		virtual void dispose() = 0;
		virtual void initialize() = 0;
		virtual void postInitialize() = 0;
	};
}