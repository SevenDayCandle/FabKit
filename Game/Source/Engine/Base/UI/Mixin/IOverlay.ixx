export module fbc.IOverlay;

export namespace fbc {
	export class IOverlay {
	public:
		virtual ~IOverlay() {}

		inline virtual void close() {}
		inline virtual void open() {}
		inline virtual void refreshHb() {}

		virtual void render() = 0;
		virtual void update() = 0;
	protected:
		IOverlay() {}
	};
}