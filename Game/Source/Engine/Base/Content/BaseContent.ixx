export module fbc.BaseContent;

import fbc.FMusic;
import fbc.FSound;
import fbc.FTexture;
import fbc.FUtil;
import std;

export namespace fbc {

	export class BaseContent {
	public:
		BaseContent(strv ID, strv contentFolder): ID(ID), contentFolder(contentFolder) {}
		virtual ~BaseContent() {}

		const str ID;
		const str contentFolder;

		inline virtual FMusic* getMusic(strv path) { return nullptr; }
		inline virtual FSound* getSound(strv path) { return nullptr; }
		inline virtual FTexture* getTexture(strv path) { return nullptr; }

		virtual void reloadAudio() {}
		virtual void reloadImages() {}

		virtual void dispose() = 0;
		virtual void initialize() = 0;
		virtual void postInitialize() = 0;
	};


}