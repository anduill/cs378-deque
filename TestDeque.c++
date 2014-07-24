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
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;

    deque_type x;
    const size_type s = x.size();
    ASSERT_EQ(0, s);
}

TYPED_TEST(TestDeque, Size_2) {
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
   typedef typename TestFixture::allocator_type  allocator_type;
   typedef typename TestFixture::value_type      value_type;
   typedef typename TestFixture::size_type       size_type;
   typedef typename TestFixture::difference_type difference_type;
   typedef typename TestFixture::pointer         pointer;
   typedef typename TestFixture::const_pointer   const_pointer;
   typedef typename TestFixture::reference       reference;
   typedef typename TestFixture::const_reference const_reference;

   deque_type x;
   x.push_back(4);
   x.push_back(5);
   x.push_back(6);
   int four = *(x.begin());
   ASSERT_EQ(4,four);
}
TYPED_TEST(TestDeque, Iterator_2) {
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
   x.push_back(4);
   x.push_back(5);
   x.push_back(6);
   int five = *(++(x.begin()));
   ASSERT_EQ(5,five);
}

TYPED_TEST(TestDeque, push_front) {
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
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;

    deque_type x;
    for (int i = 0; i < 100; ++i)
    {
        x.push_back(1);
    }
    ASSERT_EQ(100, x.size());
}

TYPED_TEST(TestDeque, pop_front) {
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
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;

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
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;

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
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;

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
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;
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

    for (int i = 0; i < x.size(); ++i)
      cout << x[i] << endl;

    ASSERT_EQ(5, x.size());
}

TYPED_TEST(TestDeque, iterator_erase) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;
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