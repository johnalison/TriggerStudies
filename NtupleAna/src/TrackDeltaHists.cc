#include "TChain.h"

//#include "TriggerStudies/NtupleAna/interface/TrackHists.h"
#include "TriggerStudies/NtupleAna/interface/TrackData.h"
#include "TriggerStudies/NtupleAna/interface/TrackDeltaHists.h"


using namespace std;
using namespace NtupleAna;

TrackDeltaHists::TrackDeltaHists(std::string name, fwlite::TFileService& fs) {

  TFileDirectory dir = fs.mkdir(name);
  m_name = name;

  m_Dip3d       = dir.make<TH1F>("ip3d",  "#Delta ip3d;#Delta IP3D [cm];Entries",100,-0.2,0.2);
  m_zoomip3d    = dir.make<TH1F>("ip3dZoom", "#Delta ip3d;#Delta IP3D [cm];Entries",100,-0.015,0.015);
  m_Dip3d_sig   = dir.make<TH1F>("ip3d_sig",  "#Delta ip3d sig;#Delta IP3D significance;Entries",100,-10,10);
  m_Dip3d_err   = dir.make<TH1F>("ip3d_err",  "#Delta ip3d err;#Delta IP3D uncertianty [cm];Entries",100,-0.005,0.005);
  m_Dip2d       = dir.make<TH1F>("ip2d",  "#Delta ip2d;#Delta IP2D [cm];Entries",100,-0.2,0.2);
  m_zoomip2d    = dir.make<TH1F>("ip2dZoom", "#Delta ip2d;#Delta IP2D [cm];Entries",100,-0.015,0.015);
  m_Dip2d_sig   = dir.make<TH1F>("ip2d_sig",  "#Delta ip2d sig;#Delta IP2D significance;Entries",100,-10,10);
  m_Dip2d_err   = dir.make<TH1F>("ip2d_err",  "#Delta ip2d err;#Delta IP2D uncertianty [cm];Entries",100,-0.005,0.005);
  m_DtrackDecayLenVal           = dir.make<TH1F>("trackDecayLenVal"    ,    "#Delta trackDecayLenVal;#Delta trackDecayLenVal [cm];Entries", 100, -1.0,  1.0);
  m_DtrackJetDistVal            = dir.make<TH1F>("trackJetDistVal"     ,    "#Delta trackJetDistVal;#Delta trackJetDistVal [cm];Entries",  100, -0.05,0.05);      
  m_DtrackPtRel                 = dir.make<TH1F>("trackPtRel"          ,    "#Delta trackPtRel;#Delta track p_{T} Rel [GeV];Entries", 100, -1.5, 1.5);          
  m_DtrackMomentum              = dir.make<TH1F>("trackMomentum"       ,    "#Delta trackMomentum;#Delta track momentum [GeV];Entries", 60, -1.5, 1.5);       
  m_DtrackEta                   = dir.make<TH1F>("trackEta"            ,    "#Delta trackEta;#Delta track #eta;Entries", 100, -0.005, 0.005);            
  m_DtrackPhi                   = dir.make<TH1F>("trackPhi"            ,    "#Delta trackPhi;#Delta track #phi;Entries", 100, -0.01, 0.01);            
  m_DtrackPPar                  = dir.make<TH1F>("trackPPar"           ,    "#Delta trackPPar;#Delta track PPar [GeV];Entries",100, -1.5, 1.5);           
  m_DtrackDeltaR                = dir.make<TH1F>("trackDeltaR"         ,    "#Delta trackDeltaR;#Delta track #DeltaR;Entries", 100, -0.15, 0.15);         
  m_DtrackPtRatio               = dir.make<TH1F>("trackPtRatio"        ,    "#Delta trackPtRatio;#Delta track p_{T} Ratio;Entries", 100, -0.1, 0.1); 
  m_DtrackPParRatio             = dir.make<TH1F>("trackPParRatio"      ,    "#Delta trackPParRatio;#Delta track P Par Ratio;Entries", 100, -0.01, 0.01);  

} 

TrackDeltaHists::~TrackDeltaHists() {} 

void TrackDeltaHists::Fill (const TrackData& track, const TrackData& trackM){
  float err3  = track.m_ip3dVal/track.m_ip3dSig;
  float errM3 = trackM.m_ip3dVal/trackM.m_ip3dSig;
  float err2  = track.m_ip2dVal/track.m_ip2dSig;
  float errM2 = trackM.m_ip2dVal/trackM.m_ip2dSig;
  m_zoomip2d          -> Fill(track.m_ip2dVal-trackM.m_ip2dVal);
  m_zoomip3d          -> Fill(track.m_ip3dVal-trackM.m_ip3dVal);
  m_Dip3d             -> Fill(track.m_ip3dVal-trackM.m_ip3dVal);
  m_Dip3d_sig         -> Fill(track.m_ip3dSig-trackM.m_ip3dSig);
  m_Dip3d_err         -> Fill(err3-errM3);
  m_Dip2d             -> Fill(track.m_ip2dVal-trackM.m_ip2dVal);
  m_Dip2d_sig         -> Fill(track.m_ip2dSig-trackM.m_ip2dSig);
  m_Dip2d_err         -> Fill(err2-errM2);
  m_DtrackDecayLenVal -> Fill(track.m_decayLenVal-trackM.m_decayLenVal);
  m_DtrackJetDistVal  -> Fill(track.m_jetDistVal-trackM.m_jetDistVal);
  m_DtrackPtRel       -> Fill(track.m_ptRel-trackM.m_ptRel);
  m_DtrackMomentum    -> Fill(track.m_momentum-trackM.m_momentum);
  m_DtrackEta         -> Fill(track.m_eta-trackM.m_eta);
  m_DtrackPhi         -> Fill(track.m_phi-trackM.m_phi);
  m_DtrackPPar        -> Fill(track.m_pPar-trackM.m_pPar);
  m_DtrackDeltaR      -> Fill(track.m_dR-trackM.m_dR);
  //  m_DtrackEtaRel      -> Fill(track.m_etaRel-trackM.m_etaRel);
  m_DtrackPtRatio     -> Fill(track.m_ptRatio-trackM.m_ptRatio);
  m_DtrackPParRatio   -> Fill(track.m_pParRatio-trackM.m_pParRatio);

  return;
};
