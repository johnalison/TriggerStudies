// -*- C++ -*-
#if !defined(LeptonHists_H)
#define LeptonHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "TriggerStudies/NtupleAna/interface/LeptonData.h"


namespace NtupleAna {


  class LeptonHists {

    TH1F* m_pt     ;
    TH1F* m_pt_l   ;
    TH1F* m_eta    ;
    TH1F* m_phi    ;
    TH1F* m_mass   ;
    TH1F* m_SF;
    TH1F* m_superClusterEta;
    TH1F* m_iso;
    TH1F* m_iso_l;
    TH1F* m_iso_vl;

    bool m_isElectrons = false;

  public:

    TH1F* m_n      ;

    LeptonHists(std::string name, fwlite::TFileService& fs, bool isElectrons=false);

    ~LeptonHists(); 
    
    void Fill (const LeptonData& lepInfo, float eventWeight = 1.0);
    
  };

}
#endif // LeptonHists_H
