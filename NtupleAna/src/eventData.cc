
#include "TriggerStudies/NtupleAna/interface/eventData.h"
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

  bool checkEventDiffs = false;
  if(checkEventDiffs && doTree2){

    //
    // Get All events in Tree2
    //
    inputBranch(tree2, "Run",             runTree2);
    inputBranch(tree2, "Evt",           eventTree2);


    treeEventsTree2 = tree2->GetEntries();

    for(long int eTree2 = 0; eTree2 < treeEventsTree2; eTree2++){
      tree2->GetEntry(eTree2);
      Tree2Events.push_back(std::make_pair(runTree2, eventTree2));
    }

    //
    // Get All events in Tree1
    //
    inputBranch(tree1, "Run",             run);
    inputBranch(tree1, "Evt",           event);
    int treeEventsTree1 = tree1->GetEntries();

    RunEventMap Tree1Events;
    for(long int eTree1 = 0; eTree1 < treeEventsTree1; eTree1++){
      tree1->GetEntry(eTree1);
      Tree1Events.push_back(std::make_pair(run, event));
    }

    //
    // Events in Tree2 but not in Tree1
    //
    std::cout << "Events in Tree2 but not in Tree1"  << std::endl;
    for (auto Tree2Pair : Tree2Events) {
      bool inTree1 = false;
      for (auto Tree1Pair : Tree1Events ){
	if(Tree2Pair.first  != Tree1Pair.first) continue;
	if(Tree2Pair.second != Tree1Pair.second) continue;
	inTree1 = true;
      }
      if(!inTree1) {
	std::cout << "\t" << Tree2Pair.first << "\t" << Tree2Pair.second << std::endl;
      }
    }


    //
    // Events in Tree1 but not in Tree2
    //
    std::cout << "Events in Tree1 but not in Tree2"  << std::endl;
    for (auto Tree1Pair : Tree1Events ){
      bool inTree2 = false;
      for (auto Tree2Pair : Tree2Events) {
	if(Tree2Pair.first  != Tree1Pair.first) continue;
	if(Tree2Pair.second != Tree1Pair.second) continue;
	inTree2 = true;
      }
      if(!inTree2) {
	std::cout << "\t" << Tree1Pair.first << "\t" << Tree1Pair.second << std::endl;
      }
    }

  } // file check


  if(doTree2){
    tree2->SetBranchStatus("Run", 1);
    tree2->SetBranchStatus("Evt", 1);
    //tree2->BuildIndex("Run","Evt");
    TTreeIndex *index = new TTreeIndex(tree2,"Run", "Evt");
    tree2->SetTreeIndex(index);
  }

  tree1->SetBranchStatus("Run", 1);
  tree1->SetBranchStatus("Evt", 1);
  //tree1->BuildIndex("Run","Evt");
  //TTreeIndex *indexRaw = new TTreeIndex(tree1,"Run", "Evt");
  //tree1->SetTreeIndex(indexRaw);



  if(doTree2){
    tree1->AddFriend(tree2);
  }

  //std::cout << "eventData::eventData() tree->Lookup(true)" << std::endl;
  ///tree->Lookup(true);
  //std::cout << "eventData::eventData() tree->LoadTree(0)" << std::endl;
  //tree1->LoadTree(0);

  inputBranch(tree1, "Run",             run);
  //inputBranch(tree, "luminosityBlock", lumiBlock);
  inputBranch(tree1, "Evt",           event);
  //inputBranch(tree1, "BitTrigger",    BitTrigger);

  connectBranchArr(true, tree1, "BitTrigger", BitTrigger,  "nBitTrigger",  "I");

  if(doTree2){
    inputBranch(tree2, "Run",             runTree2);
    //inputBranch(tree, "luminosityBlock", lumiBlock);
    inputBranch(tree2, "Evt",           eventTree2);
  }

  std::cout << "eventData::eventData() Initialize jets and muons" << std::endl;
  std::string jetSFName = year;
  if(jetSFName == "2018") jetSFName = "deepcsv2018";

  if(doTree2){
    std::cout << "\t loading jets from tree2 with name " << "" << std::endl;    
    tree2Jets  = new nTupleAnalysis::jetData( "Jet",  tree2, true, isMC,  jetDetailLevel, "",      jetSFName );
  }

  std::cout << "\t loading jet from tree1 with name " << pfJetName << std::endl;    
  tree1Jets   = new nTupleAnalysis::jetData( "Jet",  tree1, true, isMC, jetDetailLevel, pfJetName       );

  //treeMuons    = new nTupleAnalysis::muonData("PFMuon",     tree1);
  //treeElecs    = new nTupleAnalysis::elecData("PFElectron", tree1);
  if(tree1->FindBranch("nPatMuon")){
    treeMuons    = new nTupleAnalysis::muonData("PatMuon",     tree1, true, isMC, year);
  }else{
    cout << "No PatMuons (missing branch 'nPatMuon'). Will ignore Muons" << endl;
    treeMuons = nullptr;
  }

  if(tree1->FindBranch("nPatElec")){
    treeElecs    = new nTupleAnalysis::elecData("PatElec",     tree1, true, isMC, year);
  }else{
    cout << "No PatElectrons (missing branch 'nPatElec'). Will ignore Elecs" << endl;
    treeElecs = nullptr;
  }

  tree1PVs = new nTupleAnalysis::vertexData("PV",     tree1);
  
  if(doTree2) tree2PVs   = new nTupleAnalysis::vertexData("PV",     tree2);
  
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
    if((run != runTree2) || (event != eventTree2)){
      if(debug) std::cout << "Run: " << run << " vs " << runTree2  << "  Evt: " << event << " vs " << eventTree2 << std::endl;
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
    if(run != runTree2){
      if(debug) std::cout << "run: " << run << " vs " << runTree2 << std::endl;
      return;
    }

    if(event != eventTree2){
      if(debug) std::cout << "evt: " << event << " vs " << eventTree2 << std::endl;
      return;
    }
  }

  float minJetPt = 30;
  jetCol1   = tree1Jets ->getJets(minJetPt,1e6,4);
  pvsTree1    = tree1PVs     ->getVerticies();
  
  if(treeMuons)
    muons    = treeMuons  ->getMuons(30, 3.);

  if(treeElecs)
    elecs    = treeElecs  ->getElecs(30, 3.);


  if(doTree2){
    
    jetCol2  = tree2Jets->getJets(minJetPt,1e6,4);

    pvsTree2 = tree2PVs  ->getVerticies();
  }

  if(genJetTree) genJetTree->update();

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
