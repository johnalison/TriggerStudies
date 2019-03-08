RunPeriod=$1
jetLevelStudy \
    configFile=TriggerStudies/NtupleAna/scripts/jetLevelStudyConfig_cfg.py \
    maxEvents=-1 \
    outputFile=JetLevelStudyOutputMC_SantiT_${RunPeriod}.root \
    inputFiles=/eos/user/j/johnda/public/BJetTrigger/2017/MC/ST_antitW_All.root \
    puFile=TriggerStudies/NtupleAna/data/PUWeights_${RunPeriod}.root
