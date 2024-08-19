module;

#define SDL_GPU_SHADERCROSS_IMPLEMENTATION
#include "SDL_gpu_shadercross/SDL_gpu_shadercross.h"
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "SDL3_ttf/SDL_ttf.h"

export module sdl.SDLBase;

import sdl.IKeyInputListener;
import std;

namespace sdl {
	export using BlendMode = ::SDL_BlendMode;
	export using Color = ::SDL_FColor;
	export using Event = ::SDL_Event;
	export using FlipMode = ::SDL_FlipMode;
	export using Font = ::TTF_Font;
	export using Gamepad = ::SDL_Gamepad;
	export using GamepadButton = ::SDL_GamepadButton;
	export using GpuBlendFactor = ::SDL_GpuBlendFactor;
	export using GpuBlendOp = ::SDL_GpuBlendOp;
	export using GpuBuffer = ::SDL_GpuBuffer;
	export using GpuBufferBinding = ::SDL_GpuBufferBinding;
	export using GpuBufferLocation = ::SDL_GpuBufferLocation;
	export using GpuBufferRegion = ::SDL_GpuBufferRegion;
	export using GpuBufferUsageFlagBits = ::SDL_GpuBufferUsageFlagBits;
	export using GpuColorAttachmentBlendState = ::SDL_GpuColorAttachmentBlendState;
	export using GpuColorAttachmentDescription = ::SDL_GpuColorAttachmentDescription;
	export using GpuColorAttachmentInfo = ::SDL_GpuColorAttachmentInfo;
	export using GpuColorComponentFlagBits = ::SDL_GpuColorComponentFlagBits;
	export using GpuColorComponentFlags = ::SDL_GpuColorComponentFlags;
	export using GpuCommandBuffer = ::SDL_GpuCommandBuffer;
	export using GpuCompareOp = ::SDL_GpuCompareOp;
	export using GpuComputePass = ::SDL_GpuComputePass;
	export using GpuComputePipeline = ::SDL_GpuComputePipeline;
	export using GpuComputePipelineCreateInfo = ::SDL_GpuComputePipelineCreateInfo;
	export using GpuCopyPass = ::SDL_GpuCopyPass;
	export using GpuCubeMapFace = ::SDL_GpuCubeMapFace;
	export using GpuCullMode = ::SDL_GpuCullMode;
	export using GpuDepthStencilAttachmentInfo = ::SDL_GpuDepthStencilAttachmentInfo;
	export using GpuDepthStencilState = ::SDL_GpuDepthStencilState;
	export using GpuDepthStencilValue = ::SDL_GpuDepthStencilValue;
	export using GpuDevice = ::SDL_GpuDevice;
	export using GpuDriver = ::SDL_GpuDriver;
	export using GpuFence = ::SDL_GpuFence;
	export using GpuFillMode = ::SDL_GpuFillMode;
	export using GpuFilter = ::SDL_GpuFilter;
	export using GpuFrontFace = ::SDL_GpuFrontFace;
	export using GpuGraphicsPipeline = ::SDL_GpuGraphicsPipeline;
	export using GpuGraphicsPipelineAttachmentInfo = ::SDL_GpuGraphicsPipelineAttachmentInfo;
	export using GpuGraphicsPipelineCreateInfo = ::SDL_GpuGraphicsPipelineCreateInfo;
	export using GpuIndexedIndirectDrawCommand = ::SDL_GpuIndexedIndirectDrawCommand;
	export using GpuIndexElementSize = ::SDL_GpuIndexElementSize;
	export using GpuIndirectDispatchCommand = ::SDL_GpuIndirectDispatchCommand;
	export using GpuIndirectDrawCommand = ::SDL_GpuIndirectDrawCommand;
	export using GpuLoadOp = ::SDL_GpuLoadOp;
	export using GpuMultisampleState = ::SDL_GpuMultisampleState;
	export using GpuPresentMode = ::SDL_GpuPresentMode;
	export using GpuPrimitiveType = ::SDL_GpuPrimitiveType;
	export using GpuRasterizerState = ::SDL_GpuRasterizerState;
	export using GpuRenderPass = ::SDL_GpuRenderPass;
	export using GpuSampleCount = ::SDL_GpuSampleCount;
	export using GpuSampler = ::SDL_GpuSampler;
	export using GpuSamplerAddressMode = ::SDL_GpuSamplerAddressMode;
	export using GpuSamplerCreateInfo = ::SDL_GpuSamplerCreateInfo;
	export using GpuSamplerMipmapMode = ::SDL_GpuSamplerMipmapMode;
	export using GpuShader = ::SDL_GpuShader;
	export using GpuShaderCreateInfo = ::SDL_GpuShaderCreateInfo;
	export using GpuShaderFormat = ::SDL_GpuShaderFormat;
	export using GpuShaderStage = ::SDL_GpuShaderStage;
	export using GpuStencilOp = ::SDL_GpuStencilOp;
	export using GpuStencilOpState = ::SDL_GpuStencilOpState;
	export using GpuStorageBufferReadWriteBinding = ::SDL_GpuStorageBufferReadWriteBinding;
	export using GpuStorageTextureReadWriteBinding = ::SDL_GpuStorageTextureReadWriteBinding;
	export using GpuStoreOp = ::SDL_GpuStoreOp;
	export using GpuSwapchainComposition = ::SDL_GpuSwapchainComposition;
	export using GpuTexture = ::SDL_GpuTexture;
	export using GpuTextureCreateInfo = ::SDL_GpuTextureCreateInfo;
	export using GpuTextureFormat = ::SDL_GpuTextureFormat;
	export using GpuTextureLocation = ::SDL_GpuTextureLocation;
	export using GpuTextureRegion = ::SDL_GpuTextureRegion;
	export using GpuTextureSamplerBinding = ::SDL_GpuTextureSamplerBinding;
	export using GpuTextureSlice = ::SDL_GpuTextureSlice;
	export using GpuTextureTransferInfo = ::SDL_GpuTextureTransferInfo;
	export using GpuTextureType = ::SDL_GpuTextureType;
	export using GpuTextureUsageFlagBits = ::SDL_GpuTextureUsageFlagBits;
	export using GpuTextureUsageFlags = ::SDL_GpuTextureUsageFlags;
	export using GpuTransferBuffer = ::SDL_GpuTransferBuffer;
	export using GpuTransferBufferLocation = ::SDL_GpuTransferBufferLocation;
	export using GpuTransferBufferUsage = ::SDL_GpuTransferBufferUsage;
	export using GpuVertexAttribute = ::SDL_GpuVertexAttribute;
	export using GpuVertexBinding = ::SDL_GpuVertexBinding;
	export using GpuVertexElementFormat = ::SDL_GpuVertexElementFormat;
	export using GpuVertexInputRate = ::SDL_GpuVertexInputRate;
	export using GpuVertexInputState = ::SDL_GpuVertexInputState;
	export using GpuViewport = ::SDL_GpuViewport;
	export using Keycode = ::SDL_Keycode;
	export using Music = ::Mix_Music;
	export using PixelFormat = ::SDL_PixelFormat;
	export using Point = ::SDL_FPoint;
	export using PointI = ::SDL_Point;
	export using Properties = ::SDL_PropertiesID;
	export using RectF = ::SDL_FRect;
	export using RectI = ::SDL_Rect;
	export using ScaleMode = ::SDL_ScaleMode;
	export using Scancode = ::SDL_Scancode;
	export using Sound = ::Mix_Chunk;
	export using Surface = ::SDL_Surface;
	export using Window = ::SDL_Window;

