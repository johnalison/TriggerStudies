#RunPeriod=$1
#./TriggerStudies/NtupleAna/run/runTtbar_runN.sh $RunPeriod &
#./TriggerStudies/NtupleAna/run/runST_runN.sh $RunPeriod &
#./TriggerStudies/NtupleAna/run/runSantiT_runN.sh $RunPeriod &

RunPeriod=$1
./TriggerStudies/NtupleAna/run/runTtbar2018_runN.sh $RunPeriod &
./TriggerStudies/NtupleAna/run/runST2018_runN.sh $RunPeriod &
./TriggerStudies/NtupleAna/run/runSantiT2018_runN.sh $RunPeriod &
