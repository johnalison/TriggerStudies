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

    bool doTree2 = true;
    std::string jet1HistName = "off";
    std::string jet2HistName = "pf";
    std::string tree1HistName = "off";
    std::string tree2HistName = "hlt";


    bool debug = false;
    float minJetPt = 30;
    float minJetAbsEta = -1;
    float maxJetAbsEta = 4;
    float minJetDeepJet = -10;
    std::string year;
    bool isMC  = false;
    TFileDirectory dir;

    bool doTracks = true;
    //bool doCaloJets = true;
    //bool doPuppiJets = true;
    bool doEMuTandP = false;

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

      nTupleAnalysis::trackHists* hJet1Tracks           = nullptr;
      nTupleAnalysis::trackHists* hJet1Tracks_unmatched = nullptr;
      nTupleAnalysis::trackHists* hJet1Tracks_matched   = nullptr;
      nTupleAnalysis::trackHists* hJet1Tracks_noV0 = nullptr;
      nTupleAnalysis::trackHists* hJet1Tracks_matched_noV0 = nullptr;

      nTupleAnalysis::trackHists* hJet2Tracks = nullptr;
      nTupleAnalysis::trackHists* hJet2Tracks_matched = nullptr;
      nTupleAnalysis::trackHists* hJet2Tracks_unmatched = nullptr;
      nTupleAnalysis::trackHists* hJet2Tracks_noV0 = nullptr;

      nTupleAnalysis::btaggingHists* hJet1BTags = nullptr;
      nTupleAnalysis::btaggingHists* hJet1BTags_matched = nullptr;
      nTupleAnalysis::btaggingHists* hJet1BTags_unmatched = nullptr;
      nTupleAnalysis::btaggingHists* hJet1BTags_noV0 = nullptr;
      nTupleAnalysis::btaggingHists* hJet1BTags_matched_noV0 = nullptr;

      nTupleAnalysis::btaggingHists* hJet2BTags = nullptr;
      nTupleAnalysis::btaggingHists* hJet2BTags_matched = nullptr;
      nTupleAnalysis::btaggingHists* hJet2BTags_unmatched = nullptr;

      nTupleAnalysis::jetHists* hJets1_matched = nullptr;
      etaRangeHists* hJets1_matched_eta = nullptr;

      nTupleAnalysis::jetHists* hJets1_matchedJet = nullptr;
      etaRangeHists* hJets1_matchedJet_eta = nullptr;

      jetHistsTruthMatched* hJets1_matched_Truth = nullptr;
      jetHistsTruthMatched* hJets1_matchedJet_Truth = nullptr;

      nTupleAnalysis::jetHists*    hJet1TightDeepCSV_matchedJet2Jet        = nullptr;
      nTupleAnalysis::jetHists*    hJet1MediumDeepCSV_matchedJet2Jet       = nullptr;
      nTupleAnalysis::jetHists*    hJet1LooseDeepCSV_matchedJet2Jet        = nullptr;

      nTupleAnalysis::jetHists*    hJet1MedDeepCSV_matchedJet2          = nullptr;
      nTupleAnalysis::jetHists*    hJet1MedDeepCSV_matchedJet2CSV       = nullptr;
      nTupleAnalysis::jetHists*    hJet1MedDeepCSV_matchedJet2DeepCSV   = nullptr;

      nTupleAnalysis::jetHists*    hJet1MedDeepFlav_matchedJet2          = nullptr;
      nTupleAnalysis::jetHists*    hJet1MedDeepFlav_matchedJet2DeepCSV   = nullptr;
      nTupleAnalysis::jetHists*    hJet1MedDeepFlav_matchedJet2CSV       = nullptr;

      nTupleAnalysis::jetHists*    hJet1_matchedJet2csvTag          = nullptr;
      nTupleAnalysis::jetHists*    hJet1_matchedJet2csvTagJet       = nullptr;
      nTupleAnalysis::jetHists*    hJet1_matchedJet2DeepcsvTag      = nullptr;
      nTupleAnalysis::jetHists*    hJet1_matchedJet2DeepcsvTagJet   = nullptr;


      jetAnalysisHists(std::string jet1Name, std::string jet2Name, fwlite::TFileService& fs, std::string jetDetailString, bool isMC, std::string suffix=""){

	//hmttOff           = dir.make<TH1F>("mtt_"+jet1Name,               "BTagAnalysis/mtt_off;             mtt;   Entries", 100,-0.01, 2);
	//hmttOff_isFromV0  = dir.make<TH1F>("mtt_"+jet1Name+"_isFromV0",   "BTagAnalysis/mtt_off_isFromV0;    mtt;   Entries", 100,-0.01, 2);
	//hmttPf            = dir.make<TH1F>("mtt_pf",             "BTagAnalysis/mtt_pf;              mtt;   Entries", 100,-0.01, 2);
	//hmttPf_isFromV0   = dir.make<TH1F>("mtt_pf_isFromV0",    "BTagAnalysis/mtt_pf_isFromV0;     mtt;   Entries", 100,-0.01, 2);


	bool doTracks = jetDetailString.find("Tracks") != std::string::npos;
	if(doTracks){
	  hJet1Tracks           = new nTupleAnalysis::trackHists(jet1Name+"Tracks"+suffix,          fs, "");
	  hJet1Tracks_unmatched = new nTupleAnalysis::trackHists(jet1Name+"Tracks_unmatched"+suffix,fs, "");
	  hJet1Tracks_matched   = new nTupleAnalysis::trackHists(jet1Name+"Tracks_matched"+suffix,  fs, "");

	  hJet2Tracks            = new nTupleAnalysis::trackHists(jet2Name+"Tracks"+suffix,          fs, "");
	  hJet2Tracks_matched    = new nTupleAnalysis::trackHists(jet2Name+"Tracks_matched"+suffix,  fs, "");
	  hJet2Tracks_unmatched  = new nTupleAnalysis::trackHists(jet2Name+"Tracks_unmatched"+suffix,fs, "");

	  if(jetDetailString.find("noV0") != std::string::npos) {
	    hJet1Tracks_noV0           = new nTupleAnalysis::trackHists(jet1Name+"Tracks_noV0"+suffix,        fs, "");
	    hJet1Tracks_matched_noV0   = new nTupleAnalysis::trackHists(jet1Name+"Tracks_matched_noV0"+suffix,fs, "");
	  
	    hJet2Tracks_noV0            = new nTupleAnalysis::trackHists(jet2Name+"Tracks_noV0"+suffix,fs, "");
	  }
	}

	hJet1BTags           = new nTupleAnalysis::btaggingHists(jet1Name+"BTags"+suffix,          fs, "");
	hJet1BTags_matched   = new nTupleAnalysis::btaggingHists(jet1Name+"BTags_matched"+suffix,  fs, "");
	hJet1BTags_unmatched = new nTupleAnalysis::btaggingHists(jet1Name+"BTags_unmatched"+suffix,fs, "");


	if(jetDetailString.find("noV0") != std::string::npos) {
	  hJet1BTags_noV0            = new nTupleAnalysis::btaggingHists(jet1Name+"BTags_noV0"+suffix,        fs, "");
	  hJet1BTags_matched_noV0    = new nTupleAnalysis::btaggingHists(jet1Name+"BTags_matched_noV0"+suffix,fs, "");
	}


	hJet2BTags           = new nTupleAnalysis::btaggingHists(jet2Name+"BTags"+suffix,           fs, "");
	hJet2BTags_matched   = new nTupleAnalysis::btaggingHists(jet2Name+"BTags_matched"+suffix,   fs, "");
	hJet2BTags_unmatched = new nTupleAnalysis::btaggingHists(jet2Name+"BTags_unmatched"+suffix, fs, "");

	hJets1_matched        = new nTupleAnalysis::jetHists(jet1Name+"Jets_matched"+suffix,       fs, "", jetDetailString);
	hJets1_matchedJet     = new nTupleAnalysis::jetHists(jet1Name+"Jets_matchedJet"+suffix,    fs, "", jetDetailString);

	bool doEtaRegions = jetDetailString.find("EtaRegions") != std::string::npos;
	std::vector<float> etaBins = {1.5,3.0};

	if(!doEtaRegions) 
	  etaBins.clear();
  
	if(doEtaRegions){
	  std::cout << " \t loading Eta Regions " << std::endl;
	  hJets1_matched_eta    = new etaRangeHists(jet1Name+"Jets_matched"+suffix,      etaBins,   fs, jetDetailString);
	  hJets1_matchedJet_eta = new etaRangeHists(jet1Name+"Jets_matchedJet"+suffix,   etaBins,   fs, jetDetailString);
	}


	if(isMC){
	  hJets1_matched_Truth    = new jetHistsTruthMatched(jet1Name+"Jets_matched"+suffix,    fs, jetDetailString, etaBins);
	  hJets1_matchedJet_Truth = new jetHistsTruthMatched(jet1Name+"Jets_matchedJet"+suffix, fs, jetDetailString, etaBins);
	}


	hJet1_matchedJet2csvTag         = new nTupleAnalysis::jetHists(jet1Name+"Jets_matched"+jet2Name+"csvTag"+suffix,         fs, "");
	hJet1_matchedJet2csvTagJet      = new nTupleAnalysis::jetHists(jet1Name+"Jets_matched"+jet2Name+"csvTagJet"+suffix,      fs, "");
	hJet1_matchedJet2DeepcsvTag     = new nTupleAnalysis::jetHists(jet1Name+"Jets_matched"+jet2Name+"DeepcsvTag"+suffix,     fs, "");
	hJet1_matchedJet2DeepcsvTagJet  = new nTupleAnalysis::jetHists(jet1Name+"Jets_matched"+jet2Name+"DeepcsvTagJet"+suffix,  fs, "");

	hJet1TightDeepCSV_matchedJet2Jet       = new nTupleAnalysis::jetHists(jet1Name+"JetsTight_matched"+jet2Name+"Jet"+suffix,       fs, "");
	hJet1MediumDeepCSV_matchedJet2Jet      = new nTupleAnalysis::jetHists(jet1Name+"JetsMedium_matched"+jet2Name+"Jet"+suffix,      fs, "");
	hJet1LooseDeepCSV_matchedJet2Jet       = new nTupleAnalysis::jetHists(jet1Name+"JetsLoose_matched"+jet2Name+"Jet"+suffix,       fs, "");

	hJet1MedDeepCSV_matchedJet2         = new nTupleAnalysis::jetHists(jet1Name+"JetsMedDeepCSV_matched"+jet2Name+"Jet"+suffix,       fs, "", "matchedBJet");
	hJet1MedDeepCSV_matchedJet2DeepCSV  = new nTupleAnalysis::jetHists(jet1Name+"JetsMedDeepCSV_matched"+jet2Name+"DeepCSV"+suffix,      fs, "", "matchedBJet");
	hJet1MedDeepCSV_matchedJet2CSV      = new nTupleAnalysis::jetHists(jet1Name+"JetsMedDeepCSV_matched"+jet2Name+"CSV"+suffix,          fs, "", "matchedBJet");

	hJet1MedDeepFlav_matchedJet2         = new nTupleAnalysis::jetHists(jet1Name+"JetsMedDeepFlav_matched"+jet2Name+"Jet"+suffix,          fs, "", "matchedBJet");
	hJet1MedDeepFlav_matchedJet2DeepCSV  = new nTupleAnalysis::jetHists(jet1Name+"JetsMedDeepFlav_matched"+jet2Name+"DeepCSV"+suffix,      fs, "", "matchedBJet");
	hJet1MedDeepFlav_matchedJet2CSV      = new nTupleAnalysis::jetHists(jet1Name+"JetsMedDeepFlav_matched"+jet2Name+"CSV"+suffix,          fs, "", "matchedBJet");


      }

      void Fill(BTagAnalysis* bTagAna, const nTupleAnalysis::jetPtr& jet1,const nTupleAnalysis::jetPtr& jet2, float weight, bool isMC,
		float OfflineDeepCSVLooseCut, float OfflineDeepCSVMediumCut, float OfflineDeepCSVTightCut, 
		float OfflineDeepFlavourMediumCut,
		float OnlineCSVCut, float OnlineDeepCSVCut,
		bool debug=false);


    };
    
    jetAnalysisHists* jetCompHists = nullptr;
    jetAnalysisHists* jetCompHists_PVMatch  = nullptr;

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
    // jet1 Jets
    //
    nTupleAnalysis::jetHists* hSelJets1      = nullptr;
    nTupleAnalysis::jetHists* hJets1PreOLap  = nullptr;
    nTupleAnalysis::jetHists* hJets1         = nullptr;
    jetHistsTruthMatched*     hJets1_Truth   = nullptr;

    nTupleAnalysis::jetHists* hJets2 = nullptr;
    nTupleAnalysis::jetHists* hJets2_matched = nullptr;
    jetHistsTruthMatched*     hJets2_Truth = nullptr;

    //
    // BTags
    //
    nTupleAnalysis::btaggingHists* hJets1BTagsAll = nullptr;

    nTupleAnalysis::vertexHists* hTree2Vtx = nullptr;
    nTupleAnalysis::vertexHists* hTree1Vtx = nullptr;

    nTupleAnalysis::vertexHists* hTree2Vtx_PVMatch = nullptr;
    nTupleAnalysis::vertexHists* hTree1Vtx_PVMatch = nullptr;

    nTupleAnalysis::trackHists* hAllTracks           = nullptr;

    float OfflineDeepCSVTightCut  = -99;
    float OfflineDeepCSVMediumCut = -99;
    float OfflineDeepCSVLooseCut  = -99;
    float OfflineDeepFlavourMediumCut = -99;
    float OnlineCSVCut            = -99;
    float OnlineDeepCSVCut        = -99;

    TH1F*   hDeltaRJet1Jet2          ;

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


    BTagAnalysis(TChain* eventsTree1, TChain* eventsTree2, fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug, std::string PUFileName, std::string jetDetailString, const edm::ParameterSet& nnConfig, std::string pfJetName, bool _doEMuTandP = false);
    void monitor(long int);
    int eventLoop(int, int nSkipEvents = 0);
    int processEvent();
    bool passLumiMask();
    std::map<edm::LuminosityBlockID, float> lumiData;
    void getLumiData(std::string);
    ~BTagAnalysis();

    void JetToJetTrackMatching(const nTupleAnalysis::jetPtr& jet1, const nTupleAnalysis::trackPtr& jet1Trk,
			       const nTupleAnalysis::jetPtr& jet2,
			       float dRMatch);

    void JetToJetTrkTagMatching(const nTupleAnalysis::jetPtr& jet1, const nTupleAnalysis::trkTagVarPtr& jet1TrkTag,
				const nTupleAnalysis::jetPtr& jet2,
				float dRMatch);

    void JetToJetSVMatching(const nTupleAnalysis::secondaryVertexPtr& jet1SV,
			    const nTupleAnalysis::jetPtr& jet2,
			    float dRMatch);



    nTupleAnalysis::pileUpWeightTool* pileUpTool = nullptr;

  };

}
#endif // BTagAnalysis_H
