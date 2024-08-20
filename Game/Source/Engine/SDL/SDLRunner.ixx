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
	constexpr auto SHADER_NORMAL_FRAG = "Shader/Compiled/Normal.frag.spv";
	constexpr auto SHADER_NORMAL_VERT = "Shader/Compiled/Normal.vert.spv";

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
	const std::uint8_t* key;
	const std::uint8_t* pad;
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
	GpuDevice* device;
	SDL_GpuGraphicsPipeline* RENDER_FILL;
	SDL_GpuGraphicsPipeline* RENDER_STANDARD;
	std::uint64_t delta;
	std::uint64_t fpsLimit;
	std::uint64_t timeCurrent;
	std::uint64_t timeLast;
	std::uint8_t* keyJust;
	std::uint8_t* padLast;
}

namespace sdl::runner {
	export SDL_GpuBuffer* BUFFER_INDEX;
	export SDL_GpuBuffer* BUFFER_VERTEX;
	export SDL_GpuBuffer* BUFFER_VERTEX_BORDERED;
	export SDL_GpuBuffer* BUFFER_VERTEX_HORIZONTAL;
	export SDL_GpuBuffer* BUFFER_VERTEX_VERTICAL;
	export SDL_GpuSampler* SAMPLER;

	export inline bool gamepadHasJustPressed(int pressed) { return pad[pressed] && !padLast[pressed]; }
	export inline bool keyboardInputActive() { return kListener != nullptr; }
	export inline bool keyboardInputActive(IKeyInputListener* listener) { return kListener == listener; }
	export inline bool keyboardJustPressed(int pressed) {return key[pressed] && keyJust[pressed] && kListener == nullptr;} // Keyboard listeners should block regular keyboard input
	export inline bool keyboardJustPressedEnter() { return keyboardJustPressed(SDLK_KP_ENTER) || keyboardJustPressed(SDLK_RETURN); }
	export inline bool keyboardJustPressedEsc() { return keyboardJustPressed(SDLK_ESCAPE); }
	export inline bool keyboardPressed(int pressed) { return key[pressed] && kListener == nullptr; }
	export inline int mouseGetWheelX() noexcept { return mouseWheelX; }
	export inline int mouseGetWheelY() noexcept { return mouseWheelY; }
	export inline int mouseGetX() noexcept { return mousePosX; }
	export inline int mouseGetY() noexcept { return mousePosY; }
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
	export inline bool enabled() { return enabledInternal; }
	export inline SDL_bool deviceClaimWindow(SDL_Window* window, SDL_GpuSwapchainComposition swapchainComposition, SDL_GpuPresentMode presentMode) { return SDL_GpuClaimWindow(device, window, swapchainComposition, presentMode); }
	export inline SDL_bool deviceIsTextureFormatSupported(SDL_GpuTextureFormat format, SDL_GpuTextureType type, SDL_GpuTextureUsageFlags usage) { return SDL_GpuSupportsTextureFormat(device, format, type, usage); }
	export inline SDL_bool deviceQueryFence(SDL_GpuFence* fence) { return SDL_GpuQueryFence(device, fence); }
	export inline SDL_bool deviceSetSwapchainParameters(SDL_Window* window, SDL_GpuSwapchainComposition swapchainComposition, SDL_GpuPresentMode presentMode) { return SDL_GpuSetSwapchainParameters(device, window, swapchainComposition, presentMode); }
	export inline SDL_bool deviceSupportsPresentMode(SDL_Window* window, SDL_GpuPresentMode presentMode) { return SDL_GpuSupportsPresentMode(device, window, presentMode); }
	export inline SDL_bool deviceSupportsSwapchainComposition(SDL_Window* window, SDL_GpuSwapchainComposition swapchainComposition) { return SDL_GpuSupportsSwapchainComposition(device, window, swapchainComposition); }
	export inline SDL_GpuBuffer* deviceCreateBuffer(SDL_GpuBufferUsageFlags usageFlags, Uint32 sizeInBytes) { return SDL_GpuCreateBuffer(device, usageFlags, sizeInBytes); }
	export inline SDL_GpuCommandBuffer* deviceAcquireCommandBuffer() { return SDL_GpuAcquireCommandBuffer(device); }
	export inline SDL_GpuComputePipeline* deviceCreateComputePipeline(SDL_GpuComputePipelineCreateInfo* computePipelineCreateInfo) { return SDL_GpuCreateComputePipeline(device, computePipelineCreateInfo); }
	export inline SDL_GpuCopyPass* deviceBeginCopyPass(SDL_GpuCommandBuffer* commandBuffer) { return SDL_GpuBeginCopyPass(commandBuffer); }
	export inline SDL_GpuDriver deviceGetDriver() { return SDL_GpuGetDriver(device); }
	export inline SDL_GpuGraphicsPipeline* deviceCreateGraphicsPipeline(SDL_GpuGraphicsPipelineCreateInfo* pipelineCreateInfo) { return SDL_GpuCreateGraphicsPipeline(device, pipelineCreateInfo); }
	export inline SDL_GpuSampleCount deviceGetBestSampleCount(SDL_GpuTextureFormat format, SDL_GpuSampleCount desiredSampleCount) { return SDL_GpuGetBestSampleCount(device, format, desiredSampleCount); }
	export inline SDL_GpuSampler* deviceCreateSampler(SDL_GpuSamplerCreateInfo* samplerCreateInfo) { return SDL_GpuCreateSampler(device, samplerCreateInfo); }
	export inline SDL_GpuShader* deviceCreateShader(SDL_GpuShaderCreateInfo* shaderCreateInfo) { return SDL_GpuCreateShader(device, shaderCreateInfo); }
	export inline SDL_GpuTexture* deviceCreateTexture(SDL_GpuTextureCreateInfo* textureCreateInfo) { return SDL_GpuCreateTexture(device, textureCreateInfo); }
	export inline SDL_GpuTextureFormat deviceGetSwapchainTextureFormat(SDL_Window* window) { return SDL_GpuGetSwapchainTextureFormat(device, window); }
	export inline SDL_GpuTransferBuffer* deviceCreateTransferBuffer(SDL_GpuTransferBufferUsage usage, Uint32 sizeInBytes) { return SDL_GpuCreateTransferBuffer(device, usage, sizeInBytes); }
	export inline Uint64 timeDelta() { return delta; }
	export inline Uint64 timeTotal() { return timeCurrent; }
	export inline void deviceMapTransferBuffer(SDL_GpuTransferBuffer* transferBuffer, SDL_bool cycle, void** ppData) { SDL_GpuMapTransferBuffer(device, transferBuffer, cycle, ppData); }
	export inline void deviceReleaseBuffer(SDL_GpuBuffer* buffer) { SDL_GpuReleaseBuffer(device, buffer); }
	export inline void deviceReleaseComputePipeline(SDL_GpuComputePipeline* computePipeline) { SDL_GpuReleaseComputePipeline(device, computePipeline); }
	export inline void deviceReleaseFence(SDL_GpuFence* fence) { SDL_GpuReleaseFence(device, fence); }
	export inline void deviceReleaseGraphicsPipeline(SDL_GpuGraphicsPipeline* graphicsPipeline) { SDL_GpuReleaseGraphicsPipeline(device, graphicsPipeline); }
	export inline void deviceReleaseSampler(SDL_GpuSampler* sampler) { SDL_GpuReleaseSampler(device, sampler); }
	export inline void deviceReleaseShader(SDL_GpuShader* shader) { SDL_GpuReleaseShader(device, shader); }
	export inline void deviceReleaseTexture(SDL_GpuTexture* texture) { SDL_GpuReleaseTexture(device, texture); }
	export inline void deviceReleaseTransferBuffer(SDL_GpuTransferBuffer* transferBuffer) { SDL_GpuReleaseTransferBuffer(device, transferBuffer); }
	export inline void deviceSetBufferName(SDL_GpuBuffer* buffer, const char* text) { SDL_GpuSetBufferName(device, buffer, text); }
	export inline void deviceSetTextureName(SDL_GpuTexture* texture, const char* text) { SDL_GpuSetTextureName(device, texture, text); }
	export inline void deviceUnclaimWindow(SDL_Window* window) { SDL_GpuUnclaimWindow(device, window); }
	export inline void deviceUnmapTransferBuffer(SDL_GpuTransferBuffer* transferBuffer) { SDL_GpuUnmapTransferBuffer(device, transferBuffer); }
	export inline void deviceWait() { SDL_GpuWait(device); }
	export inline void deviceWaitForFences(SDL_bool waitAll, SDL_GpuFence** pFences, Uint32 fenceCount) { SDL_GpuWaitForFences(device, waitAll, pFences, fenceCount); }
	export inline void setFPSLimit(int fps) { fpsLimit = fps > 0 ? NANOS_PER_SECOND / fps : 0; }

