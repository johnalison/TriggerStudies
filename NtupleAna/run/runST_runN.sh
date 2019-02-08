RunPeriod=$1
jetLevelStudy \
    configFile=TriggerStudies/NtupleAna/scripts/jetLevelStudyConfig_cfg.py \
    maxEvents=-1 \
    outputFile=JetLevelStudyOutputMC_ST_${RunPeriod}.root \
    inputFiles=/eos/user/k/koschwei/HLTBTagging/DiLepton_v10/ST/ST_tW_part_mod_mod_mod.root \
    puFile=TriggerStudies/NtupleAna/data/PUWeights_${RunPeriod}.root
