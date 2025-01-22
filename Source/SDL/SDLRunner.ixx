module;

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <cstring>

export module sdl.SDLRunner;

import sdl.IKeyInputListener;
import sdl.SDLBase;
import std;

namespace sdl {
	constexpr auto RENDERER_VULKAN = "VULKAN";
	constexpr auto SHADER_FILL_FRAG = "Shader/Fill.frag.spv";
	constexpr auto SHADER_FILL_VERT = "Shader/Fill.vert.spv";
	constexpr auto SHADER_NORMAL_FRAG = "Shader/Normal.frag.spv";
	constexpr auto SHADER_NORMAL_VERT = "Shader/Normal.vert.spv";

	constexpr std::initializer_list<TexPos> VERTICES = {
		TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.0f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f }   // Top Left
	};
	constexpr std::initializer_list<TexPos> VERTICES_BORDERED = {
		// Top Left
		TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 0.5f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f },   // Top Left

		// Top Center
		TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 0.5f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 0.5f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Left

		// Top Right
		TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 0.5f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 0.5f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.0f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Left

		// Left
		TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 0.5f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.5f },   // Top Left

		// Center
		TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 0.5f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 0.5f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Left

		// Right
		TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 0.5f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 0.5f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.5f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Left

		// Bottom Left
		TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 1.0f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.5f },   // Top Left

		// Bottom Center
		TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 1.0f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 1.0f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Left

		// Bottom Right
		TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 1.0f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.5f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Left
	};
	constexpr std::initializer_list<TexPos> VERTICES_HORIZONTAL = {
		// Left
		TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 1.0f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f },   // Top Left

		// Center
		TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 1.0f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 1.0f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Left

		// Right
		TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 1.0f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.0f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Left
	};
	constexpr std::initializer_list<TexPos> VERTICES_VERTICAL = {
		// Top
		TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 0.5f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.0f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f },   // Top Left

		// Center
		TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 0.5f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.5f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.5f },   // Top Left

		// Bottom
		TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },  // Bottom Left
		TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },   // Bottom Right
		TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.5f },   // Top Right
		TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.5f },   // Top Left
	};
	constexpr std::initializer_list<Uint16> INDICES = { 0, 1, 2, 0, 2, 3 };

	bool enabledInternal;
	const bool* key;
	const Uint8* pad;
	int mouse = -1;
	int mouseLast = -1;
	int mousePosX = 0;
	int mousePosY = 0;
	int mouseWheelX = 0;
	int mouseWheelY = 0;
	int numKeys;
	int numPads;
	IKeyInputListener* kListener = nullptr;
	Event e;
	Gamepad* gamepad;
	GPUDevice* device;
	SDL_GPUGraphicsPipeline* RENDER_FILL;
	SDL_GPUGraphicsPipeline* RENDER_STANDARD;
	Uint64 delta;
	Uint64 fpsLimit;
	Uint64 timeCurrent;
	Uint64 timeLast;
	Uint8* keyJust;
	Uint8* padLast;
}

namespace sdl::runner {
	export SDL_GPUBuffer* BUFFER_INDEX;
	export SDL_GPUBuffer* BUFFER_VERTEX;
	export SDL_GPUBuffer* BUFFER_VERTEX_BORDERED;
	export SDL_GPUBuffer* BUFFER_VERTEX_HORIZONTAL;
	export SDL_GPUBuffer* BUFFER_VERTEX_VERTICAL;
	export SDL_GPUSampler* SAMPLER;

