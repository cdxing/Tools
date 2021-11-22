#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraph.h"
// ---------------- Read root files to generate nice plots for presentations ------------
int centPlotter(const char* inFile = "/mnt/c/Users/pjska/github/FlowExtractor/res_sys/result_sys_flow/merged_sys_primary_var0_iter3_.root"){
  TFile *myFile = new TFile(inFile,"read");
  if (!myFile || myFile->IsZombie()){
    std::cout<<"Cannot open the file"<<myFile<<std::endl;
    return 0;
  }

  TH1D* hist_TrkMult_Davis;
  TH1D* hist_TrkMult_myDef;

  // TLegend* leg_Davis;
  // TLegend* leg_myDef;
  //
  // leg_Davis->SetFillStyle(0);
  // leg_Davis->SetBorderSize(0);
  // leg_myDef->SetFillStyle(0);
  // leg_myDef->SetBorderSize(0);
  //
  hist_TrkMult_Davis = (TH1D*)myFile->Get("hist_FXTTrackMult");
  hist_TrkMult_myDef = (TH1D*)myFile->Get("hist_realTrackMult");

  Int_t cenSection_Davis[10]={2,6,12,22,39,64,100,154,191,241}; // From UC Davis, cut on nFXTMult
  Int_t cenSection_myDef[10]={5,11,22,37,57,82,113,151,174,245};// My own cent defintion, cut on nGoodTracks

  Int_t i_top_Davis = 1000 + hist_TrkMult_Davis->GetMaximum();
  Int_t i_top_myDef = 1000 + hist_TrkMult_myDef->GetMaximum();
  TLine *tl[2][10];

  for(int j = 0; j<10;j++){
    tl[0][j] = new TLine(cenSection_Davis[j],0,cenSection_Davis[j],i_top_Davis);
    tl[1][j] = new TLine(cenSection_myDef[j],0,cenSection_myDef[j],i_top_myDef);
    tl[0][j] -> SetLineColor(j+1);
    tl[1][j] -> SetLineColor(j+1);
  }
  tl[0][9] -> SetLineColor(1);
  tl[1][9] -> SetLineColor(1);
  // leg_Davis->AddEntry(tl[0][9])
  TCanvas *c1_Davis = new TCanvas("c1_Davis","c1_Davis",200,10,1024,768);
  TCanvas *c2_myDef = new TCanvas("c2_myDef","c2_myDef",200,10,1024,768);
  hist_TrkMult_Davis->GetXaxis()->SetRangeUser(0,500);
  // hist_TrkMult_Davis->GetXaxis()->SetBinLabel(cenSection_Davis[0],Form("%d 80 %%",cenSection_Davis[0]));
  hist_TrkMult_myDef->GetXaxis()->SetRangeUser(0,500);
  // hist_TrkMult_myDef->GetXaxis()->SetBinLabel(cenSection_myDef[0],"80 % ");
  c1_Davis->SetLogy();
  c2_myDef->SetLogy();

  c1_Davis->cd();
  hist_TrkMult_Davis->SetTitle("Centrality: based on # of primary tracks");
  hist_TrkMult_Davis->Draw();
  for(int j = 0; j<10;j++){
    tl[0][j] -> Draw("same");
  }

  c2_myDef->cd();
  hist_TrkMult_myDef->SetTitle("Centrality: based on # of primary tracks after QA");
  hist_TrkMult_myDef->GetXaxis()->SetTitle("N_{GoodTracks}");
  hist_TrkMult_myDef->Draw();
  for(int j = 0; j<10;j++){
    tl[1][j] -> Draw("same");
  }
  return 0;

}
