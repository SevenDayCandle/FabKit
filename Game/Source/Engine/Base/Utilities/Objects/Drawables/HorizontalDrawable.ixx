export module fbc.HorizontalDrawable;

import fbc.FTexture;
import fbc.FUtil;
import fbc.IDrawable;
import sdl;

export namespace fbc {
	export class HorizontalDrawable : public IDrawable {
	public:
		HorizontalDrawable(IDrawable& base) : base(base), patchSize(base.getWidth() / 2) {}
		HorizontalDrawable(IDrawable& base, float patchSize) : base(base), patchSize(patchSize) {}

		inline sdl::RectF* getBaseRec() override { return base.getBaseRec(); }
		inline float getHeight() override { return base.getHeight(); }
		inline float getWidth() override { return base.getWidth(); }

		void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) override;
		void setDrawBlend(const sdl::BlendMode bl) override;
		void setDrawColor(const sdl::Color& tint) override;
	private:
		IDrawable& base;
		float patchSize;
	};

	/* Assuming that the underlying base drawable consists of two seamless edges of size patchSize x patchSize stacked horizontally, we infer the center to be the left-most column of the right edge */
	void HorizontalDrawable::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) {
		float px = sourceRec->x + patchSize;

		sdl::RectF scl = { sourceRec->x, sourceRec->y , patchSize, sourceRec->h };
		sdl::RectF sc = { px, sourceRec->y , 1, sourceRec->h };
		sdl::RectF scr = { px, sourceRec->y , patchSize, sourceRec->h };

		sdl::RectF dc = { destRec->x + patchSize, destRec->y, destRec->w - (patchSize * 2), destRec->h };
		float right = dc.x + dc.w;

		sdl::RectF dcl = { destRec->x, dc.y, patchSize, dc.h };
		sdl::RectF dcr = { right, dc.y, patchSize, dc.h };

		base.drawBase(&scl, &dcl, origin, rotation, flip);
		base.drawBase(&sc, &dc, origin, rotation, flip);
		base.drawBase(&scr, &dcr, origin, rotation, flip);
	}

	void HorizontalDrawable::setDrawBlend(const sdl::BlendMode bl)
	{
		base.setDrawBlend(bl);
	}

	void HorizontalDrawable::setDrawColor(const sdl::Color& tint)
	{
		base.setDrawColor(tint);
	}
}
