#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include "TSystem.h"
#include "TChain.h"

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"

#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"

#include "TriggerStudies/NtupleAna/interface/EventData.h"
#include "TriggerStudies/NtupleAna/interface/JetDataHandler.h"
//from leptonInfo       import LeptonDataHandler
//from eventDisplayData import EventDisplayData

//from trackHists import TrackHists
#include "TriggerStudies/NtupleAna/interface/JetHists.h"
#include "TriggerStudies/NtupleAna/interface/EventHists.h"

using namespace NtupleAna;

int main(int argc, char * argv[]){
  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  FWLiteEnabler::enable();

  // parse arguments
  if ( argc < 2 ) {
    std::cout << "Usage : " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }

  if( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ){
    std::cout << " ERROR: ParametersSet 'process' is missing in your configuration file" << std::endl; exit(0);
  }

  // get the python configuration
  const edm::ParameterSet& process = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  fwlite::InputSource inputHandler_(process); fwlite::OutputFiles outputHandler_(process);


  //
  //  Inint Tree
  //
  TChain* tree = new TChain("tree");
  for(unsigned int iFile=0; iFile<inputHandler_.files().size(); ++iFile){
    // open input file (can be located on castor)
    std::cout << "inputFile is " << inputHandler_.files()[iFile].c_str() << std::endl;

    //TFile* inFile = TFile::Open(inputFiles_[iFile].c_str());
    //if( inFile ){
    tree->Add(inputHandler_.files()[iFile].c_str());
    //}
  }

  //
  // Input Data
  //
  NtupleAna::EventData eventData = NtupleAna::EventData();
  eventData.SetBranchAddress(tree);

  JetDataHandler pfJetsDB = JetDataHandler("pfJets");
  pfJetsDB.SetBranchAddress(tree);

  NtupleAna::JetDataHandler caloJetsDB = NtupleAna::JetDataHandler("caloJets");
  caloJetsDB.SetBranchAddress(tree);

  NtupleAna::JetDataHandler offJetsDB = NtupleAna::JetDataHandler("offJets");
  offJetsDB.SetBranchAddress(tree);

//muonDB = LeptonDataHandler("offTightMuons")
//muonDB.SetBranchAddress(tree)
//
//elecDB = LeptonDataHandler("offTightElectrons")
//elecDB.SetBranchAddress(tree)



  //
  // Make output ntuple/Hists
  // 
  fwlite::TFileService fs = fwlite::TFileService(outputHandler_.file());

  EventHists eventHists     = EventHists("AllEvents", fs);

//pfTrackHists            = TrackHists("pfTracks", None, outFile)
//pfTrackHists_unmatched  = TrackHists("pfTracks_unmatched", None, outFile)
//pfTrackHists_matched    = TrackHists("pfTracks_matched", None, outFile)
//offTrackHists_matched   = TrackHists("offTracks_matched", None, outFile)
//offTrackHists_unmatched = TrackHists("offTracks_unmatched", None, outFile)
//offTrackHists           = TrackHists("offTracks", None, outFile)

  JetHists pfJetHistsPreOLap     = JetHists("pfJetsPreOLap",fs);//,light=True)
  JetHists pfJetHists            = JetHists("pfJets", fs);
//pfJetHists_matched    = JetHists("pfJets_matched" ,outFile)
//pfJetHists_matchedB   = JetHists("pfJets_matchedB",outFile)
//pfJetHists_matchedL   = JetHists("pfJets_matchedL",outFile)

  JetHists caloJetHistsPreOLap     = JetHists("caloJetsPreOLap",fs);//light=True)
//caloJetHists            = JetHists("caloJets",outFile)
//caloJetHists_matched    = JetHists("caloJets_matched" ,outFile)
//caloJetHists_matchedB   = JetHists("caloJets_matchedB",outFile)
//caloJetHists_matchedL   = JetHists("caloJets_matchedL",outFile)

  JetHists offJetHistsPreOLap = JetHists("offJetsPreOLap",fs);//light=True)

//offJetHists   = JetHists("offJets",  outFile)
//offJetHists_B = JetHists("offJets_B",outFile)
//offJetHists_L = JetHists("offJets_L",outFile)
//
//offJetHists_matched        = JetHists("offJets_matched",  outFile)
//offJetHists_matchedJet     = JetHists("offJets_matchedJet",  outFile)
//offJetHists_B_matched      = JetHists("offJets_B_matched",outFile)
//offJetHists_L_matched      = JetHists("offJets_L_matched",outFile)
//
//offJetHists_matched_online60   = JetHists("offJets_matched_online60",  outFile)
//offJetHists_B_matched_online60 = JetHists("offJets_B_matched_online60",  outFile)
//offJetHists_L_matched_online60 = JetHists("offJets_L_matched_online60",  outFile)
//
//offJetHists_matched_online70   = JetHists("offJets_matched_online70",  outFile)
//offJetHists_B_matched_online70 = JetHists("offJets_B_matched_online70",  outFile)
//offJetHists_L_matched_online70 = JetHists("offJets_L_matched_online70",  outFile)
//
//offJetHists_matched_online80   = JetHists("offJets_matched_online80",  outFile)
//offJetHists_B_matched_online80 = JetHists("offJets_B_matched_online80",  outFile)
//offJetHists_L_matched_online80 = JetHists("offJets_L_matched_online80",  outFile)
//
//offJetHists_matched_online90   = JetHists("offJets_matched_online90",  outFile)
//offJetHists_B_matched_online90 = JetHists("offJets_B_matched_online90",  outFile)
//offJetHists_L_matched_online90 = JetHists("offJets_L_matched_online90",  outFile)
//
//offJetHists_offline70   = JetHists("offJets_offline70",  outFile)
//offJetHists_offline70_B = JetHists("offJets_offline70_B",outFile)
//offJetHists_offline70_L = JetHists("offJets_offline70_L",outFile)
//
//offJetHists_offline70_matched        = JetHists("offJets_offline70_matched",  outFile)
//offJetHists_offline70_B_matched      = JetHists("offJets_offline70_B_matched",outFile)
//offJetHists_offline70_L_matched      = JetHists("offJets_offline70_L_matched",outFile)
//
//offJetHists_offline70_matched_online60   = JetHists("offJets_offline70_matched_online60",  outFile)
//offJetHists_offline70_B_matched_online60 = JetHists("offJets_offline70_B_matched_online60",  outFile)
//offJetHists_offline70_L_matched_online60 = JetHists("offJets_offline70_L_matched_online60",  outFile)
//
//offJetHists_offline70_matched_online70   = JetHists("offJets_offline70_matched_online70",  outFile)
//offJetHists_offline70_B_matched_online70 = JetHists("offJets_offline70_B_matched_online70",  outFile)
//offJetHists_offline70_L_matched_online70 = JetHists("offJets_offline70_L_matched_online70",  outFile)
//
//offJetHists_offline70_matched_online80   = JetHists("offJets_offline70_matched_online80",  outFile)
//offJetHists_offline70_B_matched_online80 = JetHists("offJets_offline70_B_matched_online80",  outFile)
//offJetHists_offline70_L_matched_online80 = JetHists("offJets_offline70_L_matched_online80",  outFile)
//
//offJetHists_offline70_matched_online90   = JetHists("offJets_offline70_matched_online90",  outFile)
//offJetHists_offline70_B_matched_online90 = JetHists("offJets_offline70_B_matched_online90",  outFile)
//offJetHists_offline70_L_matched_online90 = JetHists("offJets_offline70_L_matched_online90",  outFile)

//#
//#  Event Displays
//#
//makeEventDisplays = False
//from eventDisplayData import EventDisplayData
//eventDisplay = EventDisplayData("offline")

  bool debug = false;

  std::cout << " In procNtupleExample " << std::endl;

  int nEventThisFile = tree->GetEntries();
  std::cout <<  "Number of input events: " << nEventThisFile << std::endl;


  for(int entry = 0; entry<nEventThisFile; entry++){

    if(entry %1000 == 0)
      std::cout << "Processed .... "<<entry<<" Events"<<std::endl;

    tree->GetEntry( entry );

    eventData.SetEvent();

    if(debug){
      std::cout << "RunNumber: "  << eventData.runNumber << std::endl;
      std::cout << "EventNumber: " << eventData.eventNumber << std::endl;
    }

    //
    // Fill All events
    //
    eventHists.Fill(eventData);

//    # Converting from "row-level" info to "column-level" info
//    elecs  = elecDB.getLeps()
//    muons  = muonDB.getLeps()
    std::vector<NtupleAna::JetData> pfJets   = pfJetsDB.GetJets();
    std::vector<NtupleAna::JetData> caloJets = caloJetsDB.GetJets();

//    if len(elecs)+len(muons) < 2:
//        continue
//
//    if makeEventDisplays: eventDisplay.newEvent()

    std::vector<NtupleAna::JetData> offJets = offJetsDB.GetJets();
    for(JetData offJet : offJets){

      if(fabs(offJet.m_eta) > 2.5) continue;
      if(offJet.m_pt       < 35)   continue;
      
      offJetHistsPreOLap.Fill(offJet);

//        if failOverlap(offJet,elecs): continue
//        if failOverlap(offJet,muons): continue
//
//        if makeEventDisplays: eventDisplay.AddJet("offJetAll", offJet, doTracks=True)
//
//        # Match offline to online
//        dR = 1e6
//        matchedJet = None
//        for pfJet in pfJets: 
//            this_dR = pfJet.vec.DeltaR(offJet.vec)
//            if this_dR < dR:
//                dR = this_dR
//                matchedJet = pfJet
//
//        if dR < 0.4:
//            matchedJet.matchedJet = offJet
//            matchedJet.match_dR   = dR
//            offJet.matchedJet = matchedJet
//            offJet.match_dR   = dR
//
//
//        # match tracks if we matched jets
//        if offJet.matchedJet:
//
//            if makeEventDisplays:
//                eventDisplay.AddJet("offJet", offJet)
//                eventDisplay.AddJet("offMatchJet", offJet.matchedJet)
//
//            for offTrack in offJet.tracks:
//                #need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
//                #if offTrack.dR > 0.29 - offJet.match_dR: continue
//                if offTrack.dR                                > 0.29: continue # offTrack is not in cone of offJet
//                if offTrack.vec.DeltaR(offJet.matchedJet.vec) > 0.29: continue # offTrack is not in cone of pfJet
//                offTrackHists.Fill(offTrack)
//                if makeEventDisplays: eventDisplay.AddTrk("offJet_Trks", offTrack)
//
//                dR, dR2 = 1e6, 1e6
//                matchedTrack  = None
//                secondClosest = None
//                for pfTrack in offJet.matchedJet.tracks:
//                    #need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
//                    if pfTrack.dR                     > 0.29: continue # pfTrack is not in cone of pfJet
//                    if pfTrack.vec.DeltaR(offJet.vec) > 0.29: continue # pfTrack is not in cone of offJet
//
//                    #this_dR = ((offTrack.eta - pfTrack.eta)**2 + (offTrack.dPhi(pfTrack))**2)**0.5
//                    this_dR = offTrack.vec.DeltaR(pfTrack.vec)
//                    if this_dR > dR and this_dR < dR2:
//                        dR2 = this_dR
//                        secondClosest = pfTrack
//                    if this_dR < dR: 
//                        dR2 = dR
//                        secondClosest = matchedTrack
//                            
//                        dR  = this_dR
//                        matchedTrack = pfTrack
//
//                if dR > 0.01: 
//                #if dR > 1e5:
//                    offTrackHists_unmatched.Fill(offTrack)
//                    if makeEventDisplays: eventDisplay.AddTrk("offJet_TrksNoMatch", offTrack)
//                    continue
//
//                if makeEventDisplays: eventDisplay.AddTrk("offJet_TrksMatch", offTrack)
//                matchedTrack.matchedTrack = offTrack
//                offTrack.matchedTrack     = matchedTrack
//                offTrack.secondClosest    = secondClosest
//                offTrack.nMatches              += 1
//                offTrack.matchedTrack.nMatches += 1
//                offTrackHists_matched.Fill(offTrack)
//                pfTrackHists_matched .Fill(offTrack.matchedTrack)
//
//            for pfTrack in offJet.matchedJet.tracks:
//                #need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
//                if pfTrack.dR                     > 0.29: continue # pfTrack is not in cone of pfJet
//                if pfTrack.vec.DeltaR(offJet.vec) > 0.29: continue # pfTrack is not in cone of offJet
//
//                pfTrackHists.Fill(pfTrack) #all pftracks in matched jets
//                pfTrackHists.FillMatchStats(pfTrack) #check how often we match pfTracks to more than one offTrack
//                if not pfTrack.nMatches:
//                    pfTrackHists_unmatched.Fill(pfTrack) #all unmatched pftracks
//                    pfTrackHists_unmatched.FillMatchStats(pfTrack)
//                else:
//                    pfTrackHists_matched.FillMatchStats(pfTrack)
//
//                    
//
//        # Fill offJetHists
//        # offJets_ROC
//        #  wp60 DeepCSV > 0.76 (actual efficiency = 0.604992842829)
//        #  wp70 DeepCSV > 0.56 (actual efficiency = 0.717503578586)
//        #  wp80 DeepCSV > 0.36 (actual efficiency = 0.808474091039)
//        #  wp90 DeepCSV > 0.12 (actual efficiency = 0.912533638706)
//        offJetHists.Fill(offJet)
//        if offJet.deepcsv > 0.56: offJetHists_offline70.Fill(offJet)
//        if offJet.hadronFlavour == 5:
//            offJetHists_B.Fill(offJet)
//            if offJet.deepcsv > 0.56: offJetHists_offline70_B.Fill(offJet)
//        else:
//            offJetHists_L.Fill(offJet)
//            if offJet.deepcsv > 0.56: offJetHists_offline70_L.Fill(offJet)
//
//        if offJet.matchedJet: 
//            offJetHists_matched.Fill(offJet)
//            offJetHists_matchedJet.Fill(offJet.matchedJet)
//            if offJet.deepcsv > 0.56: offJetHists_offline70_matched.Fill(offJet)
//            if offJet.hadronFlavour == 5:
//                offJetHists_B_matched.Fill(offJet)
//                if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched.Fill(offJet)
//            else:
//                offJetHists_L_matched.Fill(offJet)
//                if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched.Fill(offJet)
//            
//            # pfJets_matched_ROC
//            #  wp60 DeepCSV > 0.64 (actual efficiency = 0.610276798066)
//            #  wp70 DeepCSV > 0.48 (actual efficiency = 0.708732661175)
//            #  wp80 DeepCSV > 0.28 (actual efficiency = 0.814155211306)
//            #  wp90 DeepCSV > 0.08 (actual efficiency = 0.924525480128)
//            if offJet.matchedJet.deepcsv > 0.64: #approximate 60% Online WP
//                offJetHists_matched_online60.Fill(offJet)
//                if offJet.deepcsv > 0.56: offJetHists_offline70_matched_online60.Fill(offJet)
//                if offJet.hadronFlavour == 5:
//                    offJetHists_B_matched_online60.Fill(offJet)
//                    if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched_online60.Fill(offJet)
//                else:
//                    offJetHists_L_matched_online60.Fill(offJet)
//                    if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched_online60.Fill(offJet)
//
//            if offJet.matchedJet.deepcsv > 0.48: #approximate 70% Online WP
//                offJetHists_matched_online70.Fill(offJet)
//                if offJet.deepcsv > 0.56: offJetHists_offline70_matched_online70.Fill(offJet)
//                if offJet.hadronFlavour == 5:
//                    offJetHists_B_matched_online70.Fill(offJet)
//                    if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched_online70.Fill(offJet)
//                else:
//                    offJetHists_L_matched_online70.Fill(offJet)
//                    if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched_online70.Fill(offJet)
//
//            if offJet.matchedJet.deepcsv > 0.28: #approximate 80% Online WP
//                offJetHists_matched_online80.Fill(offJet)
//                if offJet.deepcsv > 0.56: offJetHists_offline70_matched_online80.Fill(offJet)
//                if offJet.hadronFlavour == 5:
//                    offJetHists_B_matched_online80.Fill(offJet)
//                    if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched_online80.Fill(offJet)
//                else:
//                    offJetHists_L_matched_online80.Fill(offJet)
//                    if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched_online80.Fill(offJet)
//
//            if offJet.matchedJet.deepcsv > 0.08: #approximate 90% Online WP
//                offJetHists_matched_online90.Fill(offJet)
//                if offJet.deepcsv > 0.56: offJetHists_offline70_matched_online90.Fill(offJet)
//                if offJet.hadronFlavour == 5:
//                    offJetHists_B_matched_online90.Fill(offJet)
//                    if offJet.deepcsv > 0.56: offJetHists_offline70_B_matched_online90.Fill(offJet)
//                else:
//                    offJetHists_L_matched_online90.Fill(offJet)
//                    if offJet.deepcsv > 0.56: offJetHists_offline70_L_matched_online90.Fill(offJet)
//
//        # Match offline to online
//        for caloJet in caloJets:            
//            deltaR = caloJet.vec.DeltaR(offJet.vec)
//            if deltaR < 0.4:
//                caloJet.matchedJet = offJet
//                break

    }
    

    //
    //  pf Jets
    //
    for(JetData& pfJet : pfJets){
      if(fabs(pfJet.m_eta) > 2.5) continue;
      if(pfJet.m_pt       < 35)   continue;


      pfJetHistsPreOLap.Fill(pfJet);
//        if failOverlap(pfJet,elecs): continue
//        if failOverlap(pfJet,muons): continue
//
//        if makeEventDisplays: eventDisplay.AddJet("pfJet", pfJet, doTracks=True)
//
//        pfJetHists.Fill(pfJet)
//
//        if pfJet.matchedJet:
//            pfJetHists_matched .Fill(pfJet)
//
//            if pfJet.matchedJet.hadronFlavour == 5:            
//                pfJetHists_matchedB.Fill(pfJet)
//            else:
//                pfJetHists_matchedL.Fill(pfJet)
    }

    //
    //  calo Jets
    //
    for(JetData& caloJet : caloJets){
      if(fabs(caloJet.m_eta) > 2.5) continue;
      if(caloJet.m_pt       < 35)   continue;

      caloJetHistsPreOLap.Fill(caloJet);
//        if failOverlap(caloJet,elecs): continue
//        if failOverlap(caloJet,muons): continue
//
//        caloJetHists.Fill(caloJet)
//
//        if caloJet.matchedJet:
//            caloJetHists_matched .Fill(caloJet)
//
//            if caloJet.matchedJet.hadronFlavour == 5:            
//                caloJetHists_matchedB.Fill(caloJet)
//            else:
//                caloJetHists_matchedL.Fill(caloJet)
//
    }
    

  }

  return 0;
}
