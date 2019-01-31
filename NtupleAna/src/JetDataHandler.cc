#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/JetDataHandler.h"
#include "TriggerStudies/NtupleAna/interface/JetData.h"

using namespace NtupleAna;
using namespace std;

void
JetDataHandler::SetBranchAddress(TChain* intree){

  intree->SetBranchAddress( (m_name+"_num"       ).c_str(),   m_num  );
  intree->SetBranchAddress( (m_name+"_pt"        ).c_str(),   m_pt  );
  intree->SetBranchAddress( (m_name+"_eta"       ).c_str(),   m_eta  );
  intree->SetBranchAddress( (m_name+"_phi"       ).c_str(),   m_phi  );
  intree->SetBranchAddress( (m_name+"_mass"      ).c_str(),   m_mass  );
  intree->SetBranchAddress( (m_name+"_csv"       ).c_str(),   m_csv  );
  intree->SetBranchAddress( (m_name+"_deepcsv"   ).c_str(),   m_deepcsv  );
  intree->SetBranchAddress( (m_name+"_deepcsv_bb").c_str(),   m_deepcsv_bb  );
  if(m_name != "caloJets")
    intree->SetBranchAddress( (m_name+"_passesTightLeptVetoID").c_str(), m_passesTightLeptVetoID);
  if(m_name == "offJets")
    intree->SetBranchAddress( (m_name+"_lepOverlap04Tight").c_str(),   m_lepOverlap04Tight  );

  
  if(m_loadTrkLevel){
    intree->SetBranchAddress( (m_name+"_vertexNTracks"                ).c_str()     , m_vertexNTracks                     );
    intree->SetBranchAddress( (m_name+"_vertexMass"                   ).c_str()     , m_vertexMass                        );
    intree->SetBranchAddress( (m_name+"_vertexJetDeltaR"              ).c_str()     , m_vertexJetDeltaR                   );
    intree->SetBranchAddress( (m_name+"_vertexFitProb"                ).c_str()     , m_vertexFitProb                     );
    intree->SetBranchAddress( (m_name+"_vertexEnergyRatio"            ).c_str()     , m_vertexEnergyRatio                 );
    intree->SetBranchAddress( (m_name+"_vertexCategory"               ).c_str()     , m_vertexCategory                    );
    intree->SetBranchAddress( (m_name+"_vertexBoostOverSqrtJetPt"     ).c_str()     , m_vertexBoostOverSqrtJetPt          );
    intree->SetBranchAddress( (m_name+"_trackJetPt"                   ).c_str()     , m_trackJetPt                        );
    intree->SetBranchAddress( (m_name+"_trackSumJetEtRatio"           ).c_str()     , m_trackSumJetEtRatio                );
    intree->SetBranchAddress( (m_name+"_trackSumJetDeltaR"            ).c_str()     , m_trackSumJetDeltaR                 );
    intree->SetBranchAddress( (m_name+"_trackSip2dValAboveCharm"      ).c_str()     , m_trackSip2dValAboveCharm           );
    intree->SetBranchAddress( (m_name+"_trackSip2dSigAboveCharm"      ).c_str()     , m_trackSip2dSigAboveCharm           );
    intree->SetBranchAddress( (m_name+"_trackSip3dValAboveCharm"      ).c_str()     , m_trackSip3dValAboveCharm           );
    intree->SetBranchAddress( (m_name+"_trackSip3dSigAboveCharm"      ).c_str()     , m_trackSip3dSigAboveCharm           );
    intree->SetBranchAddress( (m_name+"_totalMultiplicity"            ).c_str()     , m_totalMultiplicity                 );
    intree->SetBranchAddress( (m_name+"_photonMultiplicity"           ).c_str()     , m_photonMultiplicity                );
    intree->SetBranchAddress( (m_name+"_photonEnergyFraction"         ).c_str()     , m_photonEnergyFraction              );
    intree->SetBranchAddress( (m_name+"_neutralHadronMultiplicity"    ).c_str()     , m_neutralHadronMultiplicity         );
    intree->SetBranchAddress( (m_name+"_neutralHadronEnergyFraction"  ).c_str()     , m_neutralHadronEnergyFraction       );
    if(m_name != "caloJets"){
      intree->SetBranchAddress( (m_name+"_neMult"  ).c_str()                          , m_neMult                            );
      intree->SetBranchAddress( (m_name+"_neHadEF" ).c_str()                          , m_neHadEF                           );
      intree->SetBranchAddress( (m_name+"_neEmEF"  ).c_str()                          , m_neEmEF                            );
      intree->SetBranchAddress( (m_name+"_mult"    ).c_str()                          , m_mult                              );
      intree->SetBranchAddress( (m_name+"_muEF"    ).c_str()                          , m_muEF                              );
      intree->SetBranchAddress( (m_name+"_chMult"  ).c_str()                          , m_chMult                            );
      intree->SetBranchAddress( (m_name+"_chHadEF" ).c_str()                          , m_chHadEF                           );
      intree->SetBranchAddress( (m_name+"_chEmEF"  ).c_str()                          , m_chEmEF                            );
    }

    intree->SetBranchAddress( (m_name+"_muonMultiplicity"           ).c_str()       , m_muonMultiplicity                  );
    intree->SetBranchAddress( (m_name+"_muonEnergyFraction"         ).c_str()       , m_muonEnergyFraction                );
    intree->SetBranchAddress( (m_name+"_massVertexEnergyFraction"   ).c_str()       , m_massVertexEnergyFraction          );
    intree->SetBranchAddress( (m_name+"_jetNTracksEtaRel"           ).c_str()       , m_jetNTracksEtaRel                  );
    intree->SetBranchAddress( (m_name+"_jetNTracks"                 ).c_str()       , m_jetNTracks                        );
    intree->SetBranchAddress( (m_name+"_jetNSelectedTracks"         ).c_str()       , m_jetNSelectedTracks                );
    intree->SetBranchAddress( (m_name+"_jetNSecondaryVertices"      ).c_str()       , m_jetNSecondaryVertices             );
    intree->SetBranchAddress( (m_name+"_hadronPhotonMultiplicity"   ).c_str()       , m_hadronPhotonMultiplicity          );
    intree->SetBranchAddress( (m_name+"_hadronMultiplicity"         ).c_str()       , m_hadronMultiplicity                );
    intree->SetBranchAddress( (m_name+"_flightDistance1dSig"        ).c_str()       , m_flightDistance1dSig               );
    intree->SetBranchAddress( (m_name+"_flightDistance1dVal"        ).c_str()       , m_flightDistance1dVal               );
    intree->SetBranchAddress( (m_name+"_flightDistance2dSig"        ).c_str()       , m_flightDistance2dSig               );
    intree->SetBranchAddress( (m_name+"_flightDistance2dVal"        ).c_str()       , m_flightDistance2dVal               );
    intree->SetBranchAddress( (m_name+"_flightDistance3dSig"        ).c_str()       , m_flightDistance3dSig               );
    intree->SetBranchAddress( (m_name+"_flightDistance3dVal"        ).c_str()       , m_flightDistance3dVal               );
    intree->SetBranchAddress( (m_name+"_chargedHadronMultiplicity"  ).c_str()       , m_chargedHadronMultiplicity         );
    intree->SetBranchAddress( (m_name+"_chargedHadronEnergyFraction").c_str()       , m_chargedHadronEnergyFraction       );

    intree->SetBranchAddress( (m_name+"_trackSip3dSig").c_str(), &m_trackSip3dSig);
    intree->SetBranchAddress( (m_name+"_trackSip3dVal").c_str(), &m_trackSip3dVal);
    intree->SetBranchAddress( (m_name+"_trackSip2dSig").c_str(), &m_trackSip2dSig);
    intree->SetBranchAddress( (m_name+"_trackSip2dVal").c_str(), &m_trackSip2dVal);
  			    
    intree->SetBranchAddress( (m_name+"_trackDecayLenVal").c_str()           , &m_trackDecayLenVal           );
    //intree->SetBranchAddress( (m_name+"_trackDecayLenSig").c_str()           , &m_trackDecayLenSig           );
    intree->SetBranchAddress( (m_name+"_trackJetDistVal").c_str()            , &m_trackJetDistVal            );
    intree->SetBranchAddress( (m_name+"_trackJetDistSig").c_str()            , &m_trackJetDistSig            );
    //intree->SetBranchAddress( (m_name+"_trackGhostTrackWeight").c_str()      , &m_trackGhostTrackWeight      );
    //intree->SetBranchAddress( (m_name+"_trackGhostTrackDistSig").c_str()     , &m_trackGhostTrackDistSig     );
    //intree->SetBranchAddress( (m_name+"_trackGhostTrackDistVal").c_str()     , &m_trackGhostTrackDistVal     );
    intree->SetBranchAddress( (m_name+"_trackPtRel").c_str()                 , &m_trackPtRel                 );
    intree->SetBranchAddress( (m_name+"_trackMomentum").c_str()              , &m_trackMomentum              );
    intree->SetBranchAddress( (m_name+"_trackEta").c_str()                   , &m_trackEta                   );
    intree->SetBranchAddress( (m_name+"_trackPhi").c_str()                   , &m_trackPhi                   );
    //intree->SetBranchAddress( (m_name+"_trackCharge").c_str()                , &m_trackCharge                );
    intree->SetBranchAddress( (m_name+"_trackPPar").c_str()                  , &m_trackPPar                  );
    intree->SetBranchAddress( (m_name+"_trackDeltaR").c_str()                , &m_trackDeltaR                );
    intree->SetBranchAddress( (m_name+"_trackEtaRel").c_str()                , &m_trackEtaRel                );
    intree->SetBranchAddress( (m_name+"_trackPtRatio").c_str()               , &m_trackPtRatio               );
    intree->SetBranchAddress( (m_name+"_trackPParRatio").c_str()             , &m_trackPParRatio             );
    //intree->SetBranchAddress( (m_name+"_trackP0Par").c_str()                 , &m_trackP0Par                 );
    //intree->SetBranchAddress( (m_name+"_trackP0ParRatio").c_str()            , &m_trackP0ParRatio            );
    intree->SetBranchAddress( (m_name+"_trackChi2").c_str()                  , &m_trackChi2                  );
    intree->SetBranchAddress( (m_name+"_trackNTotalHits").c_str()            , &m_trackNTotalHits            );
    intree->SetBranchAddress( (m_name+"_trackNPixelHits").c_str()            , &m_trackNPixelHits            );
  
  }
  
  if(m_name == "offJets"){
    intree->SetBranchAddress( (m_name+"_partonFlavour").c_str()                            , m_partonFlavour                            );
    intree->SetBranchAddress( (m_name+"_hadronFlavour").c_str()                            , m_hadronFlavour                            );
  }


  

  return;
}

vector<JetData> 
JetDataHandler::GetJetsAll(){

  vector<JetData> outputJets;
  for(int iJet = 0; iJet < m_num[0]; ++iJet){
    outputJets.push_back(  JetData(m_pt[iJet], 
				   m_eta[iJet],
				   m_phi[iJet],
				   m_mass[iJet],
				   m_csv[iJet],
				   m_deepcsv[iJet],
				   m_deepcsv_bb[iJet],
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
    outputJets.push_back(  JetData(m_pt[iJet], 
				   m_eta[iJet],
				   m_phi[iJet],
				   m_mass[iJet],
				   m_csv[iJet],
				   m_deepcsv[iJet],
				   m_deepcsv_bb[iJet],
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
