import ROOT


ROOT.gROOT.SetBatch(True)
ROOT.gErrorIgnoreLevel = ROOT.kWarning

import ROOTHelp.FancyROOTStyle

from optparse import OptionParser
p = OptionParser()
#p.add_option('--input',  type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile', help = 'intput File' )
p.add_option('--output', type = 'string', default = "makeRocCurves", dest = 'outDir', help = 'output dir' )
p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
#p.add_option('--doCaloJets', action="store_true", help = '' )
#p.add_option('--doPuppiJets', action="store_true", help = '' )
(o,a) = p.parse_args()


import os
if not os.path.exists(o.outDir):
    os.makedirs(o.outDir)

from rocCurveUtils     import makeRoc
from JetLevelPlotUtils import getCMSText, getText



def makeRocPlot(inFile, name, var, bkg, sig, dir, varNorm=None,debug=False):
    sigHist = inFile.Get(dir+"_"+sig+"/"+var)
    bkgHist = inFile.Get(dir+"_"+bkg+"/"+var)

    if varNorm:
        sigNormHist = inFile.Get(dir+"_"+sig+"/"+varNorm)
        bkgNormHist = inFile.Get(dir+"_"+bkg+"/"+varNorm)
    else      :
        sigNormHist = sigHist
        bkgNormHist = bkgHist

    rocPlots = []
    for config in [("Rej",1,5e4),("Eff",5e-4,1)]:
        rocPlots.append(makeRoc(sigHist, sigNormHist, bkgHist, bkgNormHist,doErr=False,bkgMode=config[0],cleanNoCut=True,debug=debug))

        can = ROOT.TCanvas(name+"_"+config[0], name+"_"+config[0])
        can.cd().SetLogy(1)
        rocPlots[-1].SetLineWidth(5)
        rocPlots[-1].GetXaxis().SetTitle("B-Jet  Efficiency")
        rocPlots[-1].GetXaxis().SetRangeUser(0.4,1)
        if config[0] == "Rej":    yTitle ="Light Flavor Rejection"
        elif config[0] == "Eff":  yTitle ="Light Flavor Efficiency"
        rocPlots[-1].GetYaxis().SetTitle(yTitle)
        rocPlots[-1].GetYaxis().SetRangeUser(config[1],config[2])
        rocPlots[-1].Draw("AL")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".pdf")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".png")
    return rocPlots

def plotSame(name,graphs,colors,styles=None, jetNames=[], jetTextColor=None, taggerNames=[], workingPts= None,rocType=None):

    can = ROOT.TCanvas(name,name)
    can.cd().SetLogy(1)
    for gItr, g in enumerate(graphs):
        g.SetLineColor(colors[gItr])

        if styles is None:
            g.SetLineStyle(ROOT.kSolid)
        else:
            g.SetLineStyle(styles[gItr])
            
        if not gItr:
            g.Draw("AL")
        else:
            g.Draw("L")

    if not workingPts == None:
        g_wrkPts = ROOT.TGraph(len(workingPts))
        g_wrkPts.SetMarkerSize(2)
        g_wrkPts.SetMarkerColor(colors[1])
        g_wrkPts.SetMarkerStyle(34)
        for wpItr, wp in enumerate(workingPts):
            print wpItr,wp

            g_wrkPts.SetPoint(wpItr, wp[0],wp[1])

        g_wrkPts.Draw("P")

    cmsLine1, cmsLine2 = getCMSText(xStart=0.2,yStart=0.875,subtext=o.cmsText)
    cmsLine1.Draw("same")
    cmsLine2.Draw("same")

    #
    #   Do the Jet names
    #
    yStart = 0.75
    xStart = 0.2
    if rocType == "Rej":
        xStart = 0.5
        yStart = 0.875

    jetText = []
    for ijn, jn in enumerate(jetNames):
        if jetTextColor is None:
            jetText.append(getText(jn,xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack))
        else:
            jetText.append(getText(jn,xStart=xStart,yStart=yStart,size=0.04,color=jetTextColor[ijn]))
        jetText[-1].Draw("same")
        yStart = yStart - 0.05
        

    #
    #   Do the Tagger names
    #
    yStart = 0.3
    xStart = 0.6
    if rocType == "Rej":
        xStart = 0.2

    tagText = []
    for tn in taggerNames:
        tagText.append(getText(tn,xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack))
        tagText[-1].Draw("same")
        yStart = yStart - 0.05



    can.SaveAs(o.outDir+"/roc_"+name+".pdf")
    can.SaveAs(o.outDir+"/roc_"+name+".png")





