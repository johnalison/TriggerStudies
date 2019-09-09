import optparse
parser = optparse.OptionParser()
parser.add_option('-n', '--name',              dest="name",            help="Run in loop mode")
parser.add_option('-p', '--prefix',            dest="prefix",          help="Run in loop mode")
#parser.add_option(      '--period',            dest="period",          help="Run in loop mode")
parser.add_option('--rocPlot',                  dest="rocPlot",          help="Run in loop mode")
parser.add_option('--fileCompDir',              help="Run in loop mode")
parser.add_option('--jetLevelPlotDir',          help="Run in loop mode")
parser.add_option('--effDir',                   help="Run in loop mode")
parser.add_option('--flavPlotDir',              help="Run in loop mode")
parser.add_option('--algoDir',                   help="Run in loop mode")
parser.add_option('--name1',                   help="Run in loop mode")
parser.add_option('--name2',                   help="Run in loop mode")
o, a = parser.parse_args()


def makeHeader(outFile):
    outFile.write("\documentclass{beamer} \n")
    outFile.write("\mode<presentation>\n")
    outFile.write("\setbeamertemplate{footline}[frame number]\n")
    outFile.write("\\addtobeamertemplate{frametitle}{\\vspace*{0.4cm}}{\\vspace*{-0.4cm}}\n")
    outFile.write("{ \usetheme{boxes} }\n")
    outFile.write("\usepackage{times}  % fonts are up to you\n")
    outFile.write("\usefonttheme{serif}  % fonts are up to you\n")
    outFile.write("\usepackage{graphicx}\n")
    outFile.write("\usepackage{tikz}\n")
    outFile.write("\usepackage{colortbl}\n")
    outFile.write("\setlength{\pdfpagewidth}{2\paperwidth}\n")
    outFile.write("\setlength{\pdfpageheight}{2\paperheight}\n")
    outFile.write("\\title{\huge \\textcolor{myblue}{{BTagging Input Variables:\\\\ \\textcolor{myblack}{\\textit{Online vs Offline}} }}}\n")
    outFile.write("\\author{\\textcolor{cmured}{{\Large \\\\John Alison, Patrick Bryant, Ian Harris\\\\}}\n")
    outFile.write("  \\textit{\Large Carnegie Mellon University}\n")
    outFile.write("}\n")
    outFile.write("\date{  } \n")
    outFile.write("\n")
    outFile.write("\logo{\n")
    outFile.write("\\begin{picture}(10,8) %university_of_chicago_logo\n")
    #outFile.write("\put(-2.5,7.6){\includegraphics[height=0.5in]{CMSlogo_outline_black_label_May2014.pdf}}\n")
    outFile.write("\put(-2.5,7.6){\includegraphics[height=0.5in]{CMSlogo_outline_black_red_nolabel_May2014.pdf}}\n")
    outFile.write("\put(8.2,7.7){\includegraphics[height=0.45in]{CMU_Logo_Stack_Red.eps}}\n")
    outFile.write("\end{picture}\n")
    outFile.write("}\n")
    outFile.write("\n")
    outFile.write("\\beamertemplatenavigationsymbolsempty\n")
    outFile.write("\n")
    outFile.write("\unitlength=1cm\n")
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
    


def make1x2(outFile,title,files,text,xText,yText,addLeg=False):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    outFile.write("\\frametitle{\centerline{ \huge \\textcolor{myblack}{"+title+"}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")

    # for the fig
    width = 2.6
    xStart = -1.1
    xOffSet = 6.4
    yStart = 0.4
    outFile.write("  \put("+str(xStart)+","+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[0]+".pdf}}\n")
    if len(files) > 1:
        outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[1]+".pdf}}\n")

    # for the text
    textHeight = 6
    for tItr in range(len(text)):
        outFile.write("  \put("+str(xText[tItr])+","+str(yText[tItr])+"){\\textcolor{myred}{\large "+text[tItr]+"}}\n")
    #if len(text) > 1:
    #    outFile.write("  \put("+str(xStart+xOffSet+1)+","+str(textHeight)+"){\\textcolor{myred}{\large "+text[1]+" }}\n")


    if addLeg:
        legText =  [("\\textcolor{red}{Offline BJets}",                      1.5,0.3),
                    ("\\textcolor{myblack}{Offline Light-Flavour}",          5.5,0.3),
                    ("\\textcolor{red}{HLT BJets}",                          1.5,-0.2),
                    ("\\textcolor{myblack}{HLT Light-Flavour}",              5.5,-0.2),
                    ("\\tikz\draw[red,very thick] (0.25,0.4) -- (0.75,0.4);",0.8,0.415),
                    ("\\tikz\draw[red,fill=red] (0,0) circle (.55ex);",      0.975,-0.175),
                    ("\\tikz\draw[red,very thick] (0.25,0.4) -- (0.75,0.4);",0.8,-0.085),
                    ("\\tikz\draw[black,very thick] (0.25,0.4) -- (0.75,0.4);",4.8,0.415),
                    ("\\tikz\draw[black,fill=black] (0,0) circle (.55ex);",    4.975,-0.175),
                    ("\\tikz\draw[black,very thick] (0.25,0.4) -- (0.75,0.4);",4.8,-0.085),
                    ]


        for legData in legText:
            outFile.write("  \put("+str(legData[1])+","+str(legData[2])+"){\\textcolor{myred}{\large "+legData[0]+"}}\n")


    outFile.write("\end{picture}\n")
    outFile.write("\end{frame}\n")


