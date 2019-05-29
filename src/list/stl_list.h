#pragma once

namespace NanoSTL
{

template <typename T>
struct list_node {
    typedef struct list_node<T>* node_pointer;
    node_pointer prev;
    node_pointer next;
    T data;
}

template <typename T, typename Ref, typename Ptr>
class list_iterator {
    //todo
    friend class list;
public:
    typedef list_iterator<T, Ref, Ptr> self;
    // iterator_traits
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef Ptr pointer;
    typedef Ref reference;

    // constructor
    list_iterator(list_node<T>* x) :node(x) {}
    list_iterator(const self& rhs) :node(rhs.node) {}

    bool operator==(const self& rhs) {return node == rhs.node;}
    bool operator!=(const slef& rhs) {return !(this == rhs);}

    reference operator*() const {return node->data};
    pointer operator->() const {return &this->operator*()};

    self& operator++() {
        node = node->next;
        return *this;
    }

    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self& operator--() {
        node = node->prev;
        reutrn *this;
    }

    self operator--(int) {
        self tmp = *this;
        --*this();
        return tmp;
    }

private:
    list_node<T>* node;
}

template <typename T, typename Alloc = alloc>
class list {
public:
    typedef T value_type;
    typedef list_iterator<T, T&, T*> iterator;
    typedef list_iterator<T, const T&, const T*> const_iterator;
    typedef size_t size_type;

    // constructor
    list() :size(0) {
        node = data_allocator::allocate();
        node->next = node;
        node->prev = node;
    }
    list(const list<T, Alloc>& rhs) {       //copy
        list(rhs.begin(), rhs.end());
    }
    list(list<T, Alloc>&& rhs) :node(rhs.node), size(node.size) {       //move
        // make rhs destructable
        rhs.node = nullptr;
    }
    template <typename InputIterator>
    list(InputIterator first, InputIterator last) {     //range
        list();
        insert(end(), first, last);
    }

    // destructor
    ~list() {
        if (node) {
            clear();
            data_allocator::deallocate(node);
        }
    }

    // operator=
    list& operator=(list<T, Alloc> rhs) {
        swap(rhs);
        return *this;
    }

    //modifiers
    // void push_front(const value_type& val);
    // void pop_front();
    // void push_back(const value_type& val);
    // void pop_back();
    iterator insert(const_iterator position, const value_type& val) {
        list_node<T>* new_node = create_node(val);
        new_node->prev = position.node->prev;
        position.node->prev->next = new_node;
        new_node->next = position.node;
        position.node->prev = new_node;
        return new_node;
    }
    template <class InputIterator>
    iterator insert (const_iterator position, InputIterator first, InputIterator last);
    // iterator erase (const_iterator first, const_iterator last);
    // iterator erase (const_iterator position);
    void swap(list<T, Alloc>& rhs) {
        using std::swap;
        swap(node, rhs.node);
        swap(size, rhs.size);
    }
    void clear() noexcept {
        erase(begin(), end());
    }

    // capacity
    size_type size() const noexcept {return size;}

    // element access
    // reference front();
    // const_reference front() const;
    // reference back();
    // const_reference back() const;

    // // iterator
    iterator begin() noexcept {
		return node->next;
	}
	const_iterator begin() const noexcept {
		return node->next;
	}
	iterator end() noexcept {
		return node;
	}
	const_iterator end() const noexcept {
		return node;
	}
	const_iterator cbegin() const noexcept {
		return node->next;
	}
	const_iterator cend() const noexcept {
		return node;
	}

private:
    typedef simple_alloc<list_node<T>, Alloc> data_allocator;

    list_node<T>* create_node(T value) {
        list_node<T>* new_node = data_allocator::allocate();
        construct(new_node, value);
        return new_node;
    }

    void destroy_node(list_node<T>* p) {
        destroy(p->data);
        data_allocator::deallocate(p);
    }

    list_node<T> *node;
    size_type size;
}

template <typename T, typename Alloc> template <typename InputIterator>
void list<T, Alloc>::insert(const_iterator position,
                            InputIterator first, InputIterator last) {
  for ( ; first != last; ++first)
    insert(position, *first);
    ++size;
}
    
} // namespace NanoSTL