import ROOT


class VtxDiffHists:
    def __init__(self,name):
        self.hPVzDiff_s  = ROOT.TH1F("PVxDiff_"+name+"_s", "PVDiff_"+name,100,-0.02,0.02)
        self.hPVzDiff    = ROOT.TH1F("PVxDiff_"+name+"",   "PVDiff_"+name,100,-0.2,0.2)
        self.hPVzDiff_l  = ROOT.TH1F("PVxDiff_"+name+"_l", "PVDiff_"+name,100,-2,2)
        self.hPVzDiff_vl = ROOT.TH1F("PVxDiff_"+name+"_vl","PVDiff_"+name,100,-20,20)

    def Fill(self,diff):
        self.hPVzDiff_s .Fill(diff)       
        self.hPVzDiff   .Fill(diff)
        self.hPVzDiff_l .Fill(diff)
        self.hPVzDiff_vl.Fill(diff)


    def Write(self):
        self.hPVzDiff_s .Write()       
        self.hPVzDiff   .Write()
        self.hPVzDiff_l .Write()
        self.hPVzDiff_vl.Write()


class EventHists:

    def __init__(self,name):
        self.name = name
        self.PVzDiff_offVsTrue   = VtxDiffHists("OffVsTrue")
        self.PVzDiff_FastVsOff   = VtxDiffHists("FastVsOff")
        self.PVzDiff_FPVPixVsOff = VtxDiffHists("FPVPixVsOff")
        self.PVzDiff_PixVsOff    = VtxDiffHists("PixVsOff")
        self.PVzDiff_PFVsOff     = VtxDiffHists("PFVsOff")
        self.PVzDiff_L3VsOff     = VtxDiffHists("L3VsOff")
        
    def Fill(self,eventData):
        self.PVzDiff_offVsTrue  .Fill(eventData.VerticesOff - eventData.trueVertex)
        self.PVzDiff_FastVsOff  .Fill(eventData.FastPrimaryVertex - eventData.VerticesOff)
        self.PVzDiff_FPVPixVsOff.Fill(eventData.FPVPixelVertices - eventData.VerticesOff)
        self.PVzDiff_PixVsOff   .Fill(eventData.PixelVertices - eventData.VerticesOff)
        self.PVzDiff_PFVsOff    .Fill(eventData.VerticesPF - eventData.VerticesOff)
        self.PVzDiff_L3VsOff    .Fill(eventData.VerticesL3 - eventData.VerticesOff)


    def Write(self,outFile):
        outFile.mkdir(self.name).cd()
        self.PVzDiff_offVsTrue  .Write()
        self.PVzDiff_FastVsOff  .Write()
        self.PVzDiff_FPVPixVsOff.Write()
        self.PVzDiff_PixVsOff   .Write()
        self.PVzDiff_PFVsOff    .Write()
        self.PVzDiff_L3VsOff    .Write()
