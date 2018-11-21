#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/EventHists.h"

using namespace std;
using namespace NtupleAna;


EventHists::EventHists(std::string name, fwlite::TFileService& fs) {

    m_dir = fs.mkdir(name);
    m_PVzDiff_offVsTrue   = new VtxDiffHists("OffVsTrue"  , m_dir );
    m_PVzDiff_FastVsOff   = new VtxDiffHists("FastVsOff"  , m_dir );
    m_PVzDiff_FPVPixVsOff = new VtxDiffHists("FPVPixVsOff", m_dir );
    m_PVzDiff_PixVsOff    = new VtxDiffHists("PixVsOff"   , m_dir );
    m_PVzDiff_PFVsOff     = new VtxDiffHists("PFVsOff"    , m_dir );
    m_PVzDiff_L3VsOff     = new VtxDiffHists("L3VsOff"    , m_dir );

} 

EventHists::~EventHists() {} 


void
EventHists::Fill (const EventData& eventData){

  m_PVzDiff_offVsTrue  ->Fill(eventData.VerticesOff - eventData.trueVertex);
  m_PVzDiff_FastVsOff  ->Fill(eventData.FastPrimaryVertex - eventData.VerticesOff);
  m_PVzDiff_FPVPixVsOff->Fill(eventData.FPVPixelVertices - eventData.VerticesOff);
  m_PVzDiff_PixVsOff   ->Fill(eventData.PixelVertices - eventData.VerticesOff);
  m_PVzDiff_PFVsOff    ->Fill(eventData.VerticesPF - eventData.VerticesOff);
  m_PVzDiff_L3VsOff    ->Fill(eventData.VerticesL3 - eventData.VerticesOff);

  return;
}


