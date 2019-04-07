#include "TChain.h"
#include <iostream>
#include "TriggerStudies/NtupleAna/interface/JetDataHandler.h"
#include "TriggerStudies/NtupleAna/interface/JetData.h"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"

using namespace NtupleAna;
using namespace std;



JetDataHandler::JetDataHandler(std::string name, bool loadTrkLevel, bool isMC, std::string SFName) : m_name(name), m_loadTrkLevel(loadTrkLevel), m_isMC(isMC)
{
      
  if(m_isMC){
    if(SFName == "2017"){
      BTagCalibration calib = BTagCalibration("deepcsv", "TriggerStudies/NtupleAna/data/BTagSF2017/DeepCSV_94XSF_V4_B_F.csv");
      
      m_btagCalibrationTool = new BTagCalibrationReader(BTagEntry::OP_RESHAPING,              // 0 is for loose op, 1: medium, 2: tight, 3: discr. reshaping
							"central"      // central systematic type
							);

      m_btagCalibrationTool->load(calib, 
				  BTagEntry::FLAV_B,   // 0 is for b flavour, 1: FLAV_C, 2: FLAV_UDSG
				  "iterativefit"      // measurement type
				  );

      m_btagCalibrationTool->load(calib, 
				  BTagEntry::FLAV_C,   // 0 is for b flavour, 1: FLAV_C, 2: FLAV_UDSG
				  "iterativefit"      // measurement type
				  );


      m_btagCalibrationTool->load(calib, 
				  BTagEntry::FLAV_UDSG,   // 0 is for b flavour, 1: FLAV_C, 2: FLAV_UDSG
				  "iterativefit"      // measurement type
				  );


    }else{
      cout << "JetDataHandler::Warning no scale factors for " << m_name << endl;
    }

  }

}


