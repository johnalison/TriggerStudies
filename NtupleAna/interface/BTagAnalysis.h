// -*- C++ -*-
#if !defined(BTagAnalysis_H)
#define BTagAnalysis_H

#include <ctime>
#include <sys/resource.h>
#include <sstream>      // std::stringstream

#include <TChain.h>
#include <TTree.h>
#include <TSpline.h>
#include "DataFormats/FWLite/interface/InputSource.h" //for edm::LuminosityBlockRange
#include "nTupleAnalysis/baseClasses/interface/brilCSV.h"
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

#include "TriggerStudies/NtupleAna/interface/NeuralNetworkAndConstants.h"

namespace TriggerStudies {

  class BTagAnalysis {
  public:

    TChain* eventsAOD;
    TChain* eventsRAW;

    bool debug = false;
    std::string year;
    bool isMC  = false;
    TFileDirectory dir;

    bool doTracks = true;
    bool doCaloJets = true;
    bool doPuppiJets = true;
    bool doLeptonSel = false;
    bool doOfflineBTagCut = false;

    int histogramming = 1e6;
    int treeEvents;
    eventData* event;


    struct etaRangeHists { 

      std::vector<nTupleAnalysis::jetHists*> etaHists;
      std::vector<float> absEtaCuts;

      etaRangeHists(std::string jetName, std::vector<float> absEtaUpperLimits, fwlite::TFileService& fs, std::string jetDetailString ){
	
	absEtaCuts = absEtaUpperLimits;

	// Always make a first bin
	std::stringstream ss; 
	ss << 1;
	etaHists.push_back(new nTupleAnalysis::jetHists(jetName+"_eta"+ss.str(),       fs, "", jetDetailString));

	// Make a bin for each upper limit
	for(unsigned int iEta = 0; iEta < absEtaUpperLimits.size(); ++iEta){
	  ss.str(std::string());
	  ss << (iEta + 2);
	  etaHists.push_back(new nTupleAnalysis::jetHists(jetName+"_eta"+ss.str(),       fs, "", jetDetailString));
	}


      };

      void Fill(const nTupleAnalysis::jetPtr& jet, float etaForBinning, float weight){
	
	for(unsigned int iEta = 0; iEta < etaHists.size(); ++iEta){
	  
	  if(iEta < absEtaCuts.size()){
	    if(abs(etaForBinning) < absEtaCuts.at(iEta)){
	      etaHists.at(iEta)->Fill(jet,weight);	 
	      break;
	    }
	  }else{
	    etaHists.at(iEta)->Fill(jet,weight);	    
	    break;
	  }

	}

	
      };

    };



    struct jetHistsTruthMatched { 

      nTupleAnalysis::jetHists*  matched_B      = nullptr;
      nTupleAnalysis::jetHists*  matched_C      = nullptr;
      nTupleAnalysis::jetHists*  matched_LandPU = nullptr;
      nTupleAnalysis::jetHists*  matched_L      = nullptr;

      etaRangeHists*  matched_B_eta      = nullptr;
      etaRangeHists*  matched_C_eta      = nullptr;
      etaRangeHists*  matched_LandPU_eta = nullptr;
      etaRangeHists*  matched_L_eta      = nullptr;
      

      jetHistsTruthMatched(std::string jetName, fwlite::TFileService& fs, std::string jetDetailString, std::vector<float> absEtaUpperLimits = {}){
	matched_B        = new nTupleAnalysis::jetHists(jetName+"_B",       fs, "", jetDetailString );
	matched_C        = new nTupleAnalysis::jetHists(jetName+"_C",       fs, "", jetDetailString );
	matched_L        = new nTupleAnalysis::jetHists(jetName+"_L",       fs, "", jetDetailString );
	matched_LandPU   = new nTupleAnalysis::jetHists(jetName+"_LandPU",  fs, "", jetDetailString );
	
	if(absEtaUpperLimits.size()){
	  matched_B_eta        = new etaRangeHists(jetName+"_B",      absEtaUpperLimits,  fs, jetDetailString );
	  matched_C_eta        = new etaRangeHists(jetName+"_C",      absEtaUpperLimits,  fs, jetDetailString );
	  matched_L_eta        = new etaRangeHists(jetName+"_L",      absEtaUpperLimits,  fs, jetDetailString );
	  matched_LandPU_eta   = new etaRangeHists(jetName+"_LandPU", absEtaUpperLimits,  fs, jetDetailString );
	}

      };

