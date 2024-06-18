export module fbc.BaseContent;

import fbc.FUtil;
import std;

export namespace fbc {

	export class BaseContent {
	public:
		BaseContent(strv ID, strv contentFolder): ID(ID), contentFolder(contentFolder) {}
		virtual ~BaseContent() {}

		const str ID;
		const str contentFolder;

		virtual void reloadImages() {}

		virtual void dispose() = 0;
		virtual void initialize() = 0;
		virtual void postInitialize() = 0;
	};


}