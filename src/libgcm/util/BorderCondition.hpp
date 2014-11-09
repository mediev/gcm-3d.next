#ifndef _GCM_BORDER_CONDITION_H
#define _GCM_BORDER_CONDITION_H 1

#include "libgcm/util/geometricRegions/Region.hpp"
#include "libgcm/util/waveForms/WaveForm.hpp"
#include "libgcm/calc/border/BorderCalculator.hpp"
#include "libgcm/node/CalcNode.hpp"

namespace gcm {
    class BorderCondition
    {
    public:
        BorderCondition();
        BorderCondition(Region& region, WaveForm& form, BorderCalculator& calc);
        ~BorderCondition();

        void doCalc(gcm::real time, CalcNode& curNode, CalcNode& newNode, 
                    RheologyMatrixPtr matrix,
                    std::vector<CalcNode>& previousNodes, std::vector<bool>& nodeIsInner,
                    gcm::vector3r outerNormal) = 0;
    };
}

#endif