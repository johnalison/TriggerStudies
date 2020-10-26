// -*- C++ -*-
#if !defined(TrigTurnOnStudy_H)
#define TrigTurnOnStudy_H

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

  class TrigTurnOnStudy {
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

    nTupleAnalysis::jetHists* hOffJetsPreOLap;
    nTupleAnalysis::jetHists* hOffJets;
    nTupleAnalysis::jetHists* hOffJets_matched;
    nTupleAnalysis::jetHists* hOffJets_matchedJet;

    TH1F* hdR_all = nullptr;
    TH1F* hdR_2nd_all = nullptr;
    TH1F* hdR_misMatchPt = nullptr;
    TH1F* hdR_2nd_misMatchPt = nullptr;

    nTupleAnalysis::jetHists* hAllOffJets;

    struct turnOnHists { 
      
      TH1F* offJetPt;
      TH1F* trigJetPt;
      TH1F* offJetPt_l;
      TH1F* trigJetPt_l;
      TH1F* offJetPt_vl;
      TH1F* trigJetPt_vl;
      TH1F* offJetPt_2vl;
      TH1F* trigJetPt_2vl;
      TH1F* offJetPt_3vl;
      TH1F* trigJetPt_3vl;
      TH1F* offJetPt_4vl;
      TH1F* trigJetPt_4vl;

      turnOnHists(std::string ptName, TFileDirectory dir){
	trigJetPt      = dir.make<TH1F>(("trigJetPt"+ptName).c_str(),            ("TrigTurnOnStudy/trigJetPt"+ptName+";             Trig jet P_{T} [GeV];   Entries").c_str(), 100,0, 200);
	offJetPt       = dir.make<TH1F>(("offJetPt"+ptName).c_str(),             ("TrigTurnOnStudy/offJetPt"+ptName+";              jet P_{T} [GeV];   Entries").c_str(),      100,0, 200);
	trigJetPt_l    = dir.make<TH1F>(("trigJetPt"+ptName+"_l").c_str(),       ("TrigTurnOnStudy/trigJetPt"+ptName+"_l;           Trig jet P_{T} [GeV];   Entries").c_str(), 100,100, 300);
	offJetPt_l     = dir.make<TH1F>(("offJetPt"+ptName+"_l").c_str(),        ("TrigTurnOnStudy/offJetPt"+ptName+"_l;            jet P_{T} [GeV];   Entries").c_str(),      100,100, 300);
	trigJetPt_vl   = dir.make<TH1F>(("trigJetPt"+ptName+"_vl").c_str(),      ("TrigTurnOnStudy/trigJetPt"+ptName+"_vl;          Trig jet P_{T} [GeV];   Entries").c_str(), 100,200, 400);
	offJetPt_vl    = dir.make<TH1F>(("offJetPt"+ptName+"_vl").c_str(),       ("TrigTurnOnStudy/offJetPt"+ptName+"_vl;           jet P_{T} [GeV];   Entries").c_str(),      100,200, 400);
	trigJetPt_2vl  = dir.make<TH1F>(("trigJetPt"+ptName+"_2vl").c_str(),     ("TrigTurnOnStudy/trigJetPt"+ptName+"_2vl;         Trig jet P_{T} [GeV];   Entries").c_str(), 100,300, 500);
	offJetPt_2vl   = dir.make<TH1F>(("offJetPt"+ptName+"_2vl").c_str(),      ("TrigTurnOnStudy/offJetPt"+ptName+"_2vl;          jet P_{T} [GeV];   Entries").c_str(),      100,300, 500);
	trigJetPt_3vl  = dir.make<TH1F>(("trigJetPt"+ptName+"_3vl").c_str(),     ("TrigTurnOnStudy/trigJetPt"+ptName+"_3vl;         Trig jet P_{T} [GeV];   Entries").c_str(), 100,400, 600);
	offJetPt_3vl   = dir.make<TH1F>(("offJetPt"+ptName+"_3vl").c_str(),      ("TrigTurnOnStudy/offJetPt"+ptName+"_3vl;          jet P_{T} [GeV];   Entries").c_str(),      100,400, 600);
	trigJetPt_4vl  = dir.make<TH1F>(("trigJetPt"+ptName+"_4vl").c_str(),     ("TrigTurnOnStudy/trigJetPt"+ptName+"_4vl;         Trig jet P_{T} [GeV];   Entries").c_str(), 100,500, 700);
	offJetPt_4vl   = dir.make<TH1F>(("offJetPt"+ptName+"_4vl").c_str(),      ("TrigTurnOnStudy/offJetPt"+ptName+"_4vl;          jet P_{T} [GeV];   Entries").c_str(),      100,500, 700);
      };

      void Fill(float trig_Pt, float off_Pt, float weight){
	trigJetPt    ->Fill(trig_Pt, weight);
	offJetPt     ->Fill(off_Pt,  weight);
	trigJetPt_l  ->Fill(trig_Pt, weight);
	offJetPt_l   ->Fill(off_Pt,  weight);
	trigJetPt_vl ->Fill(trig_Pt, weight);
	offJetPt_vl  ->Fill(off_Pt,  weight);
	trigJetPt_2vl ->Fill(trig_Pt, weight);
	offJetPt_2vl  ->Fill(off_Pt,  weight);
	trigJetPt_3vl ->Fill(trig_Pt, weight);
	offJetPt_3vl  ->Fill(off_Pt,  weight);
	trigJetPt_4vl ->Fill(trig_Pt, weight);
	offJetPt_4vl  ->Fill(off_Pt,  weight);
      };
    
  };

    std::vector<float> trigThresolds = {0.,15.,30.,40.,45.,50.,60.,75.,80.,88.,90.,100.,103.,105.,110.,120.,140.,200.,260.,320.,400.,450.,500.,550.};
    std::map<float, turnOnHists*> turnOns;
    std::map<float, turnOnHists*> turnOns_L;
    std::map<float, turnOnHists*> turnOns_B;


    std::map<float, turnOnHists*> turnOnsAll;
    std::map<float, turnOnHists*> turnOnsAll_L;
    std::map<float, turnOnHists*> turnOnsAll_B;


    struct hTTurnOnHists { 
      
      TH1F* offHt;
      TH1F* trigHt;
      TH1F* offHt_l;
      TH1F* trigHt_l;
      TH1F* offHt_vl;
      TH1F* trigHt_vl;
      TH1F* offHt_2vl;
      TH1F* trigHt_2vl;

      TH1F* offHt30;
      TH1F* trigHt30;
      TH1F* offHt30_l;
      TH1F* trigHt30_l;
      TH1F* offHt30_vl;
      TH1F* trigHt30_vl;
      TH1F* offHt30_2vl;
      TH1F* trigHt30_2vl;


      hTTurnOnHists(std::string ptName, TFileDirectory dir){
	trigHt      = dir.make<TH1F>(("trigHt"+ptName).c_str(),            ("TrigTurnOnStudy/trigHt"+ptName+";             Trig h_{T} [GeV];   Entries").c_str(), 100,0, 500);
	offHt       = dir.make<TH1F>(("offHt"+ptName).c_str(),             ("TrigTurnOnStudy/offHt"+ptName+";              h_{T} [GeV];   Entries").c_str(),      100,0, 500);
	trigHt_l    = dir.make<TH1F>(("trigHt"+ptName+"_l").c_str(),       ("TrigTurnOnStudy/trigHt"+ptName+"_l;           Trig h_{T} [GeV];   Entries").c_str(), 100,300, 800);
	offHt_l     = dir.make<TH1F>(("offHt"+ptName+"_l").c_str(),        ("TrigTurnOnStudy/offHt"+ptName+"_l;            h_{T} [GeV];   Entries").c_str(),      100,300, 800);
	trigHt_vl   = dir.make<TH1F>(("trigHt"+ptName+"_vl").c_str(),      ("TrigTurnOnStudy/trigHt"+ptName+"_vl;          Trig h_{T} [GeV];   Entries").c_str(), 100,600, 1100);
	offHt_vl    = dir.make<TH1F>(("offHt"+ptName+"_vl").c_str(),       ("TrigTurnOnStudy/offHt"+ptName+"_vl;           h_{T} [GeV];   Entries").c_str(),      100,600, 1100);
	trigHt_2vl  = dir.make<TH1F>(("trigHt"+ptName+"_2vl").c_str(),     ("TrigTurnOnStudy/trigHt"+ptName+"_2vl;         Trig h_{T} [GeV];   Entries").c_str(), 100,900, 1400);
	offHt_2vl   = dir.make<TH1F>(("offHt"+ptName+"_2vl").c_str(),      ("TrigTurnOnStudy/offHt"+ptName+"_2vl;          h_{T} [GeV];   Entries").c_str(),      100,900, 1400);

	trigHt30      = dir.make<TH1F>(("trigHt30"+ptName).c_str(),            ("TrigTurnOnStudy/trigHt30"+ptName+";             Trig h_{T} [GeV];   Entries").c_str(), 100,0, 500);
	offHt30       = dir.make<TH1F>(("offHt30"+ptName).c_str(),             ("TrigTurnOnStudy/offHt30"+ptName+";              h_{T} [GeV];   Entries").c_str(),      100,0, 500);
	trigHt30_l    = dir.make<TH1F>(("trigHt30"+ptName+"_l").c_str(),       ("TrigTurnOnStudy/trigHt30"+ptName+"_l;           Trig h_{T} [GeV];   Entries").c_str(), 100,300, 800);
	offHt30_l     = dir.make<TH1F>(("offHt30"+ptName+"_l").c_str(),        ("TrigTurnOnStudy/offHt30"+ptName+"_l;            h_{T} [GeV];   Entries").c_str(),      100,300, 800);
	trigHt30_vl   = dir.make<TH1F>(("trigHt30"+ptName+"_vl").c_str(),      ("TrigTurnOnStudy/trigHt30"+ptName+"_vl;          Trig h_{T} [GeV];   Entries").c_str(), 100,600, 1100);
	offHt30_vl    = dir.make<TH1F>(("offHt30"+ptName+"_vl").c_str(),       ("TrigTurnOnStudy/offHt30"+ptName+"_vl;           h_{T} [GeV];   Entries").c_str(),      100,600, 1100);
	trigHt30_2vl  = dir.make<TH1F>(("trigHt30"+ptName+"_2vl").c_str(),     ("TrigTurnOnStudy/trigHt30"+ptName+"_2vl;         Trig h_{T} [GeV];   Entries").c_str(), 100,900, 1400);
	offHt30_2vl   = dir.make<TH1F>(("offHt30"+ptName+"_2vl").c_str(),      ("TrigTurnOnStudy/offHt30"+ptName+"_2vl;          h_{T} [GeV];   Entries").c_str(),      100,900, 1400);

      };

      void Fill(float trig_ht30, float trig_ht, float off_ht30, float off_ht, float weight){
	trigHt      ->Fill(trig_ht, weight);
	offHt       ->Fill(off_ht,  weight);
	trigHt_l    ->Fill(trig_ht, weight);
	offHt_l     ->Fill(off_ht,  weight);
	trigHt_vl   ->Fill(trig_ht, weight);
	offHt_vl    ->Fill(off_ht,  weight);
	trigHt_2vl  ->Fill(trig_ht, weight);
	offHt_2vl   ->Fill(off_ht,  weight);

	trigHt30      ->Fill(trig_ht30, weight);
	offHt30       ->Fill(off_ht30,  weight);
	trigHt30_l    ->Fill(trig_ht30, weight);
	offHt30_l     ->Fill(off_ht30,  weight);
	trigHt30_vl   ->Fill(trig_ht30, weight);
	offHt30_vl    ->Fill(off_ht30,  weight);
	trigHt30_2vl  ->Fill(trig_ht30, weight);
	offHt30_2vl   ->Fill(off_ht30,  weight);

      };
    
    };


    std::vector<float> htThresolds = {0.,180.,330.,250.,370.,430.,510.,590.,680.,780.,890.,1050.};
    std::map<float, hTTurnOnHists*> hTTurnOns;
    std::map<float, hTTurnOnHists*> hTTurnOnsAll;


    float OfflineDeepCSVTightCut  = -99;
    float OfflineDeepCSVMediumCut = -99;
    float OfflineDeepCSVLooseCut  = -99;
    float OnlineCSVCut            = -99;
    float OnlineDeepCSVCut        = -99;

    
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

    TrigTurnOnStudy(TChain*, TChain*, fwlite::TFileService&, bool, std::string, int, bool);
    void monitor(long int);
    int eventLoop(int);
    int processEvent();
    bool passLumiMask();
    std::map<edm::LuminosityBlockID, float> lumiData;
    void getLumiData(std::string);
    ~TrigTurnOnStudy();


  };

}
#endif // TrigTurnOnStudy_H

