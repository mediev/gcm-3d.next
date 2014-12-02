#include "body.hpp"

template <class NodeType, template <class NodeType> class MeshType>
Body<NodeType, MeshType>::Body()
{
	cout << "Body: creating without any parameters" << endl;
};

template <class NodeType, template <class NodeType> class MeshType>
Body<NodeType, MeshType>::~Body()
{
	for(typename vector<Block<NodeType, MeshType> >::iterator it = blocks.begin(); it != blocks.end(); ++it)
		delete it->mesh;
};

template <class NodeType, template <class NodeType> class MeshType>
void Body<NodeType, MeshType>::loadBlocks(unsigned int _blocksNum, unsigned int _nodesNum)
{
	for(int i = 0; i < _blocksNum; i++) {
		Block<NodeType, MeshType> block;
		block.mesh = new MeshType<NodeType>;
		block.mesh->load(_nodesNum);
		blocks.push_back(block);
	}
};

template <class NodeType, template <class NodeType> class MeshType>
void Body<NodeType, MeshType>::load(Solver<NodeType>* _solver, Model* _model)
{
	solver = _solver;
	model = _model;
	cout << "Body: Solver & Model pointers were loaded" << endl;
};

template <class NodeType, template <class NodeType> class MeshType>
void Body<NodeType, MeshType>::doCalc()
{
	for(typename vector<Block<NodeType, MeshType> >::iterator it = blocks.begin(); it != blocks.end(); ++it)
	{
		unsigned int n = it->mesh->nodesNum();
		for(int i = 0; i < n; i++)
			solver->doCalc(it->mesh->getNode(i));
	}		
	cout << "Body: " << blocks.size() << " blocks were calculated" << endl;
};

template class Body<FirstNode, CubicMesh>;
template class Body<FirstNode, TetrMesh>;
template class Body<SecondNode, CubicMesh>;
template class Body<SecondNode, TetrMesh>;
template class Body<ThirdNode, CubicMesh>;
template class Body<ThirdNode, TetrMesh>;
