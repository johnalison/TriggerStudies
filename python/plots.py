import sys
import collections
sys.path.insert(0, '../../PlotTools/python/') #https://github.com/patrickbryant/PlotTools
import PlotTools

import optparse
parser = optparse.OptionParser()
parser.add_option('-i', '--inFileName',           dest="infileName",         default=None, help="Run in loop mode")
parser.add_option('-o', '--outFileName',          dest="outfileName",        default="../run/plots/", help="Run in loop mode")
parser.add_option('-d', '--debug',                dest="debug",    action="store_true",       default=False, help="Run in loop mode")
o, a = parser.parse_args()

varLabels = {"pt"     : "p_{T} [GeV]",
             "pt_l"   : "p_{T} [GeV]",
             "deepcsv": "Deep CSV",
             "deepcsv_matched": "Deep CSV",
             "trackDeltaR" : "#DeltaR(track, jet)",
         }

rebin = {"pt"   : range(0,120,4) + range(120,200,8) + range(200,260,12) + range(260,300,20) + [300, 340, 400],
         "pt_l" : range(0,201,10)+range(220,321,20)+range(360,401,40)+range(500,801,100)+[1000],
         }
#rebin["deepcsv"] = [0.005*i for i in range(0,21)] + [0.12+0.02*i for i in range(0,39)] + [0.9+0.005*i for i in range(0,21)]
rebin["deepcsv"] = 4
rebin["deepcsv_matched"] = rebin["deepcsv"]

samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["pfJets_matched/deepcsv"] = {"label"    : "Online",
                                                   "ratio"    : "numer A",
                                                   "isData"   : True,
                                                   "color"    : "ROOT.kBlack"}

samples[o.infileName]["pfJets_matched/deepcsv_matched"] = {"label"    : "Offline (Matched)",
                                                           "ratio"    : "denom A",
                                                           "color"    : "ROOT.kRed"}

parameters = {"ratio"     : True,
              "rebin"     : rebin["deepcsv"],
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Jets / Bin",
              "outputDir" : o.outfileName,
              "outputName": "pfJets_matched_deepcsv",
              "xleg"      : [0.2,0.4],
}

PlotTools.plot(samples, parameters)

samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offJets/deepcsv_matched"] = {"label"    : "Online (Matched)",
                                                    "ratio"    : "numer A",
                                                    "isData"   : True,
                                                    "color"    : "ROOT.kBlack",
                                                    "normalize": 1,
                                                }

samples[o.infileName]["offJets/deepcsv"] = {"label"    : "Offline",
                                            "ratio"    : "denom A",
                                            "color"    : "ROOT.kRed",
                                            "normalize": 1,
                                        }

parameters = {"ratio"     : True,
              "rebin"     : rebin["deepcsv"],
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Arb. Units",
              "outputDir" : o.outfileName,
              "outputName": "offJets_deepcsv",
              "xleg"      : [0.2,0.4],
}

PlotTools.plot(samples, parameters)


samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offJets_B/deepcsv_matched"] = {"label"    : "Online (Matched)",
                                                      "ratio"    : "numer A",
                                                      "isData"   : True,
                                                      "color"    : "ROOT.kBlack",
                                                      "normalize": 1,
                                                  }

samples[o.infileName]["offJets_B/deepcsv"] = {"label"    : "Offline",
                                              "ratio"    : "denom A",
                                              "color"    : "ROOT.kRed",
                                              "normalize": 1,
                                          }

parameters = {"ratio"     : True,
              "rebin"     : rebin["deepcsv"],
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Arb. Units",
              "outputDir" : o.outfileName,
              "outputName": "offJets_B_deepcsv",
              "xleg"      : [0.2,0.4],
}

PlotTools.plot(samples, parameters)


samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offJets_L/deepcsv_matched"] = {"label"    : "Online (Matched)",
                                                      "ratio"    : "numer A",
                                                      "isData"   : True,
                                                      "color"    : "ROOT.kBlack",
                                                      "normalize": 1,
                                                  }

samples[o.infileName]["offJets_L/deepcsv"] = {"label"    : "Offline",
                                              "ratio"    : "denom A",
                                              "color"    : "ROOT.kRed",
                                              "normalize": 1,
                                          }

