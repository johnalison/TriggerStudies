from Plotter import Plotter

plots = Plotter(fileName   = "hists_highStats_Mario_PU.root",
                outputName = "hists_highStats_Mario_PU_New",
                name1      = "Reference",
                trackEffDirName1Num = "offTracks_matched",
                trackEffDirName1Den = "offTracks",
                trackEffDirName2Num = "pfTracks_matched",
                trackEffDirName2Den = "pfTracks",
                trackFakeDirName1Num = "pfTracks_unmatched", 
                trackFakeDirName1Den = "pfTracks", 
                trackFakeDirName2Num = "offTracks_unmatched",
                trackFakeDirName2Den = "offTracks",
                name2      = "mkFit_pre5",
                LFDirName1 = "offJets_matched_L",
                LFDirName2 = "offJets_matchedJet_L",
                BQDirName1 = "offJets_matched_B",
                BQDirName2 = "offJets_matchedJet_B",
                extraText = "Work in Progress",
                )

print(plots.file1)


#plots.doTrackEffs()
#plots.doBvL()
plots.doInnerHitvsNoInnerHit()



