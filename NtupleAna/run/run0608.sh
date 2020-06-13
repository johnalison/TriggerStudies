BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputRAW /uscms/home/runxuanw/nobackup/HLTOnly/CMSSW_11_1_0_pre6/src/inputFiles_2018B_RAW_All.root \
    -o /uscms/home/runxuanw/nobackup/HLTOnly/CMSSW_11_1_0_pre6/src \
    -y 2018 \
    --histogramming 1 \
    --histFile hists_06092018B.root \
    --isMC \
    --doTracks \
    --nevents -1 \
    ## --nnConfig RecoBTag/Combined/data/DeepCSV_PhaseII.json \
