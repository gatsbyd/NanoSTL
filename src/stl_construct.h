#pragma once

#include <new>

namespace NanoSTL {

template <typename T>
inline void construct(T* p, const T& value) {
	new(p) T(value);
}


template <typename T>
inline void destroy(T *p) {
	p->~T();
}

//todo: destroy(ForwardIterator first, ForwardIterator last)

}
