BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
    --inputAOD INPUT/25_05_20_HLTTDR/Offline/ttbar_NoPU.root \
    --inputRAW INPUT/25_05_20_HLTTDR/Online/ttbar_NoPU_TrackingV0.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile OUTPUT/25_05_20_HLTTDR/ttbar_NoPU_TrackingV0.root \
    --isMC \
    --doTracks \
    --nevents -1

BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
    --inputAOD INPUT/25_05_20_HLTTDR/Offline/ttbar_NoPU.root \
    --inputRAW INPUT/25_05_20_HLTTDR/Online/ttbar_NoPU_TrackingV2.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile OUTPUT/25_05_20_HLTTDR/ttbar_NoPU_TrackingV2.root \
    --isMC \
    --doTracks \
    --nevents -1

BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
    --inputAOD INPUT/25_05_20_HLTTDR/Offline/ttbar_NoPU.root \
    --inputRAW INPUT/25_05_20_HLTTDR/Online/ttbar_NoPU_TrackingV6.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile OUTPUT/25_05_20_HLTTDR/ttbar_NoPU_TrackingV6.root \
    --isMC \
    --doTracks \
    --nevents -1

BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
    --inputAOD INPUT/25_05_20_HLTTDR/Offline/ttbar_NoPU.root \
    --inputRAW INPUT/25_05_20_HLTTDR/Online/ttbar_NoPU_TrackingV6_skimmedTracks.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile OUTPUT/25_05_20_HLTTDR/ttbar_NoPU_TrackingV6_skimmedTracks.root \
    --isMC \
    --doTracks \
    --nevents -1

BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
    --inputAOD INPUT/25_05_20_HLTTDR/Offline/ttbar_NoPU.root \
    --inputRAW INPUT/25_05_20_HLTTDR/Online/ttbar_NoPU_TrackingV0_TICL.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile OUTPUT/25_05_20_HLTTDR/ttbar_NoPU_TrackingV0_TICL.root \
    --isMC \
    --doTracks \
    --nevents -1

BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
    --inputAOD INPUT/25_05_20_HLTTDR/Offline/ttbar_NoPU.root \
    --inputRAW INPUT/25_05_20_HLTTDR/Online/ttbar_NoPU_TrackingV2_TICL.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile OUTPUT/25_05_20_HLTTDR/ttbar_NoPU_TrackingV2_TICL.root \
    --isMC \
    --doTracks \
    --nevents -1

BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
    --inputAOD INPUT/25_05_20_HLTTDR/Offline/ttbar_NoPU.root \
    --inputRAW INPUT/25_05_20_HLTTDR/Online/ttbar_NoPU_TrackingV6_TICL.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile OUTPUT/25_05_20_HLTTDR/ttbar_NoPU_TrackingV6_TICL.root \
    --isMC \
    --doTracks \
    --nevents -1

BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
    --inputAOD INPUT/25_05_20_HLTTDR/Offline/ttbar_NoPU.root \
    --inputRAW INPUT/25_05_20_HLTTDR/Online/ttbar_NoPU_TrackingV6_TICL_skimmedTracks.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile OUTPUT/25_05_20_HLTTDR/ttbar_NoPU_TrackingV6_TICL_skimmedTracks.root \
    --isMC \
    --doTracks \
    --nevents -1
