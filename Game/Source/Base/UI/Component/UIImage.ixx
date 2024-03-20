export module fbc.uiImage;

import fbc.futil;
import fbc.hitbox;
import fbc.iDrawable;
import fbc.tooltip;
import fbc.uiTipHoverable;
import raylib;

export namespace fbc {
	export class UIImage : public UITipHoverable {
	public:
		raylib::Color color = raylib::White;
		float rotation = 0;
		IDrawable& image;
		raylib::Vector2 origin;

		UIImage(Hitbox* hb, IDrawable& image) : UITipHoverable(hb), image(image), origin({image.getWidth() / 2, image.getHeight() / 2}) {}
		UIImage(Hitbox* hb, IDrawable& image, raylib::Vector2 origin) : UITipHoverable(hb), image(image), origin(origin) {}
		~UIImage() override {}

		inline virtual UIImage& setColor(raylib::Color color) { return this->color = color, *this; }
		inline virtual UIImage& setImage(IDrawable& image) { return this->image = image, *this;}
		inline virtual UIImage& setOrigin(raylib::Vector2 origin) { return this->origin = origin, *this; }
		inline virtual UIImage& setRotation(const float rotation) { return this->rotation = rotation, *this; }
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	};

	void UIImage::renderImpl() {
		this->UITipHoverable::renderImpl();
		image.draw(*hb, origin, rotation, color);
	}

	void UIImage::updateImpl() {
		this->UITipHoverable::updateImpl();
	}
}