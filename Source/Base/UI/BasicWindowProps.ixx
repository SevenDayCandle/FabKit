export module fab.BasicWindowProps;

import fab.FFont;
import fab.FUtil;
import fab.FWindow;

namespace fab {
	constexpr float BASE_DENOMINATOR = 2160;

	export class BasicWindowProps : public FWindow::IProps {
	public:
		BasicWindowProps(const char* title, FFont& font, int resX, int resY): IProps(), title(title), font(font), resX(resX), resY(resY), scale(resY / BASE_DENOMINATOR) {}

		const char* title;
		FFont& font;

		virtual const char* getTitle() { return title; }
		virtual FFont& fontRegular() const { return font; }
		virtual float fontScale() const noexcept { return scale; }
		virtual float renderScale() const noexcept { return scale; }
		virtual int getResolutionX() const noexcept { return resX; }
		virtual int getResolutionY() const noexcept { return resY; }
	private:
		int resX;
		int resY;
		int scale;
	};
}