#include "libgcm/meshes/partitioners/InertiaMomentPartitioner.hpp"

using namespace gcm;

void InertiaMomentPartitioner::partMesh(Block *block, Mesh* mesh, 
                                        int N, real* proportions) {
	// partition is executed by recursive bisection
	bisectMesh(block, mesh, N, proportions);
}

void InertiaMomentPartitioner::findInertiaTensorMinAxis
                  (Mesh* mesh, const vector3r& rC, vector3r &minAxis) {
	real J[3][3]; // Inertia Tensor
	memset(J, 0, 9 * sizeof (real));
	uint elementsNum = mesh->getElementsNumber();
	for (uint i = 0; i < elementsNum; i++) {
		vector3r r = mesh->getCenterOfElement(i) - rC;
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
	
	// eigenvector related to the smallest eigenvalue is placed to the first column
	for (int j = 0; j < 3; j++)
		minAxis[j] = gsl_matrix_get(evec, j, 0);
	
	gsl_vector_free(eval);
	gsl_matrix_free(evec);
	gsl_matrix_free(J_gsl);
}

void InertiaMomentPartitioner::findBisectionParameters(Mesh* mesh, real p,
                                            vector3r &normal, vector3r &r0) {
	// center of mass of the mesh
	vector3r rC;
	uint elementsNum = mesh->getElementsNumber();
	for (uint i = 0; i < elementsNum; i++) {
		rC += mesh->getCenterOfElement(i);
	}
	rC /= elementsNum;

	// bisection is executed perpendicularly to the main axis 
	// related to the smallest main inertia moment of Inertia Tensor of the mesh
	findInertiaTensorMinAxis(mesh, rC, normal);

	// distance apart rC and the farthest point (along the normal) of mesh 
	real maxDist = 0;
	for (uint i = 0; i < elementsNum; i++) {
		real dist = (mesh->getCenterOfElement(i) - rC) * normal;
		maxDist = (dist > maxDist) ? dist : maxDist;
	}
	
	// bisection is executed through the r0 in order to keep required proportion
	r0 = rC + normal * maxDist * (1 - p) / (1 + p);
}

void InertiaMomentPartitioner::bisectMesh(Block *block, Mesh* mesh, 
                                          int N, real* proportions) {
	// bottom of recursion
	if (N == 1) {
		block->addMesh(mesh);
		return;
	}
	
	// weights of the parts mesh will be bisected
	real weight1 = 0;
	for (int i = 0; i < N/2; i++)
		weight1 += proportions[i];
	real weight2 = 0;
	for(int i = N/2; i < N; i++)
		weight2 += proportions[i];
	real proportion = weight1 / weight2;
	
	// mesh is bisected through r0 perpendicularly to normal
	vector3r r0, normal;
	findBisectionParameters(mesh, proportion, normal, r0);
	std::cout << "normal = " << normal << " r0 = " << r0 << std::endl;
	
	// two new child meshes
	uint nodesNum = mesh->getNodesNumber();
	Mesh *mesh1 = mesh->getMeshOfTheSameType();
	// FIXME - "1.2 * " is a way to prevent excess over preallocated size of
	// vector of nodes in meshes when we'll add nodes to it
	mesh1->initNodesWithoutValues(1.2 * (int) (nodesNum * proportion / (1 + proportion)));
	mesh1->setRheologyModel(mesh->getRheologyModel());
	Mesh *mesh2 = mesh->getMeshOfTheSameType();
	mesh2->initNodesWithoutValues(1.2 * (int) (nodesNum / (1 + proportion)));
	mesh2->setRheologyModel(mesh->getRheologyModel());
	
	// placing elements into one of the two new meshes depends on where is 
	// the center of the element located relative to the division surface
	uint elementsNum = mesh->getElementsNumber();
	for (uint i = 0; i < elementsNum; i++) {
		Element &element = mesh->getElementByLocalIndex(i);
		if ( (mesh->getCenterOfElement(i) - r0) * normal > 0 )
			mesh1->addElementWithNodes(element, mesh);
		else
			mesh2->addElementWithNodes(element, mesh);
	}
	
	// apply bisection to new meshes recursively
	mesh->~Mesh();
	bisectMesh(block, mesh1, N / 2, proportions);
	bisectMesh(block, mesh2, (N + 1) / 2, &(proportions[N/2]));
}
