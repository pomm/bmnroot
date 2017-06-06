
#ifndef BMNGEMVERTEXFINDER_H
#define BMNGEMVERTEXFINDER_H

#include "FairTask.h"
#include "TClonesArray.h"
#include "TString.h"
#include "BmnGemTrack.h"
#include "BmnGemStripHit.h"
#include "TMath.h"
#include "TVector3.h"
#include "BmnEnums.h"
#include "FairRunAna.h"
#include "FairField.h"
#include "CbmVertex.h"
#include "BmnKalmanFilter_tmp.h"
#include "BmnGemStripStationSet.h"
#include "BmnGemStripStationSet_RunSpring2017.h"

using namespace std;

class BmnGemVertexFinder : public FairTask {
public:

    // Constructors/Destructors ---------
    BmnGemVertexFinder();
    virtual ~BmnGemVertexFinder();

    virtual InitStatus Init();
    virtual void Exec(Option_t* opt);
    virtual void Finish();

    void SetField(Bool_t f) {
        fIsField = f;
    }
    
    void FindVertexByVirtualPlanes();

private:

    // Private Data Members ------------
    TString fHitsBranchName;
    TString fTracksBranchName;
    TString fVertexBranchName;

    Int_t fEventNo; // event counter
    Int_t fNTracks; // number of reco tracks in event
    
    BmnGemStripStationSet* fDetector;

    TClonesArray* fGemHitsArray;
    TClonesArray* fGemTracksArray;
    TClonesArray* fVertexArray;

    Bool_t fIsField;
    FairField* fField;
    BmnKalmanFilter_tmp* fKalman;

    ClassDef(BmnGemVertexFinder, 1);
};


#endif /* BMNGEMVERTEXFINDER_H */

