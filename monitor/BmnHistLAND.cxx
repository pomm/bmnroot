/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BmnHistLAND.cxx
 * Author: ilnur
 * 
 * Created on 23 января 2018 г., 12:50
 */

#include "BmnHistLAND.h"

BmnHistLAND::BmnHistLAND(TString title) : BmnHist() {
    fTitle = title;
    fName = title + "_cl";
    TString name;
    name = fTitle + "_Energy_vs_Bar_0";
    Q0vsBar = new TH2F(name, name, BAR_COUNT, 0, BAR_COUNT, 100, 0, 100);
    Q0vsBar->GetXaxis()->SetTitle("Bar");
    Q0vsBar->GetYaxis()->SetTitle("Energy");
    Q0vsBar->SetOption("colz");
    name = fTitle + "_Energy_vs_Bar_1";
    Q1vsBar = new TH2F(name, name, BAR_COUNT, 0, BAR_COUNT, 100, 0, 100);
    Q1vsBar->GetXaxis()->SetTitle("Bar");
    Q1vsBar->GetYaxis()->SetTitle("Energy");
    Q1vsBar->SetOption("colz");
    name = fTitle + "_Time_vs_Bar_0";
    T0vsBar = new TH2F(name, name, BAR_COUNT, 0, BAR_COUNT, 100, 0, 300);
    T0vsBar->GetXaxis()->SetTitle("Bar");
    T0vsBar->GetYaxis()->SetTitle("Time");
    T0vsBar->SetOption("colz");
    name = fTitle + "_Time_vs_Bar_1";
    T1vsBar = new TH2F(name, name, BAR_COUNT, 0, BAR_COUNT, 100, 0, 300);
    T1vsBar->GetXaxis()->SetTitle("Bar");
    T1vsBar->GetYaxis()->SetTitle("Time");
    T1vsBar->SetOption("colz");
    name = fTitle + "_TimeDiff_vs_Bar";
    TDiffvsBar = new TH2F(name, name, BAR_COUNT, 0, BAR_COUNT, 100, -300, 300);
    TDiffvsBar->GetXaxis()->SetTitle("Bar");
    TDiffvsBar->GetYaxis()->SetTitle("Time");
    TDiffvsBar->SetOption("colz");
    name = fTitle + "_ToF_spectra";
    QvsToF = new TH2F(name, name, 200, TOF_MIN, TOF_MAX, 100, 0, 100);
    QvsToF->GetXaxis()->SetTitle("Time");
    QvsToF->GetYaxis()->SetTitle("Energy");
    QvsToF->SetOption("colz");
    name = fTitle + "Canvas";
    can = new TCanvas(name, name, PAD_WIDTH * CANVAS_COLS, PAD_HEIGHT * CANVAS_ROWS);
    can->Divide(CANVAS_COLS, CANVAS_ROWS);
    canPads.resize(CANVAS_ROWS * CANVAS_COLS);
    for (Int_t iPad = 0; iPad < CANVAS_ROWS * CANVAS_COLS; iPad++) {
        PadInfo* p = new PadInfo();
        canPads[iPad] = p;
        can->GetPad(iPad + 1)->SetGrid();
    }
    canPads[0]->current = Q0vsBar;
    canPads[1]->current = Q1vsBar;
    canPads[2]->current = T0vsBar;
    canPads[3]->current = T1vsBar;
    canPads[4]->current = TDiffvsBar;
    canPads[5]->current = QvsToF;
    for (Int_t iPad = 0; iPad < canPads.size(); iPad++)
        if (canPads[iPad]->current) {
            Names.push_back(canPads[iPad]->current->GetName());
            canPads[iPad]->current->SetTitleSize(0.06, "XY");
            canPads[iPad]->current->SetLabelSize(0.08, "XY");
            TAxis *ax = canPads[iPad]->current->GetYaxis();
            ax->SetTitleColor(kOrange + 10);
            ax->SetTitleOffset(1.8);
            ax->SetTitleFont(62);
            ax = canPads[iPad]->current->GetXaxis();
            ax->SetTitleColor(kOrange + 10);
        }
}

BmnHistLAND::~BmnHistLAND() {
}

void BmnHistLAND::FillFromDigi(DigiArrays *fDigiArrays) {
    TClonesArray * digits = fDigiArrays->land;
    for (Int_t digIndex = 0; digIndex < digits->GetEntriesFast(); digIndex++) {
        BmnLANDDigit *dig = (BmnLANDDigit *) digits->At(digIndex);
        Q0vsBar->Fill(dig->GetGlobBar(), dig->GetEnergy(0));
        Q1vsBar->Fill(dig->GetGlobBar(), dig->GetEnergy(1));
        T0vsBar->Fill(dig->GetGlobBar(), dig->GetTime(0));
        T1vsBar->Fill(dig->GetGlobBar(), dig->GetTime(1));
        TDiffvsBar->Fill(dig->GetGlobBar(), dig->GetTime(1) - dig->GetTime(0));
        QvsToF->Fill(dig->GetTime() - dig->GetTime(), dig->GetEnergy());
    }
}

void BmnHistLAND::Register(THttpServer *serv) {
    fServer = serv;
    fServer->Register("/", this);
    TString path = "/" + fTitle + "/";
    fServer->Register(path, can);
    TString cmdTitle = path + TString("Reset");
    fServer->RegisterCommand(cmdTitle, TString("/") + fName.Data() + "/->Reset()", "button;");
    fServer->Restrict(cmdTitle.Data(), "visible=shift");
    fServer->Restrict(cmdTitle.Data(), "allow=shift");
    //    fServer->Restrict(cmdTitle.Data(), "deny=guest");
}

void BmnHistLAND::SetDir(TFile* outFile, TTree* recoTree) {
    frecoTree = recoTree;
    fDir = NULL;
    if (outFile != NULL)
        fDir = outFile->mkdir(fTitle + "_hists");
    Q0vsBar->SetDirectory(fDir);
    Q1vsBar->SetDirectory(fDir);
    T0vsBar->SetDirectory(fDir);
    T1vsBar->SetDirectory(fDir);
    TDiffvsBar->SetDirectory(fDir);
    QvsToF->SetDirectory(fDir);
}

void BmnHistLAND::Reset() {
    Q0vsBar->Reset();
    Q1vsBar->Reset();
    T0vsBar->Reset();
    T1vsBar->Reset();
    TDiffvsBar->Reset();
    QvsToF->Reset();
}

void BmnHistLAND::DrawBoth() {
    BmnHist::DrawRef(can, &canPads);
}

BmnStatus BmnHistLAND::SetRefRun(Int_t id) {
    if (refID != id) {
        TString FileName = Form("bmn_run%04d_hist.root", id);
        printf("SetRefRun: %s\n", FileName.Data());
        refRunName = FileName;
        refID = id;
        BmnHist::LoadRefRun(refID, refPath + FileName, fTitle, canPads, Names);
        DrawBoth();
    }
}

ClassImp(BmnHistLAND);