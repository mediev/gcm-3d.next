#ifndef MODELS
#define MODELS 1

#include <vector>
#include "nodes.hpp"
#include "mesh.hpp"

// Base model
class Model
{
public:
    virtual void* createContainer(int numberOfNodes) const = 0;
};

class SupportsNodeWrapper1
{
public:
    NodeWrapper1 getWrapper1(const void* container) const = 0;
};

class SupportsNodeWrapper2
{
public:
    NodeWrapper2 getWrapper2(const void* container) const = 0;
};

class ModelOne : public Model, public SupportsNodeWrapper1
{
public:
    class NodeType: public Node<2, 5>
    {
    };

    void* createContainer(int numberOfNodes) const override
    {
        return new NodeType[numberOfNodes];
    }

    NodeWrapper1 getWrapper1(const void* container) const override
    {
        NodeType node;
        return NodeWrapper1(container, sizeof(node), &node.doubles[0], &node.ints[0]);
    }
};

class ModelTwo : public Model, public SupportsNodeWrapper1, public SupportsNodeWrapper2
{
public:
    class NodeType: public Node<1, 7>
    {
    };

    void* createContainer(int numberOfNodes) const override
    {
        return new NodeType[numberOfNodes];
    }
    
    NodeWrapper1 getWrapper1(const void* container) const override
    {
        NodeType node;
        return NodeWrapper1(container, sizeof(node), &node.doubles[0], &node.ints[0]);
    }
    
    NodeWrapper2 getWrapper2(const void* container) const override
    {
        NodeType node;
        return NodeWrapper1(container, sizeof(node), &node.doubles[0], &node.ints[1], &node.ints[0]);
    }
};

#endif
