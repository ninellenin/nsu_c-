#ifndef XOR_LINKED_LIST_TEST_H
#define XOR_LINKED_LIST_TEST_H

#include <algorithm>
#include <cassert>
#include <iostream>

#include "xor_linked_list.h"

template <class T>
bool operator==(const XorLinkedList<T>& list1, const XorLinkedList<T>& list2) {
    if (list1.size() != list2.size()) {
        return false;
    }
    auto it1 = list1.begin();
    auto it2 = list2.begin();
    while (it1 != list1.end()) {
        if (*it1 != *it2) {
            return false;
        }
        ++it1;
        ++it2;
    }

    return true;
}

void push_back_test() {
    XorLinkedList<int, std::allocator<int>> list;
    XorLinkedList<int> expected({3, 2, 1});

    list.push_back(3);
    list.push_back(2);
    list.push_back(1);

    assert(list == expected);
}

void begin_test() {
    XorLinkedList<int, std::allocator<int>> list;
    list.push_back(1);
    list.push_back(2);
    assert(*list.begin() == 1);
}

void end_test() {
    XorLinkedList<int, std::allocator<int>> list;
    list.push_back(1);
    list.push_back(2);
    auto it1 = list.end();
    assert(*(++it1) == 1);
    auto it2 = list.end();
    assert(*(--it2) == 2);
}

void front_test() {
    XorLinkedList<int, std::allocator<int>> list;
    list.push_back(1);
    list.push_back(2);
    assert(list.front() == 1);
}

void back_test() {
    XorLinkedList<int, std::allocator<int>> list;
    list.push_back(1);
    list.push_back(2);
    assert(list.back() == 2);
}

void erase_test() {
    XorLinkedList<int, std::allocator<int>> list({1, 2, 3});
    XorLinkedList<int, std::allocator<int>> expected({2, 3});
    list.erase(list.begin());
    assert(list == expected);
}

void swap_test() {
    XorLinkedList<int, std::allocator<int>> list1({1, 2, 3});
    XorLinkedList<int, std::allocator<int>> list2({2, 3});
    XorLinkedList<int, std::allocator<int>> list3({2, 3});
    list1.swap(list2);
    assert(list1 == list3);
}

void reverse_test() {
    XorLinkedList<int, std::allocator<int>> list({1, 2, 3, 4});
    XorLinkedList<int, std::allocator<int>> expected({4, 3, 2, 1});
    list.reverse();
    assert(list == expected);
}

void unique_test() {
    XorLinkedList<int, std::allocator<int>> list({1, 1, 2, 3});
    XorLinkedList<int, std::allocator<int>> expected({1, 2, 3});
    list.unique();
    assert(list == expected);
}

void max_elem_test() {
    XorLinkedList<int, std::allocator<int>> list({1, 7, 2, 3});
    auto max = std::max_element(list.begin(), list.end());
    assert(*max == 7);
}

void sort_test() {
    XorLinkedList<int, std::allocator<int>> list({1, 6, 2, 3});
    XorLinkedList<int, std::allocator<int>> expected({1, 2, 3, 6});
    list.sort();
    assert(list == expected);
}


void test() {
    push_back_test();
    begin_test();
    end_test();
    front_test();
    back_test();
    erase_test();
    swap_test();
    reverse_test();
    unique_test();
    max_elem_test();
    sort_test();
}




#endif // XOR_LINKED_LIST_TEST_H
