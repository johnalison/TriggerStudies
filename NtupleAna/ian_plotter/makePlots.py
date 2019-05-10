import ROOT as r
r.gROOT.SetBatch(1)
class Plotter:
# order is [matched/fake,total,num]
    def __init__(self,var,effsOrFakes,graphs,jetsOrTracks):
        #first bool is True if efficiency, False if fakes; 2nd is True
        #if Jets, False if Tracks
        self.var,self.effs,self.jets, = var,effsOrFakes,jetsOrTracks
        self.canvas = r.TCanvas('c','canvas',1000,1000)
   #     print('created canvas')
        self.graphs = graphs
        self.title = self.getTitle()
       # print(self.title)
        if len(self.graphs)==3:
            self.p1 = r.TPad('p1','p1',0.02,0.38,0.98,0.98)
        
            self.p2 = r.TPad('p2','p2',0.02,0.0,0.98,0.42)
        else: self.p1 = r.TPad('p1','p1',0.0,0.0,0.95,0.95)
  #      print('here')

    def plot(self):
        r.gStyle.SetOptStat(0)
        r.gStyle.SetOptTitle(0)
        self.canvas.cd()
        self.p1.Draw()
        self.p1.cd()
        color = r.kBlue if self.effs else r.kRed
        if len(self.graphs)>1:
            self.graphs[1].SetLineColor(1) #Total is black
            self.graphs[1].GetYaxis().SetTitleOffset(1.5)
            self.graphs[1].GetYaxis().SetRangeUser(0,1.1*self.graphs[1].GetBinContent(self.graphs[1].GetMaximumBin()))
            self.graphs[0].SetLineColor(color)
            self.graphs[1].SetMarkerStyle(20);self.graphs[0].SetMarkerStyle(20)
            self.graphs[1].SetMarkerColor(1);self.graphs[0].SetMarkerColor(color)
            self.graphs[0].SetLineWidth(2);self.graphs[1].SetLineWidth(2)
            self.graphs[1].GetYaxis().SetTitle(self.title)
            self.graphs[1].Draw("E")
            self.graphs[0].Draw("SAME")
            self.p1.Update()
        if len(self.graphs)==3:
            self.canvas.cd()
            self.p2.Draw()
            self.p2.cd()
            ratTitle = "Efficiency" if self.effs else "Fake Rate"
            self.graphs[2].GetYaxis().SetTitle(ratTitle)
            self.graphs[2].GetYaxis().SetTitleOffset(1.5)
            self.graphs[2].GetYaxis().SetRangeUser(0,1.2)
            self.graphs[2].SetMarkerColor(color)
            self.graphs[2].SetFillColor(color)
            self.graphs[2].SetLineColor(color)
            self.graphs[2].SetLineWidth(2)
            self.graphs[2].SetMarkerStyle(20)
            self.graphs[2].Draw("E")
            # draw line at 1 on ratio plot for comparison
            line = r.TLine(self.graphs[2].GetBinLowEdge(1),1,self.graphs[2].GetBinWidth(self.graphs[2].GetNbinsX()) +
                           self.graphs[2].GetBinLowEdge(self.graphs[2].GetNbinsX()),1) 
            line.SetLineColor(1)
            line.SetLineWidth(2)
            line.SetLineStyle(9)
            line.Draw("SAME")
            l = r.TLegend(0.7,0.83,0.98,0.98)
#            l.SetHeader(self.var)
            numTitle = "Fakes" if not self.effs else "Matched"
            l.AddEntry(self.graphs[0],numTitle)
            l.AddEntry(self.graphs[1],"Total")
            self.canvas.cd()
            l.Draw()
            self.p2.Update()

        self.canvas.Modified()
        self.canvas.Update()
        self.canvas.Show()
        folder = "Jets" if self.jets else "Tracks"
        self.canvas.SaveAs("PDFs/%s/%s_%s.pdf" % (folder,self.var,numTitle))
        self.canvas.SaveAs("PNGs/%s/%s_%s.png" % (folder,self.var,numTitle))
        self.p1.Close()
        self.p2.Close()
        return None

    def getTitle(self): # Actual y axis values are entries/bin width, so 
        # get min bin width 
        minWidth = 1000000
        units = {'ip2d':'cm','ip2d_err':'cm','ip2d_sig':'','ip3d':'cm','ip3d_err':'cm','ip3d_sig':'',
                 'trackDecayLenVal':'cm','trackDeltaR':'rad','trackEta':'rad','trackJetDistVal':'cm',
                 'trackMomentum':'GeV','trackPhi':'rad','trackPPar':'GeV','trackPtRatio':'','trackPtRel':'GeV',
                 'pt':'GeV','mass':'GeV'
        }
        for i in range(self.graphs[0].GetNbinsX()):
            width = self.graphs[0].GetXaxis().GetBinWidth(i)
            if width < minWidth:minWidth = width
#        print(self.var,self.var in units)
        if not (self.var in units):return "Entries"
        else:return "Entries / %f %s" % (minWidth,units[self.var])
