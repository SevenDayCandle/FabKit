export module fbc.RegionTexture;

import fbc.FTexture;
import fbc.FUtil;
import fbc.IDrawable;
import sdl;

export namespace fbc {
	export class RegionTexture : public IDrawable {
	public:
		RegionTexture(FTexture& base, sdl::RectF dim): base(base), dim(dim) {}
		virtual ~RegionTexture() override {}

		inline sdl::RectF* getBaseRec() override { return &dim; }
		inline float getHeight() override { return dim.h; }
		inline float getWidth() override { return dim.w; }

		void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) override;
		void setDrawBlend(const sdl::BlendMode bl) override;
		void setDrawColor(const sdl::Color& tint) override;
	private:
		FTexture& base;
		sdl::RectF dim;
	};

	void RegionTexture::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip)
	{
		base.draw(sourceRec, origin, rotation, flip);
	}

	void RegionTexture::setDrawBlend(const sdl::BlendMode bl)
	{
		base.setDrawBlend(bl);
	}

	void RegionTexture::setDrawColor(const sdl::Color& tint)
	{
		base.setDrawColor(tint);
	}
}