import ROOT


ROOT.gROOT.SetBatch(True)

import sys
sys.path.insert(0, '../../')
import ROOTHelp.FancyROOTStyle


from optparse import OptionParser
p = OptionParser()
#p.add_option('--inputData',  type = 'string', dest = 'inFileData', help = 'intput File' )
p.add_option('--input1', help = 'intput File' )
p.add_option('--name1',  help = 'intput File' )
p.add_option('--input2', help = 'intput File' )
p.add_option('--name2',  help = 'intput File' )
p.add_option('--output', type = 'string', default = "jetLevelPlots", dest = 'outDir', help = 'output dir' )
p.add_option('--doAlgoStudy', action="store_true" )
p.add_option('--doCaloJets', action="store_true" )
(o,a) = p.parse_args()

#from rocCurveUtils            import drawWaterMarks
#import rebinning
#from Rebinning import rebinningDB

inFile1  = ROOT.TFile(o.input1,"READ")
inFile2    = ROOT.TFile(o.input2,  "READ")

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
    "phi"            ,
#        "eta"            ,
        "Chi2",
        "DecayLenVal"    ,
        "DecayLenVal_l"  ,
        "DeltaR"         ,
        "DeltaR_l"       ,
        "Eta"            ,
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


#        "trackMomentum"       ,
#        "ip2d",
#        "ip2d_l",
#        "ip3d",
#        "ip3d_l",
#        "ip2d_sig",
#        "ip2d_sig_l",
#        "ip3d_sig",
#        "ip3d_sig_l",
#        "ip2d_err",
#        "ip3d_err",
#        "trackHasInnerPixHit",
#        "trackNPixelHits",

#        "trackNTotalHits",

        ]

if o.doAlgoStudy:
    for i in range(30):
        vars += ["Eta_forAlgo"+str(i)]
        vars += ["Pt_forAlgo"+str(i)]

for v in vars:
    binning = 1
    if not v.find("Eta_forAlgo") == -1:
        binning = 4
    if not v.find("Pt_forAlgo") == -1:
        binning = [0,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,25,30,40,50]

        
    effNumName = "offTracks_matched"
    effDenName = "offTracks"

    eff_Matched_1 = makeEff(v ,         [effNumName,     effDenName],         inFile1,binning=binning)
    eff_Matched_2 = makeEff(v ,           [effNumName,     effDenName],         inFile2,  binning=binning)

    yLeg = 0.93
    xLeg = 0.5
    if v in  ["algo","origAlgo"]:
        yLeg = 0.4
        xLeg = 0.6

    drawComp("Eff_"+v,[(eff_Matched_1,o.name1,       ROOT.kBlack),
                       (eff_Matched_2,o.name2,  ROOT.kRed, ROOT.kOpenCircle),
                       #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                       #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                       ]
             ,yTitle="Online Track Efficiency Relative to Offline",xTitle=eff_Matched_1.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
             xMax=eff_Matched_1.GetXaxis().GetXmax(),
             xMin=eff_Matched_1.GetXaxis().GetXmin()
             )

    #
    #
    #

    if o.doCaloJets:
        effNumName = "offTracksCalo_matched"
        effDenName = "offTracksCalo"
    
        print v ,         [effNumName,     effDenName]
        eff_Matched_1 = makeEff(v ,         [effNumName,     effDenName],         inFile1,binning=binning)
        eff_Matched_2 = makeEff(v ,           [effNumName,     effDenName],         inFile2,  binning=binning)
    
        yLeg = 0.93
        xLeg = 0.5
        if v in  ["algo","origAlgo"]:
            yLeg = 0.4
            xLeg = 0.6
    
        drawComp("CaloEff_"+v,[(eff_Matched_1,o.name1,       ROOT.kBlack),
                               (eff_Matched_2,o.name2,  ROOT.kRed, ROOT.kOpenCircle),
                               #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                           #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                           ]
                 ,yTitle="Online Track Efficiency Relative to Offline",xTitle=eff_Matched_1.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
                 xMax=eff_Matched_1.GetXaxis().GetXmax(),
                 xMin=eff_Matched_1.GetXaxis().GetXmin()
                 )
    
        
        #
    #
    #

    fakeNumName = "pfTracks_unmatched"
    fakeDenName = "pfTracks"

    fake_Matched_1 = makeEff(v ,    [fakeNumName,  fakeDenName],inFile1,binning=1)
    fake_Matched_2   = makeEff(v ,    [fakeNumName,  fakeDenName],inFile2,  binning=1)

    drawComp("Fake_"+v,[(fake_Matched_1,o.name1,ROOT.kBlack),
                        (fake_Matched_2,o.name2,ROOT.kRed, ROOT.kOpenCircle),]
             ,yTitle="Online Track Fake-Rate Relative to Offline",xTitle=fake_Matched_1.GetXaxis().GetTitle(),outDir=o.outDir,yMax=0.4,yLeg=0.9,xLeg=0.6,
             xMax=fake_Matched_1.GetXaxis().GetXmax(),
             xMin=fake_Matched_1.GetXaxis().GetXmin()
             )


    #
    #
    #
    if o.doCaloJets:
        fakeNumName = "caloTracks_unmatched"
        fakeDenName = "caloTracks"
        
        fake_Matched_1 = makeEff(v ,    [fakeNumName,  fakeDenName],inFile1,binning=1)
        fake_Matched_2   = makeEff(v ,    [fakeNumName,  fakeDenName],inFile2,  binning=1)
        
        drawComp("CaloFake_"+v,[(fake_Matched_1,o.name1,ROOT.kBlack),
                            (fake_Matched_2,o.name2,ROOT.kRed, ROOT.kOpenCircle),]
                 ,yTitle="Online Track Fake-Rate Relative to Offline",xTitle=fake_Matched_1.GetXaxis().GetTitle(),outDir=o.outDir,yMax=0.4,yLeg=0.9,xLeg=0.6,
                 xMax=fake_Matched_1.GetXaxis().GetXmax(),
                 xMin=fake_Matched_1.GetXaxis().GetXmin()
                 )
        


