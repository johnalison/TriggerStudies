import ROOT

ROOT.gROOT.SetBatch(True)

#import sys
#sys.path.insert(0, '../../')
import ROOTHelp.FancyROOTStyle

from optparse import OptionParser
p = OptionParser()
p.add_option('--inputData1',  type = 'string', dest = 'inFileData1', help = 'intput File' )
p.add_option('--inputData2',  type = 'string', dest = 'inFileData2', help = 'intput File' )
p.add_option('--output', type = 'string', default = "jetLevelPlots", dest = 'outDir', help = 'output dir' )
p.add_option('--cmsText', type = 'string', default = "Work in Progress",  help = '' )
p.add_option('--lumiText', default = "",  help = '' )
(o,a) = p.parse_args()


#from rocCurveUtils            import drawWaterMarks
#import rebinning
#from Rebinning import rebinningDB

inFileData1  = ROOT.TFile(o.inFileData1,  "READ")
inFileData2    = ROOT.TFile(o.inFileData2,  "READ")

import os
if not os.path.exists(o.outDir):
    os.mkdir(o.outDir)


from JetLevelPlotUtils import makeEff, drawComp, drawCompRatio, getHist, drawStackCompRatio, makeStack, makeInverseTurnOn, make2DComp, makeInverseTurnOnAll,plotRatio

plotRatio("nPV",    "Events",inFileData1, "Data 18", inFileData2, "Data 17",xTitle="nPV", outDir=o.outDir,binning=1,cmsText=o.cmsText,lumiText=o.lumiText)

plotRatio("pt_m",         "offJets_matchedJet",inFileData1, "Data 18", inFileData2, "Data 17",xTitle="p_{T}", outDir=o.outDir,binning=1,cmsText=o.cmsText,lumiText=o.lumiText,setLogy=1)
plotRatio("eta",          "offJets_matchedJet",inFileData1, "Data 18", inFileData2, "Data 17",xTitle="#eta", outDir=o.outDir,binning=1,cmsText=o.cmsText,lumiText=o.lumiText,setLogy=0)
plotRatio("DeepCSV_l",    "offJets_matchedJet",inFileData1, "Data 18", inFileData2, "Data 17",xTitle="DeepCSV", outDir=o.outDir,binning=1,cmsText=o.cmsText,lumiText=o.lumiText,setLogy=1)

plotRatio("pt_m",         "offJets_matchedCaloJet",inFileData1, "Data 18", inFileData2, "Data 17",xTitle="p_{T}", outDir=o.outDir,binning=1,cmsText=o.cmsText,lumiText=o.lumiText,setLogy=1)
plotRatio("eta",          "offJets_matchedCaloJet",inFileData1, "Data 18", inFileData2, "Data 17",xTitle="#eta", outDir=o.outDir,binning=1,cmsText=o.cmsText,lumiText=o.lumiText,setLogy=0)
plotRatio("DeepCSV_l",    "offJets_matchedCaloJet",inFileData1, "Data 18", inFileData2, "Data 17",xTitle="DeepCSV", outDir=o.outDir,binning=1,cmsText=o.cmsText,lumiText=o.lumiText,setLogy=1)


#
#  Offline Turnon curves:
#
effBinning=5

eff_CaloCSVvsDeepCSV_Data = makeEff("DeepCSV_l" ,    ["offJets_matchedCalocsvTag","offJets_matchedCalo"],inFileData1,binning=effBinning)
eff_CaloCSVvsDeepCSV_MC   = makeEff("DeepCSV_l" ,    ["offJets_matchedCalocsvTag","offJets_matchedCalo"],inFileData2  ,binning=effBinning)
eff_PFCSVvsDeepCSV_Data   = makeEff("DeepCSV_l" ,    ["offJets_matchedPFcsvTag",  "offJets_matched"]  ,inFileData1,binning=effBinning)
eff_PFCSVvsDeepCSV_MC     = makeEff("DeepCSV_l" ,    ["offJets_matchedPFcsvTag",  "offJets_matched"]  ,inFileData2  ,binning=effBinning)


