module;

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "SDL3_shadercross/SDL_shadercross.h"
#include "SDL3_ttf/SDL_ttf.h"

export module sdl.SDLBase;

import sdl.IKeyInputListener;
import std;

/* Operators */
export bool operator==(const SDL_FColor& lhs, const SDL_FColor& rhs) { return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a; }
export bool operator!=(const SDL_FColor& lhs, const SDL_FColor& rhs) { return !(lhs == rhs); }

namespace sdl {
	export using BlendMode = ::SDL_BlendMode;
	export using Color = ::SDL_FColor;
	export using Event = ::SDL_Event;
	export using FlipMode = ::SDL_FlipMode;
	export using Font = ::TTF_Font;
	export using Gamepad = ::SDL_Gamepad;
	export using GamepadButton = ::SDL_GamepadButton;
	export using GPUAtlasDrawSequence = ::TTF_GPUAtlasDrawSequence;
	export using GPUBlendFactor = ::SDL_GPUBlendFactor;
	export using GPUBlendOp = ::SDL_GPUBlendOp;
	export using GPUBuffer = ::SDL_GPUBuffer;
	export using GPUBufferBinding = ::SDL_GPUBufferBinding;
	export using GPUBufferLocation = ::SDL_GPUBufferLocation;
	export using GPUBufferRegion = ::SDL_GPUBufferRegion;
	export using GPUBufferUsageFlags = ::SDL_GPUBufferUsageFlags;
	export using GPUColorComponentFlags = ::SDL_GPUColorComponentFlags;
	export using GPUColorTargetDescription = ::SDL_GPUColorTargetDescription;
	export using GPUColorTargetInfo = ::SDL_GPUColorTargetInfo;
	export using GPUCommandBuffer = ::SDL_GPUCommandBuffer;
	export using GPUCompareOp = ::SDL_GPUCompareOp;
	export using GPUComputePass = ::SDL_GPUComputePass;
	export using GPUComputePipeline = ::SDL_GPUComputePipeline;
	export using GPUComputePipelineCreateInfo = ::SDL_GPUComputePipelineCreateInfo;
	export using GPUCopyPass = ::SDL_GPUCopyPass;
	export using GPUCubeMapFace = ::SDL_GPUCubeMapFace;
	export using GPUCullMode = ::SDL_GPUCullMode;
	export using GPUDepthStencilState = ::SDL_GPUDepthStencilState;
	export using GPUDepthStencilTargetnfo = ::SDL_GPUDepthStencilTargetInfo;
	export using GPUDevice = ::SDL_GPUDevice;
	export using GPUFence = ::SDL_GPUFence;
	export using GPUFillMode = ::SDL_GPUFillMode;
	export using GPUFilter = ::SDL_GPUFilter;
	export using GPUFrontFace = ::SDL_GPUFrontFace;
	export using GPUGraphicsPipeline = ::SDL_GPUGraphicsPipeline;
	export using GPUGraphicsPipelineCreateInfo = ::SDL_GPUGraphicsPipelineCreateInfo;
	export using GPUIndexedIndirectDrawCommand = ::SDL_GPUIndexedIndirectDrawCommand;
	export using GPUIndexElementSize = ::SDL_GPUIndexElementSize;
	export using GPUIndirectDispatchCommand = ::SDL_GPUIndirectDispatchCommand;
	export using GPUIndirectDrawCommand = ::SDL_GPUIndirectDrawCommand;
	export using GPULoadOp = ::SDL_GPULoadOp;
	export using GPUMultisampleState = ::SDL_GPUMultisampleState;
	export using GPUPresentMode = ::SDL_GPUPresentMode;
	export using GPUPrimitiveType = ::SDL_GPUPrimitiveType;
	export using GPURasterizerState = ::SDL_GPURasterizerState;
	export using GPURenderPass = ::SDL_GPURenderPass;
	export using GPUSampleCount = ::SDL_GPUSampleCount;
	export using GPUSampler = ::SDL_GPUSampler;
	export using GPUSamplerAddressMode = ::SDL_GPUSamplerAddressMode;
	export using GPUSamplerCreateInfo = ::SDL_GPUSamplerCreateInfo;
	export using GPUSamplerMipmapMode = ::SDL_GPUSamplerMipmapMode;
	export using GPUShader = ::SDL_GPUShader;
	export using GPUShaderCreateInfo = ::SDL_GPUShaderCreateInfo;
	export using GPUShaderFormat = ::SDL_GPUShaderFormat;
	export using GPUShaderStage = ::SDL_GPUShaderStage;
	export using GPUStencilOp = ::SDL_GPUStencilOp;
	export using GPUStencilOpState = ::SDL_GPUStencilOpState;
	export using GPUStorageBufferReadWriteBinding = ::SDL_GPUStorageBufferReadWriteBinding;
	export using GPUStorageTextureReadWriteBinding = ::SDL_GPUStorageTextureReadWriteBinding;
	export using GPUStoreOp = ::SDL_GPUStoreOp;
	export using GPUSwapchainComposition = ::SDL_GPUSwapchainComposition;
	export using GPUTexture = ::SDL_GPUTexture;
	export using GPUTextureCreateInfo = ::SDL_GPUTextureCreateInfo;
	export using GPUTextureFormat = ::SDL_GPUTextureFormat;
	export using GPUTextureLocation = ::SDL_GPUTextureLocation;
	export using GPUTextureRegion = ::SDL_GPUTextureRegion;
	export using GPUTextureSamplerBinding = ::SDL_GPUTextureSamplerBinding;
	export using GPUTextureTransferInfo = ::SDL_GPUTextureTransferInfo;
	export using GPUTextureType = ::SDL_GPUTextureType;
	export using GPUTextureUsageFlags = ::SDL_GPUTextureUsageFlags;
	export using GPUTransferBuffer = ::SDL_GPUTransferBuffer;
	export using GPUTransferBufferLocation = ::SDL_GPUTransferBufferLocation;
	export using GPUTransferBufferUsage = ::SDL_GPUTransferBufferUsage;
	export using GPUVertexAttribute = ::SDL_GPUVertexAttribute;
	export using GPUVertexBufferDescription = ::SDL_GPUVertexBufferDescription;
	export using GPUVertexElementFormat = ::SDL_GPUVertexElementFormat;
	export using GPUVertexInputRate = ::SDL_GPUVertexInputRate;
	export using GPUVertexInputState = ::SDL_GPUVertexInputState;
	export using GPUViewport = ::SDL_GPUViewport;
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
	export using ShadercrossComputeMetadata = ::SDL_ShaderCross_ComputePipelineMetadata;
	export using ShadercrossGraphicsMetadata = ::SDL_ShaderCross_GraphicsShaderMetadata;
	export using ShadercrossHLSLInfo = ::SDL_ShaderCross_HLSL_Info;
	export using ShadercrossShaderStage = ::SDL_ShaderCross_ShaderStage;
	export using ShadercrossSPIRVInfo = ::SDL_ShaderCross_SPIRV_Info;
	export using Sound = ::Mix_Chunk;
	export using Surface = ::SDL_Surface;
	export using Text = ::TTF_Text;
	export using Window = ::SDL_Window;
	export using ::Sint32;
	export using ::Sint64;
	export using ::Sint8;
	export using ::Uint32;
	export using ::Uint64;
	export using ::Uint8;

