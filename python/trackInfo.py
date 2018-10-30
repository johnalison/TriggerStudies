import ROOT

class TrackData:
    
    def __init__(self,
                 Sip3dSig,
                 Sip3dVal,
                 Sip2dSig,
                 Sip2dVal,
                 DecayLenVal,
                 JetDistVal,
                 PtRel,
                 Momentum,
                 Eta,
                 PPar,
                 DeltaR,
                 PtRatio,
                 PParRatio,
             ):

        self.Sip3dSig = Sip3dSig
        self.Sip3dVal = Sip3dVal

        self.Sip2dSig = Sip2dSig
        self.Sip2dVal = Sip2dVal

        self.DecayLenVal           = DecayLenVal           
        #self.DecayLenSig           = DecayLenSig           
        self.JetDistVal            = JetDistVal            
        #self.JetDistSig            = JetDistSig            
        #self.GhostTrackWeight      = GhostTrackWeight      
        #self.GhostTrackDistSig     = GhostTrackDistSig     
        #self.GhostTrackDistVal     = GhostTrackDistVal     
        self.PtRel                 = PtRel
        self.Momentum              = Momentum              
        self.Eta                   = Eta                   
        #self.Phi                   = Phi                   
        #self.Charge                = Charge                
        self.PPar                  = PPar                  
        self.DeltaR                = DeltaR                
        self.PtRatio               = PtRatio               
        self.PParRatio             = PParRatio             
        #self.P0Par                 = P0Par                 
        #self.P0ParRatio            = P0ParRatio            
        #self.Chi2                  = Chi2                  
        #self.NTotalHits            = NTotalHits            
        #self.NPixelHits            = NPixelHits            

        self.matchedTrack  = None
        self.secondClosest = None
