// -*- C++ -*-
#if !defined(BTagAnalysisHLT_H)
#define BTagAnalysisHLT_H

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

  class BTagAnalysisHLT {
  public:

    TChain* eventsRAW;

    bool debug = false;
    std::string year;
    bool isMC  = false;
    TFileDirectory dir;

    bool doTracks = true;
    bool doCaloJets = true;
    bool doLeptonSel = false;
    
    int histogramming = 1e6;
    int treeEvents;
    eventData* event;
    
    //nTupleAnalysis::eventHists* hEvents;
    //nTupleAnalysis::eventHists* hEventsNoPUWeight;

    nTupleAnalysis::cutflowHists* cutflow;
    nTupleAnalysis::cutflowHists* cutflowJets;

    nTupleAnalysis::jetHists* hPfJets;
    nTupleAnalysis::jetHists* hPfJets_matched;

    nTupleAnalysis::jetHists* hCaloJets;
    nTupleAnalysis::jetHists* hCaloJets_matched;


    nTupleAnalysis::trackHists* hPfTracks;
    nTupleAnalysis::trackHists* hPfTracks_noV0;

    nTupleAnalysis::trackHists* hCaloTracks;
    nTupleAnalysis::trackHists* hCaloTracks_noV0;

    nTupleAnalysis::btaggingHists* hPfBTags;

    nTupleAnalysis::vertexHists* hVtx;

    TH1F*   hmttPf           ;
    TH1F*   hmttPf_isFromV0  ;
    TH1F*   hmttCalo           ;
    TH1F*   hmttCalo_isFromV0  ;

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


    BTagAnalysisHLT(TChain* _eventsRAW, fwlite::TFileService& fs, bool _isMC, std::string _year, int _histogramming, bool _debug, std::string jetDetailString, const edm::ParameterSet& nnConfig);
    void monitor(long int);
    int eventLoop(int, int nSkipEvents = 0);
    int processEvent();
    bool passLumiMask();
    std::map<edm::LuminosityBlockID, float> lumiData;
    void getLumiData(std::string);
    ~BTagAnalysisHLT();

    void PFJetAnalysis(const nTupleAnalysis::jetPtr& hltJet, float weight);
    void CaloJetAnalysis(const nTupleAnalysis::jetPtr& hltJet, float weight);

  };

}
#endif // BTagAnalysisHLT_H

