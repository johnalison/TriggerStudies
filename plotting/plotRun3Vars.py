from iUtils import getPM, setBatch, plot
setBatch()


from iUtils import parseOpts as parseOpts

(o,a) = parseOpts()
pm = getPM(o)

labelDict = {}
labelDict["Run2"] = ["HLT Run2 TRK","Offline"]
labelDict["Run3"] = ["HLT Run3 TRK","Offline"]
labelDict["Run3PU"] = ["HLT Run3 TRK w/PU","Offline"]


labels    = labelDict[o.labName]


plot("ip2d_sig_l",["offJets_matchedJet/btags","offJets_matched/btags"],logy=1,rebin=3,doratio=1,norm=1,labels=labels)
plot("ip3d_sig_l",["offJets_matchedJet/btags","offJets_matched/btags"],logy=1,rebin=3,doratio=1,norm=1,labels=labels)
plot("sv_NTracks",["offJets_matchedJet/btags","offJets_matched/btags"],logy=1,rebin=1,doratio=1,norm=1,labels=labels)
plot("sv_NTracks",["offJets_matchedJet/btags","offJets_matched/btags"],logy=0,rebin=1,doratio=1,norm=1,labels=labels,x_min=1,x_max=12)
plot("sv_nSVs",   ["offJets_matchedJet/btags","offJets_matched/btags"],logy=1,rebin=1,doratio=1,norm=1,labels=labels)
plot("sv_nSVs",   ["offJets_matchedJet/btags","offJets_matched/btags"],logy=0,rebin=1,doratio=1,norm=1,labels=labels)
plot("nTracks",   ["offJets_matchedJet",      "offJets_matched"      ],logy=0,rebin=1,doratio=1,norm=1,labels=labels)
plot("nSelTracks",   ["offJets_matchedJet",      "offJets_matched"      ],logy=0,rebin=1,doratio=1,norm=1,labels=labels)




for v in ["chargedEmEnergyFraction","chargedHadronEnergyFraction","elecEnergyFraction","muonEnergyFraction","neutralEmEnergyFraction","neutralHadronEnergyFraction","photonEnergyFraction"]:
    plot(v,["offJets_matchedJet/btags","offJets_matched/btags"],logy=0,doratio=1,norm=0, rebin=2, labels=labels)





    
for v in ["chargedHadronMultiplicity","chargedMultiplicity","elecMultiplicity","muonMultiplicity","neutralHadronMultiplicity","neutralMultiplicity","photonMultiplicity","totalMultiplicity"]:
    plot(v,["offJets_matchedJet/btags","offJets_matched/btags"],logy=0,doratio=1,norm=0, rebin=1, labels=labels)
