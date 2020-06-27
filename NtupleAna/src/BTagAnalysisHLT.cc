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


// https://cmswbm.cern.ch/cmsdb/servlet/HLTPath?PATHID=2117358
// https://cmswbm.cern.ch/cmsdb/servlet/HLTPath?PATHID=2090546
const float OnlineDeepCSVCutPF    = 0.24; 
const float OnlineDeepCSVCutCalo  = 0.17; 
const float OnlineCSVCutPF        = 0.7;
const float OnlineCSVCutCalo      = 0.5; 



BTagAnalysisHLT::BTagAnalysisHLT(TChain* _eventsRAW, /*TChain* _eventsAOD,*/ fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug, /*std::string PUFileName,*/ std::string jetDetailString, const edm::ParameterSet& nnConfig){
  if(_debug) cout<<"In BTagAnalysisHLT constructor"<<endl;
  debug      = _debug;
  isMC       = _isMC;
  year       = _year;
  eventsRAW     = _eventsRAW;
  eventsRAW->SetBranchStatus("*", 0);

  histogramming = _histogramming;

  doTracks = jetDetailString.find("Tracks") != std::string::npos;
  doCaloJets = jetDetailString.find("CaloJets") != std::string::npos;

  event      = new eventData(eventsRAW, nullptr, isMC, year, debug, jetDetailString);
  treeEvents = eventsRAW->GetEntries();

  cutflow    = new nTupleAnalysis::cutflowHists("cutflow", fs);
  cutflow->AddCut("all");
  cutflow->AddCut("passNJetCut");
  cutflow->AddCut("passNBJetCut");

  //
  //  Jets
  //
  cutflowJets    = new nTupleAnalysis::cutflowHists("cutflowJets", fs);
  cutflowJets->AddCut("all");
  cutflowJets->AddCut("eta");
  cutflowJets->AddCut("pt");



  //
  // hists
  //
  dir = fs.mkdir("BTagAnalysisHLT");

  //hEvents                 = new nTupleAnalysis::eventHists("Events", fs);
  //hEventsNoPUWeight       = new nTupleAnalysis::eventHists("EventsNoPUWeight", fs);

  hPfJets          = new nTupleAnalysis::jetHists("pfJets",           fs, "");

  if(doCaloJets){
    hCaloJets            = new nTupleAnalysis::jetHists("caloJets",           fs, "");
  }


  if(doTracks){

    hPfTracks            = new nTupleAnalysis::trackHists("pfTracks",fs, "");
    hPfTracks_noV0       = new nTupleAnalysis::trackHists("pfTracks_noV0",fs, "");

    if(doCaloJets){

      hCaloTracks            = new nTupleAnalysis::trackHists("caloTracks",fs, "");
      hCaloTracks_noV0       = new nTupleAnalysis::trackHists("caloTracks_noV0",fs, "");

    }

    hPfBTags           = new nTupleAnalysis::btaggingHists("pfBTags",fs, "");

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

  float eventWeight = 1.0;

  //
  // Fill All events
  //
  hVtx      ->Fill(event->pvs, eventWeight);

  if(debug) cout << "event->pfJets.size()" << event->pfJets.size() << endl;
  for(const nTupleAnalysis::jetPtr& pfJet : event->pfJets){ // in AOD+HLT, looping through event->offJets instead
    if(debug) cout << "entered for loop" << endl;
    cutflowJets->Fill("all", eventWeight);    

    if(fabs(pfJet->eta) > 2.4) continue;
    cutflowJets->Fill("eta", eventWeight);    
    
    if(pfJet->pt       < 35)   continue;
    cutflowJets->Fill("pt", eventWeight);    

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

    PFJetAnalysis(pfJet,eventWeight);
  }


  //
  //  Calo Jets
  //
  if(doCaloJets){

    for(const nTupleAnalysis::jetPtr& caloJet : event->caloJets){

      if(fabs(caloJet->eta) > 2.4) continue;
    
      if(caloJet->pt       < 35)   continue;
      
      CaloJetAnalysis(caloJet,eventWeight);
    }
    
  }
  
  //
  //  pf Jets
  //
  for(const nTupleAnalysis::jetPtr& pfJet : event->pfJets){
    if(fabs(pfJet->eta) > 2.5) continue;
    if(pfJet->pt       < 35)   continue;
  
    hPfJets->Fill(pfJet, eventWeight);
  }
  
  //
  //  calo Jets
  //
  if(doCaloJets){
    for(const nTupleAnalysis::jetPtr& caloJet : event->caloJets){
      if(fabs(caloJet->eta) > 2.5) continue;
      if(caloJet->pt       < 35)   continue;
  
      hCaloJets->Fill(caloJet, eventWeight);

    }
  } 


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

void BTagAnalysisHLT::PFJetAnalysis(const nTupleAnalysis::jetPtr& hltJet, float weight){

  if(doTracks){
  
    //
    // PF Tracks
    //
    unsigned int nPfTracks = 0;
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
  	
      hPfTracks->Fill(pfTrack, weight); //all pftracks in matched jets
      hPfTracks->FillMatchStats(pfTrack, weight); //check how often we match pfTracks to more than one offTrack
      ++nPfTracks;
  
      if(!pfTrack->isfromV0){
        hPfTracks_noV0->Fill(pfTrack, weight); //all pftracks in matched jets
        ++nPfTracks_noV0;
      }
    }// pfTracks
  
    hPfTracks              ->nTracks->Fill(nPfTracks, weight);
    hPfTracks_noV0         ->nTracks->Fill(nPfTracks_noV0, weight);
  
    //
    //  PF BTags
    //
    unsigned int nPfTrkTags = 0;
  
    for(const nTupleAnalysis::trkTagVarPtr& pfTrkTag: hltJet->trkTagVars){
  
      hPfBTags->FillTrkTagVarHists(pfTrkTag, weight);
      ++nPfTrkTags;
  
    }//OffTrkTag
  
    hPfBTags             ->trkTag_nTracks->Fill(nPfTrkTags, weight);

  }//doTracks  

  return;
}


void BTagAnalysisHLT::CaloJetAnalysis(const nTupleAnalysis::jetPtr& hltJet, float weight){

  if(doTracks){
    
    //
    // Calo Tracks
    //
    unsigned int nCaloTracks = 0;
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
    hCaloTracks_noV0         ->nTracks->Fill(nCaloTracks_noV0, weight);
    //hOffTracks_matched_noV0->nTracks->Fill(nOffTracks_matched_noV0, weight);

  }// doTracks

  return;
}
