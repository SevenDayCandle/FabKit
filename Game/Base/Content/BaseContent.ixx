export module fbc.baseContent;

import fbc.futil;

export namespace fbc::content {

	export class BaseContent {
	public:
		BaseContent(const str& ID): ID(ID) {}
		virtual ~BaseContent() {}

		const str ID;

		virtual void dispose() = 0;
		virtual void initialize() = 0;
		virtual void postInitialize() = 0;
	protected:
		virtual path getContentFolder() = 0;
	};
}