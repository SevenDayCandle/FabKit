export module fbc.UISearchableDropdown;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.ITextInputter;
import fbc.ScaleHitbox;
import fbc.ScreenManager;
import fbc.SelectView;
import fbc.TextInfo;
import fbc.UIDropdown;
import fbc.UIEntry;
import fbc.UIInteractable;
import fbc.UISelectorList;
import sdl;
import std;

namespace fbc {
	export template <typename T> class UISearchableDropdown : public UIDropdown<T>, public ITextInputter {
	public:

		UISearchableDropdown(Hitbox* hb,
			UISelectorList<T>* menu,
			IDrawable& image = cct.images.panel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall,
			FFont& textFont = cct.fontRegular(),
			func<str(EntryView<T>&)>& buttonLabelFunc = {}
		) : UIDropdown<T>(hb, menu, image, arrow, clear, textFont, buttonLabelFunc) {
			initSearchable();
		}
		UISearchableDropdown(Hitbox* hb,
			uptr<UISelectorList<T>> menu,
			IDrawable& image = cct.images.panel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall,
			FFont& textFont = cct.fontRegular(),
			func<str(EntryView<T>&)>& buttonLabelFunc = {}
		) : UIDropdown<T>(hb, std::move(menu), image, arrow, clear, textFont, buttonLabelFunc) {
			initSearchable();
		}
		virtual ~UISearchableDropdown() override {
			sdl::keyboardInputStopRequest(this);
		}

		virtual void onChangeItems() override;
		virtual void onSizeUpdated() override;
		virtual void openPopup() override;
		virtual void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
		virtual void start() override;
		virtual void unsetProxy() override;

		static uptr<UISearchableDropdown> multiSearch(Hitbox* hb,
			func<str(const T&)> labelFunc = futil::toString<T>,
			func<str(EntryView<T>&)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.uiDarkPanelRound,
			IDrawable& image = cct.images.panel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall);
		static uptr<UISearchableDropdown> singleSearch(Hitbox* hb,
			func<str(const T&)> labelFunc = futil::toString<T>,
			func<str(EntryView<T>&)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.uiDarkPanelRound,
			IDrawable& image = cct.images.panel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall);
	protected:
		void updateCaretPos() override;

		virtual void onSelectionUpdate(EntryView<T>& items) override;
	private:
		str lowerBuffer;

		bool checkEntry(const UIEntry<T>* entry);
		void initSearchable();
		void onBufferUpdated() override;
		void resetBuffer() override;
	};

	template<typename T> void UISearchableDropdown<T>::onChangeItems() {
		// TODO reserve text space equal to max entry length, or the length of the text on the first entry
	}

	template<typename T> void UISearchableDropdown<T>::onSizeUpdated()
	{
		UIDropdown<T>::onSizeUpdated();
		this->initCaret(this->font, this->hb->x, this->hb->y);
	}

	// Whenever this dropdown is open, the text input buffer should be active
	template<typename T> void UISearchableDropdown<T>::openPopup()
	{
		UIDropdown<T>::openPopup();
		this->start();
	}

	template<typename T>void UISearchableDropdown<T>::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp)
	{
		if (sdl::keyboardInputActive(this)) {
			UIInteractable::renderImpl(cd, rp);
			TextInfo::drawText(this->hb->x, this->hb->y);
			renderCaret();
			if (this->selectedSize() > 0) {
				this->clear.draw(&this->arrowRect, this->UIImage::color, this->origin, this->rotation);
			}
		}
		else {
			UIDropdown<T>::renderImpl(cd, rp);
		}
	}

	template<typename T> void UISearchableDropdown<T>::start()
	{
		ITextInputter::start();
		this->updateCache(buffer, sdl::COLOR_LIME);
	}

	template<typename T> void UISearchableDropdown<T>::unsetProxy()
	{
		UIDropdown<T>::unsetProxy();
		releaseBuffer();
	}

	// Directly set the textInfo text to avoid updating the display textureCache and hiding your text input
	template<typename T> void UISearchableDropdown<T>::onSelectionUpdate(EntryView<T>& items) {
		if (this->isOpen()) {
			TextInfo::text = this->getButtonText(items);
		}
		else {
			UIDropdown<T>::onSelectionUpdate(items);
		}
	}

	// An entry matches if the buffer is a prefix of the entry's text
	template<typename T> bool UISearchableDropdown<T>::checkEntry(const UIEntry<T>* entry) {
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
		this->menu->setFilterFunc([this](const UIEntry<T>* item) {return this->checkEntry(item); });
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

	template<typename T> void UISearchableDropdown<T>::updateCaretPos()
	{
		caret.x = this->hb->x + cfg.renderScale(9) + this->font.measureW(buffer.substr(0, bufferPos));
		caret.y = this->hb->y;
	}

	template<typename T> uptr<UISearchableDropdown<T>> UISearchableDropdown<T>::multiSearch(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear)
	{
		return std::make_unique<UISearchableDropdown<T>>(
			hb,
			UISelectorList<T>::multiList(new ScaleHitbox(hb->getOffSizeX(), hb->getOffSizeY()), std::move(labelFunc), itemFont, background),
			image,
			arrow,
			clear,
			textFont,
			buttonLabelFunc
		);
	}

	template<typename T> uptr<UISearchableDropdown<T>> UISearchableDropdown<T>::singleSearch(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear)
	{
		return std::make_unique<UISearchableDropdown<T>>(
			hb,
			UISelectorList<T>::singleList(new ScaleHitbox(hb->getOffSizeX(), hb->getOffSizeY()), std::move(labelFunc), itemFont, background),
			image,
			arrow,
			clear,
			textFont,
			buttonLabelFunc
		);
	}


}