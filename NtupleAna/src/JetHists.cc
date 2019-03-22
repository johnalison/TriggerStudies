
#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/JetData.h"
#include "TriggerStudies/NtupleAna/interface/JetHists.h"


using namespace std;
using namespace NtupleAna;


JetHists::JetHists(std::string name, fwlite::TFileService& fs, bool light) {

  TFileDirectory dir = fs.mkdir(name);
  m_pt      = dir.make<TH1F>("pt",  "pt  ;P_{T} [GeV];Entries",  100,0, 400);
  m_pt_l    = dir.make<TH1F>("pt_l","pt_l;P_{T} [GeV];Entries",  100,0,1000);
  m_eta     = dir.make<TH1F>("eta","eta;jet #eta;Entries",100,-3,3);
  m_phi     = dir.make<TH1F>("phi","phi;jet #phi;Entries",100,-3.2,3.2);
  m_mass    = dir.make<TH1F>("mass","mass;jet mass [GeV];Entries",100,-1,200);
  m_csv     = dir.make<TH1F>("csv","csv;csv;Entries",140,-0.2,1.2);
  m_deepcsv = dir.make<TH1F>("deepcsv","deepcsv;deepcsv;Entries",140,-0.2,1.2);
  m_SF      = dir.make<TH1F>("SF",     "SF;SF;Entries",50,-0.1,2);

  m_matched_dPt      = dir.make<TH1F>("matched_dPt",     "matched_dPt     ;P_{T}-P_{T}^{matched} [GeV];Entries",  100,-50, 50);
  m_matched_dEta     = dir.make<TH1F>("matched_dEta",    "matched_dEta    ;#eta-#eta^{matched};Entries",100,-0.5,0.5);
  m_matched_dPhi     = dir.make<TH1F>("matched_dPhi",    "matched_dPhi    ;#phi-#phi^{matched};Entries",100,-0.5,0.5);
  m_matched_dR       = dir.make<TH1F>("matched_dR",      "matched_dR      ;#DeltaR(Online,Offline);;Entries",45, 0,0.45);
  m_matched_dMass    = dir.make<TH1F>("matched_dMass",   "matched_dMass   ;mass-mass^{matched} [GeV];Entries",100,-50,50);
  m_matched_dcsv     = dir.make<TH1F>("matched_dcsv","matched_dcsv;CSV-CSV^{matched};Entries",100,-1,1);
  m_matched_dDeepcsv = dir.make<TH1F>("matched_dDeepcsv","matched_dDeepcsv;DeepCSV-DeepCSV^{matched};Entries",100,-1,1);
  
  m_csv_matched = dir.make<TH1F>("csv_matched","csv;csv;Entries",140,-0.2,1.2);
  m_csv_vs_matched_csv = dir.make<TH2F>("csv_vs_matched_csv",  "Events;CSV;Matched CSV",120,-0.2,1,120,-0.2,1);
  m_csv_vs_matched_deepcsv = dir.make<TH2F>("csv_vs_matched_deepcsv",  "Events;CSV;Matched Deep CSV",120,-0.2,1,120,-0.2,1);

  m_deepcsv_matched = dir.make<TH1F>("deepcsv_matched","deepcsv;deepcsv;Entries",140,-0.2,1.2);
  m_deepcsv_vs_matched_deepcsv = dir.make<TH2F>("deepcsv_vs_matched_deepcsv",  "Events;DeepCSV;Matched DeepCSV",120,-0.2,1,120,-0.2,1);
  
  m_deepcsv_bb = dir.make<TH1F>("deepcsv_bb","deepcsv_bb;deepcsv_bb;Entries",100,-2,2);

  m_partonFlavour                    = dir.make<TH1F>("partonFlavour"                ,"partonFlavour;partonFlavour;Entries"                        ,60, -30.5,29.5);
  m_hadronFlavour                    = dir.make<TH1F>("hadronFlavour"                ,"hadronFlavour;hadronFlavour;Entries"                        ,60, -30.5,29.5);

  m_allJetsVsnPV             = dir.make<TH1F>("AllJetsVsnPV",       "nPV  ;nPV ;All Jets",  100,-0.5, 99.5);
  m_passCSVBTagJetsVsnPV     = dir.make<TH1F>("PassCSVBTagJetsVsnPV",  "nPV  ;nPV ;CSV BTagged Jets",  100,-0.5, 99.5);
  m_passDeepCSVBTagJetsVsnPV = dir.make<TH1F>("PassDeepCSVBTagJetsVsnPV",  "nPV  ;nPV ;Deep CSV BTagged Jets",  100,-0.5, 99.5);

  m_light = light;
  if(!m_light){
      
    m_vertexNTracks                    = dir.make<TH1F>("vertexNTracks"                ,"vertexNTracks;nVertex Tracks;Entries"                 ,22, -2.5, 19.5);
    m_vertexMass                       = dir.make<TH1F>("vertexMass"                   ,"vertexMass;Vertex Mass [GeV]"                    ,100, -0.5, 50);
    m_vertexJetDeltaR                  = dir.make<TH1F>("vertexJetDeltaR"              ,"vertexJetDeltaR;Vertex-Jet #Delta R"               ,100, -0.01, 0.4);
    m_vertexFitProb                    = dir.make<TH1F>("vertexFitProb"                ,"vertexFitProb;Vertex Fit Prob"                 ,100, -50, 50);
    m_vertexEnergyRatio                = dir.make<TH1F>("vertexEnergyRatio"            ,"vertexEnergyRatio;Vertex Energy Fraction "             ,100, -0.1, 3);
    m_vertexCategory                   = dir.make<TH1F>("vertexCategory"               ,"vertexCategory;Vertex Category"                ,4 ,-1.5,2.5);
    m_vertexBoostOverSqrtJetPt         = dir.make<TH1F>("vertexBoostOverSqrtJetPt"     ,"vertexBoostOverSqrtJetPt;Vertex Boost/#sqrt{jet P_{T}}"      ,100, -0.1, 1.1);
    m_trackJetPt                       = dir.make<TH1F>("trackJetPt"           ,"trackJetPt;Track Jet P_{T} [GeV]"            ,100, 0,400);
    m_trackSumJetEtRatio               = dir.make<TH1F>("trackSumJetEtRatio"           ,"trackSumJetEtRatio;Track-jet/Jet E_{T} Ratio"            ,100, -0.1,1.5);
    m_trackSumJetDeltaR                = dir.make<TH1F>("trackSumJetDeltaR"            ,"trackSumJetDeltaR; Track-Jet - Jet #Delta R"             ,100, -0.1, 0.35);
    m_trackSip2dValAboveCharm          = dir.make<TH1F>("trackSip2dValAboveCharm"      ,"trackSip2dValAboveCharm;trackSip2dValAboveCharm"       ,100, -0.2, 0.2);
    m_trackSip2dSigAboveCharm          = dir.make<TH1F>("trackSip2dSigAboveCharm"      ,"trackSip3dSigAboveCharm;trackSip2SiglAboveCharm"       ,100, -50, 50);
    m_trackSip3dValAboveCharm          = dir.make<TH1F>("trackSip3dValAboveCharm"      ,"trackSip3dValAboveCharm;trackSip3dValAboveCharm"       ,100, -0.2, 0.2); 
    m_trackSip3dSigAboveCharm          = dir.make<TH1F>("trackSip3dSigAboveCharm"      ,"trackSip3dSigAboveCharm;trackSip3dSigAboveCharm"       ,100, -50, 50);
    m_totalMultiplicity                = dir.make<TH1F>("totalMultiplicity"            ,"totalMultiplicity;total multiplicity"             ,62, -1.5, 60.5);
    m_totalFraction                    = dir.make<TH1F>("totalFraction"                ,"totalFraction;total fraction"             ,100, -0.1,1.5);
    m_photonMultiplicity               = dir.make<TH1F>("photonMultiplicity"           ,"photonMultiplicity;photon multiplicity"            ,42, -1.5, 40.5);
    m_photonEnergyFraction             = dir.make<TH1F>("photonEnergyFraction"         ,"photonEnergyFraction;photon energy fraction"          ,100, -0.1,1.5);
    m_neutralHadronMultiplicity        = dir.make<TH1F>("neutralHadronMultiplicity"    ,"neutralHadronMultiplicity;neutralHadronMultiplicity"     ,22, -1.5, 20.5);
    m_neutralHadronEnergyFraction      = dir.make<TH1F>("neutralHadronEnergyFraction"  ,"neutralHadronEnergyFraction;neutralHadronEnergyFraction"   ,100, -0.1,1.5);
    m_neMult                           = dir.make<TH1F>("neMult"                       ,"neMult;neMult"                        ,62, -1.5, 60.5);
    m_neHadEF                          = dir.make<TH1F>("neHadEF"                      ,"neHadEF;neHadEF"                       ,100, -0.1,2.5);
    m_neEmEF                           = dir.make<TH1F>("neEmEF"                       ,"neEmEF;neEmEF"                        ,100, -0.1,2.5);
    m_muonMultiplicity                 = dir.make<TH1F>("muonMultiplicity"             ,"muonMultiplicity;muonMultiplicity"              ,12, -1.5, 10.5);
    m_muonEnergyFraction               = dir.make<TH1F>("muonEnergyFraction"           ,"muonEnergyFraction;muonEnergyFraction"            ,100, -0.1,1.5);
    m_mult                             = dir.make<TH1F>("mult"                         ,"mult;mult"                          ,62, -1.5, 60.5);
    m_muEF                             = dir.make<TH1F>("muEF"                         ,"muEF;muEF"                          ,100, -0.1,2.5);
    m_massVertexEnergyFraction         = dir.make<TH1F>("massVertexEnergyFraction"     ,"massVertexEnergyFraction;massVertexEnergyFraction"      ,100, -0.1,2.5);
    m_jetNTracksEtaRel                 = dir.make<TH1F>("jetNTracksEtaRel"             ,"jetNTracksEtaRel;jetNTracksEtaRel"              ,22, -1.5, 20.5);
    m_jetNTracks                       = dir.make<TH1F>("jetNTracks"                   ,"jetNTracks;Number Tracks"                    ,42, -1.5, 40.5);
    m_jetNSelectedTracks               = dir.make<TH1F>("jetNSelectedTracks"           ,"jetNSelectedTracks;Number Selected Tracks"            ,42, -1.5, 40.5);
    m_jetNSecondaryVertices            = dir.make<TH1F>("jetNSecondaryVertices"        ,"jetNSecondaryVertices;Number Secondary Vertices"         ,12, -1.5, 10.5);
    m_hadronPhotonMultiplicity         = dir.make<TH1F>("hadronPhotonMultiplicity"     ,"hadronPhotonMultiplicity;hadronPhotonMultiplicity"      ,62, -1.5, 60.5);
    m_hadronMultiplicity               = dir.make<TH1F>("hadronMultiplicity"           ,"hadronMultiplicity;hadronMultiplicity"            ,42, -1.5, 40.5);
    m_flightDistance1dSig              = dir.make<TH1F>("flightDistance1dSig"          ,"flightDistance1dSig;flightDistance1dSig"           ,100, -10, 150);
    m_flightDistance1dVal              = dir.make<TH1F>("flightDistance1dVal"          ,"flightDistance1dVal;flightDistance1dVal"           ,100, -0.1, 5);
    m_flightDistance2dSig              = dir.make<TH1F>("flightDistance2dSig"          ,"flightDistance2dSig;flightDistance2dSig"           ,100, -10, 150);
    m_flightDistance2dVal              = dir.make<TH1F>("flightDistance2dVal"          ,"flightDistance2dVal;flightDistance2dVal"           ,100, -0.1, 5);
    m_flightDistance3dSig              = dir.make<TH1F>("flightDistance3dSig"          ,"flightDistance3dSig;flightDistance3dSig"           ,100, -10, 150);
    m_flightDistance3dVal              = dir.make<TH1F>("flightDistance3dVal"          ,"flightDistance3dVal;flightDistance3dVal"           ,100, -0.1, 5);
    m_chargedHadronMultiplicity        = dir.make<TH1F>("chargedHadronMultiplicity"    ,"chargedHadronMultiplicity;chargedHadronMultiplicity"     ,42, -1.5, 40.5);
    m_chargedHadronEnergyFraction      = dir.make<TH1F>("chargedHadronEnergyFraction"  ,"chargedHadronEnergyFraction;chargedHadronEnergyFraction"   ,100, -0.1,1.5);
    m_chMult                           = dir.make<TH1F>("chMult"                       ,"chMult;chMult"                        ,42, -1.5, 40.5);
    m_chHadEF                          = dir.make<TH1F>("chHadEF"                      ,"chHadEF;chHadEF;Entries"                       ,100, -0.1,2.5);
    m_chEmEF                           = dir.make<TH1F>("chEmEF"                       ,"chEmEF;chEmEF;Entries"                        ,100, -0.1,2.5);


    m_nTrk = dir.make<TH1F>("nTrk","nTrk;nTracks;Entries",42,-1.5,40.5);
    m_trackHists = new TrackHists(name, fs);

  }



} 

