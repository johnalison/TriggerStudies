
# TriggerStudies Plotting

# Clone git ROOTHelp (This has to be done at the same level in the dir structure as TriggerStudies
> git clone git@github.com:johnalison/ROOTHelp.git

# eg: 
> ls basDirName 
>  TriggerStudies
>  ROOTHelp


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

> python ../plotting/MakeTrackEffs.py --input [Histograms with Trks ]  --out [Output Directory Name]

#
# Compare Track Level Efficiency plots (from two different samples)
#

> python ../plotting/MakeTrackEffsComp.py  --input1 [Histograms with Trks Sample 1] --name1 [Name 1]  --input2 [Histograms with Trks Sample 2] --name2 [Name 2] --out [Output Directory Name]