### inFile = the output of saveROCs.py where ROC curve froms different cuts are saved in one ROOT File
### join the ROC curves together in one graph in the output ROOT file

import ROOT

inFile = ROOT.TFile("PFDeepCSV_ROCs_low.root","READ")

inFile.ls()

ptCuts = [
    "0p4",
    "0p9",
    "1p5",
    "2p0",
    "2p5",
    "5p0", 
    "7p5", 
    "10p0",
    "20p0",
    ]

graphs = []
for cut in ptCuts:
    #### need to edit depending on the names of inFiles
    graphs.append(inFile.Get("PtScan_low_"+cut+"_0720;2")) 
    #### need to edit depending on the names of inFiles

can = ROOT.TCanvas()
#can.cd().SetLogy(1)
#can.cd().SetLogx(1)
# draw axis
hist = ROOT.TH1F("Axis","PFDeepCSV_ROCs_LP;B-Jet Efficiency; Light Flavor Efficiency",2,0.6,1)
hist.GetYaxis().SetRangeUser(1e-3,0.6)
hist.SetStats(0)
hist.Draw()
# draw legend
leg = ROOT.TLegend(0.5, 0.6, 0.65, 0.89)
leg.SetHeader("Track Pt Cut at: ")

for iG, graph in enumerate(graphs):
    graph.SetLineColor(iG+1)
    graph.SetMarkerColor(iG+1)
    graph.Draw("PL")
    if ptCuts[iG] == "7p5" or ptCuts[iG] == "10p0" or ptCuts[iG] == "20p0":
        leg.AddEntry(graph, "("+ptCuts[iG]+"GeV )", "l") # add parentheses
    else:
        leg.AddEntry(graph, ptCuts[iG]+"GeV", "l")


leg.Draw()
can.SaveAs("0810low.root")

