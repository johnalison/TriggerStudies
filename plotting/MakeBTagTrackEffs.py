import ROOT


ROOT.gROOT.SetBatch(True)

import sys
sys.path.insert(0, '../../')
import ROOTHelp.FancyROOTStyle


from optparse import OptionParser
p = OptionParser()
#p.add_option('--inputData',  type = 'string', dest = 'inFileData', help = 'intput File' )
p.add_option('--inputMC',  type = 'string', dest = 'inFileMC', help = 'intput File' )
p.add_option('--output', type = 'string', default = "jetLevelPlots", dest = 'outDir', help = 'output dir' )
p.add_option('--doCaloJets', action="store_true" )
p.add_option('--doPuppiJets', action="store_true" )
(o,a) = p.parse_args()

#from rocCurveUtils            import drawWaterMarks
#import rebinning
#from Rebinning import rebinningDB

#inFileData  = ROOT.TFile(o.inFileData,  "READ")
inFileMC    = ROOT.TFile(o.inFileMC,  "READ")

import os
if not os.path.exists(o.outDir):
    os.mkdir(o.outDir)


from JetLevelPlotUtils import makeEff, drawComp, getHist, drawStackCompRatio, makeStack, makeInverseTurnOn, make2DComp, makeInverseTurnOnAll,plotRatio

#plotRatio("nPV",    "Events",inFileData, "Data", inFileMC, "MC",xTitle="nPV", outDir=o.outDir,binning=1)


#
#  Offline Turnon curves:
#
#effBinning=5
vars = [

    "trackEta"       ,
    "ip2d"               ,
    "ip2d_err"           ,
    "ip2d_err_l"         ,
    "ip2d_l"             ,
    "ip2d_sig"           ,
    "ip2d_sig_l"         ,
    "ip3d"               ,
    "ip3d_err"           ,
    "ip3d_err_l"         ,
    "ip3d_l"             ,
    "ip3d_sig"           ,
    "ip3d_sig_l"         ,
    "trackChi2"          ,
    "trackDecayLenVal"   ,
    "trackDecayLenVal_l" ,
    "trackDeltaR"        ,
    "trackDeltaR_l"      ,
    "trackEta"           ,
    "trackEtaRel"        ,
    "trackIsFromV0"      ,
    "trackJetDistVal"    ,
    "trackMomentum"      ,
    "trackNPixelHits"    ,
    "trackNTotalHits"    ,
    "trackPPar"          ,
    "trackPParRatio"     ,
    "trackPhi"           ,
    "trackPt"            ,
    "trackPtRatio"       ,
    "trackPtRel"         ,
    "trackPt_logx"       ,



        ]



