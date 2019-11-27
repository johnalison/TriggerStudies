
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <TROOT.h>
#include <boost/bind.hpp>


#include "TriggerStudies/NtupleAna/interface/BTagAnalysis.h"
#include "nTupleAnalysis/baseClasses/interface/helpers.h"

using namespace TriggerStudies;

// 2018
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X
const float OfflineDeepCSVTightCut2018  = 0.7527;
const float OfflineDeepCSVMediumCut2018 = 0.4184;
const float OfflineDeepCSVLooseCut2018  = 0.1241;


const float OfflineDeepFlavourTightCut2018   = 0.7264;
const float OfflineDeepFlavourMediumCut2018  = 0.2770;
const float OfflineDeepFlavourLooseCut2018   = 0.0494;

// https://cmswbm.cern.ch/cmsdb/servlet/HLTPath?PATHID=2117358
// https://cmswbm.cern.ch/cmsdb/servlet/HLTPath?PATHID=2090546
const float OnlineDeepCSVCutPF    = 0.24; 
const float OnlineDeepCSVCutCalo  = 0.17; 
const float OnlineCSVCutPF        = 0.7;
const float OnlineCSVCutCalo      = 0.5; 


// 2017 
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
const float OfflineDeepCSVTightCut2017  = 0.8001;
const float OfflineDeepCSVMediumCut2017 = 0.4941;
const float OfflineDeepCSVLooseCut2017  = 0.1522;

const float OfflineDeepFlavourTightCut2017   = 0.7489;
const float OfflineDeepFlavourMediumCut2017  = 0.3033;
const float OfflineDeepFlavourLooseCut2017   = 0.0521;



