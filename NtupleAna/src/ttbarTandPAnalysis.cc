#include <iostream>
#include <iomanip>
#include <cstdio>
#include <TROOT.h>
#include <boost/bind.hpp>


#include "TriggerStudies/NtupleAna/interface/ttbarTandPAnalysis.h"


using std::cout; using std::endl;
using namespace TriggerStudies;
using std::vector;  using std::map; using std::string; using std::set;



//const float OfflineDeepFlavourTightCut2018   = 0.7264;
//const float OfflineDeepFlavourMediumCut2018  = 0.2770;
//const float OfflineDeepFlavourLooseCut2018   = 0.0494;



ttbarTandPAnalysis::ttbarTandPAnalysis() {

  if(debug) cout<<"Leave constructor"<<endl;
}


void ttbarTandPAnalysis::init(TChain* eventsTree1, TChain* eventsTree2, fwlite::TFileService& fs, std::string pfJetName, std::string jetDetailString){
  
  if(debug) cout<<"In ttbarTandPAnalysis constructor: Tree1: "<< eventsTree1 << " Tree2: " << eventsTree2 << endl;

  eventsTree1->SetBranchStatus("*", 0);

  if(!eventsTree2){
    doTree2 = false;
  }

  if(doTree2) eventsTree2->SetBranchStatus("*", 0);


  if(debug) cout<<"Making eventData"<<endl;
  event      = new eventData(eventsTree1, eventsTree2, isMC, year, debug, jetDetailString, pfJetName);
  treeEvents = eventsTree1->GetEntries();

  if(debug) cout<<"Making cutflow"<<endl;
  cutflow    = new nTupleAnalysis::cutflowHists("cutflow", fs);
  cutflow->AddCut("all");
  if(doTree2) cutflow->AddCut("foundMatch");
  if(doEMuTandP){
    cutflow->AddCut("passTTEMu_MuonCut");
    cutflow->AddCut("passTTEMu_ElecCut");
    cutflow->AddCut("passTTEMu_LeptonCut");
    cutflow->AddCut("passTTEMu_MeTCut");
    cutflow->AddCut("passTTEMu_NJetCut"); 
    cutflow->AddCut("passTTEMu_NBJetCut");
    cutflow->AddCut("passTTEMu_N2JetCut"); 
  }

  if(doMuTandP){
    cutflow->AddCut("passTTMu_MuonCut");
    cutflow->AddCut("passTTMu_ElecCut");
    cutflow->AddCut("passTTMu_LeptonCut");
    cutflow->AddCut("passTTMu_NJetCut"); 
    cutflow->AddCut("passTTMu_NBJetCut");
    cutflow->AddCut("passTTMu_MeTCut");
  }
    

  //
  //  Jets
  //
  if(debug) cout<<"Making cutflowJets"<<endl;
  cutflowJets    = new nTupleAnalysis::cutflowHists("cutflowJets", fs);
  cutflowJets->AddCut("all");
  cutflowJets->AddCut("eta");
  cutflowJets->AddCut("pt");
  cutflowJets->AddCut("muonOlap");
  cutflowJets->AddCut("elecOlap");
  cutflowJets->AddCut("isProbe");
  if(doTree2) cutflowJets->AddCut("hasJetMatch");


  //
  // hists
  //
  if(debug) cout<<"Making hists"<<endl;
  dir = fs.mkdir("ttbarTandPAnalysis");


  //
  // Init hists
  //
  allEvents = new ttbarTandPHists("AllEvents", fs, jetDetailString);
  if(doEMuTandP) emuTandP   = new ttbarTandPHists("emuTandP",    fs, jetDetailString);
  if(doEMuTandP) emuTandP2J = new ttbarTandPHists("emuTandP2J",  fs, jetDetailString);
  if(doMuTandP)  muTandP    = new ttbarTandPHists("muTandP",     fs, jetDetailString);


//  //
//  // Vertex Hists
//  //
//
//  hTree1Vtx    = new nTupleAnalysis::vertexHists(tree1HistName+"Vtx", fs, tree1HistName+" Vtx");


}


