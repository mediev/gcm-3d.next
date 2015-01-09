#ifndef MESH_HPP
#define	MESH_HPP

#include <vector>
#include <stdio.h>
#include <string>

#include "Node.hpp"
#include "Model.hpp"

#define NODES_IN_TEST_MESH 8

class Mesh {
protected:
	std::vector<CalcNode> nodes;
	double *container;
	Model* model;
	double elem_size;
 	
public:
	Mesh();
	~Mesh();
	virtual void load(std::vector<CalcNode>& vertices, unsigned char indx) = 0;
	//FIXME TODO@avasyukov: how can we resize mesh on the fly?
	void initContainer(unsigned int numberOfNodes);
	void setModel(Model* _model);
	Model *getModel();
	//TODO@avasyukov - do we need it?
	//CalcNode& getNodes();
	void addNode(CalcNode node);
	CalcNode& createNode();
	CalcNode& getNode(unsigned int n);
	unsigned int getNodesNumber();
	double getH();
	double getMinH();
	bool checkTopology();
private:

};

class TetrMesh : public Mesh {
public:
	void load(std::vector<CalcNode>& vertices, unsigned char indx);
};

class CubicMesh : public Mesh {
public:
	void load(std::vector<CalcNode>& vertices, unsigned char indx);
};

#endif	/* MESH_HPP */
