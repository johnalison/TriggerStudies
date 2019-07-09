
// -*- C++ -*-
#if !defined(EventHists_H)
#define EventHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "TriggerStudies/NtupleAna/interface/EventData.h"

namespace NtupleAna {


  class EventHists {

    struct VtxDiffHists {
      
      std::string m_name;
      TH1F* hPVzDiff_s ;
      TH1F* hPVzDiff   ;
      TH1F* hPVzDiff_l ;
      TH1F* hPVzDiff_vl;
    
      VtxDiffHists(std::string name, TFileDirectory& dir) {

	m_name = name;
	hPVzDiff_s  = dir.make<TH1F>(("PVxDiff_"+name+"_s" ).c_str(), ("PVDiff_"+name).c_str(),100,-0.02,0.02);
	hPVzDiff    = dir.make<TH1F>(("PVxDiff_"+name+""   ).c_str(), ("PVDiff_"+name).c_str(),100,-0.2,0.2);
	hPVzDiff_l  = dir.make<TH1F>(("PVxDiff_"+name+"_l" ).c_str(), ("PVDiff_"+name).c_str(),100,-2,2);
	hPVzDiff_vl = dir.make<TH1F>(("PVxDiff_"+name+"_vl").c_str(), ("PVDiff_"+name).c_str(),100,-20,20);
      }
      
      void Fill(float diff, float eventWeight) {
        hPVzDiff_s ->Fill(diff, eventWeight);       
        hPVzDiff   ->Fill(diff, eventWeight);
        hPVzDiff_l ->Fill(diff, eventWeight);
        hPVzDiff_vl->Fill(diff, eventWeight);
      }
      
    };
    
    TFileDirectory m_dir;
    VtxDiffHists*  m_PVzDiff_offVsTrue   ;
    VtxDiffHists*  m_PVzDiff_FastVsOff   ;
    VtxDiffHists*  m_PVzDiff_FPVPixVsOff ;
    VtxDiffHists*  m_PVzDiff_PixVsOff    ;
    VtxDiffHists*  m_PVzDiff_PFVsOff     ;
    VtxDiffHists*  m_PVzDiff_L3VsOff     ;
    
    
    TH1F* m_nPV;
    TH1F* m_pu;

  public:

    EventHists(std::string name, fwlite::TFileService& fs);

    ~EventHists(); 

    void Fill (const EventData& eventData, float eventWeight = 1.0);
    
  };

}
#endif // EventHists_H
