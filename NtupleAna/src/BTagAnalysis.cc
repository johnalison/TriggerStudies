#include <iostream>
#include <iomanip>
#include <cstdio>
#include <TROOT.h>
#include <boost/bind.hpp>


#include "TriggerStudies/NtupleAna/interface/BTagAnalysis.h"
#include "nTupleAnalysis/baseClasses/interface/helpers.h"

using std::cout; using std::endl;
using namespace TriggerStudies;
using std::vector;  using std::map; using std::string; using std::set;

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
//const float OnlineDeepCSVCutCalo  = 0.17;
//const float OnlineDeepCSVCutPuppi  = 0.17;
const float OnlineCSVCutPF        = 0.7;
//const float OnlineCSVCutCalo      = 0.5;
//const float OnlineCSVCutPuppi      = 0.5;


// 2017
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
const float OfflineDeepCSVTightCut2017  = 0.8001;
const float OfflineDeepCSVMediumCut2017 = 0.4941;
const float OfflineDeepCSVLooseCut2017  = 0.1522;

const float OfflineDeepFlavourTightCut2017   = 0.7489;
const float OfflineDeepFlavourMediumCut2017  = 0.3033;
const float OfflineDeepFlavourLooseCut2017   = 0.0521;

//const float drTrackToJet = 0.29;
//const float drTrackToJet = 1e6;
const float drTrackToJet = 0.25;







