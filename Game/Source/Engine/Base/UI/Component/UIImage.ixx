export module fbc.UIImage;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.Tooltip;
import fbc.UIBase;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLRunner;

namespace fbc {
	export class UIImage : public UIBase {
	public:
		UIImage(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image) : UIBase(window, move(hb)), image(image) {}
		UIImage(UIImage&& other) noexcept = default;
		~UIImage() override {}

		sdl::Color color = sdl::COLOR_STANDARD;
		float rotation = 0;
		IDrawable& image;

		inline virtual UIImage& setColor(sdl::Color color) { return this->color = color, *this; }
		inline virtual UIImage& setImage(IDrawable& image) { return this->image = image, *this;}
		inline virtual UIImage& setRotation(const float rotation) { return this->rotation = rotation, *this; }
		inline virtual UIImage& setRotationDeg(const float rotation) { return this->rotation = sdl::rads(rotation), *this; }
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	};

	void UIImage::renderImpl(sdl::SDLBatchRenderPass& rp) {
		image.draw(rp, *hb.get(), win.getW(), win.getH(), rotation, &color);
	}
}