export module fbc.UISearchableDropdown;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.ScreenManager;
import fbc.TextInfo;
import fbc.ITextInputter;
import fbc.UIDropdown;
import fbc.UIEntry;
import fbc.UIInteractable;
import fbc.UIMenu;
import fbc.ScaleHitbox;
import sdl;
import std;

export namespace fbc {
	export template <typename T> class UISearchableDropdown : public UIDropdown<T>, public ITextInputter {
	public:
		UISearchableDropdown(Hitbox* hb,
			UIMenu<T>* menu,
			IDrawable& image = cct.images.panel,
			IDrawable* arrow = &cct.images.uiArrowSmall.get(),
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {}
		) : UIDropdown<T>(hb, menu, image, arrow, textFont, buttonLabelFunc) {
			initSearchable();
		}
		UISearchableDropdown(Hitbox* hb,
			uptr<UIMenu<T>> menu,
			IDrawable& image = cct.images.panel,
			IDrawable* arrow = &cct.images.uiArrowSmall.get(),
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {}
		) : UIDropdown<T>(hb, std::move(menu), image, arrow, textFont, buttonLabelFunc) {
			initSearchable();
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
			IDrawable& background = cct.images.hoverPanel,
			IDrawable& image = cct.images.panel,
			IDrawable* arrow = &cct.images.uiArrowSmall.get());
		static uptr<UISearchableDropdown> singleMenu(Hitbox* hb,
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.hoverPanel,
			IDrawable& image = cct.images.panel,
			IDrawable* arrow = &cct.images.uiArrowSmall.get());
	protected:
		inline void updateCaretPos() override { caret.x = this->hb->x + cfg.renderScale(9) + this->font.measureW(buffer.substr(0, bufferPos)); }

		virtual void onSelectionUpdate(vec<UIEntry<T>*>& items) override;
	private:
		str lowerBuffer;

		bool checkEntry(UIEntry<T>* entry);
		void initSearchable();
		void onBufferUpdated() override;
		void resetBuffer() override;
	};

	// The menu onClose call should always invoke releaseBuffer
	template<typename T> UISearchableDropdown<T>& UISearchableDropdown<T>::setOnClose(func<void()> onClose)
	{
		this->menu->setOnClose([this, onClose]() {
			onClose();
			this->releaseBuffer();
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
			TextInfo::drawText(this->hb->x, this->hb->y);
			renderCaret();
		}
		else {
			UIDropdown<T>::renderImpl();
		}
	}

	// Directly set the textInfo text to avoid updating the display textureCache and hiding your text input
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

	template<typename T> void UISearchableDropdown<T>::initSearchable()
	{
		this->menu->setFilterFunc([this](UIEntry<T>* item) {return this->checkEntry(item); });
		this->menu->setOnClose([this]() {this->releaseBuffer(); });
		this->initCaret(this->font, this->hb->x, this->hb->y);
	}

	template<typename T> void UISearchableDropdown<T>::resetBuffer()
	{
		buffer.clear();
		lowerBuffer.clear();
		this->menu->refilterRows();
		this->updateCache();
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