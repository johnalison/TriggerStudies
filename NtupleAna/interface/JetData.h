// -*- C++ -*-

#if !defined(JetData_H)
#define JetData_H

namespace NtupleAna {


  class JetData {


  public:
    float m_pt         = 0;
    float m_eta        = 0;
    float m_phi        = 0;
    float m_mass       = 0;
    float m_deepcsv    = 0;
    float m_deepcsv_bb = 0;
    

//        float m_vertexNTracks                     =  vertexNTracks                    
//        float m_vertexMass                        =  vertexMass                       
//        float m_vertexJetDeltaR                   =  vertexJetDeltaR                  
//        float m_vertexFitProb                     =  vertexFitProb                    
//        float m_vertexEnergyRatio                 =  vertexEnergyRatio                
//        float m_vertexCategory                    =  vertexCategory                   
//        float m_vertexBoostOverSqrtJetPt          =  vertexBoostOverSqrtJetPt         
//        float m_trackJetPt                        =  trackJetPt
//        float m_trackSumJetEtRatio                =  trackSumJetEtRatio               
//        float m_trackSumJetDeltaR                 =  trackSumJetDeltaR                
//        float m_trackSip2dValAboveCharm           =  trackSip2dValAboveCharm          
//        float m_trackSip2dSigAboveCharm           =  trackSip2dSigAboveCharm          
//        float m_trackSip3dValAboveCharm           =  trackSip3dValAboveCharm          
//        float m_trackSip3dSigAboveCharm           =  trackSip3dSigAboveCharm          
//        float m_totalMultiplicity                 =  totalMultiplicity                
//        float m_photonMultiplicity                =  photonMultiplicity               
//        float m_photonEnergyFraction              =  photonEnergyFraction             
//        float m_neutralHadronMultiplicity         =  neutralHadronMultiplicity        
//        float m_neutralHadronEnergyFraction       =  neutralHadronEnergyFraction      
//        float m_neMult                            =  neMult                           
//        float m_neHadEF                           =  neHadEF                          
//        float m_neEmEF                            =  neEmEF                           
//        float m_muonMultiplicity                  =  muonMultiplicity                 
//        float m_muonEnergyFraction                =  muonEnergyFraction               
//        float m_mult                              =  mult                             
//        float m_muEF                              =  muEF                             
//        float m_massVertexEnergyFraction          =  massVertexEnergyFraction         
//        float m_jetNTracksEtaRel                  =  jetNTracksEtaRel                 
//        float m_jetNTracks                        =  jetNTracks                       
//        float m_jetNSelectedTracks                =  jetNSelectedTracks               
//        float m_jetNSecondaryVertices             =  jetNSecondaryVertices            
//        float m_hadronPhotonMultiplicity          =  hadronPhotonMultiplicity         
//        float m_hadronMultiplicity                =  hadronMultiplicity               
//        float m_flightDistance1dSig               =  flightDistance1dSig                             
//        float m_flightDistance1dVal               =  flightDistance1dVal                             
//        float m_flightDistance2dSig               =  flightDistance2dSig                             
//        float m_flightDistance2dVal               =  flightDistance2dVal                             
//        float m_flightDistance3dSig               =  flightDistance3dSig                             
//        float m_flightDistance3dVal               =  flightDistance3dVal              
//        float m_chargedHadronMultiplicity         =  chargedHadronMultiplicity        
//        float m_chargedHadronEnergyFraction       =  chargedHadronEnergyFraction
//        float m_chMult                            =  chMult                           
//        float m_chHadEF                           =  chHadEF                          
//        float m_chEmEF                            =  chEmEF                           
//        float m_partonFlavour                     =  partonFlavour
//        float m_hadronFlavour                     =  hadronFlavour

    JetData* matchedJet = nullptr;
    float match_dR   = -1;



  public:

