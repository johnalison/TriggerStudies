#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include "TSystem.h"
#include "TChain.h"

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"

#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"

#include "TriggerStudies/NtupleAna/interface/EventData.h"
#include "TriggerStudies/NtupleAna/interface/JetDataHandler.h"
#include "TriggerStudies/NtupleAna/interface/LeptonDataHandler.h"

#include "TriggerStudies/NtupleAna/interface/JetHists.h"
#include "TriggerStudies/NtupleAna/interface/EventHists.h"
#include "TriggerStudies/NtupleAna/interface/Helpers.h"

using namespace NtupleAna;


int main(int argc, char * argv[]){
  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  FWLiteEnabler::enable();
  
  // parse arguments
  if ( argc < 2 ) {
    std::cout << "Usage : " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }

  if( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ){
    std::cout << " ERROR: ParametersSet 'process' is missing in your configuration file" << std::endl; exit(0);
  }

  // get the python configuration
  const edm::ParameterSet& process = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  fwlite::InputSource inputHandler_(process); 
  fwlite::OutputFiles outputHandler_(process);

  //
  // Get the config
  //
  // now get each parameter
  const edm::ParameterSet& ana = process.getParameter<edm::ParameterSet>("jetLevelStudy");
  bool loadTrkLevel = ana.getParameter<bool>("LoadTrkLevel");
  bool debug = ana.getParameter<bool>("debug");

  //
  //  Inint Tree
  //
  TChain* tree = new TChain("tree");
  for(unsigned int iFile=0; iFile<inputHandler_.files().size(); ++iFile){
    // open input file (can be located on castor)
    std::cout << "inputFile is " << inputHandler_.files()[iFile].c_str() << std::endl;

    //TFile* inFile = TFile::Open(inputFiles_[iFile].c_str());
    //if( inFile ){
    tree->Add(inputHandler_.files()[iFile].c_str());
    //}
  }

  //
  // Input Data
  //
  EventData eventData = EventData();
  eventData.SetBranchAddress(tree);

  JetDataHandler pfJetsDB = JetDataHandler("pfJets",loadTrkLevel);
  pfJetsDB.SetBranchAddress(tree);

  JetDataHandler caloJetsDB = JetDataHandler("caloJets",loadTrkLevel);
  caloJetsDB.SetBranchAddress(tree);

  JetDataHandler offJetsDB = JetDataHandler("offJets",loadTrkLevel);
  offJetsDB.SetBranchAddress(tree);

  LeptonDataHandler muonDB = LeptonDataHandler("offTightMuons");
  muonDB.SetBranchAddress(tree);

  LeptonDataHandler elecDB = LeptonDataHandler("offTightElectrons");
  elecDB.SetBranchAddress(tree);

  //
  // Make output ntuple/Hists
  // 
  fwlite::TFileService fs = fwlite::TFileService(outputHandler_.file());

  EventHists eventHists     = EventHists("AllEvents", fs);

  JetHists pfJetHistsPreOLap     = JetHists("pfJetsPreOLap",fs,true);
  JetHists pfJetHists            = JetHists("pfJets", fs, true);
  JetHists pfJetHists_matched    = JetHists("pfJets_matched" ,fs, true);
  JetHists pfJetHists_matchedB   = JetHists("pfJets_matchedB",fs, true);
  JetHists pfJetHists_matchedL   = JetHists("pfJets_matchedL",fs, true);

  JetHists caloJetHistsPreOLap     = JetHists("caloJetsPreOLap",fs, true);
  JetHists caloJetHists            = JetHists("caloJets",fs, true);
  JetHists caloJetHists_matched    = JetHists("caloJets_matched" ,fs, true);
  JetHists caloJetHists_matchedB   = JetHists("caloJets_matchedB",fs, true);
  JetHists caloJetHists_matchedL   = JetHists("caloJets_matchedL",fs, true);

  JetHists offJetHistsPreOLap = JetHists("offJetsPreOLap",fs, true);

  JetHists offJetHists   = JetHists("offJets",  fs, true);
  JetHists offJetHists_B = JetHists("offJets_B",fs, true);
  JetHists offJetHists_L = JetHists("offJets_L",fs, true);

  JetHists offJetHists_matched        = JetHists("offJets_matched",  fs, true);
  JetHists offJetHists_matchedJet     = JetHists("offJets_matchedJet",  fs, true);
  JetHists offJetHists_B_matched      = JetHists("offJets_B_matched",fs, true);
  JetHists offJetHists_L_matched      = JetHists("offJets_L_matched",fs, true);

  
  std::cout << " In jetLevelStudy " << std::endl;

  int nEventThisFile = tree->GetEntries();
  int maxEvents = inputHandler_.maxEvents();
  std::cout <<  "Number of input events: " << nEventThisFile << std::endl;

  for(int entry = 0; entry<nEventThisFile; entry++){
    
    if(entry %1000 == 0 || debug)
      std::cout << "Processed .... "<<entry<<" Events"<<std::endl;
    if( (maxEvents > 0) && (entry > maxEvents))
      break;

    tree->GetEntry( entry );

    eventData.SetEvent();

    if(debug){
      std::cout << "RunNumber: "  << eventData.runNumber << std::endl;
      std::cout << "EventNumber: " << eventData.eventNumber << std::endl;
    }

    //
    // Fill All events
    //
    eventHists.Fill(eventData);

    // Converting from "row-level" info to "column-level" info
    std::vector<NtupleAna::LeptonData> elecs  = elecDB.GetLeps();
    std::vector<NtupleAna::LeptonData> muons  = muonDB.GetLeps();
    std::vector<NtupleAna::JetData>    offJets = offJetsDB.GetJets();
    std::vector<NtupleAna::JetData>    pfJets   = pfJetsDB.GetJets();
    std::vector<NtupleAna::JetData>    caloJets = caloJetsDB.GetJets();

    if((elecs.size()+muons.size()) < 2)  continue;

    for(JetData& offJet : offJets){

      if(fabs(offJet.m_eta) > 2.5) continue;
      if(offJet.m_pt       < 35)   continue;
      
      offJetHistsPreOLap.Fill(offJet);

      if(NtupleAna::failOverlap(offJet,elecs)) continue;
      if(NtupleAna::failOverlap(offJet,muons)) continue;


      // Match offline to online
      float dR = 1e6;
      JetData* matchedJet = nullptr;
      for(JetData& pfJet : pfJets){
	float this_dR = pfJet.m_vec.DeltaR(offJet.m_vec);
	if (this_dR < dR){
	  dR = this_dR;
	  matchedJet = &pfJet;
	}
      }

      if( dR < 0.4){
	matchedJet->m_matchedJet = &offJet;
	matchedJet->m_match_dR   = dR;
	offJet.m_matchedJet = matchedJet;
	offJet.m_match_dR   = dR;
      }

      // match tracks if we matched jets
      // Fill offJetHists
      // offJets_ROC
      //  wp60 DeepCSV > 0.76 (actual efficiency = 0.604992842829)
      //  wp70 DeepCSV > 0.56 (actual efficiency = 0.717503578586)
      //  wp80 DeepCSV > 0.36 (actual efficiency = 0.808474091039)
      //  wp90 DeepCSV > 0.12 (actual efficiency = 0.912533638706)
      offJetHists.Fill(offJet);
      if(offJet.m_hadronFlavour == 5){
	offJetHists_B.Fill(offJet);
      }else{
	offJetHists_L.Fill(offJet);
      }

      if(offJet.m_matchedJet){
	offJetHists_matched.Fill(offJet);
	offJetHists_matchedJet.Fill(*offJet.m_matchedJet);

	if(offJet.m_hadronFlavour == 5){
	  offJetHists_B_matched.Fill(offJet);
	}else{
	  offJetHists_L_matched.Fill(offJet);
	}


      }//m_matchedJet

      // Match offline to online
      for(JetData& caloJet : caloJets){
	float deltaR = caloJet.m_vec.DeltaR(offJet.m_vec);
	if( deltaR < 0.4){
	  caloJet.m_matchedJet = &offJet;
	  break;
	}
      }
    
    }//offJets

    //
    //  pf Jets
    //
    for(JetData& pfJet : pfJets){
      if(fabs(pfJet.m_eta) > 2.5) continue;
      if(pfJet.m_pt       < 35)   continue;


      pfJetHistsPreOLap.Fill(pfJet);

      if(NtupleAna::failOverlap(pfJet,elecs)) continue;
      if(NtupleAna::failOverlap(pfJet,muons)) continue;

      pfJetHists.Fill(pfJet);

      if(pfJet.m_matchedJet){
	pfJetHists_matched .Fill(pfJet);

	if( pfJet.m_matchedJet->m_hadronFlavour == 5)
	  pfJetHists_matchedB.Fill(pfJet);
	else
	  pfJetHists_matchedL.Fill(pfJet);
      }
    }

    //
    //  calo Jets
    //
    for(JetData& caloJet : caloJets){
      if(fabs(caloJet.m_eta) > 2.5) continue;
      if(caloJet.m_pt       < 35)   continue;

      caloJetHistsPreOLap.Fill(caloJet);
      if(NtupleAna::failOverlap(caloJet,elecs)) continue;
      if(NtupleAna::failOverlap(caloJet,muons)) continue;

      caloJetHists.Fill(caloJet);

      if(caloJet.m_matchedJet){
	caloJetHists_matched .Fill(caloJet);

	if(caloJet.m_matchedJet->m_hadronFlavour == 5)
	  caloJetHists_matchedB.Fill(caloJet);
	else
	  caloJetHists_matchedL.Fill(caloJet);
      }
    }
   
 
    
  }




  return 0;
}
