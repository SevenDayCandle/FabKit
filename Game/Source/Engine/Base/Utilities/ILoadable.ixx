export module fbc.ILoadable;

import fbc.FUtil;
import fbc.Hitbox;
import sdl;
import std;

export namespace fbc {
	export struct ILoadable {
	public:
		ILoadable() {}

		virtual ~ILoadable() {}

		virtual void dispose() = 0;
		virtual void reload () = 0;
	};
}