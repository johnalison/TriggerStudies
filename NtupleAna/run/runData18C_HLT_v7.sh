BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples//2018/crab_projects/MuonEG/Run2018C-PromptReco-v2/190611_154214/inputFiles_2018C_MiniAOD_All.root \
    --inputRAW root://cmsxrootd.fnal.gov//store/user/jda102/BTagNTuples/2018RAW/crab_projects_v5/MuonEG/Run2018C-v1/190617_185449/inputFiles_2018C_RAW_HLT_v7_All.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2018 \
    --histogramming 1 \
    --histFile hists_Data18C_HLT_v7.root \
    --nevents -1