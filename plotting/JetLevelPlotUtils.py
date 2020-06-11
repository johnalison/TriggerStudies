import ROOT
import math

import sys
sys.path.insert(0, '../../')


from   ROOTHelp.Utils         import do_variable_rebinning, makeCanvas
from   ROOTHelp.Plotting      import makeRatio, makeBayesRatio, makeBayesLikeRatio

def getLegend(entries,xStart,xWidth,yStart,yWidth,textSize=0.0):
    leg = ROOT.TLegend(xStart,yStart, (xStart+xWidth), (yStart+yWidth))
    leg.SetBorderSize(0)
    leg.SetTextFont(42)
    #leg.SetTextSize(0.0) #Nominal
    leg.SetTextSize(0.05)
    leg.SetFillStyle(0)

    for e in entries:
        leg.AddEntry(e[0],e[1],e[2])
    return leg
    #leg.Draw("same")


def getCMSText(xStart,yStart,subtext = "Work in Progress", lumiText="",xLumiStart=0.70,yLumiStart=0.95):

    yStartFirstLine = yStart
    yStartSecondLine = yStart - 0.047

    cmsScale=1.2
    textsize=0.045

    firstline = '#scale['+str(cmsScale)+']{#bf{CMS}}'
    additionaltext = ""
    if additionaltext == "Sim":
        firstline += " #it{Simulation}"
    elif additionaltext == "Supp":
        firstline += " #it{Supplementary}"

    cmsfistLine = ROOT.TLatex(xStart, yStartFirstLine, firstline)
    cmsfistLine.SetTextFont(42)
    cmsfistLine.SetTextSize(textsize)
    cmsfistLine.SetNDC()

    cmssecondline = ROOT.TLatex(xStart, yStartSecondLine, '#it{'+subtext+'}')
    cmssecondline.SetTextFont(42)
    cmssecondline.SetTextSize(textsize)
    cmssecondline.SetNDC()

    if lumiText:
        cmsLumi = ROOT.TLatex(xLumiStart, yLumiStart, lumiText)
        cmsLumi.SetTextFont(42)
        cmsLumi.SetTextSize(0.035)
        cmsLumi.SetNDC()

        return cmsfistLine, cmssecondline, cmsLumi

    return cmsfistLine, cmssecondline


def getText(text,xStart,yStart,color=ROOT.kBlack,size=0.045):

    yStartFirstLine = yStart
    yStartSecondLine = yStart - 0.047


    cmsScale=1.2

    firstline = '#scale['+str(cmsScale)+']{'+text+'}'

    cmsfistLine = ROOT.TLatex(xStart, yStartFirstLine, firstline)
    cmsfistLine.SetTextFont(42)
    cmsfistLine.SetTextSize(size)
    cmsfistLine.SetTextColor(color)
    cmsfistLine.SetNDC()


    return cmsfistLine




def getHist(inFile,dir,var,binning,norm=False,color=ROOT.kBlack):

    hist = inFile.Get(dir+"/"+var).Clone()
    if type(binning ) == type(list()):
        hist  = do_variable_rebinning(hist,binning)
    else:
        hist.Rebin(binning)

    if norm:
       hist.Scale(1./hist.Integral())

    hist.SetLineColor(color)
    hist.SetMarkerColor(color)
    hist.Sumw2()

    return hist

def drawText(text,textsize,xStart,yStart):
    if type(text) == type(list()):
        otherLabel = []
        yStartCurrent = yStart
        for ot in text:
            otherLabel.append(ROOT.TLatex(xStart, yStartCurrent, '#scale['+str(0.7)+']{'+ot+'}'))
            otherLabel[-1].SetTextSize(textsize)
            otherLabel[-1].Draw("same")
            yStartCurrent = yStart - 0.05

    elif text:
        otherLabel = ROOT.TLatex(xStart, yStart, '#scale['+str(0.7)+']{'+text+'}')
        otherLabel.Draw("same")
    return otherLabel



def makeEffFromFiles(var,dirs,inFileNum,inFileDen,binning):
    #offLF = getHist(inFile,"caloJets_matchedL",          var,binning,ROOT.kBlack)
    numHist = getHist(inFileNum,dirs,          var,binning,color=ROOT.kBlue)
    denHist = getHist(inFileDen,dirs,          var,binning,color=ROOT.kBlue)


    #effHist = makeBayesRatio(num = numHist.Clone(),  den = denHist.Clone())
    #effHist = makeBayesLikeRatio(num = numHist.Clone(),  den = denHist.Clone())
    effHist = makeRatio(num = numHist.Clone(),  den = denHist.Clone())
    #print numHist.GetXaxis().GetTitle()
    effHist.GetXaxis().SetTitle(numHist.GetXaxis().GetTitle())
    return effHist


