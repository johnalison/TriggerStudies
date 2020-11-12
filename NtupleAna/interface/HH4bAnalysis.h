// -*- C++ -*-
#if !defined(HH4bAnalysis_H)
#define HH4bAnalysis_H

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
#include "nTupleAnalysis/baseClasses/interface/eventHists.h"




namespace TriggerStudies {

  class HH4bAnalysis {
  public:

    TChain* eventsAOD;
    TChain* eventsRAW;

    bool debug = false;
    TFileDirectory dir;

    int histogramming = 1e6;
    int treeEvents;
    eventData* event;

    nTupleAnalysis::eventHists* hEvents;
    nTupleAnalysis::cutflowHists* cutflow;

    //TH1F*   h4b_all          ;
    //TH1F*   h4b_L1          ;
    //TH1F*   h4b_HLTn          ;

    //eventHists* allEvents   = NULL;
    //tagHists* passPreSel    = NULL;

    long int nEvents = 0;

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


    HH4bAnalysis(TChain* _eventsRAW, TChain* _eventsAOD, fwlite::TFileService& fs, bool _debug);
    void monitor(long int);
    int eventLoop(int, int nSkipEvents = 0);
    int processEvent();

    ~HH4bAnalysis();

  };

}
#endif // HH4bAnalysis_H
