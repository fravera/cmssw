#include "FastSimulation/CaloHitMakers/interface/PreshowerHitMaker.h"
#include "FastSimulation/CaloGeometryTools/interface/CaloGeometryHelper.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"

PreshowerHitMaker::PreshowerHitMaker(CaloGeometryHelper * calo,
			       const HepPoint3D& layer1entrance, 
			       const HepVector3D& layer1dir, 
			       const HepPoint3D& layer2entrance, 
			       const HepVector3D& layer2dir):
  CaloHitMaker(calo,DetId::Ecal,EcalPreshower,2),
  psLayer1Entrance_(layer1entrance),
  psLayer1Dir_(layer1dir),
  psLayer2Entrance_(layer2entrance),
  psLayer2Dir_(layer2dir)
{
   // Check if the entrance points are really on the wafers
  // Layer 1 
  int z=(psLayer1Entrance_.z()>0)? 1:-1;
  HepPlane3D plan1(0.,0.,1.,-z*myCalorimeter->preshowerZPosition(1));
  double dummyt;
  psLayer1Entrance_ = intersect(plan1,layer1entrance,layer1entrance+layer1dir,dummyt,false);
  x1=psLayer1Entrance_.x();
  y1=psLayer1Entrance_.y();
  z1=psLayer1Entrance_.z();
  HepVector3D dirx(psLayer1Entrance_.x(),0,psLayer1Entrance_.z());
  HepVector3D diry(0,psLayer1Entrance_.y(),psLayer1Entrance_.z());
  dirx=dirx.unit();
  diry=diry.unit();
  invcostheta1x = 1./fabs(dirx.dot(HepVector3D(0,0,1.)));
  invcostheta1y = 1./fabs(diry.dot(HepVector3D(0,0,1.)));      

  // Layer 2
  z=(psLayer2Entrance_.z()>0) ? 1:-1;
  HepPlane3D plan2(0.,0.,1.,-z*myCalorimeter->preshowerZPosition(2));
  
  psLayer2Entrance_ = intersect(plan2,layer2entrance,layer2entrance+layer2dir,dummyt,false);
  x2=psLayer2Entrance_.x();
  y2=psLayer2Entrance_.y();
  z2=psLayer2Entrance_.z();
  dirx = HepVector3D(psLayer2Entrance_.x(),0,psLayer2Entrance_.z());
  diry = HepVector3D(0,psLayer2Entrance_.y(),psLayer2Entrance_.z());
  dirx=dirx.unit();
  diry=diry.unit();
  invcostheta2x = 1./fabs(dirx.dot(HepVector3D(0,0,1.)));
  invcostheta2y = 1./fabs(diry.dot(HepVector3D(0,0,1.)));

  
}


bool PreshowerHitMaker::addHit(double r,double phi,unsigned layer)
{
  return false;
}
