#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraph.h"
// ---------------- Read root files to generate nice plots for presentations ------------
int plotsGenerator(const char* inFile = "./src/97D2AFB119464E2BB781CF04F1524B05.picoDst.result.combined.root")
{
  TFile* F_3p85_1stEps = TFile::Open("./src/26p5_1stEps.root");
  TFile* F_3p85_1stEpCorrINPUT = TFile::Open("./src/26p5_1stEpCorrINPUT.root");
  TFile* F_3p85corrResult = TFile::Open("./src/26p5corrResult.root");
  TFile* F_26p5_1stEps = TFile::Open("./src/26p5_1stEpdEpWeightedINPUT.root");
  TFile* F_26p5_1stEpCorrINPUT = TFile::Open("./src/26p5v1VsEta.root");
  TFile* F_26p5corrResult = TFile::Open("./src/26p5_1stEpWeightedCorrResult.root");
  if (!F_3p85_1stEps || F_3p85_1stEps->IsZombie()){
    std::cout<<"Cannot open the file"<<inFile<<std::endl;
    return 0;
  }
  if (!F_3p85_1stEpCorrINPUT || F_3p85_1stEpCorrINPUT->IsZombie()){
    std::cout<<"Cannot open the file"<<inFile<<std::endl;
    return 0;
  }
  if (!F_3p85corrResult || F_3p85corrResult->IsZombie()){
    std::cout<<"Cannot open the file"<<inFile<<std::endl;
    return 0;
  }
  if (!F_26p5_1stEps || F_26p5_1stEps->IsZombie()){
    std::cout<<"Cannot open the file"<<inFile<<std::endl;
    return 0;
  }
  if (!F_26p5_1stEpCorrINPUT || F_26p5_1stEpCorrINPUT->IsZombie()){
    std::cout<<"Cannot open the file"<<inFile<<std::endl;
    return 0;
  }
  if (!F_26p5corrResult || F_26p5corrResult->IsZombie()){
    std::cout<<"Cannot open the file"<<inFile<<std::endl;
    return 0;
  }

TH1D* hist_3p85_1stEpsRaw[5];
TH1D* hist_3p85_1stEpsShifted[5];
TH2D* h2_3p85_1stEpCorr[10];
TH1D* hist_3p85_1stEpCorr[10];

TH1D* hist_26p5_1stEpsRaw[5];
TH1D* hist_26p5_1stEpsWeighted[5];
TH1D* hist_26p5_1stEpsShifted[5];
TH2D* h2_26p5_1stEpCorr[10];
TH1D* hist_26p5_1stEpCorr[10];

for(int i=0;i<4;i++){// Event planes
  hist_3p85_1stEpsRaw[i] = (TH1D*)F_3p85_1stEps->Get(Form("hist_Epd_east_psi_raw_ini_%d",i+1));
  hist_3p85_1stEpsShifted[i] = (TH1D*)F_3p85_1stEps->Get(Form("hist_Epd_east_psi_Shifted_ini_%d",i+1));

  hist_26p5_1stEpsRaw[i] = (TH1D*)F_26p5_1stEps->Get(Form("hist_Epd_east_psi_raw_ini_%d",i+1));
  hist_26p5_1stEpsWeighted[i] = (TH1D*)F_26p5_1stEps->Get(Form("hist_Epd_east_psi_Weighted_ini_%d",i+1));
  hist_26p5_1stEpsShifted[i] = (TH1D*)F_26p5_1stEps->Get(Form("hist_Epd_east_psi_Shifted_ini_%d",i+1));
}
hist_3p85_1stEpsRaw[4] = (TH1D*)F_3p85_1stEps->Get("hist_tpc_all_psi_raw");
hist_3p85_1stEpsShifted[4] = (TH1D*)F_3p85_1stEps->Get("hist_tpc_all_psi_shifted");
hist_26p5_1stEpsRaw[4] = (TH1D*)F_26p5_1stEps->Get("hist_tpc_all_psi_raw");
hist_26p5_1stEpsShifted[4] = (TH1D*)F_26p5_1stEps->Get("hist_tpc_all_psi_shifted");

for(int i=0;i<6;i++){// Correlations
  h2_3p85_1stEpCorr[i]=(TH2D*)F_3p85_1stEpCorrINPUT->Get(Form("correlation2D_epd_east%d",i));
  hist_3p85_1stEpCorr[i]=(TH1D*)F_3p85corrResult->Get(Form("hist_correlation_epd_east%d",i));

  h2_26p5_1stEpCorr[i]=(TH2D*)F_26p5_1stEpCorrINPUT->Get(Form("correlation2D_epd_east%d",i));
  hist_26p5_1stEpCorr[i]=(TH1D*)F_26p5corrResult->Get(Form("hist_correlation_epd_east%d",i));
}
for(int i=0;i<4;i++){
  h2_3p85_1stEpCorr[i+6]=(TH2D*)F_3p85_1stEpCorrINPUT->Get(Form("correlation2D_epd%d_tpc",i+1));
  hist_3p85_1stEpCorr[i+6]=(TH1D*)F_3p85corrResult->Get(Form("hist_correlation_epd_tpc%d",i));

  h2_26p5_1stEpCorr[i+6]=(TH2D*)F_26p5_1stEpCorrINPUT->Get(Form("correlation2D_epd%d_tpc",i+1));
  hist_26p5_1stEpCorr[i+6]=(TH1D*)F_26p5corrResult->Get(Form("hist_correlation_epd_tpc%d",i));

}
TCanvas* c1 = new TCanvas("c1", "c1", 1280, 720);
TCanvas* c2 = new TCanvas("c2", "c2", 2400, 1600);
TCanvas* c3 = new TCanvas("c3", "c3", 2400, 1600);
c3->Divide(5,4);
for(int i=0;i<5;i++){// Correlations 26p5
c3->cd(i+1);
h2_26p5_1stEpCorr[i]->Draw("colz");
c3->cd(i+6);
hist_26p5_1stEpCorr[i]->Draw();
}
for(int i=0;i<5;i++){// Correlations 26p5
c3->cd(i+11);
h2_26p5_1stEpCorr[i+5]->Draw("colz");
c3->cd(i+16);
hist_26p5_1stEpCorr[i+5]->Draw();
}

c2->Divide(5,4);
for(int i=0;i<5;i++){// Correlations 3p85
c2->cd(i+1);
h2_3p85_1stEpCorr[i]->Draw("colz");
c2->cd(i+6);
hist_3p85_1stEpCorr[i]->Draw();
}
for(int i=0;i<5;i++){// Correlations 3p85
c2->cd(i+11);
h2_3p85_1stEpCorr[i+5]->Draw("colz");
c2->cd(i+16);
hist_3p85_1stEpCorr[i+5]->Draw();
}
c1->Divide(5,2); // Event planes of 3p85 26p5
for(int i=0;i<4;i++){
  c1->cd(i+1);
  hist_3p85_1stEpsRaw[i]->GetYaxis()->SetRangeUser(0,25000);
  hist_3p85_1stEpsRaw[i]->SetTitle(Form("EPD-%d event plane #Psi_{1}^{EPD-%d}",i+1,i+1));
  hist_3p85_1stEpsRaw[i]->GetXaxis()->SetTitle(Form("#Psi_{1}^{EPD-%d}",i+1));
  hist_3p85_1stEpsRaw[i]->Draw();
  hist_3p85_1stEpsShifted[i]->SetLineColor(kBlue);
  hist_3p85_1stEpsShifted[i]->Draw("same");
}
c1->cd(5);
hist_3p85_1stEpsRaw[4]->GetYaxis()->SetRangeUser(0,40000);
hist_3p85_1stEpsRaw[4]->SetTitle(Form("TPC event plane #Psi_{1}^{TPC}"));
hist_3p85_1stEpsRaw[4]->GetXaxis()->SetTitle(Form("#Psi_{1}^{TPC}"));
hist_3p85_1stEpsRaw[4]->Draw();
hist_3p85_1stEpsShifted[4]->SetLineColor(kBlue);
hist_3p85_1stEpsShifted[4]->Draw("same");
for(int i=0;i<4;i++){
  c1->cd(i+6);
  hist_26p5_1stEpsRaw[i]->GetYaxis()->SetRangeUser(0,50000);
  hist_26p5_1stEpsRaw[i]->SetTitle(Form("EPD-%d event plane #Psi_{1}^{EPD-%d}",i+1,i+1));
  hist_26p5_1stEpsRaw[i]->GetXaxis()->SetTitle(Form("#Psi_{1}^{EPD-%d}",i+1));
  hist_26p5_1stEpsRaw[i]->Draw();
  hist_26p5_1stEpsWeighted[i]->SetLineColor(kRed);
  hist_26p5_1stEpsShifted[i]->SetLineColor(kBlue);
  hist_26p5_1stEpsWeighted[i]->Draw("same");
  hist_26p5_1stEpsShifted[i]->Draw("same");
}
c1->cd(10);
hist_26p5_1stEpsRaw[4]->GetYaxis()->SetRangeUser(0,40000);
hist_26p5_1stEpsRaw[4]->SetTitle(Form("TPC event plane #Psi_{1}^{TPC}"));
hist_26p5_1stEpsRaw[4]->GetXaxis()->SetTitle(Form("#Psi_{1}^{TPC}"));
hist_26p5_1stEpsRaw[4]->Draw();
hist_26p5_1stEpsShifted[4]->SetLineColor(kBlue);
hist_26p5_1stEpsShifted[4]->Draw("same");
c1->SaveAs("./out/3p85_26p5_1stEps.png");
c2->SaveAs("./out/3p85_1stEpsCorrs.png");
c3->SaveAs("./out/26p5_1stEpsCorrs.png");
// H2->DrawCopy("colz");
// c1->cd(2);

          // Read Correlation files to Get 2d Histograms
  // Read resolution files to get 1d correlaiton and resolutions
  // correlaitons one fram one energy 4*5

  // TH2D* H2 = (TH2D*)F_3p85_1stEps->Get("h2_m2_QA_pq");
  //
  // TH1D* H1 = H2->ProjectionY("h1_m2",0,-1);
  //
  // double d_PRO_m2  = 0.880354;
  // double d_K_m2    = 0.24371698;
  // double d_PI_m2   = 0.019479835;
  //
  // TF1* F1 = new TF1("FitF1","[0] * TMath::Gaus(x, 0.880354, [1])", d_PRO_m2-0.13,  d_PRO_m2+0.15);
  // F1->SetParameter(0,37095);
  // F1->SetParameter(1,0.8896);
  // F1->SetParameter(2,0.04846);
  //
  // TF1* F2 = new TF1("FitF2","[0] * TMath::Gaus(x, 0.24371698, [1])", d_K_m2-0.027,  d_K_m2+0.03);
  // F2->SetParameter(0,8000);
  // F2->SetParameter(1,0.24);
  // F2->SetParameter(2,0.0176);
  //
  // TF1* F3 = new TF1("FitF3","[0] * TMath::Gaus(x, 0.019479835, [1])", 0.019-0.004,  0.019+0.007);
  // F3->SetParameter(0,600000);
  // F3->SetParameter(1,0.019);
  // F3->SetParameter(2,0.004);
  //
  //
  //
  // H1->Fit(F1->GetName(), "ER0+", "kRed", d_PRO_m2-0.1, d_PRO_m2+0.12);
  // std::cout<< "Chisquare = "<<F1->GetChisquare()<<std::endl;
  // std::cout<< "NDF = "<<F1->GetNDF()<<std::endl;
  //
  // H1->Fit(F2->GetName(), "ER0+", "kGreen", d_K_m2-0.015, d_K_m2+0.015);
  // std::cout<< "Chisquare = "<<F2->GetChisquare()<<std::endl;
  // std::cout<< "NDF = "<<F2->GetNDF()<<std::endl;
  //
  // H1->Fit(F3->GetName(), "ER0+", "kBlue", 0.019-0.001, 0.019+0.003);
  // std::cout<< "Chisquare = "<<F3->GetChisquare()<<std::endl;
  // std::cout<< "NDF = "<<F3->GetNDF()<<std::endl;
  //
  //
  //
  //
  // TCanvas* c1 = new TCanvas("c1", "Analyzer", 1600, 800);
  // // c1->Divide(2,1);
  // // c1->cd(1);
  // // H2->DrawCopy("colz");
  // // c1->cd(2);
  // c1->cd();
  // H1->DrawCopy();
  // F1->SetLineColor(2);
  // F2->SetLineColor(2);
  // F3->SetLineColor(2);
  // F1->SetLineStyle(2);
  // F2->SetLineStyle(2);
  // F3->SetLineStyle(2);
  // F1->Draw("same");
  // F2->Draw("same");
  // F3->Draw("same");
  // // F4->Draw("same");
  // // TLegend* leg1 = new TLegend(0.1,0.7,0.48,0.9);
  // // leg1->AddEntry(F2,"K_m2","lp");
  // // leg1->Draw("same");
  //
  return 0;
}