eff_CaloDeepCSV_Data = makeEff("DeepCSV_l" ,    ["offJets_matchedCaloDeepcsvTag","offJets_matchedCalo"],inFileData1,binning=effBinning)
eff_CaloDeepCSV_MC   = makeEff("DeepCSV_l" ,    ["offJets_matchedCaloDeepcsvTag","offJets_matchedCalo"],inFileData2  ,binning=effBinning)
eff_PFDeepCSV_Data   = makeEff("DeepCSV_l" ,    ["offJets_matchedPFDeepcsvTag",  "offJets_matched"]  ,inFileData1,binning=effBinning)
eff_PFDeepCSV_MC     = makeEff("DeepCSV_l" ,    ["offJets_matchedPFDeepcsvTag",  "offJets_matched"]  ,inFileData2  ,binning=effBinning)



#reveff_DeepCSV_MC = {}
#reveff_DeepCSV_Data = {}
#for jetType in ["Calo","PF"]:
#    reveff_DeepCSV_MC[jetType] = {}
#    reveff_DeepCSV_Data[jetType] = {}
#    for op in ["Loose","Medium","Tight"]:
#        jetTypeDen = jetType if jetType == "Calo" else ""
#        
#        reveff_DeepCSV_MC  [jetType][op]   = makeEff("DeepCSV_l" ,    ["offJets"+op+"_matched"+jetType+"Jet",  "offJets_matched"+jetTypeDen+"Jet"]  ,inFileData2    ,binning=effBinning)
#        reveff_DeepCSV_Data[jetType][op]   = makeEff("DeepCSV_l" ,    ["offJets"+op+"_matched"+jetType+"Jet",  "offJets_matched"+jetTypeDen+"Jet"]  ,inFileData1  ,binning=effBinning)
#
#
#    drawComp("RevEff_"+jetType+"DeepCSV_All",[(reveff_DeepCSV_Data[jetType]["Loose"], "Loose (Data)",ROOT.kBlue),
#                                              (reveff_DeepCSV_MC[jetType]["Loose"], "Loose (MC)",ROOT.kBlue,24),
#                                              (reveff_DeepCSV_Data[jetType]["Medium"],"Medium (Data)",ROOT.kGreen+1),
#                                              (reveff_DeepCSV_MC[jetType]["Medium"],"Medium (MC)",ROOT.kGreen+1,24),
#                                              (reveff_DeepCSV_Data[jetType]["Tight"], "Tight (Data)",ROOT.kRed),
#                                              (reveff_DeepCSV_MC[jetType]["Tight"], "Tight (MC)",ROOT.kRed,24),
#                                              ]
#             ,yTitle="Efficiency",xTitle="Online ("+jetType+"-Jet) DeepCSV Value", otherText="",outDir=o.outDir,yMax=1.2,leg="special",cmsText=o.cmsText,lumiText=o.lumiText)
#



#   Data vs MC 
#drawComp("Eff_CaloCSVvsDeepCSV_DataVSMC",[(eff_CaloCSVvsDeepCSV_Data,"Data",ROOT.kBlue),(eff_CaloCSVvsDeepCSV_MC,"MC",ROOT.kRed)]
#         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText="Online WP: CSV > 0.5",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#drawComp("Eff_PFCSVvsDeepCSV_DataVSMC",[(eff_PFCSVvsDeepCSV_Data,"Data",ROOT.kBlue),(eff_PFCSVvsDeepCSV_MC,"MC",ROOT.kRed)]
#         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText="Online WP: CSV > 0.7",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


