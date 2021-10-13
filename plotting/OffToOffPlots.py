#import sys
#sys.path.insert(0, '../../')
#import ROOTHelp.FancyROOTStyle

#from iPlotLoadPath import loadPath
#loadPath()


from iUtils import getPM, setBatch, plot
from Rebinning import rebinningDB
setBatch()

from iUtils import parseOpts as parseOpts
(options, args) = parseOpts()
pm = getPM(options)

print options.labName
labName = options.labName.split(",")
print labName





#
#  Logy
#

for v in ["tracks/ip3d_sig",
          "tracks/ip2d_sig",
          "DeepCSV_l",
          "deepFlavB",
          
          "btags/sv_Flight2D",
          "btags/sv_FlightSig2D",
          "btags/sv_FlightSig",
          "btags/sv_Flight",
          "btags/flightDistance2dSig",
          "btags/flightDistance2dVal",
          "btags/flightDistance3dSig",
          "btags/flightDistance3dVal",
          "tracks/ip2d",
          "tracks/ip2d_l",
          "tracks/ip2d_sig",
          "tracks/ip2d_sig_l",
          "tracks/ip3d",
          "tracks/ip3d_l",
          "tracks/ip3d_sig",
          "tracks/ip3d_sig_l",
          "tracks/pt_s",

          "btags/ip2d",
          "btags/ip2d_l",
          "btags/ip2d_sig",
          "btags/ip2d_sig_l",
          "btags/ip3d",
          "btags/ip3d_l",
          "btags/ip3d_sig",
          "btags/ip3d_sig_l",

          "pt_s",
          "pt_m",
          #"trackJetPt",
          # "trackSip2dSigAboveCharm",
          # "trackSip2dValAboveCharm",
          # "trackSip3dSigAboveCharm",
          # "trackSip3dValAboveCharm",
          # "trackSumJetDeltaR",
          #"vertexFitProb",

          "tracks/PtRel"          ,
          "tracks/PtRatio"        ,
          "tracks/PPar"           ,
          "tracks/PParRatio"      ,
          "tracks/Momentum"       ,
          "tracks/DecayLenVal_l"  ,
          "tracks/DecayLenVal"    ,
          "tracks/algo",
          "tracks/origAlgo",

          "btags/sv_Pt",
          ]:

    vName = v.split("/")[-1]
    if vName in rebinningDB:
        binning = rebinningDB[vName]
    else:
        binning = 1

    try:
        plot(v,["offJets_matchedJet","offJets_matched"],binning=binning,doratio=1,labels=["Monitored","Reference"],rMax=1.2,rMin=0.8,logy=1)
    except:
        print "failed",v
        import sys
        sys.exit(-1)

# 
#  No Logy
#
for v in [
    "tracks/eta",
    "tracks/ip2d_err",
    "tracks/ip2d_err_l",
    "tracks/ip3d_err",
    "tracks/ip3d_err_l",

    #        "neMult",
    "phi",
    "eta",

        "btags/sv_BoostOverSqrtJetPt",
    "btags/vertexEnergyRatio",
    "btags/sv_EnergyRatio",
    "btags/sv_Eta",
    "btags/sv_NDF",
    "btags/sv_Phi",
    "btags/sv_R",
    "btags/sv_Z",
    "btags/sv_massVertexEnergyFraction",
    "btags/sv_Chi2",
    "btags/vertexJetDeltaR",
    "btags/sv_JetDeltaR",
    "btags/sv_DistJetAxis",


    "tracks/JetDistVal"     ,

    "tracks/eta"            ,
    "tracks/phi"            ,

    "tracks/DeltaR"         ,
    "btags/etaRel"         ,

    #"mult",
    #"nTrk",
    "btags/jetNTracksEtaRel",

    "btags/chargedHadronMultiplicity",
    "btags/chargedMultiplicity",
    "btags/elecMultiplicity",
    "btags/muonMultiplicity",
    "btags/neutralHadronMultiplicity",
    "btags/neutralMultiplicity",
    "btags/photonMultiplicity",
    "btags/totalMultiplicity",

    "btags/vertexCategory",
        "btags/sv_Mass",
        "btags/vertexMass",
        "tracks/Chi2",

    ]:

    vName = v.split("/")[-1]
    if vName in rebinningDB:
        binning = rebinningDB[vName]
    else:
        binning = 2

    try:
        plot(v,["offJets_matchedJet","offJets_matched"],binning=binning,doratio=1,labels=["Monitored","Reference"],rMax=1.2,rMin=0.8,logy=0)
    except:
        print "failed",v
        import sys
        sys.exit(-1)




#
#  No Rebin
#
for v in [
    "btags/chargedEmEnergyFraction",
    "btags/chargedHadronEnergyFraction",
    "btags/elecEnergyFraction",
    "btags/muonEnergyFraction",
    "btags/neutralEmEnergyFraction",
    "btags/neutralHadronEnergyFraction",
    "btags/photonEnergyFraction",
    "btags/sv_nSVs",
    #"jetNSelectedTracks",
    "tracks/HasInnerPixHit",
    "tracks/NPixelHits",
    "tracks/NTotalHits",
    "tracks/NStripHits",

    "tracks/nTracks",
        #"btags_noV0/nTracks",
    "btags/vertexNTracks",
    "btags/sv_NTracks",
    #"ip2d",


    "tracks/IsFromV0",
    "tracks/IsFromSV",
    #        "neutralHadronEnergyFraction",
    # "trackSumJetEtRatio",
        ]:

    try:
        plot(v,["offJets_matchedJet","offJets_matched"],doratio=1,labels=["Monitored","Reference"],rMax=1.2,rMin=0.8,logy=0)
    except:
        print "failed",v
        import sys
        sys.exit(-1)


