
Code is should be fairly self explanatory. 

Big picture:
============

This code processes ntuples that are produced from CMSSW and makes a bunch of histograms.
   >  Actually takes two different inputs: one for HLT and one for Offline

   >  Matches events between the two using Run and Event numbers
     
  Outputs from CMSSW reco:  HLT and Offline are inputs to this code. 
     
 Almost all "analysis" that we do uses these histograms.
   >  eg: ratios of histograms in different folders can give efficiencies or fake rates as a function of any variable plotted

Overview of output ROOT file produced
=======================================

ROOT file has a bunch of directories which contain histograms

####  <ins>Directories:</ins>
  - `cutflow`     - event-level cut flow (helpful for debugging)
  - `cutflowJets` - offline Jet-level cut flow (helpful for debugging)
  - `Events` - Event level plots
  - `*Muons`  - plots of muons with various selection applied
  - `*Elecs`  - plots of electrons with various selection applied
  - `offJets*` - plots of offline jets with various selection applied
  - `pfJets*` - plots of online PF jets with various selection applied
  - `caloJets*` - plots of online Calo jets with various selection applied
  - `offTracks*` - plots of offline tracks with various selection applied
  - `*Vtx` - plots of the primary vertex quantities 

####  <ins>Some more details:</ins>
#####  <ins>jet-level:</ins>
   - `offJets` - plots of all reconstructed offline jets
   - `offJets_matched` - plots of the subset of offline jets matched to HLT (PF) jets 
   - `offJets_matchedJet` - plots of the HLT (PF) jets that matched the offline jets
   - `offJets_matched_L` - `offline_matched jets` truth-matched to light-flavor (`_L`)
   - `offJets_matched_B` - `offline_matched jets` truth-matched to a b-quark (`_B`)
   - `offJets_matched_C` - `offline_matched jets` truth-matched to a c-quark (`_C`)
   - `offJets_matchedJet_L` - offline_matchedJet (ie the PF jet that matched the offline jet) truth-matched to light-flavor (`_L`)
   - `offJets_mathcedPFcsvTag` - offline jets that match a CSV btagged HLT PF jet (check code or offJets_mathcedPFcsvTagJet plots for PF csv cut value used) 
   - `offJets_mathcedPFcsvTagJet` - CSV-btagged PF jets which matches an offline jet (check code or plots for PF csv cut value used) 
   - `offJets_mathcedPFDeepTag` - offline jets that match a DeepCSV btagged HLT PF jet (check code or offJets_mathcedPFcsvTagJet plots for PF csv cut value used) 
   - `offJetsTight_matchedPFJet` - PF jets matching an offline jets btagged with tight DeepCSV working point 
   - `offJetsMedium_matchedPFJet` - PF jets matching an offline jets btagged with medium DeepCSV working point 
   - `offJetsLoose_matchedPFJet` - PF jets matching an offline jets btagged with loose DeepCSV working point 
   - `offJetsMedDeepCSV_matchedPFJet` - offline jets pass medium DeepCSV btag that are matched to a PF jet
   - `offJetsMedDeepCSV_matchedPFDeepCSV` - offline jets pass medium DeepCSV btag that are matched to a online DeepCSV btagged PF jet
   - `offJetsMedDeepCSV_matchedPFCSV`  - offline jets pass medium DeepCSV btag that are matched to a online CSV btagged PF jet
   - `pfJets` - plots of all reconstructed HLT PF jets   
   - `pfJets_matched` - plots of all reconstructed HLT PF jets matched to an offline jet
   - `pfJets_matchedJet` - plots of the offline-jet that was matched to the HLT PF jets
    (Note: pfJets_matchedJet should be the same as offJets_matched 
            same with pfJets_matched and offJets_matchedJets)


#####  <ins>track-level:</ins>

  - `offTracks` - all offline tracks
  - `offTracks_matched` - offline tracks matched to online tracks (in PF jets)
  - `offTracks_unmatched` - offline tracks that are not matched to online tracks (in PF jets)
  - `pfTracks` - all tracks in PF jets
  - `pfTracks_matched` - tracks in PF jet that are matched to an offline track
  - `pfTracks_unmatched` - tracks in PF jet that are not matched to an offline track
  - `offBTags` - plots of tracks used as inputs to the btagging (in offline jets)
  - `offBTags_matched` - subset of tracks used as input to btagging matched to online track
  - `pfBTags` -  plots of tracks used as inputs to the btagging (in PF jets)
  - `pfBTags_unmatched` - subset of tracks used as inputs to the btagging (in PF jets) without an offline track match

#### Structure of an output directory:
  - histograms directly with in the folder are plots of jet-level quantities. 
  - sub-folders are plots of objects associated to the jet 
     eg: tracks / btagging inputs
  - btagging inputs include: Secodrary Vertex info / tracks (that pass btagging track selection)
  - some directories have more or less information depending on the detail string that is passed when the histograms are created
     (used to cut down on the output file size) 


Overview of code used to produce the histograms:
===============================================

