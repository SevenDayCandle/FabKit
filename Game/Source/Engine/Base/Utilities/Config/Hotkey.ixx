module;

#include "glaze/glaze.hpp"

export module fbc.ConfigHotkey;

import fbc.Config;
import fbc.FUtil;
import fbc.KeyedItem;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export constexpr strv BASE_HOTKEY_FILE = "hotkeys.json";

	export class Hotkey : public KeyedItem<Hotkey> {
	public:
		Hotkey(strv id, sdl::Scancode key, sdl::GamepadButton gamepad): KeyedItem(id), key(key), keyDefault(key), pad(gamepad), padDefault(gamepad) {}
		virtual ~Hotkey() = default;

		inline bool isKeyJustPressed() const { return key > 0 && sdl::runner::keyboardJustPressed(key); }
		inline int getKey() const { return key; }
		inline int getPad() const { return pad; }
		inline void setKey(sdl::Scancode key) { this->key = key; }
		inline void setPad(sdl::GamepadButton  pad) { this->pad = pad; }

		void reset();
		void set(int key, int pad);

		inline static str configPath() { return sdl::dirPref(futil::FBC.data(), BASE_HOTKEY_FILE.data()); }

		static void commit();
		static void reload();
	private:
		int key;
		int keyDefault;
		int pad;
		int padDefault;
	};

	// Reset keys and pad to defaults
	void Hotkey::reset()
	{
		key = keyDefault;
		pad = padDefault;
	}

	// Set key and pad
	void Hotkey::set(int key, int pad)
	{
		this->key = key;
		this->pad = pad;
	}

	// Save the contents of the hotkeys to an external file
	void Hotkey::commit()
	{
		map<strv, Hotkey*>& regist = registered();
		map<strv, pair<int, int>> output = futil::transformMap<strv, Hotkey*, pair<int, int>>(regist, [](const Hotkey* row) { return pair<int,int>(row->key, row->pad); });
		str configPath = Hotkey::configPath();
		auto error = glz::write_file_json(output, configPath, str{});
		if (error) {
			sdl::logError("Failed to save hotkeys at path %s", configPath.data());
		}
	}

	// Refresh the value map contents from the external file if it exists
	void Hotkey::reload()
	{
		str configPath = Hotkey::configPath();
		if (std::filesystem::exists(configPath)) {
			strumap<pair<int, int>> input = strumap<pair<int, int>>();
			auto error = glz::read_file_json(input, configPath, str{});
			if (error) {
				sdl::logError("Failed to read hotkeys at path %s: %s", configPath.data(), error.includer_error.data());
			}

			// If a hotkey is in the map, set it to whatever values were read from the map. Otherwise, reset them to their defaults
			for (auto& hk : registered()) {
				auto entry = input.find(hk.first);
				if (entry != input.end()) {
					pair<int, int> found = entry->second;
					hk.second->set(found.first, found.second);
				}
				else {
					hk.second->reset();
				}
			}
		}
	}

}