export module fbc.uiBase;

export namespace fbc {
	export class UIBase {
	public:
		virtual ~UIBase() {}

		bool enabled = true;

		inline virtual void close() {}
		inline virtual void open() {}

		virtual void render();
		virtual void update();

		virtual void renderImpl() = 0;
		virtual void updateImpl() = 0;
	};

	void UIBase::render() {
		if (enabled) {
			renderImpl();
		}
	}

	void UIBase::update() {
		if (enabled) {
			updateImpl();
		}
	}
}