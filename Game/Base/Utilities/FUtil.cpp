#include <glaze/glaze.hpp>

module fbc.futil;

namespace fbc {

	template<typename T> T read_file_json(T input, str path) {
		glz::read_file_json(input, path, str{});
		return input;
	}

	template<typename T>
	T read_json(str input) {
		return glz::read_json(input);
	}

	template<typename T>
	str write_file_json(T input, str path) {
		str buffer = str{};
		glz::write_file_json(input, path, buffer);
		return buffer;
	}

	template<typename T>
	str write_json(T input) {
		return glz::write_json(input);
	}

}