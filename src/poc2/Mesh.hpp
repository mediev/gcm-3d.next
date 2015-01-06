#ifndef MESH_HPP
#define	MESH_HPP

#include <vector>

#include "Node.hpp"
#include "Model.hpp"


class Mesh {
protected:
	std::vector<CalcNode> nodes;
	double *container;
	Model* model;
 	
public:
	Mesh();
	~Mesh();
	virtual void load() = 0;
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
private:

};

class TetrMesh : public Mesh {
public:
	void load();
};

class CubicMesh : public Mesh {
public:
	void load();
};

#endif	/* MESH_HPP */