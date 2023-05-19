import ROOT

from   ROOTHelp.Utils         import do_variable_rebinning, makeCanvas
from   ROOTHelp.Plotting      import makeRatio
#from rocCurveUtils            import drawWaterMarks
#import rebinning
from Rebinning import rebinningDB

from JetLevelPlotUtils import getCMSText
from optparse import OptionParser
import ROOTHelp.FancyROOTStyle

    
import os

ROOT.gROOT.SetBatch(True)
ROOT.gErrorIgnoreLevel = ROOT.kWarning



def getOpts():
    p = OptionParser()
    p.add_option('--input',  type = 'string', default = "outBTag.FTKBtagging.ttbar.mwt2.All.root", dest = 'inFile', help = 'intput File' )
    p.add_option('--output', type = 'string', default = "makeRocCurves", dest = 'outDir', help = 'output dir' )
    p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
    p.add_option('--labName', type = 'string', default = "Reference,Monitored",  help = '' )
    #p.add_option('--lumiText', default = "",  help = '' )
    (o,a) = p.parse_args()
    
    return o, a



maxDict = {"jetNSelectedTracks":20,
           "jetNTracks":30,
           }


def getHist(inFile,dir,var,binning,color):
    hist = inFile.Get(dir+"/"+var)
    if not hist:
        print( "ERROR getting",dir+"/"+var)
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



def doVarRatio(inFile, BQName, LFName, var, binning, xTitle, setLogy=1, minX=None, maxX=None, minY=None, yAxisSF=1.0,  outputDir = "", extraText = ""):
    offLF = getHist(inFile,LFName,          var,binning,ROOT.kBlack)
    offBQ = getHist(inFile,BQName,          var,binning,ROOT.kRed)


    maxY = max(offLF.GetMaximum(),offBQ.GetMaximum(),
               )

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


    
    xpos = 0.675
    ypos = 0.775
    xwidth = 0.25
    ywidth = 0.10

    leg = ROOT.TLegend(xpos, ypos, xpos+xwidth, ypos+ywidth)
    leg.SetNColumns(1)
    leg.AddEntry(offBQ,"b-jets","L")
    leg.AddEntry(offLF,"light-flavor","L")
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)
    canvas = makeCanvas(var, var, width=800, height=600)
    canvas.cd()
    canvas.SetLogy(setLogy)


    if var in maxDict.keys():
        offLF.GetXaxis().SetRangeUser(offLF.GetXaxis().GetXmin(),maxDict[var] )

    offLF.Draw("hist")
    offBQ.Draw("hist same")
    leg.Draw("same")

    cmsLines = getCMSText(xStart=0.2,yStart=0.85,subtext=extraText)
    for cmsl in cmsLines:
        cmsl.Draw("same")



    #varName = var.replace("tracks/","").replace("btags/","btags_")
    varName = var.replace("tracks/","track_").replace("btags/","btag_").replace("btags_noV0/","btag_noV0_").replace("matchedJet/","matchedJet_")
    canvas.SaveAs(outputDir+"/BvL_"+varName+".pdf")
    #canvas.SaveAs(o.outDir+"/"+var+".eps")
    #canvas.SaveAs(o.outDir+"/"+var+".png")



