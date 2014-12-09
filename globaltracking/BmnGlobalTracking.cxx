/** BmnGlobalTracking.cxx
 * \author Sergey Merts <Sergey.Merts@gmail.com>
 * @since 2014
 * @version 1.0
 **/

#include "BmnGlobalTracking.h"
using namespace TMath;

//some variables for efficiency calculation
static Int_t allFoundCntr = 0;
static Int_t wellFoundCntr = 0;
static Int_t wrongFoundCntr = 0;
static Int_t allHitCntr = 0;
static Int_t goodTrackCntr = 0;
static Int_t allTrackCntr = 0;
static Int_t allMcTrackCntr = 0;
static Float_t workTime = 0.0;
//-----------------------------------------

const Float_t thresh = 0.7; // threshold for efficiency calculation (70%)

BmnGlobalTracking::BmnGlobalTracking() :
fDetConf(31), //31 means that all detectors are presented
fMcTracks(NULL),
fGemTracks(NULL),
fGemHits(NULL),
fTof1Hits(NULL),
fTof2Hits(NULL),
fDch1Hits(NULL),
fDch2Hits(NULL),
fGlobalTracks(NULL),
fGemMcPoints(NULL),
fTof1McPoints(NULL),
fTof2McPoints(NULL),
fDch1McPoints(NULL),
fDch2McPoints(NULL),
fPDG(211),
fChiSqCut(25.),
fEventNo(0),
fIsHistogramsInitialized(kFALSE),
fMakeQA(kTRUE),
fTof1Histo(NULL),
fTof2Histo(NULL),
fDch1Histo(NULL),
fDch2Histo(NULL),
fGlobHisto(NULL) {
    fMerger = new BmnHitToTrackMerger();
    fFinder = new BmnTrackFinder();
    fPropagator = new BmnTrackPropagator();
    fUpdater = new BmnKalmanFilter();
    fFitter = new BmnTrackFitter(fPropagator, fUpdater);
    isRUN1 = kFALSE;
}

BmnGlobalTracking::~BmnGlobalTracking() {
    delete fMerger;
    delete fFitter;
    delete fFinder;
    delete fPropagator;
    delete fGlobHisto;
    delete fUpdater;
}

InitStatus BmnGlobalTracking::Init() {
    cout << "BmnGlobalTracking::Init started\n";

    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        Fatal("Init", "FairRootManager is not instantiated");
    }

    fDet.DetermineSetup();
    cout << fDet.ToString();

    // ----------------- MWPC1 initialization -----------------//
    if (fDet.GetDet(kMWPC1)) {
        fMwpc1Hits = (TClonesArray*) ioman->GetObject("BmnMwpc1Hit");
        if (!fMwpc1Hits) {
            Fatal("Init", "No BmnMwpc1Hit array!");
        }
    } else {
        cout << "\nWARNING! Detector MWPC1 is excluded from global tracking!!!\n" << endl;
    }


    // ----------------- MWPC2 initialization -----------------//
    if (fDet.GetDet(kMWPC2)) {
        fMwpc2Hits = (TClonesArray*) ioman->GetObject("BmnMwpc2Hit");
        if (!fMwpc2Hits) {
            Fatal("Init", "No BmnMwpc2Hit array!");
        }
    } else {
        cout << "\nWARNING! Detector MWPC2 is excluded from global tracking!!!\n" << endl;
    }


    // ----------------- MWPC3 initialization -----------------//
    if (fDet.GetDet(kMWPC3)) {
        fMwpc3Hits = (TClonesArray*) ioman->GetObject("BmnMwpc3Hit");
        if (!fMwpc3Hits) {
            Fatal("Init", "No BmnMwpc3Hit array!");
        }
    } else {
        cout << "\nWARNING! Detector MWPC3 is excluded from global tracking!!!\n" << endl;
    }

    // ----------------- GEM initialization -----------------//
    if (fDet.GetDet(kGEM)) {

        if (isRUN1) {
            fSeeds = (TClonesArray*) ioman->GetObject("BmnSeeds"); //in
        } else {
            fGemTracks = (TClonesArray*) ioman->GetObject("BmnGemTracks");
            if (!fGemTracks) {
                Fatal("Init", "No BmnGemTracks array!");
            }
        }

        fGemHits = (TClonesArray*) ioman->GetObject("BmnGemStripHit");
        if (!fGemHits) {
            Fatal("Init", "No BmnGemStripHit array!");
        }

        fGemMcPoints = (TClonesArray*) ioman->GetObject("StsPoint");
        if (!fGemMcPoints) {
            Fatal("Init", "No StsPoint array!");
        }
    } else {
        cout << "\nERROR!GEM stations are excluded from global tracking!!!\n" << endl;
        Fatal("Init", "No GEM stations!");
    }
    // ------------------------------------------------------//

    // ----------------- TOF1 initialization -----------------//
    if (fDet.GetDet(kTOF1)) {
        fTof1Hits = (TClonesArray*) ioman->GetObject("TOF1Hit");
        if (!fTof1Hits) {
            Fatal("Init", "No BmnTof1Hit array!");
        }

        fTof1McPoints = (TClonesArray*) ioman->GetObject("TOF1Point");
        if (!fTof1McPoints) {
            Fatal("Init", "No TOF1Point array!");
        }
    } else {
        cout << "\nWARNING! Detector TOF1 is excluded from global tracking!!!\n" << endl;
    }
    // ------------------------------------------------------//

    // ----------------- TOF2 initialization -----------------//
    if (fDet.GetDet(kTOF)) {
        fTof2Hits = (TClonesArray*) ioman->GetObject("BmnTof2Hit");
        if (!fTof2Hits) {
            Fatal("Init", "No BmnTof2Hit array!");
        }

        fTof2McPoints = (TClonesArray*) ioman->GetObject("TofPoint");
        if (!fTof2McPoints) {
            Fatal("Init", "No TofPoint array!");
        }
    } else {
        cout << "\nWARNING! Detector TOF2 is excluded from global tracking!!!\n" << endl;
    }
    // ------------------------------------------------------//

    // ----------------- DCH1 initialization -----------------// 
    if (fDet.GetDet(kDCH1)) {
        fDch1Hits = (TClonesArray*) ioman->GetObject("BmnDch1Hit");
        if (!fDch1Hits) {
            Fatal("Init", "No BmnDch1Hit array!");
        }

        fDch1McPoints = (TClonesArray*) ioman->GetObject("DCH1Point");
        if (!fDch1McPoints) {
            Fatal("Init", "No DCH1Point array!");
        }
    } else {
        cout << "\nWARNING! Detector DCH1 is excluded from global tracking!!!\n" << endl;
    }
    // ------------------------------------------------------// 

    // ----------------- DCH2 initialization -----------------// 
    if (fDet.GetDet(kDCH2)) {
        fDch2Hits = (TClonesArray*) ioman->GetObject("BmnDch2Hit");
        if (!fDch2Hits) {
            Fatal("Init", "No BmnDch2Hit array!");
        }

        fDch2McPoints = (TClonesArray*) ioman->GetObject("DCH2Point");
        if (!fDch2McPoints) {
            Fatal("Init", "No DCH2Point array!");
        }
    } else {
        cout << "\nWARNING! Detector DCH2 is excluded from global tracking!!!\n" << endl;
    }
    // ------------------------------------------------------// 

    // Create and register track arrays
    fGlobalTracks = new TClonesArray("BmnGlobalTrack", 100);
    ioman->Register("GlobalTrack", "GLOBAL", fGlobalTracks, kTRUE);

    fMcTracks = (TClonesArray*) ioman->GetObject("MCTrack");
    if (!fMcTracks) {
        Fatal("Init", "No MCTrack array!");
    }
    ioman->Register("MCTrack", "MC", fMcTracks, kTRUE);

    if (!fIsHistogramsInitialized && fMakeQA) {
        fTof1Histo = new BmnHitMatchingQA(TString("TOF1"));
        fTof2Histo = new BmnHitMatchingQA(TString("TOF2"));
        fDch1Histo = new BmnHitMatchingQA(TString("DCH1"));
        fDch2Histo = new BmnHitMatchingQA(TString("DCH2"));
        fGlobHisto = new BmnGlobalTrackingQA();
        fGlobHisto->Initialize();
        fTof1Histo->Initialize();
        fTof2Histo->Initialize();
        fDch1Histo->Initialize();
        fDch2Histo->Initialize();
        fIsHistogramsInitialized = kTRUE;
    }

    cout << "BmnGlobalTracking::Init finished\n";
    return kSUCCESS;
}

