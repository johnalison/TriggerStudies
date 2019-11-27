import ROOT
inFile1 = ROOT.TFile("HT_EffOnlineWrtOffline2018_v2.root","READ")
turnOn1 = inFile1.Get("ht330_pass_4b_rebin_ratio")

inFile2 = ROOT.TFile("HT_EffOnlineWrtOffline2018.root","READ")
turnOn2 = inFile2.Get("hT30_pass_3b_rebin_ratio")
turnOn2.SetLineColor(ROOT.kRed)
turnOn2.SetMarkerColor(ROOT.kRed)

inFile3 = ROOT.TFile("histTrigStudyNoL140/EffOnlineWrtOffline.root","READ")
#ht330_3tag_pass_4b_rebin_ratio
turnOn3 = inFile3.Get("ht330_sel_pass_4b_rebin_ratio")
turnOn3.SetLineColor(ROOT.kGreen)
turnOn3.SetMarkerColor(ROOT.kGreen)

#inFile3 = ROOT.TFile("histTrigStudyNewWL1/EffOnlineWrtOffline.root","READ")
turnOn4 = inFile3.Get("ht330_sel_3tag_pass_4b_rebin_ratio")
#turnOn4 = inFile3.Get("ht330_L1OR_pass_rebin_ratio")
turnOn4.SetLineColor(ROOT.kBlue)
turnOn4.SetMarkerColor(ROOT.kBlue)


can = ROOT.TCanvas("can","can")
can.cd()
turnOn1.Draw("")
#turnOn2.Draw("PL")
turnOn3.Draw("PL")
turnOn4.Draw("PL")

can.Update()
