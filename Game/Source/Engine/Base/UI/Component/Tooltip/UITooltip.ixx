export module fbc.UITooltip;

export namespace fbc {
	export class UITooltip {
	public:
		virtual void dispose();
		virtual void render();
		virtual void update();
	};
}