export module fbc.horizontalDrawable;

import fbc.ftexture;
import fbc.futil;
import fbc.iDrawable;
import sdl;

export namespace fbc {
	export class HorizontalDrawable : public IDrawable {
	public:
		HorizontalDrawable(FTexture& base,
			FTexture& borderL,
			FTexture& borderR): IDrawable(), base(base), borderL(borderL), borderR(borderR) {}
		virtual ~HorizontalDrawable() {}

		FTexture& base;
		FTexture& borderL;
		FTexture& borderR;

		inline sdl::RectF* getBaseRec() override { return base.getBaseRec(); }
		inline float getHeight() override { return base.getHeight(); }
		inline float getWidth() override { return base.getWidth(); }

		void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) override;
		void setDrawBlend(const sdl::BlendMode bl) override;
		void setDrawColor(const sdl::Color& tint) override;
	};

	void HorizontalDrawable::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip)
	{
		float width = borderL.getWidth();
		sdl::RectF center = { destRec->x + width, destRec->y, destRec->w - (width * 2), destRec->h };
		float right = center.x + center.w;
		sdl::RectF bl = { destRec->x, destRec->y, width, destRec->h };
		sdl::RectF br = { right, destRec->y, width, destRec->h };

		base.draw(&center, origin, rotation, flip);
		borderL.draw(&bl, origin, rotation, flip);
		borderR.draw(&br, origin, rotation, flip);
	}

	void HorizontalDrawable::setDrawBlend(const sdl::BlendMode bl)
	{
		base.setDrawBlend(bl);
		borderL.setDrawBlend(bl);
		borderR.setDrawBlend(bl);
	}

	void HorizontalDrawable::setDrawColor(const sdl::Color& tint)
	{
		base.setDrawColor(tint);
		borderL.setDrawColor(tint);
		borderR.setDrawColor(tint);
	}
}
