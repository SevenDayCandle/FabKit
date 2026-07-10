export module fab.RHorizontal;

import fab.FTexture;
import fab.FTextureBlock;
import fab.FUtil;
import sdl.SDLHelpers;
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

		rp.setPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.setTexture(source);

		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(tX - distX, tY, cornerSX, sY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0, 0, 0.48, 1),
			.texInd = static_cast<float>(index)
		}); // Left
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(tX, tY, edgeSX, sY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0.48, 0, 0.52, 1),
			.texInd = static_cast<float>(index)
		}); // Center
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(tX + distX, tY, cornerSX, sY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0.52, 0, 1, 1),
			.texInd = static_cast<float>(index)
		}); // Right
	}
}
