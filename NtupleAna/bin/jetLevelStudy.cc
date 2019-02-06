#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include "TSystem.h"
#include "TChain.h"

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"

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
#include "../../../HLTBTagging/measurements/modules/functions.h"

using namespace NtupleAna;
using std::cout; 
using std::endl; 
using optutl::CommandLineParser;


float OfflineDeepCSVTightCut  = 0.8001;
float OfflineDeepCSVMediumCut = 0.4941;
float OfflineDeepCSVLooseCut  = 0.1522;

int main(int argc, char * argv[]){
  std::cout << " ======== jetLevelStudy ========== " << std::endl;

  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  FWLiteEnabler::enable();
  
  // initialize command line parser
  CommandLineParser parser ("Analyze FWLite Histograms");

  parser.addOption ("configFile",   CommandLineParser::kString,
		    "configFileName");
  parser.addOption ("puType",   CommandLineParser::kString,
		    "pile-up correction type");
  // set defaults
  parser.integerValue ("maxEvents"  ) = -1;
  parser.integerValue ("outputEvery") =   10000;
  parser.stringValue  ("outputFile" ) = "TEST.root";  


  parser.parseArguments (argc, argv);
  //cout << "Running with "<<parser.integerValue("maxEvents") << " config file " << parser.stringValue("configFile") << endl;
  std::string configFile     = parser.stringValue("configFile");
  std::string outputFileName = parser.stringValue("outputFile");
  std::string puType         = parser.stringValue("puType");
  std::vector<std::string> inputFiles = parser.stringVector("inputFiles");

  cout << "\t Running with configFile: " << configFile << endl;
  cout << "\t Outputting to: " << outputFileName << endl;
  cout << "\t puType: " << puType << endl;

  
  if( !edm::readPSetsFrom(configFile)->existsAs<edm::ParameterSet>("process") ){
    std::cout << " ERROR: ParametersSet 'process' is missing in your configuration file" << std::endl; exit(0);
  }

  //
  // Get the config
  //
  // now get each parameter
  const edm::ParameterSet& process = edm::readPSetsFrom(configFile)->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet& ana = process.getParameter<edm::ParameterSet>("jetLevelStudy");
  bool loadTrkLevel = ana.getParameter<bool>("LoadTrkLevel");
  bool debug = ana.getParameter<bool>("debug");

  //
  //  Inint Tree
  //
  TChain* tree = new TChain("tree");
  cout << "\t inputFiles are: " << endl;
  for(unsigned int iFile=0; iFile<inputFiles.size(); ++iFile){
    // open input file (can be located on castor)
    std::cout << "\t\t " << inputFiles[iFile].c_str() << std::endl;

    //TFile* inFile = TFile::Open(inputFiles_[iFile].c_str());
    //if( inFile ){
    tree->Add(inputFiles[iFile].c_str());
    //}
  }

  bool isMC = bool(tree->GetBranch("pu"));
  cout << " \t isMC set to: " << isMC << endl;
  cout << " ================================="<<endl;

  //
  // Input Data
  //
  EventData eventData = EventData();
  eventData.SetBranchAddress(tree);

  JetDataHandler pfJetsDB = JetDataHandler("pfJets",loadTrkLevel);
  pfJetsDB.SetBranchAddress(tree);

  JetDataHandler caloJetsDB = JetDataHandler("caloJets",loadTrkLevel);
  caloJetsDB.SetBranchAddress(tree);

  //JetDataHandler offJetsDB = JetDataHandler("offJets",loadTrkLevel);
  JetDataHandler offJetsDB = JetDataHandler("offCleanJets",loadTrkLevel, isMC);
  offJetsDB.SetBranchAddress(tree);

  LeptonDataHandler muonDB = LeptonDataHandler("offTightMuons", isMC);
  muonDB.SetBranchAddress(tree);

  LeptonDataHandler elecDB = LeptonDataHandler("offTightElectrons", isMC);
  elecDB.SetBranchAddress(tree);

  //
  // Make output ntuple/Hists
  // 
  fwlite::TFileService fs = fwlite::TFileService(outputFileName);

  EventHists allEventHists  = EventHists("AllEvents", fs);
  EventHists eventHists     = EventHists("Events", fs);


  JetHists offJetHistsPreOLap = JetHists("offJetsPreOLap",fs, true);
  JetHists offJetHistsBeforeProbe = JetHists("offJetsBeforeProbe",fs, true);

  JetHists offJetHists   = JetHists("offJets",  fs, true);
  JetHists offJetHists_B = JetHists("offJets_B",fs, true);
  JetHists offJetHists_C = JetHists("offJets_C",fs, true);
  JetHists offJetHists_L = JetHists("offJets_L",fs, true);


  JetHists offJetHists_matchedPF               = JetHists("offJets_matchedPF",               fs, true);
  JetHists offJetHists_matchedPFJet            = JetHists("offJets_matchedPFJet",            fs, true);
  JetHists offJetHists_matchedPFcsvTag         = JetHists("offJets_matchedPFcsvTag",         fs, true);
  JetHists offJetHists_matchedPFcsvTagJet      = JetHists("offJets_matchedPFcsvTagJet",      fs, true);
  JetHists offJetHists_matchedPFDeepcsvTag     = JetHists("offJets_matchedPFDeepcsvTag",     fs, true);
  JetHists offJetHists_matchedPFDeepcsvTagJet  = JetHists("offJets_matchedPFDeepcsvTagJet",  fs, true);

  JetHists offJetTightHists_matchedPFJet          = JetHists("offJetsTight_matchedPFJet",               fs, true);
  JetHists offJetMediumHists_matchedPFJet         = JetHists("offJetsMedium_matchedPFJet",              fs, true);
  JetHists offJetLooseHists_matchedPFJet          = JetHists("offJetsLoose_matchedPFJet",               fs, true);

  JetHists offJetHists_B_matchedPF      = JetHists("offJets_B_matchedPF",fs, true);
  JetHists offJetHists_C_matchedPF      = JetHists("offJets_C_matchedPF",fs, true);
  JetHists offJetHists_L_matchedPF      = JetHists("offJets_L_matchedPF",fs, true);

  JetHists offJetHists_B_matchedPFJet   = JetHists("offJets_B_matchedPFJet",fs, true);
  JetHists offJetHists_C_matchedPFJet   = JetHists("offJets_C_matchedPFJet",fs, true);
  JetHists offJetHists_L_matchedPFJet   = JetHists("offJets_L_matchedPFJet",fs, true);


  JetHists offJetHists_matchedCalo               = JetHists("offJets_matchedCalo",           fs, true);
  JetHists offJetHists_matchedCaloJet            = JetHists("offJets_matchedCaloJet",        fs, true);
  JetHists offJetHists_matchedCalocsvTag         = JetHists("offJets_matchedCalocsvTag",     fs, true);
  JetHists offJetHists_matchedCalocsvTagJet      = JetHists("offJets_matchedCalocsvTagJet",  fs, true);
  JetHists offJetHists_matchedCaloDeepcsvTag     = JetHists("offJets_matchedCaloDeepcsvTag",     fs, true);
  JetHists offJetHists_matchedCaloDeepcsvTagJet  = JetHists("offJets_matchedCaloDeepcsvTagJet",  fs, true);

  JetHists offJetTightHists_matchedCaloJet          = JetHists("offJetsTight_matchedCaloJet",               fs, true);
  JetHists offJetMediumHists_matchedCaloJet         = JetHists("offJetsMedium_matchedCaloJet",              fs, true);
  JetHists offJetLooseHists_matchedCaloJet          = JetHists("offJetsLoose_matchedCaloJet",               fs, true);

  JetHists offJetHists_B_matchedCalo      = JetHists("offJets_B_matchedCalo",fs, true);
  JetHists offJetHists_C_matchedCalo      = JetHists("offJets_C_matchedCalo",fs, true);
  JetHists offJetHists_L_matchedCalo      = JetHists("offJets_L_matchedCalo",fs, true);


  JetHists offJetHists_B_matchedCaloJet      = JetHists("offJets_B_matchedCaloJet",fs, true);
  JetHists offJetHists_C_matchedCaloJet      = JetHists("offJets_C_matchedCaloJet",fs, true);
  JetHists offJetHists_L_matchedCaloJet      = JetHists("offJets_L_matchedCaloJet",fs, true);

  //
  //  Init the pile-up function
  //
  float (*get_puWeight)(float);
  get_puWeight = &get_puWeight_C_ReReco;
  //get_puWeight_CDF

  //float pfDeepCSV = 0.6324;
  //float pfCSV = 0.8484;
  //float caloCSV = 0.8484;


  int nEventThisFile = tree->GetEntries();
  int maxEvents = parser.integerValue("maxEvents");
  int outputEvery = parser.integerValue("outputEvery");
  std::cout <<  "Number of input events: " << nEventThisFile << std::endl;

  for(int entry = 0; entry<nEventThisFile; entry++){
    
    if(entry %outputEvery == 0 || debug)
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
    allEventHists.Fill(eventData);

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

    float eventWeight = 1.0;
    if(isMC){
      eventWeight = get_puWeight(eventData.pu) * elecs.at(0).m_SF * muons.at(0).m_SF;
      //eventWeight = get_puWeight_CDF(eventData.pu) * elecs.at(0).m_SF * muons.at(0).m_SF;
    }

    //std::cout << "PU Weight " << get_puWeight_CDF(eventData.pu) << std::endl;

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
    float totalsSFWeight = 1.0;
    for(JetData& offJet : offJets){
      if(fabs(offJet.m_eta) > 2.4) continue;
      if(offJet.m_pt       < 30)   continue;
      if(NtupleAna::failOverlap(offJet,elecs)) continue;
      if(NtupleAna::failOverlap(offJet,muons)) continue;
      if((offJet.m_deepcsv > 0) && fabs(offJet.m_deepcsv - (offJet.m_deepcsv_b + offJet.m_deepcsv_bb)) > 0.01)
	cout << "Deepcsv: " << offJet.m_deepcsv << "_b+_bb" << (offJet.m_deepcsv_b + offJet.m_deepcsv_bb) <<endl;

      ++nOffJets;
      if(offJet.m_deepcsv > OfflineDeepCSVTightCut) ++nOffJetsTagged;
      
      if(isMC)
	totalsSFWeight *= offJet.m_SF;
    }
    if(nOffJets < 2      ) continue;
    if(nOffJetsTagged < 1) continue;

    if(isMC)
      eventWeight*= totalsSFWeight;

    eventHists.Fill(eventData, eventWeight);    

    //for(auto elec: elecs){
    //  cout << "Electron pt/eta " << elec.m_pt << "/" << elec.m_eta<< " " << elec.m_SF << endl;
    //}
    
    //for(auto muon: muons){
    //  cout << "Muon pt/eta/iso " << muon.m_pt << "/" << muon.m_eta << "/" << muon.m_iso << endl;
    //}


    for(JetData& offJet : offJets){

      if(fabs(offJet.m_eta) > 2.4) continue;
      if(offJet.m_pt       < 30)   continue;
      
      offJetHistsPreOLap.Fill(offJet, eventWeight);

      if(!offJet.m_passesTightLeptVetoID) continue;
      if(NtupleAna::failOverlap(offJet,elecs)) continue;
      if(NtupleAna::failOverlap(offJet,muons)) continue;

      //
      // Check if Prob
      //
      unsigned int nTags = 0;
      for(JetData& offJetOther : offJets){
	if(offJetOther.m_deepcsv       < OfflineDeepCSVTightCut)   continue;	
	if(offJet.m_vec.DeltaR(offJetOther.m_vec) < 0.4) continue;

	if(offJetOther.m_pt       < 30)   continue;	
	if(fabs(offJetOther.m_eta) > 2.4) continue;
	if(!offJetOther.m_passesTightLeptVetoID) continue;
	if(NtupleAna::failOverlap(offJetOther,elecs)) continue;
	if(NtupleAna::failOverlap(offJetOther,muons)) continue;

	++nTags;
      }
      

      offJetHistsBeforeProbe.Fill(offJet, eventWeight);

      if(nTags != 1) continue;

      //cout << "Scaling eventWeight by: " << tagSF  << endl;

      // Fill offJetHists
      offJetHists.Fill(offJet, eventWeight);
      if(offJet.m_hadronFlavour == 5){
	offJetHists_B.Fill(offJet, eventWeight);
      }	else if(offJet.m_hadronFlavour == 4){
	offJetHists_C.Fill(offJet, eventWeight);
      }	else if(offJet.m_hadronFlavour == 0){
	offJetHists_L.Fill(offJet, eventWeight);
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

	offJetHists_matchedPF.Fill(offJet, eventWeight);
	offJetHists_matchedPFJet.Fill(*matchedJetPF, eventWeight);

	if((offJet.m_deepcsv > OfflineDeepCSVTightCut))
	  offJetTightHists_matchedPFJet.Fill(*matchedJetPF, eventWeight);	  
	if((offJet.m_deepcsv > OfflineDeepCSVMediumCut))
	  offJetMediumHists_matchedPFJet.Fill(*matchedJetPF, eventWeight);	  
	if((offJet.m_deepcsv > OfflineDeepCSVLooseCut))
	  offJetLooseHists_matchedPFJet.Fill(*matchedJetPF, eventWeight);	  


	if(offJet.m_hadronFlavour == 5){
	  offJetHists_B_matchedPF.Fill(offJet, eventWeight);
	  offJetHists_B_matchedPFJet.Fill(*matchedJetPF, eventWeight);
	}else if(offJet.m_hadronFlavour == 4){
	  offJetHists_C_matchedPF.Fill(offJet, eventWeight);
	  offJetHists_C_matchedPFJet.Fill(*matchedJetPF, eventWeight);
	}else if(offJet.m_hadronFlavour == 0){
	  offJetHists_L_matchedPF.Fill(offJet, eventWeight);
	  offJetHists_L_matchedPFJet.Fill(*matchedJetPF, eventWeight);
	}


	// 
	// If pass CVS working point
	//
	if(matchedJetPF->m_csv >= 0.8484){
	  offJetHists_matchedPFcsvTag.Fill(offJet, eventWeight);
	  offJetHists_matchedPFcsvTagJet.Fill(*matchedJetPF, eventWeight);
	}


	// 
	// If pass DeepCVS working point
	//
	if(matchedJetPF->m_deepcsv >= 0.6324){
	  offJetHists_matchedPFDeepcsvTag.Fill(offJet, eventWeight);
	  offJetHists_matchedPFDeepcsvTagJet.Fill(*matchedJetPF, eventWeight);
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

	offJetHists_matchedCalo.Fill(offJet, eventWeight);
	offJetHists_matchedCaloJet.Fill(*matchedJetCalo, eventWeight);

	if((offJet.m_deepcsv > OfflineDeepCSVTightCut))
	  offJetTightHists_matchedCaloJet.Fill(*matchedJetCalo, eventWeight);	  
	if((offJet.m_deepcsv > OfflineDeepCSVMediumCut))
	  offJetMediumHists_matchedCaloJet.Fill(*matchedJetCalo, eventWeight);	  
	if((offJet.m_deepcsv > OfflineDeepCSVLooseCut))
	  offJetLooseHists_matchedCaloJet.Fill(*matchedJetCalo, eventWeight);	  


	if(offJet.m_hadronFlavour == 5){
	  offJetHists_B_matchedCalo.Fill(offJet, eventWeight);
	  offJetHists_B_matchedCaloJet.Fill(*matchedJetCalo, eventWeight);
	}else if(offJet.m_hadronFlavour == 4){
	  offJetHists_C_matchedCalo.Fill(offJet, eventWeight);
	  offJetHists_C_matchedCaloJet.Fill(*matchedJetCalo, eventWeight);
	}else if(offJet.m_hadronFlavour == 0){
	  offJetHists_L_matchedCalo.Fill(offJet, eventWeight);
	  offJetHists_L_matchedCaloJet.Fill(*matchedJetCalo, eventWeight);
	}

	// 
	// If pass CVS working point
	//
	if(matchedJetCalo->m_csv >= 0.8484){
	  offJetHists_matchedCalocsvTag.Fill(offJet, eventWeight);
	  offJetHists_matchedCalocsvTagJet.Fill(*matchedJetCalo, eventWeight);
	}

	// 
	// If pass DeepCVS working point
	//
	if(matchedJetCalo->m_deepcsv >= 0.6324){
	  offJetHists_matchedCaloDeepcsvTag.Fill(offJet, eventWeight);
	  offJetHists_matchedCaloDeepcsvTagJet.Fill(*matchedJetCalo, eventWeight);
	}

      }//m_matchedJet

    
    }//offJets


   
 
    
  }// Events 




  return 0;
}
