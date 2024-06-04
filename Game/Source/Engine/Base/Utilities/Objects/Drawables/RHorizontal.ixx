export module fbc.RHorizontal;

import fbc.FTexture;
import fbc.FUtil;
import fbc.IDrawable;
import sdl;

export namespace fbc {
	export class RHorizontal : public IDrawable {
	public:
		RHorizontal(IDrawable& base) : base(base), patchSize(base.getWidth() / 2) {}
		RHorizontal(IDrawable& base, float patchSize) : base(base), patchSize(patchSize) {}

		inline const sdl::RectF* getBaseRec() const override { return base.getBaseRec(); }
		inline float getHeight() const override { return base.getHeight(); }
		inline float getWidth() const override { return base.getWidth(); }

		void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) override;
		void reload() override;
		void setDrawBlend(const sdl::BlendMode bl) override;
		void setDrawColor(const sdl::Color& tint) override;
	private:
		IDrawable& base;
		float patchSize;
	};

	/* Assuming that the underlying base drawable consists of two seamless edges of size patchSize x patchSize stacked horizontally, we infer the center to be the left-most column of the right edge */
	void RHorizontal::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) {
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

	// If the patch size was not manually set, automatically adjust it based on the source texture
	// Note that this working relies on the original texture being reloaded before this; this should normally be enforced when creating drawables in StaticImages through its helper methods
	void RHorizontal::reload()
	{
		if (patchSize <= 0) {
			patchSize = base.getWidth() / 2.0f;
		}
	}

	void RHorizontal::setDrawBlend(const sdl::BlendMode bl)
	{
		base.setDrawBlend(bl);
	}

	void RHorizontal::setDrawColor(const sdl::Color& tint)
	{
		base.setDrawColor(tint);
	}
}
