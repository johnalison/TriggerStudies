// -*- C++ -*-

#if !defined(LeptonDataHandler_H)
#define LeptonDataHandler_H

#include "TriggerStudies/NtupleAna/interface/LeptonData.h"
#include "TFile.h"
#include "TH2D.h"

namespace NtupleAna {


  class LeptonDataHandler {

  public:

    std::string m_name;
    std::string m_year;
    bool m_isMC;
    static const int maxLength = 40;        

    int    m_num         [1] = { };
    float  m_pt     [maxLength]  = { };
    float  m_eta    [maxLength]  = { };
    float  m_phi    [maxLength]  = { };
    float  m_mass   [maxLength]  = { };
    float  m_superClusterEta   [maxLength]  = { };
    float  m_iso   [maxLength]  = { };
    float  m_SF    [maxLength]  = { };

    bool m_isElectrons = false;

    void SetBranchAddress(TChain* intree, std::string brName, int* int_arr);
    void SetBranchAddress(TChain* intree, std::string brName, float* float_arr);

  private:

    TFile* m_SFFile1 = nullptr;
    TFile* m_SFFile2 = nullptr;
    TH2D*  m_SFHist1 = nullptr;
    TH2D*  m_SFHist2 = nullptr;

  public:
    
    LeptonDataHandler(std::string name, std::string year, bool isMC = true);

    ~LeptonDataHandler() {}; 

    void SetBranchAddress (TChain* intree);

    std::vector<LeptonData> GetLeps(float ptCut, float isoCut=0.25);
  };

}
#endif // LeptonDataHandler_H
