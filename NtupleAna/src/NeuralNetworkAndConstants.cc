#include "TriggerStudies/NtupleAna/interface/NeuralNetworkAndConstants.h"
#include <fstream>
#include <set>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp> 
#include "nTupleAnalysis/baseClasses/interface/btaggingData.h"

using namespace TriggerStudies;
using std::cout; using std::endl; 
using std::vector;  using std::map; using std::string; using std::set;


// From https://github.com/cms-sw/cmssw/blob/6ec5f2f206b43e0996b67f4d51ae3136bc5edf92/RecoBTag/Combined/plugins/DeepFlavourJetTagsProducer.cc#L119
NeuralNetworkAndConstants::NeuralNetworkAndConstants(const edm::ParameterSet& iConfig) {
  cout << " Loading NN using variables " << endl;
  bool mean_padding = iConfig.getParameter<bool>("meanPadding");

  //parse json
  edm::FileInPath nnconfig = iConfig.getParameter<edm::FileInPath>("NNConfig");
  std::ifstream jsonfile(nnconfig.fullPath());
  auto config = lwt::parse_json(jsonfile);

  //create NN and store the output names for the future
  neural_network_ =
    std::make_unique<const lwt::LightweightNeuralNetwork>(config.inputs, config.layers, config.outputs);

  outputs_ = config.outputs;
  set<string> outset(outputs_.begin(), outputs_.end());

  //in case we want to merge some different outputs together
  edm::ParameterSet toaddPSet = iConfig.getParameter<edm::ParameterSet>("toAdd");
  for (auto const& output : toaddPSet.getParameterNamesForType<string>()) {
    string target = toaddPSet.getParameter<string>(output);
    if (outset.find(output) == outset.end())
      throw cms::Exception("RuntimeError") << "The required output: " << output << " to be added to " << target
					   << " could not be found among the NN outputs" << endl;
    if (outset.find(target) == outset.end())
      throw cms::Exception("RuntimeError") << "The required output: " << target << ", target of addition of "
					   << output << " could not be found among the NN outputs" << endl;
    toadd_[output] = target;
  }

  //get the set-up for the inputs
  for (auto const& input : config.inputs) {
    MVAVar var;
    var.name = input.name;
    //two paradigms
    vector<string> tokens;
    if (var.name != "Jet_JP" && var.name != "Jet_JBP" && var.name != "Jet_SoftMu" && var.name != "Jet_SoftEl") {
      boost::split(tokens, var.name, boost::is_any_of("_"));
    } else {
      tokens.push_back(var.name);
    }
    if (tokens.empty()) {
      throw cms::Exception("RuntimeError")
	<< "I could not parse properly " << input.name << " as input feature" << std::endl;
    }
    var.id = reco::getTaggingVariableName(tokens.at(0));
    //die grafully if the tagging variable is not found!
    if (var.id == reco::btau::lastTaggingVariable) {
      throw cms::Exception("ValueError")
	<< "I could not find the TaggingVariable named " << tokens.at(0)
	<< " from the NN input variable: " << input.name << ". Please check the spelling" << std::endl;
    }
    var.index = (tokens.size() == 2) ? stoi(tokens.at(1)) : -1;
    var.default_value =
      (mean_padding)
      ? 0.
      : -1 * input.offset;  //set default to -offset so that when scaling (val+offset)*scale the outcome is 0
    //for mean padding it is set to zero so that undefined values are assigned -mean/scale
    cout << " \t " << var.name << endl;
    variables_.push_back(var);
  }
}


