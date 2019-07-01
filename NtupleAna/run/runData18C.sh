BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples//2018/crab_projects/MuonEG/Run2018C-PromptReco-v2/190611_154214/inputFiles_2018C_MiniAOD_All.root \
    --inputRAW root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples//2018_v3/crab_projects_v4/MuonEG/Run2018C-v1/190531_004239/inputFiles_2018C_RAW_All.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2018 \
    --histogramming 1 \
    --histFile hists_Data18C.root \
    --nevents -1