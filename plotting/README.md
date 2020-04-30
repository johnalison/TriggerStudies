
# TriggerStudies Plotting

# Clone git ROOTHelp (This has to be done at the same level in the dir structure as TriggerStudies
> git clone git@github.com:johnalison/ROOTHelp.git

# eg: 
> ls basDirName 
>  TriggerStudies
>  ROOTHelp

# Setup the ROOT Help 
# source ROOTHelp/setup.sh

# The plot making is then done in a subdir of TriggerStudies
# eg 

> mkdir makePDFs
> cd makePDFs

#
# Jet Level Data/MC Comparisons
#  (ROOT Histograms -> pdfs)

> python ../plotting/JetLevelPlots.py --inputData [Histograms from Data] --inputMC [Histograms from MC]  --output [Output Directory Name]

#
# Track Level Efficiency plots (from one sample)
#

> python ../plotting/MakeTrackEffs.py     --input [Histograms with Trks ]  --out [Output Directory Name]
> python ../plotting/MakeBTagTrackEffs.py --input [Histograms with Trks ]  --out [Output Directory Name]

#
# Compare Track Level Efficiency plots (from two different samples)
#

> python ../plotting/MakeTrackEffsComp.py  --input1 [Histograms with Trks Sample 1] --name1 [Name 1]  --input2 [Histograms with Trks Sample 2] --name2 [Name 2] --out [Output Directory Name]


#
#  Compare histrograms from two samples (uses track info)
#
> python ../plotting/BJetTrigValidationFileComp.py [Histograms from Sample 1] [Histograms from Sample 2]   --model BasicComp --out [Output DirName] --labName [Sample Label 1,Sample Label 2]

#
#  To Make Roc Curves
#
python ../plotting/makeRocCurves.py --in [Input MC File] --out [Output Directory]

#
#  Make plots overlaying Offline and HLT and B-Q vs L-Q
#
> python ../plotting/HLTvsOff_BvL.py --input [Histograms with tracks MC]  --out [Output Name]

#
# To make plots of pt and eta efficienies for the different tracking algos (note need AODs for the algo enum)
#
python ../plotting/PlotAlgoStudy.py [Histograms with track algo info filled] --out [Output Name]



#
#  To make plots of the online btagging eff wrt offline (and the output root file for analysis)
#
python TriggerStudies/plotting/MakeEffOnlineWrtOffline.py --input1  2018/hists_Data18BCD_wTrks.root --name1 Data --input2  2017/hists_ttbarMC_runBCDEF_2017.root    --name2 MC --out 2018/MakeEffOnlineWrtOfflineTest

#
#  To make plot of the PV 
#
python TriggerStudies/plotting/PlotPVStudy.py [input Hist] --out [Output Name]


#
# To Make plots of the deltas between matched online/offline jets and btagging inputs
#
python TriggerStudies/plotting/PlotsDeltas.py [input Hist] --out [Output Name]


