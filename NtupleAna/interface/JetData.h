// -*- C++ -*-

#if !defined(JetData_H)
#define JetData_H

#include <TLorentzVector.h>

#include "TriggerStudies/NtupleAna/interface/TrackData.h"

namespace NtupleAna {


  class JetData {


  public:
    float m_pt         = 0;
    float m_eta        = 0;
    float m_phi        = 0;
    float m_mass       = 0;
    float m_csv        = 0;
    float m_deepcsv    = 0;
    float m_deepcsv_bb = 0;
    float m_passesTightLeptVetoID = 0;    
    float m_lepOverlap04Tight = 0;
    
    float m_vertexNTracks                     =  0;
    float m_vertexMass                        =  0;
    float m_vertexJetDeltaR                   =  0;
    float m_vertexFitProb                     =  0;
    float m_vertexEnergyRatio                 =  0;
    float m_vertexCategory                    =  0;
    float m_vertexBoostOverSqrtJetPt          =  0;
    float m_trackJetPt                        =  0;
    float m_trackSumJetEtRatio                =  0;
    float m_trackSumJetDeltaR                 =  0;
    float m_trackSip2dValAboveCharm           =  0;
    float m_trackSip2dSigAboveCharm           =  0;
    float m_trackSip3dValAboveCharm           =  0;
    float m_trackSip3dSigAboveCharm           =  0;
    float m_totalMultiplicity                 =  0;
    float m_photonMultiplicity                =  0;
    float m_photonEnergyFraction              =  0;
    float m_neutralHadronMultiplicity         =  0;
    float m_neutralHadronEnergyFraction       =  0;
    float m_neMult                            =  0;
    float m_neHadEF                           =  0;
    float m_neEmEF                            =  0;
    float m_muonMultiplicity                  =  0;
    float m_muonEnergyFraction                =  0;
    float m_mult                              =  0;
    float m_muEF                              =  0;
    float m_massVertexEnergyFraction          =  0;
    float m_jetNTracksEtaRel                  =  0;
    float m_jetNTracks                        =  0;
    float m_jetNSelectedTracks                =  0;
    float m_jetNSecondaryVertices             =  0;
    float m_hadronPhotonMultiplicity          =  0;
    float m_hadronMultiplicity                =  0;
    float m_flightDistance1dSig               =  0;         
    float m_flightDistance1dVal               =  0;         
    float m_flightDistance2dSig               =  0;         
    float m_flightDistance2dVal               =  0;         
    float m_flightDistance3dSig               =  0;         
    float m_flightDistance3dVal               =  0;
    float m_chargedHadronMultiplicity         =  0;
    float m_chargedHadronEnergyFraction       =  0;
    float m_chMult                            =  0;
    float m_chHadEF                           =  0;
    float m_chEmEF                            =  0;
    float m_partonFlavour                     =  0;
    float m_hadronFlavour                     =  0;

    JetData* m_matchedJet = nullptr;
    float m_match_dR   = -1;

    TLorentzVector m_vec;

    std::vector<TrackData> m_tracks;

  public:

