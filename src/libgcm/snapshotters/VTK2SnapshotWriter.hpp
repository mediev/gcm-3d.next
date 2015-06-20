#ifndef VTK2SNAPSHOTWRITER_H_
#define VTK2SNAPSHOTWRITER_H_

#include <string>

#include "libgcm/util/Singleton.hpp"
#include "libgcm/snapshotters/AbstractVTKSnapshotWriter.hpp"

namespace gcm {
    class TetrMeshFirstOrder;

    template <>
    MeshNodeIterator<TetrMeshFirstOrder, SNAPSHOTTER_ID_VTK2>& MeshNodeIterator<TetrMeshFirstOrder, SNAPSHOTTER_ID_VTK2>::operator++();

    class VTK2SnapshotWriter : public UnstructuredVTKSnapshotWriter<TetrMeshFirstOrder, false, SNAPSHOTTER_ID_VTK2>, public Singleton<VTK2SnapshotWriter> {
     protected:
        USE_LOGGER;
        void dumpMeshSpecificData(TetrMeshFirstOrder* mesh, vtkSmartPointer<vtkUnstructuredGrid>& grid, vtkSmartPointer<vtkPoints>& points) const override;
     public:
        VTK2SnapshotWriter();
    };
}


#endif /* VTK2SNAPSHOTWRITER_H_ */
