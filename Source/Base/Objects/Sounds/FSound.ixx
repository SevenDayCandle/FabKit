module;

#include "SDL3_mixer/SDL_mixer.h"

export module fab.FSound;

import fab.FUtil;
import fab.ILoadable;
import sdl.SDLHelpers;
import sdl.SDLProps;
import sdl.SDLRunner;
import std;

namespace fab {
	export class FSound : public ILoadable {
	public:
		FSound(strv path, int index = sdl::runner::MIXER_SOUND) : index(index), path(path) {}
		FSound(const FSound&) = delete;
		~FSound() override { FSound::dispose(); }

		void dispose() override;
		void play(int loops = 0) const;
		void reload() const override;
	private:
		int index;
		mutable ::MIX_Audio* sound;
		str path;
	};

	void FSound::dispose() {
		if (sound && sdl::runner::enabled()) {
			MIX_DestroyAudio(sound);
			sound = nullptr;
		}
	}

	void FSound::play(int loops) const {
		if (sound) {
			::MIX_Track* track = sdl::runner::requestTrack(index);
			MIX_SetTrackAudio(track, sound);

			// TODO more properties like fade
			if (loops > 0) {
				sdl::SDLProps props = sdl::SDLProps();
				props.setInt(MIX_PROP_PLAY_LOOPS_NUMBER, loops);
				MIX_PlayTrack(track, props);
			}
			else {
				MIX_PlayTrack(track, 0);
			}
		}
	}

	void FSound::reload() const {
		if (sound) {
			MIX_DestroyAudio(sound);
		}
		sound = sdl::runner::mixerLoadAudio(index, path.data(), false);
		if (sound == nullptr) {
			sdl::logError("Failed to load sound %s: %s", path, sdl::getError());
		}
	}
}
