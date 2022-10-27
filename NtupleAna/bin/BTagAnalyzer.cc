
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

#include "TriggerStudies/NtupleAna/interface/BTagAnalysis.h"

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
  double minJetPt = parameters.getParameter<double>("minJetPt");
  double minJetAbsEta = parameters.getParameter<double>("minJetAbsEta");
  double maxJetAbsEta = parameters.getParameter<double>("maxJetAbsEta");
  double minJetDeepJet = parameters.getParameter<double>("minJetDeepJet");
  bool isMC  = parameters.getParameter<bool>("isMC");
  bool doLeptonSel = parameters.getParameter<bool>("doLeptonSel");
  int histogramming = parameters.getParameter<int>("histogramming");
  int skipEvents = parameters.getParameter<int>("skipEvents");
  std::string year = parameters.getParameter<std::string>("year");
  std::string tree1Name = parameters.getParameter<std::string>("tree1Name");
  std::string tree2Name = parameters.getParameter<std::string>("tree2Name");
  std::vector<std::string> filesTree2 = parameters.getParameter<std::vector<std::string> >("fileNamesTree2");
  std::string PUFileName = parameters.getParameter<std::string>("puFile");
  std::string jetDetailString = parameters.getParameter<std::string>("jetDetailString");
  std::string pfJetName = parameters.getParameter<std::string>("pfJetName");

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
  //  Add Tree1 Files
  //
  TChain* treeTree1     = new TChain(tree1Name.c_str());
  for(unsigned int iFile=0; iFile<inputHandler.files().size(); ++iFile){
    std::cout << "           Input Tree1 File: " << inputHandler.files()[iFile].c_str() << std::endl;
    int e = treeTree1    ->AddFile(inputHandler.files()[iFile].c_str());
    if(e!=1){ std::cout << "ERROR" << std::endl; return 1;}
    if(debug) std::cout<<"Added to TChain"<<std::endl;
  }


  //
  //  Add Tree2 Files
  //
  TChain* treeTree2     = nullptr;
  if(filesTree2.size()){
    treeTree2     = new TChain(tree2Name.c_str());
    for(unsigned int iFile=0; iFile<filesTree2.size(); ++iFile){
      std::cout << "           Input Tree2 File: " << filesTree2[iFile].c_str() << std::endl;
      int e = treeTree2    ->AddFile(filesTree2[iFile].c_str());
      if(e!=1){ std::cout << "ERROR" << std::endl; return 1;}
      if(debug) std::cout<<"Added to TChain"<<std::endl;
    }
  }

  //Histogram output
  fwlite::OutputFiles histOutput(process);
  std::cout << "Event Loop Histograms: " << histOutput.file() << std::endl;
  fwlite::TFileService fsh = fwlite::TFileService(histOutput.file());

  //
  // Define analysis and run event loop
  //
  std::cout << "Initialize analysis: ";

  std::cout << "BTagAnalysis with minJetPt " << minJetPt;
  std::cout << "\t minJetAbsEta " << minJetAbsEta << std::endl;
  std::cout << "\t maxJetAbsEta " << maxJetAbsEta << std::endl;
  std::cout << "\t minJetDeepJet " << minJetDeepJet << std::endl;
    
  BTagAnalysis a = BTagAnalysis(treeTree1, treeTree2, fsh, isMC, year, histogramming, debug, PUFileName, jetDetailString, nnParameters, pfJetName);
  a.minJetPt       = minJetPt;
  a.minJetAbsEta   = minJetAbsEta;
  a.maxJetAbsEta   = maxJetAbsEta;
  a.minJetDeepJet  = minJetDeepJet;
    

  a.doLeptonSel = doLeptonSel;
  //if(!isMC){
  //  a.lumiMask = lumiMask;
  //  std::string lumiData = parameters.getParameter<std::string>("lumiData");
  //  a.getLumiData(lumiData);
  //}
  int maxEvents = inputHandler.maxEvents();
  a.eventLoop(maxEvents, skipEvents);

  std::cout << std::endl;
  std::cout << "Done Event Loop" << std::endl;
  return 0;
}
