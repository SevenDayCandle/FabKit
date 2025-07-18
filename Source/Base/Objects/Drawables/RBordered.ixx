export module fab.RBordered;

import fab.FUtil;
import fab.FTexture;
import fab.FTextureBlock;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

/* An image whose horizontal and vertical borders can be stretched indefinitely */
namespace fab {
	export class RBordered : public FTexture {
	public:
		RBordered(FTextureBlock& source, strv path) : FTexture(source, path) {}
		RBordered(const RBordered&) = delete;

		void drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) override;
	};

	void RBordered::drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float cornerSX = scX * getWidth() / (2);
		const float cornerSY = scY * getHeight() / (2);
		const float edgeSX = scX * (w - getWidth());
		const float edgeSY = scY * (h - getHeight());

		const float distX = (edgeSX + cornerSX) / 2;
		const float distY = (edgeSY + cornerSY) / 2;

		const float beginX = tX - distX;
		const float beginY = tY - distY;
		const float endX = tX + distX;
		const float endY = tY + distY;

		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindTexture(source, sdl::runner::SAMPLER);

		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0, 0, 0.5, 0.5),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(beginX, beginY, cornerSX, cornerSY, rotZ)
			}); // Top Left
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0.5, 0, 0, 0.5),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX, beginY, edgeSX, cornerSY, rotZ)
			}); // Top
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0.5, 0, 0.5, 0.5),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(endX, beginY, cornerSX, cornerSY, rotZ)
			}); // Top Right
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0, 0.5, 0.5, 0),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(beginX, tY, cornerSX, edgeSY, rotZ)
			}); // Center Left
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0.5, 0.5, 0, 0),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX, tY, edgeSX, edgeSY, rotZ)
			}); // Center
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0.5, 0.5, 0.5, 0),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(endX, tY, cornerSX, edgeSY, rotZ)
			}); // Center Right
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0, 0.5, 0.5, 0.5),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(beginX, endY, cornerSX, cornerSY, rotZ)
			}); // Bottom Left
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0.5, 0.5, 0, 0.5),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX, endY, edgeSX, cornerSY, rotZ)
			}); // Bottom
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0.5, 0.5, 0.5, 0.5),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(endX, endY, cornerSX, cornerSY, rotZ)
			}); // Bottom Right
	}
}
