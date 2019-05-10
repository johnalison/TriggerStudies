#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/TrackHists.h"
#include "TriggerStudies/NtupleAna/interface/TrackData.h"



using namespace std;
using namespace NtupleAna;

TrackHists::TrackHists(std::string name, fwlite::TFileService& fs) {

  TFileDirectory dir = fs.mkdir(name);
  m_name = name;

  m_ip3d_l = dir.make<TH1F>("ip3d_l","ip3d;IP3D [cm]",100,-0.2,0.2);
  m_ip3d   = dir.make<TH1F>("ip3d",  "ip3d;IP3D [cm]",100,-0.05,0.05);
  
  m_ip3d_sig_l = dir.make<TH1F>("ip3d_sig_l","ip3d sig;IP3D significance",100,-100,100);
  m_ip3d_sig   = dir.make<TH1F>("ip3d_sig",  "ip3d sig;IP3D significance",100,-10,10);
  
  m_ip3d_err_l = dir.make<TH1F>("ip3d_err_l","ip3d err;IP3D uncertianty [cm]",100,-0.01,0.1);
  m_ip3d_err   = dir.make<TH1F>("ip3d_err",  "ip3d err;IP3D uncertianty [cm]",100,-0.001,0.01);
  
  m_ip2d_l = dir.make<TH1F>("ip2d_l","ip2d;IP2D [cm]",100,-0.2,0.2);
  m_ip2d   = dir.make<TH1F>("ip2d",  "ip2d;IP2D [cm]",100,-0.05,0.05);

            
  Double_t nBinsPt[11] = {0,2,4,6,8,10,15,20,30,40,60};
  m_ip2d_vs_pt   = dir.make<TH2F>("ip2d_vs_pt",  "ip2d_vs_pt;P_T [GeV]; IP2D [cm]",10,nBinsPt,100,-0.03,0.03);

  Double_t nBinsEta[11] = {0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5};
  m_ip2d_vs_eta   = dir.make<TH2F>("ip2d_vs_eta",  "ip2d_vs_eta;|#eta|; IP2D [cm]",10,nBinsEta,100,-0.03,0.03);


  m_ip2d_sig_l = dir.make<TH1F>("ip2d_sig_l","ip2d sig;IP2D significance",100,-100,100);
  m_ip2d_sig   = dir.make<TH1F>("ip2d_sig",  "ip2d sig;IP2D significance",100,-10,10);
        
  m_ip2d_err_l = dir.make<TH1F>("ip2d_err_l","ip2d err;IP2D uncertianty [cm]",100,-0.01,0.1);
  m_ip2d_err   = dir.make<TH1F>("ip2d_err",  "ip2d err;IP2D uncertianty [cm]",100,-0.001,0.01);
    
  m_trackDecayLenVal_l         = dir.make<TH1F>("trackDecayLenVal_l"  ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  5);
  m_trackDecayLenVal           = dir.make<TH1F>("trackDecayLenVal"    ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  0.5);
  m_trackJetDistVal            = dir.make<TH1F>("trackJetDistVal"     ,    "trackJetDistVal;trackJetDistVal [cm];Entries",  100, -0.1,0.01);      
  m_trackPtRel                 = dir.make<TH1F>("trackPtRel"          ,    "trackPtRel;track p_{T} Rel [GeV];Entries", 100, -0.1, 7);          
  m_trackMomentum              = dir.make<TH1F>("trackMomentum"       ,    "trackMomentum;track momentum [GeV];Entries", 60, 0, 60);       


  Double_t binsPt[28] = {0.9, 1.116, 1.3838, 1.716, 2.1278, 2.6385, 3.2717, 4.0569, 5.0306, 6.2379, 7.735, 9.5914, 11.8933, 14.7477, 18.2872, 22.6761, 28.1183, 34.8667, 43.2347, 53.6111, 66.4777, 82.4324, 102.2162, 126.748, 157.1676, 194.8878, 241.6609, 299.6595};
  m_trackPt_logx               = dir.make<TH1F>("trackPt_logx", "trackPt;track p_{T} [GeV];Entries", 27, binsPt);
  
  m_trackEta                   = dir.make<TH1F>("trackEta"            ,    "trackEta;track #eta;Entries", 100, -2.6, 2.6);            
  m_trackPhi                   = dir.make<TH1F>("trackPhi"            ,    "trackPhi;track #phi;Entries", 100, -3.2, 3.2);            
  m_trackPPar                  = dir.make<TH1F>("trackPPar"           ,    "trackPPar;track PPar [GeV];Entries",60, 0, 60);           
  m_trackDeltaR                = dir.make<TH1F>("trackDeltaR"         ,    "trackDeltaR;track #DeltaR;Entries", 160, -0.05, 0.35);         
  m_trackEtaRel                = dir.make<TH1F>("trackEtaRel"         ,    "trackEtaRel;track Eta Rel;Entries", 100, 0, 7);         
  m_trackPtRatio               = dir.make<TH1F>("trackPtRatio"        ,    "trackPtRatio;track p_{T} Ratio;Entries", 100, -0.01, 0.3); 
  m_trackPParRatio             = dir.make<TH1F>("trackPParRatio"      ,    "trackPParRatio;track P Par Ratio;Entries", 100, 0.95, 1.02);  
  
  m_trackChi2                  = dir.make<TH1F>("trackChi2"            ,    "trackChi2;track Chi2;Entries", 100, -0.1, 6);            
  m_trackNTotalHits            = dir.make<TH1F>("trackNTotalHits"      ,    "trackNTotalHits;trackNTotalHits;Entries", 30, -0.5, 29.5);
  m_trackNPixelHits            = dir.make<TH1F>("trackNPixelHits"      ,    "trackNPixelHits;trackNPixelHits;Entries", 10, -0.5,  9.5);  
  m_trackHasInnerPixHit        = dir.make<TH1F>("trackHasInnerPixHit"  ,    "trackHasInnerPixHit;trackHasInnerPixHit;Entries", 2, -0.5,  1.5);  
  
  
  m_track_nMatches = dir.make<TH1F>("track_nMatches", "track_nMatches;# of matched tracks;Entries", 6, -0.5, 5.5);
  
  m_track_matched_dip2d     = dir.make<TH1F>("track_matched_dip2d"    ,    "track_matched_dip2d;IP2D-IP2D^{matched} [cm];Entries",100,-0.05,0.05);
  m_track_matched_phi_vs_dip2d = dir.make<TH2F>("track_matched_phi_vs_dip2d", "track_matched_phi_vs_dip2d;#phi;IP2D-IP2D^{matched} [cm]", 64,-3.2,3.2, 40,-0.02,0.02);
  m_track_matched_eta_vs_dip2d = dir.make<TH2F>("track_matched_eta_vs_dip2d", "track_matched_eta_vs_dip2d;#eta;IP2D-IP2D^{matched} [cm]", 52,-2.6,2.6, 40,-0.02,0.02);
  m_track_matched_dPtRel    = dir.make<TH1F>("track_matched_dPtRel"   ,    "track_matched_dPtRel;p_{T}^{Rel}-p_{T}^{Rel, matched} [GeV];Entries", 100, -5, 5);
  m_track_matched_dMomentum = dir.make<TH1F>("track_matched_dMomentum",    "track_matched_dMomentum;p-p^{matched} [GeV];Entries", 500, -10, 10);
  m_track_matched_dEta      = dir.make<TH1F>("track_matched_dEta"     ,    "track_matched_dEta;#eta-#eta^{matched};Entries", 500, -0.1, 0.1);            
  m_track_matched_dEta_s    = dir.make<TH1F>("track_matched_dEta_s"   ,    "track_matched_dEta;#eta-#eta^{matched};Entries", 500, -0.01, 0.01);            
  m_track_matched_dPhi      = dir.make<TH1F>("track_matched_dPhi"     ,    "track_matched_dPhi;#phi-#phi^{matched};Entries", 500,     0, 0.1);            
  m_track_matched_dR        = dir.make<TH1F>("track_matched_dR"       ,    "track_matched_dR;#DeltaR(track, matched track);;Entries", 500, -0.05, 1.2);
  m_track_matched_dR_s      = dir.make<TH1F>("track_matched_dR_s"     ,    "track_matched_dR;#DeltaR(track, matched track);;Entries", 340, -0.005, 0.08);
  
  m_track_matched_dEta_vs_dMomentum = dir.make<TH2F>("track_matched_dEta_vs_dMomentum", "dEta_vs_dMomentum;#eta-#eta^{matched};p-p^{matched} [GeV]",100,-0.01,0.01,100,-5,5);
  m_track_matched_dEta_vs_dPhi = dir.make<TH2F>("track_matched_dEta_vs_dPhi", "dEta_vs_dPhi;#eta-#eta^{matched};|#phi-#phi^{matched}|",120,-0.012,0.012,60,0,0.012);

  m_track_secondClosest_dEta      = dir.make<TH1F>("track_secondClosest_dEta",         "track_matched_dEta2;#eta-#eta^{second closest};Entries", 500, -0.1, 0.1);
  m_track_secondClosest_dEta_s    = dir.make<TH1F>("track_secondClosest_dEta_s",       "track_matched_dEta2;#eta-#eta^{second closest};Entries", 500, -0.01, 0.01);
  m_track_secondClosest_dMomentum = dir.make<TH1F>("track_secondClosest_dMomentum",    "track_secondClosest_dMomentum;p-p^{second closest} [GeV];Entries", 500, -10, 10);
  m_track_secondClosest_dR        = dir.make<TH1F>("track_secondClosest_dR"       ,    "track_secondClosest_dR;#DeltaR(matched track, secondClosest track);;Entries", 500, -0.05, 1.2);
  m_track_secondClosest_dR_s      = dir.make<TH1F>("track_secondClosest_dR_s"     ,    "track_secondClosest_dR;#DeltaR(matched track, secondClosest track);;Entries", 340, -0.005, 0.08);
  m_track_secondClosest_dEta_vs_dMomentum = dir.make<TH2F>("track_secondClosest_dEta_vs_dMomentum", "dEta_vs_dMomentum;#eta-#eta^{secondClosest};p-p^{secondClosest} [GeV]",100,-0.01,0.01,100,-5,5);
  m_track_dEta12 = dir.make<TH1F>("track_dEta12", "track_dEta12;#eta^{matched}-#eta^{second closest};Entries", 500, -0.1, 0.1);


} 

