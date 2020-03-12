import ROOT


ROOT.gROOT.SetBatch(True)

import ROOTHelp.FancyROOTStyle

from optparse import OptionParser
p = OptionParser()
p.add_option('--input',  type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile', help = 'intput File' )
p.add_option('--output', type = 'string', default = "makeRocCurves", dest = 'outDir', help = 'output dir' )
p.add_option('--doCaloJets',  action="store_true",help = 'output dir' )
p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
#p.add_option('--lumiText', default = "",  help = '' )
(o,a) = p.parse_args()



from   ROOTHelp.Utils         import do_variable_rebinning, makeCanvas
from   ROOTHelp.Plotting      import makeRatio
#from rocCurveUtils            import drawWaterMarks
#import rebinning
from Rebinning import rebinningDB

from JetLevelPlotUtils import getCMSText

inFile  = ROOT.TFile(o.inFile,  "READ")

import os
if not os.path.exists(o.outDir):
    os.makedirs(o.outDir)


maxDict = {"jetNSelectedTracks":20,
           "jetNTracks":30,
           }


def getHist(inFile,dir,var,binning,color):
    hist = inFile.Get(dir+"/"+var)
    print dir+"/"+var
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

#def doVar(var,binning,xTitle,setLogy=1):
#    #offLF = getHist(inFile,"caloJets_matchedL",          var,binning,ROOT.kBlack)
#    offLF = getHist(inFile,"offJets_matched_L",          var,binning,ROOT.kBlack)
#    hltLF = getHist(inFile,"offJets_matchedJet_L",var,binning,ROOT.kBlack)
#    #hltLF = getHist(inFile,"caloJets_matchedL",var,binning,ROOT.kBlack)
#    #offBQ = getHist(inFile,"caloJets_matchedB",          var,binning,ROOT.kRed)
#    offBQ = getHist(inFile,"offJets_matched_B",          var,binning,ROOT.kRed)
#    hltBQ = getHist(inFile,"offJets_matchedJet_B",var,binning,ROOT.kRed)
#    #hltBQ = getHist(inFile,"caloJets_matchedB",var,binning,ROOT.kRed)
#
#    xpos = 0.18
#    ypos = 0.6
#    xwidth = 0.3
#    ywidth = 0.3
#
#    leg = ROOT.TLegend(xpos, ypos, xpos+xwidth, ypos+ywidth)
#    leg.AddEntry(offBQ,"Offline tracks b-quark jets","L")
#    leg.AddEntry(hltBQ,"HLT PF b-quark jets"    ,"PEL")
#    leg.AddEntry(offLF,"Offline tracks light-flavor jets","L")
#    leg.AddEntry(hltLF,"HLT PF light-flavor jets"    ,"PEL")
#
#
#    can = ROOT.TCanvas(var,var)
#    can.cd().SetLogy(setLogy)
#    maxY = max(offLF.GetMaximum(),offBQ.GetMaximum(),
#               hltLF.GetMaximum(),hltBQ.GetMaximum())
#    if setLogy:
#        offLF.SetMaximum(4e0*maxY)
#        offLF.SetMinimum(1e-6)
#    else:
#        offLF.SetMaximum(1.2*maxY)
#
#    offLF.GetYaxis().SetTitle("Simulated Tracks")
#    offLF.GetXaxis().SetTitle(xTitle )
#    offLF.Draw("hist")
#    #hltLF.SetMarkerSize(0.75)
#    #hltLF.SetMarkerStyle(21)
#    hltLF.Draw("same pe")
#    offBQ.Draw("hist same")
#    #hltBQ.SetMarkerSize(0.75)
#    #hltBQ.SetMarkerStyle(21)
#    hltBQ.Draw("same pe")
#    #leg.Draw("same")
#
#    cmsLine1, cmsLine2 = getCMSText(xStart=0.2,yStart=0.87)
#    cmsLine1.Draw("same")
#    cmsLine2.Draw("same")
#
#
#    #xatlas, yatlas = 0.18, 0.88
#    #atlas   = ROOT.TLatex(xatlas+0.01,   yatlas, "ATLAS")
#    ##simulation = ROOT.TLatex(xatlas+0.11,   yatlas, "Simulation Internal")
#    #simulation = ROOT.TLatex(xatlas+0.11,   yatlas, "Simulation Preliminary")
#    #lumi    = ROOT.TLatex(xatlas+0.01,    yatlas-0.05, "#sqrt{s}=13 TeV, t#bar{t}")
#    #jetText = ROOT.TLatex(xatlas+0.02,   yatlas-0.1, "p_{T}^{jet} > 40 GeV, |#eta^{jet}| < 2.5" )
#    #wm      = [atlas, simulation, lumi, jetText]
#
#    #watermarks = drawWaterMarks(wm)
#
#    varName = var.replace("tracks/","track_").replace("btags/","btag_")
#    can.SaveAs(o.outDir+"/"+varName+".pdf")
#    can.SaveAs(o.outDir+"/"+varName+".eps")
#    can.SaveAs(o.outDir+"/"+varName+".png")


def doVarRatio(var,binning,xTitle,setLogy=1,minX=None,maxX=None,minY=None):
    if o.doCaloJets:
        offLF = getHist(inFile,"offJets_matchedCalo_L",          var,binning,ROOT.kBlack)
        hltLF = getHist(inFile,"offJets_matchedCaloJet_L",var,binning,ROOT.kBlack)
        offBQ = getHist(inFile,"offJets_matchedCalo_B",          var,binning,ROOT.kRed)
        hltBQ = getHist(inFile,"offJets_matchedCaloJet_B",var,binning,ROOT.kRed)
    else:
        offLF = getHist(inFile,"offJets_matched_L",          var,binning,ROOT.kBlack)
        hltLF = getHist(inFile,"offJets_matchedJet_L",var,binning,ROOT.kBlack)
        offBQ = getHist(inFile,"offJets_matched_B",          var,binning,ROOT.kRed)
        hltBQ = getHist(inFile,"offJets_matchedJet_B",var,binning,ROOT.kRed)


    maxY = max(offLF.GetMaximum(),offBQ.GetMaximum(),
               hltLF.GetMaximum(),hltBQ.GetMaximum())
    if setLogy:
        offLF.SetMaximum(4e0*maxY)
        offLF.SetMinimum(1.01e-5)
    else:
        offLF.SetMaximum(1.2*maxY)

    if not minY == None :
        offLF.SetMinimum(minY)


    offLF.GetYaxis().SetTitle("Simulated Tracks")
    offLF.GetXaxis().SetTitle(xTitle )

    if maxX:
        offLF.GetXaxis().SetRangeUser(minX,maxX)
        offBQ.GetXaxis().SetRangeUser(minX,maxX)
        hltLF.GetXaxis().SetRangeUser(minX,maxX)
        hltBQ.GetXaxis().SetRangeUser(minX,maxX)


    LFRatio = makeRatio(num = hltLF.Clone(),  den = offLF.Clone())
    BQRatio = makeRatio(num = hltBQ.Clone(),  den = offBQ.Clone())

    xpos = 0.2
    ypos = 0.07
    xwidth = 0.7
    ywidth = 0.1

    leg = ROOT.TLegend(xpos, ypos, xpos+xwidth, ypos+ywidth)
    leg.SetNColumns(2)
    leg.AddEntry(offBQ,"Offline tracks b-quark jets","L")
    leg.AddEntry(offLF,"Offline tracks light-flavor jets","L")
    leg.AddEntry(hltBQ,"HLT tracks b-quark jets"    ,"PEL")
    leg.AddEntry(hltLF,"HLT tracks light-flavor jets" ,"PEL")

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
    #hltLF.SetMarkerSize(0.75)
    #hltLF.SetMarkerStyle(21)
    hltLF.Draw("same pe")
    offBQ.Draw("hist same")
    #hltBQ.SetMarkerSize(0.75)
    #hltBQ.SetMarkerStyle(21)
    hltBQ.Draw("same pe")
    leg.Draw("same")






    cmsLines = getCMSText(xStart=0.2,yStart=0.85,subtext=o.cmsText)
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
    #ratio_axis.GetYaxis().SetTitle("PF to Calo")
    ratio_axis.GetYaxis().SetTitle("HLT to Offline")
    ratio_axis.GetXaxis().SetTitle(offLF.GetXaxis().GetTitle())
    ratio_axis.GetYaxis().SetNdivisions(507)
    rMin = 0
    rMax = 2


    if var in maxDict.keys():
        LFRatio.GetXaxis().SetRangeUser(LFRatio.GetXaxis().GetXmin(),maxDict[var] )

    ratio_axis.GetYaxis().SetRangeUser(rMin, rMax)
    LFRatio.GetYaxis().SetRangeUser(rMin, rMax)
    #LFRatio.GetYaxis().SetTitle("Calo to Offline")
    #LFRatio.GetYaxis().SetTitle("PF to Calo")
    LFRatio.GetYaxis().SetTitle("HLT to Offline")


    LFRatio.Draw("PE")
    LFRatio.Draw("PE same")
    oldSize = LFRatio.GetMarkerSize()
    LFRatio.SetMarkerSize(0)
    LFRatio.DrawCopy("same e0")
    LFRatio.SetMarkerSize(oldSize)
    LFRatio.Draw("PE same")


    BQRatio.Draw("PE same")
    BQRatio.Draw("PE same")
    oldSize = BQRatio.GetMarkerSize()
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
    canvas.SaveAs(o.outDir+"/"+varName+".pdf")
    canvas.SaveAs(o.outDir+"/"+varName+".png")
    #canvas.SaveAs(o.outDir+"/"+var+".eps")
    #canvas.SaveAs(o.outDir+"/"+var+".png")



#doVar("ip3d_sig_l",
#      xTitle = "ip3d significance",
#      #binning = [-20,-18,-16,-14,-12,-11,-10,-8,-6,-5,-4,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,4,5,6,8,10,11,12,14,16,18,20,22,24,28,32,36,40]
#      binning = [-100 , -90,-80 , -70  , -60 ,  -50 , -40 , -34 , -32 , -30 , -28 , -26 , -24 , -22 , -20 , -18 , -16 , -14 , -12 , -10 , -8 , -6 , -4 , -2 , 0 , 2 , 4 , 6 , 8 , 10 , 12 , 14 , 16 , 18 , 20 , 22 , 24 , 26 , 28 , 30 , 32 , 34 , 40 , 50 , 60 , 70 , 80, 90 , 100]
#      #binning = [-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,-5,0,5,10,15,20,30,40,50,60,70,80,90,100]
#      )

for v in ["tracks/ip3d_sig",
          "tracks/ip2d_sig",
          "CSVv2_l",
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

          "btags/trackPt",
          "btags/trackEta",
          "btags/trackPhi",
          "btags/trackNPixelHits",
          "btags/trackNTotalHits",


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

    doVarRatio(v,
          xTitle = v,
          #binning = [-20,-18,-16,-14,-12,-11,-10,-8,-6,-5,-4,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,4,5,6,8,10,11,12,14,16,18,20,22,24,28,32,36,40]
          binning = binning,
          #binning = [-100 , -90,-80 , -70  , -60 ,  -50 , -40 , -34 , -32 , -30 , -28 , -26 , -24 , -22 , -20 , -18 , -16 , -14 , -12 , -10 , -8 , -6 , -4 , -2 , 0 , 2 , 4 , 6 , 8 , 10 , 12 , 14 , 16 , 18 , 20 , 22 , 24 , 26 , 28 , 30 , 32 , 34 , 40 , 50 , 60 , 70 , 80, 90 , 100]
          #binning = [-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,-5,0,5,10,15,20,30,40,50,60,70,80,90,100]
          )




for v in [        "tracks/eta",
        "tracks/ip2d_err",
        "tracks/ip2d_err_l",
        "tracks/ip3d_err",
        "tracks/ip3d_err_l",
#        "neMult",
        "phi",
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
        #"jetNSelectedTracks",
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
                  #"ip2d",
          "tracks/Chi2",
                  ]:

    if o.doCaloJets:
        if v in [ "btags/chargedHadronMultiplicity",
                  "btags/chargedMultiplicity",
                  "btags/elecMultiplicity",
                  "btags/muonMultiplicity",
                  "btags/neutralHadronMultiplicity",
                  "btags/neutralMultiplicity",
                  "btags/photonMultiplicity",
                  "btags/totalMultiplicity",
                  ]:
            continue

    vName = v.split("/")[-1]
    if vName in rebinningDB:
        binning = rebinningDB[vName]
    else:
        binning = 2


    doVarRatio(v,
          xTitle = v,
          binning = binning,
          setLogy = 0,
          )




for v in [
        "tracks/HasInnerPixHit",
        "tracks/NPixelHits",
        "tracks/NTotalHits",
        "tracks/NStripHits",
        "btags/sv_nSVs",
        "tracks/nTracks",
        "btags_noV0/nTracks",
        "btags/nTracks",
        "btags/sv_NTracks",
        ]:

    doVarRatio(v,
          xTitle = v,
          binning = 1,
          setLogy = 0,
          )


for v in [
"btags/chargedEmEnergyFraction",
"btags/chargedHadronEnergyFraction",
"btags/elecEnergyFraction",
"btags/muonEnergyFraction",
"btags/neutralEmEnergyFraction",
"btags/neutralHadronEnergyFraction",
"btags/photonEnergyFraction",


          "tracks/IsFromV0",
          "tracks/IsFromSV",
#        "neutralHadronEnergyFraction",
#        "trackSumJetEtRatio",
        ]:
    doVarRatio(v,
          xTitle = v,
          binning = 1,
          setLogy = 0,
               minY = 0,
         )

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
    doVarRatio(v,
          xTitle = v,
          binning = 1,
          setLogy = 0,
          minX = 0,
          maxX = 15
          )



#doVar("trk_z0Sig_signed",
#      xTitle = "z_{0} Significance",
#      #binning = [-25,-20,-18,-14,-10,-8,-6,-5,-4,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,4,5,6,8,10,12,14,16,18,20,24,25]
#      binning = [-12,-10,-8,-6,-5,-4,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,4,5,6,8,10,12,15,20]
#      )
