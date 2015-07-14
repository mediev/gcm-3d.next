#include "libgcm/meshes/partitioners/InertiaMomentPartitioner.hpp"

using namespace gcm;

void InertiaMomentPartitioner::partMesh(Block* block, Mesh* mesh, 
                                        const std::map<uint, real>& propsMap) {
	uint N = propsMap.size();
	real *proportions = new real[N];
	uint *ranks = new uint[N];
	uint counter = 0;
	for(auto it = propsMap.begin(); it != propsMap.end(); it++) {
		proportions[counter] = it->second;
		ranks[counter] = it->first;
		counter++;
	}
	
	// for best partition results - it's much better to bisect mesh into
	// approximately equal parts than into any parts
	fractalBalance(proportions, ranks, N);
	
	// partition is executed by recursive bisection
	bisectMesh(block, mesh, N, proportions, ranks);
	
	delete [] proportions;
	delete [] ranks;
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
	// related to the smallest main inertia moment
	findInertiaTensorMinAxis(mesh, rC, normal);
	
	// in order to erase computational errors
	int ind = 0; // number of axis along normal
	if (fabs(normal[ind]) < fabs(normal[1]))
		ind = 1;
	if (fabs(normal[ind]) < fabs(normal[2]))
		ind = 2;
	if (fabs(normal[ind]) > cos(M_PI/12)) {
		normal[ind] = 1;
		normal[(ind+1)%3] = normal[(ind+2)%3] = 0;
	}

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
                                          uint N, real* proportions, uint *ranks) {
	// bottom of recursion
	if (N == 1) {
		mesh->setRank(*ranks);
		block->addMesh(mesh);
		return;
	}
	
	// weights of the parts mesh will be bisected
	real weight1 = 0;
	for (uint i = 0; i < N/2; i++)
		weight1 += proportions[i];
	real weight2 = 0;
	for(uint i = N/2; i < N; i++)
		weight2 += proportions[i];
	real proportion = weight1 / weight2;
	
	// mesh is bisected through r0 perpendicularly to normal
	vector3r r0, normal;
	findBisectionParameters(mesh, proportion, normal, r0);
	std::cout << "normal = " << normal << " r0 = " << r0 << std::endl;
	
	// two new child meshes
	uint nodesNum = mesh->getNodesNumber();
	Mesh *mesh1 = mesh->getMeshOfTheSameType();
	mesh1->initNodesWithoutValues(nodesNum);
	mesh1->setRheologyModel(mesh->getRheologyModel());
	Mesh *mesh2 = mesh->getMeshOfTheSameType();
	mesh2->initNodesWithoutValues(nodesNum);
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
	bisectMesh(block, mesh1, N / 2, proportions, ranks);
	bisectMesh(block, mesh2, (N + 1) / 2, &(proportions[N/2]), &(ranks[N/2]));
}

void InertiaMomentPartitioner::fractalBalance(real* arr, uint *ranks, uint N) {
	if (N == 1) return;
	
	real *tmpArr = new real[N];
	uint *tmpRanks = new uint[N];
	uint f = 0; // index of next cell of the first half
	uint s = N/2; // index of next cell of the second half
	
	for(uint counter = 1; counter < N+1; counter++) {
		real maxVal = 0;
		int maxInd = 0;
		for(uint ind = 0; ind < N; ind++)
			if (arr[ind] > maxVal) {
				maxVal = arr[ind];
				maxInd = ind;
			}
		arr[maxInd] = 0;
		if ( (counter % 4 == 0) || (counter % 4 == 1) ) {
			if (f < N/2) {tmpArr[f] = maxVal; tmpRanks[f] = ranks[maxInd]; f++;}
			else         {tmpArr[s] = maxVal; tmpRanks[s] = ranks[maxInd]; s++;}
		}
		else {
			if (s < N) {tmpArr[s] = maxVal; tmpRanks[s] = ranks[maxInd]; s++;}
			else       {tmpArr[f] = maxVal; tmpRanks[f] = ranks[maxInd]; f++;}
		}
	}
	
	for(uint i = 0; i < N; i++) {
		arr[i] = tmpArr[i];
		ranks[i] = tmpRanks[i];
	}
	delete [] tmpArr;
	delete [] tmpRanks;
	
	fractalBalance(arr, ranks, N/2);
	fractalBalance(&(arr[N/2]), &(ranks[N/2]), (N+1)/2);
}

