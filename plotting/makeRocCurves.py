import ROOT


ROOT.gROOT.SetBatch(True)

import ROOTHelp.FancyROOTStyle

from optparse import OptionParser
p = OptionParser()
p.add_option('--input',  type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile', help = 'intput File' )
p.add_option('--output', type = 'string', default = "makeRocCurves", dest = 'outDir', help = 'output dir' )
p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
(o,a) = p.parse_args()

inFile  = ROOT.TFile(o.inFile,  "READ")


import os
if not os.path.exists(o.outDir):
    os.makedirs(o.outDir)

from rocCurveUtils     import makeRoc
from JetLevelPlotUtils import getCMSText, getText



def getWorkingPoint(var, bkg, sig, dir, varNorm):
    sigHist = inFile.Get(dir+"_"+sig+"/"+var)
    bkgHist = inFile.Get(dir+"_"+bkg+"/"+var)

    sigNormHist = inFile.Get(dir+"_"+sig+"/"+varNorm)
    bkgNormHist = inFile.Get(dir+"_"+bkg+"/"+varNorm)


    rocPlot = makeRoc(sigHist, sigNormHist, bkgHist, bkgNormHist,doErr=False,bkgMode="Rej")

    nbins      = sigHist.GetNbinsX()

    thisSig    = sigHist    .Integral(0,nbins+1)
    thisSigDen = sigNormHist.Integral(0,nbins+1)
    if not thisSigDen: thisSigDen = 1
    sigEff = float(thisSig) / float(thisSigDen)

    thisBkg    = bkgHist    .Integral(0,nbins+1)
    thisBkgDen = bkgNormHist.Integral(0,nbins+1)
    if not thisBkgDen: thisBkgDen = 1
    bkgEff =  float(thisBkg) / float(thisBkgDen)
    if bkgEff: bkgRej = 1./bkgEff
    else:      bkgRej = 1

    print bkgRej

    return (sigEff, bkgRej)

def makeRocPlot(name, var, bkg, sig, dir, varNorm=None,debug=False):
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
        can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".pdf")
        can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".png")
    return rocPlots

