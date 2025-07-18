export module fab.UITitle;

import fab.FFont;
import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.Hoverable;
import fab.TextDrawable;
import sdl.SDLBase;
import fab.BatchRenderPass;
import std;

/* Decorator around a Hoverable to give it a title */
namespace fab {
	export template <c_ext<Hoverable> T> class UITitle : public Hoverable {
	public:
		UITitle(T&& item, TextDrawable&& text) :
			ui(move(item)), text(move(text)), Hoverable(item.win) {}
		UITitle(T&& item, FFont& font, strv text, float xOff, float yOff, float w, sdl::Color color, sdl::Color colorOutline) :
			ui(move(item)),
			text(TextDrawable(font, text, w, color, colorOutline)),
			Hoverable(item.win), offX(xOff), offY(yOff) {
			UITitle::onSizeUpdated();
		}
		UITitle(T&& item) :
			UITitle(std::move(item), item.win.props.fontBold(), "", 0, 0, 0, sdl::COLOR_STANDARD, sdl::COLOR_BLACK) {}

		UITitle(UITitle&& other) noexcept : Hoverable(other.win), ui(move(other.ui)), text(move(other.text)) {}

		T ui;
		TextDrawable text;

		operator T* () { return &ui; }
		operator T& () { return ui; }

		inline Hitbox* getHb() final override { return ui.getHb(); }
		inline strv getLabelText() const { return text.getText(); }
		inline virtual float getBeginX() override { return std::min(ui.getHb()->x, ui.getHb()->x + posX); }
		inline virtual float getBeginY() override { return std::min(ui.getHb()->y, ui.getHb()->y + posY); }
		inline virtual void update() override { ui.update(); }
		inline virtual void updateImpl() override { ui.updateImpl(); }

		UITitle<T>& setPos(float xOff, float yOff);
		virtual void onSizeUpdated();
		virtual void refreshDimensions() override;
		virtual void render(BatchRenderPass& rp) override;
		virtual void renderImpl(BatchRenderPass& rp) override;

		inline static uptr<UITitle<T>> make(T&& item, TextDrawable&& text) { 
			return make_unique<UITitle<T>>(forward<T>(item), move(text));
		}
		inline static uptr<UITitle<T>> make(T&& item, FFont& font, strv text = "", float xOff = 0, float yOff = 0, float w = 0, sdl::Color color = sdl::COLOR_STANDARD, sdl::Color colorOutline = sdl::COLOR_BLACK) {
			return make_unique<UITitle<T>>(move(item), font, text, xOff, yOff, w, color, colorOutline);
		}
		inline static uptr<UITitle<T>> make(T&& item) {
			return make_unique<UITitle<T>>(move(item), item.win.props.fontBold(), "", 0, 0, 0, sdl::COLOR_STANDARD, sdl::COLOR_BLACK);
		}
	private:
		float offX = 0;
		float offY = 0;
		float posX = 0;
		float posY = 0;
	};

	template<c_ext<Hoverable> T> UITitle<T>& UITitle<T>::setPos(float xOff, float yOff) {
		this->offX = xOff;
		this->offY = yOff;
		onSizeUpdated();
		return *this;
	}

	template<c_ext<Hoverable> T> void UITitle<T>::onSizeUpdated() {
		this->posX = win.renderScale(offX);
		this->posY = win.renderScale(offY);
	}

	template<c_ext<Hoverable> T> void UITitle<T>::refreshDimensions() {
		ui.refreshDimensions();
		text.reload();
		onSizeUpdated();
	}

	template<c_ext<Hoverable> T> void UITitle<T>::render(BatchRenderPass& rp) {
		ui.render(rp);
		if (ui.enabled) {
			Hitbox& h = *ui.getHb();
			text.drawFull(rp, h.x + posX, h.y + posY);
		}
	}

	template<c_ext<Hoverable> T> void UITitle<T>::renderImpl(BatchRenderPass& rp) {
		ui.renderImpl(rp);
		Hitbox& h = *ui.getHb();
		text.drawFull(rp, h.x + posX, h.y + posY);
	}
}