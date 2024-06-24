export module fbc.AttributeObjectData;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.GameObjectData;
import fbc.ObjectStrings;
import std;

export namespace fbc {
	export class AttributeObjectData : public GameObjectData {
	public:
		AttributeObjectData(BaseContent& source, strv ID) : GameObjectData(source, ID) {}
		virtual ~AttributeObjectData() {}
	};
}