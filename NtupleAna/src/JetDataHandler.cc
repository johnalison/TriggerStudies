#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/JetDataHandler.h"


using namespace NtupleAna;
using namespace std;

void
JetDataHandler::SetBranchAddress(TChain* intree){

  intree->SetBranchAddress( (m_name+"_num"       ).c_str(),   m_num  );
  intree->SetBranchAddress( (m_name+"_pt"        ).c_str(),   m_pt  );
  intree->SetBranchAddress( (m_name+"_eta"       ).c_str(),   m_eta  );
  intree->SetBranchAddress( (m_name+"_phi"       ).c_str(),   m_phi  );
  intree->SetBranchAddress( (m_name+"_mass"      ).c_str(),   m_mass  );
  intree->SetBranchAddress( (m_name+"_deepcsv"   ).c_str(),   m_deepcsv  );
  intree->SetBranchAddress( (m_name+"_deepcsv_bb").c_str(),   m_deepcsv_bb  );
  
  return;
}


vector<JetData> 
JetDataHandler::GetJets(){

  vector<JetData> outputJets;
  for(int iJet = 0; iJet < m_num[0]; ++iJet){
    outputJets.push_back(  JetData(m_pt[iJet], 
				   m_eta[iJet],
				   m_phi[iJet],
				   m_mass[iJet],
				   m_deepcsv[iJet],
				   m_deepcsv_bb[iJet]
				   )
			   );
    
  }
  return outputJets;
}
