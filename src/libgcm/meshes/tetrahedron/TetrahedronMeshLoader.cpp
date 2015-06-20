#include "libgcm/meshes/tetrahedron/TetrahedronMeshLoader.hpp"
#include "libgcm/snapshotters/VTK2SnapshotWriter.hpp"

using namespace gcm;
using std::string;
using std::map;
using std::find;

TetrahedronMeshLoader::TetrahedronMeshLoader()
{
}

TetrahedronMeshLoader::~TetrahedronMeshLoader()
{
}

void TetrahedronMeshLoader::cleanUp()
{
    for( map<string, bool>::const_iterator itr = createdFiles.begin(); itr != createdFiles.end(); ++itr )
    {
        //LOG_DEBUG("Deleting generated file: " << getMshFileName(itr->first));
        remove( getMshFileName(itr->first).c_str() );
        //LOG_DEBUG("Deleting generated file: " << getVtkFileName(itr->first));
        //remove( getVtkFileName(itr->first).c_str() );
    }
    createdFiles.clear();
}

bool TetrahedronMeshLoader::isMshFileCreated(string fileName)
{
    return createdFiles.find(fileName) != createdFiles.end();
}

string TetrahedronMeshLoader::getMshFileName(string geoFile)
{
    return geoFile + ".msh";
}

string TetrahedronMeshLoader::getVtkFileName(string geoFile)
{
    return geoFile + ".vtu";
}

void TetrahedronMeshLoader::createMshFile(string fileName, real tetrSize)
{
    /*Engine& engine = Engine::getInstance();

    if( engine.getNumberOfWorkers() > 1 )
    {
        if( engine.getRank() != 0 )
        {
            MPI::COMM_WORLD.Barrier();
            createdFiles[fileName] = true;
            return;
        }
    }*/

    /*
     * TODO@ashevtsov: I don't really understand the meaning of all these options, values
     * have been guessed to get a mesh with acceptable tetrahedra sizes.
     * In future need to undestand GMsh meshing algorithms and set these options correctly.
     */
    //LOG_DEBUG("loadGeoScriptFile (" << fileName << "): will mesh with H = " << tetrSize);

    GmshSetOption("General", "Terminal", 1.0);
    //GmshSetOption("General", "Verbosity", engine.getGmshVerbosity());
    GmshSetOption("Mesh", "CharacteristicLengthMin", tetrSize);
    GmshSetOption("Mesh", "CharacteristicLengthMax", tetrSize);
    GmshSetOption("Mesh", "Optimize", 1.0);

    GModel gmshModel;
    gmshModel.setFactory ("Gmsh");
    gmshModel.readGEO (fileName);

    gmshModel.mesh (3);
    gmshModel.writeMSH (getMshFileName(fileName));
    createdFiles[fileName] = true;

    //if (engine.getNumberOfWorkers() > 1)
    //    MPI::COMM_WORLD.Barrier();
}

void TetrahedronMeshLoader::loadMesh(TetrMeshFirstOrder* mesh, string fileName, real tetrSize)
{
    if (!isMshFileCreated(fileName))
        createMshFile(fileName, tetrSize);

    //IBody* body = mesh->getBody();
    //Engine& engine = Engine::getInstance();
    if( true /*engine.getRank() == 0*/ )
    {
        //LOG_DEBUG("Worker 0 started generating second order mesh from first order msh file");
        //TetrMeshFirstOrder* foMesh = new TetrMeshFirstOrder();
//        foMesh->setBody(body);

        //TetrMeshSecondOrder* soMesh = new TetrMeshSecondOrder();
//        soMesh->setBody(body);

        //int sd, nn;
        //AABB scene;
        //GCMDispatcher* myDispatcher = new DummyDispatcher();
        //preLoadMesh(&scene, sd, nn, fileName, tetrSize);
        //myDispatcher->prepare(1, &scene);

        MshTetrFileReader* reader = new MshTetrFileReader();
        reader->readFile(getMshFileName(fileName), mesh);
        //soMesh->copyMesh(foMesh);
        mesh->preProcess();
        mesh->snapshot(0);
        //VTK2SnapshotWriter* sw = new VTK2SnapshotWriter();
        //sw->dump(mesh, 0);

        delete reader;
        //delete foMesh;
        //delete soMesh;
        //LOG_DEBUG("Worker 0 completed generating second order mesh");
    }

    //MPI::COMM_WORLD.Barrier();

    //LOG_DEBUG("Starting reading mesh");
    //Vtu2TetrFileReader* reader = new Vtu2TetrFileReader();
    //reader->readFile(getVtkFileName(fileName), mesh, dispatcher, engine.getRank());
    //delete reader;

    //mesh->preProcess();
}
