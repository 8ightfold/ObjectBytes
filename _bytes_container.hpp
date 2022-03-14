#ifndef BYTES_CONTAINER_HPP
#define BYTES_CONTAINER_HPP
#include "_bytes.hpp"

#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <type_traits>

//specialize a type for all of the STL containers.
//source: https://stackoverflow.com/a/31105859
namespace is_stl_container_impl {
	template <typename T>       struct is_stl_container :std::false_type {};
	template <typename T, std::size_t N> struct is_stl_container<std::array    <T, N>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::vector            <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::deque             <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::list              <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::forward_list      <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::set               <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::multiset          <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::map               <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::multimap          <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::unordered_set     <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::unordered_multiset<Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::unordered_map     <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::unordered_multimap<Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::stack             <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::queue             <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::priority_queue    <Args...>> :std::true_type {};
}
template <typename T> struct is_stl_container {
	static constexpr bool const value = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
};

//l-value
template <class T>
void _bytes_container(T& item) {
	typedef std::remove_reference<decltype(item)>::type T_val;
	typedef std::remove_reference<decltype(item[0])>::type T_val_i;
	static_assert(is_stl_container<T_val>::value, "Must be an STL Container.");

	int bytes = sizeof(item), childBytes = sizeof(item[0]);
	char bytes_print[sizeof(item)] = {};
	memcpy((void*)&bytes_print, &item, sizeof(bytes_print));

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

	int bytes = sizeof(item), childBytes = sizeof(item[0]);
	char bytes_print[sizeof(item)] = {};
	memcpy((void*)&bytes_print, &item, sizeof(bytes_print));

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
