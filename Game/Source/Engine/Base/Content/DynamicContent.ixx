export module fbc.DynamicContent;

import fbc.FUtil;
import fbc.FTexture;
import fbc.FSound;
import fbc.FMusic;
import fbc.BaseContent;
import fbc.DynamicLoadables;
import sdl;
import std;

export namespace fbc {
	export class DynamicContent : public BaseContent {
	public:
		DynamicContent(strv ID, strv folder): BaseContent(ID, folder) {}
		virtual ~DynamicContent() {}

		DynamicLoadables<FMusic> music = DynamicLoadables<FMusic>(*this);
		DynamicLoadables<FSound> sounds = DynamicLoadables<FSound>(*this);
		DynamicLoadables<FTexture> images = DynamicLoadables<FTexture>(*this);

		inline FMusic* getMusic(strv key) { return music.get(key); }
		inline FSound* getSound(strv key) { return sounds.get(key); }
		inline FTexture* getTexture(strv key) { return images.get(key); }

		void dispose() override;
		void initialize() override;
		void reloadAudio() override;
		void reloadImages() override;
	};

	void DynamicContent::dispose()
	{
		images.dispose();
		music.dispose();
		sounds.dispose();
	}

	void DynamicContent::initialize()
	{
		images.initialize();
		music.initialize();
		sounds.initialize();
	}

	void DynamicContent::reloadAudio()
	{
		music.initialize();
		sounds.initialize();
	}

	void DynamicContent::reloadImages()
	{
		images.initialize();
	}
}