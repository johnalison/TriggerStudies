#RunPeriod=$1
#./TriggerStudies/NtupleAna/run/runTtbar_runN.sh $RunPeriod &
#./TriggerStudies/NtupleAna/run/runST_runN.sh $RunPeriod &
#./TriggerStudies/NtupleAna/run/runSantiT_runN.sh $RunPeriod &

RunPeriod=$1
./TriggerStudies/NtupleAna/run/runTtbar2017_runN.sh $RunPeriod &
./TriggerStudies/NtupleAna/run/runST2017_runN.sh $RunPeriod &
./TriggerStudies/NtupleAna/run/runSantiT2017_runN.sh $RunPeriod &