void ttbarTandPAnalysis::monitor(long int e){
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

int ttbarTandPAnalysis::eventLoop(int maxEvents, int nSkipEvents){
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
    if(debug) event->dump();

    //periodically update status
    //if( (e+1)%1 == 0 || e+1==nEvents || debug)
    if( (e+1)%10000 == 0 || e+1==nEvents || debug)
      monitor(e);
  }


  cout << endl;
  cout << "ttbarTandPAnalysis::End of Event Loop" << endl;
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

int ttbarTandPAnalysis::processEvent(){
  if(debug) cout << "processEvent start" << endl;
  if(debug) cout << "Run/Event: " << event->eventDataTree1->run << "/" << event->eventDataTree1->event << endl;

  cutflow->Fill("all", 1.0);

  if(doTree2){
    if(event->eventDataTree1->run != event->eventDataTree2->run)
      return 0;

    if(event->eventDataTree1->event != event->eventDataTree2->event)
      return 0;

    cutflow->Fill("foundMatch", 1.0);
  }

  
  allEvents->Fill(event, 1.0);  

  bool passEMuTandP = doEMuTandP;
  bool passMuTandP  = doMuTandP;
  if(doEMuTandP || doMuTandP){
    if(debug) cout << "Doing Lepton Cuts " << endl;

    if(event->selMuons.size() == 1){
      if(doEMuTandP) cutflow->Fill("passTTEMu_MuonCut", 1.0);
      if(doMuTandP)  cutflow->Fill("passTTMu_MuonCut",  1.0);
    }else{
      passEMuTandP = false;
      passMuTandP  = false;
    }

    if(event->selElecs.size() >= 1){
      if(doEMuTandP) cutflow->Fill("passTTEMu_ElecCut", 1.0);
    }else{
      passEMuTandP = false;
    }

    if(event->selElecs.size() == 0){
      if(doMuTandP) cutflow->Fill("passTTMu_ElecCut", 1.0);
    }else{
      passMuTandP = false;
    }


  }
  
  if(doEMuTandP && passEMuTandP){
    cutflow->Fill("passTTEMu_LeptonCut", 1.0);
  }

  if(doMuTandP && passMuTandP){
    cutflow->Fill("passTTMu_LeptonCut", 1.0);
  }

  //
  //  Met Cut 
  // 
  bool passMet = (event->eventDataTree1->puppiMetData->pt > 40);
  if(doEMuTandP || doMuTandP){
    
    if(passMet){
      if(doEMuTandP) cutflow->Fill("passTTEMu_MeTCut", 1.0);
      if(doMuTandP)  cutflow->Fill("passTTMu_MeTCut", 1.0);
    }else{
      passEMuTandP = false;
      passMuTandP = false;
    }

  }


  //
  //  nJet BTags
  //
  if(debug) cout << "Count BTags " << endl;
  unsigned int nJetsForCut = event->selJets1.size();
  unsigned int nJetsTaggedForCut = 0;
  float totalSFWeight = 1.0;
  for(const nTupleAnalysis::jetPtr& jet1 : event->selJets1){

    if(jet1->deepFlavB > OfflineDeepFlavourMediumCut2018) ++nJetsTaggedForCut;

    if(isMC)
      totalSFWeight *= jet1->SF;
  }

  float eventWeight = 1.0;
  if(isMC) eventWeight *= totalSFWeight;



  bool passEMuTandP2J = passEMuTandP2J;
  if(doEMuTandP || doMuTandP){

     if(nJetsForCut >=  2      ){
       if(doEMuTandP) cutflow->Fill("passTTEMu_NJetCut", eventWeight);
     }else{
       passEMuTandP = false;
     }



     if(nJetsForCut >= 4      ){
       if(doMuTandP) cutflow->Fill("passTTMu_NJetCut", eventWeight);
     }else{
       passMuTandP = false;
     }

    if(nJetsTaggedForCut > 0) {
      if(doEMuTandP) cutflow->Fill("passTTEMu_NBJetCut", eventWeight);
      if(doMuTandP)  cutflow->Fill("passTTMu_NBJetCut", eventWeight);
    }else{
      passEMuTandP = false;
      passMuTandP = false;
    }

     if(nJetsForCut ==  2      ){
       if(doEMuTandP) cutflow->Fill("passTTEMu_N2JetCut", eventWeight);
     }else{
       passEMuTandP2J = false;
     }

  }


  if(doEMuTandP && passEMuTandP){
    emuTandP->Fill(event, 1.0);  
  }

  if(doEMuTandP && passEMuTandP2J){
    emuTandP2J->Fill(event, 1.0);  
  }

  if(doMuTandP && passMuTandP){
    muTandP->Fill(event, 1.0);  
  }


//  //
//  //if we are processing data, first apply lumiMask and trigger
//  //
//  if(!isMC){
//    if(!passLumiMask()){
//      if(debug) cout << "Fail lumiMask" << endl;
//      return 0;
//    }
//    //cutflow->Fill(event, "lumiMask", true);
//
//    //keep track of total lumi
//
//    //if(!event->passHLT){
//    //  if(debug) cout << "Fail HLT: data" << endl;
//    //  return 0;
//    //}
//    //cutflow->Fill(event, "HLT", true);
//  }
//  //if(allEvents != NULL && event->passHLT) allEvents->Fill(event);
//




  return 0;
}

bool ttbarTandPAnalysis::passLumiMask(){
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



ttbarTandPAnalysis::~ttbarTandPAnalysis(){
  cout << "ttbarTandPAnalysis::destroyed" << endl;
}








