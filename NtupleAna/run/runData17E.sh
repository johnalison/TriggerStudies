BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017/crab_projects_v3/MuonEG/Run2017E-31Mar2018-v1/190912_181318/inputFiles_2017_MINIAOD_All.root \
    --inputRAW root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017RAW/crab_projects_v4/MuonEG/Run2017E-v1/190709_131405/inputFiles_2017E_RAW_All.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2017 \
    --histogramming 1 \
    --histFile hists_Data17E.root \
    --doTracks \
    --nevents -1

#    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017/crab_projects_v2/MuonEG/Run2017E-31Mar2018-v1/190712_210040/inputFiles_2017E_MINIAOD_All.root \