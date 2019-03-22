
#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/LeptonData.h"
#include "TriggerStudies/NtupleAna/interface/LeptonHists.h"


using namespace std;
using namespace NtupleAna;


LeptonHists::LeptonHists(std::string name, fwlite::TFileService& fs, bool isElectrons) : m_isElectrons(isElectrons) {

  TFileDirectory dir = fs.mkdir(name);
  m_n       = dir.make<TH1F>("n",  ("n  ;N "+name+";Entries").c_str(),  5,-0.5, 4.5);
  m_pt      = dir.make<TH1F>("pt",  "pt  ;P_{T} [GeV];Entries",  100,0, 400);
  m_pt_l    = dir.make<TH1F>("pt_l","pt_l;P_{T} [GeV];Entries",  100,0,1000);
  m_eta     = dir.make<TH1F>("eta","eta;jet #eta;Entries",100,-3,3);
  m_phi     = dir.make<TH1F>("phi","phi;jet #phi;Entries",100,-3.2,3.2);
  m_mass    = dir.make<TH1F>("mass","mass;jet mass [GeV];Entries",100,-1,200);
  m_SF      = dir.make<TH1F>("SF",     "SF;SF;Entries",50,-0.1,2);
  if(m_isElectrons){
    m_superClusterEta      = dir.make<TH1F>("SuperClusterEta",     "SuperClusterEta;SuperClusterEta;Entries",100,-3,3);
  }else{
    m_iso      = dir.make<TH1F>("iso",     "iso;iso;Entries",100,-0.1,1.1);
    m_iso_l    = dir.make<TH1F>("iso_l",   "iso;iso;Entries",100,-0.1,2);
    m_iso_vl    = dir.make<TH1F>("iso_vl",   "iso;iso;Entries",100,-0.1,10);
  }
} 

LeptonHists::~LeptonHists() {} 


void
//LeptonHists::Fill (const JetData* jetPtr){
//  const JetData& jetInfo = (*jetPtr);
LeptonHists::Fill (const LeptonData& lepInfo, float eventWeight){

  m_pt      ->Fill(lepInfo.m_pt      , eventWeight);
  m_pt_l    ->Fill(lepInfo.m_pt      , eventWeight);
  m_eta     ->Fill(lepInfo.m_eta     , eventWeight);
  m_phi     ->Fill(lepInfo.m_phi     , eventWeight);
  m_mass    ->Fill(lepInfo.m_mass    , eventWeight);
  m_SF      ->Fill(lepInfo.m_SF      , eventWeight);
  if(m_isElectrons){
    m_superClusterEta     ->Fill(lepInfo.m_superClusterEta, eventWeight);
  }else{
    m_iso     ->Fill(lepInfo.m_iso, eventWeight);
    m_iso_l     ->Fill(lepInfo.m_iso, eventWeight);
    m_iso_vl     ->Fill(lepInfo.m_iso, eventWeight);
  }

  return;
}