def plotSame(name,graphs,colors,styles, plotCaloJet=False, plotPFJet=False, plotOffJet=False,plotCSV=False,plotDeepCSV=False,workingPts= None,rocType=None):

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
    xStart = 0.2
    if rocType == "Rej":
        xStart = 0.5
        yStart = 0.875

    if plotOffJet:
        offJetText  = getText("Offline Jets  ",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
        yStart = yStart - 0.05
        offJetText.Draw("same")

    if plotCaloJet:
        caloJetText = getText("HLT Calo Jets",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kRed)
        yStart = yStart - 0.05
        caloJetText.Draw("same")
    if plotPFJet:
        pfJetText   = getText("HLT PF Jets  ",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlue)

        pfJetText.Draw("same")

        #offJetTextDeep  = getText("Offline DeepCSV (Dashed)  ",xStart=0.6,yStart=0.36,size=0.03,color=ROOT.kBlack)

        #offJetText  = getText("Offline Jet  ",xStart=0.6,yStart=0.4,size=0.03,color=ROOT.kBlack)

    yStart = 0.3
    xStart = 0.6
    if rocType == "Rej":
        xStart = 0.2


    if plotDeepCSV:
        if plotCSV:
            deepCSVText   = getText("DeepCSV (solid)  ",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
        else:
            deepCSVText   = getText("DeepCSV",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
        deepCSVText.Draw("same")
        yStart = yStart - 0.05

    if plotCSV:
        if plotDeepCSV:
            CSVText   = getText("CSV      (dashed)  ",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
        else:
            CSVText   = getText("CSV",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
        CSVText.Draw("same")




    #offJetTextDeep.Draw("same")

    can.SaveAs(o.outDir+"/roc_"+name+".pdf")
    can.SaveAs(o.outDir+"/roc_"+name+".png")


#
#
#
def main():


    calo_csv_roc       = makeRocPlot("Calo_csv",     "CSVv2_l",     bkg="matchedCaloJet_L",sig="matchedCaloJet_B",dir="offJets")
    calo_deepcsv_roc   = makeRocPlot("Calo_deepcsv",  "DeepCSV_l",  bkg="matchedCaloJet_L",sig="matchedCaloJet_B",dir="offJets")



    #offcalo_csv_roc       = makeRocPlot("Calo_csv",     "CSVv2_l",     bkg="matchedCalo_L",sig="matchedCalo_B",dir="offJets")
    #offcalo_deepcsv_roc   = makeRocPlot("Calo_csv",     "DeepCSV_l", bkg="matchedCalo_L",sig="matchedCalo_B",dir="offJets")

    #calo_deepcsv_roc   = makeRocPlot("Calo_deepcsv", "deepcsv", bkg="L_matchedCaloJet",sig="B_matchedCaloJet",dir="offJets")
    # calo_csv_roc       = makeRocPlot("Calo_csv",     "CSVv2_l",     bkg="matchedCaloJet_L",sig="matchedCaloJet_B",dir="offJets")
    # calo_deepcsv_roc   = makeRocPlot("Calo_deepcsv",  "DeepCSV_l",  bkg="matchedCaloJet_L",sig="matchedCaloJet_B",dir="offJets")


    off_deepcsv_roc   = makeRocPlot("Offline_deepcsv", "DeepCSV_l", bkg="matched_L",sig="matched_B",dir="offJets")
    # off_csv_roc       = makeRocPlot("Offline_csv",     "CSVv2_l",     bkg="matched_L",sig="matched_B",dir="offJets")

    # pf_csv_roc       = makeRocPlot("PF_csv",     "CSVv2_l",     bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")
    pf_deepcsv_roc   = makeRocPlot("PF_deepcsv",     "DeepCSV_l", bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")


    for i, rocType in enumerate(["Rej","Eff"]):

        plotSame("Off_deepcsv_vs_csv_"+rocType,
                 # [off_deepcsv_roc[i], off_csv_roc[i]],
                 [off_deepcsv_roc[i]],
                 [ROOT.kBlack],
                 # [ROOT.kBlack, ROOT.kBlack],
                 [ROOT.kSolid],
                 # [ROOT.kSolid, ROOT.kDashed],
                 plotOffJet = True,
                 # plotCSV = True,
                 plotCSV = False,
                 plotDeepCSV = True,
                 rocType = rocType
                 )

        # plotSame("Calo_deepcsv_vs_csv_"+rocType,
        #          [calo_deepcsv_roc[i], calo_csv_roc[i]],
        #          [ROOT.kRed, ROOT.kRed],
        #          [ROOT.kSolid, ROOT.kDashed],
        #          plotCaloJet = True,
        #          plotCSV = True,
        #          plotDeepCSV = True,
        #          rocType = rocType
        #          )

        # plotSame("PF_deepcsv_vs_csv_"+rocType,
        #          # [calo_deepcsv_roc[i], calo_csv_roc[i]],
        #          [calo_deepcsv_roc[i]],
        #          [ROOT.kBlue],
        #          # [ROOT.kBlue, ROOT.kBlue],
        #          [ROOT.kSolid],
        #          # [ROOT.kSolid, ROOT.kDashed],
        #          plotPFJet = True,
        #          # plotCSV = True,
        #          plotCSV = False,
        #          plotDeepCSV = True,
        #          rocType = rocType
        #          )


        # plotSame("Off_vs_Calo_"+rocType,
        #          [off_deepcsv_roc[i], off_csv_roc[i], calo_csv_roc[i], calo_deepcsv_roc[i]],
        #          [ROOT.kBlack, ROOT.kBlack,  ROOT.kRed  ,  ROOT.kRed   ],
        #          [ROOT.kSolid, ROOT.kDashed, ROOT.kDashed,  ROOT.kSolid ],
        #          plotOffJet = True,
        #          plotCaloJet = True,
        #          plotCSV = True,
        #          plotDeepCSV = True,
        #          rocType = rocType
        #          )

        plotSame("Off_vs_PF_"+rocType,
                 # [off_deepcsv_roc[i], off_csv_roc[i], pf_csv_roc[i], pf_deepcsv_roc[i]],
                 [off_deepcsv_roc[i], pf_deepcsv_roc[i]],
                 [ROOT.kBlack,  ROOT.kBlue   ],
                 # [ROOT.kBlack, ROOT.kBlack,  ROOT.kBlue  ,  ROOT.kBlue   ],
                 [ROOT.kSolid,  ROOT.kSolid ],
                 # [ROOT.kSolid, ROOT.kDashed, ROOT.kDashed,  ROOT.kSolid ],
                 plotPFJet = True,
                 plotOffJet = True,
                 plotCSV = False,
                 plotDeepCSV = True,
                 rocType = rocType
                 )


        plotSame("Off_vs_HLT_"+rocType,
                 # [off_deepcsv_roc[i], off_csv_roc[i], calo_csv_roc[i], pf_csv_roc[i]],
                 [off_deepcsv_roc[i]],
                 # [ROOT.kBlack,       ROOT.kBlack,     ROOT.kRed  ,      ROOT.kBlue],
                 [ROOT.kBlack],
                 # [ROOT.kSolid,      ROOT.kDashed,    ROOT.kDashed,      ROOT.kDashed],
                 [ROOT.kSolid],
                 plotCaloJet = False,
                 plotPFJet = True,
                 plotOffJet = True,
                 plotCSV = False,
                 plotDeepCSV = True,
                 rocType = rocType
                 )


        plotSame("Off_vs_HLT_All_"+rocType,
                 [off_deepcsv_roc[i], off_csv_roc[i], calo_csv_roc[i],  calo_deepcsv_roc[i],   pf_deepcsv_roc[i],  pf_csv_roc[i]],
                 [ROOT.kBlack,       ROOT.kBlack,     ROOT.kRed  ,      ROOT.kRed,             ROOT.kBlue,         ROOT.kBlue],
                 [ROOT.kSolid,      ROOT.kDashed,     ROOT.kDashed,     ROOT.kSolid,           ROOT.kSolid,        ROOT.kDashed],
                 plotCaloJet = True,
                 plotPFJet = True,
                 plotOffJet = True,
                 plotCSV = True,
                 plotDeepCSV = True,
                 rocType = rocType
                 )


        plotSame("Off_vs_HLTDeepCSV_"+rocType,
                 [off_deepcsv_roc[i], pf_deepcsv_roc[i]],
                 # [off_deepcsv_roc[i], calo_deepcsv_roc[i], pf_deepcsv_roc[i]],
                 [ROOT.kBlack,      ROOT.kBlue],
                 # [ROOT.kBlack,       ROOT.kRed  ,      ROOT.kBlue],
                 [ROOT.kSolid,      ROOT.kSolid],
                 # [ROOT.kSolid,      ROOT.kSolid,      ROOT.kSolid],
                 plotCaloJet = False,
                 plotPFJet = True,
                 plotOffJet = True,
                 plotCSV = False,
                 plotDeepCSV = True,
                 rocType = rocType
                 )




if __name__ == "__main__":
    main()
