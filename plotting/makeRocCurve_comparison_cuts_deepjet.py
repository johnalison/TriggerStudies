import ROOT


ROOT.gROOT.SetBatch(True)

import ROOTHelp.FancyROOTStyle

from optparse import OptionParser
p = OptionParser()
p.add_option('--input',  type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile', help = 'intput File' )
p.add_option('--input2',  type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile2', help = 'intput File 2' )
p.add_option('--label',  type = 'string', default = "input", dest = 'label1', help = 'intput File' )
p.add_option('--label2',  type = 'string', default = "input2", dest = 'label2', help = 'intput File 2' )
p.add_option('--output', type = 'string', default = "makeRocCurves", dest = 'outDir', help = 'output dir' )
p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
(o,a) = p.parse_args()

label1 = o.label1
label2 =  o.label2


import os
if not os.path.exists(o.outDir):
    os.makedirs(o.outDir)

from rocCurveUtils     import makeRoc
from JetLevelPlotUtils import getCMSText, getText


def makeRocPlot(name, var, bkg, sig, dir, varNorm=None,debug=False, inFile=None):
    inFile  = ROOT.TFile(inFile,  "READ")
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
        # rocPlots[-1].SetLineWidth(2)
        rocPlots[-1].GetXaxis().SetTitle("B-Jet  Efficiency")
        rocPlots[-1].GetXaxis().SetRangeUser(0.4,1)
        if config[0] == "Rej":    yTitle ="Light Flavor Rejection"
        elif config[0] == "Eff":  yTitle ="Light Flavor Efficiency"
        rocPlots[-1].GetYaxis().SetTitle(yTitle)
        rocPlots[-1].GetYaxis().SetRangeUser(config[1],config[2])
        rocPlots[-1].Draw("AL")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+"_"+label1+"_"+".pdf")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+"_"+label1+"_"+".png")
    return rocPlots

def plotSame(name,graphs,colors,styles, plotCaloJet=False, plotPFJet=False, plotOffJet=False,plotDeepJet=False,plotDeepCSV=False,workingPts= None,rocType=None):

    can = ROOT.TCanvas(name,name)
    can.cd().SetLogy(1)
    for gItr, g in enumerate(graphs):
        g.SetLineColor(colors[gItr])
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

    yStart = 0.75
    xStart = 0.225
    if rocType == "Rej":
        xStart = 0.5
        yStart = 0.875

    if plotOffJet:
        offJetText  = getText("Offline PUPPI Jets  ",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlack)
        yStart = yStart - 0.04
        offJetText.Draw("same")

    if plotPFJet:
        pfJetText   = getText("HLT PUPPI Jets"+" TRKv6p1+TICL default (+TRKv0 dotted)",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kRed)
        pfJetText.Draw("same")
        yStart = yStart - 0.04
        # pfJetText2   = getText("HLT PF Jets"+" TRKv2 (+TICL in dotted)",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlue+1)
        # pfJetText2.Draw("same")
        # yStart = yStart - 0.04
        pfJetText3   = getText("HLT PUPPI Jets"+" TRKv6p1+TICL cuttedV1 (+TRKv0 dotted)",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kGreen+2)
        pfJetText3.Draw("same")
        # pfJetText4   = getText("HLT PF Jets"+" TRKv0+TICL",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kRed)
        # pfJetText4.Draw("same")
        # yStart = yStart - 0.04
        # pfJetText5   = getText("HLT PF Jets"+" TRKv2+TICL",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlue+1)
        # pfJetText5.Draw("same")
        yStart = yStart - 0.04
        pfJetText6   = getText("HLT PUPPI Jets"+" TRKv6p1+TICL cuttedV2 (+TRKv0 dotted)",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlue+1)
        pfJetText6.Draw("same")


    yStart = 0.25
    xStart = 0.6
    if rocType == "Rej":
        xStart = 0.2


    if plotDeepCSV:
        if plotCSV:
            deepCSVText   = getText("DeepCSV (solid)  ",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlack)
        else:
            deepCSVText   = getText("DeepCSV",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlack)
        deepCSVText.Draw("same")
        yStart = yStart - 0.04

    if plotDeepJet:
        if plotDeepCSV:
            CSVText   = getText("DeepJet      (dashed)  ",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlack)
        else:
            CSVText   = getText("DeepJet",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlack)
        CSVText.Draw("same")




    #offJetTextDeep.Draw("same")

    can.SaveAs(o.outDir+"/roc_"+name+".pdf")
    can.SaveAs(o.outDir+"/roc_"+name+".png")


