export module fbc.GameObject;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.GameObjectData;
import fbc.ObjectStrings;
import sdl;
import std;

export namespace fbc {
	export class GameObject {
	public:
		GameObject() {}
		virtual ~GameObject() {}

		virtual BaseContent& source() = 0;
		virtual ObjectStrings* strings() = 0;
		virtual strv id() = 0;
	};

	export template <c_ext<GameObjectData> T> class GameObjectDerived : public GameObject {
	public:
		GameObjectDerived(T& data) : data(data), GameObject() {}
		virtual ~GameObjectDerived() {}

		const T& data;

		inline BaseContent& source() override { return data.source; }
		inline ObjectStrings* strings() override { return data.strings; }
		inline strv description(int ind) { return data.strings && ind < data.strings->DESCRIPTION.size() ? data.strings->DESCRIPTION[ind] : futil::BLANK; }
		inline strv id() override { return data.id; }
		inline strv name() { return data.strings ? data.strings.NAME : futil::BLANK; }
	};
}