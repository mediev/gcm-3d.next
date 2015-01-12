#ifndef GCM_NODE_TYPES
#define GCM_NODE_TYPES

#include "libgcm/util/Types.hpp"
#include "libgcm/nodes/CalcNode.hpp"

namespace gcm
{
    // These constants define node types.
    // If you create a new node type - add new constant here and new case in newNode() helper.
    const uchar GENERIC_NODE_TYPE = 0;
    const uchar IDEAL_ELASTIC_NODE_TYPE = 1;
    const uchar IDEAL_ELASTIC_WITH_MICROCRACKS_NODE_TYPE = 2;
    
    CalcNode newNode(uchar nodeType);
}
#endif