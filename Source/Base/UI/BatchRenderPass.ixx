export module fab.BatchRenderPass;

import fab.FUtil;
import sdl.SDLBase;
import sdl.SDLRunner;
import std;

namespace fab {
	export class BatchRenderPass {
	public:
		BatchRenderPass(sdl::GPUCommandBuffer* cmd, sdl::GPUColorTargetInfo* info, int colorAttachmentAmount = 1, sdl::GPUDepthStencilTargetnfo* depth = nullptr): colorAttachmentAmount(colorAttachmentAmount), info(info), cmd(cmd), depth(depth) {}
		BatchRenderPass(const BatchRenderPass& other) = delete;

		~BatchRenderPass() {}

		inline void pushFragmentUniform(const void* data, fab::uint32 sizeInBytes, fab::uint32 slot = 0) { sdl::gpuPushFragmentUniformData(cmd, slot, data, sizeInBytes); };
		inline void pushVertexData(const sdl::TexProps& vertex) { buffer[numInstances++] = vertex; }
		inline void pushVertexUniform(const void* data, fab::uint32 sizeInBytes, fab::uint32 slot = 0) { sdl::gpuPushVertexUniformData(cmd, slot, data, sizeInBytes); };
		template <typename T> inline void pushFragmentUniformAuto(const T* data, fab::uint32 slot = 0) { sdl::gpuPushFragmentUniformData(cmd, slot, data, sizeof(T)); };
		template <typename T> inline void pushVertexUniformAuto(const T* data, fab::uint32 slot = 0) { sdl::gpuPushVertexUniformData(cmd, slot, data, sizeof(T)); };

		void bindPipeline(sdl::GPUGraphicsPipeline* pipeline);
		void bindTexture(sdl::GPUTexture* texture);
		void draw();
		void flush();
		void reset();

		static sdl::Matrix4x4 makeTransform(float tX, float tY, float sX, float sY, float rotZ = 0);
		static sdl::TexCoord makeCoord(float u, float v, float texW, float texH);
	private:
		int colorAttachmentAmount = 1;
		int numInstances;
		sdl::GPUColorTargetInfo* info;
		sdl::GPUCommandBuffer* cmd;
		sdl::GPUDepthStencilTargetnfo* depth;
		sdl::GPUGraphicsPipeline* lastPipeline = nullptr;
		sdl::GPUTexture* lastTexture = nullptr;
		sdl::TexProps* buffer;
	};

	// Binds a pipeline if it was not already bound
	void BatchRenderPass::bindPipeline(sdl::GPUGraphicsPipeline* pipeline) {
		if (lastPipeline != pipeline) {
			flush();
			lastPipeline = pipeline;
		}
	}

	// Binds a texture if it was not already bound
	void BatchRenderPass::bindTexture(sdl::GPUTexture* texture) {
		if (lastTexture != texture) {
			flush();
			lastTexture = texture;
		}
	}

	void BatchRenderPass::draw() {
		if (buffer && lastPipeline && numInstances > 0) {
			sdl::runner::deviceUnmapTexTransferBuffer();
			sdl::GPUCopyPass* copyPass = sdl::gpuBeginCopyPass(cmd);
			sdl::Uint32 sizeVert = numInstances * sizeof(sdl::TexProps);
			sdl::GPUTransferBufferLocation t1 = {sdl::runner::TRANSFER_BUFFER, 0};
			sdl::GPUBufferRegion r1 = {sdl::runner::STORAGE_BUFFER, 0, sizeVert};
			sdl::gpuUploadToBuffer(copyPass, &t1, &r1, false);
			sdl::gpuEndCopyPass(copyPass);

			sdl::GPURenderPass* renderPass = sdl::gpuBeginRenderPass(cmd, info, colorAttachmentAmount, depth);
			sdl::gpuBindGraphicsPipeline(renderPass, lastPipeline);
			sdl::gpuBindVertexStorageBuffers(renderPass, 0, &sdl::runner::STORAGE_BUFFER, 1);
			if (lastTexture) {
				sdl::GPUTextureSamplerBinding b = {lastTexture, sdl::runner::SAMPLER};
				sdl::gpuBindFragmentSamplers(renderPass, 0, &b, 1);
			}
			sdl::gpuDrawGpuPrimitives(renderPass, numInstances * 6, 1, 0, 0);
			sdl::gpuEndRenderPass(renderPass);
			buffer = nullptr;
			numInstances = 0;
		}
	}

	void BatchRenderPass::flush() {
		draw();
		reset();
	}

	void BatchRenderPass::reset() {
		if (buffer) {
			sdl::runner::deviceUnmapTexTransferBuffer();
		}
		buffer = sdl::runner::deviceMapTexTransferBuffer(true);
		numInstances = 0;
	}

	sdl::TexCoord BatchRenderPass::makeCoord(float u, float v, float texW, float texH) {
		return {
			u, v,
			u + texW, v,
			u, v + texH,
			u + texW, v + texH
		};
	}

	// Automatically set up a vertex buffer based on the provided center coordinates, sizes, and rotation
	sdl::Matrix4x4 BatchRenderPass::makeTransform(float tX, float tY, float sX, float sY, float rotZ) {
		if (rotZ != 0) {
			float cosZ = std::cos(rotZ);
			float sinZ = std::sin(rotZ);

			return {
				2 * sX * cosZ, 2 * -sY * sinZ, 0, 0,
				2 * sX * sinZ, 2 * sY * cosZ, 0, 0,
				0, 0, 1, 0,
				2 * tX - 1, 1 - 2 * tY, 0, 1
			};
		}
		return {
			2 * sX, 0, 0, 0,
			0, 2 * sY, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
}
