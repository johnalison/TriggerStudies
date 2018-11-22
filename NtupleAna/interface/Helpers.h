// -*- C++ -*-

#if !defined(Helpers_H)
#define Helpers_H

#include "TriggerStudies/NtupleAna/interface/JetData.h"
#include "TriggerStudies/NtupleAna/interface/LeptonData.h"

namespace NtupleAna {

  bool failOverlap(const JetData& jet,const std::vector<LeptonData>& leptons) {
    
    for( const LeptonData& l : leptons){
      if(jet.m_vec.DeltaR(l.m_vec) < 0.4)
	return true;
    }
    return false;
  }


}
#endif // Helpers_H
