import FWCore.ParameterSet.Config as cms

process = cms.PSet()

#
# ttbarMC: 
#
#inputFileList = [line.rstrip() for line in open("TriggerStudies/NtupleAna/scripts/inputFiles_ttbarMC.txt")]

#
# Data
#
inputFileList = [line.rstrip() for line in open("TriggerStudies/NtupleAna/scripts/inputFiles_2018B.txt")]
#inputFileList = [line.rstrip() for line in open("TriggerStudies/NtupleAna/scripts/inputFiles_2018C.txt")]

    
process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(inputFileList),
    maxEvents   = cms.int32(-1),                             ## optional
    outputEvery = cms.uint32(10),                            ## optional
    )

process.fwliteOutput = cms.PSet(
    fileName  = cms.string('TestFileOutput.root'),  ## mandatory
)


process.procNtupleExample = cms.PSet(
    ## input specific for this analyzer
    debug = cms.bool(False),
    MakeEventDisplays = cms.bool(False),
    LoadTrkLevel = cms.bool(True),
)