	export enum RenderMode {
		NORMAL,
		OVERLAY,
		GRAYSCALE
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
	export constexpr auto PROP_GPU_CREATEDEVICE_NAME_STRING = SDL_PROP_GPU_CREATEDEVICE_NAME_STRING;
	export constexpr Uint64 NANOS_PER_SECOND = 1000000000ULL;

	/* Directory stuff */
	export inline const char* dirBase() noexcept { return SDL_GetBasePath(); }
	export inline char* dirPref(const char* org, const char* app) { return SDL_GetPrefPath(org, app); }
	export inline void dirSelect() {
		//return SDL_ShowOpenFolderDialog();
	}

	/* File stuff */
	export inline void* fileLoad(const char* file, size_t* datasize) { return SDL_LoadFile(file, datasize); }

	/* Font management functions */
	export inline int fontAscent(TTF_Font* font) { return TTF_FontAscent(font); }
	export inline void fontClose(TTF_Font* font) { TTF_CloseFont(font); }
	export inline int fontDescent(TTF_Font* font) { return TTF_FontDescent(font); }
	export inline int fontFaceIsFixedWidth(TTF_Font* font) { return TTF_FontFaceIsFixedWidth(font); }
	export inline long fontFaces(TTF_Font* font) { return TTF_FontFaces(font); }
	export inline int fontGlyphIsProvided(TTF_Font* font, Uint16 ch) { return TTF_GlyphIsProvided(font, ch); }
	export inline int fontGlyphMetrics(TTF_Font* font, Uint16 ch, int* minx, int* maxx, int* miny, int* maxy, int* advance) { return TTF_GlyphMetrics(font, ch, minx, maxx, miny, maxy, advance); }
	export inline int fontHeight(TTF_Font* font) { return TTF_FontHeight(font); }
	export inline int fontHintingGet(TTF_Font* font) { return TTF_GetFontHinting(font); }
	export inline void fontHintingSet(TTF_Font* font, int hinting) { TTF_SetFontHinting(font, hinting); }
	export inline int fontKerningGet(TTF_Font* font) { return TTF_GetFontKerning(font); }
	export inline void fontKerningSet(TTF_Font* font, int allowed) { TTF_SetFontKerning(font, allowed); }
	export inline int fontLineSkip(TTF_Font* font) { return TTF_FontLineSkip(font); }
	export inline TTF_Font* fontOpen(const char* file, int ptsize) { return TTF_OpenFont(file, ptsize); }
	export inline TTF_Font* fontOpenIndex(const char* file, int ptsize, long index) { return TTF_OpenFontIndex(file, ptsize, index); }
	export inline TTF_Font* fontOpenIndexIO(SDL_IOStream* src, int closeio, int ptsize, long index) { return TTF_OpenFontIndexIO(src, closeio, ptsize, index); }
	export inline TTF_Font* fontOpenIO(SDL_IOStream* src, int closeio, int ptsize) { return TTF_OpenFontIO(src, closeio, ptsize); }
	export inline int fontOutlineGet(TTF_Font* font) { return TTF_GetFontOutline(font); }
	export inline void fontOutlineSet(TTF_Font* font, int outline) { TTF_SetFontOutline(font, outline); }
	export inline int fontSizeText(TTF_Font* font, const char* text, int* w, int* h) { return TTF_SizeText(font, text, w, h); }
	export inline int fontSizeUNICODE(TTF_Font* font, const Uint16* text, int* w, int* h) { return TTF_SizeUNICODE(font, text, w, h); }
	export inline int fontSizeUTF8(TTF_Font* font, const char* text, int* w, int* h) { return TTF_SizeUTF8(font, text, w, h); }
	export inline int fontStyleIsSet(TTF_Font* font, int style) { return TTF_GetFontStyle(font) & style; }
	export inline void fontStyleSet(TTF_Font* font, int style) { TTF_SetFontStyle(font, style); }