def makeEff(var,dirs,inFile,binning,bayesRatio=1,histForXBarycenterCalc=None):
    #offLF = getHist(inFile,"caloJets_matchedL",          var,binning,ROOT.kBlack)
    if not isinstance(var,list) and isinstance(dirs,list):
        numHist = getHist(inFile,dirs[0],          var,binning,color=ROOT.kBlue)
        denHist = getHist(inFile,dirs[1],          var,binning,color=ROOT.kBlue)
    elif isinstance(var,list) and not isinstance(dirs,list):
        numHist = getHist(inFile,dirs,          var[0],binning,color=ROOT.kBlue)
        denHist = getHist(inFile,dirs,          var[1],binning,color=ROOT.kBlue)
    else:
        print "ERROR",var,dirs


    print "max num is ",numHist.GetXaxis().GetXmax()
    print "max den is ",denHist.GetXaxis().GetXmax()
    if bayesRatio:
        effHist = makeBayesRatio(num = numHist.Clone(),  den = denHist.Clone(),histForXBarycenterCalc=histForXBarycenterCalc)
    else:
        effHist = makeBayesLikeRatio(num = numHist.Clone(),  den = denHist.Clone())

    print "max effHist is ",effHist.GetXaxis().GetXmax()
    #print numHist.GetXaxis().GetTitle()
    effHist.GetXaxis().SetTitle(numHist.GetXaxis().GetTitle())
    return effHist




