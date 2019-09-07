import ROOT


ROOT.gROOT.SetBatch(True)

import OfficialAtlasStyle

from optparse import OptionParser
p = OptionParser()
#p.add_option('--inputData',  type = 'string', dest = 'inFileData', help = 'intput File' )
p.add_option('--input1', help = 'intput File' )
p.add_option('--name1',  help = 'intput File' )
p.add_option('--input2', help = 'intput File' )
p.add_option('--name2',  help = 'intput File' )
p.add_option('--mc',     action="store_true",help = 'intput File' )
p.add_option('--output', type = 'string', default = "jetLevelPlots", dest = 'outDir', help = 'output dir' )
(o,a) = p.parse_args()

#from rocCurveUtils            import drawWaterMarks
#import rebinning
#from Rebinning import rebinningDB

inFile1  = ROOT.TFile(o.input1,"READ")
if o.mc:
    inFile2 = inFile1
else:
    inFile2  = ROOT.TFile(o.input2,  "READ")

import os
if not os.path.exists(o.outDir):
    os.mkdir(o.outDir)


from JetLevelPlotUtils import makeEff, drawComp, getHist, drawStackCompRatio, makeStack, makeInverseTurnOn, make2DComp, makeInverseTurnOnAll,plotRatio

#plotRatio("nPV",    "Events",inFileData, "Data", inFileMC, "MC",xTitle="nPV", outDir=o.outDir,binning=1)



effPairs = [["offJetPt15","offJetPt0"] ,
            ["offJetPt30","offJetPt0"] ,
            ["offJetPt40","offJetPt0"] ,
            ["offJetPt45","offJetPt0"] ,
            ["offJetPt50","offJetPt0"] ,
            ["offJetPt60","offJetPt0"] ,
            ["offJetPt75","offJetPt0"] ,
            ["offJetPt80","offJetPt0"] ,
            ["offJetPt90","offJetPt0"] ,
            ["offJetPt100","offJetPt0"] ,
            ["offJetPt105","offJetPt0"] ,
            ["offJetPt110","offJetPt0"] ,
            ["offJetPt120","offJetPt0"] ,
            ["offJetPt140_l","offJetPt0_l"],
            ["offJetPt200_l","offJetPt0_l"],
            ["offJetPt260_vl","offJetPt0_vl"],
            ["offJetPt320_vl","offJetPt0_vl"],
            ["offJetPt400_2vl","offJetPt0_2vl"],
            ["offJetPt450_3vl","offJetPt0_3vl"],
            ["offJetPt500_3vl","offJetPt0_3vl"],
            ["offJetPt550_4vl","offJetPt0_4vl"],
             
            ["offJetPtAll15","offJetPtAll0"] ,
            ["offJetPtAll30","offJetPtAll0"] ,
            ["offJetPtAll40","offJetPtAll0"] ,
            ["offJetPtAll45","offJetPtAll0"] ,
            ["offJetPtAll50","offJetPtAll0"] ,
            ["offJetPtAll60","offJetPtAll0"] ,
            ["offJetPtAll75","offJetPtAll0"] ,
            ["offJetPtAll80","offJetPtAll0"] ,
            ["offJetPtAll90","offJetPtAll0"] ,
            ["offJetPtAll100","offJetPtAll0"] ,
            ["offJetPtAll105","offJetPtAll0"] ,
            ["offJetPtAll110","offJetPtAll0"] ,
            ["offJetPtAll120","offJetPtAll0"] ,
            ["offJetPtAll140_l","offJetPtAll0_l"],
            ["offJetPtAll200_l","offJetPtAll0_l"],
            ["offJetPtAll260_vl","offJetPtAll0_vl"],
            ["offJetPtAll320_vl","offJetPtAll0_vl"],
            ["offJetPtAll400_2vl","offJetPtAll0_2vl"],
            ["offJetPtAll450_3vl","offJetPtAll0_3vl"],
            ["offJetPtAll500_3vl","offJetPtAll0_3vl"],
            ["offJetPtAll550_4vl","offJetPtAll0_4vl"],
                        

            ["offHtAll180","offHtAll0"],
            ["offHtAll250","offHtAll0"],
            ["offHtAll330_l","offHtAll0_l"],
            ["offHtAll370_l","offHtAll0_l"],
            ["offHtAll430_l","offHtAll0_l"],
            ["offHtAll510_l","offHtAll0_l"],
            ["offHtAll590_l","offHtAll0_l"],
            ["offHtAll680_vl","offHtAll0_vl"],
            ["offHtAll780_vl","offHtAll0_vl"],
            ["offHtAll890_vl","offHtAll0_vl"],
            ["offHtAll1050_2vl","offHtAll0_2vl"],
            ]    