	/* GPU functions */
	export inline SDL_bool gpuClaimWindow(SDL_GpuDevice* device, SDL_Window* window, SDL_GpuSwapchainComposition swapchainComposition, SDL_GpuPresentMode presentMode) { return SDL_GpuClaimWindow(device, window, swapchainComposition, presentMode); }
	export inline SDL_bool gpuIsTextureFormatSupported(SDL_GpuDevice* device, SDL_GpuTextureFormat format, SDL_GpuTextureType type, SDL_GpuTextureUsageFlags usage) { return SDL_GpuSupportsTextureFormat(device, format, type, usage); }
	export inline SDL_bool gpuQueryFence(SDL_GpuDevice* device, SDL_GpuFence* fence) { return SDL_GpuQueryFence(device, fence); }
	export inline SDL_bool gpuSetSwapchainParameters(SDL_GpuDevice* device, SDL_Window* window, SDL_GpuSwapchainComposition swapchainComposition, SDL_GpuPresentMode presentMode) { return SDL_GpuSetSwapchainParameters(device, window, swapchainComposition, presentMode); }
	export inline SDL_bool gpuSupportsPresentMode(SDL_GpuDevice* device, SDL_Window* window, SDL_GpuPresentMode presentMode) { return SDL_GpuSupportsPresentMode(device, window, presentMode); }
	export inline SDL_bool gpuSupportsSwapchainComposition(SDL_GpuDevice* device, SDL_Window* window, SDL_GpuSwapchainComposition swapchainComposition) { return SDL_GpuSupportsSwapchainComposition(device, window, swapchainComposition); }
	export inline SDL_GpuBuffer* gpuCreateBuffer(SDL_GpuDevice* device, SDL_GpuBufferUsageFlags usageFlags, Uint32 sizeInBytes) { return SDL_GpuCreateBuffer(device, usageFlags, sizeInBytes); }
	export inline SDL_GpuCommandBuffer* gpuAcquireCommandBuffer(SDL_GpuDevice* device) { return SDL_GpuAcquireCommandBuffer(device); }
	export inline SDL_GpuComputePass* gpuBeginComputePass(SDL_GpuCommandBuffer* commandBuffer, SDL_GpuStorageTextureReadWriteBinding* storageTextureBindings, Uint32 storageTextureBindingCount, SDL_GpuStorageBufferReadWriteBinding* storageBufferBindings, Uint32 storageBufferBindingCount) { return SDL_GpuBeginComputePass(commandBuffer, storageTextureBindings, storageTextureBindingCount, storageBufferBindings, storageBufferBindingCount); }
	export inline SDL_GpuComputePipeline* gpuCreateComputePipeline(SDL_GpuDevice* device, SDL_GpuComputePipelineCreateInfo* computePipelineCreateInfo) { return SDL_GpuCreateComputePipeline(device, computePipelineCreateInfo); }
	export inline SDL_GpuComputePipeline* gpuCompileSpirvCompute(SDL_GpuDevice* device, SDL_GpuShaderCreateInfo* shaderCreateInfo) { return static_cast<SDL_GpuComputePipeline*>(SDL_CompileFromSPIRV(device, &shaderCreateInfo, true)); }
	export inline SDL_GpuCopyPass* gpuBeginCopyPass(SDL_GpuCommandBuffer* commandBuffer) { return SDL_GpuBeginCopyPass(commandBuffer); }
	export inline SDL_GpuDriver gpuGetDriver(SDL_GpuDevice* device) { return SDL_GpuGetDriver(device); }
	export inline SDL_GpuFence* gpuSubmitAndAcquireFence(SDL_GpuCommandBuffer* commandBuffer) { return SDL_GpuSubmitAndAcquireFence(commandBuffer); }
	export inline SDL_GpuGraphicsPipeline* gpuCreateGraphicsPipeline(SDL_GpuDevice* device, SDL_GpuGraphicsPipelineCreateInfo* pipelineCreateInfo) { return SDL_GpuCreateGraphicsPipeline(device, pipelineCreateInfo); }
	export inline SDL_GpuRenderPass* gpuBeginRenderPass(SDL_GpuCommandBuffer* commandBuffer, SDL_GpuColorAttachmentInfo* colorAttachmentInfos, Uint32 colorAttachmentCount, SDL_GpuDepthStencilAttachmentInfo* depthStencilAttachmentInfo) { return SDL_GpuBeginRenderPass(commandBuffer, colorAttachmentInfos, colorAttachmentCount, depthStencilAttachmentInfo); }
	export inline SDL_GpuSampleCount gpuGetBestSampleCount(SDL_GpuDevice* device, SDL_GpuTextureFormat format, SDL_GpuSampleCount desiredSampleCount) { return SDL_GpuGetBestSampleCount(device, format, desiredSampleCount); }
	export inline SDL_GpuSampler* gpuCreateSampler(SDL_GpuDevice* device, SDL_GpuSamplerCreateInfo* samplerCreateInfo) { return SDL_GpuCreateSampler(device, samplerCreateInfo); }
	export inline SDL_GpuShader* gpuCompileSpirvShader(SDL_GpuDevice* device, SDL_GpuShaderCreateInfo* shaderCreateInfo) { return static_cast<SDL_GpuShader*>(SDL_CompileFromSPIRV(device, &shaderCreateInfo, false)); }
	export inline SDL_GpuShader* gpuCreateShader(SDL_GpuDevice* device, SDL_GpuShaderCreateInfo* shaderCreateInfo) { return SDL_GpuCreateShader(device, shaderCreateInfo); }
	export inline SDL_GpuTexture* gpuAcquireSwapchainTexture( SDL_GpuCommandBuffer* commandBuffer, SDL_Window* window, Uint32* pWidth, Uint32* pHeight) { return SDL_GpuAcquireSwapchainTexture(commandBuffer, window, pWidth, pHeight); }
	export inline SDL_GpuTexture* gpuCreateTexture(SDL_GpuDevice* device, SDL_GpuTextureCreateInfo* textureCreateInfo) { return SDL_GpuCreateTexture(device, textureCreateInfo); }
	export inline SDL_GpuTextureFormat gpuGetSwapchainTextureFormat(SDL_GpuDevice* device, SDL_Window* window) { return SDL_GpuGetSwapchainTextureFormat(device, window); }
	export inline SDL_GpuTransferBuffer* gpuCreateTransferBuffer(SDL_GpuDevice* device, SDL_GpuTransferBufferUsage usage, Uint32 sizeInBytes) { return SDL_GpuCreateTransferBuffer(device, usage, sizeInBytes); }
	export inline Uint32 gpuTextureFormatTexelBlockSize(SDL_GpuTextureFormat textureFormat) { return SDL_GpuTextureFormatTexelBlockSize(textureFormat); }
	export inline void gpuBindComputePipeline(SDL_GpuComputePass* computePass, SDL_GpuComputePipeline* computePipeline) { SDL_GpuBindComputePipeline(computePass, computePipeline); }
	export inline void gpuBindComputeStorageBuffers(SDL_GpuComputePass* computePass, Uint32 firstSlot, SDL_GpuBuffer** storageBuffers, Uint32 bindingCount) { SDL_GpuBindComputeStorageBuffers(computePass, firstSlot, storageBuffers, bindingCount); }
	export inline void gpuBindComputeStorageTextures(SDL_GpuComputePass* computePass, Uint32 firstSlot, SDL_GpuTextureSlice* storageTextureSlices, Uint32 bindingCount) { SDL_GpuBindComputeStorageTextures(computePass, firstSlot, storageTextureSlices, bindingCount); }
	export inline void gpuBindFragmentSamplers(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuTextureSamplerBinding* textureSamplerBindings, Uint32 bindingCount) { SDL_GpuBindFragmentSamplers(renderPass, firstSlot, textureSamplerBindings, bindingCount); }
	export inline void gpuBindFragmentStorageBuffers(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuBuffer** storageBuffers, Uint32 bindingCount) { SDL_GpuBindFragmentStorageBuffers(renderPass, firstSlot, storageBuffers, bindingCount); }
	export inline void gpuBindFragmentStorageTextures(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuTextureSlice* storageTextureSlices, Uint32 bindingCount) { SDL_GpuBindFragmentStorageTextures(renderPass, firstSlot, storageTextureSlices, bindingCount); }
	export inline void gpuBindGraphicsPipeline(SDL_GpuRenderPass* renderPass, SDL_GpuGraphicsPipeline* graphicsPipeline) { SDL_GpuBindGraphicsPipeline(renderPass, graphicsPipeline); }
	export inline void gpuBindIndexBuffer(SDL_GpuRenderPass* renderPass, SDL_GpuBufferBinding* pBinding, SDL_GpuIndexElementSize indexElementSize) { SDL_GpuBindIndexBuffer(renderPass, pBinding, indexElementSize); }
	export inline void gpuBindVertexBuffers(SDL_GpuRenderPass* renderPass, Uint32 firstBinding, SDL_GpuBufferBinding* pBindings, Uint32 bindingCount) { SDL_GpuBindVertexBuffers(renderPass, firstBinding, pBindings, bindingCount); }
	export inline void gpuBindVertexSamplers(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuTextureSamplerBinding* textureSamplerBindings, Uint32 bindingCount) { SDL_GpuBindVertexSamplers(renderPass, firstSlot, textureSamplerBindings, bindingCount); }
	export inline void gpuBindVertexStorageBuffers(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuBuffer** storageBuffers, Uint32 bindingCount) { SDL_GpuBindVertexStorageBuffers(renderPass, firstSlot, storageBuffers, bindingCount); }
	export inline void gpuBindVertexStorageTextures(SDL_GpuRenderPass* renderPass, Uint32 firstSlot, SDL_GpuTextureSlice* storageTextureSlices, Uint32 bindingCount) { SDL_GpuBindVertexStorageTextures(renderPass, firstSlot, storageTextureSlices, bindingCount); }
	export inline void gpuBlit(SDL_GpuCommandBuffer* commandBuffer, SDL_GpuTextureRegion* source, SDL_GpuTextureRegion* destination, SDL_GpuFilter filterMode, SDL_bool cycle) { SDL_GpuBlit(commandBuffer, source, destination, filterMode, cycle); }
	export inline void gpuCopyBufferToBuffer(SDL_GpuCopyPass* copyPass, SDL_GpuBufferLocation* source, SDL_GpuBufferLocation* destination, Uint32 size, SDL_bool cycle) { SDL_GpuCopyBufferToBuffer(copyPass, source, destination, size, cycle); }
	export inline void gpuCopyTextureToTexture(SDL_GpuCopyPass* copyPass, SDL_GpuTextureLocation* source, SDL_GpuTextureLocation* destination, Uint32 w, Uint32 h, Uint32 d, SDL_bool cycle) { SDL_GpuCopyTextureToTexture(copyPass, source, destination, w, h, d, cycle); }
	export inline void gpuDispatchCompute(SDL_GpuComputePass* computePass, Uint32 groupCountX, Uint32 groupCountY, Uint32 groupCountZ) { SDL_GpuDispatchCompute(computePass, groupCountX, groupCountY, groupCountZ); }
	export inline void gpuDispatchComputeIndirect(SDL_GpuComputePass* computePass, SDL_GpuBuffer* buffer, Uint32 offsetInBytes) { SDL_GpuDispatchComputeIndirect(computePass, buffer, offsetInBytes); }
	export inline void gpuDownloadFromBuffer(SDL_GpuCopyPass* copyPass, SDL_GpuBufferRegion* source, SDL_GpuTransferBufferLocation* destination) { SDL_GpuDownloadFromBuffer(copyPass, source, destination); }
	export inline void gpuDownloadFromTexture(SDL_GpuCopyPass* copyPass, SDL_GpuTextureRegion* source, SDL_GpuTextureTransferInfo* destination) { SDL_GpuDownloadFromTexture(copyPass, source, destination); }
	export inline void gpuDrawIndexedPrimitives(SDL_GpuRenderPass* renderPass, Uint32 baseVertex, Uint32 startIndex, Uint32 primitiveCount, Uint32 instanceCount) { SDL_GpuDrawIndexedPrimitives(renderPass, baseVertex, startIndex, primitiveCount, instanceCount); }
	export inline void gpuDrawIndexedPrimitivesIndirect(SDL_GpuRenderPass* renderPass, SDL_GpuBuffer* buffer, Uint32 offsetInBytes, Uint32 drawCount, Uint32 stride) { SDL_GpuDrawIndexedPrimitivesIndirect(renderPass, buffer, offsetInBytes, drawCount, stride); }
	export inline void gpuDrawPrimitives(SDL_GpuRenderPass* renderPass, Uint32 vertexStart, Uint32 primitiveCount) { SDL_GpuDrawPrimitives(renderPass, vertexStart, primitiveCount); }
	export inline void gpuDrawPrimitivesIndirect(SDL_GpuRenderPass* renderPass, SDL_GpuBuffer* buffer, Uint32 offsetInBytes, Uint32 drawCount, Uint32 stride) { SDL_GpuDrawPrimitivesIndirect(renderPass, buffer, offsetInBytes, drawCount, stride); }
	export inline void gpuEndComputePass(SDL_GpuComputePass* computePass) { SDL_GpuEndComputePass(computePass); }
	export inline void gpuEndCopyPass(SDL_GpuCopyPass* copyPass) { SDL_GpuEndCopyPass(copyPass); }
	export inline void gpuEndRenderPass(SDL_GpuRenderPass* renderPass) { SDL_GpuEndRenderPass(renderPass); }
	export inline void gpuGenerateMipmaps(SDL_GpuCopyPass* copyPass, SDL_GpuTexture* texture) { SDL_GpuGenerateMipmaps(copyPass, texture); }
	export inline void gpuInsertDebugLabel(SDL_GpuCommandBuffer* commandBuffer, const char* text) { SDL_GpuInsertDebugLabel(commandBuffer, text); }
	export inline void gpuMapTransferBuffer(SDL_GpuDevice* device, SDL_GpuTransferBuffer* transferBuffer, SDL_bool cycle, void** ppData) { SDL_GpuMapTransferBuffer(device, transferBuffer, cycle, ppData); }
	export inline void gpuPopDebugGroup(SDL_GpuCommandBuffer* commandBuffer) { SDL_GpuPopDebugGroup(commandBuffer); }
	export inline void gpuPushComputeUniformData(SDL_GpuCommandBuffer* commandBuffer, Uint32 slotIndex, const void* data, Uint32 dataLengthInBytes) { SDL_GpuPushComputeUniformData(commandBuffer, slotIndex, data, dataLengthInBytes); }
	export inline void gpuPushDebugGroup(SDL_GpuCommandBuffer* commandBuffer, const char* name) { SDL_GpuPushDebugGroup(commandBuffer, name); }
	export inline void gpuPushFragmentUniformData(SDL_GpuCommandBuffer* commandBuffer, Uint32 slotIndex, const void* data, Uint32 dataLengthInBytes) { SDL_GpuPushFragmentUniformData(commandBuffer, slotIndex, data, dataLengthInBytes); }
	export inline void gpuPushVertexUniformData(SDL_GpuCommandBuffer* commandBuffer, Uint32 slotIndex, const void* data, Uint32 dataLengthInBytes) { SDL_GpuPushVertexUniformData(commandBuffer, slotIndex, data, dataLengthInBytes); }
	export inline void gpuReleaseBuffer(SDL_GpuDevice* device, SDL_GpuBuffer* buffer) { SDL_GpuReleaseBuffer(device, buffer); }
	export inline void gpuReleaseComputePipeline(SDL_GpuDevice* device, SDL_GpuComputePipeline* computePipeline) { SDL_GpuReleaseComputePipeline(device, computePipeline); }
	export inline void gpuReleaseFence(SDL_GpuDevice* device, SDL_GpuFence* fence) { SDL_GpuReleaseFence(device, fence); }
	export inline void gpuReleaseGraphicsPipeline(SDL_GpuDevice* device, SDL_GpuGraphicsPipeline* graphicsPipeline) { SDL_GpuReleaseGraphicsPipeline(device, graphicsPipeline); }
	export inline void gpuReleaseSampler(SDL_GpuDevice* device, SDL_GpuSampler* sampler) { SDL_GpuReleaseSampler(device, sampler); }
	export inline void gpuReleaseShader(SDL_GpuDevice* device, SDL_GpuShader* shader) { SDL_GpuReleaseShader(device, shader); }
	export inline void gpuReleaseTexture(SDL_GpuDevice* device, SDL_GpuTexture* texture) { SDL_GpuReleaseTexture(device, texture); }
	export inline void gpuReleaseTransferBuffer(SDL_GpuDevice* device, SDL_GpuTransferBuffer* transferBuffer) { SDL_GpuReleaseTransferBuffer(device, transferBuffer); }
	export inline void gpuSetBufferName(SDL_GpuDevice* device, SDL_GpuBuffer* buffer, const char* text) { SDL_GpuSetBufferName(device, buffer, text); }
	export inline void gpuSetScissor(SDL_GpuRenderPass* renderPass, RectI* scissor) { SDL_GpuSetScissor(renderPass, scissor); }
	export inline void gpuSetTextureName(SDL_GpuDevice* device, SDL_GpuTexture* texture, const char* text) { SDL_GpuSetTextureName(device, texture, text); }
	export inline void gpuSetViewport(SDL_GpuRenderPass* renderPass, SDL_GpuViewport* viewport) { SDL_GpuSetViewport(renderPass, viewport); }
	export inline void gpuSubmit(SDL_GpuCommandBuffer* commandBuffer) { SDL_GpuSubmit(commandBuffer); }
	export inline void gpuUnclaimWindow(SDL_GpuDevice* device, SDL_Window* window) { SDL_GpuUnclaimWindow(device, window); }
	export inline void gpuUnmapTransferBuffer(SDL_GpuDevice* device, SDL_GpuTransferBuffer* transferBuffer) { SDL_GpuUnmapTransferBuffer(device, transferBuffer); }
	export inline void gpuUploadToBuffer(SDL_GpuCopyPass* copyPass, SDL_GpuTransferBufferLocation* source, SDL_GpuBufferRegion* destination, SDL_bool cycle = SDL_FALSE) { SDL_GpuUploadToBuffer(copyPass, source, destination, cycle); }
	export inline void gpuUploadToTexture(SDL_GpuCopyPass* copyPass, SDL_GpuTextureTransferInfo* source, SDL_GpuTextureRegion* destination, SDL_bool cycle = SDL_FALSE) { SDL_GpuUploadToTexture(copyPass, source, destination, cycle); }
	export inline void gpuWait(SDL_GpuDevice* device) { SDL_GpuWait(device); }
	export inline void gpuWaitForFences(SDL_GpuDevice* device, SDL_bool waitAll, SDL_GpuFence** pFences, Uint32 fenceCount) { SDL_GpuWaitForFences(device, waitAll, pFences, fenceCount); }