	export inline bool deviceClaimWindow(SDL_Window* window) { return SDL_ClaimWindowForGPUDevice(device, window); }
	export inline bool deviceIsTextureFormatSupported(SDL_GPUTextureFormat format, SDL_GPUTextureType type, SDL_GPUTextureUsageFlags usage) { return SDL_GPUTextureSupportsFormat(device, format, type, usage); }
	export inline bool deviceQueryFence(SDL_GPUFence* fence) { return SDL_QueryGPUFence(device, fence); }
	export inline bool deviceSetSwapchainParameters(SDL_Window* window, SDL_GPUSwapchainComposition swapchainComposition, SDL_GPUPresentMode presentMode) { return SDL_SetGPUSwapchainParameters(device, window, swapchainComposition, presentMode); }
	export inline bool deviceSupportsPresentMode(SDL_Window* window, SDL_GPUPresentMode presentMode) { return SDL_WindowSupportsGPUPresentMode(device, window, presentMode); }
	export inline bool deviceSupportsSwapchainComposition(SDL_Window* window, SDL_GPUSwapchainComposition swapchainComposition) { return SDL_WindowSupportsGPUSwapchainComposition(device, window, swapchainComposition); }
	export inline bool deviceTextureSupportsSampleCount(SDL_GPUTextureFormat format, SDL_GPUSampleCount desiredSampleCount) { return SDL_GPUTextureSupportsSampleCount(device, format, desiredSampleCount); }
	export inline bool enabled() { return enabledInternal; }
	export inline bool gamepadHasJustPressed(int pressed) { return pad[pressed] && !padLast[pressed]; }
	export inline bool keyboardInputActive() { return kListener != nullptr; }
	export inline bool keyboardInputActive(IKeyInputListener* listener) { return kListener == listener; }
	export inline bool keyboardJustPressed(int pressed) {return key[pressed] && keyJust[pressed] && kListener == nullptr;} // Keyboard listeners should block regular keyboard input
	export inline bool keyboardJustPressedEnter() { return keyboardJustPressed(SDLK_KP_ENTER) || keyboardJustPressed(SDLK_RETURN); }
	export inline bool keyboardJustPressedEsc() { return keyboardJustPressed(SDLK_ESCAPE); }
	export inline bool keyboardPressed(int pressed) { return key[pressed] && kListener == nullptr; }
	export inline bool mouseIsHovering(const RectF& rect) {return mousePosX >= rect.x && mousePosY >= rect.y && mousePosX < rect.x + rect.w && mousePosY < rect.y + rect.h;}
	export inline bool mouseIsHovering(const RectI rect) {return mousePosX >= rect.x && mousePosY >= rect.y && mousePosX < rect.x + rect.w && mousePosY < rect.y + rect.h;}
	export inline bool mouseIsLeftClicked() noexcept { return mouse == SDL_BUTTON_LEFT; }
	export inline bool mouseIsLeftJustClicked() noexcept { return mouse == SDL_BUTTON_LEFT && mouseLast != SDL_BUTTON_LEFT; }
	export inline bool mouseIsLeftJustReleased() noexcept { return mouse != SDL_BUTTON_LEFT && mouseLast == SDL_BUTTON_LEFT; }
	export inline bool mouseIsLeftReleased() noexcept { return mouse != SDL_BUTTON_LEFT; }
	export inline bool mouseIsRightClicked() noexcept { return mouse == SDL_BUTTON_RIGHT; }
	export inline bool mouseIsRightJustClicked() noexcept { return mouse == SDL_BUTTON_RIGHT && mouseLast != SDL_BUTTON_RIGHT; }
	export inline bool mouseIsRightJustReleased() noexcept { return mouse != SDL_BUTTON_RIGHT && mouseLast == SDL_BUTTON_RIGHT; }
	export inline bool mouseIsRightReleased() noexcept { return mouse != SDL_BUTTON_RIGHT; }
	export inline int mouseGetWheelX() noexcept { return mouseWheelX; }
	export inline int mouseGetWheelY() noexcept { return mouseWheelY; }
	export inline int mouseGetX() noexcept { return mousePosX; }
	export inline int mouseGetY() noexcept { return mousePosY; }
	export inline SDL_GPUBuffer* deviceCreateBuffer(Uint32 usageFlags, Uint32 sizeInBytes) { 
		SDL_GPUBufferCreateInfo info = { usageFlags, sizeInBytes };
		return SDL_CreateGPUBuffer(device, &info);
	}
	export inline SDL_GPUCommandBuffer* deviceAcquireCommandBuffer() { return SDL_AcquireGPUCommandBuffer(device); }
	export inline SDL_GPUComputePipeline* deviceCreateComputePipeline(SDL_GPUComputePipelineCreateInfo* computePipelineCreateInfo) { return SDL_CreateGPUComputePipeline(device, computePipelineCreateInfo); }
	export inline SDL_GPUCopyPass* deviceBeginCopyPass(SDL_GPUCommandBuffer* commandBuffer) { return SDL_BeginGPUCopyPass(commandBuffer); }
	export inline SDL_GPUGraphicsPipeline* deviceCreateGraphicsPipeline(SDL_GPUGraphicsPipelineCreateInfo* pipelineCreateInfo) { return SDL_CreateGPUGraphicsPipeline(device, pipelineCreateInfo); }
	export inline SDL_GPUSampler* deviceCreateSampler(SDL_GPUSamplerCreateInfo* samplerCreateInfo) { return SDL_CreateGPUSampler(device, samplerCreateInfo); }
	export inline SDL_GPUShader* deviceCreateShader(SDL_GPUShaderCreateInfo* shaderCreateInfo) { return SDL_CreateGPUShader(device, shaderCreateInfo); }
	export inline SDL_GPUTexture* deviceCreateTexture(SDL_GPUTextureCreateInfo* textureCreateInfo) { return SDL_CreateGPUTexture(device, textureCreateInfo); }
	export inline SDL_GPUTextureFormat deviceGetSwapchainTextureFormat(SDL_Window* window) { return SDL_GetGPUSwapchainTextureFormat(device, window); }
	export inline SDL_GPUTransferBuffer* deviceCreateTransferBuffer(SDL_GPUTransferBufferUsage usage, Uint32 sizeInBytes) { 
		SDL_GPUTransferBufferCreateInfo info = {usage, sizeInBytes};
		return SDL_CreateGPUTransferBuffer(device, &info);
	}
	export inline Uint64 timeDelta() { return delta; }
	export inline Uint64 timeTotal() { return timeCurrent; }
	export inline void deviceReleaseBuffer(SDL_GPUBuffer* buffer) { SDL_ReleaseGPUBuffer(device, buffer); }
	export inline void deviceReleaseComputePipeline(SDL_GPUComputePipeline* computePipeline) { SDL_ReleaseGPUComputePipeline(device, computePipeline); }
	export inline void deviceReleaseFence(SDL_GPUFence* fence) { SDL_ReleaseGPUFence(device, fence); }
	export inline void deviceReleaseGraphicsPipeline(SDL_GPUGraphicsPipeline* graphicsPipeline) { SDL_ReleaseGPUGraphicsPipeline(device, graphicsPipeline); }
	export inline void deviceReleaseSampler(SDL_GPUSampler* sampler) { SDL_ReleaseGPUSampler(device, sampler); }
	export inline void deviceReleaseShader(SDL_GPUShader* shader) { SDL_ReleaseGPUShader(device, shader); }
	export inline void deviceReleaseTexture(SDL_GPUTexture* texture) { SDL_ReleaseGPUTexture(device, texture); }
	export inline void deviceReleaseTransferBuffer(SDL_GPUTransferBuffer* transferBuffer) { SDL_ReleaseGPUTransferBuffer(device, transferBuffer); }
	export inline void deviceSetBufferName(SDL_GPUBuffer* buffer, const char* text) { SDL_SetGPUBufferName(device, buffer, text); }
	export inline void deviceSetTextureName(SDL_GPUTexture* texture, const char* text) { SDL_SetGPUTextureName(device, texture, text); }
	export inline void deviceUnclaimWindow(SDL_Window* window) { SDL_ReleaseWindowFromGPUDevice(device, window); }
	export inline void deviceUnmapTransferBuffer(SDL_GPUTransferBuffer* transferBuffer) { SDL_UnmapGPUTransferBuffer(device, transferBuffer); }
	export inline void deviceWait() { SDL_WaitForGPUIdle(device); }
	export inline void deviceWaitForFences(bool waitAll, SDL_GPUFence** pFences, Uint32 fenceCount) { SDL_WaitForGPUFences(device, waitAll, pFences, fenceCount); }
	export inline void setFPSLimit(int fps) { fpsLimit = fps > 0 ? NANOS_PER_SECOND / fps : 0; }
	export inline void* deviceMapTransferBuffer(SDL_GPUTransferBuffer* transferBuffer, bool cycle) { return SDL_MapGPUTransferBuffer(device, transferBuffer, cycle); }