JetHists::~JetHists() {} 


void
//JetHists::Fill (const JetData* jetPtr){
//  const JetData& jetInfo = (*jetPtr);
JetHists::Fill (const JetData& jetInfo, float eventWeight, const EventData* eventData){

  m_pt      ->Fill(jetInfo.m_pt      , eventWeight);
  m_pt_l    ->Fill(jetInfo.m_pt      , eventWeight);
  m_eta     ->Fill(jetInfo.m_eta     , eventWeight);
  m_phi     ->Fill(jetInfo.m_phi     , eventWeight);
  m_mass    ->Fill(jetInfo.m_mass    , eventWeight);
  m_csv     ->Fill(jetInfo.m_csv     , eventWeight);
  m_deepcsv ->Fill(jetInfo.m_deepcsv , eventWeight);
  m_SF      ->Fill(jetInfo.m_SF      , eventWeight);

  if(jetInfo.m_matchedJet){
    m_matched_dPt     ->Fill(jetInfo.m_pt - jetInfo.m_matchedJet->m_pt            , eventWeight);
    m_matched_dEta    ->Fill(jetInfo.m_eta - jetInfo.m_matchedJet->m_eta          , eventWeight);
    m_matched_dPhi    ->Fill(jetInfo.m_phi - jetInfo.m_matchedJet->m_phi          , eventWeight);
    m_matched_dR      ->Fill(jetInfo.m_vec.DeltaR(jetInfo.m_matchedJet->m_vec)    , eventWeight);
    m_matched_dMass   ->Fill(jetInfo.m_mass - jetInfo.m_matchedJet->m_mass        , eventWeight);
    m_matched_dDeepcsv->Fill(jetInfo.m_deepcsv - jetInfo.m_matchedJet->m_deepcsv  , eventWeight);
    
    m_deepcsv_matched->Fill(jetInfo.m_matchedJet->m_deepcsv, eventWeight);
    m_deepcsv_vs_matched_deepcsv->Fill(jetInfo.m_deepcsv, jetInfo.m_matchedJet->m_deepcsv, eventWeight);

    m_csv_matched->Fill(jetInfo.m_matchedJet->m_csv, eventWeight);
    m_csv_vs_matched_csv->Fill(jetInfo.m_csv, jetInfo.m_matchedJet->m_csv, eventWeight);
    m_csv_vs_matched_deepcsv->Fill(jetInfo.m_csv, jetInfo.m_matchedJet->m_deepcsv, eventWeight);
  }
  m_deepcsv_bb->Fill(jetInfo.m_deepcsv_bb, eventWeight);
  m_partonFlavour                    ->Fill(jetInfo.m_partonFlavour   , eventWeight);
  m_hadronFlavour                    ->Fill(jetInfo.m_hadronFlavour   , eventWeight);


  if(!m_light){
    m_vertexNTracks                    ->Fill(jetInfo.m_vertexNTracks               , eventWeight     );
    m_vertexMass                       ->Fill(jetInfo.m_vertexMass                  , eventWeight     );
    m_vertexJetDeltaR                  ->Fill(jetInfo.m_vertexJetDeltaR             , eventWeight     );
    m_vertexFitProb                    ->Fill(jetInfo.m_vertexFitProb               , eventWeight     );
    m_vertexEnergyRatio                ->Fill(jetInfo.m_vertexEnergyRatio           , eventWeight     );
    m_vertexCategory                   ->Fill(jetInfo.m_vertexCategory              , eventWeight     );
    m_vertexBoostOverSqrtJetPt         ->Fill(jetInfo.m_vertexBoostOverSqrtJetPt    , eventWeight     );
    m_trackJetPt                       ->Fill(jetInfo.m_trackJetPt                  , eventWeight     );
    m_trackSumJetEtRatio               ->Fill(jetInfo.m_trackSumJetEtRatio          , eventWeight     );
    if(jetInfo.m_jetNSelectedTracks > 0)
      m_trackSumJetDeltaR                ->Fill(jetInfo.m_trackSumJetDeltaR , eventWeight );
    m_trackSip2dValAboveCharm          ->Fill(jetInfo.m_trackSip2dValAboveCharm   , eventWeight       );
    m_trackSip2dSigAboveCharm          ->Fill(jetInfo.m_trackSip2dSigAboveCharm   , eventWeight       );
    m_trackSip3dValAboveCharm          ->Fill(jetInfo.m_trackSip3dValAboveCharm   , eventWeight       );
    m_trackSip3dSigAboveCharm          ->Fill(jetInfo.m_trackSip3dSigAboveCharm   , eventWeight       );
    m_totalMultiplicity                ->Fill(jetInfo.m_totalMultiplicity         , eventWeight       );
    m_totalFraction                    ->Fill((jetInfo.m_chargedHadronEnergyFraction
					       + jetInfo.m_neutralHadronEnergyFraction
					       + jetInfo.m_photonEnergyFraction
					       + jetInfo.m_muonEnergyFraction) , eventWeight);
					      
    m_photonMultiplicity               ->Fill(jetInfo.m_photonMultiplicity             , eventWeight  );
    m_photonEnergyFraction             ->Fill(jetInfo.m_photonEnergyFraction           , eventWeight  );
    m_neutralHadronMultiplicity        ->Fill(jetInfo.m_neutralHadronMultiplicity      , eventWeight  );
    m_neutralHadronEnergyFraction      ->Fill(jetInfo.m_neutralHadronEnergyFraction    , eventWeight  );
    m_neMult                           ->Fill(jetInfo.m_neMult                         , eventWeight  );
    m_neHadEF                          ->Fill(jetInfo.m_neHadEF                        , eventWeight  );
    m_neEmEF                           ->Fill(jetInfo.m_neEmEF                         , eventWeight  );
    m_muonMultiplicity                 ->Fill(jetInfo.m_muonMultiplicity               , eventWeight  );
    m_muonEnergyFraction               ->Fill(jetInfo.m_muonEnergyFraction             , eventWeight  );
    m_mult                             ->Fill(jetInfo.m_mult                           , eventWeight  );
    m_muEF                             ->Fill(jetInfo.m_muEF                           , eventWeight  );
    m_massVertexEnergyFraction         ->Fill(jetInfo.m_massVertexEnergyFraction       , eventWeight  );
    m_jetNTracksEtaRel                 ->Fill(jetInfo.m_jetNTracksEtaRel               , eventWeight  );
    m_jetNTracks                       ->Fill(jetInfo.m_jetNTracks                     , eventWeight  );
    m_jetNSelectedTracks               ->Fill(jetInfo.m_jetNSelectedTracks             , eventWeight  );
    m_jetNSecondaryVertices            ->Fill(jetInfo.m_jetNSecondaryVertices          , eventWeight  );
    m_hadronPhotonMultiplicity         ->Fill(jetInfo.m_hadronPhotonMultiplicity       , eventWeight  );
    m_hadronMultiplicity               ->Fill(jetInfo.m_hadronMultiplicity             , eventWeight  );
    m_flightDistance1dSig              ->Fill(jetInfo.m_flightDistance1dSig            , eventWeight  );
    m_flightDistance1dVal              ->Fill(jetInfo.m_flightDistance1dVal            , eventWeight  );
    m_flightDistance2dSig              ->Fill(jetInfo.m_flightDistance2dSig            , eventWeight  );
    m_flightDistance2dVal              ->Fill(jetInfo.m_flightDistance2dVal            , eventWeight  );
    m_flightDistance3dSig              ->Fill(jetInfo.m_flightDistance3dSig            , eventWeight  );
    m_flightDistance3dVal              ->Fill(jetInfo.m_flightDistance3dVal            , eventWeight  );
    m_chargedHadronMultiplicity        ->Fill(jetInfo.m_chargedHadronMultiplicity      , eventWeight  );
    m_chargedHadronEnergyFraction      ->Fill(jetInfo.m_chargedHadronEnergyFraction    , eventWeight  );
    m_chMult                           ->Fill(jetInfo.m_chMult                         , eventWeight  );
    m_chHadEF                          ->Fill(jetInfo.m_chHadEF                        , eventWeight  );
    m_chEmEF                           ->Fill(jetInfo.m_chEmEF                         , eventWeight  );

    unsigned int nTracks = jetInfo.m_tracks.size();
    m_nTrk->Fill(nTracks, eventWeight);
    for(const TrackData& track: jetInfo.m_tracks){
      m_trackHists->Fill(track, eventWeight);
    }


  }//m_light

  if(eventData){
    m_allJetsVsnPV->Fill(eventData->nPV, eventWeight);
    if(jetInfo.m_csv > 0.8484)
      m_passCSVBTagJetsVsnPV->Fill(eventData->nPV, eventWeight);
    if(jetInfo.m_deepcsv > 0.8001)
      m_passDeepCSVBTagJetsVsnPV->Fill(eventData->nPV, eventWeight);
  }


  return;
}


