export module fbc.GameObject;

import fbc.FUtil;
import fbc.GameObjectData;
import sdl;
import std;

export namespace fbc {
	export template <c_ext<GameObjectData> T = GameObjectData> class GameObject {
	public:
		GameObject(T& data): data(data) {}
		virtual ~GameObject() {}

		const T& data;

		inline strv description(int ind) { return data.strings && ind < data.strings->DESCRIPTION.size() ? data.strings->DESCRIPTION[ind] : futil::BLANK; }
		inline strv name() { return data.strings ? data.strings.NAME : futil::BLANK; }
	};
}