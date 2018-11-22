// -*- C++ -*-

#if !defined(JetDataHandler_H)
#define JetDataHandler_H

#include "TriggerStudies/NtupleAna/interface/JetData.h"


namespace NtupleAna {



  class JetDataHandler {

  public:
    std::string m_name;
    static const int maxLength = 40;

    int  m_num         [maxLength] = { };
    float m_pt         [maxLength] = { };
    float m_eta        [maxLength] = { };
    float m_phi        [maxLength] = { };
    float m_mass       [maxLength] = { };
    float m_deepcsv    [maxLength] = { };
    float m_deepcsv_bb [maxLength] = { };

    float m_vertexNTracks                      [maxLength] = { };
    float m_vertexMass                         [maxLength] = { };
    float m_vertexJetDeltaR                    [maxLength] = { };
    float m_vertexFitProb                      [maxLength] = { };
    float m_vertexEnergyRatio                  [maxLength] = { };
    float m_vertexCategory                     [maxLength] = { };
    float m_vertexBoostOverSqrtJetPt           [maxLength] = { };
    float m_trackJetPt                         [maxLength] = { };
    float m_trackSumJetEtRatio                 [maxLength] = { };
    float m_trackSumJetDeltaR                  [maxLength] = { };
    float m_trackSip3dValAboveCharm            [maxLength] = { };
    float m_trackSip3dSigAboveCharm            [maxLength] = { };
    float m_trackSip2dValAboveCharm            [maxLength] = { };
    float m_trackSip2dSigAboveCharm            [maxLength] = { };
    float m_totalMultiplicity                  [maxLength] = { };
    float m_photonMultiplicity                 [maxLength] = { };
    float m_photonEnergyFraction               [maxLength] = { };
    float m_neutralHadronMultiplicity          [maxLength] = { };
    float m_neutralHadronEnergyFraction        [maxLength] = { };
    float m_neMult                             [maxLength] = { };
    float m_neHadEF                            [maxLength] = { };
    float m_neEmEF                             [maxLength] = { };
    float m_muonMultiplicity                   [maxLength] = { };
    float m_muonEnergyFraction                 [maxLength] = { };
    float m_mult                               [maxLength] = { };
    float m_muEF                               [maxLength] = { };
    float m_massVertexEnergyFraction           [maxLength] = { };
    float m_jetNTracksEtaRel                   [maxLength] = { };
    float m_jetNTracks                         [maxLength] = { };
    float m_jetNSelectedTracks                 [maxLength] = { };
    float m_jetNSecondaryVertices              [maxLength] = { };
    float m_hadronPhotonMultiplicity           [maxLength] = { };
    float m_hadronMultiplicity                 [maxLength] = { };
    float m_flightDistance1dSig                [maxLength] = { };
    float m_flightDistance1dVal                [maxLength] = { };
    float m_flightDistance2dSig                [maxLength] = { };
    float m_flightDistance2dVal                [maxLength] = { };
    float m_flightDistance3dSig                [maxLength] = { };
    float m_flightDistance3dVal                [maxLength] = { };
    float m_chargedHadronMultiplicity          [maxLength] = { };
    float m_chargedHadronEnergyFraction        [maxLength] = { };
    float m_chMult                             [maxLength] = { };
    float m_chHadEF                            [maxLength] = { };
    float m_chEmEF                             [maxLength] = { };
    float m_partonFlavour                      [maxLength] = { };
    float m_hadronFlavour                      [maxLength] = { };


  public:

  JetDataHandler(std::string name) : m_name(name)  {
      
    }

    ~JetDataHandler() { }; 


    void SetBranchAddress(TChain* intree);
    std::vector<JetData> GetJets();
    
  };

}
#endif // JetDataHandler_H
