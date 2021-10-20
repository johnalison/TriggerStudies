import optparse
parser = optparse.OptionParser()
parser.add_option('-n', '--name',              dest="name",            help="Run in loop mode")
parser.add_option('-p', '--prefix',            dest="prefix",          help="Run in loop mode")
#parser.add_option(      '--period',            dest="period",          help="Run in loop mode")
parser.add_option('-d', '--dirWithPdfs',       dest="dirWithPdfs",     help="Run in loop mode")
parser.add_option('-t', '--tag',       default="four",     help="four is default")
#parser.add_option('--rocPlot',                  dest="rocPlot",          help="Run in loop mode")
#parser.add_option('--flavPlotDir',              help="Run in loop mode")
#parser.add_option('--effDir',                   help="Run in loop mode")
#parser.add_option('--mcAlgoDir',                   help="Run in loop mode")
#parser.add_option('--dataAlgoDir',                   help="Run in loop mode")
#parser.add_option('--doCaloJets',     action="store_true",              help="Run in loop mode")
o, a = parser.parse_args()


def makeHeader(outFile):
    outFile.write("\documentclass{beamer} \n")
    outFile.write("\mode<presentation>\n")
    outFile.write("\setbeamertemplate{footline}[frame number]\n")
    outFile.write("\\addtobeamertemplate{frametitle}{\\vspace*{0.4cm}}{\\vspace*{-0.4cm}}\n")
    outFile.write("{ \\usetheme{boxes} }\n")
    outFile.write("\\usepackage{times}  % fonts are up to you\n")
    outFile.write("\\usefonttheme{serif}  % fonts are up to you\n")
    outFile.write("\\usepackage{graphicx}\n")
    outFile.write("\\usepackage{tikz}\n")
    outFile.write("\\usepackage{colortbl}\n")
    outFile.write("\setlength{\pdfpagewidth}{2\paperwidth}\n")
    outFile.write("\setlength{\pdfpageheight}{2\paperheight}\n")
    outFile.write("\\title{\huge \\textcolor{myblue}{{BTV DQM Study }}}\n")
    outFile.write("\\author{\\textcolor{cmured}{{\Large \\\\John Alison\\\\}}\n")
    outFile.write("  \\textit{\Large Carnegie Mellon University}\n")
    outFile.write("}\n")
    
    outFile.write("\date{  } \n")
    outFile.write("\n")
    #outFile.write("\logo{\n")
    #outFile.write("\\begin{picture}(10,8) %university_of_chicago_logo\n")
    #outFile.write("\put(-2.5,7.6){\includegraphics[height=0.5in]{CMSlogo_outline_black_red_nolabel_May2014.pdf}}\n")
    #outFile.write("\put(8.2,7.7){\includegraphics[height=0.45in]{CMU_Logo_Stack_Red.eps}}\n")
    #outFile.write("\end{picture}\n")
    #outFile.write("}\n")
    outFile.write("\n")
    outFile.write("\\beamertemplatenavigationsymbolsempty\n")
    outFile.write("\n")
    outFile.write("\\unitlength=1cm\n")
    outFile.write("\definecolor{myblue}{RGB}{33,100,158}\n")
    outFile.write("\definecolor{myblack}{RGB}{0,0,0}\n")
    outFile.write("\definecolor{myred}{RGB}{168,56,39}\n")
    outFile.write("\definecolor{cmured}{RGB}{173,29,53}\n")
    outFile.write("\definecolor{UCred}{RGB}{154,52,38}\n")
    outFile.write("\definecolor{mygreen}{RGB}{0,204,0}\n")
    outFile.write("\\begin{document}\n")
    outFile.write("\n")
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    outFile.write("\\titlepage\n")
    outFile.write("\end{frame}\n")
    #outFile.write("\\begin{frame}{Overview}\n")
    #outFile.write("\\tableofcontents\n")
    #outFile.write("\end{frame}\n")
    outFile.write("\logo{\n")
    #outFile.write("\\begin{picture}(10,8) %university_of_chicago_logo\n")
    #outFile.write("\put(-2.5,7.6){\includegraphics[height=0.5in]{CMSlogo_outline_black_red_nolabel_May2014.pdf}}\n")
    #outFile.write("\put(8.2,7.7){\includegraphics[height=0.45in]{CMU_Logo_Stack_Red.eps}}\n")
    #outFile.write("\end{picture}\n")
    outFile.write("}\n")

    

def make1x2(outFile,title,files):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    outFile.write("\\frametitle{\centerline{ \huge \\textcolor{myblack}{"+title+"}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")

    # for the fig
    width = 2.6
    xStart = -1.1
    xOffSet = 6.4
    yStart = 1
    outFile.write("  \put("+str(xStart)+","+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[0]+".pdf}}\n")
    if len(files) > 1:
        outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[1]+".pdf}}\n")



    outFile.write("\end{picture}\n")
    outFile.write("\end{frame}\n")




