#ifndef XOR_LINKED_LIST_H
#define XOR_LINKED_LIST_H

#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <type_traits>

#include <is_iterator_tester.h>

enum class Enabler {};

template <typename Condition>
using EnableIf = typename std::enable_if<Condition::value, Enabler>::type;


template<class T, class Alloc = std::allocator<T> >
class XorLinkedList {
    using value_type = T;

    struct Element {
        value_type value;
        Element* next_xor_prev;

        Element();
        Element(const value_type& value);
        Element(value_type&& value);
        bool operator==(const Element &other) const;
        bool operator!=(const Element &other) const;
    };

    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = Element*;
    using const_pointer = Element * const;
    using allocator_type = typename std::allocator_traits<Alloc>::template rebind_alloc<Element>;

    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const value_type>{
    protected:
        friend XorLinkedList;
        Element* previous_;
        Element* current_;
        pointer next() const;
    public:
        const_iterator(pointer previous, pointer current);
        const_iterator(const const_iterator & other);
        const_iterator(const_iterator && other);
        const_iterator& operator=(const const_iterator& other);
        const_iterator& operator=(const_iterator&& other);
        bool operator==(const const_iterator& other) const;
        bool operator==(const_iterator&& other) const;
        bool operator!=(const const_iterator& other) const;
        bool operator!=(const_iterator&& other) const;
        const value_type& operator*() const;
        const value_type& operator->() const;
        const_iterator& operator++();
        const_iterator operator++(value_type);
        const_iterator& operator--();
        const_iterator operator--(value_type);

        virtual ~const_iterator();
    };

    class iterator: public const_iterator{
    public:
        iterator(pointer previous, pointer current);
        iterator(const iterator & other);
        iterator(iterator && other);
        iterator(const const_iterator & other);
        iterator(const_iterator && other);
        iterator& operator=(const iterator& other);
        iterator& operator=(iterator&& other);
        value_type& operator*();
        value_type& operator->();
        iterator& operator++();
        iterator operator++(value_type);
        iterator& operator--();
        iterator operator--(value_type);

        ~iterator();
    };


    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator> ;
    using difference_type = std::iterator_traits<iterator>;
    using size_type = size_t;

    allocator_type allocator_;
    Element* head_;
    Element* nil_;
    size_t size_;

    void initialize_();
    pointer get_element_(const_reference value);
    pointer get_element_(value_type &&value);
    iterator insert(const_iterator position, pointer element);


    template<class S>
    static S* xor_(S* first, S* second) {
        intptr_t first_ptr = reinterpret_cast<intptr_t>(first);
        intptr_t second_ptr = reinterpret_cast<intptr_t>(second);
        return reinterpret_cast<S*>(first_ptr ^ second_ptr);
    }