parameters = {"ratio"     : True,
              "rebin"     : rebin["deepcsv"],
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Arb. Units",
              "outputDir" : o.outfileName,
              "outputName": "offJets_L_deepcsv",
              "xleg"      : [0.2,0.4],
}

PlotTools.plot(samples, parameters)



samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offJets_matched_online60/deepcsv_matched"] = {"label"    : "Online (Matched)",
                                                                     "ratio"    : "numer A",
                                                                     "isData"   : True,
                                                                     "color"    : "ROOT.kBlack",
                                                                 }

samples[o.infileName]["offJets_matched_online60/deepcsv"] = {"label"    : "Offline",
                                                             "ratio"    : "denom A",
                                                             "color"    : "ROOT.kRed",
                                                         }

parameters = {"ratio"     : True,
              "rebin"     : rebin["deepcsv"],
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Jets / Bin",
              "outputDir" : o.outfileName,
              "outputName": "offJets_matched_online60_deepcsv",
              "xleg"      : [0.2,0.4],
}

PlotTools.plot(samples, parameters)


for var in ["pt","pt_l"]:
    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offJets_B_matched/"+var] = {"label"    : "Matched to pfJet",
                                                          "ratio"    : "numer A",
                                                          "isData"   : True,
                                                          "color"    : "ROOT.kBlack",
                                                      }

    samples[o.infileName]["offJets_B/"+var] = {"label"    : "Offline Jets",
                                               "ratio"    : "denom A",
                                               "color"    : "ROOT.kRed",
                                           }
    
    parameters = {"ratio"     : True,
                  "rMin"      : 0,
                  "rMax"      : 1,
                  "logX"      : True if "logx" in var else False,
                  "maxDigits" : 4,
                  "rebin"     : rebin[var] if var in rebin else "smart",
                  "title"     : "truth b-tagged",
                  "tMargin"   : 0.07,
                  "titleOffset": 0.0,
                  "rTitle"    : "Matched / All",
                  "xTitle"    : varLabels[var],
                  "yTitle"    : "Jets / Bin",
                  "outputDir" : o.outfileName,
                  "outputName": "offJets_B_"+var,
              }

    PlotTools.plot(samples, parameters)

    for WP in ["60","70","80","90"]:
        samples=collections.OrderedDict()
        samples[o.infileName] = collections.OrderedDict()

        samples[o.infileName]["offJets_offline70_B_matched_online"+WP+"/"+var] = {"label"    : "Online WP"+WP,
                                                                                  "ratio"    : "numer A",
                                                                                  "isData"   : True,
                                                                                  "color"    : "ROOT.kBlack",
                                                                              }

        samples[o.infileName]["offJets_offline70_B_matched/"+var] = {"label"    : "No Online Req.",
                                                                     "ratio"    : "denom A",
                                                                     "color"    : "ROOT.kRed",
                                                                 }
    
        parameters = {"ratio"     : True,
                      "rMin"      : 0,
                      "rMax"      : 1,
                      "logX"      : True if "logx" in var else False,
                      "maxDigits" : 4,
                      "rebin"     : rebin[var] if var in rebin else "smart",
                      "title"     : "matched to pfJet, truth b-tagged, offline WP70",
                      "tMargin"   : 0.07,
                      "titleOffset": 0.0,
                      "rTitle"    : "On. WP"+WP+" / No Req.",
                      "xTitle"    : varLabels[var],
                      "yTitle"    : "Jets / Bin",
                      "outputDir" : o.outfileName,
                      "outputName": "offJets_offline70_B_matched_online"+WP+"_"+var,
                  }

        PlotTools.plot(samples, parameters)


        samples=collections.OrderedDict()
        samples[o.infileName] = collections.OrderedDict()

        samples[o.infileName]["offJets_B_matched_online"+WP+"/"+var] = {"label"    : "Online WP"+WP,
                                                                      "ratio"    : "numer A",
                                                                      "isData"   : True,
                                                                      "color"    : "ROOT.kBlack",
                                                                  }

        samples[o.infileName]["offJets_B_matched/"+var] = {"label"    : "No Online Req.",
                                                         "ratio"    : "denom A",
                                                         "color"    : "ROOT.kRed",
                                                     }
    
        parameters = {"ratio"     : True,
                      "rMin"      : 0,
                      "rMax"      : 1,
                      "logX"      : True if "logx" in var else False,
                      "maxDigits" : 4,
                      "rebin"     : rebin[var] if var in rebin else "smart",
                      "title"     : "matched to pfJet, truth b-tagged",
                      "tMargin"   : 0.07,
                      "titleOffset": 0.0,
                      "rTitle"    : "On. WP"+WP+" / No Req.",
                      "xTitle"    : varLabels[var],
                      "yTitle"    : "Jets / Bin",
                      "outputDir" : o.outfileName,
                      "outputName": "offJets_B_matched_online"+WP+"_"+var,
                  }

        PlotTools.plot(samples, parameters)



