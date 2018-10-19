import ROOT
import optparse
parser = optparse.OptionParser()
parser.add_option('-i', '--inFileName',           dest="infileName",         default=None, help="Run in loop mode")
parser.add_option('-o', '--outFileName',          dest="outfileName",        default=None, help="Run in loop mode")
parser.add_option('-d', '--debug',                dest="debug",    action="store_true",       default=False, help="Run in loop mode")
o, a = parser.parse_args()

inFile = ROOT.TFile(o.infileName,"READ")
outFile= ROOT.TFile(o.outfileName,"RECREATE")

def makeROC(inFile,outFile,name,reject,select,debug=False):
    h_l = inFile.Get(reject)
    h_b = inFile.Get(select)

    nb = h_b.Integral(51,75)
    nl = h_l.Integral(51,75)

    e_b = []
    e_l = []
    r_l = []


    for bin in range(75,50,-1):
        ne_l = h_l.Integral(bin,75)
        if ne_l <= 0.0: continue

        e_b.append(h_b.Integral(bin,75)/nb)
        e_l.append(ne_l/nl)
        r_l.append(1./e_l[-1] if e_l[-1] > 0 else 1.0e9)

    ROC = ROOT.TGraph(len(e_l))
    ROC.SetName(name)
    for p in range(len(e_l)):
        ROC.SetPoint(p,ROOT.Double(e_b[p]),ROOT.Double(r_l[p]))
        

    if debug: 
        print "e_b:",e_b
        print "r_l:",r_l

    outFile.cd()
    ROC.Write()


makeROC(inFile,outFile,"offJets_ROC","offJets_L/deepcsv","offJets_B/deepcsv")
makeROC(inFile,outFile,"pfJets_matched_ROC","pfJets_matchedL/deepcsv","pfJets_matchedB/deepcsv")

inFile.Close()
outFile.Close()
