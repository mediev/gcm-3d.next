#ifndef GCM_VOLUME_CALCULATOR_H_
#define GCM_VOLUME_CALCULATOR_H_  1

#include <string>
#include <vector>

#include "libgcm/rheology/RheologyMatrix.hpp"


namespace gcm
{
    class CalcNode;
    /*
     * Base class for inner points calculators
     */
    class VolumeCalculator {
    public:
        /*
         * Destructor
         */
        virtual ~VolumeCalculator() = 0;
        /*
         * Calculate next state for the given node
         */
        virtual void doCalc(CalcNode& curNode, CalcNode& newNode, RheologyMatrixPtr matrix,
                                                std::vector<CalcNode>& previousNodes) = 0;
        /*
         * Returns type of the calculator
         */
        virtual std::string getType() = 0;

    private:

    };

}

#endif    /* GCM_VOLUME_CALCULATOR_H_ */