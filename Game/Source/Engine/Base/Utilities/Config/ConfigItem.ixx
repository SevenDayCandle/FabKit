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

        operator T() { return value; }

        inline void setOnReload(func<void(const T&)> onChange) {this->onChange = onChange;}
        inline T get() {return value;}

        void set(const T& newValue);
    protected:
        inline virtual void assignValue(const T& result) { this->value = result; }

        T parseValue(strv input);
        void reload();
    private:
        fbc::Config& config;
        const T defaultValue;
        func<void(const T&)> onChange;
        T value;
    };

    // Convert a string input into the value for this config item
    template<typename T> T ConfigItem<T>::parseValue(strv input)
    {
        try {
            // TODO use glz::read_json when it is ready to use with modules
            size_t pos = 0;
            return futil::fromString<T>(input, pos);
        }
        catch (const exception& e) {
            sdl::logError("Config item with ID %s failed to parse input %s: %s", ID.data(), input.data(), e.what());
            return defaultValue;
        }
    }

    // Reset this config's values to whatever is in the config file, if it exists
    template<typename T> void ConfigItem<T>::reload() {
        strv val = config.getValue(ID);
        if (!val.empty()) {
            T parsed = parseValue(config.getValue(ID));
            assignValue(parsed);
        }
    }

    // Set the value for this config item, write it back to the file, and broadcast this change to all listeners
    template<typename T> void ConfigItem<T>::set(const T& newValue) {
        assignValue(newValue);
        // TODO use glz::write_json when it is ready to use with modules
        config.set(ID, futil::toString(newValue));
        if (onChange) {
            onChange(newValue);
        }
    }
}