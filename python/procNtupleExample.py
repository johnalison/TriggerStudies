import optparse
parser = optparse.OptionParser()
parser.add_option('-i', '--inFileName',           dest="infileName",         default=None, help="Run in loop mode")
parser.add_option('-o', '--outFileName',          dest="outfileName",        default=None, help="Run in loop mode")
parser.add_option('-n', '--nevents',              dest="nevents",           default=None, help="Run in loop mode")
parser.add_option('-d', '--debug',                dest="debug",    action="store_true",       default=False, help="Run in loop mode")
o, a = parser.parse_args()

import ROOT
from array import array

#ROOT.gROOT.ProcessLine('.L Loader.C+')


inFile = ROOT.TFile(o.infileName,"READ")
print inFile

tree = inFile.Get("tree")
#tree.Print("*")
#print tree


#
# Input Data 
#
from eventData  import EventData
from jetInfo  import JetDataHandler
from leptonInfo  import LeptonDataHandler

eventData = EventData()
eventData.SetBranchAddress(tree)

pfJetsDB = JetDataHandler("pfJets")
pfJetsDB.SetBranchAddress(tree)

offJetsDB = JetDataHandler("offJets")
offJetsDB.SetBranchAddress(tree)

muonDB = LeptonDataHandler("offTightMuons")
muonDB.SetBranchAddress(tree)

elecDB = LeptonDataHandler("offTightElectrons")
elecDB.SetBranchAddress(tree)

#
# Make output ntuple/Hists
# 
from jetHists import JetHists
from eventHists import EventHists
outFile    = ROOT.TFile(o.outfileName,"recreate")

eventHists     = EventHists("AllEvents")
pfJetHistsPreOLap = JetHists("pfJetsPreOLap",outFile)
pfJetHists        = JetHists("pfJets",outFile)


offJetHistsPreOLap = JetHists("offJetsPreOLap",outFile)
offJetHists        = JetHists("offJets",outFile)

nEventThisFile = tree.GetEntries()

print( "Number of input events: %s" % nEventThisFile )

iEvent = 0


def failOverlap(jet,leptons):
    #print "thisJet",jet.vec.Eta(),jet.vec.Phi()
    for l in leptons:
        #print "\t",l.vec.Eta(),l.vec.Phi()
        if jet.vec.DeltaR(l.vec) < 0.4:
            return True
    return False

for entry in xrange( 0,nEventThisFile): # let's only run over the first 100 events for this example                                                         
    tree.GetEntry( entry )

    iEvent +=1
    
    if iEvent %10000 == 0:
        print "Processed .... ",iEvent,"Events"
    if o.nevents and (iEvent > int(o.nevents)):
        break

    if o.debug:
        print "RunNumber",runNumber[0],
        print "EventNumber",eventNumber[0]

    eventData.setEvent()

    #
    # Fill All events
    #
    eventHists.Fill(eventData)

    # Converting from "row-level" info to "column-level" info
    elecs  = elecDB.getLeps()
    muons  = muonDB.getLeps()
    pfJets = pfJetsDB.getJets()

    if len(elecs)+len(muons) < 2:
        continue
        
    
    for pfJet in pfJets:
        if abs(pfJet.eta) > 2.5: continue
        if pfJet.pt       < 35:  continue

        pfJetHistsPreOLap.Fill(pfJet)        
        if failOverlap(pfJet,elecs): continue
        if failOverlap(pfJet,muons): continue

        pfJetHists.Fill(pfJet)


    offJets = offJetsDB.getJets()
    for offJet in offJets:
        if abs(offJet.eta) > 2.5: continue
        if offJet.pt       < 35:  continue

        offJetHistsPreOLap.Fill(offJet)
        if failOverlap(offJet,elecs): continue
        if failOverlap(offJet,muons): continue

        offJetHists.Fill(offJet)

        
#
# Save Hists
#
pfJetHistsPreOLap.Write(outFile)
pfJetHists.Write(outFile)
offJetHistsPreOLap.Write(outFile)
offJetHists.Write(outFile)
eventHists.Write(outFile)
