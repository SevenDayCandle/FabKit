module;

#include "SDL3/SDL.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "SDL3_shadercross/SDL_shadercross.h"
#include "SDL3_ttf/SDL_ttf.h"

export module sdl.SDLRunner;

import sdl.IKeyInputListener;
import sdl.SDLHelpers;
import std;

namespace sdl {
	constexpr auto SHADER_FILL_FRAG = "Shader/Fill.frag.hlsl";
	constexpr auto SHADER_FILL_VERT = "Shader/Fill.vert.hlsl";
	constexpr auto SHADER_NORMAL_FRAG = "Shader/Normal.frag.hlsl";
	constexpr auto SHADER_NORMAL_VERT = "Shader/Normal.vert.hlsl";

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
	SDL_Event e;
	SDL_Gamepad* gamepad;
	SDL_GPUBuffer* vertexBuffer;
	SDL_GPUDevice* device;
	SDL_GPUGraphicsPipeline* renderFill;
	SDL_GPUGraphicsPipeline* renderStandard;
	SDL_GPUSampler* sampler;
	SDL_GPUTransferBuffer* transferBuffer;
	std::vector<MIX_Mixer*> mixers;
	std::vector<MIX_Track*> tracks;
	TTF_TextEngine* textEngine;
	Uint64 delta;
	Uint64 fpsLimit;
	Uint64 timeCurrent;
	Uint64 timeLast;
	Uint8* keyJust;
	Uint8* padLast;
}

namespace sdl::runner {
	export constexpr int MAX_SPRITES = 131072;

