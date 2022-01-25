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
#include "nTupleAnalysis/baseClasses/interface/truthData.h"

// for jet pseudoTag calculations
#include <TRandom3.h>
#include <numeric>
#include <boost/math/special_functions/binomial.hpp>

namespace TriggerStudies {

  class eventData {

  public:
    // Member variables
    TChain* tree1;
    TChain* tree2 = nullptr;
    bool doTree2 = true;

    typedef std::vector<std::pair<Int_t, Int_t> > RunEventMap;
    RunEventMap Tree2Events;
    int treeEventsTree2;

    bool isMC;
    std::string year;
    bool debug;
    //bool doCaloJets;
    //bool doPuppiJets;
    Int_t    run       =  0;
    UInt_t    lumiBlock =  0;
    Int_t    event     =  0;
    Int_t    runTree2       =  0;
    UInt_t    lumiBlockTree2 =  0;
    Int_t eventTree2     =  0;
    Int_t BitTrigger[1000];

    // Jets from TTree 1
    nTupleAnalysis::jetData* tree1Jets;
    std::vector<nTupleAnalysis::jetPtr> jetCol1;

    // Jets from TTree 2
    nTupleAnalysis::jetData* tree2Jets;
    std::vector<nTupleAnalysis::jetPtr> jetCol2;

    // Can load thee from separate calls to BTagAnalysis
    //nTupleAnalysis::jetData* caloTreeJets;
    //std::vector<nTupleAnalysis::jetPtr> caloJets;
    //
    //nTupleAnalysis::jetData* puppiTreeJets;
    //std::vector<nTupleAnalysis::jetPtr> puppiJets;

    nTupleAnalysis::muonData* treeMuons;
    std::vector<nTupleAnalysis::muonPtr> muons;

    nTupleAnalysis::elecData* treeElecs;
    std::vector<nTupleAnalysis::elecPtr> elecs;

    nTupleAnalysis::vertexData* tree1PVs;
    std::vector<nTupleAnalysis::vertexPtr> pvsTree1;

    nTupleAnalysis::vertexData* tree2PVs;
    std::vector<nTupleAnalysis::vertexPtr> pvsTree2;



    nTupleAnalysis::truthData* genJetTree = NULL;


    // Constructors and member functions
    eventData(TChain* _tree1, TChain* _tree2, bool mc, std::string y, bool d, std::string jetDetailLevel, std::string pfJetName = "PFJet.");
    void update(int);

    void dump();
    ~eventData();

  };

}
#endif // eventData_H