	export bool init(const char* renderer = RENDERER_VULKAN);
	export bool poll();
	export GpuGraphicsPipeline* createPipeline(GpuShader* vertexShader, GpuShader* fragmentShader, GpuTextureFormat textureFormat = GpuTextureFormat::SDL_GPU_TEXTUREFORMAT_B8G8R8A8, GpuBlendFactor srcColor = GpuBlendFactor::SDL_GPU_BLENDFACTOR_SRC_ALPHA, GpuBlendFactor dstColor = GpuBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, GpuBlendFactor srcAlpha = GpuBlendFactor::SDL_GPU_BLENDFACTOR_ONE, GpuBlendFactor dstAlpha = GpuBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA);
	export GpuGraphicsPipeline* createShapePipeline(GpuShader* vertexShader, GpuShader* fragmentShader, GpuTextureFormat textureFormat = GpuTextureFormat::SDL_GPU_TEXTUREFORMAT_B8G8R8A8, GpuBlendFactor srcColor = GpuBlendFactor::SDL_GPU_BLENDFACTOR_SRC_ALPHA, GpuBlendFactor dstColor = GpuBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, GpuBlendFactor srcAlpha = GpuBlendFactor::SDL_GPU_BLENDFACTOR_ONE, GpuBlendFactor dstAlpha = GpuBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA);
	export GpuGraphicsPipeline* pipelineForMode(RenderMode mode);
	export GpuGraphicsPipeline* shapePipelineForMode(RenderMode mode);
	export GpuShader* loadShader(const char* shaderFilename, GpuShaderStage stage, Uint32 samplerCount = 1, Uint32 uniformBufferCount = 1, Uint32 storageBufferCount = 0, Uint32 storageTextureCount = 0);
	export GpuTexture* uploadTexture(GpuCopyPass* copyPass, Surface* surface);
	export GpuTexture* uploadTexture(GpuCopyPass* copyPass, Surface* surface, GpuTransferBuffer* textureTransferBuffer);
	export GpuTexture* uploadTextureForArray(GpuCopyPass* copyPass, Surface* surface, GpuTexture* texture, GpuTransferBuffer* textureTransferBuffer, Uint32 layer);
	export void capFrame();
	export void keyboardInputStart(Window* window, IKeyInputListener* listener);
	export void keyboardInputStop(Window* window);
	export void keyboardInputStopRequest(Window* window, IKeyInputListener* listener);
	export void quit();
}

