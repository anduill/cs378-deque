// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Integer.c++ TestInteger.c++ -o TestInteger -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestInteger

To obtain coverage of the test:
    % gcov-4.7 -b Integer.c++ TestInteger.c++
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "gtest/gtest.h"

#include "Deque.h"

// ---------
// TestDeque
// ---------

#define NAMES       typedef typename TestFixture::deque_type      deque_type; \
                        typedef typename TestFixture::allocator_type  allocator_type; \
                        typedef typename TestFixture::value_type      value_type; \
                        typedef typename TestFixture::size_type       size_type; \
                        typedef typename TestFixture::difference_type difference_type; \
                        typedef typename TestFixture::pointer         pointer; \
                        typedef typename TestFixture::const_pointer   const_pointer; \
                        typedef typename TestFixture::reference       reference; \
                        typedef typename TestFixture::const_reference const_reference;

template <typename D>
struct TestDeque : testing::Test 
{
    // --------
    // typedefs
    // --------

    typedef          D                  deque_type;
    typedef typename D::allocator_type  allocator_type;
    typedef typename D::value_type      value_type;
    typedef typename D::size_type       size_type;
    typedef typename D::difference_type difference_type;
    typedef typename D::pointer         pointer;
    typedef typename D::const_pointer   const_pointer;
    typedef typename D::reference       reference;
    typedef typename D::const_reference const_reference;
    typedef typename D::iterator        iterator;
};



typedef testing::Types<
            std::deque<int>,
            std::deque<double>,
            my_deque<int>,
            my_deque<double> >
        my_types;

TYPED_TEST_CASE(TestDeque, my_types);

TYPED_TEST(TestDeque, Empty) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;

    deque_type x;
    const bool b = x.empty();
    ASSERT_TRUE(b);}

TYPED_TEST(TestDeque, Size_1) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x;
    const size_type s = x.size();
    ASSERT_EQ(0, s);
}

TYPED_TEST(TestDeque, Size_2) {
   typedef typename TestFixture::deque_type      deque_type;
   typedef typename TestFixture::size_type       size_type;

   deque_type x;
   x.push_back(4);
   x.push_back(5);
   const size_type s = x.size();
   ASSERT_EQ(2, s);
   int four_actual = x[0];
   int five_actual = x[1];
   int five_actual_1 = x.back();
   int four_actual_1 = x.front();
   ASSERT_EQ(4,four_actual);
   ASSERT_EQ(5,five_actual);
   ASSERT_EQ(5,five_actual_1);
   ASSERT_EQ(4, four_actual_1);
}
TYPED_TEST(TestDeque, Iterator_1) {
   typedef typename TestFixture::deque_type      deque_type;

   deque_type x;
   x.push_back(4);
   x.push_back(5);
   x.push_back(6);
   int four = *(x.begin());
   ASSERT_EQ(4,four);
}
TYPED_TEST(TestDeque, Iterator_2) {
   typedef typename TestFixture::deque_type      deque_type;

   deque_type x;
   x.push_back(4);
   x.push_back(5);
   x.push_back(6);
   int five = *(++(x.begin()));
   ASSERT_EQ(5,five);
}
TYPED_TEST(TestDeque, Iterator_3) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;

    deque_type x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);
    iterator my_begin = x.begin();
    my_begin += 2;
    ASSERT_EQ(3,*my_begin);
}

TYPED_TEST(TestDeque, push_front) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_back(4);
    x.push_back(5);
    x.push_front(6);
    x.push_front(7);

    int seven_actual = x[0];
    int six_actual = x[1];
    ASSERT_EQ(7, seven_actual);
    ASSERT_EQ(6, six_actual);
}

TYPED_TEST(TestDeque, push_back_a_bunch) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    for (int i = 0; i < 100; ++i)
    {
        x.push_back(1);
    }
    ASSERT_EQ(100, x.size());
}

TYPED_TEST(TestDeque, pop_front) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_front(4);
    x.pop_front();
    int two_actual = x[0];
    int e = x.back();
    
    ASSERT_EQ(2, two_actual);
}
TYPED_TEST(TestDeque, pop_back) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);
    x.pop_back();    
    
    ASSERT_EQ(3, x.back());
}

