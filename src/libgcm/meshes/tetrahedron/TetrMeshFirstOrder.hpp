#ifndef TETR_MESH_FIRST_ORDER_HPP
#define TETR_MESH_FIRST_ORDER_HPP

#include <unordered_map>
#include <algorithm>
#include <cassert>

#include "libgcm/elements/TetrahedronFirstOrder.hpp"
#include "libgcm/elements/TriangleFirstOrder.hpp"

#include "libgcm/meshes/tetrahedron/TetrahedronMesh.hpp"
#include "libgcm/elements/TetrahedronFirstOrder.hpp"
#include "libgcm/elements/TriangleFirstOrder.hpp"

#include "libgcm/rheologyModels/RheologyMatrix.hpp"
#include "libgcm/Engine.hpp"

#define STORAGE_ONDEMAND_GROW_RATE 1.25

namespace gcm {
	
	class TetrMeshFirstOrder : public TetrahedronMesh {
	protected:

		// List of first order tetrahedrons (local indexation)
		std::vector<TetrahedronFirstOrder> tetrs1;
		// Map of <global, local> tetrahedron index associations
		std::unordered_map<int, int> tetrsMap;
		// List of first order faces
		std::vector<TriangleFirstOrder> borders1;

		// The size of tetrs1
		int tetrStorageSize;
		// Number of tetrahedrons put into tetrs1
		int tetrsNumber;
		// The size of borders1
		int faceStorageSize;
		// Number of faces put into borders1
		int facesNumber;

		// Matrix that associate node local index with list of tetrahedrons indexes
        std::vector< std::vector<int> > volumeElements;
        // Matrix that associate node local index with list of faces indexes
        std::vector< std::vector<int> > borderElements;
        std::vector<int>& getVolumeElementsForNode(uint index);
        std::vector<int>& getBorderElementsForNode(uint index);

		// Calculating tetrahedron sizes & Creating all associations: volumeElements, borderElements, border nodes
		void preProcessGeometry();

        // Filling volumeElements & borderElements
        void build_volume_reverse_lookups();
        void build_surface_reverse_lookups();

        // Putting border flags for nodes
        void build_border();
        // Calculate an solid angle for a vertex of tetrahedron
        real get_solid_angle(uint node_index, uint tetr_index);

        // Check if triangle based on v[0], v[1], v[2] is border
        bool isTriangleBorder(uint v[4], bool* needSwap, bool debug);
        bool isTriangleBorder(uint v[4], bool* needSwap);
        bool isTriangleBorder(uint v[4], bool debug);
        bool isTriangleBorder(uint v[4]);

        // FIXME: What useful thing does it really do?
        TriangleFirstOrder createBorderTriangle(uint v[4], uint number);
        //void find_border_elem_normal(int border_element_index, real* x, real* y, real* z);

        // Check if {dx} displacement from node is inside the body
        int fastScanForOwnerTetr(const CalcNode& node, const vector3r& dx);


        // Return height of tetrahedron
        real tetr_h(int i);
        void calcMinH();
        void calcAvgH();
        void calcMaxH();
        void calcMaxEdge();
        // It MUST take into account mesh topology.
        // So, if the mesh will be second order, h = h / 2, etc
        real mesh_min_h;
        real mesh_avg_h;
        real mesh_max_h;
        real mesh_max_edge;

        // FIXME: Is it for communications between cores?
        unsigned long long cacheHits;
        unsigned long long cacheMisses;
        std::unordered_map<int, int> charactCache[18];
        bool charactCacheAvailable();
        bool checkCharactCache(const CalcNode& node, const vector3r& dx, int& tetrNum);
        void updateCharactCache(const CalcNode& node, const vector3r& x, int tetrNum);
        int getCharactCacheIndex(const CalcNode& node, const vector3r& dx);

	public:
		TetrMeshFirstOrder();
		virtual ~TetrMeshFirstOrder();

		void initElements(uint numberOfElements) override;
		void addElement(Element& element) override;
		vector3r getCenterOfElement(uint index) override;
		void addElementWithNodes(Element& element, Mesh* mesh) override;

		
		Mesh *getMeshOfTheSameType() override;

		/*
		 * Tetrahedron's routines
		 */
		// Add current tetrahedron to storage
		void addTetr(TetrahedronFirstOrder& tetr);
		// Resizing of storage
		void createTetrs(int number);
		int getTetrsNumber();
		
		Element& getElementByLocalIndex(uint index) override;
		uint getElementsNumber() override;

		// Returns tetrahedron from tetrs1 by local index
		TetrahedronFirstOrder& getTetrByLocalIndex(uint index);
		// Return tetrahedron from tetrsMap
		TetrahedronFirstOrder& getTetr(uint index);

		bool hasTetr(unsigned int index);

		/*
		 * Triangle's routines
		 */
		// Add current triangle to storage
		void addTriangle(TriangleFirstOrder& tri);
		// Resizing of storage
		void createTriangles(int number);
		int getTriangleNumber();

		// Returns triangle from borders1
		TriangleFirstOrder& getTriangle(uint index);

		bool belongsToTetrahedron(int nodeNum, int tetrNum, int faceNum);

        real getMinH();
        real getMaxH();
        real getAvgH();
        real getMaxEdge();
		void checkTopology(real tau) override;

		void createOutline();
	};
	
}

#endif /* TETR_MESH_FIRST_ORDER_HPP */
