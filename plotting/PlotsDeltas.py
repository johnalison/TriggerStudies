from iUtils import parseOpts, getPM, setBatch, plot

setBatch()
(o,a) = parseOpts()
pm = getPM(o)

#
# Jet-Level
#
vars = [
    "matched_dDeepcsv",
    "matched_dEta",
    "matched_dPhi",
    "matched_dPt",
    "matched_dR",
    ]


for v in vars:
    plot(v,"offJets_matched",logy=1)


#
#  BTagging Level
#
vars = [
    # Track Level
    "d_ip2d"                ,
    "d_ip2d_err"            ,
    "d_ip2d_err_l"          ,
    "d_ip2d_l"              ,
    "d_ip2d_sig"            ,
    "d_ip2d_sig_l"          ,
    "d_ip3d"                ,
    "d_ip3d_err"            ,
    "d_ip3d_err_l"          ,
    "d_ip3d_l"              ,
    "d_ip3d_sig"            ,
    "d_ip3d_sig_l"          ,
    "d_trackChi2"           ,
    "d_trackDecayLenVal"    ,
    "d_trackDecayLenVal_l"  ,
    "d_trackDeltaR"         ,
    "d_trackDeltaR_l"       ,
    "d_trackEta"            ,
    "d_trackEtaRel"         ,
    "d_trackIsFromV0"       ,
    "d_trackJetDistVal"     ,
    "d_trackMomentum"       ,
    "d_trackNPixelHits"     ,
    "d_trackNTotalHits"     ,
    "d_trackPPar"           ,
    "d_trackPParRatio"      ,
    "d_trackPhi"            ,
    "d_trackPt"             ,
    "d_trackPtRatio"        ,
    "d_trackPtRel"          ,

    # jet level
    "d_chargedEmEnergyFraction",
    "d_chargedHadronEnergyFraction",
    "d_chargedHadronMultiplicity",
    "d_chargedMultiplicity",
    "d_elecEnergyFraction",
    "d_elecMultiplicity",
    "d_jetNSecondaryVertices",
    "d_jetNTracks",
    "d_muonEnergyFraction",
    "d_muonMultiplicity",
    "d_neutralEmEnergyFraction",
    "d_neutralHadronEnergyFraction",
    "d_neutralHadronMultiplicity",
    "d_neutralMultiplicity",
    "d_photonEnergyFraction",
    "d_photonMultiplicity",
    "d_totalMultiplicity",

    # SVs
    "sv_d_BoostOverSqrtJetPt",
    "sv_d_Chi2",
    "sv_d_Chi2_l",
    "sv_d_DistJetAxis",
    "sv_d_EnergyRatio",
    "sv_d_Eta",
    "sv_d_Flight",
    "sv_d_Flight2D",
    "sv_d_FlightSig",
    "sv_d_FlightSig2D",
    "sv_d_JetDeltaR",
    "sv_d_Mass",
    "sv_d_NDF",
    "sv_d_NTracks",
    "sv_d_Phi",
    "sv_d_Pt",
    "sv_d_R",
    "sv_d_Z",
    "sv_d_massVertexEnergyFraction",
    "sv_d_nSVs",
    "sv_d_totCharge",

    ]

for v in vars:
    plot(v,"offJets_matched/btags/deltaHists",logy=1)
