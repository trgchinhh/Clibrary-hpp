#pragma once

#define ONLY_HEADER_LIST_CPP
#ifdef ONLY_HEADER_LIST_CPP

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <iterator>

template <typename T>
class List {
private:
    T* arr;             
    size_t size;        
    size_t cap;         

    void reserve_more(size_t new_cap) {
        if (new_cap <= cap) return;
        T* new_arr = static_cast<T*>(::operator new[](new_cap * sizeof(T)));
        for (size_t i = 0; i < size; i++) {
            new (&new_arr[i]) T(std::move(arr[i]));
            arr[i].~T(); 
        }
        ::operator delete[](arr);
        arr = new_arr;
        cap = new_cap;
    }

    // SFINAE mechanism to detect printable types at compile time
    template <typename U>
    static auto test_printable(int) -> decltype(std::declval<std::ostream&>() << std::declval<const U&>(), std::true_type{});
    
    template <typename U>
    static std::false_type test_printable(...);

    template <typename U>
    using is_printable = decltype(test_printable<U>(0));

    static void print_element(std::ostream& os, const T& val, std::true_type) {
        os << val << " ";
    }

    static void print_element(std::ostream& os, const T& val, std::false_type) {
        os << "[Object@" << &val << "] "; 
    }

public:
    List() : arr(nullptr), size(0), cap(4) {
        arr = static_cast<T*>(::operator new[](cap * sizeof(T)));
    }

    List(std::initializer_list<T> init) : size(0), cap(init.size() * 2) {
        arr = static_cast<T*>(::operator new[](cap * sizeof(T)));
        for (const auto& item : init) {
            new (&arr[size++]) T(item); 
        }
    }

    List(size_t initial_size, const T& value = T()) : size(initial_size), cap(initial_size * 2) {
        arr = static_cast<T*>(::operator new[](cap * sizeof(T)));
        for (size_t i = 0; i < size; i++) {
            new (&arr[i]) T(value); 
        }
    }

    List(const List& other) : size(other.size), cap(other.cap) {
        arr = static_cast<T*>(::operator new[](cap * sizeof(T)));
        for (size_t i = 0; i < size; i++) {
            new (&arr[i]) T(other.arr[i]);
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            ::operator delete[](arr);
            size = other.size;
            cap = other.cap;
            arr = static_cast<T*>(::operator new[](cap * sizeof(T)));
            for (size_t i = 0; i < size; i++) {
                new (&arr[i]) T(other.arr[i]);
            }
        }
        return *this;
    }

    List(List&& other) noexcept : arr(other.arr), size(other.size), cap(other.cap) {
        other.arr = nullptr;
        other.size = 0;
        other.cap = 0;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            ::operator delete[](arr);
            arr = other.arr;
            size = other.size;
            cap = other.cap;
            other.arr = nullptr;
            other.size = 0;
            other.cap = 0;
        }
        return *this;
    }

    ~List() {
        clear();
        if (arr) ::operator delete[](arr);
    }

    void push(T&& data) {
        if (size >= cap) reserve_more(cap == 0 ? 4 : cap * 2);
        new (&arr[size++]) T(std::move(data));
    }

    void push(const T& data) {
        if (size >= cap) reserve_more(cap == 0 ? 4 : cap * 2);
        new (&arr[size++]) T(data);
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (size >= cap) reserve_more(cap == 0 ? 4 : cap * 2);
        new (&arr[size++]) T(std::forward<Args>(args)...);
    }

    void pop() {
        if (size == 0) throw std::runtime_error("List is empty");
        size--;
        arr[size].~T(); 
    }

    void resize(size_t new_size, const T& value = T()) {
        if (new_size < size) {
            for (size_t i = new_size; i < size; i++) arr[i].~T();
        } else if (new_size > size) {
            if (new_size > cap) reserve_more(new_size);
            for (size_t i = size; i < new_size; i++) new (&arr[i]) T(value);
        }
        size = new_size;
    }

    void shrink_to_fit() {
        if (size == cap) return;
        if (size == 0) {
            ::operator delete[](arr);
            arr = nullptr;
            cap = 0;
            return;
        }
        T* new_arr = static_cast<T*>(::operator new[](size * sizeof(T)));
        for (size_t i = 0; i < size; i++) {
            new (&new_arr[i]) T(std::move(arr[i]));
            arr[i].~T();
        }
        ::operator delete[](arr);
        arr = new_arr;
        cap = size;
    }

    T& front() { if (size == 0) throw std::runtime_error("List is empty"); return arr[0]; }
    const T& front() const { if (size == 0) throw std::runtime_error("List is empty"); return arr[0]; }
    T& back() { if (size == 0) throw std::runtime_error("List is empty"); return arr[size - 1]; }
    const T& back() const { if (size == 0) throw std::runtime_error("List is empty"); return arr[size - 1]; }

    void clear() {
        for (size_t i = 0; i < size; i++) arr[i].~T();
        size = 0;
    }

    bool empty() const { return size == 0; }
    size_t capacity() const { return cap; }
    size_t getsize() const { return size; }

    T& operator[](size_t index) { return arr[index]; }
    const T& operator[](size_t index) const { return arr[index]; }

    T& at(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return arr[index];
    }
    const T& at(size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return arr[index];
    }

    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (size >= cap) reserve_more(cap * 2);
        for (size_t i = size; i > index; i--) {
            new (&arr[i]) T(std::move(arr[i - 1]));
            arr[i - 1].~T();
        }
        new (&arr[index]) T(value);
        size++;
    }

    void erase(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        arr[index].~T();
        for (size_t i = index; i < size - 1; i++) {
            new (&arr[i]) T(std::move(arr[i + 1]));
            arr[i + 1].~T();
        }
        size--;
    }

    long long find(const T& value) const {
        for (size_t i = 0; i < size; i++) if (arr[i] == value) return i;
        return -1;
    }

    bool contains(const T& value) const { return find(value) != -1; }
    void reverse() { std::reverse(arr, arr + size); }
    void sort() { std::sort(arr, arr + size); }

    T* begin() { return arr; }
    T* end() { return arr + size; }
    const T* begin() const { return arr; }
    const T* end() const { return arr + size; }

    std::reverse_iterator<T*> rbegin() { return std::reverse_iterator<T*>(end()); }
    std::reverse_iterator<T*> rend() { return std::reverse_iterator<T*>(begin()); }
    std::reverse_iterator<const T*> rbegin() const { return std::reverse_iterator<const T*>(end()); }
    std::reverse_iterator<const T*> rend() const { return std::reverse_iterator<const T*>(begin()); }

    friend std::ostream& operator<<(std::ostream& os, const List& l) {
        for (size_t i = 0; i < l.size; i++) {
            print_element(os, l.arr[i], is_printable<T>{});
        }
        return os;
    }
};

#endif