	/* Music management functions */
	export double musicGetPosition(Mix_Music* music) { return Mix_GetMusicPosition(music); }
	export inline int musicFadeOut(int ms) { return Mix_FadeOutMusic(ms); }
	export inline int musicGetVolume() { return Mix_VolumeMusic(-1); }
	export inline int musicHalt() { return Mix_HaltMusic(); }
	export inline int musicIsPaused() { return Mix_PausedMusic(); }
	export inline int musicPlay(Mix_Music* music, int loops = -1) { return Mix_PlayMusic(music, loops); }
	export inline int musicPlayFade(Mix_Music* music, int fade, int loops = -1) { return Mix_FadeInMusic(music, loops, fade); }
	export inline int musicSetPosition(double position) { return Mix_SetMusicPosition(position); }
	export inline Mix_Music* musicLoad(const char* path) { return Mix_LoadMUS(path); }
	export inline void musicFree(Mix_Music* music) { Mix_FreeMusic(music); }
	export inline void musicPause() { Mix_PauseMusic(); }
	export inline void musicResume() { Mix_ResumeMusic(); }
	export inline void musicRewind() { Mix_RewindMusic(); }
	export inline void musicSetVolume(int volume) { Mix_VolumeMusic(volume); }

	/* Surface functions */
	export inline int surfaceBlit(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) { return SDL_BlitSurface(src, srcrect, dst, dstrect); }
	export inline int surfaceBlitScaled(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect, SDL_ScaleMode mode) { return SDL_BlitSurfaceScaled(src, srcrect, dst, dstrect, mode); }
	export inline int surfaceFillRect(SDL_Surface* surface, const SDL_Rect* rect, Uint32 color) { return SDL_FillSurfaceRect(surface, rect, color); }
	export inline int surfaceFillRects(SDL_Surface* surface, const SDL_Rect* rects, int count, Uint32 color) { return SDL_FillSurfaceRects(surface, rects, count, color); }
	export inline int surfaceGetClipRect(SDL_Surface* surface, SDL_Rect* rect) { return SDL_GetSurfaceClipRect(surface, rect); }
	export inline int surfaceLock(SDL_Surface* surface) { return SDL_LockSurface(surface); }
	export inline int surfaceSetAlphaMod(SDL_Surface* surface, Uint8 alpha) { return SDL_SetSurfaceAlphaMod(surface, alpha); }
	export inline int surfaceSetBlendMode(SDL_Surface* surface, SDL_BlendMode blendMode) { return SDL_SetSurfaceBlendMode(surface, blendMode); }
	export inline int surfaceSetColorKey(SDL_Surface* surface, Uint32 key) { return SDL_SetSurfaceColorKey(surface, SDL_TRUE, key); }
	export inline int surfaceSetPalette(SDL_Surface* surface, SDL_Palette* palette) { return SDL_SetSurfacePalette(surface, palette); }
	export inline SDL_Surface* surfaceConvert(SDL_Surface* surface, SDL_PixelFormat pixel_format) { return SDL_ConvertSurface(surface, pixel_format); }
	export inline SDL_Surface* surfaceCopy(SDL_Surface* src) { return SDL_DuplicateSurface(src); }
	export inline SDL_Surface* surfaceCreate(int width, int height, SDL_PixelFormat format) { return SDL_CreateSurface(width, height, format); }
	export inline SDL_Surface* surfaceCreate(int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateSurface(width, height, SDL_GetPixelFormatForMasks(depth, Rmask, Gmask, Bmask, Amask)); }
	export inline SDL_Surface* surfaceCreateFrom(void* pixels, int width, int height, int pitch, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateSurfaceFrom(width, height, SDL_GetPixelFormatForMasks(depth, Rmask, Gmask, Bmask, Amask), pixels, pitch); }
	export inline SDL_Surface* surfaceLoad(const char* file) { return IMG_Load(file); }
	export inline void surfaceDestroy(SDL_Surface* surface) { SDL_DestroySurface(surface); }
	export inline void surfaceUnlock(SDL_Surface* surface) { SDL_UnlockSurface(surface); }

