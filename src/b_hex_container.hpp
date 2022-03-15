#ifndef BYTE_HEX_CONTAINER_HPP
#define BYTE_HEX_CONTAINER_HPP
#include "b_hex.hpp"
#include "is_stl_container.hpp"

//bools. smh.
void _bytes_container(std::vector<bool>& item) {
	using T_val = typename std::remove_reference<decltype(item)>::type;
	using T_val_i = typename std::remove_reference<decltype(item[0])>::type;
	static_assert(is_stl_container<T_val>::value, "Must be an STL Container.");

	const size_t bytes = sizeof(item), childBytes = sizeof(item[0]);

	std::array<std::byte, bytes> bytes_print;
	memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

	std::stringstream ss;

	ss << "\x1b[38;5;148mParent:\x1b[38;5;193m " << typeid(T_val).name()
		<< " (Base size: " << bytes << ((bytes > 1) ? " Bytes;" : " Byte;")
		<< " Item count: " << item.size() << ((item.size() > 1) ? " Items;" : " Item;")
		<< " Item size: " << childBytes << ((childBytes > 1) ? " Bytes):" : " Byte):")
		<< std::hex << std::uppercase;

	std::cout << ss.str() << "\n";
	std::cout << "\x1b[38;5;148mDon't use bool vectors next time :)\x1b[38;5;193m\n";

	for (auto child : item) {
		//std::cout << " " << "\x1b[38;5;156mChild:\x1b[38;5;193m ";
		//_bytes(child);
		std::cout << child << " ";
	}
	std::cout << "\n" << "\x1b[38;5;15m";
}

//l-value
template <class T>
void _bytes_container(T& item) {
	using T_val = typename std::remove_reference<decltype(item)>::type;
	using T_val_i = typename std::remove_reference<decltype(item[0])>::type;
	static_assert(is_stl_container<T_val>::value, "Must be an STL Container.");

	const size_t bytes = sizeof(item), childBytes = sizeof(item[0]);

	std::array<char, bytes> bytes_print;
	memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

	std::stringstream ss;

	ss << "\x1b[38;5;148mParent:\x1b[38;5;193m " << typeid(T_val).name()
		<< " (Base size: " << bytes << ((bytes > 1) ? " Bytes;" : " Byte;")
		<< " Item count: " << item.size() << ((item.size() > 1) ? " Items;" : " Item;")
		<< " Item size: " << childBytes << ((childBytes > 1) ? " Bytes):" : " Byte):")
		<< std::hex << std::uppercase;

	std::cout << ss.str() << "\n";

	for (auto& child : item) {
		std::cout << " " << "\x1b[38;5;156mChild:\x1b[38;5;193m ";
		_bytes(child);
	}

};

//r-value
template <class T>
void _bytes_container(T&& item) {
	using T_val = typename std::remove_reference<decltype(item)>::type;
	using T_val_i = typename std::remove_reference<decltype(item[0])>::type;
	static_assert(is_stl_container<T_val>::value, "Must be an STL Container.");

	const size_t bytes = sizeof(item), childBytes = sizeof(item[0]);

	std::array<char, bytes> bytes_print;
	memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

	std::stringstream ss;

	ss << "\x1b[38;5;148mParent:\x1b[38;5;193m " << typeid(T_val).name()
		<< " (Base size: " << bytes << ((bytes > 1) ? " Bytes;" : " Byte;")
		<< " Item count: " << item.size() << ((item.size() > 1) ? " Items;" : " Item;")
		<< " Item size: " << childBytes << ((childBytes > 1) ? " Bytes):" : " Byte):")
		<< std::hex << std::uppercase;
	std::cout << ss.str() << "\n";
	for (auto& child : item) {
		std::cout << " " << "\x1b[38;5;156mChild:\x1b[38;5;193m ";
		_bytes(child);
	}

};

#endif