/* IMPLEMENTATIONS */

namespace sdl::runner {

	// Set up SDL. Returns true if SDL setup succeeds
	bool init(const char* renderer) {
		int val = SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD);
		if (val < 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_INIT failed with value %d", val);
			return false;
		}

		val = IMG_Init(IMG_INIT_PNG);
		if (val == 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init failed with value %d", val);
			return false;
		}

		if (TTF_Init() < 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed");
			return false;
		}

		// TODO adjust spec as needed
		if (Mix_OpenAudio(0, nullptr) < 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio failed");
			return false;
		}

		// Initialize keyboard
		key = SDL_GetKeyboardState(&numKeys);
		keyJust = new Uint8[numKeys];
		memcpy(keyJust, key, numKeys);

		// Initialize driver
		SDL_PropertiesID id = SDL_CreateProperties();
		SDL_SetStringProperty(id, SDL_PROP_GPU_CREATEDEVICE_NAME_STRING, renderer);
		device = SDL_GpuCreateDevice(SDL_FALSE, SDL_FALSE, id);
		if (!device) {
			SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Device went derp: %s", getError());
			return false;
		}

		// Initialize basic vertex and indices
		constexpr size_t size = sizeof(TexPos);
		constexpr Uint32 sizeVert = size * VERTICES.size();
		constexpr Uint32 sizeVertBordered = size * VERTICES_BORDERED.size();
		constexpr Uint32 sizeVertHorizontal = size * VERTICES_HORIZONTAL.size();
		constexpr Uint32 sizeVertVertical = size * VERTICES_VERTICAL.size();
		constexpr Uint32 sizeIndices = size * INDICES.size();
		BUFFER_VERTEX = gpuCreateBuffer(device, GpuBufferUsageFlagBits::SDL_GPU_BUFFERUSAGE_VERTEX_BIT, sizeVert);
		BUFFER_VERTEX_BORDERED = gpuCreateBuffer(device, GpuBufferUsageFlagBits::SDL_GPU_BUFFERUSAGE_VERTEX_BIT, sizeVertBordered);
		BUFFER_VERTEX_HORIZONTAL = gpuCreateBuffer(device, GpuBufferUsageFlagBits::SDL_GPU_BUFFERUSAGE_VERTEX_BIT, sizeVertHorizontal);
		BUFFER_VERTEX_VERTICAL = gpuCreateBuffer(device, GpuBufferUsageFlagBits::SDL_GPU_BUFFERUSAGE_VERTEX_BIT, sizeVertVertical);
		BUFFER_INDEX = gpuCreateBuffer(device, GpuBufferUsageFlagBits::SDL_GPU_BUFFERUSAGE_INDEX_BIT, sizeIndices);

