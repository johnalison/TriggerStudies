BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017/crab_projects_v3/MuonEG/Run2017B-31Mar2018-v1/190912_180905/inputFiles_2017_MINIAOD_All.root \
    --inputRAW root://cmsxrootd.fnal.gov//store/user/jda102/BTagNTuples/2017RAW/crab_projects_v3//MuonEG/Run2017B-v1/190611_151840/inputFiles_2017B_94X_RAW_All.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2017 \
    --histogramming 1 \
    --histFile hists_Data17B.root \
    --doTracks \
    --nevents -1


#    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017/crab_projects_v2/MuonEG/Run2017B-31Mar2018-v1/190712_205650/inputFiles_2017B_MINIAOD_All.root \