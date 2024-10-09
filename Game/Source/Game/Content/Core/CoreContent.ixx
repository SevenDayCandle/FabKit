export module fbc.CoreContent;

import fbc.BaseContent;
import fbc.CoreAudio;
import fbc.CoreConfig;
import fbc.CoreImages;
import fbc.CoreStrings;
import fbc.FFont;
import fbc.FMusic;
import fbc.FSound;
import fbc.FTexture;
import fbc.FUtil;
import fbc.FWindow;
import fbc.IDrawable;
import fbc.WindowMode;
import sdl.SDLBase; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export constexpr strv BASE_FOLDER = "/Resources";

	export class CoreContent : public BaseContent, public FWindow::IProps {
	public:
		CoreContent(CoreConfig& cfg, strv id) : BaseContent(cfg, id, sdl::dirBase() + str(BASE_FOLDER)) {}
		CoreContent(CoreContent&& other) noexcept: BaseContent(move(other)), audio(move(other.audio)), images(move(other.images)), strings(move(other.strings)), registeredContents(move(other.registeredContents)), fontBoldData(move(other.fontBoldData)), fontRegularData(move(other.fontRegularData)), fontSmallData(move(other.fontSmallData)) {}

		CoreAudio audio = CoreAudio(*this);
		CoreImages images = CoreImages(*this);
		CoreStrings strings = CoreStrings(*this);

		inline bool getVsync() final { return cfg.graphicsVSync.get(); }
		inline bool hasPressedClose() final { return cfg.actEsc.isKeyJustPressed(); }
		inline bool hasPressedDirDown() final { return cfg.actDirDown.isKeyJustPressed(); }
		inline bool hasPressedDirUp() final { return cfg.actDirUp.isKeyJustPressed(); }
		inline bool hasPressedSelect() final { return cfg.actSelect.isKeyJustPressed(); }
		inline const char* getTitle() override { return "Fabricate"; }
		inline FFont& fontBold() const final { return *fontBoldData; }
		inline FFont& fontRegular() const final { return *fontRegularData; }
		inline FFont& fontSmall() const final { return *fontSmallData; }
		inline float fontScale() const noexcept final { return cfg.fontScale(); }
		inline float renderScale() const noexcept final { return cfg.renderScale(); }
		inline int effectSpeed() const noexcept final { return cfg.graphicsEffectSpeed.get(); }
		inline int getResolutionX() const noexcept final { return cfg.graphicsResolution.get().first; }
		inline int getResolutionY() const noexcept final { return cfg.graphicsResolution.get().second; }
		inline FSound* defaultClick() final { return &audio.uiClick; }
		inline IDrawable& defaultArrow() final { return images.uiArrowIncrement; }
		inline IDrawable& defaultBackground() final { return images.uiDarkPanelRound; }
		inline IDrawable& defaultButton() final { return images.uiPanel; }
		inline IDrawable& defaultCheckboxEmpty() final { return images.uiCheckboxEmpty; }
		inline IDrawable& defaultCheckboxFilled() final { return images.uiCheckboxFilled; }
		inline IDrawable& defaultPanel() final { return images.uiPanel; }
		inline IDrawable& defaultScrollBack() final { return images.uiScrollbar; }
		inline IDrawable& defaultScrollButton() final { return images.uiScrollbutton; }
		inline IDrawable& defaultSlider() final { return images.uiSliderEmpty; }
		inline WindowMode getWindowMode() const final { return cfg.graphicsWindowMode.get(); }

		BaseContent* getContent(strv content);
		FMusic* getMusic(strv content, strv path) const;
		FSound* getSound(strv content, strv path) const;
		FTexture* getTexture(strv content, strv path) const;
		template <c_ext<BaseContent> T> T& registerContent(uptr<T>&& element);
		void dispose() override;
		void initialize() override;
		void initializeContents();
		void initializeFonts();
		void onWindowInitialize(FWindow& window) override;
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

	// Gets a registered content with the designated id
	BaseContent* CoreContent::getContent(strv content)
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second.get();
		}
		return nullptr;
	}

	FMusic* CoreContent::getMusic(strv content, strv path) const
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second->getMusic(path);
		}
		return nullptr;
	}

	FSound* CoreContent::getSound(strv content, strv path) const
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second->getSound(path);
		}
		return nullptr;
	}

	FTexture* CoreContent::getTexture(strv content, strv path) const
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
		strings.initialize();
		audio.initialize();
		images.initialize();
	}

	void CoreContent::initializeContents()
	{
		// TODO order content based on dependencies
		for (uptr<BaseContent>& content : registeredContents | std::views::values) {
			content->initialize();
		}
	}

	void CoreContent::initializeFonts()
	{
		float fontScale = cfg.fontScale();
		fontBoldData = std::make_unique<FFont>(cfg.textFontBold.get(), fontScale, 48, 2, 4);
		fontRegularData = std::make_unique<FFont>(cfg.textFont.get(), fontScale, 48, 0, 4);
		fontSmallData = std::make_unique<FFont>(cfg.textFont.get(), fontScale, 32, 0, 3);
	}

	void CoreContent::onWindowInitialize(FWindow& win) {
		cfg.graphicsResolution.addOnReload([&win](const pair<int, int>& val) {win.refreshSize(val.first, val.second); });
		cfg.graphicsWindowMode.addOnReload([&win](const int& val) {sdl::windowSetFullscreen(win.sdlWindow(), val); });
		cfg.graphicsVSync.addOnReload([&win](const bool& val) { sdl::runner::deviceSetSwapchainParameters(win.sdlWindow(), sdl::GPUSwapchainComposition::SDL_GPU_SWAPCHAINCOMPOSITION_SDR, val ? sdl::GPUPresentMode::SDL_GPU_PRESENTMODE_VSYNC : sdl::GPUPresentMode::SDL_GPU_PRESENTMODE_IMMEDIATE); });
	}

	void CoreContent::postInitialize()
	{
		for (uptr<BaseContent>& content : registeredContents | std::views::values) {
			content->postInitialize();
		}
		cfg.graphicsResolution.addOnReload([this](auto& val) {reloadFonts(); });
		cfg.textFontPercent.addOnReload([this](const int& val) {reloadFonts();});
	}

	void CoreContent::reloadFonts()
	{
		float fontScale = cfg.fontScale();
		fontBoldData->setGlobalScale(fontScale);
		fontRegularData->setGlobalScale(fontScale);
		fontSmallData->setGlobalScale(fontScale);
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
		auto [it, inserted] = registeredContents.try_emplace(refer.id, std::move(element));
		if (!inserted) {
			throw std::logic_error("Duplicate Content with id: " + refer.id);
		}
		return refer;
	}
}