    template<class S, typename... Args>
    static S* xor_(S* first, S* second, Args... args) {
      return xor_(xor_(std::forward<S*>(first), std::forward<S*>(second)), args...);
    }

public:
/*
 * constructors
*/
    explicit XorLinkedList(allocator_type const & alloc = allocator_type());
    explicit XorLinkedList(size_t n);
    XorLinkedList(size_type n, const_reference val,
           const allocator_type& alloc = allocator_type());
    template <class TI, EnableIf<IsIterator<TI>>...>
    XorLinkedList(TI first, TI last, const allocator_type& alloc = allocator_type());
    XorLinkedList(const XorLinkedList& other);
    XorLinkedList(const XorLinkedList& other, const allocator_type& alloc);
    XorLinkedList(XorLinkedList&& other);
    XorLinkedList(XorLinkedList&& other, const allocator_type& alloc);
    XorLinkedList(std::initializer_list<value_type> il,
           const allocator_type& alloc = allocator_type());

/*
 * operator=
*/
    XorLinkedList& operator= (const XorLinkedList<T>& x);
    XorLinkedList& operator= (XorLinkedList<T>&& x);
    XorLinkedList& operator= (std::initializer_list<value_type> il);


/*
 * insert
 */
    iterator insert(const_iterator position, const value_type& value);
    iterator insert (const_iterator position, size_type n, const_reference val);
    template <class TI, EnableIf<IsIterator<TI>> ...>
    iterator insert (const_iterator position, TI first, TI last);
    iterator insert (const_iterator position, value_type&& val);
    iterator insert (const_iterator position, std::initializer_list<value_type> il);

/*
 * begin
 */
    iterator begin() noexcept;
    const_iterator begin() const noexcept;

/*
 * end
 */
    iterator end() noexcept;
    const_iterator end() const noexcept;

/*
 * capacity
 */
    size_t size() const noexcept;
    bool empty() const noexcept;

/*
 * front
 */
    reference front();
    const_reference front() const;

/*
 * back
 */
    reference back();
    const_reference back() const;

/*
 * assign
 */
    template <class TI, EnableIf<IsIterator<TI>>...>
    void assign (TI first, TI last);
    void assign (size_type n, const_reference val);

/*
 * push_front
 */
    void push_front(const_reference value);
    void push_front(value_type&& value);

/*
 * push_back
 */
    void push_back (const value_type& value);
    void push_back (value_type&& value);

/*
 * pop_back
 */
    void pop_back();

/*
 * pop_front
 */
    void pop_front();

/*
 * swap
 */
    void swap(XorLinkedList<T, Alloc>& other);

/*
 * resize
 */
    void resize(size_type n);
    void resize(size_type n, const value_type& val);

/*
 * splice
 */
    void splice(const_iterator position, XorLinkedList& other);
    void splice(const_iterator position, XorLinkedList&& other);
    void splice(const_iterator position, XorLinkedList& other, const_iterator it);
    void splice(const_iterator position, XorLinkedList&& other, const_iterator it);
    void splice(const_iterator position, XorLinkedList& other,
                 const_iterator first, const_iterator last);
    void splice(const_iterator position, XorLinkedList&& other,
                 const_iterator first, const_iterator last);

/*
 * reverse
 */
    void reverse() noexcept;

/*
 * sort
 */
    void sort();
    template <class Compare>
    void sort (Compare comp);
/*
 * merge
*/
    void merge (XorLinkedList<T>& x);
    void merge (XorLinkedList<T>&& x);
    template <class Compare>
      void merge (XorLinkedList<T>& x, Compare comp);
    template <class Compare>
      void merge (XorLinkedList<T>&& x, Compare comp);
/*
 * unique
 */
      void unique();
      template <class BinaryPredicate>
      void unique (BinaryPredicate binary_pred);

/*
 * erase
 */
    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);

/*
 * clear
 */
    void clear() noexcept;

    ~XorLinkedList() noexcept;
};



/*
 * ITERATOR BLOCK
 */

template <class T, class Alloc>
XorLinkedList<T, Alloc>::const_iterator::const_iterator(pointer previous, pointer current):
    previous_(previous),
    current_(current)
{}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::const_iterator::const_iterator(const const_iterator& other):
    previous_(other.previous_),
    current_(other.current_)
{}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::const_iterator::const_iterator(XorLinkedList<T, Alloc>::const_iterator && other):
    previous_(std::move(other.previous_)),
    current_(std::move(other.current_))
{}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::iterator::iterator(const const_iterator& other):
    const_iterator(other)
{}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::iterator::iterator(XorLinkedList<T, Alloc>::const_iterator && other):
    const_iterator(std::move(other))
{}


template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_iterator& XorLinkedList<T, Alloc>::const_iterator::operator=(
        const XorLinkedList<T, Alloc>::const_iterator& other)
{
    if (this != &other) {
        previous_ = other.previous_;
        current_ = other.current_;
    }

    return *this;
}


template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_iterator& XorLinkedList<T, Alloc>::const_iterator::operator=(
        XorLinkedList<T, Alloc>::const_iterator&& other)
{
    *this = std::move(other);

    return *this;
}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::iterator::iterator(pointer previous, pointer current):
    const_iterator(previous, current)
{}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::iterator::iterator(const iterator& other):
    const_iterator(other)
{}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::iterator::iterator(XorLinkedList<T, Alloc>::iterator && other):
    const_iterator(std::move(other))
{}


template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator& XorLinkedList<T, Alloc>::iterator::operator=(
        const XorLinkedList<T, Alloc>::iterator& other)
{
    if (this != &other) {
        this->previous_ = other.previous_;
        this->current_ = other.current_;
    }

    return *this;
}


template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator& XorLinkedList<T, Alloc>::iterator::operator=(
        XorLinkedList<T, Alloc>::iterator&& other)
{
    *this = std::move(other);

    return *this;
}

