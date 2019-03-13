// -*- C++ -*-

#if !defined(EventData_H)
#define EventData_H

namespace NtupleAna {


  class EventData {

  public:
    float runNumber         =  0;
    float eventNumber       =  0;
    float FastPrimaryVertex =  0;
    float FPVPixelVertices  =  0;
    float PixelVertices     =  0;
    float VerticesPF        =  0;
    float VerticesL3        =  0;
    float VerticesOff       =  0;
    float nPV               =  0;
    float pu                =  0;
    float trueVertex        =  0;
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = false;
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = false;

    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL    = false;
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = false;

    // 2017A
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = false;


  private:

    float runNumber_arr         [1] = {0};
    float eventNumber_arr       [1] = {0};
    float FastPrimaryVertex_arr [1] = {0};
    float FPVPixelVertices_arr  [1] = {0};
    float PixelVertices_arr     [1] = {0};
    float VerticesPF_arr        [1] = {0};
    float VerticesL3_arr        [1] = {0};
    float VerticesOff_arr       [1] = {0};
    float nPV_arr               [1] = {0};
    float pu_arr                [1] = {0};
    float trueVertex_arr        [1] = {0};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4_arr [1] = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4_arr [1] = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v15_arr [1] = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v7_arr     [1] = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v7_arr     [1] = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v15_arr [1] = {false};

    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6_arr[1] = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5_arr[1] = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8_arr[1] = {false};
    
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v5_arr[1] = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v6_arr[1] = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v8_arr[1] = {false};
    
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v4_arr[1]  = {false};
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v6_arr[1]  = {false};

    // 2017B
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1_arr[1]  = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1_arr[1]  = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2_arr[1]  = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2_arr[1]  = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3_arr[1]  = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3_arr[1]  = {false};
    //bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4_arr[1]  = {false};
    //bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4_arr[1]  = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v12_arr[1]  = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v12_arr[1]  = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v9_arr[1]  = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9_arr[1]  = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v10_arr[1]  = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10_arr[1]  = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v11_arr[1]  = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v11_arr[1]  = {false};
    bool HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v12_arr[1]  = {false};
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v12_arr[1]  = {false};


  public:

    EventData(); 

    ~EventData(); 

    void SetBranchAddress (TChain* intree);

    void SetEvent();

    void SetBranchAddress(TChain* intree, std::string brName, bool* Trigger_arr);
    void SetBranchAddress(TChain* intree, std::string brName, float* float_arr);

    bool passTrigger() {
      if(HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL ||
	 HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL ||
	 HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || 
	 HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ){
	return true;
      }

      return false;
    };
    
  };

}
#endif // EventData_H
