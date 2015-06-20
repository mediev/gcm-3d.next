#ifndef VTKCUBICSNAPSHOTWRITER_HPP_
#define VTKCUBICSNAPSHOTWRITER_HPP_

#include <string>

#include "libgcm/util/Singleton.hpp"
#include "libgcm/snapshotters/AbstractVTKSnapshotWriter.hpp"
#include "libgcm/nodes/CalcNode.hpp"
#include "libgcm/util/Logging.hpp"

namespace gcm {
    class CubicMesh;

    class VTKCubicSnapshotWriter : public StructuredVTKSnapshotWriter<CubicMesh>, public Singleton<VTKCubicSnapshotWriter> {
    protected:
        USE_LOGGER;
        void dumpMeshSpecificData(CubicMesh* mesh, vtkSmartPointer<vtkStructuredGrid>& grid, vtkSmartPointer<vtkPoints>& points) const override;
    public:
        VTKCubicSnapshotWriter();
    };
}

#endif /* VTKCUBICSNAPSHOTWRITER_HPP_ */
