
import sys, os
import optparse
import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
#sys.path.insert(0, 'TriggerStudies/nTupleAnalysis/scripts/')
#from cfgHelper import *

print "Input command"
print " ".join(sys.argv)


parser = optparse.OptionParser()
parser.add_option('-d', '--debug',                dest="debug",         action="store_true", default=False, help="debug")
parser.add_option('-m', '--isMC',                 dest="isMC",          action="store_true", default=False, help="isMC")
parser.add_option( '--inputRAW',                dest="inputRAW",         default="TriggerStudies/fileLists/data2016H.txt", help="Input file(s). If it ends in .txt, will treat it as a list of input files.")
parser.add_option('-o', '--outputBase',           dest="outputBase",    default="/uscms/home/bryantp/nobackup/TriggerStudies/", help="Base path for storing output histograms and picoAOD")
parser.add_option('-n', '--nevents',              dest="nevents",       default="-1", help="Number of events to process. Default -1 for no limit.")
parser.add_option(      '--skipEvents',        dest="skipEvents", default="0", help="")
parser.add_option(      '--histFile',             dest="histFile",      default="hists.root", help="name of ouptut histogram file")
o, a = parser.parse_args()


outputBase = o.outputBase + ("/" if o.outputBase[-1] != "/" else "") # make sure it ends with a slash



inputList=False


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
    if cms.bool(o.debug):
        print('fileNamesRAW:', fileNamesRAW)



pathOut = outputBase
if "root://cmsxrootd-site.fnal.gov//store/" in pathOut:
    pathOut = pathOut + fileNamesRAW[0].replace("root://cmsxrootd-site.fnal.gov//store/", "") #make it a local path
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


# Setup framwork lite output file object
process.fwliteOutput = cms.PSet(
    fileName  = cms.string(histOut),
    )

jetDetailString = "GenJet"

process.HH4bAnalyzer = cms.PSet(
    debug   = cms.bool(o.debug),
    jetDetailString    = cms.string(jetDetailString),
    skipEvents = cms.int32(int(o.skipEvents)),
)

