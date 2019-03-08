#!/usr/bin/env python

import ROOT

import sys
import glob
import os, os.path
import shutil
import argparse
import multiprocessing

def rescale_file(rootfile, xsec, lumi, nGen):
    # Check if backup file exists

    outrootfile=rootfile.replace(".root","_weighted.root")
    #if not os.path.exists(origrootfile): # Create backup
    #    shutil.copyfile(rootfile,origrootfile)

    fh_out =ROOT.TFile.Open(outrootfile,'recreate')
    fh_hist=ROOT.TFile.Open(rootfile)

    weight = float(xsec) * float(lumi)/float(nGen)
        
    ## Get event counts
    #eventCountHist = fh_hist.Get('MetaData_EventCount_XhhMiniNtuple')
    #
    #if "0x(nil)" in str(eventCountHist): 
    #    print "ERROR: Did not find MetaData_EventCount_XhhMiniNtuple"
    #    #fh_hist.ls()
    #    print "Try using EventLoop_EventCount"
    #
    #    eventCountHist = fh_hist.Get('EventLoop_EventCount')
    #    if "0x(nil)" in str(eventCountHist): 
    #        print "ERROR: Did not find EventLoop_EventCount"
    #
    #if not args.weighted:
    #    EventCount=eventCountHist.GetBinContent(1)
    #else:
    #    EventCount=eventCountHist.GetBinContent(3)

    recursive_rescale(fh_hist,fh_out,weight)

    fh_out .Close()
    fh_hist.Close()

    return 

def recursive_rescale(indir,outdir,weight):
    keys=indir.GetListOfKeys()

    for key in keys:
        name=key.GetName()
        obj=key.ReadObj()
        if obj.InheritsFrom(ROOT.TH1.Class()):
            outdir.cd()
            obj.Scale(weight)
            obj.Write()
        elif obj.InheritsFrom(ROOT.TDirectoryFile.Class()):
            newoutdir=outdir.mkdir(obj.GetName())
            recursive_rescale(obj,newoutdir,weight)
        obj.Delete()


import optparse
parser = optparse.OptionParser()
parser.add_option('-i', '--inputFile',            dest="inputFileName",         default="", help="")
parser.add_option('-l', '--lumi',            default="", help="")
parser.add_option('-x', '--xsec',                     default="", help="")
parser.add_option('-n', '--nGenEvents',                     default="", help="")
o, a = parser.parse_args()

print o.inputFileName

#os.system("cp "+o.inputFileName+" "+o.inputFileName+".SAFE")

rescale_file(o.inputFileName, o.xsec, o.lumi, o.nGenEvents)

#for result in workers.imap_unordered(rescale_file,rootfiles):
#    print(result)
# for rootfile in rootfiles:
#     print(rescale_file(rootfile))