def main():

    inFileRun2    = ROOT.TFile("hists_Run3_ttbar_Run2TRK.root",  "READ")
    inFileRun3    = ROOT.TFile("hists_Run3_ttbar_Run3TRK.root",  "READ")
    inFileRun3PU  = ROOT.TFile("hists_Run3_ttbar_Run3TRKWithPU.root",  "READ")
    inFileROI     = ROOT.TFile("hists_Run3_ttbar_ROI.root",  "READ")

    taggers = ["deepFlavB","DeepCSV_l"]

    offline = {}
    HLT_Run2TRK = {}
    HLT_Run3TRK = {}
    HLT_Run3TRKPU = {}
    HLT_ROI = {}

    HLT_Run2TRK_Puppi = {}
    HLT_Run3TRK_Puppi = {}
    HLT_Run3TRKPU_Puppi = {}
    HLT_ROI_Puppi = {}

    
    for t in taggers:
        offline[t]       = makeRocPlot(inFileRun2,  "Offline_"+t,      t, bkg="matched_L",   sig="matched_B",   dir="offJets")
        #offline[t]       = makeRocPlot(inFileRun2,  "Offline_"+t,      t, bkg="matched_L",   sig="matched_B",   dir="offJets")
        HLT_Run2TRK[t]   = makeRocPlot(inFileRun2,  "HLT_Run2TRK_"+t,  t, bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")
        HLT_Run3TRK[t]   = makeRocPlot(inFileRun3,  "HLT_Run3TRK_"+t,  t, bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")
        HLT_Run3TRKPU[t] = makeRocPlot(inFileRun3PU,"HLT_Run3TRKPU_"+t,t, bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")
        HLT_ROI[t]       = makeRocPlot(inFileROI,   "HLT_ROI_"+t,      t, bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")

        HLT_Run2TRK_Puppi[t]   = makeRocPlot(inFileRun2,  "HLT_Run2TRK_Puppi_"+t,  t, bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets")
        HLT_Run3TRK_Puppi[t]   = makeRocPlot(inFileRun3,  "HLT_Run3TRK_Puppi"+t,   t, bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets")
        HLT_Run3TRKPU_Puppi[t] = makeRocPlot(inFileRun3PU,"HLT_Run3TRKPU_Puppi_"+t,t, bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets")
        HLT_ROI_Puppi[t]       = makeRocPlot(inFileRun3PU,"HLT_ROI_Puppi_"+t,      t, bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets")


        
    for i, rocType in enumerate(["Rej","Eff"]):

        plotSame("offline_"+rocType,
                 [offline["DeepCSV_l"][i],offline["deepFlavB"][i]],
                 [ROOT.kBlack,ROOT.kBlack],
                 [ROOT.kSolid,ROOT.kDashed],
                 jetNames = ["Offline"],
                 taggerNames = ["DeepCSV (Solid)", "DeepJet (Dashed)"],
                 rocType = rocType
                 )

        plotSame("HLTRun2_"+rocType,
                 [HLT_Run2TRK["DeepCSV_l"][i],HLT_Run2TRK["deepFlavB"][i]],
                 [ROOT.kBlack,ROOT.kBlack],
                 [ROOT.kSolid,ROOT.kDashed],
                 jetNames = ["HLT Run2 Trk"],
                 taggerNames = ["DeepCSV (Solid)", "DeepJet (Dashed)"],
                 rocType = rocType
                 )

        plotSame("HLTRun2_Puppi_"+rocType,
                 [HLT_Run2TRK["DeepCSV_l"][i],HLT_Run2TRK["deepFlavB"][i],HLT_Run2TRK_Puppi["DeepCSV_l"][i],HLT_Run2TRK_Puppi["deepFlavB"][i]],
                 [ROOT.kBlack,ROOT.kBlack,ROOT.kRed,ROOT.kRed],
                 [ROOT.kSolid,ROOT.kDashed,ROOT.kSolid,ROOT.kDashed],
                 jetNames = ["HLT Run2 Trk","HLT Run2 Trk (Puppi)"],
                 jetTextColor = [ROOT.kBlack,ROOT.kRed],
                 taggerNames = ["DeepCSV (Solid)", "DeepJet (Dashed)"],
                 rocType = rocType
                 )

        
        
#        plotSame("DeepCSV_"+rocType,
#                 [offline["DeepCSV_l"][i],HLT_Run2TRK["DeepCSV_l"][i],HLT_Run3TRK["DeepCSV_l"][i],HLT_Run3TRKPU["DeepCSV_l"][i]],
#                 [ROOT.kBlack,ROOT.kRed,ROOT.kBlue,ROOT.kGreen],
#                 jetNames = ["Offline","HLT Run2 TRK","HLT Run3 TRK","HLT Run3 TRK w/PU"],
#                 jetTextColor = [ROOT.kBlack,ROOT.kRed,ROOT.kBlue,ROOT.kGreen],
#                 taggerNames = ["DeepCSV"],
#                 rocType = rocType
#                 )
#

        plotSame("DeepCSV_"+rocType,
                 [offline["DeepCSV_l"][i],HLT_Run2TRK["DeepCSV_l"][i],HLT_Run3TRK["DeepCSV_l"][i],HLT_Run3TRKPU["DeepCSV_l"][i],HLT_ROI["DeepCSV_l"][i]],
                 [ROOT.kBlack,ROOT.kRed,ROOT.kBlue,ROOT.kGreen,ROOT.kOrange],
                 jetNames = ["Offline","HLT Run2 TRK","HLT Run3 TRK","HLT Run3 TRK w/PU","HLT ROI"],
                 jetTextColor = [ROOT.kBlack,ROOT.kRed,ROOT.kBlue,ROOT.kGreen,ROOT.kOrange],
                 taggerNames = ["DeepCSV"],
                 rocType = rocType
                 )

        
        plotSame("DeepJet_"+rocType,
                 [offline["deepFlavB"][i],HLT_Run2TRK["deepFlavB"][i],HLT_Run3TRK["deepFlavB"][i],HLT_Run3TRKPU["deepFlavB"][i],HLT_ROI["deepFlavB"][i]],
                 [ROOT.kBlack,ROOT.kRed, ROOT.kBlue,ROOT.kGreen,ROOT.kOrange],
                 jetNames = ["Offline","HLT Run2 TRK","HLT Run3 TRK","HLT Run3 TRK w/PU","HLT ROI"],
                 jetTextColor = [ROOT.kBlack,ROOT.kRed,ROOT.kBlue,ROOT.kGreen,ROOT.kOrange],
                 taggerNames = ["DeepJet"],
                 rocType = rocType
                 )

        
        




if __name__ == "__main__":
    main()
