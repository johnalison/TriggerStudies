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
