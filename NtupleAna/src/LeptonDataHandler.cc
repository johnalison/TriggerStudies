#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/LeptonDataHandler.h"


using namespace NtupleAna;
using namespace std;

void
LeptonDataHandler::SetBranchAddress(TChain* intree){
  intree->SetBranchAddress( (m_name+"_num" ).c_str(),       m_num  );
  intree->SetBranchAddress( (m_name+"_pt"  ).c_str(),        m_pt   );
  intree->SetBranchAddress( (m_name+"_eta" ).c_str(),       m_eta  );
  intree->SetBranchAddress( (m_name+"_phi" ).c_str(),       m_phi  );
  intree->SetBranchAddress( (m_name+"_mass").c_str(),      m_mass );

  
  return;
}



vector<LeptonData> 
LeptonDataHandler::GetLeps(){

  vector<LeptonData> outputLeps;
  for(int iLep = 0; iLep < m_num[0]; ++iLep){
    outputLeps.push_back(  LeptonData(m_pt[iLep], 
				      m_eta[iLep],
				      m_phi[iLep],
				      m_mass[iLep]
				      )
			   );
    
  }
  return outputLeps;
}


