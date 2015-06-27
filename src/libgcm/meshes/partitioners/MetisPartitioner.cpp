#include "libgcm/meshes/partitioners/MetisPartitioner.hpp"

using namespace gcm;

using std::shared_ptr;
using std::fill_n;
using std::to_string;

MetisPartitioner::MetisPartitioner()
{
}

MetisPartitioner::~MetisPartitioner()
{
}

void MetisPartitioner::partMesh(TetrMeshFirstOrder* mesh, const uint nparts, Block* block)
{
	assert_gt(nparts, 1);

	idx_t ne = mesh->getElementsNumber();
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
	options[METIS_OPTION_OBJTYPE] = METIS_OBJTYPE_VOL;
	options[METIS_OPTION_CONTIG] = 1;

	// For non-uniform partition
	/*real_t* tpwgts = new real_t [nparts];
	tpwgts[0] = 0.5;
	for(int i = 1; i < nparts; i++)
		tpwgts[i] = 0.5 / (real_t)(nparts-1);*/

	METIS_PartMeshDual(&ne, &nn, eptr, eind, nullptr, nullptr, &ncommon, &_nparts, nullptr, options, &objval, tetrPart.get(), nodePart.get());

	delete[] eptr;
	delete[] eind;

	uint nodesNum [nparts];
	uint tetrsNum [nparts];

	fill_n(nodesNum, nparts, 0);
	fill_n(tetrsNum, nparts, 0);

	for(int i = 0; i < nn; i++)
		nodesNum[nodePart.get()[i]]++;
	for(int i = 0; i < ne; i++)
			tetrsNum[tetrPart.get()[i]]++;

	TetrMeshFirstOrder* fineMesh = new TetrMeshFirstOrder [nparts];

	for(int i = 0; i < nparts; i++) {
		fineMesh[i].setRheologyModel(mesh->getRheologyModel());
		fineMesh[i].setId("TetrMesh" + to_string(i));
		fineMesh[i].initValuesInNodes(nodesNum[i]);
		fineMesh[i].createTetrs(tetrsNum[i]);
	}
		//printf("Part #%d: %d nodes\t%d tetrs\n", i, nodesNum[i], tetrsNum[i]);

	for(int i = 0; i < nn; i++)
		fineMesh[nodePart.get()[i]].addNode(mesh->getNode(i));

	for(int i = 0; i < ne; i++)
		fineMesh[tetrPart.get()[i]].addTetr(mesh->getTetrByLocalIndex(i));


	for(int i = 0; i < nparts; i++) {
		//fineMesh[i].preProcess();
		fineMesh[i].snapshot(i);
		block->addMesh(&fineMesh[i]);
	}
}