	JetData(float pt,float eta,float phi,float mass,float deepcsv,float deepcsv_bb
              //   ,vertexNTracks                    
              //   ,vertexMass                       
              //   ,vertexJetDeltaR                  
              //   ,vertexFitProb                    
              //   ,vertexEnergyRatio                
              //   ,vertexCategory                   
              //   ,vertexBoostOverSqrtJetPt         
              //   ,trackJetPt               
              //   ,trackSumJetEtRatio               
              //   ,trackSumJetDeltaR                
              //   ,trackSip2dValAboveCharm          
              //   ,trackSip2dSigAboveCharm          
              //   ,trackSip3dValAboveCharm          
              //   ,trackSip3dSigAboveCharm          
              //   ,totalMultiplicity                
              //   ,photonMultiplicity               
              //   ,photonEnergyFraction             
              //   ,neutralHadronMultiplicity        
              //   ,neutralHadronEnergyFraction      
              //   ,neMult                           
              //   ,neHadEF                          
              //   ,neEmEF                           
              //   ,muonMultiplicity                 
              //   ,muonEnergyFraction               
              //   ,mult                             
              //   ,muEF                             
              //   ,massVertexEnergyFraction         
              //   ,jetNTracksEtaRel                 
              //   ,jetNTracks                       
              //   ,jetNSelectedTracks               
              //   ,jetNSecondaryVertices            
              //   ,hadronPhotonMultiplicity         
              //   ,hadronMultiplicity               
              //   ,flightDistance1dSig              
              //   ,flightDistance1dVal              
              //   ,flightDistance2dSig              
              //   ,flightDistance2dVal              
              //   ,flightDistance3dSig              
              //   ,flightDistance3dVal              
              //   ,chargedHadronMultiplicity        
              //   ,chargedHadronEnergyFraction
              //   ,chMult                           
              //   ,chHadEF                          
              //   ,chEmEF                           
              //   ,partonFlavour
              //   ,hadronFlavour
	      //
              //   ,trackSip3dSig,trackSip3dVal,trackSip2dSig,trackSip2dVal
              //   ,trackDecayLenVal           
              //   #,trackDecayLenSig           
              //   ,trackJetDistVal            
              //   ,trackJetDistSig            
              //   #,trackGhostTrackWeight      
              //   #,trackGhostTrackDistSig     
              //   #,trackGhostTrackDistVal     
              //   ,trackPtRel                 
              //   ,trackMomentum              
              //   ,trackEta                   
              //   ,trackPhi                   
              //   #,trackCharge                
              //   ,trackPPar                  
              //   ,trackDeltaR                
              //   ,trackEtaRel                
              //   ,trackPtRatio               
              //   ,trackPParRatio             
              //   #,trackP0Par                 
              //   #,trackP0ParRatio            
              //   ,trackChi2                  
              //   ,trackNTotalHits            
              //   ,trackNPixelHits            
		){
	  m_pt         = pt        ;
	  m_eta        = eta	 ;
	  m_phi        = phi	 ;
	  m_mass       = mass	 ;
	  m_deepcsv    = deepcsv	 ;
	  m_deepcsv_bb = deepcsv_bb;

        //float m_vertexNTracks                     =  vertexNTracks                    
        //float m_vertexMass                        =  vertexMass                       
        //float m_vertexJetDeltaR                   =  vertexJetDeltaR                  
        //float m_vertexFitProb                     =  vertexFitProb                    
        //float m_vertexEnergyRatio                 =  vertexEnergyRatio                
        //float m_vertexCategory                    =  vertexCategory                   
        //float m_vertexBoostOverSqrtJetPt          =  vertexBoostOverSqrtJetPt         
        //float m_trackJetPt                        =  trackJetPt
        //float m_trackSumJetEtRatio                =  trackSumJetEtRatio               
        //float m_trackSumJetDeltaR                 =  trackSumJetDeltaR                
        //float m_trackSip2dValAboveCharm           =  trackSip2dValAboveCharm          
        //float m_trackSip2dSigAboveCharm           =  trackSip2dSigAboveCharm          
        //float m_trackSip3dValAboveCharm           =  trackSip3dValAboveCharm          
        //float m_trackSip3dSigAboveCharm           =  trackSip3dSigAboveCharm          
        //float m_totalMultiplicity                 =  totalMultiplicity                
        //float m_photonMultiplicity                =  photonMultiplicity               
        //float m_photonEnergyFraction              =  photonEnergyFraction             
        //float m_neutralHadronMultiplicity         =  neutralHadronMultiplicity        
        //float m_neutralHadronEnergyFraction       =  neutralHadronEnergyFraction      
        //float m_neMult                            =  neMult                           
        //float m_neHadEF                           =  neHadEF                          
        //float m_neEmEF                            =  neEmEF                           
        //float m_muonMultiplicity                  =  muonMultiplicity                 
        //float m_muonEnergyFraction                =  muonEnergyFraction               
        //float m_mult                              =  mult                             
        //float m_muEF                              =  muEF                             
        //float m_massVertexEnergyFraction          =  massVertexEnergyFraction         
        //float m_jetNTracksEtaRel                  =  jetNTracksEtaRel                 
        //float m_jetNTracks                        =  jetNTracks                       
        //float m_jetNSelectedTracks                =  jetNSelectedTracks               
        //float m_jetNSecondaryVertices             =  jetNSecondaryVertices            
        //float m_hadronPhotonMultiplicity          =  hadronPhotonMultiplicity         
        //float m_hadronMultiplicity                =  hadronMultiplicity               
        //float m_flightDistance1dSig               =  flightDistance1dSig                             
        //float m_flightDistance1dVal               =  flightDistance1dVal                             
        //float m_flightDistance2dSig               =  flightDistance2dSig                             
        //float m_flightDistance2dVal               =  flightDistance2dVal                             
        //float m_flightDistance3dSig               =  flightDistance3dSig                             
        //float m_flightDistance3dVal               =  flightDistance3dVal              
        //float m_chargedHadronMultiplicity         =  chargedHadronMultiplicity        
        //float m_chargedHadronEnergyFraction       =  chargedHadronEnergyFraction
        //float m_chMult                            =  chMult                           
        //float m_chHadEF                           =  chHadEF                          
        //float m_chEmEF                            =  chEmEF                           
        //float m_partonFlavour                     =  partonFlavour
        //float m_hadronFlavour                     =  hadronFlavour

        //vec = ROOT.TLorentzVector()
        //vec.SetPtEtaPhiM(pt,eta,phi,mass)
	//
        //GetTracks(trackSip3dSig,
        //               trackSip3dVal,
        //               trackSip2dSig,
        //               trackSip2dVal,
        //               trackDecayLenVal,
        //               trackJetDistVal,
        //               trackJetDistSig,
        //               trackPtRel,
        //               trackMomentum,
        //               trackEta,
        //               trackPhi,
        //               trackPPar,
        //               trackDeltaR,
        //               trackPtRatio,
        //               trackPParRatio,
        //               trackChi2,
        //               trackNTotalHits,
        //               trackNPixelHits,
        //           )

	  
	}
	

	~JetData() {}; 
    
    //void GetTracks();
    
  };

}
#endif // JetData_H
