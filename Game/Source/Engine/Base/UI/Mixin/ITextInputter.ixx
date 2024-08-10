export module fbc.ITextInputter;

import fbc.FFont;
import fbc.FUtil;
import sdl;
import sdl.IKeyInputListener;
import std;

namespace fbc {
	export constexpr strv INDICATOR = "|";

	export struct ITextInputter : public sdl::IKeyInputListener {
	public:
		ITextInputter() {}
		virtual ~ITextInputter() override = default;

		virtual void onKeyPress(int32 c) override;
		virtual void onTextInput(const char* text) override;
		void releaseBuffer();
		virtual void start();

	protected:
		int bufferPos = 0;
		str buffer = "";
		sdl::Color caretColor = sdl::COLOR_STANDARD;
		sdl::FontRender caret;

		void initCaret(FFont& font, float x, float y);
		void movePosForCoords(float x, float y);
		void renderCaret(sdl::GpuCommandBuffer* cmd, sdl::GpuRenderPass* rp);

		virtual void onBufferUpdated() = 0;
		virtual void resetBuffer() = 0;
		virtual void updateCaretPos() = 0;
	};

	// Resets buffer and releases text input
	void ITextInputter::releaseBuffer()
	{
		resetBuffer();
		sdl::keyboardInputStopRequest(this);
	}

	void ITextInputter::start() {
		sdl::keyboardInputStart(this);
		bufferPos = buffer.size();
		updateCaretPos();
	}

	void ITextInputter::onKeyPress(int32 c)
	{
		switch (c) {
			// Moves the caret to the end
		case sdl::KEY_DOWN:
			bufferPos = buffer.size();
			updateCaretPos();
			return;
			// clears the buffer and releases text input
		case sdl::KEY_ENTER:
		case sdl::KEY_ESC:
		case sdl::KEY_RETURN:
			releaseBuffer();
			return;
			// Moves the buffer back one position
		case sdl::KEY_LEFT:
			if (bufferPos > 0) {
				bufferPos -= 1;
				updateCaretPos();
			}
			return;
			// Moves the buffer forward one position
		case sdl::KEY_RIGHT:
			if (bufferPos < buffer.size()) {
				bufferPos += 1;
				updateCaretPos();
			}
			return;
			// Moves the caret to the top
		case sdl::KEY_UP:
			bufferPos = 0;
			updateCaretPos();
			return;
			// Backspace removes the last element from the buffer
		case sdl::KEY_BACKSPACE:
			if (bufferPos <= buffer.size() && bufferPos > 0) {
				buffer.erase(bufferPos - 1, 1);
				bufferPos -= 1;
				updateCaretPos();
				onBufferUpdated();
			}
			return;
		}
	}

	// Typing adds characters to the buffer
	void ITextInputter::onTextInput(const char* text) {
		if (bufferPos <= buffer.size()) {
			buffer.insert(bufferPos, text);
			bufferPos += std::strlen(text);
			updateCaretPos();
			onBufferUpdated();
		}
	}

	void ITextInputter::initCaret(FFont& font, float x, float y)
	{
		caret = font.makeTexture(INDICATOR);
		caret.x = x;
		caret.y = y;
		caret.w = caret.w * 1.2f;
		caret.h = caret.h * 1.2f;
	}

	// Renders the caret with a smooth fading "animation"
	void ITextInputter::renderCaret(sdl::GpuCommandBuffer* cmd, sdl::GpuRenderPass* rp) {
		caretColor.a = 0.5f + 0.5f * std::sin(sdl::timeTotal() / 100000000.0f);
		sdl::queueDraw(cmd, rp, caret.texture, &caretColor, caret.x, caret.y, caret.w, caret.h);
	}
}