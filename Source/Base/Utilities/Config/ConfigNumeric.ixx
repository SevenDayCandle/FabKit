export module fab.ConfigNumeric;

import fab.Config;
import fab.ConfigValue;
import fab.FUtil;
import sdl.SDLBase; 
import sdl.SDLRunner;
import std;

namespace fab {
	export class ConfigNumeric : public ConfigValue<int> {
	public:
		ConfigNumeric(fab::Config& config, strv id, const int& defaultValue, int min = 0, int max = std::numeric_limits<int>::max()): ConfigValue<int>(config, id, defaultValue), min(min), max(max) {}

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