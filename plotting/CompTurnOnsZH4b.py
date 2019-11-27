
import ROOT


ROOT.gROOT.SetBatch(True)

import OfficialAtlasStyle

from optparse import OptionParser
p = OptionParser()
#p.add_option('--inputData',  type = 'string', dest = 'inFileData', help = 'intput File' )
p.add_option('--input', help = 'intput File' )
p.add_option('--name',  help = 'intput File' )
p.add_option('--output', type = 'string', default = "jetLevelPlots", dest = 'outDir', help = 'output dir' )
(o,a) = p.parse_args()

#from rocCurveUtils            import drawWaterMarks
#import rebinning
#from Rebinning import rebinningDB

inFile  = ROOT.TFile(o.input,"READ")

import os
if not os.path.exists(o.outDir):
    os.mkdir(o.outDir)

outFile = ROOT.TFile(o.outDir+"/EffOnlineWrtOffline.root","RECREATE")

from JetLevelPlotUtils import makeEff, drawComp, getHist, drawStackCompRatio, makeStack, makeInverseTurnOn, make2DComp, makeInverseTurnOnAll,plotRatio

#plotRatio("nPV",    "Events",inFileData, "Data", inFileMC, "MC",xTitle="nPV", outDir=o.outDir,binning=1)


#plot(["hT30_pass_4b","hT30_incl_4b"],"HtTurnOn",doratio=1,bayesRatio=1)

