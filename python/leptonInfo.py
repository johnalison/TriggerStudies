import ROOT
from array import array


class LeptonData:

    def __init__(self,pt,eta,phi,mass):
        self.pt = pt
        self.eta = eta
        self.phi = phi
        self.mass = mass

        self.vec = ROOT.TLorentzVector()
        self.vec.SetPtEtaPhiM(pt,eta,phi,mass)


        


#
# Separate File ? 
#
class LeptonDataHandler:

    def __init__(self,name,maxLenght = 40):
        self.name = name
        
        self.num     = array('i', [0])
        self.pt      = array('f',[0]*maxLenght)
        self.eta     = array('f',[0]*maxLenght)
        self.phi     = array('f',[0]*maxLenght)
        self.mass    = array('f',[0]*maxLenght)

    def SetBranchAddress(self,intree):
        intree.SetBranchAddress( self.name+'_num',       self.num  )
        intree.SetBranchAddress( self.name+'_pt',        self.pt  )
        intree.SetBranchAddress( self.name+'_eta',       self.eta  )
        intree.SetBranchAddress( self.name+'_phi',       self.phi  )
        intree.SetBranchAddress( self.name+'_mass',      self.mass  )

    def getLeps(self):

        lepList = []
        for iLep in range(self.num[0]):
            lepList.append(LeptonData(self.pt  [iLep], 
                                      self.eta [iLep],
                                      self.phi [iLep],
                                      self.mass[iLep],
                                      )
                           )

        return lepList
