import ROOT


ROOT.gROOT.SetBatch(True)

import OfficialAtlasStyle

from optparse import OptionParser
p = OptionParser()
#p.add_option('--inputData',  type = 'string', dest = 'inFileData', help = 'intput File' )
p.add_option('--inputNum', help = 'intput File' )
p.add_option('--inputDen', help = 'intput File' )
p.add_option('--name',  help = 'intput File' )
p.add_option('--output', type = 'string', default = "jetLevelPlots", dest = 'outDir', help = 'output dir' )
(o,a) = p.parse_args()

#from rocCurveUtils            import drawWaterMarks
#import rebinning
#from Rebinning import rebinningDB

inFileNum  = ROOT.TFile(o.inputNum,"READ")
inFileDen  = ROOT.TFile(o.inputDen,"READ")

import os
if not os.path.exists(o.outDir):
    os.mkdir(o.outDir)

outFile = ROOT.TFile(o.outDir+"/EffOnlineWrtOffline.root","RECREATE")

from JetLevelPlotUtils import makeEffFromFiles, drawComp, getHist, drawStackCompRatio, makeStack, makeInverseTurnOn, make2DComp, makeInverseTurnOnAll,plotRatio

#plotRatio("nPV",    "Events",inFileData, "Data", inFileMC, "MC",xTitle="nPV", outDir=o.outDir,binning=1)


#plot(["hT30_pass_4b","hT30_incl_4b"],"HtTurnOn",doratio=1,bayesRatio=1)

effHists = ("passMDRs/fourTag/mainView/inclusive/","hT30")



binning = [0,200]

for i in range(45):
    binning.append(200+10*(i+1))

    #for i in range(500):
    #    binning.append(200+i)

#    for i in range(100):
#        binning.append(500+2*(i+1))
#
#    for i in range(50):
#        binning.append(700+4*(i+1))
#
#    for i in range(50):
#        binning.append(900+8*(i+1))
#    for i in range(5):
#        binning.append(900+100*(i+1))
binning.append(700)
binning.append(800)
binning.append(900)
binning.append(1000)
binning.append(1100)
binning.append(1200)
    #binning.append(1300)
binning.append(1400)
    #binning.append(1500)
binning.append(1600)
    #binning.append(1700)
    #binning.append(1800)
binning.append(1900)
binning.append(1990)
binning.append(2000)

    #print binning
    #binning=[0,100,200,500,2000]

#binning  = 1

eff_Matched = makeEffFromFiles(effHists[1] ,         effHists[0],         inFileNum, inFileDen, binning=binning)

yLeg = 0.93
xLeg = 0.5

doFit = True#o.mc

drawComp("Eff_"+effHists[1],[(eff_Matched,o.name,       ROOT.kBlack),
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
eff_Matched.Write()
