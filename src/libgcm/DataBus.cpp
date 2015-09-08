#include "libgcm/DataBus.hpp"

using namespace gcm;
using namespace MPI;
using std::vector;

#define BARRIER(name) \
do { \
    LOG_DEBUG("Entering barrier: " << name); \
    COMM_WORLD.Barrier(); \
    LOG_DEBUG("Barrier passed: " << name); \
} while(0)

DataBus::DataBus()
{
	rank = COMM_WORLD.Get_rank();

	createStaticTypes();
}

DataBus::~DataBus()
{

}

void DataBus::createStaticTypes()
{
	CalcNode* empty_node = new CalcNode [2];
	TetrahedronFirstOrder* tetr = new TetrahedronFirstOrder [2];
	Cube* cube = new Cube [2];

	// Empty node
	Datatype empty_node_types[] = {
		LB,
		FLOAT,
		UNSIGNED,
		UB
	};

	int empty_node_lengths [] = { 1, 3, 1, 1};

	Aint empty_node_disp[] = {
			Get_address(&empty_node[0]),
			Get_address(&empty_node[0].coords[0]),
			Get_address(&empty_node[0].number),
			Get_address(&empty_node[1])
	};

	for(int i = 3; i >= 0; i--)
		empty_node_disp[i] -= Get_address(&empty_node[0]);

	MPI_EMPTY_NODE = Datatype::Create_struct(4, empty_node_lengths, empty_node_disp, empty_node_types);

	// Tetrahedron
	Datatype tetr_types[] = {
		LB,
		UNSIGNED,
		UNSIGNED,
		UB
	};

	int tetr_lengths [] = { 1, 4, 1, 1};

	Aint tetr_disp[] = {
			Get_address(&tetr[0]),
			Get_address(&tetr[0].vertices[0]),
			Get_address(&tetr[0].number),
			Get_address(&tetr[1])
	};

	for(int i = 3; i >= 0; i--)
		tetr_disp[i] -= Get_address(&tetr[0]);

	MPI_TETR = Datatype::Create_struct(4, tetr_lengths, tetr_disp, tetr_types);

	// Cube
	Datatype cube_types[] = {
		LB,
		UNSIGNED,
		UNSIGNED,
		UB
	};

	int cube_lengths [] = { 1, 8, 1, 1};

	Aint cube_disp[] = {
			Get_address(&cube[0]),
			Get_address(&cube[0].vertices[0]),
			Get_address(&cube[0].number),
			Get_address(&cube[1])
	};

	for(int i = 3; i >= 0; i--)
		cube_disp[i] -= Get_address(&cube[0]);

	MPI_CUBE = Datatype::Create_struct(4, cube_lengths, cube_disp, cube_types);

	MPI_EMPTY_NODE.Commit();
	MPI_TETR.Commit();
	MPI_CUBE.Commit();

}

void DataBus::transferMesh(TetrMeshFirstOrder* mesh, uint targetRank)
{

	BARRIER("DataBus: starting coarse meshes delivery!");
	if(rank == 0) {

		// Sending nodes
		MPI_Send(&mesh->nodes[0], mesh->nodes.size(), MPI_EMPTY_NODE, targetRank, 0, MPI_COMM_WORLD);

		// Sending tetrahedrons
		MPI_Send(&mesh->tetrs1[0], mesh->tetrs1.size(), MPI_TETR, targetRank, 0, MPI_COMM_WORLD);

	} else {
		int size;
		MPI_Status status;

		vector<CalcNode> nodes;
		vector<TetrahedronFirstOrder> tetrs;
    
		// Receiving nodes
		MPI_Probe(targetRank, 0, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_EMPTY_NODE, &size);
		nodes.resize(size);
		MPI_Recv(&nodes[0], size, MPI_EMPTY_NODE, targetRank, 0, MPI_COMM_WORLD, &status);
		
		mesh->initNodesWithoutValues(size);
		for(int i = 0; i < size; i++)
			mesh->addNode(nodes[i]);

		// Receiving tetrahedrons
		MPI_Probe(targetRank, 0, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_TETR, &size);
		tetrs.resize(size);
		MPI_Recv(&tetrs[0], size, MPI_TETR, targetRank, 0, MPI_COMM_WORLD, &status);
		
		mesh->createTetrs(size);
		for(int i = 0; i < size; i++)
			mesh->addTetr(tetrs[i]);

	}

	BARRIER("DataBus: coarse meshes transfered!");

}
