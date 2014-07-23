// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=



// -----
// using
// -----
const int INNER_SIZE  = 10;
using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;
using namespace std;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);
    }
    return b;
}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;
        }
    }
    catch (...) {
        destroy(a, p, x);
        throw;
    }
    return x;
}



// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;
        }
    }
    catch (...) {
        destroy(a, p, b);
        throw;
    }
    return e;
}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
    public:        

        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

    public:        

        /**
         * <your documentation>
         */
        friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::equal()
            return true;}
        

        /**
         * <your documentation>
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return true;
        }

    private:        

        allocator_type _a;
        T** arr_ptr;
        size_type _l;        
        size_type _b;
        size_type _e;
        size_type number_of_arrays;
        bool new_empty_deque;

    private:        

        bool valid () const {
            // <your code>
            return true;
        }

    public:        

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename my_deque::value_type      value_type;
                typedef typename my_deque::difference_type difference_type;
                typedef typename my_deque::pointer         pointer;
                typedef typename my_deque::reference       reference;

            public:

                /**
                 * <your documentation>
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    if(lhs._deque == rhs._deque){
                        return lhs.current_location == rhs.current_location;
                    }
                    return false;
                }

                /**
                 * <your documentation>
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);
                }                

                /**
                 * <your documentation>
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;
                }

                /**
                 * <your documentation>
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;
                }

                friend size_type my_deque::get_current_location(iterator& iter);

            private:                

                my_deque* _deque;
                size_type current_location;
                bool valid_iterator;

            private:                

                bool valid () const {
                    // <your code>
                    return valid_iterator;
                }

            public:                

                /**
                 * <your documentation>
                 */
                iterator (my_deque* p, size_type curr) {
                    _deque = p;
                    current_location = curr;                    
                    if(current_location >= p->_b && current_location < p->_e){
                        valid_iterator = true;
                    }                    
                    else{
                        valid_iterator = false;
                    }
                    assert(valid());
                }

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                /**
                 * <your documentation>
                 */
                reference operator * () const {                                        

                    return (*_deque)[current_location - _deque->_b];
                }                

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;
                }                

                /**
                 * <your documentation>
                 */
                iterator& operator ++ () {                    
                    assert(valid());
                    ++current_location;
                    // if(current_location >= _deque->_e){
                    //     valid_iterator = false;
                    //     current_location = _deque->_e;
                    // }
                    return *this;
                }

                /**
                 * <your documentation>
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;
                }                

                /**
                 * <your documentation>
                 */
                iterator& operator -- () {
                    // <your code>
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;
                }

                /**
                 * <your documentation>
                 */
                iterator& operator += (difference_type d) {
                    // <your code>
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
                 */
                iterator& operator -= (difference_type d) {
                    // <your code>
                    assert(valid());
                    return *this;
                }

                
            };

    public:        

        class const_iterator {
            public:                

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename my_deque::value_type      value_type;
                typedef typename my_deque::difference_type difference_type;
                typedef typename my_deque::const_pointer   pointer;
                typedef typename my_deque::const_reference reference;

            public:                
                /**
                 * <your documentation>
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    // <your code>
                    return true;}

                /**
                 * <your documentation>
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}
                

                /**
                 * <your documentation>
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}
                

                /**
                 * <your documentation>
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>

            private:                

                bool valid () const {
                    // <your code>
                    return true;}

            public:                

                /**
                 * <your documentation>
                 */
                const_iterator (/* <your arguments> */) {
                    // <your code>
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);
                

                /**
                 * <your documentation>
                 */
                reference operator * () const {
                    // <your code>
                    // dummy is just to be able to compile the skeleton, remove it
                    static value_type dummy;
                    return dummy;
                }
            

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;
                }
                

                /**
                 * <your documentation>
                 */
                const_iterator& operator ++ () {
                    // <your code>
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;
                }


                /**
                 * <your documentation>
                 */
                const_iterator& operator -- () {
                    // <your code>
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;
                }
                

                /**
                 * <your documentation>
                 */
                const_iterator& operator += (difference_type) {
                    // <your code>
                    assert(valid());
                    return *this;
                }
                

                /**
                 * <your documentation>
                 */
                const_iterator& operator -= (difference_type) {
                    // <your code>
                    assert(valid());
                    return *this;
                }
            };

    public:        



        /**
         * <your documentation>
         */
        explicit my_deque (const allocator_type& a = allocator_type()) : _a (a)
        {            
            arr_ptr = 0;
            _b = _e = number_of_arrays = _l = 0;
            new_empty_deque = true;
            assert(valid());
        }

        /**
         * <your documentation>
         */
        explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) 
        {
            // <your code>
            assert(valid());
        }

        /**
         * <your documentation>
         */
        my_deque (const my_deque& that) 
        {
            // <your code>
            assert(valid());
        }

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
         */
        ~my_deque () {
            for(int i = 0; i < number_of_arrays; ++i){
                T* temp = arr_ptr[i];
                destroy(_a,temp,temp+10);
                _a.deallocate(temp,10);
                
            }
            delete[] arr_ptr;
            assert(valid());
        }        

        /**
         * <your documentation>
         */
        my_deque& operator = (const my_deque& rhs) {
            // <your code>
            assert(valid());
            return *this;
        }
        

        /**
         * <your documentation>
         */
        reference operator [] (size_type index) {
            assert(index >= 0);
            assert(index < size());
            size_type adjusted_index = _b + index;
            size_type inner_array_number = adjusted_index / INNER_SIZE;
            size_type inner_array_index = adjusted_index % INNER_SIZE;
            T* inner_array = arr_ptr[inner_array_number] + inner_array_index;

            return *inner_array;
        }

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);
        }
        

        /**
         * <your documentation>
         */
        reference at (size_type index) {
            
            return *this[index];
        }

        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);
        }
        
        
        /**
         * <your documentation>
         */
        reference back () {
            
            return (*this)[size()-1];
        }

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();
        }
        

        /**
         * <your documentation>
         */
        iterator begin () {
            
            return iterator(this, _b);
        }

        /**
         * <your documentation>
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(/* <your arguments> */);
        }
        

        /**
         * <your documentation>
         */
        void clear () {
            if(size() > 0){
                leaping_destroy(_a,_b,_e,arr_ptr);
                _b = _e = 0;
            }
            assert(valid());
        }
        

        /**
         * <your documentation>
         */
        bool empty () const {
            return !size();
        }
        

        /**
         * <your documentation>
         */
        iterator end () {
            
            return iterator(this, _e);
        }

        /**
         * <your documentation>
         */
        const_iterator end () const {
            // <your code>
            return const_iterator(/* <your arguments> */);
        }
        

        /**
         * <your documentation>
         */
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();
        }
        

        /**
         * <your documentation>
         */
        reference front () {
            return (*this)[0];
        }

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();
        }
        
        size_type get_current_location(iterator& iter)
        {
            return iter.current_location;
        }
        /**
         * <your documentation>
         */
        iterator insert (iterator iter, const_reference v) {
            //AT THE MOMENT, ASSUMING NOT FULL
            size_type iterator_pos = get_current_location(iter) - _b;
            cout << "iterator_pos :" << iterator_pos << endl;
            ++_e;
            cout << "_e : " << _e - _b << endl;
            if(iterator_pos != _l)
            {
                size_type iterator_end = _e - _b;
                for (int i = iterator_end; i >= iterator_pos; --i)
                {
                    cout << "IN LOOP" << endl;
                    cout << "i : " << i << endl;
                    //(*this)[i + 1] = (*this)[i];
                }
                cout << "OUT OF LOOP" << endl;
                (*this)[iterator_pos] = v;
                _e = iterator_end + 2;
            }
            else{
                this->push_back(v);
            }            
            assert(valid());
            return iter;
        }
        

        /**
         * <your documentation>
         */
        void pop_back () {
            if(size() > 0){
                size_type new_e = _e -1;
                leaping_destroy(_a,new_e,_e,arr_ptr);
                _e = new_e;
            }
            assert(valid());
        }

        /**
         * <your documentation>
         */
        void pop_front () {
            
            if(size() > 0){
                
                size_type new_b = _b + 1;
                leaping_destroy(_a,_b,new_b,arr_ptr);
                _b = new_b;
            }
            assert(valid());
        }
        

        /**
         * <your documentation>
         */
        void push_back (const_reference v)
        {            
            size_type new_e = _e + 1;
            
            if(new_e > _l)
            {
                resize(size() + 1, v);
            }
            else
            {
                size_type inner_array_number = _e / INNER_SIZE;
                size_type inner_array_index = _e % INNER_SIZE;

                T* inner_array = arr_ptr[inner_array_number];
                T* inner_position = inner_array + inner_array_index;
                T* inner_end = inner_position + 1;
                uninitialized_fill(_a, inner_position, inner_end, v);
                _e = new_e;
            }

            assert(valid());
        }

        /**
         * <your documentation>
         */
        void push_front (const_reference v) {            
            int new_b = _b - 1;

            if(new_b < 0)
            {
                push_front_resize(1, v);
            }

            else
            {
                size_type inner_array_number = _b / INNER_SIZE;
                size_type inner_array_index = _b % INNER_SIZE;

                T* inner_array = arr_ptr[inner_array_number];
                T* inner_end = inner_array + inner_array_index;
                T* inner_position = inner_end - 1;
                uninitialized_fill(_a, inner_position, inner_end, v);
                _b = new_b;
            }
            
            assert(valid());
        }
        
        void push_front_resize(size_type s, const_reference v = value_type()){            
            size_type num_new_arrs = s / INNER_SIZE + 1;
            size_type one_sided_num_arrs = std::max(num_new_arrs, 2 * size());
            num_new_arrs = 2*one_sided_num_arrs + number_of_arrays;

            T** new_arr_ptr = new T*[num_new_arrs];
            for(int i = 0; i < one_sided_num_arrs; ++i)
            {
                T* temp = _a.allocate(INNER_SIZE);
                new_arr_ptr[i] = temp;
            }

            for(int i = one_sided_num_arrs; i < one_sided_num_arrs + number_of_arrays; ++i)
            {
                new_arr_ptr[i] = arr_ptr[i - one_sided_num_arrs];
            }

            for(int i = one_sided_num_arrs + number_of_arrays; i < num_new_arrs; ++i)
            {
                T* temp = _a.allocate(INNER_SIZE);
                new_arr_ptr[i] = temp;
            }
            size_type new_b = one_sided_num_arrs * INNER_SIZE - s;
            size_type old_b = _b + one_sided_num_arrs * INNER_SIZE;
            
            leaping_fill(_a, new_b, old_b, new_arr_ptr, v);
            
            if(arr_ptr != 0){
                delete[] arr_ptr;
            }                
            arr_ptr = new_arr_ptr;
            number_of_arrays = num_new_arrs;
            _l = number_of_arrays * INNER_SIZE;

            if(new_empty_deque){
                _b = new_b;
                _e = new_b + s;
                new_empty_deque = false;
            }
            else{
                _b = new_b;
                _e = _e + one_sided_num_arrs * INNER_SIZE;
            }
        }
        void leaping_destroy(A& a, size_type b, size_type e, T** arr){
            
            size_type b_array = b / INNER_SIZE;
            size_type b_index = b % INNER_SIZE;

            size_type e_array = e / INNER_SIZE;
            size_type e_index = e % INNER_SIZE;            

            T* b_array_first = arr[b_array];
            T* b_begin = b_array_first + b_index;

            if(b_array == e_array){
                T* arr_end = b_array_first + e_index;
                destroy(a,b_begin,arr_end);
            }
            else
            {
                T* b_end = b_array_first + INNER_SIZE;
                destroy(a, b_begin, b_end);
                for(int i = b_array+1; i < e_array; ++i)
                {
                    T* current = arr[i];
                    T* end_curr = current + INNER_SIZE;
                    destroy(a, current, end_curr);
                }
                T* e_begin = arr[e_array];
                T* e_end = e_begin + e_index;
                destroy(a, e_begin, e_end);
            }
        }
        void leaping_fill(A& a, size_type b, size_type e, T** arr, const value_type& v){
            size_type b_array = b / INNER_SIZE;
            size_type b_index = b % INNER_SIZE;

            size_type e_array = e / INNER_SIZE;
            size_type e_index = e % INNER_SIZE;

            T* b_array_first = arr[b_array];
            T* b_begin = b_array_first + b_index;
          
            if(b_array == e_array)
            {
                T* arr_end = b_array_first + e_index;
                uninitialized_fill(a, b_begin, arr_end, v);  
            }
            else
            {
                T* b_end = b_array_first + INNER_SIZE;
                uninitialized_fill(a, b_begin, b_end, v);
                for(int i = b_array+1; i < e_array; ++i)
                {
                    T* current = arr[i];
                    T* end_curr = current + INNER_SIZE;
                    uninitialized_fill(a, current, end_curr, v);
                }
                T* e_begin = arr[e_array];
                T* e_end = e_begin + e_index;
                uninitialized_fill(a, e_begin, e_end, v);
            }    
        }
        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {            
            
            size_type special_e = s + _b;
            if(s == size()){
                return;
            }
            if (s < size()){
                size_type diff = size() - s;
                size_type new_e = _e - diff;
                leaping_destroy(_a,new_e,_e,arr_ptr);
                _e = new_e;
            }            
            else if(special_e <= _l){                
                
                leaping_fill(_a, _e, special_e, arr_ptr, v);                
            }
            else{
                size_type size_needed = s - _l;
                size_type num_new_arrs = size_needed / INNER_SIZE + 1;

                size_type one_sided_num_arrs = std::max(num_new_arrs, 2 * size());
                num_new_arrs = 2*one_sided_num_arrs + number_of_arrays;

                T** new_arr_ptr = new T*[num_new_arrs];


                for(int i = 0; i < one_sided_num_arrs; ++i)
                {                   
                    T* temp = _a.allocate(INNER_SIZE);
                    new_arr_ptr[i] = temp;

                }

                for(int i = one_sided_num_arrs; i < one_sided_num_arrs + number_of_arrays; ++i)
                {                    
                    new_arr_ptr[i] = arr_ptr[i - one_sided_num_arrs];
                }

                for(int i = one_sided_num_arrs + number_of_arrays; i < num_new_arrs; ++i)
                {
                    T* temp = _a.allocate(INNER_SIZE);
                    new_arr_ptr[i] = temp;   
                }

                if(arr_ptr != 0){
                    delete[] arr_ptr;
                }                
                arr_ptr = new_arr_ptr;
                number_of_arrays = num_new_arrs;
                _l = number_of_arrays * INNER_SIZE;
                if(new_empty_deque){
                    _b = 0;
                    _e = size_needed;
                    new_empty_deque = false;
                }
                else{
                    _b = _b + one_sided_num_arrs * INNER_SIZE;
                    _e = _e + one_sided_num_arrs * INNER_SIZE + size_needed;
                }

                leaping_fill(_a, _e - size_needed, _e, arr_ptr, v);
            }
            
            assert(valid());
        }
        

        /**
         * <your documentation>
         */
        size_type size () const {
            
            return _e - _b;
        }
        

        /**
         * <your documentation>
         */
        void swap (my_deque&) {
            // <your code>
            assert(valid());}};

#endif // Deque_h
