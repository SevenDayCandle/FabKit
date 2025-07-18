export module fab.TextSupplier;

import fab.FFont;
import fab.FWindow;
import fab.FUtil;
import fab.RectDrawable;
import fab.TextDrawable;
import sdl.SDLBase;
import fab.BatchRenderPass;
import sdl.SDLRunner;
import sdl.IKeyInputListener;
import std;

namespace fab {
	export class TextSupplier : public sdl::IKeyInputListener {
	public:
		TextSupplier(FWindow& window, FFont& textFont) :
			buffer(textFont, "", getLimitWidth()), fwindow(window) {}

		TextSupplier(FWindow& window) :
			TextSupplier(window, window.props.fontRegular()) {}

		TextSupplier(TextSupplier&& other) noexcept = default;
		~TextSupplier() override = default;

		void onKeyPress(int32 c) override;
		void onTextInput(const char* text) override;
		virtual void releaseBuffer();
		virtual void start();
	protected:
		float caretPosX;
		float caretPosY;
		float caretSizeX;
		float caretSizeY;
		int bufferPos = 0;
		RectDrawable caret;
		TextDrawable buffer;
		sdl::Color caretColor = sdl::COLOR_STANDARD;

		inline virtual int getLimitWidth() { return 0; }

		void initCaret(float x, float y, float w = 3, float h = 12);
		void renderCaret(BatchRenderPass& rp);
		void updateCaretPos();

		virtual float getBasePosX() = 0;
		virtual float getBasePosY() = 0;
		virtual strv getSourceText() = 0;
		virtual void onBufferUpdated() = 0;
	private:
		FWindow& fwindow;
	};

	// Resets buffer and releases text input
	void TextSupplier::releaseBuffer() {
		buffer.set(getSourceText(), sdl::COLOR_WHITE);
		fwindow.keyboardInputStopRequest(this);
	}

	void TextSupplier::start() {
		fwindow.keyboardInputStart(this);
		buffer.set(getSourceText(), sdl::COLOR_LIME);
		bufferPos = buffer.getTextLen();
		updateCaretPos();
	}

	void TextSupplier::onKeyPress(int32 c) {
		switch (c) {
		// Moves the caret to the end
		case sdl::KEY_DOWN:
			bufferPos = buffer.getTextLen();
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
			if (bufferPos < buffer.getTextLen()) {
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
			if (bufferPos <= buffer.getTextLen() && bufferPos > 0) {
				buffer.textErase(bufferPos - 1, 1);
				bufferPos -= 1;
				updateCaretPos();
				onBufferUpdated();
			}
			return;
		}
	}

	// Typing adds characters to the buffer
	void TextSupplier::onTextInput(const char* text) {
		if (bufferPos <= buffer.getTextLen()) {
			buffer.textInsert(bufferPos, text);
			bufferPos += std::strlen(text);
			updateCaretPos();
			onBufferUpdated();
		}
	}

	void TextSupplier::initCaret(float x, float y, float w, float h) {
		caretPosX = x;
		caretPosY = y;
		caretSizeX = w;
		caretSizeY = h;
	}

	// Renders the caret with a smooth fading "animation"
	void TextSupplier::renderCaret(BatchRenderPass& rp) {
		caretColor.a = 0.5f + 0.5f * std::sin(sdl::runner::timeTotal() / 100000000.0f);
		caret.draw(rp, caretPosX, caretPosY, caretSizeX, caretSizeY, 1, 1, 0, &caretColor);
	}

	void TextSupplier::updateCaretPos() {
		caretPosX = getBasePosX() + fwindow.renderScale(9) + buffer.getFont()->measureW(buffer.getText().substr(0, bufferPos));
		caretPosY = getBasePosY();
	}
}
