RunPeriod=$1
BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmseos.fnal.gov//store/user/jda102//BTagNTuples/2018/crab_projects_v5/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/190709_181258/inputFiles_ST_wT_antitop_2017_MINIAOD_All.root \
    --inputRAW root://cmseos.fnal.gov//store/user/jda102//BTagNTuples/2017RAW/crab_projects_v3/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17DRPremix-PU2017_94X_mc2017_realistic_v11-v2/190709_145945/inputFiles_ST_wT_antitop_2017_RAW_All.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2017 \
    --histogramming 1 \
    --histFile hists_STMC_wAntiT_${RunPeriod}.root \
    --puFile TriggerStudies/NtupleAna/data/PUWeights_${RunPeriod}.root \
    --isMC \
    --nevents 10000

    # --debug \

# --skipEvents 172656 \