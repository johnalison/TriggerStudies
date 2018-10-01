import ROOT
from array import array


class JetData:

    def __init__(self,pt,eta,phi,mass,deepcsv,deepcsv_bb
                 ,vertexNTracks                    
                 ,vertexMass                       
                 ,vertexJetDeltaR                  
                 ,vertexFitProb                    
                 ,vertexEnergyRatio                
                 ,vertexCategory                   
                 ,vertexBoostOverSqrtJetPt         
                 ,trackJetPt               
                 ,trackSumJetEtRatio               
                 ,trackSumJetDeltaR                
                 ,trackSip2dValAboveCharm          
                 ,trackSip2dSigAboveCharm          
                 ,trackSip3dValAboveCharm          
                 ,trackSip3dSigAboveCharm          
                 ,totalMultiplicity                
                 ,photonMultiplicity               
                 ,photonEnergyFraction             
                 ,neutralHadronMultiplicity        
                 ,neutralHadronEnergyFraction      
                 ,neMult                           
                 ,neHadEF                          
                 ,neEmEF                           
                 ,muonMultiplicity                 
                 ,muonEnergyFraction               
                 ,mult                             
                 ,muEF                             
                 ,massVertexEnergyFraction         
                 ,jetNTracksEtaRel                 
                 ,jetNTracks                       
                 ,jetNSelectedTracks               
                 ,jetNSecondaryVertices            
                 ,hadronPhotonMultiplicity         
                 ,hadronMultiplicity               
                 ,flightDistance1dSig              
                 ,flightDistance1dVal              
                 ,flightDistance2dSig              
                 ,flightDistance2dVal              
                 ,flightDistance3dSig              
                 ,flightDistance3dVal              
                 ,chargedHadronMultiplicity        
                 ,chargedHadronEnergyFraction
                 ,chMult                           
                 ,chHadEF                          
                 ,chEmEF                           
                 ,trackSip3dSig,trackSip3dVal,trackSip2dSig,trackSip2dVal

                 ,trackDecayLenVal           
                 #,trackDecayLenSig           
                 ,trackJetDistVal            
                 #,trackJetDistSig            
                 #,trackGhostTrackWeight      
                 #,trackGhostTrackDistSig     
                 #,trackGhostTrackDistVal     
                 ,trackPtRel                 
                 ,trackMomentum              
                 ,trackEta                   
                 #,trackPhi                   
                 #,trackCharge                
                 ,trackPPar                  
                 ,trackDeltaR                
                 ,trackEtaRel                
                 ,trackPtRatio               
                 ,trackPParRatio             
                 #,trackP0Par                 
                 #,trackP0ParRatio            
                 #,trackChi2                  
                 #,trackNTotalHits            
                 #,trackNPixelHits            
                 ): 

        self.pt = pt
        self.eta = eta
        self.phi = phi
        self.mass = mass
        self.deepcsv = deepcsv
        self.deepcsv_bb = deepcsv_bb

        self.vertexNTracks                     =  vertexNTracks                    
        self.vertexMass                        =  vertexMass                       
        self.vertexJetDeltaR                   =  vertexJetDeltaR                  
        self.vertexFitProb                     =  vertexFitProb                    
        self.vertexEnergyRatio                 =  vertexEnergyRatio                
        self.vertexCategory                    =  vertexCategory                   
        self.vertexBoostOverSqrtJetPt          =  vertexBoostOverSqrtJetPt         
        self.trackJetPt                        =  trackJetPt
        self.trackSumJetEtRatio                =  trackSumJetEtRatio               
        self.trackSumJetDeltaR                 =  trackSumJetDeltaR                
        self.trackSip2dValAboveCharm           =  trackSip2dValAboveCharm          
        self.trackSip2dSigAboveCharm           =  trackSip2dSigAboveCharm          
        self.trackSip3dValAboveCharm           =  trackSip3dValAboveCharm          
        self.trackSip3dSigAboveCharm           =  trackSip3dSigAboveCharm          
        self.totalMultiplicity                 =  totalMultiplicity                
        self.photonMultiplicity                =  photonMultiplicity               
        self.photonEnergyFraction              =  photonEnergyFraction             
        self.neutralHadronMultiplicity         =  neutralHadronMultiplicity        
        self.neutralHadronEnergyFraction       =  neutralHadronEnergyFraction      
        self.neMult                            =  neMult                           
        self.neHadEF                           =  neHadEF                          
        self.neEmEF                            =  neEmEF                           
        self.muonMultiplicity                  =  muonMultiplicity                 
        self.muonEnergyFraction                =  muonEnergyFraction               
        self.mult                              =  mult                             
        self.muEF                              =  muEF                             
        self.massVertexEnergyFraction          =  massVertexEnergyFraction         
        self.jetNTracksEtaRel                  =  jetNTracksEtaRel                 
        self.jetNTracks                        =  jetNTracks                       
        self.jetNSelectedTracks                =  jetNSelectedTracks               
        self.jetNSecondaryVertices             =  jetNSecondaryVertices            
        self.hadronPhotonMultiplicity          =  hadronPhotonMultiplicity         
        self.hadronMultiplicity                =  hadronMultiplicity               
        self.flightDistance1dSig               =  flightDistance1dSig                             
        self.flightDistance1dVal               =  flightDistance1dVal                             
        self.flightDistance2dSig               =  flightDistance2dSig                             
        self.flightDistance2dVal               =  flightDistance2dVal                             
        self.flightDistance3dSig               =  flightDistance3dSig                             
        self.flightDistance3dVal               =  flightDistance3dVal              
        self.chargedHadronMultiplicity         =  chargedHadronMultiplicity        
        self.chargedHadronEnergyFraction       =  chargedHadronEnergyFraction
        self.chMult                            =  chMult                           
        self.chHadEF                           =  chHadEF                          
        self.chEmEF                            =  chEmEF                           


        self.vec = ROOT.TLorentzVector()
        self.vec.SetPtEtaPhiM(pt,eta,phi,mass)
        
        self.trackSip3dSig = trackSip3dSig
        self.trackSip3dVal = trackSip3dVal

        self.trackSip2dSig = trackSip2dSig
        self.trackSip2dVal = trackSip2dVal

        self.trackDecayLenVal           = trackDecayLenVal           
        #self.trackDecayLenSig           = trackDecayLenSig           
        self.trackJetDistVal            = trackJetDistVal            
        #self.trackJetDistSig            = trackJetDistSig            
        #self.trackGhostTrackWeight      = trackGhostTrackWeight      
        #self.trackGhostTrackDistSig     = trackGhostTrackDistSig     
        #self.trackGhostTrackDistVal     = trackGhostTrackDistVal     
        self.trackPtRel                 = trackPtRel                 
        self.trackMomentum              = trackMomentum              
        self.trackEta                   = trackEta                   
        #self.trackPhi                   = trackPhi                   
        #self.trackCharge                = trackCharge                
        self.trackPPar                  = trackPPar                  
        self.trackDeltaR                = trackDeltaR                
        self.trackEtaRel                = trackEtaRel                
        self.trackPtRatio               = trackPtRatio               
        self.trackPParRatio             = trackPParRatio             
        #self.trackP0Par                 = trackP0Par                 
        #self.trackP0ParRatio            = trackP0ParRatio            
        #self.trackChi2                  = trackChi2                  
        #self.trackNTotalHits            = trackNTotalHits            
        #self.trackNPixelHits            = trackNPixelHits            



        


