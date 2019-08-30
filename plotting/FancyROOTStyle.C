//
// ATLAS Style, based on a style file from BaBar
//

#include <iostream>

#include "FancyROOTStyle.h"

#include "TROOT.h"

void SetFancyStyle ()
{
  std::cout << "\nApplying Fancy style settings...\n" << std::endl ;
  static TStyle* fancyStyle = 0;

  if ( fancyStyle==0 ) fancyStyle = FancyStyle();
  gROOT->SetStyle("FANCY");
  gROOT->ForceStyle();
}

TStyle* FancyStyle() 
{
  TStyle *fancyStyle = new TStyle("FANCY","Fancy style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  fancyStyle->SetFrameBorderMode(icol);
  fancyStyle->SetFrameFillColor(icol);
  fancyStyle->SetCanvasBorderMode(icol);
  fancyStyle->SetCanvasColor(icol);
  fancyStyle->SetPadBorderMode(icol);
  fancyStyle->SetPadColor(icol);
  fancyStyle->SetStatColor(icol);
  //fancyStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  fancyStyle->SetPaperSize(20,26);

  // set margin sizes
  fancyStyle->SetPadTopMargin(0.05);
  fancyStyle->SetPadRightMargin(0.05);
  fancyStyle->SetPadBottomMargin(0.16);
  fancyStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  fancyStyle->SetTitleXOffset(1.4);
  fancyStyle->SetTitleYOffset(1.4);

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
  fancyStyle->SetTextFont(font);

  fancyStyle->SetTextSize(tsize);
  fancyStyle->SetLabelFont(font,"x");
  fancyStyle->SetTitleFont(font,"x");
  fancyStyle->SetLabelFont(font,"y");
  fancyStyle->SetTitleFont(font,"y");
  fancyStyle->SetLabelFont(font,"z");
  fancyStyle->SetTitleFont(font,"z");
  
  fancyStyle->SetLabelSize(tsize,"x");
  fancyStyle->SetTitleSize(tsize,"x");
  fancyStyle->SetLabelSize(tsize,"y");
  fancyStyle->SetTitleSize(tsize,"y");
  fancyStyle->SetLabelSize(tsize,"z");
  fancyStyle->SetTitleSize(tsize,"z");

  // use bold lines and markers
  fancyStyle->SetMarkerStyle(20);
  fancyStyle->SetMarkerSize(1.2);
  fancyStyle->SetHistLineWidth(2.);
  fancyStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  fancyStyle->SetErrorX(0.5);
  // get rid of error bar caps
  //fancyStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  fancyStyle->SetOptTitle(0);
  //fancyStyle->SetOptStat(1111);
  fancyStyle->SetOptStat(0);
  //fancyStyle->SetOptFit(1111);
  fancyStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  fancyStyle->SetPadTickX(1);
  fancyStyle->SetPadTickY(1);

  return fancyStyle;

}

