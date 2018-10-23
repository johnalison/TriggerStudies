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

samples = collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()
samples[o.infileName]["offJets_ROC"] = {"color":"ROOT.kBlack",
                                      "drawOptions":"AL",
                                      "label":"offJets",
                                  }
samples[o.infileName]["pfJets_matched_ROC"] = {"color":"ROOT.kRed",
                                             "drawOptions":"L",
                                             "label":"Matched pfJets",
                                         }

parameters = {"outputDir":"",
              "outputName":o.outfileName,
              "xTitle":"b-jet Efficiency",
              "yTitle":"light jet Rejection",
              "xMin": 0,
              "xMax": 1,
              "logY": True,
              "yMax": 5e4,
              "yMin": 1,
          }

PlotTools.plot(samples,parameters,o.debug)


samples = collections.OrderedDict()
samples[o.infileName] = collections.OrderedDict()
samples[o.infileName]["offJets_ROC"] = {"color":"ROOT.kBlack",
                                        "drawOptions":"AL",
                                        "label":"offJets",
                                        "legend": 1,
                                    }
samples[o.infileName]["offJets_matched_online60_ROC"] = {"color":"ROOT.kRed",
                                                         "drawOptions":"L",
                                                         "label":"Online WP60",
                                                         "legend": 2,
                                                     }
samples[o.infileName]["offJets_matched_online70_ROC"] = {"color":"ROOT.kMagenta",
                                                         "drawOptions":"L",
                                                         "label":"Online WP70",
                                                         "legend": 3,
                                                     }
samples[o.infileName]["offJets_matched_online80_ROC"] = {"color":"ROOT.kGreen+2",
                                                         "drawOptions":"L",
                                                         "label":"Online WP80",
                                                         "legend": 4,
                                                     }
samples[o.infileName]["offJets_matched_online90_ROC"] = {"color":"ROOT.kBlue",
                                                         "drawOptions":"L",
                                                         "label":"Online WP90",
                                                         "legend": 5,
                                                     }
samples[o.infileName]["offJets_matched_ROC"] = {"color":"ROOT.kGray+1",
                                                "drawOptions":"L",
                                                "label":"pfJets",
                                                "legend": 6,
                                            }

parameters = {"outputDir":"",
              "outputName":o.outfileName+"_onlineTag",
              "xTitle":"b-jet Efficiency",
              "yTitle":"light jet Rejection",
              "xMin": 0,
              "xMax": 1,
              "logY": True,
              "yMax": 5e4,
              "yMin": 1,
          }

PlotTools.plot(samples,parameters,o.debug)
