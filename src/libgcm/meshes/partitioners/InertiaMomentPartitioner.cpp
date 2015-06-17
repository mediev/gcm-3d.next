#include "libgcm/meshes/partitioners/InertiaMomentPartitioner.hpp"

using namespace gcm;

void InertiaMomentPartitioner::partMesh(Mesh* mesh, int N, real* proportions) {
	bisectMesh(mesh, N);
}

void InertiaMomentPartitioner::findInertiaTensorMinAxis
                  (Mesh* mesh, const vector3r& rC, vector3r &minAxis) {
	real J[3][3];
	memset(J, 0, 9 * sizeof (real));
	unsigned int nodesNum = mesh->getNodesNumber();
	for (unsigned int i = 0; i < nodesNum; i++) {
		vector3r r = mesh->getNodeByLocalIndex(i).coords - rC;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				J[i][j] += (i == j) * r * r - r[i] * r[j];
	}
	
	gsl_matrix *J_gsl = gsl_matrix_alloc(3, 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			gsl_matrix_set(J_gsl, i, j, J[i][j]);
	
	gsl_vector *eval = gsl_vector_alloc(3);
	gsl_matrix *evec = gsl_matrix_alloc(3, 3);
	gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(3);
	gsl_eigen_symmv(J_gsl, eval, evec, w);
	gsl_eigen_symmv_free(w);
	gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_ASC);
	
	for (int j = 0; j < 3; j++)
		minAxis[j] = gsl_matrix_get(evec, j, 0);
	
	gsl_vector_free(eval);
	gsl_matrix_free(evec);
	gsl_matrix_free(J_gsl);
}

void InertiaMomentPartitioner::findBisectionParameters(Mesh* mesh, real p,
                                            vector3r &normal, vector3r &r0) {
	vector3r rC; // center of mass
	unsigned int nodesNum = mesh->getNodesNumber();
	for (unsigned int i = 0; i < nodesNum; i++) {
		rC += mesh->getNodeByLocalIndex(i).coords;
	}
	rC /= nodesNum;

	findInertiaTensorMinAxis(mesh, rC, normal);

	real maxDist = 0;
	for (unsigned int i = 0; i < nodesNum; i++) {
		real dist = (mesh->getNodeByLocalIndex(i).coords - rC) * normal;
		maxDist = (dist > maxDist) ? dist : maxDist;
	}
	
	r0 = rC + normal * maxDist * (1 - p) / (1 + p);
}

void InertiaMomentPartitioner::bisectMesh(Mesh* mesh, int N) {
	if (N == 1) return;
	real proportion = ((real) (N / 2)) / ((N + 1) / 2);
	vector3r r0, normal;
	findBisectionParameters(mesh, proportion, normal, r0);
	std::cout << "normal = " << normal << " r0 = " << r0 << std::endl;
	
	unsigned int nodesNum = mesh->getNodesNumber();
	Mesh *mesh1 = mesh->getMeshOfTheSameType();
	mesh1->initNodesWithoutValues((int) (nodesNum * proportion / (1 + proportion)));
	Mesh *mesh2 = mesh->getMeshOfTheSameType();
	mesh2->initNodesWithoutValues((int) (nodesNum / (1 + proportion)));
	for (unsigned int i = 0; i < nodesNum; i++) {
		const CalcNode &node = mesh->getNodeByLocalIndex(i);
		if ( (node.coords - r0) * normal > 0 )
			mesh1->addNode2(node);
		else
			mesh2->addNode2(node);
	}
	bisectMesh(mesh1, N / 2);
	bisectMesh(mesh2, (N + 1) / 2);
}


