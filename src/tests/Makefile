all:
	g++ --std=c++11 -c `ls *.cpp | grep -v Test`
	g++ --std=c++11 -o test *.o

run-perf-test1:
	g++ -O0 --std=c++11 -o node_perf_test1 NodeTest.cpp
	./node_perf_test1
	g++ -O1 --std=c++11 -o node_perf_test1 NodeTest.cpp
	./node_perf_test1
	g++ -O2 --std=c++11 -o node_perf_test1 NodeTest.cpp
	./node_perf_test1
	g++ -O3 --std=c++11 -o node_perf_test1 NodeTest.cpp
	./node_perf_test1

run-perf-test2:
	g++ -O0 --std=c++11 -o node_perf_test2 MemoryAllocTest.cpp
	./node_perf_test2
	g++ -O1 --std=c++11 -o node_perf_test2 MemoryAllocTest.cpp
	./node_perf_test2
	g++ -O2 --std=c++11 -o node_perf_test2 MemoryAllocTest.cpp
	./node_perf_test2
	g++ -O3 --std=c++11 -o node_perf_test2 MemoryAllocTest.cpp
	./node_perf_test2

clean:
	rm -f *.o
	rm -f test
	rm -f node_perf_test1
	rm -f node_perf_test2
