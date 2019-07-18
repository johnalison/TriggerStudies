
#include "TriggerStudies/NtupleAna/interface/eventData.h"
#include <TTreeIndex.h>
using namespace TriggerStudies;


eventData::eventData(TChain* _treeRAW, TChain* _treeAOD, bool mc, std::string y, bool d, std::string jetDetailLevel){
  std::cout << "eventData::eventData()" << std::endl;
  treeRAW  = _treeRAW;
  treeAOD  = _treeAOD;
  isMC  = mc;
  year  = y;
  debug = d;

  treeAOD->SetBranchStatus("Run", 1);  
  treeAOD->SetBranchStatus("Evt", 1);  
  //treeAOD->BuildIndex("Run","Evt");
  TTreeIndex *index = new TTreeIndex(treeAOD,"Run", "Evt"); 
  treeAOD->SetTreeIndex(index);


  treeRAW->SetBranchStatus("Run", 1);  
  treeRAW->SetBranchStatus("Evt", 1);  
  //treeRAW->BuildIndex("Run","Evt");
  //TTreeIndex *indexRaw = new TTreeIndex(treeRAW,"Run", "Evt"); 
  //treeRAW->SetTreeIndex(indexRaw);


  treeRAW->AddFriend(treeAOD);

    
  //std::cout << "eventData::eventData() tree->Lookup(true)" << std::endl;
  ///tree->Lookup(true);
  //std::cout << "eventData::eventData() tree->LoadTree(0)" << std::endl;
  treeRAW->LoadTree(0);
  
  initBranch(treeRAW, "Run",             run);
  //initBranch(tree, "luminosityBlock", lumiBlock);
  initBranch(treeRAW, "Evt",           event);
    

  initBranch(treeAOD, "Run",             runAOD);
  //initBranch(tree, "luminosityBlock", lumiBlock);
  initBranch(treeAOD, "Evt",           eventAOD);
  initBranch(treeRAW, "nPV",    nPV);
  initBranch(treeAOD, "nPV",    nPVAOD);

  std::cout << "eventData::eventData() Initialize jets and muons" << std::endl;
  offTreeJets  = new nTupleAnalysis::jetData( "Jet",  treeRAW, jetDetailLevel, "",      isMC, year );
  pfTreeJets   = new nTupleAnalysis::jetData( "Jet",  treeRAW, jetDetailLevel, "PFJet."       );
  caloTreeJets = new nTupleAnalysis::jetData( "Jet",  treeRAW, jetDetailLevel, "CaloJet."     );

  //treeMuons    = new nTupleAnalysis::muonData("PFMuon",     treeRAW);
  //treeElecs    = new nTupleAnalysis::elecData("PFElectron", treeRAW);
  treeMuons    = new nTupleAnalysis::muonData("PatMuon",     treeRAW, isMC, year);
  treeElecs    = new nTupleAnalysis::elecData("PatElec",     treeRAW, isMC, year);
} 

void eventData::update(int e){
  if(debug){
    std::cout<<"Get Entry "<<e<<std::endl;
    std::cout<<treeRAW->GetCurrentFile()->GetName()<<std::endl;
    treeRAW->Show();

    std::cout<<"Get Entry (AOD) "<<e<<std::endl;
    std::cout<<treeAOD->GetCurrentFile()->GetName()<<std::endl;
    treeAOD->Show();

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

  if((run != runAOD) || (event != eventAOD)){
    if(debug) std::cout << "Run: " << run << " vs " << runAOD  << "  Evt: " << event << " vs " << eventAOD << std::endl;  
  }

  if(run != runAOD){
    if(debug) std::cout << "run: " << run << " vs " << runAOD << std::endl;
    return;
  }

  if(event != eventAOD){
    if(debug) std::cout << "evt: " << event << " vs " << eventAOD << std::endl;  
    return;
  }


  offJets  = offTreeJets->getJets(20,1e6,2.4);
  pfJets   = pfTreeJets ->getJets(20,1e6,2.4);
  caloJets = caloTreeJets ->getJets(30,1e6,2.4);
  muons    = treeMuons  ->getMuons(20, 2.4);
  elecs    = treeElecs  ->getElecs(30, 2.4);
  

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

