BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputRAW /uscms/home/runxuanw/nobackup/HLTOnly/CMSSW_11_1_0_pre6/src/Inputs/JetTree_mc_All_0p9.root \
    -o /uscms/home/runxuanw/nobackup/HLTOnly/CMSSW_11_1_0_pre6/src \
    -y 2018 \
    --histogramming 1 \
    --histFile hists_0616.root \
    --isMC \
    --doTracks \
    --nevents -1 \
    --debug True