	export constexpr int MIXER_SOUND = 0;
	export constexpr int MIXER_MUSIC = 1;

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
	export inline bool keyboardJustPressed(int pressed) { return key[pressed] && keyJust[pressed] && kListener == nullptr; } // Keyboard listeners should block regular keyboard input
	export inline bool keyboardJustPressedEnter() { return keyboardJustPressed(SDLK_KP_ENTER) || keyboardJustPressed(SDLK_RETURN); }
	export inline bool keyboardJustPressedEsc() { return keyboardJustPressed(SDLK_ESCAPE); }
	export inline bool keyboardPressed(int pressed) { return key[pressed] && kListener == nullptr; }
	export inline bool mouseIsHovering(const RectF& rect) { return mousePosX >= rect.x && mousePosY >= rect.y && mousePosX < rect.x + rect.w && mousePosY < rect.y + rect.h; }
	export inline bool mouseIsHovering(const RectI rect) { return mousePosX >= rect.x && mousePosY >= rect.y && mousePosX < rect.x + rect.w && mousePosY < rect.y + rect.h; }
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
		SDL_GPUBufferCreateInfo info = {usageFlags, sizeInBytes};
		return SDL_CreateGPUBuffer(device, &info);
	}

	export inline SDL_GPUBuffer* deviceCreateBufferIndex(Uint32 sizeInBytes) { return deviceCreateBuffer(SDL_GPU_BUFFERUSAGE_INDEX, sizeInBytes); }
	export inline SDL_GPUBuffer* deviceCreateBufferVertex(Uint32 sizeInBytes) { return deviceCreateBuffer(SDL_GPU_BUFFERUSAGE_VERTEX, sizeInBytes); }
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

	export inline TexProps* deviceMapTexTransferBuffer(bool cycle) { return static_cast<TexProps*>(SDL_MapGPUTransferBuffer(device, transferBuffer, cycle)); }
	export inline TTF_Text* textCreate(TTF_Font* font, std::string_view text) { return TTF_CreateText(textEngine, font, text.data(), text.length()); };
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
	export inline void deviceUnmapTexTransferBuffer() { SDL_UnmapGPUTransferBuffer(device, transferBuffer); }
	export inline void deviceUnmapTransferBuffer(SDL_GPUTransferBuffer* transferBuffer) { SDL_UnmapGPUTransferBuffer(device, transferBuffer); }
	export inline void deviceWait() { SDL_WaitForGPUIdle(device); }
	export inline void deviceWaitForFences(bool waitAll, SDL_GPUFence** pFences, Uint32 fenceCount) { SDL_WaitForGPUFences(device, waitAll, pFences, fenceCount); }
	export inline void setFPSLimit(int fps) { fpsLimit = fps > 0 ? NANOS_PER_SECOND / fps : 0; }
	export inline void* deviceMapTransferBuffer(SDL_GPUTransferBuffer* transferBuffer, bool cycle) { return SDL_MapGPUTransferBuffer(device, transferBuffer, cycle); }


	export bool init(const char* renderer = nullptr);
	export bool initRendering(const char* normalFrag = SHADER_NORMAL_FRAG, const char* normalVert = SHADER_NORMAL_VERT, const char* fillFrag = SHADER_FILL_FRAG, const char* fillVert = SHADER_FILL_VERT, const int maxSprites = MAX_SPRITES);
	export bool mixerSetGain(int index, float vol);
	export bool poll();
	export bool uploadVertexes(SDL_GPUCommandBuffer* cmd, SDL_GPUCopyPass* copyPass);
	export int registerMixer(SDL_AudioDeviceID devid = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, const SDL_AudioSpec* spec = nullptr);
	export MIX_Audio* mixerLoadAudio(int index, const char* path, bool predecode = false);
	export MIX_Track* requestTrack(int index);
	export SDL_GPUGraphicsPipeline* createPipeline(SDL_GPUShader* vertexShader, SDL_GPUShader* fragmentShader, SDL_GPUTextureFormat textureFormat = SDL_GPUTextureFormat::SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM, SDL_GPUBlendFactor srcColor = SDL_GPUBlendFactor::SDL_GPU_BLENDFACTOR_SRC_ALPHA,
	                                               SDL_GPUBlendFactor dstColor = SDL_GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
	                                               SDL_GPUBlendFactor srcAlpha = SDL_GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE, SDL_GPUBlendFactor dstAlpha = SDL_GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA);
	export SDL_GPUGraphicsPipeline* createShapePipeline(SDL_GPUShader* vertexShader, SDL_GPUShader* fragmentShader, SDL_GPUTextureFormat textureFormat = SDL_GPUTextureFormat::SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM, SDL_GPUBlendFactor srcColor = SDL_GPUBlendFactor::SDL_GPU_BLENDFACTOR_SRC_ALPHA,
	                                                    SDL_GPUBlendFactor dstColor = SDL_GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
	                                                    SDL_GPUBlendFactor srcAlpha = SDL_GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE, SDL_GPUBlendFactor dstAlpha = SDL_GPUBlendFactor::SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA);
	export SDL_GPUGraphicsPipeline* pipelineForMode(RenderMode mode);
	export SDL_GPUGraphicsPipeline* shapePipelineForMode(RenderMode mode);
	export SDL_GPUShader* loadShader(const char* shaderFilename, ::SDL_ShaderCross_ShaderStage stage, Uint32 samplerCount, Uint32 uniformBufferCount, Uint32 storageBufferCount = 0, Uint32 storageTextureCount = 0);
	export SDL_GPUTexture* createTextureArray(Uint32 w, Uint32 h, Uint32 maxLayers = 1024);
	export SDL_GPUTexture* uploadSingleTexture(SDL_GPUCopyPass* copyPass, Surface* surface);
	export SDL_GPUTexture* uploadSingleTexture(SDL_GPUCopyPass* copyPass, Surface* surface, SDL_GPUTransferBuffer* textureTransferBuffer);
	export SDL_GPUTexture* uploadTextureForArray(SDL_GPUCopyPass* copyPass, Surface* surface, SDL_GPUTexture* texture, SDL_GPUTransferBuffer* textureTransferBuffer, Uint32 layer);
	export void bindRenderBuffer(SDL_GPURenderPass* pass);
	export void bindTexture(SDL_GPURenderPass* pass, SDL_GPUTexture* texture);
	export void capFrame();
	export void keyboardInputStart(Window* window, IKeyInputListener* listener);
	export void keyboardInputStop(Window* window);
	export void keyboardInputStopRequest(Window* window, IKeyInputListener* listener);
	export void quit();
	export void uploadToVertexBuffer(SDL_GPUCommandBuffer* cmd, Uint32 size, Uint32 offset = 0);
}

/* IMPLEMENTATIONS */

