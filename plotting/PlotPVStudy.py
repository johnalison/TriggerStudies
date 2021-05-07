#from iPlot import loadPath
#loadPath()

from iUtils import parseOpts, getPM, setBatch, plot

setBatch()
(o,a) = parseOpts()
pm = getPM(o)

labels = ["hlt","offline"]

plot("x",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Vertex X [cm]")
plot("y",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Vertex Y [cm]")
plot("z",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Vertex Z [cm]")

plot("ex",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Vertex #sigma X [cm]")
plot("ey",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Vertex #sigma Y [cm]")
plot("ez",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Vertex #sigma Z [cm]")

plot("chi2",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Vertex #chi^{2}")
plot("ndf",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Vertex Num DoF")
plot("ndf_l",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Vertex Num DoF")
plot("n",["hltVtx","offVtx"],logy=0,labels=labels,x_title="Number of Vertices")

plot("dx","hltVtx",logy=1,x_title="#Delta Vtx-X (hlt-off)")
plot("dy","hltVtx",logy=1,x_title="#Delta Vtx-Y (hlt-off)")
plot("dz","hltVtx",logy=1,x_title="#Delta Vtx-Z (hlt-off)")
plot("dz_s","hltVtx",logy=1,x_title="#Delta Vtx-Z (hlt-off)")
plot("dz_l","hltVtx",logy=1,x_title="#Delta Vtx-Z (hlt-off)")

if o.puppi:
    plot("matched_dR","offJets_matchedPuppiJet")
    plot("matched_dR","offJets_matchedPuppi")
else:
    plot("matched_dR","offJets_matchedJet")
    plot("matched_dR","offJets_matched")


#plot(["mtt_pf","mtt_off"],"BTagAnalysis",norm=1,labels=["HLT Tracks","Offline Tracks"],xlabel="Track Pair Mass [GeV]",ylabel="Track pairs [normalized]",doratio=1,rMin=0.8,rMax=1.2)
#plot(["mtt_pf_isFromV0","mtt_off_isFromV0"],"BTagAnalysis",norm=1,labels=["HLT Tracks","Offline Tracks"],xlabel="Track Pair Mass [GeV]",ylabel="Track pairs [normalized]",doratio=1,rMin=0.8,rMax=1.2)
#
#
#for i in [2,4,5,6,7,8,9,10,11,13,14,22,23,24,29]:
#    plot("Eta_forAlgo"+str(i),["offTracks_matched","offTracks"],doratio=1,bayesRatio=1,rMin=0.0,rMax=1.2,labels=["Off. Trks","Off. Trks Matched"],rebin=2)
#    plot("Phi_forAlgo"+str(i),["offTracks_matched","offTracks"],doratio=1,bayesRatio=1,rMin=0.0,rMax=1.2,labels=["Off. Trks","Off. Trks Matched"],rebin=2)
#    plot("Pt_forAlgo"+str(i), ["offTracks_matched","offTracks"],doratio=1,bayesRatio=1,rMin=0.0,rMax=1.2,labels=["Off. Trks","Off. Trks Matched"],logy=1,
#         rebin=[0,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,25,30,40,50])
