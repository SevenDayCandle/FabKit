export module fbc.UINumberInput;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIInteractable;
import fbc.TextInfo;
import fbc.FUtil;
import fbc.ITextInputter;
import sdl;
import std;

export namespace fbc {
	export class UINumberInput : public UIInteractable, public TextInfo, public ITextInputter {
	public:
		UINumberInput(Hitbox* hb,
			IDrawable& image = cct.images.smallPanel(),
			FFont& textFont = cct.fontRegular()) : UIInteractable(hb, image), TextInfo(textFont) {
			initCaret(this->font, this->hb->x, this->hb->y);
			UINumberInput::onSizeUpdated();
		}
		virtual ~UINumberInput() {

		}

		inline int getValue() const { return val; }
		inline UINumberInput& setOnBufferUpdate(func<void(int)> onBufferUpdateCallback) { return this->onBufferUpdateCallback = onBufferUpdateCallback, *this; }
		inline UINumberInput& setOnComplete(func<void(int)> onComplete) { return this->onComplete = onComplete, *this; }

		void commit(int num);
		virtual void onSizeUpdated() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		inline virtual int getLimitWidth() override { return this->hb->w; }
		inline void updateCaretPos() override { caret.x = this->hb->x + cfg.renderScale(9) + this->font.measureW(buffer.substr(0, bufferPos)); }

		void clickLeftEvent() override;
		void onBufferUpdated() override;
		void onKeyPress(int32_t c) override;
		void onTextInput(char* text) override;
		void resetBuffer() override;
	private:
		func<void(int)> onBufferUpdateCallback;
		func<void(int)> onComplete;
		int interval = 1;
		int limMax = std::numeric_limits<int>::max();
		int limMin = 0;
		int val = 0;
		int valTemp = 0;

		void applyStep(int val);
		void commitInternal();
	};

	// Commits the number restrained to the limits and invokes the completion callback
	void UINumberInput::commit(int num)
	{
		val = std::clamp(num, limMin, limMax);
		setText(std::to_string(num));
		if (onComplete) {
			onComplete(val);
		}
	}

	void UINumberInput::onSizeUpdated()
	{
		TextInfo::setPos(cfg.renderScale(24), this->hb->h * 0.25f);
	}

	void UINumberInput::renderImpl()
	{
		UIInteractable::renderImpl();
		TextInfo::drawText(hb->x, hb->y);
		if (sdl::keyboardInputActive(this)) {
			renderCaret();
		}
	}

	// When clicking outside of the text input, commit whatever is in the input
	void UINumberInput::updateImpl()
	{
		UIInteractable::updateImpl();
		if (sdl::keyboardInputActive(this) && sdl::mouseIsLeftJustClicked() && !isHovered()) {
			commitInternal();
			releaseBuffer();
		}
	}

	// When clicked while not focused, start the text input
	void UINumberInput::clickLeftEvent()
	{
		if (!sdl::keyboardInputActive()) {
			sdl::keyboardInputStart(this);
			this->updateCache(buffer, sdl::COLOR_LIME);
		}
	}

	// Updates the display text and invokes the buffer change callback
	void UINumberInput::onBufferUpdated()
	{
		try {
			valTemp = std::stoi(buffer);
			valTemp = std::clamp(valTemp, limMin, limMax);
			this->updateCache(buffer, sdl::COLOR_LIME);
			if (onBufferUpdateCallback) {
				onBufferUpdateCallback(valTemp);
			}
		}
		catch (exception e) {
			sdl::logError("UINumberInput failed to parse: %s", e.what());
		}
	}

	/* Enter will commit the current text
		Esc will revert any changes
		Arrow up increments by interval
		Arrow down decrements by interval
	*/
	void UINumberInput::onKeyPress(int32_t c)
	{
		switch (c) {
		case sdl::KEY_ENTER:
		case sdl::KEY_RETURN:
			commitInternal();
			releaseBuffer();
			return;
		case sdl::KEY_ESC:
			this->updateCache();
			releaseBuffer();
			return;
		case sdl::KEY_DOWN:
			applyStep(-interval);
			return;
		case sdl::KEY_UP:
			applyStep(interval);
			return;
		default:
			ITextInputter::onKeyPress(c);
		}
	}

	// Typing only adds numeric characters to the buffer
	void UINumberInput::onTextInput(char* text)
	{
		if (bufferPos <= buffer.size() && futil::isNumeric(text)) {
			buffer.insert(bufferPos, text);
			bufferPos += std::strlen(text);
			updateCaretPos();
			onBufferUpdated();
		}
	}

	void UINumberInput::resetBuffer()
	{
		this->updateCache();
		buffer = getText();
	}

	void UINumberInput::applyStep(int val)
	{
		valTemp = std::clamp(valTemp + val, limMin, limMax);
		buffer = std::to_string(valTemp);
		this->updateCache(buffer, sdl::COLOR_LIME);
		if (onBufferUpdateCallback) {
			onBufferUpdateCallback(valTemp);
		}
	}

	void UINumberInput::commitInternal()
	{
		val = valTemp;
		setText(buffer);
		if (onComplete) {
			onComplete(val);
		}
	}
}