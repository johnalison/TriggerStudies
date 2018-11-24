#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/EventData.h"

using namespace std;
using namespace NtupleAna;


EventData::EventData() {} 

EventData::~EventData() {} 


void
EventData::SetBranchAddress (TChain* intree){

  intree->SetBranchAddress("run",       runNumber_arr);
  intree->SetBranchAddress("evt",       eventNumber_arr);
  intree->SetBranchAddress("FastPrimaryVertex",  FastPrimaryVertex_arr);
  intree->SetBranchAddress("FPVPixelVertices" ,  FPVPixelVertices_arr);
  intree->SetBranchAddress("PixelVertices"    ,  PixelVertices_arr);
  intree->SetBranchAddress("VerticesPF"       ,  VerticesPF_arr);
  intree->SetBranchAddress("VerticesL3"       ,  VerticesL3_arr);
  intree->SetBranchAddress("VerticesOff"      ,  VerticesOff_arr);
  intree->SetBranchAddress("nPV"              ,  nPV_arr);
  intree->SetBranchAddress("trueVertex"       ,  trueVertex_arr);
  
  return;
}


void
EventData::SetEvent (){

  runNumber          = runNumber_arr        [0];         
  eventNumber        = eventNumber_arr      [0];
  FastPrimaryVertex  = FastPrimaryVertex_arr[0];
  FPVPixelVertices   = FPVPixelVertices_arr [0];
  PixelVertices      = PixelVertices_arr    [0];
  VerticesPF         = VerticesPF_arr       [0];
  VerticesL3         = VerticesL3_arr       [0];
  VerticesOff        = VerticesOff_arr      [0];
  nPV                = nPV_arr              [0];
  trueVertex         = trueVertex_arr       [0];


  return;
}
