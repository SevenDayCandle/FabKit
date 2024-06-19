export module fbc.DynamicContent;

import fbc.BaseContent;
import fbc.BaseStrings;
import fbc.DynamicLoadables;
import fbc.FMusic;
import fbc.FSound;
import fbc.FTexture;
import fbc.FUtil;
import std;

export namespace fbc {
	export class DynamicContent : public BaseContent {
	public:
		DynamicContent(strv ID, strv folder): BaseContent(ID, folder) {}
		~DynamicContent() override {}

		BaseStrings strings = BaseStrings(*this);
		DynamicLoadables<FMusic> music = DynamicLoadables<FMusic>(*this);
		DynamicLoadables<FSound> sounds = DynamicLoadables<FSound>(*this);
		DynamicLoadables<FTexture> images = DynamicLoadables<FTexture>(*this);

		inline FMusic* getMusic(strv key) override { return music.get(key); }
		inline FSound* getSound(strv key) override { return sounds.get(key); }
		inline FTexture* getTexture(strv key) override { return images.get(key); }

		void dispose() override;
		void initialize() override;
		void reloadAudio() override;
		void reloadImages() override;
	};

	void DynamicContent::dispose() {
		images.dispose();
		music.dispose();
		sounds.dispose();
	}

	void DynamicContent::initialize() {
		images.initialize();
		music.initialize();
		sounds.initialize();
	}

	void DynamicContent::reloadAudio() {
		music.initialize();
		sounds.initialize();
	}

	void DynamicContent::reloadImages() { images.initialize(); }
}