TYPED_TEST(TestDeque, smaller_resize) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);
    x.resize(2);    
    
    ASSERT_EQ(2, x.size());
    ASSERT_EQ(1, x.front());
    ASSERT_EQ(2, x.back());
}
TYPED_TEST(TestDeque, clear) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);
    x.clear();
    ASSERT_EQ(0,x.size());
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);   
    
    ASSERT_EQ(4, x.size());
    ASSERT_EQ(1, x.front());
    ASSERT_EQ(4, x.back());
}

TYPED_TEST(TestDeque, iterator_insert) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;

    deque_type x;

    x.push_back(2);
    x.push_front(1);
    x.push_back(3);
    x.push_back(4);

    iterator my_it = x.begin();

    ++my_it;
    ++my_it;
    x.insert(my_it, 5);

    ASSERT_EQ(5, x.size());
}

TYPED_TEST(TestDeque, iterator_erase) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;

    deque_type x;
    
    x.push_back(2);
    x.push_front(1);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    iterator my_it = x.begin();

    ++my_it;
    ++my_it;
    x.erase(my_it);

    ASSERT_EQ(4, x.size());
}

TYPED_TEST(TestDeque, constructor_1) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;

    deque_type x(5,1);
    ASSERT_EQ(5,x.size());
}

TYPED_TEST(TestDeque, constructor_2) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;

    deque_type x(5,10);
    deque_type y(x);
    ASSERT_EQ(5,y.size());
    for(int i = 0; i < 5; ++i){
        ASSERT_EQ(10,y[i]);
    }
    for(int i = 0; i < 5; ++i){
        ASSERT_EQ(10,x[i]);
    }
}
TYPED_TEST(TestDeque, test_swap_1) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);
    
    deque_type y;
    for(int i = 0; i < 10; ++i){
        y.push_back(i);
    }
    deque_type x_copy(x);
    deque_type y_copy(y);
    ASSERT_TRUE(x == x_copy);
    ASSERT_TRUE(y == y_copy);
    x.swap(y);
    ASSERT_TRUE(y == x_copy);
    ASSERT_TRUE(x == y_copy);
    x.swap(y);
    ASSERT_TRUE(x == x_copy);
    ASSERT_TRUE(y == y_copy);
}
TYPED_TEST(TestDeque, test_swap_2) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);
    
    deque_type y;
    for(int i = 0; i < 10; ++i){
        y.push_back(i);
    }
    deque_type x_copy(x);
    deque_type y_copy(y);
    ASSERT_TRUE(x == x_copy);
    ASSERT_TRUE(y == y_copy);
    x.swap(y);
    ASSERT_TRUE(y == x_copy);
    ASSERT_TRUE(x == y_copy);
    x.swap(y);
    ASSERT_TRUE(x == x_copy);
    ASSERT_TRUE(y == y_copy);
}
TYPED_TEST(TestDeque, test_less_than) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);
    
    deque_type y;
    for(int i = 0; i < 10; ++i){
        y.push_back(i);
    }

    ASSERT_TRUE(y < x);
}

TYPED_TEST(TestDeque, iterator_insert_empty) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;

    deque_type x;

    iterator my_it = x.begin();

    x.insert(my_it, 5);

    ASSERT_EQ(1, x.size());
}

TYPED_TEST(TestDeque, for_each_loop) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;

    deque_type x;
    for (int i = 0; i < 5; ++i)
        x.push_back(1);
    deque_type y;

    for (int v : x)
        y.push_back(v);

    ASSERT_TRUE(x == y);
}

TYPED_TEST(TestDeque, insert_full) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;

    deque_type x;
    for (int i = 0; i < 20; ++i)
        x.push_back(1);
    
    iterator my_it = x.begin();
    ++my_it;
    ++my_it;

    my_it = x.insert(my_it, 4);
    my_it = x.insert(my_it, 5);

    ASSERT_EQ(22, x.size());
}

TYPED_TEST(TestDeque, combo_1) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;

    deque_type x;
    for (int i = 0; i < 20; ++i)
        x.push_back(1);

    for (int i = 0; i < 10; ++i)
        x.push_front(2);

    for (int i = 0; i < 20; ++i)
        x.push_front(2);


    
    iterator my_it = x.begin();
    my_it += 10;
    
    x.insert(my_it, 3);
    ++my_it;
    x.erase(my_it);

    ASSERT_EQ(50, x.size());
    ASSERT_EQ(3, x[10]);
}

