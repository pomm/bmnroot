/**
 * \file BmnTrackExtrapolator.h
 * \author Andrey Lebedev <andrey.lebedev@gsi.de> - Original author. First version of code for CBM experiment.
 * \author Sergey Merts <Sergey.Merts@gmail.com> - Modification for BMN experiment.
 * \date 2008-2014
 * \brief Interface for track extrapolation algorithm.
 */

#ifndef BMNTRACKEXTRAPOLATOR_H_
#define BMNTRACKEXTRAPOLATOR_H_

#include "BmnEnums.h"
#include "FairTrackParam.h"
#include "BmnFieldMap.h"
#include "BmnFieldMapSym3.h"

#include <vector>
#include <cstddef>

using namespace std;

class FairTrackParam;

/**
 * \class BmnTrackExtrapolator
 * \author Andrey Lebedev <andrey.lebedev@gsi.de> - Original author. First version of code for CBM experiment.
 * \author Sergey Merts <Sergey.Merts@gmail.com> - Modification for BMN experiment.
 * \date 2008-2014
 * \brief Interface for track extrapolation algorithm.
 *
 * Extrapolation algorithm do not have to take into account material effects.
 */
class BmnTrackExtrapolator
{
public:
   /**
    * \brief Constructor.
    */
   BmnTrackExtrapolator();

   /**
    * \brief Destructor.
    */
   virtual ~BmnTrackExtrapolator();

   /**
    * \brief Track parameters extrapolation with calculation of transport matrix.
    * \param[in] parIn Pointer to initial track parameters.
    * \param[out] parOut Pointer to output track parameters.
    * \param[in] zOut Z position to extrapolate to [cm].
    * \param[out] F Output transport matrix. If F == NULL than transport matrix is not calculated.
    * \return Extrapolation status.
    */
   
   BmnStatus RK4TrackExtrapolate(FairTrackParam* par, Float_t zOut, vector<Double_t>* F);
   void RK4Order(const vector<Double_t>& xIn, Float_t zIn, vector<Double_t>& xOut, Float_t zOut, vector<Double_t>& derivs) const;
   Float_t CalcOut(Float_t in, const Float_t k[4]) const;
   void TransportC(const vector<Double_t>& cIn, const vector<Double_t>& F, vector<Double_t>& cOut) const;
   
   BmnStatus LineTrackExtrapolate(FairTrackParam* par, Float_t zOut, vector<Double_t>* F);
   //BmnStatus CleverTrackExtrapolator(); NOT ADDED YET
   
private:
    FairField* fField;
   
};

#endif /*BMNTRACKEXTRAPOLATOR_H_*/