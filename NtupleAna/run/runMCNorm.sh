RunPeriod=$1
TTBARFILE=JetLevelStudyOutputMC_ttbar_${RunPeriod}
STFILE=JetLevelStudyOutputMC_ST_${RunPeriod}
SANTITFILE=JetLevelStudyOutputMC_SantiT_${RunPeriod}
python TriggerStudies/NtupleAna/scripts/applyMiniTreeEventCountWeight.py -i $TTBARFILE.root -x 88.29 -n 941634  -l 14000
python TriggerStudies/NtupleAna/scripts/applyMiniTreeEventCountWeight.py -i $STFILE.root -x 19.56  -n 727212  -l 14000
python TriggerStudies/NtupleAna/scripts/applyMiniTreeEventCountWeight.py -i $SANTITFILE.root -x 19.56 -n 5603226  -l 14000

hadd -f JetLevelStudyOutputMC_All2018_${RunPeriod}_weighted.root ${TTBARFILE}_weighted.root ${STFILE}_weighted.root ${SANTITFILE}_weighted.root 