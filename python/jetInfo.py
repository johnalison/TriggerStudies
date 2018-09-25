import ROOT
from array import array


class jetInfo:

    def __init__(self,pt,eta,phi,mass): # add more here
        self.pt = pt
        self.eta = eta
        self.phi = phi
        self.mass = mass
        # and here....

        self.thisVector = ROOT.TLorentzVector()
        self.thisVector.SetPtEtaPhiM(pt,eta,phi,mass)
        

        


#
# Separate File ? 
#
class jetInfoDB:

    def __init__(self,name,maxLenght = 40):
        self.name = name
        
        self.num  = array('i', [0])
        self.pt   = array('f',[0]*maxLenght)
        self.eta  = array('f',[0]*maxLenght)
        self.phi  = array('f',[0]*maxLenght)
        self.mass = array('f',[0]*maxLenght)
        
        # Eventually self.trackInfo = 
        self.trackSip3dSig = ROOT.std.vector('vector<float>')()
        self.trackSip3dVal = ROOT.std.vector('vector<float>')()

    def SetBranchAddresses(self,intree):
        intree.SetBranchAddress( self.name+'_num',       self.num  )
        intree.SetBranchAddress( self.name+'_pt',        self.pt  )
        intree.SetBranchAddress( self.name+'_eta',       self.eta  )
        intree.SetBranchAddress( self.name+'_phi',       self.phi  )
        intree.SetBranchAddress( self.name+'_mass',         self.mass  )
        intree.SetBranchAddress( self.name+'_trackSip3dSig', self.trackSip3dSig)
        intree.SetBranchAddress( self.name+'_trackSip3dVal', self.trackSip3dVal)

    def getJets(self):
        # thisJet = jetData(iJet) 
        jetList = []
        for iJet in range(self.num[0]):
            jetList.append(jetInfo(self.pt[iJet], 
                                   self.eta[iJet],
                                   self.phi[iJet],
                                   self.mass[iJet],
                            )
                           )

        return jetList
