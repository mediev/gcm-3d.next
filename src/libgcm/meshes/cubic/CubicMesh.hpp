#ifndef CUBICMESH_HPP
#define	CUBICMESH_HPP

#include <algorithm>

#include "libgcm/meshes/Mesh.hpp"
#include "libgcm/util/Math.hpp"
#include "libgcm/elements/Cube.hpp"
#include "libgcm/snapshotters/VTKCubicSnapshotWriter.hpp"

namespace gcm {
	class CubicMesh : public Mesh {

	friend class DataBus;

	protected:
		std::vector<Cube> cubes;
		void calcMinH();
		void preProcessGeometry();

		real meshH;
		// this variable is necessary to speed up search in function hasPoint
		uint cubeLocalIndexToStartCheckingInHasPointFunction;
	public:
		CubicMesh();
		~CubicMesh();

		void initElements(uint numberOfElements) override;
		
		Mesh* getMeshOfTheSameType() override;

		Element& getElementByLocalIndex(uint index) override;
		uint getElementsNumber() override;
		void addElement(Element& element) override;
		vector3r getCenterOfElement(uint index) override;
		void addElementWithNodes(Element& element, Mesh* mesh) override;
		void sortCubesInGlobalOrder();

		void checkTopology(real tau) override;
		bool hasPoint(const vector3r &r);
		AABB cubeToAABB(const Cube &cube);
		real getMinH();

		virtual const SnapshotWriter& getSnaphotter() const override;

	private:

	};
}

#endif	/* CUBICMESH_HPP */

