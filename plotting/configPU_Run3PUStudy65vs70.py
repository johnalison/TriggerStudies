from Plotter import Plotter

plots = Plotter(fileName1   = "hists_TestPU60All.root",
                name1      = "PU60",
                LFDirName1 = "offJets_LandPU",
                BQDirName1 = "offJets_B",

                fileName2   = "hists_TestPU70AllFix.root",
                name2      = "PU70",
                LFDirName2 = "offJets_LandPU",
                BQDirName2 = "offJets_B",

                outputName = "hists_PU60vsPU70_New",
                extraText = "Work in Progress",
                doTracks = False
                )


#plots.doTrackEffs()

plots.doBvL()



#python3 TriggerStudies/plotting/OffvsOff_BvL.py --input hists_TestPU60.root --input2 hists_TestPU70.root --out hists_TestPU60and70 --labName PU60,PU70