	export enum RenderMode {
		NORMAL,
		OVERLAY,
		GRAYSCALE
	};

	export struct Matrix4x4 {
		float m11, m12, m13, m14;
		float m21, m22, m23, m24;
		float m31, m32, m33, m34;
		float m41, m42, m43, m44;
	};

	export struct TexCoord {
		float x1, x2;
		float y1, y2;
		float w1, w2;
		float h1, h2;
	};

	export struct TexProps {
		int texInd;
		TexCoord coord;
		Color color;
		Matrix4x4 transform;
	};

	/* Color constants. RGB can be higher than 1 to make the image brighter */
	export constexpr Color COLOR_BLACK = {0, 0, 0, 1};
	export constexpr Color COLOR_BLACK_SHADOW = {0, 0, 0, 0.4f};
	export constexpr Color COLOR_GOLD = {1.0, 0.843, 0, 1};
	export constexpr Color COLOR_GRAY = {0.5f, 0.5f, 0.5f, 1};
	export constexpr Color COLOR_HIGHLIGHT_BLUE = {0.5f, 0.66f, 1.5f, 1};
	export constexpr Color COLOR_HIGHLIGHT_BLUE_LIGHT = {0.8f, 0.96f, 1.7f, 1};
	export constexpr Color COLOR_HIGHLIGHT_GREEN = {0.66f, 1.5f, 0.5f, 1};
	export constexpr Color COLOR_HIGHLIGHT_GREEN_LIGHT = {0.96f, 1.7f, 0.8f, 1};
	export constexpr Color COLOR_HIGHLIGHT_RED = {1.5f, 0.5f, 0.6f, 1};
	export constexpr Color COLOR_HIGHLIGHT_RED_LIGHT = {1.7f, 0.8f, 0.9f, 1};
	export constexpr Color COLOR_LIME = {0.6f, 1.5f, 0.84f, 1};
	export constexpr Color COLOR_SKY = {0.6f, 1.1, 1.5f, 1};
	export constexpr Color COLOR_STANDARD = {1, 1, 1, 1};
	export constexpr Color COLOR_WHITE = {2, 2, 2, 1};

	/* Scan constants (used for hotkeys) */
	export constexpr Scancode SCAN_BACKSPACE = SDL_SCANCODE_BACKSPACE;
	export constexpr Scancode SCAN_DOWN = SDL_SCANCODE_DOWN;
	export constexpr Scancode SCAN_ENTER = SDL_SCANCODE_KP_ENTER;
	export constexpr Scancode SCAN_ESC = SDL_SCANCODE_ESCAPE;
	export constexpr Scancode SCAN_LEFT = SDL_SCANCODE_LEFT;
	export constexpr Scancode SCAN_RETURN = SDL_SCANCODE_RETURN;
	export constexpr Scancode SCAN_RIGHT = SDL_SCANCODE_RIGHT;
	export constexpr Scancode SCAN_UP = SDL_SCANCODE_UP;

