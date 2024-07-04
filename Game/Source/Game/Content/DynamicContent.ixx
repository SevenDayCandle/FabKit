module;

#include "glaze/glaze.hpp"

export module fbc.DynamicContent;

import fbc.BaseContent;
import fbc.BaseStrings;
import fbc.CardData;
import fbc.CoreContent;
import fbc.CreatureData;
import fbc.DynamicLoadables;
import fbc.FMusic;
import fbc.FSound;
import fbc.FTexture;
import fbc.FUtil;
import fbc.PassiveData;
import fbc.StatusData;
import sdl;
import std;

namespace fbc {
	export constexpr strv MANIFEST = "manifest.json";
	export constexpr strv PATH_CARD = "Objects/Cards";
	export constexpr strv PATH_CREATURE = "Objects/Creatures";
	export constexpr strv PATH_ENCOUNTER = "Objects/Encounters";
	export constexpr strv PATH_KEYWORDS = "Objects/Keywords";
	export constexpr strv PATH_PASSIVE = "Objects/Passives";
	export constexpr strv PATH_STATUS = "Objects/Statuses";

	export class DynamicContent : public BaseContent {
	public:
		DynamicContent(strv id, strv folder): BaseContent(id, folder) {}
		~DynamicContent() override {}

		BaseStrings strings = BaseStrings(*this);
		DynamicLoadables<FMusic> music = DynamicLoadables<FMusic>(*this);
		DynamicLoadables<FSound> sounds = DynamicLoadables<FSound>(*this);
		DynamicLoadables<FTexture> images = DynamicLoadables<FTexture>(*this);

		inline FMusic* getMusic(strv key) override { return music.get(key); }
		inline FSound* getSound(strv key) override { return sounds.get(key); }
		inline FTexture* getTexture(strv key) override { return images.get(key); }
		inline void processCards() { setupFolder(PATH_CREATURE, [this](const dir_entry& entry) {processCard(entry.path()); }); }
		inline void processCreatures() { setupFolder(PATH_CREATURE, [this](const dir_entry& entry) {processCreature(entry.path()); }); }

		void dispose() override;
		void initialize() override;
		void postInitialize() override;
		void reloadAudio() override;
		void reloadImages() override;
		void unloadObjects();

		static void loadDynamicContent();
	private:
		void processCard(const path& entry);
		void processCreature(const path& entry);
		void setupFolder(strv base, const func<void(const dir_entry&)>& onRead);
	};

	void DynamicContent::dispose() {
		// TODO de-register creatures, objects, etc.
		images.dispose();
		music.dispose();
		sounds.dispose();
		strings.dispose();
	}

	void DynamicContent::initialize() {
		strings.initialize();
		images.initialize();
		music.initialize();
		sounds.initialize();
	}

	void DynamicContent::postInitialize()
	{
		processCreatures();
		// TODO process other types of stuff
	}

	void DynamicContent::reloadAudio() {
		music.initialize();
		sounds.initialize();
	}

	void DynamicContent::reloadImages() { images.initialize(); }

	// Attempt to parse a card entry
	void DynamicContent::processCard(const path& entry)
	{
		CardData::ExportFields fields;

		auto error = glz::read_file_json(fields, entry.string(), str{});
		if (error) {
			sdl::logError("Failed to load card at path %s", entry.string());
		}
		else {
			CardData::registerData(make_unique<CardData>(*this, entry.filename().string(), fields));
		}
	}

	// Attempt to parse a creature entry
	void DynamicContent::processCreature(const path& entry)
	{
		CreatureData::Fields fields;
		
		auto error = glz::read_file_json(fields, entry.string(), str{});
		if (error) {
			sdl::logError("Failed to load creature at path %s", entry.string());
		}
		else {
			CreatureData::registerData(make_unique<CreatureData>(*this, entry.filename().string(), fields));
		}
		
	}

	void DynamicContent::setupFolder(strv base, const func<void(const dir_entry&)>& onRead)
	{
		path folder = contentFolder;
		folder /= base;
		if (std::filesystem::exists(folder)) {
			for (const dir_entry& entry : std::filesystem::directory_iterator(folder)) {
				if (entry.is_regular_file()) {
					onRead(entry);
				}
			}
		}

	}

	// De-register creatures, objects, etc.
	void DynamicContent::unloadObjects()
	{
		// TODO
	}

	/* STATICS */

	// Generate dynamic content from each folder in the content root folder
	void DynamicContent::loadDynamicContent()
	{
		for (const dir_entry& entry : std::filesystem::directory_iterator(sdl::dirBase() + str(CONTENT_ROOT))) {
			if (std::filesystem::is_directory(entry.status())) {
				path subdir = entry.path();
				path manifestPath = subdir / MANIFEST;

				// TODO process content manifest
				if (std::filesystem::exists(manifestPath)) {
					//processManifest(manifestPath, id);
				}
				else {
					str id = subdir.filename().string();
					cct.registerContent(std::make_unique<DynamicContent>(id, subdir.string()));
				}
			}
		}
	}
}