def drawComp(name,inputHists,yTitle,xTitle,outDir,otherText="",setLogy=1,yMax= 1,leg="",xMax=1,xMin = -0.2,yLeg=0.76,xLeg=0.2,xStartOther=0.5, yStartOther=0.9, doFit = False,cmsText="Preliminary", lumiText="",xLumiStart=0.7):




    canvas = makeCanvas(name, name)#, width=800, height=600)

    if isinstance(inputHists[0][0],ROOT.TGraphAsymmErrors):
        ratio_axis = inputHists[0][0].GetHistogram()
    else:
        ratio_axis = inputHists[0][0].Clone()
    ratio_axis.GetYaxis().SetTitle(yTitle)
    ratio_axis.GetXaxis().SetTitle(xTitle)
    ratio_axis.GetYaxis().SetNdivisions(507)
    yMin = 0

    ratio_axis.GetYaxis().SetRangeUser(yMin, yMax)
    print xMin,"to",xMax
    ratio_axis.GetXaxis().SetRangeUser(xMin, xMax)
    ratio_axis.Draw("axis")



    for hInfoIndx, hInfo  in enumerate(inputHists):
        #hInfo[0].GetYaxis().SetRangeUser(yMin, yMax)
        #hInfo[0].GetXaxis().SetRangeUser(xMin, xMax)
        hInfo[0].SetLineColor  (hInfo[2])
        hInfo[0].SetMarkerColor(hInfo[2])
        hInfo[0].SetMarkerSize(0.5)
        if len(hInfo) > 3:
            hInfo[0].SetMarkerStyle(hInfo[3])
            hInfo[0].SetFillStyle(hInfo[3])
        #hInfo[0].SetMarkerStyle(0)
        if hInfoIndx:
            if isinstance(inputHists[0][0],ROOT.TGraphAsymmErrors):
                hInfo[0].Draw("PE same")
            else:
                hInfo[0].Draw("same")
        else:
            if isinstance(inputHists[0][0],ROOT.TGraphAsymmErrors):
                hInfo[0].Draw("PE")


                if doFit:
                    xAve = (ratio_axis.GetXaxis().GetXmin() + ratio_axis.GetXaxis().GetXmax()) /2
                    xmin = max(30,ratio_axis.GetXaxis().GetXmin())
                    print "Setting Range",xmin, ratio_axis.GetXaxis().GetXmax()
                    sigmoid = ROOT.TF1("func", "(1.0/(1+ TMath::Exp(-[0]*(x-[1]))))", xmin, ratio_axis.GetXaxis().GetXmax())
                    sigmoid.SetParameters(0.01, xAve)
                    inputHists[0][0].Fit(sigmoid)
                    sigmoid.Draw("same")

                    print hInfo[0].GetName(),":",
                    print sigmoid.GetParameter(0),
                    print sigmoid.GetParameter(1)

                    textFits = []
                    for i in range(2):
                        yStartFit = 0.3-0.04*i
                        textFits.append(ROOT.TLatex(0.7, yStartFit, "p"+str(i)+" = "+str(round(sigmoid.GetParameter(i),3))))
                        textFits[-1].SetTextFont(42)
                        textFits[-1].SetTextSize(0.04)
                        textFits[-1].SetNDC()
                        textFits[-1].Draw("same")



            else:
                hInfo[0].Draw("same")

                if doFit:
                    xAve = (ratio_axis.GetXaxis().GetXmin() + ratio_axis.GetXaxis().GetXmax()) /2
                    xmin = max(30,ratio_axis.GetXaxis().GetXmin())
                    print "Setting Range",xmin, ratio_axis.GetXaxis().GetXmax()
                    sigmoid = ROOT.TF1("func", "(1.0/(1+ TMath::Exp(-[0]*(x-[1]))))", xmin, ratio_axis.GetXaxis().GetXmax())
                    sigmoid.SetParameters(0.01, xAve)
                    inputHists[0][0].Fit(sigmoid,"q")
                    sigmoid.SetLineStyle(ROOT.kDashed)
                    sigmoid.SetLineColor(ROOT.kRed)
                    sigmoid.Draw("same")

                    print hInfo[0].GetName(),":",
                    print sigmoid.GetParameter(0),
                    print sigmoid.GetParameter(1)

                    textFits = []
                    for i in range(2):
                        yStartFit = 0.3-0.04*i
                        textFits.append(ROOT.TLatex(0.7, yStartFit, "p"+str(i)+" = "+str(round(sigmoid.GetParameter(i),3))))
                        textFits[-1].SetTextFont(42)
                        textFits[-1].SetTextSize(0.04)
                        textFits[-1].SetNDC()
                        textFits[-1].Draw("same")




    #effHistMC.Draw("PE same")


    #
    #  legend
    #
    if not leg:
        legInfo = []
        yWidth = 0
        for hInfo in inputHists:
            yWidth += 0.06
            print hInfo[1]
            legInfo.append((hInfo[0],"#scale[0.7]]{"+hInfo[1]+"}","LP"))
        #leg = getLegend([(effHist,"#scale[0.7]]{Data}","PE"),(effHistMC,"#scale[0.7]{t#bar{t} MC}","PE")],  xStart=0.2, xWidth=0.3, yStart=0.6, yWidth=0.16)
        leg = getLegend(legInfo,  xStart=xLeg, xWidth=0.3, yStart=yLeg-yWidth, yWidth=yWidth)
        leg.Draw("same")

    if leg == "special":
        hForLeg_Data = inputHists[0][0].Clone("leg_Data")
        hForLeg_Data.SetLineColor(ROOT.kBlack)
        hForLeg_Data.SetMarkerColor(ROOT.kBlack)
        legInfo = []
        legInfo.append((hForLeg_Data,"#scale[0.7]]{Data}","LP"))
        legData = getLegend(legInfo,  xStart=0.175, xWidth=0.3, yStart=0.76-0.08, yWidth=0.08)
        legData.Draw("same")

        hForLeg_MC = inputHists[0][0].Clone("leg_MC")
        hForLeg_MC.SetLineColor(ROOT.kBlack)
        hForLeg_MC.SetMarkerColor(ROOT.kBlack)
        hForLeg_MC.SetMarkerStyle(24)
        legInfo = []
        legInfo.append((hForLeg_MC,"#scale[0.7]]{MC  }","LP"))
        legMC = getLegend(legInfo,  xStart=0.3, xWidth=0.3, yStart=0.76-0.08, yWidth=0.08)
        legMC.Draw("same")

        textLoose = ROOT.TLatex(0.2, 0.77, "Loose")
        textLoose.SetTextFont(42)
        textLoose.SetTextSize(0.04)
        textLoose.SetTextColor(ROOT.kBlue)
        textLoose.SetNDC()
        textLoose.Draw("same")

        textMedium = ROOT.TLatex(0.3, 0.77, "Medium")
        textMedium.SetTextFont(42)
        textMedium.SetTextSize(0.04)
        textMedium.SetTextColor(ROOT.kGreen+1)
        textMedium.SetNDC()
        textMedium.Draw("same")

        textTight = ROOT.TLatex(0.43, 0.77, "Tight")
        textTight.SetTextFont(42)
        textTight.SetTextSize(0.04)
        textTight.SetTextColor(ROOT.kRed)
        textTight.SetNDC()
        textTight.Draw("same")


    #
    #  CMS Text
    #
    cmsLines = getCMSText(xStart=0.2,yStart=0.875,subtext=cmsText,lumiText=lumiText,xLumiStart=xLumiStart,yLumiStart=0.96)
    for cmsl in cmsLines:
        cmsl.Draw("same")

    if otherText:
        labels = drawText(otherText,textsize=0.05,xStart=xStartOther,yStart=yStartOther)


    canvas.SaveAs(outDir+"/"+name+".png")
    canvas.SaveAs(outDir+"/"+name+".pdf")




