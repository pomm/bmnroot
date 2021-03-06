// @(#)bmnroot/alignment:$Id$
// Author: Pavel Batyuk <pavel.batyuk@jinr.ru> 2017-03-31

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// BmnGlobalAlignment                                                         //
//                                                                            //
// Alignment of tracking detectors.                                           //
//                                                                            //
// Uses Volker Blobel and Claus Kleinwort Millepede II                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef BMNGLOBALALIGNMENT_H
#define BMNGLOBALALIGNMENT_H 1

#include <fstream>
#include <sstream>
#include <TMath.h>
#include <TCanvas.h>
#include <TNamed.h>
#include <TClonesArray.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>
#include <TGeoManager.h>
#include <TString.h>
#include "FairTask.h"
#include "FairRootManager.h"
#include "FairEventHeader.h"
#include  "BmnGlobalTrack.h"
#include  "BmnMwpcTrack.h"
#include  "BmnMwpcGeometry.h"
#include  "BmnGemTrack.h"
#include  "BmnMwpcHit.h"
#include  "BmnDchHit.h"
#include  "BmnGemStripHit.h"
#include  "BmnSiliconHit.h"
#include  "BmnDchTrack.h"
#include  "BmnMille.h"
#include  "BmnMwpcAlignCorrections.h"
#include  "BmnGemAlignCorrections.h"
#include  "BmnDchAlignCorrections.h"
#include  "BmnSiliconAlignCorrections.h"
#include <BmnSiliconStationSet.h>
#include <BmnGemStripStationSet.h>
#include <UniDbDetectorParameter.h>
#include <UniDbRun.h>
#include <BmnKalmanFilter.h>
#include <BmnFieldMap.h>
#include <BmnNewFieldMap.h>
#include <FairField.h>

using namespace std;
using namespace TMath;

class BmnGlobalAlignment : public FairTask {
public:

    BmnGlobalAlignment(TString);
    virtual ~BmnGlobalAlignment();

    virtual InitStatus Init();

    virtual void Exec(Option_t* opt);

    virtual void Finish();

    void SetDetectors(Bool_t gem, Bool_t mwpc, Bool_t dch, Bool_t vp, Bool_t si) {
        fDetectorSet[0] = gem;
        fDetectorSet[1] = mwpc;
        fDetectorSet[2] = dch;
        fDetectorSet[3] = vp;
        fDetectorSet[4] = si;
    }

    void SetUseRealHitErrors(Bool_t flag) {
        fUseRealHitErrors = flag;
    }

    void SetPreSigma(Double_t presigma) {
        fPreSigma = presigma;
    }

    void SetAccuracy(Double_t accuracy) {
        fAccuracy = accuracy;
    }

    void SetUseRegularization(Bool_t flag) {
        fUseRegularization = flag;
    }

    void SetOutlierDownweighting(Int_t n) {
        fOutlierdownweighting = n;
    }

    void SetDwfractionCut(Double_t fraction) {
        fDwfractioncut = fraction;
    }

    void SetChi2MaxPerNDF(Double_t val) {
        fChi2MaxPerNDF = val;
    }

    void SetMinHitsAccepted(Int_t val) {
        fMinHitsAccepted = val;
    }

    void SetTxMinMax(Double_t min, Double_t max) {
        fTxMin = min;
        fTxMax = max;
    }

    void SetTyMinMax(Double_t min, Double_t max) {
        fTyMin = min;
        fTyMax = max;
    }

    void SetDebug(Bool_t flag) {
        fDebug = flag;
    }

    void SetHugecut(Double_t val) {
        fHugecut = val;
    }

    void SetChisqcut(Double_t val1, Double_t val2) {
        fChisqcut[0] = val1;
        fChisqcut[1] = val2;
    }

    void SetEntriesPerParam(Int_t entries) {
        fEntries = entries;
    }

