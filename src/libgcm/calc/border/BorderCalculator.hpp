#ifndef GCM_BORDER_CALCULATOR_H_
#define GCM_BORDER_CALCULATOR_H_  1

#include <string>
#include <vector>

#include "libgcm/Logging.hpp"
#include "libgcm/node/CalcNode.hpp"
#include "libgcm/rheology/RheologyMatrix.hpp"

#include "launcher/util/xml.hpp"


namespace gcm
{
    /*
     * Base class for inner points calculators
     */
    class BorderCalculator {
    public:
        /*
         * Destructor
         */
        virtual ~BorderCalculator() = 0;
        /*
         * Calculate next state for the given node
         */
        virtual void doCalc(CalcNode& curNode, CalcNode& newNode, 
                    RheologyMatrixPtr matrix,
                    std::vector<CalcNode>& previousNodes, std::vector<bool>& nodeIsInner,
                    gcm::vector3r outerNormal, gcm::real externalValuesNorm) = 0;
        /*
         * Returns type of the calculator
         */
        virtual std::string getType() = 0;
		
		// TODO: we should either 'officially approve' using xml:Node here or implement loaders
		/*
		 * Initializes calculator parameters
		 */
		virtual void setParameters(const xml::Node& params) = 0;
    };
}

#endif    /* GCM_BORDER_CALCULATOR_H_ */