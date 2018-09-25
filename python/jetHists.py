import ROOT

class jetHists:

    def __init__(self,name):
        
        self.name = name
        self.pt  = ROOT.TH1F(self.name+"_pt","pt",100,0,400)
        #self.eta = 
        #self.phi = 
        #self.mass =
        # add more here

        
    def Fill(self,jetInfo):
        self.pt.Fill(jetInfo.pt)
        #


    def Write(self,outFile):
        outFile.mkdir(self.name).cd()
        self.pt.Write()
        # ...
