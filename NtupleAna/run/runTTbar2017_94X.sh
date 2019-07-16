BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD root://cmseos.fnal.gov//store/user/jda102//BTagNTuples/2018/crab_projects_v4/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/190701_141500/inputFiles_ttbar_94X_MINIAOD_All.root \
    --inputRAW root://cmseos.fnal.gov//store/user/johnda/BTagNTuples/2018/crab_projects_v2/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17DRPremix-TSG_94X_mc2017_realistic_v11-v1/190604_23213/inputFiles_ttbarMC_RAW_4June19_94X.root \
    -o /uscms/home/jda102/nobackup/ProcBJetNtuples/CMSSW_10_1_7/src \
    -y 2017 \
    --histogramming 1 \
    --histFile hists_ttbarMC_2017.root \
    --puFile TriggerStudies/NtupleAna/data/PUWeights_runBCDEF_2017.root \
    --isMC \
    --nevents -1


#--inputAOD root://cmseos.fnal.gov//store/user/johnda/BTagNTuples/2018/crab_projects_v3/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17DRPremix-TSG_94X_mc2017_realistic_v11-v1/190604_133320/inputFiles_ttbarMC_AOD_4June19.root \
#--inputAOD root://cmseos.fnal.gov//store/user/jda102//BTagNTuples/2018/crab_projects_v4/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/190701_141500/inputFiles_ttbar_94X_MINIAOD_All.root \