def make2x2(outFile,title,files):
    outFile.write("\n")
    outFile.write("\\begin{frame}\n")
    outFile.write("\\frametitle{\centerline{ \huge \\textcolor{myblack}{"+title+"}}}  \n")
    outFile.write("\\begin{picture}(10,8) \n")

    # for the fig
    width = 2.3
    xStart = -0.6
    xOffSet = 5.8
    yOffSet = 4.0
    yStart = -0.7
    outFile.write("  \put("+str(xStart)+","+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[2]+".pdf}}\n")
    outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart)+"){\includegraphics[width="+str(width)+"in]{"+files[3]+".pdf}}\n")
    outFile.write("  \put("+str(xStart)+" ,"+str(yStart+yOffSet)+"){\includegraphics[width="+str(width)+"in]{"+files[0]+".pdf}}\n")
    outFile.write("  \put("+str(xStart+xOffSet)+" ,"+str(yStart+yOffSet)+"){\includegraphics[width="+str(width)+"in]{"+files[1]+".pdf}}\n")


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

    prefix = o.prefix 

    text = ["\\textcolor{cmured}{\large Looking at HLT Btagging in 2018 ttbar MC and Data 2018 BCD}\\\\"]

    text += ["\\vspace*{0.2in}",
             "\\textcolor{myblue}{\large Event Selection:}",
             "\\begin{itemize}",
             "\\item[\\textcolor{myblack}{-}]Require Electron+Muon Trigger\\\\"
             "\\item[\\textcolor{myblack}{-}]Two Tight-leptons\\\\"
             "\\end{itemize}",
             "\\textcolor{myblue}{\large Jet Selection:}",
             "\\begin{itemize}",
             "\\item[\\textcolor{myblack}{-}]Overlap removal with tight leptons\\\\"
             "\\item[\\textcolor{myblack}{-}]$|\eta| < 2.5 / P_T > 35$ GeV \\\\"
             #"\\item[\\textcolor{myblack}{-}]Study tracks in jets used for btagging:\\\\ \\textit{focus on offline/online differences}  \\\\"
             "\\end{itemize}"]

    makeText(outFile,text,title="Introduction")

    if o.rocPlot:
        make1x1(outFile,"HLT BTagging Performance",
                file = o.rocPlot,
                text = ["\\textit{\\textcolor{myblack}{Online btagging significantly worse than offline}}"],
                xText = [0.0],
                yText = [0.1],
                )

    if o.jetLevelPlotDir:
        #plotDirs = ["offJet_","offJets_matchedJet_",  "offJets_matchedCaloJet_"]
        dirNames = ["\\textcolor{black}{\\textit{Offline Jets}}",
                    "\\textcolor{myblue}{\\textit{PF Jets}}",
                    "\\textcolor{myred}{\\textit{Calo Jets}}",
                    "\\textcolor{myred}{\\textit{}}",
                    ]
        
        
        for slideConfig in [("Jet Kinematics",          ["OffJet_Pt","OffJet_Eta"],             ["Jet $p_{T}$","Jet $\eta$"], dirNames[0]),
                            ("BTagging Discriminant",   ["OffJet_CSV","OffJet_DeepCSV"],             ["CSV","DeepCSV"], dirNames[0]),
                            ("BTagging Discriminant",   ["PF_CSV_FlavorComp","PF_DeepCSV_FlavorComp"],             ["CSV","DeepCSV"], dirNames[1]),
                            ("BTagging Discriminant",   ["Calo_CSV_FlavorComp","Calo_DeepCSV_FlavorComp"],             ["CSV","DeepCSV"], dirNames[2]),
                            ("Turn On Curves",          ["Eff_PFDeepCSV_DataVSMC","Eff_CaloDeepCSV_DataVSMC"], ["PF Jets","Calo Jets"], dirNames[3]),
                            ("Efficiencies wrt Offline",["PFDeepCSVEffwrtOff_All","CaloDeepCSVEffwrtOff_All"], ["PF Jets","Calo Jets"], dirNames[3]),
                            ("Reverse Turn Ons",        ["RevEff_PFDeepCSV_All","RevEff_CaloDeepCSV_All"], ["PF Jets","Calo Jets"], dirNames[3]),
                            ]:
        
            #for iDir in range(len(plotDirs)):
            text = slideConfig[2] + [slideConfig[3]]
            make1x2(outFile,slideConfig[0],
                    files = [o.jetLevelPlotDir+"/"+slideConfig[1][0],
                             o.jetLevelPlotDir+"/"+slideConfig[1][1]],
                    text = text,
                    xText = [0, 6.5 , 0.3],
                    yText = [6.7,6.7, 0.3],
                    )





        
    if o.fileCompDir:
        plotDirs = ["offJets_matched_","offJets_matchedJet_",  "offJets_matchedCaloJet_"]
        dirNames = ["\\textcolor{black}{\\textit{Offline Jets}}",
                    "\\textcolor{myblue}{\\textit{PF Jets}}",
                    "\\textcolor{myred}{\\textit{Calo Jets}}",
                    ]
        
        
        for slideConfig in [("Jet Kinematics",          ["eta","pt_m"],             ["Jet $\eta$","Jet $p_{T}$"]),
                            ("BTagging Discriminant",   ["CSVv2_l","DeepCSV_l"],             ["CSV","DeepCSV"]),
                            ]:
        
            for iDir in range(len(plotDirs)):
                text = slideConfig[2] + [dirNames[iDir]]
                make1x2(outFile,slideConfig[0],
                        files = [o.fileCompDir+"/"+plotDirs[iDir]+slideConfig[1][0],
                                 o.fileCompDir+"/"+plotDirs[iDir]+slideConfig[1][1]],
                        text = text,
                        xText = [0, 6.5 , 0.3],
                        yText = [6.7,6.7, 0.3],
                        )
        
        makeTransition(outFile,"Track-Parameters")
        
        
        for slideConfig in [("Track Parameters",   ["tracks_eta","tracks_pt_s"],             ["Track $\eta$","Track $p_{T}$"]),
                            ("Track Multiplicity", ["tracks_nTracks", "btags_noV0_nTracks"],["N Tracks","N Selected Tracks"]),
                            ("Hit Multiplicity",   ["tracks_NTotalHits","tracks_NPixelHits"],["N Total Hits","N Pixel Hits"]),
                            ("Impact Parameters",  ["tracks_ip2d","tracks_ip3d"],            ["IP2D","IP3D"]),
                            ("Impact Parameters",  ["tracks_ip2d_l","tracks_ip3d_l"],        ["IP2D","IP3D"]),
                            ("Impact Parameters",  ["tracks_ip2d_sig",  "tracks_ip3d_sig"],            ["IP2D Significance","IP3D Significance"]),
                            ("Impact Parameters",  ["tracks_ip2d_sig_l","tracks_ip3d_sig_l"],        ["IP2D Significance","IP3D Significance"]),
                            ("Track Category",     ["tracks_IsFromSV","tracks_IsFromV0"],        ["Is From SV","Is From V0"]),
                            ("Track Parameters",   ["tracks_DeltaR","tracks_JetDistVal"],        ["Track $\Delta$ R ","Track Jet Dist"]),
                            ("Impact Parameters",  ["tracks_ip2d_err","tracks_ip3d_err"],        ["IP2D Uncertianty","IP3D Uncertianty"]),
                            ]:
        
            for iDir in range(len(plotDirs)):
                text = slideConfig[2] + [dirNames[iDir]]
                make1x2(outFile,slideConfig[0] ,
                        files = [o.fileCompDir+"/"+plotDirs[iDir]+slideConfig[1][0],
                                 o.fileCompDir+"/"+plotDirs[iDir]+slideConfig[1][1],],
                        text = text,
                        xText = [0, 6.5 , 0.3],
                        yText = [6.7,6.7, 0.3],
                        )
        
        makeTransition(outFile,"Secondary Vertices")
        
        
        
        for slideConfig in [("Vertices",   ["btags_sv_nSVs","btags_sv_NTracks"],             ["Number Vertices","Number Vertex Tracks"]),
                            ("Vertices",   ["btags_sv_Eta","btags_sv_Phi"],             ["Secondary Vertex $\eta$","Secondary Vertex $\phi$"]),
                            ("Vertices",   ["btags_sv_Flight2D","btags_sv_Flight"],             ["Flight Distance 2D","Flight Distance 3D"]),
                            ("Vertices",   ["btags_sv_FlightSig2D","btags_sv_FlightSig"],             ["Flight Significance 2D","Flight Significance 3D"]),
                            ("Vetex Fractions",   ["btags_sv_EnergyRatio","btags_sv_Chi2"],             ["Vertex Energy Fraction","Vertex Chi2"]),
                            ("Vetex Mass/$\Delta$R",   ["btags_sv_Mass","btags_sv_JetDeltaR"],             ["Vertex Mass","Vertex-Jet $\Delta$R"]),
                            ]:
          
        
        
            for iDir in range(len(plotDirs)):
                text = slideConfig[2] + [dirNames[iDir]]
                make1x2(outFile,slideConfig[0] ,
                        files = [o.fileCompDir+"/"+plotDirs[iDir]+slideConfig[1][0],
                                 o.fileCompDir+"/"+plotDirs[iDir]+slideConfig[1][1],],
                        text = text,
                        xText = [0, 6.5 , 0.3],
                        yText = [6.7,6.7, 0.3],
                        )


    if o.effDir:
        makeTransition(outFile,"Efficiencies / Fake Rates")

        makeWholeSlide(outFile,"./TrackMatchingSlide.pdf")

        for slideConfig in [ ("Eff_Eta","Eff_Momentum","Eff_DeltaR","Eff_phi"),
                             ("Eff_HasInnerPixHit", "Eff_NPixelHits", "Eff_NStripHits","Eff_NTotalHits",),
                             ("Eff_ip2d",  "Eff_ip3d",  "Eff_ip2d_l","Eff_ip3d_l",),
                             ]:

            make2x2(outFile,"\Large Relative HLT \\textcolor{myblue}{(PF)} Efficiency",
                    files = [o.effDir+"/"+slideConfig[0],
                             o.effDir+"/"+slideConfig[1],
                             o.effDir+"/"+slideConfig[2],
                             o.effDir+"/"+slideConfig[3],
                             ],
                    )

            make2x2(outFile,"\Large Relative HLT \\textcolor{myred}{(Calo)} Efficiency",
                    files = [o.effDir+"/Calo"+slideConfig[0],
                             o.effDir+"/Calo"+slideConfig[1],
                             o.effDir+"/Calo"+slideConfig[2],
                             o.effDir+"/Calo"+slideConfig[3],
                             ],
                    )
    
    
    
    
    
        for slideConfig in [ ("Fake_Eta","Fake_Momentum","Fake_DeltaR","Fake_phi"),
                             ("Fake_HasInnerPixHit", "Fake_NPixelHits", "Fake_NStripHits","Fake_NTotalHits",),
                             ("Fake_ip2d",  "Fake_ip3d",  "Fake_ip2d_l","Fake_ip3d_l",),
                             ]:
    
    


            make2x2(outFile,"\Large Relative HLT \\textcolor{myblue}{(PF)} Fake Rate",
                    files = [o.effDir+"/"+slideConfig[0],
                             o.effDir+"/"+slideConfig[1],
                             o.effDir+"/"+slideConfig[2],
                             o.effDir+"/"+slideConfig[3],
                             ],
                    )

            make2x2(outFile,"\Large Relative HLT \\textcolor{myred}{(Calo)} Fake Rate",
                    files = [o.effDir+"/Calo"+slideConfig[0],
                             o.effDir+"/Calo"+slideConfig[1],
                             o.effDir+"/Calo"+slideConfig[2],
                             o.effDir+"/Calo"+slideConfig[3],
                             ],
                    )
    

    if o.flavPlotDir:
        makeTransition(outFile,"MC BTagging Inputs (By Truth Label)", doHuge=False)
    
    
        for slideConfig in [("Track Parameters",   ["track_eta","track_pt_s"],             ["Track $\eta$","Track $p_{T}$"]),
                            ("Track Multiplicity", ["track_nTracks", "btag_noV0_nTracks"],["N Tracks","N Selected Tracks"]),
                            ("Hit Multiplicity",   ["track_NTotalHits","track_NPixelHits"],["N Total Hits","N Pixel Hits"]),
                            ("Impact Parameters",  ["track_ip2d","track_ip3d"],            ["IP2D","IP3D"]),
                            ("Impact Parameters",  ["track_ip2d_l","track_ip3d_l"],        ["IP2D","IP3D"]),
                            ("Impact Parameters",  ["track_ip2d_sig",  "track_ip3d_sig"],            ["IP2D Significance","IP3D Significance"]),
                            ("Impact Parameters",  ["track_ip2d_sig_l","track_ip3d_sig_l"],        ["IP2D Significance","IP3D Significance"]),
                            ("Track Category",     ["track_IsFromSV","track_IsFromV0"],        ["Is From SV","Is From V0"]),
                            ("Track Parameters",   ["track_DeltaR","track_JetDistVal"],        ["Track $\Delta$ R ","Track Jet Dist"]),
                            ("Impact Parameters",  ["track_ip2d_err","track_ip3d_err"],        ["IP2D Uncertianty","IP3D Uncertianty"]),
                            ]:
           
            make1x2(outFile,slideConfig[0],
                    files = [o.flavPlotDir+"/"+slideConfig[1][0],o.flavPlotDir+"/"+slideConfig[1][1]],
                    text = slideConfig[2],
                    xText = [0, 6.5],
                    yText = [6.7,6.7],
                    addLeg = True
                    )
    
        makeTransition(outFile,"Secondary Vertices")
    
    
    
        for slideConfig in [("Vertices",   ["btag_sv_nSVs","btag_sv_NTracks"],             ["Number Vertices","Number Vertex Tracks"]),
                            ("Vertices",   ["btag_sv_Eta","btag_sv_Phi"],             ["Secondary Vertex $\eta$","Secondary Vertex $\phi$"]),
                            ("Vertices",   ["btag_sv_Flight2D","btag_sv_Flight"],             ["Flight Distance 2D","Flight Distance 3D"]),
                            ("Vertices",   ["btag_sv_FlightSig2D","btag_sv_FlightSig"],             ["Flight Significance 2D","Flight Significance 3D"]),
                            ("Vetex Fractions",   ["btag_sv_EnergyRatio","btag_sv_Chi2"],             ["Vertex Energy Fraction","Vertex Chi2"]),
                            ("Vetex Mass/$\Delta$R",   ["btag_sv_Mass","btag_sv_JetDeltaR"],             ["Vertex Mass","Vertex-Jet $\Delta$R"]),
                            ]:
           
            make1x2(outFile,slideConfig[0],
                    files = [o.flavPlotDir+"/"+slideConfig[1][0],o.flavPlotDir+"/"+slideConfig[1][1]],
                    text = slideConfig[2],
                    xText = [0, 6.5],
                    yText = [6.7,6.7],
                    addLeg = True
                    )
    


    makeTransition(outFile,"Back-up")

    if o.algoDir:
        makeTransition(outFile,"Efficiencies (By Offline Algo)")

        for algoPair in [(2,4),(5,6),(7,8),(9,10),(11,13),(14,22),(23,24),(29,)]:
    
            effPrefix = "offTracks_matched_vs_offTracks"
    
            files = [o.algoDir+"/"+effPrefix+"_Eta_forAlgo"+str(algoPair[0]),
                     o.algoDir+"/"+effPrefix+"_Phi_forAlgo"+str(algoPair[0]),
                     o.algoDir+"/"+effPrefix+"_Pt_forAlgo" +str(algoPair[0])]
    
            if len(algoPair) > 1:
                files += [o.algoDir+"/"+effPrefix+"_Eta_forAlgo"+str(algoPair[1]),
                          o.algoDir+"/"+effPrefix+"_Phi_forAlgo"+str(algoPair[1]),
                          o.algoDir+"/"+effPrefix+"_Pt_forAlgo" +str(algoPair[1])]
    
            make2x3(outFile,"Efficiencies (MC)",files = files)


    
                


    outFile.write("\n")
    outFile.write("\end{document}\n")



if __name__ == "__main__":
    makePresentation()
    import os
    os.system("pdflatex "+o.name+".tex")
