#ifndef GCM_SOLVER_H
#define GCM_SOLVER_H

#include <string>

#include "libgcm/mesh/Mesh.hpp"

#include "libgcm/calc/volume/VolumeCalculator.hpp"
#include "libgcm/calc/border/BorderCalculator.hpp"
#include "libgcm/calc/contact/ContactCalculator.hpp"
#include "libgcm/interpolator/TetrInterpolator.hpp"
#include "libgcm/interpolator/TetrFirstOrderInterpolator.hpp"
#include "libgcm/interpolator/TetrSecondOrderMinMaxInterpolator.hpp"
#include "libgcm/interpolator/LineFirstOrderInterpolator.hpp"


namespace gcm {
    /*
     * Numerical method
     */
    class GcmSolver {
    public:
        /*
         * Constructor
         */
        GcmSolver();
        /*
         * Destructor
         */
        virtual ~GcmSolver() = 0;

        /*
         * Computes next state (after the next part step) for the given node
         */
        // TODO: does it mean that solver will contain everything that is in Engine now?
        virtual void doNextTimeStep() = 0;

        virtual std::string getType() = 0;

        int getSpaceOrder();
        int getTimeOrder();

        virtual const RheologyModel& getRheologyModel() const = 0;
        virtual const FailureModel& getFailureModel() const = 0;
        virtual const CrossPointFinder& getCrossPointFinder() const = 0;
        // TODO: Solver provides default decomposer but the model can provide custom one
        virtual const RheologyMatrixDecomposer& getRheologyMatrixDecomposer() const = 0;
        virtual const RightHandSideSolver& getRightHandSideSolver() const = 0;
        // TODO: how can we make Solver working with different meshes?
        virtual const Interpolator& getInterpolator() const = 0;
        virtual const MeshMover& getMeshMover() const = 0;
    };
}

#endif    /* GCM_SOLVER_H */