def drawCompRatioGraphs(name,inputHists,ratioHistBinning,yTitle,xTitle,outDir,otherText="",setLogy=1,yMax= 1,yMin = 0,leg="",xMax=1,xMin = -0.2,yLeg=0.76,xLeg=0.2,xStartOther=0.5, yStartOther=0.9, doFit = False,cmsText="Preliminary", lumiText="",rTitle="Ratio",histForXBarycenterCalc=None):

    upperHist = inputHists[0][0].GetHistogram()
    upperHist.GetYaxis().SetTitle(yTitle)
    upperHist.GetXaxis().SetTitle(xTitle)
    upperHist.GetYaxis().SetNdivisions(507)


    upperHist.GetYaxis().SetRangeUser(yMin, yMax)
    upperHist.GetXaxis().SetRangeUser(xMin, xMax)



    canvas = makeCanvas(name, name, width=600, height=600)
    split=0.3
    top_pad    = ROOT.TPad("pad1", "The pad 80% of the height",0,split,1,1,0)
    bottom_pad = ROOT.TPad("pad2", "The pad 20% of the height",0,0,1,split,0)
    top_pad.Draw()
    bottom_pad.Draw()

    axissep = 0.035
    top_pad.cd()
    #top_pad.SetLogy(setLogy)
    top_pad.SetTopMargin(canvas.GetTopMargin()*1.0/(1.0-split))
    top_pad.SetBottomMargin(0.5*axissep)
    top_pad.SetRightMargin(canvas.GetRightMargin())
    top_pad.SetLeftMargin(canvas.GetLeftMargin());
    top_pad.SetFillStyle(0) # transparent
    top_pad.SetBorderSize(0)

    upperHist.Draw("axis")



    for hInfoIndx, hInfo  in enumerate(inputHists):

        hInfo[0].SetLineColor  (hInfo[2])
        hInfo[0].SetMarkerColor(hInfo[2])
        if len(hInfo) > 3:
            hInfo[0].SetMarkerStyle(hInfo[3])
            hInfo[0].SetFillStyle(hInfo[3])

        if hInfoIndx:
            hInfo[0].Draw("PE same")

        else:
            hInfo[0].Draw("PE same")

    numHist = ratioHistBinning.Clone()
    denHist = ratioHistBinning.Clone()

    for iBin in range(inputHists[0][0].GetN()):
        xValue = ROOT.Double(0)
        theEff = ROOT.Double(0)
        theEffErr = inputHists[0][0].GetErrorY(iBin)
        inputHists[0][0].GetPoint(iBin,xValue,theEff)
        #print iBin, xValue, theEff
        numHist.SetBinContent(numHist.FindBin(xValue), theEff)
        numHist.SetBinError(numHist.FindBin(xValue), theEffErr)


    for iBin in range(inputHists[1][0].GetN()):
        xValue = ROOT.Double(0)
        theEff = ROOT.Double(0)
        theEffErr = inputHists[1][0].GetErrorY(iBin)
        inputHists[1][0].GetPoint(iBin,xValue,theEff)
        #print iBin, xValue, theEff
        denHist.SetBinContent(denHist.FindBin(xValue), theEff)
        denHist.SetBinError(denHist.FindBin(xValue), theEffErr)

    histRatio = makeBayesLikeRatio(num = numHist,   den = denHist, histForXBarycenterCalc=histForXBarycenterCalc)

    #
    #  legend
    #
    if not leg:
        legInfo = []
        yWidth = 0
        for hInfo in inputHists:
            yWidth += 0.06
            print hInfo[1]
            legInfo.append((hInfo[0],"#scale[0.7]]{"+hInfo[1]+"}","LP"))
        #leg = getLegend([(effHist,"#scale[0.7]]{Data}","PE"),(effHistMC,"#scale[0.7]{t#bar{t} MC}","PE")],  xStart=0.2, xWidth=0.3, yStart=0.6, yWidth=0.16)
        leg = getLegend(legInfo,  xStart=xLeg, xWidth=0.3, yStart=yLeg-yWidth, yWidth=yWidth)
        leg.Draw("same")


    #
    #  CMS Text
    #
    cmsLines = getCMSText(xStart=0.2,yStart=0.86,subtext=cmsText,lumiText=lumiText,xLumiStart=0.7,yLumiStart=0.94)
    for cmsl in cmsLines:
        cmsl.Draw("same")


    #
    #  Other Text
    #
    if otherText:
        drawText(otherText,textsize=0.05,xStart=xStartOther,yStart=yStartCurrent)



    bottom_pad.cd()
    bottom_pad.SetTopMargin(2*axissep)
    bottom_pad.SetBottomMargin(canvas.GetBottomMargin()*1.0/split)
    bottom_pad.SetRightMargin(canvas.GetRightMargin())
    bottom_pad.SetLeftMargin(canvas.GetLeftMargin());
    bottom_pad.SetFillStyle(0) # transparent
    bottom_pad.SetBorderSize(0)

    ratio_axis = inputHists[0][0].GetHistogram().Clone()
    ratio_axis.GetXaxis().SetRangeUser(xMin, xMax)
    ratio_axis.GetYaxis().SetTitle("Data/MC")
    ratio_axis.GetXaxis().SetTitle(hInfo[0].GetXaxis().GetTitle())
    ratio_axis.GetYaxis().SetNdivisions(507)
    rMin = 0.5
    rMax = 1.5
    ratio_axis.GetYaxis().SetRangeUser(rMin, rMax)
    histRatio.GetYaxis().SetRangeUser(rMin, rMax)
    histRatio.GetYaxis().SetTitle(rTitle)

    ratio_axis.Draw("axis")
    if isinstance(histRatio, ROOT.TGraphAsymmErrors):
        histRatio.Draw("PE")
    else:
        histRatio.Draw("PE same")
        histRatio.Draw("PE same")
        oldSize = histRatio.GetMarkerSize()
        histRatio.SetMarkerSize(0)
        histRatio.DrawCopy("same e0")
        # histRatio.SetMarkerSize(oldSize)
        histRatio.SetMarkerSize(0.5)
        histRatio.Draw("PE same")

    line = ROOT.TLine()
    line.DrawLine(hInfo[0].GetXaxis().GetXmin(), 1.0, hInfo[0].GetXaxis().GetXmax(), 1.0)


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

        for pName in prims:

            if pName in procedHist: continue
            procedHist.append(pName)

            h = pad.GetPrimitive(pName)
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




    canvas.SaveAs(outDir+"/"+name+".pdf")
    canvas.SaveAs(outDir+"/"+name+".png")



