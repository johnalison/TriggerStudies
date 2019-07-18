RunPeriod=$1
BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmseos.fnal.gov//store/user/jda102//BTagNTuples/2018/crab_projects_v6/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/190710_124749/inputFiles_ST_wT_top_2017_MINIAOD_All.root \
    --inputRAW root://cmseos.fnal.gov//store/user/jda102//BTagNTuples/2017RAW/crab_projects_v3/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17DRPremix-TSG_94X_mc2017_realistic_v11-v1/190709_145913/inputFiles_ST_wT_top_2017_MINIAOD_All.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2017 \
    --histogramming 1 \
    --histFile hists_STMC_wT_${RunPeriod}.root \
    --puFile TriggerStudies/NtupleAna/data/PUWeights_${RunPeriod}.root \
    --isMC \
    --nevents -1

