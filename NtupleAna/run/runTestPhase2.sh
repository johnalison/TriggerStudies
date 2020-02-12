BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD /afs/cern.ch/work/s/sewuchte/public/BTV_PhaseII//nTuples/Offline/testFile.root \
    --inputRAW /afs/cern.ch/work/s/sewuchte/public/BTV_PhaseII//nTuples/HLT/TrackingV2/total.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile hists_Test.root \
    --isMC \
    --doTracks \
    --nevents -1


#    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017/crab_projects_v2/MuonEG/Run2017B-31Mar2018-v1/190712_205650/inputFiles_2017B_MINIAOD_All.root \