namespace sdl::runner {
	// Set up SDL. Returns true if SDL setup succeeds
	bool init(const char* renderer) {
		SDL_SetHint(SDL_HINT_RENDER_VULKAN_DEBUG, "1");

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
		if (!MIX_Init()) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "MIX_Init failed: %s", SDL_GetError());
			return false;
		}
		MIX_Mixer* mixerSound = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
		if (!mixerSound) {
			SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, "Mixer Sound went derp: %s", getError());
			return false;
		}
		mixers.push_back(mixerSound);
		MIX_Mixer* mixerMusic = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
		if (!mixerMusic) {
			SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, "Mixer Sound went derp: %s", getError());
			return false;
		}
		mixers.push_back(mixerMusic);


		// Initialize driver
		device = SDL_CreateGPUDevice(SDL_ShaderCross_GetHLSLShaderFormats(), true, renderer);
		if (!device) {
			SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Device went derp: %s", getError());
			return false;
		}

		// Initialize keyboard
		key = SDL_GetKeyboardState(&numKeys);
		keyJust = new Uint8[numKeys];
		memcpy(keyJust, key, numKeys);

		// TODO initialize pad

		enabledInternal = true;

		return true;
	}

	bool initRendering(const char* normalFrag, const char* normalVert, const char* fillFrag, const char* fillVert, const int maxSprites) {
		// Initialize vertex storage and transfer buffers
		const Uint32 sizeVert = sizeof(TexProps) * maxSprites;
		vertexBuffer = deviceCreateBuffer(SDL_GPU_BUFFERUSAGE_VERTEX, sizeVert);
		transferBuffer = deviceCreateTransferBuffer(
			SDL_GPUTransferBufferUsage::SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			(sizeVert)
		);

		// Initialize samplers
		SDL_GPUSamplerCreateInfo samplerInfo = {
			.min_filter = SDL_GPUFilter::SDL_GPU_FILTER_LINEAR,
			.mag_filter = SDL_GPUFilter::SDL_GPU_FILTER_LINEAR,
			.mipmap_mode = SDL_GPUSamplerMipmapMode::SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
			.address_mode_u = SDL_GPUSamplerAddressMode::SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
			.address_mode_v = SDL_GPUSamplerAddressMode::SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
			.address_mode_w = SDL_GPUSamplerAddressMode::SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
		};
		sampler = SDL_CreateGPUSampler(device, &samplerInfo);

		// Set up pipelines
		SDL_GPUShader* shaderFragment = loadShader(normalFrag, STAGE_FRAGMENT, 1, 1);
		SDL_GPUShader* shaderVertex = loadShader(normalVert, STAGE_VERTEX, 0, 1);
		renderStandard = createPipeline(shaderVertex, shaderFragment);

		SDL_GPUShader* shaderFillFragment = loadShader(fillFrag, STAGE_FRAGMENT, 1, 1);
		SDL_GPUShader* shaderFillVertex = loadShader(fillVert, STAGE_VERTEX, 0, 1);
		renderFill = createPipeline(shaderFillVertex, shaderFillFragment);
		// TODO more shaders/blending modes

		SDL_ReleaseGPUShader(device, shaderFragment);
		SDL_ReleaseGPUShader(device, shaderVertex);
		SDL_ReleaseGPUShader(device, shaderFillFragment);
		SDL_ReleaseGPUShader(device, shaderFillVertex);

		// Text engine
		textEngine = TTF_CreateGPUTextEngine(device);

		return true;
	}

	bool mixerSetGain(int index, float vol) {
		if (index < mixers.size()) {
			return MIX_SetMixerGain(mixers[index], vol);
		}
		return false;
	}

	// Execute a singular game loop. Returns false if the program should terminate 
	bool poll() {
		// Update time
		timeCurrent = SDL_GetTicksNS();
		delta = timeCurrent - timeLast;
		timeLast = timeCurrent;

		// Update last known mouse/keyboard states
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

	int registerMixer(SDL_AudioDeviceID devid, const SDL_AudioSpec* spec) {
		MIX_Mixer* mixer = MIX_CreateMixerDevice(devid, spec);
		if (!mixer) {
			SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, "Mixer could not be created: %s", getError());
			return false;
		}
	}

	MIX_Audio* mixerLoadAudio(int index, const char* path, bool predecode) {
		if (index < mixers.size()) {
			return MIX_LoadAudio(mixers[index], path, predecode);
		}
		return nullptr;
	}

	// Returns the first track that is available for playing sounds. If none are available, creates a new one
	MIX_Track* requestTrack(int index) {
		if (index < mixers.size()) {
			MIX_Mixer* mixer = mixers[index];
			for (MIX_Track* track : tracks) {
				if (!MIX_TrackPlaying(track)) {
					return track;
				}
			}
			MIX_Track* newTrack = MIX_CreateTrack(mixer);
			tracks.push_back(newTrack);
			return newTrack;
		}
		return nullptr;
	}

	// Generates a graphics pipeline to be used for this window
	SDL_GPUGraphicsPipeline* createPipeline(SDL_GPUShader* vertexShader, SDL_GPUShader* fragmentShader, SDL_GPUTextureFormat textureFormat, SDL_GPUBlendFactor srcColor, SDL_GPUBlendFactor dstColor, SDL_GPUBlendFactor srcAlpha, SDL_GPUBlendFactor dstAlpha) {
		SDL_GPUColorTargetDescription colorAttachmentDescriptions[] = {
			{
				.format = textureFormat,
				.blend_state = {
					.src_color_blendfactor = srcColor,
					.dst_color_blendfactor = dstColor,
					.color_blend_op = SDL_GPUBlendOp::SDL_GPU_BLENDOP_ADD,
					.src_alpha_blendfactor = srcAlpha,
					.dst_alpha_blendfactor = dstAlpha,
					.alpha_blend_op = SDL_GPUBlendOp::SDL_GPU_BLENDOP_ADD,
					.color_write_mask = 0xF,
					.enable_blend = true
				}
			}
		};
		SDL_GPUVertexBufferDescription vertexBindings[] = {
			{
				.slot = 0,
				.pitch = sizeof(TexProps),
				.input_rate = SDL_GPUVertexInputRate::SDL_GPU_VERTEXINPUTRATE_INSTANCE
			}
		};
		SDL_GPUVertexAttribute vertexAttributes[] = {
			// float4x4
			{
				.location = 0,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
				.offset = 0
			},
			{
				.location = 1,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
				.offset = sizeof(float) * 4
			},
			{
				.location = 2,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
				.offset = sizeof(float) * 8
			},
			{
				.location = 3,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
				.offset = sizeof(float) * 12
			},

			// float4
			{
				.location = 4,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
				.offset = sizeof(float) * 16
			},

			// float2x4
			{
				.location = 5,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
				.offset = sizeof(float) * 20
			},
			{
				.location = 6,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
				.offset = sizeof(float) * 22
			},
			{
				.location = 7,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
				.offset = sizeof(float) * 24
			},
			{
				.location = 8,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
				.offset = sizeof(float) * 26
			},

			// float1
			{
				.location = 9,
				.buffer_slot = 0,
				.format = SDL_GPUVertexElementFormat::SDL_GPU_VERTEXELEMENTFORMAT_FLOAT,
				.offset = sizeof(float) * 28
			},
		};

		SDL_GPUGraphicsPipelineCreateInfo pipelineCreateInfo = {
			.vertex_shader = vertexShader,
			.fragment_shader = fragmentShader,
			.vertex_input_state = {
				.vertex_buffer_descriptions = vertexBindings,
				.num_vertex_buffers = 1,
				.vertex_attributes = vertexAttributes,
				.num_vertex_attributes = 10,
			},
			.primitive_type = SDL_GPUPrimitiveType::SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
			.target_info = {
				.color_target_descriptions = colorAttachmentDescriptions,
				.num_color_targets = 1
			}
		};

		return SDL_CreateGPUGraphicsPipeline(device, &pipelineCreateInfo);
	}

	// Generates a non-texture graphics pipeline to be used for this window
	SDL_GPUGraphicsPipeline* createShapePipeline(SDL_GPUShader* vertexShader, SDL_GPUShader* fragmentShader, SDL_GPUTextureFormat textureFormat, SDL_GPUBlendFactor srcColor, SDL_GPUBlendFactor dstColor, SDL_GPUBlendFactor srcAlpha, SDL_GPUBlendFactor dstAlpha) {
		SDL_GPUColorTargetDescription colorAttachmentDescriptions[] = {
			{
				.format = textureFormat,
				.blend_state = {
					.src_color_blendfactor = srcColor,
					.dst_color_blendfactor = dstColor,
					.color_blend_op = SDL_GPUBlendOp::SDL_GPU_BLENDOP_ADD,
					.src_alpha_blendfactor = srcAlpha,
					.dst_alpha_blendfactor = dstAlpha,
					.alpha_blend_op = SDL_GPUBlendOp::SDL_GPU_BLENDOP_ADD,
					.color_write_mask = 0xF,
					.enable_blend = true
				}
			}
		};
		SDL_GPUGraphicsPipelineCreateInfo pipelineCreateInfo = {
			.vertex_shader = vertexShader,
			.fragment_shader = fragmentShader,
			.vertex_input_state = {
			},
			.primitive_type = SDL_GPUPrimitiveType::SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
			.rasterizer_state = {
				.fill_mode = SDL_GPUFillMode::SDL_GPU_FILLMODE_FILL
			},
			.multisample_state = {
				.sample_mask = 0x00000000
			},
			.depth_stencil_state = {},
			.target_info = {
				.color_target_descriptions = colorAttachmentDescriptions,
				.num_color_targets = 1
			},
		};

		return SDL_CreateGPUGraphicsPipeline(device, &pipelineCreateInfo);
	}

	// TODO more pipelines
	SDL_GPUGraphicsPipeline* pipelineForMode(RenderMode mode) {
		return renderStandard;
	}

	SDL_GPUGraphicsPipeline* shapePipelineForMode(RenderMode mode) {
		return renderFill;
	}

	// Generates a shader to be used for this window
	// TODO option to cache built shader
	SDL_GPUShader* loadShader(const char* shaderFilename, ::SDL_ShaderCross_ShaderStage stage, Uint32 samplerCount, Uint32 uniformBufferCount, Uint32 storageBufferCount, Uint32 storageTextureCount) {
		size_t codeSize;
		std::filesystem::path name = SDL_GetBasePath();
		name /= shaderFilename;
		void* code = SDL_LoadFile(name.string().data(), &codeSize);
		if (code == nullptr) {
			logError("Failed to load shader from disk: %s, %s", name.string().data(), getError());
			return nullptr;
		}

		::SDL_ShaderCross_HLSL_Info info = {
			.source = static_cast<const char*>(code),
			.entrypoint = "main",
			.shader_stage = stage
		};

		::SDL_ShaderCross_GraphicsShaderMetadata metadata = {
			.num_samplers = samplerCount,
			.num_storage_textures = storageTextureCount,
			.num_storage_buffers = storageBufferCount,
			.num_uniform_buffers = uniformBufferCount,
		};
		SDL_GPUShader* shader = SDL_ShaderCross_CompileGraphicsShaderFromHLSL(device, &info, &metadata);
		SDL_free(code);
		if (shader == nullptr) {
			logError("Failed to compile shader: %s, %s", name.string().data(), getError());
		}
		return shader;
	}

	// Create an empty texture array with the specified width and height, accepting a maximum number of layers
	SDL_GPUTexture* createTextureArray(Uint32 w, Uint32 h, Uint32 maxLayers) {
		SDL_GPUTextureCreateInfo info = {
			.type = SDL_GPU_TEXTURETYPE_2D_ARRAY,
			.format = SDL_GPUTextureFormat::SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
			.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
			.width = w,
			.height = h,
			.layer_count_or_depth = maxLayers,
			.num_levels = 1,
			.sample_count = SDL_GPUSampleCount::SDL_GPU_SAMPLECOUNT_1,
		};
		SDL_GPUTexture* tex = runner::deviceCreateTexture(&info);
		sdl::logCritical("Created texture array with %s", SDL_GetError());
		return tex;
	}

	// Convert a surface into a texture to be used for rendering
	SDL_GPUTexture* uploadSingleTexture(SDL_GPUCopyPass* copyPass, Surface* surface) {
		SDL_GPUTransferBuffer* textureTransferBuffer = runner::deviceCreateTransferBuffer(
			SDL_GPUTransferBufferUsage::SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			surface->w * surface->h * 4
		);
		SDL_GPUTexture* tex = uploadSingleTexture(copyPass, surface, textureTransferBuffer);
		runner::deviceReleaseTransferBuffer(textureTransferBuffer);
		return tex;
	}

	// Convert a surface into a texture to be used for rendering
	SDL_GPUTexture* uploadSingleTexture(SDL_GPUCopyPass* copyPass, Surface* surface, SDL_GPUTransferBuffer* textureTransferBuffer) {
		Uint32 w = surface->w;
		Uint32 h = surface->h;
		const Uint32 imageSizeInBytes = w * h * 4;

		void* textureTransferPtr = deviceMapTransferBuffer(textureTransferBuffer, false);
		std::memcpy(textureTransferPtr, surface->pixels, imageSizeInBytes);
		runner::deviceUnmapTransferBuffer(textureTransferBuffer);

		SDL_GPUTextureCreateInfo info = {
			.type = SDL_GPU_TEXTURETYPE_2D,
			.format = SDL_GPUTextureFormat::SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
			.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
			.width = w,
			.height = h,
			.layer_count_or_depth = 1,
			.num_levels = 1,
			.sample_count = SDL_GPUSampleCount::SDL_GPU_SAMPLECOUNT_1,
		};
		SDL_GPUTexture* texture = runner::deviceCreateTexture(&info);

		SDL_GPUTextureTransferInfo tInfo = {
			.transfer_buffer = textureTransferBuffer,
			.offset = 0,
		};
		SDL_GPUTextureRegion tRegion = {
			.texture = {texture},
			.mip_level = 0,
			.layer = 0,
			.w = w,
			.h = h,
			.d = 1
		};

		SDL_UploadToGPUTexture(copyPass, &tInfo, &tRegion, false);
		return texture;
	}

	// Add a surface into a texture array to be used for rendering
	SDL_GPUTexture* uploadTextureForArray(SDL_GPUCopyPass* copyPass, Surface* surface, SDL_GPUTexture* texture, SDL_GPUTransferBuffer* textureTransferBuffer, Uint32 layer) {
		Uint32 w = surface->w;
		Uint32 h = surface->h;
		const Uint32 imageSizeInBytes = w * h * 4;

		sdl::logCritical("Uploading texture of size %d x %d", w, h);

		void* textureTransferPtr = deviceMapTransferBuffer(textureTransferBuffer, false);
		std::memcpy(textureTransferPtr, surface->pixels, imageSizeInBytes);
		runner::deviceUnmapTransferBuffer(textureTransferBuffer);

		SDL_GPUTextureTransferInfo tInfo = {
			.transfer_buffer = textureTransferBuffer,
			.offset = 0,
		};
		SDL_GPUTextureRegion tRegion = {
			.texture = texture,
			.mip_level = 0,
			.layer = layer,
			.w = w,
			.h = h,
			.d = 1
		};

		SDL_UploadToGPUTexture(copyPass, &tInfo, &tRegion, false);
		return texture;
	}

	void bindRenderBuffer(SDL_GPURenderPass* pass) {
		SDL_GPUBufferBinding b = {vertexBuffer, 0};
		SDL_BindGPUVertexBuffers(pass, 0, &b, 1);
	}

	// Bind a texture to the renderpass using the default sampler
	void bindTexture(SDL_GPURenderPass* pass, SDL_GPUTexture* texture) {
		SDL_GPUTextureSamplerBinding b = {texture, sampler};
		SDL_BindGPUFragmentSamplers(pass, 0, &b, 1);
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
		SDL_ReleaseGPUBuffer(device, vertexBuffer);
		SDL_ReleaseGPUGraphicsPipeline(device, renderStandard);
		SDL_ReleaseGPUSampler(device, sampler);
		SDL_ReleaseGPUTransferBuffer(device, transferBuffer);
		vertexBuffer = nullptr;
		renderStandard = nullptr;
		sampler = nullptr;
		transferBuffer = nullptr;

		SDL_DestroyGPUDevice(device);
		device = nullptr;

		for (MIX_Mixer* mixer : mixers) {
			MIX_DestroyMixer(mixer);
		}
		mixers.clear();

		TTF_Quit();
		MIX_Quit();
		SDL_Quit();
		enabledInternal = false;
	}

	// Transfer data currently stored in the transfer buffer to the storage buffer
	void uploadToVertexBuffer(SDL_GPUCommandBuffer* cmd, Uint32 sizeVert, Uint32 offset) {
		SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(cmd);
		SDL_GPUTransferBufferLocation t1 = {transferBuffer, 0};
		SDL_GPUBufferRegion r1 = {vertexBuffer, offset, sizeVert};
		SDL_UploadToGPUBuffer(copyPass, &t1, &r1, true);
		SDL_EndGPUCopyPass(copyPass);
	}
}
