
#include "TriggerStudies/NtupleAna/interface/eventData.h"
#include <TTreeIndex.h>
using namespace TriggerStudies;

using std::cout;  using std::endl;


eventData::eventData(TChain* _treeRAW, TChain* _treeAOD, bool mc, std::string y, bool d, std::string jetDetailLevel){
  std::cout << "eventData::eventData()" << std::endl;
  treeRAW  = _treeRAW;
  treeAOD  = _treeAOD;

  if(!treeAOD){
    cout << "eventData::Only loading HLT data! " << endl;
    doOffline = false;
  }
  
  isMC  = mc;
  year  = y;
  debug = d;

  doCaloJets = jetDetailLevel.find("CaloJets") != std::string::npos;


  bool checkEventDiffs = false;
  if(checkEventDiffs && doOffline){

    //
    // Get All events in AOD
    //
    inputBranch(treeAOD, "Run",             runAOD);
    inputBranch(treeAOD, "Evt",           eventAOD);

    treeEventsAOD = treeAOD->GetEntries();

    for(long int eAOD = 0; eAOD < treeEventsAOD; eAOD++){
      treeAOD->GetEntry(eAOD);
      AODEvents.push_back(std::make_pair(runAOD, eventAOD));
    }

    //
    // Get All events in RAW
    //
    inputBranch(treeRAW, "Run",             run);
    inputBranch(treeRAW, "Evt",           event);
    int treeEventsRAW = treeRAW->GetEntries();

    RunEventMap RAWEvents;
    for(long int eRAW = 0; eRAW < treeEventsRAW; eRAW++){
      treeRAW->GetEntry(eRAW);
      RAWEvents.push_back(std::make_pair(run, event));
    }

    //
    // Events in AOD but not in RAW
    //
    std::cout << "Events in AOD but not in RAW"  << std::endl;
    for (auto AODPair : AODEvents) {
      bool inRAW = false;
      for (auto RAWPair : RAWEvents ){
	if(AODPair.first  != RAWPair.first) continue;
	if(AODPair.second != RAWPair.second) continue;
	inRAW = true;
      }
      if(!inRAW) {
	std::cout << "\t" << AODPair.first << "\t" << AODPair.second << std::endl;
      }
    }


    //
    // Events in RAW but not in AOD
    //
    std::cout << "Events in RAW but not in AOD"  << std::endl;
    for (auto RAWPair : RAWEvents ){
      bool inAOD = false;
      for (auto AODPair : AODEvents) {
	if(AODPair.first  != RAWPair.first) continue;
	if(AODPair.second != RAWPair.second) continue;
	inAOD = true;
      }
      if(!inAOD) {
	std::cout << "\t" << RAWPair.first << "\t" << RAWPair.second << std::endl;
      }
    }

  } // file check

  if(doOffline){
    treeAOD->SetBranchStatus("Run", 1);  
    treeAOD->SetBranchStatus("Evt", 1);  
    //treeAOD->BuildIndex("Run","Evt");
    TTreeIndex *index = new TTreeIndex(treeAOD,"Run", "Evt"); 
    treeAOD->SetTreeIndex(index);
  }    
    
  treeRAW->SetBranchStatus("Run", 1);  
  treeRAW->SetBranchStatus("Evt", 1);  
  //treeRAW->BuildIndex("Run","Evt");
  //TTreeIndex *indexRaw = new TTreeIndex(treeRAW,"Run", "Evt"); 
  //treeRAW->SetTreeIndex(indexRaw);
    
    
  if(doOffline){
    treeRAW->AddFriend(treeAOD);
  }
        
  //std::cout << "eventData::eventData() tree->Lookup(true)" << std::endl;
  ///tree->Lookup(true);
  //std::cout << "eventData::eventData() tree->LoadTree(0)" << std::endl;
  //treeRAW->LoadTree(0);
      
  inputBranch(treeRAW, "Run",             run);
  //inputBranch(tree, "luminosityBlock", lumiBlock);
  inputBranch(treeRAW, "Evt",           event);
        
  if(doOffline){
    inputBranch(treeAOD, "Run",             runAOD);
    //inputBranch(tree, "luminosityBlock", lumiBlock);
    inputBranch(treeAOD, "Evt",           eventAOD);
  }
    
  std::cout << "eventData::eventData() Initialize jets and muons" << std::endl;
  std::string jetSFName = year;
  if(jetSFName == "2018") jetSFName = "deepcsv2018";

  if(doOffline)  offTreeJets  = new nTupleAnalysis::jetData( "Jet",  treeRAW, true, isMC,  jetDetailLevel, "",      jetSFName );
  pfTreeJets   = new nTupleAnalysis::jetData( "Jet",  treeRAW, true, false, jetDetailLevel, "PFJet."       );
  if(doCaloJets) caloTreeJets = new nTupleAnalysis::jetData( "Jet",  treeRAW, true, false, jetDetailLevel, "CaloJet."     );
  
  //treeMuons    = new nTupleAnalysis::muonData("PFMuon",     treeRAW);
  //treeElecs    = new nTupleAnalysis::elecData("PFElectron", treeRAW);
  if(doOffline){
    if(treeRAW->FindBranch("nPatMuon")){
      treeMuons    = new nTupleAnalysis::muonData("PatMuon",     treeRAW, true, isMC, year);
    }else{
      cout << "No PatMuons (missing branch 'nPatMuon'). Will ignore Muons" << endl;
      treeMuons = nullptr;
    }

    if(treeRAW->FindBranch("nPatElec")){
      treeElecs    = new nTupleAnalysis::elecData("PatElec",     treeRAW, isMC, year);
    }else{
      cout << "No PatMuons (missing branch 'nPatElec'). Will ignore Elecs" << endl;
      treeElecs = nullptr;
    }
    
    offTreePVs = new nTupleAnalysis::vertexData("PV",     treeAOD);
  }
  
  treePVs    = new nTupleAnalysis::vertexData("PV",     treeRAW);
} 

