export module fbc.textProvider;

import fbc.futil;
import sdl;
import sdl.iKeyInputListener;
import std;

export namespace fbc {
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

		virtual void onBufferUpdated() = 0;
		virtual void updateCaretPos() = 0;
	};

	// Clears the buffer and releases text input
	void TextProvider::releaseBuffer()
	{
		bufferPos = 0;
		buffer.clear();
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
}