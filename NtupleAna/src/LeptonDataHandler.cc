#include "TChain.h"
#include <iostream> 
#include "TriggerStudies/NtupleAna/interface/LeptonDataHandler.h"


using namespace NtupleAna;
using namespace std;

LeptonDataHandler::LeptonDataHandler(std::string name, std::string year, bool isMC) : m_name(name), m_year(year), m_isMC(isMC) {
  if(m_name =="offTightElectrons") 
    m_isElectrons = true;

  

  if(m_isMC){
    if(!m_isElectrons && m_year == "2017"){

      m_SFFile1 = new TFile("TriggerStudies/NtupleAna/data/MuonSF2017/RunBCDEF_SF_ID.root","READ");
      m_SFHist1 = (TH2D*)m_SFFile1->Get("NUM_TightID_DEN_genTracks_pt_abseta");
      
      m_SFFile2 = new TFile("TriggerStudies/NtupleAna/data/MuonSF2017/RunBCDEF_SF_ISO.root","READ");
      m_SFHist2 = (TH2D*)m_SFFile2->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

    }else if(!m_isElectrons && m_year == "2018"){

      m_SFFile1 = new TFile("TriggerStudies/NtupleAna/data/MuonSF2018/RunABCD_SF_ID.root","READ");
      m_SFHist1 = (TH2D*)m_SFFile1->Get("NUM_TightID_DEN_TrackerMuons_pt_abseta");
      
      m_SFFile2 = new TFile("TriggerStudies/NtupleAna/data/MuonSF2018/RunABCD_SF_ISO.root","READ");
      m_SFHist2 = (TH2D*)m_SFFile2->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");


    }else if(m_isElectrons && m_year == "2017"){

      m_SFFile1 = new TFile("TriggerStudies/NtupleAna/data/ElecSF2017/egammaEffi.txt_EGM2D_runBCDEF_passingTight94X.root","READ");
      m_SFHist1 = (TH2D*)m_SFFile1->Get("EGamma_SF2D");
      
      m_SFFile2 = new TFile("TriggerStudies/NtupleAna/data/ElecSF2017/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root","READ");
      m_SFHist2 = (TH2D*)m_SFFile2->Get("EGamma_SF2D");

    }else if(m_isElectrons && m_year == "2018"){

      m_SFFile1 = new TFile("TriggerStudies/NtupleAna/data/ElecSF2017/2018_ElectronTight.root","READ");
      m_SFHist1 = (TH2D*)m_SFFile1->Get("EGamma_SF2D");
      
      m_SFFile2 = new TFile("TriggerStudies/NtupleAna/data/ElecSF2017/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root","READ");
      m_SFHist2 = (TH2D*)m_SFFile2->Get("EGamma_SF2D");

      
    }else {
      cout << "LeptonDataHandler::Warning no scale factors for " << m_name << " year " << m_year << endl;
    }


    if(!m_SFHist1 || !m_SFHist2){
      cout << "LeptonDataHandler::Scale Factors Not loaded for " << m_name << " year " << m_year << endl;
    }
  }

  
}



void
LeptonDataHandler::SetBranchAddress(TChain* intree){
  SetBranchAddress(intree, m_name+"_num" ,       m_num  );
  SetBranchAddress(intree, m_name+"_pt"  ,        m_pt   );
  SetBranchAddress(intree, m_name+"_eta" ,       m_eta  );
  SetBranchAddress(intree, m_name+"_phi" ,       m_phi  );
  SetBranchAddress(intree, m_name+"_mass",      m_mass );
  //SetBranchAddress(intree, m_name+"_SF["+m_name+"_num]",      m_SF);    

  SetBranchAddress(intree, m_name+"_superClusterEta",      m_superClusterEta );
  SetBranchAddress(intree, m_name+"_iso",      m_iso );

  return;
}

void LeptonDataHandler::SetBranchAddress(TChain* intree, std::string brName, int* int_arr){
  if(intree->FindBranch(brName.c_str())){
    intree->SetBranchStatus(brName.c_str(), 1);
    intree->SetBranchAddress(brName.c_str(), int_arr);
  }else{
    std::cout << "LeptonDataHandler::Cant find branch " << brName << std::endl;
  }
  
  return;
}

void LeptonDataHandler::SetBranchAddress(TChain* intree, std::string brName, float* float_arr){
  if(intree->FindBranch(brName.c_str())){
    intree->SetBranchStatus(brName.c_str(), 1);
    intree->SetBranchAddress(brName.c_str(), float_arr);
  }else{
    std::cout << "LeptonDataHandler::Cant find branch " << brName << std::endl;
  }
  
  return;
}



vector<LeptonData> 
LeptonDataHandler::GetLeps(float ptCut, float isoCut){

  vector<LeptonData> outputLeps;
  for(int iLep = 0; iLep < m_num[0]; ++iLep){

    float thisPt = m_pt[iLep];
    float thisEta = m_eta[iLep];

    float superClusterEta = -1;
    float iso             = -1;

    if(m_isElectrons){
      if(thisPt < ptCut) continue;
      if(fabs(thisEta) > 2.4) continue;
      superClusterEta = m_superClusterEta[iLep];
      if(fabs(superClusterEta) > 1.4442 && fabs(superClusterEta) < 1.5660) continue;
            

    }else{
      if(thisPt < ptCut) continue;
      if(fabs(thisEta) > 2.4) continue;
      iso = m_iso[iLep];
      if(iso > isoCut) continue;
    }

    //
    // Calculate the SF
    //
    float SF = 1.0;
    if(m_isMC){
      if(m_isElectrons){
	if(m_SFHist1)
	  SF *= m_SFHist1->GetBinContent(m_SFHist1->FindBin(superClusterEta, thisPt));
	if(m_SFHist2)
	  SF *= m_SFHist2->GetBinContent(m_SFHist2->FindBin(superClusterEta, thisPt));

      }else{
	if(m_SFHist1)
	  SF *= m_SFHist1->GetBinContent(m_SFHist1->FindBin(thisPt,fabs(thisEta)));
	if(m_SFHist2)
	  SF *= m_SFHist2->GetBinContent(m_SFHist2->FindBin(thisPt,fabs(thisEta)));
      }
    }

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


