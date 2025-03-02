#pragma once
#include <memory>
#include <stdexcept>
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;
using std::max;
using std::min;
using std::numeric_limits;
using std::reverse_iterator;
using std::make_reverse_iterator;

template<class T>
class Vec {
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef size_t size_type;
        typedef T value_type;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef ptrdiff_t difference_type;
        typedef allocator<value_type> allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;

        Vec() { create(); }
        explicit Vec(size_type n, const_reference val = value_type{}) { create(n, val); }
        template<typename iter,
            std::enable_if_t<std::is_base_of_v<typename std::iterator_traits<iter>::iterator_category,
            std::random_access_iterator_tag>, bool> = true>
        Vec(iter first, iter last) { create(first, last); }
        Vec(const Vec& vec) { create(vec.begin(), vec.end()); }
        Vec(Vec&& vec) {
            create(vec.begin(), vec.end());
            vec.~Vec();
        }
        ~Vec() { uncreate(); }

        Vec& operator=(const Vec& rhs) {
            if (&rhs != this) {
                uncreate();
                create(rhs.begin(), rhs.end());
            }
            return *this;
        }
        Vec& operator=(Vec&& rhs) {
            if (&rhs != this) {
                uncreate();
                create(rhs.begin(), rhs.end());
                rhs.~Vec();
            }
            return *this;
        }

        size_type size() const { return avail - start; }
        size_type max_size() const { return numeric_limits<size_t>::max(); }
        size_type capacity() const { return limit - start; }
        void resize(size_type n, const_reference val = value_type{}) {
            if (n < size()) {
                shrinkSize(n);
            }
            else if (n > size()) {
                if (n > capacity()) { grow(n); }
                iterator new_avail = start + n;
                uninitialized_fill(avail, new_avail, val);
                avail = new_avail;
            }
        }
        void reserve(size_type n) {
            if (n > capacity()) { grow(n); }
        }
        bool empty() const { return size() == 0; }
        void shrink_to_fit() {
            if (size() < capacity()) {
                iterator new_start = alloc.allocate(size());
                iterator new_avail = uninitialized_copy(start, avail, new_start);
                uncreate();
                start = new_start;
                avail = new_avail;
                limit = start + size();
            }
        }

        reference operator[](size_type i) { return start[i]; }
        const_reference operator[](size_type i) const { return start[i]; }
        reference at(size_type i) {
            if (i < size()) { return start[i]; }
            else { throw std::out_of_range("Index out of range."); }
        }
        const_reference at(size_type i) const {
            if (i < size()) { return start[i]; }
            else { throw std::out_of_range("Index out of range."); }
        }
        reference front() { return *start; }
        const_reference front() const { return *start; }
        reference back() { return *(avail - 1); }
        const_reference back() const { return *(avail - 1); }
        value_type* data() { return start; }
        const value_type* data() const { return start; }

        iterator begin() { return start; }
        const_iterator begin() const { return start; }
        const_iterator cbegin() const { return start; }
        reverse_iterator rbegin() { return make_reverse_iterator(avail); }
        const_reverse_iterator rbegin() const { return make_reverse_iterator(avail); }
        const_reverse_iterator crbegin() const { return make_reverse_iterator(avail); }
        iterator end() { return avail; }
        const_iterator end() const { return avail; }
        const_iterator cend() const { return avail; }
        reverse_iterator rend() { return make_reverse_iterator(start); }
        const_reverse_iterator rend() const { return make_reverse_iterator(start); }
        const_reverse_iterator crend() const { return make_reverse_iterator(start); }

