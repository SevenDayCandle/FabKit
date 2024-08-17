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
	private:
		GpuBuffer* lastBufferIndex = nullptr;
		GpuBuffer* lastBufferVertex = nullptr;
		GpuCommandBuffer* cmd;
		GpuGraphicsPipeline* lastPipeline = nullptr;
		GpuRenderPass* renderPass;
		GpuTexture* lastTexture = nullptr;
	};

	void SDLBatchRenderPass::bindBufferIndex(GpuBuffer* buffer)
	{
		if (lastBufferIndex != buffer) {
			sdl::GpuBufferBinding b = { buffer, 0 };
			sdl::gpuBindIndexBuffer(renderPass, &b, sdl::GpuIndexElementSize::SDL_GPU_INDEXELEMENTSIZE_16BIT);
			lastBufferIndex = buffer;
		}
	}

	void SDLBatchRenderPass::bindBufferVertex(GpuBuffer* buffer)
	{
		if (lastBufferVertex != buffer) {
			sdl::GpuBufferBinding b = { buffer, 0 };
			sdl::gpuBindVertexBuffers(renderPass, 0, &b, 1);
			lastBufferVertex = buffer;
		}
	}

	void SDLBatchRenderPass::bindPipeline(GpuGraphicsPipeline* pipeline)
	{
		if (lastPipeline != pipeline) {
			sdl::gpuBindGraphicsPipeline(renderPass, pipeline);
			lastPipeline = pipeline;
		}
	}

	void SDLBatchRenderPass::bindTexture(GpuTexture* texture, GpuSampler* sampler)
	{
		if (lastTexture != texture) {
			sdl::GpuTextureSamplerBinding b = { texture, sampler };
			sdl::gpuBindFragmentSamplers(renderPass, 0, &b, 1);
			lastTexture = texture;
		}
	}
}