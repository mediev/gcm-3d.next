#ifndef ICORRECTOR_HPP
#define ICORRECTOR_HPP 

#include "libgcm/node/CalcNode.hpp"

#include <memory>

namespace gcm
{
    /**
     * Interface to implement for rheology matrix corrector. Corrector is supposed to
     * perform node state correction after the main step is done 
     */
    class NodeStateCorrector
    {
        public:
            /**
             * Perform correction for the node
             *
             * @param node Node to perform correction on
             */
            virtual void correctNodeState(CalcNode& node, const MaterialPtr& material) = 0;
    };

    typedef std::shared_ptr<NodeStateCorrector> CorrectorPtr;
    
    template<typename T, typename...Args>
    std::shared_ptr<T> makeCorrectorPtr(Args...args)
    {
        return std::make_shared<T>(args...);
    }
};

#endif /* ICORRECTOR_HPP */