def make2x2_ratio(outFile,title,files):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    #outFile.write("\\frametitle{\centerline{\\textcolor{myblack}{"+title+"}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")


    # for the fig
    width = 1.8
    xStart = 0.45
    xOffSet = 5.0
    yOffSet = 4.2
    yStart = -1.2
    if len(files) > 0:
        outFile.write("  \put("+str(xStart)+" ,"+str(yStart+yOffSet)+"){\includegraphics[width="+str(width)+"in]{"+files[0]+".pdf}}\n")
    if len(files) > 1:
        outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart+yOffSet)+"){\includegraphics[width="+str(width)+"in]{"+files[1]+".pdf}}\n")        
    if len(files) > 2:
        outFile.write("  \put("+str(xStart)+","+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[2]+".pdf}}\n")
    if len(files) > 3:
        outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[3]+".pdf}}\n")

    outFile.write("  \put("+str(1)+","+str(7.5)+"){\huge{"+title+"}}\n")
        
    outFile.write("\end{picture}\n")
    outFile.write("\end{frame}\n")


def make2x2(outFile,title,files):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    #outFile.write("\\frametitle{\centerline{\\textcolor{myblack}{"+title+"}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")


    # for the fig
    width = 2.2
    xStart = -0.5
    xOffSet = 5.8
    yOffSet = 4.2
    yStart = -1.
    if len(files) > 0:
        outFile.write("  \put("+str(xStart)+" ,"+str(yStart+yOffSet)+"){\includegraphics[width="+str(width)+"in]{"+files[0]+".pdf}}\n")
    if len(files) > 1:
        outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart+yOffSet)+"){\includegraphics[width="+str(width)+"in]{"+files[1]+".pdf}}\n")        
    if len(files) > 2:
        outFile.write("  \put("+str(xStart)+","+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[2]+".pdf}}\n")
    if len(files) > 3:
        outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[3]+".pdf}}\n")

    outFile.write("  \put("+str(1)+","+str(7.5)+"){\huge{"+title+"}}\n")
        
    outFile.write("\end{picture}\n")
    outFile.write("\end{frame}\n")
    


def make2x3(outFile,title,files):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    outFile.write("\\frametitle{\centerline{ \huge \\textcolor{myblack}{"+title+"}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")

    # for the fig
    width = 1.75
    xStart = -1.0
    xOffSet = 4.25
    yOffSet = 4.0
    yStart = -0.8

    outFile.write("  \put("+str(xStart)+" ,"+str(yStart+yOffSet)+"){\includegraphics[width="+str(width)+"in]{"+files[0]+".pdf}}\n")
    outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart+yOffSet)+"){\includegraphics[width="+str(width)+"in]{"+files[1]+".pdf}}\n")
    outFile.write("  \put("+str(xStart+xOffSet+xOffSet)+" ,"+str(yStart+yOffSet)+"){\includegraphics[width="+str(width)+"in]{"+files[2]+".pdf}}\n")

    if len(files) > 3:
        outFile.write("  \put("+str(xStart)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[3]+".pdf}}\n")
        outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[4]+".pdf}}\n")
        outFile.write("  \put("+str(xStart+xOffSet+xOffSet)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[5]+".pdf}}\n")




    outFile.write("\end{picture}\n")
    outFile.write("\end{frame}\n")


def make1x1(outFile,title,file,text,xText,yText):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    outFile.write("\\frametitle{\centerline{ \huge \\textcolor{myblack}{"+title+"}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")

    # for the fig
    width = 4.5
    xStart = -0.5
    yStart = -0.2
    outFile.write("  \put("+str(xStart)+","+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+file+"}}\n")


    # for the text
    #textHeight = 7.
    outFile.write("  \put("+str(xText[0])+","+str(yText[0])+"){"+text[0]+"}\n")

    outFile.write("\end{picture}\n")
    outFile.write("\end{frame}\n")

def makeWholeSlide(outFile,inputPDF):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    #outFile.write("\\frametitle{\centerline{ \huge \\textcolor{myblack}{TEst}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")

    outFile.write("  \put("+str(-1)+","+str(-1)+"){\includegraphics[width="+str(5)+"in]{"+inputPDF+"}}\n")


    outFile.write("\end{picture}\n")
    outFile.write("\end{frame}\n")



