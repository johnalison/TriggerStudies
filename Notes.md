
Code is should be fairly self explainatory. 

Big picture:
============
  This code processes ntuples that are produces from CMSSW and makes a bunch of histograms
     - Actually take two different inputs: one for HLT and one for Offline
     - Matches events between the two using Run and Event numbers
     
  Outputs from CMSSW reco:  HLT and Offline are inputs to this code. 
     
  Almost all "analysis" that we do usese these histgrams. 
   eg: ratios of histograms in differnet folders can give efficiencies or fake rates as a function of any variable plotted

Overivew of output ROOT file produced
============

Bunch of directories: which contain historgrams 
   cutflow     - event-level cut flow (helpful for debugging)
   cutflowJets - offline Jet-level cut flow (helpful for debugging)
   Events - Event level plots
    - Event level plots
   *Muons  - plots of muons with various selection applied
   *Elecs  - plots of muons with various selection applied
   offJets* - plots of offline jets with various selection applied
   pfJets* - plots of online PF jets with various selection applied
   caloJets* - plots of online Calo jets with various selection applied
   offTracks* - plots of offline tracks with various selection applied
   *Vtx - plots of the primary vertex quantities 

Some more details:
   offJets - plots of all reconstructed offline jets
   offJets_matched - plots of the subset of offilne jets matched to HLT (PF) jets 
   offJets_matchedJet - plots of the HLT (PF) jets that matched the offline jets
   offJets_matched_L - offline_matched jets truth-matched to light-flavor ("_L")
   offJets_matched_B - offline_matched jets truth-matched to a b-quark ("_B")
   offJets_matched_C - offline_matched jets truth-matched to a c-quark ("_B")
   offJets_matchedJet_L - offline_matchedJet (ie the PF jet that matched the offline jet) truth-matched to light-flavor ("_L")
   offJets_mathcedPFcsvTag - offline jets that match a CSV btagged HLT PF jet (check code or offJets_mathcedPFcsvTagJet plots for PF csv cut value used) 
   offJets_mathcedPFcsvTagJet - CSV-btagged PF jets which matches an offline jet (check code or plots for PF csv cut value used) 
   offJets_mathcedPFDeepTag - offline jets that match a DeepCSV btagged HLT PF jet (check code or offJets_mathcedPFcsvTagJet plots for PF csv cut value used) 
   offJetsTight_matchedPFJet - Pf jets matching an offline jets btagged with tight DeepCSV working point 
   offJetsMedium_matchedPFJet - Pf jets matching an offline jets btagged with medium DeepCSV working point 
   offJetsLoose_matchedPFJet - Pf jets matching an offline jets btagged with loose DeepCSV working point 
   offJetsMedDeepCSV_matchedPFJet - offline jets pass medium DeepCSV btag that are matched to a PF jet
   offJetsMedDeepCSV_matchedPFDeepCSV - offline jets pass medium DeepCSV btag that are matched to a online DeepCSV btagged PF jet
   offJetsMedDeepCSV_matchedPFCSV  - offline jets pass medium DeepCSV btag that are matched to a online CSV btagged PF jet


   pfJets - plots of all reconstructed HLT PF jets   
   pfJets_matched - plots of all reconstructed HLT PF jets matched to an offline jet
   pfJets_matchedJet - plots of the offline-jet that was matched to the HLT PF jets
    (Note: pfJets_matchedJet should be the same as offJets_matched 
            same with pfJets_matched and offJets_matchedJets)

   offTracks - all offline tracks
   offTracks_matched - offline tracks matched to online tracks (in PF jets)
   offTracks_unmatched - offline tracks that are not matched to online tracks (in PF jets)

   pfTracks - all tracks in PF jets
   pfTracks_matched - tracks in pf jet that are matched to an offline track
   pfTracks_unmatched - tracks in pf jet that are not matched to an offline track

   offBTags - plots of tracks used as inputs to the btagging (in offline jets)
   offBTags_matched - subset of tracks ued as input to btagging matched to online track
   pfBTags -  plots of tracks used as inputs to the btagging (in PF jets)
   pfBTags_unmatched - subset of tracks used as inputs to the btagging (in PF jets) without an offline track match

Structure of an output directory:
  - histroams directly with in the folder are plots of jet-level quanties. 
  - subfolders are plots of objects assiated to the jet 
     eg: tracks / btagging inputs
  - btagging inputs include: Secodrary Vertex info / tracks (that pass btagging track slection)
  - some directories have more or less information depending on the detail string that is passed when the histograms are created
     (used to cut down on the output file size) 


Overivew of code used to produce the histograms:
-----------------------------------------------

-) Two packages used

  nTupleAnalysis - code not specific to the b-jet trigger studies
     baseclass used by several different contexts 

  TriggerStudies - code not specific to the b-jet trigger studies
     code that performs the trigger analysis

