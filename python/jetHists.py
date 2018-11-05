import ROOT
from array import array


class JetHists:

    def __init__(self,name, outFile, light=False):
        
        self.name = name
        self.thisDir = outFile.mkdir(self.name)
        self.pt   = self.makeHist("pt","pt;P_{T} [GeV];Entries",  100,0,400)
        self.eta  = self.makeHist("eta","eta;jet #eta;Entries",100,-3,3)
        self.phi  = self.makeHist("phi","phi;jet #phi;Entries",100,-3.2,3.2)
        self.mass = self.makeHist("mass","mass;jet mass [GeV];Entries",100,-1,200)
        self.deepcsv = self.makeHist("deepcsv","deepcsv;deepcsv;Entries",100,-2,2)

        self.light = light
        if not self.light:
            self.deepcsv_bb = self.makeHist("deepcsv_bb","deepcsv_bb;deepcsv_bb;Entries",100,-2,2)
    
            self.nTrk = self.makeHist("nTrk","nTrk;nTracks;Entries",42,-1.5,40.5)
    
            self.ip3d_l = self.makeHist("ip3d_l","ip3d;IP3D [cm]",100,-0.2,0.2)
            self.ip3d   = self.makeHist("ip3d",  "ip3d;IP3D [cm]",100,-0.05,0.05)
    
            self.ip3d_sig_l = self.makeHist("ip3d_sig_l","ip3d sig;IP3D significance",100,-100,100)
            self.ip3d_sig   = self.makeHist("ip3d_sig",  "ip3d sig;IP3D significance",100,-10,10)
    
            self.ip3d_err_l = self.makeHist("ip3d_err_l","ip3d err;IP3D uncertianty [cm]",100,-0.01,0.1)
            self.ip3d_err   = self.makeHist("ip3d_err",  "ip3d err;IP3D uncertianty [cm]",100,-0.001,0.01)
    
            self.ip2d_l = self.makeHist("ip2d_l","ip2d;IP2D [cm]",100,-0.2,0.2)
            self.ip2d   = self.makeHist("ip2d",  "ip2d;IP2D [cm]",100,-0.05,0.05)

            
            nBinsPt = array("d",[0,2,4,6,8,10,15,20,30,40,60])
            self.ip2d_vs_pt   = ROOT.TH2F("ip2d_vs_pt",  "ip2d_vs_pt;P_T [GeV]; IP2D [cm]",len(nBinsPt)-1,nBinsPt,100,-0.03,0.03)
            self.ip2d_vs_pt.SetDirectory(self.thisDir)    


            nBinsEta = array("d",[0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5])
            self.ip2d_vs_eta   = ROOT.TH2F("ip2d_vs_eta",  "ip2d_vs_eta;|#eta|; IP2D [cm]",len(nBinsEta)-1,nBinsEta,100,-0.03,0.03)
            self.ip2d_vs_eta.SetDirectory(self.thisDir)    


            self.ip2d_sig_l = self.makeHist("ip2d_sig_l","ip2d sig;IP2D significance",100,-100,100)
            self.ip2d_sig   = self.makeHist("ip2d_sig",  "ip2d sig;IP2D significance",100,-10,10)
    
            self.ip2d_err_l = self.makeHist("ip2d_err_l","ip2d err;IP2D uncertianty [cm]",100,-0.01,0.1)
            self.ip2d_err   = self.makeHist("ip2d_err",  "ip2d err;IP2D uncertianty [cm]",100,-0.001,0.01)
    
            self.vertexNTracks                    = self.makeHist('vertexNTracks'                ,'vertexNTracks;nVertex Tracks;Entries'                 ,22, -2.5, 19.5)
            self.vertexMass                       = self.makeHist('vertexMass'                   ,'vertexMass;Vertex Mass [GeV]'                    ,100, -0.5, 50)
            self.vertexJetDeltaR                  = self.makeHist('vertexJetDeltaR'              ,'vertexJetDeltaR;Vertex-Jet #Delta R'               ,100, -0.01, 0.4)
            self.vertexFitProb                    = self.makeHist('vertexFitProb'                ,'vertexFitProb;Vertex Fit Prob'                 ,100, -50, 50)
            self.vertexEnergyRatio                = self.makeHist('vertexEnergyRatio'            ,'vertexEnergyRatio;Vertex Energy Fraction '             ,100, -0.1, 3)
            self.vertexCategory                   = self.makeHist('vertexCategory'               ,'vertexCategory;Vertex Category'                ,4 ,-1.5,2.5)
            self.vertexBoostOverSqrtJetPt         = self.makeHist('vertexBoostOverSqrtJetPt'     ,'vertexBoostOverSqrtJetPt;Vertex Boost/#sqrt{jet P_{T}}'      ,100, -0.1, 1.1)
            self.trackJetPt                       = self.makeHist('trackJetPt'           ,'trackJetPt;Track Jet P_{T} [GeV]'            ,100, 0,400)
            self.trackSumJetEtRatio               = self.makeHist('trackSumJetEtRatio'           ,'trackSumJetEtRatio;Track-jet/Jet E_{T} Ratio'            ,100, -0.1,1.5)
            self.trackSumJetDeltaR                = self.makeHist('trackSumJetDeltaR'            ,'trackSumJetDeltaR; Track-Jet - Jet #Delta R'             ,100, -0.1, 0.35)
            self.trackSip2dValAboveCharm          = self.makeHist('trackSip2dValAboveCharm'      ,'trackSip2dValAboveCharm;trackSip2dValAboveCharm'       ,100, -0.2, 0.2)
            self.trackSip2dSigAboveCharm          = self.makeHist('trackSip2dSigAboveCharm'      ,'trackSip3dSigAboveCharm;trackSip2SiglAboveCharm'       ,100, -50, 50)
            self.trackSip3dValAboveCharm          = self.makeHist('trackSip3dValAboveCharm'      ,'trackSip3dValAboveCharm;trackSip3dValAboveCharm'       ,100, -0.2, 0.2) 
            self.trackSip3dSigAboveCharm          = self.makeHist('trackSip3dSigAboveCharm'      ,'trackSip3dSigAboveCharm;trackSip3dSigAboveCharm'       ,100, -50, 50)
            self.totalMultiplicity                = self.makeHist('totalMultiplicity'            ,'totalMultiplicity;total multiplicity'             ,62, -1.5, 60.5)
            self.photonMultiplicity               = self.makeHist('photonMultiplicity'           ,'photonMultiplicity;photon multiplicity'            ,42, -1.5, 40.5)
            self.photonEnergyFraction             = self.makeHist('photonEnergyFraction'         ,'photonEnergyFraction;photon energy fraction'          ,100, -0.1,1.5)
            self.neutralHadronMultiplicity        = self.makeHist('neutralHadronMultiplicity'    ,'neutralHadronMultiplicity;neutralHadronMultiplicity'     ,22, -1.5, 20.5)
            self.neutralHadronEnergyFraction      = self.makeHist('neutralHadronEnergyFraction'  ,'neutralHadronEnergyFraction;neutralHadronEnergyFraction'   ,100, -0.1,1.5)
            self.neMult                           = self.makeHist('neMult'                       ,'neMult;neMult'                        ,62, -1.5, 60.5)
            self.neHadEF                          = self.makeHist('neHadEF'                      ,'neHadEF;neHadEF'                       ,100, -0.1,2.5)
            self.neEmEF                           = self.makeHist('neEmEF'                       ,'neEmEF;neEmEF'                        ,100, -0.1,2.5)
            self.muonMultiplicity                 = self.makeHist('muonMultiplicity'             ,'muonMultiplicity;muonMultiplicity'              ,12, -1.5, 10.5)
            self.muonEnergyFraction               = self.makeHist('muonEnergyFraction'           ,'muonEnergyFraction;muonEnergyFraction'            ,100, -0.1,1.5)
            self.mult                             = self.makeHist('mult'                         ,'mult;mult'                          ,62, -1.5, 60.5)
            self.muEF                             = self.makeHist('muEF'                         ,'muEF;muEF'                          ,100, -0.1,2.5)
            self.massVertexEnergyFraction         = self.makeHist('massVertexEnergyFraction'     ,'massVertexEnergyFraction;massVertexEnergyFraction'      ,100, -0.1,2.5)
            self.jetNTracksEtaRel                 = self.makeHist('jetNTracksEtaRel'             ,'jetNTracksEtaRel;jetNTracksEtaRel'              ,22, -1.5, 20.5)
            self.jetNTracks                       = self.makeHist('jetNTracks'                   ,'jetNTracks;Number Tracks'                    ,42, -1.5, 40.5)
            self.jetNSelectedTracks               = self.makeHist('jetNSelectedTracks'           ,'jetNSelectedTracks;Number Selected Tracks'            ,42, -1.5, 40.5)
            self.jetNSecondaryVertices            = self.makeHist('jetNSecondaryVertices'        ,'jetNSecondaryVertices;Number Secondary Vertices'         ,12, -1.5, 10.5)
            self.hadronPhotonMultiplicity         = self.makeHist('hadronPhotonMultiplicity'     ,'hadronPhotonMultiplicity;hadronPhotonMultiplicity'      ,62, -1.5, 60.5)
            self.hadronMultiplicity               = self.makeHist('hadronMultiplicity'           ,'hadronMultiplicity;hadronMultiplicity'            ,42, -1.5, 40.5)
            self.flightDistance1dSig              = self.makeHist('flightDistance1dSig'          ,'flightDistance1dSig;flightDistance1dSig'           ,100, -10, 150)
            self.flightDistance1dVal              = self.makeHist('flightDistance1dVal'          ,'flightDistance1dVal;flightDistance1dVal'           ,100, -0.1, 5)
            self.flightDistance2dSig              = self.makeHist('flightDistance2dSig'          ,'flightDistance2dSig;flightDistance2dSig'           ,100, -10, 150)
            self.flightDistance2dVal              = self.makeHist('flightDistance2dVal'          ,'flightDistance2dVal;flightDistance2dVal'           ,100, -0.1, 5)
            self.flightDistance3dSig              = self.makeHist('flightDistance3dSig'          ,'flightDistance3dSig;flightDistance3dSig'           ,100, -10, 150)
            self.flightDistance3dVal              = self.makeHist('flightDistance3dVal'          ,'flightDistance3dVal;flightDistance3dVal'           ,100, -0.1, 5)
            self.chargedHadronMultiplicity        = self.makeHist('chargedHadronMultiplicity'    ,'chargedHadronMultiplicity;chargedHadronMultiplicity'     ,42, -1.5, 40.5)
            self.chargedHadronEnergyFraction      = self.makeHist('chargedHadronEnergyFraction'  ,'chargedHadronEnergyFraction;chargedHadronEnergyFraction'   ,100, -0.1,1.5)
            self.chMult                           = self.makeHist('chMult'                       ,'chMult;chMult'                        ,42, -1.5, 40.5)
            self.chHadEF                          = self.makeHist('chHadEF'                      ,'chHadEF;chHadEF;Entries'                       ,100, -0.1,2.5)
            self.chEmEF                           = self.makeHist('chEmEF'                       ,'chEmEF;chEmEF;Entries'                        ,100, -0.1,2.5)
            self.partonFlavour                    = self.makeHist('partonFlavour'                ,'partonFlavour;partonFlavour;Entries'                        ,60, -30.5,29.5)
            self.hadronFlavour                    = self.makeHist('hadronFlavour'                ,'hadronFlavour;hadronFlavour;Entries'                        ,60, -30.5,29.5)
    
            self.trackDecayLenVal_l         = self.makeHist("trackDecayLenVal_l"    ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  5)
            self.trackDecayLenVal           = self.makeHist("trackDecayLenVal"    ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  0.5)
            self.trackJetDistVal            = self.makeHist("trackJetDistVal"     ,    "trackJetDistVal;trackJetDistVal [cm];Entries",  100, -0.1,0.01)      
            self.trackPtRel                 = self.makeHist("trackPtRel"          ,    "trackPtRel;track Pt Rel [GeV];Entries", 100, -0.1, 7)          
            self.trackMomentum              = self.makeHist("trackMomentum"       ,    "trackMomentum;track momentum [GeV];Entries", 100, -0.1, 60)       
            self.trackEta                   = self.makeHist("trackEta"            ,    "trackEta;track #eta;Entries", 100, -2.6, 2.6)            
            self.trackPhi                   = self.makeHist("trackPhi"            ,    "trackPhi;track #phi;Entries", 100, -3.2, 3.2)            
            self.trackPPar                  = self.makeHist("trackPPar"           ,    "trackPPar;track PPar [GeV];Entries",100, -0.1, 60)           
            self.trackDeltaR                = self.makeHist("trackDeltaR"         ,    "trackDeltaR;track #Delta R;Entries", 100, -0.1, 0.35)         
            self.trackEtaRel                = self.makeHist("trackEtaRel"         ,    "trackEtaRel;track Eta Rel;Entries", 100, 0, 7)         
            self.trackPtRatio               = self.makeHist("trackPtRatio"        ,    "trackPtRatio;track Pt Ratio;Entries", 100, -0.01, 0.3)        
            self.trackPParRatio             = self.makeHist("trackPParRatio"      ,    "trackPParRatio;track P Par Ratio;Entries", 100, 0.95, 1.02)      

            self.trackChi2                  = self.makeHist("trackChi2"            ,    "trackChi2;track Chi2;Entries", 100, -0.1, 6)            
            self.trackNTotalHits            = self.makeHist("trackNTotalHits"      ,    "trackNTotalHits;trackNTotalHits;Entries", 30, -0.5, 29.5)
            self.trackNPixelHits            = self.makeHist("trackNPixelHits"      ,    "trackNPixelHits;trackNPixelHits;Entries", 10, -0.5,  9.5)  
            self.trackHasInnerPixHit        = self.makeHist("trackHasInnerPixHit"  ,    "trackHasInnerPixHit;trackHasInnerPixHit;Entries", 2, -0.5,  1.5)  
    


    def makeHist(self,name,title,bins,low,high):
        h = ROOT.TH1F(name,title,bins,low,high)
        h.SetDirectory(self.thisDir)
        return h

        
    def Fill(self,jetInfo):
        self.pt  .Fill(jetInfo.pt)
        self.eta .Fill(jetInfo.eta)
        self.phi .Fill(jetInfo.phi)
        self.mass.Fill(jetInfo.mass)
        self.deepcsv.Fill(jetInfo.deepcsv)

        if not self.light:
            self.deepcsv_bb.Fill(jetInfo.deepcsv_bb)
    
    
            self.vertexNTracks                    .Fill(jetInfo.vertexNTracks                    )
            self.vertexMass                       .Fill(jetInfo.vertexMass                       )
            self.vertexJetDeltaR                  .Fill(jetInfo.vertexJetDeltaR                  )
            self.vertexFitProb                    .Fill(jetInfo.vertexFitProb                    )
            self.vertexEnergyRatio                .Fill(jetInfo.vertexEnergyRatio                )
            self.vertexCategory                   .Fill(jetInfo.vertexCategory                   )
            self.vertexBoostOverSqrtJetPt         .Fill(jetInfo.vertexBoostOverSqrtJetPt         )
            self.trackJetPt                       .Fill(jetInfo.trackJetPt               )
            self.trackSumJetEtRatio               .Fill(jetInfo.trackSumJetEtRatio               )
            if jetInfo.jetNSelectedTracks > 0:
                self.trackSumJetDeltaR                .Fill(jetInfo.trackSumJetDeltaR                )
            self.trackSip2dValAboveCharm          .Fill(jetInfo.trackSip2dValAboveCharm          )
            self.trackSip2dSigAboveCharm          .Fill(jetInfo.trackSip2dSigAboveCharm          )
            self.trackSip3dValAboveCharm          .Fill(jetInfo.trackSip3dValAboveCharm          )
            self.trackSip3dSigAboveCharm          .Fill(jetInfo.trackSip3dSigAboveCharm          )
            self.totalMultiplicity                .Fill(jetInfo.totalMultiplicity                )
            self.photonMultiplicity               .Fill(jetInfo.photonMultiplicity               )
            self.photonEnergyFraction             .Fill(jetInfo.photonEnergyFraction             )
            self.neutralHadronMultiplicity        .Fill(jetInfo.neutralHadronMultiplicity        )
            self.neutralHadronEnergyFraction      .Fill(jetInfo.neutralHadronEnergyFraction      )
            self.neMult                           .Fill(jetInfo.neMult                           )
            self.neHadEF                          .Fill(jetInfo.neHadEF                          )
            self.neEmEF                           .Fill(jetInfo.neEmEF                           )
            self.muonMultiplicity                 .Fill(jetInfo.muonMultiplicity                 )
            self.muonEnergyFraction               .Fill(jetInfo.muonEnergyFraction               )
            self.mult                             .Fill(jetInfo.mult                             )
            self.muEF                             .Fill(jetInfo.muEF                             )
            self.massVertexEnergyFraction         .Fill(jetInfo.massVertexEnergyFraction         )
            self.jetNTracksEtaRel                 .Fill(jetInfo.jetNTracksEtaRel                 )
            self.jetNTracks                       .Fill(jetInfo.jetNTracks                       )
            self.jetNSelectedTracks               .Fill(jetInfo.jetNSelectedTracks               )
            self.jetNSecondaryVertices            .Fill(jetInfo.jetNSecondaryVertices            )
            self.hadronPhotonMultiplicity         .Fill(jetInfo.hadronPhotonMultiplicity         )
            self.hadronMultiplicity               .Fill(jetInfo.hadronMultiplicity               )
            self.flightDistance1dSig              .Fill(jetInfo.flightDistance1dSig              )
            self.flightDistance1dVal              .Fill(jetInfo.flightDistance1dVal              )
            self.flightDistance2dSig              .Fill(jetInfo.flightDistance2dSig              )
            self.flightDistance2dVal              .Fill(jetInfo.flightDistance2dVal              )
            self.flightDistance3dSig              .Fill(jetInfo.flightDistance3dSig              )
            self.flightDistance3dVal              .Fill(jetInfo.flightDistance3dVal              )
            self.chargedHadronMultiplicity        .Fill(jetInfo.chargedHadronMultiplicity        )
            self.chargedHadronEnergyFraction      .Fill(jetInfo.chargedHadronEnergyFraction      )
            self.chMult                           .Fill(jetInfo.chMult                           )
            self.chHadEF                          .Fill(jetInfo.chHadEF                          )
            self.chEmEF                           .Fill(jetInfo.chEmEF                           )
            self.partonFlavour                    .Fill(jetInfo.partonFlavour                           )
            self.hadronFlavour                    .Fill(jetInfo.hadronFlavour                           )
    
    
            nTracks = len(jetInfo.trackSip3dVal)
            self.nTrk.Fill(nTracks)
    
            #print len(jetInfo.trackSip3dVal)#, len(jetInfo.trackSip2dVal)
            for iTrk in range(nTracks):
                this_ip3d = jetInfo.trackSip3dVal.at(iTrk)
                self.ip3d  .Fill(this_ip3d)
                self.ip3d_l.Fill(this_ip3d)
    
                this_ip3d_sig = jetInfo.trackSip3dSig.at(iTrk)
                self.ip3d_sig  .Fill(this_ip3d_sig)
                self.ip3d_sig_l.Fill(this_ip3d_sig)
    
                this_ip3d_err = this_ip3d/this_ip3d_sig
                self.ip3d_err  .Fill(this_ip3d_err)
                self.ip3d_err_l.Fill(this_ip3d_err)
    
    
                this_ip2d = jetInfo.trackSip2dVal.at(iTrk)
                self.ip2d  .Fill(this_ip2d)
                self.ip2d_l.Fill(this_ip2d)
    
                this_ip2d_sig = jetInfo.trackSip2dSig.at(iTrk)
                self.ip2d_sig  .Fill(this_ip2d_sig)
                self.ip2d_sig_l.Fill(this_ip2d_sig)
    
                this_ip2d_err = this_ip2d/this_ip2d_sig
                self.ip2d_err  .Fill(this_ip2d_err)
                self.ip2d_err_l.Fill(this_ip2d_err)

                this_trackMomentum = jetInfo.trackMomentum   .at(iTrk)
                self.ip2d_vs_pt.Fill(this_trackMomentum, this_ip2d)
                
                this_trackEta = jetInfo.trackEta        .at(iTrk)
                self.ip2d_vs_eta.Fill(abs(this_trackEta), this_ip2d)
    
                this_trackPhi = jetInfo.trackPhi        .at(iTrk)
    
                self.trackDecayLenVal_l   .Fill(jetInfo.trackDecayLenVal.at(iTrk))
                self.trackDecayLenVal     .Fill(jetInfo.trackDecayLenVal.at(iTrk))
                self.trackJetDistVal      .Fill(jetInfo.trackJetDistVal .at(iTrk))
                self.trackPtRel           .Fill(jetInfo.trackPtRel      .at(iTrk))
                self.trackMomentum        .Fill(this_trackMomentum) 
                self.trackEta             .Fill(this_trackEta)
                self.trackPhi             .Fill(this_trackPhi)
                self.trackPPar            .Fill(jetInfo.trackPPar       .at(iTrk))
                self.trackDeltaR          .Fill(jetInfo.trackDeltaR     .at(iTrk))
                #self.trackEtaRel          .Fill(jetInfo.trackEtaRel     .at(iTrk))
                self.trackPtRatio         .Fill(jetInfo.trackPtRatio    .at(iTrk))
                self.trackPParRatio       .Fill(jetInfo.trackPParRatio  .at(iTrk))

                self.trackChi2                  .Fill(jetInfo.trackChi2      .at(iTrk))
                self.trackNTotalHits            .Fill(jetInfo.trackNTotalHits.at(iTrk)) 
                self.trackNPixelHits            .Fill(jetInfo.trackNPixelHits.at(iTrk))
                self.trackHasInnerPixHit        .Fill(jetInfo.trackJetDistSig.at(iTrk))

    

    def Write(self,outFile):
        self.thisDir.cd()
        self.pt  .Write()
        self.eta .Write()
        self.phi .Write()
        self.mass.Write()
        self.deepcsv.Write()
        if not self.light:
            self.deepcsv_bb.Write()
    
            self.vertexNTracks                    .Write()
            self.vertexMass                       .Write()
            self.vertexJetDeltaR                  .Write()
            self.vertexFitProb                    .Write()
            self.vertexEnergyRatio                .Write()
            self.vertexCategory                   .Write()
            self.vertexBoostOverSqrtJetPt         .Write()
            self.trackJetPt               .Write()
            self.trackSumJetEtRatio               .Write()
            self.trackSumJetDeltaR                .Write()
            self.trackSip2dValAboveCharm          .Write()
            self.trackSip2dSigAboveCharm          .Write()
            self.trackSip3dValAboveCharm          .Write()
            self.trackSip3dSigAboveCharm          .Write()
            self.totalMultiplicity                .Write()
            self.photonMultiplicity               .Write()
            self.photonEnergyFraction             .Write()
            self.neutralHadronMultiplicity        .Write()
            self.neutralHadronEnergyFraction      .Write()
            self.neMult                           .Write()
            self.neHadEF                          .Write()
            self.neEmEF                           .Write()
            self.muonMultiplicity                 .Write()
            self.muonEnergyFraction               .Write()
            self.mult                             .Write()
            self.muEF                             .Write()
            self.massVertexEnergyFraction         .Write()
            self.jetNTracksEtaRel                 .Write()
            self.jetNTracks                       .Write()
            self.jetNSelectedTracks               .Write()
            self.jetNSecondaryVertices            .Write()
            self.hadronPhotonMultiplicity         .Write()
            self.hadronMultiplicity               .Write()
            self.flightDistance1dSig              .Write()
            self.flightDistance1dVal              .Write()
            self.flightDistance2dSig              .Write()
            self.flightDistance2dVal              .Write()
            self.flightDistance3dSig              .Write()
            self.flightDistance3dVal              .Write()
            self.chargedHadronMultiplicity        .Write()
            self.chargedHadronEnergyFraction      .Write()
            self.chMult                           .Write()
            self.chHadEF                          .Write()
            self.chEmEF                           .Write()
            self.partonFlavour                           .Write()
            self.hadronFlavour                           .Write()
    
            self.nTrk.Write()
    
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

        outFile.cd()
