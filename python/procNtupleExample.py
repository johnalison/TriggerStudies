import optparse
import copy
parser = optparse.OptionParser()
parser.add_option('-i', '--inFileName',           dest="infileName",         default=None, help="Run in loop mode")
parser.add_option('--inputList',           dest="inputList",         default=False, action="store_true", help="Run in loop mode")
parser.add_option('-o', '--outFileName',          dest="outfileName",        default=None, help="Run in loop mode")
parser.add_option('-n', '--nevents',              dest="nevents",           default=None, help="Run in loop mode")
parser.add_option('-d', '--debug',                dest="debug",    action="store_true",       default=False, help="Run in loop mode")
o, a = parser.parse_args()

import ROOT
from array import array

#ROOT.gROOT.ProcessLine('.L Loader.C+')
tree = ROOT.TChain("tree")

if o.inputList:
    inFile = open(o.infileName,"r")
    for fName in inFile:
        thisFileName = fName.rstrip()
        if not len(thisFileName): continue
        if thisFileName[0] =="#": continue
        print "Adding: '"+thisFileName+"'"

        tree.Add(thisFileName)
    inFile.close()
else:
    print "Adding",o.infileName
    tree.Add(o.infileName)

#myChain->Add("/somewhere/myfile2.root")

#inFile = ROOT.TFile.Open(o.infileName,"READ")
#print inFile

#tree = inFile.Get("tree")
#tree.Print("*")
#print tree

#import sys
#sys.exit(-1)

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

caloJetsDB = JetDataHandler("caloJets")
caloJetsDB.SetBranchAddress(tree)

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
from trackHists import TrackHists
from eventHists import EventHists
outFile    = ROOT.TFile(str(o.outfileName),"recreate")

eventHists     = EventHists("AllEvents")

pfTrackHists          = TrackHists("pfTracks", None, outFile)
pfTrackHists_unmatched= TrackHists("pfTracks_unmatched", None, outFile)
pfTrackHists_matched  = TrackHists("pfTracks_matched", None, outFile)
offTrackHists_matched = TrackHists("offTracks_matched", None, outFile)
offTrackHists_unmatched = TrackHists("offTracks_unmatched", None, outFile)
offTrackHists = TrackHists("offTracks", None, outFile)

pfJetHistsPreOLap     = JetHists("pfJetsPreOLap",outFile,light=True)
pfJetHists            = JetHists("pfJets",outFile)
pfJetHists_matched    = JetHists("pfJets_matched" ,outFile)
pfJetHists_matchedB   = JetHists("pfJets_matchedB",outFile)
pfJetHists_matchedL   = JetHists("pfJets_matchedL",outFile)


caloJetHistsPreOLap     = JetHists("caloJetsPreOLap",outFile,light=True)
caloJetHists            = JetHists("caloJets",outFile)
caloJetHists_matched    = JetHists("caloJets_matched" ,outFile)
caloJetHists_matchedB   = JetHists("caloJets_matchedB",outFile)
caloJetHists_matchedL   = JetHists("caloJets_matchedL",outFile)


offJetHistsPreOLap = JetHists("offJetsPreOLap",outFile,light=True)

offJetHists   = JetHists("offJets",  outFile)
offJetHists_B = JetHists("offJets_B",outFile)
offJetHists_L = JetHists("offJets_L",outFile)

offJetHists_matched        = JetHists("offJets_matched",  outFile)
offJetHists_matchedJet     = JetHists("offJets_matchedJet",  outFile)
offJetHists_B_matched      = JetHists("offJets_B_matched",outFile)
offJetHists_L_matched      = JetHists("offJets_L_matched",outFile)

offJetHists_matched_online60   = JetHists("offJets_matched_online60",  outFile)
offJetHists_B_matched_online60 = JetHists("offJets_B_matched_online60",  outFile)
offJetHists_L_matched_online60 = JetHists("offJets_L_matched_online60",  outFile)

offJetHists_matched_online70   = JetHists("offJets_matched_online70",  outFile)
offJetHists_B_matched_online70 = JetHists("offJets_B_matched_online70",  outFile)
offJetHists_L_matched_online70 = JetHists("offJets_L_matched_online70",  outFile)

offJetHists_matched_online80   = JetHists("offJets_matched_online80",  outFile)
offJetHists_B_matched_online80 = JetHists("offJets_B_matched_online80",  outFile)
offJetHists_L_matched_online80 = JetHists("offJets_L_matched_online80",  outFile)

offJetHists_matched_online90   = JetHists("offJets_matched_online90",  outFile)
offJetHists_B_matched_online90 = JetHists("offJets_B_matched_online90",  outFile)
offJetHists_L_matched_online90 = JetHists("offJets_L_matched_online90",  outFile)

