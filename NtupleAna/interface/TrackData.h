// -*- C++ -*-

#if !defined(TrackData_H)
#define TrackData_H

#include <math.h>
#include <TLorentzVector.h>

namespace NtupleAna {
  class JetData;
}


namespace NtupleAna {

  
  class TrackData {


  public:

    float m_ip3dSig = 0;
    float m_ip3dVal = 0;

    float m_ip2dSig = 0;
    float m_ip2dVal = 0;

    float m_decayLenVal           = 0;
    //float m_DecayLenSig           = 0;
    float m_jetDistVal            = 0;
    float m_JetDistSig            = 0;
    //float m_GhostTrackWeight      = 
    //float m_GhostTrackDistSig     = 
    //float m_GhostTrackDistVal     = 
    float m_ptRel                 = 0;
    float m_momentum              = 0;
    float m_eta                   = 0;
    float m_pt                    = 0;
    float m_phi                   = 0;
    //float m_Charge                = 0;
    float m_pPar                  = 0;
    float m_dR                    = 0;
    float m_ptRatio               = 0;
    float m_pParRatio             = 0;
    //float m_P0Par                 = 0;
    //float m_P0ParRatio            = 0;
    float m_Chi2                  = 0;
    float m_NTotalHits            = 0;
    float m_NPixelHits            = 0;

    TrackData* m_matchedTrack  = nullptr;
    TrackData* m_secondClosest = nullptr;

    unsigned int m_nMatches = 0;

    JetData* m_jet = nullptr;

    TLorentzVector  m_vec;

  public:

	
    TrackData(float Sip3dSig,
	      float Sip3dVal,
	      float Sip2dSig,
	      float Sip2dVal,
	      float DecayLenVal,
	      float JetDistVal,
	      float JetDistSig,
	      float PtRel,
	      float Momentum,
	      float Eta,
	      float Phi,
	      float PPar,
	      float DeltaR,
	      float PtRatio,
	      float PParRatio,
	      float Chi2,
	      float NTotalHits,
	      float NPixelHits,
	      JetData* jet = nullptr
	      ){

      m_ip3dSig = Sip3dSig;
      m_ip3dVal = Sip3dVal;

      m_ip2dSig = Sip2dSig;
      m_ip2dVal = Sip2dVal;

      m_decayLenVal           = DecayLenVal           ;
      //m_DecayLenSig           = DecayLenSig           ;
      m_jetDistVal            = JetDistVal            ;
      m_JetDistSig            = JetDistSig           ; 
      //m_GhostTrackWeight      = GhostTrackWeight  ;    
      //m_GhostTrackDistSig     = GhostTrackDistSig     ;
      //m_GhostTrackDistVal     = GhostTrackDistVal     ;
      m_ptRel                 = PtRel;
      m_momentum              = Momentum              ;
      m_eta                   = Eta                  ; 
      m_pt                    = Momentum/coshf(m_eta);
      m_phi                   = Phi;
      //m_phi                   = Phi                   ;
      //m_Charge                = Charge                
      m_pPar                  = PPar                  ;
      m_dR                    = DeltaR               ; 
      m_ptRatio               = PtRatio             ;  
      m_pParRatio             = PParRatio          ;   
      //m_P0Par                 = P0Par           ;      
      //m_P0ParRatio            = P0ParRatio      ;      
      m_Chi2                  = Chi2              ;    
      m_NTotalHits            = NTotalHits        ;    
      m_NPixelHits            = NPixelHits        ;    

      m_matchedTrack  = nullptr;
      m_secondClosest = nullptr;

      m_nMatches = 0;

      m_jet = jet;

      m_vec = TLorentzVector();
      m_vec.SetPtEtaPhiM(m_pt,m_eta,m_phi,0);
	  
    };
	

    ~TrackData() {}; 

    float dPhi(const TrackData& rhs) const;
    
  };

}
#endif // TrackData_H
