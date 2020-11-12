
#include <iostream>
#include <iomanip>
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


#include "FWCore/PythonParameterSet/interface/MakePyBind11ParameterSets.h"



#include "PhysicsTools/FWLite/interface/TFileService.h"

#include "TriggerStudies/NtupleAna/interface/HH4bAnalysis.h"
using namespace TriggerStudies;

int main(int argc, char * argv[]){

  //
  // load framework libraries
  //
  gSystem->Load( "libFWCoreFWLite" );
  FWLiteEnabler::enable();

  //
  // parse arguments
  //
  if ( argc < 2 ) {
    std::cout << "Usage : " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }

  //
  // get the python configuration
  //
  const edm::ParameterSet& process    = edm::cmspybind11::readPSetsFrom(argv[1], argc, argv)->getParameter<edm::ParameterSet>("process");

  const edm::ParameterSet& parameters = process.getParameter<edm::ParameterSet>("HH4bAnalyzer");
  bool debug = parameters.getParameter<bool>("debug");
  int skipEvents = parameters.getParameter<int>("skipEvents");
  std::vector<std::string> filesAOD = parameters.getParameter<std::vector<std::string> >("fileNamesAOD");

  //NANOAOD Input source
  fwlite::InputSource inputHandler(process); 

  //
  //  Add RAW Files 
  //
  TChain* treeRAW     = new TChain("btagana/ttree");
  for(unsigned int iFile=0; iFile<inputHandler.files().size(); ++iFile){
    std::cout << "           Input RAW File: " << inputHandler.files()[iFile].c_str() << std::endl;
    int e = treeRAW    ->AddFile(inputHandler.files()[iFile].c_str());
    if(e!=1){ std::cout << "ERROR" << std::endl; return 1;}
    if(debug) std::cout<<"Added to TChain"<<std::endl;
  }

  
  //
  //  Add AOD Files 
  //
  TChain* treeAOD     = new TChain("btagana/ttree");
  for(unsigned int iFile=0; iFile<filesAOD.size(); ++iFile){
    std::cout << "           Input AOD File: " << filesAOD[iFile].c_str() << std::endl;
    int e = treeAOD    ->AddFile(filesAOD[iFile].c_str());
    if(e!=1){ std::cout << "ERROR" << std::endl; return 1;}
    if(debug) std::cout<<"Added to TChain"<<std::endl;
  }
  

  //Histogram output
  fwlite::OutputFiles histOutput(process);
  std::cout << "Event Loop Histograms: " << histOutput.file() << std::endl;
  fwlite::TFileService fsh = fwlite::TFileService(histOutput.file());
    
  //
  // Define analysis and run event loop
  //
  std::cout << "Initialize analysis: ";
  
  std::cout << "HH4bAnalysis " << std::endl;
  HH4bAnalysis a = HH4bAnalysis(treeRAW, treeAOD, fsh, debug);

  int maxEvents = inputHandler.maxEvents();
  a.eventLoop(maxEvents, skipEvents);
  
  std::cout << std::endl;
  std::cout << "Done Event Loop" << std::endl;
  return 0;
}
