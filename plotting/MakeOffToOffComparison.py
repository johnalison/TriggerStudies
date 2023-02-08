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


def doTrackEffs(**kwargs):

    file1           = kwargs["file1"]
    effDirName1Num  = kwargs["effDirName1Num"]
    effDirName1Den  = kwargs["effDirName1Den"]
    fakeDirName1Num = kwargs["fakeDirName1Num"]
    fakeDirName1Den = kwargs["fakeDirName1Den"]
    name1           = kwargs["name1"]

    file2           = kwargs["file2"]
    effDirName2Num  = kwargs["effDirName2Num"]
    effDirName2Den  = kwargs["effDirName2Den"]
    fakeDirName2Num = kwargs["fakeDirName2Num"]
    fakeDirName2Den = kwargs["fakeDirName2Den"]
    name2           = kwargs["name2"]

    outputDir           = kwargs["outputDir"]

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

        eff_Matched_1 = makeEff(v ,         [effDirName1Num, effDirName1Den],  file1,binning=binning)
        eff_Matched_2 = makeEff(v ,         [effDirName2Num, effDirName2Den],  file2,binning=binning)
    
        vBtag = "track"+v
        if v=="phi": vBtag = "trackPhi"
        if v=="eta": vBtag = "trackEta"

        yLeg = 0.93
        xLeg = 0.5
    
        drawComp("Eff_"+v,[(eff_Matched_1,name1,ROOT.kBlack),
                           (eff_Matched_2,name2,ROOT.kRed),
                           ]
                 ,yTitle="Relative Track Efficiency",xTitle=eff_Matched_1.GetXaxis().GetTitle(),outDir=outputDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
                 xMax=eff_Matched_1.GetXaxis().GetXmax(),
                 xMin=eff_Matched_1.GetXaxis().GetXmin()
                 )
    
    
    
    
        fake_Matched_1 = makeEff(v ,        [fakeDirName1Num,fakeDirName1Den],  file1,binning=1)
        fake_Matched_2 = makeEff(v ,        [fakeDirName2Num,fakeDirName2Den],  file2,binning=1)
        drawComp("Fake_"+v,[(fake_Matched_1,name1,ROOT.kBlack),
                            (fake_Matched_2,name2,ROOT.kRed),
                            ]
                 ,yTitle="Relative Track Fake-Rate",xTitle=fake_Matched_2.GetXaxis().GetTitle(),outDir=outputDir,yMax=0.4,yLeg=0.9,xLeg=0.6,
                 xMax=fake_Matched_2.GetXaxis().GetXmax(),
                 xMin=fake_Matched_2.GetXaxis().GetXmin()
                 )
    

    



if __name__ == "__main__":
    o, a = getOpts()

    labName = o.labName.split(",")

    #inFileData  = ROOT.TFile(o.inFileData,  "READ")
    inFileMC    = ROOT.TFile(o.inputFile,  "READ")


    import os
    if not os.path.exists(o.outDir):
        os.makedirs(o.outDir)


    doTrackEffs(file1=inFileMC, effDirName1Num="offTracks_matched",effDirName1Den = "offTracks",fakeDirName1Num="pfTracks_unmatched", fakeDirName1Den="pfTracks", name1=labName[0],
                file2=inFileMC, effDirName2Num="pfTracks_matched", effDirName2Den = "pfTracks", fakeDirName2Num="offTracks_unmatched",fakeDirName2Den="offTracks",name2=labName[1],
                outputDir = o.outDir)
    
                
