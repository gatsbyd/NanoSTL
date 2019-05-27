#pragma once

#include <string>

// #include "src/type_traits.h"
// #include "src/stl_iterator.h"
#include "src/stl_construct.h"

namespace NanoSTL {

//uninitialized_copy()
template <typename InputIterator, typename ForwordIterator>
inline ForwordIterator uninitialized_copy(InputIterator first, InputIterator last,
                                    ForwordIterator result) {
    //typedef typename type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
    //todo
    while (first != last) {
        construct(&*result, *first);
        ++result;
        ++first;
    }
    return result;
}

// template <typename InputIterator, typename ForwordIterator>
// inline ForwordIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
//                                     ForwordIterator result, __true_type /*unused*/) {
//     memmove(result, first, last - first);   //why not memset()
//     return  result + (last - first);        //only scalar type will go in here (see type_traits.h) so we can do this
// }

// template <typename InputIterator, typename ForwordIterator>
// inline ForwordIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
//                                     ForwordIterator result, __false_type /*unused*/) {
//     while (first != end) {
//         construct(result++, *(first++));
//     }
//     return result;
// }

// inline char* uninitialized_copy(const char* first, const char* last,
//                                 char* result) {
//   memmove(result, first, last - first);
//   return result + (last - first);
// }

// inline wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last,
//                                    wchar_t* result) {
//   memmove(result, first, sizeof(wchar_t) * (last - first));
//   return result + (last - first);
// }


//uninitialized_fill()
template <typename ForwardIterator, typename T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, 
                               const T& x) {
    //typedef typename type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
    //todo
    for (auto cur = first; cur != last; ++cur) {
        construct(&*cur, x);
    }
}

// template <typename ForwardIterator, typename T>
// inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, 
//                                                 const T& x, __true_type /*unused*/) {
//     typedef typename iterator_traits<ForwardIterator>::value_type value_type;
//     memset(first, x, sizeof(value_type) * (last- first));
// }

// template <typename ForwardIterator, typename T>
// inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, 
//                                                 const T& x, __false_type /*unused*/) {
//     for (auto cur = first; cur != last; ++cur) {
//         construct(cur, x);
//     }
// }

//uninitialized_fill_n()
template <typename ForwardIterator, typename Size, typename T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
                                            const T& x) {
    //typedef typename type_traits<iterator_traits<ForwardIterator>::value_type>::is_POD_type is_POD_type;
    //todo 
  ForwardIterator cur = first;
    for ( ; n > 0; --n, ++cur)
        construct(&*cur, x);
    return cur;
}

// template <typename ForwardIterator, typename Size, typename T>
// inline ForwardIterator uninitialized_fill_n_axu(ForwardIterator first, Size n,
//                                             const T& x, __true_type /*unused*/) {
//     typedef typename iterator_traits<ForwardIterator>::value_type value_type;
//     memset(first, x, szieof(value_type) * n);
//     return first + n;                                        
// }

// template <typename ForwardIterator, typename Size, typename T>
// inline ForwardIterator uninitialized_fill_n_axu(ForwardIterator first, Size n,
//                                             const T& x, __true_type /*unused*/) {
    
// }

}