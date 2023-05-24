
#include "TriggerStudies/NtupleAna/interface/eventData.h"
#include "nTupleAnalysis/baseClasses/interface/helpers.h"
#include <TTreeIndex.h>
using namespace TriggerStudies;

using std::cout;  using std::endl;


eventData::eventData(TChain* _tree1, TChain* _tree2, bool mc, std::string y, bool d, std::string jetDetailLevel, std::string pfJetName){
  std::cout << "eventData::eventData()" << _tree1 << " " << _tree2 << std::endl;
  tree1  = _tree1;
  tree2  = _tree2;

  if(!tree2){
    cout << "eventData::Only loading data from file1 ! " << endl;
    doTree2 = false;
  }

  isMC  = mc;
  year  = y;
  debug = d;

  //doCaloJets = jetDetailLevel.find("CaloJets") != std::string::npos;
  //doPuppiJets = jetDetailLevel.find("PuppiJets") != std::string::npos;

//  bool checkEventDiffs = false;
//  if(checkEventDiffs && doTree2){
//
//    //
//    // Get All events in Tree2
//    //
//    
//    if(inputBranch(tree2, "Run",             runTree2) == -1){
//      std::cout << "\t Trying run " << std::endl;
//      inputBranch(tree2, "run",             runTree2);
//    }
//
//    if(inputBranch(tree2, "Evt",           eventTree2) == -1){
//      std::cout << "\t Trying event " << std::endl;
//      inputBranch(tree2, "event",             runTree2);
//    }
//
//
//    treeEventsTree2 = tree2->GetEntries();
//
//    for(long int eTree2 = 0; eTree2 < treeEventsTree2; eTree2++){
//      tree2->GetEntry(eTree2);
//      Tree2Events.push_back(std::make_pair(runTree2, eventTree2));
//    }
//
//    //
//    // Get All events in Tree1
//    //
//    inputBranch(tree1, "Run",             run);
//    inputBranch(tree1, "Evt",           event);
//    int treeEventsTree1 = tree1->GetEntries();
//
//    RunEventMap Tree1Events;
//    for(long int eTree1 = 0; eTree1 < treeEventsTree1; eTree1++){
//      tree1->GetEntry(eTree1);
//      Tree1Events.push_back(std::make_pair(run, event));
//    }
//
//    //
//    // Events in Tree2 but not in Tree1
//    //
//    std::cout << "Events in Tree2 but not in Tree1"  << std::endl;
//    for (auto Tree2Pair : Tree2Events) {
//      bool inTree1 = false;
//      for (auto Tree1Pair : Tree1Events ){
//	if(Tree2Pair.first  != Tree1Pair.first) continue;
//	if(Tree2Pair.second != Tree1Pair.second) continue;
//	inTree1 = true;
//      }
//      if(!inTree1) {
//	std::cout << "\t" << Tree2Pair.first << "\t" << Tree2Pair.second << std::endl;
//      }
//    }
//
//
//    //
//    // Events in Tree1 but not in Tree2
//    //
//    std::cout << "Events in Tree1 but not in Tree2"  << std::endl;
//    for (auto Tree1Pair : Tree1Events ){
//      bool inTree2 = false;
//      for (auto Tree2Pair : Tree2Events) {
//	if(Tree2Pair.first  != Tree1Pair.first) continue;
//	if(Tree2Pair.second != Tree1Pair.second) continue;
//	inTree2 = true;
//      }
//      if(!inTree2) {
//	std::cout << "\t" << Tree1Pair.first << "\t" << Tree1Pair.second << std::endl;
//      }
//    }
//
//  } // file check


  if(doTree2){
    tree2->SetBranchStatus("Run", 1);
    tree2->SetBranchStatus("Evt", 1);
    //tree2->BuildIndex("Run","Evt");
    TTreeIndex *index = new TTreeIndex(tree2,"Run", "Evt");
    tree2->SetTreeIndex(index);
  }

  //tree1->BuildIndex("Run","Evt");
  //TTreeIndex *indexRaw = new TTreeIndex(tree1,"Run", "Evt");
  //tree1->SetTreeIndex(indexRaw);


  if(doTree2){
    tree1->AddFriend(tree2);
  }
  
  eventDataTree1 = new nTupleAnalysis::eventData("", tree1, true, isMC);

  if(doTree2){
    eventDataTree2 = new nTupleAnalysis::eventData("tree2", tree2, true, isMC);
  }

  std::cout << "eventData::eventData() Initialize jets and muons" << std::endl;
  std::string jetSFName = year;
  if(jetSFName == "2018") jetSFName = "deepcsv2018";

  if(doTree2){
    std::cout << "\t loading jets from tree2 with name " << "" << std::endl;    
    tree2Jets  = new nTupleAnalysis::jetData( "Jet",  tree2, true, isMC,  jetDetailLevel, "",      jetSFName );
  }

  std::cout << "\t loading jet from tree1 with name " << pfJetName << std::endl;    
  std::string jetName = "Jet";
  //std::string jetName = "btag";
  tree1Jets   = new nTupleAnalysis::jetData(jetName,  tree1, true, isMC, jetDetailLevel, pfJetName       );

  //std::string trackName = "PFCands";
  std::string trackName = "Track";
  std::cout << "\t loading tracks from tree1 with name " << trackName << std::endl;    
  if(tree1->FindBranch("nTrack")){
    tree1Tracks   = new nTupleAnalysis::trackData( trackName,  tree1 );
  }else{
    cout << "No Tracks (missing branch 'nTrack'). Will ignore Tracks" << endl;
    tree1Tracks = nullptr;
  }

  std::string svName = "SV";
  std::cout << "\t loading svs from tree1 with name " << svName << std::endl;    
  if(tree1->FindBranch("nSV")){
    tree1SVs   = new nTupleAnalysis::svData( svName,  tree1 );
  }else{
    cout << "No SVs (missing branch 'nSV'). Will ignore SVs" << endl;
    tree1SVs = nullptr;
  }



  if(tree1->FindBranch("nMuon")){
    treeMuons    = new nTupleAnalysis::muonData("Muon",     tree1, true, isMC, year);
  }else{
    cout << "No Muons (missing branch 'nMuon'). Will ignore Muons" << endl;
    treeMuons = nullptr;
  }

  if(tree1->FindBranch("nElectron")){
    treeElecs    = new nTupleAnalysis::elecData("Electron",     tree1, true, isMC, year);
  }else{
    cout << "No PatElectrons (missing branch 'nPatElec'). Will ignore Elecs" << endl;
    treeElecs = nullptr;
  }

  //tree1PVs = new nTupleAnalysis::vertexData("PV",     tree1);
  //if(doTree2) tree2PVs   = new nTupleAnalysis::vertexData("PV",     tree2);
  
  if(tree1->FindBranch("nGenJets")){
    genJetTree = new nTupleAnalysis::truthData(tree1, debug, "GenJet");
  }

}

