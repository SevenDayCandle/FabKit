export module fbc.ConfigNumeric;

import fbc.Config;
import fbc.ConfigValue;
import fbc.FUtil;
import sdl;
import std;

export namespace fbc {
	export class ConfigNumeric : public ConfigValue<int> {
	public:
		ConfigNumeric(fbc::Config& config, strv id, const int& defaultValue, int min = 0, int max = std::numeric_limits<int>::max()): ConfigValue<int>(config, id, defaultValue), min(min), max(max) {}
		virtual ~ConfigNumeric() {}

		inline int getMax() const { return max; }
		inline int getMin() const { return min; }
	protected:
		void assignValue(const int& res) override;
	private:
		int max;
		int min;
	};

	void ConfigNumeric::assignValue(const int& res) {
		ConfigValue<int>::assignValue(std::clamp(res, min, max));
	}
}