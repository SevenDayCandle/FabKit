export module fbc.UIImage;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextInfo;
import fbc.ScreenManager;
import fbc.UITooltip;
import fbc.UITipHoverable;
import sdl;

export namespace fbc {
	export class UIImage : public UITipHoverable {
	public:
		sdl::Color color = sdl::COLOR_WHITE;
		sdl::FlipMode flip = sdl::FlipMode::SDL_FLIP_NONE;
		float rotation = 0;
		IDrawable& image;
		sdl::Point origin;

		UIImage(Hitbox* hb, IDrawable& image) : UITipHoverable(hb), image(image), origin({image.getWidth() / 2, image.getHeight() / 2}) {}
		UIImage(Hitbox* hb, IDrawable& image, sdl::Point origin) : UITipHoverable(hb), image(image), origin(origin) {}
		~UIImage() override {}

		inline virtual UIImage& setColor(sdl::Color color) { return this->color = color, *this; }
		inline virtual UIImage& setImage(IDrawable& image) { return this->image = image, *this;}
		inline virtual UIImage& setOrigin(sdl::Point origin) { return this->origin = origin, *this; }
		inline virtual UIImage& setRotation(const float rotation) { return this->rotation = rotation, *this; }
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	};

	void UIImage::renderImpl() {
		image.draw(hb.get(), color, origin, rotation, flip);
	}

	void UIImage::updateImpl() {
		this->UITipHoverable::updateImpl();
	}
}