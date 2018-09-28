import ROOT
from array import array

class eventData:
    def __init__(self):
        self.runNumber_arr          = array('f', [0.0] )
        self.eventNumber_arr        = array('f', [0.0] )
        self.FastPrimaryVertex_arr  = array('f', [0.0] )
        self.FPVPixelVertices_arr   = array('f', [0.0] )
        self.PixelVertices_arr      = array('f', [0.0] )
        self.VerticesPF_arr         = array('f', [0.0] )
        self.VerticesL3_arr         = array('f', [0.0] )
        self.VerticesOff_arr        = array('f', [0.0] )
        self.nPV_arr                = array('f', [0.0] )
        self.trueVertex_arr         = array('f', [0.0] )
    
    def SetBranchAddress(self,intree):
        intree.SetBranchAddress( 'run', self.runNumber_arr)
        intree.SetBranchAddress( 'evt', self.eventNumber_arr)
        intree.SetBranchAddress('FastPrimaryVertex',  self.FastPrimaryVertex_arr)
        intree.SetBranchAddress('FPVPixelVertices' ,  self.FPVPixelVertices_arr)
        intree.SetBranchAddress('PixelVertices'    ,  self.PixelVertices_arr)
        intree.SetBranchAddress('VerticesPF'       ,  self.VerticesPF_arr)
        intree.SetBranchAddress('VerticesL3'       ,  self.VerticesL3_arr)
        intree.SetBranchAddress('VerticesOff'      ,  self.VerticesOff_arr)
        intree.SetBranchAddress('nPV'              ,  self.nPV_arr)
        intree.SetBranchAddress('trueVertex'       ,  self.trueVertex_arr)


    def setEvent(self):
        self.runNumber          = self.runNumber_arr        [0]         
        self.eventNumber        = self.eventNumber_arr      [0]
        self.FastPrimaryVertex  = self.FastPrimaryVertex_arr[0]
        self.FPVPixelVertices   = self.FPVPixelVertices_arr [0]
        self.PixelVertices      = self.PixelVertices_arr    [0]
        self.VerticesPF         = self.VerticesPF_arr       [0]
        self.VerticesL3         = self.VerticesL3_arr       [0]
        self.VerticesOff        = self.VerticesOff_arr      [0]
        self.nPV                = self.nPV_arr              [0]
        self.trueVertex         = self.trueVertex_arr       [0]
