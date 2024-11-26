export module fab.ILoadable;

import fab.FUtil;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fab {
	export struct ILoadable {
	public:
		ILoadable() {}

		virtual ~ILoadable() = default;

		virtual void dispose() = 0;
		virtual void reload() const = 0;
	};
}