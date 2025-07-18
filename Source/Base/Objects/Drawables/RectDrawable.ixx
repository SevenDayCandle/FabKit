export module fab.RectDrawable;

import fab.FUtil;
import fab.IDrawable;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

/* Represents a solid rectangle to be rendered on screen */
namespace fab {
	export class RectDrawable : public IDrawable {
	public:
		RectDrawable() {}
		virtual ~RectDrawable() = default;

		void drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override;
	};

	void RectDrawable::drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline)
	{
		// Assume origin is at the center of the drawable
		float sX = scX * w;
		float sY = scY * h;
		rp.bindPipeline(sdl::runner::shapePipelineForMode(pipeline));
		rp.pushVertexData({
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX, tY, sX, sY, rotZ)
		});
	}
}
