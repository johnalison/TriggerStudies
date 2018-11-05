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
                 jet = None,
             ):

        self.ip3dSig = Sip3dSig
        self.ip3dVal = Sip3dVal

        self.ip2dSig = Sip2dSig
        self.ip2dVal = Sip2dVal

        self.decayLenVal           = DecayLenVal           
        #self.DecayLenSig           = DecayLenSig           
        self.jetDistVal            = JetDistVal            
        #self.JetDistSig            = JetDistSig            
        #self.GhostTrackWeight      = GhostTrackWeight      
        #self.GhostTrackDistSig     = GhostTrackDistSig     
        #self.GhostTrackDistVal     = GhostTrackDistVal     
        self.ptRel                 = PtRel
        self.momentum              = Momentum              
        self.eta                   = Eta                   
        self.phi                   = None,
        #self.phi                   = Phi                   
        #self.Charge                = Charge                
        self.pPar                  = PPar                  
        self.dR                    = DeltaR                
        self.ptRatio               = PtRatio               
        self.pParRatio             = PParRatio             
        #self.P0Par                 = P0Par                 
        #self.P0ParRatio            = P0ParRatio            
        #self.Chi2                  = Chi2                  
        #self.NTotalHits            = NTotalHits            
        #self.NPixelHits            = NPixelHits            

        self.matchedTrack  = None
        self.secondClosest = None

        self.nMatches = 0

        self.jet = jet
        if self.jet: self.calcPhiOptions()


    def calcPhiOptions(self):
        dEta  = self.eta - self.jet.eta
        dPhi2 = self.dR**2 - dEta**2
        if dPhi2<0: dPhi2 = 0 #floating point rounding errors sometimes cause this
        dPhi  = (dPhi2)**0.5
        self.phi = [self.jet.phi + dPhi, self.jet.phi - dPhi]

    def dPhi(self,track2):
        absDeltaPhi = [abs(self.phi[0] - track2.phi[0]),
                       abs(self.phi[0] - track2.phi[1]),
                       abs(self.phi[1] - track2.phi[0]),
                       abs(self.phi[1] - track2.phi[1])]
        index = absDeltaPhi.index(min(absDeltaPhi))
        DeltaPhi = [self.phi[0] - track2.phi[0],
                    self.phi[0] - track2.phi[1],
                    self.phi[1] - track2.phi[0],
                    self.phi[1] - track2.phi[1]]

        return DeltaPhi[index]