for v in vars:
    binning = 1

    if not o.doPuppiJets:
        eff_Matched = makeEff(v ,         ["offBTags_matched","offBTags"]          ,inFileMC,binning=binning)
        eff_Matched_noV0 = makeEff(v ,    ["offBTags_matched_noV0","offBTags_noV0"],inFileMC,binning=binning)

    if o.doCaloJets:
        effCalo_Matched = makeEff(v ,         ["offBTagsCalo_matched","offBTagsCalo"],inFileMC,binning=binning)
        effCalo_Matched_noV0 = makeEff(v ,    ["offBTagsCalo_matched_noV0","offBTagsCalo_noV0"],inFileMC,binning=binning)
    if o.doPuppiJets:
        effPuppi_Matched = makeEff(v ,         ["offBTags_matched","offBTags"],inFileMC,binning=binning)
        effPuppi_Matched_noV0 = makeEff(v ,    ["offBTags_matched_noV0","offBTags_noV0"],inFileMC,binning=binning)

    vBtag = "track"+v
    if v=="phi": vBtag = "trackPhi"
    if v=="eta": vBtag = "trackEta"
    if v in ["HasInnerPixHit","IsFromSV","NStripHits","PV","PVweight","SV","SVweight","algo","charge"]: pass #continue
    if v in ["ip2d","ip2d_l","ip2d_err","ip2d_err_l","ip2d_sig","ip2d_sig_l",
             "ip3d","ip3d_l","ip3d_err","ip3d_err_l","ip3d_sig","ip3d_sig_l",
             ]: vBtag = v


    print "Doing ",vBtag
    #eff_Matched_BTag = makeEff(vBtag ,    ["offBTags_matched","offBTags"],inFileMC,binning=1)
    #eff_Matched_BTag_noV0 = makeEff(vBtag ,    ["offBTags_matched_noV0","offBTags_noV0"],inFileMC,binning=1)

    yLeg = 0.93
    xLeg = 0.5

    if not o.doPuppiJets:
        drawComp("Eff_"+v,[(eff_Matched,"t#bar{t} MC (All Tracks)",ROOT.kBlack),
                           (eff_Matched_noV0,"t#bar{t} MC (After V0 veto)",ROOT.kRed),
                           #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                           #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                           ]
                 ,yTitle="Online Track Efficiency Relative to Offline",xTitle=eff_Matched.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
                 xMax=eff_Matched.GetXaxis().GetXmax(),
                 xMin=eff_Matched.GetXaxis().GetXmin()
                 )
    else:
        drawComp("Eff_"+v,[(effPuppi_Matched,"t#bar{t} MC (All Tracks)",ROOT.kBlack),
                           (effPuppi_Matched_noV0,"t#bar{t} MC (After V0 veto)",ROOT.kRed),
                           #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                           #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                           ]
                 ,yTitle="Online Track Efficiency Relative to Offline",xTitle=effPuppi_Matched.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
                 xMax=effPuppi_Matched.GetXaxis().GetXmax(),
                 xMin=effPuppi_Matched.GetXaxis().GetXmin()
                 )


    if o.doCaloJets:
        drawComp("EffCalo_"+v,[(effCalo_Matched,"t#bar{t} MC (All Tracks)",ROOT.kBlack),
                               (effCalo_Matched_noV0,"t#bar{t} MC (After V0 veto)",ROOT.kRed),
                               #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                               #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                               ]
                 ,yTitle="Online Track Efficiency Relative to Offline",xTitle=effCalo_Matched.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
                 xMax=effCalo_Matched.GetXaxis().GetXmax(),
                 xMin=effCalo_Matched.GetXaxis().GetXmin()
                 )


        drawComp("Eff_PVvsCalo_"+v,[(eff_Matched,"t#bar{t} MC (PF Jets)",ROOT.kBlack),
                                    (effCalo_Matched,"t#bar{t} MC (Calo Jets)",ROOT.kRed),
                                    #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                                    #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                                    ]
                 ,yTitle="Online Track Efficiency Relative to Offline",xTitle=eff_Matched.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
                 xMax=eff_Matched.GetXaxis().GetXmax(),
                 xMin=eff_Matched.GetXaxis().GetXmin()
                 )


    if not o.doPuppiJets:
        fake_Matched = makeEff(v ,        ["pfBTags_unmatched","pfBTags"],inFileMC,binning=1)
        drawComp("Fake_"+v,[(fake_Matched,"t#bar{t} MC ",ROOT.kBlack)]
                 ,yTitle="Online Track Fake-Rate Relative to Offline",xTitle=fake_Matched.GetXaxis().GetTitle(),outDir=o.outDir,yMax=0.4,yLeg=0.9,xLeg=0.6,
                 xMax=fake_Matched.GetXaxis().GetXmax(),
                 xMin=fake_Matched.GetXaxis().GetXmin()
                 )
    else:
        fake_MatchedPuppi = makeEff(v ,        ["puppiBTags_unmatched","puppiBTags"],inFileMC,binning=1)
        drawComp("Fake_"+v,[(fake_MatchedPuppi,"t#bar{t} MC ",ROOT.kBlack)]
                 ,yTitle="Online Track Fake-Rate Relative to Offline",xTitle=fake_MatchedPuppi.GetXaxis().GetTitle(),outDir=o.outDir,yMax=0.4,yLeg=0.9,xLeg=0.6,
                 xMax=fake_MatchedPuppi.GetXaxis().GetXmax(),
                 xMin=fake_MatchedPuppi.GetXaxis().GetXmin()
                 )

    if o.doCaloJets:
        fakeCalo_Matched = makeEff(v ,    ["caloTracks_unmatched","caloTracks"],inFileMC,binning=1)
        drawComp("FakeCalo_"+v,[(fake_Matched,"t#bar{t} MC ",ROOT.kBlack)]
                 ,yTitle="Online Track Fake-Rate Relative to Offline",xTitle=fakeCalo_Matched.GetXaxis().GetTitle(),outDir=o.outDir,yMax=0.4,yLeg=0.9,xLeg=0.6,
                 xMax=fakeCalo_Matched.GetXaxis().GetXmax(),
                 xMin=fakeCalo_Matched.GetXaxis().GetXmin()
                 )
