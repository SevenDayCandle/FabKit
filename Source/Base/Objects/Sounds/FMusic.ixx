export module fab.FMusic;

import fab.FUtil;
import fab.ILoadable;
import sdl.SDLBase; 
import sdl.SDLRunner;
import std;

namespace fab {
	export class FMusic : public ILoadable {
	public:
		FMusic(strv path) : path(path) {}
		FMusic(const FMusic&) = delete;
		~FMusic() override {
			// Unload when destroyed
			if (music && sdl::runner::enabled()) {
				sdl::musicFree(music);
				music = nullptr;
			}
		}

		inline void play(int loops = -1) const { sdl::musicPlay(music, loops); }
		inline void playFade(int fade, int loops = -1) const { sdl::musicPlayFade(music, fade, loops); }

		void dispose() override;
		void reload() const override;
	private:
		mutable sdl::Music* music;
		str path;
	};

	void FMusic::dispose()
	{
		sdl::musicFree(music);
		music = nullptr;
	}

	void FMusic::reload() const
	{
		if (music) {
			sdl::musicFree(music);
		}
		music = sdl::musicLoad(path.data());
		if (music == nullptr) {
			sdl::logError("Failed to load music %s: %s", path, sdl::getError());
		}
	}
};