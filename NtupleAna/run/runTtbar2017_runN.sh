RunPeriod=$1
jetLevelStudy \
    configFile=TriggerStudies/NtupleAna/scripts/jetLevelStudyConfig_cfg.py \
    maxEvents=-1 \
    outputFile=JetLevelStudyOutputMC_ttbar_${RunPeriod}.root \
    inputFiles=`cat TriggerStudies/NtupleAna/scripts/inputFiles_ttbarMC2017_AddTrks.txt|tr -d '\n'` \
    puFile=TriggerStudies/NtupleAna/data/PUWeights_${RunPeriod}.root