template <class T, class Alloc>
bool XorLinkedList<T, Alloc>::const_iterator::operator==(const XorLinkedList<T, Alloc>::const_iterator& other) const {
    return (current_ == other.current_);
}

template <class T, class Alloc>
bool XorLinkedList<T, Alloc>::const_iterator::operator==(XorLinkedList<T, Alloc>::const_iterator&& other) const {
    return (current_ == other.current_);
}

template <class T, class Alloc>
bool XorLinkedList<T, Alloc>::const_iterator::operator!=(const XorLinkedList<T, Alloc>::const_iterator& other) const {
    return !(*this == other);
}

template <class T, class Alloc>
bool XorLinkedList<T, Alloc>::const_iterator::operator!=(XorLinkedList<T, Alloc>::const_iterator&& other) const {
        return !(*this == other);
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::value_type& XorLinkedList<T, Alloc>::iterator::operator*() {
    return this->current_->value;
}

template <class T, class Alloc>
const typename XorLinkedList<T, Alloc>::value_type& XorLinkedList<T, Alloc>::const_iterator::operator*() const {
    return current_->value;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::value_type& XorLinkedList<T, Alloc>::iterator::operator->() {
    return this->current_->value;
}

template <class T, class Alloc>
const typename XorLinkedList<T, Alloc>::value_type& XorLinkedList<T, Alloc>::const_iterator::operator->() const{
    return current_->value;
}


template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_iterator& XorLinkedList<T, Alloc>::const_iterator::operator++(){
    pointer next = xor_(previous_, current_->next_xor_prev);
    previous_ = current_;
    current_ = next;

    return *this;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_iterator XorLinkedList<T, Alloc>::const_iterator::operator++(
        XorLinkedList<T, Alloc>::value_type) {
    const_iterator tmp = *this;
    ++(*this);

    return tmp;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_iterator& XorLinkedList<T, Alloc>::const_iterator::operator--() {
    pointer before_previous = xor_(current_, previous_->next_xor_prev);
    current_ = previous_;
    previous_ = before_previous;

    return *this;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_iterator XorLinkedList<T, Alloc>::const_iterator::operator--(
        XorLinkedList<T, Alloc>::value_type) {
    const_iterator tmp = *this;
    --(*this);

    return tmp;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator& XorLinkedList<T, Alloc>::iterator::operator++(){
    pointer next = xor_(this->previous_, this->current_->next_xor_prev);
    this->previous_ = this->current_;
    this->current_ = next;

    return *this;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::iterator::operator++(
        XorLinkedList<T, Alloc>::value_type) {
    iterator tmp = *this;
    ++(*this);

    return tmp;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator& XorLinkedList<T, Alloc>::iterator::operator--() {
    pointer before_previous = xor_(this->current_, this->previous_->next_xor_prev);
    this->current_ = this->previous_;
    this->previous_ = before_previous;
    return *this;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::iterator::operator--(
        XorLinkedList<T, Alloc>::value_type) {
    iterator tmp = *this;
    --(*this);

    return tmp;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::pointer XorLinkedList<T, Alloc>::const_iterator::next() const{
    return xor_(current_->next_xor_prev, previous_);
}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::const_iterator::~const_iterator()
{}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::iterator::~iterator()
{}

/*
 * END OF ITERATOR BLOCK
 */

/*
 * ELEMENT BLOCK
*/
template <class T, class Alloc>
XorLinkedList<T, Alloc>::Element::Element() {

}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::Element::Element(const XorLinkedList<T, Alloc>::value_type & value):
    value(value)
{}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::Element::Element(XorLinkedList<T, Alloc>::value_type&& value):
    value(std::move(value))
{}

template <class T, class Alloc>
bool XorLinkedList<T,Alloc>::Element::operator==(const XorLinkedList<T,Alloc>::Element &other) const {
    return (this == &other);
}

template <class T, class Alloc>
bool XorLinkedList<T,Alloc>::Element::operator!=(const XorLinkedList<T,Alloc>::Element &other) const {
    return !(this == &other);
}


/*
 * END OF ELEMENT BLOCK
 */

/*Constructors*/
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::initialize_() {
    size_ = 0;
    nil_ = allocator_.allocate(1);
    nil_->next_xor_prev = 0;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::pointer XorLinkedList<T, Alloc>::get_element_(XorLinkedList<T, Alloc>::value_type &&value) {
    pointer element = allocator_.allocate(1);
    element->value = std::forward<value_type>(value);

    return element;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::pointer XorLinkedList<T, Alloc>::get_element_(XorLinkedList<T, Alloc>::const_reference value) {
    pointer element = allocator_.allocate(1);
    element->value = value;

    return element;
}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::XorLinkedList(XorLinkedList<T, Alloc>::allocator_type const & alloc):
    allocator_(alloc)
{
    initialize_();

}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::XorLinkedList(size_t n):
    size_(n),
    allocator_(allocator_type())
{
    initialize_();
    value_type default_value;
    while (n--) {
        insert(begin(), default_value);
    }
}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::XorLinkedList(XorLinkedList<T, Alloc>::size_type n, XorLinkedList<T, Alloc>::const_reference value,
       const XorLinkedList<T, Alloc>::allocator_type& alloc):
    allocator_(alloc)
{
    initialize_();
    while (n--) {
        insert(begin(), value);
    }
}


template <class T, class Alloc>
template <class TI, EnableIf<IsIterator<TI>>...>
XorLinkedList<T, Alloc>::XorLinkedList(TI first, TI last, const allocator_type& alloc):
    allocator_(alloc)
{
    initialize_();
    while (first != last) {
        push_back(*first);
        ++first;
    }
}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::XorLinkedList(const XorLinkedList& other):
    allocator_(allocator_type())
{
    initialize_();
    insert(begin(), other.begin(), other.end());
}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::XorLinkedList(const XorLinkedList& other, const XorLinkedList<T, Alloc>::allocator_type& alloc):
    allocator_(allocator_type())
{
    initialize_();
    insert(begin(), other.begin(), other.end());
}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::XorLinkedList(XorLinkedList<T, Alloc>&& other):
    nil_(other.nil_),
    head_(other.head_),
    allocator_(other.allocator_),
    size_(other.size_) {}


template <class T, class Alloc>
XorLinkedList<T, Alloc>::XorLinkedList(XorLinkedList<T, Alloc>&& other,
                                       const XorLinkedList<T, Alloc>::allocator_type& alloc):
    nil_(other.nil_),
    head_(other.head_),
    allocator_(alloc),
    size_(other.size_)
{}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::XorLinkedList(std::initializer_list<XorLinkedList<T, Alloc>::value_type> il,
       const XorLinkedList<T, Alloc>::allocator_type& alloc):
    allocator_(alloc)
{
    initialize_();
    insert(begin(), il);
}

/* operator= */
template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::XorLinkedList& XorLinkedList<T, Alloc>::operator=(const XorLinkedList<T>& other) {
    if (this != &other){
        clear();
        for (iterator it = other.begin(); it != other.end(); ++it) {
            push_back(*it);
        }
    }

    return *this;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::XorLinkedList& XorLinkedList<T, Alloc>::operator=(XorLinkedList<T>&& other) {
    clear();
    allocator_.deallocate(nil_);
    nil_ = other.nil_;
    head_ = other.head_;
    size_ = other.size_;
}

template <class T, class Alloc>
XorLinkedList<T, Alloc>& XorLinkedList<T, Alloc>::operator=(
        std::initializer_list<XorLinkedList<T, Alloc>::value_type> il) {
    clear();
    insert(begin(), il);
}

/*insert*/
template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::insert(XorLinkedList<T, Alloc>::const_iterator position,
                                                                  XorLinkedList<T, Alloc>::pointer element) {
    pointer previous = position.previous_;
    pointer next = position.current_;

    if (previous == nil_) {
        head_ = element;
    }

    if (size_) {
        element->next_xor_prev = xor_(previous, next);
        previous->next_xor_prev = xor_(previous->next_xor_prev, position.current_, element);
        next->next_xor_prev = xor_(next->next_xor_prev, position.previous_, element);
    } else {
        // first element
        element->next_xor_prev = 0;
    }
    ++size_;

    return iterator(previous, element);
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::insert(XorLinkedList<T, Alloc>::const_iterator position,
                                                                  const XorLinkedList<T, Alloc>::value_type& value) {
    return insert(position, get_element_(value));
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::insert(XorLinkedList<T, Alloc>::const_iterator position,
                                    size_type n, XorLinkedList<T, Alloc>::const_reference value) {
    while (n--) {
        auto next = insert(position, value);
        position = next;
    }

    return iterator(position);
}

template <class T, class Alloc>
template <class TI, EnableIf<IsIterator<TI>> ...>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::insert(XorLinkedList<T, Alloc>::const_iterator position,
                                                                 TI first, TI last) {
    iterator it(position);
    while (first != last) {
        it = ++insert(it, *first);

        ++first;
    }
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::insert(XorLinkedList<T, Alloc>::const_iterator position,
                                                                  XorLinkedList<T, Alloc>::value_type&& value) {
    return insert(position, get_element_(std::move(value)));
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::insert (XorLinkedList<T, Alloc>::const_iterator position,
                                    std::initializer_list<typename XorLinkedList<T, Alloc>::value_type> il) {

    auto il_iter = il.begin();
    iterator iter = position;
    while (il_iter != il.end()) {
        iter = ++insert(iter, *il_iter);
        ++il_iter;
    }

    return iter;
}

/* front */
template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::reference XorLinkedList<T, Alloc>::front() {
    return head_->value;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_reference XorLinkedList<T, Alloc>::front() const {
    return head_->value;
}

/* back */
template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::reference XorLinkedList<T, Alloc>::back() {
    assert(size_ > 0);
    iterator penultimate = end();
    --penultimate;
    return *penultimate;
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_reference XorLinkedList<T, Alloc>::back() const {
    assert(size_ > 0);
    return *(--end());
}

/* begin */
template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::begin() noexcept{
    if (size_)
        return iterator(nil_, head_);
    return iterator(nil_, nil_);
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_iterator XorLinkedList<T, Alloc>::begin() const noexcept{
    if (size_)
        return const_iterator(nil_, head_);
    return const_iterator(nil_, nil_);
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::end() noexcept{
    if (size_) {
        return --iterator(nil_, head_);
    }
    return iterator(nil_, nil_);
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::const_iterator XorLinkedList<T, Alloc>::end() const noexcept{
    if (size_) {
        return --const_iterator(nil_, head_);
    }
    return const_iterator(nil_, nil_);
}

template <class T, class Alloc>
size_t XorLinkedList<T, Alloc>::size() const noexcept {
    return size_;
}

template <class T, class Alloc>
bool XorLinkedList<T, Alloc>::empty() const noexcept {
    return (size_ == 0);
}

/* assign */
template <class T, class Alloc>
template <class TI, EnableIf<IsIterator<TI>>...>
void XorLinkedList<T, Alloc>::assign (TI first, TI last) {
    clear();
    insert(begin(), first, last);
}

template <class T, class Alloc>
void XorLinkedList<T, Alloc>::assign (XorLinkedList<T, Alloc>::size_type n,
                                      XorLinkedList<T, Alloc>::const_reference value) {
    clear();
    insert(begin(), n, value);
}

/* push_front */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::push_front(XorLinkedList<T, Alloc>::const_reference value) {
    insert(begin(), value);
}

template <class T, class Alloc>
void XorLinkedList<T, Alloc>::push_front(XorLinkedList<T, Alloc>::value_type&& value) {
    insert(begin(), std::move(value));
}

/* push_back */

template<class T, class Alloc>
void XorLinkedList<T, Alloc>::push_back(const value_type& value)
{
    insert(end(), value);
}

template <class T, class Alloc>
void XorLinkedList<T, Alloc>::push_back(XorLinkedList<T, Alloc>::value_type&& value) {
    std::move(value);
    insert(end(), std::move(value));
}

/* pop_back */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::pop_back() {
    if (size_) {
        erase(--end());
    }
}

/* pop_front */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::pop_front() {
    if (size_) {
        erase(begin());
    }
}

/* swap */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::swap(XorLinkedList<T, Alloc>& other) {
    pointer tmp_head = head_;
    pointer tmp_nil = nil_;
    size_type tmp_size = size_;
    allocator_type tmp_alloc = allocator_;

    head_ = other.head_;
    nil_ = other.nil_;
    size_ = other.size_;
    allocator_ = other.allocator_;
    other.head_ = tmp_head;
    other.nil_ = tmp_nil;
    other.size_ = tmp_size;
    other.allocator_ = tmp_alloc;
}

/* resize */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::resize(XorLinkedList<T, Alloc>::size_type n){
    resize(n, value_type());
}

template <class T, class Alloc>
void XorLinkedList<T, Alloc>::resize(XorLinkedList<T, Alloc>::size_type n, const XorLinkedList<T, Alloc>::value_type& value) {
    int difference = size_ - n;
    if (difference >= 0) {
        while (difference--) {
            pop_back();
        }
        return;
    }
    while (difference++ < 0) {
        push_back(value);
    }
}

/* splice */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::splice(XorLinkedList<T, Alloc>::const_iterator position, XorLinkedList& other) {
    iterator place = position;
    for(auto it = other.begin(); it != other.end(); ++it) {
        auto next = ++insert(place, std::move(*it));
        place = next;
    }
    other.nil_->next_xor_prev = 0;
    other.size_ = 0;
}

template <class T, class Alloc>
void XorLinkedList<T, Alloc>::splice(XorLinkedList<T, Alloc>::const_iterator position, XorLinkedList&& other) {
    iterator place = position;
    for(auto it = other.begin(); it != other.end(); ++it) {
        auto next = ++insert(place, std::move(*it));
        place = next;
    }
    other.nil_->next_xor_prev = 0;
    other.size_ = 0;
}

template <class T, class Alloc>
void XorLinkedList<T, Alloc>::splice(XorLinkedList<T, Alloc>::const_iterator position, XorLinkedList& other,
                                     XorLinkedList<T, Alloc>::const_iterator it) {

    iterator to = position;
    iterator from = it;
    insert(to, std::move(*from));
    Element* previous = from.previous_;
    Element* current = from.current_;
    Element* next = from.next();
    if (current == other.head_) {
        other.head_ = next;
    }
    previous->next_xor_prev = xor_(previous->next_xor_prev, current, next);
    next->next_xor_prev = xor_(next->next_xor_prev, current, previous);
    --other.size_;
}


template <class T, class Alloc>
void XorLinkedList<T, Alloc>::splice(XorLinkedList<T, Alloc>::const_iterator position, XorLinkedList&& other,
                                     XorLinkedList<T, Alloc>::const_iterator it) {
    insert(position, std::move(*it));
    Element* previous = it.previous_;
    Element* current = it.current_;
    Element* next = it.next();
    if (current == other.head_) {
        other.head_ = next;
    }
    previous->next_xor_prev = xor_(previous->next_xor_prev, current, next);
    next->next_xor_prev = xor_(next->next_xor_prev, current, previous);
    --other.size_;
}

template <class T, class Alloc>
void XorLinkedList<T, Alloc>::splice(XorLinkedList<T, Alloc>::const_iterator to, XorLinkedList& other,
             XorLinkedList<T, Alloc>::const_iterator from, XorLinkedList<T, Alloc>::const_iterator last) {
    while (from != last) {
        auto next_to = insert(to, std::move(*from));
        Element* previous = from.previous_;
        Element* current = from.current_;
        Element* next = from.next();
        if (current == other.head_) {
            other.head_ = next;
        }
        previous->next_xor_prev = xor_(previous->next_xor_prev, current, next);
        next->next_xor_prev = xor_(next->next_xor_prev, current, previous);
        --other.size_;
        to = next_to;
        iterator it(previous, next);
        from = it;
    }
}

template <class T, class Alloc>
void XorLinkedList<T, Alloc>::splice(XorLinkedList<T, Alloc>::const_iterator position, XorLinkedList&& other,
             XorLinkedList<T, Alloc>::const_iterator first, XorLinkedList<T, Alloc>::const_iterator last) {
    iterator to = position;
    iterator from = first;
    while (from != last) {
        auto next_to = insert(to, std::move(*from));
        Element* previous = from.previous_;
        Element* current = from.current_;
        Element* next = from.next();
        if (current == other.head_) {
            other.head_ = next;
        }
        previous->next_xor_prev = xor_(previous->next_xor_prev, current, next);
        next->next_xor_prev = xor_(next->next_xor_prev, current, previous);
        --other.size_;
        to = next_to;
        iterator it(previous, next);
        from = it;
    }
}

/* reverce */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::reverse() noexcept {
    if (size_ > 1) {
        head_ = (--end()).current_;
    }
}

/* sort */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::sort() {
    sort([](const_reference a, const_reference b) {return a < b;});
}

template <class T, class Alloc>
template <class Compare>
void XorLinkedList<T, Alloc>::sort(Compare compare) {
    size_type half = size_ / 2;
    if (half > 0) {
        iterator it = begin();
        while (half--) {
            ++it;
        }
        XorLinkedList list1(begin(), it);
        XorLinkedList list2(it, end());
        list1.sort();
        list2.sort();
        list1.merge(list2, compare);
        *this = list1;
    }
}

/* merge */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::merge(XorLinkedList<T>& other) {
    merge(other, [](const_reference a, const_reference b) {return a < b;});
}

template <class T, class Alloc>
void XorLinkedList<T, Alloc>::merge(XorLinkedList<T>&& other) {
    merge(other, [](const_reference a, const_reference b) {return a < b;});
}

template <class T, class Alloc>
template <class Compare>
void XorLinkedList<T, Alloc>::merge(XorLinkedList<T>& other, Compare compare) {
    iterator my_it = begin();
    iterator other_it = other.begin();
    Element* other_previous;
    Element* other_next;
    while(other_it != other.end()) {
        other_previous = other_it.previous_;
        other_next = other_it.next();
        if (compare(*my_it, *other_it) and (my_it != end())) {
            ++my_it;
        } else {
            auto my_next = insert(my_it, other_it.current_);
            if (other_it.current_ == other.head_) {
                other.head_ = other_next;
            }
            other_previous->next_xor_prev = xor_(other_previous->next_xor_prev, other_it.current_, other_next);
            other_next->next_xor_prev = xor_(other_next->next_xor_prev, other_it.current_, other_previous);
            --other.size_;

            my_it = my_next;
            other_it.previous_ = other_previous;
            other_it.current_ = other_next;
        }
    }
}

template <class T, class Alloc>
template <class Compare>
void XorLinkedList<T, Alloc>::merge(XorLinkedList<T>&& other, Compare compare) {
    iterator my_it = begin();
    iterator other_it = other.begin();
    Element* other_previous;
    Element* other_next;
    while(other_it != other.end()) {
        other_previous = other_it.previous_;
        other_next = other_it.next();
        if (compare(*my_it, *other_it) and (my_it != end())) {
            ++my_it;
        } else {
            auto my_next = insert(my_it, other_it.current_);
            if (other_it.current_ == other.head_) {
                other.head_ = other_next;
            }
            other_previous->next_xor_prev = xor_(other_previous->next_xor_prev, other_it.current_, other_next);
            other_next->next_xor_prev = xor_(other_next->next_xor_prev, other_it.current_, other_previous);
            --other.size_;

            my_it = my_next;
            other_it.previous_ = other_previous;
            other_it.current_ = other_next;
        }
    }
}

/* unique */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::unique() {
    unique([](const_reference a, const_reference b) {return a == b;});
}

template <class T, class Alloc>
template <class BinaryPredicate>
void XorLinkedList<T, Alloc>::unique (BinaryPredicate binary_pred) {
    if (size_ < 2) {
        return;
    }
    auto current = begin();
    auto next = current;
    ++next;
    while (next != end()) {
        if (!binary_pred(*current, *next)) {
            ++current;
            ++next;
        } else {
           auto new_current = erase(current);
           next = current = new_current;
           ++next;
        }
    }


}

/* erase */
template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::erase(XorLinkedList<T, Alloc>::const_iterator position) {
    assert(position != end());
    Element* previous = position.previous_;
    Element* current = position.current_;
    Element* next = position.next();
    if (current == head_) {
        head_ = next;
    }
    previous->next_xor_prev = xor_(previous->next_xor_prev, current, next);
    next->next_xor_prev = xor_(next->next_xor_prev, current, previous);
    allocator_.deallocate(current, 1);
    --size_;

    return iterator(previous, next);
}

template <class T, class Alloc>
typename XorLinkedList<T, Alloc>::iterator XorLinkedList<T, Alloc>::erase(XorLinkedList<T, Alloc>::const_iterator first,
                                                                          XorLinkedList<T, Alloc>::const_iterator last) {
    iterator it(first);
    while (it != last) {
        auto next = erase(it);
        it = next;
    }

    return last;
}

/* clear */
template <class T, class Alloc>
void XorLinkedList<T, Alloc>::clear() noexcept {
    erase(begin(), end());
}

template <class T, class Alloc>
XorLinkedList<T, Alloc>::~XorLinkedList() noexcept {
    clear();
    allocator_.deallocate(nil_, 1);
}

#endif // XOR_LINKED_LIST_H