TYPED_TEST(TestDeque, test_greater_than) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);
    
    deque_type y;
    for(int i = 0; i < 10; ++i){
        y.push_back(i);
    }

    y.push_front(5);

    ASSERT_TRUE(y > x);
}

TYPED_TEST(TestDeque, test_swap_3) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);
    
    deque_type y;
    for(int i = 0; i < 10; ++i){
        y.push_back(i);
    }

    deque_type z;
    for (int i = 0; i < 4; ++i)
    {
        z.push_back(i+5);
    }

    deque_type x_copy(x);
    deque_type y_copy(y);
    deque_type z_copy(z);
    
    x.swap(y);
    x.swap(z);

    ASSERT_TRUE(z == y_copy);
    ASSERT_TRUE(x == z_copy);
}

TYPED_TEST(TestDeque, test_swap_not_equals) {
    typedef typename TestFixture::deque_type      deque_type;

    deque_type x;
    x.push_front(2);
    x.push_back(3);
    x.push_back(4);
    x.push_front(1);
    
    deque_type y;
    for(int i = 0; i < 10; ++i){
        y.push_back(i);
    }

    deque_type z;
    for (int i = 0; i < 4; ++i)
    {
        z.push_back(i+5);
    }

    deque_type x_copy(x);
    deque_type y_copy(y);
    deque_type z_copy(z);
    
    x.swap(y);
    x.swap(z);

    ASSERT_TRUE(z != z_copy);
    ASSERT_TRUE(x != x_copy);
}

TYPED_TEST(TestDeque, at) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::const_reference const_reference;


    deque_type x;
    
    x.push_back(2);
    x.push_front(1);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    const_reference y = x.at(2);

    ASSERT_EQ(3,y);
}

TYPED_TEST(TestDeque, at_change) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::const_reference const_reference;
    typedef typename TestFixture::reference       reference;

    deque_type x;
    
    x.push_back(2);
    x.push_front(1);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    reference y = x.at(2);
    y = 10;

    ASSERT_EQ(10,x.at(2));
}

TYPED_TEST(TestDeque, at_change_1) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::const_reference const_reference;
    typedef typename TestFixture::reference       reference;

    deque_type x;
    
    x.push_back(2);
    x.push_front(1);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    reference y = x.at(2);

    reference z = y;
    x.resize(100);
    y = 10;

    ASSERT_EQ(10,z);
}

