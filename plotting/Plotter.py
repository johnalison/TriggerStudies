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
            self.file2    = ROOT.TFile(kwargs["fileName1"],  "READ")                                       
        else:
            self.file2   = self.file1

        for kw in kwargs:
            print(kw)
            setattr(self,kw,kwargs[kw])

        import os
        if not os.path.exists(self.outputName):
            os.makedirs(self.outputName)
   




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
    