	/* Shader Stage */
	export constexpr ShadercrossShaderStage STAGE_FRAGMENT = SDL_SHADERCROSS_SHADERSTAGE_FRAGMENT;
	export constexpr ShadercrossShaderStage STAGE_VERTEX = SDL_SHADERCROSS_SHADERSTAGE_VERTEX;

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
	export constexpr Uint64 NANOS_PER_SECOND = 1000000000ULL;

	// TODO get rid of SDL wrappers, this is not good form

	/* Directory stuff */
	export inline const char* dirBase() noexcept { return SDL_GetBasePath(); }
	export inline char* dirPref(const char* org, const char* app) { return SDL_GetPrefPath(org, app); }

	export inline void dirSelect() {
		//return SDL_ShowOpenFolderDialog();
	}

	/* File stuff */
	export inline void* fileLoad(const char* file, size_t* datasize) { return SDL_LoadFile(file, datasize); }

	/* Font management functions */
	export inline int fontAscent(TTF_Font* font) { return TTF_GetFontAscent(font); }
	export inline void fontClose(TTF_Font* font) { TTF_CloseFont(font); }
	export inline int fontDescent(TTF_Font* font) { return TTF_GetFontDescent(font); }
	export inline int fontIsFixedWidth(TTF_Font* font) { return TTF_FontIsFixedWidth(font); }
	export inline int fontGlyphMetrics(TTF_Font* font, Uint16 ch, int* minx, int* maxx, int* miny, int* maxy, int* advance) { return TTF_GetGlyphMetrics(font, ch, minx, maxx, miny, maxy, advance); }
	export inline int fontHasGlyph(TTF_Font* font, Uint16 ch) { return TTF_FontHasGlyph(font, ch); }
	export inline int fontHeight(TTF_Font* font) { return TTF_GetFontHeight(font); }
	export inline int fontHintingGet(TTF_Font* font) { return TTF_GetFontHinting(font); }
	export inline void fontHintingSet(TTF_Font* font, TTF_HintingFlags hinting) { TTF_SetFontHinting(font, hinting); }
	export inline int fontKerningGet(TTF_Font* font) { return TTF_GetFontKerning(font); }
	export inline void fontKerningSet(TTF_Font* font, int allowed) { TTF_SetFontKerning(font, allowed); }
	export inline int fontLineSkipGet(TTF_Font* font) { return TTF_GetFontLineSkip(font); }
	export inline TTF_Font* fontOpen(const char* file, int ptsize) { return TTF_OpenFont(file, ptsize); }
	export inline TTF_Font* fontOpenIO(SDL_IOStream* src, int closeio, int ptsize) { return TTF_OpenFontIO(src, closeio, ptsize); }
	export inline int fontOutlineGet(TTF_Font* font) { return TTF_GetFontOutline(font); }
	export inline void fontOutlineSet(TTF_Font* font, int outline) { TTF_SetFontOutline(font, outline); }
	export inline int fontSizeText(TTF_Font* font, const char* text, int* w, int* h) { return TTF_GetStringSize(font, text, 0, w, h); }
	export inline int fontStyleIsSet(TTF_Font* font, int style) { return TTF_GetFontStyle(font) & style; }
	export inline void fontStyleSet(TTF_Font* font, int style) { TTF_SetFontStyle(font, style); }

	/* GPU functions */
	export inline bool gpuClaimWindow(SDL_GPUDevice* device, SDL_Window* window) { return SDL_ClaimWindowForGPUDevice(device, window); }
	export inline bool gpuIsTextureFormatSupported(SDL_GPUDevice* device, SDL_GPUTextureFormat format, SDL_GPUTextureType type, SDL_GPUTextureUsageFlags usage) { return SDL_GPUTextureSupportsFormat(device, format, type, usage); }
	export inline bool gpuQueryFence(SDL_GPUDevice* device, SDL_GPUFence* fence) { return SDL_QueryGPUFence(device, fence); }
	export inline bool gpuSetSwapchainParameters(SDL_GPUDevice* device, SDL_Window* window, SDL_GPUSwapchainComposition swapchainComposition, SDL_GPUPresentMode presentMode) { return SDL_SetGPUSwapchainParameters(device, window, swapchainComposition, presentMode); }
	export inline bool gpuSupportsPresentMode(SDL_GPUDevice* device, SDL_Window* window, SDL_GPUPresentMode presentMode) { return SDL_WindowSupportsGPUPresentMode(device, window, presentMode); }
	export inline bool gpuSupportsSwapchainComposition(SDL_GPUDevice* device, SDL_Window* window, SDL_GPUSwapchainComposition swapchainComposition) { return SDL_WindowSupportsGPUSwapchainComposition(device, window, swapchainComposition); }
	export inline bool gpuTextureSupportsSampleCount(SDL_GPUDevice* device, SDL_GPUTextureFormat format, SDL_GPUSampleCount desiredSampleCount) { return SDL_GPUTextureSupportsSampleCount(device, format, desiredSampleCount); }

	export inline SDL_GPUBuffer* gpuCreateBuffer(SDL_GPUDevice* device, SDL_GPUBufferUsageFlags usageFlags, Uint32 sizeInBytes) {
		SDL_GPUBufferCreateInfo info = {usageFlags, sizeInBytes};
		return SDL_CreateGPUBuffer(device, &info);
	}

