import sys
import collections
sys.path.insert(0, '../../PlotTools/python/') #https://github.com/patrickbryant/PlotTools
import PlotTools

import optparse
parser = optparse.OptionParser()
parser.add_option('-i', '--inFileName',           dest="infileName",         default=None, help="Run in loop mode")
parser.add_option('-o', '--outFileName',          dest="outfileName",        default=None, help="Run in loop mode")
parser.add_option('-d', '--debug',                dest="debug",    action="store_true",       default=False, help="Run in loop mode")
o, a = parser.parse_args()

varLabels = {"pt"     : "p_{T} [GeV]",
             "pt_l"   : "p_{T} [GeV]",
             "deepcsv": "Deep CSV",
             "deepcsv_matched": "Deep CSV",
         }

rebin = {"pt"   : range(0,120,4) + range(120,200,8) + range(200,260,12) + range(260,300,20) + [300, 340, 400],
         "pt_l" : range(0,201,10)+range(220,321,20)+range(360,401,40)+range(500,801,100)+[1000],
     }

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
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Jets / Bin",
              "outputDir" : "../run/plots/",
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
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Arb. Units",
              "outputDir" : "../run/plots/",
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
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Arb. Units",
              "outputDir" : "../run/plots/",
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
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Arb. Units",
              "outputDir" : "../run/plots/",
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
              "rTitle"    : "Online / Offline",
              "xTitle"    : "DeepCSV",
              "yTitle"    : "Jets / Bin",
              "outputDir" : "../run/plots/",
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
                  "maxDigits" : 4,
                  "rebin"     : rebin[var] if var in rebin else 1,
                  "title"     : "truth b-tagged",
                  "tMargin"   : 0.07,
                  "titleOffset": 0.0,
                  "rTitle"    : "Matched / All",
                  "xTitle"    : varLabels[var],
                  "yTitle"    : "Jets / Bin",
                  "outputDir" : "../run/plots/",
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
                      "maxDigits" : 4,
                      "rebin"     : rebin[var] if var in rebin else 1,
                      "title"     : "matched to pfJet, truth b-tagged, offline WP70",
                      "tMargin"   : 0.07,
                      "titleOffset": 0.0,
                      "rTitle"    : "On. WP"+WP+" / No Req.",
                      "xTitle"    : varLabels[var],
                      "yTitle"    : "Jets / Bin",
                      "outputDir" : "../run/plots/",
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
                      "maxDigits" : 4,
                      "rebin"     : rebin[var] if var in rebin else 1,
                      "title"     : "matched to pfJet, truth b-tagged",
                      "tMargin"   : 0.07,
                      "titleOffset": 0.0,
                      "rTitle"    : "On. WP"+WP+" / No Req.",
                      "xTitle"    : varLabels[var],
                      "yTitle"    : "Jets / Bin",
                      "outputDir" : "../run/plots/",
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

    samples[o.infileName]["offJets_matched/"   +var] = {"label"    : "Offline Jets",
                                                        "legend"   : 1,
                                                        "ratio"    : "denom A",
                                                        "color"    : "ROOT.kRed"}

    samples[o.infileName]["offJets_matchedJet/"+var] = {"label"    : "Matched PF Jets",
                                                        "ratio"    : "numer A",
                                                        "isData"   : True,
                                                        "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "maxDigits" : 4,
                  "rTitle"    : "Online / Offline",
                  "outputDir" : "../run/plots/pfJets_over_offJets/",
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
                      "logY" : True,
                      "xTitleOffset" : 1,
                      "showStats" : 1100,
                      #"yMin" : 1,
                      "outputDir" : "../run/plots/offJet_minus_pfJet/",
                      "outputName": var,
                  }

    PlotTools.plot(samples, parameters)

#Track Matching plots
f.cd("offTracks_matched")
for key in ROOT.gDirectory.GetListOfKeys():
    if "TH1" not in key.GetClassName(): continue
    var = key.GetName()

    samples=collections.OrderedDict()
    samples[o.infileName] = collections.OrderedDict()

    samples[o.infileName]["offTracks_matched/"+var] = {"label"    : "Offline Tracks",
                                                       "legend"   : 1,
                                                       "ratio"    : "denom A",
                                                       "color"    : "ROOT.kRed"}

    samples[o.infileName]["pfTracks_matched/"+var] = {"label"    : "Matched PF Tracks",
                                                      "ratio"    : "numer A",
                                                      "isData"   : True,
                                                      "color"    : "ROOT.kBlack"}
    
    parameters = {"ratio"     : True,
                  "maxDigits" : 4,
                  "rTitle"    : "Online / Offline",
                  "outputDir" : "../run/plots/matching_pfTracks_over_offTracks/",
                  "outputName": var,
              }

    if "matched_d" in var:
        samples=collections.OrderedDict()
        samples[o.infileName] = collections.OrderedDict()

        samples[o.infileName]["offTracks_matched/"   +var] = {"label"    : "Offline - Online (PF)",
                                                            "isData"   : True,
                                                            "legend"   : 1,
                                                            #"ratio"    : "denom A",
                                                            "color"    : "ROOT.kBlack"}
    
        parameters = {"maxDigits" : 4,
                      "logY" : True,
                      "showStats" : 1100,
                      "xTitleOffset" : 1,
                      #"yMin" : 1,
                      "outputDir" : "../run/plots/offTrack_minus_pfTrack/",
                      "outputName": var,
                  }

    PlotTools.plot(samples, parameters)

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
                  "rTitle"    : "Online / Offline",
                  "outputDir" : "../run/plots/matched_pfTracks_over_offTracks/",
                  "outputName": var,
              }

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
                  "maxDigits" : 4,
                  "rTitle"    : "Matched / All",
                  "outputDir" : "../run/plots/matched_offTracks_over_offTracks/",
                  "outputName": var,
              }

    PlotTools.plot(samples, parameters)
