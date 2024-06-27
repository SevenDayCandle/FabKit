export module fbc.ConfigEntry;

import fbc.FUtil;

export namespace fbc {
	export class ConfigEntry {
    public:
        ConfigEntry(strv id) : id(id) {}
        virtual ~ConfigEntry() {}

        const str id;

        virtual void reload() = 0;
    };
}