export module fbc.GameObjectData;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.ContentRegisterable;
import fbc.ObjectStrings;
import std;

namespace fbc {
	export class GameObjectData {
	public:
		GameObjectData(GameObjectData&& other) = default;
		virtual ~GameObjectData() = default;

		const str id;
		BaseContent& source;
		ObjectStrings* strings;
	protected:
		GameObjectData(BaseContent& source, strv id) : source(source), id(id) {}
	private:
		//map<str,str> customFields;
	};

	export template <typename T> class GameObjectDataDerived : public GameObjectData, public ContentRegisterable<T> {
	public:
		operator strv() const override { return id; }
	protected:
		GameObjectDataDerived(BaseContent& source, strv id) : GameObjectData(source, id) {}
	};
}