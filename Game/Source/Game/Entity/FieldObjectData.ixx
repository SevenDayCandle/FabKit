export module fbc.FieldObjectData;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.GameObjectData;
import fbc.ObjectStrings;
import std;

export namespace fbc {
	export class FieldObjectData : public GameObjectData {
	public:
		FieldObjectData(BaseContent& source, strv ID) : GameObjectData(source, ID) {}
		virtual ~FieldObjectData() {}
	};
}