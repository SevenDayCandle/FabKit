export module fbc.UITextInput;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIInteractable;
import fbc.TextInfo;
import fbc.FUtil;
import fbc.TextProvider;
import sdl;
import std;

export namespace fbc {
	export class UITextInput : public UIInteractable, public TextInfo, public TextProvider {
	public:
		UITextInput(Hitbox* hb, 
			IDrawable& image = cct.images.smallPanel(),
			FFont& textFont = cct.fontRegular()): UIInteractable(hb, image), TextInfo(textFont) {
			initCaret(this->font, this->hb->x, this->hb->y);
		}
		virtual ~UITextInput() {

		}

		inline UITextInput& setOnBufferUpdate(func<void(strv)> onBufferUpdateCallback) { return this->onBufferUpdateCallback = onBufferUpdateCallback, * this; }
		inline UITextInput& setOnComplete(func<void(strv)> onComplete) { return this->onComplete = onComplete, *this; }

		void commit(strv text);
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		inline virtual int getLimitWidth() override { return this->hb->w; }
		inline void updateCaretPos() override { caretPos.x = this->hb->x + cfg.renderScale(9) + this->font.measureW(buffer.substr(0, bufferPos)); }

		void clickLeftEvent() override;
		void onBufferUpdated() override;
		void onKeyPress(int32_t c) override;
		void resetBuffer() override;
	private:
		func<void(strv)> onBufferUpdateCallback;
		func<void(strv)> onComplete;
	};

	// Commits the text and invokes the completion callback
	void UITextInput::commit(strv text)
	{
		setText(str(text));
		if (onComplete) {
			onComplete(this->getText());
		}
	}

	void UITextInput::renderImpl()
	{
		UIInteractable::renderImpl();
		float textX = this->hb->x + cfg.renderScale(24);
		float textY = this->hb->y + this->hb->h * 0.25f;
		TextInfo::drawText(textX, textY);
		if (sdl::keyboardInputActive(this)) {
			renderCaret();
		}
	}

	// When clicking outside of the text input, commit whatever is in the input
	void UITextInput::updateImpl()
	{
		UIInteractable::updateImpl();
		if (sdl::keyboardInputActive(this) && sdl::mouseIsLeftJustClicked() && !isHovered()) {
			commit(buffer);
			releaseBuffer();
		}
	}

	// Updates the display text and invokes the buffer change callback
	void UITextInput::onBufferUpdated()
	{
		this->updateCache(buffer, sdl::COLOR_LIME);
		if (onBufferUpdateCallback) {
			onBufferUpdateCallback(buffer);
		}
	}

	// When clicked while not focused, start the text input
	void UITextInput::clickLeftEvent()
	{
		if (!sdl::keyboardInputActive()) {
			sdl::keyboardInputStart(this);
			this->updateCache(buffer, sdl::COLOR_LIME);
		}
	}

	// Enter will commit the current text, while Esc will revert any changes
	void UITextInput::onKeyPress(int32_t c)
	{
		switch (c) {
		case sdl::KEY_ENTER:
		case sdl::KEY_RETURN:
			commit(buffer);
			releaseBuffer();
			return;
		case sdl::KEY_ESC:
			this->updateCache();
			releaseBuffer();
		default:
			TextProvider::onKeyPress(c);
		}
	}

	void UITextInput::resetBuffer() {
		this->updateCache();
		buffer = getText();
	}
}