#drawComp("Eff_CaloDeepCSV_DataVSMC",[(eff_CaloDeepCSV_Data,"Data",ROOT.kBlue),(eff_CaloDeepCSV_MC,"MC",ROOT.kRed)]
#         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText="Online WP: DeepCSV > 0.17",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#drawComp("Eff_PFDeepCSV_DataVSMC",[(eff_PFDeepCSV_Data,"Data",ROOT.kBlue),(eff_PFDeepCSV_MC,"MC",ROOT.kRed)]
#         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText="Online WP: DeepCSV > 0.24",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


#
#   Calo vs PF
#



#drawComp("Eff_CaloVsPF_DeepCSV_Data",[(eff_CaloDeepCSV_Data,"Calo (Data)",ROOT.kBlue),(eff_PFDeepCSV_Data,"PF (Data)",ROOT.kRed)]
#         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText=["Online Calo WP: DeepCSV > 0.17","Online PF WP: DeepCSV > 0.24"],outDir=o.outDir,xStartOther=0.4,yStartOther=0.15,cmsText=o.cmsText,lumiText=o.lumiText)
#drawComp("Eff_CaloVsPF_DeepCSV_MC",[(eff_CaloDeepCSV_MC,"Calo (MC)",ROOT.kBlue),(eff_PFDeepCSV_MC,"PF (MC)",ROOT.kRed)]
#         ,yTitle="Efficiency",xTitle="DeepCSV Value of Jets", otherText=["Online Calo WP: DeepCSV > 0.17","Online PF WP: DeepCSV > 0.24"],outDir=o.outDir,xStartOther=0.4,yStartOther=0.15,cmsText=o.cmsText,lumiText=o.lumiText)


#   (Calo vs PF) x (Data vs MC )

drawComp("Eff_CaloVsPF_DeepCSVvsDeepCSV_DataVsMC",
         [(eff_CaloDeepCSV_Data,"Calo-Jet (Data 18)",ROOT.kBlue),
          (eff_CaloDeepCSV_MC,  "Calo-Jet (Data 17)  ",ROOT.kBlue, 24),
          (eff_PFDeepCSV_Data,  "PF-Jet   (Data 18)",ROOT.kRed),
          (eff_PFDeepCSV_MC,    "PF-Jet   (Data 17)  ",ROOT.kRed, 24),
          ],
         yTitle="Efficiency",xTitle="Offline DeepCSV Value", otherText=["Online Calo WP: DeepCSV > 0.17","Online PF WP: DeepCSV > 0.24"],
         outDir=o.outDir,xStartOther=0.4,yStartOther=0.15,cmsText=o.cmsText,lumiText=o.lumiText,xLeg=0.6,yLeg=0.7,xLumiStart=0.6)
#otherText="Online WP: DeepCSV > 0.63",outDir=o.outDir)



#
# Offline vs Online
#
csvBinning=3
# Deep CSV
offDeepCSV_Calo    = getHist(inFileData1,"offJets_matchedCalo",     "DeepCSV_l",binning=csvBinning,norm=1)
caloDeepCSV        = getHist(inFileData1,"offJets_matchedCaloJet",  "DeepCSV_l",binning=csvBinning,norm=1)
offDeepCSV_Calo_MC = getHist(inFileData2,  "offJets_matchedCalo",     "DeepCSV_l",binning=csvBinning,norm=1)
caloDeepCSV_MC     = getHist(inFileData2,  "offJets_matchedCaloJet",  "DeepCSV_l",binning=csvBinning,norm=1)

offDeepCSV_PF      = getHist(inFileData1,"offJets_matched",     "DeepCSV_l",binning=csvBinning,norm=1)
pfDeepCSV          = getHist(inFileData1,"offJets_matchedJet",  "DeepCSV_l",binning=csvBinning,norm=1)
offDeepCSV_PF_MC   = getHist(inFileData2,  "offJets_matched",     "DeepCSV_l",binning=csvBinning,norm=1)
pfDeepCSV_MC       = getHist(inFileData2,  "offJets_matchedJet",  "DeepCSV_l",binning=csvBinning,norm=1)


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
#

