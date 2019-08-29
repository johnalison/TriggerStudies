

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <TROOT.h>
#include <boost/bind.hpp>
#include <sstream>      // std::stringstream

#include "TriggerStudies/NtupleAna/interface/TrigTurnOnStudy.h"
#include "nTupleAnalysis/baseClasses/interface/helpers.h"

using namespace TriggerStudies;

using std::cout; using std::endl;

// 2018
const float OfflineDeepCSVTightCut2018  = 0.7527;
const float OfflineDeepCSVMediumCut2018 = 0.4184;
const float OfflineDeepCSVLooseCut2018  = 0.1241;

const float OnlineDeepCSVCut2018  = 0.6324;
const float OnlineCSVCut2018      = 0.8484;

// 2017 
const float OfflineDeepCSVTightCut2017  = 0.8001;
const float OfflineDeepCSVMediumCut2017 = 0.4941;
const float OfflineDeepCSVLooseCut2017  = 0.1522;

const float OnlineDeepCSVCut2017  = 0.6324;
const float OnlineCSVCut2017      = 0.8484;


TrigTurnOnStudy::TrigTurnOnStudy(TChain* _eventsRAW, TChain* _eventsAOD, fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug){
  if(_debug) std::cout<<"In TrigTurnOnStudy constructor"<<std::endl;
  debug      = _debug;
  isMC       = _isMC;
  year       = _year;
  eventsRAW     = _eventsRAW;
  eventsRAW->SetBranchStatus("*", 0);

  eventsAOD     = _eventsAOD;
  eventsAOD->SetBranchStatus("*", 0);


  histogramming = _histogramming;

  //event      = new eventData(eventsRAW, eventsAOD, isMC, year, debug, "Tracks.btagInputs");
  event      = new eventData(eventsRAW, eventsAOD, isMC, year, debug, "");
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
  dir = fs.mkdir("TrigTurnOnStudy");

  hAllMuons = new nTupleAnalysis::muonHists("AllMuons", fs, "All Muons");
  hAllElecs = new nTupleAnalysis::elecHists("AllElecs", fs, "All Elecs");
  hMuons    = new nTupleAnalysis::muonHists("Muons", fs, "Muons");
  hElecs    = new nTupleAnalysis::elecHists("Elecs", fs, "Elecs");

  hOffJetsPreOLap         = new nTupleAnalysis::jetHists("offJetsPreOLap",        fs, "Pre Overlap");
  hOffJets                = new nTupleAnalysis::jetHists("offJets",               fs, "");
  hAllOffJets             = new nTupleAnalysis::jetHists("allOffJets",               fs, "");
  hOffJets_matched        = new nTupleAnalysis::jetHists("offJets_matched",       fs, "");
  hOffJets_matchedJet     = new nTupleAnalysis::jetHists("offJets_matchedJet",    fs, "");

  hdR_all =  dir.make<TH1F>("dR_all",      "TrigTurnOnStudy/dR_all      ;#DeltaR(Online,Offline);;Entries"   ,100, 0,0.45);
  hdR_2nd_all =  dir.make<TH1F>("dR_2nd_all",      "TrigTurnOnStudy/dR_2nd_all      ;#DeltaR(Online,Offline);;Entries"   ,100, 0,3);
  hdR_misMatchPt =  dir.make<TH1F>("dR_misMatchPt",      "/TrigTurnOnStudy/dR_misMatchPt      ;#DeltaR(Online,Offline);;Entries"  ,100, 0,0.45);
  hdR_2nd_misMatchPt =  dir.make<TH1F>("dR_2nd_misMatchPt",      "/TrigTurnOnStudy/dR_2nd_misMatchPt      ;#DeltaR(Online,Offline);;Entries"  ,100, 0,3);

  for(float pt : trigThresolds){
    std::stringstream ss; 
    ss << pt;
    std::string ptStr = ss.str();
    turnOns.insert(std::make_pair(pt,new turnOnHists(ptStr, dir)));
    turnOnsAll.insert(std::make_pair(pt,new turnOnHists("All"+ptStr, dir)));
    if(isMC){
      turnOns_L.insert(std::make_pair(pt,new turnOnHists(ptStr+"_L", dir)));
      turnOns_B.insert(std::make_pair(pt,new turnOnHists(ptStr+"_B", dir)));
      turnOnsAll_L.insert(std::make_pair(pt,new turnOnHists("All"+ptStr+"_L", dir)));
      turnOnsAll_B.insert(std::make_pair(pt,new turnOnHists("All"+ptStr+"_B", dir)));
    }
    //offJetPts .insert(std::make_pair(pt,dir.make<TH1F>(("offJetPt"+ptStr).c_str(),             ("TrigTurnOnStudy/offJetPt"+ptStr+";               jet #P_T [GeV];   Entries").c_str(), 100,0, 200)));
  }

  for(float ht : htThresolds){
    std::stringstream ss; 
    ss << ht;
    std::string htStr = ss.str();
    hTTurnOns   .insert(std::make_pair(ht,new hTTurnOnHists(htStr, dir)));
    hTTurnOnsAll.insert(std::make_pair(ht,new hTTurnOnHists("All"+htStr, dir)));
  }



//  if(isMC){
//    hOffJets_matched_L        = new nTupleAnalysis::jetHists("offJets_matched_L",   fs, "");
//    hOffJets_matchedJet_L     = new nTupleAnalysis::jetHists("offJets_matchedJet_L",fs, "");
//
//    hOffJets_matched_B        = new nTupleAnalysis::jetHists("offJets_matched_B",   fs, "");
//    hOffJets_matchedJet_B     = new nTupleAnalysis::jetHists("offJets_matchedJet_B",fs, "");
//  }

//  hPfJets          = new nTupleAnalysis::jetHists("pfJets",           fs, "");
//  hPfJets_matched  = new nTupleAnalysis::jetHists("pfJets_matched",           fs, "");


//  if(isMC){
//    hPfJets_matched_B  = new nTupleAnalysis::jetHists("pfJets_matched_B",           fs, "");
//    hPfJets_matched_L  = new nTupleAnalysis::jetHists("pfJets_matched_L",           fs, "");
//  }


  //
  //  Configure Selection
  // 
  OfflineDeepCSVTightCut  = OfflineDeepCSVTightCut2017  ;
  OfflineDeepCSVMediumCut = OfflineDeepCSVMediumCut2017 ;
  OfflineDeepCSVLooseCut  = OfflineDeepCSVLooseCut2017  ;
  OnlineCSVCut            = OnlineCSVCut2017;
  OnlineDeepCSVCut        = OnlineDeepCSVCut2017;
  if(_year == "2018"){
    OfflineDeepCSVTightCut  = OfflineDeepCSVTightCut2018  ;
    OfflineDeepCSVMediumCut = OfflineDeepCSVMediumCut2018 ;
    OfflineDeepCSVLooseCut  = OfflineDeepCSVLooseCut2018 ;
    OnlineCSVCut            = OnlineCSVCut2018;
    OnlineDeepCSVCut        = OnlineDeepCSVCut2018;
  }



  //  if(histogramming >= 4) allEvents     = new eventHists("allEvents",     fs);
  //  if(histogramming >= 3) passPreSel    = new   tagHists("passPreSel",    fs, true, isMC, blind);
  //  if(histogramming >= 2) passDijetMass = new   tagHists("passDijetMass", fs, true, isMC, blind);
  //  if(histogramming >= 1) passMDRs      = new   tagHists("passMDRs",      fs, true, isMC, blind);
  //  //if(histogramming > 1        ) passMDCs     = new   tagHists("passMDCs",   fs, true, isMC, blind);
  //  //if(histogramming > 0        ) passDEtaBB   = new   tagHists("passDEtaBB", fs, true, isMC, blind);
} 


