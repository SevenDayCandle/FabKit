export module fbc.DynamicContent;

import fbc.FUtil;
import fbc.FTexture;
import fbc.FSound;
import fbc.BaseContent;
import fbc.DynamicLoadables;
import sdl;
import std;

export namespace fbc {
	export class DynamicContent : public BaseContent {
	public:
		DynamicContent(strv ID, strv folder): BaseContent(ID, folder) {}
		virtual ~DynamicContent() {}

		DynamicLoadables<FSound> sounds = DynamicLoadables(*this);
		DynamicLoadables<FTexture> images = DynamicLoadables(*this);
	};
}