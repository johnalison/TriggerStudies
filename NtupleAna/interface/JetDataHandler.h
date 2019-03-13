// -*- C++ -*-

#if !defined(JetDataHandler_H)
#define JetDataHandler_H

namespace NtupleAna{
  class JetData;
}


namespace NtupleAna {



  class JetDataHandler {

  public:
    std::string m_name;
    bool  m_loadTrkLevel;
    bool  m_isMC;
    static const int maxLength = 40;

    int  m_num         [maxLength] = { };
    float m_pt         [maxLength] = { };
    float m_eta        [maxLength] = { };
    float m_phi        [maxLength] = { };
    float m_mass       [maxLength] = { };
    float m_csv        [maxLength] = { };
    float m_deepcsv    [maxLength] = { };
    float m_deepcsv_b  [maxLength] = { };
    float m_deepcsv_bb [maxLength] = { };
    float m_SF         [maxLength] = { };
    float m_passesTightLeptVetoID [maxLength] = { };
    float m_lepOverlap04Tight     [maxLength] = { };

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


    std::vector<std::vector<float> >* m_trackSip3dSig = 0;
    std::vector<std::vector<float> >* m_trackSip3dVal = 0;
    
    std::vector<std::vector<float> >* m_trackSip2dSig = 0;
    std::vector<std::vector<float> >* m_trackSip2dVal = 0;
    
    std::vector<std::vector<float> >* m_trackDecayLenVal = 0;
    //std::vector<std::vector<float> >* m_trackDecayLenSig = 0;
    std::vector<std::vector<float> >* m_trackJetDistVal = 0;
    std::vector<std::vector<float> >* m_trackJetDistSig = 0;
    //std::vector<std::vector<float> >* m_trackGhostTrackWeight = 0;
    //std::vector<std::vector<float> >* m_trackGhostTrackDistSig = 0;
    //std::vector<std::vector<float> >* m_trackGhostTrackDistVal = 0;
    std::vector<std::vector<float> >* m_trackPtRel = 0;
    std::vector<std::vector<float> >* m_trackMomentum = 0;
    std::vector<std::vector<float> >* m_trackEta = 0;
    std::vector<std::vector<float> >* m_trackPhi = 0;
    //std::vector<std::vector<float> >* m_trackCharge = 0;
    std::vector<std::vector<float> >* m_trackPPar = 0;
    std::vector<std::vector<float> >* m_trackDeltaR = 0;
    std::vector<std::vector<float> >* m_trackEtaRel = 0;
    std::vector<std::vector<float> >* m_trackPtRatio = 0;
    std::vector<std::vector<float> >* m_trackPParRatio = 0;
    //std::vector<std::vector<float> >* m_trackP0Par = 0;
    //std::vector<std::vector<float> >* m_trackP0ParRatio = 0;
    std::vector<std::vector<float> >* m_trackChi2 = 0;
    std::vector<std::vector<float> >* m_trackNTotalHits = 0;
    std::vector<std::vector<float> >* m_trackNPixelHits = 0;
    

    void SetBranchAddress(TChain* intree, std::string brName, int* int_arr);
    void SetBranchAddress(TChain* intree, std::string brName, float* float_arr);
    void SetBranchAddress(TChain* intree, std::string brName, std::vector<std::vector<float> >** vector_ptr);

  public:

    JetDataHandler(std::string name, bool loadTrkLevel = true, bool isMC = true) : m_name(name), m_loadTrkLevel(loadTrkLevel), m_isMC(isMC)  {
      
    }

    ~JetDataHandler() { }; 


    void SetBranchAddress(TChain* intree);
    std::vector<JetData> GetJets();
    std::vector<JetData> GetJetsAll();
    std::vector<JetData> GetJetsNoTrks();
    
  };

}
#endif // JetDataHandler_H
