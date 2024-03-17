export module fbc.configItem;

import fbc.config;
import fbc.futil;

export namespace fbc {
    export template<typename T> class ConfigItem {
    public:
        ConfigItem(fbc::Config& config, const str& ID, const T& defaultValue) : config(config), ID(ID), defaultValue(defaultValue), value(defaultValue) {
            config.addOnReload([this]() { this->reload(); });
        }
        inline void addSubscriber(func<void(const T&)> callback) {onChange.push_back(callback);}
        inline T get() {return value;}
        void set(const T& newValue);

    protected:
        T parseValue(const str& input);
        void reload();

    private:
        fbc::Config& config;
        const T defaultValue;
        const str ID;
        vec<func<void(const T&)>> onChange;
        T value;
    };

    // Convert a string input into the value for this config item
    template<typename T>
    T ConfigItem<T>::parseValue(const str& input)
    {
        // TODO implement this once the template issues are resolved
        //return glz::read_json(input);
        return T();
    }

    // Reset this config's values to whatever is in the config file
    template<typename T>
    void ConfigItem<T>::reload()
    {
        this->value = parseValue(config.getValue(ID));
    }

    // Set the value for this config item, write it back to the file, and broadcast this change to all listeners
    template<typename T> void ConfigItem<T>::set(const T& newValue) {
        this->value = newValue;
        // TODO implement this once the template issues are resolved
        //config->set(ID, glz::write_json(newValue));
        for (func<void(const T&)> callback : onChange) {
            callback(newValue);
        }
    }
}