import ROOT
from helpers import makeHist

class Efficiencies:

    def __init__(self,name,outFile):
        self.name = name
        self.thisDir = outFile.mkdir(self.name)

        self.ptM         = makeHist (self.thisDir, "ptEffM",         "Efficiency vs pt;Efficiency;pt",                 100,0,400) #M matched; T total
        self.etaM        = makeHist (self.thisDir, "etaEffM",        "Efficiency vs eta;Efficiency;eta",               100,-3,3)
        self.phiM        = makeHist (self.thisDir, "phiEffM",        "Efficiency vs phi;Efficiency;phi",               100,-3,3)
        self.massM       = makeHist (self.thisDir, "massEffM",       "Efficiency vs mass;Efficiency;mass",             100,0,200)
        self.deepcsvM    = makeHist (self.thisDir, "deepcsvEffM",    "Efficiency vs deepcsv;Efficiency;deepcsv",       100,0,100)
        self.deepcsv_bbM = makeHist (self.thisDir, "deepcsv_bbEffM", "Efficiency vs deepcsv_bb;Efficiency;deepcsv_bb", 100,-1,1)

        self.ptT         = makeHist (self.thisDir, "ptEffT",         "Efficiency vs pt;Efficiency;pt",                 100,0,400) #M matched; T total
        self.etaT        = makeHist (self.thisDir, "etaEffT",        "Efficiency vs eta;Efficiency;eta",               100,-3,3)
        self.phiT        = makeHist (self.thisDir, "phiEffT",        "Efficiency vs phi;Efficiency;phi",               100,-3,3)
        self.massT       = makeHist (self.thisDir, "massEffT",       "Efficiency vs mass;Efficiency;mass",             100,0,200)
        self.deepcsvT    = makeHist (self.thisDir, "deepcsvEffT",    "Efficiency vs deepcsv;Efficiency;deepcsv",       100,0,100)
        self.deepcsv_bbT = makeHist (self.thisDir, "deepcsv_bbEffT", "Efficiency vs deepcsv_bb;Efficiency;deepcsv_bb", 100,-1,1)

    def FillMatched(self,offJet): #get jet values and fill
        self.ptM         .Fill(offJet.pt)
        self.etaM        .Fill(offJet.eta)
        self.phiM        .Fill(offJet.phi)
        self.massM       .Fill(offJet.mass)
        self.deepcsvM    .Fill(offJet.deepcsv)
        self.deepcsv_bbM .Fill(offJet.deepcsv_bb)

    def fillTotal(self,offJet):
        self.ptT         .Fill(offJet.pt)
        self.etaT        .Fill(offJet.eta)
        self.phiT        .Fill(offJet.phi)
        self.massT       .Fill(offJet.mass)
        self.deepcsvT    .Fill(offJet.deepcsv)
        self.deepcsv_bbT .Fill(offJet.deepcsv_bb)

    def Write(self,outFile):
        self.pt         = self.ptM.Clone("pt")
        self.pt          .Divide(self.ptT)
        self.eta        = self.etaM.Clone("eta")
        self.eta         .Divide(self.etaT)
        self.phi        = self.phiM.Clone("phi")
        self.phi         .Divide(self.phiT)
        self.mass       = self.massM.Clone("mass")
        self.mass        .Divide(self.massT)
        self.deepcsv    = self.deepcsvM.Clone("deepcsv")
        self.deepcsv     .Divide(self.deepcsvT)
        self.deepcsv_bb = self.deepcsv_bbM.Clone("deepcsv_bb")
        self.deepcsv_bbT .Divide(self.deepcsv_bbT)

        self.thisDir.cd()
        
        self.pt         .Write()
        self.eta        .Write()
        self.phi        .Write()
        self.mass       .Write()
        self.deepcsv    .Write()
        self.deepcsv_bb .Write()

        outFile.cd()