#offCSV_B_PF_MC      = getHist(inFileData2,"offJets_matched_B",     "CSVv2_l",binning=csvBinning,norm=0)
#offCSV_C_PF_MC      = getHist(inFileData2,"offJets_matched_C",     "CSVv2_l",binning=csvBinning,norm=0)
#offCSV_L_PF_MC      = getHist(inFileData2,"offJets_matched_L",     "CSVv2_l",binning=csvBinning,norm=0)
#
#offDeepCSV_B_PF_MC  = getHist(inFileData2,"offJets_matched_B",     "DeepCSV_l",binning=csvBinning,norm=0)
#offDeepCSV_C_PF_MC  = getHist(inFileData2,"offJets_matched_C",     "DeepCSV_l",binning=csvBinning,norm=0)
#offDeepCSV_L_PF_MC  = getHist(inFileData2,"offJets_matched_L",     "DeepCSV_l",binning=csvBinning,norm=0)
#
#
#offDeepCSV_B_Calo_MC  = getHist(inFileData2,"offJets_matchedCalo_B",     "DeepCSV_l",binning=csvBinning,norm=0)
#offDeepCSV_C_Calo_MC  = getHist(inFileData2,"offJets_matchedCalo_C",     "DeepCSV_l",binning=csvBinning,norm=0)
#offDeepCSV_L_Calo_MC  = getHist(inFileData2,"offJets_matchedCalo_L",     "DeepCSV_l",binning=csvBinning,norm=0)
#
#caloCSV_B_MC      = getHist(inFileData2,"offJets_matchedCaloJet_B",     "CSVv2_l",binning=csvBinning,norm=0)
#caloCSV_C_MC      = getHist(inFileData2,"offJets_matchedCaloJet_C",     "CSVv2_l",binning=csvBinning,norm=0)
#caloCSV_L_MC      = getHist(inFileData2,"offJets_matchedCaloJet_L",     "CSVv2_l",binning=csvBinning,norm=0)
#                                                           
#caloDeepCSV_B_MC  = getHist(inFileData2,"offJets_matchedCaloJet_B",     "DeepCSV_l",binning=csvBinning,norm=0)
#caloDeepCSV_C_MC  = getHist(inFileData2,"offJets_matchedCaloJet_C",     "DeepCSV_l",binning=csvBinning,norm=0)
#caloDeepCSV_L_MC  = getHist(inFileData2,"offJets_matchedCaloJet_L",     "DeepCSV_l",binning=csvBinning,norm=0)
#
#pfCSV_B_MC        = getHist(inFileData2,"offJets_matchedJet_B",       "CSVv2_l",binning=csvBinning,norm=0)
#pfCSV_C_MC        = getHist(inFileData2,"offJets_matchedJet_C",       "CSVv2_l",binning=csvBinning,norm=0)
#pfCSV_L_MC        = getHist(inFileData2,"offJets_matchedJet_L",       "CSVv2_l",binning=csvBinning,norm=0)
#                                                         
#pfDeepCSV_B_MC    = getHist(inFileData2,"offJets_matchedJet_B",     "DeepCSV_l",binning=csvBinning,norm=0)
#pfDeepCSV_C_MC    = getHist(inFileData2,"offJets_matchedJet_C",     "DeepCSV_l",binning=csvBinning,norm=0)
#pfDeepCSV_L_MC    = getHist(inFileData2,"offJets_matchedJet_L",     "DeepCSV_l",binning=csvBinning,norm=0)
#
#
#drawStackCompRatio("Calo_CSV_FlavorComp",(caloCSV,"Data"),
#                   [(caloCSV_L_MC,"Light Flavor",ROOT.kAzure-9),
#                    (caloCSV_C_MC,"Charm Jets",ROOT.kGreen+1),
#                    (caloCSV_B_MC,"B Jets",ROOT.kYellow)]
#                   ,yTitle="Normalized",xTitle="Online (Calo-Jet) CSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#
#drawStackCompRatio("Calo_DeepCSV_FlavorComp",(caloDeepCSV,"Data"),
#                   [(caloDeepCSV_L_MC,"Light Flavor",ROOT.kAzure-9),
#                    (caloDeepCSV_C_MC,"Charm Jets",ROOT.kGreen+1),
#                    (caloDeepCSV_B_MC,"B Jets",ROOT.kYellow)]
#                   ,yTitle="Normalized",xTitle="Online (Calo-Jet) DeepCSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#
#
#drawStackCompRatio("PF_CSV_FlavorComp",(pfCSV,"Data"),
#                   [(pfCSV_L_MC,"Light Flavor",ROOT.kAzure-9),
#                    (pfCSV_C_MC,"Charm Jets",ROOT.kGreen+1),
#                    (pfCSV_B_MC,"B Jets",ROOT.kYellow)]
#                   ,yTitle="Normalized",xTitle="Online (PF-Jet) CSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#
#drawStackCompRatio("PF_DeepCSV_FlavorComp",(pfDeepCSV,"Data"),
#                   [(pfDeepCSV_L_MC,"Light Flavor",ROOT.kAzure-9),
#                    (pfDeepCSV_C_MC,"Charm Jets",ROOT.kGreen+1),
#                    (pfDeepCSV_B_MC,"B Jets",ROOT.kYellow)]
#                   ,yTitle="Normalized",xTitle="Online (PF-Jet) DeepCSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#
#
#drawStackCompRatio("Off_CSV_FlavorComp",(offCSV_PF,"Data"),
#                   [(offCSV_L_PF_MC,"Light Flavor",ROOT.kAzure-9),
#                    (offCSV_C_PF_MC,"Charm Jets",ROOT.kGreen+1),
#                    (offCSV_B_PF_MC,"B Jets",ROOT.kYellow)]
#                   ,yTitle="Normalized",xTitle="Offline CSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#
#drawStackCompRatio("Off_DeepCSV_FlavorComp",(offDeepCSV_PF,"Data"),
#                   [(offDeepCSV_L_PF_MC,"Light Flavor",ROOT.kAzure-9),
#                    (offDeepCSV_C_PF_MC,"Charm Jets",ROOT.kGreen+1),
#                    (offDeepCSV_B_PF_MC,"B Jets",ROOT.kYellow)]
#                   ,yTitle="Normalized",xTitle="Offline DeepCSV",rTitle="Data/MC",setLogy=0,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#


