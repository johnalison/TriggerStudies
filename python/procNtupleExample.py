import optparse
parser = optparse.OptionParser()
parser.add_option('-i', '--inFileName',           dest="infileName",         default=None, help="Run in loop mode")
parser.add_option('-o', '--outFileName',          dest="outfileName",        default=None, help="Run in loop mode")
parser.add_option('-n', '--nevents',              dest="nevents",           default=None, help="Run in loop mode")
parser.add_option('-d', '--debug',                dest="debug",    action="store_true",       default=False, help="Run in loop mode")
o, a = parser.parse_args()

import ROOT
from array import array

ROOT.gROOT.ProcessLine('.L Loader.C+')


inFile = ROOT.TFile(o.infileName,"READ")
print inFile

inFile.ls()
tree = inFile.Get("tree")
tree.Print("*")
print tree

#import sys
#sys.exit(-1)

#class trkInfo:
# 
#      ....

from jetInfo import jetInfoDB
from jetHists import jetHists

#pfJets_jetEta = array('f', [0,0,0,0,0,0] )

from eventData import eventData

event_data = eventData()
event_data.SetBranchAddress(tree)



pfJetsDB = jetInfoDB("pfJets")
pfJetsDB.SetBranchAddresses(tree)
pfJetHists = jetHists("pfJets")


#
# Make output ntuple
# 
outFile    = ROOT.TFile(o.outfileName,"recreate")
nEventThisFile = tree.GetEntries()

# pfJetHists = jetHists("pfJets",f) # Make "pfJets" in directory in output file 

print( "Number of input events: %s" % nEventThisFile )

iEvent = 0


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

    event_data.setEvent()
    print event_data.trueVertex,event_data.VerticesOff,event_data.FastPrimaryVertex

    # Converting from "row-level" info to "column-level" info
    pfJets = pfJetsDB.getJets()
    
    for pfJet in pfJets:
        pfJetHists.Fill(pfJet)

    #print pfJets.num[0], "vs",pfJets.trackSip3dSig.size()
    #print pfJets.trackSip3dSig
    #for iJet in range(pfJets.num[0]):
    #    thisVector = pfJets.getJet(iJet)
    #    # thisJet = pfJetsDB.getJet(iJet)
    #    #pfJetHits.Fill(thisJet)
    #
    #    print "\tjet (pt,eta,phi)",thisVector.Pt(),thisVector.Eta(),thisVector.Phi()
    #
    #    
    #    for iTrk in range(pfJets.trackSip3dSig.at(iJet).size()):
    #        sig = pfJets.trackSip3dSig.at(iJet).at(iTrk)
    #        val = pfJets.trackSip3dVal.at(iJet).at(iTrk)
    #        print "\t\t sig (val,err)",sig,"(",val,val/sig,")"

    
        

pfJetHists.Write(outFile)
