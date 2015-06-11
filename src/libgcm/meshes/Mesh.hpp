#ifndef GCM_MESH_H_
#define GCM_MESH_H_

#include <unordered_map>
#include <string>
#include <algorithm>
#include <assert.h>

#include "libgcm/util/NodeTypes.hpp"
#include "libgcm/nodes/CalcNode.hpp"
#include "libgcm/rheologyModels/models/RheologyModel.hpp"

typedef std::unordered_map<int, int>::const_iterator MapIter;


namespace gcm {
    /*
     * Base class for all meshes
     */
    class Mesh {
    protected:
        /*
         * Mesh id.
         */
        std::string id;
		std::string type;

        // TODO - restructure it after we have a concept regarding parallel impl
		RheologyModel* rheologyModel;

        /*
         * List of mesh nodes.
         */
        std::vector<CalcNode> nodes;
		/*
		 * Memory to store values of nodes
		 */
		real *valuesInNodes;
		
        std::vector<CalcNode> newNodes;
		real *valuesInNewNodes;
		
        // Maps 'global' ids of nodes to local indexes in node storage
        std::unordered_map<int, int> nodesMap;

        // If the mesh supports moving at all
        bool movable;

        USE_LOGGER;
		
        // Compatible snapshotter and dumper
//        virtual const SnapshotWriter& getSnaphotter() const = 0;
//        virtual const SnapshotWriter& getDumper() const = 0;

    public:
        /*
         * Constructor and destructor.
         */
        Mesh();
        // See http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
        virtual ~Mesh();
		void initValuesInNodes(unsigned int numberOfNodes);
		CalcNode& createNode(const real &x, const real &y, const real &z);
		
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
//        virtual void preProcessGeometry() = 0;
//
        // TODO: rename method
        /*
         * It is called before each time step.
         * You are supposed to perform necessary mesh operations here. Examples:
         * - rethink areaOfInterest, syncedArea, expandedOutline, etc
         * - optimize deformed mesh
         * Most probably, it should be just left blank for non-moving meshes.
         */
        virtual void checkTopology(float tau) = 0;
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
        int getNodesNumber();
        int getNumberOfLocalNodes();
        void initNewNodes();
		void initValuesContainer(unsigned int numberOfNodes);
        void setRheologyModel(RheologyModel *_model);
		RheologyModel *getRheologyModel();
		bool hasNode(int index);
        CalcNode& getNode(int index);
        CalcNode& getNewNode(int index);
        int getNodeLocalIndex(int index) const;
        CalcNode& getNodeByLocalIndex(unsigned int index);

        /*
         * Sets mesh id.
         */
        void setId(std::string id);
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

        void preProcess();

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

        float getMaxEigenvalue();
        float getMaxPossibleTimeStep();

        void defaultNextPartStep(float tau, int stage);
    };
}
#endif