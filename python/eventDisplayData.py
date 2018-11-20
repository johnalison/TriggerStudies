import json

class EventDisplayData:

    def __init__(self,name):
        self.name = name
        self.nDisplays = 0

        self.eventDisplayData = {}
        self.eventDisplayData["pfJet"]  = {}
        self.eventDisplayData["pfJet_Trks"]  = {}

        self.eventDisplayData["offMatchJet"]  = {}

        self.eventDisplayData["offJet"]  = {}
        self.eventDisplayData["offJet_Trks"]  = {}
        self.eventDisplayData["offJet_TrksNoMatch"]  = {}
        self.eventDisplayData["offJet_TrksMatch"]  = {}

        self.eventDisplayData["offJetAll"]  = {}
        self.eventDisplayData["offJetAll_Trks"]  = {}

    def newEvent(self):
        self.nDisplays += 1
        self.eventDisplayData["pfJet"][int(self.nDisplays)] = []
        self.eventDisplayData["pfJet_Trks"][int(self.nDisplays)] = []

        self.eventDisplayData["offMatchJet"][int(self.nDisplays)] = []

        self.eventDisplayData["offJet"][int(self.nDisplays)] = []
        self.eventDisplayData["offJet_Trks"][int(self.nDisplays)] = []
        self.eventDisplayData["offJet_TrksMatch"][int(self.nDisplays)] = []
        self.eventDisplayData["offJet_TrksNoMatch"][int(self.nDisplays)] = []

        self.eventDisplayData["offJetAll"][int(self.nDisplays)] = []
        self.eventDisplayData["offJetAll_Trks"][int(self.nDisplays)] = []


    def AddJet(self, jType, jData, doTracks=False):
        self.eventDisplayData[jType][int(self.nDisplays)].append((jData.vec.Eta(),jData.vec.Phi(),jData.vec.Pt()))

        if doTracks:
            for tData in jData.tracks:
                self.AddTrk(jType+"_Trks",tData)

    def AddTrk(self, tType, tData):
        self.eventDisplayData[tType][int(self.nDisplays)].append((tData.eta,tData.phi,tData.momentum))

    def Write(self):
        with open('Events_'+self.name+'.txt', 'w') as outfile:  
            json.dump(self.eventDisplayData, outfile)    
