// -*- C++ -*-

#if !defined(eventData_H)
#define eventData_H

#include <iostream>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"
#include "nTupleAnalysis/baseClasses/interface/muonData.h"
#include "nTupleAnalysis/baseClasses/interface/elecData.h"
#include "nTupleAnalysis/baseClasses/interface/vertexData.h"

// for jet pseudoTag calculations
#include <TRandom3.h>
#include <numeric>
#include <boost/math/special_functions/binomial.hpp>

namespace TriggerStudies {

  class eventData {

  public:
    // Member variables
    TChain* treeRAW;
    TChain* treeAOD = nullptr;
    bool doOffline = true;

    typedef std::vector<std::pair<Int_t, Int_t> > RunEventMap;
    RunEventMap AODEvents;
    int treeEventsAOD;

    bool isMC;
    std::string year;
    bool debug;
    bool doCaloJets;
    bool doPuppiJets;
    Int_t    run       =  0;
    UInt_t    lumiBlock =  0;
    Int_t    event     =  0;
    Int_t    runAOD       =  0;
    UInt_t    lumiBlockAOD =  0;
    Int_t eventAOD     =  0;
    Int_t BitTrigger[1000];

    nTupleAnalysis::jetData* offTreeJets;
    std::vector<nTupleAnalysis::jetPtr> offJets;

    nTupleAnalysis::jetData* pfTreeJets;
    std::vector<nTupleAnalysis::jetPtr> pfJets;

    nTupleAnalysis::jetData* caloTreeJets;
    std::vector<nTupleAnalysis::jetPtr> caloJets;
    
    nTupleAnalysis::jetData* puppiTreeJets;
    std::vector<nTupleAnalysis::jetPtr> puppiJets;

    nTupleAnalysis::muonData* treeMuons;
    std::vector<nTupleAnalysis::muonPtr> muons;

    nTupleAnalysis::elecData* treeElecs;
    std::vector<nTupleAnalysis::elecPtr> elecs;

    nTupleAnalysis::vertexData* treePVs;
    std::vector<nTupleAnalysis::vertexPtr> pvs;

    nTupleAnalysis::vertexData* offTreePVs;
    std::vector<nTupleAnalysis::vertexPtr> offPVs;

    // Constructors and member functions
    eventData(TChain*, TChain*, bool, std::string, bool, std::string);
    void update(int);

    void dump();
    ~eventData();

  };

}
#endif // eventData_H
