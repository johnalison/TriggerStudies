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
p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
p.add_option('--lumiText', default = "",  help = '' )
(o,a) = p.parse_args()

#from rocCurveUtils            import drawWaterMarks
#import rebinning
#from Rebinning import rebinningDB

inFile1  = ROOT.TFile(o.input1,"READ")
inFile2    = ROOT.TFile(o.input2,  "READ")

import os
if not os.path.exists(o.outDir):
    os.mkdir(o.outDir)


from JetLevelPlotUtils import makeEff, drawComp, drawCompRatioGraphs, getHist
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
    #"matched_dRBjet",
    #"matched_dRAll",
    ]

effRatios = [
    ("offJetsMedDeepCSV_matchedPFDeepCSV",   "offJetsMedDeepCSV_matchedPFJet",    "PFDeepCSV" ),
    ("offJetsMedDeepCSV_matchedPFCSV",       "offJetsMedDeepCSV_matchedPFJet",    "PFCSV" ),
    ("offJetsMedDeepCSV_matchedCaloCSV",     "offJetsMedDeepCSV_matchedCaloJet",  "CaloCSV" ),
    ("offJetsMedDeepCSV_matchedCaloDeepCSV", "offJetsMedDeepCSV_matchedCaloJet",  "CaloDeepCSV" ),
    ("offJetsMedDeepFlav_matchedPFDeepCSV",  "offJetsMedDeepFlav_matchedPFJet",   "PFDeepCSV_wrt_DeepFlav"),
    ("offJetsMedDeepFlav_matchedPFCSV",      "offJetsMedDeepFlav_matchedPFJet",   "PFCSV_wrt_DeepFlav"),
    ("offJetsMedDeepFlav_matchedCaloDeepCSV","offJetsMedDeepFlav_matchedCaloJet", "CaloDeepCSV_wrt_DeepFlav"),
    ("offJetsMedDeepFlav_matchedCaloCSV",    "offJetsMedDeepFlav_matchedCaloJet", "CaloCSV_wrt_DeepFlav"),
    ]
        

for v in vars:
    binning = 1

    if v == "pt_m":
        #binning = [0,10,20,30,40,50,60,70,80,90,100,120,140,160,200,250,300,350,400,500]
        binning = [0,10,20,30,40,50,60,70,80,90,100,120,140,160,200,250,300,500]
    if v == "pt_l":
        binning = [0,10,20,30,40,50,60,70,80,90,100,120,140,160,200,300,500,750,1000]
    if v in ["matched_dRAll","matched_dRBjet"] :
        binning = 4

    for config in effRatios:
        effNumName = config[0]
        effDenName = config[1]

        numHistOrigBinning = None
        if v == "pt_m":
            numHistOrigBinning = getHist(inFile1,effNumName, v,1)


        eff_Matched_1 = makeEff(v ,         [effNumName,     effDenName],         inFile1,  binning=binning, histForXBarycenterCalc=numHistOrigBinning)
        eff_Matched_1.SetName("Eff_"+o.name1+"_"+effNumName+"_"+v)
        eff_Matched_2 = makeEff(v ,         [effNumName,     effDenName],         inFile2,  binning=binning, histForXBarycenterCalc=numHistOrigBinning)
        eff_Matched_2.SetName("Eff_"+o.name2+"_"+effNumName+"_"+v)

        min = 0.601
        yLeg = 0.3
        if v == "pt_m":
            eff_Matched_1.GetXaxis().SetTitle("p_{T} [GeV]")
            eff_Matched_2.GetXaxis().SetTitle("p_{T} [GeV]")
            min = 0.501
            yLeg = 0.5
        xLeg = 0.2






        doRatio = True
        if doRatio:
            numHist = getHist(inFile1,effNumName,v,binning=binning)
            drawCompRatioGraphs("Eff_"+config[2]+"_"+v,[(eff_Matched_1,o.name1,       ROOT.kBlack),
                                                        (eff_Matched_2,o.name2,  ROOT.kRed, ROOT.kOpenCircle),
                                                        #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                                                        #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                                                        ],
                                ratioHistBinning=numHist.Clone(),
                                yTitle="Online BTag Efficiency Relative to Offline",xTitle=eff_Matched_1.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.06,yMin=min,yLeg=yLeg,xLeg=xLeg,
                                xMax=eff_Matched_1.GetXaxis().GetXmax(),
                                xMin=eff_Matched_1.GetXaxis().GetXmin(),
                                cmsText = o.cmsText,
                                lumiText = o.lumiText,
                                histForXBarycenterCalc = numHistOrigBinning
                                )
    
        else:
            drawComp("Eff_"+config[2]+"_"+v,[(eff_Matched_1,o.name1,       ROOT.kBlack),
                               (eff_Matched_2,o.name2,  ROOT.kRed, ROOT.kOpenCircle),
                               #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                               #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                               ]
                     ,yTitle="Online BTag Efficiency Relative to Offline",xTitle=eff_Matched_1.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.2,yLeg=yLeg,xLeg=xLeg,
                     xMax=eff_Matched_1.GetXaxis().GetXmax(),
                     xMin=eff_Matched_1.GetXaxis().GetXmin(),
                     cmsText = o.cmsText,
                     lumiText = o.lumiText,
                     )


        outFile.cd()
        eff_Matched_1.Write()
        eff_Matched_2.Write()




