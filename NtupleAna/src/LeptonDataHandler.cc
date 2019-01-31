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

  if(m_isElectrons){
    intree->SetBranchAddress( (m_name+"_superClusterEta").c_str(),      m_superClusterEta );
  }else{
    intree->SetBranchAddress( (m_name+"_iso").c_str(),      m_iso );
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
    


    outputLeps.push_back(  LeptonData(thisPt,
				      thisEta,
				      m_phi[iLep],
				      m_mass[iLep],
				      superClusterEta,
				      iso
				      )
			   );
    
  }
  return outputLeps;
}


