export module fbc.IOverlay;

export namespace fbc {
	export struct IOverlay {
	public:
		virtual ~IOverlay() {}

		inline virtual void dispose() {};
		inline virtual void open() {}
		inline virtual void refreshHb() {}  // Force resizing of hitboxes when the screen size changes
		inline virtual void refreshRenderables () {}  // Force regeneration of generated images (e.g. text) when the renderer is remade

		virtual void render() = 0;
		virtual void update() = 0;
	protected:
		IOverlay() {}
	};
}