	export bool init(const char* renderer = RENDERER_VULKAN, const char* normalFrag = SHADER_NORMAL_FRAG, const char* normalVert = SHADER_NORMAL_VERT, const char* fillFrag = SHADER_FILL_FRAG, const char* fillVert = SHADER_FILL_VERT);
	export bool poll();
	export GPUGraphicsPipeline* createPipeline(GPUShader* vertexShader, GPUShader* fragmentShader, GPUTextureFormat textureFormat = GPUTextureFormat::SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM, GPUBlendFactor srcColor = GPUBlendFactor::SDL_GPU_BLENDFACTOR_SRC_ALPHA, GPUBlendFactor dstColor = GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, GPUBlendFactor srcAlpha = GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE, GPUBlendFactor dstAlpha = GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA);
	export GPUGraphicsPipeline* createShapePipeline(GPUShader* vertexShader, GPUShader* fragmentShader, GPUTextureFormat textureFormat = GPUTextureFormat::SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM, GPUBlendFactor srcColor = GPUBlendFactor::SDL_GPU_BLENDFACTOR_SRC_ALPHA, GPUBlendFactor dstColor = GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, GPUBlendFactor srcAlpha = GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE, GPUBlendFactor dstAlpha = GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA);
	export GPUGraphicsPipeline* pipelineForMode(RenderMode mode);
	export GPUGraphicsPipeline* shapePipelineForMode(RenderMode mode);
	export GPUShader* loadShader(const char* shaderFilename, GPUShaderStage stage, Uint32 samplerCount, Uint32 uniformBufferCount, Uint32 storageBufferCount = 0, Uint32 storageTextureCount = 0);
	export GPUTexture* uploadTexture(GPUCopyPass* copyPass, Surface* surface);
	export GPUTexture* uploadTexture(GPUCopyPass* copyPass, Surface* surface, GPUTransferBuffer* textureTransferBuffer);
	export GPUTexture* uploadTextureForArray(GPUCopyPass* copyPass, Surface* surface, GPUTexture* texture, GPUTransferBuffer* textureTransferBuffer, Uint32 layer);
	export void capFrame();
	export void keyboardInputStart(Window* window, IKeyInputListener* listener);
	export void keyboardInputStop(Window* window);
	export void keyboardInputStopRequest(Window* window, IKeyInputListener* listener);
	export void quit();
}

