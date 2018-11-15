import ROOT
from helpers import makeHist
from trackHists import TrackHists
from array import array

class TrackDeltaHists:

    def __init__(self,name,outFile):
        self.name = name
        self.thisDir = outFile.mkdir(self.name)
        self.dSip3dSig    = makeHist(self.thisDir, "dSip3dSig",   "#Delta Sip3dSig;#Delta Sip3dSig;Entries",       100,-10,10)
        self.dSip3dVal    = makeHist(self.thisDir, "dSip3dVal",   "#Delta Sip3dVal;#Delta Sip3dVal;Entries",       100,-0.4,0.4)
        self.zoomip3dVal  = makeHist(self.thisDir, "zoomip3dVal", "#Delta Sip3dVal;#Delta Sip3dVal;Entries",       100,-0.015,0.015)
        self.ip3dErr      = makeHist(self.thisDir, "ip3dErr",     "ip3d Val/Sig;ip3d Val/Sig;Entries",             100,-0.05,0.05)
        self.dSip2dSig    = makeHist(self.thisDir, "dSip2dSig",   "#Delta Sip2dSig;#Delta Sip2dSig;Entries",       100,-10,10)
        self.dSip2dVal    = makeHist(self.thisDir, "dSip2dVal",   "#Delta Sip2dVal;#Delta Sip2dVal;Entries",       100,-0.4,0.4)
        self.zoomip2dVal  = makeHist(self.thisDir, "zoomip2dVal", "#Delta Sip2dVal;#Delta Sip2dVal;Entries",       100,-0.015,0.015)
        self.ip2dErr      = makeHist(self.thisDir, "ip2dErr",     "ip2d Val/Sig;ip2d Val/Sig;Entries",             100,-0.05,0.05)
        self.dDecayLenVal = makeHist(self.thisDir, "dDecayLenVal","#Delta DecayLenVal;#Delta DecayLenVal;Entries", 100,-1,1)
        self.dJetDistVal  = makeHist(self.thisDir, "dJetDistVal", "#Delta JetDistVal;#Delta JetDistVal;Entries",   100,-0.1,0.1)
        self.dPtRel       = makeHist(self.thisDir, "dPtRel",      "#Delta PtRel;#Delta PtRel;Entries",             100,-1.5,1.5)
        self.dMomentum    = makeHist(self.thisDir, "dMomentum",   "#Delta Momentum;#Delta Momentum;Entries",       100,-1.5,1.5)
        self.dEta         = makeHist(self.thisDir, "dEta",        "#Delta Eta;#Delta Eta;Entries",                 100,-0.015,0.015)
        self.dPPar        = makeHist(self.thisDir, "dPPar",       "#Delta PPar;#Delta PPar;Entries",               100,-1.5,1.5)
        self.dDeltaR      = makeHist(self.thisDir, "dDeltaR",     "#Delta DeltaR;#Delta DeltaR;Entries",           100,-0.4,0.4)
        self.dPtRatio     = makeHist(self.thisDir, "dPtRatio",    "#Delta PtRatio;#Delta PtRatio;Entries",         100,-0.4,0.4)
        self.dPParRatio   = makeHist(self.thisDir, "dPParRatio",  "#Delta PParRatio;#Delta PParRatio;Entries",     100,-0.05,0.05)

    def Fill(self,offTrack,matchedTrack):
        d3Sig = offTrack.ip3dSig - matchedTrack.ip3dSig
        d3Val = offTrack.ip3dVal - matchedTrack.ip3dVal
        d2Sig = offTrack.ip2dSig - matchedTrack.ip2dSig
        d2Val = offTrack.ip2dVal - matchedTrack.ip2dVal
        self.dSip3dSig    .Fill(d3Sig)
        self.dSip3dVal    .Fill(d3Val)
        self.ip3dErr      .Fill(d3Val/d3Sig)
        self.ip2dErr      .Fill(d2Val/d2Sig)
        self.zoomip3dVal  .Fill(d3Val)
        self.zoomip2dVal  .Fill(d2Val)
        self.dSip2dSig    .Fill(d2Sig)
        self.dSip2dVal    .Fill(d2Val)
        self.dDecayLenVal .Fill(offTrack.decayLenVal - matchedTrack.decayLenVal)
        self.dJetDistVal  .Fill(offTrack.jetDistVal - matchedTrack.jetDistVal)
        self.dPtRel       .Fill(offTrack.ptRel - matchedTrack.ptRel)
        self.dMomentum    .Fill(offTrack.momentum - matchedTrack.momentum)
        self.dEta         .Fill(offTrack.eta - matchedTrack.eta)
        self.dPPar        .Fill(offTrack.pPar - matchedTrack.pPar)
        self.dDeltaR      .Fill(offTrack.dR - matchedTrack.dR)
        self.dPtRatio     .Fill(offTrack.ptRatio - matchedTrack.ptRatio)
        self.dPParRatio   .Fill(offTrack.pParRatio - matchedTrack.pParRatio)

    def Write(self,outFile):
        self.thisDir.cd()
        self.dSip3dSig    .Write()
        self.dSip3dVal    .Write()
        self.zoomip3dVal  .Write()
        self.ip3dErr      .Write()
        self.dSip2dSig    .Write()
        self.dSip2dVal    .Write()
        self.zoomip2dVal  .Write()
        self.ip2dErr      .Write()
        self.dDecayLenVal .Write()
        self.dJetDistVal  .Write()
        self.dPtRel       .Write()
        self.dMomentum    .Write()
        self.dEta         .Write()
        self.dPPar        .Write()
        self.dDeltaR      .Write()
        self.dPtRatio     .Write()
        self.dPParRatio   .Write()
        outFile           .cd()

