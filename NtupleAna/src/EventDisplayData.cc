#include <iostream>
#include <fstream>
#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/EventDisplayData.h"

using namespace std;
using namespace NtupleAna;
namespace pt = boost::property_tree;


EventDisplayData::EventDisplayData(string name) : m_name(name) {
  
  for(string jetName : m_jetNames){
    m_OneEvent_info.insert(make_pair(jetName,pt::ptree()));
    m_AllEvent_info.insert(make_pair(jetName,pt::ptree()));
  }


  for(string trkName : m_trkNames){
    m_OneEvent_info.insert(make_pair(trkName,pt::ptree()));
    m_AllEvent_info.insert(make_pair(trkName,pt::ptree()));
  }

}


void
EventDisplayData::AddJet (string jetName, const JetData& jetData, bool doTracks, bool debug ){

  if(debug){
    cout << "In Add Jet " << jetName << endl;
    cout << "\tAdding " << jetData.m_vec.Eta() << " " << jetData.m_vec.Phi() << " " << jetData.m_vec.Pt() << endl; 
  }

  // Create an unnamed node containing the value                                                                                                                                                          
  pt::ptree var_node;
  pt::ptree jet_node;
  var_node.put("", jetData.m_vec.Eta());
  jet_node.push_back(std::make_pair("", var_node));
 
  var_node.put("", jetData.m_vec.Phi());
  jet_node.push_back(std::make_pair("", var_node));
 
  var_node.put("", jetData.m_vec.Pt());
  jet_node.push_back(std::make_pair("", var_node));

  m_OneEvent_info[jetName].push_back(std::make_pair("", jet_node));


  if(doTracks){
    for(const TrackData& tData : jetData.m_tracks){
      AddTrk(jetName+"_Trks",tData, debug);
    }
  }
    
  
  return;
}


void
EventDisplayData::AddTrk (string trkName, const TrackData& trkData, bool debug){
  if(debug){
    cout << "In Add Trk " << trkName << endl;
    cout << "\tAdding " << trkData.m_vec.Eta() << " " << trkData.m_vec.Phi() << " " << trkData.m_vec.Pt() << endl;
  }

  // Create an unnamed node containing the value                                                                                                                                                          
  pt::ptree var_node;
  pt::ptree trk_node;
  var_node.put("", trkData.m_vec.Eta());
  trk_node.push_back(std::make_pair("", var_node));
 
  var_node.put("", trkData.m_vec.Phi());
  trk_node.push_back(std::make_pair("", var_node));
 
  var_node.put("", trkData.m_vec.Pt());
  trk_node.push_back(std::make_pair("", var_node));

  m_OneEvent_info[trkName].push_back(std::make_pair("", trk_node));

  return;
}


void
EventDisplayData::NewEvent (){

  m_nDisplays += 1;

  for(string jetName : m_jetNames){
    m_AllEvent_info[jetName].push_back(std::make_pair(std::to_string(m_nDisplays), m_OneEvent_info[jetName]));    
    m_OneEvent_info[jetName].clear();
  }

  for(string trkName : m_trkNames){
    m_AllEvent_info[trkName].push_back(std::make_pair(std::to_string(m_nDisplays), m_OneEvent_info[trkName]));    
    m_OneEvent_info[trkName].clear();
  }


  return;
}

void
EventDisplayData::Write (){

  for(string jetName : m_jetNames){  
    oroot.add_child(jetName, m_AllEvent_info[jetName]);
  }

  for(string trkName : m_trkNames){  
    oroot.add_child(trkName, m_AllEvent_info[trkName]);
  }

//to_string(
  ofstream myfile;
  myfile.open ("example.txt");

  pt::write_json(myfile, oroot);
  myfile.close();
  //with open('Events_'+self.name+'.txt', 'w') as outfile:  
  //    json.dump(self.eventDisplayData, outfile)    
  return;
}
