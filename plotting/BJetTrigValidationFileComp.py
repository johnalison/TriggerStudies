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


# plotDirs = ["offJets_matched","offJets_matchedJet",    "offJets_matchedCalo",   "offJets_matchedCaloJet"]
plotDirs = ["offJets_matched","offJets_matchedJet",
            "offJets_matched_eta1","offJets_matchedJet_eta1",
            "offJets_matched_eta2","offJets_matchedJet_eta2",
            "offJets_matched_eta3","offJets_matchedJet_eta3"]



for v in ["tracks/ip3d_sig",
          "tracks/ip2d_sig",
          # "CSVv2_l",
          "probB",
          "DeepCSV_l",
          #"deepcsv_bb",
          "btags/sv_Flight2D",
          "btags/sv_FlightSig2D",
          "btags/sv_FlightSig",
          "btags/sv_Flight",
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
          #"trackSip2dSigAboveCharm",
          #"trackSip2dValAboveCharm",
          #"trackSip3dSigAboveCharm",
          #"trackSip3dValAboveCharm",
          #"trackSumJetDeltaR",
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
        binning = 2


    for d in plotDirs:
        plot(v,d,       binning=binning,doratio=1,rMin=0.5,rMax=1.5,logy=1,labels=labName,norm=options.norm)

    #doVarRatio(v,
    #      xTitle = v,
    #      #binning = [-20,-18,-16,-14,-12,-11,-10,-8,-6,-5,-4,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,4,5,6,8,10,11,12,14,16,18,20,22,24,28,32,36,40]
    #      binning = binning,
    #      #binning = [-100 , -90,-80 , -70  , -60 ,  -50 , -40 , -34 , -32 , -30 , -28 , -26 , -24 , -22 , -20 , -18 , -16 , -14 , -12 , -10 , -8 , -6 , -4 , -2 , 0 , 2 , 4 , 6 , 8 , 10 , 12 , 14 , 16 , 18 , 20 , 22 , 24 , 26 , 28 , 30 , 32 , 34 , 40 , 50 , 60 , 70 , 80, 90 , 100]
    #      #binning = [-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,-5,0,5,10,15,20,30,40,50,60,70,80,90,100]
    #      )




for v in [        "tracks/eta",
        "tracks/ip2d_err",
        "tracks/ip2d_err_l",
        "tracks/ip3d_err",
        "tracks/ip3d_err_l",




#        "neMult",
        "phi",
        "eta",





                  "btags/sv_BoostOverSqrtJetPt",

        "btags/sv_EnergyRatio",
        "btags/sv_Eta",
        "btags/sv_NDF",
        "btags/sv_Phi",
        "btags/sv_R",
        "btags/sv_Z",
                  "btags/sv_massVertexEnergyFraction",
                  "btags/sv_Chi2",

        "btags/sv_JetDeltaR",
        "btags/sv_DistJetAxis",


        "tracks/JetDistVal"     ,

        "tracks/eta"            ,
        "tracks/phi"            ,

        "tracks/DeltaR"         ,
        #"trackEtaRel"         ,

        #"mult",
        #"nTrk",
        #"jetNTracksEtaRel",

                  "btags/chargedHadronMultiplicity",
                  "btags/chargedMultiplicity",
                  "btags/elecMultiplicity",
                  "btags/muonMultiplicity",
                  "btags/neutralHadronMultiplicity",
                  "btags/neutralMultiplicity",
                  "btags/photonMultiplicity",
                  "btags/totalMultiplicity",



        #"vertexCategory",

          "tracks/Chi2",




                  ]:

#    if v in [ "btags/chargedHadronMultiplicity",
#              "btags/chargedMultiplicity",
#              "btags/elecMultiplicity",
#              "btags/muonMultiplicity",
#              "btags/neutralHadronMultiplicity",
#              "btags/neutralMultiplicity",
#              "btags/photonMultiplicity",
#              "btags/totalMultiplicity",
#              ]:
#        continue
    vName = v.split("/")[-1]
    if vName in rebinningDB:
        binning = rebinningDB[vName]
    else:
        binning = 2

    for d in plotDirs:
        plot(v,d,       binning=binning,doratio=1,rMin=0.5,rMax=1.5,logy=0,labels=labName, norm=options.norm)




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
                  "btags_noV0/nTracks",

        "btags/sv_NTracks",
                  #"ip2d",


          "tracks/IsFromV0",
          "tracks/IsFromSV",
#        "neutralHadronEnergyFraction",
#        "trackSumJetEtRatio",
        ]:
    for d in plotDirs:
        plot(v,d,       binning=1,doratio=1,rMin=0.5,rMax=1.5,logy=0,minY=0,labels=labName,norm=options.norm)

#
#
#for v in [
#        "muonEnergyFraction",
#        "muEF",
#
#        ]:
#    doVarRatio(v,
#          xTitle = v,
#          binning = 1,
#          setLogy = 1,
#          )
#
for v in [
        "btags/sv_Mass",
        "m",
        ]:
    for d in plotDirs:
        plot(v,d,       binning=1,doratio=1,rMin=0.5,rMax=1.5,logy=0,x_min = 0, x_max=15,labels=labName,norm=options.norm)
