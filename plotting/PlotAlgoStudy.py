#from iPlot import loadPath
#loadPath()

from iUtils import parseOpts, getPM, setBatch, plot

setBatch()
(o,a) = parseOpts()
pm = getPM(o)

plot(["mtt_pf","mtt_off"],"BTagAnalysis",norm=1,labels=["HLT Tracks","Offline Tracks"],xlabel="Track Pair Mass [GeV]",ylabel="Track pairs [normalized]",doratio=1,rMin=0.8,rMax=1.2)
plot(["mtt_pf_isFromV0","mtt_off_isFromV0"],"BTagAnalysis",norm=1,labels=["HLT Tracks","Offline Tracks"],xlabel="Track Pair Mass [GeV]",ylabel="Track pairs [normalized]",doratio=1,rMin=0.8,rMax=1.2)


for i in [2,4,5,6,7,8,9,10,11,13,14,22,23,24,29]:
    plot("Eta_forAlgo"+str(i),["offTracks_matched","offTracks"],doratio=1,bayesRatio=1,rMin=0.0,rMax=1.2,labels=["Off. Trks","Off. Trks Matched"],rebin=2)
    plot("Phi_forAlgo"+str(i),["offTracks_matched","offTracks"],doratio=1,bayesRatio=1,rMin=0.0,rMax=1.2,labels=["Off. Trks","Off. Trks Matched"],rebin=2)
    plot("Pt_forAlgo"+str(i), ["offTracks_matched","offTracks"],doratio=1,bayesRatio=1,rMin=0.0,rMax=1.2,labels=["Off. Trks","Off. Trks Matched"],logy=1,
         rebin=[0,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,25,30,40,50])