void eventData::update(int e){
  if(debug){
    std::cout<<"Get Entry "<<e<<std::endl;
    std::cout<<treeRAW->GetCurrentFile()->GetName()<<std::endl;
    treeRAW->Show();

    if(doOffline){
      std::cout<<"Get Entry (AOD) "<<e<<std::endl;
      std::cout<<treeAOD->GetCurrentFile()->GetName()<<std::endl;
      treeAOD->Show();
    }

  }
  Long64_t loadStatus = treeRAW->LoadTree(e);
  if(loadStatus<0){
    std::cout << "Error "<<loadStatus<<" getting event "<<e<<std::endl; 
    return;
  }


//  Long64_t loadStatusAOD = treeAOD->LoadTree(e);
//  if(loadStatusAOD<0){
//    std::cout << "Error "<<loadStatus<<" getting AOD event "<<e<<std::endl; 
//    return;
//  }


  treeRAW->GetEntry(e);
  if(debug) std::cout<<"Got Entry "<<e<<std::endl;

  if(doOffline){
    if((run != runAOD) || (event != eventAOD)){
      if(debug) std::cout << "Run: " << run << " vs " << runAOD  << "  Evt: " << event << " vs " << eventAOD << std::endl;  
      //std::cout << "Tryuing with inedex " << treeAOD->GetEntryWithIndex(run,event)  << std::endl;
    }
  }

  //if((run != runAOD) || (event != eventAOD)){
  //  if(debug) std::cout << "Run: " << run << " vs " << runAOD  << "  Evt: " << event << " vs " << eventAOD << std::endl;  
  //  std::cout << "Run: " << run << " vs " << runAOD  << "  Evt: " << event << " vs " << eventAOD << std::endl;  
  //  
  //  std::cout << "Try manual lookup" << std::endl;
  //  Int_t runToPrint = -99;
  //  treeAOD->GetEntries();
  //  for(long int eAOD = 0; eAOD < treeEventsAOD; eAOD++){
  //    treeAOD->GetEntry(eAOD);
  //    if(runAOD != runToPrint){
  //	std::cout << " \t now! " << runAOD << " " << eventAOD << std::endl;
  //	runToPrint = runAOD;
  //    }
  //
  //    if(run != runAOD) continue;
  //    std::cout << " \t now! " << runAOD << " " << eventAOD << std::endl;
  //    if(event != eventAOD) continue;
  //    std::cout << " Found match! " << std::endl;
  //    break;
  //  }
  //
  //
  //}

  if(doOffline){
    if(run != runAOD){
      if(debug) std::cout << "run: " << run << " vs " << runAOD << std::endl;
      return;
    }

    if(event != eventAOD){
      if(debug) std::cout << "evt: " << event << " vs " << eventAOD << std::endl;  
      return;
    }
  }


  if(doOffline) offJets  = offTreeJets->getJets(20,1e6,2.4);
  pfJets   = pfTreeJets ->getJets(20,1e6,2.4);
  if(doCaloJets)
    caloJets = caloTreeJets ->getJets(30,1e6,2.4);

  if(doOffline){
    if(treeMuons)
      muons    = treeMuons  ->getMuons(20, 2.4);

    if(treeElecs)
      elecs    = treeElecs  ->getElecs(30, 2.4);

    offPVs = offTreePVs  ->getVerticies();
  }

  pvs    = treePVs     ->getVerticies();


  if(debug) std::cout<<"eventData updated\n";
  return;
}


void eventData::dump(){

  std::cout << "   Run: " << run    << std::endl;
  std::cout << " Event: " << event  << std::endl;  
  //std::cout << "Weight: " << weight << std::endl;
  //std::cout << " allJets: " << allJets .size() << " |  selJets: " << selJets .size() << " | tagJets: " << tagJets.size() << std::endl;
  //std::cout << "allMuons: " << allMuons.size() << " | isoMuons: " << isoMuons.size() << std::endl;

  return;
}

eventData::~eventData(){
  std::cout << "eventData::destroyed" << std::endl;
} 

