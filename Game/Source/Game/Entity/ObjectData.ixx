export module fbc.ObjectData;

import fbc.BaseContent;
import fbc.FUtil;
import std;

export namespace fbc {
	export class ObjectData {
	public:
		ObjectData(BaseContent& source, strv ID): source(source), ID(ID) {}
		virtual ~ObjectData() {}

		const BaseContent& source;
		const str ID;
	};
}