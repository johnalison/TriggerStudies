
import sys, os
import optparse
import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
#sys.path.insert(0, 'ZZ4b/nTupleAnalysis/scripts/')
#from cfgHelper import *

parser = optparse.OptionParser()
parser.add_option('-d', '--debug',                dest="debug",         action="store_true", default=False, help="debug")
parser.add_option('-m', '--isMC',                 dest="isMC",          action="store_true", default=False, help="isMC")
parser.add_option('--isTurnOnStudy',              action="store_true",  default=False, help="doTurn On Study")
parser.add_option('--doTracks',                   action="store_true",  default=False, help="doTurn On Study")
parser.add_option('-y', '--year',                 dest="year",          default="2016", help="Year specifies trigger (and lumiMask for data)")
#parser.add_option('-l', '--lumi', type="float",   dest="lumi",          default=1.0,    help="Luminosity for MC normalization: units [pb]")
parser.add_option( '--inputAOD',                dest="inputAOD",         default="ZZ4b/fileLists/data2016H.txt", help="Input file(s). If it ends in .txt, will treat it as a list of input files.")
parser.add_option( '--inputRAW',                dest="inputRAW",         default="ZZ4b/fileLists/data2016H.txt", help="Input file(s). If it ends in .txt, will treat it as a list of input files.")
parser.add_option('-o', '--outputBase',           dest="outputBase",    default="/uscms/home/bryantp/nobackup/ZZ4b/", help="Base path for storing output histograms and picoAOD")
parser.add_option('--puFile',                     dest="puFile",       default="", help="PUFileName")
parser.add_option('-n', '--nevents',              dest="nevents",       default="-1", help="Number of events to process. Default -1 for no limit.")
parser.add_option(      '--histogramming',        dest="histogramming", default="1e6", help="Histogramming level. 0 to make no kinematic histograms. 1: only make histograms for full event selection, larger numbers add hists in reverse cutflow order.")
parser.add_option(      '--skipEvents',        dest="skipEvents", default="0", help="")
parser.add_option(      '--histFile',             dest="histFile",      default="hists.root", help="name of ouptut histogram file")
o, a = parser.parse_args()


#
# Basic Configuration
#
outputBase = o.outputBase + ("/" if o.outputBase[-1] != "/" else "") # make sure it ends with a slash
isData     = not o.isMC
JSONfiles  = {'2015':'',
              '2016':'ZZ4b/lumiMasks/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt', #Final, unlikely to change
              '2017':'ZZ4b/lumiMasks/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt',
              '2018':'ZZ4b/lumiMasks/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'} #Not Final, should be updated at some point
# Calculated lumi per lumiBlock from brilcalc. See README
lumiData   = {'2015':'',
              '2016':'ZZ4b/lumiMasks/', 
              '2017':'ZZ4b/lumiMasks/brilcalc_2017_NoTrigger.csv',
              '2018':'ZZ4b/lumiMasks/brilcalc_2018_HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5.csv'} 

# for MC we need to normalize the sample to the recommended cross section * BR times the target luminosity
## ZH cross sections https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt13TeV#ZH_Process
## ZZ cross section 15.0 +0.7 -0.6 +/-0.2 (MCFM at NLO in QCD with additional contributions from LO gg -> ZZ diagrams) or 16.2 +0.6 -0.4 (calculated at NNLO in QCD via MATRIX) https://arxiv.org/pdf/1607.08834.pdf pg 10
## Higgs BR(mH=125.0) = 0.5824, BR(mH=125.09) = 0.5809: https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBR
## Z BR = 0.1512+/-0.0005 from PDG
## store all process cross sections in pb. Can compute xs of sample with GenXsecAnalyzer. Example: 
## cd genproductions/test/calculateXSectionAndFilterEfficiency; ./calculateXSectionAndFilterEfficiency.sh -f ../../../ZZ_dataset.txt -c RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1 -d MINIAODSIM -n -1 

fileNamesAOD = []
inputList=False
if ".txt" in o.inputAOD:
    inputList = True
    for line in open(o.inputAOD, 'r').readlines():
        line = line.replace('\n','').strip()
        if line    == '' : continue
        if line[0] == '#': continue
        fileNamesAOD.append(line.replace('\n',''))
else:
    fileNamesAOD.append(o.inputAOD)


fileNamesRAW = []
inputList=False
if ".txt" in o.inputRAW:
    inputList = True
    for line in open(o.inputRAW, 'r').readlines():
        line = line.replace('\n','').strip()
        if line    == '' : continue
        if line[0] == '#': continue
        fileNamesRAW.append(line.replace('\n',''))
else:
    fileNamesRAW.append(o.inputRAW)


pathOut = outputBase
if "root://cmsxrootd-site.fnal.gov//store/" in pathOut: 
    pathOut = pathOut + fileNamesAOD[0].replace("root://cmsxrootd-site.fnal.gov//store/", "") #make it a local path
pathOut = '/'.join(pathOut.split("/")[:-1])+"/" #remove <fileName>.root
    
#if inputList: #use simplified directory structure based on grouping of filelists
#    pathOut = outputBase+o.input.split("/")[-1].replace(".txt","/")

if not os.path.exists(pathOut): 
    mkpath(pathOut)

histOut = pathOut+o.histFile

#
# ParameterSets for use in bin/<script>.cc 
#
process = cms.PSet()

#Setup framework lite input file object
process.fwliteInput = cms.PSet(
    fileNames   = cms.vstring(fileNamesRAW),
    maxEvents   = cms.int32(int(o.nevents)),
    )

# LumiMask
process.inputs = cms.PSet(
    lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
    )
if isData:
    # get JSON file correctly parced
    myList = LumiList.LumiList(filename = JSONfiles[o.year]).getCMSSWString().split(',')
    process.inputs.lumisToProcess.extend(myList)


# Setup framwork lite output file object
process.fwliteOutput = cms.PSet(
    fileName  = cms.string(histOut),
    )


if o.doTracks: 
    jetDetailString = "Tracks.btagInputs"
else:
    jetDetailString = ""


#Setup event loop object
process.BTagAnalyzer = cms.PSet(
    debug   = cms.bool(o.debug),
    fileNamesAOD   = cms.vstring(fileNamesAOD),
    isMC    = cms.bool(o.isMC),
    isTurnOnStudy    = cms.bool(o.isTurnOnStudy),
    year    = cms.string(o.year),
    puFile    = cms.string(o.puFile),
    jetDetailString    = cms.string(jetDetailString),
    lumiData= cms.string(lumiData[o.year]),
    histogramming = cms.int32(int(o.histogramming)),
    skipEvents = cms.int32(int(o.skipEvents)),
    )

