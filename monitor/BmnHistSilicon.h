/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BmnHistSilicon.h
 * Author: ilnur
 *
 * Created on March 9, 2017, 10:39 AM
 */

#ifndef BMNHISTSILICON_H
#define BMNHISTSILICON_H
#include <TNamed.h>
#include <exception>
#include <stdlib.h>
#include <vector>
#include "TChain.h"
#include "TClonesArray.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TFolder.h"
#include "TString.h"
#include "THttpServer.h"

#include "BmnHist.h"
#include "BmnSiliconDigit.h"

using namespace std;

class BmnHistSilicon : public BmnHist {
public:
    BmnHistSilicon(TString title = "Silicon", TString path = "");
    virtual ~BmnHistSilicon();
    void Reset();
    void Register(THttpServer *serv);
    void SetDir(TFile *outFile = NULL, TTree *recoTree = NULL);
    void DrawBoth();
    void FillFromDigi(DigiArrays *fDigiArrays);
    BmnStatus  SetRefRun(Int_t id);
private:
    TCanvas *canStrip;
    vector<PadInfo*> canStripPads;
//    BmnGemStripConfiguration::GEM_CONFIG gemStationConfig;
//    BmnGemStripStationSet *gemStationSet;
    vector<TString> Names;
    vector<vector<vector<TH1F*  > > > histSiliconStrip;
    UInt_t sumMods;
    UInt_t maxLayers;

    ClassDef(BmnHistSilicon, 1)
};

#endif /* BMNHISTSILICON_H */

