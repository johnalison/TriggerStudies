import FWCore.ParameterSet.Config as cms

process = cms.PSet()



process.fwliteInput = cms.PSet(
    fileNames   = cms.vstring("root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_6.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_7.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_10.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_11.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_12.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_13.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_14.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_15.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_16.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_17.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_18.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_19.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_20.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_22.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_23.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_24.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_25.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_27.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_28.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_29.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_30.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_31.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_32.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_33.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_35.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_38.root",
                              "root://cmsxrootd.fnal.gov//store/user/jda102/MCTTTEST/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MCTTTEST/181105_170228/0000/tree_50.root",
                              ),
    maxEvents   = cms.int32(-1),                             ## optional
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

