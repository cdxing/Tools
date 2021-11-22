#include <fstream>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraph.h"

// EPD geometry of different \eta range for \psi_{1}^{EPD}
// ---------------- Read EPD eta weight files to generate nice plots for presentations ------------
int epdWeight(const char* inputFile = "./res/Epd_tpc_eta_newEPD_2_new_INPUT.root")
{
  TFile* inFile = TFile::Open(inputFile);
  if (!inFile || inFile->IsZombie()){
    std::cout<<"Cannot open the file"<<inFile<<std::endl;
    return 0;
  }
  std::ofstream tileFile("./out/tileNumbers.txt",ofstream::out);

  TH2D* h2_TtVsPp[5];
  TH1D* h1_TtVsPp[5];
  TProfile2D *profile2D_1;


  for(int i=0;i<5;i++){// eta range of each EPD sub EP
    h2_TtVsPp[i]=(TH2D*)inFile->Get(Form("h2_TtVsPpNmip_%d",i));
  }
  profile2D_1=(TProfile2D*)inFile->Get("profile2D_PpVsEta");
  TCanvas* c1 = new TCanvas("c1", "c1", 1600, 720);
  c1->Divide(5,2); // Event planes of 3p85 26p5

  for(int i=0;i<5;i++){
    c1->cd(i+1);
    h2_TtVsPp[i]->SetTitle(Form("EPD-%d event plane TT vs PP",i));
    h2_TtVsPp[i]->GetXaxis()->SetTitle(Form("PP (Supersector)"));
    h2_TtVsPp[i]->GetYaxis()->SetTitle(Form("TT (Tile)"));
    h2_TtVsPp[i]->Draw("colz");
    c1->cd(i+6);
    h1_TtVsPp[i] = h2_TtVsPp[i]->ProjectionX();
    h1_TtVsPp[i]->GetYaxis()->UnZoom();
    h1_TtVsPp[i]->Draw();
  }
  c1->SaveAs("./out/26p5_1stEpdEpWtOUTPUT.png");
  for(int i=0;i<5;i++){
    for(int pp=1;pp<=12;pp++){
      for(int tt=1;tt<31;tt++){
        if(h2_TtVsPp[i]->GetBinContent(pp,tt)>0) {
          std::cout<<Form("[0,%d,%d],",pp,tt);
          tileFile<<Form("[0,%d,%d],",pp,tt);
        }
      }
    }
    std::cout<<Form("EPD sub-%d,",i)<<std::endl;
    tileFile<<std::endl;
    tileFile<<Form("EPD sub-%d,",i)<<std::endl;
    tileFile<<std::endl;
  }
  tileFile.close();
  TCanvas* c2 = new TCanvas("c2", "c2", 1080, 720);
  c2->cd();
  profile2D_1->SetTitle("<TnMIP> VS Supersector VS #eta");
  profile2D_1->Draw("colz");
  TLine *tl[5];
  tl[0] = new TLine(-5.16,0.5,-5.16,12.5);
  tl[0]->SetLineColor(2);
  tl[1] = new TLine(-3.82,0.5,-3.82,12.5);
  tl[1]->SetLineColor(2);
  tl[2] = new TLine(-3.28,0.5,-3.28,12.5);
  tl[2]->SetLineColor(2);
  tl[3] = new TLine(-2.87,0.5,-2.87,12.5);
  tl[3]->SetLineColor(2);
  tl[4] = new TLine(-2.60,0.5,-2.60,12.5);
  tl[4]->SetLineColor(2);

  for(int i = 0; i<5;i++){
    tl[i]->Draw("same");
  }

  return 1;
}
