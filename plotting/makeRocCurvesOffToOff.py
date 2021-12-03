import ROOT
ROOT.gErrorIgnoreLevel = ROOT.kWarning


ROOT.gROOT.SetBatch(True)
ROOT.gErrorIgnoreLevel = ROOT.kWarning

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


    return (sigEff, bkgRej)

def makeRocPlot(name, var, bkg, sig, indir, varNorm=None,debug=False,vsLight=True, vsLandPU=False):
    sigHist = inFile.Get(indir+sig+"/"+var)
    bkgHist = inFile.Get(indir+bkg+"/"+var)
    
    if not sigHist:
        print("ERROR: cannot get",indir+sig+"/"+var)
        print(sigHist)

    if varNorm:
        sigNormHist = inFile.Get(indir+sig+"/"+varNorm)
        bkgNormHist = inFile.Get(indir+bkg+"/"+varNorm)
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
        elif vsLandPU: yTitle = "Light Flavor (w/PU) "
        else:       yTitle = "C-Jet "
        
        if config[0] == "Rej":    yTitle +="Rejection"
        elif config[0] == "Eff":  yTitle +="Efficiency"
        rocPlots[-1].GetYaxis().SetTitle(yTitle)
        rocPlots[-1].GetYaxis().SetRangeUser(config[1],config[2])
        rocPlots[-1].Draw("AL")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".pdf")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".png")
    return rocPlots


