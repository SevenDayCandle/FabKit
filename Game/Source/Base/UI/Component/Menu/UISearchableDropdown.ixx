export module fbc.uiSearchableDropdown;

import fbc.coreConfig;
import fbc.coreContent;
import fbc.ffont;
import fbc.futil;
import fbc.hitbox;
import fbc.iDrawable;
import fbc.screenManager;
import fbc.textInfo;
import fbc.uiDropdown;
import fbc.uiEntry;
import fbc.uiImage;
import fbc.uiMenu;
import fbc.scaleHitbox;
import sdl;
import sdl.iKeyInputListener;
import std;

export namespace fbc {
	constexpr strv INDICATOR = "|";

	export template <typename T> class UISearchableDropdown : public UIDropdown<T>, sdl::IKeyInputListener {
	public:
		UISearchableDropdown(Hitbox* hb,
			UIMenu<T>* menu,
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall(),
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {}
		) : UIDropdown<T>(hb, menu, image, arrow, textFont, buttonLabelFunc) {
			this->menu->setFilterFunc([this](UIEntry<T>* item) {return this->checkEntry(item); });
			this->menu->setOnClose([this]() {this->releaseInput(); });
			indicator = textFont.makeTexture(INDICATOR);
		}
		UISearchableDropdown(Hitbox* hb,
			uptr<UIMenu<T>> menu,
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall(),
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {}
		) : UIDropdown<T>(hb, std::move(menu), image, arrow, textFont, buttonLabelFunc) {
			this->menu->setFilterFunc([this](UIEntry<T>* item) {return this->checkEntry(item); });
			this->menu->setOnClose([this]() {this->releaseInput(); });
			indicator = textFont.makeTexture(INDICATOR);
		}
		virtual ~UISearchableDropdown() {
			sdl::keyboardInputStopRequest(this);
		}

		virtual UISearchableDropdown& setOnClose(func<void()> onClose) override;

		virtual void onBackspace() override;
		virtual void onChangeItems() override;
		virtual void onTextInput(char* text) override;
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
		virtual void onSelectionUpdate(vec<UIEntry<T>*> items) override;
	private:
		int bufferPos;
		str buffer;
		str lowerBuffer;
		str ogText;
		FFontRender indicator;

		bool checkEntry(UIEntry<T>* entry);
		void onBufferUpdated();
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

	// Backspace removes the last element from the buffer
	template<typename T> void UISearchableDropdown<T>::onBackspace() {
		if (bufferPos <= buffer.size() && bufferPos > 0) {
			buffer.erase(bufferPos - 1, 1);
			bufferPos -= 1;
			onBufferUpdated();
		}
	}

	template<typename T> void UISearchableDropdown<T>::onChangeItems() {
		// TODO reserve text space equal to max entry length, or the length of the text on the first entry
	}

	// Typing adds characters to the buffer
	template<typename T> void UISearchableDropdown<T>::onTextInput(char* text) {
		if (bufferPos <= buffer.size()) {
			buffer.insert(bufferPos, text);
			bufferPos += std::strlen(text);
			onBufferUpdated();
		}
	}

	// Whenever this dropdown is open, the text input buffer should be active
	template<typename T> void UISearchableDropdown<T>::openPopup()
	{
		UIDropdown<T>::openPopup();
		sdl::keyboardInputStart(this);
		bufferPos = buffer.size();
	}

	template<typename T>void UISearchableDropdown<T>::renderImpl()
	{
		if (sdl::keyboardInputActive(this)) {
			UIImage::renderImpl();
			float textX = this->hb->x + cfg.renderScale(24);
			float textY = this->hb->y + this->hb->h * 0.25f;
			TextInfo::drawText(textX, textY);
			sdl::RectF target = { textX + this->getTextWidth(), textY, indicator.w, indicator.h };
			//sdl::textureSetAlphaMod(indicator.texture, 0.5f + 0.5f * std::sin(sdl::ticks()));
			sdl::renderCopy(indicator.texture, nullptr, &target);
		}
		else {
			UIDropdown<T>::renderImpl();
		}
	}

	// We need to keep track of the original text to restore it when the dropdown is closed
	template<typename T> void UISearchableDropdown<T>::onSelectionUpdate(vec<UIEntry<T>*> items) {
		UIDropdown<T>::onSelectionUpdate(items);
		ogText = this->getText();
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
		this->set(buffer, sdl::COLOR_LIME);
	}

	// Reset displayed text to original dropdown text, and release text input
	template<typename T>
	void UISearchableDropdown<T>::releaseInput()
	{
		sdl::keyboardInputStopRequest(this);
		this->set(ogText, sdl::COLOR_WHITE);
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