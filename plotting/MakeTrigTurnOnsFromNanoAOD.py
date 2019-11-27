
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


    ["ht330_3tag/ht330_3tag_pass",      "ht330_3tag/ht330_3tag_incl"] ,            

    #["ht330_3tag_pass_3b",   "ht330_3tag_incl_3b"] ,            
    #["ht330_3tag_pass_4b",   "ht330_3tag_incl_4b"] ,            
    #
    #["ht330_sel_pass",      "ht330_sel_incl"] ,            
    #["ht330_sel_pass_3b",   "ht330_sel_incl_3b"] ,            
    #["ht330_sel_pass_4b",   "ht330_sel_incl_4b"] ,            

    ["ht330_sel_noSubSet/ht330_sel_noSubSet_pass",    "ht330_sel_noSubSet/ht330_sel_noSubSet_incl"],
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

    ["hT30_h330_l320","hT30_all"],
    ["hT30_h330","hT30_all"],

    ["matchedPt_h20","allPt"],
    ["matchedPt_h25","allPt"],
    ["matchedPt_h30","allPt"],
    ["matchedPt_h35","allPt"],
    ["matchedPt_h40","allPt"],
    ["matchedPt_h40_l40","allPt"],
    ["matchedPt_h45","allPt"],
    ["matchedPt_h45_l40","allPt"],
    ["matchedPt_h50","allPt"],
    ["matchedPt_h60","allPt"],
    ["matchedPt_h60_l55","allPt"],
    ["matchedPt_h70","allPt"],
    ["matchedPt_h75","allPt"],
    ["matchedPt_h75_l70","allPt"],
    ["matchedPt_h80","allPt"],
    ["matchedPt_h90","allPt"],
    ["matchedPt_h100","allPt"],


    ]    


for p in effPairs:
        
    dirName    = "trigStudy"
#    binning = [0,200]
#
#    for i in range(45):
#        binning.append(200+10*(i+1))
#
#    #for i in range(500):
#    #    binning.append(200+i)
#
##    for i in range(100):
##        binning.append(500+2*(i+1))
##
##    for i in range(50):
##        binning.append(700+4*(i+1))
##
##    for i in range(50):
##        binning.append(900+8*(i+1))
##    for i in range(5):
##        binning.append(900+100*(i+1))
#    binning.append(700)
#    binning.append(800)
#    binning.append(900)
#    binning.append(1000)
#    binning.append(1100)
#    binning.append(1200)
#    #binning.append(1300)
#    binning.append(1400)
#    #binning.append(1500)
#    binning.append(1600)
#    #binning.append(1700)
#    #binning.append(1800)
#    binning.append(1900)
#    binning.append(1990)
#    binning.append(2000)
#
#    #print binning
#    #binning=[0,100,200,500,2000]
#
    #if p[0].find("ht") == -1:
    if p[1] == "allPt":
        binning = []
        for i in range(20,202,2):
            binning.append(i)
    else:
        binning = 1

    eff_Matched = makeEff(p ,         dirName,         inFile, binning=binning, bayesRatio=0)
    
    yLeg = 0.93
    xLeg = 0.5

    doFit = True#o.mc
    print "max is ",eff_Matched.GetXaxis().GetXmax()
    drawComp("Eff_"+p[0].replace("/","_"),[(eff_Matched,o.name,       ROOT.kBlack),
                          #(eff_Matched_2,o.name2,  ROOT.kRed, ROOT.kOpenCircle),
                          #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                          #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                          ]
             ,yTitle="Trigger Efficiency",xTitle=eff_Matched.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.25,yLeg=yLeg,xLeg=xLeg,
             xMax=eff_Matched.GetXaxis().GetXmax(),
             xMin=eff_Matched.GetXaxis().GetXmin(),
             doFit = doFit
             )

    outFile.cd()
    print eff_Matched.GetName()
    eff_Matched.Write()
