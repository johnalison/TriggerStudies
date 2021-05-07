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
    nTupleAnalysis::jetHists* hOffJets = nullptr;
    nTupleAnalysis::jetHists* hOffJets_matched = nullptr;
    etaRangeHists* hOffJets_matched_eta = nullptr;
    
    nTupleAnalysis::jetHists* hOffJets_matchedJet = nullptr;
    etaRangeHists* hOffJets_matchedJet_eta = nullptr;

    nTupleAnalysis::jetHists* hOffJets_matchedCalo = nullptr;
    nTupleAnalysis::jetHists* hOffJets_matchedCaloJet = nullptr;

    nTupleAnalysis::jetHists* hOffJetsPuppi = nullptr;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppi = nullptr;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppiJet = nullptr;
    etaRangeHists* hOffJets_matchedPuppi_eta = nullptr;
    etaRangeHists* hOffJets_matchedPuppiJet_eta = nullptr;


    //
    //  BTags Matching 
    //
    nTupleAnalysis::jetHists*    hOffJet_matchedPFcsvTag          = nullptr;
    nTupleAnalysis::jetHists*    hOffJet_matchedPFcsvTagJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJet_matchedPFDeepcsvTag      = nullptr;
    nTupleAnalysis::jetHists*    hOffJet_matchedPFDeepcsvTagJet   = nullptr;
    nTupleAnalysis::jetHists*    hOffJetTightDeepCSV_matchedPFJet        = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMediumDeepCSV_matchedPFJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPFJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPFDeepCSV   = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPFCSV       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetLooseDeepCSV_matchedPFJet        = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPFJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPFDeepCSV   = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPFCSV       = nullptr;


    nTupleAnalysis::jetHists*    hOffJet_matchedCalocsvTag          = nullptr;
    nTupleAnalysis::jetHists*    hOffJet_matchedCalocsvTagJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJet_matchedCaloDeepcsvTag      = nullptr;
    nTupleAnalysis::jetHists*    hOffJet_matchedCaloDeepcsvTagJet   = nullptr;
    nTupleAnalysis::jetHists*    hOffJetTightDeepCSV_matchedCaloJet        = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMediumDeepCSV_matchedCaloJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedCaloJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedCaloDeepCSV   = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedCaloCSV       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetLooseDeepCSV_matchedCaloJet        = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedCaloJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedCaloDeepCSV   = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedCaloCSV       = nullptr;


    nTupleAnalysis::jetHists*    hOffJet_matchedPuppicsvTag          = nullptr;
    nTupleAnalysis::jetHists*    hOffJet_matchedPuppicsvTagJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJet_matchedPuppiDeepcsvTag      = nullptr;
    nTupleAnalysis::jetHists*    hOffJet_matchedPuppiDeepcsvTagJet   = nullptr;
    nTupleAnalysis::jetHists*    hOffJetTightDeepCSV_matchedPuppiJet        = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMediumDeepCSV_matchedPuppiJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPuppiJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPuppiDeepCSV   = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPuppiCSV       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetLooseDeepCSV_matchedPuppiJet        = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPuppiJet       = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPuppiDeepCSV   = nullptr;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPuppiCSV       = nullptr;

    //
    // Truth Hists
    //
    jetHistsTruthMatched* hOffJets_matched_Truth = nullptr;
    jetHistsTruthMatched* hOffJets_matchedJet_Truth = nullptr;

    jetHistsTruthMatched* hOffJets_matchedCalo_Truth = nullptr;
    jetHistsTruthMatched* hOffJets_matchedCaloJet_Truth = nullptr;

    jetHistsTruthMatched* hOffJets_matchedPuppi_Truth = nullptr;
    jetHistsTruthMatched* hOffJets_matchedPuppiJet_Truth = nullptr;

    nTupleAnalysis::jetHists* hPfJets = nullptr;
    nTupleAnalysis::jetHists* hPfJets_matched = nullptr;

    nTupleAnalysis::jetHists* hCaloJets = nullptr;
    nTupleAnalysis::jetHists* hCaloJets_matched = nullptr;

    nTupleAnalysis::jetHists* hPuppiJets = nullptr;
    nTupleAnalysis::jetHists* hPuppiJets_matched = nullptr;

    //
    // Tracks
    //
    nTupleAnalysis::trackHists* hOffTracks = nullptr;
    nTupleAnalysis::trackHists* hOffTracks_unmatched = nullptr;
    nTupleAnalysis::trackHists* hOffTracks_matched = nullptr;

    nTupleAnalysis::trackHists* hOffTracksCalo = nullptr;
    nTupleAnalysis::trackHists* hOffTracksCalo_unmatched = nullptr;
    nTupleAnalysis::trackHists* hOffTracksCalo_matched = nullptr;

    nTupleAnalysis::trackHists* hOffTracksPuppi = nullptr;
    nTupleAnalysis::trackHists* hOffTracksPuppi_unmatched = nullptr;
    nTupleAnalysis::trackHists* hOffTracksPuppi_matched = nullptr;


    nTupleAnalysis::trackHists* hPfTracks = nullptr;
    nTupleAnalysis::trackHists* hPfTracks_matched = nullptr;
    nTupleAnalysis::trackHists* hPfTracks_unmatched = nullptr;
    nTupleAnalysis::trackHists* hPfTracks_noV0 = nullptr;

    nTupleAnalysis::trackHists* hCaloTracks = nullptr;
    nTupleAnalysis::trackHists* hCaloTracks_matched = nullptr;
    nTupleAnalysis::trackHists* hCaloTracks_unmatched = nullptr;
    nTupleAnalysis::trackHists* hCaloTracks_noV0 = nullptr;

    nTupleAnalysis::trackHists* hPuppiTracks = nullptr;
    nTupleAnalysis::trackHists* hPuppiTracks_matched = nullptr;
    nTupleAnalysis::trackHists* hPuppiTracks_unmatched = nullptr;
    nTupleAnalysis::trackHists* hPuppiTracks_noV0 = nullptr;


    nTupleAnalysis::trackHists* hOffTracks_noV0 = nullptr;
    nTupleAnalysis::trackHists* hOffTracks_matched_noV0 = nullptr;

    nTupleAnalysis::trackHists* hOffTracksCalo_noV0 = nullptr;
    nTupleAnalysis::trackHists* hOffTracksCalo_matched_noV0 = nullptr;

    nTupleAnalysis::trackHists* hOffTracksPuppi_noV0 = nullptr;
    nTupleAnalysis::trackHists* hOffTracksPuppi_matched_noV0 = nullptr;

    nTupleAnalysis::btaggingHists* hOffBTagsAll = nullptr;
    nTupleAnalysis::btaggingHists* hOffBTags = nullptr;
    nTupleAnalysis::btaggingHists* hOffBTags_matched = nullptr;
    nTupleAnalysis::btaggingHists* hOffBTags_unmatched = nullptr;
    nTupleAnalysis::btaggingHists* hOffBTags_noV0 = nullptr;
    nTupleAnalysis::btaggingHists* hOffBTags_matched_noV0 = nullptr;

    nTupleAnalysis::btaggingHists* hPfBTags = nullptr;
    nTupleAnalysis::btaggingHists* hPfBTags_matched = nullptr;
    nTupleAnalysis::btaggingHists* hPfBTags_unmatched = nullptr;

    nTupleAnalysis::btaggingHists* hPuppiBTags = nullptr;
    nTupleAnalysis::btaggingHists* hPuppiBTags_matched = nullptr;
    nTupleAnalysis::btaggingHists* hPuppiBTags_unmatched = nullptr;

    nTupleAnalysis::vertexHists* hVtx = nullptr;
    nTupleAnalysis::vertexHists* hOffVtx = nullptr;

    float OfflineDeepCSVTightCut  = -99;
    float OfflineDeepCSVMediumCut = -99;
    float OfflineDeepCSVLooseCut  = -99;
    float OfflineDeepFlavourMediumCut = -99;
    float OnlineCSVCut            = -99;
    float OnlineDeepCSVCut        = -99;


    TH1F*   hmttOff          ;
    TH1F*   hmttOff_isFromV0 ;
    TH1F*   hmttPf           ;
    TH1F*   hmttPf_isFromV0  ;
    TH1F*   hmttCalo           ;
    TH1F*   hmttCalo_isFromV0  ;
    TH1F*   hmttPuppi           ;
    TH1F*   hmttPuppi_isFromV0  ;


    TH1F*   hDeltaROffPf          ;

    //eventHists* allEvents   = NULL;
    //tagHists* passPreSel    = NULL;

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


    void PFJetAnalysis(const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight);
    void CaloJetAnalysis(const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight);
    void PuppiJetAnalysis(const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight);

    nTupleAnalysis::pileUpWeightTool* pileUpTool = nullptr;

  };

}
#endif // BTagAnalysis_H
