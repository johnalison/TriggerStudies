BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmseos.fnal.gov//store/user/jda102//BTagNTuples/2018/crab_projects_v8/MuonEG/Run2018D-PromptReco-v2/190628_182213/inputFiles_2018D_MINIAOD_All.root \
    --inputRAW root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2018_v3/crab_projects_v4/MuonEG/Run2018D-v1/190518_131745/inputFiles_2018D_RAW_All.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2018 \
    --histogramming 1 \
    --histFile hists_Data18D.root \
    --nevents -1

