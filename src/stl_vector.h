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
	// vector(initializer_list<value_type> il) {
	// 	//todo
	// }

	//destructor
	~vector() {
		destory(start, finish);
		deallocate();
	}

	//operator=
	vector<value_type, Alloc>& operator=(const vector<value_type, Alloc> rhs) {		//pass by value, not reference
		swap(*this, rhs);
		return *this;
	}
	vector<value_type, Alloc>& operator=(vector<value_type, Alloc>&& rhs) {
		if (this != &rhs) {
			destory(start, finish);
			deallocate();
			this.start = rhs.start;
			this.finish = rhs.finish;
			this.end_of_storage = rhs.end_of_storage;

			rhs.start = rhs.finish = rhs.end_of_storage = nullptr;
		}
	}

	//modifiers
	// void push_back(const value_type& val);
	// void push_back(value_type&& val);
	// void pop_back();
	// iterator insert(const_iterator position, const value_type& val);
	// iterator insert(const_iterator position, size_type n, const value_type& val);
	// iterator insert(const_iterator position, value_type&& val);
	// iterator erase(const_iterator position);
	// iterator erase(const_iterator first, const_iterator last);
	void swap(vector<value_type, Alloc>& x) {
		using std::swap;
		swap(this.start, x.start);
		swap(this.finish, x.finish);
		swap(this.end_of_storage, x.end_of_storage);
	}
	// void clear() noexcept;

	// //element access
	// reference operator[] (size_type n);
	// const_reference operator[] (size_type n) const;

	// //capacity
	size_type size() const noexcept {
		return static_cast<size_type>(end() - begin());
	}
	// size_type capacity() const noexcept;

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


}
