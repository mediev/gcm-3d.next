#include "libgcm/meshes/tetrahedron/MshTetrFileReader.hpp"

using namespace gcm;
using std::string;
using std::vector;
using std::map;
//using std::numeric_limits;
using std::ifstream;

MshTetrFileReader::MshTetrFileReader()
{
}

MshTetrFileReader::~MshTetrFileReader()
{
}

void MshTetrFileReader::readFile(string file, TetrMeshFirstOrder* mesh)
{
	assert_true(mesh);

	string str;
	int tmp_int;
	real tmp_real;

	int tetrsCount = 0;
	int fileVer;
	int number_of_nodes;
	int number_of_elements;

	// Open *.msh file
	ifstream infile;
	infile.open(file.c_str(), ifstream::in);
	assert_false(infile.is_open());

	infile >> str;
	assert_true( strcmp(str.c_str(), "$MeshFormat") != 0 );

    infile >> tmp_real >> tmp_int >> tmp_int;
    fileVer = (int)(tmp_real * 10.0);

    infile >> str;
    assert_true( strcmp(str.c_str(),"$EndMeshFormat") != 0 );

    infile >> str;
    assert_true( strcmp(str.c_str(),"$Nodes") != 0 );

    infile >> number_of_nodes;

    vector<CalcNode>* nodes = new vector<CalcNode>;
    RheologyModel* rModel = mesh->getRheologyModel();

    vector3r coords;
    for(int i = 0; i < number_of_nodes; i++)
    {
    	infile >> tmp_int;
    	assert_gt(tmp_int, 0);
    	infile >> coords[0] >> coords[1] >> coords[2];
    	CalcNode node = newNode(rModel->getNodeType());
        node.number = tmp_int - 1;
        node.coords = coords;
        //node->setPlacement(true);
        nodes->push_back( node );
    }

    mesh->initValuesInNodes( number_of_nodes );
    for(unsigned int i = 0; i < nodes->size(); i++)
    {
        mesh->addNode( nodes->at(i) );
    }

    nodes->clear();
    delete nodes;

    infile >> str;
    assert_true( strcmp(str.c_str(),"$EndNodes") != 0 );

    infile >> str;
    assert_true( strcmp(str.c_str(),"$Elements") != 0 );

    infile >> number_of_elements;
    vector<TetrahedronFirstOrder*>* tetrs = new vector<TetrahedronFirstOrder*>;

    for(int i = 0; i < number_of_elements; i++)
    {
        uint number;
        infile >> number >> tmp_int;
        if(tmp_int != 4) {
            getline(infile, str);
            continue;
        } else if (tmp_int == 4) {
            tetrsCount++;
            //number = tetrs->size();
            uint vert[4];
            if( fileVer == 22 ) {
                infile >> tmp_int >> tmp_int >> tmp_int
                    >> vert[0] >> vert[1] >> vert[2] >> vert[3];
            } else {
                infile >> tmp_int >> tmp_int >> tmp_int >> tmp_int
                    >> vert[0] >> vert[1] >> vert[2] >> vert[3];
            }

            assert_true( (vert[0] <= 0) || (vert[1] <= 0) || (vert[2] <= 0) || (vert[3] <= 0) );

            vert[0]--; vert[1]--; vert[2]--; vert[3]--;

            if( mesh->hasNode(vert[0])
                    || mesh->hasNode(vert[1])
                    || mesh->hasNode(vert[2])
                    || mesh->hasNode(vert[3]) )
                tetrs->push_back( new TetrahedronFirstOrder( number, vert ) );
        }
    }

    mesh->createTetrs( tetrs->size() );
    for(unsigned int i = 0; i < tetrs->size(); i++)
    {
        TetrahedronFirstOrder& tetr = *tetrs->at(i);
        mesh->addTetr(tetr);
        //for(int j = 0; j < 4; j++)
        //    if( ! mesh->hasNode( tetr->verts[j] ) )
        //        remoteNodes[tetr->verts[j]] = i;
    }
    tetrs->clear();
    delete tetrs;

    infile >> str;
    assert_true(strcmp(str.c_str(),"$EndElements") != 0);

    infile.close();

}
