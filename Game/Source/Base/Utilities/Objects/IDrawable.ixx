export module fbc.iDrawable;

import fbc.futil;
import sdl;

export namespace fbc {
	export class IDrawable {
	public:
		IDrawable() {}
		virtual ~IDrawable() {}

		virtual void draw(const sdl::RectF* destRec, const sdl::Point& origin, float rotation, const sdl::Color& tint, sdl::RendererFlip flip) = 0;
		virtual void draw(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, const sdl::Color& tint, sdl::RendererFlip flip) = 0;
		virtual float getHeight() = 0;
		virtual float getWidth() = 0;
	};
}