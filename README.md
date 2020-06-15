# TriggerStudies

## Quick Start

## 
cmsrel CMSSW_11_1_0_pre6
cd CMSSW_11_1_0_pre6/src/
cmsenv 
git cms-init
git cms-merge-topic patrickbryant:MakePyBind11ParameterSetsIncludingCommandLineArguments
git clone -b CMSSW_11  git@github.com:patrickbryant/nTupleAnalysis.git
git clone -b CMSSW_11  git@github.com:johnalison/TriggerStudies.git


## Assuming that goes well and example that runs on data is (From LPC)

> source TriggerStudies/NtupleAna/run/runData18B.sh




> wget https://raw.githubusercontent.com/cms-data/RecoBTag-Combined/master/DeepCSV_PhaseII.json -P RecoBTag/Combined/data/

