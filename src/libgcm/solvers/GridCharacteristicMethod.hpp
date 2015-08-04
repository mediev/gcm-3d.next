#ifndef GCM_GRIDCHARACTERISTICMETHOD_HPP
#define GCM_GRIDCHARACTERISTICMETHOD_HPP

#include <string>
#include <iostream>
#include <mpi.h>

#include "libgcm/meshes/Mesh.hpp"
#include "libgcm/Engine.hpp"
#include "libgcm/util/Singleton.hpp"


namespace gcm {
    class GridCharacteristicMethod : public Singleton<GridCharacteristicMethod>
	{
    public:
		void stageX(Mesh* mesh);
    };
}

#endif    /* GCM_GRIDCHARACTERISTICMETHOD_HPP */