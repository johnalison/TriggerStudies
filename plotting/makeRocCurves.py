import ROOT


ROOT.gROOT.SetBatch(True)

import OfficialAtlasStyle

from optparse import OptionParser
p = OptionParser()
p.add_option('--input',  type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile', help = 'intput File' )
p.add_option('--output', type = 'string', default = "makeRocCurves", dest = 'outDir', help = 'output dir' )
(o,a) = p.parse_args()

inFile  = ROOT.TFile(o.inFile,  "READ")



import os
if not os.path.exists(o.outDir):
    os.mkdir(o.outDir)

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

    cmsLine1, cmsLine2 = getCMSText(xStart=0.2,yStart=0.875)
    cmsLine1.Draw("same")
    cmsLine2.Draw("same")
        
    yStart = 0.75
    xStart = 0.225
    if rocType == "Rej":
        xStart = 0.5
        yStart = 0.875
    
    if plotOffJet:
        offJetText  = getText("Offline Jets  ",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlack)    
        yStart = yStart - 0.04
        offJetText.Draw("same")

    if plotCaloJet:
        caloJetText = getText("HLT Calo Jets",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kRed)    
        yStart = yStart - 0.04
        caloJetText.Draw("same")
    if plotPFJet:
        pfJetText   = getText("HLT PF Jets  ",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlue)    
        pfJetText.Draw("same")

        #offJetTextDeep  = getText("Offline DeepCSV (Dashed)  ",xStart=0.6,yStart=0.36,size=0.03,color=ROOT.kBlack)    

        #offJetText  = getText("Offline Jet  ",xStart=0.6,yStart=0.4,size=0.03,color=ROOT.kBlack)    

    yStart = 0.25
    xStart = 0.6
    if rocType == "Rej":
        xStart = 0.2
    

    if plotDeepCSV:
        deepCSVText   = getText("DeepCSV (solid)  ",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlack)    
        deepCSVText.Draw("same")
        yStart = yStart - 0.04

    if plotCSV:
        CSVText   = getText("CSV      (dashed)  ",xStart=xStart,yStart=yStart,size=0.03,color=ROOT.kBlack)    
        CSVText.Draw("same")




    #offJetTextDeep.Draw("same")

    can.SaveAs(o.outDir+"/roc_"+name+".pdf")        


#
#
#
def main():


    
    #offcalo_csv_roc       = makeRocPlot("Calo_csv",     "CSVv2_l",     bkg="matchedCalo_L",sig="matchedCalo_B",dir="offJets")
    #offcalo_deepcsv_roc   = makeRocPlot("Calo_csv",     "DeepCSV_l", bkg="matchedCalo_L",sig="matchedCalo_B",dir="offJets")

    #calo_deepcsv_roc   = makeRocPlot("Calo_deepcsv", "deepcsv", bkg="L_matchedCaloJet",sig="B_matchedCaloJet",dir="offJets")
    calo_csv_roc       = makeRocPlot("Calo_csv",     "CSVv2_l",     bkg="matchedCaloJet_L",sig="matchedCaloJet_B",dir="offJets")
    calo_deepcsv_roc   = makeRocPlot("Calo_deepcsv",  "DeepCSV_l",  bkg="matchedCaloJet_L",sig="matchedCaloJet_B",dir="offJets")

    off_deepcsv_roc   = makeRocPlot("Offline_deepcsv", "DeepCSV_l", bkg="matched_L",sig="matched_B",dir="offJets")
    off_csv_roc       = makeRocPlot("Offline_csv",     "CSVv2_l",     bkg="matched_L",sig="matched_B",dir="offJets")

    pf_csv_roc       = makeRocPlot("PF_csv",     "CSVv2_l",     bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")
    pf_deepcsv_roc   = makeRocPlot("PF_deepcsv",     "DeepCSV_l", bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")


    for i, rocType in enumerate(["Rej","Eff"]):
        plotSame("Off_deepcsv_vs_csv_"+rocType,
                 [off_deepcsv_roc[i], off_csv_roc[i]], 
                 [ROOT.kBlack, ROOT.kBlack],
                 [ROOT.kSolid, ROOT.kDashed],
                 plotOffJet = True,
                 plotCSV = True,
                 plotDeepCSV = True,
                 rocType = rocType
                 )

        plotSame("Calo_deepcsv_vs_csv_"+rocType,
                 [calo_deepcsv_roc[i], calo_csv_roc[i]], 
                 [ROOT.kRed, ROOT.kRed],
                 [ROOT.kSolid, ROOT.kDashed],
                 plotCaloJet = True,
                 plotCSV = True,
                 plotDeepCSV = True,
                 rocType = rocType
                 )

        plotSame("PF_deepcsv_vs_csv_"+rocType,
                 [calo_deepcsv_roc[i], calo_csv_roc[i]], 
                 [ROOT.kBlue, ROOT.kBlue],
                 [ROOT.kSolid, ROOT.kDashed],
                 plotPFJet = True,
                 plotCSV = True,
                 plotDeepCSV = True,
                 rocType = rocType
                 )


        plotSame("Off_vs_Calo_"+rocType,
                 [off_deepcsv_roc[i], off_csv_roc[i], calo_csv_roc[i], calo_deepcsv_roc[i]], 
                 [ROOT.kBlack, ROOT.kBlack,  ROOT.kRed  ,  ROOT.kRed   ],
                 [ROOT.kSolid, ROOT.kDashed, ROOT.kDashed,  ROOT.kSolid ],
                 plotOffJet = True,
                 plotCaloJet = True,
                 plotCSV = True,
                 plotDeepCSV = True,
                 rocType = rocType
                 )

        plotSame("Off_vs_PF_"+rocType,
                 [off_deepcsv_roc[i], off_csv_roc[i], pf_csv_roc[i], pf_deepcsv_roc[i]], 
                 [ROOT.kBlack, ROOT.kBlack,  ROOT.kBlue  ,  ROOT.kBlue   ],
                 [ROOT.kSolid, ROOT.kDashed, ROOT.kDashed,  ROOT.kSolid ],
                 plotPFJet = True,
                 plotOffJet = True,
                 plotCSV = True,
                 plotDeepCSV = True,
                 rocType = rocType
                 )


        plotSame("Off_vs_HLT_"+rocType,
                 [off_deepcsv_roc[i], off_csv_roc[i], calo_csv_roc[i], pf_csv_roc[i]], 
                 [ROOT.kBlack,       ROOT.kBlack,     ROOT.kRed  ,      ROOT.kBlue],
                 [ROOT.kSolid,      ROOT.kDashed,    ROOT.kDashed,      ROOT.kDashed],
                 plotCaloJet = True,
                 plotPFJet = True,
                 plotOffJet = True,
                 plotCSV = True,
                 plotDeepCSV = True,
                 rocType = rocType
                 )

    

#    vars = ["MV2c10_l","SV1_normdist", "IP3D", "IP2D"]
#    #vars += ["MV2c20","MV2c20_l"]
#    for v in vars:
#
#        print v
#        hlt_roc   = makeRocPlot("HLTRoc_"+v, "hlt_"+v, bkg="HLTJetsLF",sig="HLTJetsBQ",dir="boffperf_split")
#        # hlt_roc   = makeRocPlot("HLTRoc_"+v, v, bkg="OffJetsLF",sig="OffJetsBQ",dir="OffJets")
#        off_roc   = makeRocPlot("OffRoc_"+v, "off_"+v, bkg="offJetsLF",sig="offJetsBQ",dir="boffperf_split")
#
#                 
#
#        hlt_roc_c = makeRocPlot("HLTRoc_c_"+v, "hlt_"+v,bkg="HLTJetsCQ",sig="HLTJetsBQ",dir="boffperf_split", yTitle="Charm Rejection")
#        off_roc_c = makeRocPlot("OffRoc_c_"+v, "off_"+v,bkg="offJetsCQ",sig="offJetsBQ",dir="boffperf_split", yTitle="Charm Rejection")
#
#        plotSame("HLT_vs_Off_c_"+v,  
#                 [off_roc_c, hlt_roc_c], 
#                 [ROOT.kBlack, ROOT.kRed],
#                 [ROOT.kSolid, ROOT.kSolid],
#                 )
#
#
#        off_roc_00   = makeRocPlot("OffRoc00", "off_"+v,            bkg="offJetsLF",varNorm="off_"+v,sig="offJetsBQ",dir="boffperf_split")
#        off_roc_85   = makeRocPlot("OffRoc85", "off_match_hlt85_"+v,bkg="offJetsLF",varNorm="off_"+v,sig="offJetsBQ",dir="boffperf_split")
#        off_roc_77   = makeRocPlot("OffRoc77", "off_match_hlt77_"+v,bkg="offJetsLF",varNorm="off_"+v,sig="offJetsBQ",dir="boffperf_split")
#        off_roc_70   = makeRocPlot("OffRoc70", "off_match_hlt70_"+v,bkg="offJetsLF",varNorm="off_"+v,sig="offJetsBQ",dir="boffperf_split")
#        off_roc_60   = makeRocPlot("OffRoc60", "off_match_hlt60_"+v,bkg="offJetsLF",varNorm="off_"+v,sig="offJetsBQ",dir="boffperf_split")
#        off_roc_50   = makeRocPlot("OffRoc50", "off_match_hlt50_"+v,bkg="offJetsLF",varNorm="off_"+v,sig="offJetsBQ",dir="boffperf_split")
#        off_roc_40   = makeRocPlot("OffRoc40", "off_match_hlt40_"+v,bkg="offJetsLF",varNorm="off_"+v,sig="offJetsBQ",dir="boffperf_split")
#
#
#        workingPts_85 = []
#        for offlineCut in ["85", "77", "70", "60"]:
#            workingPts_85 .append(getWorkingPoint(var="off"+offlineCut+"_match_hlt85_"+v,
#                                                  sig="offJetsBQ",bkg="offJetsLF",varNorm="off_"+v,dir="boffperf_split"))
#
#
#        plotSame("Off_wrt_HLT_85_"+v,  
#                 [off_roc_00,  off_roc_85,   hlt_roc], 
#                 [ROOT.kBlack, ROOT.kBlue,   ROOT.kRed],
#                 [ROOT.kDashed, ROOT.kSolid, ROOT.kDashed],
#                 workingPts_85
#                 )
#
#        workingPts_77 = []
#        for offlineCut in ["85", "77", "70", "60"]:
#            workingPts_77 .append(getWorkingPoint(var="off"+offlineCut+"_match_hlt77_"+v,
#                                                  sig="offJetsBQ",bkg="offJetsLF",varNorm="off_"+v,dir="boffperf_split"))
#
#
#        plotSame("Off_wrt_HLT_77_"+v,  
#                 [off_roc_00,  off_roc_77,   hlt_roc], 
#                 [ROOT.kBlack, ROOT.kBlue,   ROOT.kRed],
#                 [ROOT.kDashed, ROOT.kSolid, ROOT.kDashed],
#                 workingPts_77,
#                 )
#
#
#        workingPts_70 = []
#        for offlineCut in ["85", "77", "70", "60"]:
#            workingPts_70 .append(getWorkingPoint(var="off"+offlineCut+"_match_hlt70_"+v,
#                                                  sig="offJetsBQ",bkg="offJetsLF",varNorm="off_"+v,dir="boffperf_split"))
#
#
#        plotSame("Off_wrt_HLT_70_"+v,  
#                 [off_roc_00,  off_roc_70,   hlt_roc], 
#                 [ROOT.kBlack, ROOT.kBlue,   ROOT.kRed],
#                 [ROOT.kDashed, ROOT.kSolid, ROOT.kDashed],
#                 workingPts_70,
#                 )
#
#        workingPts_60 = []
#        for offlineCut in ["85", "77", "70", "60"]:
#            workingPts_60 .append(getWorkingPoint(var="off"+offlineCut+"_match_hlt60_"+v,
#                                                  sig="offJetsBQ",bkg="offJetsLF",varNorm="off_"+v,dir="boffperf_split"))
#
#
#        plotSame("Off_wrt_HLT_60_"+v,  
#                 [off_roc_00,  off_roc_60,   hlt_roc], 
#                 [ROOT.kBlack, ROOT.kBlue,   ROOT.kRed],
#                 [ROOT.kDashed, ROOT.kSolid, ROOT.kDashed],
#                 workingPts_60,
#                 )
#
#
#        workingPts_50 = []
#        for offlineCut in ["85", "77", "70", "60"]:
#            workingPts_50 .append(getWorkingPoint(var="off"+offlineCut+"_match_hlt50_"+v,
#                                                  sig="offJetsBQ",bkg="offJetsLF",varNorm="off_"+v,dir="boffperf_split"))
#
#
#        plotSame("Off_wrt_HLT_50_"+v,  
#                 [off_roc_00,  off_roc_50,   hlt_roc], 
#                 [ROOT.kBlack, ROOT.kBlue,   ROOT.kRed],
#                 [ROOT.kDashed, ROOT.kSolid, ROOT.kDashed],
#                 workingPts_50,
#                 )
#
#
#        workingPts_40 = []
#        for offlineCut in ["85", "77", "70", "60"]:
#            workingPts_40 .append(getWorkingPoint(var="off"+offlineCut+"_match_hlt40_"+v,
#                                                  sig="offJetsBQ",bkg="offJetsLF",varNorm="off_"+v,dir="boffperf_split"))
#
#
#        plotSame("Off_wrt_HLT_40_"+v,  
#                 [off_roc_00,  off_roc_40,   hlt_roc], 
#                 [ROOT.kBlack, ROOT.kBlue,   ROOT.kRed],
#                 [ROOT.kDashed, ROOT.kSolid, ROOT.kDashed],
#                 workingPts_40,
#                 )
#
#
#
#        plotSame("Off_wrt_HLT_"+v,  
#                 [off_roc_00,  off_roc_85,   off_roc_77  , off_roc_70  , off_roc_60  , off_roc_50  , off_roc_40  , off_roc_00 , hlt_roc], 
#                 [ROOT.kBlack, ROOT.kBlue,   ROOT.kBlue  , ROOT.kBlue  , ROOT.kBlue  , ROOT.kBlue  , ROOT.kBlue  , ROOT.kBlack, ROOT.kRed],
#                 [ROOT.kSolid, ROOT.kDashed, ROOT.kDashed, ROOT.kDashed, ROOT.kDashed, ROOT.kDashed, ROOT.kDashed, ROOT.kSolid, ROOT.kDashed],
#                 )
#
#
#
#        # 70
#
#        for offlineCut in [85, 77, 70, 60]:
#            for onlineCut in [85, 77, 70, 60, 50, 40]:
#    
#                off_roc_offwrt_on_cut   = makeRocPlot("offwrton_cut_"+v, 
#                                                      "off"+str(offlineCut)+"_match_hlt"+str(onlineCut)+"_"+v,
#                                                      bkg="offJetsLF",
#                                                      varNorm="off_"+v,
#                                                      sig="offJetsBQ",
#                                                      dir="boffperf_split")
#    
#                off_roc_off   = makeRocPlot("off_cut_"+v, 
#                                            "off"+str(offlineCut)+"_"+v,
#                                            bkg="offJetsLF",
#                                            varNorm="off_"+v,
#                                            sig="offJetsBQ",
#                                            dir="boffperf_split")
#    
#         
#                
#                name =  "Off"+str(offlineCut)+"_wrt_HLT_"+str(onlineCut)+"Study"+v
#                can = ROOT.TCanvas(name,name)
#                can.cd().SetLogy(1)        
#                off_roc_00.Draw("AL")
#                
#                off_roc_off.SetLineColor(ROOT.kYellow)
#                off_roc_off.SetLineStyle(ROOT.kDashed)
#                off_roc_off.Draw("L")
#         
#                off_roc_offwrt_on_cut.SetLineColor(ROOT.kRed)
#                off_roc_offwrt_on_cut.SetLineStyle(ROOT.kDashed)
#                off_roc_offwrt_on_cut.Draw("L")
#         
#                can.SaveAs(o.outDir+"/roc_"+name+".pdf")        
#    



if __name__ == "__main__":
    main()

