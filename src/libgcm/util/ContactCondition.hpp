#ifndef _GCM_CONTACT_CONDITION_H
#define _GCM_CONTACT_CONDITION_H 1

#include "libgcm/util/geometricRegions/Region.hpp"
#include "libgcm/util/waveForms/WaveForm.hpp"
#include "libgcm/calc/contact/ContactCalculator.hpp"
#include "libgcm/node/CalcNode.hpp"

namespace gcm {
    class ContactCondition
    {
    protected:
        /** 
         * Parameter of contact condition. It is interpreted by contact calculator.
         * Depending on contact type it can be adhesion treshold, friction coefficient or smth else.
         */
        real conditionParam;
        
    public:
        ContactCondition();
        ContactCondition(Region& region, WaveForm& form, ContactCalculator& calc);
        ~ContactCondition();

        void doCalc(gcm::real time, CalcNode& curNode, CalcNode& newNode, CalcNode& virtNode,
                    RheologyMatrixPtr matrix, 
                    std::vector<CalcNode>& previousNodes, std::vector<bool>& nodeIsInner,
                    RheologyMatrixPtr virtMatrix, 
                    std::vector<CalcNode>& virtPreviousNodes, std::vector<bool>& virtNodeIsInner,
                    gcm::vector3r outerNormal = 0;

        void setConditionParam(gcm::real param);
        gcm::real getConditionParam() const;
    };
}

#endif