#
# Separate File ? 
#
class JetDataHandler:

    def __init__(self,name,maxLenght = 40):
        self.name = name
        
        self.num     = array('i', [0])
        self.pt      = array('f',[0]*maxLenght)
        self.eta     = array('f',[0]*maxLenght)
        self.phi     = array('f',[0]*maxLenght)
        self.mass    = array('f',[0]*maxLenght)
        self.deepcsv = array('f',[0]*maxLenght)
        self.deepcsv_bb = array('f',[0]*maxLenght)


        self.vertexNTracks                      = array('f',[0]*maxLenght)
        self.vertexMass                         = array('f',[0]*maxLenght)
        self.vertexJetDeltaR                    = array('f',[0]*maxLenght)
        self.vertexFitProb                      = array('f',[0]*maxLenght)
        self.vertexEnergyRatio                  = array('f',[0]*maxLenght)
        self.vertexCategory                     = array('f',[0]*maxLenght)
        self.vertexBoostOverSqrtJetPt           = array('f',[0]*maxLenght)
        self.trackJetPt                         = array('f',[0]*maxLenght)
        self.trackSumJetEtRatio                 = array('f',[0]*maxLenght)
        self.trackSumJetDeltaR                  = array('f',[0]*maxLenght)
        self.trackSip3dValAboveCharm            = array('f',[0]*maxLenght)
        self.trackSip3dSigAboveCharm            = array('f',[0]*maxLenght)
        self.trackSip2dValAboveCharm            = array('f',[0]*maxLenght)
        self.trackSip2dSigAboveCharm            = array('f',[0]*maxLenght)
        self.totalMultiplicity                  = array('i',[0]*maxLenght)
        self.photonMultiplicity                 = array('i',[0]*maxLenght)
        self.photonEnergyFraction               = array('f',[0]*maxLenght)
        self.neutralHadronMultiplicity          = array('f',[0]*maxLenght)
        self.neutralHadronEnergyFraction        = array('f',[0]*maxLenght)
        self.neMult                             = array('f',[0]*maxLenght)
        self.neHadEF                            = array('f',[0]*maxLenght)
        self.neEmEF                             = array('f',[0]*maxLenght)
        self.muonMultiplicity                   = array('i',[0]*maxLenght)
        self.muonEnergyFraction                 = array('f',[0]*maxLenght)
        self.mult                               = array('f',[0]*maxLenght)
        self.muEF                               = array('f',[0]*maxLenght)
        self.massVertexEnergyFraction           = array('f',[0]*maxLenght)
        self.jetNTracksEtaRel                   = array('f',[0]*maxLenght)
        self.jetNTracks                         = array('f',[0]*maxLenght)
        self.jetNSelectedTracks                 = array('f',[0]*maxLenght)
        self.jetNSecondaryVertices              = array('f',[0]*maxLenght)
        self.hadronPhotonMultiplicity           = array('i',[0]*maxLenght)
        self.hadronMultiplicity                 = array('i',[0]*maxLenght)
        self.flightDistance1dSig                = array('f',[0]*maxLenght)
        self.flightDistance1dVal                = array('f',[0]*maxLenght)
        self.flightDistance2dSig                = array('f',[0]*maxLenght)
        self.flightDistance2dVal                = array('f',[0]*maxLenght)
        self.flightDistance3dSig                = array('f',[0]*maxLenght)
        self.flightDistance3dVal                = array('f',[0]*maxLenght)
        self.chargedHadronMultiplicity          = array('i',[0]*maxLenght)
        self.chargedHadronEnergyFraction        = array('f',[0]*maxLenght)
        self.chMult                             = array('i',[0]*maxLenght)
        self.chHadEF                            = array('f',[0]*maxLenght)
        self.chEmEF                             = array('f',[0]*maxLenght)
 
        # Eventually self.trackInfo = 
        self.trackSip3dSig = ROOT.std.vector('vector<float>')()
        self.trackSip3dVal = ROOT.std.vector('vector<float>')()

        self.trackSip2dSig = ROOT.std.vector('vector<float>')()
        self.trackSip2dVal = ROOT.std.vector('vector<float>')()

        self.trackDecayLenVal           = ROOT.std.vector('vector<float>')()
        #self.trackDecayLenSig           = ROOT.std.vector('vector<float>')()
        self.trackJetDistVal            = ROOT.std.vector('vector<float>')()
        #self.trackJetDistSig            = ROOT.std.vector('vector<float>')()
        #self.trackGhostTrackWeight      = ROOT.std.vector('vector<float>')()
        #self.trackGhostTrackDistSig     = ROOT.std.vector('vector<float>')()
        #self.trackGhostTrackDistVal     = ROOT.std.vector('vector<float>')()
        self.trackPtRel                 = ROOT.std.vector('vector<float>')()
        self.trackMomentum              = ROOT.std.vector('vector<float>')()
        self.trackEta                   = ROOT.std.vector('vector<float>')()
        #self.trackPhi                   = ROOT.std.vector('vector<float>')()
        #self.trackCharge                = ROOT.std.vector('vector<float>')()
        self.trackPPar                  = ROOT.std.vector('vector<float>')()
        self.trackDeltaR                = ROOT.std.vector('vector<float>')()
        self.trackEtaRel                = ROOT.std.vector('vector<float>')()
        self.trackPtRatio               = ROOT.std.vector('vector<float>')()
        self.trackPParRatio             = ROOT.std.vector('vector<float>')()
        #self.trackP0Par                 = ROOT.std.vector('vector<float>')()
        #self.trackP0ParRatio            = ROOT.std.vector('vector<float>')()
        #self.trackChi2                  = ROOT.std.vector('vector<float>')()
        #self.trackNTotalHits            = ROOT.std.vector('vector<float>')()
        #self.trackNPixelHits            = ROOT.std.vector('vector<float>')()

    def SetBranchAddress(self,intree):
        intree.SetBranchAddress( self.name+'_num',       self.num  )
        intree.SetBranchAddress( self.name+'_pt',        self.pt  )
        intree.SetBranchAddress( self.name+'_eta',       self.eta  )
        intree.SetBranchAddress( self.name+'_phi',       self.phi  )
        intree.SetBranchAddress( self.name+'_mass',      self.mass  )
        intree.SetBranchAddress( self.name+'_deepcsv',   self.deepcsv  )
        intree.SetBranchAddress( self.name+'_deepcsv_bb',   self.deepcsv_bb  )

        intree.SetBranchAddress( self.name+'_vertexNTracks'                     , self.vertexNTracks                     )
        intree.SetBranchAddress( self.name+'_vertexMass'                        , self.vertexMass                        )
        intree.SetBranchAddress( self.name+'_vertexJetDeltaR'                   , self.vertexJetDeltaR                   )
        intree.SetBranchAddress( self.name+'_vertexFitProb'                     , self.vertexFitProb                     )
        intree.SetBranchAddress( self.name+'_vertexEnergyRatio'                 , self.vertexEnergyRatio                 )
        intree.SetBranchAddress( self.name+'_vertexCategory'                    , self.vertexCategory                    )
        intree.SetBranchAddress( self.name+'_vertexBoostOverSqrtJetPt'          , self.vertexBoostOverSqrtJetPt          )
        intree.SetBranchAddress( self.name+'_trackJetPt'                        , self.trackJetPt                )
        intree.SetBranchAddress( self.name+'_trackSumJetEtRatio'                , self.trackSumJetEtRatio                )
        intree.SetBranchAddress( self.name+'_trackSumJetDeltaR'                 , self.trackSumJetDeltaR                 )
        intree.SetBranchAddress( self.name+'_trackSip2dValAboveCharm'           , self.trackSip2dValAboveCharm           )
        intree.SetBranchAddress( self.name+'_trackSip2dSigAboveCharm'           , self.trackSip2dSigAboveCharm           )
        intree.SetBranchAddress( self.name+'_trackSip3dValAboveCharm'           , self.trackSip3dValAboveCharm           )
        intree.SetBranchAddress( self.name+'_trackSip3dSigAboveCharm'           , self.trackSip3dSigAboveCharm           )
        intree.SetBranchAddress( self.name+'_totalMultiplicity'                 , self.totalMultiplicity                 )
        intree.SetBranchAddress( self.name+'_photonMultiplicity'                , self.photonMultiplicity                )
        intree.SetBranchAddress( self.name+'_photonEnergyFraction'              , self.photonEnergyFraction              )
        intree.SetBranchAddress( self.name+'_neutralHadronMultiplicity'         , self.neutralHadronMultiplicity         )
        intree.SetBranchAddress( self.name+'_neutralHadronEnergyFraction'       , self.neutralHadronEnergyFraction       )
        intree.SetBranchAddress( self.name+'_neMult'                            , self.neMult                            )
        intree.SetBranchAddress( self.name+'_neHadEF'                           , self.neHadEF                           )
        intree.SetBranchAddress( self.name+'_neEmEF'                            , self.neEmEF                            )
        intree.SetBranchAddress( self.name+'_muonMultiplicity'                  , self.muonMultiplicity                  )
        intree.SetBranchAddress( self.name+'_muonEnergyFraction'                , self.muonEnergyFraction                )
        intree.SetBranchAddress( self.name+'_mult'                              , self.mult                              )
        intree.SetBranchAddress( self.name+'_muEF'                              , self.muEF                              )
        intree.SetBranchAddress( self.name+'_massVertexEnergyFraction'          , self.massVertexEnergyFraction          )
        intree.SetBranchAddress( self.name+'_jetNTracksEtaRel'                  , self.jetNTracksEtaRel                  )
        intree.SetBranchAddress( self.name+'_jetNTracks'                        , self.jetNTracks                        )
        intree.SetBranchAddress( self.name+'_jetNSelectedTracks'                , self.jetNSelectedTracks                )
        intree.SetBranchAddress( self.name+'_jetNSecondaryVertices'             , self.jetNSecondaryVertices             )
        intree.SetBranchAddress( self.name+'_hadronPhotonMultiplicity'          , self.hadronPhotonMultiplicity          )
        intree.SetBranchAddress( self.name+'_hadronMultiplicity'                , self.hadronMultiplicity                )
        intree.SetBranchAddress( self.name+'_flightDistance1dSig'               , self.flightDistance1dSig               )
        intree.SetBranchAddress( self.name+'_flightDistance1dVal'               , self.flightDistance1dVal               )
        intree.SetBranchAddress( self.name+'_flightDistance2dSig'               , self.flightDistance2dSig               )
        intree.SetBranchAddress( self.name+'_flightDistance2dVal'               , self.flightDistance2dVal               )
        intree.SetBranchAddress( self.name+'_flightDistance3dSig'               , self.flightDistance3dSig               )
        intree.SetBranchAddress( self.name+'_flightDistance3dVal'               , self.flightDistance3dVal               )
        intree.SetBranchAddress( self.name+'_chargedHadronMultiplicity'         , self.chargedHadronMultiplicity         )
        intree.SetBranchAddress( self.name+'_chargedHadronEnergyFraction'       , self.chargedHadronEnergyFraction       )
        intree.SetBranchAddress( self.name+'_chMult'                            , self.chMult                            )
        intree.SetBranchAddress( self.name+'_chHadEF'                           , self.chHadEF                           )
        intree.SetBranchAddress( self.name+'_chEmEF'                            , self.chEmEF                            )

        intree.SetBranchAddress( self.name+'_trackSip3dSig', self.trackSip3dSig)
        intree.SetBranchAddress( self.name+'_trackSip3dVal', self.trackSip3dVal)
        intree.SetBranchAddress( self.name+'_trackSip2dSig', self.trackSip2dSig)
        intree.SetBranchAddress( self.name+'_trackSip2dVal', self.trackSip2dVal)

        intree.SetBranchAddress( self.name+'_trackDecayLenVal'           ,  self.trackDecayLenVal           )
        #intree.SetBranchAddress( self.name+'_trackDecayLenSig'           ,  self.trackDecayLenSig           )
        intree.SetBranchAddress( self.name+'_trackJetDistVal'            ,  self.trackJetDistVal            )
        #intree.SetBranchAddress( self.name+'_trackJetDistSig'            ,  self.trackJetDistSig            )
        #intree.SetBranchAddress( self.name+'_trackGhostTrackWeight'      ,  self.trackGhostTrackWeight      )
        #intree.SetBranchAddress( self.name+'_trackGhostTrackDistSig'     ,  self.trackGhostTrackDistSig     )
        #intree.SetBranchAddress( self.name+'_trackGhostTrackDistVal'     ,  self.trackGhostTrackDistVal     )
        intree.SetBranchAddress( self.name+'_trackPtRel'                 ,  self.trackPtRel                 )
        intree.SetBranchAddress( self.name+'_trackMomentum'              ,  self.trackMomentum              )
        intree.SetBranchAddress( self.name+'_trackEta'                   ,  self.trackEta                   )
        #intree.SetBranchAddress( self.name+'_trackPhi'                   ,  self.trackPhi                   )
        #intree.SetBranchAddress( self.name+'_trackCharge'                ,  self.trackCharge                )
        intree.SetBranchAddress( self.name+'_trackPPar'                  ,  self.trackPPar                  )
        intree.SetBranchAddress( self.name+'_trackDeltaR'                ,  self.trackDeltaR                )
        intree.SetBranchAddress( self.name+'_trackEtaRel'                ,  self.trackEtaRel                )
        intree.SetBranchAddress( self.name+'_trackPtRatio'               ,  self.trackPtRatio               )
        intree.SetBranchAddress( self.name+'_trackPParRatio'             ,  self.trackPParRatio             )
        #intree.SetBranchAddress( self.name+'_trackP0Par'                 ,  self.trackP0Par                 )
        #intree.SetBranchAddress( self.name+'_trackP0ParRatio'            ,  self.trackP0ParRatio            )
        #intree.SetBranchAddress( self.name+'_trackChi2'                  ,  self.trackChi2                  )
        #intree.SetBranchAddress( self.name+'_trackNTotalHits'            ,  self.trackNTotalHits            )
        #intree.SetBranchAddress( self.name+'_trackNPixelHits'            ,  self.trackNPixelHits            )
  

    def getJets(self):
        # thisJet = jetData(iJet) 
        jetList = []
        for iJet in range(self.num[0]):
            jetList.append(JetData(self.pt[iJet], 
                                   self.eta[iJet],
                                   self.phi[iJet],
                                   self.mass[iJet],
                                   self.deepcsv[iJet],
                                   self.deepcsv_bb[iJet],
                                   self.vertexNTracks                     [iJet],
                                   self.vertexMass                        [iJet],
                                   self.vertexJetDeltaR                   [iJet],
                                   self.vertexFitProb                     [iJet],
                                   self.vertexEnergyRatio                 [iJet],
                                   self.vertexCategory                    [iJet],
                                   self.vertexBoostOverSqrtJetPt          [iJet],
                                   self.trackJetPt                        [iJet],
                                   self.trackSumJetEtRatio                [iJet],
                                   self.trackSumJetDeltaR                 [iJet],
                                   self.trackSip2dValAboveCharm           [iJet],
                                   self.trackSip2dSigAboveCharm           [iJet],
                                   self.trackSip3dValAboveCharm           [iJet],
                                   self.trackSip3dSigAboveCharm           [iJet],
                                   self.totalMultiplicity                 [iJet],
                                   self.photonMultiplicity                [iJet],
                                   self.photonEnergyFraction              [iJet],
                                   self.neutralHadronMultiplicity         [iJet],
                                   self.neutralHadronEnergyFraction       [iJet],
                                   self.neMult                            [iJet],
                                   self.neHadEF                           [iJet],
                                   self.neEmEF                            [iJet],
                                   self.muonMultiplicity                  [iJet],
                                   self.muonEnergyFraction                [iJet],
                                   self.mult                              [iJet],
                                   self.muEF                              [iJet],
                                   self.massVertexEnergyFraction          [iJet],
                                   self.jetNTracksEtaRel                  [iJet],
                                   self.jetNTracks                        [iJet],
                                   self.jetNSelectedTracks                [iJet],
                                   self.jetNSecondaryVertices             [iJet],
                                   self.hadronPhotonMultiplicity          [iJet],
                                   self.hadronMultiplicity                [iJet],
                                   self.flightDistance1dSig               [iJet],
                                   self.flightDistance1dVal               [iJet],
                                   self.flightDistance2dSig               [iJet],
                                   self.flightDistance2dVal               [iJet],
                                   self.flightDistance3dSig               [iJet],
                                   self.flightDistance3dVal               [iJet],
                                   self.chargedHadronMultiplicity         [iJet],
                                   self.chargedHadronEnergyFraction       [iJet],
                                   self.chMult                            [iJet],
                                   self.chHadEF                           [iJet],
                                   self.chEmEF                            [iJet],

                                   self.trackSip3dSig[iJet],
                                   self.trackSip3dVal[iJet],
                                   self.trackSip2dSig[iJet],
                                   self.trackSip2dVal[iJet],

                                   self.trackDecayLenVal           [iJet],
                                   #self.trackDecayLenSig           [iJet],
                                   self.trackJetDistVal            [iJet],
                                   #self.trackJetDistSig            [iJet],
                                   #self.trackGhostTrackWeight      [iJet],
                                   #self.trackGhostTrackDistSig     [iJet],
                                   #self.trackGhostTrackDistVal     [iJet],
                                   self.trackPtRel                 [iJet],
                                   self.trackMomentum              [iJet],
                                   self.trackEta                   [iJet],
                                   #self.trackPhi                   [iJet],
                                   #self.trackCharge                [iJet],
                                   self.trackPPar                  [iJet],
                                   self.trackDeltaR                [iJet],
                                   self.trackEtaRel                [iJet],
                                   self.trackPtRatio               [iJet],
                                   self.trackPParRatio             [iJet],
                                   #self.trackP0Par                 [iJet],
                                   #self.trackP0ParRatio            [iJet],
                                   #self.trackChi2                  [iJet],
                                   #self.trackNTotalHits            [iJet],
                                   #self.trackNPixelHits            [iJet],
                                   )
                           )

        return jetList
