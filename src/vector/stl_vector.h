#pragma once

namespace NanoSTL {

template <typename T, typename Alloc = alloc>
class vector {
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
  	typedef value_type& reference;
  	typedef const value_type& const_reference;
  	typedef size_t size_type;
  	typedef ptrdiff_t difference_type;

	//constructor
	vector():start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
	vector(size_type n, const value_type& value) {
		start = allocate_and_fill(n, value);
    	finish = start + n;
    	end_of_storage = finish; 
	}
	vector(const vector<value_type, Alloc>& rhs) {		//copy
		start = allocate_and_copy(rhs.size(), rhs.begin(), rhs.end());
    	finish = start + (rhs.size());
    	end_of_storage = finish;
	}
	vector(vector<value_type, Alloc>&& rhs)			//move
		:start(rhs.start), finish(rhs.finish), end_of_storage(rhs.end_of_storage) {
		rhs.start = rhs.finish = rhs.end_of_storage = nullptr;
	}
	template <class InputIterator>
	vector(InputIterator first, InputIterator last) :start(nullptr), finish(nullptr), end_of_storage(nullptr) {		// range
		for (; first != last; ++first) {
			push_back(*first);
		}
	}
	// vector(initializer_list<value_type> il) {
	// 	//todo
	// }

	//destructor
	~vector() {
		destroy(start, finish);
		deallocate();
	}

	//operator=
	vector<value_type, Alloc>& operator=(vector<value_type, Alloc> rhs) {		//pass by value, not reference
		this->swap(rhs);
		return *this;
	}

	//modifiers
	void push_back(const value_type& val);
	// void push_back(value_type&& val);
	void pop_back() {
    	--finish;
    	destroy(finish);
	}
	iterator insert(const_iterator position, const value_type& val);
	iterator insert(const_iterator position, size_type n, const value_type& val);
	// iterator insert(const_iterator position, value_type&& val);
	iterator erase(const_iterator position);
	iterator erase(const_iterator first, const_iterator last);
	void swap(vector<value_type, Alloc>& x) {
		NanoSTL::swap(start, x.start);
		NanoSTL::swap(finish, x.finish);
		NanoSTL::swap(end_of_storage, x.end_of_storage);
	}
	void clear() noexcept {
		erase(begin(), end());
	}

	// //element access
	reference operator[] (size_type n) {
		return start[n];
	}
	const_reference operator[] (size_type n) const {
		return start[n];
	}
	reference front() {
		return *begin();
	}
	const_reference front() const {
		return *begin();
	}

	// //capacity
	size_type size() const noexcept {
		return static_cast<size_type>(end() - begin());
	}
	size_type capacity() const noexcept {
		return static_cast<size_type>(end_of_storage, begin());
	}
	bool empty() const noexcept {return start == finish;}
	

	// //iterator
	iterator begin() noexcept {
		return start;
	}
	const_iterator begin() const noexcept {
		return start;
	}
	iterator end() noexcept {
		return finish;
	}
	const_iterator end() const noexcept {
		return finish;
	}
	const_iterator cbegin() const noexcept {
		return start;
	}
	const_iterator cend() const noexcept {
		return finish;
	}

private:
	iterator allocate_and_fill(size_type n, const value_type& x) {
    	iterator result = data_allocator::allocate(n);
      	uninitialized_fill_n(result, n, x);
      	return result;
    }
  
	iterator allocate_and_copy(size_type n, const_iterator first, const_iterator last) {
		iterator result = data_allocator::allocate(n);
		uninitialized_copy(first, last, result);
		return result;
	}

	void deallocate() {
    	if (start)
			data_allocator::deallocate(start, size());
  	}


	typedef simple_alloc<value_type, Alloc> data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;
};

template <typename T, typename Alloc>
void vector<T, Alloc>::push_back(const value_type& val) {
	insert(cend(), val);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator position, const value_type& val) {
	return insert(position, 1, val);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator position, size_type n, const value_type& val) {

	const size_type elems_before = static_cast<size_type>(position - start);
	iterator pos = start + (position - start);

	if (static_cast<size_type>(end_of_storage - finish) >= n) {
		const size_type elems_after = finish - pos;
		if (n <= elems_after) {
			copy(position, position + (elems_after - n), pos + n);
			uninitialized_copy(position + (elems_after - n), cend(), finish);
			fill_n(pos, n, val);
		} else {
			uninitialized_copy(position, cend(), pos + n);
			fill_n(pos, elems_after, val);
			uninitialized_fill_n(finish, n - elems_after, val);
		}

		finish = finish + n;
	} else {
		const size_type old_capacity = size();
		const size_type new_capacity = old_capacity + max(old_capacity, n);
		iterator new_start = data_allocator::allocate(new_capacity);
		iterator new_finish = new_start;
		iterator new_end_of_storage = new_start + new_capacity;

		//todo: move if noexcept
		new_finish = uninitialized_copy(cbegin(), position, new_start);
		new_finish = uninitialized_fill_n(new_finish, n, val);
		new_finish = uninitialized_copy(position, cend(), new_finish);

		destroy(start, finish);
		deallocate();

		start = new_start;
		finish = new_finish;
		end_of_storage = new_end_of_storage;
	}
	return start + elems_before;
}



template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(const_iterator position) {
	return erase(position, position + 1);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(const_iterator first, const_iterator last) {
	iterator erase_start = begin() + (first - cbegin());
	iterator result = copy(last, cend(), erase_start);
	destroy(result, end());
	finish = result;
	return erase_start;
}

}
