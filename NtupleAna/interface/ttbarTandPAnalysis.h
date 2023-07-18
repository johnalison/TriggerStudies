// -*- C++ -*-
#if !defined(ttbarTandPAnalysis_H)
#define ttbarTandPAnalysis_H

#include <ctime>
#include <sys/resource.h>
#include <sstream>      // std::stringstream

#include <TChain.h>
#include <TTree.h>
#include <TSpline.h>
#include "DataFormats/FWLite/interface/InputSource.h" //for edm::LuminosityBlockRange
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "TriggerStudies/NtupleAna/interface/eventData.h"
#include "nTupleAnalysis/baseClasses/interface/cutflowHists.h"
#include "nTupleAnalysis/baseClasses/interface/muonHists.h"
#include "nTupleAnalysis/baseClasses/interface/elecHists.h"
#include "nTupleAnalysis/baseClasses/interface/jetHists.h"
#include "nTupleAnalysis/baseClasses/interface/trackHists.h"
#include "nTupleAnalysis/baseClasses/interface/eventHists.h"
#include "nTupleAnalysis/baseClasses/interface/vertexHists.h"
#include "nTupleAnalysis/baseClasses/interface/pileUpWeightTool.h"


namespace TriggerStudies {

  class ttbarTandPAnalysis {
  public:

    bool doTree2 = true;
    std::string jet1HistName = "off";
    std::string jet2HistName = "pf";
    std::string tree1HistName = "off";
    std::string tree2HistName = "hlt";

    bool debug = false;
    float minJetPt = 30;
    std::string year;
    bool isMC  = false;
    TFileDirectory dir;

    float OfflineDeepFlavourMediumCut2018  = 0.2770;

    bool doEMuTandP = false;
    bool doMuTandP = false;

    int treeEvents;
    eventData* event;

    struct ttbarTandPHists { 

      float OfflineDeepFlavourMediumCut2018  = 0.2770;

      nTupleAnalysis::eventHists* hEvents = nullptr;

      nTupleAnalysis::muonHists* hAllMuons = nullptr;
      nTupleAnalysis::muonHists* hSelMuons = nullptr;

      nTupleAnalysis::elecHists* hAllElecs = nullptr;
      nTupleAnalysis::elecHists* hSelElecs = nullptr;

      nTupleAnalysis::jetHists*  hAllJets1     = nullptr;
      nTupleAnalysis::jetHists*  hProbeJets1   = nullptr;
      nTupleAnalysis::jetHists*  hMedTagJets1  = nullptr;

      ttbarTandPHists(std::string name, fwlite::TFileService& fs, std::string jetDetailString, bool doElecs=true){

	hEvents   = new nTupleAnalysis::eventHists(name+"/Events", fs);

	hAllMuons = new nTupleAnalysis::muonHists(name+"/AllMuons", fs, "All Muons");
	hSelMuons = new nTupleAnalysis::muonHists(name+"/SelMuons", fs, "Sel Muons");

	if(doElecs){
	  hAllElecs = new nTupleAnalysis::elecHists(name+"/AllElecs", fs, "All Elecs");
	  hSelElecs = new nTupleAnalysis::elecHists(name+"/SelElecs", fs, "Sel Elecs");
	}

	hAllJets1    = new nTupleAnalysis::jetHists(name+"/AllJets",   fs, "", jetDetailString);
	hProbeJets1  = new nTupleAnalysis::jetHists(name+"/ProbeJets", fs, "", jetDetailString);
	hMedTagJets1 = new nTupleAnalysis::jetHists(name+"/MedTagJets",fs, "", jetDetailString);
	

      };
      
