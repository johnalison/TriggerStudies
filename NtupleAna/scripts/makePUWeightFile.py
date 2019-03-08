import optparse
parser = optparse.OptionParser()
parser.add_option('-d', '--inputFileData',            default="", help="")
parser.add_option('-m', '--inputFileMC',              default="", help="")
parser.add_option('-o', '--outputPUFile',             default="", help="")
o, a = parser.parse_args()

import ROOT

inFileData = ROOT.TFile(o.inputFileData,"READ")
inFileMC   = ROOT.TFile(o.inputFileMC,  "READ")

hNPVData = inFileData.Get("Events/nPV")
hNPVData.Scale(1./hNPVData.Integral())

hNPVMC   = inFileMC  .Get("EventsNoPUWeight/nPV")
hNPVMC.Scale(1./hNPVMC.Integral())

hPUWeights = hNPVData.Clone("PUWeights.root")
hPUWeights.Divide(hNPVMC)
hPUWeights.SetName("nPV_weight")

outFile   = ROOT.TFile(o.outputPUFile,  "RECREATE")
outFile.cd()
hPUWeights.Write()

outFile.Close()
inFileData.Close()
inFileMC.Close()