import ROOT
f=ROOT.TFile(o.infileName,"READ")
f.cd("offJets_matched")
for key in ROOT.gDirectory.GetListOfKeys():
    if "TH1" not in key.GetClassName(): continue
    var = key.GetName()

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offJets/"   +var] = {"label"    : "All Offline Jets",
                                                "legend"   : 1,
                                                "ratio"    : "denom A",
                                                "color"    : "ROOT.kRed"}

    samples[o.infileName]["offJets_matched/"+var] = {"label"    : "Matched Offline Jets",
                                                     "ratio"    : "numer A",
                                                     "isData"   : True,
                                                     "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "rMax"      : 1,
                  "rMin"      : 0,
                  "logX"      : True if "logx" in var else False,
                  "maxDigits" : 4,
                  "rTitle"    : "Matched / All",
                  "outputDir" : o.outfileName+"/matched_offJets_over_offJets/",
                  "outputName": var,
              }

    if "matched_d" in var:
        samples=collections.OrderedDict()
        samples[o.infileName] = collections.OrderedDict()

        samples[o.infileName]["offJets_matched/"   +var] = {"label"    : "Offline - Online (PF)",
                                                            "isData"   : True,
                                                            "legend"   : 1,
                                                            #"ratio"    : "denom A",
                                                            "color"    : "ROOT.kBlack"}
    
        parameters = {"maxDigits" : 4,
                      "logX"      : True if "logx" in var else False,
                      "logY" : True,
                      "yleg"      : [0.7, 0.8],
                      "xTitleOffset" : 1,
                      "showStats" : 1100,
                      #"yMin" : 1,
                      "outputDir" : o.outfileName+"/offJet_minus_pfJet/",
                      "outputName": var,
                  }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offJets_matched/"   +var] = {"label"    : "Offline Jet",
                                                        "legend"   : 1,
                                                        "ratio"    : "denom A",
                                                        "color"    : "ROOT.kRed"}

    samples[o.infileName]["offJets_matchedJet/"+var] = {"label"    : "Matched Online Jet",
                                                        "ratio"    : "numer A",
                                                        "isData"   : True,
                                                        "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "rMax"      : 2,
                  "rMin"      : 0,
                  "logX"      : True if "logx" in var else False,
                  "maxDigits" : 4,
                  "rTitle"    : "Matched / All",
                  "outputDir" : o.outfileName+"/offJets_matchedJet_over_offJets_matched/",
                  "outputName": var,
              }

    if "matched_d" in var: continue
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)

#Track Matching plots
samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offTracks_matched/track_matched_dEta_s"] = {"label"    : "First Match",
                                                                   "legend"   : 1,
                                                                   "color"    : "ROOT.kRed"}

samples[o.infileName]["offTracks_matched/track_secondClosest_dEta_s"] = {"label"    : "Second Match",
                                                                         "legend"   : 2,
                                                                         "color"    : "ROOT.kBlue"}

parameters = {"maxDigits" : 4,
              "xTitleOffset" : 1,
              "xTitle"    : "#eta-#eta^{match}",
              "logY"      : True,
              "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
              "outputName": "matching_dEta",
          }
PlotTools.plot(samples,parameters)

samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offTracks_matched/track_matched_dMomentum"] = {"label"    : "First Match",
                                                                 "legend"   : 1,
                                                                 "color"    : "ROOT.kRed"}

samples[o.infileName]["offTracks_matched/track_secondClosest_dMomentum"] = {"label"    : "Second Match",
                                                                       "legend"   : 2,
                                                                       "color"    : "ROOT.kBlue"}

