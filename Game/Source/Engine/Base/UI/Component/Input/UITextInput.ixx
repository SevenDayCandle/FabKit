export module fbc.UITextInput;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIInteractable;
import fbc.TextInfo;
import fbc.FUtil;
import fbc.ITextInputter;
import fbc.UITitledInteractable;
import sdl;
import std;

export namespace fbc {
	export class UITextInput : public UITitledInteractable, public TextInfo, public ITextInputter {
	public:
		UITextInput(Hitbox* hb, 
			IDrawable& image = cct.images.panel,
			FFont& textFont = cct.fontRegular()): UITitledInteractable(hb, image), TextInfo(textFont) {
			initCaret(this->font, this->hb->x, this->hb->y);
			UITextInput::onSizeUpdated();
		}
		virtual ~UITextInput() {

		}

		inline UITextInput& setOnBufferUpdate(const func<void(strv)>& onBufferUpdateCallback) { return this->onBufferUpdateCallback = onBufferUpdateCallback, * this; }
		inline UITextInput& setOnComplete(const func<void(strv)>& onComplete) { return this->onComplete = onComplete, *this; }

		void commit(strv text);
		virtual void onSizeUpdated() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl() override;
		virtual void start() override;
		virtual void updateImpl() override;
	protected:
		inline virtual int getLimitWidth() override { return this->hb->w; }

		void clickLeftEvent() override;
		void onBufferUpdated() override;
		void onKeyPress(int32 c) override;
		void resetBuffer() override;
		void updateCaretPos() override;
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

	void UITextInput::onSizeUpdated()
	{
		TextInfo::setPos(cfg.renderScale(24), this->hb->h * 0.25f);
		initCaret(this->font, this->hb->x, this->hb->y);
	}

	void UITextInput::refreshDimensions()
	{
		UITitledInteractable::refreshDimensions();
		updateCache();
	}

	void UITextInput::renderImpl()
	{
		UITitledInteractable::renderImpl();
		TextInfo::drawText(hb->x, hb->y);
		if (sdl::keyboardInputActive(this)) {
			renderCaret();
		}
	}

	void UITextInput::start() 
	{
		buffer = getText();
		ITextInputter::start();
		this->updateCache(buffer, sdl::COLOR_LIME);
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

	void UITextInput::updateCaretPos()
	{
		caret.x = this->hb->x + cfg.renderScale(9) + this->font.measureW(buffer.substr(0, bufferPos));
		caret.y = this->hb->y;
	}

	// When clicked while not focused, start the text input
	void UITextInput::clickLeftEvent()
	{
		if (!sdl::keyboardInputActive()) {
			start();
		}
	}

	// Enter will commit the current text, while Esc will revert any changes
	void UITextInput::onKeyPress(int32 c)
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
			return;
		default:
			ITextInputter::onKeyPress(c);
		}
	}

	void UITextInput::resetBuffer() {
		this->updateCache();
		buffer = getText();
	}
}