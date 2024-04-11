export module fbc.verticalDrawable;

import fbc.ftexture;
import fbc.futil;
import fbc.iDrawable;

export namespace fbc {
	export class VerticalDrawable : public IDrawable {
	public:
		VerticalDrawable(FTexture& base,
			FTexture& borderB,
			FTexture& borderT) : IDrawable(), base(base), borderB(borderB), borderT(borderT) {
		}

		FTexture& base;
		FTexture& borderB;
		FTexture& borderT;

		inline sdl::RectF* getBaseRec() override { return base.getBaseRec(); }
		inline float getHeight() override { return base.getHeight(); }
		inline float getWidth() override { return base.getWidth(); }

		void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::RendererFlip flip) override;
		void setDrawBlend(const sdl::BlendMode bl) override;
		void setDrawColor(const sdl::Color& tint) override;
	};

	// Draw the base stretched around destRec, then draw the corners and edges around destRec
	// Assumes that corner and border textures have the exact same size
	void VerticalDrawable::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::RendererFlip flip) {
		float height = borderB.getHeight();
		float top = destRec->y - height;
		float bottom = destRec->y + destRec->h;
		sdl::RectF bt = { destRec->x, top, destRec->w, height };
		sdl::RectF bb = { destRec->x, bottom, destRec->w, height };

		base.draw(destRec, origin, rotation, flip);
		borderT.draw(&bt, origin, rotation, flip);
		borderB.draw(&bb, origin, rotation, flip);
	}

	void VerticalDrawable::setDrawBlend(const sdl::BlendMode bl)
	{
		base.setDrawBlend(bl);
		borderT.setDrawBlend(bl);
		borderB.setDrawBlend(bl);
	}

	void VerticalDrawable::setDrawColor(const sdl::Color& tint)
	{
		base.setDrawColor(tint);
		borderT.setDrawColor(tint);
		borderB.setDrawColor(tint);
	}
}
