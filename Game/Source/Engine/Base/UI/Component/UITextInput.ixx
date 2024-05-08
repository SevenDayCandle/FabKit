export module fbc.uiTextInput;

import fbc.coreConfig;
import fbc.coreContent;
import fbc.ffont;
import fbc.hitbox;
import fbc.iDrawable;
import fbc.uiInteractable;
import fbc.textInfo;
import fbc.futil;
import fbc.textProvider;
import sdl;
import std;

export namespace fbc {
	export class UITextInput : public UIInteractable, public TextInfo, public TextProvider {
	public:
		UITextInput(Hitbox* hb, IDrawable& image, FFont& textFont = cct.fontRegular()): UIInteractable(hb, image), TextInfo(textFont) {}
		virtual ~UITextInput() {

		}

		inline UITextInput& setOnBufferUpdate(func<void(strv)> onBufferUpdateCallback) { return this->onBufferUpdateCallback = onBufferUpdateCallback, * this; }
		inline UITextInput& setOnComplete(func<void(strv)> onComplete) { return this->onComplete = onComplete, *this; }

		void commit(strv text);
		virtual void renderImpl() override;
	protected:
		inline virtual int getLimitWidth() override { return this->hb->w; }
		inline void updateCaretPos() override { caretPos.x = this->hb->x + cfg.renderScale(9) + this->font.measureW(buffer.substr(0, bufferPos)); }

		void onBufferUpdated() override;
		void onKeyPress(int32_t c) override;
	private:
		func<void(strv)> onBufferUpdateCallback;
		func<void(strv)> onComplete;
	};

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
		//sdl::textureSetAlphaMod(caret.texture, 0.5f + 0.5f * std::sin(sdl::ticks()));
		sdl::renderCopy(caret.texture, nullptr, &caretPos);
	}

	void UITextInput::onBufferUpdated()
	{
		this->updateCache(buffer, sdl::COLOR_LIME);
		if (onBufferUpdateCallback) {
			onBufferUpdateCallback(buffer);
		}
	}

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
}