def make1x3(outFile,title,files,text):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    outFile.write("\\frametitle{\centerline{ \huge \\textcolor{myblack}{"+title+"}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")

    # for the fig
    width = 1.75
    xStart = -1.
    xOffSet = 4.25
    yStart = 1
    outFile.write("  \put("+str(xStart)+","+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[0]+".pdf}}\n")
    if len(files) > 1:
        outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[1]+".pdf}}\n")
    if len(files) > 2:
        outFile.write("  \put("+str(xStart+2*xOffSet)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[2]+".pdf}}\n")

    # for the text
    textHeight = 5.2
    textStart = -0.25
    outFile.write("  \put("+str(textStart)+","+str(textHeight)+"){\\textcolor{myred}{\large "+text[0]+"}}\n")
    if len(text) > 1:
        outFile.write("  \put("+str(textStart+xOffSet)+","+str(textHeight)+"){\\textcolor{myred}{\large "+text[1]+" }}\n")
    if len(text) > 2:
        outFile.write("  \put("+str(textStart+(2*xOffSet))+","+str(textHeight)+"){\\textcolor{myred}{\large "+text[2]+" }}\n")

    outFile.write("\end{picture}\n")
    outFile.write("\end{frame}\n")


def makeTransition(outFile,text,doHuge=True):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    #outFile.write("\\frametitle{\centerline{ \huge \\textcolor{myblack}{"+title+"}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")

    # for the text
    textHeight = 4
    if doHuge:
        outFile.write("  \put("+str(0)+","+str(textHeight)+"){\\textcolor{myred}{\Huge \\textit{"+text+"}}}\n")
    else:
        outFile.write("  \put("+str(0)+","+str(textHeight)+"){\\textcolor{myred}{\Large \\textit{"+text+"}}}\n")
    outFile.write("\end{picture}\n")
    outFile.write("\end{frame}\n")


def makeText(outFile,text,title=""):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    outFile.write("\\frametitle{\centerline{ \huge \\textcolor{myblack}{"+title+"}}}  \n")
    for t in text:
        outFile.write(t+"\n")
    outFile.write("\end{frame}\n")





