#ifndef BMNMATH_H_
#define BMNMATH_H_

#include "FairTrackParam.h"

class CbmHit;
class CbmStripHit;
class CbmPixelHit;
class CbmGlobalTrack;

namespace lit
{

/* Calculates chi square
 * @param par Pointer to the updated or smoothed track parameter
 * @param hit Pointer to the hit
 * @return chi square contribution for this hit */
Float_t ChiSq(const FairTrackParam* par, const CbmHit* hit);

/* Calculates chi square for strip hits
 * @param par Pointer to the updated or smoothed track parameter
 * @param hit Pointer to the strip hit
 * @return chi square contribution for this strip hit */
Float_t ChiSq(const FairTrackParam* par, const CbmStripHit* hit);

/* Calculates chi square for pixel hits
 * @param par Pointer to the updated or smoothed track parameter
 * @param hit Pointer to the pixel hit
 * @return chi square contribution for this pixel hit */
Float_t ChiSq(const FairTrackParam* par, const CbmPixelHit* hit);

/* Calculates number of degrees of freedom
 * @param track Pointer to the track */
Int_t NDF(const CbmGlobalTrack* track);

}
#endif /*BMNMATH_H_*/