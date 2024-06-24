export module fbc.GameObjectData;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.ObjectStrings;
import std;

export namespace fbc {
	export class GameObjectData {
	public:
		GameObjectData(BaseContent& source, strv ID): source(source), ID(ID) {}
		virtual ~GameObjectData() {}

		const BaseContent& source;
		const str ID;
		ObjectStrings* strings;
	};
}