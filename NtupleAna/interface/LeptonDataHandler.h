// -*- C++ -*-

#if !defined(LeptonDataHandler_H)
#define LeptonDataHandler_H

#include "TriggerStudies/NtupleAna/interface/LeptonData.h"

namespace NtupleAna {


  class LeptonDataHandler {

  public:

    std::string m_name;
    static const int maxLength = 40;        

    int  m_num         [1] = { };
    float  m_pt     [maxLength]  = { };
    float  m_eta    [maxLength]  = { };
    float  m_phi    [maxLength]  = { };
    float  m_mass   [maxLength]  = { };

  public:
    
  LeptonDataHandler(std::string name) : m_name(name)  {
      
    }

    ~LeptonDataHandler() {}; 

    void SetBranchAddress (TChain* intree);

    std::vector<LeptonData> GetLeps();
  };

}
#endif // LeptonDataHandler_H