void BmnGlobalTracking::Exec(Option_t* opt) {

    cout << "\n======================== Global tracking exec started =====================\n" << endl;
    cout << " Event number: " << fEventNo++ << endl;

    clock_t tStart = clock();
    fGlobalTracks->Clear();

    if (isRUN1) Run1GlobalTrackFinder();

    if (isRUN1) {
        for (Int_t i = 0; i < fSeeds->GetEntriesFast(); ++i) {
            BmnGemTrack* seed = (BmnGemTrack*) fSeeds->At(i);
            new((*fGlobalTracks)[i]) BmnGlobalTrack();
            BmnGlobalTrack* glTr = (BmnGlobalTrack*) fGlobalTracks->At(i);
            glTr->SetParamFirst(seed->GetParamFirst());
            glTr->SetParamLast(seed->GetParamLast());
            glTr->SetGemTrackIndex(i);
            glTr->SetNofHits(seed->GetNHits());
            glTr->SetRefId(seed->GetRef());
            //glTr->SetFlag(kBMNGOOD); //kBMNGOOD or kBMNGOODMERGE???

            //            if (NearestHitMergeGEM(glTr) == kBMNSUCCESS) {
            //                /*Refit(glTr);*/            }
            if (NearestHitMergeTOF(glTr, 1) == kBMNSUCCESS) {
                /*Refit(glTr);*/            }
            if (NearestHitMergeDCH(glTr, 1) == kBMNSUCCESS) {
                /*Refit(glTr);*/            }
            if (NearestHitMergeDCH(glTr, 2) == kBMNSUCCESS) {
                /*Refit(glTr);*/            }
            if (NearestHitMergeTOF(glTr, 2) == kBMNSUCCESS) {
                /*Refit(glTr);*/            }
            if (Refit(glTr) == kBMNERROR)
                glTr->SetFlag(kBMNBAD);
            else
                glTr->SetFlag(kBMNGOOD);
        }
    } else {
        for (Int_t i = 0; i < fGemTracks->GetEntriesFast(); ++i) {
            BmnGemTrack* gemTrack = (BmnGemTrack*) fGemTracks->At(i);
            new((*fGlobalTracks)[i]) BmnGlobalTrack();
            BmnGlobalTrack* glTr = (BmnGlobalTrack*) fGlobalTracks->At(i);
            glTr->SetParamFirst(gemTrack->GetParamFirst());
            glTr->SetParamLast(gemTrack->GetParamLast());
            glTr->SetGemTrackIndex(i);
            glTr->SetNofHits(gemTrack->GetNHits());
            glTr->SetRefId(gemTrack->GetRef());
            //glTr->SetFlag(kBMNGOOD); //kBMNGOOD or kBMNGOODMERGE???

            if (NearestHitMergeTOF(glTr, 1) == kBMNSUCCESS) {
                /*Refit(glTr);*/            }
            if (NearestHitMergeDCH(glTr, 1) == kBMNSUCCESS) {
                /*Refit(glTr);*/            }
            if (NearestHitMergeDCH(glTr, 2) == kBMNSUCCESS) {
                /*Refit(glTr);*/            }
            if (NearestHitMergeTOF(glTr, 2) == kBMNSUCCESS) {
                /*Refit(glTr);*/            }
            if (Refit(glTr) == kBMNERROR)
                glTr->SetFlag(kBMNBAD);
            else
                glTr->SetFlag(kBMNGOOD);
        }
    }
    CalculateLength();
    clock_t tFinish = clock();

    workTime += ((Float_t) (tFinish - tStart)) / CLOCKS_PER_SEC;

    //    EfficiencyCalculation();

    if (fMakeQA) {
        for (Int_t i = 0; i < fGlobalTracks->GetEntriesFast(); ++i) {
            BmnGlobalTrack* globalTrack = (BmnGlobalTrack*) fGlobalTracks->At(i);
            if (globalTrack->GetFlag() == kBMNBAD) continue;
            BmnGemTrack* gemTr = (BmnGemTrack*) fGemTracks->At(globalTrack->GetGemTrackIndex());
            Int_t numHitsInTrack = gemTr->GetNHits();
            Int_t nodeIdx = 0;
            for (Int_t idx = 0; idx < gemTr->GetNHits(); ++idx) {
                BmnHit* hit = (BmnHit*) fGemHits->At(gemTr->GetHitIndex(idx));
                if (!hit) continue;
                FillGlobHistoQA(globalTrack, nodeIdx, TVector3(hit->GetX(), hit->GetY(), hit->GetZ()));
                nodeIdx++;
            }
            if (fDet.GetDet(kTOF1)) {
                if (globalTrack->GetTof1HitIndex() != -1) {
                    CbmHit* hit = (CbmHit*) fTof1Hits->At(globalTrack->GetTof1HitIndex());
                    if (!hit) continue;
                    FillGlobHistoQA(globalTrack, nodeIdx, TVector3(hit->GetX(), hit->GetY(), hit->GetZ()));
                    FillMatchHistoQA(globalTrack, nodeIdx, TVector3(hit->GetX(), hit->GetY(), hit->GetZ()), fTof1Histo);
                    numHitsInTrack++;
                    nodeIdx++;
                }
            }

            if (fDet.GetDet(kDCH1)) {
                if (globalTrack->GetDch1HitIndex() != -1) {
                    BmnHit* hit = (BmnHit*) fDch1Hits->At(globalTrack->GetDch1HitIndex());
                    if (!hit) continue;
                    FillGlobHistoQA(globalTrack, nodeIdx, TVector3(hit->GetX(), hit->GetY(), hit->GetZ()));
                    FillMatchHistoQA(globalTrack, nodeIdx, TVector3(hit->GetX(), hit->GetY(), hit->GetZ()), fDch1Histo);
                    numHitsInTrack++;
                    nodeIdx++;
                }
            }

            if (fDet.GetDet(kDCH2)) {
                if (globalTrack->GetDch2HitIndex() != -1) {
                    BmnHit* hit = (BmnHit*) fDch2Hits->At(globalTrack->GetDch2HitIndex());
                    if (!hit) continue;
                    FillGlobHistoQA(globalTrack, nodeIdx, TVector3(hit->GetX(), hit->GetY(), hit->GetZ()));
                    FillMatchHistoQA(globalTrack, nodeIdx, TVector3(hit->GetX(), hit->GetY(), hit->GetZ()), fDch2Histo);
                    numHitsInTrack++;
                    nodeIdx++;
                }
            }

            if (fDet.GetDet(kTOF)) {
                if (globalTrack->GetTof2HitIndex() != -1) {
                    CbmHit* hit = (CbmHit*) fTof2Hits->At(globalTrack->GetTof2HitIndex());
                    if (!hit) continue;
                    FillGlobHistoQA(globalTrack, nodeIdx, TVector3(hit->GetX(), hit->GetY(), hit->GetZ()));
                    FillMatchHistoQA(globalTrack, nodeIdx, TVector3(hit->GetX(), hit->GetY(), hit->GetZ()), fTof2Histo);
                    numHitsInTrack++;
                    nodeIdx++;
                }
            }

            fGlobHisto->_hNumOfHitsDistr->Fill(numHitsInTrack);
            TVector3 mom;
            globalTrack->GetParamLast()->Momentum(mom);
            fGlobHisto->_hMomentumDistr->Fill(mom.Mag());
            fGlobHisto->_hPx->Fill(mom.X());
            fGlobHisto->_hPy->Fill(mom.Y());
            fGlobHisto->_hPz->Fill(mom.Z());
            fGlobHisto->_hPt->Fill(Sqrt(mom.X() * mom.X() + mom.Z() * mom.Z()));
        }
    }
    cout << "GLOBAL_TRACKING: Number of merged tracks: " << fGlobalTracks->GetEntriesFast() << endl;

    cout << "\n======================= Global tracking exec finished =====================\n" << endl;
}

