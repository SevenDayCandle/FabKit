export module fbc.borderedDrawable;

import fbc.ftexture;
import fbc.futil;
import fbc.iDrawable;

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

		inline sdl::RectI* getBaseRec() override { return base.getBaseRec(); }
		inline float getHeight() override { return base.getHeight();}
		inline float getWidth() override { return base.getWidth(); }

		void drawBase(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::RendererFlip flip) override;
		void setDrawBlend(const sdl::BlendMode bl) override;
		void setDrawColor(const sdl::Color& tint) override;
	};

	// Draw the base stretched around destRec, then draw the corners and edges around destRec
	// Assumes that corner and border textures have the exact same size
	void BorderedDrawable::drawBase(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::RendererFlip flip) {
		float width = cornerTL.getWidth();
		float height = cornerTL.getHeight();
		float left = destRec->x - width;
		float top = destRec->y - height;
		float right = destRec->x + destRec->w;
		float bottom = destRec->y + destRec->h;
		sdl::RectF ctl = { left, top, width, height };
		sdl::RectF ctr = { right, top, width, height };
		sdl::RectF cbl = { left, bottom, width, height };
		sdl::RectF cbr = { right, bottom, width, height };
		sdl::RectF bt = { destRec->x, top, destRec->w, height };
		sdl::RectF bl = { left, destRec->y, width, destRec->h };
		sdl::RectF br = { right, destRec->y, width, destRec->h };
		sdl::RectF bb = { destRec->x, bottom, destRec->w, height };

		base.draw(destRec, origin, rotation, flip);
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