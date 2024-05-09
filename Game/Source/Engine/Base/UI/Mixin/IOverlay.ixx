export module fbc.IOverlay;

export namespace fbc {
	export class IOverlay {
	public:
		IOverlay() {}
		virtual ~IOverlay() {}

		inline virtual void close() {}
		inline virtual void open() {}
		inline virtual void refreshSize() {}

		virtual void render() = 0;
		virtual void update() = 0;
	};
}