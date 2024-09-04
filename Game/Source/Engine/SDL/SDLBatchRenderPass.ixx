export module sdl.SDLBatchRenderPass;

import fbc.FUtil;
import sdl.SDLBase;
import std;

namespace sdl {
	export class SDLBatchRenderPass {
	public:
		SDLBatchRenderPass(GpuCommandBuffer* cmd, GpuColorAttachmentInfo* info, int colorAttachmentAmount = 1, GpuDepthStencilAttachmentInfo* depth = nullptr): cmd(cmd), renderPass(sdl::gpuBeginRenderPass(cmd, info, colorAttachmentAmount, depth)) {}
		SDLBatchRenderPass(GpuCommandBuffer* cmd, GpuRenderPass* rp): cmd(cmd), renderPass(rp) {}
		SDLBatchRenderPass(const SDLBatchRenderPass& other) = delete;
		~SDLBatchRenderPass() { gpuEndRenderPass(renderPass); }

		inline void drawIndexedPrimitives(fbc::uint32 baseVertex = 0, fbc::uint32 startIndex = 0, fbc::uint32 primitiveCount = 6, fbc::uint32 instanceCount = 1) { sdl::gpuDrawIndexedPrimitives(renderPass, baseVertex, startIndex, primitiveCount, instanceCount); }
		inline void pushFragmentUniform(const void* data, fbc::uint32 sizeInBytes, fbc::uint32 slot = 0) { sdl::gpuPushFragmentUniformData(cmd, slot, data, sizeInBytes); };
		inline void pushVertexUniform(const void* data, fbc::uint32 sizeInBytes, fbc::uint32 slot = 0) { sdl::gpuPushVertexUniformData(cmd, slot, data, sizeInBytes); };
		inline void setScissor(RectI* rect) { sdl::gpuSetScissor(renderPass, rect); }
		template <typename T> inline void pushFragmentUniformAuto(const T* data, fbc::uint32 slot = 0) { sdl::gpuPushFragmentUniformData(cmd, slot, data, sizeof(T)); };
		template <typename T> inline void pushVertexUniformAuto(const T* data, fbc::uint32 slot = 0) { sdl::gpuPushVertexUniformData(cmd, slot, data, sizeof(T)); };

		void bindBufferIndex(GpuBuffer* buffer);
		void bindBufferVertex(GpuBuffer* buffer);
		void bindPipeline(GpuGraphicsPipeline* pipeline);
		void bindTexture(GpuTexture* texture, GpuSampler* sampler);
		void setupVertexUniform(float tX, float tY, float sX, float sY, float rotZ = 0);
	private:
		GpuBuffer* lastBufferIndex = nullptr;
		GpuBuffer* lastBufferVertex = nullptr;
		GpuCommandBuffer* cmd;
		GpuGraphicsPipeline* lastPipeline = nullptr;
		GpuRenderPass* renderPass;
		GpuTexture* lastTexture = nullptr;
		inline static sdl::Matrix4x4 MATRIX_UNIFORM = {
		1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	};

	// Binds an index buffer if it was not already bound
	void SDLBatchRenderPass::bindBufferIndex(GpuBuffer* buffer)
	{
		if (lastBufferIndex != buffer) {
			sdl::GpuBufferBinding b = { buffer, 0 };
			sdl::gpuBindIndexBuffer(renderPass, &b, sdl::GpuIndexElementSize::SDL_GPU_INDEXELEMENTSIZE_16BIT);
			lastBufferIndex = buffer;
		}
	}

	// Binds a vertex buffer if it was not already bound
	void SDLBatchRenderPass::bindBufferVertex(GpuBuffer* buffer)
	{
		if (lastBufferVertex != buffer) {
			sdl::GpuBufferBinding b = { buffer, 0 };
			sdl::gpuBindVertexBuffers(renderPass, 0, &b, 1);
			lastBufferVertex = buffer;
		}
	}

	// Binds a pipeline if it was not already bound
	void SDLBatchRenderPass::bindPipeline(GpuGraphicsPipeline* pipeline)
	{
		if (lastPipeline != pipeline) {
			sdl::gpuBindGraphicsPipeline(renderPass, pipeline);
			lastPipeline = pipeline;
		}
	}

	// Binds a texture if it was not already bound
	void SDLBatchRenderPass::bindTexture(GpuTexture* texture, GpuSampler* sampler)
	{
		if (lastTexture != texture) {
			sdl::GpuTextureSamplerBinding b = { texture, sampler };
			sdl::gpuBindFragmentSamplers(renderPass, 0, &b, 1);
			lastTexture = texture;
		}
	}

	// Automatically set up a vertex buffer based on the provided center coordinates, sizes, and rotation
	void SDLBatchRenderPass::setupVertexUniform(float tX, float tY, float sX, float sY, float rotZ) {
		MATRIX_UNIFORM.m41 = 2 * tX - 1;
		MATRIX_UNIFORM.m42 = 1 - 2 * tY;

		if (rotZ != 0) {
			float cosZ = std::cos(rotZ);
			float sinZ = std::sin(rotZ);

			MATRIX_UNIFORM.m11 = 2 * sX * cosZ;
			MATRIX_UNIFORM.m12 = 2 * sX * sinZ;
			MATRIX_UNIFORM.m21 = -sY * sinZ;
			MATRIX_UNIFORM.m22 = sY * cosZ;
		}
		else {
			MATRIX_UNIFORM.m11 = 2 * sX;
			MATRIX_UNIFORM.m12 = 0;
			MATRIX_UNIFORM.m21 = 0;
			MATRIX_UNIFORM.m22 = 2 * sY;
		}
		pushVertexUniform(&MATRIX_UNIFORM, sizeof(sdl::Matrix4x4));
	}
}