    void SetGemFixedRun6(Bool_t st0_0, Bool_t st1_0, Bool_t st2_0,
            Bool_t st3_0, Bool_t st3_1, Bool_t st4_0,
            Bool_t st4_1, Bool_t st5_0, Bool_t st5_1) {

        cout << "GEM" << endl;
        const Int_t nModulMax = 2; // To be fixed         
        Bool_t** gems = new Bool_t*[fDetectorGEM->GetNStations()];
        for (Int_t iStat = 0; iStat < fDetectorGEM->GetNStations(); iStat++)
            gems[iStat] = new Bool_t[nModulMax];
        gems[0][0] = st0_0;
        gems[1][0] = st1_0;
        gems[2][0] = st2_0;
        gems[3][0] = st3_0;
        gems[3][1] = st3_1;
        gems[4][0] = st4_0;
        gems[4][1] = st4_1;
        gems[5][0] = st5_0;
        gems[5][1] = st5_1;

        for (Int_t iStat = 0; iStat < fDetectorGEM->GetNStations(); iStat++)
            for (Int_t iMod = 0; iMod < fDetectorGEM->GetGemStation(iStat)->GetNModules(); iMod++)
                if (gems[iStat][iMod])
                    fixedGemElements[iStat][iMod] = kTRUE;

        if (fDebug)
            for (Int_t iStat = 0; iStat < fDetectorGEM->GetNStations(); iStat++)
                for (Int_t iMod = 0; iMod < fDetectorGEM->GetGemStation(iStat)->GetNModules(); iMod++)
                    cout << "Stat = " << iStat << " Mod = " << iMod << " isFixed (true / false) " << fixedGemElements[iStat][iMod] << endl;
    }

    void SetSiFixedRun6(Bool_t st0_0, Bool_t st0_1, Bool_t st0_2, Bool_t st0_3,
            Bool_t st0_4, Bool_t st0_5, Bool_t st0_6, Bool_t st0_7) {
        cout << "SI" << endl;
        const Int_t nModulMax = 8; // FIXME         
        Bool_t** si = new Bool_t*[fDetectorSI->GetNStations()];
        for (Int_t iStat = 0; iStat < fDetectorSI->GetNStations(); iStat++)
            si[iStat] = new Bool_t[nModulMax];
        si[0][0] = st0_0;
        si[0][1] = st0_1;
        si[0][2] = st0_2;
        si[0][3] = st0_3;
        si[0][4] = st0_4;
        si[0][5] = st0_5;
        si[0][6] = st0_6;
        si[0][7] = st0_7;

        for (Int_t iStat = 0; iStat < fDetectorSI->GetNStations(); iStat++)
            for (Int_t iMod = 0; iMod < fDetectorSI->GetSiliconStation(iStat)->GetNModules(); iMod++)
                if (si[iStat][iMod])
                    fixedSiElements[iStat][iMod] = kTRUE;

        if (fDebug)
            for (Int_t iStat = 0; iStat < fDetectorSI->GetNStations(); iStat++)
                for (Int_t iMod = 0; iMod < fDetectorSI->GetSiliconStation(iStat)->GetNModules(); iMod++)
                    cout << "Stat = " << iStat << " Mod = " << iMod << " isFixed (true / false) " << fixedSiElements[iStat][iMod] << endl;
    }

    void SetUseTrackWithMinChi2(Bool_t flag) {
        fUseTrackWithMinChi2 = flag;
    }

    void SetExclusionRangeTx(Double_t min, Double_t max) {
        fIsExcludedTx = kTRUE;
        fTxLeft = min;
        fTxRight = max;
    }

    void SetExclusionRangeTy(Double_t min, Double_t max) {
        fIsExcludedTy = kTRUE;
        fTyLeft = min;
        fTyRight = max;
    }

    void SetRoughPrimaryVertex(TVector3 Vp) {
        fRoughVertex = Vp;
    }

    void SetUsePrimaryVertex(Bool_t flag) {
        fUseVp = flag;
    }

private:
    void CreateDetectorGeometries();
    void PrintToFullFormat(TString, Char_t*);
    const Int_t MakeBinFile();
    void MakeSteerFile();
    void MilleNoFieldRuns(BmnGlobalTrack*, Int_t, Int_t, Char_t*);
    Bool_t MilleFieldRuns(Int_t, Int_t, Char_t*);
    void Pede();
    void ReadPedeOutput(ifstream&);
    void ExtractCorrValues(ifstream&, Double_t*);
    FairTrackParam UseKalman(BmnGemTrack*, Int_t, Int_t);

