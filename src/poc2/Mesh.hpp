#ifndef MESH_HPP
#define	MESH_HPP

#include <vector>

#include "Node.hpp"
#include "Model.hpp"


class Mesh {
protected:
	std::vector<RawNode> nodes;
	double *container;
	Model* model;
 	
public:
	Mesh();
	~Mesh();
	virtual void load() = 0;
	//FIXME TODO@avasyukov: how can we resize mesh on the fly?
	void initContainer(unsigned int numberOfNodes);
	CalcNode& getNodes();
	void setModel(Model* _model);
	void addNode(RawNode node);
	RawNode& createNode();
	RawNode& getNode(unsigned int n);
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