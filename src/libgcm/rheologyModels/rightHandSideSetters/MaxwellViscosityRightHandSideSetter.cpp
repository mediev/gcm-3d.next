#include "libgcm/rheologyModels/rightHandSideSetters/MaxwellViscosityRightHandSideSetter.hpp"

using namespace gcm;


void MaxwellViscosityRightHandSideSetter::setVector(CalcNode& f, 
                                                    const CalcNode& node) const {
	// TODO - assertion of node type (that node contains sigma_ij)
	f.clear();
	// property of viscosity - relaxation time
	real tau = 1; // TODO - get tau from Material node.getMaterial();
	const IdealElasticNode &node1 = static_cast<const IdealElasticNode&> (node);
	( static_cast<IdealElasticNode&> (f) ).sxx() = - node1.getSxx() / tau;
	( static_cast<IdealElasticNode&> (f) ).sxy() = - node1.getSxy() / tau;
	( static_cast<IdealElasticNode&> (f) ).sxz() = - node1.getSxz() / tau;
	( static_cast<IdealElasticNode&> (f) ).syy() = - node1.getSyy() / tau;
	( static_cast<IdealElasticNode&> (f) ).syz() = - node1.getSyz() / tau;
	( static_cast<IdealElasticNode&> (f) ).szz() = - node1.getSzz() / tau;
}