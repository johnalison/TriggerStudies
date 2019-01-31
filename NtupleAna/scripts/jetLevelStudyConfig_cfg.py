import FWCore.ParameterSet.Config as cms

process = cms.PSet()

#
# ttbarMC: 
#
#inputFileList = [line.rstrip() for line in open("TriggerStudies/NtupleAna/scripts/inputFiles_ttbarMC.txt")]

#
# Data
#
#inputFileList = [line.rstrip() for line in open("TriggerStudies/NtupleAna/scripts/inputFiles_2017C.txt")]
inputFileList = [line.rstrip() for line in open("TriggerStudies/NtupleAna/scripts/inputFiles_ttbarMC2017.txt")]

#inputFileList = [line.rstrip() for line in open("TriggerStudies/NtupleAna/scripts/inputFiles_2018C.txt")]

    
process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(inputFileList),
    maxEvents   = cms.int32(100000),                             ## optional
    outputEvery = cms.uint32(10),                            ## optional
    )

process.fwliteOutput = cms.PSet(
    fileName  = cms.string('JetLevelStudyOutputMC.root'),  ## mandatory
)


process.jetLevelStudy = cms.PSet(
    ## input specific for this analyzer
    debug = cms.bool(False),
    LoadTrkLevel = cms.bool(False),
)

