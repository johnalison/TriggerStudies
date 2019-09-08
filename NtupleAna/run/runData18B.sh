BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2018/crab_projects_v8/MuonEG/Run2018B-17Sep2018-v1/190806_200007//inputFiles_2018B_MINIAOD_All.root \
    --inputRAW root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2018_v3/crab_projects_v4/MuonEG/Run2018B-v1/190531_004122/inputFiles_2018B_RAW_All.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2018 \
    --histogramming 1 \
    --histFile hists_Data18B.root \
    --doTracks \
    --nevents -1


#    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2018/crab_projects_v8/MuonEG/Run2018B-PromptReco-v2/190628_181933/inputFiles_2018B_MINIAOD_All.root \