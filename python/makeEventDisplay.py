#!/usr/bin/python2.7
import ROOT 
import json
ROOT.gROOT.SetBatch(True)

import optparse
parser = optparse.OptionParser()
parser.add_option('-o', '--outputDir',           dest="outputDir",          default=False, help="Run in loop mode")
parser.add_option('-i', '--inputFile',           dest="inputFile",          default=False, help="Run in loop mode")
o, a = parser.parse_args()


with open(o.inputFile) as json_file:  
    data = json.load(json_file)

nEvents = len(data["offJet"])


pi=3.1415926536
import os
if not os.path.isdir(o.outputDir):
    print("making",o.outputDir)
    os.mkdir(o.outputDir)


#print len(JetData)
#print len(JetData[str(1)])
#print len(TrkData)
#print len(TrkData[str(1)])



def makeOneCircle(eta,phi,r,color,fillColor=None,linestyle=ROOT.kSolid):
    circle =  ROOT.TEllipse (eta,phi,r,r)
    circle .SetLineColor(color)
    circle .SetLineStyle(linestyle)

    if fillColor:
        circle .SetFillColor(fillColor)
    else:
        circle .SetFillStyle(0)

    circle.Draw("same"); 
    return circle

def makeCircle(eta,phi,r,color,fillColor=None,linestyle=ROOT.kSolid):
    output = []
    output.append(makeOneCircle(eta,phi,r,color,fillColor=fillColor,linestyle=linestyle))

    if phi+r > pi: output.append(makeOneCircle(eta,phi-2*3.14,r,color,fillColor=fillColor,linestyle=linestyle))
    if phi-r < pi: output.append(makeOneCircle(eta,phi+2*3.14,r,color,fillColor=fillColor,linestyle=linestyle))
        
    return output

def makeX(eta,phi,color):

    text = ROOT.TText()
    text. SetTextSize(0.03)
    text. SetTextAlign(21)
    text. SetTextColor(color)
    text.DrawText(eta, phi, "x");

    #output.append(makeOneCircle(eta,phi,r,color,fillColor=None,linestyle=linestyle))

    return text



def makeEvent(num):

    canEvent = ROOT.TCanvas("canEvent"+str(num),"canEvent"+str(num),int(2000*10/6.2),2000)
    canEvent.cd()

    hAxis = ROOT.TH2F("axis","Axis;eta;phi",2,-5,5,2,-pi,pi)
    hAxis.SetStats(0)
    hAxis.Draw()

    hAxisJet = ROOT.TH2F("axisJet","AxisJet;eta;phi",2,-0.5,0.5,2,-0.5,0.5)
    hAxisJet.SetStats(0)



    output = []
    
    jetNum = 0
    for j in data["offJet"][str(num)]:
        etaPos = j[0]
        phiPos = j[1]
        output.append(makeCircle(etaPos,phiPos, 0.4, ROOT.kRed))


        canJet = ROOT.TCanvas("canJet_"+str(num)+"_"+str(jetNum),"canJet_"+str(num)+"_"+str(jetNum),1000,1000)
        jetNum += 1

        canJet.cd()
        hAxisJet.Draw()
        output.append(makeCircle(etaPos-etaPos,phiPos-phiPos, 0.4, ROOT.kRed))


        for j in data["offMatchJet"][str(num)]:
            match_etaPos = j[0]
            match_phiPos = j[1]
            output.append(makeCircle(match_etaPos-etaPos,match_phiPos-phiPos, 0.4, ROOT.kBlue))

        for j in data["offJetAll"][str(num)]:
            allJet_etaPos = j[0]
            allJet_phiPos = j[1]
            output.append(makeCircle(allJet_etaPos-etaPos,allJet_phiPos-phiPos, 0.4, ROOT.kRed, linestyle=ROOT.kDashed))


        for j in data["pfJet"][str(num)]:
            pfJet_etaPos = j[0]
            pfJet_phiPos = j[1]
            output.append(makeCircle(pfJet_etaPos-etaPos,pfJet_phiPos-phiPos, 0.4, ROOT.kBlue, linestyle=ROOT.kDashed))



        for t in data["offJet_Trks"][str(num)]:
            trk_etaPos = t[0]
            trk_phiPos = t[1]
            output.append(makeCircle(trk_etaPos-etaPos,trk_phiPos-phiPos, 0.01, ROOT.kRed))

        for t in data["offJet_TrksNoMatch"][str(num)]:
            trk_etaPos = t[0]
            trk_phiPos = t[1]
            output.append(makeCircle(trk_etaPos-etaPos,trk_phiPos-phiPos, 0.01, ROOT.kRed, fillColor=ROOT.kRed))


        for t in data["pfJet_Trks"][str(num)]:
            trk_etaPos = t[0]
            trk_phiPos = t[1]
            output.append(makeCircle(trk_etaPos-etaPos,trk_phiPos-phiPos, 0.01, ROOT.kBlue, linestyle=ROOT.kDashed))



        canJet.SaveAs(o.outputDir+"/Event_"+str(num)+"_"+str(jetNum)+".pdf")
        canEvent.cd()        


    for j in data["offJetAll"][str(num)]:
        etaPos = j[0]
        phiPos = j[1]
        output.append(makeCircle(etaPos,phiPos, 0.4, ROOT.kRed, linestyle=ROOT.kDashed))

    for j in data["offMatchJet"][str(num)]:
        etaPos = j[0]
        phiPos = j[1]
        output.append(makeCircle(etaPos,phiPos, 0.4, ROOT.kBlue))

    for j in data["pfJet"][str(num)]:
        etaPos = j[0]
        phiPos = j[1]
        output.append(makeCircle(etaPos,phiPos, 0.4, ROOT.kBlue, linestyle=ROOT.kDashed))



    for t in data["offJet_Trks"][str(num)]:
        etaPos = t[0]
        phiPos = t[1]
        output.append(makeCircle(etaPos,phiPos, 0.01, ROOT.kRed))

    for t in data["offJet_TrksNoMatch"][str(num)]:
        etaPos = t[0]
        phiPos = t[1]
        output.append(makeCircle(etaPos,phiPos, 0.01, ROOT.kRed, fillColor=ROOT.kRed))


    upperBox = ROOT.TBox (-5,pi+0.01,5,4)
    upperBox.SetFillColor(0)
    upperBox.Draw("same")


    hAxis.Draw("axis same")
    canEvent.SaveAs(o.outputDir+"/Event"+str(num)+".pdf")
   
    
for i in range(nEvents):
    makeEvent(i+1)
