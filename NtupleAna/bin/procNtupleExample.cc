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
  fwlite::InputSource inputHandler_(process); fwlite::OutputFiles outputHandler_(process);


  // book a set of histograms
  fwlite::TFileService fs = fwlite::TFileService(outputHandler_.file());
  TFileDirectory dir = fs.mkdir("analyzeBasicPat");

  std::cout << " In procNtupleExample " << std::endl;

  TChain* tree = new TChain("tree");


  for(unsigned int iFile=0; iFile<inputHandler_.files().size(); ++iFile){
    // open input file (can be located on castor)
    std::cout << "inputFile is " << inputHandler_.files()[iFile].c_str() << std::endl;

    //TFile* inFile = TFile::Open(inputFiles_[iFile].c_str());
    //if( inFile ){
    tree->Add(inputHandler_.files()[iFile].c_str());
    //}
  }

  
  float runNumber_arr[1] = {0};
  float eventNumber_arr[1] = {0};
  
  tree->SetBranchAddress("run", runNumber_arr);
  tree->SetBranchAddress("evt", eventNumber_arr);


  int nEventThisFile = tree->GetEntries();
  std::cout <<  "Number of input events: " << nEventThisFile << std::endl;


  for(int entry = 0; entry<nEventThisFile; entry++){
    std::cout << "Processed .... "<<entry<<" Events"<<std::endl;
    tree->GetEntry( entry );

    std::cout << "RunNumber: "  << runNumber_arr[0] << std::endl;
    std::cout << "EventNumber: " << eventNumber_arr[0] << std::endl;

  }



//    fwlite::Event ev(inFile);
//    fwlite::Handle<LumiSummary> summary;
//    
//    std::cout << "----------- Accessing by event ----------------" << std::endl;
//    
//    // get run and luminosity blocks from events as well as associated 
//    // products. (This works for both ChainEvent and MultiChainEvent.)
//    for(ev.toBegin(); !ev.atEnd(); ++ev){
//	// get the Luminosity block ID from the event
//	std::cout << " Luminosity ID " << ev.getLuminosityBlock().id() << std::endl;
//	// get the Run ID from the event
//	std::cout <<" Run ID " << ev.getRun().id()<< std::endl;
//	// get the Run ID from the luminosity block you got from the event
//	std::cout << "Run via lumi " << ev.getLuminosityBlock().getRun().id() << std::endl;
//	// get the integrated luminosity (or any luminosity product) from 
//	// the event
//	summary.getByLabel(ev.getLuminosityBlock(),"lumiProducer");
//    }
//    
//    std::cout << "----------- Accessing by lumi block ----------------" << std::endl;
//    
//    double lumi_tot = 0.0;
//    // loop over luminosity blocks (in analogy to looping over events)
//    fwlite::LuminosityBlock ls(inFile);
//    for(ls.toBegin(); !ls.atEnd(); ++ls){
//	summary.getByLabel(ls,"lumiProducer");
//	std::cout  << ls.id() << " Inst.  Luminosity = " << summary->avgInsRecLumi() << std::endl;
//	// get the associated run from this lumi
//	std::cout << "Run from lumi " << ls.getRun().id() << std::endl;
//	// add up the luminosity by lumi block
//	lumi_tot += summary->avgInsRecLumi();
//    }
//    // print the result
//    std::cout << "----------------------------------------------------" << std::endl;
//    std::cout << "Total luminosity from lumi sections = " << lumi_tot   << std::endl;
//    std::cout << "----------------------------------------------------" << std::endl;
//    
//    std::cout << "----------- Accessing by run ----------------" << std::endl;
//    
//    // do the same for runs
//    fwlite::Run r(inFile);
//    for(r.toBegin(); !r.atEnd(); ++r) {
//	std::cout << "Run " << r.id() << std::endl;
//    }
//    // close input file
//    inFile->Close();
//  }

//  }
  return 0;
}