BmnStatus BmnGlobalTracking::NearestHitMergeGEM(BmnGlobalTrack* tr) {

    if (!fDet.GetDet(kDCH1)) return kBMNERROR;

    // First find hit with minimum Z position and build map from Z hit position
    // to track parameter to improve the calculation speed.

    Double_t zMin = 10e10;
    map<Float_t, FairTrackParam> zParamMap;

    for (Int_t hitIdx = 0; hitIdx < fGemHits->GetEntriesFast(); ++hitIdx) {
        const BmnHit* hit = (BmnHit*) fGemHits->At(hitIdx);
        if (hit->IsUsed()) continue;
        zMin = min(zMin, hit->GetZ());
        zParamMap[hit->GetZ()] = FairTrackParam();
    }

    //    tr->SetFlag(kBMNGOOD); //FIXME: check it
    FairTrackParam par(*(tr->GetParamLast()));
    // Extrapolate track minimum Z position of hit using magnetic field propagator
    if (fPropagator->TGeoTrackPropagate(&par, zMin, fPDG, NULL, NULL, "field") == kBMNERROR) {
        return kBMNERROR;
    }
    // Extrapolate track parameters to each Z position in the map.
    // This is done to improve calculation speed.
    // In case of planar TOF geometry only 1 track extrapolation is required,
    // since all hits located at the same Z.
    for (map<Float_t, FairTrackParam>::iterator it = zParamMap.begin(); it != zParamMap.end(); it++) {
        (*it).second = par;
        fPropagator->TGeoTrackPropagate(&(*it).second, (*it).first, fPDG, NULL, NULL, "field");
    }

    // Loop over hits
    Float_t minChiSq = 10e10; // minimum chi-square of hit
    BmnHit* minHit = NULL; // Pointer to hit with minimum chi-square
    Float_t minDist = 10e6;
    Int_t minIdx = 0;
    Float_t dist = 0.0;
    FairTrackParam minPar; // Track parameters for closest hit
    for (Int_t hitIdx = 0; hitIdx < fGemHits->GetEntriesFast(); ++hitIdx) {
        BmnHit* hit = (BmnHit*) fGemHits->At(hitIdx);
        if (hit->IsUsed()) continue;
        if (zParamMap.find(hit->GetZ()) == zParamMap.end()) { // This should never happen
            cout << "GEM_MATCHING: NearestHitMerge: Z position " << hit->GetZ() << " not found in map. Something is wrong.\n";
        }
        FairTrackParam tpar(zParamMap[hit->GetZ()]);
        Float_t chi = 0.0;
        fUpdater->Update(&tpar, hit, chi); //update by KF
        dist = Sqrt((tpar.GetX() - hit->GetX()) * (tpar.GetX() - hit->GetX()) + (tpar.GetY() - hit->GetY()) * (tpar.GetY() - hit->GetY()));

        if (chi < fChiSqCut && chi < minChiSq) { // Check if hit is inside validation gate and closer to the track.
            minDist = dist;
            minChiSq = chi;
            minHit = hit;
            minPar = tpar;
            minIdx = hitIdx;
        }
    }

    if (minHit != NULL) { // Check if hit was added
        tr->SetParamLast(&minPar);
        tr->SetChi2(tr->GetChi2() + minChiSq);
        minHit->SetUsing(kTRUE);
        tr->SetGemTrackIndex(minIdx);
        tr->SetNofHits(tr->GetNofHits() + 1);
        return kBMNSUCCESS;
    } else {
        return kBMNERROR;
    }

}