lwt::ValueMap NeuralNetworkAndConstants::compute(const nTupleAnalysis::jetPtr& jet, bool debug){
  lwt::ValueMap inputs_;  //typedef of unordered_map<string, float>
  //neuralNet->check_sv_for_defaults();

      
  const nTupleAnalysis::tagVarPtr& btagData = jet->tagVars;

  if(btagData->jetNTracks < 1){
    lwt::ValueMap defaultOut = {{"probb",-0.1},{"probbb",0.0}};
    return defaultOut;
  }

  inputs_["jetPt"] = jet->pt;
  inputs_["jetEta"] = jet->eta;
  inputs_["jetAbsEta"] = fabs(jet->eta);
  inputs_["jetNSecondaryVertices"] = btagData->jetNSecondaryVertices;
  inputs_["trackSumJetEtRatio"] = btagData->trackSumJetEtRatio;
  inputs_["trackSumJetDeltaR"] = btagData->trackSumJetDeltaR;
  inputs_["vertexCategory"] = btagData->vertexCategory;
  inputs_["trackSip2dValAboveCharm"] = btagData->trackSip2dValAboveCharm;
  inputs_["trackSip2dSigAboveCharm"] = btagData->trackSip2dSigAboveCharm;
  inputs_["trackSip3dValAboveCharm"] = btagData->trackSip3dValAboveCharm;
  inputs_["trackSip3dSigAboveCharm"] = btagData->trackSip3dSigAboveCharm;

  //cout << btagData->jetNTracksCSV << " vs " << jet->nseltracks << endl;

  inputs_["jetNSelectedTracks"]  = btagData->jetNTracks; 
  inputs_["jetNTracksEtaRel"]    = btagData->jetNTracksEtaRel; // Need
  inputs_["vertexMass"]          = btagData->vertexMass;
  inputs_["vertexNTracks"]       = btagData->vertexNTracks;
  inputs_["vertexJetDeltaR"]     = btagData->vertexJetDeltaR;
  inputs_["vertexEnergyRatio"]   = btagData->vertexEnergyRatio;
  inputs_["flightDistance2dVal"] = btagData->flightDistance2dVal;
  inputs_["flightDistance2dSig"] = btagData->flightDistance2dSig;
  inputs_["flightDistance3dVal"] = btagData->flightDistance3dVal;
  inputs_["flightDistance3dSig"] = btagData->flightDistance3dSig;

  std::stringstream ss;

  float defaultValue = 0.0;
  unsigned int nTracks = jet->trkTagVars.size();
  
  for(unsigned int trkItr = 0; trkItr < 6; ++trkItr){
    ss.str("");
    ss << trkItr;
    
    float trackJetDistVal   = defaultValue;
    float trackPtRelVal     = defaultValue;
    float trackDeltaRVal    = defaultValue;
    float trackPtRatio      = defaultValue;
    float trackSip3dSig     = defaultValue;
    float trackSip2dSig     = defaultValue;
    float trackDecayLenVal  = defaultValue;

    std::string trackJetDistName     = "trackJetDist_" + ss.str();
    std::string trackPtRelName       = "trackPtRel_" + ss.str();
    std::string trackDeltaRName      = "trackDeltaR_" + ss.str();
    std::string trackPtRatioName     = "trackPtRatio_" + ss.str();
    std::string trackSip3dSigName    = "trackSip3dSig_" + ss.str();
    std::string trackSip2dSigName    = "trackSip2dSig_" + ss.str();
    std::string trackDecayLenValName = "trackDecayLenVal_" + ss.str();

    if(trkItr < nTracks){
      const nTupleAnalysis::trkTagVarPtr& thisTrk = jet->trkTagVars.at(trkItr);
      trackJetDistVal  = thisTrk->trackJetDistVal;
      trackPtRelVal    = thisTrk->trackPtRel;
      trackDeltaRVal   = thisTrk->trackDeltaR;
      trackPtRatio     = thisTrk->trackPtRatio;
      trackSip3dSig    = thisTrk->trackSip3dSig;
      trackSip2dSig    = thisTrk->trackSip2dSig;
      trackDecayLenVal = thisTrk->trackDecayLenVal;
    }
    
    inputs_[trackJetDistName     ] = trackJetDistVal;
    inputs_[trackPtRelName       ] = trackPtRelVal;
    inputs_[trackDeltaRName      ] = trackDeltaRVal    ;
    inputs_[trackPtRatioName     ] = trackPtRatio      ;
    inputs_[trackSip3dSigName    ] = trackSip3dSig     ;
    inputs_[trackSip2dSigName    ] = trackSip2dSig     ;
    inputs_[trackDecayLenValName ] = trackDecayLenVal  ;
  }

  for(unsigned int trkEtaRelItr = 0; trkEtaRelItr < 4; ++trkEtaRelItr){
    ss.str("");
    ss << trkEtaRelItr;

    float trackEtaRelVal   = defaultValue;

    std::string trackEtaRelName     = "trackEtaRel_" + ss.str();

    if(trkEtaRelItr < btagData->TagVarCSV_trackEtaRel.size()){
      trackEtaRelVal   = btagData->TagVarCSV_trackEtaRel.at(trkEtaRelItr);
    }

    inputs_[trackEtaRelName] = trackEtaRelVal;// Need
  }

  if(debug){
    for(auto const& var : variables()){
      cout << var.name << " is " << inputs_[var.name] << endl;
    }

    lwt::ValueMap nnout = neural_network()->compute(inputs_);
    cout << "\t" << "probb probbb"  << endl;
    cout << nnout["probb"] << " " <<  nnout["probbb"] << endl;
    cout << "\t sum" << nnout["probb"] + nnout["probbb"] << endl;
    cout << " Input DeepCSV is " << jet->DeepCSV << endl;
  }



  return neural_network()->compute(inputs_);
}
