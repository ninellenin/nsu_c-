#ifndef IS_ITERATOR_TESTER_H
#define IS_ITERATOR_TESTER_H

#include <type_traits>

template <typename T>
struct SfinaeTrue : std::true_type {};

struct IsIteratorTester {
    template <typename T>
    static SfinaeTrue<typename std::iterator_traits<T>::iterator_category> test(int);

    template <typename>
    static std::false_type test(...);
};

template <typename T>
struct IsIterator: decltype(IsIteratorTester::test<T>(0)) {};


#endif // IS_ITERATOR_TESTER_H