BmnStatus BmnGlobalTracking::NearestHitMergeTOF(BmnGlobalTrack* tr, Int_t num) {

    TClonesArray* tofHits = (num == 1) ? fTof1Hits : fTof2Hits;
    if ((num == 1) && (!fDet.GetDet(kTOF1))) return kBMNERROR;
    if ((num == 2) && (!fDet.GetDet(kTOF))) return kBMNERROR;

    // First find hit with minimum Z position and build map from Z hit position
    // to track parameter to improve the calculation speed.

    Double_t zMin = 10e10;
    map<Float_t, FairTrackParam> zParamMap;

    for (Int_t hitIdx = 0; hitIdx < tofHits->GetEntriesFast(); ++hitIdx) {
        const BmnHit* hit = (BmnHit*) tofHits->At(hitIdx);
        if (hit->GetFlag() == kBMNTOFGOOD) continue;
        zMin = min(zMin, hit->GetZ());
        zParamMap[hit->GetZ()] = FairTrackParam();
    }

    //    tr->SetFlag(kBMNGOOD); //FIXME: check it
    FairTrackParam par(*(tr->GetParamLast()));
    // Extrapolate track minimum Z position of hit using magnetic field propagator
    if (fPropagator->TGeoTrackPropagate(&par, zMin, fPDG, NULL, NULL, "field") == kBMNERROR) {
        return kBMNERROR;
    }
    // Extrapolate track parameters to each Z position in the map.
    // This is done to improve calculation speed.
    // In case of planar TOF geometry only 1 track extrapolation is required,
    // since all hits located at the same Z.
    for (map<Float_t, FairTrackParam>::iterator it = zParamMap.begin(); it != zParamMap.end(); it++) {
        (*it).second = par;
        fPropagator->TGeoTrackPropagate(&(*it).second, (*it).first, fPDG, NULL, NULL, "field");
    }

    // Loop over hits
    Float_t minChiSq = 10e10; // minimum chi-square of hit
    BmnHit* minHit = NULL; // Pointer to hit with minimum chi-square
    Float_t minDist = 10e6;
    Int_t minIdx = 0;
    Float_t dist = 0.0;
    FairTrackParam minPar; // Track parameters for closest hit
    for (Int_t hitIdx = 0; hitIdx < tofHits->GetEntriesFast(); ++hitIdx) {
        BmnHit* hit = (BmnHit*) tofHits->At(hitIdx);
        if (hit->GetFlag() == kBMNTOFGOOD) continue;
        if (zParamMap.find(hit->GetZ()) == zParamMap.end()) { // This should never happen
            cout << "TOF_MATCHING: NearestHitMerge: Z position " << hit->GetZ() << " not found in map. Something is wrong.\n";
        }
        FairTrackParam tpar(zParamMap[hit->GetZ()]);
        Float_t chi = 0.0;
        fUpdater->Update(&tpar, hit, chi); //update by KF
        dist = Sqrt((tpar.GetX() - hit->GetX()) * (tpar.GetX() - hit->GetX()) + (tpar.GetY() - hit->GetY()) * (tpar.GetY() - hit->GetY()));

        if (chi < fChiSqCut && chi < minChiSq) { // Check if hit is inside validation gate and closer to the track.
            minDist = dist;
            minChiSq = chi;
            minHit = hit;
            minPar = tpar;
            minIdx = hitIdx;
        }
    }

    if (minHit != NULL) { // Check if hit was added
        tr->SetParamLast(&minPar);
        tr->SetChi2(tr->GetChi2() + minChiSq);
        minHit->SetFlag(kBMNTOFGOOD);
        if (num == 1)
            tr->SetTof1HitIndex(minIdx);
        else
            tr->SetTof2HitIndex(minIdx);
        tr->SetNofHits(tr->GetNofHits() + 1);
        return kBMNSUCCESS;
    } else {
        return kBMNERROR;
    }
}

BmnStatus BmnGlobalTracking::NearestHitMergeDCH(BmnGlobalTrack* tr, Int_t num) {

    TClonesArray* dchHits = (num == 1) ? fDch1Hits : fDch2Hits;
    if ((num == 1) && (!fDet.GetDet(kDCH1))) return kBMNERROR;
    if ((num == 2) && (!fDet.GetDet(kDCH2))) return kBMNERROR;

    // First find hit with minimum Z position and build map from Z hit position
    // to track parameter to improve the calculation speed.

    Double_t zMin = 10e10;
    map<Float_t, FairTrackParam> zParamMap;

    for (Int_t hitIdx = 0; hitIdx < dchHits->GetEntriesFast(); ++hitIdx) {
        const BmnHit* hit = (BmnHit*) dchHits->At(hitIdx);
        if (hit->IsUsed()) continue;
        zMin = min(zMin, hit->GetZ());
        zParamMap[hit->GetZ()] = FairTrackParam();
    }

    //    tr->SetFlag(kBMNGOOD); //FIXME: check it
    FairTrackParam par(*(tr->GetParamLast()));
    // Extrapolate track minimum Z position of hit using magnetic field propagator
    if (fPropagator->TGeoTrackPropagate(&par, zMin, fPDG, NULL, NULL, "field") == kBMNERROR) {
        return kBMNERROR;
    }
    // Extrapolate track parameters to each Z position in the map.
    // This is done to improve calculation speed.
    // In case of planar TOF geometry only 1 track extrapolation is required,
    // since all hits located at the same Z.
    for (map<Float_t, FairTrackParam>::iterator it = zParamMap.begin(); it != zParamMap.end(); it++) {
        (*it).second = par;
        fPropagator->TGeoTrackPropagate(&(*it).second, (*it).first, fPDG, NULL, NULL, "field");
    }

    // Loop over hits
    Float_t minChiSq = 10e10; // minimum chi-square of hit
    BmnHit* minHit = NULL; // Pointer to hit with minimum chi-square
    Float_t minDist = 10e6;
    Int_t minIdx = 0;
    Float_t dist = 0.0;
    FairTrackParam minPar; // Track parameters for closest hit
    for (Int_t hitIdx = 0; hitIdx < dchHits->GetEntriesFast(); ++hitIdx) {
        BmnHit* hit = (BmnHit*) dchHits->At(hitIdx);
        if (hit->IsUsed()) continue;
        if (zParamMap.find(hit->GetZ()) == zParamMap.end()) { // This should never happen
            cout << "DCH_MATCHING: NearestHitMerge: Z position " << hit->GetZ() << " not found in map. Something is wrong.\n";
        }
        FairTrackParam tpar(zParamMap[hit->GetZ()]);
        Float_t chi = 0.0;
        fUpdater->Update(&tpar, hit, chi); //update by KF
        dist = Sqrt((tpar.GetX() - hit->GetX()) * (tpar.GetX() - hit->GetX()) + (tpar.GetY() - hit->GetY()) * (tpar.GetY() - hit->GetY()));

        if (chi < fChiSqCut && chi < minChiSq) { // Check if hit is inside validation gate and closer to the track.
            minDist = dist;
            minChiSq = chi;
            minHit = hit;
            minPar = tpar;
            minIdx = hitIdx;
        }
    }

    if (minHit != NULL) { // Check if hit was added
        tr->SetParamLast(&minPar);
        tr->SetChi2(tr->GetChi2() + minChiSq);
        minHit->SetUsing(kTRUE);
        if (num == 1)
            tr->SetDch1HitIndex(minIdx);
        else
            tr->SetDch2HitIndex(minIdx);
        tr->SetNofHits(tr->GetNofHits() + 1);
        return kBMNSUCCESS;
    } else {
        return kBMNERROR;
    }

}