if o.mc:
    effPairs = [["offJetPtAll15_L","offJetPtAll0_L"] ,
                ["offJetPtAll30_L","offJetPtAll0_L"] ,
                ["offJetPtAll40_L","offJetPtAll0_L"] ,
                ["offJetPtAll45_L","offJetPtAll0_L"] ,
                ["offJetPtAll50_L","offJetPtAll0_L"] ,
                ["offJetPtAll60_L","offJetPtAll0_L"] ,
                ["offJetPtAll75_L","offJetPtAll0_L"] ,
                ["offJetPtAll80_L","offJetPtAll0_L"] ,
                ["offJetPtAll90_L","offJetPtAll0_L"] ,
                ["offJetPtAll100_L","offJetPtAll0_L"] ,
                ["offJetPtAll105_L","offJetPtAll0_L"] ,
                ["offJetPtAll110_L","offJetPtAll0_L"] ,
                ["offJetPtAll120_L","offJetPtAll0_L"] ,
                ["offJetPtAll140_L_l","offJetPtAll0_L_l"],
                ["offJetPtAll200_L_l","offJetPtAll0_L_l"],
                ["offJetPtAll260_L_vl","offJetPtAll0_L_vl"],
                ["offJetPtAll320_L_vl","offJetPtAll0_L_vl"],
                ["offJetPtAll400_L_2vl","offJetPtAll0_L_2vl"],
                ["offJetPtAll450_L_3vl","offJetPtAll0_L_3vl"],
                ["offJetPtAll500_L_3vl","offJetPtAll0_L_3vl"],
                ["offJetPtAll550_L_4vl","offJetPtAll0_L_4vl"],
                ]    

for p in effPairs:
        
    dirName    = "TrigTurnOnStudy"
    
    eff_Matched_1 = makeEff(p ,         dirName,         inFile1, binning=1)
    if o.mc:
        eff_Matched_2 = makeEff([p[0].replace("_L","_B"),p[1].replace("_L","_B")] ,         dirName,         inFile1, binning=1)
    else:
        eff_Matched_2 = makeEff(p ,         dirName,         inFile2, binning=1)

    yLeg = 0.93
    xLeg = 0.5

    doFit = True#o.mc

    drawComp("Eff_"+p[0],[(eff_Matched_1,o.name1,       ROOT.kBlack),
                          (eff_Matched_2,o.name2,  ROOT.kRed, ROOT.kOpenCircle),
                          #(eff_Matched_BTag,"t#bar{t} MC ",ROOT.kBlue),
                          #(eff_Matched_BTag_noV0,"t#bar{t} MC ",ROOT.kGreen)
                          ]
             ,yTitle="Trigger Efficiency",xTitle=eff_Matched_1.GetXaxis().GetTitle(),outDir=o.outDir,yMax=1.25,yLeg=yLeg,xLeg=xLeg,
             xMax=eff_Matched_1.GetXaxis().GetXmax(),
             xMin=eff_Matched_1.GetXaxis().GetXmin(),
             doFit = doFit
             )

