
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


# Jet Level Data/MC Comparisons
#  (ROOT Histograms -> pdfs)

> python ../plotting/JetLevelPlots.py --inputData [Histograms from Data] --inputMC [Histograms from MC]  --output [Output Directory Name]