export module fbc.ConfigEntry;

import fbc.FUtil;

export namespace fbc {
	export class ConfigEntry {
    public:
        ConfigEntry(strv ID) : ID(ID) {}
        virtual ~ConfigEntry() {}

        const str ID;

        virtual void reload() = 0;
    };
}