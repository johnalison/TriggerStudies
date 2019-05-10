import ROOT
import math,sys

def run(path):
    f = ROOT.TFile(path,"READ")

    JetVars,TrackVars = [],[]
    varFile = open('../vars.txt','r') #TESTVARS.txt for pt only
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
        outFile = open('%s.txt' % var,'a')
        matched = f.Get("offJets_matched/%s" % var)
        for bin in range(matched.GetNbinsX()):
            low  = matched.GetXaxis().GetBinLowEdge(bin)
            high = low + matched.GetXaxis().GetBinWidth(bin)
#            print high
            line = '%f , %f\n' % (low,high)
            outFile.write(line)

    for var in TrackVars:
        outFile = open('%s.txt' % var,'a')
        pfFake  = f.Get("pfTracks_unmatched/%s" % var)
        for bin in range(pfFake.GetNbinsX()):
            low  = pfFake.GetXaxis().GetBinLowEdge(bin)
            high = low + pfFake.GetXaxis().GetBinWidth(bin)
            line = '%f , %f\n' % (low,high)
            outFile.write(line)

run("../TestFileOutput.root")
sys.exit(1)