parameters = {"maxDigits" : 4,
              # "xMax"      : 0.02,
              # "xMin"      : -0.02,
              "xTitleOffset" : 1,
              "xTitle"    : "p-p^{match}",
              "logY"      : True,
              "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
              "outputName": "matching_dMomentum",
          }
PlotTools.plot(samples,parameters)

samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offTracks_matched/track_matched_dR"] = {"label"    : "First Match",
                                                                 "legend"   : 1,
                                                                 "color"    : "ROOT.kRed"}

samples[o.infileName]["offTracks_matched/track_secondClosest_dR"] = {"label"    : "Second Match",
                                                                       "legend"   : 2,
                                                                       "color"    : "ROOT.kBlue"}

parameters = {"maxDigits" : 4,
              # "xMax"      : 0.02,
              # "xMin"      : -0.02,
              "xTitleOffset" : 1,
              "xTitle"    : "#DeltaR(track, match)",
              "logY"      : True,
              "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
              "outputName": "matching_dR",
}
PlotTools.plot(samples,parameters)

samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offTracks_matched/track_matched_dR_s"] = {"label"    : "First Match",
                                                                 "legend"   : 1,
                                                                 "color"    : "ROOT.kRed"}

samples[o.infileName]["offTracks_matched/track_secondClosest_dR_s"] = {"label"    : "Second Match",
                                                                       "legend"   : 2,
                                                                       "color"    : "ROOT.kBlue"}

parameters = {"maxDigits" : 4,
              # "xMax"      : 0.02,
              # "xMin"      : -0.02,
              "yMax"      : 3e5,
              "yMin"      : 20,
              "xTitleOffset" : 1,
              "xTitle"    : "#DeltaR(track, match)",
              "logY"      : True,
              "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
              "outputName": "matching_dR_s",
}
PlotTools.plot(samples,parameters)


samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offTracks_matched/track_matched_dEta_vs_dMomentum"] = {"TObject":"",
                                                                              "drawOptions": "COLZ",
                                                                          }

parameters = {"maxDigits" : 4,
              "xTitleOffset": 0.8,
              "yTitleOffset": 0.8,
              "logZ"      : True,
              "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
              "outputName": "track_matched_dEta_vs_dMomentum",
}
PlotTools.plot(samples,parameters)

samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offTracks_matched/track_secondClosest_dEta_vs_dMomentum"] = {"TObject":"",
                                                                              "drawOptions": "COLZ",
                                                                          }

parameters = {"maxDigits" : 4,
              "xTitleOffset": 0.8,
              "yTitleOffset": 0.8,
              "logZ"      : True,
              "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
              "outputName": "track_secondClosest_dEta_vs_dMomentum",
}
PlotTools.plot(samples,parameters)

samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["offTracks_matched/track_matched_dEta_vs_dPhi"] = {"TObject":"",
                                                                         "drawOptions": "COLZ",
                                                                     }

parameters = {"maxDigits" : 4,
              "xTitleOffset": 0.8,
              "yTitleOffset": 0.8,
              "logZ"      : True,
              "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
              "outputName": "track_matched_dEta_vs_dPhi",
}
PlotTools.plot(samples,parameters)

# samples=collections.OrderedDict()
# samples[o.infileName] = collections.OrderedDict()

# samples[o.infileName]["offTracks_matched/track_secondClosest_dEta_vs_dPhi"] = {"TObject":"",
#                                                                                "drawOptions": "COLZ",
#                                                                            }

# parameters = {"maxDigits" : 4,
#               "xTitleOffset": 0.8,
#               "yTitleOffset": 0.8,
#               "logZ"      : True,
#               "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
#               "outputName": "track_secondClosest_dEta_vs_dPhi",
# }
# PlotTools.plot(samples,parameters)

