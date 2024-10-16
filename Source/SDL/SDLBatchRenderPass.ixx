export module sdl.SDLBatchRenderPass;

import fab.FUtil;
import sdl.SDLBase;
import std;

namespace sdl {
	export class SDLBatchRenderPass {
	public:
		SDLBatchRenderPass(GPUCommandBuffer* cmd, GPUColorTargetInfo* info, int colorAttachmentAmount = 1, GPUDepthStencilTargetnfo* depth = nullptr): cmd(cmd), renderPass(sdl::gpuBeginRenderPass(cmd, info, colorAttachmentAmount, depth)) {}
		SDLBatchRenderPass(GPUCommandBuffer* cmd, GPURenderPass* rp): cmd(cmd), renderPass(rp) {}
		SDLBatchRenderPass(const SDLBatchRenderPass& other) = delete;
		~SDLBatchRenderPass() { gpuEndRenderPass(renderPass); }

		inline void drawIndexedPrimitives(Sint32 vertex_offset = 0, Uint32 num_indices = 6, Uint32 num_instances = 1, Uint32 first_index = 0, Uint32 first_instance = 0) const { sdl::gpuDrawIndexedPrimitives(renderPass, num_indices, num_instances, first_index, vertex_offset, first_instance); }
		inline void pushFragmentUniform(const void* data, fab::uint32 sizeInBytes, fab::uint32 slot = 0) { sdl::gpuPushFragmentUniformData(cmd, slot, data, sizeInBytes); };
		inline void pushVertexUniform(const void* data, fab::uint32 sizeInBytes, fab::uint32 slot = 0) { sdl::gpuPushVertexUniformData(cmd, slot, data, sizeInBytes); };
		inline void setScissor(RectI* rect) { sdl::gpuSetScissor(renderPass, rect); }
		template <typename T> inline void pushFragmentUniformAuto(const T* data, fab::uint32 slot = 0) { sdl::gpuPushFragmentUniformData(cmd, slot, data, sizeof(T)); };
		template <typename T> inline void pushVertexUniformAuto(const T* data, fab::uint32 slot = 0) { sdl::gpuPushVertexUniformData(cmd, slot, data, sizeof(T)); };

		void bindBufferIndex(GPUBuffer* buffer);
		void bindBufferVertex(GPUBuffer* buffer);
		void bindPipeline(GPUGraphicsPipeline* pipeline);
		void bindTexture(GPUTexture* texture, GPUSampler* sampler);
		void setupVertexUniform(float tX, float tY, float sX, float sY, float rotZ = 0);
	private:
		GPUBuffer* lastBufferIndex = nullptr;
		GPUBuffer* lastBufferVertex = nullptr;
		GPUCommandBuffer* cmd;
		GPUGraphicsPipeline* lastPipeline = nullptr;
		GPURenderPass* renderPass;
		GPUTexture* lastTexture = nullptr;
		inline static sdl::Matrix4x4 MATRIX_UNIFORM = {
		1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	};

	// Binds an index buffer if it was not already bound
	void SDLBatchRenderPass::bindBufferIndex(GPUBuffer* buffer)
	{
		if (lastBufferIndex != buffer) {
			sdl::GPUBufferBinding b = { buffer, 0 };
			sdl::gpuBindIndexBuffer(renderPass, &b, sdl::GPUIndexElementSize::SDL_GPU_INDEXELEMENTSIZE_16BIT);
			lastBufferIndex = buffer;
		}
	}

	// Binds a vertex buffer if it was not already bound
	void SDLBatchRenderPass::bindBufferVertex(GPUBuffer* buffer)
	{
		if (lastBufferVertex != buffer) {
			sdl::GPUBufferBinding b = { buffer, 0 };
			sdl::gpuBindVertexBuffers(renderPass, 0, &b, 1);
			lastBufferVertex = buffer;
		}
	}

	// Binds a pipeline if it was not already bound
	void SDLBatchRenderPass::bindPipeline(GPUGraphicsPipeline* pipeline)
	{
		if (lastPipeline != pipeline) {
			sdl::gpuBindGraphicsPipeline(renderPass, pipeline);
			lastPipeline = pipeline;
		}
	}

	// Binds a texture if it was not already bound
	void SDLBatchRenderPass::bindTexture(GPUTexture* texture, GPUSampler* sampler)
	{
		if (lastTexture != texture) {
			sdl::GPUTextureSamplerBinding b = { texture, sampler };
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
			MATRIX_UNIFORM.m12 = 2 * -sY * sinZ;
			MATRIX_UNIFORM.m21 = 2 * sX * sinZ;
			MATRIX_UNIFORM.m22 = 2 * sY * cosZ;
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