#
#
#
def main():

    # off_deepcsv_roc   = makeRocPlot("Offline_PUPPI_deepcsv", "DeepJet_l", bkg="matchedPuppi_L",sig="matchedPuppi_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV6_cutsV1.root")
    # pf_deepcsv_roc    = makeRocPlot("PUPPI_deepcsv",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV6_cutsV1.root")
    # pf_deepcsv_roc3   = makeRocPlot("PUPPI_deepcsv",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV6_TICL_cutsV1.root")
    # pf_deepcsv_roc4   = makeRocPlot("PUPPI_deepcsv",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV6_cutsV2.root")
    # pf_deepcsv_roc6   = makeRocPlot("PUPPI_deepcsv",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV6_TICL_cutsV2.root")
    off_deepjet_roc   = makeRocPlot("PU200_Offline_PUPPI_deepjet", "DeepJet_l", bkg="matchedPuppi_L",sig="matchedPuppi_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV0_default.root")
    pf_deepjet_roc    = makeRocPlot("PU200_PUPPI_deepjet_v0_def",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV0_default.root")
    pf_deepjet_roc2    = makeRocPlot("PU200_PUPPI_deepjet_v0_c1",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV0_cutsV1.root")
    pf_deepjet_roc3    = makeRocPlot("PU200_PUPPI_deepjet_v0_c2",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV0_cutsV2.root")
    pf_deepjet_roc4   = makeRocPlot("PU200_PUPPI_deepjet_v6T_def",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV6p1_TICL_default.root")
    pf_deepjet_roc5   = makeRocPlot("PU200_PUPPI_deepjet_v6T_c1",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV6p1_TICL_cutsV1.root")
    pf_deepjet_roc6   = makeRocPlot("PU200_PUPPI_deepjet_v6T_c2",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU200_TrackingV6p1_TICL_cutsV2.root")

    for i, rocType in enumerate(["Rej","Eff"]):

        plotSame("PU200_Off_vs_HLTDeepJet_"+rocType,
                 # [off_deepjet_roc[i], pf_deepjet_roc[i],  pf_deepjet_roc2[i], pf_deepjet_roc3[i],  pf_deepjet_roc4[i], pf_deepjet_roc5[i] ,pf_deepjet_roc6[i]],
                 [off_deepjet_roc[i], pf_deepjet_roc4[i],  pf_deepjet_roc5[i], pf_deepjet_roc6[i],  pf_deepjet_roc[i], pf_deepjet_roc2[i] ,pf_deepjet_roc3[i]],
                 [ROOT.kBlack,      ROOT.kRed,  ROOT.kGreen+2, ROOT.kBlue, ROOT.kRed, ROOT.kGreen+2, ROOT.kBlue],
                 [ROOT.kSolid,      ROOT.kSolid,  ROOT.kSolid, ROOT.kSolid, ROOT.kDotted, ROOT.kDotted, ROOT.kDotted],
                 plotCaloJet = False,
                 plotPFJet = True,
                 plotOffJet = True,
                 plotDeepCSV = False,
                 plotDeepJet = True,
                 rocType = rocType
                 )

    off_deepjet_roc   = makeRocPlot("Offline_PUPPI_deepjet", "DeepJet_l", bkg="matchedPuppi_L",sig="matchedPuppi_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_NoPU_TrackingV0_default.root")

    pf_deepjet_roc    = makeRocPlot("PUPPI_deepjet_v0_def",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_NoPU_TrackingV0_default.root")
    pf_deepjet_ro2    = makeRocPlot("PUPPI_deepjet_v0_c1",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_NoPU_TrackingV0_cutsV1.root")
    pf_deepjet_roc3   = makeRocPlot("PUPPI_deepjet_v0_c2",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_NoPU_TrackingV0_cutsV2.root")

    pf_deepjet_roc4   = makeRocPlot("PUPPI_deepjet_v6T_def",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_NoPU_TrackingV6p1_TICL_default.root")
    pf_deepjet_roc5   = makeRocPlot("PUPPI_deepjet_v6T_c1",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_NoPU_TrackingV6p1_TICL_cutsV1.root")
    pf_deepjet_roc6   = makeRocPlot("PUPPI_deepjet_v6T_c2",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_NoPU_TrackingV6p1_TICL_cutsV2.root")

    for i, rocType in enumerate(["Rej","Eff"]):

        plotSame("NoPU_Off_vs_HLTDeepJet_"+rocType,
                 # [off_deepjet_roc[i], pf_deepjet_roc[i],  pf_deepjet_roc2[i], pf_deepjet_roc3[i],  pf_deepjet_roc4[i], pf_deepjet_roc5[i] ,pf_deepjet_roc6[i]],
                 [off_deepjet_roc[i], pf_deepjet_roc4[i],  pf_deepjet_roc5[i], pf_deepjet_roc6[i],  pf_deepjet_roc[i], pf_deepjet_roc2[i] ,pf_deepjet_roc3[i]],
                 [ROOT.kBlack,      ROOT.kRed,  ROOT.kGreen+2, ROOT.kBlue, ROOT.kRed, ROOT.kGreen+2, ROOT.kBlue],
                 [ROOT.kSolid,      ROOT.kSolid,  ROOT.kSolid, ROOT.kSolid, ROOT.kDotted, ROOT.kDotted, ROOT.kDotted],
                 # [off_deepjet_roc[i], pf_deepjet_roc[i]],
                 # [ROOT.kBlack,      ROOT.kRed,  ROOT.kGreen+2, ROOT.kRed, ROOT.kGreen+2],
                 # [ROOT.kSolid,      ROOT.kSolid,  ROOT.kSolid, ROOT.kDotted, ROOT.kDotted],
                 plotCaloJet = False,
                 plotPFJet = True,
                 plotOffJet = True,
                 plotDeepJet = True,
                 plotDeepCSV = False,
                 rocType = rocType
                 )

    # off_deepjet_roc   = makeRocPlot("PU140_Offline_PUPPI_deepjet", "DeepJet_l", bkg="matchedPuppi_L",sig="matchedPuppi_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU140_TrackingV0_default.root")
    #
    # pf_deepjet_roc    = makeRocPlot("PU140_PUPPI_deepjet_v0_def",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU140_TrackingV0_default.root")
    # pf_deepjet_ro2    = makeRocPlot("PU140_PUPPI_deepjet_v0_c1",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU140_TrackingV0_cutsV1.root")
    # pf_deepjet_roc3   = makeRocPlot("PU140_PUPPI_deepjet_v0_c2",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU140_TrackingV0_cutsV2.root")
    #
    # pf_deepjet_roc4   = makeRocPlot("PU140_PUPPI_deepjet_v6T_def",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU140_TrackingV6p1_TICL_default.root")
    # pf_deepjet_roc5   = makeRocPlot("PU140_PUPPI_deepjet_v6T_c1",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU140_TrackingV6p1_TICL_cutsV1.root")
    # pf_deepjet_roc6   = makeRocPlot("PU140_PUPPI_deepjet_v6T_c2",     "DeepJet_l", bkg="matchedPuppiJet_L",sig="matchedPuppiJet_B",dir="offJets", inFile = "../NtupleAna/run/OUTPUT/17_10_20_PreWorkshop/ttbar_PU140_TrackingV6p1_TICL_cutsV2.root")
    #
    # for i, rocType in enumerate(["Rej","Eff"]):
    #
    #     plotSame("PU140_Off_vs_HLTDeepJet_"+rocType,
    #              # [off_deepjet_roc[i], pf_deepjet_roc[i],  pf_deepjet_roc2[i], pf_deepjet_roc3[i],  pf_deepjet_roc4[i], pf_deepjet_roc5[i] ,pf_deepjet_roc6[i]],
    #              [off_deepjet_roc[i], pf_deepjet_roc4[i],  pf_deepjet_roc5[i], pf_deepjet_roc6[i],  pf_deepjet_roc[i], pf_deepjet_roc2[i] ,pf_deepjet_roc3[i]],
    #              [ROOT.kBlack,      ROOT.kRed,  ROOT.kGreen+2, ROOT.kBlue, ROOT.kRed, ROOT.kGreen+2, ROOT.kBlue],
    #              [ROOT.kSolid,      ROOT.kSolid,  ROOT.kSolid, ROOT.kSolid, ROOT.kDotted, ROOT.kDotted, ROOT.kDotted],
    #              # [off_deepjet_roc[i], pf_deepjet_roc[i]],
    #              # [ROOT.kBlack,      ROOT.kRed,  ROOT.kGreen+2, ROOT.kRed, ROOT.kGreen+2],
    #              # [ROOT.kSolid,      ROOT.kSolid,  ROOT.kSolid, ROOT.kDotted, ROOT.kDotted],
    #              plotCaloJet = False,
    #              plotPFJet = True,
    #              plotOffJet = True,
    #              plotDeepJet = True,
    #              plotDeepCSV = False,
    #              rocType = rocType
    #              )

if __name__ == "__main__":
    main()
