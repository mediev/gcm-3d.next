all:
	g++ -c *.cpp
	g++ -o test *.o

run-perf-test:
	g++ -O0 --std=c++11 -o node_perf_test NodeTest.cpp
	./node_perf_test
	g++ -O1 --std=c++11 -o node_perf_test NodeTest.cpp
	./node_perf_test
	g++ -O2 --std=c++11 -o node_perf_test NodeTest.cpp
	./node_perf_test
	g++ -O3 --std=c++11 -o node_perf_test NodeTest.cpp
	./node_perf_test

clean:
	rm -f *.o
	rm -f test
	rm -f node_perf_test
