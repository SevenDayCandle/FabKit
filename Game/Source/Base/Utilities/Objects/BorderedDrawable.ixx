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

		inline float getHeight() override { return (float)base.height;}
		inline float getWidth() override { return (float)base.width; }

		void draw(const raylib::Rectangle& destRec, const raylib::Vector2& origin, float rotation, raylib::Color tint) override;
		void draw(const raylib::Rectangle& sourceRec, const raylib::Rectangle& destRec, const raylib::Vector2& origin, float rotation, raylib::Color tint) override;
	};

	// Draw the base stretched around destRec, then draw the corners and edges around destRec
	// Assumes that corner and border textures have the exact same size
	void BorderedDrawable::draw(const raylib::Rectangle& destRec, const raylib::Vector2& origin = { 0, 0 },
		float rotation = 0, raylib::Color tint = raylib::White) {
		float width = (float)cornerTL.width;
		float height = (float)cornerTL.height;
		float left = destRec.x - width;
		float top = destRec.y - height;
		float right = destRec.x + destRec.width;
		float bottom = destRec.y + destRec.height;

		base.draw(destRec, origin, rotation, tint);
		cornerTL.draw({ left, top, width, height }, origin, rotation, tint);
		cornerTR.draw({ right, top, width, height }, origin, rotation, tint);
		cornerBL.draw({ left, bottom, width, height }, origin, rotation, tint);
		cornerBR.draw({ right, bottom, width, height }, origin, rotation, tint);
		borderT.draw({ destRec.x, top, destRec.width, height }, origin, rotation, tint);
		borderL.draw({ left, destRec.y, width, destRec.height }, origin, rotation, tint);
		borderR.draw({ right, destRec.y, width, destRec.height }, origin, rotation, tint);
		borderB.draw({ destRec.x, bottom, destRec.width, height }, origin, rotation, tint);
	}

	// Unsupported, falls back to base draw function
	void BorderedDrawable::draw(const raylib::Rectangle& sourceRec, const raylib::Rectangle& destRec, const raylib::Vector2& origin = { 0, 0 },
		float rotation = 0, raylib::Color tint = raylib::White) {
		draw(destRec, origin, rotation, tint);
	}
}