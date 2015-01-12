#ifndef GCM_IdealElasticRheologyModel_H
#define GCM_IdealElasticRheologyModel_H

#include <string>
#include <vector>

#include "libgcm/util/Logging.hpp"
#include "libgcm/rheologyModels/RheologyModel.hpp"

namespace gcm {

    class IdealElasticRheologyModel : public RheologyModel {
    public:
        IdealElasticRheologyModel();

    private:
        USE_LOGGER;
    };
}

#endif