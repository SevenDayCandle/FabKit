export module fab.ILoadable;

import fab.FUtil;
import sdl.SDLBase; 
import fab.BatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fab {
	export struct ILoadable {
	public:
		ILoadable() {}

		virtual ~ILoadable() = default;

		inline virtual void reload(sdl::GPUCopyPass* copyPass) const { reload(); }

		virtual void dispose() = 0;
		virtual void reload() const = 0;
	};
}