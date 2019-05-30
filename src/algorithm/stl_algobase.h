#pragma once

#include <string.h>

namespace NanoSTL {

//todo: rough implementation
template <typename InputIterator, typename OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last,
                           OutputIterator result) {
    for ( ; first != last; ++result, ++first)
        *result = *first;
    return result;
}

inline char* copy(const char* first, const char* last, char* result) {
    memmove(result, first, last - first);
    return result + (last - first);
}

inline wchar_t* copy(const wchar_t* first, const wchar_t* last,
                     wchar_t* result) {
    memmove(result, first, sizeof(wchar_t) * (last - first));
    return result + (last - first);
}

template <typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
    for ( ; first != last; ++first)
      *first = value;
}

template <typename OutputIterator, typename Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
    for ( ; n > 0; --n, ++first)
      *first = value;
    return first;
}

template <typename T>
inline const T& min(const T& a, const T& b) {
  return b < a ? b : a;
}

template <typename T>
inline const T& max(const T& a, const T& b) {
  return  a < b ? b : a;
}

template <class T>
inline void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

}