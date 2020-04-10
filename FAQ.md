FAQ: 
====
- "off" - specifies offline quantities
- "PF" - specifies Online (HLT) "Particle-flow" quantities (Default) 
- "Calo" - specifies Online (HLT) "Calo" quantities 
- `XXX_matched` - is a directory of `XXX` objects matched to the corresponding HLT or Off object
    > `offJets_matched` = directory with plots of offline jets that have been matched to online (PF) jets

    >  `pfJets_matched` = directory with plots of online PF jets that have been matched to offline jets
- `XXX_matchedJet` - is a directory of the objects that matched the `XXX` objects
    > `offJets_matchedJet` = directory with plots of online PF jets that were matched to the offline jets

    > `pfJets_matchedJet` = directory with plots of offline jets that were matched to the online PF jets
- `isProbe`: is a ttbar tag-and-probe selection 
- Histogram post-fixes like  `_l`, `_m` `_s`, ect are used when plotting same variable with different range: 
   > eg: pt_l / pt_m / pt_s  could have ranges
   
   >    `pt_l`  ("Large") has pt range 0 - 1000 GeV

   >    `pt_m`  ("Medium") has pt range 0 - 500 GeV

   >    `pt_s`  ("Small") has pt range 0 - 100 GeV

- Directors with postscripts `_L` / `_C`, and `_B` refers to truth-matched jets
   - `_L` - only light-flavour
   - `_B` - only bjets
   - `_C` - only charm-jets

- **Truth matching:** All truth matching is done via offline jet labels. 
   ie: truth label of an HLT jet is the truth label of the matching offline-jet