// -*- C++ -*-

#if !defined(EventDisplayData_H)
#define EventDisplayData_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "TriggerStudies/NtupleAna/interface/JetData.h"


//
//  // Some values
//  int height = 10;
//  oroot.put("height", height);
//  oroot.put("some.complex.path", "bonjour");
//  pt::write_json(std::cout, oroot);
//

namespace NtupleAna {

  typedef std::vector<float> JetVector;
  
  class EventDisplayData {
    
  public: 
    
    // Create a root
    boost::property_tree::ptree oroot;
    
    std::map<std::string, boost::property_tree::ptree> OneEvent_info;
    std::map<std::string, boost::property_tree::ptree> AllEvent_info;
    //boost::property_tree::ptree offJetAllOneEvent_node;
    //boost::property_tree::ptree offJetAll_node;

    int m_nDisplays = 0;

    std::string m_name;

    std::vector<std::string> m_jetNames = {"offJetAll","offJet","pfJet"};
    
//  map<std::string, std::map<int, 
//    self.eventDisplayData = {}
//    self.eventDisplayData["pfJet"]  = {}
//    self.eventDisplayData["pfJet_Trks"]  = {}
//
//    self.eventDisplayData["offMatchJet"]  = {}
//
//    self.eventDisplayData["offJet"]  = {}
//    self.eventDisplayData["offJet_Trks"]  = {}
//    self.eventDisplayData["offJet_TrksNoMatch"]  = {}
//    self.eventDisplayData["offJet_TrksMatch"]  = {}
//
//    self.eventDisplayData["offJetAll"]  = {}
//    self.eventDisplayData["offJetAll_Trks"]  = {}

  public:

    EventDisplayData(std::string name);
    
    ~EventDisplayData() {}; 

    void AddJet (std::string jetName, const JetData& jetData, bool doTracks=false);
    void AddTrk (std::string trackName, const TrackData& trkData);

    void NewEvent();

    void Write();
  };

}
#endif // EventDisplayData_H
