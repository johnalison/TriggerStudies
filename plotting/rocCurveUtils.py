import ROOT
import ctypes

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
