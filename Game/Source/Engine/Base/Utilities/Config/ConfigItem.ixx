export module fbc.ConfigItem;

import fbc.Config;
import fbc.FUtil;
import sdl;

export namespace fbc {
    export template<typename T> class ConfigItem {
    public:
        ConfigItem(fbc::Config& config, strv ID, const T& defaultValue) : config(config), ID(ID), defaultValue(defaultValue), value(defaultValue) {
            config.addOnReload([this]() { this->reload(); });
        }

        const str ID;

        inline void addSubscriber(func<void(const T&)> callback) {onChange.push_back(callback);}
        inline T get() {return value;}
        void set(const T& newValue);

        operator T() { return value; }

    protected:
        T parseValue(const str& input);
        void reload();

    private:
        fbc::Config& config;
        const T defaultValue;
        vec<func<void(const T&)>> onChange;
        T value;
    };

    // Convert a string input into the value for this config item
    template<typename T> T ConfigItem<T>::parseValue(const str& input)
    {
        try {
            // TODO use glz::read_json when it is ready to use with modules
            size_t pos = 0;
            return futil::fromString<T>(input, pos);
        }
        catch (const exception& e) {
            sdl::logError("Config item with ID %s failed to parse input %s: %s", ID, input, e);
            return defaultValue;
        }
    }

    // Reset this config's values to whatever is in the config file
    template<typename T> void ConfigItem<T>::reload() {
        this->value = parseValue(config.getValue(ID));
    }

    // Set the value for this config item, write it back to the file, and broadcast this change to all listeners
    template<typename T> void ConfigItem<T>::set(const T& newValue) {
        this->value = newValue;
        // TODO use glz::write_json when it is ready to use with modules
        config.set(ID, futil::toString(newValue));
        for (func<void(const T&)>& callback : onChange) {
            callback(newValue);
        }
    }
}