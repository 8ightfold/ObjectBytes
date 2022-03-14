#ifndef BYTE_HEX_HPP
#define BYTE_HEX_HPP
#include <iostream>
#include <type_traits>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <array>

//l-value
template <class T>
void _bytes(T& item) {
    
    using T_val = typename std::remove_reference<decltype(item)>::type;

    const size_t bytes = sizeof(item);

    std::array<char, bytes> bytes_print;
    memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

    std::stringstream ss;

    ss << typeid(T_val).name() << " (" << bytes
        << ((bytes > 1) ? " Bytes): " : " Byte): ") << std::hex << std::uppercase;

    for (auto& c : bytes_print) {
        ss << ((abs(c) != c) ? "-" : "")
            << "0x"
            << std::setfill('0') << std::setw(sizeof(char) * 2)
            << (int)abs(c)
            << " ";
    }
    ss << (char)(0x08);
    std::cout << ss.str() << "\n" << "\x1b[38;5;15m";
};
template <class T>
void _bytes(T* (&item)) {
    
    using T_val = typename std::remove_reference<decltype(item)>::type;
    using T_val_child = typename std::remove_pointer<T_val>::type;

    const size_t bytes = sizeof(item), childBytes = sizeof(T_val_child);

    std::array<char, bytes> bytes_print;
    memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

    std::stringstream ss;

    ss << "\x1b[38;5;202mPointer:\x1b[38;5;223m " << typeid(T_val).name()
        << " (Pointer: " << bytes << ((bytes > 1) ? " Bytes;" : " Byte;")
        << " Pointee: " << childBytes << " Bytes): "
        << std::hex << std::uppercase;

    for (auto& c : bytes_print) {
        ss << ((abs(c) != c) ? "-" : "")
            << "0x"
            << std::setfill('0') << std::setw(sizeof(char) * 2)
            << (int)abs(c)
            << " ";
    }
    
    if(!item){
        ss << "\n\x1b[38;5;216m Pointee:\x1b[38;5;223m N/A (nullptr)";
        std::cout << ss.str() << "\n" << "\x1b[38;5;15m";
        return;
    }
    
    ss << (char)(0x08);
    std::cout << ss.str() << "\n";
    std::cout << "\x1b[38;5;216m Pointee:\x1b[38;5;223m ";

    _bytes(*item);
};
template <class T, size_t N>
void _bytes(T (&item)[N]) {
    using T_val = typename std::remove_reference<decltype(item)>::type;
    using T_val_a = typename std::remove_reference<decltype(item[0])>::type;
    static_assert(std::is_array<T_val>::value, "Must be an array.");

    const size_t bytes = sizeof(item), childBytes = sizeof(item[0]);
    const size_t arrBytes = bytes / childBytes;

    std::array<char, bytes> bytes_print;
    memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

    std::array<T_val_a, arrBytes> item_a;
    memcpy((void*)item_a.data(), &item, (size_t)item_a.size());
    
    std::stringstream ss;

    int len = childBytes / bytes;
    ss << "\x1b[38;5;159mParent:\x1b[38;5;195m " << typeid(T_val).name()
        << " (Total size: " << bytes << ((bytes > 1) ? " Bytes;" : " Byte;")
        << " Element size: " << childBytes << ((childBytes > 1) ? " Bytes):" : " Byte):")
        << std::hex << std::uppercase;
    std::cout << ss.str() << "\n";
    for (auto& child : item_a) {
        std::cout << " " << "\x1b[38;5;153mChild:\x1b[38;5;195m ";
        try { _bytes(child); }
        catch (const std::exception& e) { std::cout << "Error: " << e.what() << std::endl; }
    }
};

//r-value
template <class T>
void _bytes(T&& item) {

    using T_val = typename std::remove_reference<decltype(item)>::type;

    const size_t bytes = sizeof(item);

    std::array<char, bytes> bytes_print;
    memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

    std::stringstream ss;

    ss << typeid(T_val).name() << " (" << bytes
        << ((bytes > 1) ? " Bytes): " : " Byte): ") << std::hex << std::uppercase;

    for (auto& c : bytes_print) {
        ss << ((abs(c) != c) ? "-" : "")
            << "0x"
            << std::setfill('0') << std::setw(sizeof(char) * 2)
            << (int)abs(c)
            << " ";
    }
    ss << (char)(0x08);
    std::cout << ss.str() << "\n" << "\x1b[38;5;15m";
};
template <class T>
void _bytes(T* (&&item)) {

    using T_val = typename std::remove_reference<decltype(item)>::type;
    using T_val_child = typename std::remove_pointer<T_val>::type;

    const size_t bytes = sizeof(item), childBytes = sizeof(T_val_child);

    std::array<char, bytes> bytes_print;
    memcpy((void*)bytes_print.data(), &item, (size_t)bytes_print.size());

    std::stringstream ss;

    ss << "\x1b[38;5;202mPointer:\x1b[38;5;223m " << typeid(T_val).name()
        << " (Pointer: " << bytes << ((bytes > 1) ? " Bytes;" : " Byte;")
        << " Pointee: " << childBytes << " Bytes): "
        << std::hex << std::uppercase;

    for (auto& c : bytes_print) {
        ss << ((abs(c) != c) ? "-" : "")
            << "0x"
            << std::setfill('0') << std::setw(sizeof(char) * 2)
            << (int)abs(c)
            << " ";
    }

    if (!item) {
        ss << "\n\x1b[38;5;216m Pointee:\x1b[38;5;223m N/A (nullptr)";
        std::cout << ss.str() << "\n" << "\x1b[38;5;15m";
        return;
    }

    ss << (char)(0x08);
    std::cout << ss.str() << "\n";
    std::cout << "\x1b[38;5;216m Pointee:\x1b[38;5;223m ";

    _bytes(*item);
};
template <class T, size_t N>
void _bytes(T(&&item)[N]) {
    using T_val = typename std::remove_reference<decltype(item)>::type;
    using T_val_a = typename std::remove_reference<decltype(item[0])>::type;
    static_assert(std::is_array<T_val>::value, "Must be an array.");

    const size_t bytes = sizeof(item), childBytes = sizeof(item[0]);
    const size_t arrBytes = bytes / childBytes;

    std::array<char, bytes> bytes_print;
    memcpy((void*)bytes_print.data(), &item, sizeof(item));

    std::array<T_val_a, arrBytes> item_a;
    memcpy((void*)item_a.data(), &item, (size_t)item_a.size());

    std::stringstream ss;

    int len = childBytes / bytes;
    ss << "\x1b[38;5;159mParent:\x1b[38;5;195m " << typeid(T_val).name()
        << " (Total size: " << bytes << ((bytes > 1) ? " Bytes;" : " Byte;")
        << " Element size: " << childBytes << ((childBytes > 1) ? " Bytes):" : " Byte):")
        << std::hex << std::uppercase;
    std::cout << ss.str() << "\n";
    for (auto& child : item_a) {
        std::cout << " " << "\x1b[38;5;153mChild:\x1b[38;5;195m ";
        try { _bytes(child); }
        catch (const std::exception& e) { std::cout << "Error: " << e.what() << std::endl; }
    }
};

#endif
