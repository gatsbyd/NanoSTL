#pragma once

namespace NanoSTL {

template <typename T, typename Sequence = vector<T>, typename Compare = less<typename Sequence::value_type>>
class priority_queue {
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;

    // constructor
    priority_queue() = default;
    explicit priority_queue(const Compare& x) :  container(), comp(x) {}

    template <class InputIterator>
    priority_queue(InputIterator first, InputIterator last) // range  
        : container(first, last) {
        make_heap(container.begin(), container.end(), comp);
    }

    template <class InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare& x)
        : container(first, last), comp(x) {
        make_heap(container.begin(), container.end(), comp);
    }

    bool empty() const { return container.empty(); }
    size_type size() const { return container.size(); }
    const_reference top() const { return container.front(); }

    // modify
    void push(const value_type& x) {
        container.push_back(x);
        push_heap(container.begin(), container.end(), comp);
    }
    void pop() {
        pop_heap(container.begin(), container.end(), comp);
        container.pop_back();
    }


// private:
    Sequence container;
    Compare comp;
};

}