void
JetDataHandler::SetBranchAddress(TChain* intree){

  SetBranchAddress(intree, m_name+"_num"       ,   m_num  );
  SetBranchAddress(intree, m_name+"_pt"        ,   m_pt  );
  SetBranchAddress(intree, m_name+"_eta"       ,   m_eta  );
  SetBranchAddress(intree, m_name+"_phi"       ,   m_phi  );
  SetBranchAddress(intree, m_name+"_mass"      ,   m_mass  );
  SetBranchAddress(intree, m_name+"_csv"       ,   m_csv  );
  SetBranchAddress(intree, m_name+"_deepcsv"   ,   m_deepcsv  );
  SetBranchAddress(intree, m_name+"_deepcsv_b" ,   m_deepcsv_b  );
  SetBranchAddress(intree, m_name+"_deepcsv_bb",   m_deepcsv_bb  );

  //SetBranchAddress(intree, m_name+"_deepcsvSF["+m_name+"_num]",   m_SF  );
  SetBranchAddress(intree, m_name+"_passesTightLeptVetoID"    , m_passesTightLeptVetoID);
  SetBranchAddress(intree, m_name+"_lepOverlap04Tight"        ,   m_lepOverlap04Tight  );

  
  if(m_loadTrkLevel){
    SetBranchAddress(intree, m_name+"_vertexNTracks"                     , m_vertexNTracks                     );
    SetBranchAddress(intree, m_name+"_vertexMass"                        , m_vertexMass                        );
    SetBranchAddress(intree, m_name+"_vertexJetDeltaR"                   , m_vertexJetDeltaR                   );
    SetBranchAddress(intree, m_name+"_vertexFitProb"                     , m_vertexFitProb                     );
    SetBranchAddress(intree, m_name+"_vertexEnergyRatio"                 , m_vertexEnergyRatio                 );
    SetBranchAddress(intree, m_name+"_vertexCategory"                    , m_vertexCategory                    );
    SetBranchAddress(intree, m_name+"_vertexBoostOverSqrtJetPt"          , m_vertexBoostOverSqrtJetPt          );
    SetBranchAddress(intree, m_name+"_trackJetPt"                        , m_trackJetPt                        );
    SetBranchAddress(intree, m_name+"_trackSumJetEtRatio"                , m_trackSumJetEtRatio                );
    SetBranchAddress(intree, m_name+"_trackSumJetDeltaR"                 , m_trackSumJetDeltaR                 );
    SetBranchAddress(intree, m_name+"_trackSip2dValAboveCharm"           , m_trackSip2dValAboveCharm           );
    SetBranchAddress(intree, m_name+"_trackSip2dSigAboveCharm"           , m_trackSip2dSigAboveCharm           );
    SetBranchAddress(intree, m_name+"_trackSip3dValAboveCharm"           , m_trackSip3dValAboveCharm           );
    SetBranchAddress(intree, m_name+"_trackSip3dSigAboveCharm"           , m_trackSip3dSigAboveCharm           );
    SetBranchAddress(intree, m_name+"_totalMultiplicity"                 , m_totalMultiplicity                 );
    SetBranchAddress(intree, m_name+"_photonMultiplicity"                , m_photonMultiplicity                );
    SetBranchAddress(intree, m_name+"_photonEnergyFraction"              , m_photonEnergyFraction              );
    SetBranchAddress(intree, m_name+"_neutralHadronMultiplicity"         , m_neutralHadronMultiplicity         );
    SetBranchAddress(intree, m_name+"_neutralHadronEnergyFraction"       , m_neutralHadronEnergyFraction       );

    SetBranchAddress(intree, m_name+"_neMult"                            , m_neMult                            );
    SetBranchAddress(intree, m_name+"_neHadEF"                           , m_neHadEF                           );
    SetBranchAddress(intree, m_name+"_neEmEF"                            , m_neEmEF                            );
    SetBranchAddress(intree, m_name+"_mult"                              , m_mult                              );
    SetBranchAddress(intree, m_name+"_muEF"                              , m_muEF                              );
    SetBranchAddress(intree, m_name+"_chMult"                            , m_chMult                            );
    SetBranchAddress(intree, m_name+"_chHadEF"                           , m_chHadEF                           );
    SetBranchAddress(intree, m_name+"_chEmEF"                            , m_chEmEF                            );
    SetBranchAddress(intree, m_name+"_muonMultiplicity"                  , m_muonMultiplicity                  );
    SetBranchAddress(intree, m_name+"_muonEnergyFraction"                , m_muonEnergyFraction                );
    SetBranchAddress(intree, m_name+"_massVertexEnergyFraction"          , m_massVertexEnergyFraction          );
    SetBranchAddress(intree, m_name+"_jetNTracksEtaRel"                  , m_jetNTracksEtaRel                  );
    SetBranchAddress(intree, m_name+"_jetNTracks"                        , m_jetNTracks                        );
    SetBranchAddress(intree, m_name+"_jetNSelectedTracks"                , m_jetNSelectedTracks                );
    SetBranchAddress(intree, m_name+"_jetNSecondaryVertices"             , m_jetNSecondaryVertices             );
    SetBranchAddress(intree, m_name+"_hadronPhotonMultiplicity"          , m_hadronPhotonMultiplicity          );
    SetBranchAddress(intree, m_name+"_hadronMultiplicity"                , m_hadronMultiplicity                );
    SetBranchAddress(intree, m_name+"_flightDistance1dSig"               , m_flightDistance1dSig               );
    SetBranchAddress(intree, m_name+"_flightDistance1dVal"               , m_flightDistance1dVal               );
    SetBranchAddress(intree, m_name+"_flightDistance2dSig"               , m_flightDistance2dSig               );
    SetBranchAddress(intree, m_name+"_flightDistance2dVal"               , m_flightDistance2dVal               );
    SetBranchAddress(intree, m_name+"_flightDistance3dSig"               , m_flightDistance3dSig               );
    SetBranchAddress(intree, m_name+"_flightDistance3dVal"               , m_flightDistance3dVal               );
    SetBranchAddress(intree, m_name+"_chargedHadronMultiplicity"         , m_chargedHadronMultiplicity         );
    SetBranchAddress(intree, m_name+"_chargedHadronEnergyFraction"       , m_chargedHadronEnergyFraction       );

    SetBranchAddress(intree, m_name+"_trackSip3dSig", &m_trackSip3dSig);
    SetBranchAddress(intree, m_name+"_trackSip3dSig", &m_trackSip3dSig);
    SetBranchAddress(intree, m_name+"_trackSip3dVal", &m_trackSip3dVal);
    SetBranchAddress(intree, m_name+"_trackSip2dSig", &m_trackSip2dSig);
    SetBranchAddress(intree, m_name+"_trackSip2dVal", &m_trackSip2dVal);
  			    
    SetBranchAddress(intree, m_name+"_trackDecayLenVal"           , &m_trackDecayLenVal           );
//  SetBranchAddress(intree, m_name+"_trackDecayLenSig"           , &m_trackDecayLenSig           );
    SetBranchAddress(intree, m_name+"_trackJetDistVal"            , &m_trackJetDistVal            );
    SetBranchAddress(intree, m_name+"_trackJetDistSig"            , &m_trackJetDistSig            );
//  SetBranchAddress(intree, m_name+"_trackGhostTrackWeight"      , &m_trackGhostTrackWeight      );
//  SetBranchAddress(intree, m_name+"_trackGhostTrackDistSig"     , &m_trackGhostTrackDistSig     );
//  SetBranchAddress(intree, m_name+"_trackGhostTrackDistVal"     , &m_trackGhostTrackDistVal     );
    SetBranchAddress(intree, m_name+"_trackPtRel"                 , &m_trackPtRel                 );
    SetBranchAddress(intree, m_name+"_trackMomentum"              , &m_trackMomentum              );
    SetBranchAddress(intree, m_name+"_trackEta"                   , &m_trackEta                   );
    SetBranchAddress(intree, m_name+"_trackPhi"                   , &m_trackPhi                   );
//  SetBranchAddress(intree, m_name+"_trackCharge"                , &m_trackCharge                );
    SetBranchAddress(intree, m_name+"_trackPPar"                  , &m_trackPPar                  );
    SetBranchAddress(intree, m_name+"_trackDeltaR"                , &m_trackDeltaR                );
    SetBranchAddress(intree, m_name+"_trackEtaRel"                , &m_trackEtaRel                );
    SetBranchAddress(intree, m_name+"_trackPtRatio"               , &m_trackPtRatio               );
    SetBranchAddress(intree, m_name+"_trackPParRatio"             , &m_trackPParRatio             );
//  SetBranchAddress(intree, m_name+"_trackP0Par"                 , &m_trackP0Par                 );
//  SetBranchAddress(intree, m_name+"_trackP0ParRatio"            , &m_trackP0ParRatio            );
    SetBranchAddress(intree, m_name+"_trackChi2"                  , &m_trackChi2                  );
    SetBranchAddress(intree, m_name+"_trackNTotalHits"            , &m_trackNTotalHits            );
    SetBranchAddress(intree, m_name+"_trackNPixelHits"            , &m_trackNPixelHits            );
  
  }
  

  SetBranchAddress(intree, m_name+"_partonFlavour"                            , m_partonFlavour                            );
  SetBranchAddress(intree, m_name+"_hadronFlavour"                            , m_hadronFlavour                            );

  return;
}