offJetHists_offline70   = JetHists("offJets_offline70",  outFile)
offJetHists_offline70_B = JetHists("offJets_offline70_B",outFile)
offJetHists_offline70_L = JetHists("offJets_offline70_L",outFile)

offJetHists_offline70_matched        = JetHists("offJets_offline70_matched",  outFile)
offJetHists_offline70_B_matched      = JetHists("offJets_offline70_B_matched",outFile)
offJetHists_offline70_L_matched      = JetHists("offJets_offline70_L_matched",outFile)

offJetHists_offline70_matched_online60   = JetHists("offJets_offline70_matched_online60",  outFile)
offJetHists_offline70_B_matched_online60 = JetHists("offJets_offline70_B_matched_online60",  outFile)
offJetHists_offline70_L_matched_online60 = JetHists("offJets_offline70_L_matched_online60",  outFile)

offJetHists_offline70_matched_online70   = JetHists("offJets_offline70_matched_online70",  outFile)
offJetHists_offline70_B_matched_online70 = JetHists("offJets_offline70_B_matched_online70",  outFile)
offJetHists_offline70_L_matched_online70 = JetHists("offJets_offline70_L_matched_online70",  outFile)

offJetHists_offline70_matched_online80   = JetHists("offJets_offline70_matched_online80",  outFile)
offJetHists_offline70_B_matched_online80 = JetHists("offJets_offline70_B_matched_online80",  outFile)
offJetHists_offline70_L_matched_online80 = JetHists("offJets_offline70_L_matched_online80",  outFile)

