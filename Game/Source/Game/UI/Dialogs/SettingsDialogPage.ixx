export module fbc.SettingsDialogPage;

import fbc.ConfigItem;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.RelativeHitbox;
import fbc.UICanvas;
import fbc.UIDropdown;
import fbc.UINumberInput;
import fbc.UITextInput;
import fbc.UISlider;
import fbc.UIToggle;
import sdl;
import std;

export namespace fbc {
	export class SettingsDialogPage : public UICanvas {
		class SettingsDialogBaseCache {
		public:
			func<void()> onReset;

			inline void setOnReset(func<void()> onReset) { this->onReset = onReset; }
		};

		template<typename T> class SettingsDialogCache : public SettingsDialogBaseCache {
		public:
			SettingsDialogCache(ConfigItem<T>& conf) : conf(conf), value(conf.get()) {}

			ConfigItem<T>& conf;
			T value;
		};

	public:
		SettingsDialogPage(Hitbox* hb, strv name): UICanvas(hb), name(name) {}
		virtual ~SettingsDialogPage() {}

		const str name;

		friend std::ostream& operator<<(std::ostream& os, const SettingsDialogPage& obj) { return os << obj; }

		template <typename T, c_itr<T> Iterable> UIDropdown<T>& addDropdown(ConfigItem<T>& conf, strv name, Iterable& items, func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); });
		UINumberInput& addInputNum(ConfigItem<int>& conf, strv name);
		UITextInput& addInputText(ConfigItem<str>& conf, strv name);
		UISlider& addSlider(ConfigItem<int>& conf, strv name, int min = 0, int max = std::numeric_limits<int>::max());
		UIToggle& addToggle(ConfigItem<bool>& conf, strv name);
		void reset();
	private:
		vec<SettingsDialogBaseCache> confs;
	};


	UISlider& SettingsDialogPage::addSlider(ConfigItem<int>& conf, strv name, int min, int max)
	{
		SettingsDialogCache<int>& cache = static_cast<SettingsDialogCache<int>&>(confs.emplace_back(SettingsDialogCache<int>(conf)));
		UISlider& slider = stackElementYDir(std::make_unique<UISlider>(new RelativeHitbox(*hb, 150, 100), min, max));
		slider
			.setValue(conf.get())
			.setOnComplete([&cache](int val) {cache.value = val; })
			.withLabel(name);
		cache.setOnReset([&slider, &conf]() {slider.setValue(conf.get()); });
		return slider;
	}

	UIToggle& SettingsDialogPage::addToggle(ConfigItem<bool>& conf, strv name)
	{
		SettingsDialogCache<bool>& cache = static_cast<SettingsDialogCache<bool>&>(confs.emplace_back(SettingsDialogCache<bool>(conf)));
		UIToggle& toggle = stackElementYDir(std::make_unique<UIToggle>(new RelativeHitbox(*hb, 100, 100), name));
		toggle.setToggleState(conf.get())
			.setOnClick([&conf](const UIToggle& toggle) {conf.set(toggle.toggled); });
		cache.setOnReset([&toggle, &conf]() {toggle.toggle(conf.get()); });
		return toggle;
	}

	template<typename T, c_itr<T> Iterable> UIDropdown<T>& SettingsDialogPage::addDropdown(ConfigItem<T>& conf, strv name, Iterable& items, func<str(const T&)> labelFunc)
	{
		SettingsDialogCache<T>& cache = static_cast<SettingsDialogCache<T>&>(confs.emplace_back(SettingsDialogCache<T>(conf)));
		UIDropdown<T> dr = stackElementYDir(UIDropdown<T>::singleMenu(new RelativeHitbox(*hb, 200, 100), labelFunc));
		dr.setItems(items)
			.updateSelection({ conf.get() })
			.setOnChange([conf](vec<T*>& items) { if (items.size() > 0) conf.set(items[0]); })
			.withLabel(name);
		cache.setOnReset([&dr, &conf]() {dr.selectSelection(conf.get()); });
		return dr;
	}

	void SettingsDialogPage::reset()
	{
		for (const SettingsDialogBaseCache& conf : confs) {
			conf.onReset();
		}
	}
}