def drawCompRatio(outName,histInfo,yTitle,xTitle,rTitle,outDir,setLogy=1,yMax=None,leg="",cmsText="", lumiText=""):
    hist1 = histInfo[0][0].Clone()


    hist2 = histInfo[1][0].Clone()
    hist2.SetFillColor(ROOT.kYellow)

    if yMax:
        maxY = yMax
    else:
        maxY = max(hist1.GetMaximum(),hist2.GetMaximum())

    if setLogy:
        hist2.SetMaximum(4e0*maxY)
        hist2.SetMinimum(1e-6)
        hist1.SetMaximum(4e0*maxY)
        hist1.SetMinimum(1e-6)
    else:
        hist2.SetMaximum(1.2*maxY)
        hist1.SetMaximum(1.2*maxY)

    hist2.GetYaxis().SetTitle(yTitle)
    hist2.GetXaxis().SetTitle(xTitle)

    hist1.GetYaxis().SetTitle(yTitle)
    hist1.GetXaxis().SetTitle(xTitle)


    histRatio = makeRatio(num = hist1.Clone(),  den = hist2.Clone())

    xpos = 0.5
    ypos = 0.79
    xwidth = 0.3
    ywidth = 0.1

    leg = ROOT.TLegend(xpos, ypos, xpos+xwidth, ypos+ywidth)
    leg.AddEntry(hist1,histInfo[0][1],"PEL")
    leg.AddEntry(hist2,histInfo[1][1] ,"F")
    #leg.AddEntry(offLF,"Offline tracks light-flavor jets","L")
    #leg.AddEntry(hltLF,"HLT tracks light-flavor jets"    ,"PEL")

    canvas = makeCanvas(outName, outName, width=600, height=600)
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


    hist2.Draw("hist")
    #hltLF.SetMarkerSize(0.75)
    hltLF.SetMarkerSize(0.5)
    #hltLF.SetMarkerStyle(21)
    hist1.Draw("same pe")
    #offBQ.Draw("hist same")
    hltBQ.SetMarkerSize(0.5)
    #hltBQ.SetMarkerStyle(21)
    #hltBQ.Draw("same pe")
    leg.Draw("same")

    cmsLines = getCMSText(xStart=0.225,yStart=0.85,subtext=cmsText,lumiText=lumiText)
    for cmsl in cmsLines:
        cmsl.Draw("same")


    bottom_pad.cd()
    bottom_pad.SetTopMargin(2*axissep)
    bottom_pad.SetBottomMargin(canvas.GetBottomMargin()*1.0/split)
    bottom_pad.SetRightMargin(canvas.GetRightMargin())
    bottom_pad.SetLeftMargin(canvas.GetLeftMargin());
    bottom_pad.SetFillStyle(0) # transparent
    bottom_pad.SetBorderSize(0)
    ratio_axis = hist1.Clone()
    #ratio_axis.GetYaxis().SetTitle("PF to Calo")
    ratio_axis.GetYaxis().SetTitle("Ratio")
    ratio_axis.GetXaxis().SetTitle(hist1.GetXaxis().GetTitle())
    ratio_axis.GetYaxis().SetNdivisions(507)
    rMin = 0
    rMax = 2
    ratio_axis.GetYaxis().SetRangeUser(rMin, rMax)
    histRatio.GetYaxis().SetRangeUser(rMin, rMax)
    histRatio.GetYaxis().SetTitle(rTitle)


    histRatio.Draw("PE")
    histRatio.Draw("PE same")
    oldSize = histRatio.GetMarkerSize()
    histRatio.SetMarkerSize(0)
    histRatio.DrawCopy("same e0")
    # histRatio.SetMarkerSize(oldSize)
    histRatio.SetMarkerSize(0.5)
    histRatio.Draw("PE same")

    line = ROOT.TLine()
    line.DrawLine(hist1.GetXaxis().GetXmin(), 1.0, hist1.GetXaxis().GetXmax(), 1.0)

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






    canvas.SaveAs(outDir+"/"+outName+".pdf")
    canvas.SaveAs(outDir+"/"+outName+".png")


def plotRatio(var, dir, inFileData1, name1, inFileData2, name2, xTitle, outDir, rTitle="Ratio",setLogy=0,binning=1, cmsText="",lumiText=""):

    hist_Data1     = getHist(inFileData1,  dir,  var,binning=binning,norm=1)
    hist_Data2     = getHist(inFileData2,  dir,  var,binning=binning,norm=1)

    drawCompRatio(dir+"_"+var,[(hist_Data1,name1),(hist_Data2,name2)]
                  ,yTitle="Normalized",xTitle=xTitle,rTitle=rTitle,outDir=outDir,setLogy=setLogy,cmsText=cmsText,lumiText=lumiText)