effPairs = [
    #["ht330_pass",   "ht330_incl"] ,
    #["ht330_pass_3b","ht330_incl_3b"] ,
    #["ht330_pass_4b","ht330_incl_4b"] ,


    #["ht330_3tag/ht330_3tag_pass",      "ht330_3tag/ht330_3tag_incl"] ,            

    #["ht330_3tag_pass_3b",   "ht330_3tag_incl_3b"] ,            
    #["ht330_3tag_pass_4b",   "ht330_3tag_incl_4b"] ,            
    #
    #["ht330_sel_pass",      "ht330_sel_incl"] ,            
    #["ht330_sel_pass_3b",   "ht330_sel_incl_3b"] ,            
    #["ht330_sel_pass_4b",   "ht330_sel_incl_4b"] ,            

    #["ht330_sel_noSubSet/ht330_sel_noSubSet_pass",    "ht330_sel_noSubSet/ht330_sel_noSubSet_incl"],
    #["ht330_sel_noSubSet_pass_3b", "ht330_sel_noSubSet_incl_3b"],
    #["ht330_sel_noSubSet_pass_4b", "ht330_sel_noSubSet_incl_4b"],

#    ["ht330_sel_3tag_pass",      "ht330_sel_3tag_incl"] ,            
#    ["ht330_sel_3tag_pass_3b",   "ht330_sel_3tag_incl_3b"] ,            
#    ["ht330_sel_3tag_pass_4b",   "ht330_sel_3tag_incl_4b"] ,            
    
    
    #["ht330_L1OR_pass", "ht330_L1OR_incl"],
    #
    #["L1OR_pass",   "L1OR_incl"] ,
    #
    #["j3_4j_pass",    "j3_4j_incl"],
    #["j3_4j_pass_3b", "j3_4j_incl_3b"],
    #["j3_4j_pass_4b", "j3_4j_incl_4b"],
    #
    #["j3_4j_wrt_HT_3j_pass", "j3_4j_wrt_HT_3j_incl"], 
    #["j3_4j_wrt_HT_3j_pass_3b", "j3_4j_wrt_HT_3j_incl_3b"], 
    #["j3_4j_wrt_HT_3j_pass_4b", "j3_4j_wrt_HT_3j_incl_4b"], 

    #["hT30_h330_l320","hT30_all"],

    ["j40_l40_vs_j40",["matchedPt_h40_l40","allPt"],["matchedPt_h40","allPt"]],
    ["j45_l40_vs_j45",["matchedPt_h45_l40","allPt"],["matchedPt_h45","allPt"]],
    ["j60_l55_vs_j60",["matchedPt_h60_l55","allPt"],["matchedPt_h60","allPt"]],
    ["j75_l70_vs_j75",["matchedPt_h75_l70","allPt"],["matchedPt_h75","allPt"]],


    ["j40_vs_4thJetEvent",["j3_4j/j3_4j_pass_3b","j3_4j/j3_4j_incl_3b"],["matchedPt_h40","allPt"]],
    ["j45_vs_3rdJetEvent",["j2_4j/j2_4j_pass_3b","j2_4j/j2_4j_incl_3b"],["matchedPt_h45","allPt"]],
    ["j60_vs_2ndJetEvent",["j1_4j/j1_4j_pass_3b","j1_4j/j1_4j_incl_3b"],["matchedPt_h60","allPt"]],
    ["j75_vs_1stJetEvent",["j0_4j/j0_4j_pass_3b","j0_4j/j0_4j_incl_3b"],["matchedPt_h75","allPt"]],

    ["j40_l40_vs_4thJetEvent",["j3_4j/j3_4j_pass_3b","j3_4j/j3_4j_incl_3b"],["matchedPt_h40_l40","allPt"]],
    ["j45_l40_vs_3rdJetEvent",["j2_4j/j2_4j_pass_3b","j2_4j/j2_4j_incl_3b"],["matchedPt_h45_l40","allPt"]],
    ["j60_l55_vs_2ndJetEvent",["j1_4j/j1_4j_pass_3b","j1_4j/j1_4j_incl_3b"],["matchedPt_h60_l55","allPt"]],
    ["j75_l70_vs_1stJetEvent",["j0_4j/j0_4j_pass_3b","j0_4j/j0_4j_incl_3b"],["matchedPt_h75_l70","allPt"]],

    ["ht330_l320_vs_ht330",["hT30_h330_l320","hT30_all"],["hT30_h330","hT30_all"]],
    ["ht330_l320_vs_htEvent",["hT30_h330_l320","hT30_all"],["ht_4j/ht_4j_pass_3b","ht_4j/ht_4j_incl_3b"]],
    ["ht330_vs_htEvent",["hT30_h330","hT30_all"],["ht_4j/ht_4j_pass_3b","ht_4j/ht_4j_incl_3b"]],
    ["ht330_EM_4j_vs_4j_3b",["ht_4j_em/ht_4j_em_pass_4b","ht_4j_em/ht_4j_em_incl_4b"],["ht_4j_3b_em/ht_4j_3b_em_pass_4b","ht_4j_3b_em/ht_4j_3b_em_incl_4b"]],
    ["ht330_EM_4j_vs_ht330",["ht_4j_em/ht_4j_em_pass_4b","ht_4j_em/ht_4j_em_incl_4b"],["hT30_h330","hT30_all"]],
    ["ht330_EM_4j_3b_vs_ht330",["ht_4j_3b_em/ht_4j_3b_em_pass_4b","ht_4j_3b_em/ht_4j_3b_em_incl_4b"],["hT30_h330","hT30_all"]],
#    [["ht_4j_em/ht_4j_em_pass_4b","ht_4j_em/ht_4j_em_incl_4b"],["hT30_h330","hT30_all"]],
    ]    


for (pName, p1, p2) in effPairs:

    dirName    = "trigStudy"
    if p1[1] == "allPt":
        binning = []
        for i in range(20,202,2):
            binning.append(i)
    else:
        binning = 1

    eff1 = makeEff(p1 ,         dirName,         inFile, binning=binning, bayesRatio=0)
    eff2 = makeEff(p2 ,         dirName,         inFile, binning=binning, bayesRatio=0)
    
    yLeg = 0.93
    xLeg = 0.5

    doFit = False#o.mc
    print "max is ",eff1.GetXaxis().GetXmax()
    drawComp("Eff_"+pName.replace("/","_"),[(eff1,p1[0],       ROOT.kBlack),
                                            (eff2,p2[0],       ROOT.kRed),
                                            #(eff_Matched_2,o.name2,  ROOT.kRed, ROOT.kOpenCircle),
                                            #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                                            #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                                            ]
             ,yTitle="Trigger Efficiency",xTitle=eff1.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.25,yLeg=yLeg,xLeg=xLeg,
             xMax=eff1.GetXaxis().GetXmax(),
             xMin=eff1.GetXaxis().GetXmin(),
             doFit = doFit
             )

    outFile.cd()
    eff1.Write()
