#ifndef CUBICMESH_HPP
#define	CUBICMESH_HPP

#include "libgcm/meshes/Mesh.hpp"
#include "libgcm/util/Math.hpp"
#include "libgcm/elements/Cube.hpp"

namespace gcm {
	class CubicMesh : public Mesh {
	protected:
		std::vector<Cube> cubes;
		void calcMinH();
		void preProcessGeometry();

		real meshH;
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

		// Redefining of virtual methods
		void checkTopology(real tau) override;
		void createOutline();
		real getMinH();

	private:

	};
}

#endif	/* CUBICMESH_HPP */

