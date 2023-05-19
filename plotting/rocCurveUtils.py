import ROOT
import ctypes
from JetLevelPlotUtils import getCMSText, getText

def drawWaterMarks(watermarks):

    #watermarks = [atlas, lumi, tagging]

    wmNum = 0
    for wm in watermarks:
        wm.SetTextAlign(11)
        if wmNum == 0:
            wm.SetTextSize(0.04)
            wm.SetTextFont(72)
        else:
            wm.SetTextSize(0.04)
            wm.SetTextFont(42)
        wmNum+=1
        wm.SetNDC()
        wm.Draw()
    return watermarks



#-----------------------------------------------------------
def getEffErrors(num,den):
    
    numHist = ROOT.TH1F('num','num',1,0,1)
    numHist.SetBinContent(1,num)
    
    denHist = ROOT.TH1F('den','den',1,0,1)
    denHist.SetBinContent(1,den)

    eff = ROOT.TGraphAsymmErrors(1)
    #eff.BayesDivide(numHist,denHist)
    eff.Divide(numHist,denHist,"cl=0.683 b(1,1) mode")
    errHigh = eff.GetErrorYhigh(0)
    errLow = eff.GetErrorYlow(0)

    xValue = ctypes.c_double(0)
    theEff = ctypes.c_double(0)
    eff.GetPoint(0,xValue,theEff)
    
    return (theEff,errHigh,errLow)



#----------------------------------------------------------------------
def getSymmEffErrors(num,den):
    eff, errHigh, errLow = getEffErrors(num,den)
    return (float(errHigh) + float(errLow))/2



def makeRoc(sigNum,sigDen,bkgNum,bkgDen,bkgMode="Eff",doErr = False, cutAbove=False,cleanNoCut=False,debug=False):

    nbins = sigNum.GetNbinsX()

    sigTot = sigDen.Integral(0,nbins+1)
    #print "total sig",sigTot
    
    bkgTot = bkgDen.Integral(0,nbins+1)
    #print "total bkg",bkgTot

    xPoints = []
    xErrors = []
    yPoints = []
    yErrors = []
    
    for i in range(nbins):
        bin = i
        
        if debug: print( bin)
            

        if cutAbove:
            thisSig = sigNum.Integral(0,bin)
            thisBkg = bkgNum.Integral(0,bin)
        else:
            thisSig = abs(sigNum.Integral(bin,nbins+1))
            thisBkg = abs(bkgNum.Integral(bin,nbins+1))
            

        if sigTot:
            sigEff = (thisSig)/sigTot
            sigErr = getSymmEffErrors(thisSig,sigTot)
        else:
            sigEff = 0
            sigErr = 0

        if not bkgTot: bkgTot = 1
        bkgEff = thisBkg/bkgTot
        bkgEffErr = getSymmEffErrors(thisBkg,bkgTot)
        #print "\t",thisBkg, bkgTot

        if debug: 
            print( "bkgEff",bkgEff,)
            print( "sigEff",sigEff)
            print( "\tbkg:",thisBkg,"total",bkgTot)
        if bkgEff:
            bkgRej = 1.0/bkgEff
            bkgRejErr = bkgEffErr/(bkgEff*bkgEff)
        else:
            continue
            bkgRej = bkgTot
            bkgRejErr = 0

                
        if not doErr:
            bkgEffErr = bkgEffErr/10000
            bkgRejErr = bkgRejErr/10000
            sigErr    = sigErr/10000


        #print i,thisBkg,bkgTot,"\t",thisSig,sigTot
        if sigEff == 1 and bkgEff == 1: 
            #print roc.GetN()
            #roc.Set(roc.GetN()-2)
            #print roc.GetN()
            #continue
            xValue = ctypes.c_double(0)
            yValue = ctypes.c_double(0)
            theEff = ctypes.c_double(0)
            #print bin
            #roc.GetPoint(bin-1,xValue,yValue)
            #print xValue,yValue
            #sigEff = roc.GetPoint(bin-1)

        if bkgMode == "Rej":
            #print sigEff, bkgRej
            #roc.SetPoint     (bin,sigEff,bkgRej)
            #roc.SetPointError(bin,sigErr,bkgRejErr)
            xPoints.append(sigEff)
            xErrors.append(sigErr)
            yPoints.append(bkgRej)
            yErrors.append(bkgRejErr)
        else:
            #roc.SetPoint     (bin,sigEff,bkgEff)
            #roc.SetPointError(bin,sigErr,bkgEffErr)
            xPoints.append(sigEff)
            xErrors.append(sigErr)
            yPoints.append(bkgEff)
            yErrors.append(bkgEffErr)
        
    
    #
    #
    #
    nbins = len(xPoints)

    if cleanNoCut: 
        popList = []
        for i in range(len(xPoints)):
            if xPoints[i] == 1:
                popList.append(i)

        popList.sort(reverse=True)
        for i in popList:
            xPoints.pop(i)
            yPoints.pop(i)
            xErrors.pop(i)
            yErrors.pop(i)

        nbins = len(xPoints)

            

    #
    # 
    #
    roc = ROOT.TGraphErrors(nbins)
    for i in range(nbins):
        roc.SetPoint     (i,xPoints[i],yPoints[i])
        roc.SetPointError(i,xErrors[i],yErrors[i])        
    

    return roc