	/* Sound management functions */
	export inline int soundChannelPaused(int channel) { return Mix_Paused(channel); }
	export inline int soundExpireChannel(int channel, int ticks) { return Mix_ExpireChannel(channel, ticks); }
	export inline int soundFadeOutChannel(int channel, int ms) { return Mix_FadeOutChannel(channel, ms); }
	export inline int soundGetChannelVolume(int channel) { return Mix_Volume(channel, -1); }
	export inline int soundHaltChannel(int channel) { return Mix_HaltChannel(channel); }
	export inline int soundPlay(Sound* sound, int loops = 0, int time = -1) { return Mix_PlayChannelTimed(-1, sound, loops, time); }
	export inline int soundPlayFade(Sound* sound, int fade, int loops = 0, int time = -1) { return Mix_FadeInChannelTimed(-1, sound, loops, fade, time); }
	export inline int soundReserveChannels(int num) { return Mix_ReserveChannels(num); }
	export inline int soundSetVolume(Sound* sound, int volume) { return Mix_VolumeChunk(sound, volume); }
	export inline Sound* soundGetChunk(int channel) { return Mix_GetChunk(channel); }
	export inline Sound* soundLoad(const char* path) { return Mix_LoadWAV(path); }
	export inline void soundFree(Sound* sound) { Mix_FreeChunk(sound); }
	export inline void soundPauseChannel(int channel) { Mix_Pause(channel); }
	export inline void soundResumeChannel(int channel) { Mix_Resume(channel); }
	export inline void soundSetAllVolume(int volume) {
		for (int i = 0; i < Mix_AllocateChannels(-1); ++i) {
			Mix_Volume(i, volume);
		}
	}

