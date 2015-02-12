#include "BmnGemStripHit.h"

BmnGemStripHit::BmnGemStripHit() : BmnHit() {
    fModule = -1;
    fELoss  = 0.0;
}

BmnGemStripHit::BmnGemStripHit(Int_t detID, TVector3 pos, TVector3 dpos, Int_t index)
: BmnHit(detID, pos, dpos, index) {
    fModule = -1;
    fELoss = 0.0;
}

BmnGemStripHit::~BmnGemStripHit() {

}

ClassImp(BmnGemStripHit)