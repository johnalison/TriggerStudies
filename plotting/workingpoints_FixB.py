### take in a folder of root files with histograms, output pdfs with graph showing 
### light flavor efficiency vs cut given certain B-jet efficiency
# --inFolder aFolderWithHistsOutputFromRunningTriggerStudies
# --output outPutDitractory
import ROOT
import os
ROOT.gROOT.SetBatch(True)
import ROOTHelp.FancyROOTStyle
from JetLevelPlotUtils import getCMSText, getText

# parser
from optparse import OptionParser
p = OptionParser()
p.add_option('--inFolder', type = 'string', default = "", dest = 'inFolder', help = 'intput folder' )
p.add_option('--output', type = 'string', default = "WorkingPoints", dest = 'outDir', help = 'output dir' )
(o,a) = p.parse_args()

# store all files from folder in []files
path = o.inFolder
files = []
for r, d, f in os.walk(path): # r=root, d=directories, f = files
    for file in f:
        files.append(os.path.join(r, file))
print "Read in files: ", files

if not os.path.exists(o.outDir):
    os.mkdir(o.outDir)

def computebkgEff(inFile, var, bkg, sig, dir,workingpoint = 0.7, debug=False):
    # input signal and background
    sigNum = inFile.Get(dir+"_"+sig+"/"+var)
    bkgNum = inFile.Get(dir+"_"+bkg+"/"+var)
    sigDen = sigNum 
    bkgDen = bkgNum
    nbins = sigNum.GetNbinsX() # number of bins

    sigTot = sigDen.Integral(0,nbins+1) # total signal
    #print "total sig",sigTot
    bkgTot = bkgDen.Integral(0,nbins+1) # total background
    #print "total bkg",bkgTot
 
    for bin in range(nbins, 0, -1):
        thisSig = abs(sigNum.Integral(bin,nbins+1))
        thisBkg = abs(bkgNum.Integral(bin,nbins+1))
        sigEff = thisSig/sigTot
        bkgEff = thisBkg/bkgTot
        if bkgEff:
            bkgRej = 1.0/bkgEff
        if sigEff > workingpoint:
            cut = inFile.GetName()[:inFile.GetName().find(".")].replace("/","_")
            #print "sigeff: ",sigEff, "bkgeff: ",bkgEff 
            return sigEff, bkgEff

def makeWorkingPointsHists(workingpoint, cuts, bkgEffs):
    c1 = ROOT.TCanvas("c1", "Light Flavor Efficiency as B-Jet Efficiency fixed to "+str(workingpoint))
    c1.SetGrid()
    gr = ROOT.TGraph(len(cuts))
    #print("in make working points hists:", cuts, bkgEffs)
    for i in range(len(cuts)):
        gr.SetPoint(i,cuts[i],bkgEffs[i])    
    gr.GetXaxis().SetTitle("TrackPtCut/GeV")
    gr.GetYaxis().SetTitle("Light-Flavor Efficiency")
    gr.SetLineColor( 2 )
    gr.SetLineWidth( 4 )
    gr.SetMarkerColor( 4 )
    gr.SetMarkerStyle( 21 )
    gr.SetTitle("Light Flavor Efficiency as B-Jet Efficiency fixed to "+str(workingpoint))
    gr.Draw("ALP")
    cmsLine1, cmsLine2 = getCMSText(xStart=0.2,yStart=0.875,subtext="B-Jet Efficiency fixed to "+str(workingpoint))
    cmsLine1.Draw("same")
    cmsLine2.Draw("same")
    c1.Update()
    c1.GetFrame().SetFillColor( 21 )
    c1.GetFrame().SetBorderSize( 12 )
    c1.Modified()
    c1.Update()
    c1.SaveAs(o.outDir+"/"+str(workingpoint*100)+"_high.pdf")

def nametoCut(name):
    if "0p4" in name:
        return 0.4
    if "0p9" in name:
        return 0.9
    if "1p5" in name:
        return 1.5
    if "2p0" in name:
        return 2.0
    if "2p5" in name:
        return 2.5    

def main():
    workingpoints = [0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95]
    for workingpoint in workingpoints:
        cuts = []
        sigEffs = []
        bkgEffs = []
        for f in files:
            inFile  = ROOT.TFile(f,  "READ")
            #print(inFile)
	    #print(inFile.GetName())
            sigEff, bkgEff = computebkgEff(inFile, "DeepCSV_l", bkg="matchedJet_L", sig="matchedJet_B", dir="offJets", workingpoint = workingpoint)
            cut = nametoCut(f)
            cuts.append(cut)
            sigEffs.append(sigEff)
            bkgEffs.append(bkgEff)
        #print("at"+str(workingpoint)+"  bkgEffs[]:", bkgEffs)
        makeWorkingPointsHists(workingpoint, cuts, bkgEffs)

if __name__ == "__main__":
    main()
