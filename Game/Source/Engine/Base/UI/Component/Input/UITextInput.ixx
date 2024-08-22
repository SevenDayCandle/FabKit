export module fbc.UITextInput;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextSupplier;
import fbc.TextDrawable;
import fbc.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class UITextInput : public UIInteractable, public TextSupplier {
	public:
		UITextInput(FWindow& window, uptr<Hitbox>&& hb, 
			IDrawable& image = cct.images.uiPanel,
			FFont& textFont = cct.fontRegular()): UIInteractable(window, move(hb), image), TextSupplier(window, textFont) {
			initCaret(this->hb->x, this->hb->y);
			UITextInput::onSizeUpdated();
		}

		inline UITextInput& setOnBufferUpdate(const func<void(strv)>& onBufferUpdateCallback) { return this->onBufferUpdateCallback = onBufferUpdateCallback, * this; }
		inline UITextInput& setOnComplete(const func<void(strv)>& onComplete) { return this->onComplete = onComplete, *this; }

		void commit(strv text);
		virtual void onSizeUpdated() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
	protected:
		inline float getBasePosX() final override { return this->hb->x; }
		inline float getBasePosY() final override { return this->hb->y; }
		inline int getLimitWidth() override { return this->hb->w; }
		inline strv getSourceText() final override { return resText;  }

		void clickLeftEvent() override;
		void onBufferUpdated() override;
		void onKeyPress(int32 c) override;
	private:
		func<void(strv)> onBufferUpdateCallback;
		func<void(strv)> onComplete;
		str resText;
	};

	// Commits the text and invokes the completion callback
	void UITextInput::commit(strv text)
	{
		resText = text;
		if (onComplete) {
			onComplete(resText);
		}
	}

	void UITextInput::onSizeUpdated()
	{
		buffer.setPos(cfg.renderScale(24), this->hb->h * 0.25f);
		initCaret(this->hb->x, this->hb->y);
	}

	void UITextInput::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		buffer.reload();
	}

	void UITextInput::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UIInteractable::renderImpl(rp);
		buffer.draw(rp, hb->x, hb->y, win.getW(), win.getH());
		if (sdl::runner::keyboardInputActive(this)) {
			renderCaret(rp);
		}
	}

	// When clicking outside of the text input, commit whatever is in the input
	void UITextInput::updateImpl()
	{
		UIInteractable::updateImpl();
		if (sdl::runner::keyboardInputActive(this) && sdl::runner::mouseIsLeftJustClicked() && !isHovered()) {
			commit(buffer.getText());
			releaseBuffer();
		}
	}

	// Updates the display text and invokes the buffer change callback
	void UITextInput::onBufferUpdated()
	{
		if (onBufferUpdateCallback) {
			onBufferUpdateCallback(buffer.getText());
		}
	}

	// When clicked while not focused, start the text input
	void UITextInput::clickLeftEvent()
	{
		if (!sdl::runner::keyboardInputActive()) {
			start();
		}
	}

	// Enter will commit the current text, while Esc will revert any changes
	void UITextInput::onKeyPress(int32 c)
	{
		switch (c) {
		case sdl::KEY_ENTER:
		case sdl::KEY_RETURN:
			commit(buffer.getText());
			releaseBuffer();
			return;
		default:
			TextSupplier::onKeyPress(c);
		}
	}
}