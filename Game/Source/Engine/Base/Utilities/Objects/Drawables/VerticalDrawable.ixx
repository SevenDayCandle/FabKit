export module fbc.VerticalDrawable;

import fbc.FTexture;
import fbc.FUtil;
import fbc.IDrawable;
import sdl;

export namespace fbc {
	export class VerticalDrawable : public IDrawable {
	public:
		VerticalDrawable(IDrawable& base) : base(base), patchSize(base.getWidth()) {}
		VerticalDrawable(IDrawable& base, float patchSize) : base(base), patchSize(patchSize) {}

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

	// Draw the base stretched around destRec, then draw the corners and edges around destRec
	// Assumes that corner and border textures have the exact same size
	void VerticalDrawable::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) {
		float p1x = sourceRec->x + patchSize;
		float p1y = sourceRec->y + patchSize;
		float p2y = p1y + patchSize;

		sdl::RectF st = { p1x, sourceRec->y, patchSize, patchSize };
		sdl::RectF sc = { p1x, p1y, patchSize,patchSize };
		sdl::RectF sb = { p1x, p2y, patchSize, patchSize };


		sdl::RectF dc = { destRec->x, destRec->y + patchSize, destRec->w, destRec->h - (patchSize * 2) };
		float bottom = dc.y + dc.h;

		sdl::RectF dt = { dc.x,  destRec->y, dc.w, patchSize };
		sdl::RectF db = { dc.x, bottom, dc.w, patchSize };

		base.drawBase(&st, &dt, origin, rotation, flip);
		base.drawBase(&sc, &dc, origin, rotation, flip);
		base.drawBase(&sb, &db, origin, rotation, flip);
	}

	void VerticalDrawable::setDrawBlend(const sdl::BlendMode bl)
	{
		base.setDrawBlend(bl);
	}

	void VerticalDrawable::setDrawColor(const sdl::Color& tint)
	{
		base.setDrawColor(tint);
	}
}
