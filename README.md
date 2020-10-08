# TriggerStudies

## Quick Start in SLC7

```bash
cmsrel CMSSW_11_1_0_pre6
cd CMSSW_11_1_0_pre6/src/
cmsenv 
git cms-init
git cms-merge-topic patrickbryant:MakePyBind11ParameterSetsIncludingCommandLineArguments
git clone git@github.com:patrickbryant/nTupleAnalysis.git
git clone git@github.com:johnalison/TriggerStudies.git
```

> Edit:
>  `nTupleAnalysis/baseClasses/src/myParameterSetReader.cc`
> and
>  `nTupleAnalysis/baseClasses/src/myMakeParameterSets.cc`
> to make sure that line
>
>    `#define NTUPLEANALYSIS_SLC6 1` 
>
> is commented OUT


>Edit 
>`TriggerStudies/NtupleAna/bin/BTagAnalyzer.cc`
>to make sure that line
>
>  `#define BTagAnalysis_SLC6 1` 
>
> is commented OUT

```bash
scram b -j 5
```


## Assuming that goes well and example that runs on data is (From LPC)

> source TriggerStudies/NtupleAna/run/runData18B.sh



## Neural Net input files

> wget https://raw.githubusercontent.com/cms-data/RecoBTag-Combined/master/DeepCSV_PhaseII.json -P RecoBTag/Combined/data/