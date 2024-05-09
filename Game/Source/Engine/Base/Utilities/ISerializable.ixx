export module fbc.Iserializable;

import std;

export namespace fbc {
	export struct ISerializable {
	public:
		virtual ~ISerializable() {}

		operator std::string() const { return write(); }
		friend std::ostream& operator<<(std::ostream& os, const ISerializable& obj) { return os << obj; }

		virtual void read(std::string& str) = 0;
		virtual std::string write() const = 0;
	};
}