		GpuTransferBuffer* bufferTransferBuffer = gpuCreateTransferBuffer(
			device,
			GpuTransferBufferUsage::SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			(sizeVert + sizeVertBordered + sizeVertHorizontal + sizeVertVertical + sizeIndices)
		);
		void* transferData;
		gpuMapTransferBuffer(
			device,
			bufferTransferBuffer,
			false,
			&transferData
		);

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

		gpuUnmapTransferBuffer(device, bufferTransferBuffer);

		GpuCommandBuffer* uploadCmdBuf = gpuAcquireCommandBuffer(device);
		GpuCopyPass* copyPass = gpuBeginCopyPass(uploadCmdBuf);

		GpuTransferBufferLocation t1 = { bufferTransferBuffer , 0 };
		GpuBufferRegion r1 = { BUFFER_VERTEX, 0, sizeVert };
		gpuUploadToBuffer(copyPass, &t1, &r1, false);

		GpuTransferBufferLocation t2 = { bufferTransferBuffer , sizeVert };
		GpuBufferRegion r2 = { BUFFER_VERTEX_BORDERED, 0, sizeVertBordered };
		gpuUploadToBuffer(copyPass, &t2, &r2, false);

		GpuTransferBufferLocation t3 = { bufferTransferBuffer ,sizeVert + sizeVertBordered };
		GpuBufferRegion r3 = { BUFFER_VERTEX_HORIZONTAL, 0, sizeVertHorizontal };
		gpuUploadToBuffer(copyPass, &t3, &r3, false);

		GpuTransferBufferLocation t4 = { bufferTransferBuffer , sizeVert + sizeVertBordered + sizeVertHorizontal };
		GpuBufferRegion r4 = { BUFFER_VERTEX_VERTICAL, 0, sizeVertVertical };
		gpuUploadToBuffer(copyPass, &t4, &r4, false);

		GpuTransferBufferLocation t5 = { bufferTransferBuffer , sizeVert + sizeVertBordered + sizeVertHorizontal + sizeVertVertical };
		GpuBufferRegion r5 = { BUFFER_INDEX, 0, sizeIndices };
		gpuUploadToBuffer(copyPass, &t5, &r5, false);

		gpuEndCopyPass(copyPass);
		gpuSubmit(uploadCmdBuf);
		gpuReleaseTransferBuffer(device, bufferTransferBuffer);

		// Initialize samplers
		GpuSamplerCreateInfo samplerInfo = {
			.minFilter = GpuFilter::SDL_GPU_FILTER_LINEAR,
			.magFilter = GpuFilter::SDL_GPU_FILTER_LINEAR,
			.mipmapMode = GpuSamplerMipmapMode::SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
			.addressModeU = GpuSamplerAddressMode::SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
			.addressModeV = GpuSamplerAddressMode::SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
			.addressModeW = GpuSamplerAddressMode::SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
		};
		SAMPLER = gpuCreateSampler(device, &samplerInfo);

		// Set up pipelines