BTagAnalysis::BTagAnalysis(TChain* _eventsRAW, TChain* _eventsAOD, fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug, std::string PUFileName, std::string jetDetailString){
  if(_debug) std::cout<<"In BTagAnalysis constructor"<<std::endl;
  debug      = _debug;
  isMC       = _isMC;
  year       = _year;
  eventsRAW     = _eventsRAW;
  eventsRAW->SetBranchStatus("*", 0);

  eventsAOD     = _eventsAOD;
  eventsAOD->SetBranchStatus("*", 0);


  histogramming = _histogramming;

  doTracks = jetDetailString.find("Tracks") != std::string::npos;

  event      = new eventData(eventsRAW, eventsAOD, isMC, year, debug, jetDetailString);
  treeEvents = eventsRAW->GetEntries();

  cutflow    = new nTupleAnalysis::cutflowHists("cutflow", fs);
  cutflow->AddCut("all");
  cutflow->AddCut("foundMatch");
  cutflow->AddCut("passMuonCut");  
  cutflow->AddCut("passElecCut");  
  cutflow->AddCut("passLeptonCut");
  cutflow->AddCut("passNJetCut");
  cutflow->AddCut("passNBJetCut");

  //
  //  Jets
  //
  cutflowJets    = new nTupleAnalysis::cutflowHists("cutflowJets", fs);
  cutflowJets->AddCut("all");
  cutflowJets->AddCut("eta");
  cutflowJets->AddCut("pt");
  cutflowJets->AddCut("muonOlap");  
  cutflowJets->AddCut("elecOlap");  
  cutflowJets->AddCut("isProbe");
  cutflowJets->AddCut("hasHLTMatchPF");
  cutflowJets->AddCut("hasHLTMatchCalo");


  //
  // hists
  //
  dir = fs.mkdir("BTagAnalysis");

  hAllMuons = new nTupleAnalysis::muonHists("AllMuons", fs, "All Muons");
  hAllElecs = new nTupleAnalysis::elecHists("AllElecs", fs, "All Elecs");
  hSelMuons = new nTupleAnalysis::muonHists("SelMuons", fs, "Sel Muons");
  hSelElecs = new nTupleAnalysis::elecHists("SelElecs", fs, "Sel Elecs");
  hMuons    = new nTupleAnalysis::muonHists("Muons", fs, "Muons");
  hElecs    = new nTupleAnalysis::elecHists("Elecs", fs, "Elecs");

  hEvents                 = new nTupleAnalysis::eventHists("Events", fs);
  hEventsNoPUWeight       = new nTupleAnalysis::eventHists("EventsNoPUWeight", fs);

  hOffJetsPreOLap         = new nTupleAnalysis::jetHists("offJetsPreOLap",        fs, "Pre Overlap");
  hOffJets                = new nTupleAnalysis::jetHists("offJets",               fs, "");
  hOffJets_matched        = new nTupleAnalysis::jetHists("offJets_matched",       fs, "", jetDetailString);
  hOffJets_matchedJet     = new nTupleAnalysis::jetHists("offJets_matchedJet",    fs, "", jetDetailString);
  hOffJets_matchedCalo    = new nTupleAnalysis::jetHists("offJets_matchedCalo",   fs, "", jetDetailString);
  hOffJets_matchedCaloJet = new nTupleAnalysis::jetHists("offJets_matchedCaloJet",fs, "", jetDetailString);

  hOffJet_matchedPFcsvTag         = new nTupleAnalysis::jetHists("offJets_matchedPFcsvTag",         fs, "");
  hOffJet_matchedPFcsvTagJet      = new nTupleAnalysis::jetHists("offJets_matchedPFcsvTagJet",      fs, "");
  hOffJet_matchedPFDeepcsvTag     = new nTupleAnalysis::jetHists("offJets_matchedPFDeepcsvTag",     fs, "");
  hOffJet_matchedPFDeepcsvTagJet  = new nTupleAnalysis::jetHists("offJets_matchedPFDeepcsvTagJet",  fs, "");

  hOffJetTightDeepCSV_matchedPFJet       = new nTupleAnalysis::jetHists("offJetsTight_matchedPFJet",       fs, "");
  hOffJetMediumDeepCSV_matchedPFJet      = new nTupleAnalysis::jetHists("offJetsMedium_matchedPFJet",      fs, "");
  hOffJetLooseDeepCSV_matchedPFJet       = new nTupleAnalysis::jetHists("offJetsLoose_matchedPFJet",       fs, "");

  hOffJetMedDeepCSV_matchedPFJet         = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedPFJet",      fs, "", "");
  hOffJetMedDeepCSV_matchedPFDeepCSV  = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedPFDeepCSV",      fs, "", "");
  hOffJetMedDeepCSV_matchedPFCSV      = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedPFCSV",          fs, "", "");

  hOffJetMedDeepFlav_matchedPFJet      = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedPFJet",          fs, "", "matchedBJet");
  hOffJetMedDeepFlav_matchedPFDeepCSV  = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedPFDeepCSV",      fs, "", "matchedBJet");
  hOffJetMedDeepFlav_matchedPFCSV      = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedPFCSV",          fs, "", "matchedBJet");

  hOffJet_matchedCalocsvTag         = new nTupleAnalysis::jetHists("offJets_matchedCalocsvTag",         fs, "");
  hOffJet_matchedCalocsvTagJet      = new nTupleAnalysis::jetHists("offJets_matchedCalocsvTagJet",      fs, "");
  hOffJet_matchedCaloDeepcsvTag     = new nTupleAnalysis::jetHists("offJets_matchedCaloDeepcsvTag",     fs, "");
  hOffJet_matchedCaloDeepcsvTagJet  = new nTupleAnalysis::jetHists("offJets_matchedCaloDeepcsvTagJet",  fs, "");

  hOffJetTightDeepCSV_matchedCaloJet       = new nTupleAnalysis::jetHists("offJetsTight_matchedCaloJet",       fs, "");
  hOffJetMediumDeepCSV_matchedCaloJet      = new nTupleAnalysis::jetHists("offJetsMedium_matchedCaloJet",      fs, "");
  hOffJetLooseDeepCSV_matchedCaloJet       = new nTupleAnalysis::jetHists("offJetsLoose_matchedCaloJet",       fs, "");

  hOffJetMedDeepCSV_matchedCaloJet      = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedCaloJet",      fs, "", "");
  hOffJetMedDeepCSV_matchedCaloDeepCSV  = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedCaloDeepCSV",  fs, "", "");
  hOffJetMedDeepCSV_matchedCaloCSV      = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedCaloCSV",      fs, "", "");

  hOffJetMedDeepFlav_matchedCaloJet      = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedCaloJet",      fs, "", "matchedBJet");
  hOffJetMedDeepFlav_matchedCaloDeepCSV  = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedCaloDeepCSV",  fs, "", "matchedBJet");
  hOffJetMedDeepFlav_matchedCaloCSV      = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedCaloCSV",      fs, "", "matchedBJet");

  if(isMC){
    hOffJets_matched_L        = new nTupleAnalysis::jetHists("offJets_matched_L",       fs, "", jetDetailString);
    hOffJets_matchedJet_L     = new nTupleAnalysis::jetHists("offJets_matchedJet_L",    fs, "", jetDetailString);
    hOffJets_matchedCalo_L    = new nTupleAnalysis::jetHists("offJets_matchedCalo_L",   fs, "", jetDetailString);
    hOffJets_matchedCaloJet_L = new nTupleAnalysis::jetHists("offJets_matchedCaloJet_L",fs, "", jetDetailString);

    hOffJets_matched_B        = new nTupleAnalysis::jetHists("offJets_matched_B",       fs, "", jetDetailString );
    hOffJets_matchedJet_B     = new nTupleAnalysis::jetHists("offJets_matchedJet_B",    fs, "", jetDetailString );
    hOffJets_matchedCalo_B    = new nTupleAnalysis::jetHists("offJets_matchedCalo_B",   fs, "", jetDetailString );
    hOffJets_matchedCaloJet_B = new nTupleAnalysis::jetHists("offJets_matchedCaloJet_B",fs, "", jetDetailString );

    hOffJets_matched_C        = new nTupleAnalysis::jetHists("offJets_matched_C",       fs, "");
    hOffJets_matchedJet_C     = new nTupleAnalysis::jetHists("offJets_matchedJet_C",    fs, "");
    hOffJets_matchedCalo_C    = new nTupleAnalysis::jetHists("offJets_matchedCalo_C",   fs, "");
    hOffJets_matchedCaloJet_C = new nTupleAnalysis::jetHists("offJets_matchedCaloJet_C",fs, "");
  }

  hPfJets          = new nTupleAnalysis::jetHists("pfJets",           fs, "");
  hPfJets_matched  = new nTupleAnalysis::jetHists("pfJets_matched",           fs, "");



  hCaloJets            = new nTupleAnalysis::jetHists("caloJets",           fs, "");
  hCaloJets_matched    = new nTupleAnalysis::jetHists("caloJets_matched",           fs, "");


  if(doTracks){
    hOffTracks           = new nTupleAnalysis::trackHists("offTracks",fs, "");
    hOffTracks_unmatched = new nTupleAnalysis::trackHists("offTracks_unmatched",fs, "");
    hOffTracks_matched   = new nTupleAnalysis::trackHists("offTracks_matched",fs, "");
    hOffTracks_noV0           = new nTupleAnalysis::trackHists("offTracks_noV0",fs, "");
    hOffTracks_matched_noV0   = new nTupleAnalysis::trackHists("offTracks_matched_noV0",fs, "");

    hPfTracks            = new nTupleAnalysis::trackHists("pfTracks",fs, "");
    hPfTracks_noV0       = new nTupleAnalysis::trackHists("pfTracks_noV0",fs, "");
    hPfTracks_matched    = new nTupleAnalysis::trackHists("pfTracks_matched",fs, "");
    hPfTracks_unmatched  = new nTupleAnalysis::trackHists("pfTracks_unmatched",fs, "");

    hOffTracksCalo                = new nTupleAnalysis::trackHists("offTracksCalo",fs, "");
    hOffTracksCalo_unmatched      = new nTupleAnalysis::trackHists("offTracksCalo_unmatched",fs, "");
    hOffTracksCalo_matched        = new nTupleAnalysis::trackHists("offTracksCalo_matched",fs, "");
    hOffTracksCalo_noV0           = new nTupleAnalysis::trackHists("offTracksCalo_noV0",fs, "");
    hOffTracksCalo_matched_noV0   = new nTupleAnalysis::trackHists("offTracksCalo_matched_noV0",fs, "");

    hCaloTracks            = new nTupleAnalysis::trackHists("caloTracks",fs, "");
    hCaloTracks_noV0       = new nTupleAnalysis::trackHists("caloTracks_noV0",fs, "");
    hCaloTracks_matched    = new nTupleAnalysis::trackHists("caloTracks_matched",fs, "");
    hCaloTracks_unmatched  = new nTupleAnalysis::trackHists("caloTracks_unmatched",fs, "");

    hOffBTags           = new nTupleAnalysis::btaggingHists("offBTags",fs, "");
    hOffBTags_matched   = new nTupleAnalysis::btaggingHists("offBTags_matched",fs, "");
    hOffBTags_noV0           = new nTupleAnalysis::btaggingHists("offBTags_noV0",fs, "");
    hOffBTags_matched_noV0   = new nTupleAnalysis::btaggingHists("offBTags_matched_noV0",fs, "");

    hPfBTags           = new nTupleAnalysis::btaggingHists("pfBTags",fs, "");

    hmttOff           = dir.make<TH1F>("mtt_off",            "BTagAnalysis/mtt_off;             mtt;   Entries", 100,-0.01, 2);
    hmttOff_isFromV0  = dir.make<TH1F>("mtt_off_isFromV0",   "BTagAnalysis/mtt_off_isFromV0;    mtt;   Entries", 100,-0.01, 2);
    hmttPf            = dir.make<TH1F>("mtt_pf",             "BTagAnalysis/mtt_pf;              mtt;   Entries", 100,-0.01, 2);
    hmttPf_isFromV0   = dir.make<TH1F>("mtt_pf_isFromV0",    "BTagAnalysis/mtt_pf_isFromV0;     mtt;   Entries", 100,-0.01, 2);
    hmttCalo            = dir.make<TH1F>("mtt_calo",             "BTagAnalysis/mtt_calo;              mtt;   Entries", 100,-0.01, 2);
    hmttCalo_isFromV0   = dir.make<TH1F>("mtt_calo_isFromV0",    "BTagAnalysis/mtt_calo_isFromV0;     mtt;   Entries", 100,-0.01, 2);
  }

  //
  //  Configure Selection
  // 
//  OfflineDeepCSVTightCut  = OfflineDeepCSVTightCut2017  ;
//  OfflineDeepCSVMediumCut = OfflineDeepCSVMediumCut2017 ;
//  OfflineDeepCSVLooseCut  = OfflineDeepCSVLooseCut2017  ;
//  OfflineDeepFlavourMediumCut = OfflineDeepFlavourMediumCut2017 ;
//  if(_year == "2018"){
    OfflineDeepCSVTightCut  = OfflineDeepCSVTightCut2018  ;
    OfflineDeepCSVMediumCut = OfflineDeepCSVMediumCut2018 ;
    OfflineDeepCSVLooseCut  = OfflineDeepCSVLooseCut2018 ;
    OfflineDeepFlavourMediumCut = OfflineDeepFlavourMediumCut2018 ;
    //  }



  //
  //  Init the pile-up function
  //
  if(isMC){
    if( PUFileName != ""){
      pileUpTool = new nTupleAnalysis::pileUpWeightTool(PUFileName);
    }else{
      std::cout << "Skipping PU reweighting" << std::endl;
    }
  }

  //  if(histogramming >= 4) allEvents     = new eventHists("allEvents",     fs);
  //  if(histogramming >= 3) passPreSel    = new   tagHists("passPreSel",    fs, true, isMC, blind);
  //  if(histogramming >= 2) passDijetMass = new   tagHists("passDijetMass", fs, true, isMC, blind);
  //  if(histogramming >= 1) passMDRs      = new   tagHists("passMDRs",      fs, true, isMC, blind);
  //  //if(histogramming > 1        ) passMDCs     = new   tagHists("passMDCs",   fs, true, isMC, blind);
  //  //if(histogramming > 0        ) passDEtaBB   = new   tagHists("passDEtaBB", fs, true, isMC, blind);
} 


