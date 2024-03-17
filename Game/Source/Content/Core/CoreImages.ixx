export module fbc.coreImages;

import fbc.baseContent;
import fbc.baseImages;
import fbc.coreConfig;
import fbc.futil;
import raylib;

export namespace fbc {
	export class CoreImages : public fbc::BaseImages {
	public:
		CoreImages(fbc::BaseContent& cnt) : fbc::BaseImages(cnt) {}

		inline FTexture& squareButton() { return getTexture("UI/SquareButton.png"); };
	};
}