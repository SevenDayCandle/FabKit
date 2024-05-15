export module fbc.BorderedDrawable;

import fbc.FUtil;
import fbc.IDrawable;
import sdl;

export namespace fbc {
	export class BorderedDrawable : public IDrawable {
	public:
		BorderedDrawable(IDrawable& base) : base(base), patchSize(base.getWidth() / 3.0f) {}
		BorderedDrawable(IDrawable& base, float patchSize): base(base), patchSize(patchSize) {}

		inline sdl::RectF* getBaseRec() override { return base.getBaseRec(); }
		inline float getHeight() override { return base.getHeight();}
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
	void BorderedDrawable::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) {
		float p1x = sourceRec->x + patchSize;
		float p2x = p1x + patchSize;
		float p1y = sourceRec->y + patchSize;
		float p2y = p1y + patchSize;

		sdl::RectF stl = { sourceRec->x,  sourceRec->y, patchSize, patchSize };
		sdl::RectF st = { p1x, sourceRec->y, patchSize, patchSize };
		sdl::RectF str = { p2x,  sourceRec->y, patchSize, patchSize };
		sdl::RectF scl = { sourceRec->x, p1y, patchSize, patchSize };
		sdl::RectF sc = { p1x, p1y, patchSize,patchSize };
		sdl::RectF scr = { p2x, p1y, patchSize, patchSize };
		sdl::RectF sbl = { sourceRec->x, p2y, patchSize, patchSize };
		sdl::RectF sb = { p1x, p2y, patchSize, patchSize };
		sdl::RectF sbr = { p2x, p2y, patchSize, patchSize };


		sdl::RectF dc = {destRec->x + patchSize, destRec->y + patchSize, destRec->w - (patchSize * 2), destRec->h - (patchSize * 2)};
		float right = dc.x + dc.w;
		float bottom = dc.y + dc.h;

		sdl::RectF dtl = { destRec->x,  destRec->y, patchSize, patchSize };
		sdl::RectF dt = { dc.x,  destRec->y, dc.w, patchSize };
		sdl::RectF dtr = { right,  destRec->y, patchSize, patchSize };
		sdl::RectF dcl = { destRec->x, dc.y, patchSize, dc.h };
		sdl::RectF dcr = { right, dc.y, patchSize, dc.h };
		sdl::RectF dbl = { destRec->x, bottom, patchSize, patchSize };
		sdl::RectF db = { dc.x, bottom, dc.w, patchSize };
		sdl::RectF dbr = { right, bottom, patchSize, patchSize };

		base.drawBase(&stl, &dtl, origin, rotation, flip);
		base.drawBase(&st, &dt, origin, rotation, flip);
		base.drawBase(&str, &dtr, origin, rotation, flip);
		base.drawBase(&scl, &dcl, origin, rotation, flip);
		base.drawBase(&sc, &dc, origin, rotation, flip);
		base.drawBase(&scr, &dcr, origin, rotation, flip);
		base.drawBase(&sbl, &dbl, origin, rotation, flip);
		base.drawBase(&sb, &db, origin, rotation, flip);
		base.drawBase(&sbr, &dbr, origin, rotation, flip);
	}

	void BorderedDrawable::setDrawBlend(const sdl::BlendMode bl)
	{
		base.setDrawBlend(bl);
	}

	void BorderedDrawable::setDrawColor(const sdl::Color& tint)
	{
		base.setDrawColor(tint);
	}
}