void BTagAnalysis::monitor(long int e){
  //Monitor progress
  percent        = (e+1)*100/nEvents;
  duration       = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  eventRateAVE      = (e+1)/duration;
  timeRemaining  = (nEvents-e)/eventRateAVE;
  minutes = static_cast<int>(timeRemaining/60);
  seconds = static_cast<int>(timeRemaining - minutes*60);
  getrusage(who, &usage);
  usageMB = usage.ru_maxrss/1024;
  
  
  timeStep = (std::clock() - lastTime) / (double) CLOCKS_PER_SEC;
  eventStep = e - lastEvent;
  eventRate = eventStep/timeStep;
  //print status and flush stdout so that status bar only uses one line
  if(isMC){
    fprintf(stdout, "\rProcessed: %8li of %li ( %2li%% | %.0f events/s AVE | %.0f events/s  | done in %02i:%02i | memory usage: %li MB)       ", 
	    e+1, nEvents, percent,   eventRateAVE,    eventRate, minutes, seconds,                usageMB);
  }else{
    fprintf(stdout, "\rProcessed: %8li of %li ( %2li%% | %.0f events/s AVE | %.0f events/s | done in %02i:%02i | memory usage: %li MB | LumiBlocks %i  )       ", 
	    e+1, nEvents, percent,   eventRateAVE,    eventRate, minutes, seconds,                usageMB,            nls );    
  }
  fflush(stdout);
  lastTime = std::clock();
  lastEvent = e+1;
}

int BTagAnalysis::eventLoop(int maxEvents, int nSkipEvents){
  //Set Number of events to process. Take manual maxEvents if maxEvents is > 0 and less than the total number of events in the input files. 
  nEvents = (maxEvents > 0 && maxEvents < treeEvents) ? maxEvents : treeEvents;

  std::cout << "\nProcess " << nEvents << " of " << treeEvents << " events.\n";

  start = std::clock();//2546000 //2546043
  lastTime = std::clock();
  lastEvent = 0;
  for(long int e = 0; e < nEvents; e++){

    if(e < nSkipEvents) continue;

    event->update(e);    
    processEvent();
    if(debug) event->dump();

    //periodically update status
    //if( (e+1)%1 == 0 || e+1==nEvents || debug) 
    if( (e+1)%10000 == 0 || e+1==nEvents || debug) 
      monitor(e);

  }
  
  std::cout << std::endl;
  std::cout << "BTagAnalysis::End of Event Loop" << std::endl;
  if(!isMC) std::cout << "Runs " << firstRun << "-" << lastRun << std::endl;

  minutes = static_cast<int>(duration/60);
  seconds = static_cast<int>(duration - minutes*60);
                                        
  if(isMC){
    fprintf(stdout,"---------------------------\nProcessed in %02i:%02i", minutes, seconds);
  }else{
    fprintf(stdout,"---------------------------\nProcessed in %02i:%02i", minutes, seconds);
  }
  return 0;
}

