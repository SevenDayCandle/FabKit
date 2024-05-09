export module fbc.TextProvider;

import fbc.FFont;
import fbc.futil;
import sdl;
import sdl.IKeyInputListener;
import std;

export namespace fbc {
	constexpr strv INDICATOR = "|";

	export class TextProvider : public sdl::IKeyInputListener {
	public:
		TextProvider() {}
		virtual ~TextProvider() {}

		void releaseBuffer();
		virtual void onKeyPress(int32_t c) override;
		virtual void onTextInput(char* text) override;

	protected:
		int bufferPos = 0;
		str buffer = "";
		sdl::FontRender caret;
		sdl::RectF caretPos;

		void initCaret(FFont& font, float x, float y);
		void renderCaret() const;

		virtual void onBufferUpdated() = 0;
		virtual void resetBuffer() = 0;
		virtual void updateCaretPos() = 0;
	};

	// Resets buffer and releases text input
	void TextProvider::releaseBuffer()
	{
		resetBuffer();
		bufferPos = buffer.size();
		updateCaretPos();
		sdl::keyboardInputStopRequest(this);
	}

	void TextProvider::onKeyPress(int32_t c)
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
	void TextProvider::onTextInput(char* text) {
		if (bufferPos <= buffer.size()) {
			buffer.insert(bufferPos, text);
			bufferPos += std::strlen(text);
			updateCaretPos();
			onBufferUpdated();
		}
	}

	void TextProvider::initCaret(FFont& font, float x, float y)
	{
		caret = font.makeTexture(INDICATOR);
		caretPos = { x,y, caret.w * 1.2f, caret.h * 1.25f };
	}

	// Renders the caret with a smooth fading "animation"
	void TextProvider::renderCaret() const {
		sdl::textureSetAlphaMod(caret.texture, 127 + 127 * std::sin(sdl::ticks() / 100000000.0f));
		sdl::renderCopy(caret.texture, nullptr, &caretPos);
	}
}