        template<typename iter,
            std::enable_if_t<std::is_base_of_v<typename std::iterator_traits<iter>::iterator_category,
            std::random_access_iterator_tag>, bool> = true>
        void assign(iter first, iter last) {
            size_type new_size = last - first;
            if (new_size > capacity()) { grow(new_size); }
            if (new_size > size()) { avail = start + new_size; }
            else {
                iterator new_avail = start + new_size;
                iterator it = avail;
                while (it != new_avail) { alloc.destroy(--it); }
                avail = new_avail;
            }
            uninitialized_copy(first, last, start);
        }
        void assign(size_type n, const_reference val) {
            if (n > capacity()) { grow(n); }
            if (n > size()) { avail = start + n; }
            else {
                iterator new_avail = start + n;
                iterator it = avail;
                while (it != new_avail) { alloc.destroy(--it); }
                avail = new_avail;
            }
            uninitialized_fill(start, avail, val);
        }
        void push_back(const_reference val) {
            if (avail == limit) { grow(); }
            unchecked_append(val);
        }
        void pop_back() {
            alloc.destroy(avail - 1);
            avail--;
        }
        iterator insert(iterator position, const_reference val) {
            size_type pos = position - start;
            if (avail == limit) { insertGrow(position, 1); }
            alloc.construct(start + pos, val);
            return start + pos;
        }
        iterator insert(iterator position, size_type n, const_reference val) {
            size_type pos = position - start;
            if (avail == limit) { insertGrow(position, n); }
            uninitialized_fill(start + pos, start + pos + n, val);
            return start + pos;
        }
        template<typename iter,
            std::enable_if_t<std::is_base_of_v<typename std::iterator_traits<iter>::iterator_category,
            std::random_access_iterator_tag>, bool> = true>
        iterator insert(iterator position, iter first, iter last) {
            size_type pos = position - start;
            size_type n = last - first;
            if (avail == limit) { insertGrow(position, n); }
            uninitialized_copy(first, last, start + pos);
            return start + pos;
        }
        iterator erase(iterator position) {
            alloc.destroy(position);
            uninitialized_copy(position + 1, avail, position);
            alloc.destroy(--avail);
            return position;
        }
        iterator erase(iterator first, iterator last) {
            size_type n = last - first;
            iterator it = last;
            while (it != first) { alloc.destroy(--it); }
            uninitialized_copy(last, avail, first);
            iterator new_avail = avail - n;
            it = avail;
            while (it != new_avail) { alloc.destroy(--it); }
            avail = new_avail;
            return first;
        }
        void swap(Vec& x) {
            iterator temp_start = start;
            iterator temp_avail = avail;
            iterator temp_limit = limit;
            start = x.start;
            avail = x.avail;
            limit = x.limit;
            x.start = temp_start;
            x.avail = temp_avail;
            x.limit = temp_limit;
        }
        void clear() {
            uncreate();
        }

        allocator_type get_allocator() const { return alloc; }

        bool operator== (const Vec& rhs) {
            Vec& lhs = *this;
            if (size() == rhs.size()) {
                for (int i = 0; i < size(); i++) {
                    if (lhs[i] != rhs[i]) { return false; }
                }
                return true;
            }
            return false;
        }

        bool operator!= (const Vec& rhs) {
            Vec& lhs = *this;
            return !(lhs == rhs);
        }

        bool operator< (const Vec& rhs) {
            const Vec& lhs = *this;
            for (int i = 0; i < min(lhs.size(), rhs.size()); i++) {
                if(lhs[i] < rhs[i]) { return true; }
                else if(lhs[i] > rhs[i]){return false;}
            }
            return lhs.size() < rhs.size();
        }

        bool operator> (Vec& rhs) {
            const Vec& lhs = *this;
            return rhs < lhs;
        }

        bool operator<= (Vec& rhs) {
            const Vec& lhs = *this;
            return !(rhs < lhs);
        }

        bool operator>= (const Vec& rhs) {
            Vec& lhs = *this;
            return !(lhs < rhs);
        }

    private:
        iterator start;
        iterator avail;
        iterator limit;

        allocator_type alloc;

        void create() {
            start = avail = limit = nullptr;
        }
        void create(size_type n, const_reference val) {
            start = alloc.allocate(n);
            limit = avail = start + n;
            uninitialized_fill(start, limit, val);
        }

        template<typename iter,
            std::enable_if_t<std::is_base_of_v<typename std::iterator_traits<iter>::iterator_category,
            std::random_access_iterator_tag>, bool> = true>
        void create(iter b, iter e) {
            start = alloc.allocate(e - b);
            limit = avail = uninitialized_copy(b, e, start);
        }

        void uncreate() {
            if (start) {
                iterator it = avail;
                while (it != start) { alloc.destroy(--it); }
                alloc.deallocate(start, limit - start);
            }
            start = limit = avail = nullptr;
        }

        void insertGrow(iterator position, size_type n) {
            size_type new_capacity = 2 * (limit - start) + n;
            iterator new_start = alloc.allocate(new_capacity);
            uninitialized_copy(start, position, new_start);
            iterator new_avail = uninitialized_copy(position, avail, new_start + (position - start) + n);
            uncreate();
            start = new_start;
            avail = new_avail;
            limit = start + new_capacity;
        }

        void grow() {
            size_type new_capacity = max(2 * (limit - start), difference_type(1));
            iterator new_start = alloc.allocate(new_capacity);
            iterator new_avail = uninitialized_copy(start, avail, new_start);
            uncreate();
            start = new_start;
            avail = new_avail;
            limit = start + new_capacity;
        }

        void grow(size_type n) {
            iterator new_start = alloc.allocate(n);
            iterator new_avail = uninitialized_copy(start, avail, new_start);
            uncreate();
            start = new_start;
            avail = new_avail;
            limit = start + n;
        }

        void shrinkSize(size_type n) {
            iterator new_avail = start + n;
            iterator it = avail;
            while (it != new_avail) { alloc.destroy(--it); }
            avail = new_avail;
        }
        void unchecked_append(const_reference val) {
            alloc.construct(avail++, val);
        }
};

template<class T>
void swap(Vec<T>& x, Vec<T>& y) {
    x.swap(y);
}