// -*- C++ -*-

#if !defined(EventDisplayData_H)
#define EventDisplayData_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


#include "TriggerStudies/NtupleAna/interface/JetData.h"



namespace NtupleAna {

  class EventDisplayData {


  public: 
    
    // Create a root
    boost::property_tree::ptree oroot;
     
    std::map<std::string, boost::property_tree::ptree> m_OneEvent_info;
    std::map<std::string, boost::property_tree::ptree> m_AllEvent_info;

    int m_nDisplays = 0;


    std::string m_name;

    std::vector<std::string> m_jetNames = {"offJetAll","offJet","offMatchJet","pfJet"};
    std::vector<std::string> m_trkNames = {"offJetAll_Trks","offJet_Trks","offJet_TrksNoMatch","offJet_TrksMatch","pfJet_Trks"};
    
  public:

    EventDisplayData(std::string name);
    
    ~EventDisplayData() {}; 

    void AddJet (std::string jetName, const JetData& jetData, bool doTracks=false, bool debug=false);
    void AddTrk (std::string trkName, const TrackData& trkData, bool debug=false);

    void NewEvent();

    void Write();
  };

}
#endif // EventDisplayData_H
