import ROOT

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
            print(kw)
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
        from OffvsOff_BvL import makePlots

        makePlots(inFile1   = self.file1, 
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

