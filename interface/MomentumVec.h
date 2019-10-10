#ifndef __MYTREE_MOMENTUMVEC_H__
#define __MYTREE_MOMENTUMVEC_H__

#include "Math/Point3D.h"
#include "Math/GenVector/CoordinateSystemTags.h"
typedef ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double> > Point3D;

#include "Math/PxPyPzE4D.h"
#include "Math/LorentzVector.h"
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > MyLorentzVector;

#endif