def makePlots(inFile, BQName, LFName, outputDir, extraText):

    
    for v in [
            "dPt",               
            "dEta",    
            "dPhi",    
            "dR",      
            "dcsv",    
    
            "dDeepcsv",
            "ddeepFlavB",    
            "dnTracks",      
            "dnSelTracks",   
            "dIp2N"         ,
            "dIp2P"         ,
            "dIp3N"         ,
            "dIp3P"         ,
            "dProbaN"       ,
            "dProba"        ,
            "dBprobN"       ,
            "dBprob"        ,
            "dSvx"          ,
            "dSvxHP"        ,
            "dCombIVF"      ,
            "dCombIVF_N"    ,
            "dSoftMuN"      ,
            "dSoftMu"       ,
            "dSoftElN"      ,
            "dSoftEl"       ,
            "dcMVAv2"       ,
            "dcMVAv2N"      ,
    
              ]:
        
        binning = 1
        doVarRatio(inFile, 
                   BQName, 
                   LFName,
                   "matchedJet/"+v,
                   xTitle = "(per Jet) "+("#Delta"+v).replace("#Deltad","#Delta"),
                   binning = binning,
                   setLogy = 1,
                   #yAxisSF = 100
                   outputDir = outputDir,
                   extraText = extraText,
                   )
    
    
    for v in [
            "dsv_NTracks"                ,
            "dsv_Mass"                   ,
            "dsv_JetDeltaR"              ,
            "dsv_EnergyRatio"            ,
            "dsv_R"            ,
            "dsv_Z"            ,
            "dsv_Chi2"         ,
            "dsv_Chi2_l"       ,
            "dsv_NDF"          ,
            "dsv_Flight"       ,
            "dsv_FlightSig"    ,
            "dsv_Flight2D"     ,
            "dsv_FlightSig2D"  ,
            "dsv_Pt"           ,
            "dsv_Eta"          ,
            "dsv_Phi"          ,
            "dsv_DistJetAxis"  ,
            "dsv_BoostOverSqrtJetPt"     ,
            "dsv_massVertexEnergyFraction"     ,
            "dsv_totCharge"     ,
            ]:
        
        binning = 1
        doVarRatio(inFile, 
                   BQName, 
                   LFName,
                   "matchedJet/btags/"+v,
                   xTitle = "(per SV) "+("#Delta"+v).replace("#Deltad","#Delta"),
                   binning = binning,
                   setLogy = 1,
                   #yAxisSF = 100
                   outputDir = outputDir,
                   extraText = extraText,
                   )
    
    
    
    for v in [
            "dip3d_l",
            "dip3d",
            "dip3d_sig_l",
            "dip3d_sig",  
            "dip3d_err_l",
            "dip3d_err",  
            "dip2d_l",
            "dip2d",
            "dip2d_sig_l",
            "dip2d_sig",  
            "dip2d_err_l",
            "dip2d_err",  
            "dtrackDecayLenVal_l"  ,
            "dtrackDecayLenVal"    ,
            "dtrackJetDistVal"     ,
            "dtrackPtRel"          ,
            "dtrackPt"             ,
            "dtrackMomentum"       ,
            
            "dtrackEta"            ,
            "dtrackPhi"            ,
            "dtrackPPar"           ,
            "dtrackDeltaR"         ,
            "dtrackDeltaR_l"       ,
            "dtrackEtaRel"         ,
            "dtrackPtRatio"        ,
            "dtrackPParRatio"      ,
    
            "dtrackChi2"            , 
            "dtrackNTotalHits"      , 
            "dtrackNPixelHits"      , 
            "dtrackIsFromV0"  ,
    
    
    
    
    
            ]:
        
        binning = 1
        doVarRatio(inFile, 
                   BQName, 
                   LFName,
                   "matchedJet/btags/"+v,
                   xTitle = "(per Track) "+("#Delta"+v).replace("#Deltad","#Delta"),
                   binning = binning,
                   setLogy = 1,
                   #yAxisSF = 100
                   outputDir = outputDir,
                   extraText = extraText,
                   )
    
    
    
    
    
    for v in [
            "djetNTracks"                   ,
            "djetNSecondaryVertices"        ,
    
            "dchargedMultiplicity"           ,
            "dchargedHadronEnergyFraction"   ,
            "dchargedHadronMultiplicity"     ,
            "dchargedEmEnergyFraction"       ,
    
            "dneutralMultiplicity"           ,
            "dneutralHadronEnergyFraction"   ,
            "dneutralHadronMultiplicity"     ,
            "dneutralEmEnergyFraction"       ,
    
            "dphotonMultiplicity"           ,
            "dphotonEnergyFraction"         ,
    
            "dmuonMultiplicity"             ,
            "dmuonEnergyFraction"           ,
            
            "delecMultiplicity"             ,
            "delecEnergyFraction"           ,
            
            "dtotalMultiplicity"            ,
    
            ]:
        
        binning = 1
        doVarRatio(inFile, 
                   BQName, 
                   LFName,
                   "matchedJet/btags/"+v,
                   xTitle = "(per Jet) "+("#Delta"+v).replace("#Deltad","#Delta"),
                   binning = binning,
                   setLogy = 1,
                   #yAxisSF = 100
                   outputDir = outputDir,
                   extraText = extraText,
                   )
    

if __name__ == "__main__":
    o, a = getOpts()
    
    inFile  = ROOT.TFile(o.inFile,  "READ")
    labName = o.labName.split(",")


    if not os.path.exists(o.outDir):
        os.makedirs(o.outDir)
        
    makePlots(inFile = inFile,
              LFName = "offJets_matched_L",
              BQName = "offJets_matched_B",
              outputDir = o.outDir,
              extraText = o.cmsText,
              )



