#ifndef NODES
#define NODES 1

template<int intVariables, int doubleVariables>
class Node
{
    int ints[intVariables];
    double doubles[doubleVariables];
};

class NodeWrapper
{
    protected:
        char* ptr;
        int size;
    public:
        NodeWrapper(const void* ptr, int size): ptr((char*)ptr), size(size)
        {
        }

        NodeWrapper& operator++()
        {
            ptr += size;
        }
};

class NodeWrapper1: public NodeWrapper
{
    /*
     * double A;
     * int B;
     */

    protected:
        int offsetA, offsetB;
    public:
        NodeWrapper(const void* ptr, int size, const double* A, const int* B): NodeWrapper(ptr, size), offsetA((char*)A-(char*)ptr), offsetB((char*)B-(char*)ptr)
        {
        }

        double getA()
        {
            return *(double*)(ptr+offsetA);
        }

        int getB()
        {
            return *(int*)(ptr+offsetB);
        }
};

class NodeWrapper2: public NodeWrapper
{
    /*
     * double A;
     * int B;
     * int C;
     */

    protected:
        int offsetA, offsetB, offsetC;
    public:
        NodeWrapper(const void* ptr, int size, const double* A, const int* B, const int* C): NodeWrapper(ptr, size), offsetA((char*)A-(char*)ptr), offsetB((char*)B-(char*)ptr), offsetC((char*)C-(char*)ptr)
        {
        }

        double getA()
        {
            return *(double*)(ptr+offsetA);
        }

        int getB()
        {
            return *(int*)(ptr+offsetB);
        }
        
        int getC()
        {
            return *(int*)(ptr+offsetC);
        }
};

#endif
