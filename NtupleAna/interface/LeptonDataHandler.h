// -*- C++ -*-

#if !defined(LeptonDataHandler_H)
#define LeptonDataHandler_H

#include "TriggerStudies/NtupleAna/interface/LeptonData.h"

namespace NtupleAna {


  class LeptonDataHandler {

  public:

    std::string m_name;
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

  public:
    
    LeptonDataHandler(std::string name, bool isMC = true) : m_name(name), m_isMC(isMC)  {
      if(m_name =="offTightElectrons") m_isElectrons = true;
    }

    ~LeptonDataHandler() {}; 

    void SetBranchAddress (TChain* intree);

    std::vector<LeptonData> GetLeps();
  };

}
#endif // LeptonDataHandler_H
