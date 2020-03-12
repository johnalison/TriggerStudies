from iUtils import parseOpts, getPM, setBatch, plot

setBatch()
(o,a) = parseOpts()
pm = getPM(o)

labels = ["HLT Tracks","Offline Tracks"]

# plot("Del_nTracks_l",     ["offJets_matchedJet_L","offJets_matched_L"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
# plot("Del_nTracks_noV0_l",["offJets_matchedJet_L","offJets_matched_L"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
# plot("Del_nTracks_l",     ["offJets_matchedJet_B","offJets_matched_B"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
# plot("Del_nTracks_noV0_l",["offJets_matchedJet_B","offJets_matched_B"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
plot("Del_nTracks",     ["offJets_matchedJet_L","offJets_matched_L"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
plot("Del_nTracks_noV0",["offJets_matchedJet_L","offJets_matched_L"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
plot("Del_nTracks",     ["offJets_matchedJet_B","offJets_matched_B"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")
plot("Del_nTracks_noV0",["offJets_matchedJet_B","offJets_matched_B"],logy=1,norm=1,x_min=-1,x_max=30,labels=labels,x_title="#Delta N_{trks} (reco - selected)")



plot("trackEta",["offJets_matchedJet_L/btags","offJets_matched_L/btags"],logy=1,norm=1,doratio=0,rMin=0.,rMax=2,labels=["HLT","Offline"])
plot("trackPhi",["offJets_matchedJet_L/btags","offJets_matched_L/btags"],logy=1,norm=1,doratio=0,rMin=0.,rMax=2,labels=["HLT","Offline"])