void JetDataHandler::SetBranchAddress(TChain* intree, std::string brName, int* int_arr){
  if(intree->FindBranch(brName.c_str())){
    intree->SetBranchStatus(brName.c_str(), 1);
    intree->SetBranchAddress(brName.c_str(), int_arr);
  }else{
    std::cout << "JetDataHandler::Cant find branch " << brName << std::endl;
  }
  
  return;
}

void JetDataHandler::SetBranchAddress(TChain* intree, std::string brName, float* float_arr){
  if(intree->FindBranch(brName.c_str())){
    intree->SetBranchStatus(brName.c_str(), 1);
    intree->SetBranchAddress(brName.c_str(), float_arr);
  }else{
    std::cout << "JetDataHandler::Cant find branch " << brName << std::endl;
  }
  
  return;
}

void JetDataHandler::SetBranchAddress(TChain* intree, std::string brName, std::vector<std::vector<float> >** vector_ptr){
  if(intree->FindBranch(brName.c_str())){
    intree->SetBranchStatus(brName.c_str(), 1);
    intree->SetBranchAddress( brName.c_str(), vector_ptr);
  }else{
    std::cout << "JetDataHandler::Cant find branch " << brName << std::endl;
  }
  
  return;
}


float 
JetDataHandler::getSF(float jetEta,  float jetPt,  float jetDeepCSV, int jetHadronFlavour){ 
  if(fabs(jetHadronFlavour) == 5){
    return m_btagCalibrationTool->eval_auto_bounds("central", BTagEntry::FLAV_B, fabs(jetEta), jetPt, jetDeepCSV);
  }else if(fabs(jetHadronFlavour) == 4){
    return m_btagCalibrationTool->eval_auto_bounds("central", BTagEntry::FLAV_C, fabs(jetEta), jetPt, jetDeepCSV);
  }

  return m_btagCalibrationTool->eval_auto_bounds("central", BTagEntry::FLAV_UDSG, fabs(jetEta), jetPt, jetDeepCSV);
}


