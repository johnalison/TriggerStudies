RunPeriod=$1
jetLevelStudy \
    configFile=TriggerStudies/NtupleAna/scripts/jetLevelStudyConfig2017_cfg.py \
    maxEvents=-1 \
    outputFile=JetLevelStudyOutputMC_ST_${RunPeriod}.root \
    inputFiles=`cat TriggerStudies/NtupleAna/scripts/inputFiles_ST_2017_AddTrks.txt|tr -d '\n'` \
    puFile=TriggerStudies/NtupleAna/data/PUWeights_${RunPeriod}.root
