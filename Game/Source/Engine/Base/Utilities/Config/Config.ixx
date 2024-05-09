module;

#include "glaze/glaze.hpp"

export module fbc.Config;

import fbc.futil;
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
        str getValue(const str& key);
        void initialize();
        void reload();
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
    }

    // Refresh the value map contents from the external file if it exists
    void Config::initialize() {
        str configPath = getConfigPath();
        if (std::filesystem::exists(configPath)) {
            glz::parse_error error = glz::read_file_json(values_map, configPath, str{});
            if (error) {
                sdl::logError("Failed to read config at path %s", configPath.data());
            }
        }
    }

    // Get the path to the file used to store this config's data
    str Config::getConfigPath() const {
        return sdl::dirPref(futil::FBC.data(), ID.c_str()) + str(BASE_CONFIG_FILE);
    }

    // Get the mapped value for key
    str Config::getValue(const str& key) {
        auto val = values_map.find(key);
        if (val != values_map.end()) {
            return val->second;
        }
        return "";
    }

    // Refresh the config (reloadInternal) and then update all listeners with the new config values
    void Config::reload() {
        initialize();
        for (func<void()>& callback : items) {
            callback();
        }
    }

    // Set the value in the map
    void Config::set(const str& key, const str& value) {
        values_map[key] = value;
    }
}