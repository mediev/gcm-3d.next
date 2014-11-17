#include "libgcm/solvers/helpers/CrossPointFinder.hpp"
#include "libgcm/Logging.hpp"

CrossPointFinder::CrossPointFinder() {
    INIT_LOGGER("gcm.CrossPointFinder");
};

CrossPointFinder::~CrossPointFinder()
{
}

void CrossPointFinder::find(const Node& curNode, RheologyMatrixPtr matrix, const gcm::real tau, vector3r& point)
{
	
}

vector3r CrossPointFinder::find(const Node& curNode, RheologyMatrixPtr matrix, const gcm::real tau, int num)
{

}
