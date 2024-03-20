export module fbc.iDrawable;

import fbc.futil;
import raylib;

export namespace fbc {
	export class IDrawable {
	public:
		IDrawable() {}
		virtual ~IDrawable() {}

		virtual void draw(const raylib::Rectangle& destRec, const raylib::Vector2& origin = { 0, 0 }, float rotation = 0, raylib::Color tint = raylib::White) = 0;
		virtual void draw(const raylib::Rectangle& sourceRec, const raylib::Rectangle& destRec, const raylib::Vector2& origin = { 0, 0 }, float rotation = 0, raylib::Color tint = raylib::White) = 0;
		virtual float getHeight() = 0;
		virtual float getWidth() = 0;
	};
}