RunPeriod=$1
jetLevelStudy \
    configFile=TriggerStudies/NtupleAna/scripts/jetLevelStudyConfig_cfg.py \
    maxEvents=-1 \
    outputFile=JetLevelStudyOutputMC_ttbar_${RunPeriod}.root \
    inputFiles=/eos/user/k/koschwei/HLTBTagging/DiLepton_v10/ttbar/ttbar_98p0_mod_mod_mod_mod_mod_mod.root \
    puFile=TriggerStudies/NtupleAna/data/PUWeights_${RunPeriod}.root

