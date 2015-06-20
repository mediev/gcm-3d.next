#ifndef GCM_MESH_HPP
#define GCM_MESH_HPP

#include <unordered_map>
#include <string>
#include <algorithm>
#include <assert.h>
#include <limits>
#include <cmath>

#include "libgcm/util/NodeTypes.hpp"
#include "libgcm/nodes/CalcNode.hpp"
#include "libgcm/rheologyModels/models/RheologyModel.hpp"
#include "libgcm/util/Math.hpp"
#include "libgcm/snapshotters/SnapshotWriter.hpp"

typedef std::unordered_map<int, int>::const_iterator MapIter;

namespace gcm {
    /*
     * Base class for all meshes
     */
    class Mesh {
    protected:
    	// Id of mesh
        std::string id;
        // Type of mesh
		std::string type;

        // TODO - restructure it after we have a concept regarding parallel impl
		// Rheology model used in the mesh
		RheologyModel* rheologyModel;

		/*
		 * Basic nodal objects
		 */
        // List of mesh nodes (local indexation)
        std::vector<CalcNode> nodes;
		// Pointer to memory for nodal data
		real *valuesInNodes;
		// Map of <global, local> nodal index associations
		std::unordered_map<int, int> nodesMap;
		// Number of nodes for reserving
		int nodeStorageSize;

		/*
		 * Basic objects for additional nodes
		 */
		// List of additional nodes
        //std::vector<CalcNode> newNodes;
        // Pointer to memory for new nodal data
		//real *valuesInNewNodes;

        // If the mesh supports moving at all
        bool movable;

        // Outline around mesh
        // AABB outline;

        USE_LOGGER;

        virtual const SnapshotWriter& getSnaphotter() const = 0;

    public:
        Mesh();
        // See http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
        virtual ~Mesh();
		void initNodesWithoutValues(unsigned int numberOfNodes);
		void addNode2(const CalcNode &node);

		virtual Mesh *getMeshOfTheSameType() = 0;

        // Preparing mesh for calculating
        void preProcess();
        // Remake mesh before calculation
        virtual void preProcessGeometry() = 0;

        /*
         * Nodal routines
         */
        // Allocate memory for values in nodes and reserve memory in mesh
		void initValuesInNodes(unsigned int numberOfNodes);
		// Add current node to storage
		void addNode(const CalcNode& node);
		// Provide an access to node by global index with map
		CalcNode& getNode(int index);
		// Provide an access to node by local index from vector directly
		CalcNode& getNodeByLocalIndex(uint index);
		// Provide local index for current global index
		int getNodeLocalIndex(int index) const;
        // TODO: Rethink about new_nodes
        //CalcNode& getNewNode(int index);

		// Return number of nodes put in storage
        uint getNodesNumber();

		/*
		 * Routines for rheology model access
		 */
        void setRheologyModel(RheologyModel *_model);
		RheologyModel *getRheologyModel();

		// Create an outline around mesh
		virtual void createOutline();

		// Checking mesh topology
		virtual void checkTopology(real tau) = 0;
		// Calculate minimal height of element among all
		virtual void calcMinH() = 0;
		virtual real getMinH() = 0;

		bool hasNode(int index);

