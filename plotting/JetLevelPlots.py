import ROOT

ROOT.gROOT.SetBatch(True)

#import sys
#sys.path.insert(0, '../../')
import ROOTHelp.FancyROOTStyle

from optparse import OptionParser
p = OptionParser()
p.add_option('--inputData',  type = 'string', dest = 'inFileData', help = 'intput File' )
p.add_option('--inputMC',  type = 'string', dest = 'inFileMC', help = 'intput File' )
p.add_option('--output', type = 'string', default = "jetLevelPlots", dest = 'outDir', help = 'output dir' )
p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
p.add_option('--lumiText', default = "",  help = '' )
(o,a) = p.parse_args()


#from rocCurveUtils            import drawWaterMarks
#import rebinning
#from Rebinning import rebinningDB

inFileData  = ROOT.TFile(o.inFileData,  "READ")
inFileMC    = ROOT.TFile(o.inFileMC,  "READ")

import os
if not os.path.exists(o.outDir):
    os.makedirs(o.outDir)


from JetLevelPlotUtils import makeEff, drawComp, getHist, drawStackCompRatio, makeStack, makeInverseTurnOn, make2DComp, makeInverseTurnOnAll,plotRatio

plotRatio("nPV",    "Events",inFileData, "Data", inFileMC, "MC",xTitle="nPV", outDir=o.outDir,binning=1)


#
#  Offline Turnon curves:
#
effBinning=5
eff_CaloCSV_Data = makeEff("CSVv2_l" ,    ["offJets_matchedCalocsvTag","offJets_matchedCalo"],inFileData,binning=effBinning)
eff_CaloCSV_MC   = makeEff("CSVv2_l" ,    ["offJets_matchedCalocsvTag","offJets_matchedCalo"],inFileMC  ,binning=effBinning)
eff_PFCSV_Data   = makeEff("CSVv2_l" ,    ["offJets_matchedPFcsvTag",  "offJets_matched"]  ,inFileData,binning=effBinning)
eff_PFCSV_MC     = makeEff("CSVv2_l" ,    ["offJets_matchedPFcsvTag",  "offJets_matched"]  ,inFileMC  ,binning=effBinning)

eff_CaloCSVvsDeepCSV_Data = makeEff("DeepCSV_l" ,    ["offJets_matchedCalocsvTag","offJets_matchedCalo"],inFileData,binning=effBinning)
eff_CaloCSVvsDeepCSV_MC   = makeEff("DeepCSV_l" ,    ["offJets_matchedCalocsvTag","offJets_matchedCalo"],inFileMC  ,binning=effBinning)
eff_PFCSVvsDeepCSV_Data   = makeEff("DeepCSV_l" ,    ["offJets_matchedPFcsvTag",  "offJets_matched"]  ,inFileData,binning=effBinning)
eff_PFCSVvsDeepCSV_MC     = makeEff("DeepCSV_l" ,    ["offJets_matchedPFcsvTag",  "offJets_matched"]  ,inFileMC  ,binning=effBinning)


eff_CaloDeepCSV_Data = makeEff("DeepCSV_l" ,    ["offJets_matchedCaloDeepcsvTag","offJets_matchedCalo"],inFileData,binning=effBinning)
eff_CaloDeepCSV_MC   = makeEff("DeepCSV_l" ,    ["offJets_matchedCaloDeepcsvTag","offJets_matchedCalo"],inFileMC  ,binning=effBinning)
eff_PFDeepCSV_Data   = makeEff("DeepCSV_l" ,    ["offJets_matchedPFDeepcsvTag",  "offJets_matched"]  ,inFileData,binning=effBinning)
eff_PFDeepCSV_MC     = makeEff("DeepCSV_l" ,    ["offJets_matchedPFDeepcsvTag",  "offJets_matched"]  ,inFileMC  ,binning=effBinning)


