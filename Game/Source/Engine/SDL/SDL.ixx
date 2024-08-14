module;

#define SDL_GPU_SPIRVCROSS_IMPLEMENTATION
#include "SDL_gpu_spirvcross/SDL_gpu_spirvcross.h"
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <cstring>

export module sdl;

import sdl.IKeyInputListener;
import std;

namespace sdl {
	export using BlendMode = ::SDL_BlendMode;
	export using Color = ::SDL_GpuColor;
	export using FlipMode = ::SDL_FlipMode;
	export using Font = ::TTF_Font;
	export using GamepadButton = ::SDL_GamepadButton;
	export using GpuColorAttachmentInfo = ::SDL_GpuColorAttachmentInfo;
	export using GpuCommandBuffer = ::SDL_GpuCommandBuffer;
	export using GpuCopyPass = ::SDL_GpuCopyPass;
	export using GpuGraphicsPipeline = ::SDL_GpuGraphicsPipeline;
	export using GpuLoadOp = ::SDL_GpuLoadOp;
	export using GpuRenderPass = ::SDL_GpuRenderPass;
	export using GpuShader = ::SDL_GpuShader;
	export using GpuStoreOp = ::SDL_GpuStoreOp;
	export using GpuTexture = ::SDL_GpuTexture;
	export using GpuTextureCreateInfo = ::SDL_GpuTextureCreateInfo;
	export using GpuTextureFormat = ::SDL_GpuTextureFormat;
	export using GpuTextureRegion = ::SDL_GpuTextureRegion;
	export using GpuTextureTransferInfo = ::SDL_GpuTextureTransferInfo;
	export using GpuTextureUsageFlagBits = ::SDL_GpuTextureUsageFlagBits;
	export using GpuTransferBuffer = ::SDL_GpuTransferBuffer;
	export using GpuTransferBufferUsage = ::SDL_GpuTransferBufferUsage;
	export using Keycode = ::SDL_Keycode;
	export using Music = ::Mix_Music;
	export using PixelFormat = ::SDL_PixelFormat;
	export using Point = ::SDL_FPoint;
	export using PointI = ::SDL_Point;
	export using RectF = ::SDL_FRect;
	export using RectI = ::SDL_Rect;
	export using ScaleMode = ::SDL_ScaleMode;
	export using Scancode = ::SDL_Scancode;
	export using Sound = ::Mix_Chunk;
	export using Surface = ::SDL_Surface;

	export struct FontRender : RectF {
		sdl::GpuTexture* texture;
	};

	export struct Matrix4x4
	{
		float m11, m12, m13, m14;
		float m21, m22, m23, m24;
		float m31, m32, m33, m34;
		float m41, m42, m43, m44;
	};
	export struct TexPos {
		float x, y, z;
		float u, v;
	};