vector<JetData> 
JetDataHandler::GetJetsAll(){

  vector<JetData> outputJets;
  for(int iJet = 0; iJet < m_num[0]; ++iJet){
    float SF = 1.0;
    if(m_isMC && m_btagCalibrationTool){
      SF = getSF(m_eta[iJet], m_pt[iJet], m_deepcsv[iJet], m_hadronFlavour[iJet]);
    }

    outputJets.push_back(  JetData(m_pt[iJet], 
				   m_eta[iJet],
				   m_phi[iJet],
				   m_mass[iJet],
				   m_csv[iJet],
				   m_deepcsv[iJet],
				   m_deepcsv_b[iJet],
				   m_deepcsv_bb[iJet],
				   SF,
				   m_passesTightLeptVetoID[iJet],
				   m_lepOverlap04Tight[iJet],
                                   m_vertexNTracks                     [iJet],
                                   m_vertexMass                        [iJet],
                                   m_vertexJetDeltaR                   [iJet],
                                   m_vertexFitProb                     [iJet],
                                   m_vertexEnergyRatio                 [iJet],
                                   m_vertexCategory                    [iJet],
                                   m_vertexBoostOverSqrtJetPt          [iJet],
                                   m_trackJetPt                        [iJet],
                                   m_trackSumJetEtRatio                [iJet],
                                   m_trackSumJetDeltaR                 [iJet],
                                   m_trackSip2dValAboveCharm           [iJet],
                                   m_trackSip2dSigAboveCharm           [iJet],
                                   m_trackSip3dValAboveCharm           [iJet],
                                   m_trackSip3dSigAboveCharm           [iJet],
                                   m_totalMultiplicity                 [iJet],
                                   m_photonMultiplicity                [iJet],
                                   m_photonEnergyFraction              [iJet],
                                   m_neutralHadronMultiplicity         [iJet],
                                   m_neutralHadronEnergyFraction       [iJet],
                                   m_neMult                            [iJet],
                                   m_neHadEF                           [iJet],
                                   m_neEmEF                            [iJet],
                                   m_muonMultiplicity                  [iJet],
                                   m_muonEnergyFraction                [iJet],
                                   m_mult                              [iJet],
                                   m_muEF                              [iJet],
                                   m_massVertexEnergyFraction          [iJet],
                                   m_jetNTracksEtaRel                  [iJet],
                                   m_jetNTracks                        [iJet],
                                   m_jetNSelectedTracks                [iJet],
                                   m_jetNSecondaryVertices             [iJet],
                                   m_hadronPhotonMultiplicity          [iJet],
                                   m_hadronMultiplicity                [iJet],
                                   m_flightDistance1dSig               [iJet],
                                   m_flightDistance1dVal               [iJet],
                                   m_flightDistance2dSig               [iJet],
                                   m_flightDistance2dVal               [iJet],
                                   m_flightDistance3dSig               [iJet],
                                   m_flightDistance3dVal               [iJet],
                                   m_chargedHadronMultiplicity         [iJet],
                                   m_chargedHadronEnergyFraction       [iJet],
                                   m_chMult                            [iJet],
                                   m_chHadEF                           [iJet],
                                   m_chEmEF                            [iJet],
                                   m_partonFlavour                     [iJet],
                                   m_hadronFlavour                     [iJet],
                                   m_trackSip3dSig->at(iJet),
                                   m_trackSip3dVal->at(iJet),
                                   m_trackSip2dSig->at(iJet),
                                   m_trackSip2dVal->at(iJet),
				   
                                   m_trackDecayLenVal           ->at(iJet),
                                   //m_trackDecayLenSig           ->at(iJet),
                                   m_trackJetDistVal            ->at(iJet),
                                   m_trackJetDistSig            ->at(iJet),
                                   //m_trackGhostTrackWeight      ->at(iJet),
                                   //m_trackGhostTrackDistSig     ->at(iJet),
                                   //m_trackGhostTrackDistVal     ->at(iJet),
                                   m_trackPtRel                 ->at(iJet),
                                   m_trackMomentum              ->at(iJet),
                                   m_trackEta                   ->at(iJet),
                                   m_trackPhi                   ->at(iJet),
                                   //m_trackCharge                ->at(iJet),
                                   m_trackPPar                  ->at(iJet),
                                   m_trackDeltaR                ->at(iJet),
                                   m_trackEtaRel                ->at(iJet),
                                   m_trackPtRatio               ->at(iJet),
                                   m_trackPParRatio             ->at(iJet),
                                   //m_trackP0Par                 ->at(iJet),
                                   //m_trackP0ParRatio            ->at(iJet),
                                   m_trackChi2                  ->at(iJet),
                                   m_trackNTotalHits            ->at(iJet),
                                   m_trackNPixelHits            ->at(iJet)
				   )
			   );
  }
  return outputJets;
}


