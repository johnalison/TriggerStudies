// -*- C++ -*-
#if !defined(TrackDeltaHists_H)
#define TrackDeltaHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"

//namespace NtupleAna {
//class TrackData;
//};

namespace NtupleAna {


  class TrackDeltaHists {

    std::string m_name;
    //m_Dip3d_sig
    TH1F* m_Dip2d;
    TH1F* m_zoomip2d;
    TH1F* m_Dip2d_sig;
    TH1F* m_Dip2d_err;
    TH1F* m_Dip3d;
    TH1F* m_zoomip3d;
    TH1F* m_Dip3d_sig;
    TH1F* m_Dip3d_err;
    TH1F* m_DtrackDecayLenVal;
    TH1F* m_DtrackJetDistVal;
    TH1F* m_DtrackPtRel;
    TH1F* m_DtrackMomentum;
    TH1F* m_DtrackEta;
    TH1F* m_DtrackPhi;
    TH1F* m_DtrackPPar;
    TH1F* m_DtrackDeltaR;
    TH1F* m_DtrackEtaRel;
    TH1F* m_DtrackPtRatio;
    TH1F* m_DtrackPParRatio;

  public:

    TrackDeltaHists(std::string name, fwlite::TFileService& fs);

    ~TrackDeltaHists();

    void Fill (const TrackData& track, const TrackData& trackM);
  };
};

#endif // TrackDeltaHists_H