	constexpr auto SHADER_NORMAL_FRAG = "Shader/Compiled/Normal.frag.spv";
	constexpr auto SHADER_NORMAL_VERT = "Shader/Compiled/Normal.vert.spv";
	constexpr std::initializer_list<TexPos> VERTICES = {
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.0f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f }   // Top Left
	};
	constexpr std::initializer_list<TexPos> VERTICES_BORDERED = {
		// Top Left
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 0.5f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f },   // Top Left

		// Top Center
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 0.5f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 0.5f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Left

		// Top Right
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 0.5f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 0.5f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.0f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Left

		// Left
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 0.5f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.5f },   // Top Left

		// Center
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 0.5f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 0.5f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Left

		// Right
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 0.5f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 0.5f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.5f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Left

		// Bottom Left
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 1.0f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.5f },   // Top Left

		// Bottom Center
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 1.0f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 1.0f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Left

		// Bottom Right
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 1.0f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.5f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.5f },   // Top Left
	};
	constexpr std::initializer_list<TexPos> VERTICES_HORIZONTAL = {
		// Left
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 1.0f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f },   // Top Left

		// Center
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 1.0f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 0.5f, 1.0f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Left

		// Right
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.5f, 1.0f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.0f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.5f, 0.0f },   // Top Left
	};
	constexpr std::initializer_list<TexPos> VERTICES_VERTICAL = {
		// Top
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 0.5f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.0f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f },   // Top Left

		// Center
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 0.5f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 0.5f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.5f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.5f },   // Top Left

		// Bottom
		sdl::TexPos{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },  // Bottom Left
		sdl::TexPos{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },   // Bottom Right
		sdl::TexPos{ 0.5f,  0.5f, 0.0f, 1.0f, 0.5f },   // Top Right
		sdl::TexPos{ -0.5f,  0.5f, 0.0f, 0.0f, 0.5f },   // Top Left
	};
	constexpr std::initializer_list<uint16_t> INDICES = { 0, 1, 2, 0, 2, 3 };

	bool enabled;
	const Uint8* key;
	const Uint8* pad;
	int mouse = -1;
	int mouseLast = -1;
	int mousePosX = 0;
	int mousePosY = 0;
	int mouseWheelX = 0;
	int mouseWheelY = 0;
	int numKeys;
	int numPads;
	int winH;
	int winW;
	IKeyInputListener* kListener = nullptr;
	Matrix4x4 matrixUniform = {
			1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
	};
	SDL_Event e;
	SDL_Gamepad* gamepad;
	SDL_GpuBuffer* bufferIndex;
	SDL_GpuBuffer* bufferVertex;
	SDL_GpuBuffer* bufferVertexBordered;
	SDL_GpuBuffer* bufferVertexHorizontal;
	SDL_GpuBuffer* bufferVertexVertical;
	SDL_GpuBuffer* lastBufferIndex;
	SDL_GpuBuffer* lastBufferVertex;
	SDL_GpuDevice* device;
	SDL_GpuGraphicsPipeline* lastPipeline;
	SDL_GpuSampler* sampler;
	SDL_GpuTexture* lastTexture;
	SDL_Window* window;
	Uint64 delta;
	Uint64 fpsLimit;
	Uint64 timeCurrent;
	Uint64 timeLast;
	Uint8* keyJust;
	Uint8* padLast;

	/* Rendering pipelines */
	export SDL_GpuGraphicsPipeline* RENDER_STANDARD;


	/* Color constants. RGB can be higher than 1 to make the image brighter */
	export constexpr Color COLOR_BLACK = { 0, 0, 0, 1 };
	export constexpr Color COLOR_BLACK_SHADOW = { 0, 0, 0, 0.4f };
	export constexpr Color COLOR_GOLD = { 0.13373f, 0.11843, 0.5176, 1 };
	export constexpr Color COLOR_GRAY = { 0.5f, 0.5f, 0.5f, 1 };
	export constexpr Color COLOR_LIME = { 0.6f, 2, 0.84f, 1 };
	export constexpr Color COLOR_SKY = { 0.6f, 1.1, 1.5f, 1 };
	export constexpr Color COLOR_STANDARD = { 1, 1, 1, 1 };
	export constexpr Color COLOR_WHITE = { 2, 2, 2, 1 };

	/* Scan constants (used for hotkeys) */
	export constexpr Scancode SCAN_BACKSPACE = SDL_SCANCODE_BACKSPACE;
	export constexpr Scancode SCAN_DOWN = SDL_SCANCODE_DOWN;
	export constexpr Scancode SCAN_ENTER = SDL_SCANCODE_KP_ENTER;
	export constexpr Scancode SCAN_ESC = SDL_SCANCODE_ESCAPE;
	export constexpr Scancode SCAN_LEFT = SDL_SCANCODE_LEFT;
	export constexpr Scancode SCAN_RETURN = SDL_SCANCODE_RETURN;
	export constexpr Scancode SCAN_RIGHT = SDL_SCANCODE_RIGHT;
	export constexpr Scancode SCAN_UP = SDL_SCANCODE_UP;

	/* Key constants (used for input listeners) */
	export constexpr Sint32 KEY_BACKSPACE = SDLK_BACKSPACE;
	export constexpr Sint32 KEY_DOWN = SDLK_DOWN;
	export constexpr Sint32 KEY_ENTER = SDLK_KP_ENTER;
	export constexpr Sint32 KEY_ESC = SDLK_ESCAPE;
	export constexpr Sint32 KEY_LEFT = SDLK_LEFT;
	export constexpr Sint32 KEY_RETURN = SDLK_RETURN;
	export constexpr Sint32 KEY_RIGHT = SDLK_RIGHT;
	export constexpr Sint32 KEY_UP = SDLK_UP;

	/* Other constants */
	export constexpr int CONST_FALSE = SDL_FALSE;
	export constexpr int CONST_TRUE = SDL_TRUE;
	export constexpr Uint64 NANOS_PER_SECOND = 1000000000ULL;

	/* Directory stuff */
	export const char* dirBase() noexcept { return SDL_GetBasePath(); }
	export char* dirPref(const char* org, const char* app) { return SDL_GetPrefPath(org, app); }
	export void dirSelect() {
		//return SDL_ShowOpenFolderDialog();
	}

	/* Font management functions */
	export int fontAscent(TTF_Font* font) { return TTF_FontAscent(font); }
	export void fontClose(TTF_Font* font) { TTF_CloseFont(font); }
	export int fontDescent(TTF_Font* font) { return TTF_FontDescent(font); }
	export int fontFaceIsFixedWidth(TTF_Font* font) { return TTF_FontFaceIsFixedWidth(font); }
	export long fontFaces(TTF_Font* font) { return TTF_FontFaces(font); }
	export int fontGlyphIsProvided(TTF_Font* font, Uint16 ch) { return TTF_GlyphIsProvided(font, ch); }
	export int fontGlyphMetrics(TTF_Font* font, Uint16 ch, int* minx, int* maxx, int* miny, int* maxy, int* advance) { return TTF_GlyphMetrics(font, ch, minx, maxx, miny, maxy, advance); }
	export int fontHeight(TTF_Font* font) { return TTF_FontHeight(font); }
	export int fontHintingGet(TTF_Font* font) { return TTF_GetFontHinting(font); }
	export void fontHintingSet(TTF_Font* font, int hinting) { TTF_SetFontHinting(font, hinting); }
	export int fontKerningGet(TTF_Font* font) { return TTF_GetFontKerning(font); }
	export void fontKerningSet(TTF_Font* font, int allowed) { TTF_SetFontKerning(font, allowed); }
	export int fontLineSkip(TTF_Font* font) { return TTF_FontLineSkip(font); }
	export TTF_Font* fontOpen(const char* file, int ptsize) { return TTF_OpenFont(file, ptsize); }
	export TTF_Font* fontOpenIndex(const char* file, int ptsize, long index) { return TTF_OpenFontIndex(file, ptsize, index); }
	export TTF_Font* fontOpenIndexIO(SDL_IOStream* src, int closeio, int ptsize, long index) { return TTF_OpenFontIndexIO(src, closeio, ptsize, index); }
	export TTF_Font* fontOpenIO(SDL_IOStream* src, int closeio, int ptsize) { return TTF_OpenFontIO(src, closeio, ptsize); }
	export int fontOutlineGet(TTF_Font* font) { return TTF_GetFontOutline(font); }
	export void fontOutlineSet(TTF_Font* font, int outline) { TTF_SetFontOutline(font, outline); }
	export int fontSizeText(TTF_Font* font, const char* text, int* w, int* h) { return TTF_SizeText(font, text, w, h); }
	export int fontSizeUNICODE(TTF_Font* font, const Uint16* text, int* w, int* h) { return TTF_SizeUNICODE(font, text, w, h); }
	export int fontSizeUTF8(TTF_Font* font, const char* text, int* w, int* h) { return TTF_SizeUTF8(font, text, w, h); }
	export int fontStyleIsSet(TTF_Font* font, int style) { return TTF_GetFontStyle(font) & style; }
	export void fontStyleSet(TTF_Font* font, int style) { TTF_SetFontStyle(font, style); }

	/* Gamepad functions */
	export bool gamepadHasJustPressed(int pressed) { return pad[pressed] && !padLast[pressed]; }

	/* GPU functions */
	export SDL_bool gpuIsTextureFormatSupported(SDL_GpuTextureFormat format, SDL_GpuTextureType type, SDL_GpuTextureUsageFlags usage) { return SDL_GpuIsTextureFormatSupported(device, format, type, usage); }
	export SDL_bool gpuQueryFence(SDL_GpuFence* fence) { return SDL_GpuQueryFence(device, fence); }
	export SDL_bool gpuSetSwapchainParameters(SDL_GpuSwapchainComposition swapchainComposition, SDL_GpuPresentMode presentMode) { return SDL_GpuSetSwapchainParameters(device, window, swapchainComposition, presentMode); }
	export SDL_bool gpuSupportsPresentMode(SDL_GpuPresentMode presentMode) { return SDL_GpuSupportsPresentMode(device, window, presentMode); }
	export SDL_bool gpuSupportsSwapchainComposition(SDL_GpuSwapchainComposition swapchainComposition) { return SDL_GpuSupportsSwapchainComposition(device, window, swapchainComposition); }
	export SDL_GpuBackend gpuGetBackend() { return SDL_GpuGetBackend(device); }
	export SDL_GpuBuffer* gpuCreateBuffer(SDL_GpuBufferUsageFlags usageFlags, Uint32 sizeInBytes) { return SDL_GpuCreateBuffer(device, usageFlags, sizeInBytes); }
	export SDL_GpuCommandBuffer* gpuAcquireCommandBuffer() { return SDL_GpuAcquireCommandBuffer(device); }
	export SDL_GpuComputePass* gpuBeginComputePass(SDL_GpuCommandBuffer* commandBuffer, SDL_GpuStorageTextureReadWriteBinding* storageTextureBindings, Uint32 storageTextureBindingCount, SDL_GpuStorageBufferReadWriteBinding* storageBufferBindings, Uint32 storageBufferBindingCount) { return SDL_GpuBeginComputePass(commandBuffer, storageTextureBindings, storageTextureBindingCount, storageBufferBindings, storageBufferBindingCount); }
	export SDL_GpuComputePipeline* gpuCreateComputePipeline(SDL_GpuComputePipelineCreateInfo* computePipelineCreateInfo) { return SDL_GpuCreateComputePipeline(device, computePipelineCreateInfo); }
	export SDL_GpuCopyPass* gpuBeginCopyPass(SDL_GpuCommandBuffer* commandBuffer) { return SDL_GpuBeginCopyPass(commandBuffer); }
	export SDL_GpuDevice* gpuCreateDevice(SDL_GpuBackend preferredBackends, SDL_bool debugMode, SDL_bool preferLowPower) { return SDL_GpuCreateDevice(preferredBackends, debugMode, preferLowPower); }
	export SDL_GpuFence* gpuSubmitAndAcquireFence(SDL_GpuCommandBuffer* commandBuffer) { return SDL_GpuSubmitAndAcquireFence(commandBuffer); }
	export SDL_GpuGraphicsPipeline* gpuCreateGraphicsPipeline(SDL_GpuGraphicsPipelineCreateInfo* pipelineCreateInfo) { return SDL_GpuCreateGraphicsPipeline(device, pipelineCreateInfo); }
	export SDL_GpuGraphicsPipeline* gpuCreateGraphicsPipelineForShader(SDL_GpuShader* vertexShader, SDL_GpuShader* fragmentShader, SDL_GpuBlendFactor srcColor = SDL_GPU_BLENDFACTOR_SRC_ALPHA, SDL_GpuBlendFactor dstColor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, SDL_GpuBlendFactor srcAlpha = SDL_GPU_BLENDFACTOR_ONE, SDL_GpuBlendFactor dstAlpha = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA) {
		SDL_GpuVertexBinding vertexBindings[] = { {
					.binding = 0,
					.stride = sizeof(TexPos),
					.inputRate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
					.stepRate = 0
		} };
		SDL_GpuVertexAttribute vertexAttributes[] = { {
					.location = 0,
					.binding = 0,
					.format = SDL_GPU_VERTEXELEMENTFORMAT_VECTOR3,
					.offset = 0
				}, {
					.location = 1,
					.binding = 0,
					.format = SDL_GPU_VERTEXELEMENTFORMAT_VECTOR2,
					.offset = sizeof(float) * 3
				} };
		SDL_GpuColorAttachmentDescription colorAttachmentDescriptions[] = { {
					.format = SDL_GpuGetSwapchainTextureFormat(device, window),
					.blendState = {
						.blendEnable = SDL_TRUE,
						.srcColorBlendFactor = srcColor,
						.dstColorBlendFactor = dstColor,
						.colorBlendOp = SDL_GPU_BLENDOP_ADD,
						.srcAlphaBlendFactor = srcAlpha,
						.dstAlphaBlendFactor = dstAlpha,
						.alphaBlendOp = SDL_GPU_BLENDOP_ADD,
						.colorWriteMask = 0xF
					}
				} };

		SDL_GpuGraphicsPipelineCreateInfo pipelineCreateInfo = {
			.vertexShader = vertexShader,
			.fragmentShader = fragmentShader,
			.vertexInputState = {
				.vertexBindings = vertexBindings,
				.vertexBindingCount = 1,
				.vertexAttributes = vertexAttributes,
				.vertexAttributeCount = 2,
			},
			.primitiveType = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
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

		return SDL_GpuCreateGraphicsPipeline(device, &pipelineCreateInfo);
	}
	export SDL_GpuRenderPass* gpuBeginRenderPass(SDL_GpuCommandBuffer* commandBuffer, SDL_GpuColorAttachmentInfo* colorAttachmentInfos, Uint32 colorAttachmentCount, SDL_GpuDepthStencilAttachmentInfo* depthStencilAttachmentInfo) { return SDL_GpuBeginRenderPass(commandBuffer, colorAttachmentInfos, colorAttachmentCount, depthStencilAttachmentInfo); }
	export SDL_GpuSampleCount gpuGetBestSampleCount(SDL_GpuTextureFormat format, SDL_GpuSampleCount desiredSampleCount) { return SDL_GpuGetBestSampleCount(device, format, desiredSampleCount); }
	export SDL_GpuSampler* gpuCreateSampler(SDL_GpuSamplerCreateInfo* samplerCreateInfo) { return SDL_GpuCreateSampler(device, samplerCreateInfo); }
	export SDL_GpuShader* gpuCreateShader(SDL_GpuShaderCreateInfo* shaderCreateInfo) { return SDL_GpuCreateShader(device, shaderCreateInfo); }
	export SDL_GpuShader* gpuLoadCompiledShader(
		const char* shaderFilename,
		SDL_GpuShaderStage stage,
		Uint32 samplerCount = 1,
		Uint32 uniformBufferCount = 1,
		Uint32 storageBufferCount = 0,
		Uint32 storageTextureCount = 0) {

		size_t codeSize;
		void* code = SDL_LoadFile(shaderFilename, &codeSize);
		if (code == nullptr)
		{
			SDL_Log("Failed to load shader from disk: %s", shaderFilename);
			return nullptr;
		}

		SDL_GpuShader* shader;
		SDL_GpuShaderCreateInfo shaderInfo = {
			.codeSize = codeSize,
			.code = static_cast<const Uint8*>(code),
			.entryPointName = "main",
			.format = SDL_GPU_SHADERFORMAT_SPIRV,
			.stage = stage,
			.samplerCount = samplerCount,
			.storageTextureCount = storageTextureCount,
			.storageBufferCount = storageBufferCount,
			.uniformBufferCount = uniformBufferCount,
		};
		if (SDL_GpuGetBackend(device) == SDL_GPU_BACKEND_VULKAN)
		{
			shader = SDL_GpuCreateShader(device, &shaderInfo);
		}
		else
		{
			shader = static_cast<SDL_GpuShader*>(SDL_CompileFromSPIRV(device, &shaderInfo, SDL_FALSE)); // TODO alter implemention for type safety
		}
		SDL_free(code);
		return shader;
	}
	export SDL_GpuShader* gpuLoadCompiledShaderFragment(const char* shaderFilename, Uint32 uniformBufferCount = 1) { return gpuLoadCompiledShader(shaderFilename, SDL_GPU_SHADERSTAGE_FRAGMENT, 1, uniformBufferCount); }
	export SDL_GpuShader* gpuLoadCompiledShaderVertex(const char* shaderFilename, Uint32 uniformBufferCount = 1) { return gpuLoadCompiledShader(shaderFilename, SDL_GPU_SHADERSTAGE_VERTEX, 0, uniformBufferCount); }
	export SDL_GpuTexture* gpuAcquireSwapchainTexture(SDL_GpuCommandBuffer* commandBuffer, Uint32* pWidth, Uint32* pHeight) { return SDL_GpuAcquireSwapchainTexture(commandBuffer, window, pWidth, pHeight); }
	export SDL_GpuTexture* gpuCreateTexture(SDL_GpuTextureCreateInfo* textureCreateInfo) { return SDL_GpuCreateTexture(device, textureCreateInfo); }
	export SDL_GpuTextureFormat gpuGetSwapchainTextureFormat() { return SDL_GpuGetSwapchainTextureFormat(device, window); }
	export SDL_GpuTransferBuffer* gpuCreateTransferBuffer(SDL_GpuTransferBufferUsage usage, Uint32 sizeInBytes) { return SDL_GpuCreateTransferBuffer(device, usage, sizeInBytes); }
	export Uint32 gpuTextureFormatTexelBlockSize(SDL_GpuTextureFormat textureFormat) { return SDL_GpuTextureFormatTexelBlockSize(textureFormat); }
	export void gpuBindComputePipeline(SDL_GpuComputePass* computePass, SDL_GpuComputePipeline* computePipeline) { SDL_GpuBindComputePipeline(computePass, computePipeline); }
	export void gpuBindComputeStorageBuffers(SDL_GpuComputePass* computePass, Uint32 firstSlot, SDL_GpuBuffer** storageBuffers, Uint32 bindingCount) { SDL_GpuBindComputeStorageBuffers(computePass, firstSlot, storageBuffers, bindingCount); }
	export void gpuBindComputeStorageTextures(SDL_GpuComputePass* computePass, Uint32 firstSlot, SDL_GpuTextureSlice* storageTextureSlices, Uint32 bindingCount) { SDL_GpuBindComputeStorageTextures(computePass, firstSlot, storageTextureSlices, bindingCount); }
	export void gpuBindFragmentSamplers(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuTextureSamplerBinding* textureSamplerBindings, Uint32 bindingCount) { SDL_GpuBindFragmentSamplers(renderPass, firstSlot, textureSamplerBindings, bindingCount); }
	export void gpuBindFragmentStorageBuffers(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuBuffer** storageBuffers, Uint32 bindingCount) { SDL_GpuBindFragmentStorageBuffers(renderPass, firstSlot, storageBuffers, bindingCount); }
	export void gpuBindFragmentStorageTextures(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuTextureSlice* storageTextureSlices, Uint32 bindingCount) { SDL_GpuBindFragmentStorageTextures(renderPass, firstSlot, storageTextureSlices, bindingCount); }
	export void gpuBindGraphicsPipeline(SDL_GpuRenderPass* renderPass, SDL_GpuGraphicsPipeline* graphicsPipeline) { SDL_GpuBindGraphicsPipeline(renderPass, graphicsPipeline); }
	export void gpuBindIndexBuffer(SDL_GpuRenderPass* renderPass, SDL_GpuBufferBinding* pBinding, SDL_GpuIndexElementSize indexElementSize) { SDL_GpuBindIndexBuffer(renderPass, pBinding, indexElementSize); }
	export void gpuBindVertexBuffers(SDL_GpuRenderPass* renderPass, Uint32 firstBinding, SDL_GpuBufferBinding* pBindings, Uint32 bindingCount) { SDL_GpuBindVertexBuffers(renderPass, firstBinding, pBindings, bindingCount); }
	export void gpuBindVertexSamplers(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuTextureSamplerBinding* textureSamplerBindings, Uint32 bindingCount) { SDL_GpuBindVertexSamplers(renderPass, firstSlot, textureSamplerBindings, bindingCount); }
	export void gpuBindVertexStorageBuffers(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuBuffer** storageBuffers, Uint32 bindingCount) { SDL_GpuBindVertexStorageBuffers(renderPass, firstSlot, storageBuffers, bindingCount); }
	export void gpuBindVertexStorageTextures(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuTextureSlice* storageTextureSlices, Uint32 bindingCount) { SDL_GpuBindVertexStorageTextures(renderPass, firstSlot, storageTextureSlices, bindingCount); }
	export void gpuBlit(SDL_GpuCommandBuffer* commandBuffer, SDL_GpuTextureRegion* source, SDL_GpuTextureRegion* destination, SDL_GpuFilter filterMode, SDL_bool cycle) { SDL_GpuBlit(commandBuffer, source, destination, filterMode, cycle); }
	export void gpuCopyBufferToBuffer(SDL_GpuCopyPass* copyPass, SDL_GpuBufferLocation* source, SDL_GpuBufferLocation* destination, Uint32 size, SDL_bool cycle) { SDL_GpuCopyBufferToBuffer(copyPass, source, destination, size, cycle); }
	export void gpuCopyTextureToTexture(SDL_GpuCopyPass* copyPass, SDL_GpuTextureLocation* source, SDL_GpuTextureLocation* destination, Uint32 w, Uint32 h, Uint32 d, SDL_bool cycle) { SDL_GpuCopyTextureToTexture(copyPass, source, destination, w, h, d, cycle); }
	export void gpuDispatchCompute(SDL_GpuComputePass* computePass, Uint32 groupCountX, Uint32 groupCountY, Uint32 groupCountZ) { SDL_GpuDispatchCompute(computePass, groupCountX, groupCountY, groupCountZ); }
	export void gpuDispatchComputeIndirect(SDL_GpuComputePass* computePass, SDL_GpuBuffer* buffer, Uint32 offsetInBytes) { SDL_GpuDispatchComputeIndirect(computePass, buffer, offsetInBytes); }
	export void gpuDownloadFromBuffer(SDL_GpuCopyPass* copyPass, SDL_GpuBufferRegion* source, SDL_GpuTransferBufferLocation* destination) { SDL_GpuDownloadFromBuffer(copyPass, source, destination); }
	export void gpuDownloadFromTexture(SDL_GpuCopyPass* copyPass, SDL_GpuTextureRegion* source, SDL_GpuTextureTransferInfo* destination) { SDL_GpuDownloadFromTexture(copyPass, source, destination); }
	export void gpuDrawIndexedPrimitives(SDL_GpuRenderPass* renderPass, Uint32 baseVertex, Uint32 startIndex, Uint32 primitiveCount, Uint32 instanceCount) { SDL_GpuDrawIndexedPrimitives(renderPass, baseVertex, startIndex, primitiveCount, instanceCount); }
	export void gpuDrawIndexedPrimitivesIndirect(SDL_GpuRenderPass* renderPass, SDL_GpuBuffer* buffer, Uint32 offsetInBytes, Uint32 drawCount, Uint32 stride) { SDL_GpuDrawIndexedPrimitivesIndirect(renderPass, buffer, offsetInBytes, drawCount, stride); }
	export void gpuDrawPrimitives(SDL_GpuRenderPass* renderPass, Uint32 vertexStart, Uint32 primitiveCount) { SDL_GpuDrawPrimitives(renderPass, vertexStart, primitiveCount); }
	export void gpuDrawPrimitivesIndirect(SDL_GpuRenderPass* renderPass, SDL_GpuBuffer* buffer, Uint32 offsetInBytes, Uint32 drawCount, Uint32 stride) { SDL_GpuDrawPrimitivesIndirect(renderPass, buffer, offsetInBytes, drawCount, stride); }
	export void gpuEndComputePass(SDL_GpuComputePass* computePass) { SDL_GpuEndComputePass(computePass); }
	export void gpuEndCopyPass(SDL_GpuCopyPass* copyPass) { SDL_GpuEndCopyPass(copyPass); }
	export void gpuEndRenderPass(SDL_GpuRenderPass* renderPass) { SDL_GpuEndRenderPass(renderPass); }
	export void gpuGenerateMipmaps(SDL_GpuCopyPass* copyPass, SDL_GpuTexture* texture) { SDL_GpuGenerateMipmaps(copyPass, texture); }
	export void gpuGetTransferData(SDL_GpuTransferBufferRegion* source, void* destination) { SDL_GpuGetTransferData(device, source, destination); }
	export void gpuInsertDebugLabel(SDL_GpuCommandBuffer* commandBuffer, const char* text) { SDL_GpuInsertDebugLabel(commandBuffer, text); }
	export void gpuMapTransferBuffer(SDL_GpuTransferBuffer* transferBuffer, SDL_bool cycle, void** ppData) { SDL_GpuMapTransferBuffer(device, transferBuffer, cycle, ppData); }
	export void gpuPopDebugGroup(SDL_GpuCommandBuffer* commandBuffer) { SDL_GpuPopDebugGroup(commandBuffer); }
	export void gpuPushComputeUniformData(SDL_GpuCommandBuffer* commandBuffer, Uint32 slotIndex, const void* data, Uint32 dataLengthInBytes) { SDL_GpuPushComputeUniformData(commandBuffer, slotIndex, data, dataLengthInBytes); }
	export void gpuPushDebugGroup(SDL_GpuCommandBuffer* commandBuffer, const char* name) { SDL_GpuPushDebugGroup(commandBuffer, name); }
	export void gpuPushFragmentUniformData(SDL_GpuCommandBuffer* commandBuffer, Uint32 slotIndex, const void* data, Uint32 dataLengthInBytes) { SDL_GpuPushFragmentUniformData(commandBuffer, slotIndex, data, dataLengthInBytes); }
	export void gpuPushVertexUniformData(SDL_GpuCommandBuffer* commandBuffer, Uint32 slotIndex, const void* data, Uint32 dataLengthInBytes) { SDL_GpuPushVertexUniformData(commandBuffer, slotIndex, data, dataLengthInBytes); }
	export void gpuReleaseBuffer(SDL_GpuBuffer* buffer) { SDL_GpuReleaseBuffer(device, buffer); }
	export void gpuReleaseComputePipeline(SDL_GpuComputePipeline* computePipeline) { SDL_GpuReleaseComputePipeline(device, computePipeline); }
	export void gpuReleaseFence(SDL_GpuFence* fence) { SDL_GpuReleaseFence(device, fence); }
	export void gpuReleaseGraphicsPipeline(SDL_GpuGraphicsPipeline* graphicsPipeline) { SDL_GpuReleaseGraphicsPipeline(device, graphicsPipeline); }
	export void gpuReleaseSampler(SDL_GpuSampler* sampler) { SDL_GpuReleaseSampler(device, sampler); }
	export void gpuReleaseShader(SDL_GpuShader* shader) { SDL_GpuReleaseShader(device, shader); }
	export void gpuReleaseTexture(SDL_GpuTexture* texture) { SDL_GpuReleaseTexture(device, texture); }
	export void gpuReleaseTransferBuffer(SDL_GpuTransferBuffer* transferBuffer) { SDL_GpuReleaseTransferBuffer(device, transferBuffer); }
	export void gpuSetBufferName(SDL_GpuBuffer* buffer, const char* text) { SDL_GpuSetBufferName(device, buffer, text); }
	export void gpuSetScissor(SDL_GpuRenderPass* renderPass, SDL_GpuRect* scissor) { SDL_GpuSetScissor(renderPass, scissor); }
	export void gpuSetTextureName(SDL_GpuTexture* texture, const char* text) { SDL_GpuSetTextureName(device, texture, text); }
	export void gpuSetTransferData(const void* source, SDL_GpuTransferBufferRegion* destination, SDL_bool cycle) { SDL_GpuSetTransferData(device, source, destination, cycle); }
	export void gpuSetViewport(SDL_GpuRenderPass* renderPass, SDL_GpuViewport* viewport) { SDL_GpuSetViewport(renderPass, viewport); }
	export void gpuSubmit(SDL_GpuCommandBuffer* commandBuffer) { SDL_GpuSubmit(commandBuffer); }
	export void gpuUnmapTransferBuffer(SDL_GpuTransferBuffer* transferBuffer) { SDL_GpuUnmapTransferBuffer(device, transferBuffer); }
	export void gpuUploadToBuffer(SDL_GpuCopyPass* copyPass, SDL_GpuTransferBufferLocation* source, SDL_GpuBufferRegion* destination, SDL_bool cycle = SDL_FALSE) { SDL_GpuUploadToBuffer(copyPass, source, destination, cycle); }
	export void gpuUploadToTexture(SDL_GpuCopyPass* copyPass, SDL_GpuTextureTransferInfo* source, SDL_GpuTextureRegion* destination, SDL_bool cycle = SDL_FALSE) { SDL_GpuUploadToTexture(copyPass, source, destination, cycle); }
	export void gpuWait() { SDL_GpuWait(device); }
	export void gpuWaitForFences(SDL_bool waitAll, SDL_GpuFence** pFences, Uint32 fenceCount) { SDL_GpuWaitForFences(device, waitAll, pFences, fenceCount); }

	/* Keyboard functions */
	export bool keyboardInputActive() { return kListener != nullptr; }
	export bool keyboardInputActive(IKeyInputListener* listener) { return kListener == listener; }
	export void keyboardInputStart(IKeyInputListener* listener) {
		if (!kListener) {
			kListener = listener;
			SDL_StartTextInput(window);
		}
	}

	export void keyboardInputStop() {
		kListener = nullptr;
		SDL_StopTextInput(window);
	}
	export void keyboardInputStopRequest(IKeyInputListener* listener) {
		if (kListener == listener) {
			kListener = nullptr;
			SDL_StopTextInput(window);
		}
	}
	export bool keyboardJustPressed(int pressed) {
		return key[pressed] && keyJust[pressed] && kListener == nullptr;
	} // Keyboard listeners should block regular keyboard input
	export bool keyboardJustPressedEnter() { return keyboardJustPressed(SDLK_KP_ENTER) || keyboardJustPressed(SDLK_RETURN); }
	export bool keyboardJustPressedEsc() { return keyboardJustPressed(SDLK_ESCAPE); }
	export bool keyboardPressed(int pressed) { return key[pressed] && kListener == nullptr; }

	/* Mouse state functions */
	export int mouseGetWheelX() noexcept { return mouseWheelX; }
	export int mouseGetWheelY() noexcept { return mouseWheelY; }
	export int mouseGetX() noexcept { return mousePosX; }
	export int mouseGetY() noexcept { return mousePosY; }
	export bool mouseIsHovering(const RectF& rect) {
		int mx = sdl::mouseGetX();
		int my = sdl::mouseGetY();
		return mx >= rect.x && my >= rect.y && mx < rect.x + rect.w && my < rect.y + rect.h;
	}
	export bool mouseIsHovering(const RectI rect) {
		int mx = sdl::mouseGetX();
		int my = sdl::mouseGetY();
		return mx >= rect.x && my >= rect.y && mx < rect.x + rect.w && my < rect.y + rect.h;
	}
	export bool mouseIsLeftClicked() noexcept { return mouse == SDL_BUTTON_LEFT; }
	export bool mouseIsLeftJustClicked() noexcept { return mouse == SDL_BUTTON_LEFT && mouseLast != SDL_BUTTON_LEFT; }
	export bool mouseIsLeftJustReleased() noexcept { return mouse != SDL_BUTTON_LEFT && mouseLast == SDL_BUTTON_LEFT; }
	export bool mouseIsLeftReleased() noexcept { return mouse != SDL_BUTTON_LEFT; }
	export bool mouseIsRightClicked() noexcept { return mouse == SDL_BUTTON_RIGHT; }
	export bool mouseIsRightJustClicked() noexcept { return mouse == SDL_BUTTON_RIGHT && mouseLast != SDL_BUTTON_RIGHT; }
	export bool mouseIsRightJustReleased() noexcept { return mouse != SDL_BUTTON_RIGHT && mouseLast == SDL_BUTTON_RIGHT; }
	export bool mouseIsRightReleased() noexcept { return mouse != SDL_BUTTON_RIGHT; }

	/* Music management functions */
	export double musicGetPosition(Mix_Music* music) { return Mix_GetMusicPosition(music); }
	export int musicFadeOut(int ms) { return Mix_FadeOutMusic(ms); }
	export int musicGetVolume() { return Mix_VolumeMusic(-1); }
	export int musicHalt() { return Mix_HaltMusic(); }
	export int musicIsPaused() { return Mix_PausedMusic(); }
	export int musicPlay(Mix_Music* music, int loops = -1) { return Mix_PlayMusic(music, loops); }
	export int musicPlayFade(Mix_Music* music, int fade, int loops = -1) { return Mix_FadeInMusic(music, loops, fade); }
	export int musicSetPosition(double position) { return Mix_SetMusicPosition(position); }
	export Mix_Music* musicLoad(const char* path) { return Mix_LoadMUS(path); }
	export void musicFree(Mix_Music* music) { Mix_FreeMusic(music); }
	export void musicPause() { Mix_PauseMusic(); }
	export void musicResume() { Mix_ResumeMusic(); }
	export void musicRewind() { Mix_RewindMusic(); }
	export void musicSetVolume(int volume) { Mix_VolumeMusic(volume); }

	/* Surface functions */
	export int surfaceBlit(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) { return SDL_BlitSurface(src, srcrect, dst, dstrect); }
	export int surfaceBlitScaled(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect, SDL_ScaleMode mode) { return SDL_BlitSurfaceScaled(src, srcrect, dst, dstrect, mode); }
	export int surfaceFillRect(SDL_Surface* surface, const SDL_Rect* rect, Uint32 color) { return SDL_FillSurfaceRect(surface, rect, color); }
	export int surfaceFillRects(SDL_Surface* surface, const SDL_Rect* rects, int count, Uint32 color) { return SDL_FillSurfaceRects(surface, rects, count, color); }
	export int surfaceGetClipRect(SDL_Surface* surface, SDL_Rect* rect) { return SDL_GetSurfaceClipRect(surface, rect); }
	export int surfaceLock(SDL_Surface* surface) { return SDL_LockSurface(surface); }
	export int surfaceSetAlphaMod(SDL_Surface* surface, Uint8 alpha) { return SDL_SetSurfaceAlphaMod(surface, alpha); }
	export int surfaceSetBlendMode(SDL_Surface* surface, SDL_BlendMode blendMode) { return SDL_SetSurfaceBlendMode(surface, blendMode); }
	export int surfaceSetColorKey(SDL_Surface* surface, Uint32 key) { return SDL_SetSurfaceColorKey(surface, SDL_TRUE, key); }
	export int surfaceSetPalette(SDL_Surface* surface, SDL_Palette* palette) { return SDL_SetSurfacePalette(surface, palette); }
	export SDL_Surface* surfaceConvert(SDL_Surface* surface, SDL_PixelFormat pixel_format) { return SDL_ConvertSurface(surface, pixel_format); }
	export SDL_Surface* surfaceCopy(SDL_Surface* src) { return SDL_DuplicateSurface(src); }
	export SDL_Surface* surfaceCreate(int width, int height, SDL_PixelFormat format) { return SDL_CreateSurface(width, height, format); }
	export SDL_Surface* surfaceCreate(int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateSurface(width, height, SDL_GetPixelFormatForMasks(depth, Rmask, Gmask, Bmask, Amask)); }
	export SDL_Surface* surfaceCreateFrom(void* pixels, int width, int height, int pitch, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateSurfaceFrom(width, height, SDL_GetPixelFormatForMasks(depth, Rmask, Gmask, Bmask, Amask), pixels, pitch); }
	export SDL_Surface* surfaceLoad(const char* file) { return IMG_Load(file); }
	export void surfaceDestroy(SDL_Surface* surface) { SDL_DestroySurface(surface); }
	export void surfaceUnlock(SDL_Surface* surface) { SDL_UnlockSurface(surface); }

	/* Sound management functions */
	export int soundChannelPaused(int channel) { return Mix_Paused(channel); }
	export int soundExpireChannel(int channel, int ticks) { return Mix_ExpireChannel(channel, ticks); }
	export int soundFadeOutChannel(int channel, int ms) { return Mix_FadeOutChannel(channel, ms); }
	export int soundGetChannelVolume(int channel) { return Mix_Volume(channel, -1); }
	export int soundHaltChannel(int channel) { return Mix_HaltChannel(channel); }
	export int soundPlay(Sound* sound, int loops = 0, int time = -1) { return Mix_PlayChannelTimed(-1, sound, loops, time); }
	export int soundPlayFade(Sound* sound, int fade, int loops = 0, int time = -1) { return Mix_FadeInChannelTimed(-1, sound, loops, fade, time); }
	export int soundReserveChannels(int num) { return Mix_ReserveChannels(num); }
	export int soundSetVolume(Sound* sound, int volume) { return Mix_VolumeChunk(sound, volume); }
	export Sound* soundGetChunk(int channel) { return Mix_GetChunk(channel); }
	export Sound* soundLoad(const char* path) { return Mix_LoadWAV(path); }
	export void soundFree(Sound* sound) { Mix_FreeChunk(sound); }
	export void soundPauseChannel(int channel) { Mix_Pause(channel); }
	export void soundResumeChannel(int channel) { Mix_Resume(channel); }
	export void soundSetAllVolume(int volume) {
		for (int i = 0; i < Mix_AllocateChannels(-1); ++i) {
			Mix_Volume(i, volume);
		}
	}

	/* Text rendering functions */
	export SDL_Surface* textRenderBlended(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderText_Blended(font, text, fg); }
	export SDL_Surface* textRenderBlendedWrapped(TTF_Font* font, const char* text, SDL_Color fg, Uint32 wrapLength) { return TTF_RenderText_Blended_Wrapped(font, text, fg, wrapLength); }
	export SDL_Surface* textRenderShaded(TTF_Font* font, const char* text, SDL_Color fg, SDL_Color bg) { return TTF_RenderText_Shaded(font, text, fg, bg); }
	export SDL_Surface* textRenderSolid(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderText_Solid(font, text, fg); }
	export SDL_Surface* textRenderUNICODEBlended(TTF_Font* font, const Uint16* text, SDL_Color fg) { return TTF_RenderUNICODE_Blended(font, text, fg); }
	export SDL_Surface* textRenderUNICODEBlendedWrapped(TTF_Font* font, const Uint16* text, SDL_Color fg, Uint32 wrapLength) { return TTF_RenderUNICODE_Blended_Wrapped(font, text, fg, wrapLength); }
	export SDL_Surface* textRenderUNICODEShaded(TTF_Font* font, const Uint16* text, SDL_Color fg, SDL_Color bg) { return TTF_RenderUNICODE_Shaded(font, text, fg, bg); }
	export SDL_Surface* textRenderUNICODESolid(TTF_Font* font, const Uint16* text, SDL_Color fg) { return TTF_RenderUNICODE_Solid(font, text, fg); }
	export SDL_Surface* textRenderUTF8Blended(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderUTF8_Blended(font, text, fg); }
	export SDL_Surface* textRenderUTF8BlendedWrapped(TTF_Font* font, const char* text, SDL_Color fg, Uint32 wrapLength) { return TTF_RenderUTF8_Blended_Wrapped(font, text, fg, wrapLength); }
	export SDL_Surface* textRenderUTF8Shaded(TTF_Font* font, const char* text, SDL_Color fg, SDL_Color bg) { return TTF_RenderUTF8_Shaded(font, text, fg, bg); }
	export SDL_Surface* textRenderUTF8Solid(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderUTF8_Solid(font, text, fg); }

	/* Window functions */
	export const char* windowGetTitle() { return SDL_GetWindowTitle(window); }
	export float windowGetOpacity() { return SDL_GetWindowOpacity(window); }
	export int windowSetFullscreen(Uint32 flags) { return SDL_SetWindowFullscreen(window, flags); }
	export int windowUpdateSurface() { return SDL_UpdateWindowSurface(window); }
	export SDL_bool windowGetMouseGrab() { return SDL_GetWindowMouseGrab(window); }
	export SDL_Renderer* windowCreateRenderer() { return SDL_CreateRenderer(window, nullptr); }
	export SDL_Surface* windowGetSurface() { return SDL_GetWindowSurface(window); }
	export Uint32 windowGetFlags() { return SDL_GetWindowFlags(window); }
	export void windowGetPosition(int* x, int* y) { SDL_GetWindowPosition(window, x, y); }
	export void windowGetSize(int* w, int* h) { SDL_GetWindowSize(window, w, h); }
	export void windowHide() { SDL_HideWindow(window); }
	export void windowMaximize() { SDL_MaximizeWindow(window); }
	export void windowMinimize() { SDL_MinimizeWindow(window); }
	export void windowRaise() { SDL_RaiseWindow(window); }
	export void windowRestore() { SDL_RestoreWindow(window); }
	export void windowSetIcon(SDL_Surface* icon) { SDL_SetWindowIcon(window, icon); }
	export void windowSetModalFor(SDL_Window* modal_window, SDL_Window* parent_window) { SDL_SetWindowModalFor(modal_window, parent_window); }
	export void windowSetMouseGrab(SDL_bool grabbed) { SDL_SetWindowMouseGrab(window, grabbed); }
	export void windowSetOpacity(float opacity) { SDL_SetWindowOpacity(window, opacity); }
	export void windowSetPosition(int x, int y) { SDL_SetWindowPosition(window, x, y); }
	export void windowSetSize(int w, int h) {
		SDL_SetWindowSize(window, w, h);
		winH = h;
		winW = w;
	}
	export void windowSetTitle(const char* title) { SDL_SetWindowTitle(window, title); }
	export void windowShow() { SDL_ShowWindow(window); }

	/* Misc functions */
	export const char* __cdecl getError() { return TTF_GetError(); }
	export template <typename... Args> void log(SDL_LogPriority priority, const char* message, const Args&... args) { SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message, args...); }
	export template <typename... Args> void log(SDL_LogPriority priority, std::string_view message, const Args&... args) { SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message.data(), args...); }
	export template <typename... Args> void logInfo(const char* message, const Args&... args) { log(SDL_LOG_PRIORITY_INFO, message, args...); }
	export template <typename... Args> void logInfo(std::string_view message, const Args&... args) { log(SDL_LOG_PRIORITY_INFO, message, args...); }
	export template <typename... Args> void logError(const char* message, const Args&... args) { log(SDL_LOG_PRIORITY_ERROR, message, args...); }
	export template <typename... Args> void logError(std::string_view message, const Args&... args) { log(SDL_LOG_PRIORITY_ERROR, message, args...); }
	export bool sdlEnabled() { return enabled; }
	export Uint64 timeDelta() { return delta; }
	export Uint64 timeTotal() { return timeCurrent; }
	export void setFPSLimit(int fps) { fpsLimit = fps > 0 ? NANOS_PER_SECOND / fps : 0; }

	/*
	 * CUSTOM FUNCTIONS
	 */

	export SDL_Color toTextColor(const Color& c) {
		return {
			static_cast<Uint8>(255 * c.r),
			static_cast<Uint8>(255 * c.g),
			static_cast<Uint8>(255 * c.b),
			static_cast<Uint8>(255 * c.a),
		};
	}

	// When using a fixed framerate, sleep to fill up remaining time
	export void capFrame() {
		if (fpsLimit > delta) {
			SDL_Delay(fpsLimit - delta);
		}
	}

	// Draw a texture with the given parameters
	export void queueDraw(GpuCommandBuffer* cmdbuf, SDL_GpuRenderPass* renderPass, SDL_GpuTexture* texture, const Color* color, float x, float y, float w, float h, float rotZ, SDL_GpuGraphicsPipeline* pipeline, SDL_GpuBuffer* vertexBuffer, int vertexOff = 0) {
		if (rotZ != 0) {
			float cosZ = std::cos(rotZ);
			float sinZ = std::sin(rotZ);

			matrixUniform.m11 = (w / winW * 2) * cosZ;
			matrixUniform.m12 = -(w / winW * 2) * sinZ;
			matrixUniform.m21 = (h / winH * 2) * sinZ;
			matrixUniform.m22 = (h / winH * 2) * cosZ;
			matrixUniform.m41 = (2 * x / winW) - 1 + w / winW;
			matrixUniform.m42 = 1 - (2 * y / winH) - h / winH;
		}
		else {
			matrixUniform.m11 = w / winW * 2;
			matrixUniform.m12 = 0;
			matrixUniform.m21 = 0;
			matrixUniform.m22 = h / winH * 2;
			matrixUniform.m41 = (2 * x / winW) - 1 + w / winW;
			matrixUniform.m42 = 1 - (2 * y / winH) - h / winH;
		}

		if (lastPipeline != pipeline) {
			SDL_GpuBindGraphicsPipeline(renderPass, pipeline);
			lastPipeline = pipeline;
		}
		if (lastBufferVertex != vertexBuffer) {
			SDL_GpuBufferBinding b = { vertexBuffer, 0 };
			SDL_GpuBindVertexBuffers(renderPass, 0, &b, 1);
			lastBufferIndex = vertexBuffer;
		}
		if (lastBufferIndex != bufferIndex) {
			SDL_GpuBufferBinding b = { bufferIndex, 0 };
			SDL_GpuBindIndexBuffer(renderPass, &b, SDL_GPU_INDEXELEMENTSIZE_16BIT);
			lastBufferIndex = bufferIndex;
		}
		if (lastTexture != texture) {
			SDL_GpuTextureSamplerBinding b = { texture, sampler };
			SDL_GpuBindFragmentSamplers(renderPass, 0, &b, 1);
			lastTexture = texture;
		}

		SDL_GpuPushVertexUniformData(cmdbuf, 0, &matrixUniform, sizeof(matrixUniform));
		SDL_GpuPushFragmentUniformData(cmdbuf, 0, color, sizeof(SDL_GpuColor));
		SDL_GpuDrawIndexedPrimitives(renderPass, vertexOff, 0, 2, 1);
	}
	export void queueDraw(GpuCommandBuffer* cmdbuf, SDL_GpuRenderPass* renderPass, SDL_GpuTexture* texture, const Color* color, float x, float y, float w, float h, float rotZ = 0, SDL_GpuGraphicsPipeline* pipeline = RENDER_STANDARD, int vertexOff = 0) { queueDraw(cmdbuf, renderPass, texture, color, x, y, w, h, rotZ, pipeline, bufferVertex, vertexOff); }
	export void queueDrawBordered(GpuCommandBuffer* cmdbuf, SDL_GpuRenderPass* renderPass, SDL_GpuTexture* texture, const Color* color, float x, float y, float w, float h, float rotZ = 0, SDL_GpuGraphicsPipeline* pipeline = RENDER_STANDARD, int vertexOff = 0) { queueDraw(cmdbuf, renderPass, texture, color, x, y, w, h, rotZ, pipeline, bufferVertexBordered, vertexOff); }
	export void queueDrawHorizontal(GpuCommandBuffer* cmdbuf, SDL_GpuRenderPass* renderPass, SDL_GpuTexture* texture, const Color* color, float x, float y, float w, float h, float rotZ = 0, SDL_GpuGraphicsPipeline* pipeline = RENDER_STANDARD, int vertexOff = 0) { queueDraw(cmdbuf, renderPass, texture, color, x, y, w, h, rotZ, pipeline, bufferVertexHorizontal, vertexOff); }
	export void queueDrawVertical(GpuCommandBuffer* cmdbuf, SDL_GpuRenderPass* renderPass, SDL_GpuTexture* texture, const Color* color, float x, float y, float w, float h, float rotZ = 0, SDL_GpuGraphicsPipeline* pipeline = RENDER_STANDARD, int vertexOff = 0) { queueDraw(cmdbuf, renderPass, texture, color, x, y, w, h, rotZ, pipeline, bufferVertexVertical, vertexOff); }

	// Reset draw parameters at the end of each frame
	export void resetDrawCaches() {
		lastPipeline = nullptr;
		lastBufferIndex = nullptr;
		lastBufferVertex = nullptr;
		lastTexture = nullptr;
	}

	// Uploads data for a single texture
	export GpuTexture* uploadTexture(SDL_GpuCopyPass* copyPass, SDL_Surface* surface, SDL_GpuTransferBuffer* textureTransferBuffer) {
		Uint32 w = surface->w;
		Uint32 h = surface->h;
		const Uint32 imageSizeInBytes = w * h * 4;

		SDL_GpuTransferBufferRegion tbr = {
			.transferBuffer = textureTransferBuffer,
				.offset = 0,
				.size = w * h * 4
		};
		SDL_GpuSetTransferData(
			device,
			surface->pixels,
			&tbr,
			SDL_FALSE
		);

		SDL_GpuTextureCreateInfo info = {
				.width = w,
				.height = h,
				.depth = 1,
				.isCube = SDL_FALSE,
				.layerCount = 1,
				.levelCount = 1,
				.sampleCount = SDL_GPU_SAMPLECOUNT_1,
				.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8,
				.usageFlags = SDL_GPU_TEXTUREUSAGE_SAMPLER_BIT
		};
		GpuTexture* texture = sdl::gpuCreateTexture(&info);

		SDL_GpuTextureTransferInfo tInfo = {
			.transferBuffer = textureTransferBuffer,
			.offset = 0,
		};
		SDL_GpuTextureRegion tRegion = {
			.textureSlice = {texture},
				.w = w,
				.h = h,
				.d = 1
		};

		sdl::gpuUploadToTexture(copyPass, &tInfo, &tRegion, sdl::CONST_FALSE);
		return texture;
	}

	// Uploads data for a single texture, generating a dedicated transfer buffer for this texture
	export GpuTexture* uploadTexture(SDL_GpuCopyPass* copyPass, SDL_Surface* surface) {
		SDL_GpuTransferBuffer* textureTransferBuffer = sdl::gpuCreateTransferBuffer(
			SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			surface->w * surface->h * 4
		);
		GpuTexture* tex = uploadTexture(copyPass, surface, textureTransferBuffer);
		sdl::gpuReleaseTransferBuffer(textureTransferBuffer);
		return tex;
	}

	// Uploads data for a texture to be placed in a texture array
	export GpuTexture* uploadTextureForArray(SDL_GpuCopyPass* copyPass, SDL_Surface* surface, GpuTexture* texture, GpuTransferBuffer* textureTransferBuffer, Uint32 layer) {
		Uint32 w = surface->w;
		Uint32 h = surface->h;
		const Uint32 imageSizeInBytes = w * h * 4;

		SDL_GpuTransferBufferRegion tbr = {
			.transferBuffer = textureTransferBuffer,
				.offset = imageSizeInBytes * layer,
				.size = imageSizeInBytes
		};
		SDL_GpuSetTransferData(
			device,
			surface->pixels,
			&tbr,
			SDL_FALSE
		);

		SDL_GpuTextureTransferInfo tInfo = {
			.transferBuffer = textureTransferBuffer,
			.offset = imageSizeInBytes * layer,
		};
		SDL_GpuTextureRegion tRegion = {
			.textureSlice = {texture, layer},
			.w = w,
			.h = h,
			.d = 1
		};

		sdl::gpuUploadToTexture(copyPass, &tInfo, &tRegion, sdl::CONST_FALSE);
		return texture;
	}


	// Set up SDL. Returns true if SDL setup succeeds
	export bool initSDL() {
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

		// TODO initialize pad

		enabled = true;

		return true;
	}

	// Set up window and its rendering device. Returns true if set up successfully
	// TODO allow modifying sampler settings
	export bool initWindow(int w, int h, Uint32 windowFlags = 0, bool vsync = false, const char* title = "Fabricate") {
		window = SDL_CreateWindow(title, w, h, windowFlags);
		if (!window) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Window went derp: %s", SDL_GetError());
			SDL_Quit();
			return false;
		}
		winH = h;
		winW = w;

		// Setup device for this window
		device = SDL_GpuCreateDevice(SDL_GPU_BACKEND_ALL, SDL_TRUE, SDL_FALSE);
		if (!device) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Device went derp: %s", SDL_GetError());
			SDL_Quit();
			return false;
		}
		if (!SDL_GpuClaimWindow(device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, vsync ? SDL_GPU_PRESENTMODE_VSYNC : SDL_GPU_PRESENTMODE_IMMEDIATE))
		{
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "GpuClaimWindow went derp: %s", SDL_GetError());
			SDL_Quit();
			return false;
		}

		// Setup buffers
		constexpr Uint32 sizeVert = sizeof(TexPos) * VERTICES.size();
		constexpr Uint32 sizeVertBordered = sizeof(TexPos) * VERTICES_BORDERED.size();
		constexpr Uint32 sizeVertHorizontal = sizeof(TexPos) * VERTICES_HORIZONTAL.size();
		constexpr Uint32 sizeVertVertical = sizeof(TexPos) * VERTICES_VERTICAL.size();
		constexpr Uint32 sizeIndices = sizeof(Uint16) * INDICES.size();
		bufferVertex = SDL_GpuCreateBuffer(device, SDL_GPU_BUFFERUSAGE_VERTEX_BIT, sizeVert);
		bufferVertexBordered = SDL_GpuCreateBuffer(device, SDL_GPU_BUFFERUSAGE_VERTEX_BIT, sizeVertBordered);
		bufferVertexHorizontal = SDL_GpuCreateBuffer(device, SDL_GPU_BUFFERUSAGE_VERTEX_BIT, sizeVertHorizontal);
		bufferVertexVertical = SDL_GpuCreateBuffer(device, SDL_GPU_BUFFERUSAGE_VERTEX_BIT, sizeVertVertical);
		bufferIndex = SDL_GpuCreateBuffer(device, SDL_GPU_BUFFERUSAGE_INDEX_BIT, sizeIndices);

		SDL_GpuTransferBuffer* bufferTransferBuffer = SDL_GpuCreateTransferBuffer(
			device,
			SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			(sizeVert + sizeVertBordered + sizeVertHorizontal + sizeVertVertical + sizeIndices)
		);
		void* transferData;
		sdl::gpuMapTransferBuffer(
			bufferTransferBuffer,
			SDL_FALSE,
			&transferData
		);

		sdl::TexPos* vertexData = reinterpret_cast<sdl::TexPos*>(transferData);
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

		sdl::gpuUnmapTransferBuffer(bufferTransferBuffer);

		SDL_GpuCommandBuffer* uploadCmdBuf = gpuAcquireCommandBuffer();
		SDL_GpuCopyPass* copyPass = SDL_GpuBeginCopyPass(uploadCmdBuf);

		SDL_GpuTransferBufferLocation t1 = { bufferTransferBuffer , 0 };
		SDL_GpuBufferRegion r1 = { bufferVertex, 0, sizeVert };
		SDL_GpuUploadToBuffer(copyPass, &t1, &r1, SDL_FALSE);

		SDL_GpuTransferBufferLocation t2 = { bufferTransferBuffer , sizeVert };
		SDL_GpuBufferRegion r2 = { bufferVertexBordered, 0, sizeVertBordered };
		SDL_GpuUploadToBuffer(copyPass, &t2, &r2, SDL_FALSE);

		SDL_GpuTransferBufferLocation t3 = { bufferTransferBuffer ,sizeVert + sizeVertBordered };
		SDL_GpuBufferRegion r3 = { bufferVertexHorizontal, 0, sizeVertHorizontal };
		SDL_GpuUploadToBuffer(copyPass, &t3, &r3, SDL_FALSE);

		SDL_GpuTransferBufferLocation t4 = { bufferTransferBuffer , sizeVert + sizeVertBordered + sizeVertHorizontal };
		SDL_GpuBufferRegion r4 = { bufferVertexVertical, 0, sizeVertVertical };
		SDL_GpuUploadToBuffer(copyPass, &t4, &r4, SDL_FALSE);

		SDL_GpuTransferBufferLocation t5 = { bufferTransferBuffer , sizeVert + sizeVertBordered + sizeVertHorizontal + sizeVertVertical };
		SDL_GpuBufferRegion r5 = { bufferIndex, 0, sizeIndices };
		SDL_GpuUploadToBuffer(copyPass, &t5, &r5, SDL_FALSE);

		SDL_GpuEndCopyPass(copyPass);
		SDL_GpuSubmit(uploadCmdBuf);
		SDL_GpuReleaseTransferBuffer(device, bufferTransferBuffer);

		// Set up standard pipeline
		SDL_GpuSamplerCreateInfo samplerInfo = {
			.minFilter = SDL_GPU_FILTER_LINEAR,
				.magFilter = SDL_GPU_FILTER_LINEAR,
				.mipmapMode = SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
				.addressModeU = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
				.addressModeV = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
				.addressModeW = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
		};
		sampler = SDL_GpuCreateSampler(device, &samplerInfo);

		SDL_GpuShader* shaderFragment = sdl::gpuLoadCompiledShaderFragment(SHADER_NORMAL_FRAG);
		SDL_GpuShader* shaderVertex = sdl::gpuLoadCompiledShaderVertex(SHADER_NORMAL_VERT);
		RENDER_STANDARD = sdl::gpuCreateGraphicsPipelineForShader(shaderVertex, shaderFragment);
		// TODO more shaders/blending modes

		SDL_GpuReleaseShader(device, shaderFragment);
		SDL_GpuReleaseShader(device, shaderVertex);

		return true;
	}

	// Update the renderer with the VSync settings
	export void updateVSync(bool vsync) {
		SDL_GpuSetSwapchainParameters(device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, vsync ? SDL_GPU_PRESENTMODE_VSYNC : SDL_GPU_PRESENTMODE_IMMEDIATE);
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

	// Clean up SDL
	export void quit() {
		// Clean graphics stuff
		SDL_GpuReleaseGraphicsPipeline(device, RENDER_STANDARD);
		SDL_GpuReleaseBuffer(device, bufferVertex);
		SDL_GpuReleaseBuffer(device, bufferVertexBordered);
		SDL_GpuReleaseBuffer(device, bufferVertexHorizontal);
		SDL_GpuReleaseBuffer(device, bufferVertexVertical);
		SDL_GpuReleaseBuffer(device, bufferIndex);
		SDL_GpuReleaseSampler(device, sampler);
		RENDER_STANDARD = nullptr;
		bufferVertex = nullptr;
		bufferVertexBordered = nullptr;
		bufferVertexHorizontal = nullptr;
		bufferVertexVertical = nullptr;
		bufferIndex = nullptr;
		sampler = nullptr;

		SDL_GpuUnclaimWindow(device, window);
		SDL_DestroyWindow(window);
		SDL_GpuDestroyDevice(device);
		device = nullptr;
		window = nullptr;
		TTF_Quit();
		IMG_Quit();
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		enabled = false;
	}
}