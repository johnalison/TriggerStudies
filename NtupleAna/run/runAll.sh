RunPeriod=$1
./TriggerStudies/NtupleAna/run/runTtbar_runN.sh $RunPeriod &
./TriggerStudies/NtupleAna/run/runST_runN.sh $RunPeriod &
./TriggerStudies/NtupleAna/run/runSantiT_runN.sh $RunPeriod &