	/* Text rendering functions */
	export inline SDL_Surface* textRenderBlended(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderText_Blended(font, text, fg); }
	export inline SDL_Surface* textRenderBlendedWrapped(TTF_Font* font, const char* text, SDL_Color fg, Uint32 wrapLength) { return TTF_RenderText_Blended_Wrapped(font, text, fg, wrapLength); }
	export inline SDL_Surface* textRenderShaded(TTF_Font* font, const char* text, SDL_Color fg, SDL_Color bg) { return TTF_RenderText_Shaded(font, text, fg, bg); }
	export inline SDL_Surface* textRenderSolid(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderText_Solid(font, text, fg); }
	export inline SDL_Surface* textRenderUNICODEBlended(TTF_Font* font, const Uint16* text, SDL_Color fg) { return TTF_RenderUNICODE_Blended(font, text, fg); }
	export inline SDL_Surface* textRenderUNICODEBlendedWrapped(TTF_Font* font, const Uint16* text, SDL_Color fg, Uint32 wrapLength) { return TTF_RenderUNICODE_Blended_Wrapped(font, text, fg, wrapLength); }
	export inline SDL_Surface* textRenderUNICODEShaded(TTF_Font* font, const Uint16* text, SDL_Color fg, SDL_Color bg) { return TTF_RenderUNICODE_Shaded(font, text, fg, bg); }
	export inline SDL_Surface* textRenderUNICODESolid(TTF_Font* font, const Uint16* text, SDL_Color fg) { return TTF_RenderUNICODE_Solid(font, text, fg); }
	export inline SDL_Surface* textRenderUTF8Blended(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderUTF8_Blended(font, text, fg); }
	export inline SDL_Surface* textRenderUTF8BlendedWrapped(TTF_Font* font, const char* text, SDL_Color fg, Uint32 wrapLength) { return TTF_RenderUTF8_Blended_Wrapped(font, text, fg, wrapLength); }
	export inline SDL_Surface* textRenderUTF8Shaded(TTF_Font* font, const char* text, SDL_Color fg, SDL_Color bg) { return TTF_RenderUTF8_Shaded(font, text, fg, bg); }
	export inline SDL_Surface* textRenderUTF8Solid(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderUTF8_Solid(font, text, fg); }

