max_heap.h
==========

This is a C++ header file that implements a max heap data structure. It provides a class called max_heap. The max_heap class supports insertion, retrieval of the maximum value, and removal of the maximum value from the heap.

Usage:
------

To use the max_heap class, include the max_heap.h header file in your C++ code.

#include "max_heap.h"
Class Definition
The max_heap class is defined as follows:

namespace pic10c {
    template <typename T, typename compare_type = std::less<T>>
    class max_heap {
        // Class members and methods
    };
}

Constructor:
------------
The max_heap class provides a default constructor that accepts an optional comparison function object. The default comparison function is std::less<T>, which uses the < operator to compare elements.


max_heap(const compare_type& compare = compare_type{});

Member Functions:
-----------------
The max_heap class provides the following member functions:

void insert(const T& foo): Inserts an lvalue foo into the heap.
void insert(const T&& foo): Inserts an rvalue foo into the heap.
size_t size() const: Returns the number of elements in the heap.
T top() const: Returns the maximum value from the heap.
void pop(): Removes the maximum value from the heap.
Helper Functions
The max_heap class also includes some private helper functions used internally:

void promote(T foo): Helper function used to demote the parent value if the new value is larger.
size_t index_p(size_t i) const: Returns the index of the parent node.
size_t index_l(size_t i) const: Returns the index of the left child.
size_t index_r(size_t i) const: Returns the index of the right child.
T get_p(size_t i) const: Returns the value of the parent node.
T get_l(size_t i) const: Returns the value of the left child.
T get_r(size_t i) const: Returns the value of the right child.
Example Usage

Here's an example demonstrating the usage of the max_heap class:

#include <iostream>
#include "max_heap.h"

int main() {
    pic10c::max_heap<int> heap;

    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);

    std::cout << "Heap size: " << heap.size() << std::endl;
    std::cout << "Maximum value: " << heap.top() << std::endl;

    heap.pop();

    std::cout << "Heap size after pop: " << heap.size() << std::endl;
    std::cout << "New maximum value: " << heap.top() << std::endl;

    return 0;
}

Output:
-------
Heap size: 4
Maximum value: 20
Heap size after pop: 3
New maximum value: 15