def drawStackCompRatio(outName,dataInfo,MCInfo,yTitle,xTitle,rTitle,outDir,min=1,setLogy=1,x_min=None,x_max=None,cmsText="", lumiText=""):
    histData = dataInfo[0].Clone()


    stacksum=MCInfo[0][0].Clone("tmp")
    stacksum.Reset()
    for h in MCInfo:
        stacksum.Add(h[0])

    stacksum.Integral()
    scaleFactor = histData.Integral()/stacksum.Integral()



    stack = ROOT.THStack("TestStack", outName)
    for hMC in MCInfo:
        hMC[0].SetFillColor(hMC[2])
        hMC[0].Scale(scaleFactor)
        stack.Add(hMC[0], 'sames')

    stacksum.Scale(scaleFactor)

#    hist2 = histInfo[1][0].Clone()
#    hist2.SetFillColor(ROOT.kYellow)

    maxY = max(histData.GetMaximum(),stack.GetMaximum())

    if setLogy:
        histData.SetMaximum(4e0*maxY)
        histData.SetMinimum(min)
        stack.SetMaximum(4e0*maxY)
        stack.SetMinimum(min)
    else:
        stack.SetMaximum(1.4*maxY)
        histData.SetMaximum(1.4*maxY)


    histData.GetYaxis().SetTitle(yTitle)
    histData.GetXaxis().SetTitle(xTitle)




    xpos = 0.5
    ypos = 0.69
    xwidth = 0.3
    ywidth = 0.05*(len(MCInfo)+1)

    leg = ROOT.TLegend(xpos, ypos, xpos+xwidth, ypos+ywidth)
    leg.AddEntry(histData,dataInfo[1],"PEL")
    for hMC in MCInfo:
        leg.AddEntry(hMC[0],hMC[1] ,"F")
    #leg.AddEntry(offLF,"Offline tracks light-flavor jets","L")
    #leg.AddEntry(hltLF,"HLT tracks light-flavor jets"    ,"PEL")

    canvas = makeCanvas(outName, outName, width=600, height=600)
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


    stack.Draw()
    if x_max is not None and x_min is not None:
        stack.GetXaxis().SetRangeUser(x_min,x_max)
        histData.GetXaxis().SetRangeUser(x_min,x_max)

    stack.GetYaxis().SetTitle(yTitle)
    stack.GetXaxis().SetTitle(xTitle)
    stack.Draw("hist")


    #hltLF.SetMarkerSize(0.75)
    hltLF.SetMarkerSize(0.5)
    #hltLF.SetMarkerStyle(21)
    histData.Draw("same pe")
    #offBQ.Draw("hist same")
    hltBQ.SetMarkerSize(0.5)
    #hltBQ.SetMarkerStyle(21)
    #hltBQ.Draw("same pe")
    leg.Draw("same")

    histRatio = makeRatio(num = histData.Clone(),  den = stacksum.Clone())

    cmsLines = getCMSText(xStart=0.225,yStart=0.85,subtext=cmsText,lumiText=lumiText)
    for cmsl in cmsLines:
        cmsl.Draw("same")



    bottom_pad.cd()
    bottom_pad.SetTopMargin(2*axissep)
    bottom_pad.SetBottomMargin(canvas.GetBottomMargin()*1.0/split)
    bottom_pad.SetRightMargin(canvas.GetRightMargin())
    bottom_pad.SetLeftMargin(canvas.GetLeftMargin());
    bottom_pad.SetFillStyle(0) # transparent
    bottom_pad.SetBorderSize(0)
    ratio_axis = histData.Clone()
    #ratio_axis.GetYaxis().SetTitle("PF to Calo")
    ratio_axis.GetYaxis().SetTitle("Ratio")
    ratio_axis.GetXaxis().SetTitle(histData.GetXaxis().GetTitle())
    ratio_axis.GetYaxis().SetNdivisions(507)
    rMin = 0
    rMax = 2
    ratio_axis.GetYaxis().SetRangeUser(rMin, rMax)
    histRatio.GetYaxis().SetRangeUser(rMin, rMax)
    histRatio.GetYaxis().SetTitle(rTitle)


    histRatio.Draw("PE")
    histRatio.Draw("PE same")
    oldSize = histRatio.GetMarkerSize()
    histRatio.SetMarkerSize(0)
    histRatio.DrawCopy("same e0")
    # histRatio.SetMarkerSize(oldSize)
    histRatio.SetMarkerSize(0.5)
    histRatio.Draw("PE same")

    line = ROOT.TLine()
    if x_max is not None and x_min is not None:
        line.DrawLine(x_min, 1.0, x_max, 1.0)
    else:
        line.DrawLine(histData.GetXaxis().GetXmin(), 1.0, histData.GetXaxis().GetXmax(), 1.0)

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






    canvas.SaveAs(outDir+"/"+outName+".pdf")
    canvas.SaveAs(outDir+"/"+outName+".png")