TYPED_TEST(TestDeque, const_equals_1) {
    typedef typename TestFixture::deque_type      deque_type;  
    typedef typename TestFixture::const_reference const_reference;
    typedef typename TestFixture::reference       reference;


    deque_type x;
    
    x.push_front(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    const deque_type y(x);
    const_reference _y = y.at(0);
    reference _x = x.at(0);

    ASSERT_EQ(_x,_y);
}

TYPED_TEST(TestDeque, const_equals_2) {
    typedef typename TestFixture::deque_type      deque_type;  
    typedef typename TestFixture::const_reference const_reference;
    typedef typename TestFixture::reference       reference;


    deque_type x;
    
    x.push_front(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    const deque_type y(x);
    const_reference _y = y.back();
    reference _x = x.back();

    ASSERT_EQ(_x,_y);
}

TYPED_TEST(TestDeque, end) {
    typedef typename TestFixture::deque_type      deque_type;      
    typedef typename TestFixture::iterator        iterator;



    deque_type x;
    
    x.push_front(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    iterator my_it = --x.end();

    ASSERT_EQ(5, *my_it);
}

TYPED_TEST(TestDeque, test_lots_of_stuff) {
    typedef typename TestFixture::deque_type      deque_type;  
    typedef typename TestFixture::const_reference const_reference;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::iterator        iterator;



    deque_type x;
    
    x.push_front(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    for (int i = 0; i < 500; ++i)
        x.push_front(6);

    for (int i = 0; i < 500; ++i)
        x.push_back(7);

    
    iterator my_it = x.begin();
    ++my_it;

    x.insert(my_it, 8);
}

TYPED_TEST(TestDeque, beginning) {
    typedef typename TestFixture::deque_type      deque_type;  
    typedef typename TestFixture::const_reference const_reference;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::iterator        iterator;



    deque_type x;
    
    x.push_front(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    for (int i = 0; i < 500; ++i)
        x.push_front(7);

    for (int i = 0; i < 1000; ++i)
        x.push_back(9);

    iterator my_it = x.begin();

    x.insert(my_it, 8);

    ASSERT_EQ(1506, x.size());
}
TYPED_TEST(TestDeque, test_assignment) {
    typedef typename TestFixture::deque_type      deque_type;      



    deque_type x;
    
    x.push_front(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    x[0] = 6;
    x[1] = 7;
    x[2] = 8;
    x[3] = 9;
    x[4] = 10;

    ASSERT_EQ(10, x[4]);
    ASSERT_EQ(9, x[3]);
    ASSERT_EQ(8, x[2]);
    ASSERT_EQ(7, x[1]);
    ASSERT_EQ(6, x[0]);
}

TYPED_TEST(TestDeque, huge_deque) {
    typedef typename TestFixture::deque_type      deque_type;    
    typedef typename TestFixture::size_type       size_type;  


    size_type start = 20;
    deque_type x;

    for (int i = 0; i < 1400; ++i)
        x.push_back(9);
    

    ASSERT_EQ(1400,x.size());
}

TYPED_TEST(TestDeque, huge_deque_front_push) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::iterator        iterator;   


    deque_type x;

    for (int i = 0; i < 1400; ++i)
        x.push_front(9);

    for (int i = 0; i < 1000; ++i)
        x.push_back(9);
    
    iterator my_it = x.begin();
    x.insert(my_it, 8);

    ASSERT_EQ(2401,x.size());
}

TYPED_TEST(TestDeque, pop_front_and_back) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;   

    deque_type x;

    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.push_back(4);
    x.push_back(5);
    x.push_back(6);

    size_type loop = x.size() / 2;

    for (int i = 0; i < loop; ++i)
    {
        x.pop_front();
        x.pop_back();
    }

    ASSERT_EQ(0, x.size());
}

TYPED_TEST(TestDeque, const_inc_pre_1) {
    typedef typename TestFixture::deque_type      deque_type; 
    
    deque_type x;
    x.push_back(7);
    x.push_back(3);
    x.push_front(1);
    x.push_front(2);
    
    const deque_type y(x);
    
    ASSERT_EQ(y.size(), 4);
    ASSERT_EQ(y[1], 1);
    
    ASSERT_EQ(*(++y.begin()), 1);
}

TYPED_TEST(TestDeque, const_inc_pre_2) {
    typedef typename TestFixture::deque_type      deque_type;  

    deque_type x;
    x.push_back(7);
    x.push_back(3);
    x.push_back(2);
    x.push_front(1);
    x.pop_back();
    
    const deque_type y(x);
    
    ASSERT_EQ(y.size(), 3);
    ASSERT_EQ(y[0], 1);
    
    ASSERT_EQ(*(y.begin()), 1);
    ASSERT_EQ(*(++y.begin()), 7);
    ASSERT_EQ(*(++++y.begin()), 3);
}

TYPED_TEST(TestDeque, const_inc_pre_3) {
    typedef typename TestFixture::deque_type      deque_type; 

    deque_type x;
    for(int i = 0; i < 5; ++i)
        x.push_back(1);

    for (int i = 0; i < 5; ++i)
        x.push_front(2);

    for (int i = 0; i < 5; ++i)
        x.push_back(3);
    
    const deque_type y(x);
    
    ASSERT_EQ(y.size(), 15);
    ASSERT_EQ(y[0], 2);
    
    ASSERT_EQ(*(y.begin()), 2);
    ASSERT_EQ(*(++y.begin()), 2);
    ASSERT_EQ(*(++++y.begin()), 2);
}
TYPED_TEST(TestDeque, back_3) 
{
    NAMES
    deque_type x;
    x.push_back(5);
    ASSERT_EQ(x.back(), 5);
}

TYPED_TEST(TestDeque, back_4) 
{
    NAMES
    deque_type x;
    x.push_front(5);
    x.push_front(6);
    x.push_front(5);
    ASSERT_EQ(x.back(), 5);
    x.pop_back();
    ASSERT_EQ(x.back(), 6);
}

TYPED_TEST(TestDeque, back_5) 
{
    NAMES
    deque_type x;
    x.push_back(5);
    x.push_back(6);
    x.pop_back();
    ASSERT_EQ(x.back(), 5);
}

TYPED_TEST(TestDeque, back_6) 
{
    NAMES
    deque_type x;
    x.push_back(5);
    x.push_back(6);
    x.push_back(7);
    x.pop_back();
    ASSERT_EQ(x.back(), 6);
}
TYPED_TEST(TestDeque, push_back_3) 
{
    NAMES
    deque_type x;
    x.push_back(0);
    x.push_back(1);
    ASSERT_EQ(x[0], 0);
    ASSERT_EQ(x[1], 1);
}

TYPED_TEST(TestDeque, push_back_4) 
{
    NAMES
    deque_type x(10,2);
    x.push_back(1);
    ASSERT_EQ(x[10], 1);
}

TYPED_TEST(TestDeque, push_back_5)
{
    NAMES
    deque_type x;
    x.push_back(3);
    x.push_back(4);
    ASSERT_EQ(x[1], 4);
    x.push_back(5);
    ASSERT_EQ(x[2], 5);
}

TYPED_TEST(TestDeque, push_front_1)
{
    NAMES
    deque_type x;
    x.push_front(5);
    ASSERT_EQ(x[0], 5);
}

TYPED_TEST(TestDeque, push_front_2)
{
    NAMES
    deque_type x;
    x.push_front(5);
    x.push_front(6);
    ASSERT_EQ(x[0], 6);
}

TYPED_TEST(TestDeque, push_front_3)
{
    NAMES
    deque_type x;
    x.push_front(5);
    x.push_front(6);
    ASSERT_EQ(x[0], 6);
    x.push_front(7);
    ASSERT_EQ(x[0], 7);
}

TYPED_TEST(TestDeque, push_front_4)
{
    NAMES
    deque_type x;
    x.push_front(5);
    x.push_front(6);
    ASSERT_EQ(x[0], 6);
    x.push_front(7);
    ASSERT_EQ(x[0], 7);
    x.push_back(8);
    ASSERT_EQ(x[0], 7);
}

TYPED_TEST(TestDeque, push_front_5)
{
    NAMES
    deque_type x;
    x.push_front(5);
    x.push_front(6);
    ASSERT_EQ(x[0], 6);
    x.pop_front();
    ASSERT_EQ(x[0], 5);
}

TYPED_TEST(TestDeque, push_front_6)
{
    NAMES
    deque_type x;
    x.push_front(5);
    ASSERT_EQ(x[0], 5);
    assert(x.size() == 1);
}
TYPED_TEST(TestDeque, star_iterator_1)
{
    NAMES
    deque_type x;
    x.push_back(1);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*y, 1);
}

TYPED_TEST(TestDeque, star_iterator_2)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_back(20);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*y, 1);
}

TYPED_TEST(TestDeque, star_iterator_3)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(3);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*y, 3);
}

