#include <iostream>
#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/EventDisplayData.h"

using namespace std;
using namespace NtupleAna;
namespace pt = boost::property_tree;


EventDisplayData::EventDisplayData(std::string name) : m_name(name) {
  
  for(std::string jetName : m_jetNames){
    OneEvent_info.insert(std::make_pair(jetName,pt::ptree()));
    AllEvent_info.insert(std::make_pair(jetName,pt::ptree()));
  }

}


void
EventDisplayData::AddJet (std::string jetName, const JetData& jetData, bool doTracks){

  std::cout << "In Add Jet " << jetName << std::endl;
  std::cout << "\tAdding " << jetData.m_vec.Eta() << " " << jetData.m_vec.Phi() << " " << jetData.m_vec.Pt() << std::endl;

  JetVector thisData = JetVector();
  // Create an unnamed node containing the value                                                                                                                                                          
  pt::ptree var_node;
  pt::ptree jet_node;
  var_node.put("", jetData.m_vec.Eta());
  jet_node.push_back(std::make_pair("", var_node));

  var_node.put("", jetData.m_vec.Phi());
  jet_node.push_back(std::make_pair("", var_node));

  var_node.put("", jetData.m_vec.Pt());
  jet_node.push_back(std::make_pair("", var_node));

  // Add this node to the list.                                                                                                                                                                           
  OneEvent_info[jetName].push_back(std::make_pair("", jet_node));

  //
  //      if doTracks:
  //          for tData in jData.tracks:
  //              self.AddTrk(jType+"_Trks",tData)


  
  return;
}


void
EventDisplayData::AddTrk (std::string trackName, const TrackData& trkData){

  //def AddTrk(self, tType, tData):
  //self.eventDisplayData[tType][int(self.nDisplays)].append((tData.eta,tData.phi,tData.momentum))
  return;
}


void
EventDisplayData::NewEvent (){

  m_nDisplays += 1;
  std::cout << "In NewEvent " << m_nDisplays << std::endl;

  for(std::string jetName : m_jetNames){
    AllEvent_info[jetName].push_back(std::make_pair(std::to_string(m_nDisplays), OneEvent_info[jetName]));
  }
  //oroot.add_child(, jets_node);

  //pt::write_json(std::cout, OneEvent_info["offJetAll"]);

  //"offJetAll"

  //m_eventDisplayData.insert["pfJet"][int(m_nDisplays)] = []
  //      m_eventDisplayData["pfJet_Trks"][int(m_nDisplays)] = []
  //
  //      m_eventDisplayData["offMatchJet"][int(m_nDisplays)] = []
  //
  //      m_eventDisplayData["offJet"][int(m_nDisplays)] = []
  //      m_eventDisplayData["offJet_Trks"][int(m_nDisplays)] = []
  //      m_eventDisplayData["offJet_TrksMatch"][int(m_nDisplays)] = []
  //      m_eventDisplayData["offJet_TrksNoMatch"][int(m_nDisplays)] = []
  //
  //      m_eventDisplayData["offJetAll"][int(m_nDisplays)] = []
  //      m_eventDisplayData["offJetAll_Trks"][int(m_nDisplays)] = []



  return;
}

void
EventDisplayData::Write (){

  for(std::string jetName : m_jetNames){  
    oroot.add_child(jetName, AllEvent_info[jetName]);
  }
  pt::write_json(std::cout, oroot);
  //with open('Events_'+self.name+'.txt', 'w') as outfile:  
  //    json.dump(self.eventDisplayData, outfile)    
  return;
}