def makeStack(name,var,dir,binning,xTitle,rTitle,logy,inFileData,inFileMC,outDir,min=1,x_min=None,x_max=None,cmsText="",lumiText=""):
    hist_Data    = getHist(inFileData, dir.replace("_X_","").replace("_X",""),      var, binning=binning,norm=0)
    hist_B_MC    = getHist(inFileMC,   dir.replace("X","B"),      var, binning=binning,norm=0)
    hist_C_MC    = getHist(inFileMC,   dir.replace("X","C"),      var, binning=binning,norm=0)
    hist_L_MC    = getHist(inFileMC,   dir.replace("X","L"),      var, binning=binning,norm=0)


    drawStackCompRatio(name,
                       (hist_Data,"Data"),
                       [(hist_L_MC,"Light Flavor",ROOT.kAzure-9),
                        (hist_C_MC,"Charm Jets",  ROOT.kGreen+1),
                        (hist_B_MC,"B Jets",      ROOT.kYellow)]
                       ,yTitle="Normalized",xTitle=xTitle,rTitle=rTitle,min=min,setLogy=logy,outDir=outDir,x_min=x_min,x_max=x_max,cmsText=cmsText,lumiText=lumiText)


def getInverseTurnOn(name,var,dir,inFile,binning):
    hist = getHist(inFile,dir,var,binning)

    histEff = hist.Clone(name)
    histEff.Reset()

    totalIntegral = hist.Integral()
    #print totalIntegral ,"vs",hist.Integral(-1,hist.GetNbinsX()+1)

    nBinsX = hist.GetNbinsX()
    #print hist.Integral(),hist.Integral(-1,nBinsX+1)

    for iBin in range(nBinsX+1):
        numberFailed = hist.Integral(-1,iBin)

        fractionFailed = (totalIntegral - numberFailed)/totalIntegral
        error = math.sqrt(fractionFailed*(1-fractionFailed)/totalIntegral)

        histEff.SetBinContent(iBin, fractionFailed)
        histEff.SetBinError(iBin, error)

    return histEff


def makeInverseTurnOn(name,var,dir,inFile,binning, otherText, outDir,cmsText="", lumiText=""):


    histTight  = getInverseTurnOn(name,var,dir.replace("WORKINGPOINT","Tight"), inFile,binning)
    histTight.SetMarkerColor(ROOT.kRed)
    histTight.SetLineColor(ROOT.kRed)

    histMedium = getInverseTurnOn(name,var,dir.replace("WORKINGPOINT","Medium"),inFile,binning)
    histMedium.SetMarkerColor(ROOT.kGreen)
    histMedium.SetLineColor(ROOT.kGreen)

    histLoose  = getInverseTurnOn(name,var,dir.replace("WORKINGPOINT","Loose"), inFile,binning)
    histLoose.SetMarkerColor(ROOT.kBlue)
    histLoose.SetLineColor(ROOT.kBlue)

    #hist = getHist(inFile,dir,var,binning)

    histLoose.GetXaxis().SetTitle("Online CSV Cut Value")
    histLoose.GetYaxis().SetTitle("Relative Efficiency")
    histLoose.GetXaxis().SetRangeUser(0,1)
    histLoose.GetYaxis().SetRangeUser(0,1.2)


    can = ROOT.TCanvas(name, name,600,500)#x, 700, 500)
    can.cd()

    histLoose .Draw()

    histMedium.Draw("same")
    histTight .Draw("same")
    histLoose .Draw("axis, same")

    #
    #  CMS Text
    #
    cmsLines = getCMSText(xStart=0.2,yStart=0.875,subtext=cmsText,lumiText=lumiText,xLumiStart=0.7,yLumiStart=0.96)
    for cmsl in cmsLines:
        cmsl.Draw("same")




    xpos = 0.2
    ypos = 0.3
    xwidth = 0.3
    ywidth = 0.2

    leg = ROOT.TLegend(xpos, ypos, xpos+xwidth, ypos+ywidth)
    leg.AddEntry(histLoose, "wrt Offline Loose","PEL")
    leg.AddEntry(histMedium,"wrt Offline Medium","PEL")
    leg.AddEntry(histTight, "wrt Offline Tight","PEL")
    #leg.AddEntry(,histInfo[1][1] ,"F")

    leg.Draw("same")

    if otherText:

        xStartOther=0.4
        yStartOther=1.1
        textsize=0.045
        otherLabel = ROOT.TLatex(xStartOther, yStartOther, '#scale['+str(0.7)+']{'+otherText+'}')

        otherLabel.Draw("same")



    can.SaveAs(outDir+"/"+name+".pdf")
    can.SaveAs(outDir+"/"+name+".png")




