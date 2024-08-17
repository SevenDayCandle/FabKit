export module fbc.UIImage;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextInfo;
import fbc.Tooltip;
import fbc.UITipHoverable;
import sdl;

namespace fbc {
	export class UIImage : public UITipHoverable {
	public:
		sdl::Color color = sdl::COLOR_STANDARD;
		float rotation = 0;
		IDrawable& image;

		UIImage(FWindow& window, Hitbox* hb, IDrawable& image) : UITipHoverable(window, hb), image(image) {}
		~UIImage() override {}

		inline virtual UIImage& setColor(sdl::Color color) { return this->color = color, *this; }
		inline virtual UIImage& setImage(IDrawable& image) { return this->image = image, *this;}
		inline virtual UIImage& setRotation(const float rotation) { return this->rotation = rotation, *this; }
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
	};

	void UIImage::renderImpl(sdl::SDLBatchRenderPass& rp) {
		image.draw(rp, *hb.get(), win.getH(), win.getH(), rotation, &color);
	}

	void UIImage::updateImpl() {
		this->UITipHoverable::updateImpl();
	}
}