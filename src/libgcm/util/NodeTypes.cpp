#include "libgcm/util/NodeTypes.hpp"

#include "libgcm/nodes/CalcNode.hpp"
#include "libgcm/nodes/IdealElasticNode.hpp"
#include "libgcm/nodes/IdealElasticWithMicrocracksNode.hpp"

#include "libgcm/util/Exception.hpp"

namespace gcm
{
    CalcNode newNode(uchar nodeType)
    {
        switch (nodeType)
        {
            case IDEAL_ELASTIC_NODE_TYPE:
                return IdealElasticNode();
            case IDEAL_ELASTIC_WITH_MICROCRACKS_NODE_TYPE:
                return IdealElasticWithMicrocracksNode();
            default:
                THROW_UNSUPPORTED("Unknown node type requested: " + nodeType);
        }
    }
}