void eventData::update(int e){
  if(debug){
    std::cout<<"Get Entry "<<e<<std::endl;
    std::cout<<tree1->GetCurrentFile()->GetName()<<std::endl;
    tree1->Show();

    if(doTree2){
      std::cout<<"Get Entry (Tree2) "<<e<<std::endl;
      std::cout<<tree2->GetCurrentFile()->GetName()<<std::endl;
      tree2->Show();
    }

  }
  Long64_t loadStatus = tree1->LoadTree(e);
  if(loadStatus<0){
    std::cout << "Error "<<loadStatus<<" getting event "<<e<<std::endl;
    return;
  }


//  Long64_t loadStatusTree2 = tree2->LoadTree(e);
//  if(loadStatusTree2<0){
//    std::cout << "Error "<<loadStatus<<" getting Tree2 event "<<e<<std::endl;
//    return;
//  }


  tree1->GetEntry(e);
  if(debug) std::cout<<"Got Entry "<<e<<std::endl;


  if(doTree2){
    if((eventDataTree1->run != eventDataTree2->run) || (eventDataTree1->event != eventDataTree2->event)){
      if(debug) std::cout << "Run: " << eventDataTree1->run << " vs " << eventDataTree2->run  << "  Evt: " << eventDataTree1->event << " vs " << eventDataTree2->event << std::endl;
      //std::cout << "Tryuing with inedex " << tree2->GetEntryWithIndex(run,event)  << std::endl;
    }
  }

  //if((run != runTree2) || (event != eventTree2)){
  //  if(debug) std::cout << "Run: " << run << " vs " << runTree2  << "  Evt: " << event << " vs " << eventTree2 << std::endl;
  //  std::cout << "Run: " << run << " vs " << runTree2  << "  Evt: " << event << " vs " << eventTree2 << std::endl;
  //
  //  std::cout << "Try manual lookup" << std::endl;
  //  Int_t runToPrint = -99;
  //  tree2->GetEntries();
  //  for(long int eTree2 = 0; eTree2 < treeEventsTree2; eTree2++){
  //    tree2->GetEntry(eTree2);
  //    if(runTree2 != runToPrint){
  //	std::cout << " \t now! " << runTree2 << " " << eventTree2 << std::endl;
  //	runToPrint = runTree2;
  //    }
  //
  //    if(run != runTree2) continue;
  //    std::cout << " \t now! " << runTree2 << " " << eventTree2 << std::endl;
  //    if(event != eventTree2) continue;
  //    std::cout << " Found match! " << std::endl;
  //    break;
  //  }
  //
  //
  //}

  if(doTree2){
    if(eventDataTree1->run != eventDataTree2->run){
      if(debug) std::cout << "run: " << eventDataTree1->run << " vs " << eventDataTree2->run << std::endl;
      return;
    }

    if(eventDataTree1->event != eventDataTree2->event){
      if(debug) std::cout << "evt: " << eventDataTree1->event << " vs " << eventDataTree2->event << std::endl;
      return;
    }
  }


  if(treeMuons){
    muons       = treeMuons  ->getMuons(30, 2.4);
    selMuons    = treeMuons  ->getMuons(30, 2.4, 3, true, 3);
  }

  if(treeElecs){
    elecs    = treeElecs  ->getElecs(30, 2.0);
    selElecs = treeElecs  ->getElecs(30, 2.0, true);
  }


  float minJetPt = 30;
  jetCol1   = tree1Jets ->getJets(minJetPt,1e6,2.4);
  selJets1.clear();
  for(const nTupleAnalysis::jetPtr& jet1 : jetCol1){

    if(nTupleAnalysis::failOverlap(jet1->p,muons,0.4)) continue;
    if(nTupleAnalysis::failOverlap(jet1->p,elecs,0.4)) continue;
    selJets1.push_back(jet1);
  }

  //pvsTree1    = tree1PVs     ->getVerticies();

  if(tree1Tracks){
    trkCol1   = tree1Tracks ->getTracks(true);
    for(const nTupleAnalysis::jetPtr& jet1 : selJets1){
      jet1->addTracks(trkCol1);
    }

  }


  if(tree1SVs){
    svCol1   = tree1SVs ->getSVs();
    for(const nTupleAnalysis::jetPtr& jet1 : selJets1){
      jet1->addSVs(svCol1);
    }

  }


  if(doTree2){
    jetCol2  = tree2Jets->getJets(minJetPt,1e6,2.4);
    //pvsTree2 = tree2PVs  ->getVerticies();
  }

  if(genJetTree) genJetTree->update();

  if(debug) std::cout<<"eventData updated\n";
  return;
}


void eventData::dump(){

  std::cout << "   Run: " << eventDataTree1->run    << std::endl;
  std::cout << " Event: " << eventDataTree1->event  << std::endl;
  //std::cout << "Weight: " << weight << std::endl;
  //std::cout << " allJets: " << allJets .size() << " |  selJets: " << selJets .size() << " | tagJets: " << tagJets.size() << std::endl;
  //std::cout << "allMuons: " << allMuons.size() << " | isoMuons: " << isoMuons.size() << std::endl;

  return;
}

eventData::~eventData(){
  std::cout << "eventData::destroyed" << std::endl;
}
