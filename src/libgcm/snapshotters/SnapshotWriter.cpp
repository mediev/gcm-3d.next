#include "libgcm/snapshotters/SnapshotWriter.hpp"
#include "libgcm/Engine.hpp"

using namespace gcm;
using std::string;
using std::to_string;

SnapshotWriter::~SnapshotWriter() {
}

string SnapshotWriter::getFileName(int step, string meshId) const
{
    string filename = Engine::SNAPSHOT_OUTPUT_PATH_PATTERN;

    auto replace = [&filename](string from, string to)
    {
        size_t start_pos = 0;
        while((start_pos = filename.find(from, start_pos)) != string::npos) {
            filename.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    };

    replace("%{RANK}", to_string (MPI::COMM_WORLD.Get_rank()));
    replace("%{STEP}", to_string (step));
    replace("%{MESH}", meshId);
    replace("%{SUFFIX}", suffix);
    replace("%{EXT}", extension);

    return filename;
}

string SnapshotWriter::dump(Mesh* mesh, int step) const
{
	char meshId[9];
	sprintf(meshId, "%06u", mesh->getId());
    return dump(mesh, step, getFileName(step, meshId));
}