      void Fill(const eventData* event, float weight){
	
	hEvents->Fill(*event->eventDataTree1, weight);

	for(const nTupleAnalysis::muonPtr& muon: event->muons){
	  hAllMuons->Fill(muon,weight);
	}
	hAllMuons->nMuons->Fill(event->muons.size(), weight);

	for(const nTupleAnalysis::muonPtr& muon: event->selMuons){
	  hSelMuons->Fill(muon,weight);
	}
	hSelMuons->nMuons->Fill(event->selMuons.size(), weight);

	if(hAllElecs){
	  for(const nTupleAnalysis::elecPtr& elec: event->elecs){
	    hAllElecs->Fill(elec,weight);
	  }
	  hAllElecs->nElecs->Fill(event->elecs.size(),weight);

	  for(const nTupleAnalysis::elecPtr& elec: event->selElecs){
	    hSelElecs->Fill(elec,weight);
	  }
	  hSelElecs->nElecs->Fill(event->selElecs.size(),weight);
	}

	//
	// jets
	//
	unsigned int nProbeJets1             = 0;
	unsigned int nMedTagJets1            = 0;
	for(const nTupleAnalysis::jetPtr& jet1 : event->selJets1){
	  hAllJets1->Fill(jet1,weight);
	  if(hAllJets1->vsLB) hAllJets1->vsLB->Fill(event->eventDataTree1->luminosityBlock,weight);	    
	  
	  bool isProbe = false;
	  for(const nTupleAnalysis::jetPtr& other_jet1 : event->selJets1){
	    if(other_jet1 == jet1) continue;
	    if(other_jet1->deepFlavB  < OfflineDeepFlavourMediumCut2018)   continue;
	    if(other_jet1->p.DeltaR(jet1->p) < 0.4) continue;
	    isProbe = true;
	  }

	  if(isProbe){
	    ++nProbeJets1;
	    hProbeJets1->Fill(jet1,weight);	    
	    if(hProbeJets1->vsLB) hProbeJets1->vsLB->Fill(event->eventDataTree1->luminosityBlock,weight);	    

	    if(jet1->deepFlavB  > OfflineDeepFlavourMediumCut2018){
	      ++nMedTagJets1;
	      hMedTagJets1->Fill(jet1,weight);	    
	      if(hMedTagJets1->vsLB) hMedTagJets1->vsLB->Fill(event->eventDataTree1->luminosityBlock,weight);	    
	    }
	  }//isProbe
	  
	}
	hAllJets1  ->nJets->Fill(event->selJets1.size(),weight);
	hProbeJets1->nJets->Fill(nProbeJets1,weight);
	hMedTagJets1->nJets->Fill(nMedTagJets1,weight);
	
      };

    };

    ttbarTandPHists* allEvents  = nullptr;    
    ttbarTandPHists* emuTandP   = nullptr;
    ttbarTandPHists* emuTandP2J = nullptr;
    ttbarTandPHists* muTandP    = nullptr;

    nTupleAnalysis::cutflowHists* cutflow = nullptr;
    nTupleAnalysis::cutflowHists* cutflowJets = nullptr;

//    // 
//    // jet1 Jets
//    //
//    nTupleAnalysis::jetHists* hSelJets1      = nullptr;
//    nTupleAnalysis::jetHists* hJets1PreOLap  = nullptr;

//
//    nTupleAnalysis::jetHists* hJets2 = nullptr;
//    nTupleAnalysis::jetHists* hJets2_matched = nullptr;
//
//
//    //
//    // BTags
//    //
//    nTupleAnalysis::btaggingHists* hJets1BTagsAll = nullptr;
//
//    nTupleAnalysis::vertexHists* hTree2Vtx = nullptr;
//    nTupleAnalysis::vertexHists* hTree1Vtx = nullptr;
//
//    nTupleAnalysis::vertexHists* hTree2Vtx_PVMatch = nullptr;
//    nTupleAnalysis::vertexHists* hTree1Vtx_PVMatch = nullptr;
//
//    nTupleAnalysis::trackHists* hAllTracks           = nullptr;
//
//    float OfflineDeepCSVTightCut  = -99;
//    float OfflineDeepCSVMediumCut = -99;
//    float OfflineDeepCSVLooseCut  = -99;
//    float OfflineDeepFlavourMediumCut = -99;
//    float OnlineCSVCut            = -99;
//    float OnlineDeepCSVCut        = -99;


    long int nEvents = 0;
    std::vector<edm::LuminosityBlockRange> lumiMask;
    UInt_t prevLumiBlock = 0;
    UInt_t firstRun      = 1e9;
    UInt_t lastRun       = 0;
    UInt_t prevRun       = 0;
    UInt_t nruns = 0;
    UInt_t nls   = 0;

    //Monitoring Variables
    long int percent;
    std::clock_t start;
    std::clock_t lastTime;
    double duration;
    double timeStep;
    double eventRateAVE;
    double eventRate;
    long int    eventStep;
    long int    lastEvent;
    double timeRemaining;
    int minutes;
    int seconds;
    int who = RUSAGE_SELF;
    struct rusage usage;
    long int usageMB;


    ttbarTandPAnalysis();
    void monitor(long int);
    int eventLoop(int, int nSkipEvents = 0);
    int processEvent();
    bool passLumiMask();
    std::map<edm::LuminosityBlockID, float> lumiData;
    void getLumiData(std::string);
    ~ttbarTandPAnalysis();
    void init(TChain* eventsTree1, TChain* eventsTree2, fwlite::TFileService& fs, std::string pfJetName, std::string jetDetailString);


  };

}
#endif // ttbarTandPAnalysis_H
