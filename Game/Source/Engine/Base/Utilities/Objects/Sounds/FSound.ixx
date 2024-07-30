export module fbc.FSound;

import fbc.FUtil;
import fbc.ILoadable;
import sdl;
import std;

namespace fbc {
	export class FSound : public ILoadable {
	public:
		FSound(strv path) : path(path) {}
		FSound(const FSound&) = delete;
		~FSound() override {
			// Unload sound when destroyed
			if (sound && sdl::sdlEnabled()) {
				sdl::soundFree(sound);
				sound = nullptr;
			}
		}

		inline void play(int loops = 0, int time = -1) const { sdl::soundPlay(sound, loops, time); }
		inline void playFade(int fade, int loops = 0, int time = -1) const { sdl::soundPlayFade(sound, fade, loops, time); }

		void dispose() override;
		void reload() const override;
	private:
		mutable sdl::Sound* sound;
		str path;
	};

	void FSound::dispose()
	{
		sdl::soundFree(sound);
		sound = nullptr;
	}

	void FSound::reload() const
	{
		if (sound) {
			sdl::soundFree(sound);
		}
		sound = sdl::soundLoad(path.data());
		if (sound == nullptr) {
			sdl::logError("Failed to load sound %s: %s", path, sdl::getError());
		}
	}
}