Two packages used

  `nTupleAnalysis` - code not specific to the b-jet trigger studies.
    Baseclass used by several different contexts.

  `TriggerStudies` - code specific to the b-jet trigger studies.
     This is the code that performs the trigger analysis.

## nTupleAnalysis
  
- Has containers that hold object-level data ([Data-objects](###Data-objects))
- Has classes that define and fill object-level histograms ([Histogram-classes](###Histogram-classes))
- Almost all histograms produced come from object-level histograms in `nTupleAnalysis`
     >  eg: `jetHists` /`trackHists` ect 
- advantage of using `nTupleAnalysis` is can share code in different contexts.	 



### Data objects

<ins>**Idea:**</ins>  Build data structures at the object-level that are easier to work with.

   >  jetData.cc , trackData.cc ect.

 - We read in "flat ntuples"
 - ntuples organized "by row" meaning have list of variables, entry for each object
   > eg: jet_Pt = [pt_jet1, pt_jet2 , ... ] and jet_Eta = [eta_jet1, eta_jet2, ...] 

   >  Input grouped by jet-variable not by jet 
- Much more useful and physically motivated to group by jet instead of by variable 
   > ie: can group "by column", where we create "jet-object" that is filled with each jet-variable for given jet
 
   > eg: jet1.pt = jet_Pt[1]  jet1.eta = jet_Eta[1] ect
- Whole point of `*Data.cc` classes is to do the "by row" -> "by column" conversion
- Result is a list of objects (simple c++ container classes) that have all variables associated to the given object
- Downstream physics analysis then uses these objects: make analysis logic and filling histograms cleaner/easier 
- Simple object-level data structures located in corresponding header files. eg: jet class defined in `jetData.h`
- Point of `nTupleAnalysis` is to hide the details of the input ntuple from you
   > All the thinking is happening at the object-level not the variable level

### Histogram classes
   > straight-forward

**nTupleAnalysis take away**:   No high-level thought happening in the baseclass. Just reading things in, and filling histograms.
  No complicated selection no fancy physics calculation.  
 

## TriggerStudies 
This is where more of the finesse is happening. 
- does selection
- does object-matching
- defines and fills histograms  

### Breakdown of input command:

Here is Example run script (input files on lxplus) 

```bash
 BTagAnalyzer TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py \
    --inputAOD /eos/cms/store/group/phys_btag/HLTPhaseII/INPUTS/26_02_20_NewOfflineLikeSequence/Offline/ttbar_PU200.root \
    --inputRAW /eos/cms/store/group/phys_btag/HLTPhaseII/INPUTS/26_02_20_NewOfflineLikeSequence/Online/ttbar_TrackingV0_PU200.root \
    -o $PWD \
    -y phase2 \
    --histogramming 1 \
    --histFile hists_Phase2_TrackingV0_PU200_NewOff.root \
    --isMC \
    --doTracks \
    --nevents -1
```

This command calls a c++ executable and configures it with a python file and various command line input options.

- `BTagAnalyzer` - name of c++ executable (source in /bin ) 
- `TriggerStudies/NtupleAna/scripts/BTagAnalyzer_cfg.py` - configuration file written in python that gets passed to the c++ executable
-  other lines are options passed to the python configuration.   
    >  --input* paths to the input files
  
    >  -o where to put the output histogram 
  
    >  --histFile name of output histogram


**The executable lives in `bin/BTagAnalyzer.cc`**
   Whole point of this code is to read-in the configuration and pass everything to `BTagAnlysis` class (`src/BTagAnalysis.cc`) which does the work event loop.
   

**Configuration file `scripts/BTagAnalyzer_cfg.py`**
   Reads in the command line options, passes them to the c++ executable `BTagAnalyzer`

Code with the analysis is `src/BTagAnalysis.cc`
Does four things
  - Creates `eventData`
  - Does the event loop
  - Does object matching (and truth labeling) 
  - Defines and fills histograms

### eventData: 
Class in `TriggerStudies` package  that loads the various objects-level offJet / PFJets ect. data  (deined  
- simple structure that holds data for the whole event
- meta-version of the object-level data classes in the `nTupleAnalysis`
- configures which object-level data to hold
- most of work forwarded to the `nTupleAnalysis` baseclass
- `eventData::update` gets called every event, 
   > the calls the functions that do the "by-row" -> "by-column" conversion
- hold vectors of the column-sorted objects (`offJets`/ `pfJets` etc.)

### Histograms 
Histograms are defined in the constructor (called once per job) 
eg:
```c++
hOffJets_matched_B        = new nTupleAnalysis::jetHists("offJets_matched_B",       fs, "", jetDetailString );
```
here:
- `offJets_matched_B` - specifies directory name in the output rootfile
- `jetDetailString` - is a string that encodes the level of detail of plots produced  


### eventLopp 
Also called once per job. 
 - loops over the events and actually does the analysis 

All the action happens within this loop. (and subroutines within this loop) 
Best to look at the code to see whats done. 

