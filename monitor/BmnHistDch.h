/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BmnHistDch.h
 * Author: ilnur
 *
 * Created on November 29, 2016, 2:44 PM
 */

#ifndef BMNHISTDCH_H
#define BMNHISTDCH_H 1
#include <TNamed.h>
#include <exception>
#include <stdlib.h>
#include <vector>
#include "TChain.h"
#include "TColor.h"
#include "TClonesArray.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TFolder.h"
#include "TString.h"
#include "THttpServer.h"
#include "BmnDchDigit.h"

#define kNPLANES     16
#define kNREALWIRES 240
#define kNWIRES     256
#define Number        4
#define nb          100

using namespace std;

class BmnHistDch : public TNamed {
public:
    BmnHistDch(TString title);
    virtual ~BmnHistDch();
    void Reset();
    void Register(THttpServer *serv);
    void SetDir(TFile *outFile, TTree *recoTree);
    void FillFromDigi(TClonesArray * digits);

    TH1F * h_wires[kNPLANES];
    Float_t v_wires[kNPLANES][kNWIRES];

private:
    THttpServer *fServer;
    TTree *frecoTree;

    Int_t myPalette[nb];


    ClassDef(BmnHistDch, 1)
};

#endif /* BMNHISTDCH_H */
