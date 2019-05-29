#pragma once

#include <cstdlib>

namespace NanoSTL {

class first_level_alloc;
typedef first_level_alloc alloc;

class first_level_alloc {
public:
	static void* allocate(size_t n) {
		void* result = malloc(n);
		//todo: out of memory handler
		return result;
	}
	static void deallocate(void* p, size_t) {
		free(p);
	}
};

template <typename T, typename Alloc>
class simple_alloc {
public:
	static T* allocate(size_t n) {
		return (0 == n) ? nullptr : static_cast<T *>(Alloc::allocate(n * sizeof(T)));
	}
	static T* allocate() {
		return static_cast<T *>(Alloc::allocate(sizeof(T)));
	}
	static void deallocate(T *p, size_t n) {
		if (0 != n) {
			Alloc::deallocate(p, n * sizeof(T));
		}
	}
	static void deallocate(T *p) {
		Alloc::deallocate(p, sizeof(T));
	}
};

}
