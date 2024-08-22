export module fbc.UITitle;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.TextDrawable;
import sdl.SDLBase;
import sdl.SDLBatchRenderPass;
import std;

namespace fbc {
	export template <c_ext<FWindow::Hoverable> T> class UITitle : public FWindow::Hoverable {
	public:
		UITitle(T&& item, TextDrawable&& text): ui(move(item)), text(move(text)), Hoverable(item.win) {}
		UITitle(T&& item, FFont& font = cct.fontBold(), strv text = "", float xOff = 0, float yOff = 0, float w = 0, sdl::Color color = sdl::COLOR_STANDARD, sdl::Color colorOutline = sdl::COLOR_BLACK) :
			ui(move(item)),
			text(TextDrawable(font, text, cfg.renderScale(xOff), cfg.renderScale(yOff), w, color, colorOutline)), 
			Hoverable(item.win), xOff(xOff), yOff(yOff) {}
		UITitle(UITitle&& other) noexcept : Hoverable(other.win), ui(move(other.ui)), text(move(other.text)) {}

		T ui;
		TextDrawable text;

		operator T* () { return &ui; }
		operator T& () { return ui; }

		inline Hitbox* getHb() final override { return ui.getHb(); }
		inline strv getLabelText() const { return text.getText(); }
		inline virtual float getBeginX() override { return std::min(ui.getHb()->x, ui.getHb()->x + text.getPosX()); }
		inline virtual float getBeginY() override { return std::min(ui.getHb()->y, ui.getHb()->y + text.getPosY()); }
		inline virtual void update() override { ui.update(); }
		inline virtual void updateImpl() override { ui.updateImpl(); }

		UITitle<T>& setPos(float xOff, float yOff);
		virtual void refreshDimensions() override;
		virtual void render(sdl::SDLBatchRenderPass& rp) override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;

		inline static uptr<UITitle<T>> make(T&& item, TextDrawable&& text) { return make_unique<UITitle<T>>(forward<T>(item), move(text)); }
		inline static uptr<UITitle<T>> make(T&& item, FFont& font = cct.fontBold(), strv text = "", float xOff = 0, float yOff = 0, float w = 0, sdl::Color color = sdl::COLOR_STANDARD, sdl::Color colorOutline = sdl::COLOR_BLACK) { return make_unique<UITitle<T>>(move(item), font, text, xOff, yOff, w, color, colorOutline); }
	private:
		float xOff = 0;
		float yOff = 0;
	};

	template<c_ext<FWindow::Hoverable> T> UITitle<T>& UITitle<T>::setPos(float xOff, float yOff) {
		this->xOff = xOff;
		this->yOff = yOff;
		text.setPos(cfg.renderScale(xOff), cfg.renderScale(yOff));
		return this;
	}

	template<c_ext<FWindow::Hoverable> T> void UITitle<T>::refreshDimensions() {
		ui.refreshDimensions();
		text.reload();
		text.setPos(cfg.renderScale(xOff), cfg.renderScale(yOff));
	}

	template<c_ext<FWindow::Hoverable> T> void UITitle<T>::render(sdl::SDLBatchRenderPass& rp) {
		ui.render(rp);
		if (ui.enabled) {
			text.draw(rp, ui.getHb()->x, ui.getHb()->y, win.getW(), win.getH());
		}
	}

	template<c_ext<FWindow::Hoverable> T> void UITitle<T>::renderImpl(sdl::SDLBatchRenderPass& rp) {
		ui.renderImpl(rp);
		text.draw(rp, ui.getHb()->x, ui.getHb()->y, win.getW(), win.getH());
	}
}