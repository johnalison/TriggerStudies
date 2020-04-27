#include "TriggerStudies/NtupleAna/interface/NeuralNetworkAndConstants.h"
#include <fstream>
#include <set>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp> 


using namespace TriggerStudies;
using std::cout; using std::endl; 
using std::vector;  using std::map; using std::string; using std::set;


// From https://github.com/cms-sw/cmssw/blob/6ec5f2f206b43e0996b67f4d51ae3136bc5edf92/RecoBTag/Combined/plugins/DeepFlavourJetTagsProducer.cc#L119
NeuralNetworkAndConstants::NeuralNetworkAndConstants(const edm::ParameterSet& iConfig) {

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

    variables_.push_back(var);
  }
}


lwt::ValueMap NeuralNetworkAndConstants::compute(const nTupleAnalysis::jetPtr& jet){
  
  lwt::ValueMap inputs_;  //typedef of unordered_map<string, float>
  //neuralNet->check_sv_for_defaults();
      
  inputs_["jetPt"] = 12.1284;
  inputs_["jetEta"] = -1.50645;
  inputs_["jetNSecondaryVertices"] = 0;
  inputs_["trackSumJetEtRatio"] = 0.242598;
  inputs_["trackSumJetDeltaR"] = 0.0971793;
  inputs_["vertexCategory"] = 2;
  inputs_["trackSip2dValAboveCharm"] = -1;
  inputs_["trackSip2dSigAboveCharm"] = -1;
  inputs_["trackSip3dValAboveCharm"] = -1;
  inputs_["trackSip3dSigAboveCharm"] = -1;
  inputs_["jetNSelectedTracks"] = 2;
  inputs_["jetNTracksEtaRel"] = 0;
  inputs_["trackJetDist_0"] =  -0.00630845;
  inputs_["trackJetDist_1"] =  -0.00272192;
  inputs_["trackJetDist_2"] =  0;
  inputs_["trackJetDist_3"] =  0;
  inputs_["trackJetDist_4"] =  0;
  inputs_["trackJetDist_5"] =  0;
  inputs_["trackPtRel_0"] =  0.210688;
  inputs_["trackPtRel_1"] =  0.10662;
  inputs_["trackPtRel_2"] =  0;
  inputs_["trackPtRel_3"] =  0;
  inputs_["trackPtRel_4"] =  0;
  inputs_["trackPtRel_5"] =  0;
  inputs_["trackDeltaR_0"] =  0.121708;
  inputs_["trackDeltaR_1"] =  0.097125;
  inputs_["trackDeltaR_2"] =  0;
  inputs_["trackDeltaR_3"] =  0;
  inputs_["trackDeltaR_4"] =  0;
  inputs_["trackDeltaR_5"] =  0;
  inputs_["trackPtRatio_0"] =  0.0539723;
  inputs_["trackPtRatio_1"] =  0.042573;
  inputs_["trackPtRatio_2"] =  0;
  inputs_["trackPtRatio_3"] =  0;
  inputs_["trackPtRatio_4"] =  0;
  inputs_["trackPtRatio_5"] =  0;
  inputs_["trackSip3dSig_0"] = 1.82768;
  inputs_["trackSip3dSig_1"] = 1.95659;
  inputs_["trackSip3dSig_2"] = 0;
  inputs_["trackSip3dSig_3"] = 0;
  inputs_["trackSip3dSig_4"] = 0;
  inputs_["trackSip3dSig_5"] = 0;
  inputs_["trackSip2dSig_0"] = 1.81956;
  inputs_["trackSip2dSig_1"] = 0.590408;
  inputs_["trackSip2dSig_2"] = 0;
  inputs_["trackSip2dSig_3"] = 0;
  inputs_["trackSip2dSig_4"] = 0;
  inputs_["trackSip2dSig_5"] = 0;
  inputs_["trackDecayLenVal_0"] = 0.0458966;
  inputs_["trackDecayLenVal_1"] = 0.263346;
  inputs_["trackDecayLenVal_2"] = 0;
  inputs_["trackDecayLenVal_3"] = 0;
  inputs_["trackDecayLenVal_4"] = 0;
  inputs_["trackDecayLenVal_5"] = 0;
  inputs_["trackEtaRel_0"] = 0;
  inputs_["trackEtaRel_1"] = 0;
  inputs_["trackEtaRel_2"] = 0;
  inputs_["trackEtaRel_3"] = 0;
  inputs_["vertexMass"] = 0;
  inputs_["vertexNTracks"] = 0;
  inputs_["vertexEnergyRatio"] = 0;
  inputs_["vertexJetDeltaR"] = 0;
  inputs_["flightDistance2dVal"] = 0;
  inputs_["flightDistance2dSig"] = 0;
  inputs_["flightDistance3dVal"] = 0;
  inputs_["flightDistance3dSig"] = 0;


  return neural_network()->compute(inputs_);;
}