int BTagAnalysis::processEvent(){
  if(debug) std::cout << "processEvent start" << std::endl;

  cutflow->Fill("all", 1.0);
  if(event->run != event->runAOD)
    return 0;

  if(event->event != event->eventAOD)
    return 0;

  cutflow->Fill("foundMatch", 1.0);

  std::vector<nTupleAnalysis::muonPtr> selMuons;
  for(nTupleAnalysis::muonPtr& muon: event->muons){
    hAllMuons->Fill(muon,1.0);
    if(muon->tightId && muon->isolation_corrected < 0.2){
      hSelMuons->Fill(muon,1.0);
      selMuons.push_back(muon);
    }
  }
  hAllMuons->nMuons->Fill(event->muons.size());
  hSelMuons->nMuons->Fill(selMuons.size());

  
  std::vector<nTupleAnalysis::elecPtr> selElecs;
  for(nTupleAnalysis::elecPtr& elec: event->elecs){
    hAllElecs->Fill(elec,1.0);
    if(elec->tightId && elec->isolation_corrected < 0.2){
      hSelElecs->Fill(elec,1.0);
      selElecs.push_back(elec);
    }
  }
  hAllElecs->nElecs->Fill(event->elecs.size());
  hSelElecs->nElecs->Fill(selElecs.size());

  bool doLeptonCuts = false;
  if(doLeptonCuts){
    if(selMuons.size() == 1)
      cutflow->Fill("passMuonCut", 1.0);
    
    if(selElecs.size() == 1)
      cutflow->Fill("passElecCut", 1.0);
    
    if(selMuons.size() != 1){
      if(debug) std::cout << "Fail Muon Cut" << std::endl;
      return 0;
    }
    
    if(selElecs.size() != 1){
      if(debug) std::cout << "Fail Elec Cut" << std::endl;
      return 0;
    }
    cutflow->Fill("passLeptonCut", 1.0);
  }

  float eventWeight = 1.0;
  float puWeight    = 1.0;
  if(isMC && pileUpTool){
    puWeight = pileUpTool->getWeight(event->nPVAOD);
    eventWeight =  puWeight * selElecs.at(0)->SF * selMuons.at(0)->SF;
  }


  //
  //  Offline BTags
  //
  unsigned int nOffJetsForCut = 0;
  unsigned int nOffJetsTaggedForCut = 0;
  float totalSFWeight = 1.0;
  for(const nTupleAnalysis::jetPtr& offJet : event->offJets){
    if(fabs(offJet->eta) > 2.4) continue;
    if(offJet->pt       < 35)   continue;

    if(nTupleAnalysis::failOverlap(offJet->p,event->elecs,0.4)) continue;
    if(nTupleAnalysis::failOverlap(offJet->p,event->muons,0.4)) continue;
    
    ++nOffJetsForCut;
    if(offJet->DeepCSV > OfflineDeepCSVTightCut) ++nOffJetsTaggedForCut;
    
    if(isMC)
      totalSFWeight *= offJet->SF;
  }
  
  if(nOffJetsForCut < 2      ){
    if(debug) std::cout << "Fail NJet Cut" << std::endl;
    return 0;
  }
  cutflow->Fill("passNJetCut", eventWeight);

  bool doOfflineBTagCut = false;
  if(doOfflineBTagCut){
    
    if(nOffJetsTaggedForCut < 1) {
      if(debug) std::cout << "Fail NBJet Cut" << std::endl;
      return 0;
    }
    cutflow->Fill("passNBJetCut", eventWeight);
  }
  
  if(isMC)
    eventWeight *= totalSFWeight;

  hMuons->nMuons->Fill(event->muons.size());
  for(auto muon: event->muons)
    hMuons->Fill(muon,eventWeight);

  hElecs->nElecs->Fill(event->elecs.size());
  for(auto elec: event->elecs)
    hElecs->Fill(elec,eventWeight);


  //
  // Fill All events
  //
  hEvents->Fill(event->nPVAOD,  0.0, eventWeight);
  if(puWeight)
    hEventsNoPUWeight->Fill(event->nPVAOD,  0.0, eventWeight/puWeight);

  //
  //
  //
  unsigned int nOffJetsPreOLap      = 0;
  unsigned int nOffJets             = 0;
  unsigned int nOffJets_matched     = 0;
  unsigned int nOffJets_matchedCalo = 0;

  for(const nTupleAnalysis::jetPtr& offJet : event->offJets){
    cutflowJets->Fill("all", eventWeight);    

    if(fabs(offJet->eta) > 2.4) continue;
    cutflowJets->Fill("eta", eventWeight);    
    
    if(offJet->pt       < 35)   continue;
    cutflowJets->Fill("pt", eventWeight);    

    ++nOffJetsPreOLap;
    hOffJetsPreOLap->Fill(offJet, eventWeight);


    if(nTupleAnalysis::failOverlap(offJet->p,event->muons,0.4)) continue;
    cutflowJets->Fill("muonOlap", eventWeight);    

    if(nTupleAnalysis::failOverlap(offJet->p,event->elecs,0.4)) continue;
    cutflowJets->Fill("elecOlap", eventWeight);    



    //
    // Check if jet is a Probe
    //
    unsigned int nOtherTags = 0;
    float min_dR_all  = 1000;
    float min_dR_bjet = 1000;
    //const JetData* tagJet = nullptr;
    for(const nTupleAnalysis::jetPtr& offJetOther : event->offJets){
      if(offJetOther == offJet) continue;


      if(offJetOther->pt       < 35)   continue;	
      if(fabs(offJetOther->eta) > 2.4) continue;
      if(nTupleAnalysis::failOverlap(offJetOther->p,event->elecs,0.4)) continue;
      if(nTupleAnalysis::failOverlap(offJetOther->p,event->muons,0.4)) continue;
      float thisDr = offJetOther->p.DeltaR(offJet->p);
      if(thisDr < min_dR_all) min_dR_all = thisDr;

      if(offJetOther->DeepCSV       < OfflineDeepCSVTightCut)   continue;	
      if(thisDr < min_dR_bjet) min_dR_bjet = thisDr;

      ++nOtherTags;
      //tagJet = &offJetOther;
    }


    if(min_dR_all  < 1000) offJet->match_dR       = min_dR_all;
    if(min_dR_bjet < 1000) offJet->match_dR_bjet = min_dR_bjet;
    
    // Require that there only be one other probe
    //    Note: this will suppress LF
    if(nOtherTags != 1) continue;
    cutflowJets->Fill("isProbe", eventWeight);    

    //
    //  Offline Jets
    //
    ++nOffJets;
    hOffJets->Fill(offJet,eventWeight);

    if(offJet->DeepCSV > 1)
      std::cout << "Error " << "Offline" << " DeepCSV is " << offJet->DeepCSV << std::endl; 
			       
    if(offJet->DeepCSVb > 1)   
      std::cout << "Error " << "Offline" << " DeepCSVb is " << offJet->DeepCSVb << std::endl; 
			       
    if(offJet->DeepCSVbb > 1)  
      std::cout << "Error " << "Offline" << " DeepCSVbb is " << offJet->DeepCSVbb << std::endl; 
        
    // Match offline to online
    float dR = 1e6;
    nTupleAnalysis::jetPtr matchedJet = nullptr;

    for(const nTupleAnalysis::jetPtr& pfJet : event->pfJets){
      float this_dR = pfJet->p.DeltaR(offJet->p);
      if (this_dR < dR){
	dR = this_dR;
	matchedJet = pfJet;
      }
    }

    // 
    //  Have PF Match
    //
    if( dR < 0.4){
      
      cutflowJets->Fill("hasHLTMatchPF", eventWeight);    
      offJet->matchedJet = matchedJet;

      PFJetAnalysis(offJet,matchedJet,eventWeight);
      
      ++nOffJets_matched;

    }//offJet has match


    //
    //  Calo Jets
    //
    float dRCalo = 1e6;
    nTupleAnalysis::jetPtr matchedCaloJet = nullptr;

    for(const nTupleAnalysis::jetPtr& caloJet : event->caloJets){
      float this_dR = caloJet->p.DeltaR(offJet->p);
      if (this_dR < dRCalo){
    	dRCalo = this_dR;
    	matchedCaloJet = caloJet;
      }
    }
    
    if( dRCalo < 0.4){

      cutflowJets->Fill("hasHLTMatchCalo", eventWeight);    

      CaloJetAnalysis(offJet,matchedCaloJet,eventWeight);
      
      ++nOffJets_matchedCalo;
    }


    // Fill offJetHists
    // offJets_ROC
    //  wp60 DeepCSV > 0.76 (actual efficiency = 0.604992842829)
    //  wp70 DeepCSV > 0.56 (actual efficiency = 0.717503578586)
    //  wp80 DeepCSV > 0.36 (actual efficiency = 0.808474091039)
    //  wp90 DeepCSV > 0.12 (actual efficiency = 0.912533638706)
      
    //if(offJetMatchedJet){

      ///        // pfJets_matched_ROC
      ///	//  wp60 DeepCSV > 0.64 (actual efficiency = 0.610276798066)
      ///	//  wp70 DeepCSV > 0.48 (actual efficiency = 0.708732661175)
      ///	//  wp80 DeepCSV > 0.28 (actual efficiency = 0.814155211306)
      ///	//  wp90 DeepCSV > 0.08 (actual efficiency = 0.924525480128)
      ///	if(offJet.m_matchedJet->m_deepcsv > 0.64){ //approximate 60% Online WP
      ///	  offJetHists_matched_online60.Fill(offJet);
      ///	  if( offJet.m_deepcsv > 0.56) offJetHists_offline70_matched_online60.Fill(offJet);
      ///	  if(offJet.m_hadronFlavour == 5){
      ///	    offJetHists_B_matched_online60.Fill(offJet);
      ///	    if(offJet.m_deepcsv > 0.56) offJetHists_offline70_B_matched_online60.Fill(offJet);
      ///	  }else{
      ///	    offJetHists_L_matched_online60.Fill(offJet);
      ///	    if(offJet.m_deepcsv > 0.56) offJetHists_offline70_L_matched_online60.Fill(offJet);
      ///	  }
      ///	}
      ///
      ///	if(offJet.m_matchedJet->m_deepcsv > 0.48){ //approximate 70% Online WP
      ///	  offJetHists_matched_online70.Fill(offJet);
      ///	  if(offJet.m_deepcsv > 0.56) offJetHists_offline70_matched_online70.Fill(offJet);
      ///	  if(offJet.m_hadronFlavour == 5){
      ///	    offJetHists_B_matched_online70.Fill(offJet);
      ///	    if(offJet.m_deepcsv > 0.56) offJetHists_offline70_B_matched_online70.Fill(offJet);
      ///	  }else{
      ///	    offJetHists_L_matched_online70.Fill(offJet);
      ///	    if(offJet.m_deepcsv > 0.56) offJetHists_offline70_L_matched_online70.Fill(offJet);
      ///	  }
      ///	}
      ///	
      ///	if(offJet.m_matchedJet->m_deepcsv > 0.28){ //approximate 80% Online WP
      ///	  offJetHists_matched_online80.Fill(offJet);
      ///	  if(offJet.m_deepcsv > 0.56) offJetHists_offline70_matched_online80.Fill(offJet);
      ///	  if(offJet.m_hadronFlavour == 5){
      ///	    offJetHists_B_matched_online80.Fill(offJet);
      ///	    if(offJet.m_deepcsv > 0.56) offJetHists_offline70_B_matched_online80.Fill(offJet);
      ///	  }else{
      ///	    offJetHists_L_matched_online80.Fill(offJet);
      ///	    if(offJet.m_deepcsv > 0.56) offJetHists_offline70_L_matched_online80.Fill(offJet);
      ///	  }
      ///	}
      ///      
      ///	if(offJet.m_matchedJet->m_deepcsv > 0.08){ //approximate 90% Online WP
      ///	  offJetHists_matched_online90.Fill(offJet);
      ///	  if(offJet.m_deepcsv > 0.56) offJetHists_offline70_matched_online90.Fill(offJet);
      ///	  if(offJet.m_hadronFlavour == 5){
      ///	    offJetHists_B_matched_online90.Fill(offJet);
      ///	    if(offJet.m_deepcsv > 0.56) offJetHists_offline70_B_matched_online90.Fill(offJet);
      ///	  }else{
      ///	    offJetHists_L_matched_online90.Fill(offJet);
      ///	    if(offJet.m_deepcsv > 0.56) offJetHists_offline70_L_matched_online90.Fill(offJet);
      ///	  }
      ///	}
    //    }//m_matchedJet


  }//offJets


  hOffJetsPreOLap    ->nJets->Fill(nOffJetsPreOLap ,eventWeight);
  hOffJets           ->nJets->Fill(nOffJets        ,eventWeight);
  hOffJets_matched   ->nJets->Fill(nOffJets_matched,eventWeight);

  hOffJets_matchedCalo->nJets->Fill(nOffJets_matchedCalo,eventWeight);
  hOffJets_matchedCaloJet->nJets->Fill(nOffJets_matchedCalo,eventWeight);



  //
  //  pf Jets
  //
  for(const nTupleAnalysis::jetPtr& pfJet : event->pfJets){
    if(fabs(pfJet->eta) > 2.5) continue;
    if(pfJet->pt       < 35)   continue;
  
    //pfJetHistsPreOLap.Fill(pfJet);
  
    if(nTupleAnalysis::failOverlap(pfJet->p,event->elecs, 0.4)) continue;
    if(nTupleAnalysis::failOverlap(pfJet->p,event->muons, 0.4)) continue;
  
    hPfJets->Fill(pfJet, eventWeight);
  
    const nTupleAnalysis::jetPtr pfJetMatchedJet = pfJet->matchedJet.lock();
    if(pfJetMatchedJet){
      hPfJets_matched->Fill(pfJet, eventWeight);
  
      //if(isMC){
      //	if( pfJetMatchedJet->hadronFlavour == 5){
      //	  hPfJets_matched_B->Fill(pfJet, eventWeight);
      //	}else if( pfJetMatchedJet->hadronFlavour == 4){
      //	  hPfJets_matched_C->Fill(pfJet, eventWeight);
      //	}else if( pfJetMatchedJet->hadronFlavour == 0){
      //	  hPfJets_matched_L->Fill(pfJet, eventWeight);
      //	}
      //}
    }
  }
  
  //
  //  calo Jets
  //
  for(const nTupleAnalysis::jetPtr& caloJet : event->caloJets){
    if(fabs(caloJet->eta) > 2.5) continue;
    if(caloJet->pt       < 35)   continue;
  
    //caloJetHistsPreOLap.Fill(caloJet);
    if(nTupleAnalysis::failOverlap(caloJet->p,event->elecs, 0.4)) continue;
    if(nTupleAnalysis::failOverlap(caloJet->p,event->muons, 0.4)) continue;
  
    hCaloJets->Fill(caloJet, eventWeight);

    if(caloJet->DeepCSV > 1)
      std::cout << "Error " << "Offline" << " DeepCSV is " << caloJet->DeepCSV << std::endl; 
			       
    if(caloJet->DeepCSVb > 1)   
      std::cout << "Error " << "Offline" << " DeepCSVb is " << caloJet->DeepCSVb << std::endl; 
			       
    if(caloJet->DeepCSVbb > 1)  
      std::cout << "Error " << "Offline" << " DeepCSVbb is " << caloJet->DeepCSVbb << std::endl; 


    const nTupleAnalysis::jetPtr caloJetMatchedJet = caloJet->matchedJet.lock();  
    if(caloJetMatchedJet){
      hCaloJets_matched->Fill(caloJet, eventWeight);
  
      //if(caloJet->m_matchedJet->m_hadronFlavour == 5)
      //	caloJetHists_matchedB.Fill(caloJet);
      //	else
      //	  caloJetHists_matchedL.Fill(caloJet);
    }
  }
 
    

  
 

  //
  //if we are processing data, first apply lumiMask and trigger
  //
  if(!isMC){
    if(!passLumiMask()){
      if(debug) std::cout << "Fail lumiMask" << std::endl;
      return 0;
    }
    //cutflow->Fill(event, "lumiMask", true);

    //keep track of total lumi

    //if(!event->passHLT){
    //  if(debug) std::cout << "Fail HLT: data" << std::endl;
    //  return 0;
    //}
    //cutflow->Fill(event, "HLT", true);
  }
  //if(allEvents != NULL && event->passHLT) allEvents->Fill(event);





  return 0;
}