#
#  Calls makeRoc make 
#
def makeRocPlot(inFile, name, var, bkg, sig, indir="", varNorm=None,debug=False,vsLight=True, vsLandPU=False):
    sigHist = inFile.Get(indir+sig+"/"+var).Clone()
    bkgHist = inFile.Get(indir+bkg+"/"+var).Clone()
    
    if not sigHist:
        print("ERROR: cannot get",indir+sig+"/"+var)
        print(sigHist)

    if varNorm:
        sigNormHist = inFile.Get(indir+sig+"/"+varNorm)
        bkgNormHist = inFile.Get(indir+bkg+"/"+varNorm)
    else      :
        sigNormHist = sigHist
        bkgNormHist = bkgHist

    rocPlots = []
    for config in [("Rej",1,5e4),("Eff",5e-4,1)]:
        rocPlots.append(makeRoc(sigHist, sigNormHist, bkgHist, bkgNormHist,doErr=False,bkgMode=config[0],cleanNoCut=True,debug=debug))

        ##can = ROOT.TCanvas(name+"_"+config[0], name+"_"+config[0])
        ##can.cd().SetLogy(1)
        rocPlots[-1].SetLineWidth(5)
        rocPlots[-1].GetXaxis().SetTitle("B-Jet  Efficiency")
        rocPlots[-1].GetXaxis().SetRangeUser(0.4,1)
        if vsLight: yTitle = "Light Flavor "
        elif vsLandPU: yTitle = "Light Flavor (w/PU) "
        else:       yTitle = "C-Jet "
        
        if config[0] == "Rej":    yTitle +="Rejection"
        elif config[0] == "Eff":  yTitle +="Efficiency"
        rocPlots[-1].GetYaxis().SetTitle(yTitle)
        rocPlots[-1].GetYaxis().SetRangeUser(config[1],config[2])
        rocPlots[-1].Draw("AL")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".pdf")
        # can.SaveAs(o.outDir+"/roc_"+name+"_"+config[0]+".png")

    return rocPlots



