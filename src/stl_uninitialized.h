#pragma once

#include <string>

#include "src/type_traits.h"
#include "src/iterator.h"

namespace NanoSTL {

//uninitialized_copy()
template <tepename InputIterator, typename ForwordIterator>
inline ForwordIterator uninitialized_copy(InputIterator first, InputIterator last,
                                    ForwordIterator result) {
    typedef typename type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
    return _uninitialized_copy_aux(first, last, result, is_POD_type());
}

template <tepename InputIterator, typename ForwordIterator>
inline ForwordIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                    ForwordIterator result, __true_type /*unused*/) {
    memmove(result, first, last - first);   //why not memset()
    return  result + (last - first);        //only built-in type will go in here so we can do this
}

template <tepename InputIterator, typename ForwordIterator>
inline ForwordIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                    ForwordIterator result, __false_type /*unused*/) {
    while (first != end) {
        construct(result++, *(first++));
    }
    return result;
}


//uninitialized_fill()
template <template ForwardIterator, template T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, 
                               const T& x) {
    typedef typename type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
    return _uninitialized_fill_aux(first, last, x, is_POD_type());
}

template <template ForwardIterator, template T>
inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, 
                                                const T& x, __true_type /*unused*/) {
    typedef typename iterator_traits<ForwardIterator>::value_type value_type;
    memset(first, x, sizeof(value_type) * (last- first));
}

template <template ForwardIterator, template T>
inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, 
                                                const T& x, __false_type /*unused*/) {
    for (auto cur = first; cur != last; ++cur) {
        construct(cur, x);
    }
}

//uninitialized_fill_n()
template <template ForwardIterator, template Size, template T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
                                            const T& x) {
    //todo
}