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
    nTupleAnalysis::muonHists* hMuons;
    nTupleAnalysis::elecHists* hElecs;

    nTupleAnalysis::jetHists* hOffJetsPreOLap;
    nTupleAnalysis::jetHists* hOffJets;
    nTupleAnalysis::jetHists* hOffJets_matched;
    nTupleAnalysis::jetHists* hOffJets_matchedJet;

    nTupleAnalysis::jetHists*  hOffJets_L   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_L   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_L;
    nTupleAnalysis::jetHists*  hOffJets_B   ;
    nTupleAnalysis::jetHists*  hOffJets_matched_B   ;
    nTupleAnalysis::jetHists*  hOffJets_matchedJet_B;


    nTupleAnalysis::jetHists* hPfJets;
    nTupleAnalysis::jetHists* hPfJets_matched;
    nTupleAnalysis::jetHists* hPfJets_matched_L;
    nTupleAnalysis::jetHists* hPfJets_matched_B;

    nTupleAnalysis::jetHists* hCaloJets;
    nTupleAnalysis::jetHists* hCaloJets_matched;

    nTupleAnalysis::trackHists* hOffTracks;
    nTupleAnalysis::trackHists* hOffTracks_unmatched;
    nTupleAnalysis::trackHists* hOffTracks_matched;
    nTupleAnalysis::trackHists* hPfTracks;
    nTupleAnalysis::trackHists* hPfTracks_matched;
    nTupleAnalysis::trackHists* hPfTracks_unmatched;
    nTupleAnalysis::trackHists* hPfTracks_noV0;

    nTupleAnalysis::trackHists* hOffTracks_noV0;
    nTupleAnalysis::trackHists* hOffTracks_matched_noV0;

    nTupleAnalysis::btaggingHists* hOffBTags;
    nTupleAnalysis::btaggingHists* hOffBTags_matched;
    nTupleAnalysis::btaggingHists* hOffBTags_noV0;
    nTupleAnalysis::btaggingHists* hOffBTags_matched_noV0;

    nTupleAnalysis::btaggingHists* hPfBTags;

    TH1F*   hmttOff          ;
    TH1F*   hmttOff_isFromV0 ;
    TH1F*   hmttPf           ;
    TH1F*   hmttPf_isFromV0  ;


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
    double duration;
    double eventRate;
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

  };

}
#endif // BTagAnalysis_H