	export inline const char* gpuGetDriver(int index) { return SDL_GetGPUDriver(index); }
	export inline SDL_GPUCommandBuffer* gpuAcquireCommandBuffer(SDL_GPUDevice* device) { return SDL_AcquireGPUCommandBuffer(device); }

	export inline SDL_GPUComputePass* gpuBeginComputePass(SDL_GPUCommandBuffer* commandBuffer, SDL_GPUStorageTextureReadWriteBinding* storageTextureBindings, Uint32 storageTextureBindingCount, SDL_GPUStorageBufferReadWriteBinding* storageBufferBindings, Uint32 storageBufferBindingCount) {
		return SDL_BeginGPUComputePass(commandBuffer, storageTextureBindings, storageTextureBindingCount, storageBufferBindings, storageBufferBindingCount);
	}

	export inline SDL_GPUComputePipeline* gpuCreateComputePipeline(SDL_GPUDevice* device, SDL_GPUComputePipelineCreateInfo* computePipelineCreateInfo) { return SDL_CreateGPUComputePipeline(device, computePipelineCreateInfo); }
	export inline SDL_GPUComputePipeline* gpuCompileHLSLCompute(SDL_GPUDevice* device, const SDL_ShaderCross_HLSL_Info* info, SDL_ShaderCross_ComputePipelineMetadata* metadata) { return SDL_ShaderCross_CompileComputePipelineFromHLSL(device, info, metadata); }
	export inline SDL_GPUComputePipeline* gpuCompileSPIRVCompute(SDL_GPUDevice* device, const SDL_ShaderCross_SPIRV_Info* info, SDL_ShaderCross_ComputePipelineMetadata* metadata) { return SDL_ShaderCross_CompileComputePipelineFromSPIRV(device, info, metadata); }
	export inline SDL_GPUCopyPass* gpuBeginCopyPass(SDL_GPUCommandBuffer* commandBuffer) { return SDL_BeginGPUCopyPass(commandBuffer); }
	export inline SDL_GPUDevice* gpuCreateDevice(SDL_GPUShaderFormat format_flags, bool debug_mode, const char* name) { return SDL_CreateGPUDevice(format_flags, debug_mode, name); }
	export inline SDL_GPUDevice* gpuCreateDeviceWithProperties(SDL_PropertiesID props) { return SDL_CreateGPUDeviceWithProperties(props); }
	export inline SDL_GPUFence* gpuSubmitAndAcquireFence(SDL_GPUCommandBuffer* commandBuffer) { return SDL_SubmitGPUCommandBufferAndAcquireFence(commandBuffer); }
	export inline SDL_GPUGraphicsPipeline* gpuCreateGraphicsPipeline(SDL_GPUDevice* device, SDL_GPUGraphicsPipelineCreateInfo* pipelineCreateInfo) { return SDL_CreateGPUGraphicsPipeline(device, pipelineCreateInfo); }
	export inline SDL_GPURenderPass* gpuBeginRenderPass(SDL_GPUCommandBuffer* commandBuffer, SDL_GPUColorTargetInfo* colorAttachmentInfos, Uint32 colorAttachmentCount, SDL_GPUDepthStencilTargetInfo* depthStencilAttachmentInfo) { return SDL_BeginGPURenderPass(commandBuffer, colorAttachmentInfos, colorAttachmentCount, depthStencilAttachmentInfo); }
	export inline SDL_GPUSampler* gpuCreateSampler(SDL_GPUDevice* device, SDL_GPUSamplerCreateInfo* samplerCreateInfo) { return SDL_CreateGPUSampler(device, samplerCreateInfo); }
	export inline SDL_GPUShader* gpuCompileHLSLShader(SDL_GPUDevice* device, const SDL_ShaderCross_HLSL_Info* info, SDL_ShaderCross_GraphicsShaderMetadata* metadata) { return SDL_ShaderCross_CompileGraphicsShaderFromHLSL(device, info, metadata); }
	export inline SDL_GPUShader* gpuCompileSPIRVShader(SDL_GPUDevice* device, const SDL_ShaderCross_SPIRV_Info* info, SDL_ShaderCross_GraphicsShaderMetadata* metadata) { return SDL_ShaderCross_CompileGraphicsShaderFromSPIRV(device, info, metadata); }
	export inline SDL_GPUShader* gpuCreateShader(SDL_GPUDevice* device, SDL_GPUShaderCreateInfo* shaderCreateInfo) { return SDL_CreateGPUShader(device, shaderCreateInfo); }
	export inline SDL_GPUShaderFormat gpuGetHLSLShaderFormats() { return SDL_ShaderCross_GetHLSLShaderFormats(); }
	export inline SDL_GPUShaderFormat gpuGetSPIRVShaderFormats() { return SDL_ShaderCross_GetSPIRVShaderFormats(); }

