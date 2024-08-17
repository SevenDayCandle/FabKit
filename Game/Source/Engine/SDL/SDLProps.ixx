module;

#include "SDL3/SDL.h"

export module sdl.SDLProps;

import std;

namespace sdl {
	export class SDLProps {
	public:
		SDLProps(): id(SDL_CreateProperties()) {}
		SDLProps(const SDLProps& other) : id(SDL_CreateProperties()) { SDL_CopyProperties(other.id, id); };
		SDLProps(SDLProps&& move) noexcept: id(move.id) {}
		~SDLProps() { SDL_DestroyProperties(id); }

		operator SDL_PropertiesID() const { return id; }

		inline int clearProperty(const char* name) {return SDL_ClearProperty(id, name);}
		inline bool getBool(const char* name, bool defaultValue = false) const {return SDL_GetBooleanProperty(id, name, defaultValue);}
		inline float getFloat(const char* name, float defaultValue = 0.0f) const {return SDL_GetFloatProperty(id, name, defaultValue);}
		inline Sint64 getInt(const char* name, Sint64 defaultValue = 0) const {return SDL_GetNumberProperty(id, name, defaultValue);}
		inline const char* getString(const char* name, const char* defaultValue = "") const {return SDL_GetStringProperty(id, name, defaultValue);}
		inline int setBool(const char* name, const bool value) { return SDL_SetBooleanProperty(id, name, value); }
		inline int setFloat(const char* name, const float value) { return SDL_SetFloatProperty(id, name, value); }
		inline int setInt(const char* name, const Sint64 value) { return SDL_SetNumberProperty(id, name, value); }
		inline int setString(const char* name, const char* value) { return SDL_SetStringProperty(id, name, value); }
	private:
		SDL_PropertiesID id;
	};
}