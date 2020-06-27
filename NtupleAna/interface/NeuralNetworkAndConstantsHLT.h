// -*- C++ -*-
#if !defined(NEURALNETWORKANDCONSTANTS_H)
#define NEURALNETWORKANDCONSTANTS_H

#include "DataFormats/BTauReco/interface/TaggingVariable.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"

//from lwtnn
#include "lwtnn/LightweightNeuralNetwork.hh"
#include "lwtnn/parse_json.hh"


namespace TriggerStudies {

  // From https://github.com/cms-sw/cmssw/blob/6ec5f2f206b43e0996b67f4d51ae3136bc5edf92/RecoBTag/Combined/plugins/DeepFlavourJetTagsProducer.cc#L58
  struct MVAVar {
    std::string name;
    reco::btau::TaggingVariableName id;
    int index;
    double default_value;
  };

  class NeuralNetworkAndConstants {
  public:
    NeuralNetworkAndConstants(const edm::ParameterSet&);

    std::unique_ptr<const lwt::LightweightNeuralNetwork> const& neural_network() const { return neural_network_; }
    std::vector<std::string> const& outputs() const { return outputs_; }
    bool check_sv_for_defaults() const { return check_sv_for_defaults_; }
    std::map<std::string, std::string> const& toadd() const { return toadd_; }
    std::vector<MVAVar> const& variables() const { return variables_; }
    lwt::ValueMap compute(const nTupleAnalysis::jetPtr& jet, bool debug = false);

  private:
    std::unique_ptr<const lwt::LightweightNeuralNetwork> neural_network_;
    std::vector<std::string> outputs_;
    bool check_sv_for_defaults_;
    std::map<std::string, std::string> toadd_;
    std::vector<MVAVar> variables_;
  };


}
#endif // NEURALNETWORKANDCONSTANTS_H
