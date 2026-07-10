module;

#include "SDL3/SDL.h"

export module fab.BatchRenderPass;

import fab.FUtil;
import sdl.SDLHelpers;
import sdl.SDLRunner;
import std;

namespace fab {
	export class BatchRenderPass {
		struct Entry {
			::SDL_GPUGraphicsPipeline* pipeline;
			::SDL_GPUTexture* texture;
			int offset;
			int size;
		};
	public:
		BatchRenderPass(::SDL_GPUCommandBuffer* cmd, ::SDL_GPUColorTargetInfo* info, int colorAttachmentAmount = 1, ::SDL_GPUDepthStencilTargetInfo* depth = nullptr) : colorAttachmentAmount(colorAttachmentAmount), info(info), cmd(cmd), depth(depth) {}
		BatchRenderPass(const BatchRenderPass& other) = delete;

		~BatchRenderPass() {}

		inline bool canPush() const { return buffer; }
		inline void pushFragmentUniform(const void* data, fab::uint32 sizeInBytes, fab::uint32 slot = 0) { SDL_PushGPUFragmentUniformData(cmd, slot, data, sizeInBytes); };
		inline void pushVertexData(const sdl::TexProps& vertexData) { buffer[currentIndex++] = vertexData; }
		inline void pushVertexUniform(const void* data, fab::uint32 sizeInBytes, fab::uint32 slot = 0) { SDL_PushGPUVertexUniformData(cmd, slot, data, sizeInBytes); };
		template <typename T> inline void pushFragmentUniformAuto(const T* data, fab::uint32 slot = 0) { SDL_PushGPUFragmentUniformData(cmd, slot, data, sizeof(T)); };
		template <typename T> inline void pushVertexUniformAuto(const T* data, fab::uint32 slot = 0) { SDL_PushGPUVertexUniformData(cmd, slot, data, sizeof(T)); };

		void draw();
		void reset();
		void setPipeline(::SDL_GPUGraphicsPipeline* pipeline);
		void setTexture(::SDL_GPUTexture* texture);
		void start();

		static sdl::Matrix4x4 makeTransform(float tX, float tY, float sX, float sY, float rotZ = 0);
		static sdl::TexCoord makeCoord(float u0, float v0, float u1, float v1);
	private:
		int colorAttachmentAmount = 1;
		int currentIndex = 0;
		int lastIndex = 0;
		::SDL_GPUColorTargetInfo* info;
		::SDL_GPUCommandBuffer* cmd;
		::SDL_GPUDepthStencilTargetInfo* depth;
		::SDL_GPUGraphicsPipeline* lastPipeline = nullptr;
		::SDL_GPUTexture* lastTexture = nullptr;
		sdl::TexProps* buffer;
		vec<Entry> ledger;

		void queueContents();
		void queueOnBind();
	};

	void BatchRenderPass::draw() {
		if (buffer) {
			sdl::runner::deviceUnmapTexTransferBuffer();
			sdl::runner::uploadToVertexBuffer(cmd, currentIndex * sizeof(sdl::TexProps));
			buffer = nullptr;
		}

		if (currentIndex > lastIndex) {
			queueContents();
		}

		::SDL_GPURenderPass* pass = SDL_BeginGPURenderPass(cmd, info, colorAttachmentAmount, depth);
		sdl::runner::bindRenderBuffer(pass);
		::SDL_GPUGraphicsPipeline* drawPipeline = nullptr;
		::SDL_GPUTexture* drawTexture = nullptr;
		for (const Entry& entry : ledger) {
			if (drawPipeline != entry.pipeline) {
				SDL_BindGPUGraphicsPipeline(pass, entry.pipeline);
				drawPipeline = entry.pipeline;
			}
			if (drawTexture != entry.texture) {
				sdl::runner::bindTexture(pass, entry.texture);
				drawTexture = entry.texture;
			}
			SDL_DrawGPUPrimitives(pass, 6, entry.size, 0, entry.offset);
		}
		SDL_EndGPURenderPass(pass);
		ledger.clear();
		currentIndex = lastIndex = 0;
	}

	void BatchRenderPass::queueContents() {
		int entrySize = currentIndex - lastIndex;

		ledger.push_back({
			.pipeline = lastPipeline,
			.texture = lastTexture,
			.offset = lastIndex,
			.size = entrySize
		});
	}

	void BatchRenderPass::queueOnBind() {
		if (currentIndex > lastIndex) {
			queueContents();
			lastIndex = currentIndex;
		}
	}

	void BatchRenderPass::reset() {
		if (buffer) {
			sdl::runner::deviceUnmapTexTransferBuffer();
		}
		buffer = sdl::runner::deviceMapTexTransferBuffer(true);
		currentIndex = lastIndex = 0;
	}

	// Binds a pipeline if it was not already bound
	void BatchRenderPass::setPipeline(::SDL_GPUGraphicsPipeline* pipeline) {
		if (lastPipeline != pipeline) {
			queueOnBind();
			lastPipeline = pipeline;
		}
	}

	// Binds a texture if it was not already bound
	void BatchRenderPass::setTexture(::SDL_GPUTexture* texture) {
		if (lastTexture != texture) {
			queueOnBind();
			lastTexture = texture;
		}
	}

	void BatchRenderPass::start() {
		buffer = sdl::runner::deviceMapTexTransferBuffer(true);
	}

	sdl::TexCoord BatchRenderPass::makeCoord(float u0, float v0, float u1, float v1) {
		return {
			u0, v1,
			u1, v1,
			u1, v0,
			u0, v0
		};
	}

	// Automatically set up a vertex buffer based on the provided center coordinates, sizes, and rotation
	sdl::Matrix4x4 BatchRenderPass::makeTransform(float tX, float tY, float sX, float sY, float rotZ) {
		float cosZ = std::cos(rotZ);
		float sinZ = std::sin(rotZ);

		return {
			sX * cosZ, -sY * sinZ, 0, 0,
			sX * sinZ, sY * cosZ, 0, 0,
			0, 0, 1, 0,
			tX, tY, 0, 1
		};
	}
}
