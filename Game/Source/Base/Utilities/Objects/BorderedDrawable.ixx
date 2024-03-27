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

		inline float getHeight() override { return base.getHeight();}
		inline float getWidth() override { return base.getWidth(); }

		void draw(const sdl::RectF* destRec, const sdl::Point& origin = { 0, 0 }, float rotation = 0, const sdl::Color& tint = sdl::WHITE, sdl::RendererFlip flip = SDL_FLIP_NONE) override;
		void draw(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin = { 0, 0 }, float rotation = 0, const sdl::Color& tint = sdl::WHITE, sdl::RendererFlip flip = SDL_FLIP_NONE) override;
	};

	// Draw the base stretched around destRec, then draw the corners and edges around destRec
	// Assumes that corner and border textures have the exact same size
	void BorderedDrawable::draw(const sdl::RectF* destRec, const sdl::Point& origin, float rotation, const sdl::Color& tint, sdl::RendererFlip flip) {
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

		base.draw(destRec, origin, rotation, tint, flip);
		cornerTL.draw(&ctl, origin, rotation, tint, flip);
		cornerTR.draw(&ctr, origin, rotation, tint, flip);
		cornerBL.draw(&cbl ,origin, rotation, tint, flip);
		cornerBR.draw(&cbr, origin, rotation, tint, flip);
		borderT.draw(&bt, origin, rotation, tint, flip);
		borderL.draw(&bl, origin, rotation, tint, flip);
		borderR.draw(&br, origin, rotation, tint, flip);
		borderB.draw(&bb, origin, rotation, tint, flip);
	}

	// Unsupported, falls back to base draw function
	void BorderedDrawable::draw(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, const sdl::Color& tint, sdl::RendererFlip flip) {
		draw(destRec, origin, rotation, tint, flip);
	}
}