offJetHists_offline70_matched_online90   = JetHists("offJets_offline70_matched_online90",  outFile)
offJetHists_offline70_B_matched_online90 = JetHists("offJets_offline70_B_matched_online90",  outFile)
offJetHists_offline70_L_matched_online90 = JetHists("offJets_offline70_L_matched_online90",  outFile)

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
    
    if iEvent %1000 == 0:
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
    caloJets = caloJetsDB.getJets()

    if len(elecs)+len(muons) < 2:
        continue

    for caloJet in caloJets:
        if abs(caloJet.eta) > 2.5: continue
        if caloJet.pt       < 35:  continue

        caloJetHistsPreOLap.Fill(caloJet)
        if failOverlap(caloJet,elecs): continue
        if failOverlap(caloJet,muons): continue

        caloJetHists.Fill(caloJet)

    offJets = offJetsDB.getJets()
    for offJet in offJets:
        if abs(offJet.eta) > 2.5: continue
        if offJet.pt       < 35:  continue

        offJetHistsPreOLap.Fill(offJet)
        if failOverlap(offJet,elecs): continue
        if failOverlap(offJet,muons): continue

        # Match offline to online
        dR = 1e6
        matchedJet = None
        for pfJet in pfJets: 
            this_dR = pfJet.vec.DeltaR(offJet.vec)
            if this_dR < dR:
                dR = this_dR
                matchedJet = pfJet
        if dR < 0.02:
            matchedJet.matchedJet = offJet
            matchedJet.match_dR   = dR
            offJet.matchedJet = matchedJet
            offJet.match_dR   = dR


        # match tracks if we matched jets
        if offJet.matchedJet:
            if offJet.matchedJet.tracks: #dont include case where matched pf jet has no tracks due to bug where single tracks get dropped.
                for offTrack in offJet.tracks:
                    #need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
                    if offTrack.dR > 0.29 - offJet.match_dR: continue
                    offTrackHists.Fill(offTrack)

                    dR, dR2 = 1e6, 1e6
                    matchedTrack  = None
                    secondClosest = None
                    for pfTrack in offJet.matchedJet.tracks:
                        this_dR = ((offTrack.eta - pfTrack.eta)**2 + (offTrack.dPhi(pfTrack)/2)**2)**0.5 #phi resolution is about half as good due to extrapolation from jet axis
                        if this_dR > dR and this_dR < dR2:
                            dR2 = this_dR
                            secondClosest = pfTrack
                        if this_dR < dR: 
                            dR2 = dR
                            secondClosest = matchedTrack
                            
                            dR  = this_dR
                            matchedTrack = pfTrack

                    #this dR is with dPhi/2. The dR in the plots does not have that resolution fudge factor
                    if dR > 0.005: 
                    #if dR > 1e5:
                        offTrackHists_unmatched.Fill(offTrack)
                        continue
                    matchedTrack.matchedTrack = offTrack
                    offTrack.matchedTrack     = matchedTrack
                    offTrack.secondClosest    = secondClosest
                    offTrack.nMatches              += 1
                    offTrack.matchedTrack.nMatches += 1
                    offTrackHists_matched.Fill(offTrack)
                    pfTrackHists_matched .Fill(offTrack.matchedTrack)

                for pfTrack in offJet.matchedJet.tracks:
                    #Keep in mind that some of these tracks can't possibly be matched due to regions where jet cones do not overlap
                    pfTrackHists.Fill(pfTrack) #all pftracks in matched jets
                    pfTrackHists.FillMatchStats(pfTrack) #check how often we match pfTracks to more than one offTrack
                    if not pfTrack.nMatches:
                        pfTrackHists_unmatched.Fill(pfTrack) #all unmatched pftracks
                        pfTrackHists_unmatched.FillMatchStats(pfTrack)
                    else:
                        pfTrackHists_matched.FillMatchStats(pfTrack)
                    

        # Fill offJetHists
        # offJets_ROC
        #  wp60 DeepCSV > 0.76 (actual efficiency = 0.604992842829)
        #  wp70 DeepCSV > 0.56 (actual efficiency = 0.717503578586)
        #  wp80 DeepCSV > 0.36 (actual efficiency = 0.808474091039)
        #  wp90 DeepCSV > 0.12 (actual efficiency = 0.912533638706)
        offJetHists.Fill(offJet)
        if offJet.deepcsv > 0.56: offJetHists_offline70.Fill(offJet)
        if offJet.hadronFlavour == 5:
            offJetHists_B.Fill(offJet)
            if offJet.deepcsv > 0.56: offJetHists_offline70_B.Fill(offJet)
        else:
            offJetHists_L.Fill(offJet)
            if offJet.deepcsv > 0.56: offJetHists_offline70_L.Fill(offJet)

        if offJet.matchedJet: 
            offJetHists_matched.Fill(offJet)
            offJetHists_matchedJet.Fill(offJet.matchedJet)
            if offJet.deepcsv > 0.56: offJetHists_offline70_matched.Fill(offJet)
            if offJet.hadronFlavour == 5:
                offJetHists_B_matched.Fill(offJet)
                if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched.Fill(offJet)
            else:
                offJetHists_L_matched.Fill(offJet)
                if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched.Fill(offJet)
            
            # pfJets_matched_ROC
            #  wp60 DeepCSV > 0.64 (actual efficiency = 0.610276798066)
            #  wp70 DeepCSV > 0.48 (actual efficiency = 0.708732661175)
            #  wp80 DeepCSV > 0.28 (actual efficiency = 0.814155211306)
            #  wp90 DeepCSV > 0.08 (actual efficiency = 0.924525480128)
            if offJet.matchedJet.deepcsv > 0.64: #approximate 60% Online WP
                offJetHists_matched_online60.Fill(offJet)
                if offJet.deepcsv > 0.56: offJetHists_offline70_matched_online60.Fill(offJet)
                if offJet.hadronFlavour == 5:
                    offJetHists_B_matched_online60.Fill(offJet)
                    if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched_online60.Fill(offJet)
                else:
                    offJetHists_L_matched_online60.Fill(offJet)
                    if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched_online60.Fill(offJet)

            if offJet.matchedJet.deepcsv > 0.48: #approximate 70% Online WP
                offJetHists_matched_online70.Fill(offJet)
                if offJet.deepcsv > 0.56: offJetHists_offline70_matched_online70.Fill(offJet)
                if offJet.hadronFlavour == 5:
                    offJetHists_B_matched_online70.Fill(offJet)
                    if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched_online70.Fill(offJet)
                else:
                    offJetHists_L_matched_online70.Fill(offJet)
                    if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched_online70.Fill(offJet)

            if offJet.matchedJet.deepcsv > 0.28: #approximate 80% Online WP
                offJetHists_matched_online80.Fill(offJet)
                if offJet.deepcsv > 0.56: offJetHists_offline70_matched_online80.Fill(offJet)
                if offJet.hadronFlavour == 5:
                    offJetHists_B_matched_online80.Fill(offJet)
                    if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched_online80.Fill(offJet)
                else:
                    offJetHists_L_matched_online80.Fill(offJet)
                    if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched_online80.Fill(offJet)

            if offJet.matchedJet.deepcsv > 0.08: #approximate 90% Online WP
                offJetHists_matched_online90.Fill(offJet)
                if offJet.deepcsv > 0.56: offJetHists_offline70_matched_online90.Fill(offJet)
                if offJet.hadronFlavour == 5:
                    offJetHists_B_matched_online90.Fill(offJet)
                    if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched_online90.Fill(offJet)
                else:
                    offJetHists_L_matched_online90.Fill(offJet)
                    if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched_online90.Fill(offJet)

        # Match offline to online
        for caloJet in caloJets:            
            deltaR = caloJet.vec.DeltaR(offJet.vec)
            if deltaR < 0.4:
                caloJet.matchedJet = offJet
                break

    #
    #  pf Jets
    #
    for pfJet in pfJets:
        if abs(pfJet.eta) > 2.5: continue
        if pfJet.pt       < 35:  continue

        pfJetHistsPreOLap.Fill(pfJet)        
        if failOverlap(pfJet,elecs): continue
        if failOverlap(pfJet,muons): continue

        pfJetHists.Fill(pfJet)

        if pfJet.matchedJet:
            pfJetHists_matched .Fill(pfJet)

            if pfJet.matchedJet.hadronFlavour == 5:            
                pfJetHists_matchedB.Fill(pfJet)
            else:
                pfJetHists_matchedL.Fill(pfJet)



    #
    #  calo Jets
    #
    for caloJet in caloJets:
        if abs(caloJet.eta) > 2.5: continue
        if caloJet.pt       < 35:  continue

        caloJetHistsPreOLap.Fill(caloJet)        
        if failOverlap(caloJet,elecs): continue
        if failOverlap(caloJet,muons): continue

        caloJetHists.Fill(caloJet)

        if caloJet.matchedJet:
            caloJetHists_matched .Fill(caloJet)

            if caloJet.matchedJet.hadronFlavour == 5:            
                caloJetHists_matchedB.Fill(caloJet)
            else:
                caloJetHists_matchedL.Fill(caloJet)


        