reveff_CSV_MC = {}
reveff_CSV_Data = {}
reveff_DeepCSV_MC = {}
reveff_DeepCSV_Data = {}
for jetType in ["Calo","PF"]:
    reveff_CSV_MC[jetType] = {}
    reveff_CSV_Data[jetType] = {}
    reveff_DeepCSV_MC[jetType] = {}
    reveff_DeepCSV_Data[jetType] = {}
    for op in ["Loose","Medium","Tight"]:
        jetTypeDen = jetType if jetType == "Calo" else ""

        reveff_CSV_MC  [jetType][op]   = makeEff("CSVv2_l" ,    ["offJets"+op+"_matched"+jetType+"Jet",  "offJets_matched"+jetTypeDen+"Jet"]  ,inFileMC    ,binning=effBinning)
        reveff_CSV_Data[jetType][op]   = makeEff("CSVv2_l" ,    ["offJets"+op+"_matched"+jetType+"Jet",  "offJets_matched"+jetTypeDen+"Jet"]  ,inFileData  ,binning=effBinning)

        reveff_DeepCSV_MC  [jetType][op]   = makeEff("DeepCSV_l" ,    ["offJets"+op+"_matched"+jetType+"Jet",  "offJets_matched"+jetTypeDen+"Jet"]  ,inFileMC    ,binning=effBinning)
        reveff_DeepCSV_Data[jetType][op]   = makeEff("DeepCSV_l" ,    ["offJets"+op+"_matched"+jetType+"Jet",  "offJets_matched"+jetTypeDen+"Jet"]  ,inFileData  ,binning=effBinning)


    drawComp("RevEff_"+jetType+"CSV_MC",[(reveff_CSV_MC[jetType]["Loose"], "Loose",ROOT.kBlue),
                                         (reveff_CSV_MC[jetType]["Medium"],"Medium",ROOT.kGreen),
                                         (reveff_CSV_MC[jetType]["Tight"], "Tight",ROOT.kRed),]
             ,yTitle="Efficiency",xTitle="CSV Value of Jets", otherText=""+jetType+" Jets (MC)",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)

    drawComp("RevEff_"+jetType+"CSV_Data",[(reveff_CSV_Data[jetType]["Loose"], "Loose",ROOT.kBlue),
                                           (reveff_CSV_Data[jetType]["Medium"],"Medium",ROOT.kGreen),
                                           (reveff_CSV_Data[jetType]["Tight"], "Tight",ROOT.kRed),]
             ,yTitle="Efficiency",xTitle="CSV Value of Jets", otherText=""+jetType+" Jets (Data)",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


    drawComp("RevEff_"+jetType+"CSV_All",[(reveff_CSV_Data[jetType]["Loose"], "Loose (Data)",ROOT.kBlue),
                                          (reveff_CSV_MC[jetType]["Loose"], "Loose (MC)",ROOT.kBlue,24),
                                          (reveff_CSV_Data[jetType]["Medium"],"Medium (Data)",ROOT.kGreen+1),
                                          (reveff_CSV_MC[jetType]["Medium"],"Medium (MC)",ROOT.kGreen+1,24),
                                          (reveff_CSV_Data[jetType]["Tight"], "Tight (Data)",ROOT.kRed),
                                          (reveff_CSV_MC[jetType]["Tight"], "Tight (MC)",ROOT.kRed,24),
                                          ]
             ,yTitle="Efficiency",xTitle="Online ("+jetType+"-Jet) CSV Value", otherText="",outDir=o.outDir,yMax=1.2,leg="special",cmsText=o.cmsText,lumiText=o.lumiText)

    drawComp("RevEff_"+jetType+"DeepCSV_All",[(reveff_DeepCSV_Data[jetType]["Loose"], "Loose (Data)",ROOT.kBlue),
                                              (reveff_DeepCSV_MC[jetType]["Loose"], "Loose (MC)",ROOT.kBlue,24),
                                              (reveff_DeepCSV_Data[jetType]["Medium"],"Medium (Data)",ROOT.kGreen+1),
                                              (reveff_DeepCSV_MC[jetType]["Medium"],"Medium (MC)",ROOT.kGreen+1,24),
                                              (reveff_DeepCSV_Data[jetType]["Tight"], "Tight (Data)",ROOT.kRed),
                                              (reveff_DeepCSV_MC[jetType]["Tight"], "Tight (MC)",ROOT.kRed,24),
                                              ]
             ,yTitle="Efficiency",xTitle="Online ("+jetType+"-Jet) DeepCSV Value", otherText="",outDir=o.outDir,yMax=1.2,leg="special",cmsText=o.cmsText,lumiText=o.lumiText)




#   Data vs MC
drawComp("Eff_CaloCSV_DataVSMC",[(eff_CaloCSV_Data,"Data",ROOT.kBlue),(eff_CaloCSV_MC,"MC",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="CSV Value of Jets", otherText="Online WP: CSV > 0.5",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
drawComp("Eff_PFCSV_DataVSMC",[(eff_PFCSV_Data,"Data",ROOT.kBlue),(eff_PFCSV_MC,"MC",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="CSV Value of Jets", otherText="Online WP: CSV > 0.7",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)

drawComp("Eff_CaloCSVvsDeepCSV_DataVSMC",[(eff_CaloCSVvsDeepCSV_Data,"Data",ROOT.kBlue),(eff_CaloCSVvsDeepCSV_MC,"MC",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText="Online WP: CSV > 0.5",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
drawComp("Eff_PFCSVvsDeepCSV_DataVSMC",[(eff_PFCSVvsDeepCSV_Data,"Data",ROOT.kBlue),(eff_PFCSVvsDeepCSV_MC,"MC",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText="Online WP: CSV > 0.7",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


drawComp("Eff_CaloDeepCSV_DataVSMC",[(eff_CaloDeepCSV_Data,"Data",ROOT.kBlue),(eff_CaloDeepCSV_MC,"MC",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText="Online WP: DeepCSV > 0.17",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
drawComp("Eff_PFDeepCSV_DataVSMC",[(eff_PFDeepCSV_Data,"Data",ROOT.kBlue),(eff_PFDeepCSV_MC,"MC",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText="Online WP: DeepCSV > 0.24",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


#
#   Calo vs PF
#
drawComp("Eff_CaloVsPF_CSV_Data",[(eff_CaloCSV_Data,"Calo (Data)",ROOT.kBlue),(eff_PFCSV_Data,"PF (Data)",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="CSV Value of Jets", otherText=["Online Calo WP: CSV > 0.5","Online PF WP: CSV > 0.7"],outDir=o.outDir,xStartOther=0.3,cmsText=o.cmsText,lumiText=o.lumiText)
drawComp("Eff_CaloVsPF_CSV_MC",[(eff_CaloCSV_MC,"Calo (MC)",ROOT.kBlue),(eff_PFCSV_MC,"PF (MC)",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="CSV Value of Jets", otherText=["Online Calo WP: CSV > 0.5","Online PF WP: CSV > 0.7"],outDir=o.outDir,xStartOther=0.3,cmsText=o.cmsText,lumiText=o.lumiText)

drawComp("Eff_CaloVsPF_CSVvsDeepCSV_Data",[(eff_CaloCSVvsDeepCSV_Data,"Calo (Data)",ROOT.kBlue),(eff_PFCSVvsDeepCSV_Data,"PF (Data)",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText=["Online Calo WP: CSV > 0.5","Online PF WP: CSV > 0.7"],outDir=o.outDir,xStartOther=0.3,cmsText=o.cmsText,lumiText=o.lumiText)
drawComp("Eff_CaloVsPF_CSVvsDeepCSV_MC",[(eff_CaloCSVvsDeepCSV_MC,"Calo (MC)",ROOT.kBlue),(eff_PFCSVvsDeepCSV_MC,"PF (MC)",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText=["Online Calo WP: CSV > 0.5","Online PF WP: CSV > 0.7"],outDir=o.outDir,xStartOther=0.3,cmsText=o.cmsText,lumiText=o.lumiText)


drawComp("Eff_CaloVsPF_DeepCSV_Data",[(eff_CaloDeepCSV_Data,"Calo (Data)",ROOT.kBlue),(eff_PFDeepCSV_Data,"PF (Data)",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText=["Online Calo WP: DeepCSV > 0.17","Online PF WP: DeepCSV > 0.24"],outDir=o.outDir,xStartOther=0.4,yStartOther=0.15,cmsText=o.cmsText,lumiText=o.lumiText)
drawComp("Eff_CaloVsPF_DeepCSV_MC",[(eff_CaloDeepCSV_MC,"Calo (MC)",ROOT.kBlue),(eff_PFDeepCSV_MC,"PF (MC)",ROOT.kRed)]
         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText=["Online Calo WP: DeepCSV > 0.17","Online PF WP: DeepCSV > 0.24"],outDir=o.outDir,xStartOther=0.4,yStartOther=0.15,cmsText=o.cmsText,lumiText=o.lumiText)


#   (Calo vs PF) x (Data vs MC )
drawComp("Eff_CaloVsPF_CSV_DataVsMC",
         [(eff_CaloCSV_Data,"Calo-Jet (Data)",ROOT.kBlue),
          (eff_CaloCSV_MC,  "Calo-Jet (MC)  ",ROOT.kBlue, 24),
          (eff_PFCSV_Data,  "PF-Jet   (Data)",ROOT.kRed),
          (eff_PFCSV_MC,    "PF-Jet   (MC)  ",ROOT.kRed, 24),
          ]
         ,yTitle="Efficiency",xTitle="Offline CSV Value", otherText=["Online Calo WP: CSV > 0.5","Online PF WP: CSV > 0.7"],outDir=o.outDir,xStartOther=0.3,cmsText=o.cmsText,lumiText=o.lumiText)


drawComp("Eff_CaloVsPF_CSVvsDeepCSV_DataVsMC",
         [(eff_CaloCSVvsDeepCSV_Data,"Calo-Jet (Data)",ROOT.kBlue),
          (eff_CaloCSVvsDeepCSV_MC,  "Calo-Jet (MC)  ",ROOT.kBlue, 24),
          (eff_PFCSVvsDeepCSV_Data,  "PF-Jet   (Data)",ROOT.kRed),
          (eff_PFCSVvsDeepCSV_MC,    "PF-Jet   (MC)  ",ROOT.kRed, 24),
          ]
         ,yTitle="Efficiency",xTitle="Offline DeepCSV Value", otherText=["Online Calo WP: CSV > 0.5","Online PF WP: CSV > 0.7"],outDir=o.outDir,xStartOther=0.3,cmsText=o.cmsText,lumiText=o.lumiText)

drawComp("Eff_CaloVsPF_DeepCSVvsDeepCSV_DataVsMC",
         [(eff_CaloDeepCSV_Data,"Calo-Jet (Data)",ROOT.kBlue),
          (eff_CaloDeepCSV_MC,  "Calo-Jet (MC)  ",ROOT.kBlue, 24),
          (eff_PFDeepCSV_Data,  "PF-Jet   (Data)",ROOT.kRed),
          (eff_PFDeepCSV_MC,    "PF-Jet   (MC)  ",ROOT.kRed, 24),
          ]
         ,yTitle="Efficiency",xTitle="Offline DeepCSV Value", otherText=["Online Calo WP: DeepCSV > 0.17","Online PF WP: DeepCSV > 0.24"],outDir=o.outDir,xStartOther=0.4,yStartOther=0.15,cmsText=o.cmsText,lumiText=o.lumiText)
#otherText="Online WP: DeepCSV > 0.63",outDir=o.outDir)



#
# Offline vs Online
#
csvBinning=3
# Deep CSV
offDeepCSV_Calo    = getHist(inFileData,"offJets_matchedCalo",     "DeepCSV_l",binning=csvBinning,norm=1)
caloDeepCSV        = getHist(inFileData,"offJets_matchedCaloJet",  "DeepCSV_l",binning=csvBinning,norm=1)
offDeepCSV_Calo_MC = getHist(inFileMC,  "offJets_matchedCalo",     "DeepCSV_l",binning=csvBinning,norm=1)
caloDeepCSV_MC     = getHist(inFileMC,  "offJets_matchedCaloJet",  "DeepCSV_l",binning=csvBinning,norm=1)

offDeepCSV_PF      = getHist(inFileData,"offJets_matched",     "DeepCSV_l",binning=csvBinning,norm=1)
pfDeepCSV          = getHist(inFileData,"offJets_matchedJet",  "DeepCSV_l",binning=csvBinning,norm=1)
offDeepCSV_PF_MC   = getHist(inFileMC,  "offJets_matched",     "DeepCSV_l",binning=csvBinning,norm=1)
pfDeepCSV_MC       = getHist(inFileMC,  "offJets_matchedJet",  "DeepCSV_l",binning=csvBinning,norm=1)

# CSV
offCSV_Calo    = getHist(inFileData,"offJets_matchedCalo",     "CSVv2_l",binning=csvBinning,norm=1)
caloCSV        = getHist(inFileData,"offJets_matchedCaloJet",  "CSVv2_l",binning=csvBinning,norm=1)
offCSV_Calo_MC = getHist(inFileMC,  "offJets_matchedCalo",     "CSVv2_l",binning=csvBinning,norm=1)
caloCSV_MC     = getHist(inFileMC,  "offJets_matchedCaloJet",  "CSVv2_l",binning=csvBinning,norm=1)

offCSV_PF      = getHist(inFileData,"offJets_matched",       "CSVv2_l",binning=csvBinning,norm=1)
pfCSV          = getHist(inFileData,"offJets_matchedJet",    "CSVv2_l",binning=csvBinning,norm=1)
offCSV_PF_MC   = getHist(inFileMC,  "offJets_matched",       "CSVv2_l",binning=csvBinning,norm=1)
pfCSV_MC       = getHist(inFileMC,  "offJets_matchedJet",    "CSVv2_l",binning=csvBinning,norm=1)

###
#### Off Vs HLT
#drawCompRatio("DeepCSV_CaloVsOff",[(caloDeepCSV,"Calo Jets (Data)"),(offDeepCSV_Calo,"Offline Jets (Data)")]
#              ,yTitle="Normalized",xTitle="DeepCSV Value of Jets",rTitle="Calo/Offline",setLogy=0)
#drawCompRatio("DeepCSV_CaloVsOff_MC",[(caloDeepCSV_MC,"Calo Jets (MC)"),(offDeepCSV_Calo_MC,"Offline Jets (MC)")]
#              ,yTitle="Normalized",xTitle="DeepCSV Value of Jets",rTitle="Calo/Offline",setLogy=0)
#drawCompRatio("DeepCSV_PFVsOff",[(pfDeepCSV,"PF Jets (Data)"),(offDeepCSV_PF,"Offline Jets (Data)")]
#              ,yTitle="Normalized",xTitle="DeepCSV Value of Jets",rTitle="PF/Offline",setLogy=0)
#drawCompRatio("DeepCSV_PFVsOff_MC",[(pfDeepCSV_MC,"PF Jets (MC)"),(offDeepCSV_PF_MC,"Offline Jets (MC)")]
#              ,yTitle="Normalized",xTitle="DeepCSV Value of Jets",rTitle="PF/Offline",setLogy=0)
#
## Data Vs MC
#drawCompRatio("CSV_Calo_DataVsMC",[(caloCSV,"Data"),(caloCSV_MC,"MC")]
#              ,yTitle="Normalized",xTitle="Calo CSV",rTitle="Data/MC",setLogy=0)
#drawCompRatio("DeepCSV_Calo_DataVsMC",[(caloDeepCSV,"Data"),(caloDeepCSV_MC,"MC")]
#              ,yTitle="Normalized",xTitle="Calo DeepCSV",rTitle="Data/MC",setLogy=0)
#drawCompRatio("CSV_Off_DataVsMC",[(offCSV_PF,"Data"),(offCSV_PF_MC,"MC")]
#              ,yTitle="Normalized",xTitle="Offline CSV",rTitle="Data/MC",setLogy=0)
#drawCompRatio("DeepCSV_Off_DataVsMC",[(offDeepCSV_PF,"Data"),(offDeepCSV_PF_MC,"MC")]
#              ,yTitle="Normalized",xTitle="Offline DeepCSV",rTitle="Data/MC",setLogy=0)
#drawCompRatio("CSV_PF_DataVsMC",[(pfCSV,"Data"),(pfCSV_MC,"MC")]
#              ,yTitle="Normalized",xTitle="PF CSV",rTitle="Data/MC",setLogy=0)
#drawCompRatio("DeepCSV_PF_DataVsMC",[(pfDeepCSV,"Data"),(pfDeepCSV_MC,"MC")]
#              ,yTitle="Normalized",xTitle="PF DeepCSV",rTitle="Data/MC",setLogy=0)


offCSV_B_PF_MC      = getHist(inFileMC,"offJets_matched_B",     "CSVv2_l",binning=csvBinning,norm=0)
offCSV_C_PF_MC      = getHist(inFileMC,"offJets_matched_C",     "CSVv2_l",binning=csvBinning,norm=0)
offCSV_L_PF_MC      = getHist(inFileMC,"offJets_matched_L",     "CSVv2_l",binning=csvBinning,norm=0)

offDeepCSV_B_PF_MC  = getHist(inFileMC,"offJets_matched_B",     "DeepCSV_l",binning=csvBinning,norm=0)
offDeepCSV_C_PF_MC  = getHist(inFileMC,"offJets_matched_C",     "DeepCSV_l",binning=csvBinning,norm=0)
offDeepCSV_L_PF_MC  = getHist(inFileMC,"offJets_matched_L",     "DeepCSV_l",binning=csvBinning,norm=0)


offDeepCSV_B_Calo_MC  = getHist(inFileMC,"offJets_matchedCalo_B",     "DeepCSV_l",binning=csvBinning,norm=0)
offDeepCSV_C_Calo_MC  = getHist(inFileMC,"offJets_matchedCalo_C",     "DeepCSV_l",binning=csvBinning,norm=0)
offDeepCSV_L_Calo_MC  = getHist(inFileMC,"offJets_matchedCalo_L",     "DeepCSV_l",binning=csvBinning,norm=0)

caloCSV_B_MC      = getHist(inFileMC,"offJets_matchedCaloJet_B",     "CSVv2_l",binning=csvBinning,norm=0)
caloCSV_C_MC      = getHist(inFileMC,"offJets_matchedCaloJet_C",     "CSVv2_l",binning=csvBinning,norm=0)
caloCSV_L_MC      = getHist(inFileMC,"offJets_matchedCaloJet_L",     "CSVv2_l",binning=csvBinning,norm=0)

caloDeepCSV_B_MC  = getHist(inFileMC,"offJets_matchedCaloJet_B",     "DeepCSV_l",binning=csvBinning,norm=0)
caloDeepCSV_C_MC  = getHist(inFileMC,"offJets_matchedCaloJet_C",     "DeepCSV_l",binning=csvBinning,norm=0)
caloDeepCSV_L_MC  = getHist(inFileMC,"offJets_matchedCaloJet_L",     "DeepCSV_l",binning=csvBinning,norm=0)

pfCSV_B_MC        = getHist(inFileMC,"offJets_matchedJet_B",       "CSVv2_l",binning=csvBinning,norm=0)
pfCSV_C_MC        = getHist(inFileMC,"offJets_matchedJet_C",       "CSVv2_l",binning=csvBinning,norm=0)
pfCSV_L_MC        = getHist(inFileMC,"offJets_matchedJet_L",       "CSVv2_l",binning=csvBinning,norm=0)

pfDeepCSV_B_MC    = getHist(inFileMC,"offJets_matchedJet_B",     "DeepCSV_l",binning=csvBinning,norm=0)
pfDeepCSV_C_MC    = getHist(inFileMC,"offJets_matchedJet_C",     "DeepCSV_l",binning=csvBinning,norm=0)
pfDeepCSV_L_MC    = getHist(inFileMC,"offJets_matchedJet_L",     "DeepCSV_l",binning=csvBinning,norm=0)


drawStackCompRatio("Calo_CSV_FlavorComp",(caloCSV,"Data"),
                   [(caloCSV_L_MC,"Light Flavor",ROOT.kAzure-9),
                    (caloCSV_C_MC,"Charm Jets",ROOT.kGreen+1),
                    (caloCSV_B_MC,"B Jets",ROOT.kYellow)]
                   ,yTitle="Normalized",xTitle="Online (Calo-Jet) CSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)

drawStackCompRatio("Calo_DeepCSV_FlavorComp",(caloDeepCSV,"Data"),
                   [(caloDeepCSV_L_MC,"Light Flavor",ROOT.kAzure-9),
                    (caloDeepCSV_C_MC,"Charm Jets",ROOT.kGreen+1),
                    (caloDeepCSV_B_MC,"B Jets",ROOT.kYellow)]
                   ,yTitle="Normalized",xTitle="Online (Calo-Jet) DeepCSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


drawStackCompRatio("PF_CSV_FlavorComp",(pfCSV,"Data"),
                   [(pfCSV_L_MC,"Light Flavor",ROOT.kAzure-9),
                    (pfCSV_C_MC,"Charm Jets",ROOT.kGreen+1),
                    (pfCSV_B_MC,"B Jets",ROOT.kYellow)]
                   ,yTitle="Normalized",xTitle="Online (PF-Jet) CSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)

drawStackCompRatio("PF_DeepCSV_FlavorComp",(pfDeepCSV,"Data"),
                   [(pfDeepCSV_L_MC,"Light Flavor",ROOT.kAzure-9),
                    (pfDeepCSV_C_MC,"Charm Jets",ROOT.kGreen+1),
                    (pfDeepCSV_B_MC,"B Jets",ROOT.kYellow)]
                   ,yTitle="Normalized",xTitle="Online (PF-Jet) DeepCSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


drawStackCompRatio("Off_CSV_FlavorComp",(offCSV_PF,"Data"),
                   [(offCSV_L_PF_MC,"Light Flavor",ROOT.kAzure-9),
                    (offCSV_C_PF_MC,"Charm Jets",ROOT.kGreen+1),
                    (offCSV_B_PF_MC,"B Jets",ROOT.kYellow)]
                   ,yTitle="Normalized",xTitle="Offline CSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)

drawStackCompRatio("Off_DeepCSV_FlavorComp",(offDeepCSV_PF,"Data"),
                   [(offDeepCSV_L_PF_MC,"Light Flavor",ROOT.kAzure-9),
                    (offDeepCSV_C_PF_MC,"Charm Jets",ROOT.kGreen+1),
                    (offDeepCSV_B_PF_MC,"B Jets",ROOT.kYellow)]
                   ,yTitle="Normalized",xTitle="Offline DeepCSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)



#plot("pt","offJets",norm=1,logy=1)offJets_matched


makeStack("OffJet_Pt",     "pt_m",     "offJets_matched_X",binning=2,xTitle="Offline Jet Pt", rTitle="Data/MC",logy=1,inFileData=inFileData,inFileMC=inFileMC,outDir=o.outDir,min=20,cmsText=o.cmsText,lumiText=o.lumiText)
makeStack("OffJet_Eta",    "eta",      "offJets_matched_X",binning=1,xTitle="Offline Jet Eta",rTitle="Data/MC",logy=0,inFileData=inFileData,inFileMC=inFileMC,outDir=o.outDir,x_min=-3,x_max=3,cmsText=o.cmsText,lumiText=o.lumiText)
makeStack("OffJet_Phi",    "phi",      "offJets_matched_X",binning=2,xTitle="Offline Jet Phi",rTitle="Data/MC",logy=0,inFileData=inFileData,inFileMC=inFileMC,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
makeStack("OffJet_DeepCSV","DeepCSV_l","offJets_matched_X",binning=csvBinning,xTitle="Offline Jet DeepCSV",rTitle="Data/MC",logy=0,inFileData=inFileData,inFileMC=inFileMC,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
makeStack("OffJet_CSV",    "CSVv2_l",    "offJets_matched_X",binning=csvBinning,xTitle="Offline Jet CSV",rTitle="Data/MC",logy=0,inFileData=inFileData,inFileMC=inFileMC,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)



ROOT.gStyle.SetPalette(1)
oldMargin =  ROOT.gStyle.GetPadRightMargin()
ROOT.gStyle.SetPadRightMargin(0.2)



#make2DComp("PFCompDeepCSV_Data",inFileData,"offJets_matchedJet","deepcsv_vs_matched_deepcsv",xTitle="PF Jet Deep CSV",yTitle="Offline Jet Deep CSV")
#make2DComp("PFCompDeepCSV_MC",  inFileMC  ,"offJets_matchedJet","deepcsv_vs_matched_deepcsv",xTitle="PF Jet Deep CSV",yTitle="Offline Jet Deep CSV")

#make2DComp("PFCompCSVvsDeepCSV_Data",inFileData,"offJets_matchedJet","csv_vs_matched_deepcsv",xTitle="Online (PF-Jet) CSV",yTitle="Offline DeepCSV",outDir=o.outDir)
#make2DComp("PFCompCSVvsDeepCSV_MC",  inFileMC,  "offJets_matchedJet","csv_vs_matched_deepcsv",xTitle="Online (PF-Jet) CSV",yTitle="Offline DeepCSV",outDir=o.outDir)
#
#make2DComp("PFCompCSV_Data",inFileData,"offJets_matchedJet","csv_vs_matched_csv",xTitle="Online (PF-Jet) CSV",yTitle="Offline CSV",outDir=o.outDir)
#make2DComp("PFCompCSV_MC",  inFileMC,  "offJets_matchedJet","csv_vs_matched_csv",xTitle="Online (PF-Jet) CSV",yTitle="Offline CSV",outDir=o.outDir)
#
#
##make2DComp("CaloCompDeepCSV_Data",inFileData,"offJets_matchedCaloJet","deepcsv_vs_matched_deepcsv",xTitle="Calo Jet Deep CSV",yTitle="Offline Jet Deep CSV")
##make2DComp("CaloCompDeepCSV_MC",  inFileMC,  "offJets_matchedCaloJet","deepcsv_vs_matched_deepcsv",xTitle="Calo Jet Deep CSV",yTitle="Offline Jet Deep CSV")
#
#make2DComp("CaloCompCSV_Data",inFileData,"offJets_matchedCaloJet","csv_vs_matched_csv",xTitle="Online (Calo-Jet) CSV",yTitle="Offline CSV",outDir=o.outDir)
#make2DComp("CaloCompCSV_MC",  inFileMC,  "offJets_matchedCaloJet","csv_vs_matched_csv",xTitle="Online (Calo-Jet) CSV",yTitle="Offline CSV",outDir=o.outDir)
#
#make2DComp("CaloCompCSVvsDeepCSV_Data",inFileData,"offJets_matchedCaloJet","csv_vs_matched_deepcsv",xTitle="Online (Calo-Jet) CSV",yTitle="Offline DeepCSV",outDir=o.outDir)
#make2DComp("CaloCompCSVvsDeepCSV_MC",  inFileMC,  "offJets_matchedCaloJet","csv_vs_matched_deepcsv",xTitle="Online (Calo-Jet) CSV",yTitle="Offline DeepCSV",outDir=o.outDir)
#

ROOT.gStyle.SetPadRightMargin(oldMargin)


makeInverseTurnOn("CaloCSVEffwrtOff_MC",   "CSVv2_l","offJetsWORKINGPOINT_matchedCaloJet", inFileMC,  binning=1, otherText="Online Calo CSV Eff wrt Offline (MC)",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
makeInverseTurnOn("CaloCSVEffwrtOff_Data", "CSVv2_l","offJetsWORKINGPOINT_matchedCaloJet", inFileData,binning=1, otherText="Online Calo CSV Eff wrt Offline (Data)",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
makeInverseTurnOnAll("CaloCSVEffwrtOff_All", "CSVv2_l","offJetsWORKINGPOINT_matchedCaloJet", inFileData,"Data",inFileMC,"MC",binning=1, otherText="Online Calo CSV Eff wrt Offline",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
makeInverseTurnOnAll("CaloDeepCSVEffwrtOff_All", "DeepCSV_l","offJetsWORKINGPOINT_matchedCaloJet", inFileData,"Data",inFileMC,"MC",binning=1, otherText="Online Calo DeepCSV Eff wrt Offline",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


makeInverseTurnOn("PFCSVEffwrtOff_MC",   "CSVv2_l","offJetsWORKINGPOINT_matchedPFJet", inFileMC,  binning=1, otherText="Online PF CSV Eff wrt Offline (MC)",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
makeInverseTurnOn("PFCSVEffwrtOff_Data", "CSVv2_l","offJetsWORKINGPOINT_matchedPFJet", inFileData,binning=1, otherText="Online PF CSV Eff wrt Offline (Data)",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
makeInverseTurnOnAll("PFCSVEffwrtOff_All", "CSVv2_l","offJetsWORKINGPOINT_matchedPFJet", inFileData,"Data",inFileMC,"MC",binning=1, otherText="Online PF CSV Eff wrt Offline",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
makeInverseTurnOnAll("PFDeepCSVEffwrtOff_All", "DeepCSV_l","offJetsWORKINGPOINT_matchedPFJet", inFileData,"Data",inFileMC,"MC",binning=1, otherText="Online PF DeepCSV Eff wrt Offline",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


for op in ["Loose","Medium","Tight"]:
    makeInverseTurnOnAll("CaloCSVEffwrtOff_"+op, "CSVv2_l","offJetsWORKINGPOINT_matchedCaloJet", inFileData,"Data",inFileMC,"MC",binning=1, otherText="Online Calo CSV Eff wrt Offline",outDir=o.outDir,
                         wps=[op],cmsText=o.cmsText,lumiText=o.lumiText)


    makeInverseTurnOnAll("PFCSVEffwrtOff_"+op, "CSVv2_l","offJetsWORKINGPOINT_matchedPFJet", inFileData,"Data",inFileMC,"MC",binning=1, otherText="Online PF CSV Eff wrt Offline",outDir=o.outDir,
                         wps=[op],cmsText=o.cmsText,lumiText=o.lumiText)
