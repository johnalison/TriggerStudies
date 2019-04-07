// -*- C++ -*-
#if !defined(JetHists_H)
#define JetHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "TriggerStudies/NtupleAna/interface/TrackHists.h"
#include "TriggerStudies/NtupleAna/interface/JetData.h"
#include "TriggerStudies/NtupleAna/interface/EventData.h"


namespace NtupleAna {


  class JetHists {

    TH1F* m_pt     ;
    TH1F* m_pt_l   ;
    TH1F* m_eta    ;
    TH1F* m_phi    ;
    TH1F* m_mass   ;
    TH1F* m_csv    ;
    TH1F* m_deepcsv;
    TH1F* m_SF;
    TH1F* m_lepOverlap04Tight;

    bool m_light = false;

    TH1F* m_matched_dPt      ;
    TH1F* m_matched_dEta     ;
    TH1F* m_matched_dPhi     ;
    TH1F* m_matched_dR       ;
    TH1F* m_matched_dMass    ;
    TH1F* m_matched_dcsv ;
    TH1F* m_matched_dDeepcsv ;

    TH1F* m_csv_matched ;
    TH2F* m_csv_vs_matched_csv;
    TH2F* m_csv_vs_matched_deepcsv;

    TH1F* m_deepcsv_matched ;
    TH2F* m_deepcsv_vs_matched_deepcsv;


    TH1F* m_deepcsv_bb;

    TH1F* m_vertexNTracks                    ;
    TH1F* m_vertexMass                       ;
    TH1F* m_vertexJetDeltaR                  ;
    TH1F* m_vertexFitProb                    ;
    TH1F* m_vertexEnergyRatio                ;
    TH1F* m_vertexCategory                   ;
    TH1F* m_vertexBoostOverSqrtJetPt         ;
    TH1F* m_trackJetPt                       ;
    TH1F* m_trackSumJetEtRatio               ;
    TH1F* m_trackSumJetDeltaR                ;
    TH1F* m_trackSip2dValAboveCharm          ;
    TH1F* m_trackSip2dSigAboveCharm          ;
    TH1F* m_trackSip3dValAboveCharm          ;
    TH1F* m_trackSip3dSigAboveCharm          ;
    TH1F* m_totalMultiplicity                ;
    TH1F* m_totalFraction                ;
    TH1F* m_photonMultiplicity               ;
    TH1F* m_photonEnergyFraction             ;
    TH1F* m_neutralHadronMultiplicity        ;
    TH1F* m_neutralHadronEnergyFraction      ;
    TH1F* m_neMult                           ;
    TH1F* m_neHadEF                          ;
    TH1F* m_neEmEF                           ;
    TH1F* m_muonMultiplicity                 ;
    TH1F* m_muonEnergyFraction               ;
    TH1F* m_mult                             ;
    TH1F* m_muEF                             ;
    TH1F* m_massVertexEnergyFraction         ;
    TH1F* m_jetNTracksEtaRel                 ;
    TH1F* m_jetNTracks                       ;
    TH1F* m_jetNSelectedTracks               ;
    TH1F* m_jetNSecondaryVertices            ;
    TH1F* m_hadronPhotonMultiplicity         ;
    TH1F* m_hadronMultiplicity               ;
    TH1F* m_flightDistance1dSig              ;
    TH1F* m_flightDistance1dVal              ;
    TH1F* m_flightDistance2dSig              ;
    TH1F* m_flightDistance2dVal              ;
    TH1F* m_flightDistance3dSig              ;
    TH1F* m_flightDistance3dVal              ;
    TH1F* m_chargedHadronMultiplicity        ;
    TH1F* m_chargedHadronEnergyFraction      ;
    TH1F* m_chMult                           ;
    TH1F* m_chHadEF                          ;
    TH1F* m_chEmEF                           ;
    TH1F* m_partonFlavour                    ;
    TH1F* m_hadronFlavour                    ;

    TH1F* m_allJetsVsnPV             ;
    TH1F* m_passCSVBTagJetsVsnPV     ;
    TH1F* m_passDeepCSVBTagJetsVsnPV ;


    TH1F* m_nTrk; 
    TrackHists* m_trackHists;


  public:

    JetHists(std::string name, fwlite::TFileService& fs, bool light=false);

    ~JetHists(); 
    
    //void Fill (const JetData* jetPtr);
    void Fill (const JetData& jetPtr, float eventWeight = 1.0, const EventData* eventDataPtr = nullptr);
    
  };

}
#endif // JetHists_H
