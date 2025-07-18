export module fab.UISearchableDropdown;

import fab.FFont;
import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.TextSupplier;
import fab.ScaleHitbox;
import fab.SelectView;
import fab.TextDrawable;
import fab.UIDropdown;
import fab.UIEntry;
import fab.UIInteractable;
import fab.UISelectorList;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export template <typename T> class UISearchableDropdown : public UIDropdown<T>, public TextSupplier {
	public:
		UISearchableDropdown(FWindow& window, uptr<Hitbox>&& hb, uptr<UISelectorList<T>> menu,
			IDrawable& image, IDrawable& arrow, IDrawable& clear,
			FFont& textFont, func<str(EntryView<T>&)>& buttonLabelFunc = {}) :
			UIDropdown<T>(window, move(hb), std::move(menu), image, arrow, clear, textFont, buttonLabelFunc),
			TextSupplier(window) {
			initSearchable();
		}
		UISearchableDropdown(FWindow& window, uptr<Hitbox>&& hb, uptr<UISelectorList<T>> menu, func<str(EntryView<T>&)>& buttonLabelFunc = {}) :
			UISearchableDropdown(window, std::move(hb), std::move(menu),
				window.props.defaultButton(), window.props.defaultArrowSmall(), window.props.defaultClear(),
				window.props.fontRegular(), buttonLabelFunc) {}
		UISearchableDropdown(UISearchableDropdown&& other) noexcept : UIDropdown<T>(other), TextSupplier(other.win) {
			initSearchable();
		};
		virtual ~UISearchableDropdown() override {
			sdl::runner::keyboardInputStopRequest(this);
		}

		inline float getBasePosX() final override { return this->hb->x; }
		inline float getBasePosY() final override { return this->hb->y; }
		inline strv getSourceText() final override { return ""; } // Empty out the search area upon starting and clearing search

		virtual void onChangeItems() override;
		virtual void onSizeUpdated() override;
		virtual void openPopup() override;
		virtual void renderImpl(BatchRenderPass& rp) override;
		virtual void unsetProxy() override;

		inline static UISearchableDropdown multiSearch(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc = futil::toString<T>) {
			return multiSearch(window, std::move(hb), labelFunc, {}, window.props.fontRegular(), window.props.fontRegular(), window.props.defaultBackground(), window.props.defaultButton(), window.props.defaultArrowSmall(), window.props.defaultClear());
		}

		inline static UISearchableDropdown singleSearch(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc = futil::toString<T>) {
			return singleSearch(window, std::move(hb), labelFunc, {}, window.props.fontRegular(), window.props.fontRegular(), window.props.defaultBackground(), window.props.defaultButton(), window.props.defaultArrowSmall(), window.props.defaultClear());
		}

		static UISearchableDropdown multiSearch(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear);
		static UISearchableDropdown singleSearch(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear);
	protected:
		virtual void onSelectionUpdate(EntryView<T>& items) override;
	private:
		str lowercaseText;

		bool checkEntry(const UIEntry<T>* entry);
		void initSearchable();
		void onBufferUpdated() override;
		void releaseBuffer() override;
	};

	template<typename T> void UISearchableDropdown<T>::onChangeItems() {
		// TODO reserve text space equal to max entry length, or the length of the text on the first entry
	}

	template<typename T> void UISearchableDropdown<T>::onSizeUpdated()
	{
		UIDropdown<T>::onSizeUpdated();
		initCaret(this->hb->x, this->hb->y);
	}

	// Whenever this dropdown is open, the text input buffer should be active
	template<typename T> void UISearchableDropdown<T>::openPopup()
	{
		UIDropdown<T>::openPopup();
		this->start();
	}

	template<typename T>void UISearchableDropdown<T>::renderImpl(BatchRenderPass& rp)
	{
		if (sdl::runner::keyboardInputActive(this)) {
			UIInteractable::renderImpl(rp);
			this->buffer.draw(rp, this->hb->x, this->hb->y);
			renderCaret(rp);
			if (this->selectedSize() > 0) {
				this->clear.draw(rp, this->arrowRect, this->rotation, this->UIImage::color);
			}
		}
		else {
			UIDropdown<T>::renderImpl(rp);
		}
	}

	template<typename T> void UISearchableDropdown<T>::unsetProxy()
	{
		UIDropdown<T>::unsetProxy();
		releaseBuffer();
	}

	// Directly set the textInfo text to avoid updating the display textureCache and hiding your text input
	template<typename T> void UISearchableDropdown<T>::onSelectionUpdate(EntryView<T>& items) {
		if (this->isOpen()) {
			this->text.setText(this->getButtonText(items));
		}
		else {
			UIDropdown<T>::onSelectionUpdate(items);
		}
	}

	// An entry matches if the buffer is a prefix of the entry's text
	template<typename T> bool UISearchableDropdown<T>::checkEntry(const UIEntry<T>* entry) {
		strv text = entry->getText();
		if (lowercaseText.size() > text.size()) {
			return false;
		}
		for (int i = 0; i < lowercaseText.size(); ++i) {
			if (std::tolower(text[i]) != lowercaseText[i]) {
				return false;
			}
		}
		return true;
	}

	// The entries displayed in the menu should be filtered by the current buffer text
	template<typename T> void UISearchableDropdown<T>::onBufferUpdated()
	{
		lowercaseText.resize(buffer.getTextLen()); // Cache lowercase version of buffer to reuse for prefix matching
		std::transform(buffer.getTextBegin(), buffer.getTextEnd(), lowercaseText.begin(), [](unsigned char c) {return std::tolower(c); });
		this->menu->refilterRows();
	}

	template<typename T> void UISearchableDropdown<T>::initSearchable()
	{
		this->menu->setFilterFunc([this](const UIEntry<T>* item) {return this->checkEntry(item); });
		this->menu->setOnClose([this]() {this->releaseBuffer(); });
		initCaret(this->hb->x, this->hb->y);
	}

	template<typename T> void UISearchableDropdown<T>::releaseBuffer()
	{
		TextSupplier::releaseBuffer();
		lowercaseText.clear();
		this->menu->refilterRows();
	}

	template<typename T> UISearchableDropdown<T> UISearchableDropdown<T>::multiSearch(
		FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear) {
		Hitbox& ref = *hb;
		return UISearchableDropdown<T>(
			window,
			move(hb),
			UISelectorList<T>::multiList(make_unique<ScaleHitbox>(window, ref.getOffSizeX(), ref.getOffSizeY()), std::move(labelFunc), itemFont, background),
			image,
			arrow,
			clear,
			textFont,
			buttonLabelFunc
		);
	}

	template<typename T> UISearchableDropdown<T> UISearchableDropdown<T>::singleSearch(
		FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear) {
		Hitbox& ref = *hb;
		return UISearchableDropdown<T>(
			window,
			move(hb),
			UISelectorList<T>::singleList(make_unique<ScaleHitbox>(window, ref.getOffSizeX(), ref.getOffSizeY()), std::move(labelFunc), itemFont, background),
			image,
			arrow,
			clear,
			textFont,
			buttonLabelFunc
		);
	}
}