#
#
#
def plotSame(name,graphs,colors,styles, workingPts= None,rocType="Eff",plotDeepCSV=False,plotDeepJet=False, taggerNames=[], coloredText=[], logy=True, yMin=1e-4, xMin=0.3, labelNames =[], cmsText="",outputDir = ""):

    can = ROOT.TCanvas(name,name)
    if logy:
        can.cd().SetLogy(1)
    hist_axis = ROOT.TH1F("hist_axis","hist_axis",1,xMin,1)
    hist_axis.GetYaxis().SetTitle(graphs[0].GetYaxis().GetTitle())
    hist_axis.GetXaxis().SetTitle(graphs[0].GetXaxis().GetTitle())
    hist_axis.Draw()

    xMax = 1 
    hist_axis.GetXaxis().SetRangeUser(xMin,xMax)
    hist_axis.GetYaxis().SetRangeUser(yMin,1)

    line = ROOT.TF1("guessing","x",xMin,xMax)
    line.SetLineColor(ROOT.kGray)
    line.SetLineStyle(10)
    line.Draw("same")
    #line.DrawLine(max(xMin,yMin), 1*max(xMin,yMin), xMax, 1.0*xMax)

    for gItr, g in enumerate(graphs):
        g.SetLineColor(colors[gItr])
        g.SetLineStyle(styles[gItr])
        #if not gItr:
        #    g.Draw("AL")
        #else:
        #    g.Draw("L")
        g.Draw("L")

    if not workingPts == None:
        g_wrkPts = ROOT.TGraph(len(workingPts))
        g_wrkPts.SetMarkerSize(2)
        g_wrkPts.SetMarkerColor(colors[1])
        g_wrkPts.SetMarkerStyle(34)
        for wpItr, wp in enumerate(workingPts):
            #print wpItr,wp

            g_wrkPts.SetPoint(wpItr, wp[0],wp[1])

        g_wrkPts.Draw("P")

    cmsLine1, cmsLine2 = getCMSText(xStart=0.2,yStart=0.875,subtext=cmsText)
    cmsLine1.Draw("same")
    cmsLine2.Draw("same")

    yStart = 0.75
    xStart = 0.2
    if rocType == "Rej":
        xStart = 0.5
        yStart = 0.875



    offJetText  = getText(labelNames[0]+" Jets (Solid)  ",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
    yStart = yStart - 0.05
    offJetText.Draw("same")

    pfJetText   = getText(labelNames[1]+" Jet (Dashed)  ",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
    pfJetText.Draw("same")

        #offJetTextDeep  = getText("Offline DeepCSV (Dashed)  ",xStart=0.6,yStart=0.36,size=0.03,color=ROOT.kBlack)

        #offJetText  = getText("Offline Jet  ",xStart=0.6,yStart=0.4,size=0.03,color=ROOT.kBlack)



    for t in taggerNames:
        yStart = yStart - 0.05
        deepCSVText   = getText(t,xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kRed+2)
        deepCSVText.Draw("same")


    cTexts = [ ]
    for iCt, ct in enumerate(coloredText):
        yStart = yStart - 0.05
        cTexts.append(getText(ct,xStart=xStart,yStart=yStart,size=0.04,color=colors[2*iCt]))
        cTexts[-1].Draw("same")



    yStart = yStart - 0.05
    if plotDeepCSV:
        if plotDeepJet:
            deepCSVText   = getText("DeepCSV",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlue)
        else:
            deepCSVText   = getText("DeepJet",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)

        deepCSVText.Draw("same")
        yStart = yStart - 0.05

    if plotDeepJet:
        if plotDeepCSV:
            deepJetText   = getText("DeepJet",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlack)
        else:
            deepJetText   = getText("DeepCSV",xStart=xStart,yStart=yStart,size=0.04,color=ROOT.kBlue)
        deepJetText.Draw("same")
        yStart = yStart - 0.05





    #offJetTextDeep.Draw("same")

    can.SaveAs(outputDir+"/roc_"+name+".pdf")



def makePt(numSig,denSig,numBkg,denBkg,bkgMode="Eff",doErr = False):

    oPt = ROOT.TGraphErrors(1)

    sigTot = denSig.Integral(1,denSig.GetNbinsX())
    bkgTot = denBkg.Integral(1,denBkg.GetNbinsX())
    
    thisSig = numSig.Integral(1,numSig.GetNbinsX())
    if sigTot:
        sigEff = (thisSig)/sigTot
        sigErr = getSymmEffErrors(thisSig,sigTot)
    else:
        sigEff = 0
        sigErr = 0

    thisBkg = numBkg.Integral(1,numBkg.GetNbinsX())
    if not bkgTot: bkgTot = 1
    bkgEff = thisBkg/bkgTot
    bkgEffErr = getSymmEffErrors(thisBkg,bkgTot)

    if bkgEff:
        bkgRej = 1.0/bkgEff
        bkgRejErr = bkgEffErr/(bkgEff*bkgEff)
    else:
        bkgRej = bkgTot
        bkgRejErr = 0
                
    if not doErr:
        bkgEffErr = bkgEffErr/1000
        bkgRejErr = bkgRejErr/1000
        sigErr    = sigErr/1000


    if bkgMode == "Rej":
        oPt.SetPoint     (0,sigEff,bkgRej)
        oPt.SetPointError(0,sigErr,bkgRejErr)
    else:
        oPt.SetPoint     (0,sigEff,bkgEff)
        oPt.SetPointError(0,sigErr,bkgEffErr)
        
    return oPt


def GetRoc(inFile, sigNameNum,sigNameDen,bkgNameNum,bkgNameDen,doErr=False,mode="Rej", cutAbove=False):
    hsigNum = inFile.Get(sigNameNum)
    hbkgNum = inFile.Get(bkgNameNum)
    hsigDen = inFile.Get(sigNameDen)
    hbkgDen = inFile.Get(bkgNameDen)

    if not hsigNum:
        print( "Cannot get ",hsigNum,sigNameNum)
    if not hbkgNum:
        print( "Cannot get ",hbkgNum)

    rocCurve = makeRoc(hsigNum,hsigDen,hbkgNum,hbkgDen,bkgMode=mode,doErr=doErr, cutAbove=cutAbove)

    return rocCurve



def GetPt(inFile,numSigName,denSigName,numBkgName, denBkgName,doErr=False,mode="Rej"):
    hnumSig = inFile.Get(numSigName)
    hdenSig = inFile.Get(denSigName)
    hnumBkg = inFile.Get(numBkgName)
    hdenBkg = inFile.Get(denBkgName)

    if not hnumSig: print( "Cannot get",hnumSig,numSigName)
        

    opPt = makePt(hnumSig,hdenSig,hnumBkg,hdenBkg,bkgMode=mode,doErr=doErr)
    
    return opPt



def configRoc(name, dirPrefix, tagger, color,style):
    return {"name"     : name,
            "tagger"   : tagger,
            "BQDirNum" : dirPrefix+"_TruthJetsBQ",
            "BQDirDen" : dirPrefix+"_TruthJetsBQ",
            "LFDirNum" : dirPrefix+"_TruthJetsLF",
            "LFDirDen" : dirPrefix+"_TruthJetsLF",
            "color"    : color,
            "style"    : style,
            }

def configRocWrtTrig(name, dirPrefix, trigOpPt, tagger, color,style):
    return {"name"     : name,
            "tagger"   : tagger,
            "BQDirNum" : dirPrefix+"_"+trigOpPt+"_TruthJetsBQ",
            "BQDirDen" : dirPrefix+"_TruthJetsBQ",
            "LFDirNum" : dirPrefix+"_"+trigOpPt+"_TruthJetsLF",
            "LFDirDen" : dirPrefix+"_TruthJetsLF",
            "color"    : color,
            "style"    : style,
            }



def configOpPt(name, tagger, numDir, denDir, color,style):
    return {"name"   : name,
            "tagger" : tagger,
            "numBQDir" : numDir+"_TruthJetsBQ",
            "numLFDir" : numDir+"_TruthJetsLF",                        
            "denBQDir" : denDir+"_TruthJetsBQ",
            "denLFDir" : denDir+"_TruthJetsLF",                        
            "color"    : color,
            "style"    : style,
            }
