// -*- C++ -*-

#if !defined(LeptonData_H)
#define LeptonData_H

#include <TLorentzVector.h>

namespace NtupleAna {


  class LeptonData {

  public:
    
    float m_pt   = 0;
    float m_eta  = 0;
    float m_phi  = 0;
    float m_mass = 0;

    TLorentzVector m_vec;


  public:

  LeptonData(float pt, float eta, float phi, float mass) : m_pt(pt), m_eta(eta), m_phi(phi), m_mass(mass) {
      m_vec.SetPtEtaPhiM(pt,eta,phi,mass);
    }; 

    ~LeptonData() {}; 

  };

}
#endif // LeptonData_H
