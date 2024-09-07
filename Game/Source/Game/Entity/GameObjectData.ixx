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
		GameObjectData(BaseContent& source, strv id) : ContentRegisterable<T>(source, id), strings(source.getObjectStrings(T::LOCPATH, id)) {}
		GameObjectData(BaseContent& source, strv id, ObjectStrings* strings) : ContentRegisterable<T>(source, id), strings(strings) {}
	private:
		//map<str,str> customFields;
	};
}