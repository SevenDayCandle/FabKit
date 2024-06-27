export module fbc.ConfigValue;

import fbc.Config;
import fbc.ConfigEntry;
import fbc.FUtil;
import sdl;

export namespace fbc {
    export template<typename T> class ConfigValue : public ConfigEntry {
    public:
        ConfigValue(Config& config, strv id, const T& defaultValue) : ConfigEntry(id), config(config), defaultValue(defaultValue), value(defaultValue) {
            config.registerEntry(this);
        }
        virtual ~ConfigValue() override {}

        const str id;

        operator T() { return value; }

        inline void setOnReload(const func<void(const T&)>& onChange) {this->onChange = onChange;}
        inline T get() {return value;}

        void reload() override;
        void set(const T& newValue);
    protected:
        inline virtual void assignValue(const T& result) { this->value = result; }

        T parseValue(strv input);
    private:
        const T defaultValue;
        Config& config;
        func<void(const T&)> onChange;
        T value;
    };

    // Convert a string input into the value for this config item
    template<typename T> T ConfigValue<T>::parseValue(strv input)
    {
        try {
            // TODO use glz::read_json when it is ready to use with modules
            size_t pos = 0;
            return futil::fromString<T>(input, pos);
        }
        catch (const exception& e) {
            sdl::logError("Config item with id %s failed to parse input %s: %s", id.data(), input.data(), e.what());
            return defaultValue;
        }
    }

    // Reset this config's values to whatever is in the config file, if it exists
    template<typename T> void ConfigValue<T>::reload() {
        strv val = config.getValue(id);
        if (!val.empty()) {
            T parsed = parseValue(config.getValue(id));
            assignValue(parsed);
        }
    }

    // Set the value for this config item, write it back to the file, and broadcast this change to all listeners
    template<typename T> void ConfigValue<T>::set(const T& newValue) {
        assignValue(newValue);
        // TODO use glz::write_json when it is ready to use with modules
        config.set(id, futil::toString(newValue));
        if (onChange) {
            onChange(newValue);
        }
    }
}