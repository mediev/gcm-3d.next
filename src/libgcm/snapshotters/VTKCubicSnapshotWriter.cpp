#include "libgcm/snapshotters/VTKCubicSnapshotWriter.hpp"

#include <vtkStdString.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkPointData.h>

#include "libgcm/meshes/cubic/CubicMesh.hpp"

using namespace gcm;

VTKCubicSnapshotWriter::VTKCubicSnapshotWriter() {
    //INIT_LOGGER("gcm.VTKCubicSnapshotWriter");
    extension = "vts";
    suffix = "";
}

void VTKCubicSnapshotWriter::dumpMeshSpecificData(CubicMesh* mesh, vtkSmartPointer<vtkStructuredGrid>& grid, vtkSmartPointer<vtkPoints>& points) const
{
    for(int i = 0; i < mesh->getNodesNumber(); i++)
    {
        CalcNode& node = mesh->getNodeByLocalIndex(i);
        points->InsertNextPoint( node.coords[0], node.coords[1], node.coords[2] );
    }

    // Specify the dimensions of the grid
    //AABB outline = mesh->getOutline();
    // We suppose that mesh is uniform
    float meshH = mesh->getMinH();
    int meshSize = 1 + (1 + meshH * 0.1) / meshH;
    grid->SetDimensions(meshSize, meshSize, meshSize);
}
