#ifndef BLOCK_HPP
#define	BLOCK_HPP

#include "Model.hpp"
#include "Solver.hpp"
#include "Mesh.hpp"

class Block
{
	protected:
		Model* model;
		Solver* solver;
		Mesh* mesh;
	public:
		std::string name;
		
		Block(Mesh* _mesh) : mesh(_mesh) {};
		Block(std::string _name, Model* _model, Solver* _solver, Mesh* _mesh) : 
			name(_name), model(_model), solver(_solver), mesh(_mesh) {};
		
		void doCalc();
		void setModel();
		void load(std::vector<CalcNode>& vertices, unsigned char indx);
		bool checkTopology();
		void initContainer(double* container);
		Model* getModel();
};

#endif	/* BLOCK_HPP */
