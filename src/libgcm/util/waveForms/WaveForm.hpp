#ifndef _GCM_WaveForm_H
#define _GCM_WaveForm_H 1

#include "libgcm/util/Types.hpp"
#include "libgcm/util/geometricRegions/Region.hpp"

// TODO: discuss interface, it's not that intuitive now

namespace gcm
{
    class WaveForm
    {
    public:
        WaveForm( gcm::real startTime, gcm::real duration );
        virtual ~WaveForm() = 0;
        virtual gcm::real valueNorm( gcm::real time, gcm::vector3r coords, Region& region ) = 0;
        bool isActive( gcm::real time );
    protected:
        gcm::real startTime;
        gcm::real duration;
    };
}

#endif