		GpuShader* shaderFragment = loadShader(SHADER_NORMAL_FRAG, SDL_GPU_SHADERSTAGE_FRAGMENT);
		GpuShader* shaderVertex = loadShader(SHADER_NORMAL_VERT, SDL_GPU_SHADERSTAGE_VERTEX);
		RENDER_STANDARD = createPipeline(shaderVertex, shaderFragment);
		RENDER_FILL = createShapePipeline(shaderVertex, shaderFragment);
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
	GpuGraphicsPipeline* createPipeline(GpuShader* vertexShader, GpuShader* fragmentShader, GpuTextureFormat textureFormat, GpuBlendFactor srcColor, GpuBlendFactor dstColor, GpuBlendFactor srcAlpha, GpuBlendFactor dstAlpha)
	{
		GpuVertexBinding vertexBindings[] = { {
					.binding = 0,
					.stride = sizeof(TexPos),
					.inputRate = GpuVertexInputRate::SDL_GPU_VERTEXINPUTRATE_VERTEX,
					.stepRate = 0
		} };
		GpuVertexAttribute vertexAttributes[] = { {
					.location = 0,
					.binding = 0,
					.format = GpuVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_VECTOR3,
					.offset = 0
				}, {
					.location = 1,
					.binding = 0,
					.format = GpuVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_VECTOR2,
					.offset = sizeof(float) * 3
				} };
		GpuColorAttachmentDescription colorAttachmentDescriptions[] = { {
					.format = textureFormat,
					.blendState = {
						.blendEnable = true,
						.srcColorBlendFactor = srcColor,
						.dstColorBlendFactor = dstColor,
						.colorBlendOp = GpuBlendOp::SDL_GPU_BLENDOP_ADD,
						.srcAlphaBlendFactor = srcAlpha,
						.dstAlphaBlendFactor = dstAlpha,
						.alphaBlendOp = GpuBlendOp::SDL_GPU_BLENDOP_ADD,
						.colorWriteMask = 0xF
					}
				} };
		GpuGraphicsPipelineCreateInfo pipelineCreateInfo = {
			.vertexShader = vertexShader,
			.fragmentShader = fragmentShader,
			.vertexInputState = {
				.vertexBindings = vertexBindings,
				.vertexBindingCount = 1,
				.vertexAttributes = vertexAttributes,
				.vertexAttributeCount = 2,
			},
			.primitiveType = GpuPrimitiveType::SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
			.rasterizerState = {},
			.multisampleState = {
				.sampleMask = 0xFFFF
			},
			.depthStencilState = {},
			.attachmentInfo = {
				.colorAttachmentDescriptions = colorAttachmentDescriptions,
				.colorAttachmentCount = 1
			},
			.blendConstants = {0.0f, 0.0f, 0.0f, 0.0f}
		};

		return gpuCreateGraphicsPipeline(device, &pipelineCreateInfo);
	}

	GpuGraphicsPipeline* createShapePipeline(GpuShader* vertexShader, GpuShader* fragmentShader, GpuTextureFormat textureFormat, GpuBlendFactor srcColor, GpuBlendFactor dstColor, GpuBlendFactor srcAlpha, GpuBlendFactor dstAlpha)
	{
		GpuColorAttachmentDescription colorAttachmentDescriptions[] = { {
					.format = textureFormat,
					.blendState = {
						.blendEnable = true,
						.srcColorBlendFactor = srcColor,
						.dstColorBlendFactor = dstColor,
						.colorBlendOp = GpuBlendOp::SDL_GPU_BLENDOP_ADD,
						.srcAlphaBlendFactor = srcAlpha,
						.dstAlphaBlendFactor = dstAlpha,
						.alphaBlendOp = GpuBlendOp::SDL_GPU_BLENDOP_ADD,
						.colorWriteMask = 0xF
					}
				} };
		GpuGraphicsPipelineCreateInfo pipelineCreateInfo = {
			.vertexShader = nullptr,
			.fragmentShader = nullptr,
			.vertexInputState = {
			},
			.primitiveType = GpuPrimitiveType::SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
			.rasterizerState = {
				.fillMode = SDL_GpuFillMode::SDL_GPU_FILLMODE_FILL
			},
			.multisampleState = {
				.sampleMask = 0xFFFF
			},
			.depthStencilState = {},
			.attachmentInfo = {
				.colorAttachmentDescriptions = colorAttachmentDescriptions,
				.colorAttachmentCount = 1
			},
			.blendConstants = {0.0f, 0.0f, 0.0f, 0.0f}
		};

		return gpuCreateGraphicsPipeline(device, &pipelineCreateInfo);
	}

	// TODO more pipelines
	GpuGraphicsPipeline* pipelineForMode(RenderMode mode)
	{
		return RENDER_STANDARD;
	}

	GpuGraphicsPipeline* shapePipelineForMode(RenderMode mode)
	{
		return RENDER_FILL;
	}

