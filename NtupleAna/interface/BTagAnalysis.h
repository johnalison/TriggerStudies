// -*- C++ -*-
#if !defined(BTagAnalysis_H)
#define BTagAnalysis_H

#include <ctime>
#include <sys/resource.h>

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

    int histogramming = 1e6;
    int treeEvents;
    eventData* event;

    nTupleAnalysis::eventHists* hEvents;
    nTupleAnalysis::eventHists* hEventsNoPUWeight;

    nTupleAnalysis::cutflowHists* cutflow;
    nTupleAnalysis::cutflowHists* cutflowJets;
    nTupleAnalysis::muonHists* hMuons;
    nTupleAnalysis::elecHists* hElecs;
    nTupleAnalysis::muonHists* hAllMuons;
    nTupleAnalysis::elecHists* hAllElecs;
    nTupleAnalysis::muonHists* hSelMuons;
    nTupleAnalysis::elecHists* hSelElecs;

    nTupleAnalysis::jetHists* hOffJetsPreOLap;
    nTupleAnalysis::jetHists* hOffJets;
    nTupleAnalysis::jetHists* hOffJets_matched;
    nTupleAnalysis::jetHists* hOffJets_matched_eta1;
    nTupleAnalysis::jetHists* hOffJets_matched_eta2;
    nTupleAnalysis::jetHists* hOffJets_matched_eta3;
    nTupleAnalysis::jetHists* hOffJets_matchedJet;
    nTupleAnalysis::jetHists* hOffJets_matchedJet_eta1;
    nTupleAnalysis::jetHists* hOffJets_matchedJet_eta2;
    nTupleAnalysis::jetHists* hOffJets_matchedJet_eta3;
    nTupleAnalysis::jetHists* hOffJets_matchedCalo;
    nTupleAnalysis::jetHists* hOffJets_matchedCaloJet;

    nTupleAnalysis::jetHists* hOffJetsPuppi;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppi;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppiJet;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppi_eta1;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppi_eta2;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppi_eta3;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppiJet_eta1;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppiJet_eta2;
    nTupleAnalysis::jetHists* hOffJets_matchedPuppiJet_eta3;

    nTupleAnalysis::jetHists*    hOffJet_matchedPFcsvTag         ;
    nTupleAnalysis::jetHists*    hOffJet_matchedPFcsvTagJet      ;
    nTupleAnalysis::jetHists*    hOffJet_matchedPFDeepcsvTag     ;
    nTupleAnalysis::jetHists*    hOffJet_matchedPFDeepcsvTagJet  ;
    nTupleAnalysis::jetHists*    hOffJetTightDeepCSV_matchedPFJet       ;
    nTupleAnalysis::jetHists*    hOffJetMediumDeepCSV_matchedPFJet      ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPFJet      ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPFDeepCSV  ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPFCSV      ;
    nTupleAnalysis::jetHists*    hOffJetLooseDeepCSV_matchedPFJet       ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPFJet      ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPFDeepCSV  ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPFCSV      ;


    nTupleAnalysis::jetHists*    hOffJet_matchedCalocsvTag         ;
    nTupleAnalysis::jetHists*    hOffJet_matchedCalocsvTagJet      ;
    nTupleAnalysis::jetHists*    hOffJet_matchedCaloDeepcsvTag     ;
    nTupleAnalysis::jetHists*    hOffJet_matchedCaloDeepcsvTagJet  ;
    nTupleAnalysis::jetHists*    hOffJetTightDeepCSV_matchedCaloJet       ;
    nTupleAnalysis::jetHists*    hOffJetMediumDeepCSV_matchedCaloJet      ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedCaloJet      ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedCaloDeepCSV  ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedCaloCSV      ;
    nTupleAnalysis::jetHists*    hOffJetLooseDeepCSV_matchedCaloJet       ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedCaloJet      ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedCaloDeepCSV  ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedCaloCSV      ;


    nTupleAnalysis::jetHists*    hOffJet_matchedPuppicsvTag         ;
    nTupleAnalysis::jetHists*    hOffJet_matchedPuppicsvTagJet      ;
    nTupleAnalysis::jetHists*    hOffJet_matchedPuppiDeepcsvTag     ;
    nTupleAnalysis::jetHists*    hOffJet_matchedPuppiDeepcsvTagJet  ;
    nTupleAnalysis::jetHists*    hOffJetTightDeepCSV_matchedPuppiJet       ;
    nTupleAnalysis::jetHists*    hOffJetMediumDeepCSV_matchedPuppiJet      ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPuppiJet      ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPuppiDeepCSV  ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepCSV_matchedPuppiCSV      ;
    nTupleAnalysis::jetHists*    hOffJetLooseDeepCSV_matchedPuppiJet       ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPuppiJet      ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPuppiDeepCSV  ;
    nTupleAnalysis::jetHists*    hOffJetMedDeepFlav_matchedPuppiCSV      ;


    nTupleAnalysis::jetHists*  hOffJets_matched_L   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_L_eta1   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_L_eta2   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_L_eta3   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_L;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_L_eta1;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_L_eta2;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_L_eta3;
    nTupleAnalysis::jetHists*  hOffJets_matchedCalo_L;
    nTupleAnalysis::jetHists*  hOffJets_matchedCaloJet_L;
    nTupleAnalysis::jetHists*  hOffJets_matched_B   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_B_eta1   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_B_eta2   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_B_eta3   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_B;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_B_eta1;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_B_eta2;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_B_eta3;
    nTupleAnalysis::jetHists*  hOffJets_matchedCalo_B;
    nTupleAnalysis::jetHists*  hOffJets_matchedCaloJet_B;
    nTupleAnalysis::jetHists*  hOffJets_matched_C   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_C_eta1   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_C_eta2   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_C_eta3   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_C;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_C_eta1;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_C_eta2;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_C_eta3;
    nTupleAnalysis::jetHists*  hOffJets_matchedCalo_C;
    nTupleAnalysis::jetHists*  hOffJets_matchedCaloJet_C;

    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_L;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_L_eta1   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_L_eta2   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_L_eta3   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_L;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_L_eta1;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_L_eta2;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_L_eta3;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_B;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_B_eta1   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_B_eta2   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_B_eta3   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_B;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_B_eta1;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_B_eta2;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_B_eta3;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_C;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_C_eta1   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_C_eta2   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppi_C_eta3   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_C;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_C_eta1;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_C_eta2;
    nTupleAnalysis::jetHists*  hOffJets_matchedPuppiJet_C_eta3;

    nTupleAnalysis::jetHists* hPfJets;
    nTupleAnalysis::jetHists* hPfJets_matched;
    //nTupleAnalysis::jetHists* hPfJets_matched_L;
    //nTupleAnalysis::jetHists* hPfJets_matched_B;
    //nTupleAnalysis::jetHists* hPfJets_matched_C;

    nTupleAnalysis::jetHists* hCaloJets;
    nTupleAnalysis::jetHists* hCaloJets_matched;
    //nTupleAnalysis::jetHists* hCaloJets_matched_L;
    //nTupleAnalysis::jetHists* hCaloJets_matched_B;
    //nTupleAnalysis::jetHists* hCaloJets_matched_C;

    nTupleAnalysis::jetHists* hPuppiJets;
    nTupleAnalysis::jetHists* hPuppiJets_matched;
    //nTupleAnalysis::jetHists* hPuppiJets_matched_L;
    //nTupleAnalysis::jetHists* hPuppiJets_matched_B;
    //nTupleAnalysis::jetHists* hPuppiJets_matched_C;

    nTupleAnalysis::trackHists* hOffTracks;
    nTupleAnalysis::trackHists* hOffTracks_unmatched;
    nTupleAnalysis::trackHists* hOffTracks_matched;

    nTupleAnalysis::trackHists* hOffTracksCalo;
    nTupleAnalysis::trackHists* hOffTracksCalo_unmatched;
    nTupleAnalysis::trackHists* hOffTracksCalo_matched;

    nTupleAnalysis::trackHists* hOffTracksPuppi;
    nTupleAnalysis::trackHists* hOffTracksPuppi_unmatched;
    nTupleAnalysis::trackHists* hOffTracksPuppi_matched;


    nTupleAnalysis::trackHists* hPfTracks;
    nTupleAnalysis::trackHists* hPfTracks_matched;
    nTupleAnalysis::trackHists* hPfTracks_unmatched;
    nTupleAnalysis::trackHists* hPfTracks_noV0;

    nTupleAnalysis::trackHists* hCaloTracks;
    nTupleAnalysis::trackHists* hCaloTracks_matched;
    nTupleAnalysis::trackHists* hCaloTracks_unmatched;
    nTupleAnalysis::trackHists* hCaloTracks_noV0;

    nTupleAnalysis::trackHists* hPuppiTracks;
    nTupleAnalysis::trackHists* hPuppiTracks_matched;
    nTupleAnalysis::trackHists* hPuppiTracks_unmatched;
    nTupleAnalysis::trackHists* hPuppiTracks_noV0;


    nTupleAnalysis::trackHists* hOffTracks_noV0;
    nTupleAnalysis::trackHists* hOffTracks_matched_noV0;

    nTupleAnalysis::trackHists* hOffTracksCalo_noV0;
    nTupleAnalysis::trackHists* hOffTracksCalo_matched_noV0;

    nTupleAnalysis::trackHists* hOffTracksPuppi_noV0;
    nTupleAnalysis::trackHists* hOffTracksPuppi_matched_noV0;

    nTupleAnalysis::btaggingHists* hOffBTagsAll;
    nTupleAnalysis::btaggingHists* hOffBTags;
    nTupleAnalysis::btaggingHists* hOffBTags_matched;
    nTupleAnalysis::btaggingHists* hOffBTags_unmatched;
    nTupleAnalysis::btaggingHists* hOffBTags_noV0;
    nTupleAnalysis::btaggingHists* hOffBTags_matched_noV0;

    nTupleAnalysis::btaggingHists* hPfBTags;
    nTupleAnalysis::btaggingHists* hPfBTags_matched;
    nTupleAnalysis::btaggingHists* hPfBTags_unmatched;

    nTupleAnalysis::btaggingHists* hPuppiBTags;
    nTupleAnalysis::btaggingHists* hPuppiBTags_matched;
    nTupleAnalysis::btaggingHists* hPuppiBTags_unmatched;

    nTupleAnalysis::vertexHists* hVtx;
    nTupleAnalysis::vertexHists* hOffVtx;

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


    BTagAnalysis(TChain* _eventsRAW, TChain* _eventsAOD, fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug, std::string PUFileName, std::string jetDetailString, const edm::ParameterSet& nnConfig);
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