BmnStatus BmnGlobalTracking::Refit(BmnGlobalTrack* tr) {

    vector<BmnFitNode> nodes(tr->GetNofHits());
    Int_t nodeIdx = tr->GetNofHits() - 1;
    FairTrackParam par = *(tr->GetParamLast());
    //    FairTrackParam par = *(tr->GetParamFirst());

    //TOF2 part
    if (fDet.GetDet(kTOF)) {
        if (tr->GetTof2HitIndex() != -1) {
            BmnHit* tof2Hit = (BmnHit*) fTof2Hits->At(tr->GetTof2HitIndex());
            Float_t Ze = tof2Hit->GetZ();
            Float_t length = 0;
            vector<Double_t> F(25);
            if (fPropagator->TGeoTrackPropagate(&par, Ze, 211/*glTr->GetPDG()*/, &F, &length, TString("field")) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "PROP ERROR: hit number = " << nodeIdx << " Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }

            nodes[nodeIdx].SetPredictedParam(&par);
            nodes[nodeIdx].SetF(F);
            Float_t chi2Hit = 0.;
            if (fUpdater->Update(&par, tof2Hit, chi2Hit) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "UPD ERROR: Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }
            tr->SetParamLast(&par);

            nodes[nodeIdx].SetUpdatedParam(&par);
            nodes[nodeIdx].SetChiSqFiltered(chi2Hit);
            tr->SetChi2(tr->GetChi2() + chi2Hit);
            tr->SetLength(tr->GetLength() + length);
            nodeIdx--;
        }
    }

    //DCH2 part
    if (fDet.GetDet(kDCH2)) {
        if (tr->GetDch2HitIndex() != -1) {
            BmnHit* dch2Hit = (BmnHit*) fDch2Hits->At(tr->GetDch2HitIndex());
            Float_t Ze = dch2Hit->GetZ();
            Float_t length = 0;
            vector<Double_t> F(25);
            if (fPropagator->TGeoTrackPropagate(&par, Ze, 211/*glTr->GetPDG()*/, &F, &length, TString("field")) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "PROP ERROR: hit number = " << nodeIdx << " Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }

            nodes[nodeIdx].SetPredictedParam(&par);
            nodes[nodeIdx].SetF(F);
            Float_t chi2Hit = 0.;
            if (fUpdater->Update(&par, dch2Hit, chi2Hit) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "UPD ERROR: Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }
            tr->SetParamLast(&par);

            nodes[nodeIdx].SetUpdatedParam(&par);
            nodes[nodeIdx].SetChiSqFiltered(chi2Hit);
            tr->SetChi2(tr->GetChi2() + chi2Hit);
            tr->SetLength(tr->GetLength() + length);
            nodeIdx--;
        }
    }

    //DCH1 part
    if (fDet.GetDet(kDCH1)) {
        if (tr->GetDch1HitIndex() != -1) {
            BmnHit* dch1Hit = (BmnHit*) fDch1Hits->At(tr->GetDch1HitIndex());
            Float_t Ze = dch1Hit->GetZ();
            Float_t length = 0;
            vector<Double_t> F(25);
            if (fPropagator->TGeoTrackPropagate(&par, Ze, 211/*glTr->GetPDG()*/, &F, &length, TString("field")) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "PROP ERROR: hit number = " << nodeIdx << " Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }

            nodes[nodeIdx].SetPredictedParam(&par);
            nodes[nodeIdx].SetF(F);
            Float_t chi2Hit = 0.;
            if (fUpdater->Update(&par, dch1Hit, chi2Hit) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "UPD ERROR: Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }
            tr->SetParamLast(&par);

            nodes[nodeIdx].SetUpdatedParam(&par);
            nodes[nodeIdx].SetChiSqFiltered(chi2Hit);
            tr->SetChi2(tr->GetChi2() + chi2Hit);
            tr->SetLength(tr->GetLength() + length);
            nodeIdx--;
        }
    }

    //TOF1 part
    if (fDet.GetDet(kTOF1)) {
        if (tr->GetTof1HitIndex() != -1) {
            BmnHit* tof1Hit = (BmnHit*) fTof1Hits->At(tr->GetTof1HitIndex());
            Float_t Ze = tof1Hit->GetZ();
            Float_t length = 0;
            vector<Double_t> F(25);
            if (fPropagator->TGeoTrackPropagate(&par, Ze, 211/*glTr->GetPDG()*/, &F, &length, TString("field")) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "PROP ERROR: hit number = " << nodeIdx << " Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }

            nodes[nodeIdx].SetPredictedParam(&par);
            nodes[nodeIdx].SetF(F);
            Float_t chi2Hit = 0.;
            if (fUpdater->Update(&par, tof1Hit, chi2Hit) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "UPD ERROR: Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }
            tr->SetParamLast(&par);

            nodes[nodeIdx].SetUpdatedParam(&par);
            nodes[nodeIdx].SetChiSqFiltered(chi2Hit);
            tr->SetChi2(tr->GetChi2() + chi2Hit);
            tr->SetLength(tr->GetLength() + length);
            nodeIdx--;
        }
    }

    if (!isRUN1) {
        //GEM part
        if (tr->GetGemTrackIndex() != -1) {
            BmnHit* hit = (BmnHit*) fGemHits->At(tr->GetGemTrackIndex());
            Float_t Ze = hit->GetZ();
            Float_t length = 0;
            vector<Double_t> F(25);
            if (fPropagator->TGeoTrackPropagate(&par, Ze, 211/*glTr->GetPDG()*/, &F, &length, TString("field")) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "PROP ERROR: hit number = " << nodeIdx << " Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }

            nodes[nodeIdx].SetPredictedParam(&par);
            nodes[nodeIdx].SetF(F);
            Float_t chi2Hit = 0.;
            if (fUpdater->Update(&par, hit, chi2Hit) == kBMNERROR) {
                tr->SetFlag(kBMNBAD);
                cout << "UPD ERROR: Ze = " << Ze << " length = " << length << " \npar = ";
                par.Print();
                return kBMNERROR;
            }
            tr->SetParamFirst(&par);

            nodes[nodeIdx].SetUpdatedParam(&par);
            nodes[nodeIdx].SetChiSqFiltered(chi2Hit);
            tr->SetChi2(tr->GetChi2() + chi2Hit);
            tr->SetLength(tr->GetLength() + length);
            nodeIdx--;
        }
    }

    tr->SetFitNodes(nodes);
    return kBMNSUCCESS;
}

//BmnStatus BmnGlobalTracking::EfficiencyCalculation() {
//
//    for (Int_t i = 0; i < fGlobalTracks->GetEntriesFast(); ++i) {
//        map<Int_t, Int_t> indexes; //pairs of trackId and number of hits corresponded this trackId
//        BmnGlobalTrack* glTrack = (BmnGlobalTrack*) fGlobalTracks->At(i);
//        BmnGemTrack* gemTrack = (BmnGemTrack*) fGemTracks->At(i);
//        Int_t trId = gemTrack->GetRef(); //id of GEM track (id of 70% hits in GEM track)
//
//        for (Int_t j = 0; j < gemTrack->GetNHits(); ++j) { //loop over hits from the second to the last. Needed for comparing id of hits
//            BmnHit* curHit = (BmnHit*) fGemHits->At(gemTrack->GetHitIndex(j));
//            if (!curHit) continue;
//            Int_t id = ((CbmStsPoint*) fGemMcPoints->At(curHit->GetRefIndex()))->GetTrackID();
//            FillIndexMap(indexes, id);
//            if (trId == id) {
//                wellFoundCntr++;
//            } else {
//                wrongFoundCntr++;
//            }
//        }
//        if (fDet.GetDet(kTOF1)) {
//            if (glTrack->GetTof1HitIndex() != -1) {
//                BmnHit* tofHit = (BmnHit*) fTof1Hits->At(glTrack->GetTof1HitIndex());
//                if (!tofHit) continue;
//                Int_t id = ((CbmTofPoint*) fTof1McPoints->At(tofHit->GetRefId()))->GetTrackID();
//                FillIndexMap(indexes, id);
//                IdChecker(trId, id, TVector3(tofHit->GetX(), tofHit->GetY(), tofHit->GetZ()), fTof1Histo);
//                allFoundCntr++;
//            }
//        }
//        if (fDet.GetDet(kDCH1)) {
//            if (glTrack->GetDch1HitIndex() != -1) {
//                BmnHit* dchHit = (BmnHit*) fDch1Hits->At(glTrack->GetDch1HitIndex());
//                if (!dchHit) continue;
//                Int_t id = ((FairMCPoint*) fDch1McPoints->At(dchHit->GetRefIndex()))->GetTrackID();
//                FillIndexMap(indexes, id);
//                IdChecker(trId, id, TVector3(dchHit->GetX(), dchHit->GetY(), dchHit->GetZ()), fDch1Histo);
//                allFoundCntr++;
//            }
//        }
//        if (fDet.GetDet(kDCH2)) {
//            if (glTrack->GetDch2HitIndex() != -1) {
//                BmnHit* dchHit = (BmnHit*) fDch2Hits->At(glTrack->GetDch2HitIndex());
//                if (!dchHit) continue;
//                Int_t id = ((FairMCPoint*) fDch2McPoints->At(dchHit->GetRefIndex()))->GetTrackID();
//                FillIndexMap(indexes, id);
//                IdChecker(trId, id, TVector3(dchHit->GetX(), dchHit->GetY(), dchHit->GetZ()), fDch2Histo);
//                allFoundCntr++;
//            }
//        }
//        if (fDet.GetDet(kTOF)) {
//            if (glTrack->GetTof2HitIndex() != -1) {
//                BmnHit* tofHit = (BmnHit*) fTof2Hits->At(glTrack->GetTof2HitIndex());
//                if (!tofHit) continue;
//                Int_t id = ((CbmTofPoint*) fTof2McPoints->At(tofHit->GetRefId()))->GetTrackID();
//                FillIndexMap(indexes, id);
//                IdChecker(trId, id, TVector3(tofHit->GetX(), tofHit->GetY(), tofHit->GetZ()), fTof2Histo);
//                allFoundCntr++;
//            }
//        }
//
//        Int_t maxNumOfHits = -1;
//        Int_t maxId = -1;
//        for (map<Int_t, Int_t>::iterator it = indexes.begin(); it != indexes.end(); it++) {
//            if ((*it).second > glTrack->GetNofHits() * thresh) goodTrackCntr++;
//            if ((*it).second > maxNumOfHits) {
//                maxNumOfHits = (*it).second;
//                maxId = (*it).first;
//            }
//        }
//
//        glTrack->SetRefId(maxId);
//        if (fMakeQA) {
//            fGlobHisto->_hNumMcTrack->Fill(indexes.size());
//        }
//        allFoundCntr += gemTrack->GetNHits();
//    }
//
//    for (Int_t i = 0; i < fMcTracks->GetEntriesFast(); ++i) {
//        //Only primaries added now
//        //FIXME! Use flag!
//
//        //if (((CbmMCTrack*) fMcTracks->At(i))->GetMotherId() != -1) continue;
//        //if (((CbmMCTrack*) fMcTracks->At(i))->GetP() < 0.5) continue; 
//        allMcTrackCntr++;
//    }
//
//
//    allTrackCntr += fGemTracks->GetEntriesFast();
//    allHitCntr += fGemHits->GetEntriesFast();
//    if (fDet.GetDet(kTOF1)) allHitCntr += fTof1Hits->GetEntriesFast();
//    if (fDet.GetDet(kDCH1)) allHitCntr += fDch1Hits->GetEntriesFast();
//    if (fDet.GetDet(kDCH2)) allHitCntr += fDch2Hits->GetEntriesFast();
//    if (fDet.GetDet(kTOF)) allHitCntr += fTof2Hits->GetEntriesFast();
//}

void BmnGlobalTracking::FillIndexMap(map<Int_t, Int_t> &indexes, Int_t id) {
    if (indexes.find(id) == indexes.end()) indexes.insert(pair<Int_t, Int_t > (id, 1));
    else (indexes.find(id)->second)++;
}

void BmnGlobalTracking::IdChecker(Int_t refId, Int_t hitId, TVector3 pos, BmnHitMatchingQA* hist) {
    if (refId == hitId) {
        hist->_hX_well_matched_hits->Fill(pos.X());
        hist->_hY_well_matched_hits->Fill(pos.Y());
        hist->_hZ_well_matched_hits->Fill(pos.Z());
        hist->_hXY_well_matched_hits->Fill(pos.X(), pos.Y());
        hist->_hZX_well_matched_hits->Fill(pos.Z(), pos.X());
        hist->_hZY_well_matched_hits->Fill(pos.Z(), pos.Y());
        hist->_hZXY_well_matched_hits->Fill(pos.Y(), pos.X(), pos.Y());
        wellFoundCntr++;
    } else {
        hist->_hX_wrong_matched_hits->Fill(pos.X());
        hist->_hY_wrong_matched_hits->Fill(pos.Y());
        hist->_hZ_wrong_matched_hits->Fill(pos.Z());
        hist->_hXY_wrong_matched_hits->Fill(pos.X(), pos.Y());
        hist->_hZX_wrong_matched_hits->Fill(pos.Z(), pos.X());
        hist->_hZY_wrong_matched_hits->Fill(pos.Z(), pos.Y());
        hist->_hZXY_wrong_matched_hits->Fill(pos.Y(), pos.X(), pos.Y());
        wrongFoundCntr++;
    }
}

void BmnGlobalTracking::FillGlobHistoQA(BmnGlobalTrack* tr, Int_t nodeId, TVector3 pos) {
    const BmnFitNode* n = tr->GetFitNode(nodeId);
    if (!n) return;
    const FairTrackParam* par = n->GetUpdatedParam();
    if (!par) return;
    const Float_t trX = par->GetX();
    const Float_t trY = par->GetY();
    Float_t x = pos.X();
    Float_t y = pos.Y();
    Float_t z = pos.Z();
    fGlobHisto->_hHitDist->Fill(Sqrt((trX - x) * (trX - x) + (trY - y) * (trY - y)));
    fGlobHisto->_hHitXDist->Fill(trX - x);
    fGlobHisto->_hHitYDist->Fill(trY - y);
    fGlobHisto->_hX_global->Fill(x);
    fGlobHisto->_hY_global->Fill(y);
    fGlobHisto->_hZ_global->Fill(z);
    fGlobHisto->_hXY_global->Fill(x, y);
    fGlobHisto->_hZX_global->Fill(z, x);
    fGlobHisto->_hZY_global->Fill(z, y);
    fGlobHisto->_hZXY_global->Fill(z, x, y);
}

void BmnGlobalTracking::FillMatchHistoQA(BmnGlobalTrack* tr, Int_t nodeId, TVector3 pos, BmnHitMatchingQA* hist) {
    const BmnFitNode* n = tr->GetFitNode(nodeId);
    if (!n) return;
    const FairTrackParam* par = n->GetUpdatedParam();
    if (!par) return;
    const Float_t trX = par->GetX();
    const Float_t trY = par->GetY();
    Float_t x = pos.X();
    Float_t y = pos.Y();
    Float_t z = pos.Z();
    hist->_hX_matched_hits->Fill(x);
    hist->_hY_matched_hits->Fill(y);
    hist->_hZ_matched_hits->Fill(z);
    //    hist->_hX_not_matched_hits->Fill();
    //    hist->_hY_not_matched_hits->Fill();
    //    hist->_hZ_not_matched_hits->Fill();

    hist->_hXY_matched_hits->Fill(x, y);
    hist->_hZX_matched_hits->Fill(z, x);
    hist->_hZY_matched_hits->Fill(z, y);
    //    hist->_hXY_not_matched_hits->Fill();
    //    hist->_hZX_not_matched_hits->Fill();
    //    hist->_hZY_not_matched_hits->Fill();

    hist->_hZXY_matched_hits->Fill(z, x, y);
    //    hist->_hZXY_not_matched_hits->Fill();

    hist->_hRdist_matched_hits->Fill(Sqrt((trX - x) * (trX - x) + (trY - y) * (trY - y)));
    hist->_hXdist_matched_hits->Fill(trX - x);
    hist->_hYdist_matched_hits->Fill(trY - y);
    //    hist->_hRdist_well_matched_hits->Fill();
    //    hist->_hXdist_well_matched_hits->Fill();
    //    hist->_hYdist_well_matched_hits->Fill();
    //    hist->_hRdist_wrong_matched_hits->Fill();
    //    hist->_hXdist_wrong_matched_hits->Fill();
    //    hist->_hYdist_wrong_matched_hits->Fill();
}

void BmnGlobalTracking::Finish() {


    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);

    //    cout << "\n\t-----------------------------------------------------------------------------------------" << endl;
    //    cout << "\t|                              Efficiency of Global tracking                            |" << endl;
    //    cout << "\t-----------------------------------------------------------------------------------------" << endl;
    //    cout << "\t|  Percent of connected hits:\t\t\t|\t" << allFoundCntr << " / " << allHitCntr << "\t|  " << allFoundCntr * 100.0 / allHitCntr << "%\t|" << endl;
    //    cout << "\t|  Percent of well connected hits:\t\t|\t" << wellFoundCntr << " / " << allFoundCntr << "\t|  " << wellFoundCntr * 100.0 / allFoundCntr << "%\t|" << endl;
    //    cout << "\t|  Percent of wrong connected hits:\t\t|\t" << wrongFoundCntr << " / " << allFoundCntr << "\t|  " << wrongFoundCntr * 100.0 / allFoundCntr << "%\t|" << endl;
    //    cout << "\t|  Percent of well found tracks (thr = " << thresh << "):\t|\t" << goodTrackCntr << " / " << allTrackCntr << "\t|  " << goodTrackCntr * 100.0 / allTrackCntr << "%\t|" << endl;
    //    cout << "\t|  Percent of found tracks:\t\t\t|\t" << allTrackCntr << " / " << allMcTrackCntr << "\t|  " << allTrackCntr * 100.0 / allMcTrackCntr << "%\t|" << endl;
    //    cout << "\t|  Work time: full / per one event:\t\t|\t" << workTime << " sec.\t|  " << workTime / fEventNo << " sec.\t|" << endl;
    //    cout << "\t-----------------------------------------------------------------------------------------" << endl;

    if (fMakeQA) {
        //WRITE QA IN TREE
        FairRunAna* run = FairRunAna::Instance();
        TFile* output = run->GetOutputFile();
        output->cd();
        toDirectory("QA/GlobalTracking");
        fGlobHisto->Write();
        toDirectory("QA/TOF1");
        fTof1Histo->Write();
        toDirectory("QA/DCH1");
        fDch1Histo->Write();
        toDirectory("QA/DCH2");
        fDch2Histo->Write();
        toDirectory("QA/TOF2");
        fTof2Histo->Write();
        gFile->cd();
    }
}

void BmnGlobalTracking::CalculateLength() {
    if (fGlobalTracks == NULL) return;

    /* Calculate the length of the global track
     * starting with (0, 0, 0) and adding all
     * distances between hits
     */
    for (Int_t iTr = 0; iTr < fGlobalTracks->GetEntriesFast(); iTr++) {
        BmnGlobalTrack* glTr = (BmnGlobalTrack*) fGlobalTracks->At(iTr);
        vector<Float_t> X, Y, Z;
        X.push_back(0.);
        Y.push_back(0.);
        Z.push_back(0.);

        if (glTr->GetGemTrackIndex() > -1) {
            if (!isRUN1) {
                const BmnGemTrack* gemTr = (BmnGemTrack*) fGemTracks->At(glTr->GetGemTrackIndex());
                for (Int_t iGem = 0; iGem < gemTr->GetNHits(); iGem++) {
                    const BmnHit* hit = (BmnHit*) fGemHits->At(gemTr->GetHitIndex(iGem));
                    if (!hit) continue;
                    X.push_back(hit->GetX());
                    Y.push_back(hit->GetY());
                    Z.push_back(hit->GetZ());
                }
            }
        }
        if (fDet.GetDet(kTOF1)) {
            if (glTr->GetTof1HitIndex() > -1) {
                const BmnHit* hit = (BmnHit*) fTof1Hits->At(glTr->GetTof1HitIndex());
                if (!hit) continue;
                X.push_back(hit->GetX());
                Y.push_back(hit->GetY());
                Z.push_back(hit->GetZ());
            }
        }
        if (fDet.GetDet(kDCH1)) {
            if (glTr->GetDch1HitIndex() > -1) {
                const BmnHit* hit = (BmnHit*) fDch1Hits->At(glTr->GetDch1HitIndex());
                if (!hit) continue;
                X.push_back(hit->GetX());
                Y.push_back(hit->GetY());
                Z.push_back(hit->GetZ());
            }
        }
        if (fDet.GetDet(kDCH2)) {
            if (glTr->GetDch2HitIndex() > -1) {
                const BmnHit* hit = (BmnHit*) fDch2Hits->At(glTr->GetDch2HitIndex());
                if (!hit) continue;
                X.push_back(hit->GetX());
                Y.push_back(hit->GetY());
                Z.push_back(hit->GetZ());
            }
        }
        if (fDet.GetDet(kTOF)) {
            if (glTr->GetTof2HitIndex() > -1) {
                const BmnHit* hit = (BmnHit*) fTof2Hits->At(glTr->GetTof2HitIndex());
                if (!hit) continue;
                X.push_back(hit->GetX());
                Y.push_back(hit->GetY());
                Z.push_back(hit->GetZ());
            }
        }
        // Calculate distances between hits
        Float_t length = 0.;
        for (Int_t i = 0; i < X.size() - 1; i++) {
            Float_t dX = X[i] - X[i + 1];
            Float_t dY = Y[i] - Y[i + 1];
            Float_t dZ = Z[i] - Z[i + 1];
            length += Sqrt(dX * dX + dY * dY + dZ * dZ);
        }
        glTr->SetLength(length);
        if (fMakeQA) {
            fGlobHisto->_hTrackLength->Fill(length);
        }
    }
}

BmnStatus BmnGlobalTracking::Run1GlobalTrackFinder() {

    Float_t houghMin = 0.0;
    Float_t houghMax = 180.0;
    Int_t nBins = Int_t(houghMax - houghMin) * 20;
    TH2F* hough = new TH2F("hough", "hough", 500, houghMin, houghMax, 500, -0.03, 0.03);
    TH1F* h1 = new TH1F("1", "1", 200, -0.4, 0.4);
    TGraph* orig = new TGraph();
    TGraph* seeds = new TGraph();
    //    seeds->SetMinimum(-1);
    //    seeds->SetMaximum(1);
    seeds->SetMarkerStyle(8);
    seeds->SetMarkerSize(0.5);
    TH2F* cm = new TH2F("cm", "cm", 500, -0.3, 0.3, 500, -0.3, 0.3);

    //    FillHoughHistogram(hough, orig, cm, seeds, fMwpc1Hits);
    //    FillHoughHistogram(hough, orig, cm, seeds, fMwpc2Hits);
    //    FillHoughHistogram(hough, orig, cm, seeds, fMwpc3Hits);
    //    FillHoughHistogram(hough, orig, cm, seeds, fGemHits);
    //    FillHoughHistogram(hough, orig, cm, seeds, fTof1Hits);
    //    FillHoughHistogram(hough, orig, cm, seeds, fDch1Hits);
    //    FillHoughHistogram(hough, orig, cm, seeds, fDch2Hits);
    //    FillHoughHistogram(hough, orig, cm, seeds, fTof2Hits);

    FillHoughHistogram(h1, orig, cm, seeds, fMwpc1Hits);
    FillHoughHistogram(h1, orig, cm, seeds, fMwpc2Hits);
    FillHoughHistogram(h1, orig, cm, seeds, fMwpc3Hits);
    FillHoughHistogram(h1, orig, cm, seeds, fGemHits);
    //    FillHoughHistogram(h1, orig, cm, seeds, fTof1Hits);
    //    FillHoughHistogram(h1, orig, cm, seeds, fDch1Hits);
    //    FillHoughHistogram(h1, orig, cm, seeds, fDch2Hits);
    //    FillHoughHistogram(h1, orig, cm, seeds, fTof2Hits);

    Float_t max = 0.0;
    for (Int_t i = 1; i < hough->GetNbinsX(); ++i)
        for (Int_t j = 1; j < hough->GetNbinsY(); ++j)
            if (hough->GetBinContent(i, j) > max)
                max = hough->GetBinContent(i, j);


    cout << "MAX = " << max << endl;
    for (Int_t i = 1; i < hough->GetNbinsX(); ++i) {
        for (Int_t j = 1; j < hough->GetNbinsY(); ++j) {
            if (hough->GetBinContent(i, j) > 0.95 * max) {
                Float_t phi0 = hough->GetXaxis()->GetBinCenter(i);
                Float_t r0 = hough->GetYaxis()->GetBinCenter(j);
                cout << "i = " << i << " j = " << j << " r0 = " << r0 << " phi0 = " << phi0 << " content = " << hough->GetBinContent(i, j) << endl;
                for (Int_t k = 0; k < 1000; ++k) {
                    Float_t x = 0.6 * k / 1000 - 0.3;
                    Float_t y = (r0 - x * Cos(phi0)) / Sin(phi0);
                    cm->Fill(x, y);
                }
            }
        }
    }

    //    TCanvas* c = new TCanvas("c", "c", 800, 800);
    //    c->Divide(2, 2);
    //    c->cd(1);
    //    orig->Draw("AP");
    //    c->cd(2);
    //    seeds->Draw("AP");
    //    c->cd(3);
    //    cm->Draw("colz");
    //    c->cd(4);
    ////    hough->Draw("colz");
    //    h1->Draw("");

    return kBMNSUCCESS;
}

BmnStatus BmnGlobalTracking::FillHoughHistogram(TH1F* h, TGraph* orig, TH2F* cm, TGraph* seeds, TClonesArray* arr) {

    for (Int_t i = 0; i < arr->GetEntriesFast(); ++i) {
        BmnHit* hit = (BmnHit*) arr->At(i);
        //if (hit->IsUsed()) continue;
        Float_t x = hit->GetX();
        Float_t y = hit->GetY();
        Float_t z = hit->GetZ();
        Float_t r2 = x * x + y * y;
        Float_t R = Sqrt(x * x + y * y + z * z);
        Float_t xr2 = x / r2;
        Float_t yr2 = y / r2;

        Int_t N = 10000;
        for (Int_t iBin = 0; iBin < N; ++iBin) {
            Float_t phi = (180.0 * iBin) / N;
            Float_t r = xr2 * Cos(phi * DegToRad()) + yr2 * Sin(phi * DegToRad());
            //            hough->Fill(phi, r);
        }
        seeds->SetPoint(seeds->GetN(), x / R, y / R);
        //        seeds->SetPoint(seeds->GetN() + 1, x*R , y*R );
        orig->SetPoint(orig->GetN(), x, y);
        cm->Fill(xr2, yr2, 100);
        h->Fill(y / R);
    }
    return kBMNSUCCESS;
}

ClassImp(BmnGlobalTracking);