module;

#include "SDL3/SDL.h"

export module fab.ILoadable;

import fab.FUtil;
import sdl.SDLHelpers;
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export struct ILoadable {
	public:
		ILoadable() {}

		virtual ~ILoadable() = default;

		inline virtual void reload(::SDL_GPUCopyPass* copyPass) const { reload(); }

		virtual void dispose() = 0;
		virtual void reload() const = 0;
	};
}
