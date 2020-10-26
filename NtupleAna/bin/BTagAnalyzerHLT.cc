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

// Uncomment for SCL6
//#define BTagAnalysis_SLC6 1  

#if defined BTagAnalysis_SLC6
#include "nTupleAnalysis/baseClasses/interface/myParameterSetReader.h"
#else
#include "FWCore/PythonParameterSet/interface/MakePyBind11ParameterSets.h"
#endif 

#include "PhysicsTools/FWLite/interface/TFileService.h"

#include "TriggerStudies/NtupleAna/interface/BTagAnalysisHLT.h"
#include "TriggerStudies/NtupleAna/interface/TrigTurnOnStudy.h"
#include "TriggerStudies/NtupleAna/interface/TrigTurnOnStudyHLT.h"
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
#if defined BTagAnalysis_SLC6
  const edm::ParameterSet& process    = edm::readPSetsFrom(argv[1], argc, argv)->getParameter<edm::ParameterSet>("process");
#else
  const edm::ParameterSet& process    = edm::cmspybind11::readPSetsFrom(argv[1], argc, argv)->getParameter<edm::ParameterSet>("process");
#endif 

  const edm::ParameterSet& parameters = process.getParameter<edm::ParameterSet>("BTagAnalyzer");
  bool debug = parameters.getParameter<bool>("debug");
  bool isMC  = parameters.getParameter<bool>("isMC");
  int histogramming = parameters.getParameter<int>("histogramming");
  int skipEvents = parameters.getParameter<int>("skipEvents");
  std::string year = parameters.getParameter<std::string>("year");
  std::string jetDetailString = parameters.getParameter<std::string>("jetDetailString");
  const edm::ParameterSet& nnParameters = process.getParameter<edm::ParameterSet>("NNConfig");

  //
  //lumiMask
  //
  const edm::ParameterSet& inputs = process.getParameter<edm::ParameterSet>("inputs");   
  std::vector<edm::LuminosityBlockRange> lumiMask;
  if( !isMC && inputs.exists("lumisToProcess") ){
    std::vector<edm::LuminosityBlockRange> const & lumisTemp = inputs.getUntrackedParameter<std::vector<edm::LuminosityBlockRange> > ("lumisToProcess");
    lumiMask.resize( lumisTemp.size() );
    copy( lumisTemp.begin(), lumisTemp.end(), lumiMask.begin() );
  }
  if(debug) for(auto lumiID: lumiMask) std::cout<<"lumiID "<<lumiID<<std::endl;

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

  //Histogram output
  fwlite::OutputFiles histOutput(process);
  std::cout << "Event Loop Histograms: " << histOutput.file() << std::endl;
  fwlite::TFileService fsh = fwlite::TFileService(histOutput.file());
    
  //
  // Define analysis and run event loop
  //
  std::cout << "Initialize analysis: ";
  std::cout << "BTagAnalysis (HLT) " << std::endl;
  BTagAnalysisHLT a = BTagAnalysisHLT(treeRAW, fsh, isMC, year, histogramming, debug, jetDetailString, nnParameters);
  int maxEvents = inputHandler.maxEvents();
  a.eventLoop(maxEvents, skipEvents);
  
  std::cout << std::endl;
  std::cout << "Done Event Loop (HLT)" << std::endl;
  return 0;
}