#plot("pt","offJets",norm=1,logy=1)offJets_matched


#makeStack("OffJet_Pt",     "pt_m",     "offJets_matched_X",binning=2,xTitle="Offline Jet Pt", rTitle="Data/MC",logy=1,inFileData1=inFileData1,inFileData2=inFileData2,outDir=o.outDir,min=20,cmsText=o.cmsText,lumiText=o.lumiText)
#makeStack("OffJet_Eta",    "eta",      "offJets_matched_X",binning=1,xTitle="Offline Jet Eta",rTitle="Data/MC",logy=0,inFileData1=inFileData1,inFileData2=inFileData2,outDir=o.outDir,x_min=-3,x_max=3,cmsText=o.cmsText,lumiText=o.lumiText)
#makeStack("OffJet_Phi",    "phi",      "offJets_matched_X",binning=2,xTitle="Offline Jet Phi",rTitle="Data/MC",logy=0,inFileData1=inFileData1,inFileData2=inFileData2,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#makeStack("OffJet_DeepCSV","DeepCSV_l","offJets_matched_X",binning=csvBinning,xTitle="Offline Jet DeepCSV",rTitle="Data/MC",logy=0,inFileData1=inFileData1,inFileData2=inFileData2,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)
#makeStack("OffJet_CSV",    "CSVv2_l",    "offJets_matched_X",binning=csvBinning,xTitle="Offline Jet CSV",rTitle="Data/MC",logy=0,inFileData1=inFileData1,inFileData2=inFileData2,outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)



