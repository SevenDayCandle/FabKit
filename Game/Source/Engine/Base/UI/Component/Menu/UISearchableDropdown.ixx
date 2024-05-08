export module fbc.uiSearchableDropdown;

import fbc.coreConfig;
import fbc.coreContent;
import fbc.ffont;
import fbc.futil;
import fbc.hitbox;
import fbc.iDrawable;
import fbc.screenManager;
import fbc.textInfo;
import fbc.textProvider;
import fbc.uiDropdown;
import fbc.uiEntry;
import fbc.uiInteractable;
import fbc.uiMenu;
import fbc.scaleHitbox;
import sdl;
import std;

export namespace fbc {
	constexpr strv INDICATOR = "|";

	export template <typename T> class UISearchableDropdown : public UIDropdown<T>, public TextProvider {
	public:
		UISearchableDropdown(Hitbox* hb,
			UIMenu<T>* menu,
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall(),
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {}
		) : UIDropdown<T>(hb, menu, image, arrow, textFont, buttonLabelFunc) {
			init();
		}
		UISearchableDropdown(Hitbox* hb,
			uptr<UIMenu<T>> menu,
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall(),
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {}
		) : UIDropdown<T>(hb, std::move(menu), image, arrow, textFont, buttonLabelFunc) {
			init();
		}
		virtual ~UISearchableDropdown() override {
			sdl::keyboardInputStopRequest(this);
		}

		virtual UISearchableDropdown& setOnClose(func<void()> onClose) override;

		virtual void onChangeItems() override;
		virtual void openPopup() override;
		virtual void renderImpl() override;

		static uptr<UISearchableDropdown> multiMenu(Hitbox* hb,
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.flatPanel(),
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall());
		static uptr<UISearchableDropdown> singleMenu(Hitbox* hb,
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.flatPanel(),
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall());
	protected:
		inline void updateCaretPos() override { caretPos.x = this->hb->x + cfg.renderScale(9) + this->font.measureW(buffer.substr(0, bufferPos)); }

		virtual void onSelectionUpdate(vec<UIEntry<T>*>& items) override;
	private:
		str lowerBuffer;

		bool checkEntry(UIEntry<T>* entry);
		void onBufferUpdated() override;
		void init();
		void releaseInput();
	};

	// The menu onClose call should always invoke releaseInput
	template<typename T> UISearchableDropdown<T>& UISearchableDropdown<T>::setOnClose(func<void()> onClose)
	{
		this->menu->setOnClose([this, onClose]() {
			onClose();
			this->releaseInput();
		});
		return *this;
	}


	template<typename T> void UISearchableDropdown<T>::onChangeItems() {
		// TODO reserve text space equal to max entry length, or the length of the text on the first entry
	}

	// Whenever this dropdown is open, the text input buffer should be active
	template<typename T> void UISearchableDropdown<T>::openPopup()
	{
		UIDropdown<T>::openPopup();
		sdl::keyboardInputStart(this);
		this->updateCache(buffer, sdl::COLOR_LIME);
	}

	template<typename T>void UISearchableDropdown<T>::renderImpl()
	{
		if (sdl::keyboardInputActive(this)) {
			UIInteractable::renderImpl();
			float textX = this->hb->x + cfg.renderScale(24);
			float textY = this->hb->y + this->hb->h * 0.25f;
			TextInfo::drawText(textX, textY);
			//sdl::textureSetAlphaMod(caret.texture, 0.5f + 0.5f * std::sin(sdl::ticks()));
			sdl::renderCopy(caret.texture, nullptr, &caretPos);
		}
		else {
			UIDropdown<T>::renderImpl();
		}
	}

	// Directly set the textInfo text to avoid updating the display cache and hiding your text input
	template<typename T> void UISearchableDropdown<T>::onSelectionUpdate(vec<UIEntry<T>*>& items) {
		if (this->isOpen()) {
			TextInfo::text = this->getButtonText(items);
		}
		else {
			UIDropdown<T>::onSelectionUpdate(items);
		}
	}

	// An entry matches if the buffer is a prefix of the entry's text
	template<typename T> bool UISearchableDropdown<T>::checkEntry(UIEntry<T>* entry) {
		strv text = entry->getText();
		if (lowerBuffer.size() > text.size()) {
			return false;
		}
		for (int i = 0; i < lowerBuffer.size(); ++i) {
			if (std::tolower(text[i]) != lowerBuffer[i]) {
				return false;
			}
		}
		return true;
	}

	// The entries displayed in the menu should be filtered by the current buffer text
	template<typename T> void UISearchableDropdown<T>::onBufferUpdated()
	{
		lowerBuffer.resize(buffer.size()); // Cache lowercase version of buffer to reuse for prefix matching
		std::transform(buffer.begin(), buffer.end(), lowerBuffer.begin(), [](unsigned char c) {return std::tolower(c); });
		this->menu->refilterRows();
		this->updateCache(buffer, sdl::COLOR_LIME);
	}

	template<typename T>
	void UISearchableDropdown<T>::init()
	{
		this->menu->setFilterFunc([this](UIEntry<T>* item) {return this->checkEntry(item); });
		this->menu->setOnClose([this]() {this->releaseInput(); });
		caret = this->font.makeTexture(INDICATOR);
		caretPos = { this->hb->x,this->hb->y + this->hb->h * 0.25f , caret.w, caret.h };
	}

	// Reset displayed text to original dropdown text, and release text input
	template<typename T>
	void UISearchableDropdown<T>::releaseInput()
	{
		sdl::keyboardInputStopRequest(this);
		this->updateCache();
		buffer.clear();
		lowerBuffer.clear();
		bufferPos = 0;
		updateCaretPos();
		this->menu->refilterRows();
	}

	template<typename T> uptr<UISearchableDropdown<T>> UISearchableDropdown<T>::multiMenu(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(vec<UIEntry<T>*>)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable* arrow)
	{
		return std::make_unique<UISearchableDropdown<T>>(
			hb,
			UIMenu<T>::multiMenu(new ScaleHitbox(hb->getOffsetSizeX(), hb->getOffsetSizeY()), labelFunc, itemFont, background),
			image,
			arrow,
			textFont,
			buttonLabelFunc
		);
	}

	template<typename T> uptr<UISearchableDropdown<T>> UISearchableDropdown<T>::singleMenu(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(vec<UIEntry<T>*>)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable* arrow)
	{
		return std::make_unique<UISearchableDropdown<T>>(
			hb,
			UIMenu<T>::singleMenu(new ScaleHitbox(hb->getOffsetSizeX(), hb->getOffsetSizeY()), labelFunc, itemFont, background),
			image,
			arrow,
			textFont,
			buttonLabelFunc
		);
	}


}