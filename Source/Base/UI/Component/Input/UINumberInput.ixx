export module fab.UINumberInput;

import fab.FFont;
import fab.FWindow;
import fab.FUtil;
import fab.Hitbox;
import fab.IDrawable;
import fab.TextSupplier;
import fab.TextDrawable;
import fab.UIButton;
import fab.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class UINumberInput : public UIInteractable, public TextSupplier {
	public:
		UINumberInput(FWindow& window, uptr<Hitbox>&& hb, int limMin, int limMax, IDrawable& image, IDrawable& arrow, FFont& textFont) : 
			TextSupplier(window, textFont), UIInteractable(window, move(hb), image), limMin(limMin), limMax(limMax), arrow(arrow) {
			initCaret(this->hb->x, this->hb->y);
			UINumberInput::onSizeUpdated();
		}
		UINumberInput(FWindow& window, uptr<Hitbox>&& hb, int limMin, int limMax, IDrawable& image) :
			UINumberInput(window, move(hb), limMin, limMax, image, window.props.defaultArrow(), window.props.fontRegular()) {}
		UINumberInput(FWindow& window, uptr<Hitbox>&& hb, int limMin = 0, int limMax = std::numeric_limits<int>::max()) :
			UINumberInput(window, move(hb), limMin, limMax, window.props.defaultPanel(), window.props.defaultArrow(), window.props.fontRegular()) {}

		inline int getValue() const { return val; }
		inline UINumberInput& setOnBufferUpdate(const func<void(int)>& onBufferUpdateCallback) { return this->onBufferUpdateCallback = onBufferUpdateCallback, *this; }
		inline UINumberInput& setOnBufferUpdate(func<void(int)>&& onBufferUpdateCallback) { return this->onBufferUpdateCallback = move(onBufferUpdateCallback), *this; }
		inline UINumberInput& setOnComplete(const func<void(int)>& onComplete) { return this->onComplete = onComplete, *this; }
		inline UINumberInput& setOnComplete(func<void(int)>&& onComplete) { return this->onComplete = move(onComplete), *this; }

		void commit(int num);
		virtual UINumberInput& setLimits(int limMin, int limMax);
		virtual UINumberInput& setValue(int num);
		virtual void onSizeUpdated() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
	protected:
		int limMax = std::numeric_limits<int>::max();
		int limMin = 0;

		inline float getBasePosX() final override { return this->hb->x; }
		inline float getBasePosY() final override { return this->hb->y; }
		inline strv getSourceText() final override { return futil::toString(val); }
		inline void doOnComplete(int val) { if (onComplete) onComplete(val); }

		virtual void commitInternal();
		void clickLeftEvent() override;
		void onBufferUpdated() override;
		void onKeyPress(int32 c) override;
		void onTextInput(const char* text) override;
	private:
		func<void(int)> onBufferUpdateCallback;
		func<void(int)> onComplete;
		IDrawable& arrow;
		sdl::RectF lessRect;
		sdl::RectF moreRect;
		int interval = 1;
		int val = 0;
		int valTemp = 0;

		void modifyDuringInput(int val);
	};

	// Commits the number restrained to the limits and invokes the completion callback
	void UINumberInput::commit(int num)
	{
		setValue(num);
		doOnComplete(num);
	}

	// Sets the limits to constrain inputted values
	UINumberInput& UINumberInput::setLimits(int limMin, int limMax)
	{
		this->limMin = limMin;
		this->limMax = limMax;
		if (val < limMin || val > limMax) {
			setValue(val);
		}
		return *this;
	}

	void UINumberInput::onSizeUpdated()
	{
		moreRect.w = moreRect.h = lessRect.w = lessRect.h = hb->h / 2;
	}

	void UINumberInput::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		buffer.reload();
	}

	void UINumberInput::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UIInteractable::renderImpl(rp);
		buffer.draw(rp, hb->x + win.renderScale(24), hb->y + hb->h * 0.25f, win.getW(), win.getH());
		arrow.draw(rp, lessRect, win.getW(), win.getH());
		arrow.draw(rp, moreRect, win.getW(), win.getH(), 1, -1);
		if (sdl::runner::keyboardInputActive(this)) {
			renderCaret(rp);
		}
	}

	// Sets the number restrained to the limits WITHOUT invoking the completion callback
	UINumberInput& UINumberInput::setValue(int num)
	{
		valTemp = val = std::clamp(num, limMin, limMax);
		buffer.setText(std::to_string(num));
		return *this;
	}

	// When clicking outside of the text input, commit whatever is in the input
	void UINumberInput::updateImpl()
	{
		UIInteractable::updateImpl();
		moreRect.x = lessRect.x = hb->x + hb->w - moreRect.w;
		moreRect.y = hb->y;
		lessRect.y = hb->y + moreRect.h;
		if (sdl::runner::keyboardInputActive(this) && sdl::runner::mouseIsLeftJustClicked() && !isHovered()) {
			commitInternal();
			releaseBuffer();
		}
	}

	// When clicked while not focused, start the text input
	void UINumberInput::clickLeftEvent()
	{
		if (!sdl::runner::keyboardInputActive()) {
			if (sdl::runner::mouseIsHovering(lessRect)) {
				commit(val - interval);
			}
			else if (sdl::runner::mouseIsHovering(moreRect)) {
				commit(val + interval);
			}
			else {
				start();
			}
		}
		else if (sdl::runner::mouseIsHovering(lessRect)) {
			modifyDuringInput(valTemp - interval);
		}
		else if (sdl::runner::mouseIsHovering(moreRect)) {
			modifyDuringInput(valTemp + interval);
		}
	}

	// Updates the display text and invokes the buffer change callback
	void UINumberInput::onBufferUpdated()
	{
		try {
			if (buffer.empty()) {
				valTemp = std::max(0, limMin);
			}
			else {
				valTemp = std::stoi(str(buffer.getText()));
				valTemp = std::clamp(valTemp, limMin, limMax);
			}
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
	void UINumberInput::onKeyPress(int32 c)
	{
		switch (c) {
		case sdl::KEY_ENTER:
		case sdl::KEY_RETURN:
			commitInternal();
			releaseBuffer();
			return;
		case sdl::KEY_DOWN:
			modifyDuringInput(valTemp - interval);
			return;
		case sdl::KEY_UP:
			modifyDuringInput(valTemp + interval);
			return;
		default:
			TextSupplier::onKeyPress(c);
		}
	}

	// Typing only adds numeric characters to the buffer
	void UINumberInput::onTextInput(const char* text)
	{
		if (bufferPos <= buffer.getTextLen() && futil::isNumeric(text)) {
			buffer.textInsert(bufferPos, text);
			bufferPos += std::strlen(text);
			updateCaretPos();
			onBufferUpdated();
		}
	}

	void UINumberInput::commitInternal()
	{
		val = valTemp;
		if (onComplete) {
			onComplete(val);
		}
	}

	void UINumberInput::modifyDuringInput(int val)
	{
		valTemp = std::clamp(val, limMin, limMax);
		buffer.set(std::to_string(valTemp), sdl::COLOR_LIME);
		if (onBufferUpdateCallback) {
			onBufferUpdateCallback(valTemp);
		}
	}
}