export module fbc.BaseContent;

import fbc.futil;
import std;

export namespace fbc {

	export class BaseContent {
		static map<strv, BaseContent&> registeredContents;

	public:
		BaseContent(const strv& ID, const str& contentFolder): ID(ID), contentFolder(contentFolder) {}
		virtual ~BaseContent() {}

		const str ID;
		const str contentFolder;

		virtual void dispose() = 0;
		virtual void initialize() = 0;
		virtual void postInitialize() = 0;

		template <c_ext<BaseContent> T> static T registerContent(const strv& ID, const str& contentFolder);
	};

	template<c_ext<BaseContent> T> T BaseContent::registerContent(const strv& ID, const str& contentFolder)
	{
		T content = T(ID, contentFolder);
		registeredContents[content.ID] = content;
		return content;
	}
}