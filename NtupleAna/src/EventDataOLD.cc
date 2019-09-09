#include "TChain.h"

#include "TriggerStudies/NtupleAna/interface/EventDataOLD.h"

using namespace std;
using namespace NtupleAna;


EventDataOLD::EventDataOLD() {} 

EventDataOLD::~EventDataOLD() {} 


void
EventDataOLD::SetBranchAddress (TChain* intree){
  
  SetBranchAddress(intree,"run",       runNumber_arr);
  SetBranchAddress(intree,"evt",       eventNumber_arr);
  SetBranchAddress(intree,"FastPrimaryVertex",  FastPrimaryVertex_arr);
  SetBranchAddress(intree,"FPVPixelVertices" ,  FPVPixelVertices_arr);
  SetBranchAddress(intree,"PixelVertices"    ,  PixelVertices_arr);
  SetBranchAddress(intree,"VerticesPF"       ,  VerticesPF_arr);
  SetBranchAddress(intree,"VerticesL3"       ,  VerticesL3_arr);
  SetBranchAddress(intree,"VerticesOff"      ,  VerticesOff_arr);


  SetBranchAddress(intree,"nPV"              ,  nPV_arr);
  SetBranchAddress(intree,"pu"               ,  pu_arr);
  SetBranchAddress(intree,"trueVertex"       ,  trueVertex_arr);
  
  
  SetBranchAddress(intree,"HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4",HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4_arr);
  SetBranchAddress(intree,"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4",HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4_arr);

  SetBranchAddress(intree, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v5", HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v5_arr);
  SetBranchAddress(intree, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5", HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5_arr);


  SetBranchAddress(intree, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v6", HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v6_arr);
  SetBranchAddress(intree, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6", HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6_arr);

  SetBranchAddress(intree, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v8", HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v8_arr);
  SetBranchAddress(intree, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8", HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8_arr);


  //SetBranchAddress(intree, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v4",  HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v4_arr );
  //SetBranchAddress(intree, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v6",  HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v6_arr );

  SetBranchAddress(intree,"HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v15", HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v15_arr);
  SetBranchAddress(intree,"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v15", HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v15_arr);       

  SetBranchAddress(intree,"HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v7"    , HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v7_arr);   
  SetBranchAddress(intree,"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v7"    , HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v7_arr);   
  
  SetBranchAddress(intree,"HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1",HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1_arr);
  SetBranchAddress(intree,"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1",HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1_arr);

  SetBranchAddress(intree,"HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2",HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2_arr);
  SetBranchAddress(intree,"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2",HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2_arr);

  SetBranchAddress(intree,"HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3",HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3_arr);
  SetBranchAddress(intree,"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3",HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3_arr);

  SetBranchAddress(intree,"HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v12",HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v12_arr);
  SetBranchAddress(intree,"HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v12",HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v12_arr);


  SetBranchAddress(intree, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v9",  HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v9_arr);
  SetBranchAddress(intree, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9",  HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9_arr);
  SetBranchAddress(intree, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v10", HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v10_arr);
  SetBranchAddress(intree, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10", HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10_arr);
  SetBranchAddress(intree, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v11", HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v11_arr);
  SetBranchAddress(intree, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v11", HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v11_arr);
  SetBranchAddress(intree, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v12", HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v12_arr);
  SetBranchAddress(intree, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v12", HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v12_arr);

  return;
}

void EventDataOLD::SetBranchAddress(TChain* intree, std::string brName, bool* Trigger_arr){
  if(intree->FindBranch(brName.c_str())){
    intree->SetBranchStatus(brName.c_str(), 1);
    intree->SetBranchAddress(brName.c_str(), Trigger_arr);
  }
  
  return;
}

void EventDataOLD::SetBranchAddress(TChain* intree, std::string brName, float* float_arr){
  if(intree->FindBranch(brName.c_str())){
    intree->SetBranchStatus(brName.c_str(), 1);
    intree->SetBranchAddress(brName.c_str(), float_arr);
  }
  
  return;
}


void
EventDataOLD::SetEvent (){

  runNumber          = runNumber_arr        [0];         
  eventNumber        = eventNumber_arr      [0];
  FastPrimaryVertex  = FastPrimaryVertex_arr[0];
  FPVPixelVertices   = FPVPixelVertices_arr [0];
  PixelVertices      = PixelVertices_arr    [0];
  VerticesPF         = VerticesPF_arr       [0];
  VerticesL3         = VerticesL3_arr       [0];
  VerticesOff        = VerticesOff_arr      [0];
  nPV                = nPV_arr              [0];
  pu                 = pu_arr               [0];
  trueVertex         = trueVertex_arr       [0];


  HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL         = (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1_arr [0] ||
							     HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2_arr [0] ||
							     HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3_arr [0] ||
							     HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4_arr [0] ||
							     HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v7_arr [0] ||
							     HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v12_arr [0] );

  HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL         = (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1_arr [0] ||
							     HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2_arr [0] ||
							     HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3_arr [0] ||
							     HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4_arr [0] ||
							     HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v7_arr [0] ||
							     HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v12_arr [0] );


  HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v5_arr[0] ||
							HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v6_arr[0] ||
							HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v8_arr[0] ||
							HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v9_arr[0] ||
							HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v10_arr[0] ||
							HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v11_arr[0] ||
							HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v12_arr[0] ||
							HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v15_arr[0] );

  HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5_arr[0] ||
							HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6_arr[0] ||
							HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8_arr[0] ||
							HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9_arr[0] ||
							HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10_arr[0] ||
							HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v11_arr[0] ||
							HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v12_arr[0] ||
							HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v15_arr[0] );



  return;
}
