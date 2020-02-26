# BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
#     --inputAOD INPUTS/newGT_v1/Offline/RelValCMSSW11/ttbar.root \
#     --inputRAW INPUTS/newGT_v1/Online/RelValCMSSW11/ttbar_TrackV2.root  \
#     -o $PWD \
#     -y phase2 \
#     --histogramming 1 \
#     --histFile OUTPUT/newGT_v1/RelValCMSSW11/ttbar_TrackV2.root \
#     --isMC \
#     --doTracks \
#     --nevents -1

# BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
#     --inputAOD INPUTS/newGT_v1/Offline/RelValCMSSW11_0_0/ttbar_NoPU.root \
#     --inputRAW INPUTS/newGT_v1/Online/RelValCMSSW11_0_0/ttbar_NoPU.root  \
#     -o $PWD \
#     -y phase2 \
#     --histogramming 1 \
#     --histFile OUTPUT/newGT_v1/RelValCMSSW11_0_0/ttbar_NoPU.root \
#     --isMC \
#     --doTracks \
#     --nevents -1

# BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
#     --inputAOD INPUTS/newGT_v1/Offline/CMSSW11_NewGT_v1/ttbar.root \
#     --inputRAW INPUTS/newGT_v1/Online/CMSSW11_NewGT_v1/ttbar_TrackV2_crab.root  \
#     -o $PWD \
#     -y phase2 \
#     --histogramming 1 \
#     --histFile OUTPUT/newGT_v1/CMSSW11_NewGT_v1/ttbar_TrackV2_crab.root \
#     --isMC \
#     --doTracks \
#     --nevents -1
#
# BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
#     --inputAOD INPUTS/newGT_v1/Offline/CMSSW11_NewGT_v1/ttbar_NoPU.root \
#     --inputRAW INPUTS/newGT_v1/Online/CMSSW11_NewGT_v1/ttbar_TrackV2_NoPU_crab.root  \
#     -o $PWD \
#     -y phase2 \
#     --histogramming 1 \
#     --histFile OUTPUT/newGT_v1/CMSSW11_NewGT_v1/ttbar_TrackV2_NoPU_crab.root \
#     --isMC \
#     --doTracks \
#     --nevents -1
#
# BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
#     --inputAOD INPUTS/newGT_v1/Offline/CMSSW11_NewGT_v1/ttbar.root \
#     --inputRAW INPUTS/newGT_v1/Online/CMSSW11_NewGT_v1/ttbar_TrackV0_crab.root  \
#     -o $PWD \
#     -y phase2 \
#     --histogramming 1 \
#     --histFile OUTPUT/newGT_v1/CMSSW11_NewGT_v1/ttbar_TrackV0_crab.root \
#     --isMC \
#     --doTracks \
#     --nevents -1
#    --inputAOD root://cmsxrootd.fnal.gov//store/user/jda102//BTagNTuples/2017/crab_projects_v2/MuonEG/Run2017B-31Mar2018-v1/190712_205650/inputFiles_2017B_MINIAOD_All.root \



BTagAnalyzer ../scripts/BTagAnalyzer_cfg.py \
    --inputAOD INPUTS/30_01_20_FullRelValStudy/Offline/ttbar_PU200_correctGT.root \
    --inputRAW INPUTS/30_01_20_FullRelValStudy/Online/ttbar_PU200_TrackingV0_skimTracks_correctGT.root  \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile OUTPUT/30_01_20_FullRelValStudy/ttbar_PU200_TrackingV0_skimTracks_correctGT.root \
    --isMC \
    --doTracks \
    --nevents -1
