export module fab.UITextInput;

import fab.FFont;
import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.TextSupplier;
import fab.TextDrawable;
import fab.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class UITextInput : public UIInteractable, public TextSupplier {
	public:
		UITextInput(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image, FFont& textFont) :
			UIInteractable(window, move(hb), image), TextSupplier(window, textFont) {
			initCaret(this->hb->x, this->hb->y);
			UITextInput::onSizeUpdated();
		}
		UITextInput(FWindow& window, uptr<Hitbox>&& hb) :
			UITextInput(window, std::move(hb), window.props.defaultPanel(), window.props.fontRegular()) {}

		inline UITextInput& setOnBufferUpdate(const func<void(strv)>& onBufferUpdateCallback) { return this->onBufferUpdateCallback = onBufferUpdateCallback, * this; }
		inline UITextInput& setOnBufferUpdate(func<void(strv)>&& onBufferUpdateCallback) { return this->onBufferUpdateCallback = move(onBufferUpdateCallback), *this; }
		inline UITextInput& setOnComplete(const func<void(strv)>& onComplete) { return this->onComplete = onComplete, *this; }
		inline UITextInput& setOnComplete(func<void(strv)>&& onComplete) { return this->onComplete = move(onComplete), *this; }

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
		buffer.drawFull(rp, hb->x + win.renderScale(24), hb->y + hb->h * 0.25f, win.getW(), win.getH());
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