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
		rp.bindTexture(source);

		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(beginX, beginY, cornerSX, cornerSY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0, 0.52, 0.48, 1),
			.texInd = static_cast<float>(index),
		}); // Top Left
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(tX, beginY, edgeSX, cornerSY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0.48, 0.52, 0.52, 1),
			.texInd = static_cast<float>(index)
		}); // Top
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(endX, beginY, cornerSX, cornerSY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0.52, 0.52, 1, 1),
			.texInd = static_cast<float>(index)
		}); // Top Right
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(beginX, tY, cornerSX, edgeSY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0, 0.48, 0.48, 0.52),
			.texInd = static_cast<float>(index)
		}); // Center Left
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(tX, tY, edgeSX, edgeSY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0.48, 0.48, 0.52, 0.52),
			.texInd = static_cast<float>(index)
		}); // Center
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(endX, tY, cornerSX, edgeSY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0.52, 0.48, 1, 0.52),
			.texInd = static_cast<float>(index)
		}); // Center Right
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(beginX, endY, cornerSX, cornerSY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0, 0, 0.48, 0.48),
			.texInd = static_cast<float>(index)
		}); // Bottom Left
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(tX, endY, edgeSX, cornerSY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0.48, 0, 0.52, 0.48),
			.texInd = static_cast<float>(index)
		}); // Bottom
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(endX, endY, cornerSX, cornerSY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0.52, 0, 1, 0.48),
			.texInd = static_cast<float>(index)
		}); // Bottom Right
	}
}
