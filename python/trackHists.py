import ROOT
from array import array
from helpers import makeHist

class TrackHists:

    def __init__(self,name, directory, outFile = None):
        
        self.name = name
        if directory:
            self.thisDir = directory
        else:
            self.thisDir = outFile.mkdir(self.name)
        
        self.ip3d_l = makeHist(self.thisDir, "ip3d_l","ip3d;IP3D [cm]",100,-0.2,0.2)
        self.ip3d   = makeHist(self.thisDir, "ip3d",  "ip3d;IP3D [cm]",100,-0.05,0.05)
            
        self.ip3d_sig_l = makeHist(self.thisDir, "ip3d_sig_l","ip3d sig;IP3D significance",100,-100,100)
        self.ip3d_sig   = makeHist(self.thisDir, "ip3d_sig",  "ip3d sig;IP3D significance",100,-10,10)
            
        self.ip3d_err_l = makeHist(self.thisDir, "ip3d_err_l","ip3d err;IP3D uncertianty [cm]",100,-0.01,0.1)
        self.ip3d_err   = makeHist(self.thisDir, "ip3d_err",  "ip3d err;IP3D uncertianty [cm]",100,-0.001,0.01)
            
        self.ip2d_l = makeHist(self.thisDir, "ip2d_l","ip2d;IP2D [cm]",100,-0.2,0.2)
        self.ip2d   = makeHist(self.thisDir, "ip2d",  "ip2d;IP2D [cm]",100,-0.05,0.05)

            
        nBinsPt = array("d",[0,2,4,6,8,10,15,20,30,40,60])
        self.ip2d_vs_pt   = ROOT.TH2F("ip2d_vs_pt",  "ip2d_vs_pt;P_T [GeV]; IP2D [cm]",len(nBinsPt)-1,nBinsPt,100,-0.03,0.03)
        self.ip2d_vs_pt.SetDirectory(self.thisDir)    


        nBinsEta = array("d",[0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5])
        self.ip2d_vs_eta   = ROOT.TH2F("ip2d_vs_eta",  "ip2d_vs_eta;|#eta|; IP2D [cm]",len(nBinsEta)-1,nBinsEta,100,-0.03,0.03)
        self.ip2d_vs_eta.SetDirectory(self.thisDir)    


        self.ip2d_sig_l = makeHist(self.thisDir, "ip2d_sig_l","ip2d sig;IP2D significance",100,-100,100)
        self.ip2d_sig   = makeHist(self.thisDir, "ip2d_sig",  "ip2d sig;IP2D significance",100,-10,10)
        
        self.ip2d_err_l = makeHist(self.thisDir, "ip2d_err_l","ip2d err;IP2D uncertianty [cm]",100,-0.01,0.1)
        self.ip2d_err   = makeHist(self.thisDir, "ip2d_err",  "ip2d err;IP2D uncertianty [cm]",100,-0.001,0.01)
    
        self.trackDecayLenVal_l         = makeHist(self.thisDir, "trackDecayLenVal_l"  ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  5)
        self.trackDecayLenVal           = makeHist(self.thisDir, "trackDecayLenVal"    ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  0.5)
        self.trackJetDistVal            = makeHist(self.thisDir, "trackJetDistVal"     ,    "trackJetDistVal;trackJetDistVal [cm];Entries",  100, -0.1,0.01)      
        self.trackPtRel                 = makeHist(self.thisDir, "trackPtRel"          ,    "trackPtRel;track p_{T} Rel [GeV];Entries", 100, -0.1, 7)          
        self.trackMomentum              = makeHist(self.thisDir, "trackMomentum"       ,    "trackMomentum;track momentum [GeV];Entries", 60, 0, 60)       

        binsPt = []
        for bin in range(28):
            binsPt.append(0.9*1.24**bin)
        binsPt = array("d",binsPt)
        self.trackPt_logx               = ROOT.TH1F("trackPt_logx", "trackPt;track p_{T} [GeV];Entries", len(binsPt)-1, binsPt)
        self.trackPt_logx.SetDirectory(self.thisDir)

        self.trackEta                   = makeHist(self.thisDir, "trackEta"            ,    "trackEta;track #eta;Entries", 100, -2.6, 2.6)            
        self.trackPhi                   = makeHist(self.thisDir, "trackPhi"            ,    "trackPhi;track #phi;Entries", 100, -3.2, 3.2)            
        self.trackPPar                  = makeHist(self.thisDir, "trackPPar"           ,    "trackPPar;track PPar [GeV];Entries",60, 0, 60)           
        self.trackDeltaR                = makeHist(self.thisDir, "trackDeltaR"         ,    "trackDeltaR;track #DeltaR;Entries", 160, -0.05, 0.35)         
        self.trackEtaRel                = makeHist(self.thisDir, "trackEtaRel"         ,    "trackEtaRel;track Eta Rel;Entries", 100, 0, 7)         
        self.trackPtRatio               = makeHist(self.thisDir, "trackPtRatio"        ,    "trackPtRatio;track p_{T} Ratio;Entries", 100, -0.01, 0.3) 
        self.trackPParRatio             = makeHist(self.thisDir, "trackPParRatio"      ,    "trackPParRatio;track P Par Ratio;Entries", 100, 0.95, 1.02)  

        self.trackChi2                  = makeHist(self.thisDir, "trackChi2"            ,    "trackChi2;track Chi2;Entries", 100, -0.1, 6)            
        self.trackNTotalHits            = makeHist(self.thisDir, "trackNTotalHits"      ,    "trackNTotalHits;trackNTotalHits;Entries", 30, -0.5, 29.5)
        self.trackNPixelHits            = makeHist(self.thisDir, "trackNPixelHits"      ,    "trackNPixelHits;trackNPixelHits;Entries", 10, -0.5,  9.5)  
        self.trackHasInnerPixHit        = makeHist(self.thisDir, "trackHasInnerPixHit"  ,    "trackHasInnerPixHit;trackHasInnerPixHit;Entries", 2, -0.5,  1.5)  


        self.track_nMatches = makeHist(self.thisDir, "track_nMatches", "track_nMatches;# of matched tracks;Entries", 6, -0.5, 5.5)

        self.track_matched_dip2d     = makeHist(self.thisDir, "track_matched_dip2d"    ,    "track_matched_dip2d;IP2D-IP2D^{matched} [cm];Entries",100,-0.05,0.05)
        self.track_matched_dPtRel    = makeHist(self.thisDir, "track_matched_dPtRel"   ,    "track_matched_dPtRel;p_{T}^{Rel}-p_{T}^{Rel, matched} [GeV];Entries", 100, -5, 5)
        self.track_matched_dMomentum = makeHist(self.thisDir, "track_matched_dMomentum",    "track_matched_dMomentum;p_{T}-p_{T}^{matched} [GeV];Entries", 500, -10, 10)
        self.track_matched_dEta      = makeHist(self.thisDir, "track_matched_dEta"     ,    "track_matched_dEta;#eta-#eta^{matched};Entries", 500, -0.1, 0.1)            
        self.track_matched_dEta_s    = makeHist(self.thisDir, "track_matched_dEta_s"   ,    "track_matched_dEta;#eta-#eta^{matched};Entries", 500, -0.01, 0.01)            
        self.track_matched_dPhi      = makeHist(self.thisDir, "track_matched_dPhi"     ,    "track_matched_dPhi;#phi-#phi^{matched};Entries", 500, -0.1, 0.1)            
        self.track_matched_dR        = makeHist(self.thisDir, "track_matched_dR"       ,    "track_matched_dR;#DeltaR(track, matched track);Entries", 500, -0.05, 1.2)
        self.track_matched_dR_s      = makeHist(self.thisDir, "track_matched_dR_s"     ,    "track_matched_dR;#DeltaR(track, matched track);Entries", 340, -0.005, 0.08)

        self.track_matched_dEta_vs_dMomentum = ROOT.TH2F("track_matched_dEta_vs_dMomentum", "dEta_vs_dMomentum;#eta-#eta^{matched};p_{T}-p_{T}^{matched} [GeV]",100,-0.01,0.01,100,-5,5)
        self.track_matched_dEta_vs_dMomentum.SetDirectory(self.thisDir)
        self.track_matched_dEta_vs_dPhi = ROOT.TH2F("track_matched_dEta_vs_dPhi", "dEta_vs_dPhi;#eta-#eta^{matched};#phi-#phi^{matched}",120,-0.006,0.006,120,-0.012,0.012)
        self.track_matched_dEta_vs_dPhi.SetDirectory(self.thisDir)

        self.track_secondClosest_dEta      = makeHist(self.thisDir, "track_secondClosest_dEta",         "track_matched_dEta2;#eta-#eta^{second closest};Entries", 500, -0.1, 0.1)
        self.track_secondClosest_dEta_s    = makeHist(self.thisDir, "track_secondClosest_dEta_s",       "track_matched_dEta2;#eta-#eta^{second closest};Entries", 500, -0.01, 0.01)
        self.track_secondClosest_dMomentum = makeHist(self.thisDir, "track_secondClosest_dMomentum",    "track_secondClosest_dMomentum;p_{T}-p_{T}^{second closest} [GeV];Entries", 500, -10, 10)
        self.track_secondClosest_dR        = makeHist(self.thisDir, "track_secondClosest_dR"       ,    "track_secondClosest_dR;#DeltaR(matched track, secondClosest track);Entries", 500, -0.05, 1.2)
        self.track_secondClosest_dR_s      = makeHist(self.thisDir, "track_secondClosest_dR_s"     ,    "track_secondClosest_dR;#DeltaR(matched track, secondClosest track);Entries", 340, -0.005, 0.08)
        self.track_secondClosest_dEta_vs_dMomentum = ROOT.TH2F("track_secondClosest_dEta_vs_dMomentum", "dEta_vs_dMomentum;#eta-#eta^{secondClosest};p_{T}-p_{T}^{secondClosest} [GeV]",100,-0.01,0.01,100,-5,5)
        self.track_secondClosest_dEta_vs_dMomentum.SetDirectory(self.thisDir)
        self.track_dEta12 = makeHist(self.thisDir, "track_dEta12", "track_dEta12;#eta^{matched}-#eta^{second closest};Entries", 500, -0.1, 0.1)
  

    def Fill(self, track):
        self.ip3d  .Fill(track.ip3dVal)
        self.ip3d_l.Fill(track.ip3dVal)
        
        self.ip3d_sig  .Fill(track.ip3dSig)
        self.ip3d_sig_l.Fill(track.ip3dSig)
        
        this_ip3d_err = track.ip3dVal/track.ip3dSig
        self.ip3d_err  .Fill(this_ip3d_err)
        self.ip3d_err_l.Fill(this_ip3d_err)
        
    
        self.ip2d  .Fill(track.ip2dVal)
        self.ip2d_l.Fill(track.ip2dVal)
        
        self.ip2d_sig  .Fill(track.ip2dSig)
        self.ip2d_sig_l.Fill(track.ip2dSig)
        
        this_ip2d_err = track.ip2dVal/track.ip2dSig
        self.ip2d_err  .Fill(this_ip2d_err)
        self.ip2d_err_l.Fill(this_ip2d_err)

        self.ip2d_vs_pt.Fill(     track.momentum, track.ip2dVal)
        self.ip2d_vs_eta.Fill(abs(track.eta)    , track.ip2dVal)
        

        self.trackDecayLenVal_l   .Fill(track.decayLenVal)
        self.trackDecayLenVal     .Fill(track.decayLenVal)
        self.trackJetDistVal      .Fill(track.jetDistVal )
        self.trackPtRel           .Fill(track.ptRel      )
        self.trackMomentum        .Fill(track.momentum   ) 
        self.trackPt_logx         .Fill(track.momentum   ) 
        self.trackEta             .Fill(track.eta        )
        self.trackPhi             .Fill(track.phi        )
        self.trackPPar            .Fill(track.pPar       )
        self.trackDeltaR          .Fill(track.dR         )
        #self.trackEtaRel          .Fill(track.etaRel     )
        self.trackPtRatio         .Fill(track.ptRatio    )
        self.trackPParRatio       .Fill(track.pParRatio  )

        self.trackChi2                  .Fill(track.Chi2      )
        self.trackNTotalHits            .Fill(track.NTotalHits) 
        self.trackNPixelHits            .Fill(track.NPixelHits)
        self.trackHasInnerPixHit        .Fill(track.JetDistSig)


        if track.matchedTrack:
            self.track_matched_dip2d    .Fill(track.ip2dVal  - track.matchedTrack.ip2dVal)
            self.track_matched_dPtRel   .Fill(track.ptRel    - track.matchedTrack.ptRel)
            self.track_matched_dMomentum.Fill(track.momentum - track.matchedTrack.momentum) 
            self.track_matched_dEta     .Fill(track.eta      - track.matchedTrack.eta)
            self.track_matched_dEta_s   .Fill(track.eta      - track.matchedTrack.eta)
            self.track_matched_dPhi     .Fill(track.dPhi(track.matchedTrack))
            matched_dPhi = track.dPhi(track.matchedTrack)
            matched_dR   = ( (track.eta-track.matchedTrack.eta)**2 + matched_dPhi**2 )**0.5
            self.track_matched_dR       .Fill(matched_dR)
            self.track_matched_dR_s     .Fill(matched_dR)

            self.track_matched_dEta_vs_dMomentum.Fill(track.eta - track.matchedTrack.eta, track.momentum - track.matchedTrack.momentum)
            self.track_matched_dEta_vs_dPhi     .Fill(track.eta - track.matchedTrack.eta, matched_dPhi)

        if track.secondClosest:
            self.track_secondClosest_dEta     .Fill(track.eta      - track.secondClosest.eta)
            self.track_secondClosest_dEta_s   .Fill(track.eta      - track.secondClosest.eta)
            self.track_secondClosest_dMomentum.Fill(track.momentum - track.secondClosest.momentum) 
            secondClosest_dR = ( (track.eta-track.secondClosest.eta)**2 + track.dPhi(track.secondClosest)**2 )**0.5
            self.track_secondClosest_dR       .Fill(secondClosest_dR)
            self.track_secondClosest_dR_s     .Fill(secondClosest_dR)
            self.track_secondClosest_dEta_vs_dMomentum.Fill(track.eta - track.secondClosest.eta, track.momentum - track.secondClosest.momentum)

            self.track_dEta12.Fill(track.matchedTrack.eta - track.secondClosest.eta)

    def FillMatchStats(self, track):
        self.track_nMatches.Fill(track.nMatches)

    def Write(self, outFile=None):
        self.thisDir.cd()
    
        self.ip3d_l.Write()
        self.ip3d  .Write()
        
        self.ip3d_sig_l.Write()
        self.ip3d_sig  .Write()
    
        self.ip3d_err_l.Write()
        self.ip3d_err  .Write()
    
    
        self.ip2d_l.Write()
        self.ip2d  .Write()
        
        self.ip2d_sig_l.Write()
        self.ip2d_sig  .Write()
        
        self.ip2d_err_l.Write()
        self.ip2d_err  .Write()

        self.ip2d_vs_pt.Write()
        self.ip2d_vs_eta.Write()
    
        self.trackDecayLenVal_l   .Write()
        self.trackDecayLenVal     .Write()
        self.trackJetDistVal      .Write()        
        self.trackPtRel           .Write()
        self.trackMomentum        .Write()
        self.trackPt_logx         .Write()
        self.trackEta             .Write()
        self.trackPhi             .Write()
        self.trackPPar            .Write()
        self.trackDeltaR          .Write()
        self.trackEtaRel          .Write()
        self.trackPtRatio         .Write()
        self.trackPParRatio       .Write()

        self.trackChi2            .Write()
        self.trackNTotalHits      .Write()
        self.trackNPixelHits      .Write()
        self.trackHasInnerPixHit  .Write()

        self.track_nMatches.Write()
    
        self.track_matched_dip2d    .Write()
        self.track_matched_dPtRel   .Write()
        self.track_matched_dMomentum.Write()
        self.track_matched_dEta     .Write()
        self.track_matched_dEta_s   .Write()
        self.track_matched_dPhi     .Write()
        self.track_matched_dR       .Write()
        self.track_matched_dR_s     .Write()
        self.track_matched_dEta_vs_dMomentum.Write()
        self.track_matched_dEta_vs_dPhi     .Write()

        self.track_secondClosest_dEta  .Write()
        self.track_secondClosest_dEta_s.Write()
        self.track_secondClosest_dMomentum.Write()
        self.track_secondClosest_dR       .Write()
        self.track_secondClosest_dR_s     .Write()
        self.track_secondClosest_dEta_vs_dMomentum.Write()
        
        self.track_dEta12.Write()

        if outFile: outFile.cd()
