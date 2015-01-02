#include<iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <vector>
#include <algorithm>
#include <new>

#include<math.h>
#include<stdlib.h>

#define DUMMY_FUNC [](){}

// Real parameters that matter
#define sizeOfVectorInPDE 10
#define sizeOfValuesInODEs 3
#define numberOfNodes 1000000
#define readIterations 100


using namespace std::chrono;
using namespace std;

typedef struct
{
    long time;
    long std_dev;
    long iterations;
} exec_time;

exec_time measure_time(std::function<void (void)> func, int n)
{
    vector<microseconds::rep> t(n);
    
    for (int i = 0; i < n; i++)
    {
        auto t1 = high_resolution_clock::now();
        func();
        auto t2 = high_resolution_clock::now();

        t[i] = duration_cast<microseconds>(t2-t1).count();
    }

    double mean = 0;

    for_each(t.begin(), t.end(), [&mean](microseconds::rep v)
    {
        mean += v; 
    });

    mean /= n;
    
    long d = 0;
    
    for_each(t.begin(), t.end(), [&d, mean](microseconds::rep v)
    {
        d += (v-mean)*(v-mean); 
    });

    exec_time et;
    et.time = mean;
    et.std_dev = sqrt(d/n);
    et.iterations = n;

    return et;
}

void print_test_results(std::string test1, exec_time time1, std::string test2, exec_time time2)
{
    cout << "Test run " << time1.iterations << " times" << endl;

    auto flags = cout.flags();

    cout << fixed;
    cout << setprecision(2);

    cout << test1 << ": " << time1.time << " usec (standard deviation is " << 100.0*time1.std_dev/time1.time << "%)" << endl;
    cout << test2 << ": " << time2.time << " usec (standard deviation is " << 100.0*time2.std_dev/time2.time << "%)" << endl;
    float ratio = 1.0*time1.time/time2.time;
    
    if (ratio < 1.0)
        cout << test1 << " is " << 1/ratio << "x faster" << endl;
    else
        cout << test2 << " is " << ratio << "x faster" << endl;

    cout << endl;
    cout.setf(flags);
}

class Node1 {
public:
    double *vectorInPDE;
    double *valuesInODEs;
    double coords[3];
    
    Node1();
    ~Node1();
    void initMemory(double *buffer, int nodeNum);
};

Node1::Node1() {
}

void Node1::initMemory(double *buffer, int nodeNum) {
    double* startAddr = buffer + nodeNum * (sizeOfVectorInPDE + sizeOfValuesInODEs);
    vectorInPDE = new (startAddr) double[sizeOfVectorInPDE];
    new double[50];
    valuesInODEs = new (startAddr + sizeOfVectorInPDE) double[sizeOfValuesInODEs];
}

Node1::~Node1() {
    //delete [] vectorInPDE;
    //delete [] valuesInODEs;
}


class Node2 {
public:
    double vectorInPDE[sizeOfVectorInPDE];
    double valuesInODEs[sizeOfValuesInODEs];
    double coords[3];
    
    Node2();
    ~Node2();
};

Node2::Node2() {
    new double[50];
}

Node2::~Node2() {
}


int main()
{
    Node1* n1 = new Node1[numberOfNodes];
    double* buffer = new double[(numberOfNodes * (sizeOfValuesInODEs + sizeOfVectorInPDE) * sizeof(double))];
    for (int i = 0; i < numberOfNodes; i++) {
        n1[i].initMemory(buffer, i);
    }

    Node2* n2 = new Node2[numberOfNodes];
    
    // Fill nodes
    for(int i = 0; i < numberOfNodes; i++) {
        for(int j = 0; j < 3; j++) {
            double v = 1.0 * (double) rand() / RAND_MAX;
            n1[i].coords[j] = v;
            n2[i].coords[j] = v;
        }
        for(int j = 0; j < sizeOfValuesInODEs; j++) {
            double v = 1.0 * (double) rand() / RAND_MAX;
            n1[i].valuesInODEs[j] = v;
            n2[i].valuesInODEs[j] = v;
        }
        for(int j = 0; j < sizeOfVectorInPDE; j++) {
            double v = 1.0 * (double) rand() / RAND_MAX;
            n1[i].vectorInPDE[j] = v;
            n2[i].vectorInPDE[j] = v;
        }
    }
    
    // Naive verify - just to ensure that everything is really filled and accessible
    for(int i = 0; i < numberOfNodes; i++) {
        for(int j = 0; j < 3; j++) {
            if(fabs(n1[i].coords[j] - n2[i].coords[j]) > 1e-9 )
                std::cout << "Mismatch\n";
        }
        for(int j = 0; j < sizeOfValuesInODEs; j++) {
            if(fabs(n1[i].valuesInODEs[j] - n2[i].valuesInODEs[j]) > 1e-9 )
                std::cout << "Mismatch\n";
        }
        for(int j = 0; j < sizeOfVectorInPDE; j++) {
            if(fabs(n1[i].vectorInPDE[j] - n2[i].vectorInPDE[j]) > 1e-9 )
                std::cout << "Mismatch\n";
        }
    }

    double r1 = 0.0;
    // Benchmark reading n1
    auto t1 = measure_time(
    [&]()
    {
        for(int i = 0; i < numberOfNodes; i++) {
            for(int j = 0; j < 3; j++) {
                r1 += n1[i].coords[j];
            }
            for(int j = 0; j < sizeOfValuesInODEs; j++) {
                r1 += n1[i].valuesInODEs[j];
            }
            for(int j = 0; j < sizeOfVectorInPDE; j++) {
                r1 += n1[i].vectorInPDE[j];
            }
        }
    }, readIterations);

    // Benchmark reading n2
    double r2 = 0.0;
    auto t2 = measure_time(
    [&]()
    {
        for(int i = 0; i < numberOfNodes; i++) {
            for(int j = 0; j < 3; j++) {
                r2 += n2[i].coords[j];
            }
            for(int j = 0; j < sizeOfValuesInODEs; j++) {
                r2 += n2[i].valuesInODEs[j];
            }
            for(int j = 0; j < sizeOfVectorInPDE; j++) {
                r2 += n2[i].vectorInPDE[j];
            }
        }
    }, readIterations);
    
    if(fabs(r1-r2) > 1e-9)
        std::cout << "Mismatch\n";
    
    print_test_results("Non-aligned", t1, "Aligned", t2);
    

    delete[] (n1);
    delete[] (n2);
    delete[] (buffer);

    return 0;
}