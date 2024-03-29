all:

clean:
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  Deque.log
	rm -f  TestDeque
	rm -f  TestDeque.out
	rm -rf html

config:
	doxygen -g

doc: Deque.h
	doxygen Doxyfile

Deque.log:
	git log > Integer.log

TestDeque: Deque.h TestDeque.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread

TestDeque.out: TestDeque
	-valgrind TestDeque
	gcov-4.7 -b TestDeque.c++
	cat         TestDeque.c++.gcov
