export module fbc.uiBase;

export namespace fbc::cpt {
	export class UIBase {
	public:
		virtual ~UIBase() {}

		bool enabled;

		virtual void close();
		virtual void dispose();
		virtual void renderImpl();
		virtual void updateImpl();

		void render() {
			if (enabled) {
				renderImpl();
			}
		}
		void update() {
			if (enabled) {
				updateImpl();
			}
		}
	};
}