TYPED_TEST(TestDeque, star_iterator_4)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(30);
    x.push_front(49);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*y, 49);
}
TYPED_TEST(TestDeque, iterator_equals_1)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(3);
    typename deque_type::iterator y = x.begin();
    typename deque_type::iterator z = x.begin();
    assert(y==z);
}

TYPED_TEST(TestDeque, iterator_equals_2)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(3);
    typename deque_type::iterator y = x.end() - 1;
    ASSERT_EQ(*y, 1);
    typename deque_type::iterator z = x.end() - 1;
    ASSERT_EQ(*z, 1);
    assert(y==z);
}

TYPED_TEST(TestDeque, iterator_not_equals_1)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(3);
    x.push_front(4);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*y, 4);
    typename deque_type::iterator z = x.end() - 1;
    ASSERT_EQ(*z, 1);
    assert(y!=z);
}

TYPED_TEST(TestDeque, iterator_not_equals_2)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(4);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*y, 4);
    typename deque_type::iterator z = x.end() - 1;
    ASSERT_EQ(*z, 1);
    assert(y!=z);
}

TYPED_TEST(TestDeque, iterator_not_equals_3)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(4);
    x.push_back(5);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*y, 4);
    typename deque_type::iterator z = x.end() - 1;
    ASSERT_EQ(*z, 5);
    assert(y!=z);
}

