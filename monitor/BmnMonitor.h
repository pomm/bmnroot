#ifndef BMNMONITOR_H
#define BMNMONITOR_H 1
// STL
#include <iostream>
#include <iterator>
#include <regex>
// FairROOT
#include <TNamed.h>
#include "TFile.h"
#include "TChain.h"
#include "TClonesArray.h"
#include "TColor.h"
#include "TFolder.h"
#include "THttpServer.h"
#include "TMessage.h"
#include "TMonitor.h"
#include "TString.h"
#include "TSystemDirectory.h"
#include "TList.h"
#include "TSystemFile.h"
#include "TServerSocket.h"
// BmnRoot
#include <BmnTrigDigit.h>
#include <BmnTof1Digit.h>
#include <BmnGemStripDigit.h>
#include <BmnDchDigit.h>
#include "BmnDataReceiver.h"
#include <BmnRawDataDecoder.h>
#include "BmnEventHeader.h"
// BmnRoot Monitor
#include "BmnHistToF.h"
#include "BmnHistToF700.h"
#include "BmnHistTrigger.h"
#include "BmnHistDch.h"
#include "BmnHistMwpc.h"
#include "BmnHistGem.h"
#include "BmnOnlineDecoder.h"
#include "BmnHistZDC.h"
#include "BmnHistECAL.h"
#include "BmnHistLAND.h"
#include "BmnOnlineDecoder.h"
#include "BmnHistSilicon.h"
#include "BmnHistSrc.h"

#define TTREE_MAX_SIZE          3e11

using namespace std;
using namespace TMath;

class BmnMonitor : public TNamed {
public:

    BmnMonitor();
    virtual ~BmnMonitor();
    void MonitorStreamZ(TString dir, TString refDir = "", TString decoAddr = "localhost", Int_t webPort = 9000);
    static void threadDecodeWrapper(TString dirname, TString startFile, Bool_t runCurrent);
    static void threadCmdWrapper(string cmd);
    static TObjArray* GetAlikeRuns(BmnEventHeader* header);
    
    // Getters
    deque<UInt_t> * GetDataQue() { return fDataQue;}

    // Setters
    void SetDataQue(deque<UInt_t> * v) { fDataQue = v;}

private:
    void InitServer();
    void ProcessDigi(Int_t iEv);
    void RegisterAll();
    void UpdateRuns();
    BmnStatus CreateFile(Int_t runID = 0);
    BmnStatus OpenStream();
    void FinishRun();
    
    
    void * _ctx;
    void * _decoSocket;
    deque<UInt_t> * fDataQue;
    TString _curFile;
    TString _curDir;
    TString _refDir;
    TString fRawDecoAddr;
    TTree *fRecoTree;
    TTree *fRecoTree4Show;
    TFile *fHistOut;
    TFile *fHistOutTemp;
    THttpServer * fServer;
    TSocket *fRawDecoSocket;
    DigiArrays *fDigiArrays;

    vector < BmnHist* > bhVec;
    vector < BmnHist* > bhVec4show;
    
    TCanvas *infoCanvas;
    TList *refList;

    BmnDataReceiver *dataReceiver;
    BmnOnlineDecoder *onlineDecoder;

    Bool_t keepWorking;
    Int_t _webPort;
    Int_t fTest;
    Int_t fRunID;
    Int_t fEvents;
    BmnWorkerState fState;
    Int_t itersToUpdate;
    Int_t decoTimeout;
    


    ClassDef(BmnMonitor, 1)
};

#endif