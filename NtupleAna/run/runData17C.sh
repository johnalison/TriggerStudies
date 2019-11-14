BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017/crab_projects_v3/MuonEG/Run2017C-31Mar2018-v1/190912_181033/inputFiles_2017_MINIAOD_All.root \
    --inputRAW root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017RAW/crab_projects_v3/MuonEG/Run2017C-v1/190611_151927/inputFiles_2017C_RAW_All.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2017 \
    --histogramming 1 \
    --histFile hists_Data17C.root \
    --doTracks \
    --nevents -1

#    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017/crab_projects_v2/MuonEG/Run2017C-31Mar2018-v1/190712_205807/inputFiles_2017C_MINIAOD_All.root \