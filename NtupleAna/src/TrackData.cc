#include "TriggerStudies/NtupleAna/interface/TrackData.h"
#include "DataFormats/Math/interface/deltaPhi.h"

using namespace NtupleAna;

float 
TrackData::dPhi(const TrackData& rhs) const{
  return reco::deltaPhi(m_phi, rhs.m_phi);
}