f.cd("offTracks_matched")
for key in ROOT.gDirectory.GetListOfKeys():
    if "TH1" not in key.GetClassName(): continue
    var = key.GetName()

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offTracks_matched/"+var] = {"label"    : "Matched Offline Tracks",
                                                       "legend"   : 1,
                                                       "ratio"    : "denom A",
                                                       "color"    : "ROOT.kRed"}

    samples[o.infileName]["pfTracks_matched/"+var] = {"label"    : "Matched PF Tracks",
                                                      "ratio"    : "numer A",
                                                      "isData"   : True,
                                                      "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "logX"      : True if "logx" in var else False,
                  "maxDigits" : 4,
                  "rTitle"    : "Online / Offline",
                  "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
                  "outputName": var,
              }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    if "matched_d" in var:
        samples=collections.OrderedDict()
        samples[o.infileName] = collections.OrderedDict()

        samples[o.infileName]["offTracks_matched/"   +var] = {"label"    : "Offline - Online (PF)",
                                                            "isData"   : True,
                                                            "legend"   : 1,
                                                            #"ratio"    : "denom A",
                                                            "color"    : "ROOT.kBlack"}
    
        parameters = {"maxDigits" : 4,
                      "logX"      : True if "logx" in var else False,
                      "logY" : True,
                      "yleg"      : [0.7, 0.8],
                      "showStats" : 1100,
                      "xTitleOffset" : 1,
                      #"yMin" : 1,
                      "outputDir" : o.outfileName+"/offTrack_minus_pfTrack/",
                      "outputName": var,
                  }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)


#nMatches
samples=collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()

samples[o.infileName]["pfTracks/track_nMatches"] = {"label"    : "PF Tracks (Matched Jets)",
                                                    #"isData"   : True,
                                                    "drawOptions": "HIST PE",
                                                    "legend"   : 1,
                                                    "color"    : "ROOT.kBlack"}

parameters = {"maxDigits" : 4,
              # "xMax"      : 0.02,
              # "xMin"      : -0.02,
              "yleg"      : [0.7, 0.8],
              "yTitle"    : "# of PF tracks",
              "xTitleOffset" : 1,
              "xTitle"    : "# of matched offline tracks",
              "logY"      : True,
              "outputDir" : o.outfileName+"/matching_pfTracks_over_offTracks/",
              "outputName": "pfTracks_nMatches",
}
PlotTools.plot(samples,parameters)