    JetData(float pt,float eta,float phi,float mass,float csv,float deepcsv,float deepcsv_bb, float passesTightLeptVetoID, float lepOverlap04Tight
		,float vertexNTracks                    
                ,float vertexMass                       
                ,float vertexJetDeltaR                  
                ,float vertexFitProb                    
                ,float vertexEnergyRatio                
                ,float vertexCategory                   
                ,float vertexBoostOverSqrtJetPt         
                ,float trackJetPt               
                ,float trackSumJetEtRatio               
                ,float trackSumJetDeltaR                
                ,float trackSip2dValAboveCharm          
                ,float trackSip2dSigAboveCharm          
                ,float trackSip3dValAboveCharm          
                ,float trackSip3dSigAboveCharm          
                ,float totalMultiplicity                
                ,float photonMultiplicity               
                ,float photonEnergyFraction             
                ,float neutralHadronMultiplicity        
                ,float neutralHadronEnergyFraction      
                ,float neMult                           
                ,float neHadEF                          
                ,float neEmEF                           
                ,float muonMultiplicity                 
                ,float muonEnergyFraction               
                ,float mult                             
                ,float muEF                             
                ,float massVertexEnergyFraction         
                ,float jetNTracksEtaRel                 
                ,float jetNTracks                       
                ,float jetNSelectedTracks               
                ,float jetNSecondaryVertices            
                ,float hadronPhotonMultiplicity         
                ,float hadronMultiplicity               
                ,float flightDistance1dSig              
                ,float flightDistance1dVal              
                ,float flightDistance2dSig              
                ,float flightDistance2dVal              
                ,float flightDistance3dSig              
                ,float flightDistance3dVal              
                ,float chargedHadronMultiplicity        
                ,float chargedHadronEnergyFraction
                ,float chMult                           
                ,float chHadEF                          
                ,float chEmEF                           
                ,float partonFlavour
		,float hadronFlavour
	      
		,std::vector<float> trackSip3dSig
		,std::vector<float> trackSip3dVal,std::vector<float> trackSip2dSig,std::vector<float> trackSip2dVal
		,std::vector<float> trackDecayLenVal           
		//,std::vector<float> trackDecayLenSig           
		,std::vector<float> trackJetDistVal            
		,std::vector<float> trackJetDistSig            
                //,std::vector<float> trackGhostTrackWeight      
		//,std::vector<float> trackGhostTrackDistSig     
		//,std::vector<float> trackGhostTrackDistVal     
                ,std::vector<float> trackPtRel                 
                ,std::vector<float> trackMomentum              
                ,std::vector<float> trackEta                   
                ,std::vector<float> trackPhi                   
                //,std::vector<float> trackCharge                
                ,std::vector<float> trackPPar                  
                ,std::vector<float> trackDeltaR                
                ,std::vector<float> trackEtaRel                
                ,std::vector<float> trackPtRatio               
                ,std::vector<float> trackPParRatio             
		//,std::vector<float> trackP0Par                 
		//,std::vector<float> trackP0ParRatio            
		,std::vector<float> trackChi2                  
		,std::vector<float> trackNTotalHits            
		,std::vector<float> trackNPixelHits            
		){
	  m_pt         = pt        ;
	  m_eta        = eta	 ;
	  m_phi        = phi	 ;
	  m_mass       = mass	 ;
	  m_csv        = csv	 ;
	  m_deepcsv    = deepcsv	 ;
	  m_deepcsv_bb = deepcsv_bb;
	  m_passesTightLeptVetoID = passesTightLeptVetoID;
	  m_lepOverlap04Tight = lepOverlap04Tight;

	  m_vertexNTracks                     =  vertexNTracks                   ;
          m_vertexMass                        =  vertexMass                      ;
          m_vertexJetDeltaR                   =  vertexJetDeltaR                 ;
          m_vertexFitProb                     =  vertexFitProb                   ;
          m_vertexEnergyRatio                 =  vertexEnergyRatio               ;
          m_vertexCategory                    =  vertexCategory                  ;
          m_vertexBoostOverSqrtJetPt          =  vertexBoostOverSqrtJetPt        ;
          m_trackJetPt                        =  trackJetPt			     ;
          m_trackSumJetEtRatio                =  trackSumJetEtRatio              ;
          m_trackSumJetDeltaR                 =  trackSumJetDeltaR               ;
          m_trackSip2dValAboveCharm           =  trackSip2dValAboveCharm         ;
          m_trackSip2dSigAboveCharm           =  trackSip2dSigAboveCharm         ;
          m_trackSip3dValAboveCharm           =  trackSip3dValAboveCharm         ;
          m_trackSip3dSigAboveCharm           =  trackSip3dSigAboveCharm         ;
          m_totalMultiplicity                 =  totalMultiplicity               ;
          m_photonMultiplicity                =  photonMultiplicity              ;
          m_photonEnergyFraction              =  photonEnergyFraction            ;
          m_neutralHadronMultiplicity         =  neutralHadronMultiplicity       ;
          m_neutralHadronEnergyFraction       =  neutralHadronEnergyFraction     ;
          m_neMult                            =  neMult                          ;
          m_neHadEF                           =  neHadEF                         ;
          m_neEmEF                            =  neEmEF                          ;
          m_muonMultiplicity                  =  muonMultiplicity                ;
          m_muonEnergyFraction                =  muonEnergyFraction              ;
          m_mult                              =  mult                            ;
          m_muEF                              =  muEF                            ;
          m_massVertexEnergyFraction          =  massVertexEnergyFraction        ;
          m_jetNTracksEtaRel                  =  jetNTracksEtaRel                ;
          m_jetNTracks                        =  jetNTracks                      ;
          m_jetNSelectedTracks                =  jetNSelectedTracks              ;
          m_jetNSecondaryVertices             =  jetNSecondaryVertices           ;
          m_hadronPhotonMultiplicity          =  hadronPhotonMultiplicity        ;
          m_hadronMultiplicity                =  hadronMultiplicity              ;
          m_flightDistance1dSig               =  flightDistance1dSig             ;               
          m_flightDistance1dVal               =  flightDistance1dVal             ;               
          m_flightDistance2dSig               =  flightDistance2dSig             ;               
          m_flightDistance2dVal               =  flightDistance2dVal             ;               
          m_flightDistance3dSig               =  flightDistance3dSig             ;               
          m_flightDistance3dVal               =  flightDistance3dVal             ;
          m_chargedHadronMultiplicity         =  chargedHadronMultiplicity       ;
          m_chargedHadronEnergyFraction       =  chargedHadronEnergyFraction     ;
          m_chMult                            =  chMult                          ;
          m_chHadEF                           =  chHadEF                         ;
          m_chEmEF                            =  chEmEF                          ;
          m_partonFlavour                     =  partonFlavour		     ;
          m_hadronFlavour                     =  hadronFlavour                   ;

	  m_vec.SetPtEtaPhiM(pt,eta,phi,mass);

	  m_tracks.clear();
	  unsigned int nTracks = trackSip3dSig.size();
	  for(unsigned int iTrack = 0; iTrack < nTracks; ++iTrack){
            m_tracks.push_back(TrackData(trackSip3dSig.at(iTrack),
                                         trackSip3dVal.at(iTrack),
                                         trackSip2dSig.at(iTrack),
                                         trackSip2dVal.at(iTrack),
                                         trackDecayLenVal.at(iTrack),
                                         trackJetDistVal.at(iTrack),
                                         trackJetDistSig.at(iTrack),
                                         trackPtRel.at(iTrack),
                                         trackMomentum.at(iTrack),
                                         trackEta.at(iTrack),
                                         trackPhi.at(iTrack),
                                         trackPPar.at(iTrack),
                                         trackDeltaR.at(iTrack),
                                         trackPtRatio.at(iTrack),
                                         trackPParRatio.at(iTrack),
                                         trackChi2.at(iTrack),
                                         trackNTotalHits.at(iTrack),
                                         trackNPixelHits.at(iTrack),
                                         this
					 )
			       );
	      }

	  
	};
	

	~JetData() {}; 
    
    
  };

}
#endif // JetData_H