	/* Window functions */
	export inline const char* windowGetTitle(Window* window) { return SDL_GetWindowTitle(window); }
	export inline float windowGetOpacity(Window* window) { return SDL_GetWindowOpacity(window); }
	export inline int windowSetFullscreen(Window* window, Uint32 flags) { return SDL_SetWindowFullscreen(window, flags); }
	export inline int windowUpdateSurface(Window* window) { return SDL_UpdateWindowSurface(window); }
	export inline SDL_bool windowGetMouseGrab(Window* window) { return SDL_GetWindowMouseGrab(window); }
	export inline SDL_Renderer* windowCreateRenderer(Window* window) { return SDL_CreateRenderer(window, nullptr); }
	export inline SDL_Surface* windowGetSurface(Window* window) { return SDL_GetWindowSurface(window); }
	export inline SDL_Window* windowCreate(const char* title, int w, int h, SDL_WindowFlags flags) { return SDL_CreateWindow(title, w, h, flags); }
	export inline Uint32 windowGetFlags(Window* window) { return SDL_GetWindowFlags(window); }
	export inline void windowDestroy(Window* window) { SDL_DestroyWindow(window); }
	export inline void windowGetPosition(Window* window, int* x, int* y) { SDL_GetWindowPosition(window, x, y); }
	export inline void windowGetSize(Window* window, int* w, int* h) { SDL_GetWindowSize(window, w, h); }
	export inline void windowHide(Window* window) { SDL_HideWindow(window); }
	export inline void windowMaximize(Window* window) { SDL_MaximizeWindow(window); }
	export inline void windowMinimize(Window* window) { SDL_MinimizeWindow(window); }
	export inline void windowRaise(Window* window) { SDL_RaiseWindow(window); }
	export inline void windowRestore(Window* window) { SDL_RestoreWindow(window); }
	export inline void windowSetIcon(Window* window, SDL_Surface* icon) { SDL_SetWindowIcon(window, icon); }
	export inline void windowSetModalFor(SDL_Window* modal_window, SDL_Window* parent_window) { SDL_SetWindowModalFor(modal_window, parent_window); }
	export inline void windowSetMouseGrab(Window* window, SDL_bool grabbed) { SDL_SetWindowMouseGrab(window, grabbed); }
	export inline void windowSetOpacity(Window* window, float opacity) { SDL_SetWindowOpacity(window, opacity); }
	export inline void windowSetPosition(Window* window, int x, int y) { SDL_SetWindowPosition(window, x, y); }
	export inline void windowSetSize(Window* window, int w, int h) {SDL_SetWindowSize(window, w, h);}
	export inline void windowSetTitle(Window* window, const char* title) { SDL_SetWindowTitle(window, title); }
	export inline void windowShow(Window* window) { SDL_ShowWindow(window); }