	export inline SDL_GPUTexture* gpuAcquireSwapchainTexture(SDL_GPUCommandBuffer* commandBuffer, SDL_Window* window, Uint32* pWidth, Uint32* pHeight) {
		SDL_GPUTexture* texture;
		if (!SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window, &texture, pWidth, pHeight)) {
			SDL_Log("WaitAndAcquireGPUSwapchainTexture failed: %s", SDL_GetError());
		}
		return texture;
	}

	export inline SDL_GPUTexture* gpuCreateTexture(SDL_GPUDevice* device, SDL_GPUTextureCreateInfo* textureCreateInfo) { return SDL_CreateGPUTexture(device, textureCreateInfo); }
	export inline SDL_GPUTextureFormat gpuGetSwapchainTextureFormat(SDL_GPUDevice* device, SDL_Window* window) { return SDL_GetGPUSwapchainTextureFormat(device, window); }

	export inline SDL_GPUTransferBuffer* gpuCreateTransferBuffer(SDL_GPUDevice* device, SDL_GPUTransferBufferUsage usage, Uint32 sizeInBytes) {
		SDL_GPUTransferBufferCreateInfo info = {usage, sizeInBytes};
		return SDL_CreateGPUTransferBuffer(device, &info);
	}

	export inline Uint32 gpuTextureFormatTexelBlockSize(SDL_GPUTextureFormat textureFormat) { return SDL_GPUTextureFormatTexelBlockSize(textureFormat); }
	export inline void gpuBindComputePipeline(SDL_GPUComputePass* computePass, SDL_GPUComputePipeline* computePipeline) { SDL_BindGPUComputePipeline(computePass, computePipeline); }
	export inline void gpuBindComputeStorageBuffers(SDL_GPUComputePass* computePass, Uint32 firstSlot, SDL_GPUBuffer** storageBuffers, Uint32 bindingCount) { SDL_BindGPUComputeStorageBuffers(computePass, firstSlot, storageBuffers, bindingCount); }
	export inline void gpuBindComputeStorageTextures(SDL_GPUComputePass* computePass, Uint32 firstSlot, SDL_GPUTexture* const* storageTextureSlices, Uint32 bindingCount) { SDL_BindGPUComputeStorageTextures(computePass, firstSlot, storageTextureSlices, bindingCount); }
	export inline void gpuBindFragmentSamplers(SDL_GPURenderPass* renderPass, Uint32 firstSlot, SDL_GPUTextureSamplerBinding* textureSamplerBindings, Uint32 bindingCount) { SDL_BindGPUFragmentSamplers(renderPass, firstSlot, textureSamplerBindings, bindingCount); }
	export inline void gpuBindFragmentStorageBuffers(SDL_GPURenderPass* renderPass, Uint32 firstSlot, SDL_GPUBuffer** storageBuffers, Uint32 bindingCount) { SDL_BindGPUFragmentStorageBuffers(renderPass, firstSlot, storageBuffers, bindingCount); }
	export inline void gpuBindFragmentStorageTextures(SDL_GPURenderPass* renderPass, Uint32 firstSlot, SDL_GPUTexture* const* storageTextureSlices, Uint32 bindingCount) { SDL_BindGPUFragmentStorageTextures(renderPass, firstSlot, storageTextureSlices, bindingCount); }
	export inline void gpuBindGraphicsPipeline(SDL_GPURenderPass* renderPass, SDL_GPUGraphicsPipeline* graphicsPipeline) { SDL_BindGPUGraphicsPipeline(renderPass, graphicsPipeline); }
	export inline void gpuBindIndexBuffer(SDL_GPURenderPass* renderPass, SDL_GPUBufferBinding* pBinding, SDL_GPUIndexElementSize indexElementSize) { SDL_BindGPUIndexBuffer(renderPass, pBinding, indexElementSize); }
	export inline void gpuBindVertexBuffers(SDL_GPURenderPass* renderPass, Uint32 firstBinding, SDL_GPUBufferBinding* pBindings, Uint32 bindingCount) { SDL_BindGPUVertexBuffers(renderPass, firstBinding, pBindings, bindingCount); }
	export inline void gpuBindVertexSamplers(SDL_GPURenderPass* renderPass, Uint32 firstSlot, SDL_GPUTextureSamplerBinding* textureSamplerBindings, Uint32 bindingCount) { SDL_BindGPUVertexSamplers(renderPass, firstSlot, textureSamplerBindings, bindingCount); }
	export inline void gpuBindVertexStorageBuffers(SDL_GPURenderPass* renderPass, Uint32 firstSlot, SDL_GPUBuffer** storageBuffers, Uint32 bindingCount) { SDL_BindGPUVertexStorageBuffers(renderPass, firstSlot, storageBuffers, bindingCount); }
	export inline void gpuBindVertexStorageTextures(SDL_GPURenderPass* renderPass, Uint32 firstSlot, SDL_GPUTexture* const* storageTextureSlices, Uint32 bindingCount) { SDL_BindGPUVertexStorageTextures(renderPass, firstSlot, storageTextureSlices, bindingCount); }
	export inline void gpuBlit(SDL_GPUCommandBuffer* commandBuffer, SDL_GPUBlitInfo* info) { SDL_BlitGPUTexture(commandBuffer, info); }
	export inline void gpuCopyBufferToBuffer(SDL_GPUCopyPass* copyPass, SDL_GPUBufferLocation* source, SDL_GPUBufferLocation* destination, Uint32 size, bool cycle) { SDL_CopyGPUBufferToBuffer(copyPass, source, destination, size, cycle); }
	export inline void gpuCopyTextureToTexture(SDL_GPUCopyPass* copyPass, SDL_GPUTextureLocation* source, SDL_GPUTextureLocation* destination, Uint32 w, Uint32 h, Uint32 d, bool cycle) { SDL_CopyGPUTextureToTexture(copyPass, source, destination, w, h, d, cycle); }
	export inline void gpuDispatchCompute(SDL_GPUComputePass* computePass, Uint32 groupCountX, Uint32 groupCountY, Uint32 groupCountZ) { SDL_DispatchGPUCompute(computePass, groupCountX, groupCountY, groupCountZ); }
	export inline void gpuDispatchComputeIndirect(SDL_GPUComputePass* computePass, SDL_GPUBuffer* buffer, Uint32 offsetInBytes) { SDL_DispatchGPUComputeIndirect(computePass, buffer, offsetInBytes); }
	export inline void gpuDownloadFromBuffer(SDL_GPUCopyPass* copyPass, SDL_GPUBufferRegion* source, SDL_GPUTransferBufferLocation* destination) { SDL_DownloadFromGPUBuffer(copyPass, source, destination); }
	export inline void gpuDownloadFromTexture(SDL_GPUCopyPass* copyPass, SDL_GPUTextureRegion* source, SDL_GPUTextureTransferInfo* destination) { SDL_DownloadFromGPUTexture(copyPass, source, destination); }
	export inline void gpuDrawGpuPrimitives(SDL_GPURenderPass* renderPass, Uint32 num_vertices, Uint32 num_instances, Uint32 first_vertex, Uint32 first_instance) { SDL_DrawGPUPrimitives(renderPass, num_vertices, num_instances, first_vertex, first_instance); }
	export inline void gpuDrawIndexedPrimitives(SDL_GPURenderPass* renderPass, Uint32 num_indices, Uint32 num_instances, Uint32 first_index, Sint32 vertex_offset, Uint32 first_instance) { SDL_DrawGPUIndexedPrimitives(renderPass, num_indices, num_instances, first_index, vertex_offset, first_instance); }
	export inline void gpuDrawIndexedPrimitivesIndirect(SDL_GPURenderPass* renderPass, SDL_GPUBuffer* buffer, Uint32 offsetInBytes, Uint32 drawCount) { SDL_DrawGPUIndexedPrimitivesIndirect(renderPass, buffer, offsetInBytes, drawCount); }
	export inline void gpuDrawPrimitives(SDL_GPURenderPass* renderPass, Uint32 num_vertices, Uint32 num_instances, Uint32 first_vertex, Uint32 first_instance) { SDL_DrawGPUPrimitives(renderPass, num_vertices, num_instances, first_vertex, first_instance); }
	export inline void gpuDrawPrimitivesIndirect(SDL_GPURenderPass* renderPass, SDL_GPUBuffer* buffer, Uint32 offsetInBytes, Uint32 drawCount) { SDL_DrawGPUPrimitivesIndirect(renderPass, buffer, offsetInBytes, drawCount); }
	export inline void gpuEndComputePass(SDL_GPUComputePass* computePass) { SDL_EndGPUComputePass(computePass); }
	export inline void gpuEndCopyPass(SDL_GPUCopyPass* copyPass) { SDL_EndGPUCopyPass(copyPass); }
	export inline void gpuEndRenderPass(SDL_GPURenderPass* renderPass) { SDL_EndGPURenderPass(renderPass); }
	export inline void gpuGenerateMipmaps(SDL_GPUCommandBuffer* commandBuffer, SDL_GPUTexture* texture) { SDL_GenerateMipmapsForGPUTexture(commandBuffer, texture); }
	export inline void gpuInsertDebugLabel(SDL_GPUCommandBuffer* commandBuffer, const char* text) { SDL_InsertGPUDebugLabel(commandBuffer, text); }
	export inline void gpuPopDebugGroup(SDL_GPUCommandBuffer* commandBuffer) { SDL_PopGPUDebugGroup(commandBuffer); }
	export inline void gpuPushComputeUniformData(SDL_GPUCommandBuffer* commandBuffer, Uint32 slotIndex, const void* data, Uint32 dataLengthInBytes) { SDL_PushGPUComputeUniformData(commandBuffer, slotIndex, data, dataLengthInBytes); }
	export inline void gpuPushDebugGroup(SDL_GPUCommandBuffer* commandBuffer, const char* name) { SDL_PushGPUDebugGroup(commandBuffer, name); }
	export inline void gpuPushFragmentUniformData(SDL_GPUCommandBuffer* commandBuffer, Uint32 slotIndex, const void* data, Uint32 dataLengthInBytes) { SDL_PushGPUFragmentUniformData(commandBuffer, slotIndex, data, dataLengthInBytes); }
	export inline void gpuPushVertexUniformData(SDL_GPUCommandBuffer* commandBuffer, Uint32 slotIndex, const void* data, Uint32 dataLengthInBytes) { SDL_PushGPUVertexUniformData(commandBuffer, slotIndex, data, dataLengthInBytes); }
	export inline void gpuReleaseBuffer(SDL_GPUDevice* device, SDL_GPUBuffer* buffer) { SDL_ReleaseGPUBuffer(device, buffer); }
	export inline void gpuReleaseComputePipeline(SDL_GPUDevice* device, SDL_GPUComputePipeline* computePipeline) { SDL_ReleaseGPUComputePipeline(device, computePipeline); }
	export inline void gpuReleaseFence(SDL_GPUDevice* device, SDL_GPUFence* fence) { SDL_ReleaseGPUFence(device, fence); }
	export inline void gpuReleaseGraphicsPipeline(SDL_GPUDevice* device, SDL_GPUGraphicsPipeline* graphicsPipeline) { SDL_ReleaseGPUGraphicsPipeline(device, graphicsPipeline); }
	export inline void gpuReleaseSampler(SDL_GPUDevice* device, SDL_GPUSampler* sampler) { SDL_ReleaseGPUSampler(device, sampler); }
	export inline void gpuReleaseShader(SDL_GPUDevice* device, SDL_GPUShader* shader) { SDL_ReleaseGPUShader(device, shader); }
	export inline void gpuReleaseTexture(SDL_GPUDevice* device, SDL_GPUTexture* texture) { SDL_ReleaseGPUTexture(device, texture); }
	export inline void gpuReleaseTransferBuffer(SDL_GPUDevice* device, SDL_GPUTransferBuffer* transferBuffer) { SDL_ReleaseGPUTransferBuffer(device, transferBuffer); }
	export inline void gpuSetBufferName(SDL_GPUDevice* device, SDL_GPUBuffer* buffer, const char* text) { SDL_SetGPUBufferName(device, buffer, text); }
	export inline void gpuSetScissor(SDL_GPURenderPass* renderPass, RectI* scissor) { SDL_SetGPUScissor(renderPass, scissor); }
	export inline void gpuSetTextureName(SDL_GPUDevice* device, SDL_GPUTexture* texture, const char* text) { SDL_SetGPUTextureName(device, texture, text); }
	export inline void gpuSetViewport(SDL_GPURenderPass* renderPass, SDL_GPUViewport* viewport) { SDL_SetGPUViewport(renderPass, viewport); }
	export inline void gpuSubmit(SDL_GPUCommandBuffer* commandBuffer) { SDL_SubmitGPUCommandBuffer(commandBuffer); }
	export inline void gpuUnclaimWindow(SDL_GPUDevice* device, SDL_Window* window) { SDL_ReleaseWindowFromGPUDevice(device, window); }
	export inline void gpuUnmapTransferBuffer(SDL_GPUDevice* device, SDL_GPUTransferBuffer* transferBuffer) { SDL_UnmapGPUTransferBuffer(device, transferBuffer); }
	export inline void gpuUploadToBuffer(SDL_GPUCopyPass* copyPass, SDL_GPUTransferBufferLocation* source, SDL_GPUBufferRegion* destination, bool cycle = false) { SDL_UploadToGPUBuffer(copyPass, source, destination, cycle); }
	export inline void gpuUploadToTexture(SDL_GPUCopyPass* copyPass, SDL_GPUTextureTransferInfo* source, SDL_GPUTextureRegion* destination, bool cycle = false) { SDL_UploadToGPUTexture(copyPass, source, destination, cycle); }
	export inline void gpuWait(SDL_GPUDevice* device) { SDL_WaitForGPUIdle(device); }
	export inline void gpuWaitForFences(SDL_GPUDevice* device, bool waitAll, SDL_GPUFence** pFences, Uint32 fenceCount) { SDL_WaitForGPUFences(device, waitAll, pFences, fenceCount); }
	export inline void* gpuMapTransferBuffer(SDL_GPUDevice* device, SDL_GPUTransferBuffer* transferBuffer, bool cycle) { return SDL_MapGPUTransferBuffer(device, transferBuffer, cycle); }

	/* Music management functions */
	export double musicGetPosition(Mix_Music* music) { return Mix_GetMusicPosition(music); }
	export inline int musicFadeOut(int ms) { return Mix_FadeOutMusic(ms); }
	export inline int musicGetVolume() { return Mix_VolumeMusic(-1); }
	export inline int musicIsPaused() { return Mix_PausedMusic(); }
	export inline int musicPlay(Mix_Music* music, int loops = -1) { return Mix_PlayMusic(music, loops); }
	export inline int musicPlayFade(Mix_Music* music, int fade, int loops = -1) { return Mix_FadeInMusic(music, loops, fade); }
	export inline int musicSetPosition(double position) { return Mix_SetMusicPosition(position); }
	export inline Mix_Music* musicLoad(const char* path) { return Mix_LoadMUS(path); }
	export inline void musicFree(Mix_Music* music) { Mix_FreeMusic(music); }
	export inline void musicHalt() { return Mix_HaltMusic(); }
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
	export inline int surfaceSetColorKey(SDL_Surface* surface, bool enabled, Uint32 key) { return SDL_SetSurfaceColorKey(surface, enabled, key); }
	export inline int surfaceSetPalette(SDL_Surface* surface, SDL_Palette* palette) { return SDL_SetSurfacePalette(surface, palette); }
	export inline SDL_Surface* surfaceConvert(SDL_Surface* surface, SDL_PixelFormat pixel_format) { return SDL_ConvertSurface(surface, pixel_format); }
	export inline SDL_Surface* surfaceCopy(SDL_Surface* src) { return SDL_DuplicateSurface(src); }
	export inline SDL_Surface* surfaceCreate(int width, int height, SDL_PixelFormat format) { return SDL_CreateSurface(width, height, format); }
	export inline SDL_Surface* surfaceCreate(int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateSurface(width, height, SDL_GetPixelFormatForMasks(depth, Rmask, Gmask, Bmask, Amask)); }
	export inline SDL_Surface* surfaceCreateFrom(void* pixels, int width, int height, int pitch, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateSurfaceFrom(width, height, SDL_GetPixelFormatForMasks(depth, Rmask, Gmask, Bmask, Amask), pixels, pitch); }
	export inline SDL_Surface* surfaceLoad(const char* file) { return IMG_Load(file); }
	export inline SDL_Surface* surfaceLoad(std::string_view file) { return IMG_Load(file.data()); }
	export inline void surfaceDestroy(SDL_Surface* surface) { SDL_DestroySurface(surface); }
	export inline void surfaceUnlock(SDL_Surface* surface) { SDL_UnlockSurface(surface); }

	/* Sound management functions */
	export inline int soundChannelPaused(int channel) { return Mix_Paused(channel); }
	export inline int soundExpireChannel(int channel, int ticks) { return Mix_ExpireChannel(channel, ticks); }
	export inline int soundFadeOutChannel(int channel, int ms) { return Mix_FadeOutChannel(channel, ms); }
	export inline int soundGetChannelVolume(int channel) { return Mix_Volume(channel, -1); }
	export inline int soundPlay(Sound* sound, int loops = 0, int time = -1) { return Mix_PlayChannelTimed(-1, sound, loops, time); }
	export inline int soundPlayFade(Sound* sound, int fade, int loops = 0, int time = -1) { return Mix_FadeInChannelTimed(-1, sound, loops, fade, time); }
	export inline int soundReserveChannels(int num) { return Mix_ReserveChannels(num); }
	export inline int soundSetVolume(Sound* sound, int volume) { return Mix_VolumeChunk(sound, volume); }
	export inline Sound* soundGetChunk(int channel) { return Mix_GetChunk(channel); }
	export inline Sound* soundLoad(const char* path) { return Mix_LoadWAV(path); }
	export inline void soundFree(Sound* sound) { Mix_FreeChunk(sound); }
	export inline void soundHaltChannel(int channel) { return Mix_HaltChannel(channel); }
	export inline void soundPauseChannel(int channel) { Mix_Pause(channel); }
	export inline void soundResumeChannel(int channel) { Mix_Resume(channel); }

	export inline void soundSetAllVolume(int volume) {
		for (int i = 0; i < Mix_AllocateChannels(-1); ++i) {
			Mix_Volume(i, volume);
		}
	}

	/* Text rendering functions */
	export inline SDL_Surface* textGetGlyph(TTF_Font* font, Uint32 glyph_index, TTF_ImageType* image_type) { return TTF_GetGlyphImageForIndex(font, glyph_index, image_type); }
	export inline SDL_Surface* textRenderBlended(TTF_Font* font, const char* text, SDL_Color fg, size_t range = 0) { return TTF_RenderText_Blended(font, text, range, fg); }
	export inline SDL_Surface* textRenderBlendedWrapped(TTF_Font* font, const char* text, SDL_Color fg, Uint32 wrapLength, size_t range = 0) { return TTF_RenderText_Blended_Wrapped(font, text, range, fg, wrapLength); }
	export inline SDL_Surface* textRenderShaded(TTF_Font* font, const char* text, SDL_Color fg, SDL_Color bg, size_t range = 0) { return TTF_RenderText_Shaded(font, text, range, fg, bg); }
	export inline TTF_GPUAtlasDrawSequence* textGetSequence(TTF_Text* text) { return TTF_GetGPUTextDrawData(text); }
	export inline void textDestroy(TTF_Text* text) { TTF_DestroyText(text); }

	/* Window functions */
	export inline const char* windowGetTitle(Window* window) { return SDL_GetWindowTitle(window); }
	export inline float windowGetOpacity(Window* window) { return SDL_GetWindowOpacity(window); }
	export inline int windowSetFullscreen(Window* window, Uint32 flags) { return SDL_SetWindowFullscreen(window, flags); }
	export inline int windowUpdateSurface(Window* window) { return SDL_UpdateWindowSurface(window); }
	export inline bool windowGetMouseGrab(Window* window) { return SDL_GetWindowMouseGrab(window); }
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
	export inline void windowSetModal(SDL_Window* modal_window, SDL_Window* parent_window) { SDL_SetWindowModal(modal_window, parent_window); }
	export inline void windowSetMouseGrab(Window* window, bool grabbed) { SDL_SetWindowMouseGrab(window, grabbed); }
	export inline void windowSetOpacity(Window* window, float opacity) { SDL_SetWindowOpacity(window, opacity); }
	export inline void windowSetPosition(Window* window, int x, int y) { SDL_SetWindowPosition(window, x, y); }
	export inline void windowSetSize(Window* window, int w, int h) { SDL_SetWindowSize(window, w, h); }
	export inline void windowSetTitle(Window* window, const char* title) { SDL_SetWindowTitle(window, title); }
	export inline void windowShow(Window* window) { SDL_ShowWindow(window); }

	/* Misc functions */
	export inline const char* __cdecl getError() { return SDL_GetError(); }
	export inline constexpr float rads(float deg) { return deg * std::numbers::pi_v<float> / 180; }

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
