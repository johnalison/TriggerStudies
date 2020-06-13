BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD inputFiles_2017_MINIAOD_All.root \
    --inputRAW inputFiles_2018B_RAW_All.root \
    -o /uscms/home/runxuanw/nobackup/Test0516/CMSSW_11_1_0_pre6/src/Outputs \
    -y 2018 \
    --histogramming 1 \
    --histFile hists_Data18B.root \
    --doTracks \
    --nevents -1

#    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2018/crab_projects_v8/MuonEG/Run2018B-17Sep2018-v1/190806_200007//inputFiles_2018B_MINIAOD_All.root \
#    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2018/crab_projects_v8/MuonEG/Run2018B-PromptReco-v2/190628_181933/inputFiles_2018B_MINIAOD_All.root \
