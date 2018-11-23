import FWCore.ParameterSet.Config as cms

process = cms.PSet()



process.fwliteInput = cms.PSet(
    fileNames   = cms.vstring('root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_6.root'), ## mandatory
    maxEvents   = cms.int32(3000),                             ## optional
    outputEvery = cms.uint32(10),                            ## optional
)

process.fwliteOutput = cms.PSet(
    fileName  = cms.string('TestFileOutput.root'),  ## mandatory
)


process.procNtupleExample = cms.PSet(
    ## input specific for this analyzer
    debug = cms.bool(False),
    MakeEventDisplays = cms.bool(True),
)

