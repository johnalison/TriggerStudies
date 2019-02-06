TTBARFILE=JetLevelStudyOutputMC_ttbar_runC.root
STFILE=JetLevelStudyOutputMC_ST_runC.root
SANTITFILE=JetLevelStudyOutputMC_SantiT_runC.root
echo python TriggerStudies/NtupleAna/scripts/applyMiniTreeEventCountWeight.py -i $TTBARFILE.root -x 88.34 -n 941634  -l 14000
echo python TriggerStudies/NtupleAna/scripts/applyMiniTreeEventCountWeight.py -i $STFILE.root -x 35.85 -n 727212  -l 14000
echo python TriggerStudies/NtupleAna/scripts/applyMiniTreeEventCountWeight.py -i $SANTITFILE.root -x 35.85 -n 5603226  -l 14000
 
echo hadd JetLevelStudyOutputMC_All_runC_weighted.root JetLevelStudyOutputMC_ttbar_runC_weighted.root JetLevelStudyOutputMC_ST_runC_weighted.root JetLevelStudyOutputMC_SantiT_runC_weighted.root 