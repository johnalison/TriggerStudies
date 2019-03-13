#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/LeptonDataHandler.h"


using namespace NtupleAna;
using namespace std;

void
LeptonDataHandler::SetBranchAddress(TChain* intree){
  SetBranchAddress(intree, m_name+"_num" ,       m_num  );
  SetBranchAddress(intree, m_name+"_pt"  ,        m_pt   );
  SetBranchAddress(intree, m_name+"_eta" ,       m_eta  );
  SetBranchAddress(intree, m_name+"_phi" ,       m_phi  );
  SetBranchAddress(intree, m_name+"_mass",      m_mass );
  SetBranchAddress(intree, m_name+"_SF["+m_name+"_num]",      m_SF);    

  SetBranchAddress(intree, m_name+"_superClusterEta",      m_superClusterEta );
  SetBranchAddress(intree, m_name+"_iso",      m_iso );

  return;
}

void LeptonDataHandler::SetBranchAddress(TChain* intree, std::string brName, int* int_arr){
  if(intree->FindBranch(brName.c_str())){
    intree->SetBranchStatus(brName.c_str(), 1);
    intree->SetBranchAddress(brName.c_str(), int_arr);
  }
  
  return;
}

void LeptonDataHandler::SetBranchAddress(TChain* intree, std::string brName, float* float_arr){
  if(intree->FindBranch(brName.c_str())){
    intree->SetBranchStatus(brName.c_str(), 1);
    intree->SetBranchAddress(brName.c_str(), float_arr);
  }
  
  return;
}



vector<LeptonData> 
LeptonDataHandler::GetLeps(){

  vector<LeptonData> outputLeps;
  for(int iLep = 0; iLep < m_num[0]; ++iLep){

    float thisPt = m_pt[iLep];
    float thisEta = m_eta[iLep];

    float superClusterEta = -1;
    float iso             = -1;

    if(m_isElectrons){
      if(thisPt < 30) continue;
      if(fabs(thisEta) > 2.4) continue;
      superClusterEta = m_superClusterEta[iLep];
      if(fabs(superClusterEta) > 1.4442 && fabs(superClusterEta) < 1.5660) continue;
            

    }else{
      if(thisPt < 20) continue;
      if(fabs(thisEta) > 2.4) continue;
      iso = m_iso[iLep];
      if(iso > 0.25) continue;
    }

    float SF = 1.0;
    if(m_isMC)
      SF = m_SF[iLep];


    outputLeps.push_back(  LeptonData(thisPt,
				      thisEta,
				      m_phi[iLep],
				      m_mass[iLep],
				      superClusterEta,
				      iso,
				      SF
				      )
			   );
    
  }
  return outputLeps;
}


