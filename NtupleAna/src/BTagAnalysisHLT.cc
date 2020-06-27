#include <iostream>
#include <iomanip>
#include <cstdio>
#include <TROOT.h>
#include <boost/bind.hpp>


#include "TriggerStudies/NtupleAna/interface/BTagAnalysisHLT.h"
#include "nTupleAnalysis/baseClasses/interface/helpers.h"

using std::cout; using std::endl; 
using namespace TriggerStudies;
using std::vector;  using std::map; using std::string; using std::set;

// 2018
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X
/*
const float OfflineDeepCSVTightCut2018  = 0.7527;
const float OfflineDeepCSVMediumCut2018 = 0.4184;
const float OfflineDeepCSVLooseCut2018  = 0.1241;


const float OfflineDeepFlavourTightCut2018   = 0.7264;
const float OfflineDeepFlavourMediumCut2018  = 0.2770;
const float OfflineDeepFlavourLooseCut2018   = 0.0494;
*/

// https://cmswbm.cern.ch/cmsdb/servlet/HLTPath?PATHID=2117358
// https://cmswbm.cern.ch/cmsdb/servlet/HLTPath?PATHID=2090546
const float OnlineDeepCSVCutPF    = 0.24; 
const float OnlineDeepCSVCutCalo  = 0.17; 
const float OnlineCSVCutPF        = 0.7;
const float OnlineCSVCutCalo      = 0.5; 


// 2017 
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
/*
const float OfflineDeepCSVTightCut2017  = 0.8001;
const float OfflineDeepCSVMediumCut2017 = 0.4941;
const float OfflineDeepCSVLooseCut2017  = 0.1522;

const float OfflineDeepFlavourTightCut2017   = 0.7489;
const float OfflineDeepFlavourMediumCut2017  = 0.3033;
const float OfflineDeepFlavourLooseCut2017   = 0.0521;
*/


