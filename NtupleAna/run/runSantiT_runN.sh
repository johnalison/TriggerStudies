RunPeriod=$1
jetLevelStudy \
    configFile=TriggerStudies/NtupleAna/scripts/jetLevelStudyConfig_cfg.py \
    maxEvents=-1 \
    outputFile=JetLevelStudyOutputMC_SantiT_${RunPeriod}.root \
    inputFiles=/eos/user/k/koschwei/HLTBTagging/DiLepton_v10/SantiT/ST_antitW_mod_mod_mod.root \
    puFile=TriggerStudies/NtupleAna/data/PUWeights_${RunPeriod}.root
