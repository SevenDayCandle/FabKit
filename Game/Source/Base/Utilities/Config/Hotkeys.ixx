export module fbc.hotkeys;

import fbc.futil;
import raylib;

export namespace fbc {
	export class Hotkeys {
        public:
            Hotkeys();
            void addOnReload(func<void()> action);
            void commit();
            pair<raylib::KeyboardKey, raylib::GamepadButton> getValue(const str& key);
            void reload();
            void set(const str& ID, const raylib::KeyboardKey& key, const raylib::GamepadButton& button);

        private:
            static const str CONFIG_NAME;
            static str configFilePath;
            map<str, pair<raylib::KeyboardKey, raylib::GamepadButton>> keysMap;
            func<void()> onReload;
            void reloadInternal();
	};
}