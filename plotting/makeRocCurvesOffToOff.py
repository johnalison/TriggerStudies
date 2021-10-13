import ROOT


ROOT.gROOT.SetBatch(True)

import ROOTHelp.FancyROOTStyle

from optparse import OptionParser
p = OptionParser()
p.add_option('--input',  type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile', help = 'intput File' )
p.add_option('--output', type = 'string', default = "makeRocCurves", dest = 'outDir', help = 'output dir' )
p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
p.add_option('--labName', type = 'string', default = "Reference,Monitored",  help = '' )
(o,a) = p.parse_args()

inFile  = ROOT.TFile(o.inFile,  "READ")

labName = o.labName.split(",")

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

def makeRocPlot(name, var, bkg, sig, dir, varNorm=None,debug=False,vsLight=True):
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
        if vsLight: yTitle = "Light Flavor "
        else:       yTitle = "C-Jet "
        
        if config[0] == "Rej":    yTitle +="Rejection"
        elif config[0] == "Eff":  yTitle +="Efficiency"
        rocPlots[-1].GetYaxis().SetTitle(yTitle)
        rocPlots[-1].GetYaxis().SetRangeUser(config[1],config[2])
        rocPlots[-1].Draw("AL")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".pdf")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".png")
    return rocPlots


def plotSame(name,graphs,colors,styles, workingPts= None,rocType=None,plotDeepCSV=False,plotDeepJet=False):

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

    offJetText  = getText(labName[0]+" Jets (Solid)  ",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
    yStart = yStart - 0.05
    offJetText.Draw("same")

    pfJetText   = getText(labName[1]+" Jet (Dashed)  ",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
    pfJetText.Draw("same")

        #offJetTextDeep  = getText("Offline DeepCSV (Dashed)  ",xStart=0.6,yStart=0.36,size=0.03,color=ROOT.kBlack)

        #offJetText  = getText("Offline Jet  ",xStart=0.6,yStart=0.4,size=0.03,color=ROOT.kBlack)

    yStart = 0.3
    xStart = 0.6
    if rocType == "Rej":
        xStart = 0.2


    if plotDeepCSV:
        if plotDeepJet:
            deepCSVText   = getText("DeepCSV",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlue)
        else:
            deepCSVText   = getText("DeepJet",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)

        deepCSVText.Draw("same")
        yStart = yStart - 0.05

    if plotDeepJet:
        if plotDeepCSV:
            deepJetText   = getText("DeepJet",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
        else:
            deepJetText   = getText("DeepCSV",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlue)
        deepJetText.Draw("same")
        yStart = yStart - 0.05





    #offJetTextDeep.Draw("same")

    can.SaveAs(o.outDir+"/roc_"+name+".pdf")





def main():


    mon_deepcsv_roc        = makeRocPlot("Offline_deepcsv",      "DeepCSV_l", bkg="matched_L",sig="matched_B",dir="offJets")
    mon_deepJet_roc        = makeRocPlot("Offline_deepJet",      "deepFlavB", bkg="matched_L",sig="matched_B",dir="offJets")

    ref_deepcsv_roc        = makeRocPlot("PF_deepcsv",      "DeepCSV_l", bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")
    ref_deepJet_roc        = makeRocPlot("PF_deepJet",      "deepFlavB", bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")

    mon_deepcsv_roc_C        = makeRocPlot("Offline_deepcsv",      "DeepCSV_l", bkg="matched_C",sig="matched_B",dir="offJets", vsLight=False)
    mon_deepJet_roc_C        = makeRocPlot("Offline_deepJet",      "deepFlavB", bkg="matched_C",sig="matched_B",dir="offJets", vsLight=False)

    ref_deepcsv_roc_C        = makeRocPlot("PF_deepcsv",      "DeepCSV_l", bkg="matchedJet_C",sig="matchedJet_B",dir="offJets", vsLight=False)
    ref_deepJet_roc_C        = makeRocPlot("PF_deepJet",      "deepFlavB", bkg="matchedJet_C",sig="matchedJet_B",dir="offJets", vsLight=False)



    for i, rocType in enumerate(["Rej","Eff"]):


        plotSame("DeepCSV_"+rocType,
                 [mon_deepcsv_roc[i], ref_deepcsv_roc[i]],
                 [ROOT.kBlack,      ROOT.kBlue],
                 [ROOT.kSolid,      ROOT.kDashed],
                 plotDeepJet = False,
                 plotDeepCSV = True,
                 rocType = rocType
                 )

        plotSame("DeepJet_"+rocType,
                 [mon_deepJet_roc[i], ref_deepJet_roc[i]],
                 [ROOT.kBlack,      ROOT.kBlack],
                 [ROOT.kSolid,      ROOT.kSolid],
                 plotDeepCSV = False,
                 plotDeepJet = True,
                 rocType = rocType
                 )



        plotSame("All_"+rocType,
                 [mon_deepcsv_roc[i], mon_deepJet_roc[i], ref_deepcsv_roc[i], ref_deepJet_roc[i]],
                 [ROOT.kBlue, ROOT.kBlack,  ROOT.kBlue  ,  ROOT.kBlack   ],
                 [ROOT.kSolid, ROOT.kSolid, ROOT.kDashed,  ROOT.kDashed ],
                 plotDeepCSV = True,
                 plotDeepJet = True,
                 rocType = rocType
                 )



        plotSame("DeepCSV_C_"+rocType,
                 [mon_deepcsv_roc_C[i], ref_deepcsv_roc_C[i]],
                 [ROOT.kBlack,      ROOT.kBlue],
                 [ROOT.kSolid,      ROOT.kDashed],
                 plotDeepJet = False,
                 plotDeepCSV = True,
                 rocType = rocType
                 )

        plotSame("DeepJet_C_"+rocType,
                 [mon_deepJet_roc_C[i], ref_deepJet_roc_C[i]],
                 [ROOT.kBlack,      ROOT.kBlack],
                 [ROOT.kSolid,      ROOT.kSolid],
                 plotDeepCSV = False,
                 plotDeepJet = True,
                 rocType = rocType
                 )



        plotSame("All_C_"+rocType,
                 [mon_deepcsv_roc_C[i], mon_deepJet_roc_C[i], ref_deepcsv_roc_C[i], ref_deepJet_roc_C[i]],
                 [ROOT.kBlue, ROOT.kBlack,  ROOT.kBlue  ,  ROOT.kBlack   ],
                 [ROOT.kSolid, ROOT.kSolid, ROOT.kDashed,  ROOT.kDashed ],
                 plotDeepCSV = True,
                 plotDeepJet = True,
                 rocType = rocType
                 )
        







if __name__ == "__main__":
    main()
