export module fbc.uiImage;

import fbc.ftexture;
import fbc.futil;
import fbc.hitbox;
import fbc.tooltip;
import fbc.uiHoverable;
import raylib;

export namespace fbc::cpt {
	export class UIImage : public UIHoverable {
	public:
		raylib::Color color = raylib::White;
		float rotation = 0;
		float scale = 1;
		sptr<fbc::FTexture> image;

		UIImage(hitbox::Hitbox* hb, sptr<fbc::FTexture> image) : UIHoverable(hb), image(image) {}
		~UIImage() override {}

		inline virtual UIImage& setColor(raylib::Color color) { return this->color = color, *this; }
		inline virtual UIImage& setImage(sptr<fbc::FTexture> image) { return this->image = image, *this;}
		inline virtual UIImage& setRotation(const float rotation) { return this->rotation = rotation, *this; }
		inline virtual UIImage& setScale(float scale) { return this->scale = scale, *this;}
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	};

	void UIImage::renderImpl() {
		this->UIHoverable::renderImpl();
		image->draw({ hb->x, hb->y }, rotation, scale, color);
	}

	void UIImage::updateImpl() {
		this->UIHoverable::updateImpl();
	}
}