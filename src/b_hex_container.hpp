#ifndef BYTE_HEX_CONTAINER_HPP
#define BYTE_HEX_CONTAINER_HPP
#include "b_hex.hpp"
#include "is_stl_container.hpp"

//l-value
template <class T>
void _bytes_container(T& item) {
	typedef std::remove_reference<decltype(item)>::type T_val;
	typedef std::remove_reference<decltype(item[0])>::type T_val_i;
	static_assert(is_stl_container<T_val>::value, "Must be an STL Container.");

	const size_t bytes = sizeof(item), childBytes = sizeof(item[0]);

	std::array<char, bytes> bytes_print;
	memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

	std::stringstream ss;

	ss << "\x1b[38;5;148mParent:\x1b[38;5;193m " << typeid(T_val).name()
		<< " (Container size: " << bytes << ((bytes > 1) ? " Bytes;" : " Byte;")
		<< " Index size: " << childBytes << ((childBytes > 1) ? " Bytes):" : " Byte):")
		<< std::hex << std::uppercase;
	std::cout << ss.str() << "\n";
	for (auto& child : item) {
		std::cout << " " << "\x1b[38;5;156mChild:\x1b[38;5;193m ";
		try { _bytes(child); }
		catch (const std::exception& e) { std::cout << "Error: " << e.what() << std::endl; }
	}

};

//r-value
template <class T>
void _bytes_container(T&& item) {
	typedef std::remove_reference<decltype(item)>::type T_val;
	typedef std::remove_reference<decltype(item[0])>::type T_val_i;
	static_assert(is_stl_container<T_val>::value, "Must be an STL Container.");

	const size_t bytes = sizeof(item), childBytes = sizeof(item[0]);

	std::array<char, bytes> bytes_print;
	memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

	std::stringstream ss;

	ss << "\x1b[38;5;148mParent:\x1b[38;5;193m " << typeid(T_val).name()
		<< " (Container size: " << bytes << ((bytes > 1) ? " Bytes;" : " Byte;")
		<< " Index size: " << childBytes << ((childBytes > 1) ? " Bytes):" : " Byte):")
		<< std::hex << std::uppercase;
	std::cout << ss.str() << "\n";
	for (auto& child : item) {
		std::cout << " " << "\x1b[38;5;156mChild:\x1b[38;5;193m ";
		try { _bytes(child); }
		catch (const std::exception& e) { std::cout << "Error: " << e.what() << std::endl; }
	}

};

#endif
