export module fbc.uiImage;

import fbc.ftexture;
import fbc.futil;
import fbc.hitbox;
import fbc.tooltip;
import fbc.uiTipHoverable;
import raylib;

export namespace fbc {
	export class UIImage : public UITipHoverable {
	public:
		raylib::Color color = raylib::White;
		float rotation = 0;
		fbc::FTexture& image;
		raylib::Vector2 origin;

		UIImage(Hitbox* hb, fbc::FTexture& image) : UITipHoverable(hb), image(image), origin({(float) image.width / 2, (float) image.height / 2}) {}
		UIImage(Hitbox* hb, fbc::FTexture& image, raylib::Vector2 origin) : UITipHoverable(hb), image(image), origin(origin) {}
		~UIImage() override {}

		inline virtual UIImage& setColor(raylib::Color color) { return this->color = color, *this; }
		inline virtual UIImage& setImage(fbc::FTexture& image) { return this->image = image, *this;}
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