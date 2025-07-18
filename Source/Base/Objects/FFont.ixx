export module fab.FFont;

import fab.FTextureBlock;
import fab.FUtil;
import fab.ILoadable;
import sdl.SDLBase;
import fab.BatchRenderPass;
import sdl.SDLRunner;

namespace fab {
	export class FFont : public ILoadable {
	public:
		struct Props {
			float globalScale = 1;
			int size = 12;
			int outlineSize = 0;
			int shadowSize = 0;
		};

		FFont(strv path, float scalar, int size, int outlineSize = 0, int shadowSize = 0): globalScale(scalar), outlineSize(outlineSize), shadowSize(shadowSize), size(size), path(path) {}
		FFont(strv path, const Props& props) : FFont(path, props.globalScale, props.size, props.outlineSize, props.shadowSize) {}
		FFont(const FFont&) = delete;

		~FFont() override {
			if (sdl::runner::enabled()) {
				FFont::dispose();
			}
		}

		operator sdl::Font*() const { return font; }

		inline int getOutlineSize() const { return outlineSize; }
		inline int getShadowSize() const { return outlineSize; }
		inline int getSize() const { return size; }

		FFont& setAllSizes(int size, int outlineSize, int shadowSize);
		FFont& setGlobalScale(float scale);
		FFont& setOutlineSize(int size);
		FFont& setShadowSize(int size);
		FFont& setSize(int size);
		int measureH(strv text) const;
		int measureW(strv text) const;
		pair<int, int> measureDim(strv text) const;
		void dispose() override;
		void reload() const override;
		void reload(sdl::GPUCopyPass* copyPass) const override;
	private:
		mutable sdl::Font* font;
		float globalScale = 1;
		int outlineSize;
		int shadowSize;
		int size;
		str path;
	};

	// Get the x and y sizes of the given text written with this font
	pair<int, int> FFont::measureDim(strv text) const {
		pair<int, int> pair;
		sdl::fontSizeText(font, text.data(), &pair.first, &pair.second);
		return pair;
	}

	// Get the x size of the given text written with this font
	int FFont::measureH(strv text) const {
		int w, h;
		sdl::fontSizeText(font, text.data(), &w, &h);
		return h;
	}

	// Get the y size of the given text written with this font
	int FFont::measureW(strv text) const {
		int w, h;
		sdl::fontSizeText(font, text.data(), &w, &h);
		return w;
	}

	// Update all sizes and reload the font with the new size. Note that sizes will be scaled by fontScale and should not be multiplied by it beforehand.
	FFont& FFont::setAllSizes(int size, int outlineSize, int shadowSize) {
		this->size = size;
		this->outlineSize = outlineSize;
		this->shadowSize = shadowSize;
		reload();
		return *this;
	}

	FFont& FFont::setGlobalScale(float scale) {
		this->globalScale = scale;
		reload();
		return *this;
	}

	// Update the font size and reload the font with the new size. Note that sizes will be scaled by fontScale and should not be multiplied by it beforehand.
	FFont& FFont::setOutlineSize(int size) {
		this->outlineSize = size;
		return *this;
	}

	// Update the font size and reload the font with the new size. Note that sizes will be scaled by fontScale and should not be multiplied by it beforehand.
	FFont& FFont::setShadowSize(int size) {
		this->shadowSize = size;
		return *this;
	}

	// Update the font size and reload the font with the new size. Note that sizes will be scaled by fontScale and should not be multiplied by it beforehand.
	FFont& FFont::setSize(int size) {
		this->size = size;
		reload();
		return *this;
	}

	/* Close the font */
	void FFont::dispose() {
		if (font) {
			sdl::fontClose(font);
			font = nullptr;
		}
	}

	/* Refreshes the font to match its size */
	void FFont::reload() const {
		sdl::GPUCommandBuffer* uploadCmdBuf = sdl::runner::deviceAcquireCommandBuffer();
		sdl::GPUCopyPass* copyPass = sdl::gpuBeginCopyPass(uploadCmdBuf);
		reload(copyPass);
		sdl::gpuEndCopyPass(copyPass);
		sdl::gpuSubmit(uploadCmdBuf);
	}

	/* Refreshes the font to match its size */
	void FFont::reload(sdl::GPUCopyPass* copyPass) const {
		if (font) {
			sdl::fontClose(font);
		}

		int res = globalScale * (size);
		font = sdl::fontOpen(path.c_str(), res);
		if (!font) {
			sdl::logError("Failed to load font %s: %s", path.c_str(), sdl::getError());
		}
	}
}