      void Fill(const nTupleAnalysis::jetPtr& jet, int hadronFlavour, int flavourCleaned,  float weight, float etaForBinning=-1){

	if(hadronFlavour == 5){
	  matched_B->Fill(jet, weight);
	  if(matched_B_eta) matched_B_eta->Fill(jet, etaForBinning, weight);
	}else if(hadronFlavour == 4){
	  matched_C->Fill(jet, weight);
	  if(matched_C_eta) matched_C_eta->Fill(jet, etaForBinning, weight);
	}else if(hadronFlavour == 0){
	  matched_LandPU->Fill(jet, weight);
	  if(matched_LandPU_eta) matched_LandPU_eta->Fill(jet, etaForBinning, weight);
	  if(flavourCleaned!=0){
	    matched_L->Fill(jet, weight);
	    if(matched_L_eta) matched_L_eta->Fill(jet, etaForBinning, weight);
	  }
	}
	
      };

    };

    //
    //  jetAnalysisHists
    //
    struct jetAnalysisHists { 
      
      TH1F*   hmttOff          = nullptr;
      TH1F*   hmttOff_isFromV0 = nullptr;

      TH1F*   hmttHLT          = nullptr;
      TH1F*   hmttHLT_isFromV0 = nullptr;

      nTupleAnalysis::trackHists* hOffTracks           = nullptr;
      nTupleAnalysis::trackHists* hOffTracks_unmatched = nullptr;
      nTupleAnalysis::trackHists* hOffTracks_matched   = nullptr;
      nTupleAnalysis::trackHists* hOffTracks_noV0 = nullptr;
      nTupleAnalysis::trackHists* hOffTracks_matched_noV0 = nullptr;

      nTupleAnalysis::trackHists* hHltTracks = nullptr;
      nTupleAnalysis::trackHists* hHltTracks_matched = nullptr;
      nTupleAnalysis::trackHists* hHltTracks_unmatched = nullptr;
      nTupleAnalysis::trackHists* hHltTracks_noV0 = nullptr;

      nTupleAnalysis::btaggingHists* hOffBTags = nullptr;
      nTupleAnalysis::btaggingHists* hOffBTags_matched = nullptr;
      nTupleAnalysis::btaggingHists* hOffBTags_unmatched = nullptr;
      nTupleAnalysis::btaggingHists* hOffBTags_noV0 = nullptr;
      nTupleAnalysis::btaggingHists* hOffBTags_matched_noV0 = nullptr;

      nTupleAnalysis::btaggingHists* hHltBTags = nullptr;
      nTupleAnalysis::btaggingHists* hHltBTags_matched = nullptr;
      nTupleAnalysis::btaggingHists* hHltBTags_unmatched = nullptr;

      nTupleAnalysis::jetHists* hOffJets_matched = nullptr;
      etaRangeHists* hOffJets_matched_eta = nullptr;

      nTupleAnalysis::jetHists* hOffJets_matchedJet = nullptr;
      etaRangeHists* hOffJets_matchedJet_eta = nullptr;

      jetHistsTruthMatched* hOffJets_matched_Truth = nullptr;
      jetHistsTruthMatched* hOffJets_matchedJet_Truth = nullptr;

      nTupleAnalysis::jetHists*    hOffJetTightDeepCSV_matchedHLTJet        = nullptr;
      nTupleAnalysis::jetHists*    hOffJetMediumDeepCSV_matchedHLTJet       = nullptr;
      nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedHLTJet       = nullptr;
      nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedHLTCSV       = nullptr;
      nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedHLTDeepCSV   = nullptr;
      nTupleAnalysis::jetHists*    hOffJetLooseDeepCSV_matchedHLTJet        = nullptr;
      nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedHLTJet       = nullptr;
      nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedHLTDeepCSV   = nullptr;
      nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedHLTCSV       = nullptr;

