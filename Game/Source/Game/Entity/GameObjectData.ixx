export module fbc.GameObjectData;

import fbc.BaseContent;
import fbc.ContentRegisterable;
import fbc.FUtil;
import fbc.ObjectStrings;

namespace fbc {
	export template <typename T> class GameObjectData : public ContentRegisterable<T> {
	public:
		ObjectStrings* strings;
	protected:
		GameObjectData(BaseContent& source, strv id) : ContentRegisterable<T>(source, id) {}
	private:
		//map<str,str> customFields;
	};
}