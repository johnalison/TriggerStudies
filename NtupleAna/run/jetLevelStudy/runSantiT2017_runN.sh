RunPeriod=$1
jetLevelStudy \
    configFile=TriggerStudies/NtupleAna/scripts/jetLevelStudyConfig2017_cfg.py \
    maxEvents=-1 \
    outputFile=JetLevelStudyOutputMC_SantiT_${RunPeriod}.root \
    inputFiles=`cat TriggerStudies/NtupleAna/scripts/inputFiles_SantiT_2017_AddTrks.txt|tr -d '\n'` \
    puFile=TriggerStudies/NtupleAna/data/PUWeights_${RunPeriod}.root