      nTupleAnalysis::jetHists*    hOffJet_matchedHLTcsvTag          = nullptr;
      nTupleAnalysis::jetHists*    hOffJet_matchedHLTcsvTagJet       = nullptr;
      nTupleAnalysis::jetHists*    hOffJet_matchedHLTDeepcsvTag      = nullptr;
      nTupleAnalysis::jetHists*    hOffJet_matchedHLTDeepcsvTagJet   = nullptr;


      jetAnalysisHists(std::string offName, std::string HLTName, std::string HLTMatchName, fwlite::TFileService& fs, std::string jetDetailString, bool isMC){

	//hmttOff           = dir.make<TH1F>("mtt_"+offName,               "BTagAnalysis/mtt_off;             mtt;   Entries", 100,-0.01, 2);
	//hmttOff_isFromV0  = dir.make<TH1F>("mtt_"+offName+"_isFromV0",   "BTagAnalysis/mtt_off_isFromV0;    mtt;   Entries", 100,-0.01, 2);
	//hmttPf            = dir.make<TH1F>("mtt_pf",             "BTagAnalysis/mtt_pf;              mtt;   Entries", 100,-0.01, 2);
	//hmttPf_isFromV0   = dir.make<TH1F>("mtt_pf_isFromV0",    "BTagAnalysis/mtt_pf_isFromV0;     mtt;   Entries", 100,-0.01, 2);


	bool doTracks = jetDetailString.find("Tracks") != std::string::npos;
	if(doTracks){
	  hOffTracks           = new nTupleAnalysis::trackHists(offName+"Tracks",          fs, "");
	  hOffTracks_unmatched = new nTupleAnalysis::trackHists(offName+"Tracks_unmatched",fs, "");
	  hOffTracks_matched   = new nTupleAnalysis::trackHists(offName+"Tracks_matched",  fs, "");

	  hHltTracks            = new nTupleAnalysis::trackHists(HLTName+"Tracks",          fs, "");
	  hHltTracks_matched    = new nTupleAnalysis::trackHists(HLTName+"Tracks_matched",  fs, "");
	  hHltTracks_unmatched  = new nTupleAnalysis::trackHists(HLTName+"Tracks_unmatched",fs, "");

	  if(jetDetailString.find("noV0") != std::string::npos) {
	    hOffTracks_noV0           = new nTupleAnalysis::trackHists(offName+"Tracks_noV0",        fs, "");
	    hOffTracks_matched_noV0   = new nTupleAnalysis::trackHists(offName+"Tracks_matched_noV0",fs, "");
	  
	    hHltTracks_noV0            = new nTupleAnalysis::trackHists(HLTName+"Tracks_noV0",fs, "");
	  }
	}

	hOffBTags           = new nTupleAnalysis::btaggingHists(offName+"BTags",          fs, "");
	hOffBTags_matched   = new nTupleAnalysis::btaggingHists(offName+"BTags_matched",  fs, "");
	hOffBTags_unmatched = new nTupleAnalysis::btaggingHists(offName+"BTags_unmatched",fs, "");


	if(jetDetailString.find("noV0") != std::string::npos) {
	  hOffBTags_noV0            = new nTupleAnalysis::btaggingHists(offName+"BTags_noV0",        fs, "");
	  hOffBTags_matched_noV0    = new nTupleAnalysis::btaggingHists(offName+"BTags_matched_noV0",fs, "");
	}


	hHltBTags           = new nTupleAnalysis::btaggingHists(HLTName+"BTags",           fs, "");
	hHltBTags_matched   = new nTupleAnalysis::btaggingHists(HLTName+"BTags_matched",   fs, "");
	hHltBTags_unmatched = new nTupleAnalysis::btaggingHists(HLTName+"BTags_unmatched", fs, "");

	hOffJets_matched        = new nTupleAnalysis::jetHists(offName+"Jets_matched",       fs, "", jetDetailString);
	hOffJets_matchedJet     = new nTupleAnalysis::jetHists(offName+"Jets_matchedJet",    fs, "", jetDetailString);

	bool doEtaRegions = jetDetailString.find("EtaRegions") != std::string::npos;
	std::vector<float> etaBins = {1.5,3.0};

	if(!doEtaRegions) 
	  etaBins.clear();
  
	if(doEtaRegions){
	  std::cout << " \t loading Eta Regions " << std::endl;
	  hOffJets_matched_eta    = new etaRangeHists(offName+"Jets_matched",      etaBins,   fs, jetDetailString);
	  hOffJets_matchedJet_eta = new etaRangeHists(offName+"Jets_matchedJet",   etaBins,   fs, jetDetailString);
	}


	if(isMC){
	  hOffJets_matched_Truth    = new jetHistsTruthMatched(offName+"Jets_matched",    fs, jetDetailString, etaBins);
	  hOffJets_matchedJet_Truth = new jetHistsTruthMatched(offName+"Jets_matchedJet", fs, jetDetailString, etaBins);
	}


	hOffJet_matchedHLTcsvTag         = new nTupleAnalysis::jetHists(offName+"Jets_matched"+HLTMatchName+"csvTag",         fs, "");
	hOffJet_matchedHLTcsvTagJet      = new nTupleAnalysis::jetHists(offName+"Jets_matched"+HLTMatchName+"csvTagJet",      fs, "");
	hOffJet_matchedHLTDeepcsvTag     = new nTupleAnalysis::jetHists(offName+"Jets_matched"+HLTMatchName+"DeepcsvTag",     fs, "");
	hOffJet_matchedHLTDeepcsvTagJet  = new nTupleAnalysis::jetHists(offName+"Jets_matched"+HLTMatchName+"DeepcsvTagJet",  fs, "");

	hOffJetTightDeepCSV_matchedHLTJet       = new nTupleAnalysis::jetHists(offName+"JetsTight_matched"+HLTMatchName+"Jet",       fs, "");
	hOffJetMediumDeepCSV_matchedHLTJet      = new nTupleAnalysis::jetHists(offName+"JetsMedium_matched"+HLTMatchName+"Jet",      fs, "");
	hOffJetLooseDeepCSV_matchedHLTJet       = new nTupleAnalysis::jetHists(offName+"JetsLoose_matched"+HLTMatchName+"Jet",       fs, "");

	hOffJetMedDeepCSV_matchedHLTJet         = new nTupleAnalysis::jetHists(offName+"JetsMedDeepCSV_matched"+HLTMatchName+"Jet",       fs, "", "matchedBJet");
	hOffJetMedDeepCSV_matchedHLTDeepCSV  = new nTupleAnalysis::jetHists(offName+"JetsMedDeepCSV_matched"+HLTMatchName+"DeepCSV",      fs, "", "matchedBJet");
	hOffJetMedDeepCSV_matchedHLTCSV      = new nTupleAnalysis::jetHists(offName+"JetsMedDeepCSV_matched"+HLTMatchName+"CSV",          fs, "", "matchedBJet");

	hOffJetMedDeepFlav_matchedHLTJet      = new nTupleAnalysis::jetHists(offName+"JetsMedDeepFlav_matched"+HLTMatchName+"Jet",          fs, "", "matchedBJet");
	hOffJetMedDeepFlav_matchedHLTDeepCSV  = new nTupleAnalysis::jetHists(offName+"JetsMedDeepFlav_matched"+HLTMatchName+"DeepCSV",      fs, "", "matchedBJet");
	hOffJetMedDeepFlav_matchedHLTCSV      = new nTupleAnalysis::jetHists(offName+"JetsMedDeepFlav_matched"+HLTMatchName+"CSV",          fs, "", "matchedBJet");


      }