	/* Misc functions */
	export inline const char* __cdecl getError() { return TTF_GetError(); }
	export inline SDL_Color toTextColor(const Color& c) {
		return {
			static_cast<Uint8>(255 * c.r),
			static_cast<Uint8>(255 * c.g),
			static_cast<Uint8>(255 * c.b),
			static_cast<Uint8>(255 * c.a),
		};
	}
	export inline void free(void* code) { SDL_free(code); }
	export template <typename... Args> inline void log(SDL_LogPriority priority, const char* message, const Args&... args) { SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message, args...); }
	export template <typename... Args> inline void log(SDL_LogPriority priority, std::string_view message, const Args&... args) { SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message.data(), args...); }
	export template <typename... Args> inline void logCritical(const char* message, const Args&... args) { log(SDL_LOG_PRIORITY_CRITICAL, message, args...); }
	export template <typename... Args> inline void logCritical(std::string_view message, const Args&... args) { log(SDL_LOG_PRIORITY_CRITICAL, message, args...); }
	export template <typename... Args> inline void logInfo(const char* message, const Args&... args) { log(SDL_LOG_PRIORITY_INFO, message, args...); }
	export template <typename... Args> inline void logInfo(std::string_view message, const Args&... args) { log(SDL_LOG_PRIORITY_INFO, message, args...); }
	export template <typename... Args> inline void logError(const char* message, const Args&... args) { log(SDL_LOG_PRIORITY_ERROR, message, args...); }
	export template <typename... Args> inline void logError(std::string_view message, const Args&... args) { log(SDL_LOG_PRIORITY_ERROR, message, args...); }
}