def makeInverseTurnOnAll(name,var,dir,inFile1,name1,inFile2,name2,binning, outDir, otherText="",  wps=["Loose","Medium","Tight"],colors=[ROOT.kRed,ROOT.kOrange+1,ROOT.kBlue],cmsText="", lumiText="",wpLine=None,wpTextY=1.025):

    histFile1 = []
    histFile2 = []

    for i, thisWP in enumerate(wps):
        histFile1.append(getInverseTurnOn(name,var,dir.replace("WORKINGPOINT",thisWP), inFile1,binning))
        histFile1[-1].SetMarkerColor(colors[i])
        histFile1[-1].SetLineColor(colors[i])

        histFile2.append(getInverseTurnOn(name,var,dir.replace("WORKINGPOINT",thisWP), inFile2,binning))
        histFile2[-1].SetMarkerColor(colors[i])
        histFile2[-1].SetLineColor(colors[i])
        histFile2[-1].SetMarkerStyle(24)

    #hist = getHist(inFile,dir,var,binning)

    histFile1[-1].GetXaxis().SetTitle("Online "+var.replace("v2_l","").replace("_l","")+" Cut Value")
    histFile1[-1].GetYaxis().SetTitle("Efficiency Relative to Offline Working Point")
    histFile1[-1].GetXaxis().SetRangeUser(0,1)
    histFile1[-1].GetYaxis().SetRangeUser(0,1.2)



    xpos = 0.18
    ypos = 0.2
    xwidth = 0.3
    ywidth = 0.2


    leg  = ROOT.TLegend(xpos, ypos, xpos+xwidth, ypos+ywidth)
    leg.SetTextSize(0.03)
    leg2 = ROOT.TLegend(xpos+0.35, ypos, xpos+xwidth+0.3, ypos+ywidth)
    leg2.SetTextSize(0.03)

    can = ROOT.TCanvas(name, name,600,500)#x, 700, 500)
    can.cd()
    histFile1[-1] .Draw()

    for i, thisHist in enumerate(histFile2):
        thisHist .Draw("same")
        leg2.AddEntry(thisHist, "wrt Offline "+wps[i]+" ("+name2+")  ","PE")


    for i, thisHist in enumerate(histFile1):
        thisHist .Draw("same")
        leg.AddEntry(thisHist, "wrt Offline "+wps[i]+" ("+name1+")", "PE")



    histFile1[-1] .Draw("axis, same")

    #
    #  CMS Text
    #
    cmsLines = getCMSText(xStart=0.2,yStart=0.875,subtext=cmsText,lumiText=lumiText,xLumiStart=0.7,yLumiStart=0.96)
    for cmsl in cmsLines:
        cmsl.Draw("same")

    #leg.AddEntry(histMedium,"wrt Offline Medium (Data)","P")
    #leg.AddEntry(histTight, "wrt Offline Tight (Data)", "P")

    #leg2.AddEntry(histMedium2,"wrt Offline Medium (MC)  ","P")
    #leg2.AddEntry(histTight2, "wrt Offline Tight (MC)  ","P")

    #leg.AddEntry(,histInfo[1][1] ,"F")


    if wpLine:
        xValue = wpLine
        yMin = 0.6
        yMax = 1.0
        opLine = ROOT.TLine(xValue,yMin,xValue,yMax)
        opLine.SetLineWidth(3)
        opLine.SetLineStyle(ROOT.kDashed)
        opLine.Draw("same")

        wpText="Example working point"
        textsize=0.05
        wpLabel = ROOT.TLatex(xValue-0.12, wpTextY, '#scale['+str(0.7)+']{'+wpText+'}')
        wpLabel.SetTextSize(textsize)
        wpLabel.Draw("same")




    leg .Draw("same")
    leg2.Draw("same")

    if otherText:

        xStartOther=0.4
        yStartOther=1.1
        textsize=0.05
        otherLabel = ROOT.TLatex(xStartOther, yStartOther, '#scale['+str(0.7)+']{'+otherText+'}')

        otherLabel.SetTextSize(textsize)

        otherLabel.Draw("same")





    can.SaveAs(outDir+"/"+name+".pdf")
    can.SaveAs(outDir+"/"+name+".png")


def make2DComp(name,inFile,dir,var,xTitle,yTitle,outDir):
    hist2D = getHist(inFile,dir,var,binning=1,norm=0)

    hist2D.GetXaxis().SetRangeUser(-0.2,1)
    hist2D.GetYaxis().SetRangeUser(-0.2,1)
    hist2D.GetXaxis().SetTitle(xTitle)
    hist2D.GetYaxis().SetTitle(yTitle)
    can = ROOT.TCanvas(name,name)
    can.cd()
    can.SetLogz(True)
    hist2D.Draw("colz")


    corrFactor = round(hist2D.GetCorrelationFactor(),3)
    cmsfistLine = ROOT.TLatex(-0.175, 1.02, "Correlation Factor = "+str(corrFactor))
    cmsfistLine.SetTextFont(42)
    cmsfistLine.SetTextSize(0.025)
    #cmsfistLine.SetNDC()
    cmsfistLine.Draw("same")

    can.SaveAs(outDir+"/"+name+".pdf")
    can.SaveAs(outDir+"/"+name+".png")