TrackHists::~TrackHists() {} 


void
TrackHists::Fill (const TrackData& track, float eventWeight){
  
  m_ip3d  ->Fill(track.m_ip3dVal);
  m_ip3d_l->Fill(track.m_ip3dVal);
        
  m_ip3d_sig  ->Fill(track.m_ip3dSig);
  m_ip3d_sig_l->Fill(track.m_ip3dSig);
  
  float this_ip3d_err = track.m_ip3dVal/track.m_ip3dSig;
  m_ip3d_err  ->Fill(this_ip3d_err);
  m_ip3d_err_l->Fill(this_ip3d_err);
  
  
  m_ip2d  ->Fill(track.m_ip2dVal);
  m_ip2d_l->Fill(track.m_ip2dVal);
  
  m_ip2d_sig  ->Fill(track.m_ip2dSig);
  m_ip2d_sig_l->Fill(track.m_ip2dSig);
  
  float this_ip2d_err = track.m_ip2dVal/track.m_ip2dSig;
  m_ip2d_err  ->Fill(this_ip2d_err);
  m_ip2d_err_l->Fill(this_ip2d_err);

  m_ip2d_vs_pt->Fill(     track.m_momentum, track.m_ip2dVal);
  m_ip2d_vs_eta->Fill(fabs(track.m_eta)    , track.m_ip2dVal);
        

  m_trackDecayLenVal_l   ->Fill(track.m_decayLenVal);
  m_trackDecayLenVal     ->Fill(track.m_decayLenVal);
  m_trackJetDistVal      ->Fill(track.m_jetDistVal );
  m_trackPtRel           ->Fill(track.m_ptRel      );
  m_trackMomentum        ->Fill(track.m_momentum   ); 
  m_trackPt_logx         ->Fill(track.m_pt         ); 
  m_trackEta             ->Fill(track.m_eta        );
  m_trackPhi             ->Fill(track.m_phi        );
  m_trackPPar            ->Fill(track.m_pPar       );
  m_trackDeltaR          ->Fill(track.m_dR         );
  //m_trackEtaRel          ->Fill(track.m_etaRel     );
  m_trackPtRatio         ->Fill(track.m_ptRatio    );
  m_trackPParRatio       ->Fill(track.m_pParRatio  );

  m_trackChi2                  ->Fill(track.m_Chi2      );
  m_trackNTotalHits            ->Fill(track.m_NTotalHits); 
  m_trackNPixelHits            ->Fill(track.m_NPixelHits);
  m_trackHasInnerPixHit        ->Fill(track.m_JetDistSig);


  if(track.m_matchedTrack){
    m_track_matched_dip2d       ->Fill(           track.m_ip2dVal  - track.m_matchedTrack->m_ip2dVal);
    m_track_matched_phi_vs_dip2d->Fill(track.m_phi, track.m_ip2dVal  - track.m_matchedTrack->m_ip2dVal);
    m_track_matched_eta_vs_dip2d->Fill(track.m_eta, track.m_ip2dVal  - track.m_matchedTrack->m_ip2dVal);
    m_track_matched_dPtRel   ->Fill(track.m_ptRel    - track.m_matchedTrack->m_ptRel);
    m_track_matched_dMomentum->Fill(track.m_momentum - track.m_matchedTrack->m_momentum); 
    m_track_matched_dEta     ->Fill(track.m_eta      - track.m_matchedTrack->m_eta);
    m_track_matched_dEta_s   ->Fill(track.m_eta      - track.m_matchedTrack->m_eta);
    float matched_dPhi = track.dPhi(*(track.m_matchedTrack));
    m_track_matched_dPhi     ->Fill(matched_dPhi);

    float matched_dEta = (track.m_eta-track.m_matchedTrack->m_eta);
    float matched_dR   = pow(matched_dEta*matched_dEta + matched_dPhi*matched_dPhi , 0.5);
    m_track_matched_dR       ->Fill(matched_dR);
    m_track_matched_dR_s     ->Fill(matched_dR);
    
    m_track_matched_dEta_vs_dMomentum->Fill(matched_dEta, track.m_momentum - track.m_matchedTrack->m_momentum);
    m_track_matched_dEta_vs_dPhi     ->Fill(matched_dEta, matched_dPhi);
  }

  if(track.m_secondClosest != nullptr){
    m_track_secondClosest_dEta     ->Fill(track.m_eta      - track.m_secondClosest->m_eta);
    m_track_secondClosest_dEta_s   ->Fill(track.m_eta      - track.m_secondClosest->m_eta);
    m_track_secondClosest_dMomentum->Fill(track.m_momentum - track.m_secondClosest->m_momentum); 

    float secondClosest_dEta = track.m_eta-track.m_secondClosest->m_eta;
    float secondClosest_dPhi = track.dPhi(*track.m_secondClosest);
    float secondClosest_dR = pow( secondClosest_dEta*secondClosest_dEta + secondClosest_dPhi*secondClosest_dPhi, 0.5);
    m_track_secondClosest_dR       ->Fill(secondClosest_dR);
    m_track_secondClosest_dR_s     ->Fill(secondClosest_dR);
    m_track_secondClosest_dEta_vs_dMomentum->Fill(secondClosest_dEta, track.m_momentum - track.m_secondClosest->m_momentum);
    m_track_dEta12->Fill(track.m_matchedTrack->m_eta - track.m_secondClosest->m_eta);
  }

  return;
}

void 
TrackHists::FillMatchStats (const TrackData& track){
  m_track_nMatches->Fill(track.m_nMatches);
  return;
}


