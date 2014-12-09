// -------------------------------------------------------------------------
// -----                        FairPointSetDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#include "FairPointSetDraw.h"

#include "FairEventManager.h"           // for FairEventManager
#include "FairRootManager.h"            // for FairRootManager
#include "FairMCPointDraw.h"

#include "Riosfwd.h"                    // for ostream
#include "TClonesArray.h"               // for TClonesArray
#include "TEveManager.h"                // for TEveManager, gEve
#include "TEvePointSet.h"               // for TEvePointSet
#include "TEveTreeTools.h"              // for TEvePointSelectorConsumer, etc
#include "TNamed.h"                     // for TNamed
#include "TString.h"                    // for Form
#include "TVector3.h"                   // for TVector3

#include <stddef.h>                     // for NULL
#include <iostream>                     // for operator<<, basic_ostream, etc

class TObject;

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairPointSetDraw::FairPointSetDraw()
  : FairTask("FairPointSetDraw", 0),
    fVerbose(0),
    fPointList(NULL),
    fEventManager(NULL),
    fq(NULL),
    fColor(0),
    fStyle(0)
{
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairPointSetDraw::FairPointSetDraw(const char* name, Color_t color ,Style_t mstyle,Int_t iVerbose)
  : FairTask(name, iVerbose),
    fVerbose(iVerbose),
    fPointList(NULL),
    fEventManager(NULL),
    fq(NULL),
    fColor(color),
    fStyle(mstyle)
{
}

// -------------------------------------------------------------------------
InitStatus FairPointSetDraw::Init()
{
  if (fVerbose > 1)
      cout<<  "FairPointSetDraw::Init()" << endl;

  FairRootManager* fManager = FairRootManager::Instance();

  fPointList = (TClonesArray*)fManager->GetObject(GetName());
  if(fPointList == 0)
  {
    cout << "FairPointSetDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< endl;
    SetActive(kFALSE);
  }
  if (fVerbose > 2)
      cout<< "FairPointSetDraw::Init() get point list" << fPointList << endl;

  fEventManager = FairEventManager::Instance();
  if (fVerbose > 2)
      cout<< "FairPointSetDraw::Init() get instance of FairEventManager " << endl;

  fq = 0;

  return kSUCCESS;
}

// -------------------------------------------------------------------------
void FairPointSetDraw::Exec(Option_t* option)
{
  if (IsActive())
  {
    Reset();

    Int_t npoints = fPointList->GetEntriesFast();
    TEvePointSet* q = new TEvePointSet(GetName(), npoints, TEvePointSelectorConsumer::kTVT_XYZ);

    q->SetOwnIds(kTRUE);
    q->SetMarkerColor(fColor);
    q->SetMarkerSize(1.5);
    q->SetMarkerStyle(fStyle);
    //std::cout << "fPointList: " << fPointList << " " << fPointList->GetEntries() << std::endl;

    for (Int_t i=0; i < npoints; i++)
    {
      TObject* p = (TObject*)fPointList->At(i);
      if(p != 0)
      {
          TVector3 vec(GetVector(p));
          q->SetNextPoint(vec.X(),vec.Y(), vec.Z());
          q->SetPointId(GetValue(p, i));
      }
    }

    // check: this point is instance of FairMCPointDraw class
    FairMCPointDraw* pCheckClass = dynamic_cast<FairMCPointDraw*>(this);
    if (pCheckClass != NULL)
    {
        if (fEventManager->EveMCPoints == NULL)
        {
            fEventManager->EveMCPoints = new TEveElementList("MC points");
            gEve->AddElement(fEventManager->EveMCPoints, fEventManager);
            fEventManager->EveMCPoints->SetRnrState(kFALSE);
        }

        gEve->AddElement(q, fEventManager->EveMCPoints);
    }
    else
    {
        if (fEventManager->EveRecoPoints == NULL)
        {
            fEventManager->EveRecoPoints = new TEveElementList("Reco points");
            gEve->AddElement(fEventManager->EveRecoPoints, fEventManager);
            fEventManager->EveRecoPoints->SetRnrState(kFALSE);
        }

        gEve->AddElement(q, fEventManager->EveRecoPoints);
    }

    gEve->Redraw3D(kFALSE);

    fq = q;
  }
}

TObject* FairPointSetDraw::GetValue(TObject* obj,Int_t i)
{
  return new TNamed(Form("Point %d", i),"");
}

// -----   Destructor   ----------------------------------------------------
FairPointSetDraw::~FairPointSetDraw()
{
}
// -------------------------------------------------------------------------
void FairPointSetDraw::SetParContainers()
{

}
// -------------------------------------------------------------------------
/** Action after each event**/
void FairPointSetDraw::Finish()
{
}
// -------------------------------------------------------------------------
void FairPointSetDraw::Reset()
{
  if (fq != 0)
  {
    fq->Reset();

    FairMCPointDraw* pCheckClass = dynamic_cast<FairMCPointDraw*>(this);
    if (pCheckClass != NULL)
        gEve->RemoveElement(fq, fEventManager->EveMCPoints);
    else
        gEve->RemoveElement(fq, fEventManager->EveRecoPoints);
  }
}

ClassImp(FairPointSetDraw);