jetLevelStudy \
    configFile=TriggerStudies/NtupleAna/scripts/jetLevelStudyConfig_cfg.py \
    maxEvents=-1 \
    outputFile=JetLevelStudyOutputData_runDLuca.root \
    inputFiles=`cat TriggerStudies/NtupleAna/scripts/inputFiles_2017DLuca.txt|tr -d '\n'` \
    puFile=TriggerStudies/NtupleAna/data/PUWeights_runC.root 

