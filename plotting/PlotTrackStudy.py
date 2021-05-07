from iUtils import parseOpts, getPM, setBatch, plot

setBatch()
(o,a) = parseOpts()
pm = getPM(o)

labels = ["HLT Tracks","Offline Tracks"]

if not o.puppi:
    plot("Del_nTracks_l",     ["offJets_matchedJet_L","offJets_matched_L"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_noV0_l",["offJets_matchedJet_L","offJets_matched_L"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_l",     ["offJets_matchedJet_B","offJets_matched_B"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_noV0_l",["offJets_matchedJet_B","offJets_matched_B"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks",     ["offJets_matchedJet_L","offJets_matched_L"],logy=1,norm=1,doratio=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_noV0",["offJets_matchedJet_L","offJets_matched_L"],logy=1,norm=1,doratio=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks",     ["offJets_matchedJet_B","offJets_matched_B"],logy=1,norm=1,doratio=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_noV0",["offJets_matchedJet_B","offJets_matched_B"],logy=1,norm=1,doratio=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")


    plot("trackPt",["offJets_matchedJet_L/btags","offJets_matched_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedJet_L/btags","offJets_matched_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedJet_L/btags","offJets_matched_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedJet_B/btags","offJets_matched_B/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedJet_B/btags","offJets_matched_B/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])

    plot("trackPt",["offJets_matchedJet_L/btags_noV0","offJets_matched_L/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedJet_L/btags_noV0","offJets_matched_L/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedJet_L/btags_noV0","offJets_matched_L/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedJet_B/btags_noV0","offJets_matched_B/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedJet_B/btags_noV0","offJets_matched_B/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])


    plot("trackPt",["offJets_matchedJet/btags","offJets_matched_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedJet/btags","offJets_matched_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedJet/btags","offJets_matched_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedJet/btags","offJets_matched_B/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedJet/btags","offJets_matched_B/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])

    plot("trackPt",["offJets_matchedJet/btags_noV0","offJets_matched/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedJet/btags_noV0","offJets_matched/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedJet/btags_noV0","offJets_matched/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedJet/btags_noV0","offJets_matched/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedJet/btags_noV0","offJets_matched/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])

    plot("eta",["offJets_matchedJet_L/tracks","offJets_matched_L/tracks"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("phi",["offJets_matchedJet_L/tracks","offJets_matched_L/tracks"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("eta",["offJets_matchedJet_B/tracks","offJets_matched_B/tracks"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("phi",["offJets_matchedJet_B/tracks","offJets_matched_B/tracks"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    #
    plot("eta",["offJets_matchedJet_L/tracks_noV0","offJets_matched_L/tracks_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("phi",["offJets_matchedJet_L/tracks_noV0","offJets_matched_L/tracks_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("eta",["offJets_matchedJet_B/tracks_noV0","offJets_matched_B/tracks_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("phi",["offJets_matchedJet_B/tracks_noV0","offJets_matched_B/tracks_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
else:
    plot("Del_nTracks_l",     ["offJets_matchedPuppiJet_L","offJets_matchedPuppi_L"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_noV0_l",["offJets_matchedPuppiJet_L","offJets_matchedPuppi_L"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_l",     ["offJets_matchedPuppiJet_B","offJets_matchedPuppi_B"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_noV0_l",["offJets_matchedPuppiJet_B","offJets_matchedPuppi_B"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks",     ["offJets_matchedPuppiJet_L","offJets_matchedPuppi_L"],logy=1,norm=1,doratio=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_noV0",["offJets_matchedPuppiJet_L","offJets_matchedPuppi_L"],logy=1,norm=1,doratio=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks",     ["offJets_matchedPuppiJet_B","offJets_matchedPuppi_B"],logy=1,norm=1,doratio=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
    plot("Del_nTracks_noV0",["offJets_matchedPuppiJet_B","offJets_matchedPuppi_B"],logy=1,norm=1,doratio=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")


    plot("trackPt",["offJets_matchedPuppiJet_L/btags","offJets_matchedPuppi_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedPuppiJet_L/btags","offJets_matchedPuppi_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedPuppiJet_L/btags","offJets_matchedPuppi_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedPuppiJet_B/btags","offJets_matchedPuppi_B/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedPuppiJet_B/btags","offJets_matchedPuppi_B/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])

    plot("trackPt",["offJets_matchedPuppiJet_L/btags_noV0","offJets_matchedPuppi_L/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedPuppiJet_L/btags_noV0","offJets_matchedPuppi_L/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedPuppiJet_L/btags_noV0","offJets_matchedPuppi_L/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedPuppiJet_B/btags_noV0","offJets_matchedPuppi_B/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedPuppiJet_B/btags_noV0","offJets_matchedPuppi_B/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])


    plot("trackPt",["offJets_matchedPuppiJet/btags","offJets_matchedPuppi_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedPuppiJet/btags","offJets_matchedPuppi_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedPuppiJet/btags","offJets_matchedPuppi_L/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedPuppiJet/btags","offJets_matchedPuppi_B/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedPuppiJet/btags","offJets_matchedPuppi_B/btags"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])

    plot("trackPt",["offJets_matchedPuppiJet/btags_noV0","offJets_matchedPuppi/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedPuppiJet/btags_noV0","offJets_matchedPuppi/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedPuppiJet/btags_noV0","offJets_matchedPuppi/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackEta",["offJets_matchedPuppiJet/btags_noV0","offJets_matchedPuppi/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("trackPhi",["offJets_matchedPuppiJet/btags_noV0","offJets_matchedPuppi/btags_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])

    plot("eta",["offJets_matchedPuppiJet_L/tracks","offJets_matchedPuppi_L/tracks"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("phi",["offJets_matchedPuppiJet_L/tracks","offJets_matchedPuppi_L/tracks"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("eta",["offJets_matchedPuppiJet_B/tracks","offJets_matchedPuppi_B/tracks"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("phi",["offJets_matchedPuppiJet_B/tracks","offJets_matchedPuppi_B/tracks"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    #
    plot("eta",["offJets_matchedPuppiJet_L/tracks_noV0","offJets_matchedPuppi_L/tracks_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("phi",["offJets_matchedPuppiJet_L/tracks_noV0","offJets_matchedPuppi_L/tracks_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("eta",["offJets_matchedPuppiJet_B/tracks_noV0","offJets_matchedPuppi_B/tracks_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
    plot("phi",["offJets_matchedPuppiJet_B/tracks_noV0","offJets_matchedPuppi_B/tracks_noV0"],logy=1,norm=1,doratio=1,rMin=0.5,rMax=1.5,labels=["HLT","Offline"])
