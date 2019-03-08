// -*- C++ -*-

#if !defined(PileUpWeightTool_H)
#define PileUpWeightTool_H

#include <map>
#include <TFile.h>

namespace NtupleAna {

  class PileUpWeightTool {

  public:

    std::string m_inputFileName;
    std::string m_puWeightHistName = "nPV_weight";
    std::map<int, float> m_weights;

  public:
    
    PileUpWeightTool(std::string inputFileName) : m_inputFileName(inputFileName)  { 
      
      TFile* inFile = new TFile(inputFileName.c_str(),"READ");
      TH1F* hWeights = (TH1F*)inFile->Get(m_puWeightHistName.c_str());

      unsigned int nBinX = hWeights->GetNbinsX();
      for(unsigned int iBin = 0; iBin < (nBinX+1); ++iBin){
	int binCenter = hWeights->GetBinCenter(iBin);
	float thisWeight = hWeights->GetBinContent(iBin);
	//std::cout << "Adding binCenter / weight " << binCenter << " / " << thisWeight << std::endl;
	m_weights.insert(std::make_pair(binCenter,thisWeight));
      }
      
      inFile->Close();
      delete inFile;
    }
    
    ~PileUpWeightTool() {}; 

    float getWeight(int nPV){

      for(auto elem : m_weights){
	if(nPV >= elem.first && nPV < (elem.first + 1)){
	  return elem.second;
	}
      }

      return 0.0; 
    }

      

  };

}
#endif // PileUpWeightTool_H