TYPED_TEST(TestDeque, iterator_plus_equals_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    y = y + 1;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_plus_equals_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    y = y + 2;
    ASSERT_EQ(*y, 1);
}

TYPED_TEST(TestDeque, iterator_plus_equals_3)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    try
        {y = y + 3;}
    catch(...)
        {assert(true);}
}

TYPED_TEST(TestDeque, iterator_minus_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() -1;
    y = y - 1;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_minus_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    y = y - 2;
    ASSERT_EQ(*y, 5);
}

TYPED_TEST(TestDeque, iterator_postincrement_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    y++;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_postincrement_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    y++;
    y++;
    ASSERT_EQ(*y, 1);
}

TYPED_TEST(TestDeque, iterator_preincrement_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    ++y;
    ++y;
    ASSERT_EQ(*y, 1);
}

TYPED_TEST(TestDeque, iterator_predecrement_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    --y;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_predecrement_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    --y;
    --y;
    ASSERT_EQ(*y, 5);
}

TYPED_TEST(TestDeque, iterator_postdecrement_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    y--;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_postdecrement_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    y--;
    y--;
    ASSERT_EQ(*y, 5);
}
TYPED_TEST(TestDeque, iterator_plus_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*(y+1),4);
}

TYPED_TEST(TestDeque, iterator_plus_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*(y+2),1);
}

TYPED_TEST(TestDeque, iterator_plus_3)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    x.push_front(6);
    typename deque_type::iterator y = x.begin();
    ASSERT_EQ(*(y+3),1);
}

TYPED_TEST(TestDeque, const_iterator_equals_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*(y+1),4);
}

TYPED_TEST(TestDeque, const_iterator_equals_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*(y+2),1);
}

TYPED_TEST(TestDeque, const_iterator_equals_3)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    x.push_front(6);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*(y+3),1);
}

TYPED_TEST(TestDeque, star_const_iterator_1)
{
    NAMES
    deque_type x;
    x.push_back(1);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*y, 1);
}

TYPED_TEST(TestDeque, star_const_iterator_2)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_back(20);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*y, 1);
}

TYPED_TEST(TestDeque, star_const_iterator_3)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(3);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*y, 3);
}

TYPED_TEST(TestDeque, star_const_iterator_4)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(30);
    x.push_front(49);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*y, 49);
}

TYPED_TEST(TestDeque, iterator_const_equals_1)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(3);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    typename deque_type::const_iterator z = a.begin();
    assert(y==z);
}

TYPED_TEST(TestDeque, iterator_const_equals_2)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(3);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.end() - 1;
    ASSERT_EQ(*y, 1);
    typename deque_type::const_iterator z = a.end() - 1;
    ASSERT_EQ(*z, 1);
    assert(y==z);
}

TYPED_TEST(TestDeque, iterator_const_not_equals_1)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(3);
    x.push_front(4);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*y, 4);
    typename deque_type::const_iterator z = a.end() - 1;
    ASSERT_EQ(*z, 1);
    assert(y!=z);
}

TYPED_TEST(TestDeque, iterator_const_not_equals_2)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(4);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*y, 4);
    typename deque_type::const_iterator z = a.end() - 1;
    ASSERT_EQ(*z, 1);
    assert(y!=z);
}

TYPED_TEST(TestDeque, iterator_const_not_equals_3)
{
    NAMES
    deque_type x;
    x.push_back(1);
    x.push_front(4);
    x.push_back(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*y, 4);
    typename deque_type::const_iterator z = a.end() - 1;
    ASSERT_EQ(*z, 5);
    assert(y!=z);
}

TYPED_TEST(TestDeque, iterator_const_plus_equals_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    y = y + 1;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_const_plus_equals_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    y = y + 2;
    ASSERT_EQ(*y, 1);
}

TYPED_TEST(TestDeque, iterator_const_plus_equals_3)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    try
        {y = y + 3;}
    catch(...)
        {assert(true);}
}

