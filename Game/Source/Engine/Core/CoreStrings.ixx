export module fbc.CoreStrings;

import fbc.BaseContent;
import fbc.BaseStrings;
import fbc.CoreConfig;
import fbc.FUtil;
import fbc.KeywordStrings;
import std;

export namespace fbc {
	export class CoreStrings : public BaseStrings {
	public:
		CoreStrings(BaseContent& cnt) : BaseStrings(cnt) {}

		void initialize() override;

		inline str options_graphics_fps() const { return uiStrings.at("options_graphics_fps"); };
		inline str options_graphics_resolution() const { return uiStrings.at("options_graphics_resolution"); };
		inline str options_graphics_vsync() const { return uiStrings.at("options_graphics_vsync"); };
		inline str options_graphics_window_mode() const { return uiStrings.at("options_graphics_window_mode"); };
		inline str options_graphics_window_mode_borderless() const { return uiStrings.at("options_graphics_window_mode_borderless"); };
		inline str options_graphics_window_mode_fullscreen() const { return uiStrings.at("options_graphics_window_mode_fullscreen"); };
		inline str options_graphics_window_mode_windowed() const { return uiStrings.at("options_graphics_window_mode_windowed"); };
		inline str options_sound_effects() const { return uiStrings.at("options_sound_effects"); };
		inline str options_sound_master() const { return uiStrings.at("options_sound_master"); };
		inline str options_sound_music() const { return uiStrings.at("options_sound_music"); };
		inline str options_section_graphics() const { return uiStrings.at("options_section_graphics"); };
		inline str options_section_hotkeys() const { return uiStrings.at("options_section_hotkeys"); };
		inline str options_section_sound() const { return uiStrings.at("options_section_sound"); };
		inline str options_section_text() const { return uiStrings.at("options_section_text"); };
		inline str screen_setup_header() const { return uiStrings.at("screen_setup_header"); };
		inline str screen_title_header() const { return uiStrings.at("screen_title_header"); };
		inline str ui_apply() const { return uiStrings.at("ui_apply"); };
		inline str ui_cancel() const { return uiStrings.at("ui_cancel"); };
		inline str ui_close() const { return uiStrings.at("ui_close"); };
		inline str ui_confirm() const { return uiStrings.at("ui_confirm"); };
		inline str ui_items() const { return uiStrings.at("ui_items"); };
		inline str ui_items(int val) const { return std::vformat(ui_items(), std::make_format_args(val)); };
		inline str ui_save() const { return uiStrings.at("ui_save"); };
	private:
		umap<str, KeywordStrings> keywordStrings;
		umap<str, str> uiStrings;
	};

	// Core contains UI strings, keyword strings
	void CoreStrings::initialize()
	{
		loadUIStrings(uiStrings);
		loadKeywordStrings(keywordStrings);
	}
}