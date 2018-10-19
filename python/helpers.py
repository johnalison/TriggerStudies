import ROOT

def makeHist(directory,name,title,bins,low,high):
    h = ROOT.TH1F(name,title,bins,low,high)
    h.SetDirectory(directory)
    return h