BTagAnalysis::BTagAnalysis(TChain* eventsTree1, TChain* eventsTree2, fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug, std::string PUFileName, std::string jetDetailString, const edm::ParameterSet& nnConfig, std::string pfJetName){
  if(_debug) cout<<"In BTagAnalysis constructor: Tree1: "<< eventsTree1 << " Tree2: " << eventsTree2 << endl;
  debug      = _debug;
  isMC       = _isMC;
  year       = _year;
  eventsTree1->SetBranchStatus("*", 0);

  if(!eventsTree2){
    doTree2 = false;
  }

  if(doTree2) eventsTree2->SetBranchStatus("*", 0);

  histogramming = _histogramming;

  doTracks    = jetDetailString.find("Tracks")    != std::string::npos;
  //doCaloJets  = jetDetailString.find("CaloJets")  != std::string::npos;
  //doPuppiJets = jetDetailString.find("PuppiJets") != std::string::npos;

  if(_debug) cout<<"Making eventData"<<endl;
  event      = new eventData(eventsTree1, eventsTree2, isMC, year, debug, jetDetailString, pfJetName);
  treeEvents = eventsTree1->GetEntries();

  if(_debug) cout<<"Making cutflow"<<endl;
  cutflow    = new nTupleAnalysis::cutflowHists("cutflow", fs);
  cutflow->AddCut("all");
  if(doTree2) cutflow->AddCut("foundMatch");
  if(doLeptonSel){
    cutflow->AddCut("passMuonCut");
    cutflow->AddCut("passElecCut");
    cutflow->AddCut("passLeptonCut");
  }
  if(doNJetCut) cutflow->AddCut("passNJetCut"); 
  if(doBTagCut) cutflow->AddCut("passNBJetCut");
    

  //
  //  Jets
  //
  if(_debug) cout<<"Making cutflowJets"<<endl;
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
  if(_debug) cout<<"Making hists"<<endl;
  dir = fs.mkdir("BTagAnalysis");

  hAllMuons = new nTupleAnalysis::muonHists("AllMuons", fs, "All Muons");
  hAllElecs = new nTupleAnalysis::elecHists("AllElecs", fs, "All Elecs");
  hSelMuons = new nTupleAnalysis::muonHists("SelMuons", fs, "Sel Muons");
  hSelElecs = new nTupleAnalysis::elecHists("SelElecs", fs, "Sel Elecs");
  hMuons    = new nTupleAnalysis::muonHists("Muons", fs, "Muons");
  hElecs    = new nTupleAnalysis::elecHists("Elecs", fs, "Elecs");

  hEvents                 = new nTupleAnalysis::eventHists("Events", fs);
  hEventsNoPUWeight       = new nTupleAnalysis::eventHists("EventsNoPUWeight", fs);


  hJets1PreOLap         = new nTupleAnalysis::jetHists(jet1HistName+"JetsPreOLap",        fs, "Pre Overlap");

  bool doEtaRegions = jetDetailString.find("EtaRegions") != std::string::npos;
  std::vector<float> etaBins = {1.5,3.0};

  if(!doEtaRegions) 
    etaBins.clear();

  hJets1                     = new nTupleAnalysis::jetHists(jet1HistName+"Jets",  fs, "", jetDetailString);
  if(isMC) hJets1_Truth      = new jetHistsTruthMatched(jet1HistName+"Jets",      fs, jetDetailString, etaBins);

  if(doTree2){
    jetCompHists         = new jetAnalysisHists(jet1HistName,  jet2HistName,  fs, jetDetailString, isMC);
    jetCompHists_PVMatch = new jetAnalysisHists(jet1HistName,  jet2HistName,  fs, jetDetailString, isMC, "_PVMatch");

    hJets2                     = new nTupleAnalysis::jetHists(jet2HistName+"Jets",           fs, "");
    if(isMC) hJets2_Truth      = new jetHistsTruthMatched(jet2HistName+"Jets",    fs, jetDetailString, etaBins);

    hJets2_matched  = new nTupleAnalysis::jetHists(jet2HistName+"Jets_matched",           fs, "");
    hDeltaRJet1Jet2       = dir.make<TH1F>(("dR_"+jet1HistName+jet2HistName).c_str(),            ("BTagAnalysis/dR_"+jet1HistName+jet2HistName+";             DeltaR;   Entries").c_str(), 100,-0.01, 5);
  }

  if(doTracks){

    hJets1BTagsAll        = new nTupleAnalysis::btaggingHists(jet1HistName+"BTagsAll",fs, "");


//    hmttOff           = dir.make<TH1F>("mtt_off",            "BTagAnalysis/mtt_off;             mtt;   Entries", 100,-0.01, 2);
//    hmttOff_isFromV0  = dir.make<TH1F>("mtt_off_isFromV0",   "BTagAnalysis/mtt_off_isFromV0;    mtt;   Entries", 100,-0.01, 2);
//    hmttPf            = dir.make<TH1F>("mtt_pf",             "BTagAnalysis/mtt_pf;              mtt;   Entries", 100,-0.01, 2);
//    hmttPf_isFromV0   = dir.make<TH1F>("mtt_pf_isFromV0",    "BTagAnalysis/mtt_pf_isFromV0;     mtt;   Entries", 100,-0.01, 2);
  }

  //
  //  Track Hists
  //
  hAllTracks    = new nTupleAnalysis::trackHists("allTracks", fs, "allTracks");

  //
  // Vertex Hists
  //

  hTree1Vtx    = new nTupleAnalysis::vertexHists(tree1HistName+"Vtx", fs, tree1HistName+" Vtx");

  if(doTree2) {
    hTree2Vtx       = new nTupleAnalysis::vertexHists(tree2HistName+"Vtx", fs, tree2HistName+" Vtx");
    hTree2Vtx       ->makeDiffHists(tree2HistName+"Vtx", fs, tree2HistName+" Vtx");
    hTree2Vtx_PVMatch       = new nTupleAnalysis::vertexHists(tree2HistName+"Vtx_PVMatch", fs, tree2HistName+" Vtx (PV Match)");
    hTree2Vtx_PVMatch       ->makeDiffHists(tree2HistName+"Vtx_PVMatch", fs, tree2HistName+" Vtx (PV Match)");

    hTree1Vtx_PVMatch    = new nTupleAnalysis::vertexHists(tree1HistName+"Vtx_PVMatch", fs, tree1HistName+" Vtx (PV Match");
  }

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
  if(_debug) cout<<"Leave constructor"<<endl;
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
  cout << "BTagAnalysis::End of Event Loop" << endl;
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

int BTagAnalysis::processEvent(){
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

  if(debug) cout << "Fill/Select Muons" << endl;
  std::vector<nTupleAnalysis::muonPtr> selMuons;
  for(nTupleAnalysis::muonPtr& muon: event->muons){
    hAllMuons->Fill(muon,1.0);
    if(muon->tightId && muon->miniPFRelIso_all < 0.2){
      hSelMuons->Fill(muon,1.0);
      selMuons.push_back(muon);
    }
  }
  hAllMuons->nMuons->Fill(event->muons.size());
  hSelMuons->nMuons->Fill(selMuons.size());


  if(debug) cout << "Fill/Select Elecs" << endl;

  std::vector<nTupleAnalysis::elecPtr> selElecs;
  for(nTupleAnalysis::elecPtr& elec: event->elecs){
    hAllElecs->Fill(elec,1.0);
    if(elec->mvaIso_WP80){
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

  float eventWeight = 1.0;
  float puWeight    = 1.0;
  if(isMC && pileUpTool){
//    puWeight = pileUpTool->getWeight(event->pvsTree1.size());
//    eventWeight =  puWeight;
//    if(doLeptonSel)
//      eventWeight *= (selElecs.at(0)->SF * selMuons.at(0)->SF);
  }



  //
  //  Jet1 BTags
  //
  if(debug) cout << "Count BTags " << endl;
  unsigned int nJets1ForCut = 0;
  unsigned int nJets1TaggedForCut = 0;
  float totalSFWeight = 1.0;
  for(const nTupleAnalysis::jetPtr& jet1 : event->jetCol1){

    for(const nTupleAnalysis::trkTagVarPtr& trkTag: jet1->trkTagVars) {
      hJets1BTagsAll->FillTrkTagVarHists(trkTag, eventWeight);
    }

    float absEta = fabs(jet1->eta);
    if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;
    if(jet1->pt       < minJetPt)   continue;
    if(jet1->deepFlavB  < minJetDeepJet)   continue;

    if(nTupleAnalysis::failOverlap(jet1->p,event->elecs,0.4)) continue;
    if(nTupleAnalysis::failOverlap(jet1->p,event->muons,0.4)) continue;

    ++nJets1ForCut;
    if(jet1->DeepCSV > OfflineDeepCSVTightCut) ++nJets1TaggedForCut;

    if(isMC)
      totalSFWeight *= jet1->SF;
  }

  if(doNJetCut){
     if(nJets1ForCut < 2      ){
       if(debug) cout << "Fail NJet Cut" << endl;
       return 0;
     }
     cutflow->Fill("passNJetCut", eventWeight);
     if(debug) cout << "Pass NJet Cut " << endl;
  }

  if(doBTagCut){

    if(nJets1TaggedForCut < 1) {
      if(debug) cout << "Fail NBJet Cut" << endl;
      return 0;
    }
    cutflow->Fill("passNBJetCut", eventWeight);
  }

  if(debug) cout << "Pass NBJet Cut " << endl;

  if(isMC)
    eventWeight *= totalSFWeight;

  if(debug) cout << "Fill Leptons " << endl;
  hMuons->nMuons->Fill(event->muons.size());
  for(auto muon: event->muons)
    hMuons->Fill(muon,eventWeight);

  hElecs->nElecs->Fill(event->elecs.size());
  for(auto elec: event->elecs)
    hElecs->Fill(elec,eventWeight);


  //
  // Fill All events
  //
  if(debug) cout << "Fill All Events " << endl;
  hEvents->Fill(*event->eventDataTree1, eventWeight);
  if(puWeight)
    hEventsNoPUWeight->Fill(*event->eventDataTree1, eventWeight/puWeight);

  hAllTracks->nTracks->Fill(event->trkCol1.size());
  for(auto trk : event->trkCol1)
    hAllTracks->Fill(trk, eventWeight);
  

//  hTree1Vtx   ->Fill(event->pvsTree1, eventWeight);

  bool vtxMatch = false;

  if(doTree2){
//    hTree2Vtx      ->Fill(event->pvsTree2, eventWeight);
//    hTree2Vtx      ->FillDiffHists(event->pvsTree2, event->pvsTree1, eventWeight);
//    if(event->pvsTree2.size() > 0 && event->pvsTree1.size() > 0){
//      if( fabs(event->pvsTree2.at(0)->z - event->pvsTree1.at(0)->z) < 0.02)
//	vtxMatch = true;
//    }
//
//    if(vtxMatch){
//      hTree2Vtx_PVMatch      ->Fill(event->pvsTree2, eventWeight);
//      hTree2Vtx_PVMatch      ->FillDiffHists(event->pvsTree2, event->pvsTree1, eventWeight);
//      hTree1Vtx_PVMatch   ->Fill(event->pvsTree1, eventWeight);
//    }
  }
    

  //
  //
  //
  unsigned int nJets1PreOLap      = 0;
  unsigned int nJets1             = 0;
  unsigned int nJets1_matched     = 0;
  //unsigned int nJets1_matchedCalo = 0;
  //unsigned int nJets1_matchedPuppi = 0;
  vector<unsigned int> usedJetIndex;

  if(debug) cout << "Starting jet1 loop  " << endl;
  for(const nTupleAnalysis::jetPtr& jet1 : event->jetCol1){
    cutflowJets->Fill("all", eventWeight);

    float absEta = fabs(jet1->eta);
    if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;

    cutflowJets->Fill("eta", eventWeight);

    if(jet1->pt       < minJetPt)   continue;
    if(jet1->deepFlavB  < minJetDeepJet)   continue;
    cutflowJets->Fill("pt", eventWeight);

    ++nJets1PreOLap;
    hJets1PreOLap->Fill(jet1, eventWeight);


    if(nTupleAnalysis::failOverlap(jet1->p,event->muons,0.4)) continue;
    cutflowJets->Fill("muonOlap", eventWeight);
    
    if(nTupleAnalysis::failOverlap(jet1->p,event->elecs,0.4)) continue;
    cutflowJets->Fill("elecOlap", eventWeight);


    bool requireProbe = false;
    
    if(requireProbe){
        //
        // Check if jet is a Probe
        //
        unsigned int nOtherTags = 0;
        float min_dR_all  = 1000;
        float min_dR_bjet = 1000;
        //const JetData* tagJet = nullptr;
    
        if(debug) cout << "Starting jet1 jets loop for probe check " << endl;
        for(const nTupleAnalysis::jetPtr& jet1Other : event->jetCol1){
          if(jet1Other == jet1) continue;
    
    
          if(jet1Other->pt       < minJetPt)   continue;
	  float absEta = fabs(jet1Other->eta);
	  if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;

          if(nTupleAnalysis::failOverlap(jet1Other->p,event->elecs,0.4)) continue;
          if(nTupleAnalysis::failOverlap(jet1Other->p,event->muons,0.4)) continue;
          float thisDr = jet1Other->p.DeltaR(jet1->p);
          if(thisDr < min_dR_all) min_dR_all = thisDr;
    
          if(jet1Other->DeepCSV       < OfflineDeepCSVTightCut)   continue;
    
          if(thisDr < min_dR_bjet) min_dR_bjet = thisDr;
    
          ++nOtherTags;
          //tagJet = &jet1Other;
        }
    
    
        if(min_dR_all  < 1000) jet1->match_dR       = min_dR_all;
        if(min_dR_bjet < 1000) jet1->match_dR_bjet = min_dR_bjet;
    
        // Require that there only be one other probe
        //    Note: this will suppress LF
        if(nOtherTags != 1) continue;
    }

    cutflowJets->Fill("isProbe", eventWeight);
    if(debug) cout << "Pass Probe cut " << endl;

    //
    //  Jet1 Jets
    //
    ++nJets1;
    hJets1->Fill(jet1,eventWeight);

    if(isMC){
      hJets1_Truth   ->Fill(jet1, jet1->hadronFlavour, jet1->flavourCleaned, eventWeight, jet1->p.Eta());
    }


    if(debug) cout << "Filling " << jet1HistName << " BTags " << endl;

    for(const nTupleAnalysis::trkTagVarPtr& trkTag: jet1->trkTagVars) {
      hJets1BTagsAll->FillTrkTagVarHists(trkTag, eventWeight);
    }

    if(jet1->DeepCSV > 1)
      cout << "Error " << jet1HistName << " DeepCSV is " << jet1->DeepCSV << endl;

    if(jet1->DeepCSVb > 1)
      cout << "Error " << jet1HistName << " DeepCSVb is " << jet1->DeepCSVb << endl;

    if(jet1->DeepCSVbb > 1)
      cout << "Error " << jet1HistName << " DeepCSVbb is " << jet1->DeepCSVbb << endl;


    // Match tree1 to tree2
    if(doTree2){

      float dR = 1e6;
      nTupleAnalysis::jetPtr matchedJet = nullptr;

      unsigned int jet2Index = 0;
      unsigned int jet2IndexMatch = 0;

      if(debug) cout << "Matching to " << jet2HistName << "  jets " << endl;
      for(const nTupleAnalysis::jetPtr& jet2 : event->jetCol2){
	++jet2Index;
	if(jet2->pt       < minJetPt)   {
	  continue;
	}
	float absEta = fabs(jet2->eta);
	if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;

	if(debug) cout << " new jet " << endl;
	float this_dR = jet2->p.DeltaR(jet1->p);
	if(debug) cout << " this dR " << this_dR << endl;
	if (this_dR < dR){
	  dR = this_dR;
	  matchedJet = jet2;
	  jet2IndexMatch = jet2Index;
	}
      }


      hDeltaRJet1Jet2->Fill(dR,eventWeight);

      bool hasValidMatch = (dR < 0.2);

      if(find(usedJetIndex.begin(), usedJetIndex.end(), jet2IndexMatch) != usedJetIndex.end()){
	if(debug) cout << "Using Jet again !"  <<endl;
	hasValidMatch = false;
      }else{
	usedJetIndex.push_back(jet2IndexMatch);
      }
    
      //
      //  Have Match
      //
      if( hasValidMatch){

	if(debug) cout << "Have a " << jet2HistName << " jet match " << endl;
	cutflowJets->Fill("hasJetMatch", eventWeight);
	jet1->matchedJet = matchedJet;

	//
	// Testing Neural Net
	//
	if(neuralNet){
	  if(debug) cout << "Testing the NN " << endl;

	  lwt::ValueMap nnout = neuralNet->compute(matchedJet);
	  float DeepCSV_reCalc = nnout["probb"] + nnout["probbb"];
	  matchedJet->DeepCSV_reCalc = DeepCSV_reCalc;

	  if(fabs(DeepCSV_reCalc - matchedJet->DeepCSV) > 0.001){
	    cout << "Event: " << event->eventDataTree1->event << endl;
	    cout << "DeepCSV_reCalc: " << DeepCSV_reCalc << " vs " << matchedJet->DeepCSV << endl;
	    nnout = neuralNet->compute(matchedJet, true);
	  }
	}


	if(debug) cout << "Doing " << jet2HistName << "JetAnalysis " << endl;
	jetCompHists->Fill(this, jet1, matchedJet, eventWeight, isMC, 
			 OfflineDeepCSVLooseCut, OfflineDeepCSVMediumCut, OfflineDeepCSVTightCut, 
			 OfflineDeepFlavourMediumCut,
			 OnlineCSVCutPF, OnlineDeepCSVCutPF, 
			 debug);

	if(vtxMatch)
	  jetCompHists_PVMatch->Fill(this, jet1, matchedJet, eventWeight, isMC, 
				   OfflineDeepCSVLooseCut, OfflineDeepCSVMediumCut, OfflineDeepCSVTightCut, 
				   OfflineDeepFlavourMediumCut,
				   OnlineCSVCutPF, OnlineDeepCSVCutPF, 
				   debug);
      

	++nJets1_matched;


      }//jet1 has match

    }//doTree2

  }//jet1s
  if(debug) cout << "Done jetCol1 " << endl;

  hJets1PreOLap    ->nJets->Fill(nJets1PreOLap ,eventWeight);
  hJets1           ->nJets->Fill(nJets1        ,eventWeight);

  if(jetCompHists){
    jetCompHists->hJets1_matched     ->nJets->Fill(nJets1_matched,eventWeight);
    jetCompHists->hJets1_matchedJet  ->nJets->Fill(nJets1_matched,eventWeight);
  }


  //
  //  Jet Collection 2
  //
  if(doTree2){
    for(const nTupleAnalysis::jetPtr& jet2 : event->jetCol2){

      float absEta = fabs(jet2->eta);
      if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;

      if(jet2->pt       < minJetPt)   continue;
      if(jet2->deepFlavB  < minJetDeepJet)   continue;
      //jet2HistsPreOLap.Fill(jet2);

      if(nTupleAnalysis::failOverlap(jet2->p,event->elecs, 0.4)) continue;
      if(nTupleAnalysis::failOverlap(jet2->p,event->muons, 0.4)) continue;

      hJets2->Fill(jet2, eventWeight);
      if(isMC){
	//cout << jet2->hadronFlavour << endl;
	hJets2_Truth   ->Fill(jet2, jet2->hadronFlavour, jet2->flavourCleaned, eventWeight, jet2->p.Eta());
      }


      const nTupleAnalysis::jetPtr jet2MatchedJet = jet2->matchedJet.lock();
      if(jet2MatchedJet){
	hJets2_matched->Fill(jet2, eventWeight);

	//if(isMC){
	//	if( jet2MatchedJet->hadronFlavour == 5){
	//	  hJets2_matched_B->Fill(jet2, eventWeight);
	//	}else if( jet2MatchedJet->hadronFlavour == 4){
	//	  hJets2_matched_C->Fill(jet2, eventWeight);
	//	}else if( jet2MatchedJet->hadronFlavour == 0){
	//	  hJets2_matched_L->Fill(jet2, eventWeight);
	//	}
	//}
      }
    }

  }//doTree2



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

bool BTagAnalysis::passLumiMask(){
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



BTagAnalysis::~BTagAnalysis(){
  cout << "BTagAnalysis::destroyed" << endl;
}


//
//  Set Match tracks
//
void BTagAnalysis::JetToJetTrackMatching(const nTupleAnalysis::jetPtr& jet1, const nTupleAnalysis::trackPtr& jet1Trk,
						const nTupleAnalysis::jetPtr& jet2,
						float dRMatch){

  float dR = 1e6;
  float dR2 = 1e6;

  nTupleAnalysis::trackPtr matchedTrack  = nullptr;
  nTupleAnalysis::trackPtr secondClosest = nullptr;

  for(const nTupleAnalysis::trackPtr& jet2Trk: jet2->tracks){

    //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
    if(jet2Trk->dR                  > drTrackToJet) continue; // jet2Trk is not in cone of jet2
    if(jet2Trk->p.DeltaR(jet1->p) > drTrackToJet) continue; // jet2Trk is not in cone of jet1

    float this_dR = jet1Trk->p.DeltaR(jet2Trk->p);

    if(this_dR > dR && this_dR < dR2){
      dR2 = this_dR;
      secondClosest = jet2Trk;
    }

    if(this_dR < dR){
      dR2 = dR;
      secondClosest = matchedTrack;

      dR  = this_dR;
      matchedTrack = jet2Trk;
    }

  }// matched tracks


  if(dR < dRMatch){
    matchedTrack->matchedTrack = jet1Trk;
    matchedTrack->nMatches += 1;

    jet1Trk->matchedTrack     = matchedTrack;
    jet1Trk->secondClosest    = secondClosest;
    jet1Trk->nMatches              += 1;
  }

  return;
}

//
//  Set Match Track Tags
//
void BTagAnalysis::JetToJetTrkTagMatching(const nTupleAnalysis::jetPtr& jet1, const nTupleAnalysis::trkTagVarPtr& jet1TrkTag,
					  const nTupleAnalysis::jetPtr& jet2,
					  float dRMatch){

  float dR = 1e6;
  nTupleAnalysis::trkTagVarPtr matchedTrkTag  = nullptr;
  for(const nTupleAnalysis::trkTagVarPtr& jet2TrkTag: jet2->trkTagVars){
    if(jet2TrkTag->trackDeltaR                  > drTrackToJet) continue; // jet2Track is not in cone of jet2
    if(jet2TrkTag->p.DeltaR(jet1->p) > drTrackToJet) continue; // jet2Track is not in cone of jet1

    float this_dR = jet1TrkTag->p.DeltaR(jet2TrkTag->p);
    if(this_dR < dR){
      dR  = this_dR;
      matchedTrkTag = jet2TrkTag;
    }


  }

  if(dR < dRMatch){
    matchedTrkTag->matchedTrkTagVar = jet1TrkTag;
    jet1TrkTag->matchedTrkTagVar     = matchedTrkTag;
  }//else{
    //cout << " dR  " << dR << endl;
    //cout << " \t offtrk  " << jet1TrkTag->trackEta << " " << jet1TrkTag->trackPhi << endl;
    //if(matchedTrkTag)
    //  cout << " \t hlttrk  " << matchedTrkTag->trackEta << " " << matchedTrkTag->trackPhi << endl;
  //}

  return;
}



//
//  Set Match Track Tags
//
void BTagAnalysis::JetToJetSVMatching(const nTupleAnalysis::svPtr& jet1SV,
				      const nTupleAnalysis::jetPtr& jet2,
				      float dRMatch){

  float dR2 = 1e6;

  nTupleAnalysis::svPtr matchedSV  = nullptr;
  for(const nTupleAnalysis::svPtr& jet2SV: jet2->svs){

    float dX = (jet1SV->x - jet2SV->x);
    float dY = (jet1SV->y - jet2SV->y);
    float dZ = (jet1SV->z - jet2SV->z);
    float this_dR2 =  dX*dX + dY*dY + dZ*dZ;

    if(this_dR2 < dR2){
      dR2  = this_dR2;
      matchedSV = jet2SV;
    }

  }

  if(dR2 < (dRMatch*dRMatch)){
    matchedSV->matchedSV = jet1SV;
    jet1SV     ->matchedSV     = matchedSV;
  }

  return;
}


void BTagAnalysis::jetAnalysisHists::Fill(BTagAnalysis* bTagAna, const nTupleAnalysis::jetPtr& jet1,const nTupleAnalysis::jetPtr& jet2, float weight, bool isMC,
					  float OfflineDeepCSVLooseCut, float OfflineDeepCSVMediumCut, float OfflineDeepCSVTightCut, 
					  float OfflineDeepFlavourMediumCut,
					  float OnlineCSVCut, float OnlineDeepCSVCut, 
					  bool debug){
  if(debug) cout << "In JetAnalysis " << endl;

  if(hJet1Tracks){
    if(debug) cout << " ... doing tracks " << endl;

    //
    //  Off tracks
    //
    unsigned int nJet1Tracks = 0;
    unsigned int nJet1Tracks_matched = 0;
    unsigned int nJet1Tracks_noV0 = 0;
    unsigned int nJet1Tracks_matched_noV0 = 0;


    for(const nTupleAnalysis::trackPtr& jet1Track: jet1->tracks){

      //
      //  track mass calculation
      //
      //for(const nTupleAnalysis::trackPtr& jet1Track_pair: jet1->tracks){
      //  if(jet1Track == jet1Track_pair) continue;
      //  float thisMass = (jet1Track->p + jet1Track_pair->p).M();
      //
      //  //FIXhmttOff->Fill(thisMass , weight);
      //  //FIXif(jet1Track->isfromV0)
      //	//FIX  hmttOff_isFromV0->Fill(thisMass , weight);
      //
      //}

      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if jet1Track.dR > 0.29 - jet1.match_dR: continue
      if(jet1Track->dR                > drTrackToJet) continue; // jet1Track is not in cone of jet1
      if(jet1Track->p.DeltaR(jet2->p) > drTrackToJet) continue; // jet1Track is not in cone of jet2


      hJet1Tracks->Fill(jet1Track, weight);
      ++nJet1Tracks;
      if(!jet1Track->isfromV0){
        if(hJet1Tracks_noV0) hJet1Tracks_noV0->Fill(jet1Track, weight);
        ++nJet1Tracks_noV0;
      }

      //
      //  Match jet1 track with jet2  Track
      //
      bTagAna->JetToJetTrackMatching(jet1, jet1Track, jet2, 0.01);

      const nTupleAnalysis::trackPtr jet1TrackMatchedTrack = jet1Track->matchedTrack.lock();

      if(jet1TrackMatchedTrack){

	if(!jet1Track->isfromV0 && !jet1TrackMatchedTrack->isfromV0){
	  if(hJet1Tracks_matched_noV0) hJet1Tracks_matched_noV0->Fill(jet1Track, weight);
	  ++nJet1Tracks_matched_noV0;
	}

	++nJet1Tracks_matched;
	hJet1Tracks_matched    ->Fill(jet1Track, weight);
	hJet2Tracks_matched ->Fill(jet1TrackMatchedTrack,weight);

      }else{
        hJet1Tracks_unmatched->Fill(jet1Track, weight);
      }

    }//off Tracks

    hJet1Tracks             ->nTracks->Fill(nJet1Tracks, weight);
    hJet1Tracks_matched     ->nTracks->Fill(nJet1Tracks_matched, weight);
    if(hJet1Tracks_noV0) hJet1Tracks_noV0        ->nTracks->Fill(nJet1Tracks_noV0, weight);
    if(hJet1Tracks_matched_noV0) hJet1Tracks_matched_noV0->nTracks->Fill(nJet1Tracks_matched_noV0, weight);


    //
    //  jet1 BTags trkTagVars
    //
    unsigned int nTrkTags = 0;
    unsigned int nTrkTags_matched = 0;
    unsigned int nTrkTags_noV0 = 0;
    unsigned int nTrkTags_matched_noV0 = 0;

    for(const nTupleAnalysis::trkTagVarPtr& jet1TrkTag: jet1->trkTagVars){

      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if jet1Track.dR > 0.29 - jet1.match_dR: continue
      if(jet1TrkTag->trackDeltaR                              > drTrackToJet) continue; // jet1Track is not in cone of jet1
      if(jet1TrkTag->p.DeltaR(jet2->p) > drTrackToJet) continue; // jet1Track is not in cone of jet2

      hJet1BTags->FillTrkTagVarHists(jet1TrkTag, weight);
      ++nTrkTags;

      if(!jet1TrkTag->matchIsFromV0){
        if(hJet1BTags_noV0) hJet1BTags_noV0->FillTrkTagVarHists(jet1TrkTag, weight);
        ++nTrkTags_noV0;
      }

      bTagAna->JetToJetTrkTagMatching(jet1, jet1TrkTag, jet2, 0.01);

      const nTupleAnalysis::trkTagVarPtr jet1TrackMatchedTrkTag = jet1TrkTag->matchedTrkTagVar.lock();
      if(jet1TrackMatchedTrkTag){

	if(!jet1TrkTag->matchIsFromV0 && !jet1TrackMatchedTrkTag->matchIsFromV0){
	  if(hJet1BTags_matched_noV0) hJet1BTags_matched_noV0->FillTrkTagVarHists(jet1TrkTag, weight);
	  ++nTrkTags_matched_noV0;
	}

	++nTrkTags_matched;
	hJet1BTags_matched    ->FillTrkTagVarHists(jet1TrkTag, weight);
	//const nTupleAnalysis::trackPtr jet1TrackMatchedTrkTag = jet1TrkTag->matchedTrkTagVar.lock();
	//hPfTracks_matched ->FillTrkTagVarHists(jet1TrackMatchedTrkTag,weight);
      }else{
	hJet1BTags_unmatched    ->FillTrkTagVarHists(jet1TrkTag, weight);
      }

    }//Jet1TrkTag

    hJet1BTags             ->trkTag_nTracks->Fill(nTrkTags, weight);
    hJet1BTags_matched     ->trkTag_nTracks->Fill(nTrkTags_matched, weight);
    if(hJet1BTags_noV0) hJet1BTags_noV0        ->trkTag_nTracks->Fill(nTrkTags_noV0, weight);
    if(hJet1BTags_matched_noV0) hJet1BTags_matched_noV0->trkTag_nTracks->Fill(nTrkTags_matched_noV0, weight);


    //
    //  Jet1 BTags SVs
    //
    for(const nTupleAnalysis::svPtr& jet1SV: jet1->svs){

      bTagAna->JetToJetSVMatching(jet1SV, jet2, 0.01);

    }


    //
    // Jet2 Tracks
    //
    unsigned int nJet2Tracks = 0;
    unsigned int nJet2Tracks_matched = 0;
    unsigned int nJet2Tracks_noV0 = 0;
    for(const nTupleAnalysis::trackPtr& jet2Track: jet2->tracks){

      //
      //  track mass calculation
      //
      //for(const nTupleAnalysis::trackPtr& jet2Track_pair: jet2->tracks){
      //  if(jet2Track == jet2Track_pair) continue;
      //  float thisMass = (jet2Track->p + jet2Track_pair->p).M();
      //
      //  //FIXhmttPf->Fill(thisMass , weight);
      //  //FIXif(pfTrack->isfromV0)
      //	//FIX  hmttPf_isFromV0->Fill(thisMass , weight);
      //
      //}

      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      if(jet2Track->dR                  > drTrackToJet) continue; // jet2Track is not in cone of jet2
      if(jet2Track->p.DeltaR(jet1->p) > drTrackToJet) continue; // jet2Track is not in cone of jet1

      hJet2Tracks->Fill(jet2Track, weight); //all pftracks in matched jets
      hJet2Tracks->FillMatchStats(jet2Track, weight); //check how often we match jet2Tracks to more than one jet1Track
      ++nJet2Tracks;

      if(!jet2Track->isfromV0){
        if(hJet2Tracks_noV0) hJet2Tracks_noV0->Fill(jet2Track, weight); //all pftracks in matched jets
        ++nJet2Tracks_noV0;
      }

      if(!jet2Track->nMatches){
        hJet2Tracks_unmatched->Fill(jet2Track, weight); //all unmatched pftracks
        hJet2Tracks_unmatched->FillMatchStats(jet2Track, weight);
      }else{
        hJet2Tracks_matched->FillMatchStats(jet2Track, weight);
        ++nJet2Tracks_matched;
      }
    }// jet2Tracks

    hJet2Tracks              ->nTracks->Fill(nJet2Tracks, weight);
    hJet2Tracks_matched      ->nTracks->Fill(nJet2Tracks_matched, weight);
    if(hJet2Tracks_noV0) hJet2Tracks_noV0         ->nTracks->Fill(nJet2Tracks_noV0, weight);
    //hJet1Tracks_matched_noV0->nTracks->Fill(nJet1Tracks_matched_noV0, weight);


    //
    //  jet2 BTags
    //
    unsigned int nJet2TrkTags = 0;

    for(const nTupleAnalysis::trkTagVarPtr& jet2TrkTag: jet2->trkTagVars){
      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if jet1Track.dR > 0.29 - jet1.match_dR: continue
      if(jet2TrkTag->trackDeltaR         > drTrackToJet) continue; // jet1Track is not in cone of jet1
      if(jet2TrkTag->p.DeltaR(jet1->p) > drTrackToJet) continue; // jet1Track is not in cone of jet2


      hJet2BTags->FillTrkTagVarHists(jet2TrkTag, weight);
      const nTupleAnalysis::trkTagVarPtr jet2TrkTagMatch = jet2TrkTag->matchedTrkTagVar.lock();
      if(jet2TrkTagMatch){
	hJet2BTags_matched  ->FillTrkTagVarHists(jet2TrkTag, weight);
      }else{
	hJet2BTags_unmatched->FillTrkTagVarHists(jet2TrkTag, weight);
      }

      ++nJet2TrkTags;

    }//jet2TrkTag

    hJet2BTags             ->trkTag_nTracks->Fill(nJet2TrkTags, weight);

  }//doTracks


  //
  // Jet info
  //
  if(debug) cout << " ... doing jet info " << endl;
  hJets1_matched->Fill(jet1,weight);
  if(hJets1_matched_eta) hJets1_matched_eta->Fill(jet1,jet2->p.Eta(),weight);
  
  hJets1_matchedJet->Fill(jet2,weight);
  if(hJets1_matchedJet_eta) hJets1_matchedJet_eta->Fill(jet2,jet2->p.Eta(),weight);

  //
  // Jet1 Btaggs
  //
  if((jet1->DeepCSV > OfflineDeepCSVTightCut))
    hJet1TightDeepCSV_matchedJet2Jet->Fill(jet2, weight);

  if((jet1->DeepCSV > OfflineDeepCSVMediumCut)){
    hJet1MediumDeepCSV_matchedJet2Jet->Fill(jet2, weight);
    hJet1MedDeepCSV_matchedJet2    ->Fill(jet1, weight);
    if(jet2->CSVv2   > OnlineCSVCut)     hJet1MedDeepCSV_matchedJet2CSV    ->Fill(jet1, weight);
    if(jet2->DeepCSV > OnlineDeepCSVCut) hJet1MedDeepCSV_matchedJet2DeepCSV->Fill(jet1, weight);
  }

  if((jet1->DeepCSV > OfflineDeepCSVLooseCut))
    hJet1LooseDeepCSV_matchedJet2Jet->Fill(jet2, weight);

  if(jet1->deepFlavB > OfflineDeepFlavourMediumCut){
    hJet1MedDeepFlav_matchedJet2 ->Fill(jet1, weight);
    if(jet2->CSVv2   > OnlineCSVCut)     hJet1MedDeepFlav_matchedJet2CSV    ->Fill(jet1, weight);
    if(jet2->DeepCSV > OnlineDeepCSVCut) hJet1MedDeepFlav_matchedJet2DeepCSV->Fill(jet1, weight);
  }

  //
  // If pass CVS working point
  //
  if(jet2->CSVv2 >= OnlineCSVCut){
    hJet1_matchedJet2csvTag   ->Fill(jet1, weight);
    hJet1_matchedJet2csvTagJet->Fill(jet2, weight);
  }


  //
  // If pass DeepCVS working point
  //
  if(jet2->DeepCSV >= OnlineDeepCSVCut){
    hJet1_matchedJet2DeepcsvTag   ->Fill(jet1, weight);
    hJet1_matchedJet2DeepcsvTagJet->Fill(jet2, weight);
  }


  if(isMC){
    hJets1_matched_Truth   ->Fill(jet1, jet1->hadronFlavour, jet1->flavourCleaned, weight, jet2->p.Eta());
    hJets1_matchedJet_Truth->Fill(jet2, jet1->hadronFlavour, jet1->flavourCleaned, weight, jet2->p.Eta());
  }// isMC


  return;
}