        // Virtual functions to be implemented by children classes

//		/*	Comment until it will be realized in derived classes	*/
//        /*
//         * Should return time step that is considered ideal for the mesh.
//         * It may be courant step or whatever.
//         * The simpliest option is to return just getMaxPossibleTimeStep()
//         */
//		
//
//		virtual float getRecommendedTimeStep() = 0;
//
//        /*
//         * Performs the next part step using time step 'tau' and stage number 'stage'.
//         * Most probably just calling defaultNextPartStep(tau, stage) will work.
//         */
//        virtual void doNextPartStep(float tau, int stage) = 0;
//
//        /*
//         * Calculates and stores minimum h over mesh.
//         * Minimum h is required very often, so we are to pre-calculate it.
//         */
//        virtual void calcMinH() = 0;
//
//        /*
//         * Returns pre-calculated minumum h
//         */
//        virtual float getMinH() = 0;
//
//        /*
//         * Performs mesh pre-processing
//         * It is called
//         *    (a) either after the mesh was created
//         *    (b) or after mesh nodes were rebalanced
//         */
//
//
        // TODO: rename method
        /*
         * It is called before each time step.
         * You are supposed to perform necessary mesh operations here. Examples:
         * - rethink areaOfInterest, syncedArea, expandedOutline, etc
         * - optimize deformed mesh
         * Most probably, it should be just left blank for non-moving meshes.
         */
//
//        /*
//         * Logs major mesh stats (obviously, it's specific for each mesh type)
//         */
//        virtual void logMeshStats() = 0;
//
//        // TODO: rethink methods for interpolation.
//        // Most probably we can reduce the number of similar functions.
//
//        /*
//         * Interpolates node that is (dx; dy; dz) from 'origin'.
//         * Return value - is the node was interpolated (as internal volume node or border cross).
//         * Returns interpolated results in 'targetNode'.
//         * Sets 'isInnerPoint' flag.
//         * If returns 'false', targetNode is undefined.
//         */
//        virtual bool interpolateNode(CalcNode& origin, float dx, float dy, float dz, bool debug,
//                                CalcNode& targetNode, bool& isInnerPoint) = 0;
//
//        /*
//         * Interpolates given point, returns values in the node itself.
//         * Returns 'true' if interpolated successfully
//         * and 'false' if the node can not be interpolated with this mesh.
//         */
//        virtual bool interpolateNode(CalcNode& node) = 0;
//        
//        /*
//         * Takes vector from (x; y; z) with length (dx; dy; dz) and
//         * finds its intersection with mesh border.
//         * It's a separate function since (x; y; z) is outside of the mesh, 
//         * and we neither have 'origin' node nor exact 'target' node position.
//         * Returns 'true' if vector intersects mesh border and target node interpolated successfully.
//         * Returns 'false' if vector does not intersect mesh border.
//         */
//        virtual bool interpolateBorderNode(real x, real y, real z, 
//                                real dx, real dy, real dz, CalcNode& node) = 0;
//
//        virtual void findBorderNodeNormal(const CalcNode& node, float* x, float* y, float* z, bool debug) = 0;


        std::string snapshot(int number);
        std::string dump(int number);

        // TODO: rethink the list of the functions below.
        // It definetely contains some sheet.

        // We place all these functions into generic mesh to simplify children classes.
        // It allows to remove nodesMap complexity (required by parallel impl) from children classes.
        // We do believe that all children classes will use the same node storage.
        // If it's not the case, we need to convert these functions into virtual.

        /*
         * Sets mesh id.
         */
        void setId(std::string _id);
        /*
         * Returns mesh id.
         */
        std::string getId() const;
        /*
         * Returns type of mesh.
         */
        std::string getType();

        void setMovable(bool movable);
        bool getMovable();

//        virtual void createOutline();
//        AABB getOutline();
//        const AABB& getExpandedOutline() const;
//        void setInitialState(Area* area, float* values);
//		void setBorderCondition(Area* area, unsigned int num);
//		void setContactCondition(Area* area, unsigned int num);
//        void setRheology(unsigned char matId);
//        void setRheology(unsigned char matId, Area* area);

//        virtual void transfer(float x, float y, float z);
		void scale(float x0, float y0, float z0, 
				float scaleX, float scaleY, float scaleZ);
//        void applyRheology(RheologyCalculator* rc);
        void clearContactState();
        void clearNodesState();
        void processStressState();
//        void processMaterialFailure(FailureModel* failureModel, const float tau);
        void applyCorrectors();
//        virtual void moveCoords(float tau);

        real getMaxEigenvalue();
        real getMaxPossibleTimeStep();
    };
}
#endif
