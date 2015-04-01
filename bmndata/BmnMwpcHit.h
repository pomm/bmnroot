// BmnMwpcHit class

#ifndef BmnMwpcHit_H
#define BmnMwpcHit_H 1

#include <math.h>
#include <iostream>
#include <vector>
#include "FairHit.h"
#include <TObject.h>

using namespace std;

// class TClonesArray;

class BmnMwpcHit : public FairHit {
public:

    /** Default constructor **/
    BmnMwpcHit();

    /** Constructor to use **/
    BmnMwpcHit(Int_t detUID, TVector3 posHit, TVector3 posHitErr, Int_t pointIndx);

    Int_t GetXaddr() const {
        return fXaddr;
    }

    Int_t GetYaddr() const {
        return fYaddr;
    }

    ULong_t GetAddr() const {
        return fAddr;
    }
    
    Short_t GetMwpcId() const {
        return fMwpcId;
    }

    Bool_t IsUsed() const {
        return fUsing;
    }

    void SetUsing(Bool_t use) {
        fUsing = use;
    }

    void SetXaddr(Int_t addr) {
        fXaddr = addr;
    }

    void SetYaddr(Int_t addr) {
        fYaddr = addr;
    }

    void SetAddr(ULong_t addr) {
        fAddr = addr;
    }
    
    void SetMwpcId(Short_t id) {
        fMwpcId = id;
    }
    

    /** Destructor **/
    virtual ~BmnMwpcHit();

private:

    Bool_t fUsing;
    Int_t fXaddr;
    Int_t fYaddr;
    ULong_t fAddr;
    Short_t fMwpcId; // 1, 2, 3

    ClassDef(BmnMwpcHit, 1);

};

#endif