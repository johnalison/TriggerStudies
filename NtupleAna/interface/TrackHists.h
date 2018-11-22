// -*- C++ -*-
#if !defined(TrackHists_H)
#define TrackHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"

namespace NtupleAna {
  class TrackData;
}

namespace NtupleAna {


  class TrackHists {

        
    TH1F* m_ip3d_l ;
    TH1F* m_ip3d   ;
    
    TH1F* m_ip3d_sig_l;
    TH1F* m_ip3d_sig  ;
    
    TH1F* m_ip3d_err_l;
    TH1F* m_ip3d_err  ;
    
    TH1F* m_ip2d_l ;
    TH1F* m_ip2d   ;
    
    
    TH2F* m_ip2d_vs_pt;

    TH2F* m_ip2d_vs_eta;


    TH1F* m_ip2d_sig_l;
    TH1F* m_ip2d_sig;
        
    TH1F* m_ip2d_err_l;
    TH1F* m_ip2d_err;
    
    TH1F* m_trackDecayLenVal_l ;
    TH1F* m_trackDecayLenVal;
    TH1F* m_trackJetDistVal ;    
    TH1F* m_trackPtRel      ; 
    TH1F* m_trackMomentum   ;
    
    TH1F* m_trackPt_logx           ;

    TH1F* m_trackEta           ;       
    TH1F* m_trackPhi           ;       
    TH1F* m_trackPPar          ;       
    TH1F* m_trackDeltaR        ;       
    TH1F* m_trackEtaRel        ;       
    TH1F* m_trackPtRatio       ;       
    TH1F* m_trackPParRatio     ;       
    
    TH1F* m_trackChi2          ;       
    TH1F* m_trackNTotalHits    ;       
    TH1F* m_trackNPixelHits    ;       
    TH1F* m_trackHasInnerPixHit;       


    TH1F* m_track_nMatches;

    TH1F* m_track_matched_dip2d;
    TH2F* m_track_matched_phi_vs_dip2d;
    TH2F* m_track_matched_eta_vs_dip2d;
    TH1F* m_track_matched_dPtRel   ; 
    TH1F* m_track_matched_dMomentum; 
    TH1F* m_track_matched_dEta     ;  
    TH1F* m_track_matched_dEta_s   ;    
    TH1F* m_track_matched_dPhi     ;   
    TH1F* m_track_matched_dR       ; 
    TH1F* m_track_matched_dR_s     ; 

    TH2F* m_track_matched_dEta_vs_dMomentum;
    TH2F* m_track_matched_dEta_vs_dPhi;

    TH1F* m_track_secondClosest_dEta              ;
    TH1F* m_track_secondClosest_dEta_s    	;
    TH1F* m_track_secondClosest_dMomentum 	;
    TH1F* m_track_secondClosest_dR        	;
    TH1F* m_track_secondClosest_dR_s      	;
    TH2F* m_track_secondClosest_dEta_vs_dMomentum	;
    TH1F* m_track_dEta12                          ;

  public:

    TrackHists(std::string name, fwlite::TFileService& fs);

    ~TrackHists(); 
    
    void Fill (const TrackData& track);

    void FillMatchStats(const TrackData& track);

    
  };

}
#endif // TrackHists_H
