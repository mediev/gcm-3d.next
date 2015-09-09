#include "libgcm/meshes/tetrahedron/Mesh2GeoLoader.hpp"

using namespace gcm;
using std::string;
using std::vector;
using std::ofstream;
using std::endl;
using std::pair;
using std::make_pair;
using std::map;


Mesh2GeoLoader::Mesh2GeoLoader()
{
}

Mesh2GeoLoader::~Mesh2GeoLoader()
{
}

int Mesh2GeoLoader::getLineNum(int node1, int node2, int ordNum)
{
	line1 = make_pair(node1, node2);
	line2 = make_pair(node2, node1);

	it = lineNums.find(line1);
	if( it == lineNums.end() )
	{
		it = lineNums.find(line2);
		if( it == lineNums.end() )
		{
			lineNums[line1] = ordNum;
			return ordNum;

		} else
			return -it->second;

	} else
		return it->second;
}


void Mesh2GeoLoader::writeGeoFile(string fileName, TetrMeshFirstOrder* mesh)
{
	assert_true(mesh);

	ofstream geo;
	geo.open(fileName.c_str(), ofstream::out);

	geo << "meshPointDist = 0.2;" << endl << endl;

	int ordNum = 1;

	for(int i = 0; i < mesh->getNodesNumber(); i++)
	{
		CalcNode& node = mesh->getNodeByLocalIndex(i);
		geo << "Point(" << ordNum++ << ") = {" << node.coords[0] << ", " \
												<< node.coords[1] << ", " \
												<< node.coords[2] << ", meshPointDist};" << endl;
	}

	map<Line, int>::iterator it1, it2;
	int lineIdx [3];
	int nodeIdx1, nodeIdx2;
	for(int i = 0; i < mesh->getTriangleNumber(); i++)
	{
		TriangleFirstOrder& tri = mesh->getTriangle(i);

		nodeIdx1 = mesh->getNodeLocalIndex(tri.vertices[0]) + 1;
		nodeIdx2 = mesh->getNodeLocalIndex(tri.vertices[1]) + 1;
		lineIdx[0] = getLineNum( nodeIdx1, nodeIdx2, ordNum );
		if(lineIdx[0] == ordNum)
			geo << "Line(" << ordNum++ << ") = {" << nodeIdx1 << ", " \
													<< nodeIdx2 << "};" << endl;

		nodeIdx1 = mesh->getNodeLocalIndex(tri.vertices[1]) + 1;
		nodeIdx2 = mesh->getNodeLocalIndex(tri.vertices[2]) + 1;
		lineIdx[1] = getLineNum( nodeIdx1, nodeIdx2, ordNum );
		if(lineIdx[1] == ordNum)
			geo << "Line(" << ordNum++ << ") = {" << nodeIdx1 << ", " \
													<< nodeIdx2 << "};" << endl;

		nodeIdx1 = mesh->getNodeLocalIndex(tri.vertices[2]) + 1;
		nodeIdx2 = mesh->getNodeLocalIndex(tri.vertices[0]) + 1;
		lineIdx[2] = getLineNum( nodeIdx1, nodeIdx2, ordNum );
		if(lineIdx[2] == ordNum)
			geo << "Line(" << ordNum++ << ") = {" << nodeIdx1 << ", " \
													<< nodeIdx2 << "};" << endl;

		geo << "Line Loop(" << ordNum++ << ") = {" << lineIdx[0] << ", " \
													<< lineIdx[1] << ", " \
													<< lineIdx[2] << "};" << endl;
		geo << "Ruled Surface(" << ordNum++ << ") = {" << ordNum - 1 << "};" << endl;

		surfNums.push_back(ordNum - 1);
	}

	geo << "Surface Loop(" << ordNum++ << ") = {";
	for(int i = 0; i < surfNums.size() - 1; i++)
		geo << surfNums[i] << ", ";
	geo << surfNums[ surfNums.size() - 1 ] << "};" << endl;

	geo << "Volume(" << ordNum << ") = {" << ordNum - 1 << "};" << endl;

	geo.close();
}
