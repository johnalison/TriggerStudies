import optparse
parser = optparse.OptionParser()
parser.add_option('-i', '--inFileName',           dest="infileName",         default=None, help="Run in loop mode")
parser.add_option('-o', '--outFileName',          dest="outfileName",        default=None, help="Run in loop mode")
parser.add_option('-n', '--nevents',              dest="nevents",           default=None, help="Run in loop mode")
o, a = parser.parse_args()

import ROOT
from array import array

ROOT.gROOT.ProcessLine('.L Loader.C+')


inFile = ROOT.TFile(o.infileName,"READ")
print inFile

inFile.ls()
tree = inFile.Get("tree")
#tree.Print()
print tree

runNumber = array('f', [0.0] )
eventNumber = array('f', [0.0] )
pfJets_jetEta = array('f', [0,0,0,0,0,0] )
maxLenght = 40
pfJets_num = array('i', [0])
pfJets_pt = array('f',[0]*maxLenght)
pfJets_eta = array('f',[0]*maxLenght)
pfJets_phi = array('f',[0]*maxLenght)
pfJets_mass = array('f',[0]*maxLenght)
pfJets_trackSip3dSig = ROOT.std.vector('vector<float>')()
pfJets_trackSip3dVal = ROOT.std.vector('vector<float>')()



tree.SetBranchAddress( 'run', runNumber)
tree.SetBranchAddress( 'evt', eventNumber)
tree.SetBranchAddress( 'pfJets_num',       pfJets_num  )
tree.SetBranchAddress( 'pfJets_pt',        pfJets_pt  )
tree.SetBranchAddress( 'pfJets_eta',       pfJets_eta  )
tree.SetBranchAddress( 'pfJets_phi',       pfJets_phi  )
tree.SetBranchAddress( 'pfJets_mass',         pfJets_mass  )
tree.SetBranchAddress( 'pfJets_trackSip3dSig', pfJets_trackSip3dSig)
tree.SetBranchAddress( 'pfJets_trackSip3dVal', pfJets_trackSip3dVal)


#
# Make output ntuple
# 
f    = ROOT.TFile(o.outfileName,"recreate")
nEventThisFile = tree.GetEntries()
print( "Number of input events: %s" % nEventThisFile )

iEvent = 0


for entry in xrange( 0,nEventThisFile): # let's only run over the first 100 events for this example                                                         
    tree.GetEntry( entry )

    iEvent +=1
    
    if iEvent %10000 == 0:
        print "Processed .... ",iEvent,"Events"
    if o.nevents and (iEvent > int(o.nevents)):
        break


    print "RunNumber",runNumber[0],
    print "EventNumber",eventNumber[0]
    
    print pfJets_num[0], "vs",pfJets_trackSip3dSig.size()
    print pfJets_trackSip3dSig
    for iJet in range(pfJets_num[0]):
        thisVector = ROOT.TLorentzVector()
        thisVector.SetPtEtaPhiM(pfJets_pt[iJet],
                                pfJets_eta[iJet],
                                pfJets_phi[iJet],
                                pfJets_mass[iJet])
        
        print "\tjet (pt,eta,phi)",thisVector.Pt(),thisVector.Eta(),thisVector.Phi()

        
        for iTrk in range(pfJets_trackSip3dSig.at(iJet).size()):
            sig = pfJets_trackSip3dSig.at(iJet).at(iTrk)
            val = pfJets_trackSip3dVal.at(iJet).at(iTrk)
            print "\t\t sig (val,err)",sig,"(",val,val/sig,")"

    
        