def makePresentation():

    outFile = open(o.name+".tex","w")
    makeHeader(outFile)

            
    cut = "passMDRs"
    pdfDir = o.dirWithPdfs
    prefix = o.prefix 

    
    #outFile.write("\subsection{ROCs} \n")

    for slideConfig in [
            ("roc_All_Eff","roc_All_C_Eff","",""),
        ]:
        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/"+slideConfig[i]]
        make1x2(outFile,"ROCs",
                files = files,
                )

    #outFile.write("\subsection{Inputs} \n")
    makeTransition(outFile,"Inputs")    


    #
    #  Jet-Level Inputs
    #
    for slideConfig in [
            ("DeepCSV_l","deepFlavB","pt_m","eta"),
            ("Ip2P","Ip3P","Ip2P_l","Ip3P_l"),
            ("Bprob","Proba","Svx","SvxHP"),
            ("track_nTracks","btag_sv_nSVs","btag_chargedMultiplicity","btag_neutralMultiplicity"),
    ]:
        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/BvL_"+slideConfig[i]]
        make2x2_ratio(outFile,"Jet-Level Inputs",
                      files = files,
                      )


    #
    #  Tracks 
    #
    for slideConfig in [
            ("eta","pt_s","DeltaR","PtRel"),
            ("NPixelHits","HasInnerPixHit","NStripHits","NTotalHits"),
            ("ip2d","ip2d_l","ip2d_sig","ip2d_sig_l"),
            ("ip3d","ip3d_l","ip3d_sig","ip3d_sig_l"),
            #("Chi2","","",""),
    ]:
        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/BvL_track_"+slideConfig[i]]
        make2x2_ratio(outFile,"Track-Level Inputs",
                      files = files,
                      )



    #
    #  Secondary Vertex
    #
    for slideConfig in [
            ("Mass","NTracks","R","Z"),
            ("Eta", "Pt","JetDeltaR","Chi2"),
            ("Flight","FlightSig","Flight2D","FlightSig2D"),
            #("Chi2","","",""),
    ]:
        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/BvL_btag_sv_"+slideConfig[i]]
        make2x2_ratio(outFile,"Secondary Vertex Inputs",
                      files = files,
                      )



    #
    #  Event-by-Event Matching
    #
    makeTransition(outFile,"Event Matching")    
    for slideConfig in [
            ("dR","dPt","dPhi","dEta"),
            ("dDeepcsv","ddeepFlavB","dProba","dBprob"),
            ("dSvx"    ,"dSvxHP"    ,"dIp2P" ,        "dIp3P"),
            ("btag_djetNTracks","btag_djetNSecondaryVertices","btag_dchargedHadronMultiplicity","btag_dneutralMultiplicity"),
    ]:
        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/BvL_matchedJet_"+slideConfig[i]]
        make2x2(outFile,"Event-by-Event Jet Matching",
                files = files,
        )



    for slideConfig in [
            ("R"  ,"Z"            ,        "Eta"          ,        "Phi"          ),
            ("nSVs"         ,"NTracks"                ,"Mass"                   ,"Pt")           ,
            ("JetDeltaR"              ,        "totCharge"     ,        "Chi2"         ,"EnergyRatio"            ),
            ("Flight"       ,"FlightSig"    ,"Flight2D"     ,"FlightSig2D")  ,


    ]:
        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/BvL_matchedJet_btag_dsv_"+slideConfig[i]]
        make2x2(outFile,"Event-by-Event SV Matching",
                files = files,
        )




    for slideConfig in [

            ("dtrackEta"            ,"dtrackPhi"            ,        "dtrackPt"             ,        "dtrackMomentum"       ),
            ("dtrackChi2"            , "dtrackNTotalHits"      , "dtrackNPixelHits"      , "dtrackIsFromV0"  ),
            ("dip2d","dip2d_sig","dip2d_sig_l","dip2d_err",),
            ("dip3d","dip3d_sig","dip3d_sig_l","dip3d_err",),
            ("dtrackPtRel"          ,"dtrackDeltaR"         ,"dtrackJetDistVal"     ,"dtrackPPar"           ),



        ]:
    


        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/BvL_matchedJet_btag_"+slideConfig[i]]
        make2x2(outFile,"Event-by-Event Track Matching",
                files = files,
        )

        
        
        
    makeTransition(outFile,"Back-up")    
                
    for slideConfig in [
            ("roc_All_Eff","roc_All_C_Eff","",""),
            ("roc_Bprob_Eff","roc_Bprob_C_Eff","",""),
            ("roc_cMVAv2_Eff",   "roc_cMVAv2_C_Eff",   "",""),
            ("roc_CombIVF_Eff",  "roc_CombIVF_C_Eff",  "",""),
            ("roc_Svx_Eff",      "roc_Svx_C_Eff",      "",""),
            ("roc_SvxHP_Eff",    "roc_SvxHP_C_Eff",    "",""),
            ("roc_Bprob_Eff",    "roc_Bprob_C_Eff",    "",""),
            ("roc_Proba_Eff",    "roc_Proba_C_Eff",    "",""),
            ("roc_Ip2P_Eff",     "roc_Ip2P_C_Eff",     "",""),
            ("roc_Ip3P_Eff",     "roc_Ip3P_C_Eff",     "",""),
            ("roc_SoftMu_Eff",   "roc_SoftMu_C_Eff",   "",""),
            ("roc_SoftEl_Eff",   "roc_SoftEl_C_Eff",   "",""),


        ]:
        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/"+slideConfig[i]]
        make1x2(outFile,"ROCs",
                files = files,
                )


    #
    #  Track Efficiiences
    #
    for slideConfig in [
            ("Eta","Phi","pt_s","pt_m"),
            ("NPixelHits","HasInnerPixHit","NStripHits","NTotalHits"),
            ("ip2d","ip2d_l","ip2d_sig","ip2d_sig_l"),
            ("ip3d","ip3d_l","ip3d_sig","ip3d_sig_l"),
            ("DeltaR","","",""),
            
            #("Chi2","","",""),
    ]:
        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/Eff_"+slideConfig[i]]
        make2x2(outFile,"Tracking Relative Efficiencies",
                      files = files,
                      )


    #
    #  Track Fakes
    #
    for slideConfig in [
            ("Eta","Phi","pt_s","pt_m"),
            ("NPixelHits","HasInnerPixHit","NStripHits","NTotalHits"),
            ("ip2d","ip2d_l","ip2d_sig","ip2d_sig_l"),
            ("ip3d","ip3d_l","ip3d_sig","ip3d_sig_l"),
            ("DeltaR","","",""),
            
            #("Chi2","","",""),
    ]:
        files = []
        for i in range(4): 
            if slideConfig[i]: files += [pdfDir+"/Fake_"+slideConfig[i]]
        make2x2(outFile,"Tracking Relative Fake Rates",
                      files = files,
                      )



    outFile.write("\n")
    outFile.write("\end{document}\n")



if __name__ == "__main__":
    makePresentation()
    import os

    fileName = o.name
    filePathAndName = o.name
    if len(o.name.split("/")):
        fileName = o.name.split("/")[-1]
        filePath = "/".join(o.name.split("/")[0:-1])
        print( "fileName:",fileName)
        print( "filePath:",filePath)


    os.system("rm "+fileName+".aux")

    os.system("pdflatex "+filePathAndName+".tex")
    os.system("pdflatex "+filePathAndName+".tex")
    os.system("pdflatex "+filePathAndName+".tex")


    os.system("rm "+fileName+".out")
    os.system("rm "+fileName+".toc")
    os.system("rm "+fileName+".snm")
    os.system("rm "+fileName+".aux")
    os.system("rm "+fileName+".nav")
    os.system("rm "+fileName+".log")

    if len(o.name.split("/")):
        os.system("mv "+fileName+".pdf "+filePath)