-) nTupleAnalysis 
    - has cointainers that hold object-level data 
    - has classes that define and fill object-level histograms
    - almost all histograms produced come from object-level histograms in ntupleanalysis
     eg: jetHists /trackHists ect 
    - advantage of using ntupleanalysis is can share code in different contexts.	 

    Data-objects: jetData /trackData ect.
       Idea:  Build data structures at the object-level that are easier to work with.
          - we read in "flat ntuples"
          - ntuples organized "by row" meaning have list of variables, entry for each object
             eg: jet_Pt = [pt_jet1, pt_jet2 , ... ] and jet_Eta = [eta_jet1, eta_jet2, ...] 
             Input grouped by jet-variable not by jet 
          - much more useful and physically motivated to group by jet instread of by variable 
              ie: can group "by column", where we create "jet-object" that is filled with each jet-variable for given jet
                 eg: jet1.pt = jet_Pt[1]  jet1.eta = jet_Eta[1] ect
          - whole point of *Data.cc classes is to do the "by row" -> "by column" conversion
          - result is a list of objects (simple c++ container classes) that have all variables associated to the given object
          - physics analysis uses these objects: make analyis logic / filling histograms cleaner/easier 
          - simple object-level data structures located in correspoding header files. eg: jet class defined in jetData.h
	  - point of nTupleAnalysis is to hide the details of the input ntuple from you
             All the thinking is happening at the object-level not the variable level

     Histogram classes: straight-foward

  No high-level thought happening in the baseclass. Just reading things in, and filling histograms
    No complicated selection no fancy physics calculation.  
 
-) Trigger Studies 

    WHere more of the finesse is happening. 
       - does selection
       - does object-matching
       - defines and fills histograms  

    -) Breakdown of input command:

Here is Example run script (input files on lxplus) 

> BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD /eos/cms/store/group/phys_btag/HLTPhaseII/INPUTS/26_02_20_NewOfflineLikeSequence/Offline/ttbar_PU200.root \
    --inputRAW /eos/cms/store/group/phys_btag/HLTPhaseII/INPUTS/26_02_20_NewOfflineLikeSequence/Online/ttbar_TrackingV0_PU200.root \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile hists_Phase2_TrackingV0_PU200_NewOff.root \
    --isMC \
    --doTracks \
    --nevents -1

 Calls a c++ executable and configures it with a python file and various input options

  BTagAnalyzer - name of c++ executible (source in /bin ) 
  TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py - configuration file written in python that gets passed to the c++ executable
  other lines are options passed to the python configuration.   
    --input* paths to the input files
    -o where to put the output histogram 
    --histFile name of output histogram


Executable lives in bin/BTagAnalyzer.cc
   Whole point of this code is to read-in the configuration and pass everythign to BTagAnlysis class (src/BTagAnalysis.cc) wihch does the work event loop
   

Configuration file in scripts/BTagAnalyzer_cfg.py
   read in the command line options, passes them to the c++ executable BTagAnalyzer

Code with the analyis is src/BTagAnalysis.cc
  Does three things
  - Creates eventData
  - Does event loop
  - Does object matching (truth labeling) 
  - Defines and fill histrams

  eventData:  (in TriggerStudies) class that loads the various objets-level offJet / PFJets ect. data  (deined  
    - simple structure that holds data for the whole event
    - meta-version of the object-level data classes in the nTupleAnalysis
    - configures which object-level data to hold
    - most of work forwarded to the nTupleAnalysis baseclass
    - eventData::update gets called every event, the calls the functions that do the "by-row" -> "by-columnn" conversion
    - hold vectors of the column sorted objects (offJets/ pfJets etc.)

  Histograms are defined  in the constructor (called once per job) 
   eg:    hOffJets_matched_B        = new nTupleAnalysis::jetHists("offJets_matched_B",       fs, "", jetDetailString );
       "offJets_matched_B" - specifies name in the output rootfile
        jetDetailString - string that encode the level of detail of plots produced  


  eventLopp also called once per job. 
     - loops over the events and actually does the analysis 

   All the action happens within this loop. (and subroutines within this loop) 
   Best to look at the code to see whats done. 

FAQ: 
-----
  - "Off" - specifies offline quantities
  - "PF" - specifies Online (HLT) "Particle-flow" quantities (Default) 
  - "Calo" - specifies Online (HLT) "Calo" quantities 
  - XXX_matched - is a directory of XXX objects matched to the correspoding HLT or Off object
      eg: offJets_matched = directory with plots of offline jets matched to online (PF) jets
          pfJets_matched = directory with plots of online PF jets matched to offline jets
  - XXX_matchedJet - is a directory of the objects that matched the XXX objects
       eg: offJets_matchedJet = directory with plots of online PF jets that were matched to the offline jets
           pfJets_matchedJet = directory with plots of offline jets that were matched to the online PF jets
  - isProbe: is a ttbar tag-and-probe selection 
  - Histogram postfixes like  "_l", "_m" "_s", ect are used when plotting same variable with differnet range: 
     eg: pt_l / pt_m / pt_s  could have ranges
         _l  (Large) 0 - 1000
         _m  (medium) 0 - 500
         _s  (medium) 0 - 100

  - Directors with postscripts "_L" / "_C", and "_B" refers to truth-matched jets
     "_L" - only light-flavour
     "_B" - only bjets
     "_C" - only chram-jets

  - Truth matching: All truth mathcing is done via offline jet lables. 
     ie: truth label of an HLT jet is the truth label of the matching offline-jet