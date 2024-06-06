export module fbc.IOverlay;

export namespace fbc {
	export struct IOverlay {
	public:
		virtual ~IOverlay() {}

		inline virtual void dispose() {};
		inline virtual void open() {}
		inline virtual void refreshDimensions() {}  // Force resizing of hitboxes when the screen size changes

		virtual void render() = 0;
		virtual void update() = 0;
	protected:
		IOverlay() {}
	};
}