    static Int_t fCurrentEvent;
    static Int_t trackCounter;
    Bool_t fIsField;
    Int_t fRunId;

    BmnMwpcGeometry* mwpcGeo;
    BmnGemStripStationSet* fDetectorGEM; // GEM-geometry
    BmnSiliconStationSet* fDetectorSI; // SI-geometry

    TClonesArray* fMwpcAlignCorr;
    TClonesArray* fGemAlignCorr;
    TClonesArray* fTofAlignCorr;
    TClonesArray* fDchAlignCorr;
    TClonesArray* fSiAlignCorr;

    TString fBranchMwpcAlignCorr;
    TString fBranchGemAlignCorr;
    TString fBranchTofAlignCorr;
    TString fBranchDchAlignCorr;
    TString fBranchSiAlignCorr;

    Bool_t* fDetectorSet;

    TString fBranchMwpcHits;
    TString fBranchSiHits;
    TString fBranchGemHits;
    TString fBranchTof1Hits;
    TString fBranchDchHits;

    TString fBranchMwpcTracks;
    TString fBranchGemTracks;
    TString fBranchDchTracks;

    TString fBranchGlobalTracks;
    TString fBranchGemResiduals;
    TString fBranchFairEventHeader;

    TClonesArray* fMwpcHits;
    TClonesArray* fSiHits;
    TClonesArray* fGemHits;
    TClonesArray* fTof1Hits;
    TClonesArray* fDchHits;

    TClonesArray* fMwpcTracks;
    TClonesArray* fGemTracks;
    TClonesArray* fDchTracks;

    TClonesArray* fGlobalTracks;
    TClonesArray* fGemResiduals;

    FILE* fin_txt;
    TString fRecoFileName;
    TChain* fChain;

    FairEventHeader* fFairEventHeader;

    Bool_t fUseRealHitErrors; // errors are taken from hit finder algorithm
    Bool_t fUseTrackWithMinChi2; // in case of target select track with minimal value of chi2

    // Restrictions on track params
    Double_t fChi2MaxPerNDF;
    Double_t fMinHitsAccepted;
    Double_t fTxMin;
    Double_t fTxMax;
    Double_t fTyMin;
    Double_t fTyMax;
    // Range to be exluded in case of "beam-target" alignment...
    Bool_t fIsExcludedTx; // do exclusion (true) or not, manipulated by SetExclusionRangeTx
    Bool_t fIsExcludedTy; // do exclusion (true) or not, manipulated by SetExclusionRangeTy
    Double_t fTxLeft;
    Double_t fTxRight;
    Double_t fTyLeft;
    Double_t fTyRight;

    Int_t nSelectedTracks;

    UInt_t fNumOfIterations;
    Double_t fAccuracy;
    Double_t fPreSigma;

    // Millepede params
    Bool_t fUseRegularization; // use regularization or not
    Double_t fHugecut; // cut factor in iteration 0
    Double_t fChisqcut[2]; // cut factor in iterations 1 and 2
    Int_t fEntries; // lower limit on number of entries/parameter
    Int_t fOutlierdownweighting; // number of internal iterations (> 1)
    Double_t fDwfractioncut; // reject all cases with a down-weight fraction >= val

    Int_t fNGL;
    Int_t fNLC;
    Int_t nDetectors;

    vector <Int_t> fFixedStats;
    Bool_t** fixedGemElements;
    Bool_t** fixedSiElements;

    Bool_t fDebug;
    Int_t* Labels; //array containing a fixed param. number for each detector. 
    // GEMs: 1 - 27; MWPC: 28 - 30; DCH: 31 - 33; VERTEX: 34 - 36; SILICON: 37 - 60

    TCanvas* fCanv;

    FairField* fField;
    BmnFieldMap* fMagField;
    BmnKalmanFilter* fKalman;

    Bool_t fUseVp;
    TVector3 fRoughVertex;

    TString fBranchVertex;
    TClonesArray* fVertex;

    ClassDef(BmnGlobalAlignment, 1)
};

#endif
