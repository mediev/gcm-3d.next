#ifndef BODY_HPP
#define BODY_HPP 1

#include "meshes.hpp"
#include "models.hpp"
#include "block.hpp"
#include "solvers.hpp"
#include <new>

template <class NodeType, template <class NodeType> class MeshType>
class Body
{
	protected:
		vector<Block<NodeType, MeshType> > blocks;
		Model* model;
		Solver<NodeType>* solver;
	public:
		Body();
		Body(vector<Block<NodeType, MeshType> > _blocks, Solver<NodeType>* _solver, Model* _model) : blocks(_blocks), solver(_solver), model(_model) {};
		~Body();
		
		void loadBlocks(unsigned int _blocksNum, unsigned int _nodesNum);
		void load(Solver<NodeType>* _solver, Model* _model);
		void doCalc();
};

#endif
