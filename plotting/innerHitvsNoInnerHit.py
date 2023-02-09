import ROOT

from   ROOTHelp.Utils         import do_variable_rebinning, makeCanvas
from   ROOTHelp.Plotting      import makeRatio
#from rocCurveUtils            import drawWaterMarks
#import rebinning
from Rebinning import rebinningDB


ROOT.gROOT.SetBatch(True)
ROOT.gErrorIgnoreLevel = ROOT.kWarning

import ROOTHelp.FancyROOTStyle
from JetLevelPlotUtils import getCMSText
from optparse import OptionParser

def getOpts():

    p = OptionParser()
    p.add_option('--input',  type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile', help = 'intput File' )
    p.add_option('--input2',  type = 'string', default = None, dest = 'inFile2', help = 'intput File' )
    p.add_option('--output', type = 'string', default = "makeRocCurves", dest = 'outDir', help = 'output dir' )
    p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
    #p.add_option('--labName', type = 'string', default = "Reference,Monitored",  help = '' )
    #p.add_option('--lumiText', default = "",  help = '' )
    (o,a) = p.parse_args()

    return o, a



maxDict = {"jetNSelectedTracks":20,
           "jetNTracks":30,
           }


def getHist(inFile,dir,var,binning,color):
    hist = inFile.Get(dir+"/"+var)
    print( dir+"/"+var)
    if type(binning ) == type(list()):
        hist  = do_variable_rebinning(hist,binning)
    else:
        hist.Rebin(binning)

    hist.SetLineColor(color)
    hist.SetMarkerColor(color)
    hist.Sumw2()
    if hist.Integral():
        hist.Scale(1./hist.Integral())
    return hist




def doVarRatioPlot(var, offLF, hltLF, offBQ, hltBQ, xTitle, setLogy=1, minX=None, maxX=None, minY=None, yAxisSF=1.0, subText="", outputDir=""):
    maxY = max(offLF.GetMaximum(),offBQ.GetMaximum(),
               hltLF.GetMaximum(),hltBQ.GetMaximum())

    maxY = maxY*yAxisSF
    if setLogy:
        offLF.SetMaximum(4e0*maxY)
        offLF.SetMinimum(1.01e-5)
    else:
        offLF.SetMaximum(1.2*maxY)

    if not minY == None :
        offLF.SetMinimum(minY)


    offLF.GetYaxis().SetTitle("Normalized")
    offLF.GetXaxis().SetTitle(xTitle )

    if maxX:
        offLF.GetXaxis().SetRangeUser(minX,maxX)
        offBQ.GetXaxis().SetRangeUser(minX,maxX)
        hltLF.GetXaxis().SetRangeUser(minX,maxX)
        hltBQ.GetXaxis().SetRangeUser(minX,maxX)


    LFRatio = makeRatio(num = hltLF.Clone(),  den = offLF.Clone())
    BQRatio = makeRatio(num = hltBQ.Clone(),  den = offBQ.Clone())

    xpos = 0.5
    ypos = 0.675
    xwidth = 0.4
    ywidth = 0.2

    leg = ROOT.TLegend(xpos, ypos, xpos+xwidth, ypos+ywidth)
    leg.SetNColumns(1)
    leg.AddEntry(offBQ,"inner Pix Hit b-jets","L")
    leg.AddEntry(offLF,"inner Pix Hit light-flavor","L")
    leg.AddEntry(hltBQ,"no Inner Pix Hit b-jets"    ,"PEL")
    leg.AddEntry(hltLF,"no Inner Pix Hit light-flavor" ,"PEL")

    canvas = makeCanvas(var, var, width=600, height=600)
    split=0.3
    top_pad    = ROOT.TPad("pad1", "The pad 80% of the height",0,split,1,1,0)
    bottom_pad = ROOT.TPad("pad2", "The pad 20% of the height",0,0,1,split,0)
    top_pad.Draw()
    bottom_pad.Draw()

    axissep = 0.02
    top_pad.cd()
    top_pad.SetLogy(setLogy)
    top_pad.SetTopMargin(canvas.GetTopMargin()*1.0/(1.0-split))
    top_pad.SetBottomMargin(0.5*axissep)
    top_pad.SetRightMargin(canvas.GetRightMargin())
    top_pad.SetLeftMargin(canvas.GetLeftMargin());
    top_pad.SetFillStyle(0) # transparent
    top_pad.SetBorderSize(0)

    if var in maxDict.keys():
        offLF.GetXaxis().SetRangeUser(offLF.GetXaxis().GetXmin(),maxDict[var] )

    offLF.Draw("hist")
    # hltLF.SetMarkerSize(0.75)
    hltLF.SetMarkerSize(0.5)
    #hltLF.SetMarkerStyle(21)
    hltLF.Draw("same pe")
    offBQ.Draw("hist same")
    hltBQ.SetMarkerSize(0.5)
    #hltBQ.SetMarkerStyle(21)
    hltBQ.Draw("same pe")
    leg.Draw("same")






    cmsLines = getCMSText(xStart=0.2,yStart=0.85,subtext=subText)
    for cmsl in cmsLines:
        cmsl.Draw("same")



    bottom_pad.cd()
    bottom_pad.SetTopMargin(2*axissep)
    bottom_pad.SetBottomMargin(canvas.GetBottomMargin()*1.0/split)
    bottom_pad.SetRightMargin(canvas.GetRightMargin())
    bottom_pad.SetLeftMargin(canvas.GetLeftMargin());
    bottom_pad.SetFillStyle(0) # transparent
    bottom_pad.SetBorderSize(0)
    ratio_axis = offLF.Clone()
    ratio_axis.GetYaxis().SetTitle("Ratio")
    ratio_axis.GetXaxis().SetTitle(offLF.GetXaxis().GetTitle())
    ratio_axis.GetYaxis().SetNdivisions(507)
    rMin = 0.0
    rMax = 2.0


    if var in maxDict.keys():
        LFRatio.GetXaxis().SetRangeUser(LFRatio.GetXaxis().GetXmin(),maxDict[var] )

    ratio_axis.GetYaxis().SetRangeUser(rMin, rMax)
    LFRatio.GetYaxis().SetRangeUser(rMin, rMax)
    LFRatio.GetYaxis().SetTitle("Ratio")


    LFRatio.Draw("PE")
    LFRatio.Draw("PE same")
    # oldSize = LFRatio.GetMarkerSize()
    oldSize = hltLF.GetMarkerSize()
    LFRatio.SetMarkerSize(0)
    LFRatio.DrawCopy("same e0")
    LFRatio.SetMarkerSize(oldSize)
    LFRatio.Draw("PE same")


    BQRatio.Draw("PE same")
    BQRatio.Draw("PE same")
    # oldSize = BQRatio.GetMarkerSize()
    oldSize = hltBQ.GetMarkerSize()
    BQRatio.SetMarkerSize(0)
    BQRatio.DrawCopy("same e0")
    BQRatio.SetMarkerSize(oldSize)
    BQRatio.Draw("PE same")



    line = ROOT.TLine()
    line.DrawLine(offLF.GetXaxis().GetXmin(), 1.0, offLF.GetXaxis().GetXmax(), 1.0)

    ndivs=[505,503]

    pads = [top_pad, bottom_pad]
    factors = [0.8/(1.0-split), 0.7/split]
    for i_pad, pad in enumerate(pads):

        factor = factors[i_pad]
        ndiv   = ndivs[i_pad]

        prims = [ p.GetName() for p in pad.GetListOfPrimitives() ]

        #
        #  Protection for scaling hists multiple times
        #
        procedHist = []

        for name in prims:

            if name in procedHist: continue
            procedHist.append(name)

            h = pad.GetPrimitive(name)
            if isinstance(h, ROOT.TH1) or isinstance(h, ROOT.THStack) or isinstance(h, ROOT.TGraph) or isinstance(h, ROOT.TGraphErrors) or isinstance(h, ROOT.TGraphAsymmErrors):
                if isinstance(h, ROOT.TGraph) or isinstance(h, ROOT.THStack) or isinstance(h, ROOT.TGraphErrors) or isinstance(h, ROOT.TGraphAsymmErrors):
                    h = h.GetHistogram()
                #print "factor is",factor,h.GetName(),split

                if i_pad == 1:
                    h.SetLabelSize(h.GetLabelSize('Y')*factor, 'Y')
                    h.SetTitleSize(h.GetTitleSize('X')*factor, 'X')
                    h.SetTitleSize(h.GetTitleSize('Y')*factor, 'Y')
                    h.SetTitleOffset(h.GetTitleOffset('Y')/factor, 'Y')

                if i_pad == 1:
                    h.GetYaxis().SetNdivisions(ndiv)
                h.GetXaxis().SetNdivisions()
                if i_pad == 0:
                    h.SetLabelSize(0.0, 'X')
                    h.GetXaxis().SetTitle("")
                else:
                    h.SetLabelSize(h.GetLabelSize('X')*factor, 'X')
                    ## Trying to remove overlapping y-axis labels.  Doesn't work.
                    # h.GetYaxis().Set(4, h.GetYaxis().GetXmin(), h.GetYaxis().GetXmax())
                    # h.GetYaxis().SetBinLabel( h.GetYaxis().GetLast(), '')





    ##xatlas, yatlas = 0.18, 0.88
    ##atlas   = ROOT.TLatex(xatlas+0.01,   yatlas, "ATLAS")
    ###simulation = ROOT.TLatex(xatlas+0.11,   yatlas, "Simulation Internal")
    ##simulation = ROOT.TLatex(xatlas+0.11,   yatlas, "Simulation Preliminary")
    ##lumi    = ROOT.TLatex(xatlas+0.01,    yatlas-0.05, "#sqrt{s}=13 TeV, t#bar{t}")
    ##jetText = ROOT.TLatex(xatlas+0.02,   yatlas-0.1, "p_{T}^{jet} > 40 GeV, |#eta^{jet}| < 2.5" )
    ##wm      = [atlas, simulation, lumi, jetText]

    #watermarks = drawWaterMarks(wm)

    #varName = var.replace("tracks/","").replace("btags/","btags_")
    varName = var.replace("tracks/","track_").replace("btags/","btag_").replace("btags_noV0/","btag_noV0_")
    varName = varName.replace("tracks_innerPixHit/","track_innerPixHit_").replace("tracks_noInnerPixHit/","track_noInnerPixHit_")
    canvas.SaveAs(outputDir+"/BvL_"+varName+".pdf")
    #canvas.SaveAs(o.outDir+"/"+var+".eps")
    #canvas.SaveAs(o.outDir+"/"+var+".png")



def doVarRatioInnerPixel(inFile1, inFile2, BQName1, LFName1, BQName2, LFName2, var, binning, xTitle, setLogy=1, minX=None, maxX=None, minY=None, yAxisSF=1.0, subText="", outputDir=""):
    
    
    
    offLF = getHist(inFile1,LFName1+"/tracks_innerPixHit",   var,binning,ROOT.kBlack)
    hltLF = getHist(inFile2,LFName2+"/tracks_noInnerPixHit", var,binning,ROOT.kBlack)
    offBQ = getHist(inFile1,BQName1+"/tracks_innerPixHit",   var,binning,ROOT.kRed)
    hltBQ = getHist(inFile2,BQName2+"/tracks_noInnerPixHit", var,binning,ROOT.kRed)
    doVarRatioPlot(var+"_compInnerPix", offLF, hltLF, offBQ, hltBQ, xTitle=xTitle, setLogy=setLogy, minX=minX, maxX=maxX, minY=minY, yAxisSF=yAxisSF, subText=subText, outputDir=outputDir)
#    doVarRatioPlot(offLF, hltLF, offBQ, hltBQ, xTitle, setLogy=1, minX=None, maxX=None, minY=None, yAxisSF=1.0)


#doVar("ip3d_sig_l",
#      xTitle = "ip3d significance",
#      #binning = [-20,-18,-16,-14,-12,-11,-10,-8,-6,-5,-4,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,4,5,6,8,10,11,12,14,16,18,20,22,24,28,32,36,40]
#      binning = [-100 , -90,-80 , -70  , -60 ,  -50 , -40 , -34 , -32 , -30 , -28 , -26 , -24 , -22 , -20 , -18 , -16 , -14 , -12 , -10 , -8 , -6 , -4 , -2 , 0 , 2 , 4 , 6 , 8 , 10 , 12 , 14 , 16 , 18 , 20 , 22 , 24 , 26 , 28 , 30 , 32 , 34 , 40 , 50 , 60 , 70 , 80, 90 , 100]
#      #binning = [-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,-5,0,5,10,15,20,30,40,50,60,70,80,90,100]
#      )

def makePlots(inFile1, inFile2, extraText, outputDir, BQName1, LFName1, BQName2, LFName2):



    for v in [
              "ip2d",
              "ip2d_l",
              "ip2d_sig",
              "ip2d_sig_l",
              "ip3d",
              "ip3d_l",
              "ip3d_sig",
              "ip3d_sig_l",
            ]:
    
        vName = v.split("/")[-1]
        if vName in rebinningDB:
            binning = rebinningDB[vName]
        else:
            binning = 2
            
        doVarRatioInnerPixel(inFile1, 
                             inFile2, 
                             BQName1, 
                             LFName1, 
                             BQName2, 
                             LFName2, 
                             v,
                             xTitle = v,
                             binning = binning,
                             yAxisSF = 100,
                             subText=extraText,
                             outputDir = outputDir
        )
    



if __name__ == "__main__":
    o, a = getOpts()

    inFile1  = ROOT.TFile(o.inFile,  "READ")

    if o.inFile2: 
        inFile2  = ROOT.TFile(o.inFile2,  "READ")
    else:
        inFile2 = inFile1
    

    #labName = o.labName.split(",")
    
    import os
    if not os.path.exists(o.outDir):
        os.makedirs(o.outDir)


    makePlots(
        BQName1 = "offJets_matched_B",
        BQName2 = "offJets_matched_B",
        LFName1 = "offJets_matched_L",
        LFName2 = "offJets_matched_L",
        inFile1   = inFile1,
        inFile2   = inFile2,
        extraText = o.cmsText,
        outputDir = o.outDir
    )


