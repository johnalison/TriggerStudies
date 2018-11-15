import ROOT
import numpy as np

class TrackData:
    
    def __init__(self,
                 Sip3dSig,
                 Sip3dVal,
                 Sip2dSig,
                 Sip2dVal,
                 DecayLenVal,
                 JetDistVal,
                 JetDistSig,
                 PtRel,
                 Momentum,
                 Eta,
                 Phi,
                 PPar,
                 DeltaR,
                 PtRatio,
                 PParRatio,
                 Chi2,
                 NTotalHits,
                 NPixelHits,
                 jet = None,
             ):

        self.ip3dSig = Sip3dSig
        self.ip3dVal = Sip3dVal

        self.ip2dSig = Sip2dSig
        self.ip2dVal = Sip2dVal

        self.decayLenVal           = DecayLenVal           
        #self.DecayLenSig           = DecayLenSig           
        self.jetDistVal            = JetDistVal            
        self.JetDistSig            = JetDistSig            
        #self.GhostTrackWeight      = GhostTrackWeight      
        #self.GhostTrackDistSig     = GhostTrackDistSig     
        #self.GhostTrackDistVal     = GhostTrackDistVal     
        self.ptRel                 = PtRel
        self.momentum              = Momentum              
        self.eta                   = Eta                   
        self.pt                    = Momentum/np.cosh(self.eta)
        self.phi                   = Phi
        #self.phi                   = Phi                   
        #self.Charge                = Charge                
        self.pPar                  = PPar                  
        self.dR                    = DeltaR                
        self.ptRatio               = PtRatio               
        self.pParRatio             = PParRatio             
        #self.P0Par                 = P0Par                 
        #self.P0ParRatio            = P0ParRatio            
        self.Chi2                  = Chi2                  
        self.NTotalHits            = NTotalHits            
        self.NPixelHits            = NPixelHits            

        self.matchedTrack  = None
        self.secondClosest = None

        self.nMatches = 0

        self.jet = jet

        self.doPhiHack = False
        if self.doPhiHack:
            if self.jet: self.calcPhiOptions()

        self.vec = ROOT.TLorentzVector()
        self.vec.SetPtEtaPhiM(self.pt,self.eta,self.phi,0)



    def calcPhiOptions(self):
        dEta  = self.eta - self.jet.eta
        dPhi2 = self.dR**2 - dEta**2
        if dPhi2<0: dPhi2 = 0 #floating point rounding errors sometimes cause this
        dPhi  = (dPhi2)**0.5
        self.phi = [self.jet.phi + dPhi, self.jet.phi - dPhi]

    def dPhi(self,track2):
        if self.doPhiHack:
            DeltaPhi = [abs(self.phi[0] - track2.phi[0])%np.pi,
                        abs(self.phi[0] - track2.phi[1])%np.pi,
                        abs(self.phi[1] - track2.phi[0])%np.pi,
                        abs(self.phi[1] - track2.phi[1])%np.pi]
            index = DeltaPhi.index(min(absDeltaPhi))    
            return DeltaPhi[index]

        else:
            dPhi = abs(self.phi - track2.phi)%np.pi
            return dPhi
