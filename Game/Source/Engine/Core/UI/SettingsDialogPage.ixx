export module fbc.SettingsDialogPage;

import fbc.CoreContent;
import fbc.CoreConfig;
import fbc.ConfigItem;
import fbc.ConfigNumeric;
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
			SettingsDialogBaseCache() {}
			virtual ~SettingsDialogBaseCache() {}

			func<void()> onReset;

			inline void setOnReset(func<void()> onReset) { this->onReset = onReset; }

			virtual void commit() = 0;
		};

		template<typename T> class SettingsDialogCache : public SettingsDialogBaseCache {
		public:
			SettingsDialogCache(ConfigItem<T>& conf) : conf(conf), value(conf.get()) {}
			virtual ~SettingsDialogCache() override {}

			ConfigItem<T>& conf;
			T value;

			inline void commit() override { conf.set(value); }
		};

	public:
		SettingsDialogPage(Hitbox* hb, strv name): UICanvas(hb), name(name) {}
		virtual ~SettingsDialogPage() {}

		const str name;

		friend std::ostream& operator<<(std::ostream& os, const SettingsDialogPage& obj) { return os << obj.name; }

		inline UISlider& addSlider(ConfigNumeric& conf, strv name, float xOff = 400) { return addSlider(conf, name, conf.getMin(), conf.getMax(), xOff); }
		template <typename T, c_itr<T> Iterable> inline UIDropdown<T>& addDropdown(ConfigItem<T>& conf, strv name, const Iterable& items, func<str(const T&)> labelFunc = futil::toString<T>, int min = 1) { return addDropdownImpl<T, Iterable>(conf, name, items, labelFunc, min); }
		template <typename T, c_itr<T*> Iterable> inline UIDropdown<T>& addDropdown(ConfigItem<T>& conf, strv name, const Iterable& items, func<str(const T&)> labelFunc = futil::toString<T>, int min = 1) { return addDropdownImpl<T, Iterable>(conf, name, items, labelFunc, min); }
		template <typename T, typename U, c_itr<U> Iterable> inline UIDropdown<U>& addDropdownMapped(ConfigItem<T>& conf, strv name, Iterable& items, func<T(const U*)> convFunc, func<str(const T&)> labelFunc = futil::toString<T>, int min = 1) { return addDropdownMappedImpl<T, U, Iterable>(conf, name, items, convFunc, labelFunc, min); }
		template <typename T, typename U, c_itr<U*> Iterable> inline UIDropdown<U>& addDropdownMapped(ConfigItem<T>& conf, strv name, Iterable& items, func<T(const U*)> convFunc, func<str(const T&)> labelFunc = futil::toString<T>, int min = 1) { return addDropdownMappedImpl<T, U, Iterable>(conf, name, items, convFunc, labelFunc, min); }

		UINumberInput& addInputNum(ConfigItem<int>& conf, strv name);
		UITextInput& addInputText(ConfigItem<str>& conf, strv name);
		UISlider& addSlider(ConfigItem<int>& conf, strv name, int min, int max, float xOff = 400);
		UIToggle& addToggle(ConfigItem<bool>& conf, strv name);
		void commit();
		void reset();
	private:
		vec<uptr<SettingsDialogBaseCache>> confs;

		template <typename T, typename Iterable> UIDropdown<T>& addDropdownImpl(ConfigItem<T>& conf, strv name, const Iterable& items, func<str(const T&)> labelFunc = futil::toString<T>, int min = 1);
		template <typename T, typename U, typename Iterable> UIDropdown<U>& addDropdownMappedImpl(ConfigItem<T>& conf, strv name, const Iterable& items, func<T(const U*)> convFunc, func<str(const T&)> labelFunc = futil::toString<T>, int min = 1);
		float getOffsetFromLast();
	};


	UISlider& SettingsDialogPage::addSlider(ConfigItem<int>& conf, strv name, int min, int max, float xOff)
	{
		SettingsDialogCache<int>& cache = static_cast<SettingsDialogCache<int>&>(*confs.emplace_back(std::make_unique<SettingsDialogCache<int>>(conf)));
		UISlider& slider = stackElementYDir(std::make_unique<UISlider>(new RelativeHitbox(*hb, xOff, 0, 200, 100), min, max), 8, getOffsetFromLast());
		slider
			.setValue(conf.get())
			.setOnComplete([&cache](int val) {cache.value = val; })
			.withLabel(name, cct.fontBold(), -xOff, 25);
		cache.setOnReset([&slider, &conf]() {slider.setValue(conf.get()); });
		return slider;
	}

	UIToggle& SettingsDialogPage::addToggle(ConfigItem<bool>& conf, strv name)
	{
		SettingsDialogCache<bool>& cache = static_cast<SettingsDialogCache<bool>&>(*confs.emplace_back(std::make_unique<SettingsDialogCache<bool>>(conf)));
		UIToggle& toggle = stackElementYDir(std::make_unique<UIToggle>(new RelativeHitbox(*hb, 100, 100), name));
		toggle.setToggleState(conf.get())
			.setOnClick([&cache](const UIToggle& toggle) {cache.value = toggle.toggled; });
		cache.setOnReset([&toggle, &conf]() {toggle.toggle(conf.get()); });
		return toggle;
	}

	template<typename T, typename Iterable> UIDropdown<T>& SettingsDialogPage::addDropdownImpl(ConfigItem<T>& conf, strv name, const Iterable& items, func<str(const T&)> labelFunc, int min)
	{
		SettingsDialogCache<T>& cache = static_cast<SettingsDialogCache<T>&>(*confs.emplace_back(std::make_unique<SettingsDialogCache<T>>(conf)));
		UIDropdown<T>& dr = stackElementYDir(UIDropdown<T>::singleList(new RelativeHitbox(*hb, 400, 0, 500, 100), labelFunc), 8, getOffsetFromLast());
		dr.setItems(items)
			.setOnChange([&cache](vec<const T*> res) { if (res.size() > 0) cache.value = *res[0]; })
			.withLabel(name, cct.fontBold(), -400, 25);
		dr.updateSingle(conf.get());
		if (min > 0) {
			dr.setSelectionMin(min);
		}
		cache.setOnReset([&dr, &conf]() {dr.selectSingle(conf.get()); });
		return dr;
	}

	template<typename T, typename U, typename Iterable> UIDropdown<U>& SettingsDialogPage::addDropdownMappedImpl(ConfigItem<T>& conf, strv name, const Iterable& items, func<T(const U*)> convFunc, func<str(const T&)> labelFunc, int min)
	{
		SettingsDialogCache<T>& cache = static_cast<SettingsDialogCache<T>&>(*confs.emplace_back(std::make_unique<SettingsDialogCache<T>>(conf)));
		UIDropdown<U>& dr = stackElementYDir(UIDropdown<U>::singleList(new RelativeHitbox(*hb, 400, 0, 500, 100), labelFunc), 8, getOffsetFromLast());
		dr.setItems(items)
			.setOnChange([&cache, convFunc](vec<const U*> res) { if (res.size() > 0) cache.value = convFunc(res[0]); })
			.withLabel(name, cct.fontBold(), -400, 25);
		dr.updateSingle(conf.get());
		if (min > 0) {
			dr.setSelectionMin(min);
		}
		cache.setOnReset([&dr, &conf]() {dr.selectSingle(conf.get()); });
		return dr;
	}

	void SettingsDialogPage::commit()
	{
		for (const uptr<SettingsDialogBaseCache>& conf : confs) {
			conf->commit();
		}
	}

	void SettingsDialogPage::reset()
	{
		for (const uptr<SettingsDialogBaseCache>& conf : confs) {
			conf->onReset();
		}
	}

	float SettingsDialogPage::getOffsetFromLast()
	{
		UIBase* last = getLastItem();
		return last ? std::max(last->hb->x - last->getBeginX(), 0.0f) : 0;
	}
}