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
using std::cout; 
using std::endl; 

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

  JetHists offJetHistsPreOLap = JetHists("offJetsPreOLap",fs, true);
  JetHists offJetHistsBeforeProbe = JetHists("offJetsBeforeProbe",fs, true);

  JetHists offJetHists   = JetHists("offJets",  fs, true);
  JetHists offJetHists_B = JetHists("offJets_B",fs, true);
  JetHists offJetHists_L = JetHists("offJets_L",fs, true);

  JetHists offJetHists_matchedPF               = JetHists("offJets_matchedPF",               fs, true);
  JetHists offJetHists_matchedPFJet            = JetHists("offJets_matchedPFJet",            fs, true);
  JetHists offJetHists_matchedPFcsvTag         = JetHists("offJets_matchedPFcsvTag",         fs, true);
  JetHists offJetHists_matchedPFcsvTagJet      = JetHists("offJets_matchedPFcsvTagJet",      fs, true);
  JetHists offJetHists_matchedPFDeepcsvTag     = JetHists("offJets_matchedPFDeepcsvTag",     fs, true);
  JetHists offJetHists_matchedPFDeepcsvTagJet  = JetHists("offJets_matchedPFDeepcsvTagJet",  fs, true);

  JetHists offJetHists_matchedCalo               = JetHists("offJets_matchedCalo",           fs, true);
  JetHists offJetHists_matchedCaloJet            = JetHists("offJets_matchedCaloJet",        fs, true);
  JetHists offJetHists_matchedCalocsvTag         = JetHists("offJets_matchedCalocsvTag",     fs, true);
  JetHists offJetHists_matchedCalocsvTagJet      = JetHists("offJets_matchedCalocsvTagJet",  fs, true);
  JetHists offJetHists_matchedCaloDeepcsvTag     = JetHists("offJets_matchedCaloDeepcsvTag",     fs, true);
  JetHists offJetHists_matchedCaloDeepcsvTagJet  = JetHists("offJets_matchedCaloDeepcsvTagJet",  fs, true);
  

  JetHists offJetHists_B_matched      = JetHists("offJets_B_matchedPF",fs, true);
  JetHists offJetHists_L_matched      = JetHists("offJets_L_matchedPF",fs, true);


  //float pfDeepCSV = 0.6324;
  //float pfCSV = 0.8484;
  //float caloCSV = 0.8484;

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

    //
    // Lepton Selection
    //
    //if((elecs.size()+muons.size()) < 2)  continue;
    if(elecs.size() != 1)  continue;
    if(muons.size() != 1)  continue;

    //
    // Trigger Selection
    //
    if(!(eventData.HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4 ||eventData.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4 ))
      continue;

    //
    // cut on number of clean jets
    //
    // Sum$(offCleanJets_pt > 30 && abs(offCleanJets_eta) < 2.4) >= 2"

    //
    // Cut on CSV Selection
    //
    unsigned int nOffJets = 0;
    unsigned int nOffJetsTagged = 0;
    for(JetData& offJet : offJets){
      if(fabs(offJet.m_eta) > 2.4) continue;
      if(offJet.m_pt       < 30)   continue;
      if(NtupleAna::failOverlap(offJet,elecs)) continue;
      if(NtupleAna::failOverlap(offJet,muons)) continue;
      ++nOffJets;
      if(offJet.m_deepcsv > 0.8001) ++nOffJetsTagged;

    }
    if(nOffJets < 2) continue;
    

    //for(auto elec: elecs){
    //  cout << "Electron pt/eta " << elec.m_pt << "/" << elec.m_eta<<endl;
    //}
    //
    //for(auto muon: muons){
    //  cout << "Muon pt/eta/iso " << muon.m_pt << "/" << muon.m_eta << "/" << muon.m_iso << endl;
    //}


    for(JetData& offJet : offJets){

      if(fabs(offJet.m_eta) > 2.4) continue;
      if(offJet.m_pt       < 30)   continue;
      
      offJetHistsPreOLap.Fill(offJet);

      if(!offJet.m_passesTightLeptVetoID) continue;
      if(NtupleAna::failOverlap(offJet,elecs)) continue;
      if(NtupleAna::failOverlap(offJet,muons)) continue;

      //
      // Check if Prob
      //
      bool isProbe = false;
      for(JetData& offJetOther : offJets){
	if(offJetOther.m_deepcsv       < 0.8001)   continue;	
	if(offJet.m_vec.DeltaR(offJetOther.m_vec) < 0.4) continue;

	if(offJetOther.m_pt       < 30)   continue;	
	if(fabs(offJetOther.m_eta) > 2.4) continue;
	if(!offJetOther.m_passesTightLeptVetoID) continue;
	if(NtupleAna::failOverlap(offJetOther,elecs)) continue;
	if(NtupleAna::failOverlap(offJetOther,muons)) continue;


	isProbe = true;
      }
      
      offJetHistsBeforeProbe.Fill(offJet);

      if(!isProbe) continue;

      // Fill offJetHists
      offJetHists.Fill(offJet);
      if(offJet.m_hadronFlavour == 5){
	offJetHists_B.Fill(offJet);
      }else{
	offJetHists_L.Fill(offJet);
      }

      //
      // Match offline to PF
      //
      float dR_PF = 1e6;
      JetData* matchedJetPF = nullptr;

      for(JetData& pfJet : pfJets){
	float this_dR = pfJet.m_vec.DeltaR(offJet.m_vec);
	if (this_dR < dR_PF){
	  dR_PF = this_dR;
	  matchedJetPF = &pfJet;
	}
      }

      //
      //  IF have a PF Match
      //
      if( dR_PF < 0.4){
	matchedJetPF->m_matchedJet = &offJet;
	matchedJetPF->m_match_dR   = dR_PF;
	offJet.m_matchedJet = matchedJetPF;
	offJet.m_match_dR   = dR_PF;

	offJetHists_matchedPF.Fill(offJet);
	offJetHists_matchedPFJet.Fill(*matchedJetPF);

	if(offJet.m_hadronFlavour == 5){
	  offJetHists_B_matched.Fill(offJet);
	}else{
	  offJetHists_L_matched.Fill(offJet);
	}

	// 
	// If pass CVS working point
	//
	if(matchedJetPF->m_csv >= 0.8484){
	  offJetHists_matchedPFcsvTag.Fill(offJet);
	  offJetHists_matchedPFcsvTagJet.Fill(*matchedJetPF);
	}


	// 
	// If pass DeepCVS working point
	//
	if(matchedJetPF->m_deepcsv >= 0.6324){
	  offJetHists_matchedPFDeepcsvTag.Fill(offJet);
	  offJetHists_matchedPFDeepcsvTagJet.Fill(*matchedJetPF);
	}
	  

      }//m_matchedJet

      //
      // Match offline to Calo
      //
      float dR_Calo = 1e6;
      JetData* matchedJetCalo = nullptr;

      for(JetData& caloJet : caloJets){
	float this_dR = caloJet.m_vec.DeltaR(offJet.m_vec);
	if (this_dR < dR_Calo){
	  dR_Calo = this_dR;
	  matchedJetCalo = &caloJet;
	}
      }

      //
      //  IF have a Calo Match
      //
      if( dR_Calo < 0.4){
	matchedJetCalo->m_matchedJet = &offJet;
	matchedJetCalo->m_match_dR   = dR_Calo;
	//offJet.m_matchedJet = matchedJet;
	//offJet.m_match_dR   = dR_PF;

	offJetHists_matchedCalo.Fill(offJet);
	offJetHists_matchedCaloJet.Fill(*matchedJetCalo);

	//if(offJet.m_hadronFlavour == 5){
	//  offJetHists_B_matched.Fill(offJet);
	//}else{
	//  offJetHists_L_matched.Fill(offJet);
	//}

	// 
	// If pass CVS working point
	//
	if(matchedJetCalo->m_csv >= 0.8484){
	  offJetHists_matchedCalocsvTag.Fill(offJet);
	  offJetHists_matchedCalocsvTagJet.Fill(*matchedJetCalo);
	}

	// 
	// If pass DeepCVS working point
	//
	if(matchedJetCalo->m_deepcsv >= 0.6324){
	  offJetHists_matchedCaloDeepcsvTag.Fill(offJet);
	  offJetHists_matchedCaloDeepcsvTagJet.Fill(*matchedJetCalo);
	}

      }//m_matchedJet

    
    }//offJets


   
 
    
  }// Events 




  return 0;
}