void TrigTurnOnStudy::monitor(long int e){
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

int TrigTurnOnStudy::eventLoop(int maxEvents){
  //Set Number of events to process. Take manual maxEvents if maxEvents is > 0 and less than the total number of events in the input files. 
  nEvents = (maxEvents > 0 && maxEvents < treeEvents) ? maxEvents : treeEvents;
  
  std::cout << "\nProcess " << nEvents << " of " << treeEvents << " events.\n";

  start = std::clock();//2546000 //2546043
  lastTime = std::clock();
  lastEvent = 0;
  for(long int e = 0; e < nEvents; e++){

    event->update(e);    
    processEvent();
    if(debug) event->dump();

    //periodically update status
    //if( (e+1)%1 == 0 || e+1==nEvents || debug) 
    if( (e+1)%10000 == 0 || e+1==nEvents || debug) 
      monitor(e);

  }
  
  std::cout << std::endl;
  std::cout << "TrigTurnOnStudy::End of Event Loop" << std::endl;
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

int TrigTurnOnStudy::processEvent(){
  if(debug) std::cout << "processEvent start" << std::endl;
  float weight = 1.0;

  cutflow->Fill("all", weight);
  if(event->run != event->runAOD)
    return 0;

  if(event->event != event->eventAOD)
    return 0;
  if(debug) std::cout << "Found Match " << std::endl;
  cutflow->Fill("foundMatch", weight);

  //
  //  HT
  //
  float trigHt = 0;
  float trigHt30 = 0;
  for(const nTupleAnalysis::jetPtr& pfJet : event->pfJets){
    trigHt += pfJet->pt;
    if(fabs(pfJet->eta) < 2.5){
      if(pfJet->pt > 30){
	trigHt30 += pfJet->pt;
      }
    }
  }

  float offHt = 0;
  float offHt30 = 0;
  for(const nTupleAnalysis::jetPtr& offJet : event->offJets){
    hAllOffJets->Fill(offJet,weight);
    offHt += offJet->pt;
    if(fabs(offJet->eta) < 2.5){
      if(offJet->pt > 30){
	offHt30 += offJet->pt;
      }
    }
  }
  if(debug) std::cout << "Got HT " << std::endl;


  //
  // Fill All events
  //
  for(const nTupleAnalysis::jetPtr& offJet : event->offJets){
    if(fabs(offJet->eta) > 2.4) continue;
    if(offJet->pt       < 20)   continue;
    if(nTupleAnalysis::failOverlap(offJet->p,event->muons,0.4)) continue;
    if(nTupleAnalysis::failOverlap(offJet->p,event->elecs,0.4)) continue;

    // Match offline to online
    float dR = 1e6;
    float dR_2nd = 1e6;
    nTupleAnalysis::jetPtr matchedJet = nullptr;

    for(const nTupleAnalysis::jetPtr& pfJet : event->pfJets){
      float this_dR = pfJet->p.DeltaR(offJet->p);
      if (this_dR < dR){
	dR_2nd = dR;
	dR = this_dR;
	matchedJet = pfJet;
      }else if(this_dR < dR_2nd){
	dR_2nd = this_dR;
      }
      
      
    }

    // 
    //  Have PF Match
    //
    if( dR < 0.1){
      
      hdR_all->Fill(dR);
      hdR_2nd_all->Fill(dR_2nd);
      if(matchedJet->pt > 60 && offJet->pt < 30){
	hdR_misMatchPt->Fill(dR);
	hdR_2nd_misMatchPt->Fill(dR_2nd);
      }
      //cout << matchedJet->pt << " vs " << offJet->pt  << " dR is " << dR  << endl;

      for(float pt : trigThresolds){
	if(matchedJet->pt > pt){
	  turnOnsAll[pt]->Fill(matchedJet->pt, offJet->pt, weight);

	  if(isMC){
	    if(offJet->hadronFlavour == 5){
	      turnOnsAll_B[pt]->Fill(matchedJet->pt, offJet->pt, weight);
	    }else if(offJet->hadronFlavour == 0){
	      turnOnsAll_L[pt]->Fill(matchedJet->pt, offJet->pt, weight);
	    }
	  }

	}
      }


    }//offJet has match

  }//offJets


  for(float ht : htThresolds){
    if(trigHt30 > ht){
      hTTurnOnsAll[ht]->Fill(trigHt30, trigHt, offHt30, offHt, weight);
    }
  }
  
  if(debug) std::cout << "Filled All Events " << std::endl;

  //
  // Event Selection
  //


  hAllMuons->nMuons->Fill(event->muons.size());
  for(auto muon: event->muons)
    hAllMuons->Fill(muon,weight);

  hAllElecs->nElecs->Fill(event->elecs.size());
  for(auto elec: event->elecs)
    hAllElecs->Fill(elec,weight);

  if(event->muons.size() == 1)
    cutflow->Fill("passMuonCut", weight);

  if(event->elecs.size() == 1)
    cutflow->Fill("passElecCut", weight);

  if(event->muons.size() != 1){
    if(debug) std::cout << "Fail Muon Cut" << std::endl;
    return 0;
  }

  if(event->elecs.size() != 1){
    if(debug) std::cout << "Fail Elec Cut" << std::endl;
    return 0;
  }
  cutflow->Fill("passLeptonCut", weight);

  if(debug) std::cout << "Pass Letpton Selection " << std::endl;

  //
  //  Offline BTags
  //
  unsigned int nOffJetsForCut = 0;
  unsigned int nOffJetsTaggedForCut = 0;
  //float totalsSFWeight = 1.0;
  for(const nTupleAnalysis::jetPtr& offJet : event->offJets){
    if(fabs(offJet->eta) > 2.4) continue;
    if(offJet->pt       < 30)   continue;

    if(nTupleAnalysis::failOverlap(offJet->p,event->elecs,0.4)) continue;
    if(nTupleAnalysis::failOverlap(offJet->p,event->muons,0.4)) continue;
    
    ++nOffJetsForCut;
    if(offJet->DeepCSV > OfflineDeepCSVTightCut) ++nOffJetsTaggedForCut;
    
    //if(isMC)
    //totalsSFWeight *= offJet.m_SF;
  }

  if(nOffJetsForCut < 2      ){
    if(debug) std::cout << "Fail NJet Cut" << std::endl;
    return 0;
  }
  cutflow->Fill("passNJetCut", weight);

  if(nOffJetsTaggedForCut < 1) {
    if(debug) std::cout << "Fail NBJet Cut" << std::endl;
    return 0;
  }
  cutflow->Fill("passNBJetCut", weight);
  //if(isMC)
  //eventWeight*= totalsSFWeight;

  if(debug) std::cout << "Pass Jet Cuts " << std::endl;

  hMuons->nMuons->Fill(event->muons.size());
  for(auto muon: event->muons)
    hMuons->Fill(muon,weight);

  hElecs->nElecs->Fill(event->elecs.size());
  for(auto elec: event->elecs)
    hElecs->Fill(elec,weight);


  //
  // Fill All events
  //
  //eventHists.Fill(eventData);

  //
  //
  //
  unsigned int nOffJetsPreOLap      = 0;
  unsigned int nOffJets             = 0;
  unsigned int nOffJets_matched     = 0;

  for(const nTupleAnalysis::jetPtr& offJet : event->offJets){
    cutflowJets->Fill("all", weight);    

    if(fabs(offJet->eta) > 2.4) continue;
    cutflowJets->Fill("eta", weight);    

    if(offJet->pt       < 20)   continue;
    cutflowJets->Fill("pt", weight);    

    ++nOffJetsPreOLap;
    hOffJetsPreOLap->Fill(offJet, weight);


    if(nTupleAnalysis::failOverlap(offJet->p,event->muons,0.4)) continue;
    cutflowJets->Fill("muonOlap", weight);    

    if(nTupleAnalysis::failOverlap(offJet->p,event->elecs,0.4)) continue;
    cutflowJets->Fill("elecOlap", weight);    

    //
    // Check if jet is a Probe
    //
    unsigned int nOtherTags = 0;
    //const JetData* tagJet = nullptr;
    for(const nTupleAnalysis::jetPtr& offJetOther : event->offJets){
      if(offJetOther == offJet) continue;
      if(offJetOther->DeepCSV       < OfflineDeepCSVTightCut)   continue;	

      if(offJetOther->pt       < 30)   continue;	
      if(fabs(offJetOther->eta) > 2.4) continue;
      if(nTupleAnalysis::failOverlap(offJetOther->p,event->elecs,0.4)) continue;
      if(nTupleAnalysis::failOverlap(offJetOther->p,event->muons,0.4)) continue;

      ++nOtherTags;
      //tagJet = &offJetOther;
    }
    
    // Require that there only be one other probe
    //    Note: this will suppress LF
    if(nOtherTags != 1) continue;
    cutflowJets->Fill("isProbe", weight);    

    //
    //  Offline Jets
    //
    ++nOffJets;
    hOffJets->Fill(offJet,weight);


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
    if( dR < 0.1){
      
      cutflowJets->Fill("hasHLTMatchPF", weight);    
      
      ++nOffJets_matched;
      offJet->matchedJet = matchedJet;
      hOffJets_matched  ->  Fill(offJet,weight);
      hOffJets_matchedJet->  Fill(matchedJet,weight);

      for(float pt : trigThresolds){
	if(matchedJet->pt > pt){
	  turnOns[pt]->Fill(matchedJet->pt, offJet->pt, weight);

	  if(isMC){
	    if(offJet->hadronFlavour == 5){
	      turnOns_B[pt]->Fill(matchedJet->pt, offJet->pt, weight);
	    }else if(offJet->hadronFlavour == 0){
	      turnOns_L[pt]->Fill(matchedJet->pt, offJet->pt, weight);
	    }
	  }

	}
      }


    }//offJet has match

  }//offJets

  for(float ht : htThresolds){
    if(trigHt30 > ht){
      hTTurnOns[ht]->Fill(trigHt30, trigHt, offHt30, offHt, weight);
    }
  }



  hOffJetsPreOLap    ->nJets->Fill(nOffJetsPreOLap ,weight);
  hOffJets           ->nJets->Fill(nOffJets        ,weight);
  hOffJets_matched   ->nJets->Fill(nOffJets_matched,weight);

//  hOffJets_matchedCalo->nJets->Fill(nOffJets_matchedCalo,weight);
//  hOffJets_matchedCaloJet->nJets->Fill(nOffJets_matchedCalo,weight);


  
 
    

  
 

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

bool TrigTurnOnStudy::passLumiMask(){
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



TrigTurnOnStudy::~TrigTurnOnStudy(){
  std::cout << "TrigTurnOnStudy::destroyed" << std::endl;
} 