BTagAnalysisHLT::BTagAnalysisHLT(TChain* _eventsRAW, /*TChain* _eventsAOD,*/ fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug, /*std::string PUFileName,*/ std::string jetDetailString, const edm::ParameterSet& nnConfig){
  if(_debug) cout<<"In BTagAnalysisHLT constructor"<<endl;
  debug      = _debug;
  isMC       = _isMC;
  year       = _year;
  eventsRAW     = _eventsRAW;
  eventsRAW->SetBranchStatus("*", 0);

  /*eventsAOD     = _eventsAOD;
  eventsAOD->SetBranchStatus("*", 0);
  */


  histogramming = _histogramming;

  doTracks = jetDetailString.find("Tracks") != std::string::npos;
  doCaloJets = jetDetailString.find("CaloJets") != std::string::npos;

  event      = new eventDataHLT(eventsRAW, isMC, year, debug, jetDetailString,nullptr);
  treeEvents = eventsRAW->GetEntries();

  cutflow    = new nTupleAnalysis::cutflowHists("cutflow", fs);
  cutflow->AddCut("all");
  //cutflow->AddCut("foundMatch");
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
  //cutflowJets->AddCut("hasHLTMatchPF");
  //cutflowJets->AddCut("hasHLTMatchCalo");


  //
  // hists
  //
  dir = fs.mkdir("BTagAnalysisHLT");

  //hAllMuons = new nTupleAnalysis::muonHists("AllMuons", fs, "All Muons");
  //hAllElecs = new nTupleAnalysis::elecHists("AllElecs", fs, "All Elecs");
  //hSelMuons = new nTupleAnalysis::muonHists("SelMuons", fs, "Sel Muons");
  //hSelElecs = new nTupleAnalysis::elecHists("SelElecs", fs, "Sel Elecs");
  //hMuons    = new nTupleAnalysis::muonHists("Muons", fs, "Muons");
  //hElecs    = new nTupleAnalysis::elecHists("Elecs", fs, "Elecs");

  //hEvents                 = new nTupleAnalysis::eventHists("Events", fs);
  //hEventsNoPUWeight       = new nTupleAnalysis::eventHists("EventsNoPUWeight", fs);

/*
  hOffJetsPreOLap         = new nTupleAnalysis::jetHists("offJetsPreOLap",        fs, "Pre Overlap");
  hOffJets                = new nTupleAnalysis::jetHists("offJets",               fs, "", jetDetailString);
  hOffJets_matched        = new nTupleAnalysis::jetHists("offJets_matched",       fs, "", jetDetailString);
  hOffJets_matchedJet     = new nTupleAnalysis::jetHists("offJets_matchedJet",    fs, "", jetDetailString);
  if(doCaloJets){
    hOffJets_matchedCalo    = new nTupleAnalysis::jetHists("offJets_matchedCalo",   fs, "", jetDetailString);
    hOffJets_matchedCaloJet = new nTupleAnalysis::jetHists("offJets_matchedCaloJet",fs, "", jetDetailString);
  }

  hOffJet_matchedPFcsvTag         = new nTupleAnalysis::jetHists("offJets_matchedPFcsvTag",         fs, "");
  hOffJet_matchedPFcsvTagJet      = new nTupleAnalysis::jetHists("offJets_matchedPFcsvTagJet",      fs, "");
  hOffJet_matchedPFDeepcsvTag     = new nTupleAnalysis::jetHists("offJets_matchedPFDeepcsvTag",     fs, "");
  hOffJet_matchedPFDeepcsvTagJet  = new nTupleAnalysis::jetHists("offJets_matchedPFDeepcsvTagJet",  fs, "");

  hOffJetTightDeepCSV_matchedPFJet       = new nTupleAnalysis::jetHists("offJetsTight_matchedPFJet",       fs, "");
  hOffJetMediumDeepCSV_matchedPFJet      = new nTupleAnalysis::jetHists("offJetsMedium_matchedPFJet",      fs, "");
  hOffJetLooseDeepCSV_matchedPFJet       = new nTupleAnalysis::jetHists("offJetsLoose_matchedPFJet",       fs, "");

  hOffJetMedDeepCSV_matchedPFJet         = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedPFJet",       fs, "", "matchedBJet");
  hOffJetMedDeepCSV_matchedPFDeepCSV  = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedPFDeepCSV",      fs, "", "matchedBJet");
  hOffJetMedDeepCSV_matchedPFCSV      = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedPFCSV",          fs, "", "matchedBJet");

  hOffJetMedDeepFlav_matchedPFJet      = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedPFJet",          fs, "", "matchedBJet");
  hOffJetMedDeepFlav_matchedPFDeepCSV  = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedPFDeepCSV",      fs, "", "matchedBJet");
  hOffJetMedDeepFlav_matchedPFCSV      = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedPFCSV",          fs, "", "matchedBJet");

  if(doCaloJets){
    hOffJet_matchedCalocsvTag         = new nTupleAnalysis::jetHists("offJets_matchedCalocsvTag",         fs, "");
    hOffJet_matchedCalocsvTagJet      = new nTupleAnalysis::jetHists("offJets_matchedCalocsvTagJet",      fs, "");
    hOffJet_matchedCaloDeepcsvTag     = new nTupleAnalysis::jetHists("offJets_matchedCaloDeepcsvTag",     fs, "");
    hOffJet_matchedCaloDeepcsvTagJet  = new nTupleAnalysis::jetHists("offJets_matchedCaloDeepcsvTagJet",  fs, "");

    hOffJetTightDeepCSV_matchedCaloJet       = new nTupleAnalysis::jetHists("offJetsTight_matchedCaloJet",       fs, "");
    hOffJetMediumDeepCSV_matchedCaloJet      = new nTupleAnalysis::jetHists("offJetsMedium_matchedCaloJet",      fs, "");
    hOffJetLooseDeepCSV_matchedCaloJet       = new nTupleAnalysis::jetHists("offJetsLoose_matchedCaloJet",       fs, "");

    hOffJetMedDeepCSV_matchedCaloJet      = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedCaloJet",      fs, "", "matchedBJet");
    hOffJetMedDeepCSV_matchedCaloDeepCSV  = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedCaloDeepCSV",  fs, "", "matchedBJet");
    hOffJetMedDeepCSV_matchedCaloCSV      = new nTupleAnalysis::jetHists("offJetsMedDeepCSV_matchedCaloCSV",      fs, "", "matchedBJet");

    hOffJetMedDeepFlav_matchedCaloJet      = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedCaloJet",      fs, "", "matchedBJet");
    hOffJetMedDeepFlav_matchedCaloDeepCSV  = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedCaloDeepCSV",  fs, "", "matchedBJet");
    hOffJetMedDeepFlav_matchedCaloCSV      = new nTupleAnalysis::jetHists("offJetsMedDeepFlav_matchedCaloCSV",      fs, "", "matchedBJet");
  }

  if(isMC){
    hOffJets_matched_L        = new nTupleAnalysis::jetHists("offJets_matched_L",       fs, "", jetDetailString);
    hOffJets_matchedJet_L     = new nTupleAnalysis::jetHists("offJets_matchedJet_L",    fs, "", jetDetailString);

    hOffJets_matched_B        = new nTupleAnalysis::jetHists("offJets_matched_B",       fs, "", jetDetailString );
    hOffJets_matchedJet_B     = new nTupleAnalysis::jetHists("offJets_matchedJet_B",    fs, "", jetDetailString );

    hOffJets_matched_C        = new nTupleAnalysis::jetHists("offJets_matched_C",       fs, "");
    hOffJets_matchedJet_C     = new nTupleAnalysis::jetHists("offJets_matchedJet_C",    fs, "");

    if(doCaloJets){
      hOffJets_matchedCalo_L    = new nTupleAnalysis::jetHists("offJets_matchedCalo_L",   fs, "", jetDetailString);
      hOffJets_matchedCaloJet_L = new nTupleAnalysis::jetHists("offJets_matchedCaloJet_L",fs, "", jetDetailString);

      hOffJets_matchedCalo_B    = new nTupleAnalysis::jetHists("offJets_matchedCalo_B",   fs, "", jetDetailString );
      hOffJets_matchedCaloJet_B = new nTupleAnalysis::jetHists("offJets_matchedCaloJet_B",fs, "", jetDetailString );

      hOffJets_matchedCalo_C    = new nTupleAnalysis::jetHists("offJets_matchedCalo_C",   fs, "");
      hOffJets_matchedCaloJet_C = new nTupleAnalysis::jetHists("offJets_matchedCaloJet_C",fs, "");
    }
    

  }
  */

  hPfJets          = new nTupleAnalysis::jetHists("pfJets",           fs, "");
  //hPfJets_matched  = new nTupleAnalysis::jetHists("pfJets_matched",           fs, "");


  if(doCaloJets){
    hCaloJets            = new nTupleAnalysis::jetHists("caloJets",           fs, "");
    hCaloJets_matched    = new nTupleAnalysis::jetHists("caloJets_matched",           fs, "");
  }


  if(doTracks){
    /* off Tracks
    hOffTracks           = new nTupleAnalysis::trackHists("offTracks",fs, "");
    hOffTracks_unmatched = new nTupleAnalysis::trackHists("offTracks_unmatched",fs, "");
    hOffTracks_matched   = new nTupleAnalysis::trackHists("offTracks_matched",fs, "");
    hOffTracks_noV0           = new nTupleAnalysis::trackHists("offTracks_noV0",fs, "");
    hOffTracks_matched_noV0   = new nTupleAnalysis::trackHists("offTracks_matched_noV0",fs, "");
    */

    hPfTracks            = new nTupleAnalysis::trackHists("pfTracks",fs, "");
    hPfTracks_noV0       = new nTupleAnalysis::trackHists("pfTracks_noV0",fs, "");
    //hPfTracks_matched    = new nTupleAnalysis::trackHists("pfTracks_matched",fs, "");
    //hPfTracks_unmatched  = new nTupleAnalysis::trackHists("pfTracks_unmatched",fs, "");

    if(doCaloJets){
      /* off Track Calo
      hOffTracksCalo                = new nTupleAnalysis::trackHists("offTracksCalo",fs, "");
      hOffTracksCalo_unmatched      = new nTupleAnalysis::trackHists("offTracksCalo_unmatched",fs, "");
      hOffTracksCalo_matched        = new nTupleAnalysis::trackHists("offTracksCalo_matched",fs, "");
      hOffTracksCalo_noV0           = new nTupleAnalysis::trackHists("offTracksCalo_noV0",fs, "");
      hOffTracksCalo_matched_noV0   = new nTupleAnalysis::trackHists("offTracksCalo_matched_noV0",fs, "");
      */
      hCaloTracks            = new nTupleAnalysis::trackHists("caloTracks",fs, "");
      hCaloTracks_noV0       = new nTupleAnalysis::trackHists("caloTracks_noV0",fs, "");
      //hCaloTracks_matched    = new nTupleAnalysis::trackHists("caloTracks_matched",fs, "");
      //hCaloTracks_unmatched  = new nTupleAnalysis::trackHists("caloTracks_unmatched",fs, "");
    }
  /* OffBTags
    hOffBTagsAll        = new nTupleAnalysis::btaggingHists("offBTagsAll",fs, "");
    hOffBTags           = new nTupleAnalysis::btaggingHists("offBTags",fs, "");
    hOffBTags_matched   = new nTupleAnalysis::btaggingHists("offBTags_matched",fs, "");
    hOffBTags_unmatched = new nTupleAnalysis::btaggingHists("offBTags_unmatched",fs, "");
    hOffBTags_noV0           = new nTupleAnalysis::btaggingHists("offBTags_noV0",fs, "");
    hOffBTags_matched_noV0   = new nTupleAnalysis::btaggingHists("offBTags_matched_noV0",fs, "");
  */
    hPfBTags           = new nTupleAnalysis::btaggingHists("pfBTags",fs, "");
    //hPfBTags_matched   = new nTupleAnalysis::btaggingHists("pfBTags_matched",fs, "");
    //hPfBTags_unmatched = new nTupleAnalysis::btaggingHists("pfBTags_unmatched",fs, "");
  /*
    hDeltaROffPf       = dir.make<TH1F>("dR_OffPf",            "BTagAnalysisHLT/dR_OffPf;             DeltaR;   Entries", 100,-0.01, 5);

    hmttOff           = dir.make<TH1F>("mtt_off",            "BTagAnalysisHLT/mtt_off;             mtt;   Entries", 100,-0.01, 2);
    hmttOff_isFromV0  = dir.make<TH1F>("mtt_off_isFromV0",   "BTagAnalysisHLT/mtt_off_isFromV0;    mtt;   Entries", 100,-0.01, 2);
  */  
    hmttPf            = dir.make<TH1F>("mtt_pf",             "BTagAnalysisHLT/mtt_pf;              mtt;   Entries", 100,-0.01, 2);
    hmttPf_isFromV0   = dir.make<TH1F>("mtt_pf_isFromV0",    "BTagAnalysisHLT/mtt_pf_isFromV0;     mtt;   Entries", 100,-0.01, 2);
    if(doCaloJets){
      hmttCalo            = dir.make<TH1F>("mtt_calo",             "BTagAnalysisHLT/mtt_calo;              mtt;   Entries", 100,-0.01, 2);
      hmttCalo_isFromV0   = dir.make<TH1F>("mtt_calo_isFromV0",    "BTagAnalysisHLT/mtt_calo_isFromV0;     mtt;   Entries", 100,-0.01, 2);
    }
  }

  //
  // Vertex Hists
  //
  hVtx       = new nTupleAnalysis::vertexHists("hltVtx", fs, "HLT Vtx");
  hVtx       ->makeDiffHists("hltVtx", fs, "HLT Vtx");

  //hOffVtx    = new nTupleAnalysis::vertexHists("offVtx", fs, "Off Vtx");
  
/* Configure Selection
  //
  //  Configure Selection
  // 
  OfflineDeepCSVTightCut  = OfflineDeepCSVTightCut2017  ;
  OfflineDeepCSVMediumCut = OfflineDeepCSVMediumCut2017 ;
  OfflineDeepCSVLooseCut  = OfflineDeepCSVLooseCut2017  ;
  OfflineDeepFlavourMediumCut = OfflineDeepFlavourMediumCut2017 ;
  if(_year == "2018"){
    OfflineDeepCSVTightCut  = OfflineDeepCSVTightCut2018  ;
    OfflineDeepCSVMediumCut = OfflineDeepCSVMediumCut2018 ;
    OfflineDeepCSVLooseCut  = OfflineDeepCSVLooseCut2018 ;
    OfflineDeepFlavourMediumCut = OfflineDeepFlavourMediumCut2018 ;
  }
*/

/*Init the pile-up function
  //
  //  Init the pile-up function
  //
  if(isMC){
    if( PUFileName != ""){
      pileUpTool = new nTupleAnalysis::pileUpWeightTool(PUFileName);
    }else{
      cout << "Skipping PU reweighting" << endl;
    }
  }
*/
  //
  // Adding the NN
  //
  //
  if(nnConfig.getParameter<bool>("reCalcWeights")){
    edm::FileInPath nnInputFile = nnConfig.getParameter<edm::FileInPath>("NNConfig");
    cout << "Creating Neuralnet from  " << nnInputFile << endl;
    neuralNet = std::make_shared<NeuralNetworkAndConstants>(nnConfig);
  }else{
    neuralNet = nullptr; 
  }

} 


