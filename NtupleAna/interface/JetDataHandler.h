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


  public:

  JetDataHandler(std::string name) : m_name(name)  {
      
    }

    ~JetDataHandler() { }; 


    void SetBranchAddress(TChain* intree);
    std::vector<JetData> GetJets();
    
  };

}
#endif // JetDataHandler_H
