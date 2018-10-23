import ROOT
import optparse
parser = optparse.OptionParser()
parser.add_option('-i', '--inFileName',           dest="infileName",         default=None, help="Run in loop mode")
parser.add_option('-o', '--outFileName',          dest="outfileName",        default=None, help="Run in loop mode")
parser.add_option('-d', '--debug',                dest="debug",    action="store_true",       default=False, help="Run in loop mode")
o, a = parser.parse_args()

inFile = ROOT.TFile(o.infileName,"READ")
outFile= ROOT.TFile(o.outfileName,"RECREATE")

def makeROC(inFile,outFile,name,reject,select,debug=False,reject_denom=None,select_denom=None):
    print name
    h_l = inFile.Get(reject)
    h_b = inFile.Get(select)
    up = h_b.GetXaxis().FindBin(1.0)

    nb = h_b.Integral(0,up)
    nl = h_l.Integral(0,up)

    if reject_denom: 
        nl = inFile.Get(reject_denom).Integral(0,up)
    if select_denom:
        nb = inFile.Get(select_denom).Integral(0,up)

    e_b = []
    e_l = []
    r_l = []

    wp60 = None
    wp70 = None
    wp80 = None
    wp90 = None
    ne_l_previous = 0
    ne_b_previous = 0
    for bin in range(up,-1,-1):
        ne_l = h_l.Integral(bin,up)
        if ne_l <= 0.0: continue
        ne_b = h_b.Integral(bin,up)
        #if ((ne_l + ne_b) - (ne_l_previous + ne_b_previous))/(ne_l + ne_b)**0.5 < 2 and bin != up: continue
        if (ne_l - ne_l_previous)/ne_l < 0.15 and bin != 0: continue
        ne_l_previous = ne_l
        ne_b_previous = ne_b

        x = h_b.GetBinLowEdge(bin)
        
        e_b.append(ne_b/nb)
        e_l.append(ne_l/nl)
        r_l.append(nl/ne_l)

        if e_b[-1] > 0.6 and not wp60: 
            wp60 = x
            print " wp60 DeepCSV >",wp60,"(actual efficiency = "+str(e_b[-1])+")"
        if e_b[-1] > 0.7 and not wp70: 
            wp70 = x
            print " wp70 DeepCSV >",wp70,"(actual efficiency = "+str(e_b[-1])+")"
        if e_b[-1] > 0.8 and not wp80: 
            wp80 = x
            print " wp80 DeepCSV >",wp80,"(actual efficiency = "+str(e_b[-1])+")"
        if e_b[-1] > 0.9 and not wp90: 
            wp90 = x
            print " wp90 DeepCSV >",wp90,"(actual efficiency = "+str(e_b[-1])+")"


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
makeROC(inFile,outFile,"offJets_matched_ROC","offJets_L_matched/deepcsv_matched","offJets_B_matched/deepcsv_matched")
makeROC(inFile,outFile,"pfJets_matched_ROC","pfJets_matchedL/deepcsv","pfJets_matchedB/deepcsv")
makeROC(inFile,outFile,"offJets_matched_online60_ROC",
        "offJets_L_matched_online60/deepcsv",
        "offJets_B_matched_online60/deepcsv",
        False,
        "offJets_L_matched/deepcsv",
        "offJets_B_matched/deepcsv")
makeROC(inFile,outFile,"offJets_matched_online70_ROC",
        "offJets_L_matched_online70/deepcsv",
        "offJets_B_matched_online70/deepcsv",
        False,
        "offJets_L_matched/deepcsv",
        "offJets_B_matched/deepcsv")
makeROC(inFile,outFile,"offJets_matched_online80_ROC",
        "offJets_L_matched_online80/deepcsv",
        "offJets_B_matched_online80/deepcsv",
        False,
        "offJets_L_matched/deepcsv",
        "offJets_B_matched/deepcsv")
makeROC(inFile,outFile,"offJets_matched_online90_ROC",
        "offJets_L_matched_online90/deepcsv",
        "offJets_B_matched_online90/deepcsv",
        False,
        "offJets_L_matched/deepcsv",
        "offJets_B_matched/deepcsv")

inFile.Close()
outFile.Close()
