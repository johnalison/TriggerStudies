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







BTagAnalysis::BTagAnalysis(TChain* eventsRAW, TChain* eventsAOD, fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug, std::string PUFileName, std::string jetDetailString, const edm::ParameterSet& nnConfig, std::string pfJetName){
  if(_debug) cout<<"In BTagAnalysis constructor: RAW: "<< eventsRAW << " AOD: " << eventsAOD << endl;
  debug      = _debug;
  isMC       = _isMC;
  year       = _year;
  eventsRAW->SetBranchStatus("*", 0);

  if(!eventsAOD){
    doTree2 = false;
  }

  if(doTree2) eventsAOD->SetBranchStatus("*", 0);
  

  histogramming = _histogramming;

  doTracks    = jetDetailString.find("Tracks")    != std::string::npos;
  //doCaloJets  = jetDetailString.find("CaloJets")  != std::string::npos;
  //doPuppiJets = jetDetailString.find("PuppiJets") != std::string::npos;

  if(_debug) cout<<"Making eventData"<<endl;
  event      = new eventData(eventsRAW, eventsAOD, isMC, year, debug, jetDetailString, pfJetName);
  treeEvents = eventsRAW->GetEntries();

  if(_debug) cout<<"Making cutflow"<<endl;
  cutflow    = new nTupleAnalysis::cutflowHists("cutflow", fs);
  cutflow->AddCut("all");
  if(doTree2) cutflow->AddCut("foundMatch");
  if(doLeptonSel){
    cutflow->AddCut("passMuonCut");
    cutflow->AddCut("passElecCut");
    cutflow->AddCut("passLeptonCut");
  }
  if(doTree2) cutflow->AddCut("passNJetCut");
  if(doOfflineBTagCut)
    cutflow->AddCut("passNBJetCut");

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
  if(doTree2){
    cutflowJets->AddCut("hasHLTMatchPF");
    //cutflowJets->AddCut("hasHLTMatchCalo");
    //cutflowJets->AddCut("hasHLTMatchPuppi");
  }


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

  hOffJetsPreOLap         = new nTupleAnalysis::jetHists("offJetsPreOLap",        fs, "Pre Overlap");

  bool doEtaRegions = jetDetailString.find("EtaRegions") != std::string::npos;
  std::vector<float> etaBins = {1.5,3.0};

  if(!doEtaRegions) 
    etaBins.clear();

  hOffJets                = new nTupleAnalysis::jetHists("offJets",               fs, "", jetDetailString);
  if(isMC) hOffJets_Truth      = new jetHistsTruthMatched("offJets",    fs, jetDetailString, etaBins);

  if(doTree2){
    PFJetHists         = new jetAnalysisHists("off","pf", "PF", fs, jetDetailString, isMC);
    PFJetHists_PVMatch = new jetAnalysisHists("off","pf", "PF", fs, jetDetailString, isMC, "_PVMatch");

    hPfJets          = new nTupleAnalysis::jetHists("pfJets",           fs, "");
    if(isMC) hPfJets_Truth      = new jetHistsTruthMatched("pfJets",    fs, jetDetailString, etaBins);

    hPfJets_matched  = new nTupleAnalysis::jetHists("pfJets_matched",           fs, "");
    hDeltaROffPf       = dir.make<TH1F>("dR_OffPf",            "BTagAnalysis/dR_OffPf;             DeltaR;   Entries", 100,-0.01, 5);
  }

  if(doTracks){

    hOffBTagsAll        = new nTupleAnalysis::btaggingHists("offBTagsAll",fs, "");


    //hDeltaROffPuppi       = dir.make<TH1F>("dR_OffPuppi",            "BTagAnalysis/dR_OffPuppi;             DeltaR;   Entries", 100,-0.01, 5);

//    hmttOff           = dir.make<TH1F>("mtt_off",            "BTagAnalysis/mtt_off;             mtt;   Entries", 100,-0.01, 2);
//    hmttOff_isFromV0  = dir.make<TH1F>("mtt_off_isFromV0",   "BTagAnalysis/mtt_off_isFromV0;    mtt;   Entries", 100,-0.01, 2);
//    hmttPf            = dir.make<TH1F>("mtt_pf",             "BTagAnalysis/mtt_pf;              mtt;   Entries", 100,-0.01, 2);
//    hmttPf_isFromV0   = dir.make<TH1F>("mtt_pf_isFromV0",    "BTagAnalysis/mtt_pf_isFromV0;     mtt;   Entries", 100,-0.01, 2);
//    if(doCaloJets){
//      hmttCalo            = dir.make<TH1F>("mtt_calo",             "BTagAnalysis/mtt_calo;              mtt;   Entries", 100,-0.01, 2);
//      hmttCalo_isFromV0   = dir.make<TH1F>("mtt_calo_isFromV0",    "BTagAnalysis/mtt_calo_isFromV0;     mtt;   Entries", 100,-0.01, 2);
//    }
//
//    if(doPuppiJets){
//      hmttPuppi            = dir.make<TH1F>("mtt_puppi",             "BTagAnalysis/mtt_puppi;              mtt;   Entries", 100,-0.01, 2);
//      hmttPuppi_isFromV0   = dir.make<TH1F>("mtt_puppi_isFromV0",    "BTagAnalysis/mtt_puppi_isFromV0;     mtt;   Entries", 100,-0.01, 2);
//    }
  }


  //
  // Vertex Hists
  //
  hVtx       = new nTupleAnalysis::vertexHists("hltVtx", fs, "HLT Vtx");
  hVtx       ->makeDiffHists("hltVtx", fs, "HLT Vtx");
  hOffVtx    = new nTupleAnalysis::vertexHists("offVtx", fs, "Off Vtx");

  if(doTree2){
    hVtx_PVMatch       = new nTupleAnalysis::vertexHists("hltVtx_PVMatch", fs, "HLT Vtx (PV Match)");
    hVtx_PVMatch       ->makeDiffHists("hltVtx_PVMatch", fs, "HLT Vtx (PV Match)");
    hOffVtx_PVMatch    = new nTupleAnalysis::vertexHists("offVtx_PVMatch", fs, "Off Vtx (PV Match");
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

  cutflow->Fill("all", 1.0);

  if(doTree2){
    if(event->run != event->runTree2)
      return 0;

    if(event->event != event->eventTree2)
      return 0;

    cutflow->Fill("foundMatch", 1.0);
  }

  if(debug) cout << "Fill/Select Muons" << endl;
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


  if(debug) cout << "Fill/Select Elecs" << endl;

  std::vector<nTupleAnalysis::elecPtr> selElecs;
  for(nTupleAnalysis::elecPtr& elec: event->elecs){
    hAllElecs->Fill(elec,1.0);
    //if(elec->tightId && elec->isolation_corrected < 0.2){
      hSelElecs->Fill(elec,1.0);
      selElecs.push_back(elec);
      //}
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
    puWeight = pileUpTool->getWeight(event->pvsTree1.size());
    eventWeight =  puWeight;
    if(doLeptonSel)
      eventWeight *= (selElecs.at(0)->SF * selMuons.at(0)->SF);
  }




  //
  //  Offline BTags
  //
  if(debug) cout << "Count BTags " << endl;
  unsigned int nOffJetsForCut = 0;
  unsigned int nOffJetsTaggedForCut = 0;
  float totalSFWeight = 1.0;
  for(const nTupleAnalysis::jetPtr& offJet : event->jetCol1){

    for(const nTupleAnalysis::trkTagVarPtr& trkTag: offJet->trkTagVars) {
      hOffBTagsAll->FillTrkTagVarHists(trkTag, eventWeight);
    }

    float absEta = fabs(offJet->eta);
    if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;
    if(offJet->pt       < minJetPt)   continue;
    if(offJet->deepFlavB  < minJetDeepJet)   continue;

    if(nTupleAnalysis::failOverlap(offJet->p,event->elecs,0.4)) continue;
    if(nTupleAnalysis::failOverlap(offJet->p,event->muons,0.4)) continue;

    ++nOffJetsForCut;
    if(offJet->DeepCSV > OfflineDeepCSVTightCut) ++nOffJetsTaggedForCut;

    if(isMC)
      totalSFWeight *= offJet->SF;
  }

  if(doTree2){
     if(nOffJetsForCut < 2      ){
       if(debug) cout << "Fail NJet Cut" << endl;
       return 0;
     }
     cutflow->Fill("passNJetCut", eventWeight);
     if(debug) cout << "Pass NJet Cut " << endl;
  }

  if(doOfflineBTagCut){

    if(nOffJetsTaggedForCut < 1) {
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
  hEvents->Fill(event->pvsTree1.size(),  0.0, eventWeight);
  if(puWeight)
    hEventsNoPUWeight->Fill(event->pvsTree1.size(),  0.0, eventWeight/puWeight);

  hVtx      ->Fill(event->pvsTree2, eventWeight);
  hVtx      ->FillDiffHists(event->pvsTree2, event->pvsTree1, eventWeight);
  hOffVtx   ->Fill(event->pvsTree1, eventWeight);

  bool hltVtxMatch = false;
  if(event->pvsTree2.size() > 0 && event->pvsTree1.size() > 0){
    if( fabs(event->pvsTree2.at(0)->z - event->pvsTree1.at(0)->z) < 0.02)
      hltVtxMatch = true;
  }

  if(hltVtxMatch){
    hVtx_PVMatch      ->Fill(event->pvsTree2, eventWeight);
    hVtx_PVMatch      ->FillDiffHists(event->pvsTree2, event->pvsTree1, eventWeight);
    hOffVtx_PVMatch   ->Fill(event->pvsTree1, eventWeight);
  }
    

  //
  //
  //
  unsigned int nOffJetsPreOLap      = 0;
  unsigned int nOffJets             = 0;
  unsigned int nOffJets_matched     = 0;
  //unsigned int nOffJets_matchedCalo = 0;
  //unsigned int nOffJets_matchedPuppi = 0;
  vector<unsigned int> usedJetIndex;

  if(debug) cout << "Starting off jets loop  " << endl;
  for(const nTupleAnalysis::jetPtr& offJet : event->jetCol1){
    cutflowJets->Fill("all", eventWeight);

    float absEta = fabs(offJet->eta);
    if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;

    cutflowJets->Fill("eta", eventWeight);

    if(offJet->pt       < minJetPt)   continue;
    if(offJet->deepFlavB  < minJetDeepJet)   continue;
    cutflowJets->Fill("pt", eventWeight);

    ++nOffJetsPreOLap;
    hOffJetsPreOLap->Fill(offJet, eventWeight);


    if(nTupleAnalysis::failOverlap(offJet->p,event->muons,0.4)) continue;
    cutflowJets->Fill("muonOlap", eventWeight);
    
    if(nTupleAnalysis::failOverlap(offJet->p,event->elecs,0.4)) continue;
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
    
        if(debug) cout << "Starting off jets loop for probe check " << endl;
        for(const nTupleAnalysis::jetPtr& offJetOther : event->jetCol1){
          if(offJetOther == offJet) continue;
    
    
          if(offJetOther->pt       < minJetPt)   continue;
	  float absEta = fabs(offJetOther->eta);
	  if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;

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
    }

    cutflowJets->Fill("isProbe", eventWeight);
    if(debug) cout << "Pass Probe cut " << endl;

    //
    //  Offline Jets
    //
    ++nOffJets;
    hOffJets->Fill(offJet,eventWeight);

    if(isMC){
      hOffJets_Truth   ->Fill(offJet, offJet->hadronFlavour, offJet->flavourCleaned, eventWeight, offJet->p.Eta());
    }


    if(debug) cout << "Filling offline BTags " << endl;

    for(const nTupleAnalysis::trkTagVarPtr& trkTag: offJet->trkTagVars) {
      hOffBTagsAll->FillTrkTagVarHists(trkTag, eventWeight);
    }

    if(offJet->DeepCSV > 1)
      cout << "Error " << "Offline" << " DeepCSV is " << offJet->DeepCSV << endl;

    if(offJet->DeepCSVb > 1)
      cout << "Error " << "Offline" << " DeepCSVb is " << offJet->DeepCSVb << endl;

    if(offJet->DeepCSVbb > 1)
      cout << "Error " << "Offline" << " DeepCSVbb is " << offJet->DeepCSVbb << endl;


    // Match tree1 to tree2
    if(doTree2){

      float dR = 1e6;
      nTupleAnalysis::jetPtr matchedJet = nullptr;

      unsigned int pfJetIndex = 0;
      unsigned int pfJetIndexMatch = 0;

      if(debug) cout << "Matching to PF jets " << endl;
      for(const nTupleAnalysis::jetPtr& pfJet : event->jetCol2){
	++pfJetIndex;
	if(pfJet->pt       < minJetPt)   {
	  continue;
	}
	float absEta = fabs(pfJet->eta);
	if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;

	if(debug) cout << " new jet " << endl;
	float this_dR = pfJet->p.DeltaR(offJet->p);
	if(debug) cout << " this dR " << this_dR << endl;
	if (this_dR < dR){
	  dR = this_dR;
	  matchedJet = pfJet;
	  pfJetIndexMatch = pfJetIndex;
	}
      }


      hDeltaROffPf->Fill(dR,eventWeight);

      bool hasValidMatch = (dR < 0.2);

      if(find(usedJetIndex.begin(), usedJetIndex.end(), pfJetIndexMatch) != usedJetIndex.end()){
	if(debug) cout << "Using Jet again !"  <<endl;
	hasValidMatch = false;
      }else{
	usedJetIndex.push_back(pfJetIndexMatch);
      }
    
      //
      //  Have PF Match
      //
      if( hasValidMatch){
      


	if(debug) cout << "Have a PF jet match " << endl;
	cutflowJets->Fill("hasHLTMatchPF", eventWeight);
	offJet->matchedJet = matchedJet;

	//
	// Testing Neural Net
	//
	if(neuralNet){
	  if(debug) cout << "Testing the NN " << endl;

	  lwt::ValueMap nnout = neuralNet->compute(matchedJet);
	  float DeepCSV_reCalc = nnout["probb"] + nnout["probbb"];
	  matchedJet->DeepCSV_reCalc = DeepCSV_reCalc;

	  if(fabs(DeepCSV_reCalc - matchedJet->DeepCSV) > 0.001){
	    cout << "Event: " << event->event << endl;
	    cout << "DeepCSV_reCalc: " << DeepCSV_reCalc << " vs " << matchedJet->DeepCSV << endl;
	    nnout = neuralNet->compute(matchedJet, true);
	  }
	}


	if(debug) cout << "Doing PFJetAnalysis " << endl;
	PFJetHists->Fill(this, offJet, matchedJet, eventWeight, isMC, 
			 OfflineDeepCSVLooseCut, OfflineDeepCSVMediumCut, OfflineDeepCSVTightCut, 
			 OfflineDeepFlavourMediumCut,
			 OnlineCSVCutPF, OnlineDeepCSVCutPF, 
			 debug);

	if(hltVtxMatch)
	  PFJetHists_PVMatch->Fill(this, offJet, matchedJet, eventWeight, isMC, 
				   OfflineDeepCSVLooseCut, OfflineDeepCSVMediumCut, OfflineDeepCSVTightCut, 
				   OfflineDeepFlavourMediumCut,
				   OnlineCSVCutPF, OnlineDeepCSVCutPF, 
				   debug);
      

	++nOffJets_matched;


      }//offJet has match

    }//doTree2

  }//offJets


  hOffJetsPreOLap    ->nJets->Fill(nOffJetsPreOLap ,eventWeight);
  hOffJets           ->nJets->Fill(nOffJets        ,eventWeight);

  if(PFJetHists){
    PFJetHists->hOffJets_matched     ->nJets->Fill(nOffJets_matched,eventWeight);
    PFJetHists->hOffJets_matchedJet  ->nJets->Fill(nOffJets_matched,eventWeight);
  }


  //
  //  pf Jets
  //
  if(doTree2){
    for(const nTupleAnalysis::jetPtr& pfJet : event->jetCol2){

      float absEta = fabs(pfJet->eta);
      if(absEta > maxJetAbsEta || absEta < minJetAbsEta) continue;

      if(pfJet->pt       < minJetPt)   continue;
      if(pfJet->deepFlavB  < minJetDeepJet)   continue;
      //pfJetHistsPreOLap.Fill(pfJet);

      if(nTupleAnalysis::failOverlap(pfJet->p,event->elecs, 0.4)) continue;
      if(nTupleAnalysis::failOverlap(pfJet->p,event->muons, 0.4)) continue;

      hPfJets->Fill(pfJet, eventWeight);
      if(isMC){
	//cout << pfJet->hadronFlavour << endl;
	hPfJets_Truth   ->Fill(pfJet, pfJet->hadronFlavour, pfJet->flavourCleaned, eventWeight, pfJet->p.Eta());
      }


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
void BTagAnalysis::OfflineToOnlineTrackMatching(const nTupleAnalysis::jetPtr& offJet, const nTupleAnalysis::trackPtr& offTrk,
						const nTupleAnalysis::jetPtr& hltJet,
						float dRMatch){

  float dR = 1e6;
  float dR2 = 1e6;

  nTupleAnalysis::trackPtr matchedTrack  = nullptr;
  nTupleAnalysis::trackPtr secondClosest = nullptr;

  for(const nTupleAnalysis::trackPtr& hltTrack: hltJet->tracks){

    //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
    if(hltTrack->dR                  > drTrackToJet) continue; // hltTrack is not in cone of pfJet
    if(hltTrack->p.DeltaR(offJet->p) > drTrackToJet) continue; // hltTrack is not in cone of offJet

    float this_dR = offTrk->p.DeltaR(hltTrack->p);

    if(this_dR > dR && this_dR < dR2){
      dR2 = this_dR;
      secondClosest = hltTrack;
    }

    if(this_dR < dR){
      dR2 = dR;
      secondClosest = matchedTrack;

      dR  = this_dR;
      matchedTrack = hltTrack;
    }

  }// matched pf tracks


  if(dR < dRMatch){
    matchedTrack->matchedTrack = offTrk;
    matchedTrack->nMatches += 1;

    offTrk->matchedTrack     = matchedTrack;
    offTrk->secondClosest    = secondClosest;
    offTrk->nMatches              += 1;
  }

  return;
}

//
//  Set Match Track Tags
//
void BTagAnalysis::OfflineToOnlineTrkTagMatching(const nTupleAnalysis::jetPtr& offJet, const nTupleAnalysis::trkTagVarPtr& offTrkTag,
						 const nTupleAnalysis::jetPtr& hltJet,
						 float dRMatch){

  float dR = 1e6;
  nTupleAnalysis::trkTagVarPtr matchedTrkTag  = nullptr;
  for(const nTupleAnalysis::trkTagVarPtr& hltTrkTag: hltJet->trkTagVars){
    if(hltTrkTag->trackDeltaR                  > drTrackToJet) continue; // hltTrack is not in cone of hltJet
    if(hltTrkTag->p.DeltaR(offJet->p) > drTrackToJet) continue; // hltTrack is not in cone of offJet

    float this_dR = offTrkTag->p.DeltaR(hltTrkTag->p);
    if(this_dR < dR){
      dR  = this_dR;
      matchedTrkTag = hltTrkTag;
    }


  }

  if(dR < dRMatch){
    matchedTrkTag->matchedTrkTagVar = offTrkTag;
    offTrkTag->matchedTrkTagVar     = matchedTrkTag;
  }//else{
    //cout << " dR  " << dR << endl;
    //cout << " \t offtrk  " << offTrkTag->trackEta << " " << offTrkTag->trackPhi << endl;
    //if(matchedTrkTag)
    //  cout << " \t hlttrk  " << matchedTrkTag->trackEta << " " << matchedTrkTag->trackPhi << endl;
  //}

  return;
}



//
//  Set Match Track Tags
//
void BTagAnalysis::OfflineToOnlineSVMatching(const nTupleAnalysis::svPtr& offSV,
					     const nTupleAnalysis::jetPtr& hltJet,
					     float dRMatch){

  float dR2 = 1e6;

  nTupleAnalysis::svPtr matchedSV  = nullptr;
  for(const nTupleAnalysis::svPtr& hltSV: hltJet->svs){

    float dX = (offSV->x - hltSV->x);
    float dY = (offSV->y - hltSV->y);
    float dZ = (offSV->z - hltSV->z);
    float this_dR2 =  dX*dX + dY*dY + dZ*dZ;

    if(this_dR2 < dR2){
      dR2  = this_dR2;
      matchedSV = hltSV;
    }

  }

  if(dR2 < (dRMatch*dRMatch)){
    matchedSV->matchedSV = offSV;
    offSV     ->matchedSV     = matchedSV;
  }

  return;
}


void BTagAnalysis::jetAnalysisHists::Fill(BTagAnalysis* bTagAna, const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight, bool isMC,
					  float OfflineDeepCSVLooseCut, float OfflineDeepCSVMediumCut, float OfflineDeepCSVTightCut, 
					  float OfflineDeepFlavourMediumCut,
					  float OnlineCSVCut, float OnlineDeepCSVCut, 
					  bool debug){
  if(debug) cout << "In JetAnalysis " << endl;

  if(hOffTracks){
    if(debug) cout << " ... doing tracks " << endl;

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
      //for(const nTupleAnalysis::trackPtr& offTrack_pair: offJet->tracks){
      //  if(offTrack == offTrack_pair) continue;
      //  float thisMass = (offTrack->p + offTrack_pair->p).M();
      //
      //  //FIXhmttOff->Fill(thisMass , weight);
      //  //FIXif(offTrack->isfromV0)
      //	//FIX  hmttOff_isFromV0->Fill(thisMass , weight);
      //
      //}

      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if offTrack.dR > 0.29 - offJet.match_dR: continue
      if(offTrack->dR                  > drTrackToJet) continue; // offTrack is not in cone of offJet
      if(offTrack->p.DeltaR(hltJet->p) > drTrackToJet) continue; // offTrack is not in cone of pfJet


      hOffTracks->Fill(offTrack, weight);
      ++nOffTracks;
      if(!offTrack->isfromV0){
        if(hOffTracks_noV0) hOffTracks_noV0->Fill(offTrack, weight);
        ++nOffTracks_noV0;
      }

      //
      //  Match offline track with PF Track
      //
      bTagAna->OfflineToOnlineTrackMatching(offJet, offTrack, hltJet, 0.01);

      const nTupleAnalysis::trackPtr offTrackMatchedTrack = offTrack->matchedTrack.lock();

      if(offTrackMatchedTrack){

	if(!offTrack->isfromV0 && !offTrackMatchedTrack->isfromV0){
	  if(hOffTracks_matched_noV0) hOffTracks_matched_noV0->Fill(offTrack, weight);
	  ++nOffTracks_matched_noV0;
	}

	++nOffTracks_matched;
	hOffTracks_matched    ->Fill(offTrack, weight);
	hHltTracks_matched ->Fill(offTrackMatchedTrack,weight);

      }else{
        hOffTracks_unmatched->Fill(offTrack, weight);
      }

    }//off Tracks

    hOffTracks             ->nTracks->Fill(nOffTracks, weight);
    hOffTracks_matched     ->nTracks->Fill(nOffTracks_matched, weight);
    if(hOffTracks_noV0) hOffTracks_noV0        ->nTracks->Fill(nOffTracks_noV0, weight);
    if(hOffTracks_matched_noV0) hOffTracks_matched_noV0->nTracks->Fill(nOffTracks_matched_noV0, weight);


    //
    //  Off BTags trkTagVars
    //
    unsigned int nTrkTags = 0;
    unsigned int nTrkTags_matched = 0;
    unsigned int nTrkTags_noV0 = 0;
    unsigned int nTrkTags_matched_noV0 = 0;

    for(const nTupleAnalysis::trkTagVarPtr& offTrkTag: offJet->trkTagVars){

      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if offTrack.dR > 0.29 - offJet.match_dR: continue
      if(offTrkTag->trackDeltaR                              > drTrackToJet) continue; // offTrack is not in cone of offJet
      if(offTrkTag->p.DeltaR(hltJet->p) > drTrackToJet) continue; // offTrack is not in cone of pfJet

      hOffBTags->FillTrkTagVarHists(offTrkTag, weight);
      ++nTrkTags;

      if(!offTrkTag->matchIsFromV0){
        if(hOffBTags_noV0) hOffBTags_noV0->FillTrkTagVarHists(offTrkTag, weight);
        ++nTrkTags_noV0;
      }

      bTagAna->OfflineToOnlineTrkTagMatching(offJet, offTrkTag, hltJet, 0.01);

      const nTupleAnalysis::trkTagVarPtr offTrackMatchedTrkTag = offTrkTag->matchedTrkTagVar.lock();
      if(offTrackMatchedTrkTag){

	if(!offTrkTag->matchIsFromV0 && !offTrackMatchedTrkTag->matchIsFromV0){
	  if(hOffBTags_matched_noV0) hOffBTags_matched_noV0->FillTrkTagVarHists(offTrkTag, weight);
	  ++nTrkTags_matched_noV0;
	}

	++nTrkTags_matched;
	//cout << "Filling offBTag_match" << endl;
	hOffBTags_matched    ->FillTrkTagVarHists(offTrkTag, weight);
	//const nTupleAnalysis::trackPtr offTrackMatchedTrkTag = offTrkTag->matchedTrkTagVar.lock();
	//hPfTracks_matched ->FillTrkTagVarHists(offTrackMatchedTrkTag,weight);
      }else{
	hOffBTags_unmatched    ->FillTrkTagVarHists(offTrkTag, weight);
      }

    }//OffTrkTag

    hOffBTags             ->trkTag_nTracks->Fill(nTrkTags, weight);
    hOffBTags_matched     ->trkTag_nTracks->Fill(nTrkTags_matched, weight);
    if(hOffBTags_noV0) hOffBTags_noV0        ->trkTag_nTracks->Fill(nTrkTags_noV0, weight);
    if(hOffBTags_matched_noV0) hOffBTags_matched_noV0->trkTag_nTracks->Fill(nTrkTags_matched_noV0, weight);


    //
    //  Off BTags SVs
    //
    for(const nTupleAnalysis::svPtr& offSV: offJet->svs){

      bTagAna->OfflineToOnlineSVMatching(offSV, hltJet, 0.01);

    }//OffTrkTag


    //
    // HLT Tracks
    //
    unsigned int nHltTracks = 0;
    unsigned int nHltTracks_matched = 0;
    unsigned int nHltTracks_noV0 = 0;
    for(const nTupleAnalysis::trackPtr& hltTrack: hltJet->tracks){

      //
      //  track mass calculation
      //
      //for(const nTupleAnalysis::trackPtr& hltTrack_pair: hltJet->tracks){
      //  if(hltTrack == hltTrack_pair) continue;
      //  float thisMass = (hltTrack->p + hltTrack_pair->p).M();
      //
      //  //FIXhmttPf->Fill(thisMass , weight);
      //  //FIXif(pfTrack->isfromV0)
      //	//FIX  hmttPf_isFromV0->Fill(thisMass , weight);
      //
      //}

      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      if(hltTrack->dR                  > drTrackToJet) continue; // hltTrack is not in cone of pfJet
      if(hltTrack->p.DeltaR(offJet->p) > drTrackToJet) continue; // hltTrack is not in cone of offJet

      hHltTracks->Fill(hltTrack, weight); //all pftracks in matched jets
      hHltTracks->FillMatchStats(hltTrack, weight); //check how often we match hltTracks to more than one offTrack
      ++nHltTracks;

      if(!hltTrack->isfromV0){
        if(hHltTracks_noV0) hHltTracks_noV0->Fill(hltTrack, weight); //all pftracks in matched jets
        ++nHltTracks_noV0;
      }

      if(!hltTrack->nMatches){
        hHltTracks_unmatched->Fill(hltTrack, weight); //all unmatched pftracks
        hHltTracks_unmatched->FillMatchStats(hltTrack, weight);
      }else{
        hHltTracks_matched->FillMatchStats(hltTrack, weight);
        ++nHltTracks_matched;
      }
    }// hltTracks

    hHltTracks              ->nTracks->Fill(nHltTracks, weight);
    hHltTracks_matched      ->nTracks->Fill(nHltTracks_matched, weight);
    if(hHltTracks_noV0) hHltTracks_noV0         ->nTracks->Fill(nHltTracks_noV0, weight);
    //hOffTracks_matched_noV0->nTracks->Fill(nOffTracks_matched_noV0, weight);


    //
    //  Hlt BTags
    //
    unsigned int nHltTrkTags = 0;

    for(const nTupleAnalysis::trkTagVarPtr& hltTrkTag: hltJet->trkTagVars){
      //need to check that the track (with matching resolution cone r=0.01) is in region where R=0.3 circles inside the two jets overlap!
      //if offTrack.dR > 0.29 - offJet.match_dR: continue
      if(hltTrkTag->trackDeltaR         > drTrackToJet) continue; // offTrack is not in cone of offJet
      if(hltTrkTag->p.DeltaR(offJet->p) > drTrackToJet) continue; // offTrack is not in cone of pfJet


      hHltBTags->FillTrkTagVarHists(hltTrkTag, weight);
      const nTupleAnalysis::trkTagVarPtr hltTrkTagMatch = hltTrkTag->matchedTrkTagVar.lock();
      if(hltTrkTagMatch){
	hHltBTags_matched  ->FillTrkTagVarHists(hltTrkTag, weight);
      }else{
	hHltBTags_unmatched->FillTrkTagVarHists(hltTrkTag, weight);
      }

      ++nHltTrkTags;

    }//OffTrkTag

    hHltBTags             ->trkTag_nTracks->Fill(nHltTrkTags, weight);

  }//doTracks


  //
  // Jet info
  //
  if(debug) cout << " ... doing jet info " << endl;
  hOffJets_matched->Fill(offJet,weight);
  if(hOffJets_matched_eta) hOffJets_matched_eta->Fill(offJet,hltJet->p.Eta(),weight);
  
  hOffJets_matchedJet->Fill(hltJet,weight);
  if(hOffJets_matchedJet_eta) hOffJets_matchedJet_eta->Fill(hltJet,hltJet->p.Eta(),weight);

  //
  // Offline Btaggs
  //
  if((offJet->DeepCSV > OfflineDeepCSVTightCut))
    hOffJetTightDeepCSV_matchedHLTJet->Fill(hltJet, weight);
  if((offJet->DeepCSV > OfflineDeepCSVMediumCut)){
    hOffJetMediumDeepCSV_matchedHLTJet->Fill(hltJet, weight);
    hOffJetMedDeepCSV_matchedHLTJet    ->Fill(offJet, weight);
    if(hltJet->CSVv2   > OnlineCSVCut)     hOffJetMedDeepCSV_matchedHLTCSV    ->Fill(offJet, weight);
    if(hltJet->DeepCSV > OnlineDeepCSVCut) hOffJetMedDeepCSV_matchedHLTDeepCSV->Fill(offJet, weight);
  }

  if((offJet->DeepCSV > OfflineDeepCSVLooseCut))
    hOffJetLooseDeepCSV_matchedHLTJet->Fill(hltJet, weight);

  if(offJet->deepFlavB > OfflineDeepFlavourMediumCut){
    hOffJetMedDeepFlav_matchedHLTJet ->Fill(offJet, weight);
    if(hltJet->CSVv2   > OnlineCSVCut)     hOffJetMedDeepFlav_matchedHLTCSV    ->Fill(offJet, weight);
    if(hltJet->DeepCSV > OnlineDeepCSVCut) hOffJetMedDeepFlav_matchedHLTDeepCSV->Fill(offJet, weight);
  }

  //
  // If pass CVS working point
  //
  if(hltJet->CSVv2 >= OnlineCSVCut){
    hOffJet_matchedHLTcsvTag   ->Fill(offJet, weight);
    hOffJet_matchedHLTcsvTagJet->Fill(hltJet, weight);
  }


  //
  // If pass DeepCVS working point
  //
  if(hltJet->DeepCSV >= OnlineDeepCSVCut){
    hOffJet_matchedHLTDeepcsvTag   ->Fill(offJet, weight);
    hOffJet_matchedHLTDeepcsvTagJet->Fill(hltJet, weight);
  }


  if(isMC){
    hOffJets_matched_Truth   ->Fill(offJet, offJet->hadronFlavour, offJet->flavourCleaned, weight, hltJet->p.Eta());
    hOffJets_matchedJet_Truth->Fill(hltJet, offJet->hadronFlavour, offJet->flavourCleaned, weight, hltJet->p.Eta());
  }// isMC


  return;
}





