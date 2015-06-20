#include "libgcm/snapshotters/VTK2SnapshotWriter.hpp"

#include <vtkStdString.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkTetra.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>

#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/nodes/CalcNode.hpp"
#include "libgcm/elements/TetrahedronFirstOrder.hpp"

using namespace gcm;
using std::map;


template <>
MeshNodeIterator<TetrMeshFirstOrder, SNAPSHOTTER_ID_VTK2>& MeshNodeIterator<TetrMeshFirstOrder, SNAPSHOTTER_ID_VTK2>::operator++()
{
    index++;
    if (!hasNext())
        return *this;
    // We should snapshot unused nodes as well
    //if (!mesh->getNodeByLocalIndex(index).isUsed())
    //    return ++(*this);

    return *this;
}


VTK2SnapshotWriter::VTK2SnapshotWriter() {
    INIT_LOGGER("gcm.VTK2SnapshotWriter");
    extension = "vtu";
    suffix = "";
}

void VTK2SnapshotWriter::dumpMeshSpecificData(TetrMeshFirstOrder* mesh, vtkSmartPointer<vtkUnstructuredGrid>& grid, vtkSmartPointer<vtkPoints>& points) const
{
    map<int, int> snapNodeMap;

    int snapNodeCount = 0;

    for(uint i = 0; i < mesh->getNodesNumber(); i++) {
        CalcNode& node = mesh->getNodeByLocalIndex(i);

        snapNodeMap[node.number] = snapNodeCount++;

        points->InsertNextPoint( node.coords[0], node.coords[1], node.coords[2] );
    }

    auto tetr1stOrderNodes = vtkSmartPointer<vtkIntArray>::New ();
    tetr1stOrderNodes->SetNumberOfComponents (4);

    //auto tetr2ndOrderNodes = vtkSmartPointer<vtkIntArray>::New ();
    //tetr2ndOrderNodes->SetNumberOfComponents (6);

    auto tetrNumber = vtkSmartPointer<vtkIntArray>::New ();
    auto tetra=vtkSmartPointer<vtkTetra>::New();

    for(int i = 0; i < mesh->getTetrsNumber(); i++) {
        TetrahedronFirstOrder& tetr = mesh->getTetrByLocalIndex(i);
        bool shouldSnapshotTetr = true;
        /*for( int z = 0; z < 4; z++)
        {
            CalcNode& node = mesh->getNode( tetr.verts[z] );
            if(!node.isUsed())
                shouldSnapshotTetr = false;
        }
        for( int z = 0; z < 6; z++)
        {
            CalcNode& node = mesh->getNode( tetr.addVerts[z] );
            if(!node.isUsed())
                shouldSnapshotTetr = false;
        }
        if( !shouldSnapshotTetr )
            continue;
		*/
        for( int z = 0; z < 4; z++)
        {
            int snapIndex = snapNodeMap[ tetr.vertices[z] ];
            tetra->GetPointIds()->SetId( z, snapIndex );
        }
        grid->InsertNextCell(tetra->GetCellType(),tetra->GetPointIds());

        tetr1stOrderNodes->InsertNextTupleValue ((int*)tetr.vertices);
        //tetr2ndOrderNodes->InsertNextTupleValue (tetr.addVerts);
        tetrNumber->InsertNextValue (tetr.number);
    }


    tetr1stOrderNodes->SetName ("tetr1stOrderNodes");
    grid->GetCellData()->AddArray (tetr1stOrderNodes);

    //tetr2ndOrderNodes->SetName ("tetr2ndOrderNodes");
    //grid->GetCellData ()->AddArray (tetr2ndOrderNodes);

    tetrNumber->SetName ("tetrNumber");
    grid->GetCellData ()->AddArray (tetrNumber);
}
