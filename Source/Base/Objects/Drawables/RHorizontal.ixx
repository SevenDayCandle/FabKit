export module fab.RHorizontal;

import fab.FTexture;
import fab.FTextureBlock;
import fab.FUtil;
import sdl.SDLBase;
import fab.BatchRenderPass;
import sdl.SDLRunner;

/* An image whose horizontal borders can be stretched indefinitely */
namespace fab {
	export class RHorizontal : public FTexture {
	public:
		RHorizontal(FTextureBlock& source, strv path) : FTexture(source, path) {}
		RHorizontal(const RHorizontal&) = delete;

		void drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) override;
	};

	void RHorizontal::drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float sY = scY * h;
		const float cornerSX = scX * getWidth() / 2;
		const float edgeSX = scX * (w - getWidth());
		const float distX = (edgeSX + cornerSX) / 2;

		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindTexture(source);

		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0, 0, 0.5, 1),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX - distX, tY, cornerSX, sY, rotZ)
		}); // Left
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0.5, 0, 0, 1),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX, tY, edgeSX, sY, rotZ)
		}); // Center
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0.5, 0, 0.5, 1),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX + distX, tY, cornerSX, sY, rotZ)
		}); // Right
	}
}
