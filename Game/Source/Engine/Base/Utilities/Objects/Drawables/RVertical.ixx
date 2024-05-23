export module fbc.RVertical;

import fbc.FUtil;
import fbc.IDrawable;
import sdl;

export namespace fbc {
	export class RVertical : public IDrawable {
	public:
		RVertical(IDrawable& base) : base(base), patchSize(base.getHeight() / 2) {}
		RVertical(IDrawable& base, float patchSize) : base(base), patchSize(patchSize) {}

		inline const sdl::RectF* getBaseRec() override { return base.getBaseRec(); }
		inline float getHeight() override { return base.getHeight(); }
		inline float getWidth() override { return base.getWidth(); }

		void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) override;
		void setDrawBlend(const sdl::BlendMode bl) override;
		void setDrawColor(const sdl::Color& tint) override;
	private:
		IDrawable& base;
		float patchSize;
	};

	/* Assuming that the underlying base drawable consists of two seamless edges of size patchSize x patchSize stacked vertically, we infer the center to be the top-most column of the bottom edge */
	void RVertical::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) {
		float py = sourceRec->y + patchSize;

		sdl::RectF st = { sourceRec->x, sourceRec->y, sourceRec->w, patchSize };
		sdl::RectF sc = { sourceRec->x, py, sourceRec->w,1 };
		sdl::RectF sb = { sourceRec->x, py, sourceRec->w, patchSize };


		sdl::RectF dc = { destRec->x, destRec->y + patchSize, destRec->w, destRec->h - (patchSize * 2) };
		float bottom = dc.y + dc.h;

		sdl::RectF dt = { dc.x,  destRec->y, dc.w, patchSize };
		sdl::RectF db = { dc.x, bottom, dc.w, patchSize };

		base.drawBase(&st, &dt, origin, rotation, flip);
		base.drawBase(&sc, &dc, origin, rotation, flip);
		base.drawBase(&sb, &db, origin, rotation, flip);
	}

	void RVertical::setDrawBlend(const sdl::BlendMode bl)
	{
		base.setDrawBlend(bl);
	}

	void RVertical::setDrawColor(const sdl::Color& tint)
	{
		base.setDrawColor(tint);
	}
}
