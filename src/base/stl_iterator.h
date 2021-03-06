#pragma once

#include <cstddef>

////////////////////////////////////////////////////////////////////////////////

namespace NanoSTL {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

////////////////////////////////////////////////////////////////////////////////

//iterator traits template class
template <typename Iterator>
struct iterator_traits {
	typedef typename Iterator::iterator_category iterator_category;
	typedef typename Iterator::value_type        value_type;
	typedef typename Iterator::difference_type   difference_type;
	typedef typename Iterator::pointer           pointer;
	typedef typename Iterator::reference         reference;
};

//partial specialization for pointer
template <typename T>
struct iterator_traits<T*> {
 	typedef random_access_iterator_tag iterator_category;
  	typedef T                          value_type;
 	typedef ptrdiff_t                  difference_type;
  	typedef T*                         pointer;
  	typedef T&                         reference;
};

//partial specialization for const pointer
template <typename T>
struct iterator_traits<const T*> {
 	typedef random_access_iterator_tag iterator_category;
  	typedef T                          value_type;
 	typedef ptrdiff_t                  difference_type;
  	typedef const T*                         pointer;
  	typedef const T&                         reference;
};

/////////////////////////////////////////////////////////////////////////////////

template <typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	return iterator_category();
}

template <typename Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

template <typename Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

}