def plotSame(name,graphs,colors,styles, workingPts= None,rocType=None,plotDeepCSV=False,plotDeepJet=False, taggerNames=[], coloredText=[], logy=True, yMin=1e-4, xMin=0.3):

    can = ROOT.TCanvas(name,name)
    if logy:
        can.cd().SetLogy(1)
    hist_axis = ROOT.TH1F("hist_axis","hist_axis",1,xMin,1)
    hist_axis.GetYaxis().SetTitle(graphs[0].GetYaxis().GetTitle())
    hist_axis.GetXaxis().SetTitle(graphs[0].GetXaxis().GetTitle())
    hist_axis.Draw()

    xMax = 1 
    hist_axis.GetXaxis().SetRangeUser(xMin,xMax)
    hist_axis.GetYaxis().SetRangeUser(yMin,1)

    line = ROOT.TF1("guessing","x",xMin,xMax)
    line.SetLineColor(ROOT.kGray)
    line.SetLineStyle(10)
    line.Draw("same")
    #line.DrawLine(max(xMin,yMin), 1*max(xMin,yMin), xMax, 1.0*xMax)

    for gItr, g in enumerate(graphs):
        g.SetLineColor(colors[gItr])
        g.SetLineStyle(styles[gItr])
        #if not gItr:
        #    g.Draw("AL")
        #else:
        #    g.Draw("L")
        g.Draw("L")

    if not workingPts == None:
        g_wrkPts = ROOT.TGraph(len(workingPts))
        g_wrkPts.SetMarkerSize(2)
        g_wrkPts.SetMarkerColor(colors[1])
        g_wrkPts.SetMarkerStyle(34)
        for wpItr, wp in enumerate(workingPts):
            #print wpItr,wp

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



    for t in taggerNames:
        yStart = yStart - 0.05
        deepCSVText   = getText(t,xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kRed+2)
        deepCSVText.Draw("same")


    cTexts = [ ]
    for iCt, ct in enumerate(coloredText):
        yStart = yStart - 0.05
        cTexts.append(getText(ct,xStart=xStart,yStart=yStart,size=0.04,color=colors[2*iCt]))
        cTexts[-1].Draw("same")



    yStart = yStart - 0.05
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

    mon_roc = {}
    ref_roc = {}

    mon_roc_all = {}
    ref_roc_all = {}

    mon_roc_C = {}
    ref_roc_C = {}

    mon_roc_all_C = {}
    ref_roc_all_C = {}

    mon_roc_LandPU = {}
    ref_roc_LandPU = {}


    taggers = [("DeepCSV","DeepCSV_l"),
               ("DeepJet","deepFlavB"),
               ("cMVAv2", "cMVAv2"),
               ("CombIVF", "CombIVF"),
               ("Svx", "Svx"),
               ("SvxHP", "SvxHP"),
               ("Bprob", "Bprob"),
               ("Proba", "Proba",{"xMin":0}),
               ("Ip2P", "Ip2P_l"),
               ("Ip3P", "Ip3P_l"),
               ("SoftMu", "SoftMu"),
               ("SoftEl", "SoftEl"),
               ("neutralHadronMultiplicity","btags/neutralHadronMultiplicity",{"logy":False,"yMin":0.1}),
               ("chargedHadronMultiplicity","btags/chargedHadronMultiplicity",{"logy":False,"yMin":0.1}),
               ("photonMultiplicity","btags/photonMultiplicity",{"logy":False,"yMin":0.1}),
    ]

    for tag in taggers:
        
        mon_roc[tag[0]]          = makeRocPlot("Mon_"+tag[0],          tag[1], bkg="matchedJet_L",      sig="matchedJet_B",    indir="offJets_")
        mon_roc_all[tag[0]]      = makeRocPlot("Mon_all"+tag[0],       tag[1], bkg="pfJets_L",          sig="pfJets_B",      indir="")
        mon_roc_all_C[tag[0]]    = makeRocPlot("Mon_all_C"+tag[0],     tag[1], bkg="pfJets_C",          sig="pfJets_B",      indir="")
        mon_roc_LandPU[tag[0]]   = makeRocPlot("Mon_LandPU_"+tag[0],   tag[1], bkg="matchedJet_LandPU", sig="matchedJet_B",    indir="offJets_", vsLight=False, vsLandPU=True)
        mon_roc_C[tag[0]]        = makeRocPlot("Mon_C_"+tag[0],        tag[1], bkg="matchedJet_C",      sig="matchedJet_B",    indir="offJets_", vsLight=False)


        ref_roc[tag[0]]        = makeRocPlot("Ref_"+tag[0],        tag[1], bkg="matched_L",      sig="matched_B",  indir="offJets_")
        ref_roc_all[tag[0]]    = makeRocPlot("Ref_all"+tag[0],     tag[1], bkg="offJets_L",      sig="offJets_B",      indir="")
        ref_roc_all_C[tag[0]]  = makeRocPlot("Ref_all_C_"+tag[0],  tag[1], bkg="offJets_C",      sig="offJets_B",      indir="")
        ref_roc_LandPU[tag[0]] = makeRocPlot("Ref_LandPU_"+tag[0], tag[1], bkg="matched_LandPU", sig="matched_B",    indir="offJets_", vsLight=False, vsLandPU=True)
        ref_roc_C[tag[0]]      = makeRocPlot("Ref_C_"+tag[0],      tag[1], bkg="matched_C",      sig="matched_B",  indir="offJets_", vsLight=False)



    
    #
    #  Pt Study
    #
    ptBins = ["50","100","300","10000"]

    mon_roc_pt = {}
    ref_roc_pt = {}

    mon_roc_C_pt = {}
    ref_roc_C_pt = {}

    taggersPt = [("DeepJet","deepFlavB"),
               ("Proba", "Proba"),
               ]

    for tag in taggersPt:

        mon_roc_pt[tag[0]] = {}
        ref_roc_pt[tag[0]] = {}

        mon_roc_C_pt[tag[0]] = {}
        ref_roc_C_pt[tag[0]] = {}


        for ptB in ptBins:
            
            #mon_roc_pt[tag[0]][ptB]   = makeRocPlot("Mon_"+tag[0]+"_pt"+ptB,    tag[1]+"_pt"+ptB, bkg="matchedJet_L",   sig="matchedJet_B",   indir="offJets_")
            #mon_roc_C_pt[tag[0]][ptB] = makeRocPlot("Mon_"+tag[0]+"_C_pt"+ptB,  tag[1]+"_pt"+ptB, bkg="matchedJet_C",   sig="matchedJet_B",  indir="offJets_", vsLight=False)
            #
            #ref_roc_pt[tag[0]][ptB]   = makeRocPlot("Ref_"+tag[0]+"_pt"+ptB,    tag[1]+"_pt"+ptB, bkg="matched_L",      sig="matched_B",indir="offJets_")
            #ref_roc_C_pt[tag[0]][ptB] = makeRocPlot("Ref_"+tag[0]+"_C_pt"+ptB,  tag[1]+"_pt"+ptB, bkg="matched_C",      sig="matched_B",indir="offJets_", vsLight=False)
    
            mon_roc_pt[tag[0]][ptB]   = makeRocPlot("Mon_"+tag[0]+"_pt"+ptB,    tag[1]+"_pt"+ptB, bkg="pfJets_L",       sig="pfJets_B",   indir="")
            mon_roc_C_pt[tag[0]][ptB] = makeRocPlot("Mon_"+tag[0]+"_C_pt"+ptB,  tag[1]+"_pt"+ptB, bkg="pfJets_C",       sig="pfJets_B",   indir="", vsLight=False)
            ref_roc_pt[tag[0]][ptB]   = makeRocPlot("Ref_"+tag[0]+"_pt"+ptB,    tag[1]+"_pt"+ptB, bkg="offJets_L",      sig="offJets_B",  indir="")
            ref_roc_C_pt[tag[0]][ptB] = makeRocPlot("Ref_"+tag[0]+"_C_pt"+ptB,  tag[1]+"_pt"+ptB, bkg="offJets_C",      sig="offJets_B",  indir="", vsLight=False)
    

    #
    #  Eta Study
    #
    etaBins = ["0.5","1","1.5","2","2.5"]

    mon_roc_eta = {}
    ref_roc_eta = {}

    mon_roc_C_eta = {}
    ref_roc_C_eta = {}

    for tag in taggersPt:

        mon_roc_eta[tag[0]] = {}
        ref_roc_eta[tag[0]] = {}

        mon_roc_C_eta[tag[0]] = {}
        ref_roc_C_eta[tag[0]] = {}


        for etaB in etaBins:
            
            #mon_roc_eta  [tag[0]][etaB] = makeRocPlot("Mon_"+tag[0]+"_eta"+etaB,    tag[1]+"_eta"+etaB, bkg="matchedJet_L",   sig="matchedJet_B",   indir="offJets_")
            #mon_roc_C_eta[tag[0]][etaB] = makeRocPlot("Mon_"+tag[0]+"_C_eta"+etaB,  tag[1]+"_eta"+etaB, bkg="matchedJet_C",   sig="matchedJet_B",   indir="offJets_", vsLight=False)
            #ref_roc_eta  [tag[0]][etaB] = makeRocPlot("Ref_"+tag[0]+"_eta"+etaB,    tag[1]+"_eta"+etaB, bkg="matched_L",      sig="matched_B",indir="offJets_")
            #ref_roc_C_eta[tag[0]][etaB] = makeRocPlot("Ref_"+tag[0]+"_C_eta"+etaB,  tag[1]+"_eta"+etaB, bkg="matched_C",      sig="matched_B",indir="offJets_", vsLight=False)
    
            mon_roc_eta  [tag[0]][etaB] = makeRocPlot("Mon_"+tag[0]+"_eta"+etaB,    tag[1]+"_eta"+etaB, bkg="pfJets_L",       sig="pfJets_B",   indir="")
            mon_roc_C_eta[tag[0]][etaB] = makeRocPlot("Mon_"+tag[0]+"_C_eta"+etaB,  tag[1]+"_eta"+etaB, bkg="pfJets_C",       sig="pfJets_B",   indir="", vsLight=False)
            ref_roc_eta  [tag[0]][etaB] = makeRocPlot("Ref_"+tag[0]+"_eta"+etaB,    tag[1]+"_eta"+etaB, bkg="offJets_L",      sig="offJets_B",indir="")
            ref_roc_C_eta[tag[0]][etaB] = makeRocPlot("Ref_"+tag[0]+"_C_eta"+etaB,  tag[1]+"_eta"+etaB, bkg="offJets_C",      sig="offJets_B",indir="", vsLight=False)
    


    for i, rocType in enumerate(["Rej","Eff"]):


        for tag in taggers:
            kw = {}
            if len(tag) > 2: 
                kw = tag[2]
                


            plotSame(tag[0]+"_"+rocType,
                     [mon_roc[tag[0]][i], ref_roc[tag[0]][i]],
                     [ROOT.kBlack,      ROOT.kBlack],
                     [ROOT.kDashed,     ROOT.kSolid],
                     taggerNames = [tag[0]],
                     plotDeepJet = False,
                     plotDeepCSV = False,
                     rocType = rocType,
                     **kw
            )

            plotSame(tag[0]+"_all_"+rocType,
                     [mon_roc_all[tag[0]][i], ref_roc_all[tag[0]][i]],
                     [ROOT.kBlack,      ROOT.kBlack],
                     [ROOT.kDashed,     ROOT.kSolid],
                     taggerNames = [tag[0]],
                     plotDeepJet = False,
                     plotDeepCSV = False,
                     rocType = rocType,
                     **kw
            )


            plotSame(tag[0]+"_LandPU_"+rocType,
                     [mon_roc_LandPU[tag[0]][i], ref_roc_LandPU[tag[0]][i]],
                     [ROOT.kBlack,      ROOT.kBlack],
                     [ROOT.kDashed,     ROOT.kSolid],
                     taggerNames = [tag[0]],
                     plotDeepJet = False,
                     plotDeepCSV = False,
                     rocType = rocType,
                     **kw
            )



            plotSame(tag[0]+"_C_"+rocType,
                     [mon_roc_C[tag[0]][i], ref_roc_C[tag[0]][i]],
                     [ROOT.kBlack,      ROOT.kBlack],
                     [ROOT.kDashed,     ROOT.kSolid],
                     taggerNames = [tag[0]],
                     plotDeepJet = False,
                     plotDeepCSV = False,
                     rocType = rocType,
                     **kw
                 )



        all_rocs = []
        all_rocs_C = []
        all_styles = []
        all_colors = []
        
        def addToAll(roc,roc_c,style,color):
            all_rocs.append(roc)
            all_rocs_C.append(roc_c)
            all_styles.append(style)
            all_colors.append(color)

        def addTaggerToAll(name, color):
            #addToAll(mon_roc[name][i], mon_roc_C[name][i], ROOT.kDashed, color)
            #addToAll(ref_roc[name][i], ref_roc_C[name][i], ROOT.kSolid,  color)

            addToAll(mon_roc_all[name][i], mon_roc_all_C[name][i], ROOT.kDashed, color)
            addToAll(ref_roc_all[name][i], ref_roc_all_C[name][i], ROOT.kSolid,  color)

            

        addTaggerToAll("DeepCSV", ROOT.kBlue)
        addTaggerToAll("DeepJet", ROOT.kBlack)


        plotSame("All_"+rocType,
                 all_rocs, all_colors, all_styles,
                 plotDeepCSV = True,
                 plotDeepJet = True,
                 rocType = rocType
             )



        plotSame("All_C_"+rocType,
                 all_rocs_C, all_colors, all_styles,
                 plotDeepCSV = True,
                 plotDeepJet = True,
                 rocType = rocType,
                 )


        addTaggerToAll("cMVAv2", ROOT.kRed)
        addTaggerToAll("CombIVF", ROOT.kOrange)
        addTaggerToAll("Svx", ROOT.kPink)
        addTaggerToAll("SvxHP", ROOT.kRed+2)
        addTaggerToAll("Bprob", ROOT.kGray)
        addTaggerToAll("Proba", ROOT.kGray+2)
        addTaggerToAll("Ip2P"  , ROOT.kGreen+2)
        addTaggerToAll("Ip3P"  , ROOT.kGreen)
        addTaggerToAll("SoftMu", ROOT.kMagenta)
        addTaggerToAll("SoftEl", ROOT.kMagenta+1)



        plotSame("All_Extra_"+rocType,
                 all_rocs, all_colors, all_styles,
                 rocType = rocType
                 )



        plotSame("All_Extra_C_"+rocType,
                 all_rocs_C, all_colors, all_styles,
                 rocType = rocType
                 )



        #
        #  Pt Study
        #
        pt_rocs_deepJet = []
        pt_rocs_deepJet_C = []
        pt_rocs_Proba = []
        pt_rocs_Proba_C = []
        pt_styles = []
        pt_colors = []
        pt_text = []
        
        def addToPt(rocs,rocs_c,name,i,style,color):
            pt_rocs_deepJet  .append(rocs  ["DeepJet"][name][i])
            pt_rocs_deepJet_C.append(rocs_c["DeepJet"][name][i])
            pt_rocs_Proba  .append(rocs  ["Proba"][name][i])
            pt_rocs_Proba_C.append(rocs_c["Proba"][name][i])

            pt_styles.append(style)
            pt_colors.append(color)

        def addPtToPt(name, color, text):
            pt_text.append(text)
            addToPt(mon_roc_pt, mon_roc_C_pt, name, i, ROOT.kDashed, color)
            addToPt(ref_roc_pt, ref_roc_C_pt, name, i, ROOT.kSolid,  color)


        addPtToPt("50",   ROOT.kBlack, "pt < 50 GeV")
        addPtToPt("100",  ROOT.kBlue,  "50 - 100 GeV")
        addPtToPt("300",  ROOT.kOrange,    "100 - 300 GeV")
        addPtToPt("10000",ROOT.kRed, "pt > 300 GeV")

        plotSame("DeepJetPtBins_"+rocType,
                 pt_rocs_deepJet, pt_colors, pt_styles,
                 plotDeepJet = False,
                 plotDeepCSV = False,
                 rocType = rocType,
                 coloredText = pt_text,
             )


        plotSame("DeepJetPtBins_C_"+rocType,
                 pt_rocs_deepJet_C, pt_colors, pt_styles,
                 plotDeepJet = False,
                 plotDeepCSV = False,
                 rocType = rocType,
                 coloredText = pt_text,
             )


        plotSame("ProbaPtBins_"+rocType,
                 pt_rocs_Proba, pt_colors, pt_styles,
                 plotDeepJet = False,
                 plotDeepCSV = False,
                 rocType = rocType,
                 coloredText = pt_text,
             )


        plotSame("ProbaPtBins_C_"+rocType,
                 pt_rocs_Proba_C, pt_colors, pt_styles,
                 plotDeepJet = False,
                 plotDeepCSV = False,
                 rocType = rocType,
                 coloredText = pt_text,
             )
        



        #
        #  Eta Study
        #
        eta_rocs_deepJet = []
        eta_rocs_deepJet_C = []
        eta_rocs_Proba = []
        eta_rocs_Proba_C = []
        eta_styles = []
        eta_colors = []
        eta_text = []
        
        def addToEta(rocs,rocs_c,name,i,style,color):
            eta_rocs_deepJet  .append(rocs  ["DeepJet"][name][i])
            eta_rocs_deepJet_C.append(rocs_c["DeepJet"][name][i])
            eta_rocs_Proba    .append(rocs  ["Proba"][name][i])
            eta_rocs_Proba_C  .append(rocs_c["Proba"][name][i])

            eta_styles.append(style)
            eta_colors.append(color)

        def addEtaToEta(name, color, text):
            eta_text.append(text)
            addToEta(mon_roc_eta, mon_roc_C_eta, name, i, ROOT.kDashed, color)
            addToEta(ref_roc_eta, ref_roc_C_eta, name, i, ROOT.kSolid,  color)


        addEtaToEta("0.5",  ROOT.kBlack, "|eta| < 0.5")
        addEtaToEta("1",    ROOT.kBlue,   "0.5 - 1.0")
        addEtaToEta("1.5",  ROOT.kRed,    "1.0 - 1.5")
        addEtaToEta("2",    ROOT.kOrange, "1.5 - 2.0")
        addEtaToEta("2.5",  ROOT.kGreen+2, "2.0 - 2.5")

        plotSame("DeepJetEtaBins_"+rocType,
                 eta_rocs_deepJet, eta_colors, eta_styles,
                 plotDeepJet = False,
                 plotDeepCSV = False,
                 rocType = rocType,
                 coloredText = eta_text,
             )


        plotSame("DeepJetEtaBins_C_"+rocType,
                 eta_rocs_deepJet_C, eta_colors, eta_styles,
                 plotDeepJet = False,
                 plotDeepCSV = False,
                 rocType = rocType,
                 coloredText = eta_text,
             )


        plotSame("ProbaEtaBins_"+rocType,
                 eta_rocs_Proba, eta_colors, eta_styles,
                 plotDeepJet = False,
                 plotDeepCSV = False,
                 rocType = rocType,
                 coloredText = eta_text,
             )


        plotSame("ProbaEtaBins_C_"+rocType,
                 eta_rocs_Proba_C, eta_colors, eta_styles,
                 plotDeepJet = False,
                 plotDeepCSV = False,
                 rocType = rocType,
                 coloredText = eta_text,
             )






if __name__ == "__main__":
    main()
