// -*- C++ -*-
#if !defined(JetHists_H)
#define JetHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "TriggerStudies/NtupleAna/interface/JetData.h"

namespace NtupleAna {


  class JetHists {

    TH1F* m_pt     ;
    TH1F* m_pt_l   ;
    TH1F* m_eta    ;
    TH1F* m_phi    ;
    TH1F* m_mass   ;
    TH1F* m_deepcsv;

  public:

    JetHists(std::string name, fwlite::TFileService& fs);

    ~JetHists(); 
    
    void Fill (const JetData& jetInfo);
    
  };

}
#endif // JetHists_H