      void Fill(BTagAnalysis* bTagAna, const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight, bool isMC,
		float OfflineDeepCSVLooseCut, float OfflineDeepCSVMediumCut, float OfflineDeepCSVTightCut, 
		float OfflineDeepFlavourMediumCut,
		float OnlineCSVCut, float OnlineDeepCSVCut,
		bool debug=false);


    };
    
    jetAnalysisHists* PFJetHists;
    jetAnalysisHists* CaloJetHists;
    jetAnalysisHists* PuppiJetHists;


    nTupleAnalysis::eventHists* hEvents = nullptr;
    nTupleAnalysis::eventHists* hEventsNoPUWeight = nullptr;

    nTupleAnalysis::cutflowHists* cutflow = nullptr;
    nTupleAnalysis::cutflowHists* cutflowJets = nullptr;

    nTupleAnalysis::muonHists* hMuons = nullptr;
    nTupleAnalysis::muonHists* hAllMuons = nullptr;
    nTupleAnalysis::muonHists* hSelMuons = nullptr;

    nTupleAnalysis::elecHists* hElecs = nullptr;
    nTupleAnalysis::elecHists* hAllElecs = nullptr;
    nTupleAnalysis::elecHists* hSelElecs = nullptr;

    // 
    // Offline Jets
    //
    nTupleAnalysis::jetHists* hOffJetsPreOLap = nullptr;
    nTupleAnalysis::jetHists* hOffJets         = nullptr;