#Track Matching Efficincy plots
f.cd("offTracks")
for key in ROOT.gDirectory.GetListOfKeys():
    if "TH1" not in key.GetClassName(): continue
    var = key.GetName()
    if "matched_d" in var: continue

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offTracks/"+var] = {"label"    : "Offline Tracks",
                                               "legend"   : 1,
                                               "ratio"    : "denom A",
                                               "color"    : "ROOT.kRed"}

    samples[o.infileName]["pfTracks_matched/"+var] = {"label"    : "Matched PF Tracks",
                                                      "ratio"    : "numer A",
                                                      "isData"   : True,
                                                      "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "maxDigits" : 4,
                  "logX"      : True if "logx" in var else False,
                  "rTitle"    : "Online / Offline",
                  "outputDir" : o.outfileName+"/matched_pfTracks_over_offTracks/",
                  "outputName": var,
              }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offTracks/"+var] = {"label"    : "All Offline Tracks",
                                               "legend"   : 1,
                                               "ratio"    : "denom A",
                                               "color"    : "ROOT.kRed"}

    samples[o.infileName]["offTracks_matched/"+var] = {"label"    : "Matched Offline Tracks",
                                                       "ratio"    : "numer A",
                                                       "isData"   : True,
                                                       "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "rMin"      : 0.5,
                  "rMax"      : 1,
                  "logX"      : True if "logx" in var else False,
                  "maxDigits" : 4,
                  "rTitle"    : "Matched / All",
                  "outputDir" : o.outfileName+"/matched_offTracks_over_offTracks/",
                  "outputName": var,
              }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offTracks/"+var] = {"ratio"    : "denom A",
                                               "color"    : "ROOT.kRed"}

    samples[o.infileName]["offTracks_matched/"+var] = {"ratio"    : "numer A",
                                                       "isData"   : True,
                                                       "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "ratioOnly" : True,
                  "logX"      : True if "logx" in var else False,
                  "xTitleOffset":0.5,
                  "rMin"      : 0.6,
                  "rMax"      : 1.02,
                  #"maxDigits" : 4,
                  "rTitle"    : "Efficiency",
                  "outputDir" : o.outfileName+"/matched_offTracks_over_offTracks/",
                  "outputName": var+"_efficiency",
              }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["pfTracks/"+var] = {"label"    : "PF Tracks",
                                              "legend"   : 1,
                                              "isData"   : True,
                                              "ratio"    : "numer A",
                                              "color"    : "ROOT.kBlack",
                                          }

    samples[o.infileName]["pfTracks_unmatched/"+var] = {"label"    : "Unmatched",
                                                        "ratio"    : "denom A",
                                                        "stack"    : 1,
                                                        "legend"   : 3,
                                                        "color"    : "ROOT.kAzure-9"}

    samples[o.infileName]["pfTracks_matched/"+var] = {"label"    : "Matched",
                                                      "ratio"    : "denom A",
                                                      "stack"    : 2,
                                                      "legend"   : 2,
                                                      "color"    : "ROOT.kYellow"}
    
    parameters = {"ratio"     : True,
                  "maxDigits" : 4,
                  "logX"      : True if "logx" in var else False,
                  "rTitle"    : "Online / Stack",
                  "outputDir" : o.outfileName+"/pfTracks/",
                  "outputName": var,
              }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offTracks/"+var] = {"label"    : "Offline Tracks",
                                              "legend"   : 1,
                                              "isData"   : True,
                                              "ratio"    : "numer A",
                                              "color"    : "ROOT.kBlack",
                                          }

    samples[o.infileName]["offTracks_unmatched/"+var] = {"label"    : "Unmatched",
                                                         "ratio"    : "denom A",
                                                         "stack"    : 1,
                                                         "legend"   : 3,
                                                         "color"    : "ROOT.kAzure-9"}

    samples[o.infileName]["offTracks_matched/"+var] = {"label"    : "Matched",
                                                      "ratio"    : "denom A",
                                                      "stack"    : 2,
                                                      "legend"   : 2,
                                                      "color"    : "ROOT.kYellow"}
    
    parameters = {"ratio"     : True,
                  "maxDigits" : 4,
                  "logX"      : True if "logx" in var else False,
                  "rTitle"    : "Offline / Stack",
                  "outputDir" : o.outfileName+"/offTracks/",
                  "outputName": var,
              }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)


    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["pfTracks/"+var] = {"label"    : "PF Tracks",
                                              "legend"   : 1,
                                              "ratio"    : "denom A",
                                              "color"    : "ROOT.kRed",
                                          }

    samples[o.infileName]["pfTracks_unmatched/"+var] = {"label"    : "Unmatched",
                                                        "ratio"    : "numer A",
                                                        "isData"   : True,
                                                        "legend"   : 2,
                                                        "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "maxDigits" : 4,
                  "logX"      : True if "logx" in var else False,
                  "rMax"      : 0.3,
                  "rMin"      : 0,
                  "rTitle"    : "Unmatched / All",
                  "outputDir" : o.outfileName+"/unmatched_pfTracks_over_pfTracks/",
                  "outputName": var,
              }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offTracks_unmatched/"+var] = {"label"    : "Unmatched Off Tracks",
                                                         "legend"   : 1,
                                                         "ratio"    : "denom A",
                                                         "color"    : "ROOT.kRed",
                                                     }

    samples[o.infileName]["pfTracks_unmatched/"+var] = {"label"    : "Unmatched PF Tracks",
                                                        "ratio"    : "numer A",
                                                        "legend"   : 2,
                                                        "isData"   : True,
                                                        "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "maxDigits" : 4,
                  "logX"      : True if "logx" in var else False,
                  "rTitle"    : "PF / Offline",
                  "outputDir" : o.outfileName+"/unmatched_pfTracks_over_unmatched_offTracks/",
                  "outputName": var,
              }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)


    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offTracks/"+var] = {"label"    : "Offline Tracks",
                                              "legend"   : 1,
                                              "ratio"    : "denom A",
                                              "color"    : "ROOT.kRed",
                                          }

    samples[o.infileName]["offTracks_unmatched/"+var] = {"label"    : "Unmatched",
                                                        "ratio"    : "numer A",
                                                        "isData"   : True,
                                                        "legend"   : 2,
                                                        "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "maxDigits" : 4,
                  "logX"      : True if "logx" in var else False,
                  "rMax"      : 0.3,
                  "rMin"      : 0,
                  "rTitle"    : "Unmatched / All",
                  "outputDir" : o.outfileName+"/unmatched_offTracks_over_offTracks/",
                  "outputName": var,
              }
    if var in varLabels: parameters["xTitle"] = varLabels[var]

    PlotTools.plot(samples, parameters)