void BTagAnalysisHLT::monitor(long int e){
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

int BTagAnalysisHLT::eventLoop(int maxEvents, int nSkipEvents){
  //Set Number of events to process. Take manual maxEvents if maxEvents is > 0 and less than the total number of events in the input files. 
  nEvents = (maxEvents > 0 && maxEvents < treeEvents) ? maxEvents : treeEvents;

  cout << "\nProcess " << nEvents << " of " << treeEvents << " events.\n";

  start = std::clock();//2546000 //2546043
  lastTime = std::clock();
  lastEvent = 0;
  for(long int e = 0; e < nEvents; e++){

    if(e < nSkipEvents) continue;

    event->update(e);    
    processEvent();
    //if(debug) event->dump();

    //periodically update status
    //if( (e+1)%1 == 0 || e+1==nEvents || debug) 
    if( (e+1)%10000 == 0 || e+1==nEvents || debug) 
      monitor(e);

  }
  
  cout << endl;
  cout << "BTagAnalysisHLT::End of Event Loop" << endl;
  if(!isMC) cout << "Runs " << firstRun << "-" << lastRun << endl;

  minutes = static_cast<int>(duration/60);
  seconds = static_cast<int>(duration - minutes*60);
                                        
  if(isMC){
    fprintf(stdout,"---------------------------\nProcessed in %02i:%02i", minutes, seconds);
  }else{
    fprintf(stdout,"---------------------------\nProcessed in %02i:%02i", minutes, seconds);
  }
  return 0;
}

int BTagAnalysisHLT::processEvent(){
  if(debug) cout << "processEvent start" << endl;

  cutflow->Fill("all", 1.0);
  /*
  if(event->run != event->runAOD)
    return 0;

  if(event->event != event->eventAOD)
    return 0;
  */
  //cutflow->Fill("foundMatch", 1.0);
  /*
  if(debug) cout << "Fill/Select Muons" << endl;
  std::vector<nTupleAnalysis::muonPtr> selMuons;
  for(nTupleAnalysis::muonPtr& muon: event->muons){
    hAllMuons->Fill(muon,1.0);
    if(muon->tightId && muon->isolation_corrected < 0.2){
      hSelMuons->Fill(muon,1.0);
      if(debug) cout << "filled a muon" << endl;
      selMuons.push_back(muon);
    }
  }
  hAllMuons->nMuons->Fill(event->muons.size());
  if(debug) cout << "muons.size() = " << event->muons.size() << endl;
  hSelMuons->nMuons->Fill(selMuons.size());
  if(debug) cout << "selMuons.size() = " << selMuons.size() << endl;

  

  if(debug) cout << "Fill/Select Elecs" << endl;
  std::vector<nTupleAnalysis::elecPtr> selElecs;
  for(nTupleAnalysis::elecPtr& elec: event->elecs){
    hAllElecs->Fill(elec,1.0);
    if(elec->tightId && elec->isolation_corrected < 0.2){
      hSelElecs->Fill(elec,1.0);
      selElecs.push_back(elec);
    }
  }
  if(debug) cout << "Done Elec Loop" << endl;
  hAllElecs->nElecs->Fill(event->elecs.size());
  hSelElecs->nElecs->Fill(selElecs.size());
  if(debug) cout << "Done Elec Fill " << endl;

  if(doLeptonSel){
    if(debug) cout << "Doing Lepton Cuts " << endl;
    if(selMuons.size() == 1)
      cutflow->Fill("passMuonCut", 1.0);
    
    if(selElecs.size() == 1)
      cutflow->Fill("passElecCut", 1.0);
    
    if(selMuons.size() != 1){
      if(debug) cout << "Fail Muon Cut" << endl;
      return 0;
    }
    
    if(selElecs.size() != 1){
      if(debug) cout << "Fail Elec Cut" << endl;
      return 0;
    }
    cutflow->Fill("passLeptonCut", 1.0);
  }
  */
  float eventWeight = 1.0;
  float puWeight    = 1.0;

  //
  // Fill All events
  //
  /*
  if(debug) cout << "event->offPVs.size() = " << event->offPVs.size() << endl;
  hEvents->Fill(event->offPVs.size(),  0.0, eventWeight);
  if(puWeight)
    hEventsNoPUWeight->Fill(event->offPVs.size(),  0.0, eventWeight/puWeight);
  */
  hVtx      ->Fill(event->pvs, eventWeight);
  //hVtx      ->FillDiffHists(event->pvs, event->offPVs, eventWeight);
  //hOffVtx   ->Fill(event->offPVs, eventWeight);

  //unsigned int nOffJetsPreOLap      = 0;
  //unsigned int nOffJets             = 0;
  //unsigned int nOffJets_matched     = 0;
  //unsigned int nOffJets_matchedCalo = 0;
  if(debug) cout << "event->pfJets.size()" << event->pfJets.size() << endl;
  for(const nTupleAnalysis::jetPtr& pfJet : event->pfJets){ // in AOD+HLT, looping through event->offJets instead
    if(debug) cout << "entered for loop" << endl;
    cutflowJets->Fill("all", eventWeight);    

    if(fabs(pfJet->eta) > 2.4) continue;
    cutflowJets->Fill("eta", eventWeight);    
    
    if(pfJet->pt       < 35)   continue;
    cutflowJets->Fill("pt", eventWeight);    

    //hOffJetsPreOLap->Fill(offJet, eventWeight);

    //if(nTupleAnalysis::failOverlap(pfJet->p,event->muons,0.4)) continue;
    //cutflowJets->Fill("muonOlap", eventWeight);    

    //if(nTupleAnalysis::failOverlap(pfJet->p,event->elecs,0.4)) continue;
    //cutflowJets->Fill("elecOlap", eventWeight);    

    //
    // Check if jet is a Probe
    //
    unsigned int nOtherTags = 0;
    float min_dR_all  = 1000;
    float min_dR_bjet = 1000;
    //const JetData* tagJet = nullptr;
    for(const nTupleAnalysis::jetPtr& pfJetOther : event->pfJets){ // in AOD+HLT, looping through event->offJets instead
      if(pfJetOther == pfJet) continue;

      if(pfJetOther->pt       < 35)   continue;	
      if(fabs(pfJetOther->eta) > 2.4) continue;
      //if(nTupleAnalysis::failOverlap(pfJetOther->p,event->elecs,0.4)) continue;
      //if(nTupleAnalysis::failOverlap(pfJetOther->p,event->muons,0.4)) continue;
      float thisDr = pfJetOther->p.DeltaR(pfJet->p);
      if(thisDr < min_dR_all) min_dR_all = thisDr;
 
      //if(offJetOther->DeepCSV       < OfflineDeepCSVTightCut)   continue;	
      if(thisDr < min_dR_bjet) min_dR_bjet = thisDr;

      ++nOtherTags;
      //tagJet = &offJetOther;
    }

    if(min_dR_all  < 1000) pfJet->match_dR       = min_dR_all;
    if(min_dR_bjet < 1000) pfJet->match_dR_bjet = min_dR_bjet;
    
    // Require that there only be one other probe
    //    Note: this will suppress LF
    if(nOtherTags != 1) continue;
    cutflowJets->Fill("isProbe", eventWeight);    

    //
    // Testing Neural Net
    //
    if(neuralNet){
      lwt::ValueMap nnout = neuralNet->compute(pfJet);
      float DeepCSV_reCalc = nnout["probb"] + nnout["probbb"];
      pfJet->DeepCSV_reCalc = DeepCSV_reCalc;

      if(fabs(DeepCSV_reCalc - pfJet->DeepCSV) > 0.001){
        cout << "Event: " << event->event << endl;
        cout << "DeepCSV_reCalc: " << DeepCSV_reCalc << " vs " << pfJet->DeepCSV << endl;
        nnout = neuralNet->compute(pfJet, true);
      }
    }
    PFJetAnalysis(pfJet,eventWeight,nullptr);
    //++nOffJets_matched;
  }

  /*
    //
    //  Calo Jets
    //
    if(doCaloJets){
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
    }
  */
  //
  //  pf Jets
  //
  for(const nTupleAnalysis::jetPtr& pfJet : event->pfJets){
    if(fabs(pfJet->eta) > 2.5) continue;
    if(pfJet->pt       < 35)   continue;
  
    //if(nTupleAnalysis::failOverlap(pfJet->p,event->elecs, 0.4)) continue;
    //if(nTupleAnalysis::failOverlap(pfJet->p,event->muons, 0.4)) continue; 0624
  
    hPfJets->Fill(pfJet, eventWeight);
  }
  
  //
  //  calo Jets
  //
  if(doCaloJets){
    for(const nTupleAnalysis::jetPtr& caloJet : event->caloJets){
      if(fabs(caloJet->eta) > 2.5) continue;
      if(caloJet->pt       < 35)   continue;
  
      //caloJetHistsPreOLap.Fill(caloJet);
      //if(nTupleAnalysis::failOverlap(caloJet->p,event->elecs, 0.4)) continue;
      //if(nTupleAnalysis::failOverlap(caloJet->p,event->muons, 0.4)) continue;
  
      hCaloJets->Fill(caloJet, eventWeight);

      if(caloJet->DeepCSV > 1)
	      cout << "Error " << "Offline" << " DeepCSV is " << caloJet->DeepCSV << endl; 
			       
      if(caloJet->DeepCSVb > 1)   
	      cout << "Error " << "Offline" << " DeepCSVb is " << caloJet->DeepCSVb << endl; 
			       
      if(caloJet->DeepCSVbb > 1)  
	      cout << "Error " << "Offline" << " DeepCSVbb is " << caloJet->DeepCSVbb << endl; 

      const nTupleAnalysis::jetPtr caloJetMatchedJet = caloJet->matchedJet.lock();  
      if(caloJetMatchedJet){
	      hCaloJets_matched->Fill(caloJet, eventWeight);
  
	      //if(caloJet->m_matchedJet->m_hadronFlavour == 5)
	      //	caloJetHists_matchedB.Fill(caloJet);
	      //	else
	      //	  caloJetHists_matchedL.Fill(caloJet);
      }
    }
  } 

  //
  //if we are processing data, first apply lumiMask and trigger
  //
  if(!isMC){
    if(!passLumiMask()){
      if(debug) cout << "Fail lumiMask" << endl;
      return 0;
    }
    //cutflow->Fill(event, "lumiMask", true);

    //keep track of total lumi

    //if(!event->passHLT){
    //  if(debug) cout << "Fail HLT: data" << endl;
    //  return 0;
    //}
    //cutflow->Fill(event, "HLT", true);
  }
  //if(allEvents != NULL && event->passHLT) allEvents->Fill(event);

  return 0;
}

bool BTagAnalysisHLT::passLumiMask(){
  // if the lumiMask is empty, then no JSON file was provided so all
  // events should pass
  if(lumiMask.empty()) return true;

  //make lumiID run:lumiBlock
  //edm::LuminosityBlockID lumiID(event->run, event->lumiBlock);

  //define function that checks if a lumiID is contained in a lumiBlockRange
  //bool (*funcPtr) (edm::LuminosityBlockRange const &, edm::LuminosityBlockID const &) = &edm::contains;

  //Loop over the lumiMask and use funcPtr to check for a match
  //std::vector< edm::LuminosityBlockRange >::const_iterator iter = std::find_if (lumiMask.begin(), lumiMask.end(), boost::bind(funcPtr, _1, lumiID) );

  //return lumiMask.end() != iter; 
  return true;
}

BTagAnalysisHLT::~BTagAnalysisHLT(){
  cout << "BTagAnalysisHLT::destroyed" << endl;
} 

void BTagAnalysisHLT::PFJetAnalysis(const nTupleAnalysis::jetPtr& hltJet, float weight, const nTupleAnalysis::jetPtr& offJet=nullptr){

  if(doTracks){
  
    //
    // PF Tracks
    //
    unsigned int nPfTracks = 0;
    unsigned int nPfTracks_matched = 0;
    unsigned int nPfTracks_noV0 = 0;
    for(const nTupleAnalysis::trackPtr& pfTrack: hltJet->tracks){
      if(debug) cout << "do track for loop at:" << __LINE__ << endl;
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
      //if(pfTrack->p.DeltaR(offJet->p) > 0.29) continue; // pfTrack is not in cone of offJet
  	
      hPfTracks->Fill(pfTrack, weight); //all pftracks in matched jets
      hPfTracks->FillMatchStats(pfTrack, weight); //check how often we match pfTracks to more than one offTrack
      ++nPfTracks;
  
      if(!pfTrack->isfromV0){
        hPfTracks_noV0->Fill(pfTrack, weight); //all pftracks in matched jets
        ++nPfTracks_noV0;
      }
    }// pfTracks
  
    hPfTracks              ->nTracks->Fill(nPfTracks, weight);
    //hPfTracks_matched      ->nTracks->Fill(nPfTracks_matched, weight);
    hPfTracks_noV0         ->nTracks->Fill(nPfTracks_noV0, weight);
    //hOffTracks_matched_noV0->nTracks->Fill(nOffTracks_matched_noV0, weight);
  
    //
    //  PF BTags
    //
    unsigned int nPfTrkTags = 0;
  
    for(const nTupleAnalysis::trkTagVarPtr& pfTrkTag: hltJet->trkTagVars){
      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if offTrack.dR > 0.29 - offJet.match_dR: continue
      //if(pfTrkTag->trackDeltaR                              > 0.29) continue; // offTrack is not in cone of offJet
      //if(pfTrkTag->p.DeltaR(offJet->p) > 0.29) continue; // offTrack is not in cone of pfJet
  
      hPfBTags->FillTrkTagVarHists(pfTrkTag, weight);
      ++nPfTrkTags;
  
    }//OffTrkTag
  
    hPfBTags             ->trkTag_nTracks->Fill(nPfTrkTags, weight);

  }//doTracks  

  return;
}


void BTagAnalysisHLT::CaloJetAnalysis(const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight){

  if(doTracks){
    
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
      //if(caloTrack->p.DeltaR(offJet->p) > 0.29) continue; // caloTrack is not in cone of offJet
	
      hCaloTracks->Fill(caloTrack, weight); //all calotracks in matched jets
      hCaloTracks->FillMatchStats(caloTrack, weight); //check how often we match caloTracks to more than one offTrack
      ++nCaloTracks;

      if(!caloTrack->isfromV0){
	      hCaloTracks_noV0->Fill(caloTrack, weight); //all calotracks in matched jets
	      ++nCaloTracks_noV0;
      }

    }// caloTracks

    hCaloTracks              ->nTracks->Fill(nCaloTracks, weight);
    hCaloTracks_matched      ->nTracks->Fill(nCaloTracks_matched, weight);
    hCaloTracks_noV0         ->nTracks->Fill(nCaloTracks_noV0, weight);
    //hOffTracks_matched_noV0->nTracks->Fill(nOffTracks_matched_noV0, weight);

  }// doTracks

  return;
}