bool BTagAnalysis::passLumiMask(){
  // if the lumiMask is empty, then no JSON file was provided so all
  // events should pass
  if(lumiMask.empty()) return true;

  //make lumiID run:lumiBlock
  //edm::LuminosityBlockID lumiID(event->run, event->lumiBlock);

  //define function that checks if a lumiID is contained in a lumiBlockRange
  bool (*funcPtr) (edm::LuminosityBlockRange const &, edm::LuminosityBlockID const &) = &edm::contains;

  //Loop over the lumiMask and use funcPtr to check for a match
  //std::vector< edm::LuminosityBlockRange >::const_iterator iter = std::find_if (lumiMask.begin(), lumiMask.end(), boost::bind(funcPtr, _1, lumiID) );

  //return lumiMask.end() != iter; 
  return true;
}



BTagAnalysis::~BTagAnalysis(){
  std::cout << "BTagAnalysis::destroyed" << std::endl;
} 


void BTagAnalysis::PFJetAnalysis(const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight){

  //
  // Jet info
  //
  hOffJets_matched->Fill(offJet,weight);
  hOffJets_matchedJet->Fill(hltJet,weight);

  //
  // Offline Btaggs
  //
  if((offJet->DeepCSV > OfflineDeepCSVTightCut))
    hOffJetTightDeepCSV_matchedPFJet->Fill(hltJet, weight);	  
  if((offJet->DeepCSV > OfflineDeepCSVMediumCut)){
    hOffJetMediumDeepCSV_matchedPFJet->Fill(hltJet, weight);	  
    hOffJetMedDeepCSV_matchedPFJet    ->Fill(offJet, weight);    
    if(hltJet->CSVv2   > OnlineCSVCutPF)     hOffJetMedDeepCSV_matchedPFCSV    ->Fill(offJet, weight);    
    if(hltJet->DeepCSV > OnlineDeepCSVCutPF) hOffJetMedDeepCSV_matchedPFDeepCSV->Fill(offJet, weight);    
  }
    
  if((offJet->DeepCSV > OfflineDeepCSVLooseCut))
    hOffJetLooseDeepCSV_matchedPFJet->Fill(hltJet, weight);	  

  if(offJet->deepFlavB > OfflineDeepFlavourMediumCut){
    hOffJetMedDeepFlav_matchedPFJet ->Fill(offJet, weight);	  
    if(hltJet->CSVv2   > OnlineCSVCutPF)     hOffJetMedDeepFlav_matchedPFCSV    ->Fill(offJet, weight);    
    if(hltJet->DeepCSV > OnlineDeepCSVCutPF) hOffJetMedDeepFlav_matchedPFDeepCSV->Fill(offJet, weight);    
  }

  // 
  // If pass CVS working point
  //
  if(hltJet->CSVv2 >= OnlineCSVCutPF){
    hOffJet_matchedPFcsvTag   ->Fill(offJet, weight);
    hOffJet_matchedPFcsvTagJet->Fill(hltJet, weight);
  }


  // 
  // If pass DeepCVS working point
  //
  if(hltJet->DeepCSV >= OnlineDeepCSVCutPF){
    hOffJet_matchedPFDeepcsvTag   ->Fill(offJet, weight);
    hOffJet_matchedPFDeepcsvTagJet->Fill(hltJet, weight);
  }

  
  if(isMC){
    if(offJet->hadronFlavour == 5){
      hOffJets_matched_B->Fill(offJet, weight);
      hOffJets_matchedJet_B->Fill(hltJet, weight);
    }else if(offJet->hadronFlavour == 4){
      hOffJets_matched_C->Fill(offJet, weight);
      hOffJets_matchedJet_C->Fill(hltJet, weight);
    }else if(offJet->hadronFlavour == 0){
      hOffJets_matched_L->Fill(offJet, weight);
      hOffJets_matchedJet_L->Fill(hltJet, weight);
    }
  }

  if(doTracks){

    //
    //  Off tracks
    //
    unsigned int nOffTracks = 0;
    unsigned int nOffTracks_matched = 0;
    unsigned int nOffTracks_noV0 = 0;
    unsigned int nOffTracks_matched_noV0 = 0;
  
  
    for(const nTupleAnalysis::trackPtr& offTrack: offJet->tracks){
  	
      //
      //  track mass calculation
      //
      for(const nTupleAnalysis::trackPtr& offTrack_pair: offJet->tracks){
        if(offTrack == offTrack_pair) continue;
        float thisMass = (offTrack->p + offTrack_pair->p).M();
  	  
        hmttOff->Fill(thisMass , weight);
        if(offTrack->isfromV0)
	  hmttOff_isFromV0->Fill(thisMass , weight);
  	  
      }
  
      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if offTrack.dR > 0.29 - offJet.match_dR: continue
      if(offTrack->dR                              > 0.29) continue; // offTrack is not in cone of offJet
      if(offTrack->p.DeltaR(hltJet->p) > 0.29) continue; // offTrack is not in cone of pfJet
  	
  	
      hOffTracks->Fill(offTrack, weight);
      ++nOffTracks;
      if(!offTrack->isfromV0){
        hOffTracks_noV0->Fill(offTrack, weight);	  
        ++nOffTracks_noV0;
      }
  
      float dR = 1e6;
      float dR2 = 1e6;
      float dR_noV0 = 1e6;
      nTupleAnalysis::trackPtr matchedTrack  = nullptr;
      nTupleAnalysis::trackPtr secondClosest = nullptr;
  
      for(const nTupleAnalysis::trackPtr& pfTrack: hltJet->tracks){
        //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
        if(pfTrack->dR                  > 0.29) continue; // pfTrack is not in cone of pfJet
        if(pfTrack->p.DeltaR(offJet->p) > 0.29) continue; // pfTrack is not in cone of offJet
  
        float this_dR = offTrack->p.DeltaR(pfTrack->p);
        if(this_dR > dR && this_dR < dR2){
	  dR2 = this_dR;
	  secondClosest = pfTrack;
        }
  
        if(this_dR < dR){
	  dR2 = dR;
	  secondClosest = matchedTrack;
  	    
	  dR  = this_dR;
	  matchedTrack = pfTrack;
        }
  	  
        if(!pfTrack->isfromV0 && this_dR < dR_noV0){
	  dR_noV0 = this_dR;
        }
  	  
      }// matched pf tracks
  	
      if( dR > 0.01){
        //if dR > 1e5:
        hOffTracks_unmatched->Fill(offTrack, weight);
        continue;
      }
  	
      if(!offTrack->isfromV0 && (dR_noV0 < 0.01)){
        hOffTracks_matched_noV0->Fill(offTrack, weight);
        ++nOffTracks_matched_noV0;
      }
  
      ++nOffTracks_matched;
      matchedTrack->matchedTrack = offTrack;
      offTrack->matchedTrack     = matchedTrack;
      offTrack->secondClosest    = secondClosest;
      offTrack->nMatches              += 1;
      matchedTrack->nMatches += 1;
      hOffTracks_matched    ->Fill(offTrack, weight);
      const nTupleAnalysis::trackPtr offTrackMatchedTrack = offTrack->matchedTrack.lock();
      hPfTracks_matched ->Fill(offTrackMatchedTrack,weight);
    }//off Tracks
        
    hOffTracks             ->nTracks->Fill(nOffTracks, weight);
    hOffTracks_matched     ->nTracks->Fill(nOffTracks_matched, weight);
    hOffTracks_noV0        ->nTracks->Fill(nOffTracks_noV0, weight);
    hOffTracks_matched_noV0->nTracks->Fill(nOffTracks_matched_noV0, weight);
  

    //
    //  Off BTags
    //
    unsigned int nTrkTags = 0;
    unsigned int nTrkTags_matched = 0;
    unsigned int nTrkTags_noV0 = 0;
    unsigned int nTrkTags_matched_noV0 = 0;
  
    for(const nTupleAnalysis::trkTagVarPtr& offTrkTag: offJet->trkTagVars){
      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if offTrack.dR > 0.29 - offJet.match_dR: continue
      if(offTrkTag->trackDeltaR                              > 0.29) continue; // offTrack is not in cone of offJet
      if(offTrkTag->p.DeltaR(hltJet->p) > 0.29) continue; // offTrack is not in cone of pfJet
  
  
      hOffBTags->FillTrkTagVarHists(offTrkTag, weight);
      ++nTrkTags;
  
      if(!offTrkTag->matchIsFromV0){
        hOffBTags_noV0->FillTrkTagVarHists(offTrkTag, weight);	  
        ++nTrkTags_noV0;
      }
  
      float dR = 1e6;
      float dR_noV0 = 1e6;
      nTupleAnalysis::trkTagVarPtr matchedTrkTag  = nullptr;
      for(const nTupleAnalysis::trkTagVarPtr& pfTrkTag: hltJet->trkTagVars){
        if(pfTrkTag->trackDeltaR                  > 0.29) continue; // pfTrack is not in cone of pfJet
        if(pfTrkTag->p.DeltaR(offJet->p) > 0.29) continue; // pfTrack is not in cone of offJet
  
        float this_dR = offTrkTag->p.DeltaR(pfTrkTag->p);
        if(this_dR < dR){
	  dR  = this_dR;
	  matchedTrkTag = pfTrkTag;
        }
  
        if(!pfTrkTag->matchIsFromV0 && this_dR < dR_noV0){
	  dR_noV0 = this_dR;
        }
  
      }
  	
  
      if( dR > 0.01){
        //if dR > 1e5:
        //hOffBTags_unmatched->Fill(offTrack, weight);
        continue;
      }
  
      if(!offTrkTag->matchIsFromV0 && (dR_noV0 < 0.01)){
        hOffBTags_matched_noV0->FillTrkTagVarHists(offTrkTag, weight);
        ++nTrkTags_matched_noV0;
      }
  
      ++nTrkTags_matched;
      matchedTrkTag->matchedTrkTagVar = offTrkTag;
      offTrkTag->matchedTrkTagVar     = matchedTrkTag;
      hOffBTags_matched    ->FillTrkTagVarHists(offTrkTag, weight);
      //const nTupleAnalysis::trackPtr offTrackMatchedTrkTag = offTrkTag->matchedTrkTagVar.lock();
      //hPfTracks_matched ->FillTrkTagVarHists(offTrackMatchedTrkTag,weight);
  
  
    }//OffTrkTag
  
    hOffBTags             ->trkTag_nTracks->Fill(nTrkTags, weight);
    hOffBTags_matched     ->trkTag_nTracks->Fill(nTrkTags_matched, weight);
    hOffBTags_noV0        ->trkTag_nTracks->Fill(nTrkTags_noV0, weight);
    hOffBTags_matched_noV0->trkTag_nTracks->Fill(nTrkTags_matched_noV0, weight);
  
  
    //
    // PF Tracks
    //
    unsigned int nPfTracks = 0;
    unsigned int nPfTracks_matched = 0;
    unsigned int nPfTracks_noV0 = 0;
    for(const nTupleAnalysis::trackPtr& pfTrack: hltJet->tracks){
  
      //
      //  track mass calculation
      //
      for(const nTupleAnalysis::trackPtr& pfTrack_pair: hltJet->tracks){
        if(pfTrack == pfTrack_pair) continue;
        float thisMass = (pfTrack->p + pfTrack_pair->p).M();
  	  
        hmttPf->Fill(thisMass , weight);
        if(pfTrack->isfromV0)
	  hmttPf_isFromV0->Fill(thisMass , weight);
  	  
      }
  
      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      if(pfTrack->dR                  > 0.29) continue; // pfTrack is not in cone of pfJet
      if(pfTrack->p.DeltaR(offJet->p) > 0.29) continue; // pfTrack is not in cone of offJet
  	
      hPfTracks->Fill(pfTrack, weight); //all pftracks in matched jets
      hPfTracks->FillMatchStats(pfTrack, weight); //check how often we match pfTracks to more than one offTrack
      ++nPfTracks;
  
      if(!pfTrack->isfromV0){
        hPfTracks_noV0->Fill(pfTrack, weight); //all pftracks in matched jets
        ++nPfTracks_noV0;
      }
  
      if(!pfTrack->nMatches){
        hPfTracks_unmatched->Fill(pfTrack, weight); //all unmatched pftracks
        hPfTracks_unmatched->FillMatchStats(pfTrack, weight);
      }else{
        hPfTracks_matched->FillMatchStats(pfTrack, weight);
        ++nPfTracks_matched;
      }
    }// pfTracks
  
    hPfTracks              ->nTracks->Fill(nPfTracks, weight);
    hPfTracks_matched      ->nTracks->Fill(nPfTracks_matched, weight);
    hPfTracks_noV0         ->nTracks->Fill(nPfTracks_noV0, weight);
    //hOffTracks_matched_noV0->nTracks->Fill(nOffTracks_matched_noV0, weight);
  
  
    //
    //  PF BTags
    //
    unsigned int nPfTrkTags = 0;
  
    for(const nTupleAnalysis::trkTagVarPtr& pfTrkTag: hltJet->trkTagVars){
      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if offTrack.dR > 0.29 - offJet.match_dR: continue
      if(pfTrkTag->trackDeltaR                              > 0.29) continue; // offTrack is not in cone of offJet
      if(pfTrkTag->p.DeltaR(offJet->p) > 0.29) continue; // offTrack is not in cone of pfJet
  
  
      hPfBTags->FillTrkTagVarHists(pfTrkTag, weight);
      ++nPfTrkTags;
  
    }//OffTrkTag
  
    hPfBTags             ->trkTag_nTracks->Fill(nPfTrkTags, weight);

  }//doTracks  

  return;
}


