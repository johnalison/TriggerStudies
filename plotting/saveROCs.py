### extract multiple ROC Plots of the same variable from different root files in a folder and store them in one output root file
# --inFolder aFolderOfROOTFiles(HistsOutputFromRunningTriggerStudies)
# --outroot NameOfOutputRootFileWithIndividualGraphs
# --var name of the variable about wich the ROC plots are to be extracted, e.g., "PF_deepcsv"
import ROOT
import os
ROOT.gROOT.SetBatch(True)
import ROOTHelp.FancyROOTStyle

# parser
from optparse import OptionParser
p = OptionParser()
p.add_option('--input', type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile', help = 'intput file' )
p.add_option('--inFolder', type = 'string', default = "", dest = 'inFolder', help = 'intput folder' )
p.add_option('--output', type = 'string', default = "makeRocCurves", dest = 'outDir', help = 'output dir' )
p.add_option('--outroot', type = 'string', default ='outputroot', dest = 'outrootName', help = 'output root file name')
p.add_option('--var', type = 'string', default ='PF_deepcsv', dest = 'varName', help = 'hist to be extracted')
p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
p.add_option('--doCaloJets', action="store_true", help = '' )
(o,a) = p.parse_args()

# store all files from folder in []files
path = o.inFolder
files = []
for r, d, f in os.walk(path): # r=root, d=directories, f = files
    for file in f:
        files.append(os.path.join(r, file))
print(files)

if not os.path.exists(o.outDir):
    os.mkdir(o.outDir)

from rocCurveUtils     import makeRoc
from JetLevelPlotUtils import getCMSText, getText

outrootName = o.outrootName
varName = o.varName
hfile = ROOT.TFile(outrootName, "UPDATE")

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
        temproc = makeRoc(sigHist, sigNormHist, bkgHist, bkgNormHist,doErr=False,bkgMode=config[0],cleanNoCut=True,debug=debug)
        rocPlots.append(temproc)
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
        if name == varName:
            hfile.cd()
            ### the next line might need to change depending on the name of inFile
            rocPlots[-1].Write(inFile.GetName()[:inFile.GetName().find(".")].replace("/","_")) # write the current rocPlot into 
    return rocPlots
    
def plotSame(inFile, name,graphs,colors,styles, plotCaloJet=False, plotPFJet=False, plotOffJet=False,plotCSV=False,plotDeepCSV=False,workingPts= None,rocType=None):

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


#
#
#
def main():
    for f in files:
        inFile  = ROOT.TFile(f,  "READ")
        print(inFile)
	print(inFile.GetName())
        off_deepcsv_roc   = makeRocPlot(inFile, "Offline_deepcsv", "DeepCSV_l", bkg="matched_L",sig="matched_B",dir="offJets")
        off_csv_roc       = makeRocPlot(inFile, "Offline_csv",     "CSVv2_l",     bkg="matched_L",sig="matched_B",dir="offJets")

        pf_csv_roc       = makeRocPlot(inFile, "PF_csv",     "CSVv2_l",     bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")
        pf_deepcsv_roc   = makeRocPlot(inFile, "PF_deepcsv",     "DeepCSV_l", bkg="matchedJet_L",sig="matchedJet_B",dir="offJets")


        for i, rocType in enumerate(["Rej","Eff"]):
            plotSame(inFile, "Off_vs_HLT_All_"+rocType,
                     [off_deepcsv_roc[i], off_csv_roc[i], pf_deepcsv_roc[i],  pf_csv_roc[i]], 
                     [ROOT.kBlack,       ROOT.kBlack,     ROOT.kBlue,         ROOT.kBlue],
                     [ROOT.kSolid,      ROOT.kDashed,     ROOT.kSolid,        ROOT.kDashed],
                     plotCaloJet = False,
                     plotPFJet = True,
                     plotOffJet = True,
                     plotCSV = True,
                     plotDeepCSV = True,
                     rocType = rocType
                     )

if __name__ == "__main__":
    main()