    nTupleAnalysis::jetHists* hPfJets = nullptr;
    nTupleAnalysis::jetHists* hPfJets_matched = nullptr;

    nTupleAnalysis::jetHists* hCaloJets = nullptr;
    nTupleAnalysis::jetHists* hCaloJets_matched = nullptr;

    nTupleAnalysis::jetHists* hPuppiJets = nullptr;
    nTupleAnalysis::jetHists* hPuppiJets_matched = nullptr;

    //
    // BTags
    //
    nTupleAnalysis::btaggingHists* hOffBTagsAll = nullptr;

    nTupleAnalysis::vertexHists* hVtx = nullptr;
    nTupleAnalysis::vertexHists* hOffVtx = nullptr;

    nTupleAnalysis::vertexHists* hVtx_PVMatch = nullptr;
    nTupleAnalysis::vertexHists* hOffVtx_PVMatch = nullptr;

    float OfflineDeepCSVTightCut  = -99;
    float OfflineDeepCSVMediumCut = -99;
    float OfflineDeepCSVLooseCut  = -99;
    float OfflineDeepFlavourMediumCut = -99;
    float OnlineCSVCut            = -99;
    float OnlineDeepCSVCut        = -99;

    TH1F*   hDeltaROffPf          ;

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

    std::shared_ptr<NeuralNetworkAndConstants>  neuralNet;


    BTagAnalysis(TChain* _eventsRAW, TChain* _eventsAOD, fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug, std::string PUFileName, std::string jetDetailString, const edm::ParameterSet& nnConfig, std::string pfJetName);
    void monitor(long int);
    int eventLoop(int, int nSkipEvents = 0);
    int processEvent();
    bool passLumiMask();
    std::map<edm::LuminosityBlockID, float> lumiData;
    void getLumiData(std::string);
    ~BTagAnalysis();

    void OfflineToOnlineTrackMatching(const nTupleAnalysis::jetPtr& offJet, const nTupleAnalysis::trackPtr& offTrk,
				      const nTupleAnalysis::jetPtr& hltJet,
				      float dRMatch);

    void OfflineToOnlineTrkTagMatching(const nTupleAnalysis::jetPtr& offJet, const nTupleAnalysis::trkTagVarPtr& offTrkTag,
				       const nTupleAnalysis::jetPtr& hltJet,
				       float dRMatch);

    void OfflineToOnlineSVMatching(const nTupleAnalysis::svPtr& offSV,
				   const nTupleAnalysis::jetPtr& hltJet,
				   float dRMatch);



    nTupleAnalysis::pileUpWeightTool* pileUpTool = nullptr;

  };

}
#endif // BTagAnalysis_H