#ROOT.gStyle.SetPalette(1)
#oldMargin =  ROOT.gStyle.GetPadRightMargin()
#ROOT.gStyle.SetPadRightMargin(0.2)



#make2DComp("PFCompDeepCSV_Data",inFileData1,"offJets_matchedJet","deepcsv_vs_matched_deepcsv",xTitle="PF Jet Deep CSV",yTitle="Offline Jet Deep CSV")
#make2DComp("PFCompDeepCSV_MC",  inFileData2  ,"offJets_matchedJet","deepcsv_vs_matched_deepcsv",xTitle="PF Jet Deep CSV",yTitle="Offline Jet Deep CSV")

#make2DComp("PFCompCSVvsDeepCSV_Data",inFileData1,"offJets_matchedJet","csv_vs_matched_deepcsv",xTitle="Online (PF-Jet) CSV",yTitle="Offline DeepCSV",outDir=o.outDir)
#make2DComp("PFCompCSVvsDeepCSV_MC",  inFileData2,  "offJets_matchedJet","csv_vs_matched_deepcsv",xTitle="Online (PF-Jet) CSV",yTitle="Offline DeepCSV",outDir=o.outDir)
#
#make2DComp("PFCompCSV_Data",inFileData1,"offJets_matchedJet","csv_vs_matched_csv",xTitle="Online (PF-Jet) CSV",yTitle="Offline CSV",outDir=o.outDir)
#make2DComp("PFCompCSV_MC",  inFileData2,  "offJets_matchedJet","csv_vs_matched_csv",xTitle="Online (PF-Jet) CSV",yTitle="Offline CSV",outDir=o.outDir)
#
#
##make2DComp("CaloCompDeepCSV_Data",inFileData1,"offJets_matchedCaloJet","deepcsv_vs_matched_deepcsv",xTitle="Calo Jet Deep CSV",yTitle="Offline Jet Deep CSV")
##make2DComp("CaloCompDeepCSV_MC",  inFileData2,  "offJets_matchedCaloJet","deepcsv_vs_matched_deepcsv",xTitle="Calo Jet Deep CSV",yTitle="Offline Jet Deep CSV")
#
#make2DComp("CaloCompCSV_Data",inFileData1,"offJets_matchedCaloJet","csv_vs_matched_csv",xTitle="Online (Calo-Jet) CSV",yTitle="Offline CSV",outDir=o.outDir)
#make2DComp("CaloCompCSV_MC",  inFileData2,  "offJets_matchedCaloJet","csv_vs_matched_csv",xTitle="Online (Calo-Jet) CSV",yTitle="Offline CSV",outDir=o.outDir)
#
#make2DComp("CaloCompCSVvsDeepCSV_Data",inFileData1,"offJets_matchedCaloJet","csv_vs_matched_deepcsv",xTitle="Online (Calo-Jet) CSV",yTitle="Offline DeepCSV",outDir=o.outDir)
#make2DComp("CaloCompCSVvsDeepCSV_MC",  inFileData2,  "offJets_matchedCaloJet","csv_vs_matched_deepcsv",xTitle="Online (Calo-Jet) CSV",yTitle="Offline DeepCSV",outDir=o.outDir)
#

#ROOT.gStyle.SetPadRightMargin(oldMargin)



#makeInverseTurnOnAll("CaloDeepCSVEffwrtOff_All", "DeepCSV_l","offJetsWORKINGPOINT_matchedCaloJet", inFileData1,"Data",inFileData2,"MC",binning=1, otherText="Online Calo DeepCSV Eff wrt Offline",outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText)


#makeInverseTurnOnAll("PFDeepCSVEffwrtOff_All", "DeepCSV_l","offJetsWORKINGPOINT_matchedPFJet", inFileData1,"Data",inFileData2,"MC",binning=1, outDir=o.outDir,cmsText=o.cmsText,lumiText=o.lumiText,wpLine=0.24,wpTextY=0.525)




