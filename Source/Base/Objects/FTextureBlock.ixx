export module fab.FTextureBlock;

import fab.FUtil;
import fab.ILoadable;
import sdl.SDLBase;
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	/* A wrapper around a texture array that tracks individual textures and delegates them to subscribers */
	export class FTextureBlock : public ILoadable {
	public:
		constexpr static int DEFAULT_LENGTH = 1024;

		/* An element that can be placed into a FWindow */
		class Item : public ILoadable {
		public:
			Item(FTextureBlock& source) : source(source) {}
			Item(Item&& other) noexcept : source(other.source), index(other.index) {}
			~Item() override = default;

			operator bool() const { return loaded(); }

			inline bool loaded() const { return source && index > -1; }
			inline bool reupload(sdl::GPUCopyPass* copyPass, sdl::Surface* surface) const { return source.reuploadSurface(copyPass, this, surface); }
			inline void release() const { return source.release(this); }
		protected:
			FTextureBlock& source;
			mutable int index = -1;
			friend FTextureBlock;
		};

		FTextureBlock(int w, int h, int maxLength = DEFAULT_LENGTH) : texH(h), texW(w), loadables(std::max(1, maxLength)) {}
		FTextureBlock(const FTextureBlock&) = delete;

		FTextureBlock(FTextureBlock&& other) noexcept : texH(other.texH), texW(other.texW), texture(other.texture) {
			other.texture = nullptr;
		}

		~FTextureBlock() override {
			if (sdl::runner::enabled()) {
				FTextureBlock::dispose();
			}
		}

		operator bool() const { return texture != nullptr; }
		operator sdl::GPUTexture*() const { return texture; }

		inline bool loaded() const { return texture != nullptr; }
		inline int getHeight() const { return texH; }
		inline int getWidth() const { return texW; }
		inline int getMaxLength() const { return loadables.size(); }

		bool reserve(sdl::GPUCopyPass* copyPass, const FTextureBlock::Item* loadable, sdl::Surface* surface) const;
		bool reuploadSurface(sdl::GPUCopyPass* copyPass, const FTextureBlock::Item* loadable, sdl::Surface* surface) const;
		template <c_ext<FTextureBlock::Item> T> T& create(const strv& key);
		void dispose() override;
		void release(const FTextureBlock::Item* loadable) const;
		void reload() const override;
		void reload(sdl::GPUCopyPass* copyPass) const override;
		void resize(int maxLength) const;
		void setup() const;
	protected:
		const int texH = 0;
		const int texW = 0;

		int uploadSurface(sdl::GPUCopyPass* copyPass, sdl::Surface* surface) const;
		int uploadSurface(sdl::GPUCopyPass* copyPass, sdl::Surface* surface, int index) const;
	private:
		mutable int freeIndex = 0;
		mutable sdl::GPUTexture* texture = nullptr;
		mutable sdl::GPUTransferBuffer* textureTransferBuffer = nullptr;
		mutable vec<uptr<FTextureBlock::Item>> loadables;

		friend FTextureBlock::Item;
	};

	int FTextureBlock::uploadSurface(sdl::GPUCopyPass* copyPass, sdl::Surface* surface) const {
		int res = uploadSurface(copyPass, surface, freeIndex);
		if (res) {
			while (freeIndex < loadables.size() && loadables[freeIndex] != nullptr) {
				freeIndex += 1;
			}
		}
		return res;
	}

	int FTextureBlock::uploadSurface(sdl::GPUCopyPass* copyPass, sdl::Surface* surface, int index) const {
		sdl::Uint32 w = surface->w;
		sdl::Uint32 h = surface->h;
		if (w != texW || h != texH) {
			sdl::logError("Mismatched dimensions for texture array: %d x %d. Expected %d x %d", w, h, texW, texH);
			return -1;
		}
		if (index >= loadables.size()) {
			sdl::logError("Index %d is beyond length limit for texture array: %d", index, loadables.size());
			return -1;
		}
		sdl::runner::uploadTextureForArray(copyPass, surface, texture, textureTransferBuffer, index);
		return index;
	}

	bool FTextureBlock::reserve(sdl::GPUCopyPass* copyPass, const FTextureBlock::Item* loadable, sdl::Surface* surface) const {
		if (!loadable || &loadable->source != this) {
			return false;
		}
		int res = uploadSurface(copyPass, surface);
		if (res >= 0) {
			loadable->index = res;
			return true;
		}
		return false;
	}

	bool FTextureBlock::reuploadSurface(sdl::GPUCopyPass* copyPass, const FTextureBlock::Item* loadable, sdl::Surface* surface) const {
		if (!loadable || &loadable->source != this) {
			return false;
		}
		int ind = loadable->index;
		if (ind < 0) {
			return reserve(copyPass, loadable, surface);
		}
		int res = uploadSurface(copyPass, surface, ind);
		return res >= 0;
	}

	void FTextureBlock::dispose() {
		if (texture) {
			sdl::runner::deviceReleaseTexture(texture);
			texture = nullptr;
		}
		if (textureTransferBuffer) {
			sdl::runner::deviceReleaseTransferBuffer(textureTransferBuffer);
			textureTransferBuffer = nullptr;
		}
		loadables.clear();
		freeIndex = 0;
	}

	/* Frees up an item's hold on a particular slot in this block to be able to be taken by other items */
	void FTextureBlock::release(const FTextureBlock::Item* loadable) const {
		if (loadable) {
			int index = loadable->index;
			if (index >= 0 && index < loadables.size()) {
				loadables[index] = nullptr;
				if (index < freeIndex) {
					freeIndex = index;
				}
				loadable->index = -1;
			}
			else {
				sdl::logError("Tried to release loadable with out-of-bound index for texture array at index %d", index);
			}
		}
		else {
			sdl::logError("Tried to release NULL for texture array");
		}
	}

	void FTextureBlock::reload() const {
		sdl::GPUCommandBuffer* uploadCmdBuf = sdl::runner::deviceAcquireCommandBuffer();
		sdl::GPUCopyPass* copyPass = sdl::gpuBeginCopyPass(uploadCmdBuf);
		reload(copyPass);
		sdl::gpuEndCopyPass(copyPass);
		sdl::gpuSubmit(uploadCmdBuf);
	}

	void FTextureBlock::reload(sdl::GPUCopyPass* copyPass) const {
		setup();
		for (int i = 0; i < loadables.size(); ++i) {
			if (loadables[i]) {
				loadables[i]->reload(copyPass);
			}
		}
	}

	void FTextureBlock::resize(int size) const {
		loadables.resize(loadables.size());
		reload();
	}

	void FTextureBlock::setup() const {
		if (texture) {
			sdl::runner::deviceReleaseTexture(texture);
		}
		if (textureTransferBuffer) {
			sdl::runner::deviceReleaseTransferBuffer(textureTransferBuffer);
		}
		texture = sdl::runner::createTextureArray(texW, texH, loadables.size());
		textureTransferBuffer = sdl::runner::deviceCreateTransferBuffer(
			sdl::GPUTransferBufferUsage::SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			texW * texH * 4
		);
	}

	template <c_ext<FTextureBlock::Item> T> T& FTextureBlock::create(const strv& key) {
		if (freeIndex >= loadables.size()) {
			resize(loadables.size() * 2); // TODO have a better way to resize, watch for failures
		}
		T& item = static_cast<T&>(*loadables.emplace_back(make_unique<T>(*this, key)));
		item.index = loadables.size() - 1;
		return item;
	}
}
