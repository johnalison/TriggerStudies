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
outFile = ROOT.TFile(o.outDir+"/EffOnlineWrtOffline.root","RECREATE")


#
#  Offline Turnon curves:
#
#effBinning=5
vars = [
    "pt_s",
    "pt_m",
    "pt_l",
    "eta"            ,
    "matched_dRBjet",
    "matched_dRAll",
    ]

effRatios = [
        ("offJetsMedDeepFlav_matchedPFDeepCSV",  "offJetsMedDeepFlav_matchedPFJet", "PFDeepCSV"),
        ("offJetsMedDeepFlav_matchedPFCSV",      "offJetsMedDeepFlav_matchedPFJet", "PFCSV"),
        ("offJetsMedDeepFlav_matchedCaloDeepCSV","offJetsMedDeepFlav_matchedCaloJet", "CaloDeepCSV"),
        ("offJetsMedDeepFlav_matchedCaloCSV",    "offJetsMedDeepFlav_matchedCaloJet", "CaloCSV"),
        ]
        

for v in vars:
    binning = 1
    
    if v == "pt_m":
        binning = [0,10,20,30,40,50,60,70,80,90,100,120,140,160,200,250,300,350,400,500]
    if v == "pt_l":
        binning = [0,10,20,30,40,50,60,70,80,90,100,120,140,160,200,300,500,750,1000]
    if v in ["matched_dRAll","matched_dRBjet"] :
        binning = 4

    for config in effRatios:
        effNumName = config[0]
        effDenName = config[1]

        eff_Matched_1 = makeEff(v ,         [effNumName,     effDenName],         inFile1,  binning=binning)
        eff_Matched_1.SetName("Eff_"+o.name1+"_"+effNumName+"_"+v)
        eff_Matched_2 = makeEff(v ,         [effNumName,     effDenName],         inFile2,  binning=binning)
        eff_Matched_2.SetName("Eff_"+o.name2+"_"+effNumName+"_"+v)

        yLeg = 0.93
        xLeg = 0.5

        drawComp("Eff_"+config[2]+"_"+v,[(eff_Matched_1,o.name1,       ROOT.kBlack),
                           (eff_Matched_2,o.name2,  ROOT.kRed, ROOT.kOpenCircle),
                           #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                           #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                           ]
                 ,yTitle="Online BTag Efficiency Relative to Offline",xTitle=eff_Matched_1.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
                 xMax=eff_Matched_1.GetXaxis().GetXmax(),
                 xMin=eff_Matched_1.GetXaxis().GetXmin()
                 )


        outFile.cd()
        eff_Matched_1.Write()
        eff_Matched_2.Write()




