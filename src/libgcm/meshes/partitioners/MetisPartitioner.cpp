#include "libgcm/meshes/partitioners/MetisPartitioner.hpp"

using namespace gcm;

using std::string;
using std::shared_ptr;
using std::fill_n;
using std::to_string;

MetisPartitioner::MetisPartitioner()
{
}

MetisPartitioner::~MetisPartitioner()
{
}

void MetisPartitioner::partMesh(TetrMeshFirstOrder* mesh, const uint nparts, TetrMeshFirstOrder* coarsePart)
{
	assert_gt(nparts, 1);

	idx_t ne = mesh->getTetrsNumber();
	idx_t nn = mesh->getNodesNumber();

	idx_t* eptr = new idx_t [ne + 1];
	idx_t* eind = new idx_t [4 * ne];

	idx_t k = 0;
	for (int i = 0; i < ne; i++) {
		eptr[i] = k;
		TetrahedronFirstOrder& tetr = mesh->getTetrByLocalIndex(i);
	    eind[k++] = tetr.vertices[0];
	    eind[k++] = tetr.vertices[1];
	    eind[k++] = tetr.vertices[2];
	    eind[k++] = tetr.vertices[3];
	}
	eptr[ne] = k;

	idx_t ncommon = 3;
	idx_t _nparts = nparts;
	idx_t objval;
	shared_ptr<idx_t> tetrPart( new idx_t[ne], []( idx_t *p ) { delete[] p; } );
	shared_ptr<idx_t> nodePart( new idx_t[nn], []( idx_t *p ) { delete[] p; } );

	idx_t options[METIS_NOPTIONS];
	METIS_SetDefaultOptions(options);
	options[METIS_OPTION_OBJTYPE] = METIS_OBJTYPE_CUT;
	options[METIS_OPTION_CONTIG] = 1;
	options[METIS_OPTION_NUMBERING] = 0;

	// For non-uniform partition
	/*real_t* tpwgts = new real_t [nparts];
	tpwgts[0] = 0.5;
	for(int i = 1; i < nparts; i++)
		tpwgts[i] = 0.5 / (real_t)(nparts-1);*/

	// Main partitioning function
	METIS_PartMeshDual(&ne, &nn, eptr, eind, nullptr, nullptr, &ncommon, &_nparts, nullptr, options, &objval, tetrPart.get(), nodePart.get());

	printf("Number of edgecut = %d\n", objval);

	delete[] eptr;
	delete[] eind;

	uint nodesNum [nparts];
	uint tetrsNum [nparts];

	fill_n(nodesNum, nparts, 0);
	fill_n(tetrsNum, nparts, 0);

	// Getting number of nodes & elements belong to each part
	for(int i = 0; i < nn; i++)
		nodesNum[nodePart.get()[i]]++;
	for(int i = 0; i < ne; i++)
		tetrsNum[tetrPart.get()[i]]++;

	// Creating meshes for each part
	for(uint i = 0; i < nparts; i++) {
		coarsePart[i].setRheologyModel(mesh->getRheologyModel());
		coarsePart[i].setId(1000 + i);
		coarsePart[i].initNodesWithoutValues(nodesNum[i] + (int)(objval / 2 + 1));
		coarsePart[i].createTetrs(tetrsNum[i]);
	}

	// Filling meshes by tetrahedrons and nodes
	uint idx;
	for(int i = 0; i < ne; i++) {
		idx = tetrPart.get()[i];
		TetrahedronFirstOrder& tetr = mesh->getTetrByLocalIndex(i);
		for(int j = 0; j < 4; j++) {
			CalcNode& node = mesh->getNode(tetr.vertices[j]);
			if(!coarsePart[idx].hasNode(node.number))
				coarsePart[idx].addNode(node);
		}

		coarsePart[idx].addTetr(tetr);
	}


	for(uint i = 0; i < nparts; i++) {
		coarsePart[i].preProcess();
		coarsePart[i].snapshot(0);
	}
}

void MetisPartitioner::partMesh(CubicMesh* mesh, const uint nparts, CubicMesh* coarsePart)
{
	assert_gt(nparts, 1);

	idx_t ne = mesh->getElementsNumber();
	idx_t nn = mesh->getNodesNumber();

	idx_t* eptr = new idx_t [ne + 1];
	idx_t* eind = new idx_t [8 * ne];

	idx_t k = 0;
	for (int i = 0; i < ne; i++) {
		eptr[i] = k;
		Cube& cube = static_cast<Cube&>(mesh->getElementByLocalIndex(i));
		for(int j = 0; j < 8; j++) {
			eind[k++] = cube.vertices[j];
		}
	}
	eptr[ne] = k;

	idx_t ncommon = 4;
	idx_t _nparts = nparts;
	idx_t objval;
	shared_ptr<idx_t> cubesPart( new idx_t[ne], []( idx_t *p ) { delete[] p; } );
	shared_ptr<idx_t> nodePart( new idx_t[nn], []( idx_t *p ) { delete[] p; } );

	idx_t options[METIS_NOPTIONS];
	METIS_SetDefaultOptions(options);
	options[METIS_OPTION_OBJTYPE] = METIS_OBJTYPE_CUT;
	options[METIS_OPTION_CONTIG] = 1;
	options[METIS_OPTION_NUMBERING] = 0;

	// For non-uniform partition
	/*real_t* tpwgts = new real_t [nparts];
	tpwgts[0] = 0.5;
	for(int i = 1; i < nparts; i++)
		tpwgts[i] = 0.5 / (real_t)(nparts-1);*/

	// Main partitioning function
	METIS_PartMeshDual(&ne, &nn, eptr, eind, nullptr, nullptr, &ncommon, &_nparts, nullptr, options, &objval, cubesPart.get(), nodePart.get());

	printf("Number of edgecut = %d\n", objval);

	delete[] eptr;
	delete[] eind;

	uint nodesNum [nparts];
	uint cubesNum [nparts];

	fill_n(nodesNum, nparts, 0);
	fill_n(cubesNum, nparts, 0);

	// Getting number of nodes & elements belong to each part
	for(int i = 0; i < nn; i++)
		nodesNum[nodePart.get()[i]]++;
	for(int i = 0; i < ne; i++)
		cubesNum[cubesPart.get()[i]]++;

	// Creating meshes for each part
	for(uint i = 0; i < nparts; i++) {
		coarsePart[i].setRheologyModel(mesh->getRheologyModel());
		coarsePart[i].setId(1000 + i);
		coarsePart[i].initNodesWithoutValues(nodesNum[i] + (int)(objval));
		coarsePart[i].initElements(cubesNum[i]);
	}

	// Filling meshes by cubes and nodes
	uint idx;
	for(int i = 0; i < ne; i++) {
		idx = cubesPart.get()[i];
		Cube& cube = static_cast<Cube&>(mesh->getElementByLocalIndex(i));
		for(int j = 0; j < 8; j++) {
			CalcNode& node = mesh->getNode(cube.vertices[j]);
			if(!coarsePart[idx].hasNode(node.number))
				coarsePart[idx].addNode(node);
		}

		coarsePart[idx].addElement(cube);
	}

	for(uint i = 0; i < nparts; i++) {
		coarsePart[i].preProcess();
		coarsePart[i].snapshot(0);
	}
}

