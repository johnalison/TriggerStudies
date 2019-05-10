import ROOT
import sys,random,math
import numpy as np
from ROOT import TH1F,TCanvas
from makePlots import Plotter

def run(path):
    f = ROOT.TFile(path,"READ")

    JetVars,TrackVars = [],[]
    varFile = open('vars.txt','r') #TESTVARS.txt for pt only
#    varFile = open('TESTVARS.txt','r')
    jets = True
    for line in varFile.read().splitlines():
        if line == "":continue
        if line == "Jets":
            jets = True
            continue
        if line == "Tracks":
            jets = False
            continue
    
        if jets:JetVars.append(line)
        else:TrackVars.append(line)

    for var in JetVars:
        plotter = None
        total   = f.Get("offJets/%s" % var)
        matched = f.Get("offJets_matched/%s" % var)
        num     = matched.Clone()
        total.Sumw2();matched.Sumw2();num.Sumw2()
        Matched,Total,Num = rebin([matched,total,num],var)
        Num.Divide(Total)
        plotter = Plotter(var,True,[Matched,Total,Num],True)
        a = plotter.plot()

    for var in TrackVars:
        plotter    = None
        pfTotal    = f.Get("pfTracks/%s" % var)
        offTotal   = f.Get("offTracks/%s" % var)
        pfFake     = f.Get("pfTracks_unmatched/%s" % var)
        offMatched = f.Get("offTracks_matched/%s" % var)
        offNum     = offMatched.Clone()
        pfNum      = pfFake.Clone()
        offTotal.Sumw2();offMatched.Sumw2();offNum.Sumw2()
        pfTotal.Sumw2();pfFake.Sumw2();pfNum.Sumw2()
        OffMatched,OffTotal,OffNum = rebin([offMatched,offTotal,offNum],var)
        PfFake,PfTotal,PfNum = rebin([pfFake,pfTotal,pfNum],var)
        OffNum.Divide(OffTotal); PfNum.Divide(PfTotal)
        OffTotal.GetYaxis().SetTitle('Entries')
        PfTotal.GetYaxis().SetTitle('Entries')
        offPlotter = Plotter(var,True,[OffMatched,OffTotal,OffNum],False)
        a = offPlotter.plot()
        pfPlotter  = Plotter(var,False,[PfFake,PfTotal,PfNum],False)
        b = pfPlotter.plot()

### Main rebinning function; reads low edges from txt file
def rebin(hists,var): ### What I will do is use the SAME bins for the three hists
# so they are compatible
    bins = getBins(var) # Hardcoded in file
 #   print('bins are',bins,'for %s' %var)
    return do_variable_rebinning(hists[0],bins),do_variable_rebinning(hists[1],bins),do_variable_rebinning(hists[2],bins)

def getBins(var):
    varFile = open('bins/%s.txt' % var,'r')
#    print(varFile.read().splitlines())
    bins = []
    for item in varFile.read().splitlines():
#        print(item.split())
        low = float(item.split()[0])
        bins.append(low)
    return np.asarray(bins)

### Variable rebinning script from Patrick Bryant
def do_variable_rebinning(hist,bins,debug=False):
    if debug: print "Doing var rebinning"
    a=hist.GetXaxis()
    if debug: print "bins are",bins
    newhist = ROOT.TH1F(hist.GetName()+"variableBins_"+str(random.random()),
                      hist.GetTitle()+";"+hist.GetXaxis().GetTitle()+";"+hist.GetYaxis().GetTitle(),
                      len(bins)-1, bins)
    histErrorOption = hist.GetBinErrorOption()
    newhist.SetBinErrorOption(histErrorOption)
    if not newhist.GetSumw2N(): newhist.Sumw2()
    newa=newhist.GetXaxis()
    if debug: print newa.GetXmin(),"-",newa.GetXmax()
    for b in range(1, hist.GetNbinsX()+1):
        newb=newa.FindBin(a.GetBinCenter(b))
        val=newhist.GetBinContent(newb)
        ratio_bin_widths=newa.GetBinWidth(newb)/a.GetBinWidth(b)
        if abs(ratio_bin_widths - int(ratio_bin_widths*1e6)/1.0e6) > 0.001: 
            print ratio_bin_widths,"NOT INTEGER RATIO OF BIN WITDHS!!!", abs(ratio_bin_widths - int(ratio_bin_widths*1e6)/1.0e6)
            print hist.GetName()
            raw_input()
        val=val+hist.GetBinContent(b)/ratio_bin_widths
        newhist.SetBinContent(newb,val)

        if not histErrorOption:#gaussian error bars
            err=newhist.GetBinError(newb)
            err=math.sqrt(err**2+(hist.GetBinError(b)/ratio_bin_widths)**2)
            newhist.SetBinError(newb,err)
        else: #poisson error bars
            errUp=newhist.GetBinErrorUp(newb)
            errUp=math.sqrt(errUp**2+hist.GetBinErrorUp(b)/ratio_bin_widths*hist.GetBinErrorUp(b)/ratio_bin_widths)
            #newhist.SetBinErrorUp(newb,errUp)
            errLow=newhist.GetBinErrorLow(newb)
            errLow=math.sqrt(errLow**2+(hist.GetBinErrorLow(b)/ratio_bin_widths)**2)
            #newhist.SetBinErrorLow(newb,errLow)

    #if "m4j_l__data" in str(hist): raw_input()

    return (newhist)

run("TestFileOutput.root")
sys.exit(1)
