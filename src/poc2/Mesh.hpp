#ifndef MESH_HPP
#define	MESH_HPP

#include <vector>

#include "Node.hpp"


class Mesh {
protected:
	std::vector<Node> nodes;
 	
public:
	Mesh();
	~Mesh();
	virtual void load(unsigned char sizeOfVectorInPDE, unsigned char sizeOfValuesInODEs) {};
	void addNode(Node node);
	Node& getNode(unsigned int n);
private:

};

class TetrMesh : public Mesh {
public:
	void load(unsigned char sizeOfVectorInPDE, unsigned char sizeOfValuesInODEs);
};

class CubicMesh : public Mesh {
public:
	void load(unsigned char sizeOfVectorInPDE, unsigned char sizeOfValuesInODEs);
};

#endif	/* MESH_HPP */

