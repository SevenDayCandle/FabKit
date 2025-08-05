export module fab.RVertical;

import fab.FTexture;
import fab.FTextureBlock;
import fab.FUtil;
import sdl.SDLBase;
import fab.BatchRenderPass;
import sdl.SDLRunner;

/* An image whose vertical borders can be stretched indefinitely */
namespace fab {
	export class RVertical : public FTexture {
	public:
		RVertical(FTextureBlock& source, strv path) : FTexture(source, path) {}
		RVertical(const RVertical&) = delete;

		void drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) override;
	};

	void RVertical::drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float sX = scX * w;
		const float cornerSY = scY * getHeight() / 2;
		const float edgeSY = scY * (h - getHeight());
		const float distY = (edgeSY + cornerSY) / 2;

		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindTexture(source);

		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0, 0, 1, 0.5),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX, tY - distY, sX, cornerSY, rotZ)
		}); // Top
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0, 0.5, 1, 0),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX, tY, sX, edgeSY, rotZ)
		}); // Center
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0, 0.5, 1, 0.5),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX, tY + distY, sX, cornerSY, rotZ)
		}); // Bottom
	}
}
