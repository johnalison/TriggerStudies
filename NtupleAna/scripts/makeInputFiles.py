import subprocess
import math
import os

import optparse
parser = optparse.OptionParser()
parser.add_option('-i', '--inputDir',        default="")
parser.add_option('-o', '--outputName',      default="")
parser.add_option('-n', '--nFilesPerHadd',   default=500)
parser.add_option('-t', '--threads',         default=5)
parser.add_option('-r', '--run',             action="store_true")
parser.add_option('-l', '--makeFileLists',   action="store_true")
o, a = parser.parse_args()

outputName    = o.outputName 
eosls         = "eos root://cmseos.fnal.gov ls "
eosPrefix     = "root://cmsxrootd.fnal.gov/"
eosDir        = o.inputDir
nFilesPerHadd = int(o.nFilesPerHadd)
if o.makeFileLists:
    outputFile = open(o.outputName+".txt","w")

def getAllInputFiles():
    subdirs = os.popen(eosls+" "+eosDir).readlines()
    inputFileList = []
    
    for s in subdirs:
        sName = s.rstrip()
        print "Doing SubDir", s
        fileNames = os.popen(eosls+" "+eosDir+"/"+s).readlines()    
    
        for f in fileNames:
            fName = f.rstrip()
            inputFileList.append(sName+"/"+fName)
    
    return inputFileList


def getHaddCommand(haddIdx, idx_start, idx_end, inputFiles):
    print "Hadding ",idx_start," to ",idx_end
    if o.run:
        haddCmd = "hadd "+outputName+"_"+str(haddIdx)+".root " 
    else:
        haddCmd = "echo hadd "+outputName+"_"+str(haddIdx)+".root " 
    for f in inputFiles[idx_start:idx_end]:
        haddCmd += eosPrefix+eosDir+"/"+f+" "
    #print haddCmd
    process = subprocess.Popen(haddCmd, shell=True)
    return process


def writeFileNames(outputFile, idx_start, idx_end, inputFiles):
    for f in inputFiles[idx_start:idx_end]:
        outputFile.write(eosPrefix+eosDir+"/"+f+"\n")
    return



def main():
    inputFiles = getAllInputFiles()
    nInputFiles = len(inputFiles)
    print inputFiles
    nSubHadd = int(math.ceil(float(nInputFiles)/nFilesPerHadd))
    print "Total subhadds:",nSubHadd
    print "\t we'll only do ",o.threads,"at a time"
    
    processes = []
    for i in range(nSubHadd-1):
        idx_start = i*nFilesPerHadd
        idx_end   = idx_start + nFilesPerHadd - 1
        if not o.makeFileLists:
            processes.append(getHaddCommand(i,idx_start, idx_end,inputFiles))
        else:
            writeFileNames(outputFile,idx_start, idx_end,inputFiles)

        if len(processes) >= int(o.threads):
            exit_codes = [p.wait() for p in processes]
            print "Exit Codes are",exit_codes
            processes = []
    
    idx_start = (nSubHadd-1)*nFilesPerHadd
    idx_end   = -1
    if not o.makeFileLists:
        processes.append(getHaddCommand(nSubHadd-1,idx_start, idx_end,inputFiles))
    else:
        writeFileNames(outputFile,idx_start, idx_end,inputFiles)
    
    if not o.makeFileLists:    
        exit_codes = [p.wait() for p in processes]
        print "Exit Codes are",exit_codes
    
        if o.run:    
            finalHaddCmd = "hadd "+outputName+"_All.root "
        else:
            finalHaddCmd = "echo hadd "+outputName+"_All.root "
        for i in range(nSubHadd):
            finalHaddCmd += outputName+"_"+str(i)+".root " 
            
        finalProcess = subprocess.Popen(finalHaddCmd, shell=True)
        finalProcess.wait()


        if o.run:
            copyCMD = "xrdcp "+outputName+"_All.root root://cmseos.fnal.gov/"+eosDir
        else:
            copyCMD = "echo xrdcp "+outputName+"_All.root root://cmseos.fnal.gov/"+eosDir

        finalCopy = subprocess.Popen(copyCMD, shell=True)
        finalCopy.wait()            

if __name__ == "__main__":
    main()
