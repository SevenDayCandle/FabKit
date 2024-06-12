module;

#include "glaze/glaze.hpp"

export module fbc.Config;

import fbc.FUtil;
import sdl;
import std;

export namespace fbc {
    constexpr strv BASE_CONFIG_FILE = "config.json";

    export class Config {
    public:
        Config(strv ID) : ID(ID) {}
        virtual ~Config() {}

        const str ID;

        inline void addOnReload(func<void()> callback) {
            items.push_back(callback);
        }
        inline virtual void postInitialize() {}

        void commit();
        strv getValue(const str& key);
        void load();
        void refreshItems();
        void set(const str& key, const str& value);
    protected:
        str getConfigPath() const;
    private:
        map<str, str> values_map = map<str,str>();
        vec<func<void()>> items;
    };


    // Save the contents of the values_map to an external file
    void Config::commit() {
        str configPath = getConfigPath();
        glz::write_error error = glz::write_file_json(values_map, configPath, str{});
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
            glz::parse_error error = glz::read_file_json(values_map, configPath, str{});
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
        for (func<void()>& callback : items) {
            callback();
        }
    }

    // Get the path to the file used to store this config's data
    str Config::getConfigPath() const {
        return sdl::dirPref(futil::FBC.data(), ID.c_str()) + str(BASE_CONFIG_FILE);
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