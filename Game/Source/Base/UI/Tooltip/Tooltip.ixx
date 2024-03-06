export module fbc.tooltip;

export namespace fbc::tooltip {
	export class Tooltip {
	public:
		virtual void dispose();
		virtual void render();
		virtual void update();
	};
}