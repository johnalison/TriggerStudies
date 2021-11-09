import ROOT


ROOT.gROOT.SetBatch(True)
ROOT.gErrorIgnoreLevel = ROOT.kWarning


import sys
sys.path.insert(0, '../../')
import ROOTHelp.FancyROOTStyle

from JetLevelPlotUtils import makeEff, drawComp # , drawStackCompRatio, makeStack, makeInverseTurnOn, make2DComp, makeInverseTurnOnAll,plotRatio

def getOpts():
    from optparse import OptionParser
    p = OptionParser()
    #p.add_option('--inputData',  type = 'string', dest = 'inFileData', help = 'intput File' )
    p.add_option('--inputFile',  type = 'string', help = 'intput File' )
    p.add_option('--outDir', type = 'string', help = 'output dir' )
    p.add_option('--labName', type = 'string', default = "Reference,Monitored",  help = '' )
    #p.add_option('--doAlgoStudy', action="store_true" )
    (o,a) = p.parse_args()

    return o, a


def doTrackEffs():


    #
    #  Offline Turnon curves:
    #
    #effBinning=5
    vars = [
        "phi"            ,
        "Chi2",
        "DecayLenVal"    ,
        "DecayLenVal_l"  ,
        "DeltaR"         ,
        "DeltaR_l"       ,
        "Eta"            ,
        "EtaRel"            ,
        "HasInnerPixHit",
        "IsFromSV"       ,
        "IsFromV0"       ,
        "JetDistVal"     ,
        "Momentum"       ,
        "NPixelHits"     ,
        "NStripHits"     ,
        "NTotalHits"     ,
        "PPar"           ,
        "PParRatio"      ,
        "PV"             ,
        "PVweight"       ,
        "Phi"            ,
        "PtRatio"        ,
        "PtRel"          ,
        "Pt_logx"        ,
        "pt_s"        ,
        "pt_m"        ,
        "SV"             ,
        "SVweight"       ,
        "algo"           ,
        "origAlgo"           ,
        "charge"         ,
        "eta"           ,
        "ip2d"           ,
        "ip2d_err"       ,
        "ip2d_err_l"     ,
        "ip2d_l"         ,
        "ip2d_sig"       ,
        "ip2d_sig_l"     ,
        "ip3d"           ,
        "ip3d_err"       ,
        "ip3d_err_l"     ,
        "ip3d_l"         ,
        "ip3d_sig"       ,
        "ip3d_sig_l"     ,
        ]



    for v in vars:
        binning = 1

        eff_Matched_Ref = makeEff(v ,         ["offTracks_matched","offTracks"],inFileMC,binning=binning)
        eff_Matched_Mon = makeEff(v ,         ["pfTracks_matched","pfTracks"],inFileMC,binning=binning)
    
        vBtag = "track"+v
        if v=="phi": vBtag = "trackPhi"
        if v=="eta": vBtag = "trackEta"

        yLeg = 0.93
        xLeg = 0.5
    
        drawComp("Eff_"+v,[(eff_Matched_Ref,labName[0],ROOT.kBlack),
                           # (eff_Matched_noV0,"t#bar{t} MC (After V0 veto)",ROOT.kRed),
                           (eff_Matched_Mon,labName[1],ROOT.kRed),
                           #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                           #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                           ]
                 ,yTitle="Online Track Efficiency Relative to Offline",xTitle=eff_Matched_Ref.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
                 xMax=eff_Matched_Ref.GetXaxis().GetXmax(),
                 xMin=eff_Matched_Ref.GetXaxis().GetXmin()
                 )
    
    
    
    
        fake_Matched_Ref = makeEff(v ,        ["pfTracks_unmatched","pfTracks"],  inFileMC,binning=1)
        fake_Matched_Mon = makeEff(v ,        ["offTracks_unmatched","offTracks"],inFileMC,binning=1)
        drawComp("Fake_"+v,[(fake_Matched_Ref,labName[0],ROOT.kBlack),
                            (fake_Matched_Mon,labName[1],ROOT.kRed),
                            ]
                 ,yTitle="Online Track Fake-Rate Relative to Offline",xTitle=fake_Matched_Mon.GetXaxis().GetTitle(),outDir=o.outDir,yMax=0.4,yLeg=0.9,xLeg=0.6,
                 xMax=fake_Matched_Mon.GetXaxis().GetXmax(),
                 xMin=fake_Matched_Mon.GetXaxis().GetXmin()
                 )
    

    



if __name__ == "__main__":
    o, a = getOpts()

    labName = o.labName.split(",")

    #inFileData  = ROOT.TFile(o.inFileData,  "READ")
    inFileMC    = ROOT.TFile(o.inputFile,  "READ")

    import os
    if not os.path.exists(o.outDir):
        os.makedirs(o.outDir)


    doTrackEffs()
