export module fbc.iDrawable;

import fbc.futil;
import sdl;

export namespace fbc {
	export class IDrawable {
	public:
		IDrawable() {}
		virtual ~IDrawable() {}

		inline void draw(const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::RendererFlip flip) { drawBase(getBaseRec(), destRec, origin, rotation, flip); }
		inline void draw(const sdl::RectF* destRec, const sdl::Color& tint, const sdl::Point& origin, float rotation, sdl::RendererFlip flip) { draw(getBaseRec(), destRec, tint, origin, rotation, flip); }
		inline void draw(const sdl::RectF* destRec, const sdl::BlendMode blend, const sdl::Color& tint, const sdl::Point& origin, float rotation, sdl::RendererFlip flip) { draw(getBaseRec(), destRec, blend, tint, origin, rotation, flip); }

		void draw(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Color& tint, const sdl::Point& origin, float rotation, sdl::RendererFlip flip);
		void draw(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::BlendMode blend, const sdl::Color& tint, const sdl::Point& origin, float rotation, sdl::RendererFlip flip);

		virtual void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::RendererFlip flip) = 0;
		virtual sdl::RectF* getBaseRec() = 0;
		virtual float getHeight() = 0;
		virtual float getWidth() = 0;
		virtual void setDrawBlend(const sdl::BlendMode bl) = 0;
		virtual void setDrawColor(const sdl::Color& tint) = 0;
	};

	void IDrawable::draw(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Color& tint, const sdl::Point& origin, float rotation, sdl::RendererFlip flip)
	{
		setDrawColor(tint);
		drawBase(sourceRec, destRec, origin, rotation, flip);
	}

	void IDrawable::draw(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::BlendMode blend, const sdl::Color& tint, const sdl::Point& origin, float rotation, sdl::RendererFlip flip)
	{
		setDrawBlend(blend);
		setDrawColor(tint);
		drawBase(sourceRec, destRec, origin, rotation, flip);
		setDrawBlend(sdl::BlendMode::SDL_BLENDMODE_BLEND);
	}
}