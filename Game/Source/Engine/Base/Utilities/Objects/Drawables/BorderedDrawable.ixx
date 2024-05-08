export module fbc.borderedDrawable;

import fbc.ftexture;
import fbc.futil;
import fbc.iDrawable;
import sdl;

export namespace fbc {
	export class BorderedDrawable : public IDrawable {
	public:
		BorderedDrawable(FTexture& base,
		FTexture& borderB,
		FTexture& borderL,
		FTexture& borderR,
		FTexture& borderT,
		FTexture& cornerBL,
		FTexture& cornerBR,
		FTexture& cornerTL,
		FTexture& cornerTR): IDrawable(), base(base), borderB(borderB), borderL(borderL), borderR(borderR), borderT(borderT), cornerBL(cornerBL), cornerBR(cornerBR), cornerTL(cornerTL), cornerTR(cornerTR) {

		}

		FTexture& base;
		FTexture& borderB;
		FTexture& borderL;
		FTexture& borderR;
		FTexture& borderT;
		FTexture& cornerBL;
		FTexture& cornerBR;
		FTexture& cornerTL;
		FTexture& cornerTR;

		inline sdl::RectF* getBaseRec() override { return base.getBaseRec(); }
		inline float getHeight() override { return base.getHeight();}
		inline float getWidth() override { return base.getWidth(); }

		void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) override;
		void setDrawBlend(const sdl::BlendMode bl) override;
		void setDrawColor(const sdl::Color& tint) override;
	};

	// Draw the base stretched around destRec, then draw the corners and edges around destRec
	// Assumes that corner and border textures have the exact same size
	void BorderedDrawable::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) {
		float cwidth = cornerTL.getWidth();
		float cheight = cornerTL.getHeight();
		sdl::RectF center = {destRec->x + cwidth, destRec->y + cheight, destRec->w - (cwidth * 2), destRec->h - (cheight * 2)};

		float right = center.x + center.w;
		float bottom = center.y + center.h;
		sdl::RectF ctl = { destRec->x,  destRec->y, cwidth, cheight };
		sdl::RectF ctr = { right,  destRec->y, cwidth, cheight };
		sdl::RectF cbl = { destRec->x, bottom, cwidth, cheight };
		sdl::RectF cbr = { right, bottom, cwidth, cheight };
		sdl::RectF bt = { center.x,  destRec->y, center.w, cheight };
		sdl::RectF bl = { destRec->x, center.y, cwidth, center.h };
		sdl::RectF br = { right, center.y, cwidth, center.h };
		sdl::RectF bb = { center.x, bottom, center.w, cheight };

		base.draw(&center, origin, rotation, flip);
		cornerTL.draw(&ctl, origin, rotation, flip);
		cornerTR.draw(&ctr, origin, rotation, flip);
		cornerBL.draw(&cbl ,origin, rotation, flip);
		cornerBR.draw(&cbr, origin, rotation, flip);
		borderT.draw(&bt, origin, rotation, flip);
		borderL.draw(&bl, origin, rotation, flip);
		borderR.draw(&br, origin, rotation, flip);
		borderB.draw(&bb, origin, rotation, flip);
	}

	void BorderedDrawable::setDrawBlend(const sdl::BlendMode bl)
	{
		base.setDrawBlend(bl);
		cornerTL.setDrawBlend(bl);
		cornerTR.setDrawBlend(bl);
		cornerBL.setDrawBlend(bl);
		cornerBR.setDrawBlend(bl);
		borderT.setDrawBlend(bl);
		borderL.setDrawBlend(bl);
		borderR.setDrawBlend(bl);
		borderB.setDrawBlend(bl);
	}

	void BorderedDrawable::setDrawColor(const sdl::Color& tint)
	{
		base.setDrawColor(tint);
		cornerTL.setDrawColor(tint);
		cornerTR.setDrawColor(tint);
		cornerBL.setDrawColor(tint);
		cornerBR.setDrawColor(tint);
		borderT.setDrawColor(tint);
		borderL.setDrawColor(tint);
		borderR.setDrawColor(tint);
		borderB.setDrawColor(tint);
	}
}
