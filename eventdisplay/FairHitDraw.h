/*
 * FairHitDraw.h
 *
 *  Created on: Apr 16, 2009
 *      Author: stockman
 *
 *      Simple method to draw points derived from FairHit
 */

#ifndef FAIRHITDRAW_H
#define FAIRHITDRAW_H

#include "FairBoxSetDraw.h"
#include "Rtypes.h"
#include "TVector3.h"


class FairHitDraw : public FairBoxSetDraw
{
  public:
    FairHitDraw();

    /** Standard constructor
      *@param name        Name of task
      *@param iVerbose    Verbosity level
      **/
    FairHitDraw(const char* name, Int_t iVerbose = 0);

  protected:
    TVector3 GetVector(TObject* obj);

    ClassDef(FairHitDraw,1);
};

#endif /* FAIRHITDRAW_H */