vector<JetData> 
JetDataHandler::GetJetsNoTrks(){

  std::vector<float> nullVector;

  vector<JetData> outputJets;
  for(int iJet = 0; iJet < m_num[0]; ++iJet){
    float SF = 1.0;
    if(m_isMC && m_btagCalibrationTool){
      SF = getSF(m_eta[iJet], m_pt[iJet], m_deepcsv[iJet], m_hadronFlavour[iJet]);
    }
    outputJets.push_back(  JetData(m_pt[iJet], 
				   m_eta[iJet],
				   m_phi[iJet],
				   m_mass[iJet],
				   m_csv[iJet],
				   m_deepcsv[iJet],
				   m_deepcsv_b[iJet],
				   m_deepcsv_bb[iJet],
				   SF,
				   m_passesTightLeptVetoID[iJet],
				   m_lepOverlap04Tight[iJet],
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   -1,
                                   m_partonFlavour                     [iJet],
                                   m_hadronFlavour                     [iJet],
                                   nullVector,
                                   nullVector,
                                   nullVector,
                                   nullVector,
				   
                                   nullVector,
                                 //nullVector,
                                   nullVector,
                                   nullVector,
                                 //nullVector,
                                 //nullVector,
                                 //nullVector,
                                   nullVector,
                                   nullVector,
                                   nullVector,
                                   nullVector,
                                 //nullVector,
                                   nullVector,
                                   nullVector,
                                   nullVector,
                                   nullVector,
                                   nullVector,
                                 //nullVector,
                                 //nullVector,
                                   nullVector,
                                   nullVector,
                                   nullVector
				   )
			   );
   }
   return outputJets;

}

vector<JetData> 
JetDataHandler::GetJets(){

  if(m_loadTrkLevel) return this->GetJetsAll();
  
  return this->GetJetsNoTrks();
}
