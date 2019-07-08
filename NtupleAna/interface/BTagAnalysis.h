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
//#include "ZZ4b/nTupleAnalysis/interface/eventHists.h"
//#include "ZZ4b/nTupleAnalysis/interface/tagHists.h"

namespace TriggerStudies {

  class BTagAnalysis {
  public:

    TChain* eventsAOD;
    TChain* eventsRAW;

    bool debug = false;
    std::string year;
    bool isMC  = false;
    TFileDirectory dir;

    int histogramming = 1e6;
    int treeEvents;
    eventData* event;

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
    nTupleAnalysis::jetHists* hOffJets_matchedJet;
    nTupleAnalysis::jetHists* hOffJets_matchedCalo;
    nTupleAnalysis::jetHists* hOffJets_matchedCaloJet;

    nTupleAnalysis::jetHists*  hOffJets_matched_L   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_L;
    nTupleAnalysis::jetHists*  hOffJets_matchedCalo_L;
    nTupleAnalysis::jetHists*  hOffJets_matchedCaloJet_L;
    nTupleAnalysis::jetHists*  hOffJets_matched_B   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_B;
    nTupleAnalysis::jetHists*  hOffJets_matchedCalo_B;
    nTupleAnalysis::jetHists*  hOffJets_matchedCaloJet_B;


    nTupleAnalysis::jetHists* hPfJets;
    nTupleAnalysis::jetHists* hPfJets_matched;
    nTupleAnalysis::jetHists* hPfJets_matched_L;
    nTupleAnalysis::jetHists* hPfJets_matched_B;

    nTupleAnalysis::jetHists* hCaloJets;
    nTupleAnalysis::jetHists* hCaloJets_matched;
    nTupleAnalysis::jetHists* hCaloJets_matched_L;
    nTupleAnalysis::jetHists* hCaloJets_matched_B;

    nTupleAnalysis::trackHists* hOffTracks;
    nTupleAnalysis::trackHists* hOffTracks_unmatched;
    nTupleAnalysis::trackHists* hOffTracks_matched;

    nTupleAnalysis::trackHists* hOffTracksCalo;
    nTupleAnalysis::trackHists* hOffTracksCalo_unmatched;
    nTupleAnalysis::trackHists* hOffTracksCalo_matched;


    nTupleAnalysis::trackHists* hPfTracks;
    nTupleAnalysis::trackHists* hPfTracks_matched;
    nTupleAnalysis::trackHists* hPfTracks_unmatched;
    nTupleAnalysis::trackHists* hPfTracks_noV0;

    nTupleAnalysis::trackHists* hCaloTracks;
    nTupleAnalysis::trackHists* hCaloTracks_matched;
    nTupleAnalysis::trackHists* hCaloTracks_unmatched;
    nTupleAnalysis::trackHists* hCaloTracks_noV0;


    nTupleAnalysis::trackHists* hOffTracks_noV0;
    nTupleAnalysis::trackHists* hOffTracks_matched_noV0;

    nTupleAnalysis::trackHists* hOffTracksCalo_noV0;
    nTupleAnalysis::trackHists* hOffTracksCalo_matched_noV0;

    nTupleAnalysis::btaggingHists* hOffBTags;
    nTupleAnalysis::btaggingHists* hOffBTags_matched;
    nTupleAnalysis::btaggingHists* hOffBTags_noV0;
    nTupleAnalysis::btaggingHists* hOffBTags_matched_noV0;

    nTupleAnalysis::btaggingHists* hPfBTags;

    float OfflineDeepCSVTightCut  = -99;
    float OfflineDeepCSVMediumCut = -99;
    float OfflineDeepCSVLooseCut  = -99;
    float OnlineCSVCut            = -99;
    float OnlineDeepCSVCut        = -99;
  

    TH1F*   hmttOff          ;
    TH1F*   hmttOff_isFromV0 ;
    TH1F*   hmttPf           ;
    TH1F*   hmttPf_isFromV0  ;
    TH1F*   hmttCalo           ;
    TH1F*   hmttCalo_isFromV0  ;


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

    BTagAnalysis(TChain*, TChain*, fwlite::TFileService&, bool, std::string, int, bool);
    void monitor(long int);
    int eventLoop(int);
    int processEvent();
    bool passLumiMask();
    std::map<edm::LuminosityBlockID, float> lumiData;
    void getLumiData(std::string);
    ~BTagAnalysis();

    void PFJetAnalysis(const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight);
    void CaloJetAnalysis(const nTupleAnalysis::jetPtr& offJet,const nTupleAnalysis::jetPtr& hltJet, float weight);

  };

}
#endif // BTagAnalysis_H

