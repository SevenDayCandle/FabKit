module;

#include "glaze/glaze.hpp"

export module fbc.Config;

import fbc.FUtil;
import sdl;
import std;

namespace fbc {
    export constexpr strv BASE_CONFIG_FILE = "config.json";

    export class Config {
    public:
        class ConfigEntry {
        public:
            ConfigEntry(strv id) : id(id) {}
            virtual ~ConfigEntry() {}

            const str id;

            virtual void reload() = 0;
        };

        Config(strv id) : id(id) {}
        virtual ~Config() {}

        const str id;

        inline virtual void postInitialize() {}

        strv getValue(const str& key);
        void commit();
        void load();
        void refreshItems();
        void registerEntry(ConfigEntry* item);
        void set(const str& key, const str& value);
    protected:
        str getConfigPath() const;
    private:
        map<str, str> values_map;
        map<strv, ConfigEntry*> items;
    };


    // Save the contents of the values_map to an external file
    void Config::commit() {
        str configPath = getConfigPath();
        auto error = glz::write_file_json(values_map, configPath, str{});
        if (error) {
            sdl::logError("Failed to save config at path %s", configPath.data());
        }
        else {
            sdl::logInfo("Saved config at path %s", configPath.data());
        }
    }

    // Refresh the value map contents from the external file if it exists, then update all listeners with the new config values
    void Config::load() {
        str configPath = getConfigPath();
        if (std::filesystem::exists(configPath)) {
            auto error = glz::read_file_json(values_map, configPath, str{});
            if (error) {
                sdl::logError("Failed to read config at path %s", configPath.data());
            }
            else {
                sdl::logInfo("Read config at path %s", configPath.data());
            }
        }
        refreshItems();
    }

    // Update all listeners with the read config values
    void Config::refreshItems() {
        for (ConfigEntry* item : items | std::views::values) {
            item->reload();
        }
    }

    // Add a listener to this config. Disallows items with duplicate IDs
    void Config::registerEntry(ConfigEntry* item)
    {
        auto [it, inserted] = items.try_emplace(item->id, item);
        if (!inserted) {
            throw std::logic_error("Duplicate Config entry in " + this->id + " with id: " + item->id);
        }
    }

    // Get the path to the file used to store this config's data
    str Config::getConfigPath() const {
        return sdl::dirPref(futil::FBC.data(), id.c_str()) + str(BASE_CONFIG_FILE);
    }

    // Get the mapped value for key
    strv Config::getValue(const str& key) {
        auto val = values_map.find(key);
        if (val != values_map.end()) {
            return val->second;
        }
        return strv{};
    }

    // Set the value in the map
    void Config::set(const str& key, const str& value) {
        values_map[key] = value;
    }
}