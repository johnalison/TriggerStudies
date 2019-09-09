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

    m_nPV      = m_dir.make<TH1F>("nPV",  "nPV  ;nPV ;Entries",  100,-0.5, 99.5);
    m_pu       = m_dir.make<TH1F>("pu",   "pu   ;pu  ;Entries",  100,-0.5, 99.5);
   
} 

EventHists::~EventHists() {} 


void
EventHists::Fill (const EventDataOLD& eventData, float eventWeight){

  m_PVzDiff_offVsTrue  ->Fill(eventData.VerticesOff - eventData.trueVertex       , eventWeight);
  m_PVzDiff_FastVsOff  ->Fill(eventData.FastPrimaryVertex - eventData.VerticesOff, eventWeight);
  m_PVzDiff_FPVPixVsOff->Fill(eventData.FPVPixelVertices - eventData.VerticesOff , eventWeight);
  m_PVzDiff_PixVsOff   ->Fill(eventData.PixelVertices - eventData.VerticesOff    , eventWeight);
  m_PVzDiff_PFVsOff    ->Fill(eventData.VerticesPF - eventData.VerticesOff       , eventWeight);
  m_PVzDiff_L3VsOff    ->Fill(eventData.VerticesL3 - eventData.VerticesOff       , eventWeight);

  m_nPV -> Fill(eventData.nPV, eventWeight);
  m_pu  -> Fill(eventData.pu , eventWeight);

  return;
}


