jetLevelStudy \
    configFile=TriggerStudies/NtupleAna/scripts/jetLevelStudyConfig2018_cfg.py \
    maxEvents=-1 \
    outputFile=JetLevelStudyOutputData_runC2018.root \
    inputFiles=`cat TriggerStudies/NtupleAna/scripts/inputFiles_2018C.txt|tr -d '\n'` \
    puFile=TriggerStudies/NtupleAna/data/PUWeights_runC.root
