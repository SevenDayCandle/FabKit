export module fbc.UIImage;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextInfo;
import fbc.ScreenManager;
import fbc.Tooltip;
import fbc.UITipHoverable;
import sdl;

namespace fbc {
	export class UIImage : public UITipHoverable {
	public:
		sdl::Color color = sdl::COLOR_STANDARD;
		float rotation = 0;
		IDrawable& image;

		UIImage(Hitbox* hb, IDrawable& image) : UITipHoverable(hb), image(image) {}
		~UIImage() override {}

		inline virtual UIImage& setColor(sdl::Color color) { return this->color = color, *this; }
		inline virtual UIImage& setImage(IDrawable& image) { return this->image = image, *this;}
		inline virtual UIImage& setRotation(const float rotation) { return this->rotation = rotation, *this; }
		virtual void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
		virtual void updateImpl() override;
	};

	void UIImage::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) {
		image.draw(cd, rp, *hb.get(), &color, rotation);
	}

	void UIImage::updateImpl() {
		this->UITipHoverable::updateImpl();
	}
}