#ifndef GCM_CONTACT_CALCULATOR_H_
#define GCM_CONTACT_CALCULATOR_H_  1

#include <string>
#include <vector>

#include "libgcm/Logging.hpp"
#include "libgcm/node/CalcNode.hpp"
#include "libgcm/rheology/RheologyMatrix.hpp"


namespace gcm
{
    /*
     * Base class for inner points calculators
     */
    class ContactCalculator {
    public:
        /*
         * Destructor
         */
        virtual ~ContactCalculator() = 0;
        /*
         * Calculate next state for the given node
         */
        virtual void doCalc(CalcNode& curNode, CalcNode& newNode, CalcNode& virtNode,
                    RheologyMatrixPtr matrix, 
                    std::vector<CalcNode>& previousNodes, std::vector<bool>& nodeIsInner,
                    RheologyMatrixPtr virtMatrix, 
                    std::vector<CalcNode>& virtPreviousNodes, std::vector<bool>& virtNodeIsInner,
                    gcm::vector3r outerNormal, gcm::real externalValuesNorm) = 0;
        /*
         * Returns type of the calculator
         */
        std::string getType();
    };
}

#endif    /* GCM_CONTACT_CALCULATOR_H_ */