/* IMPLEMENTATIONS */

namespace sdl::runner {

	// Set up SDL. Returns true if SDL setup succeeds
	bool init(const char* renderer, const char* normalFrag, const char* normalVert, const char* fillFrag, const char* fillVert) {
		int val = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD);
		if (val < 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_INIT failed with value %d", val);
			return false;
		}

		if (!TTF_Init()) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed: %s", SDL_GetError());
			return false;
		}

		// TODO adjust spec as needed
		if (!Mix_OpenAudio(0, nullptr)) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio failed: %s", SDL_GetError());
			return false;
		}

		// Initialize driver
		device = SDL_CreateGPUDevice(gpuSpirvShaderFormats(), false, renderer);
		if (!device) {
			SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Device went derp: %s", getError());
			return false;
		}

		// Initialize keyboard
		key = SDL_GetKeyboardState(&numKeys);
		keyJust = new Uint8[numKeys];
		memcpy(keyJust, key, numKeys);

		// Initialize basic vertex and indices
		constexpr size_t size = sizeof(TexPos);
		constexpr Uint32 sizeVert = size * VERTICES.size();
		constexpr Uint32 sizeVertBordered = size * VERTICES_BORDERED.size();
		constexpr Uint32 sizeVertHorizontal = size * VERTICES_HORIZONTAL.size();
		constexpr Uint32 sizeVertVertical = size * VERTICES_VERTICAL.size();
		constexpr Uint32 sizeIndices = size * INDICES.size();
		BUFFER_VERTEX = deviceCreateBuffer(SDL_GPU_BUFFERUSAGE_VERTEX, sizeVert);
		BUFFER_VERTEX_BORDERED = deviceCreateBuffer(SDL_GPU_BUFFERUSAGE_VERTEX, sizeVertBordered);
		BUFFER_VERTEX_HORIZONTAL = deviceCreateBuffer(SDL_GPU_BUFFERUSAGE_VERTEX, sizeVertHorizontal);
		BUFFER_VERTEX_VERTICAL = deviceCreateBuffer(SDL_GPU_BUFFERUSAGE_VERTEX, sizeVertVertical);
		BUFFER_INDEX = deviceCreateBuffer(SDL_GPU_BUFFERUSAGE_INDEX, sizeIndices);

		GPUTransferBuffer* bufferTransferBuffer = deviceCreateTransferBuffer(
			GPUTransferBufferUsage::SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			(sizeVert + sizeVertBordered + sizeVertHorizontal + sizeVertVertical + sizeIndices)
		);
		void* transferData = deviceMapTransferBuffer(bufferTransferBuffer,false);

		TexPos* vertexData = reinterpret_cast<TexPos*>(transferData);
		int i = 0;
		for (const TexPos& pos : VERTICES) {
			vertexData[i++] = pos;
		}
		for (const TexPos& pos : VERTICES_BORDERED) {
			vertexData[i++] = pos;
		}
		for (const TexPos& pos : VERTICES_HORIZONTAL) {
			vertexData[i++] = pos;
		}
		for (const TexPos& pos : VERTICES_VERTICAL) {
			vertexData[i++] = pos;
		}

		Uint16* indexData = reinterpret_cast<Uint16*>(&vertexData[i]);
		i = 0;
		for (const Uint16& pos : INDICES) {
			indexData[i++] = pos;
		}

		deviceUnmapTransferBuffer(bufferTransferBuffer);

		GPUCommandBuffer* uploadCmdBuf = gpuAcquireCommandBuffer(device);
		GPUCopyPass* copyPass = gpuBeginCopyPass(uploadCmdBuf);

		GPUTransferBufferLocation t1 = { bufferTransferBuffer , 0 };
		GPUBufferRegion r1 = { BUFFER_VERTEX, 0, sizeVert };
		gpuUploadToBuffer(copyPass, &t1, &r1, false);

		GPUTransferBufferLocation t2 = { bufferTransferBuffer , sizeVert };
		GPUBufferRegion r2 = { BUFFER_VERTEX_BORDERED, 0, sizeVertBordered };
		gpuUploadToBuffer(copyPass, &t2, &r2, false);

		GPUTransferBufferLocation t3 = { bufferTransferBuffer ,sizeVert + sizeVertBordered };
		GPUBufferRegion r3 = { BUFFER_VERTEX_HORIZONTAL, 0, sizeVertHorizontal };
		gpuUploadToBuffer(copyPass, &t3, &r3, false);

		GPUTransferBufferLocation t4 = { bufferTransferBuffer , sizeVert + sizeVertBordered + sizeVertHorizontal };
		GPUBufferRegion r4 = { BUFFER_VERTEX_VERTICAL, 0, sizeVertVertical };
		gpuUploadToBuffer(copyPass, &t4, &r4, false);

		GPUTransferBufferLocation t5 = { bufferTransferBuffer , sizeVert + sizeVertBordered + sizeVertHorizontal + sizeVertVertical };
		GPUBufferRegion r5 = { BUFFER_INDEX, 0, sizeIndices };
		gpuUploadToBuffer(copyPass, &t5, &r5, false);

		gpuEndCopyPass(copyPass);
		gpuSubmit(uploadCmdBuf);
		gpuReleaseTransferBuffer(device, bufferTransferBuffer);

		// Initialize samplers
		GPUSamplerCreateInfo samplerInfo = {
			.min_filter = GPUFilter::SDL_GPU_FILTER_LINEAR,
			.mag_filter = GPUFilter::SDL_GPU_FILTER_LINEAR,
			.mipmap_mode = GPUSamplerMipmapMode::SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
			.address_mode_u = GPUSamplerAddressMode::SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
			.address_mode_v = GPUSamplerAddressMode::SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
			.address_mode_w = GPUSamplerAddressMode::SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
		};
		SAMPLER = gpuCreateSampler(device, &samplerInfo);

		// Set up pipelines
		GPUShader* shaderFragment = loadShader(normalFrag, SDL_GPU_SHADERSTAGE_FRAGMENT, 1, 1);
		GPUShader* shaderVertex = loadShader(normalVert, SDL_GPU_SHADERSTAGE_VERTEX, 0, 1);
		RENDER_STANDARD = createPipeline(shaderVertex, shaderFragment);

		GPUShader* shaderFillFragment = loadShader(fillFrag, SDL_GPU_SHADERSTAGE_FRAGMENT, 1, 1);
		GPUShader* shaderFillVertex = loadShader(fillVert, SDL_GPU_SHADERSTAGE_VERTEX, 0, 1);
		RENDER_FILL = createPipeline(shaderFillVertex, shaderFillFragment);
		// TODO more shaders/blending modes

		gpuReleaseShader(device, shaderFragment);
		gpuReleaseShader(device, shaderVertex);

		// TODO initialize pad

		enabledInternal = true;

		return true;
	}

	// Execute a singular game loop. Returns false if the program should terminate 
	export bool poll() {
		// Update time
		timeCurrent = SDL_GetTicksNS();
		delta = timeCurrent - timeLast;
		timeLast = timeCurrent;

		// Update temporary states
		mouseLast = mouse;
		mouseWheelX = 0;
		mouseWheelY = 0;
		std::memset(keyJust, 0, numKeys);

		// Update input events
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_EVENT_QUIT:
				return false;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				mouse = e.button.button;
				mousePosX = e.button.x;
				mousePosY = e.button.y;
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				mouse = -1;
				mousePosX = e.button.x;
				mousePosY = e.button.y;
				break;
			case SDL_EVENT_MOUSE_MOTION:
				mousePosX = e.button.x;
				mousePosY = e.button.y;
				break;
			case SDL_EVENT_MOUSE_WHEEL:
				mouseWheelX = e.wheel.x;
				mouseWheelY = e.wheel.y;
				break;
				// Key down: If a listener is present, special keys will trigger listeners. These keys are independent of hotkey settings
			case SDL_EVENT_KEY_DOWN:
				if (kListener) {
					kListener->onKeyPress(e.key.key);
				}
				keyJust[e.key.scancode] = 1;
				break;
			case SDL_EVENT_KEY_UP:
				keyJust[e.key.scancode] = 1;
				break;
			case SDL_EVENT_TEXT_INPUT:
				if (kListener) {
					kListener->onTextInput(e.text.text);
				}
				break;
				// TODO file dialog
			case SDL_EVENT_DROP_FILE:
				break;
			}
		}

		return true;
	}

	// Generates a graphics pipeline to be used for this window
	GPUGraphicsPipeline* createPipeline(GPUShader* vertexShader, GPUShader* fragmentShader, GPUTextureFormat textureFormat, GPUBlendFactor srcColor, GPUBlendFactor dstColor, GPUBlendFactor srcAlpha, GPUBlendFactor dstAlpha)
	{
		GPUVertexBufferDescription vertexBindings[] = { {
					.slot = 0,
					.pitch = sizeof(TexPos),
					.input_rate = GPUVertexInputRate::SDL_GPU_VERTEXINPUTRATE_VERTEX,
					.instance_step_rate = 0
		} };
		GPUVertexAttribute vertexAttributes[] = { {
					.location = 0,
					.buffer_slot = 0,
					.format = GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
					.offset = 0
				}, {
					.location = 1,
					.buffer_slot = 0,
					.format = GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
					.offset = sizeof(float) * 3
				} };
		GPUColorTargetDescription colorAttachmentDescriptions[] = { {
					.format = textureFormat,
					.blend_state = {
						.src_color_blendfactor = srcColor,
						.dst_color_blendfactor = dstColor,
						.color_blend_op = GPUBlendOp::SDL_GPU_BLENDOP_ADD,
						.src_alpha_blendfactor = srcAlpha,
						.dst_alpha_blendfactor = dstAlpha,
						.alpha_blend_op = GPUBlendOp::SDL_GPU_BLENDOP_ADD,
						.color_write_mask = 0xF,
						.enable_blend = true
					}
				} };
		GPUGraphicsPipelineCreateInfo pipelineCreateInfo = {
			.vertex_shader = vertexShader,
			.fragment_shader = fragmentShader,
			.vertex_input_state = {
				.vertex_buffer_descriptions = vertexBindings,
				.num_vertex_buffers = 1,
				.vertex_attributes = vertexAttributes,
				.num_vertex_attributes = 2,
			},
			.primitive_type = GPUPrimitiveType::SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
			.rasterizer_state = {},
			.multisample_state = {
				.sample_mask = 0xFFFF
			},
			.depth_stencil_state = {},
			.target_info = {
				.color_target_descriptions = colorAttachmentDescriptions,
				.num_color_targets = 1
			}
		};

		return gpuCreateGraphicsPipeline(device, &pipelineCreateInfo);
	}

	// Generates a non-texture graphics pipeline to be used for this window
	GPUGraphicsPipeline* createShapePipeline(GPUShader* vertexShader, GPUShader* fragmentShader, GPUTextureFormat textureFormat, GPUBlendFactor srcColor, GPUBlendFactor dstColor, GPUBlendFactor srcAlpha, GPUBlendFactor dstAlpha)
	{
		GPUColorTargetDescription colorAttachmentDescriptions[] = { {
			.format = textureFormat,
			.blend_state = {
				.src_color_blendfactor = srcColor,
				.dst_color_blendfactor = dstColor,
				.color_blend_op = GPUBlendOp::SDL_GPU_BLENDOP_ADD,
				.src_alpha_blendfactor = srcAlpha,
				.dst_alpha_blendfactor = dstAlpha,
				.alpha_blend_op = GPUBlendOp::SDL_GPU_BLENDOP_ADD,
				.color_write_mask = 0xF,
				.enable_blend = true
			}
		} };
		GPUGraphicsPipelineCreateInfo pipelineCreateInfo = {
			.vertex_shader = vertexShader,
			.fragment_shader = fragmentShader,
			.vertex_input_state = {
			},
			.primitive_type = GPUPrimitiveType::SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
			.rasterizer_state = {
				.fill_mode = SDL_GPUFillMode::SDL_GPU_FILLMODE_FILL
			},
			.multisample_state = {
				.sample_mask = 0xFFFF
			},
			.depth_stencil_state = {},
			.target_info = {
				.color_target_descriptions = colorAttachmentDescriptions,
				.num_color_targets = 1
			},
		};

		return gpuCreateGraphicsPipeline(device, &pipelineCreateInfo);
	}

	// TODO more pipelines
	GPUGraphicsPipeline* pipelineForMode(RenderMode mode)
	{
		return RENDER_STANDARD;
	}

	GPUGraphicsPipeline* shapePipelineForMode(RenderMode mode)
	{
		return RENDER_FILL;
	}

	// Generates a shader to be used for this window
	GPUShader* loadShader(const char* shaderFilename, GPUShaderStage stage, Uint32 samplerCount, Uint32 uniformBufferCount, Uint32 storageBufferCount, Uint32 storageTextureCount)
	{
		size_t codeSize;
		std::filesystem::path name = sdl::dirBase();
		name /= shaderFilename;
		void* code = fileLoad(name.string().data(), &codeSize);
		if (code == nullptr)
		{
			logError("Failed to load shader from disk: %s, %s", name.string().data(), getError());
			return nullptr;
		}

		GPUShaderCreateInfo shaderInfo = {
			.code_size = codeSize,
			.code = static_cast<const Uint8*>(code),
			.entrypoint = "main",
			.format = SDL_GPU_SHADERFORMAT_SPIRV,
			.stage = stage,
			.num_samplers = samplerCount,
			.num_storage_textures = storageTextureCount,
			.num_storage_buffers = storageBufferCount,
			.num_uniform_buffers = uniformBufferCount,
		};
		GPUShader* shader = gpuCompileSpirvShader(device, &shaderInfo);
		free(code);
		return shader;
	}

	// Convert a surface into a texture to be used for rendering
	GPUTexture* uploadTexture(GPUCopyPass* copyPass, Surface* surface)
	{
		GPUTransferBuffer* textureTransferBuffer = runner::deviceCreateTransferBuffer(
			GPUTransferBufferUsage::SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			surface->w * surface->h * 4
		);
		GPUTexture* tex = uploadTexture(copyPass, surface, textureTransferBuffer);
		runner::deviceReleaseTransferBuffer(textureTransferBuffer);
		return tex;
	}

	// Convert a surface into a texture to be used for rendering
	GPUTexture* uploadTexture(GPUCopyPass* copyPass, Surface* surface, GPUTransferBuffer* textureTransferBuffer)
	{
		Uint32 w = surface->w;
		Uint32 h = surface->h;
		const Uint32 imageSizeInBytes = w * h * 4;

		void* textureTransferPtr = deviceMapTransferBuffer(textureTransferBuffer, false);
		std::memcpy(textureTransferPtr, surface->pixels, imageSizeInBytes);
		runner::deviceUnmapTransferBuffer(textureTransferBuffer);

		GPUTextureCreateInfo info = {
				.type = SDL_GPU_TEXTURETYPE_2D,
				.format = GPUTextureFormat::SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
				.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
				.width = w,
				.height = h,
				.layer_count_or_depth = 1,
				.num_levels = 1,
				.sample_count = GPUSampleCount::SDL_GPU_SAMPLECOUNT_1,
		};
		GPUTexture* texture = runner::deviceCreateTexture(&info);

		GPUTextureTransferInfo tInfo = {
			.transfer_buffer = textureTransferBuffer,
			.offset = 0,
		};
		GPUTextureRegion tRegion = {
			.texture = {texture},
			.mip_level = 0,
			.layer = 0,
				.w = w,
				.h = h,
				.d = 1
		};

		gpuUploadToTexture(copyPass, &tInfo, &tRegion, false);
		return texture;
	}

	// Add a surface into a texture array to be used for rendering
	GPUTexture* uploadTextureForArray(GPUCopyPass* copyPass, Surface* surface, GPUTexture* texture, GPUTransferBuffer* textureTransferBuffer, Uint32 layer)
	{
		Uint32 w = surface->w;
		Uint32 h = surface->h;
		const Uint32 imageSizeInBytes = w * h * 4;

		void* textureTransferPtr = deviceMapTransferBuffer(textureTransferBuffer, false);
		std::memcpy(textureTransferPtr, surface->pixels, imageSizeInBytes);
		runner::deviceUnmapTransferBuffer(textureTransferBuffer);

		GPUTextureTransferInfo tInfo = {
			.transfer_buffer = textureTransferBuffer,
			.offset = imageSizeInBytes * layer,
		};
		GPUTextureRegion tRegion = {
			.texture = texture,
			.mip_level = 0,
			.layer = layer,
			.w = w,
			.h = h,
			.d = 1
		};

		gpuUploadToTexture(copyPass, &tInfo, &tRegion, false);
		return texture;
	}

	// When using a fixed framerate, sleep to fill up remaining time
	void capFrame() {
		if (fpsLimit > delta) {
			SDL_Delay(fpsLimit - delta);
		}
	}

	// Activate a key input listener attached to the given window. Only one listener can be active across all windows
	export void keyboardInputStart(Window* window, IKeyInputListener* listener) {
		if (!kListener) {
			kListener = listener;
			SDL_StartTextInput(window);
		}
	}

	// Stop the current listener
	export void keyboardInputStop(Window* window) {
		kListener = nullptr;
		SDL_StopTextInput(window);
	}

	// Stop a specific listener in the given window
	export void keyboardInputStopRequest(Window* window, IKeyInputListener* listener) {
		if (kListener == listener) {
			kListener = nullptr;
			SDL_StopTextInput(window);
		}
	}

	// Clean up SDL
	export void quit() {
		gpuReleaseBuffer(device, BUFFER_VERTEX_BORDERED);
		gpuReleaseBuffer(device, BUFFER_VERTEX_HORIZONTAL);
		gpuReleaseBuffer(device, BUFFER_VERTEX_VERTICAL);
		gpuReleaseBuffer(device, BUFFER_INDEX);
		gpuReleaseGraphicsPipeline(device, RENDER_STANDARD);
		gpuReleaseSampler(device, SAMPLER);
		BUFFER_VERTEX = nullptr;
		BUFFER_VERTEX_BORDERED = nullptr;
		BUFFER_VERTEX_HORIZONTAL = nullptr;
		BUFFER_VERTEX_VERTICAL = nullptr;
		BUFFER_INDEX = nullptr;
		RENDER_STANDARD = nullptr;
		SAMPLER = nullptr;

		SDL_DestroyGPUDevice(device);
		device = nullptr;
		TTF_Quit();
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		enabledInternal = false;
	}
}