void BTagAnalysis::CaloJetAnalysis(const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight){

  //
  // Jet info
  //
  hOffJets_matchedCalo   ->Fill(offJet,weight);
  hOffJets_matchedCaloJet->Fill(hltJet,weight);
  
  //
  // Offline Btaggs
  //
  if((offJet->DeepCSV > OfflineDeepCSVTightCut))
    hOffJetTightDeepCSV_matchedCaloJet->Fill(hltJet, weight);	  
  if((offJet->DeepCSV > OfflineDeepCSVMediumCut)){
    hOffJetMediumDeepCSV_matchedCaloJet->Fill(hltJet, weight);	  
    hOffJetMedDeepCSV_matchedCaloJet    ->Fill(offJet, weight);    
    if(hltJet->CSVv2   > OnlineCSVCutPF)     hOffJetMedDeepCSV_matchedCaloCSV    ->Fill(offJet, weight);    
    if(hltJet->DeepCSV > OnlineDeepCSVCutPF) hOffJetMedDeepCSV_matchedCaloDeepCSV->Fill(offJet, weight);    
  }

  if((offJet->DeepCSV > OfflineDeepCSVLooseCut))
    hOffJetLooseDeepCSV_matchedCaloJet->Fill(hltJet, weight);	  

  if(offJet->deepFlavB > OfflineDeepFlavourMediumCut){
    hOffJetMedDeepFlav_matchedCaloJet ->Fill(offJet, weight);	  
    if(hltJet->CSVv2   > OnlineCSVCutCalo)     hOffJetMedDeepFlav_matchedCaloCSV    ->Fill(offJet, weight);    
    if(hltJet->DeepCSV > OnlineDeepCSVCutCalo) hOffJetMedDeepFlav_matchedCaloDeepCSV->Fill(offJet, weight);    
  }


  // 
  // If pass CVS working point
  //
  if(hltJet->CSVv2 >= OnlineCSVCutCalo){
    hOffJet_matchedCalocsvTag   ->Fill(offJet, weight);
    hOffJet_matchedCalocsvTagJet->Fill(hltJet, weight);
  }


  // 
  // If pass DeepCVS working point
  //
  if(hltJet->DeepCSV >= OnlineDeepCSVCutCalo){
    hOffJet_matchedCaloDeepcsvTag   ->Fill(offJet, weight);
    hOffJet_matchedCaloDeepcsvTagJet->Fill(hltJet, weight);
  }



  if(isMC){
    if(offJet->hadronFlavour == 5){
      hOffJets_matchedCalo_B->Fill(offJet, weight);
      hOffJets_matchedCaloJet_B->Fill(hltJet, weight);
    }else if(offJet->hadronFlavour == 4){
      hOffJets_matchedCalo_C->Fill(offJet, weight);
      hOffJets_matchedCaloJet_C->Fill(hltJet, weight);
    }else if(offJet->hadronFlavour == 0){
      hOffJets_matchedCalo_L->Fill(offJet, weight);
      hOffJets_matchedCaloJet_L->Fill(hltJet, weight);
    }
  }




  if(doTracks){

    //
    //  Off tracks
    //
    unsigned int nOffTracks = 0;
    unsigned int nOffTracks_matched = 0;
    unsigned int nOffTracks_noV0 = 0;
    unsigned int nOffTracks_matched_noV0 = 0;


    for(const nTupleAnalysis::trackPtr& offTrack: offJet->tracks){

      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if offTrack.dR > 0.29 - offJet.match_dR: continue
      if(offTrack->dR                  > 0.29) continue; // offTrack is not in cone of offJet
      if(offTrack->p.DeltaR(hltJet->p) > 0.29) continue; // offTrack is not in cone of caloJet
	
	
      hOffTracksCalo->Fill(offTrack, weight);
      ++nOffTracks;
      if(!offTrack->isfromV0){
	hOffTracksCalo_noV0->Fill(offTrack, weight);	  
	++nOffTracks_noV0;
      }

      float dR = 1e6;
      float dR2 = 1e6;
      float dR_noV0 = 1e6;
      nTupleAnalysis::trackPtr matchedTrack  = nullptr;
      nTupleAnalysis::trackPtr secondClosest = nullptr;

      for(const nTupleAnalysis::trackPtr& caloTrack: hltJet->tracks){
	//need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
	if(caloTrack->dR                  > 0.29) continue; // caloTrack is not in cone of caloJet
	if(caloTrack->p.DeltaR(offJet->p) > 0.29) continue; // caloTrack is not in cone of offJet

	float this_dR = offTrack->p.DeltaR(caloTrack->p);
	if(this_dR > dR && this_dR < dR2){
	  dR2 = this_dR;
	  secondClosest = caloTrack;
	}

	if(this_dR < dR){
	  dR2 = dR;
	  secondClosest = matchedTrack;
	    
	  dR  = this_dR;
	  matchedTrack = caloTrack;
	}
	  
	if(!caloTrack->isfromV0 && this_dR < dR_noV0){
	  dR_noV0 = this_dR;
	}
	  
      }// matched calo tracks
	
      if( dR > 0.01){
	//if dR > 1e5:
	hOffTracksCalo_unmatched->Fill(offTrack, weight);
	continue;
      }
	
      if(!offTrack->isfromV0 && (dR_noV0 < 0.01)){
	hOffTracksCalo_matched_noV0->Fill(offTrack, weight);
	++nOffTracks_matched_noV0;
      }

      ++nOffTracks_matched;
      matchedTrack->matchedTrack = offTrack;
      offTrack->matchedTrack     = matchedTrack;
      offTrack->secondClosest    = secondClosest;
      offTrack->nMatches              += 1;
      matchedTrack->nMatches += 1;
      hOffTracksCalo_matched    ->Fill(offTrack, weight);
      const nTupleAnalysis::trackPtr offTrackMatchedTrack = offTrack->matchedTrack.lock();
      hCaloTracks_matched ->Fill(offTrackMatchedTrack,weight);
    }//off Tracks
      
    hOffTracksCalo             ->nTracks->Fill(nOffTracks, weight);
    hOffTracksCalo_matched     ->nTracks->Fill(nOffTracks_matched, weight);
    hOffTracksCalo_noV0        ->nTracks->Fill(nOffTracks_noV0, weight);
    hOffTracksCalo_matched_noV0->nTracks->Fill(nOffTracks_matched_noV0, weight);


    //
    // Calo Tracks
    //
    unsigned int nCaloTracks = 0;
    unsigned int nCaloTracks_matched = 0;
    unsigned int nCaloTracks_noV0 = 0;
    for(const nTupleAnalysis::trackPtr& caloTrack: hltJet->tracks){

      //
      //  track mass calculation
      //
      for(const nTupleAnalysis::trackPtr& caloTrack_pair: hltJet->tracks){
	if(caloTrack == caloTrack_pair) continue;
	float thisMass = (caloTrack->p + caloTrack_pair->p).M();
	  
	hmttCalo->Fill(thisMass , weight);
	if(caloTrack->isfromV0)
	  hmttCalo_isFromV0->Fill(thisMass , weight);
	  
      }

      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      if(caloTrack->dR                  > 0.29) continue; // caloTrack is not in cone of caloJet
      if(caloTrack->p.DeltaR(offJet->p) > 0.29) continue; // caloTrack is not in cone of offJet
	
      hCaloTracks->Fill(caloTrack, weight); //all calotracks in matched jets
      hCaloTracks->FillMatchStats(caloTrack, weight); //check how often we match caloTracks to more than one offTrack
      ++nCaloTracks;

      if(!caloTrack->isfromV0){
	hCaloTracks_noV0->Fill(caloTrack, weight); //all calotracks in matched jets
	++nCaloTracks_noV0;
      }

      if(!caloTrack->nMatches){
	hCaloTracks_unmatched->Fill(caloTrack, weight); //all unmatched pftracks
	hCaloTracks_unmatched->FillMatchStats(caloTrack, weight);
      }else{
	hCaloTracks_matched->FillMatchStats(caloTrack, weight);
	++nCaloTracks_matched;
      }
    }// caloTracks

    hCaloTracks              ->nTracks->Fill(nCaloTracks, weight);
    hCaloTracks_matched      ->nTracks->Fill(nCaloTracks_matched, weight);
    hCaloTracks_noV0         ->nTracks->Fill(nCaloTracks_noV0, weight);
    //hOffTracks_matched_noV0->nTracks->Fill(nOffTracks_matched_noV0, weight);
  }

  return;
}
