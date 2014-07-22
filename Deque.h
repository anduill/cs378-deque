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


#define INNER_SIZE 10;
// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

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
        //size_type d_size;
        size_type _b;
        size_type _e;
        size_type number_of_arrays;
        // <your data>

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
                    // <your code>
                    return true;
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

            private:                

                // <your data>

            private:                

                bool valid () const {
                    // <your code>
                    return true;
                }

            public:                

                /**
                 * <your documentation>
                 */
                iterator (/* <your arguments> */) {
                    // <your code>
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
                iterator& operator ++ () {
                    // <your code>
                    assert(valid());
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
            /*arr_ptr = new T*[3];// we initialize standard array of pointers
            number_of_arrays = 3;
            for(int i = 0; i < 3; ++i){
                T* temp = _a.allocate(10);
                T* temp_end = uninitialized_fill(_a,temp,temp+10,value_type());
                arr_ptr[i] = temp;                
            }*/
            _b = _e = number_of_arrays = _l = 0;
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
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;
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
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;
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
            // <your code>
            return iterator(/* <your arguments> */);
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
            // <your code>
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
            // <your code>
            return iterator(/* <your arguments> */);
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
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;
        }

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();
        }
        

        /**
         * <your documentation>
         */
        iterator insert (iterator, const_reference) {
            // <your code>
            assert(valid());
            return iterator();
        }
        

        /**
         * <your documentation>
         */
        void pop_back () {
            // <your code>
            assert(valid());
        }

        /**
         * <your documentation>
         */
        void pop_front () {
            // <your code>
            assert(valid());
        }
        

        /**
         * <your documentation>
         */
        void push_back (const_reference v)
        {
            size_type new_e = _e + 1;
            if(new_e >= _l)
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
            // <your code>
            assert(valid());
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
            if(s == size()){
                return;
            }
            if (s < size()){

            }
            else if( s <= _l){
                size_type extra_size = s - size();
                size_type new_e = _e + extra_size;
                //leaping_fill                
            }
            else{

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
