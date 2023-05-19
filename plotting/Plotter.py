import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.gErrorIgnoreLevel = ROOT.kWarning
import ROOTHelp.FancyROOTStyle

class Plotter: 

    def __init__(self,  **kwargs):

        if "fileName" in kwargs:
            self.file1    = ROOT.TFile(kwargs["fileName"],  "READ")
        elif "fileName1" in kwargs:
            self.file1    = ROOT.TFile(kwargs["fileName1"],  "READ")
        else:
            raise Exception("Missing filename or filename1 for Plotter")
            
        if "fileName2" in kwargs:
            self.file2    = ROOT.TFile(kwargs["fileName2"],  "READ")                                       
        else:
            self.file2   = self.file1

        for kw in kwargs:
            setattr(self,kw,kwargs[kw])

        import os
        if not os.path.exists(self.outputName):
            os.makedirs(self.outputName)


        if "doTracks" not in kwargs:
            self.doTracks = True




    def doTrackEffs(self):
        from MakeOffToOffComparison import doTrackEffs

        doTrackEffs(file1=self.file1,
                    effDirName1Num=self.trackEffDirName1Num,
                    effDirName1Den=self.trackEffDirName1Den,
                    fakeDirName1Num=self.trackFakeDirName1Num,
                    fakeDirName1Den=self.trackFakeDirName1Den,
                    name1 = self.name1,

                    file2=self.file2,
                    effDirName2Num=self.trackEffDirName2Num,
                    effDirName2Den=self.trackEffDirName2Den,
                    fakeDirName2Num=self.trackFakeDirName2Num,
                    fakeDirName2Den=self.trackFakeDirName2Den,
                    name2 = self.name2,

                    outputDir = self.outputName
                  )
    



    def doBvL(self):
        from OffvsOff_BvL import makePlotsAll

        makePlotsAll(inFile1   = self.file1, 
                     inFile2   = self.file2,
                     LFName1   = self.LFDirName1,
                     LFName2   = self.LFDirName2,
                     BQName1   = self.BQDirName1,
                     BQName2   = self.BQDirName2,
                     extraText = self.extraText,
                     name1     = self.name1,
                     name2     = self.name2,
                     outputDir = self.outputName,
                     doTracks  = self.doTracks,
        )



    def doInnerHitvsNoInnerHit(self):
        from innerHitvsNoInnerHit import makePlots
        
        makePlots(inFile1   = self.file1, 
                  inFile2   = self.file2,
                  LFName1   = self.LFDirName1, # These should indeed be the same  
                  LFName2   = self.LFDirName1, # These should indeed be the same 
                  BQName1   = self.BQDirName1, #
                  BQName2   = self.BQDirName1, # Ditto
                  extraText = self.extraText,
                  outputDir = self.outputName,
              )



    def doRoc(self, rocs):
        from rocCurveUtils import plotSame, makeRocPlot
        
        
        kw = {}
        kw["colors"] =  [ROOT.kBlack,      ROOT.kBlack]
        kw["styles"] =  [ROOT.kSolid,      ROOT.kDashed]
        kw["taggerNames"] = ["DeepJet"]
        kw["labelNames"]  = [self.name1,self.name2]
        kw["cmsText"]     = self.extraText
        kw["outputDir"]   = self.outputName

        for r in rocs:

            vsLight = True
            if "vsLight" in r: vsLight = r["vsLight"]
                            
            plotSame(r["name"],
                     [makeRocPlot(self.file1, "f1_"+r["var"].replace("/","_"),        r["var"], bkg=r["dir1"][0],      sig=r["dir1"][1], vsLight=vsLight)[1],
                      makeRocPlot(self.file2, "f2_"+r["var"].replace("/","_"),        r["var"], bkg=r["dir2"][0],      sig=r["dir2"][1], vsLight=vsLight)[1]],
                     **kw
            )

