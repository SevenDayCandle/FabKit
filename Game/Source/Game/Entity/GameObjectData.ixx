export module fbc.GameObjectData;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.IRegisterable;
import fbc.ObjectStrings;
import std;

export namespace fbc {
	export class GameObjectData {
	public:
		virtual ~GameObjectData() {}

		const str id;
		BaseContent& source;
		ObjectStrings* strings;
	protected:
		GameObjectData(BaseContent& source, strv id) : source(source), id(id) {}
	private:
		//map<str,str> customFields;
	};

	export template <typename T> class GameObjectDataDerived : public GameObjectData, public IRegisterable<T> {
	public:
		virtual ~GameObjectDataDerived() {}
	protected:
		GameObjectDataDerived(BaseContent& source, strv id) : GameObjectData(source, id) {}

		inline strv registrationID() const override { return id; } // Used for IRegisterable
	};
}