TYPED_TEST(TestDeque, iterator_const_minus_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.end() -1;
    y = y - 1;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_const_minus_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    auto y = a.end() - 1;
    y = y - 2;
    ASSERT_EQ(*y, 5);
}

TYPED_TEST(TestDeque, iterator_const_minus_equals_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    auto y = a.end() - 1;
    y -= 2;
    ASSERT_EQ(*y, 5);
}

TYPED_TEST(TestDeque, iterator_const_minus_equals_2)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    auto y = a.end() - 1;
    ASSERT_EQ(*(y -2), 5);
}

TYPED_TEST(TestDeque, iterator_const_postincrement_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    y++;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_const_preincrement_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ++y;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_const_predecrement_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.end() - 1;
    --y;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, iterator_const_postdecrement_1)
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.end() - 1;
    y--;
    ASSERT_EQ(*y, 4);
}
TYPED_TEST(TestDeque, resize_1) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.pop_front();

    x.resize(15);
    ASSERT_EQ(x.size(), 15);
}

TYPED_TEST(TestDeque, resize_2) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.pop_front();

    x.resize(10);
    ASSERT_EQ(x.size(), 10);
}

TYPED_TEST(TestDeque, resize_3) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);

    x.resize(100);
    ASSERT_EQ(x.size(), 100);
}

TYPED_TEST(TestDeque, resize_4) 
{
    NAMES
    deque_type x;

    x.resize(10,5);
    ASSERT_EQ(x.size(), 10);
    ASSERT_EQ(x[0], 5);
}

TYPED_TEST(TestDeque, resize_5) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.push_back(2);
    x.pop_front();

    x.resize(15,5);
    ASSERT_EQ(x.size(), 15);
    ASSERT_EQ(x[0], 2);
}

TYPED_TEST(TestDeque, resize_6) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.pop_front();

    ASSERT_EQ(x.size(), 2);
}

TYPED_TEST(TestDeque, insert_1) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.insert(x.begin(), 5);

    ASSERT_EQ(x[0], 5);
}

TYPED_TEST(TestDeque, insert_2) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.insert(x.end(), 5);

    
    ASSERT_EQ(*(x.end() - 1), 5);
}

TYPED_TEST(TestDeque, insert_3) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);

    ASSERT_EQ(*x.insert(x.begin(), 5), 5);
    ASSERT_EQ(x[0], 5);
    ASSERT_EQ(x[1], 3);
}

TYPED_TEST(TestDeque, insert_4) 
{
    NAMES
    deque_type x;
    x.insert(x.begin(), 5);
    ASSERT_EQ(x[0], 5);
}

TYPED_TEST(TestDeque, insert_5) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.push_back(2);
    x.pop_front();

    x.insert(x.begin(), 10);
    ASSERT_EQ(x[0], 10);
    ASSERT_EQ(x[1], 2);
}

TYPED_TEST(TestDeque, insert_6) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.pop_front();

    x.insert(x.end(), 10);
    ASSERT_EQ(*(x.end()-1), 10);
}

TYPED_TEST(TestDeque, erase_1) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.erase(x.begin());

    ASSERT_EQ(x[0], 2);
}

TYPED_TEST(TestDeque, erase_2) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.insert(x.end(), 5);
    x.erase(x.end());
    
    ASSERT_EQ(*(x.end() - 1), 1);
}

TYPED_TEST(TestDeque, erase_3) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);

    x.insert(x.begin(), 5);
    x.erase(x.begin());

    ASSERT_EQ(x[0], 3);
}

TYPED_TEST(TestDeque, erase_4) 
{
    NAMES
    deque_type x;
    x.insert(x.begin(), 5);
    x.erase(x.begin());
    assert(x.empty());
}

TYPED_TEST(TestDeque, erase_5) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.push_back(2);
    x.pop_front();

    x.insert(x.begin(), 10);
    x.erase(x.begin());
    ASSERT_EQ(x[0], 2);
}

TYPED_TEST(TestDeque, erase_6) 
{
    NAMES
    deque_type x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.erase(x.begin());
    x.erase(x.begin());
    ASSERT_EQ(*x.begin(), 1);
}