#
# Save Hists
#
pfTrackHists.Write(outFile)
pfTrackHists_unmatched.Write(outFile)
pfTrackHists_matched.Write(outFile)
offTrackHists_matched.Write(outFile)
offTrackHists_unmatched.Write(outFile)
offTrackHists.Write(outFile)

pfJetHistsPreOLap   .Write(outFile)
pfJetHists          .Write(outFile)
pfJetHists_matched  .Write(outFile)
pfJetHists_matchedB .Write(outFile)
pfJetHists_matchedL .Write(outFile)

caloJetHistsPreOLap   .Write(outFile)
caloJetHists          .Write(outFile)
caloJetHists_matched  .Write(outFile)
caloJetHists_matchedB .Write(outFile)
caloJetHists_matchedL .Write(outFile)

offJetHistsPreOLap  .Write(outFile)

offJetHists         .Write(outFile)
offJetHists_B       .Write(outFile)
offJetHists_L       .Write(outFile)

offJetHists_matched.Write(outFile)
offJetHists_matchedJet.Write(outFile)
offJetHists_B_matched.Write(outFile)
offJetHists_L_matched.Write(outFile)

offJetHists_matched_online60.Write(outFile)
offJetHists_B_matched_online60.Write(outFile)
offJetHists_L_matched_online60.Write(outFile)

offJetHists_matched_online70.Write(outFile)
offJetHists_B_matched_online70.Write(outFile)
offJetHists_L_matched_online70.Write(outFile)

offJetHists_matched_online80.Write(outFile)
offJetHists_B_matched_online80.Write(outFile)
offJetHists_L_matched_online80.Write(outFile)

offJetHists_matched_online90.Write(outFile)
offJetHists_B_matched_online90.Write(outFile)
offJetHists_L_matched_online90.Write(outFile)

offJetHists_offline70         .Write(outFile)
offJetHists_offline70_B       .Write(outFile)
offJetHists_offline70_L       .Write(outFile)

offJetHists_offline70_matched.Write(outFile)
offJetHists_offline70_B_matched.Write(outFile)
offJetHists_offline70_L_matched.Write(outFile)

offJetHists_offline70_matched_online60.Write(outFile)
offJetHists_offline70_B_matched_online60.Write(outFile)
offJetHists_offline70_L_matched_online60.Write(outFile)

offJetHists_offline70_matched_online70.Write(outFile)
offJetHists_offline70_B_matched_online70.Write(outFile)
offJetHists_offline70_L_matched_online70.Write(outFile)

offJetHists_offline70_matched_online80.Write(outFile)
offJetHists_offline70_B_matched_online80.Write(outFile)
offJetHists_offline70_L_matched_online80.Write(outFile)

offJetHists_offline70_matched_online90.Write(outFile)
offJetHists_offline70_B_matched_online90.Write(outFile)
offJetHists_offline70_L_matched_online90.Write(outFile)

eventHists          .Write(outFile)
