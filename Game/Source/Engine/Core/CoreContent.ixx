export module fbc.CoreContent;

import fbc.BaseContent;
import fbc.CoreAudio;
import fbc.CoreConfig;
import fbc.CoreImages;
import fbc.CoreStrings;
import fbc.DynamicContent;
import fbc.FFont;
import fbc.FMusic;
import fbc.FSound;
import fbc.FTexture;
import fbc.FUtil;
import sdl;
import std;

export namespace fbc {
	constexpr strv BASE_FOLDER = "/Resources";
	constexpr strv MANIFEST = "manifest.json";

	export class CoreContent : public BaseContent {
	public:
		CoreContent(strv ID) : BaseContent(ID, sdl::dirBase() + str(BASE_FOLDER)) {}

		CoreAudio audio = CoreAudio(*this);
		CoreImages images = CoreImages(*this);
		CoreStrings strings = CoreStrings(*this);

		inline FFont& fontBold() { return *fontBoldData; }
		inline FFont& fontRegular() { return *fontRegularData; }
		inline FFont& fontSmall() { return *fontSmallData; }

		BaseContent* getContent(strv content);
		FMusic* getMusic(strv content, strv path);
		FSound* getSound(strv content, strv path);
		FTexture* getTexture(strv content, strv path);
		template <c_ext<BaseContent> T> T& registerContent(uptr<T>&& element);
		void dispose() override;
		void initialize() override;
		void initializeFonts();
		void loadDynamicContent();
		void postInitialize() override;
		void reloadAudio() override;
		void reloadFonts();
		void reloadImages() override;

	private:
		map<strv, uptr<BaseContent>> registeredContents;
		uptr<FFont> fontBoldData;
		uptr<FFont> fontRegularData;
		uptr<FFont> fontSmallData;
	};

	export CoreContent cct = CoreContent(futil::FBC);

	// Gets a registered content with the designated ID
	BaseContent* CoreContent::getContent(strv content)
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second.get();
		}
		return nullptr;
	}

	FMusic* CoreContent::getMusic(strv content, strv path)
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second->getMusic(path);
		}
		return nullptr;
	}

	FSound* CoreContent::getSound(strv content, strv path)
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second->getSound(path);
		}
		return nullptr;
	}

	FTexture* CoreContent::getTexture(strv content, strv path)
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second->getTexture(path);
		}
		return nullptr;
	}

	void CoreContent::dispose()
	{
		for (uptr<BaseContent>& content : registeredContents | std::views::values) {
			content->dispose();
		}
		audio.dispose();
		images.dispose();
		strings.dispose();
		fontBoldData = nullptr;
		fontRegularData = nullptr;
		fontSmallData = nullptr;
	}

	// Set up the core content as well as all registered contents. Dynamic content is also initialized in this step
	void CoreContent::initialize()
	{
		initializeFonts();
		audio.initialize();
		images.initialize();
		strings.initialize();

		loadDynamicContent();

		for (uptr<BaseContent>& content : registeredContents | std::views::values) {
			content->initialize();
		}
	}

	void CoreContent::initializeFonts()
	{
		fontBoldData = std::make_unique<FFont>(cfg.textFontBold.get(), 48, 2, 4);
		fontRegularData = std::make_unique<FFont>(cfg.textFont.get(), 48, 0, 4);
		fontSmallData = std::make_unique<FFont>(cfg.textFont.get(), 32, 0, 3);
	}

	// Generate dynamic content from each folder in the content root folder
	void CoreContent::loadDynamicContent()
	{
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(sdl::dirBase() + str(CONTENT_ROOT))) {
			if (std::filesystem::is_directory(entry.status())) {
				path subdir = entry.path();
				path manifestPath = subdir / MANIFEST;

				// TODO process content manifest
				if (std::filesystem::exists(manifestPath)) {
					//processManifest(manifestPath, id);
				}
				else {
					str id = subdir.filename().string();
					auto [it, inserted] = registeredContents.emplace(std::piecewise_construct,
						std::forward_as_tuple(id),
						std::forward_as_tuple(std::make_unique<DynamicContent>(id, subdir.string())));
				}
			}
		}
	}

	void CoreContent::postInitialize()
	{
		for (uptr<BaseContent>& content : registeredContents | std::views::values) {
			content->postInitialize();
		}
	}

	void CoreContent::reloadFonts()
	{
		fontBoldData->reload();
		fontRegularData->reload();
		fontSmallData->reload();
	}

	void CoreContent::reloadAudio()
	{
		audio.initialize();
		for (uptr<BaseContent>& content : registeredContents | std::views::values) {
			content->reloadAudio();
		}
	}

	void CoreContent::reloadImages()
	{
		images.initialize();
		for (uptr<BaseContent>& content : registeredContents | std::views::values) {
			content->reloadImages();
		}
	}

	// Adds a content object to be managed by the core content
	template<c_ext<BaseContent> T> T& CoreContent::registerContent(uptr<T>&& element)
	{
		T& refer = *element;
		auto [it, inserted] = registeredContents.try_emplace(refer.ID, std::move(element));
		if (!inserted) {
			throw std::logic_error("Duplicate Content with ID: " + refer.ID);
		}
		return refer;
	}
}