	// Generates a shader to be used for this window
	GpuShader* loadShader(const char* shaderFilename, GpuShaderStage stage, Uint32 samplerCount, Uint32 uniformBufferCount, Uint32 storageBufferCount, Uint32 storageTextureCount)
	{
		size_t codeSize;
		void* code = fileLoad(shaderFilename, &codeSize);
		if (code == nullptr)
		{
			logError("Failed to load shader from disk: %s", shaderFilename);
			return nullptr;
		}

		GpuShader* shader;
		GpuShaderCreateInfo shaderInfo = {
			.codeSize = codeSize,
			.code = static_cast<const Uint8*>(code),
			.entryPointName = "main",
			.format = GpuShaderFormat::SDL_GPU_SHADERFORMAT_SPIRV,
			.stage = stage,
			.samplerCount = samplerCount,
			.storageTextureCount = storageTextureCount,
			.storageBufferCount = storageBufferCount,
			.uniformBufferCount = uniformBufferCount,
		};
		if (gpuGetDriver(device) == GpuDriver::SDL_GPU_DRIVER_VULKAN)
		{
			shader = gpuCreateShader(device, &shaderInfo);
		}
		else
		{
			shader = gpuCompileSpirvShader(device, &shaderInfo);
		}
		free(code);
		return shader;
	}

	GpuTexture* uploadTexture(GpuCopyPass* copyPass, Surface* surface)
	{
		GpuTransferBuffer* textureTransferBuffer = runner::deviceCreateTransferBuffer(
			GpuTransferBufferUsage::SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			surface->w * surface->h * 4
		);
		GpuTexture* tex = uploadTexture(copyPass, surface, textureTransferBuffer);
		runner::deviceReleaseTransferBuffer(textureTransferBuffer);
		return tex;
	}

	GpuTexture* uploadTexture(GpuCopyPass* copyPass, Surface* surface, GpuTransferBuffer* textureTransferBuffer)
	{
		Uint32 w = surface->w;
		Uint32 h = surface->h;
		const Uint32 imageSizeInBytes = w * h * 4;

		Uint8* textureTransferPtr;
		runner::deviceMapTransferBuffer(textureTransferBuffer, false, (void**)&textureTransferPtr);
		std::memcpy(textureTransferPtr, surface->pixels, imageSizeInBytes);
		runner::deviceUnmapTransferBuffer(textureTransferBuffer);

		GpuTextureCreateInfo info = {
				.width = w,
				.height = h,
				.depth = 1,
				.isCube = false,
				.layerCount = 1,
				.levelCount = 1,
				.sampleCount = GpuSampleCount::SDL_GPU_SAMPLECOUNT_1,
				.format = GpuTextureFormat::SDL_GPU_TEXTUREFORMAT_R8G8B8A8,
				.usageFlags = GpuTextureUsageFlagBits::SDL_GPU_TEXTUREUSAGE_SAMPLER_BIT
		};
		GpuTexture* texture = runner::deviceCreateTexture(&info);

		GpuTextureTransferInfo tInfo = {
			.transferBuffer = textureTransferBuffer,
			.offset = 0,
		};
		GpuTextureRegion tRegion = {
			.textureSlice = {texture},
				.w = w,
				.h = h,
				.d = 1
		};

		gpuUploadToTexture(copyPass, &tInfo, &tRegion, false);
		return texture;
	}

	GpuTexture* uploadTextureForArray(GpuCopyPass* copyPass, Surface* surface, GpuTexture* texture, GpuTransferBuffer* textureTransferBuffer, Uint32 layer)
	{
		Uint32 w = surface->w;
		Uint32 h = surface->h;
		const Uint32 imageSizeInBytes = w * h * 4;

		Uint8* textureTransferPtr;
		runner::deviceMapTransferBuffer(textureTransferBuffer, false, (void**)&textureTransferPtr);
		std::memcpy(textureTransferPtr, surface->pixels, imageSizeInBytes);
		runner::deviceUnmapTransferBuffer(textureTransferBuffer);

		GpuTextureTransferInfo tInfo = {
			.transferBuffer = textureTransferBuffer,
			.offset = imageSizeInBytes * layer,
		};
		GpuTextureRegion tRegion = {
			.textureSlice = {texture, layer},
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

		SDL_GpuDestroyDevice(device);
		device = nullptr;
		TTF_Quit();
		IMG_Quit();
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		enabledInternal = false;
	}
}