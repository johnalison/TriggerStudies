#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/JetHists.h"

using namespace std;
using namespace NtupleAna;


JetHists::JetHists(std::string name, fwlite::TFileService& fs) {

  TFileDirectory dir = fs.mkdir(name);
  m_pt      = dir.make<TH1F>("pt",  "pt  ;P_{T} [GeV];Entries",  100,0, 400);
  m_pt_l    = dir.make<TH1F>("pt_l","pt_l;P_{T} [GeV];Entries",  100,0,1000);
  m_eta     = dir.make<TH1F>("eta","eta;jet #eta;Entries",100,-3,3);
  m_phi     = dir.make<TH1F>("phi","phi;jet #phi;Entries",100,-3.2,3.2);
  m_mass    = dir.make<TH1F>("mass","mass;jet mass [GeV];Entries",100,-1,200);
  m_deepcsv = dir.make<TH1F>("deepcsv","deepcsv;deepcsv;Entries",200,0,1);

} 

JetHists::~JetHists() {} 


void
JetHists::Fill (const JetData& jetInfo){

  m_pt      ->Fill(jetInfo.m_pt);
  m_pt_l    ->Fill(jetInfo.m_pt);
  m_eta     ->Fill(jetInfo.m_eta);
  m_phi     ->Fill(jetInfo.m_phi);
  m_mass    ->Fill(jetInfo.m_mass);
  m_deepcsv ->Fill(jetInfo.m_deepcsv);

  return;
}


