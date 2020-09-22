#include <iostream>
#include <fstream>
#include <cmath>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"

#include "TMath.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TProfile3D.h"

////////////////////////////////////////
//
// Read and generate correlation and resolution information
//
////////////////////////////////////////


Double_t resoErr(Double_t corrAB, Double_t corrAC, Double_t corrBC,
                 Double_t errAB, Double_t errAC, Double_t errBC);
Double_t resoVal(Double_t corrAB, Double_t corrAC, Double_t corrBC);
const int _Ncentralities = 9;
int corrFinder(){
  TFile* inFile = new TFile("./res/res_sysErr/merged_EpCorrection_OUTPUT_sys_etaGap_var2_iter1_207E5DF8B847DCF7C9680FE70B213088_.root","READ");

  TProfile *profile_correlation_epd_east[2][6], *profile_correlation_epd_tpc[2][4];
  Double_t binContentEpd[2][6][_Ncentralities]; // Indexes R1, R2; correlations; centrality
  Double_t binErrorEpd[2][6][_Ncentralities];
  Double_t binContentTpc[2][4][_Ncentralities];
  Double_t binErrorTpc[2][4][_Ncentralities];
  for(int i=0;i<6;i++){
    for(int n=0;n<2;n++){
      profile_correlation_epd_east[n][i] = (TProfile*)inFile->Get(Form("profile_correlation_n%d_epd_east%d",n+1,i));
    }
  }
  for(int i=0;i<4;i++){
    for(int n=0;n<2;n++){
      profile_correlation_epd_tpc[n][i] = (TProfile*)inFile->Get(Form("profile_correlation_n%d_epd%d_tpc",n+1,i+1));
    }
  }
  for(int i=0;i<6;i++){
    for(int j=0;j<_Ncentralities;j++){
      for(int n=0;n<2;n++){
        binContentEpd[n][i][j]=profile_correlation_epd_east[n][i]->GetBinContent(j+1);
        std::cout<<Form("profile_correlation_n%d_epd_east%d binNumber%d binContent: ",n+1,i,j+1) << binContentEpd[n][i][j];
        binErrorEpd[n][i][j]=profile_correlation_epd_east[n][i]->GetBinError(j+1);
        std::cout<<Form("; binError: ") << binErrorEpd[n][i][j]<<std::endl;
      }
    }
  }
  for(int i=0;i<4;i++){
    for(int j=0;j<_Ncentralities;j++){
      for(int n=0;n<2;n++){
        binContentTpc[n][i][j]=profile_correlation_epd_tpc[n][i]->GetBinContent(j+1);
        std::cout<<Form("profile_correlation_n%d_epd%d_tpc binNumber%d binContent: ",n+1,i+1,j+1) << binContentTpc[n][i][j];
        binErrorTpc[n][i][j]=profile_correlation_epd_tpc[n][i]->GetBinError(j+1);
        std::cout<<Form("; binError: ") << binErrorTpc[n][i][j]<<std::endl;
      }
    }
  }

  // --------------------- sqrt bin Contents ---------------------------------
  for(int i=0;i<6;i++){
    for(int j=0;j<_Ncentralities;j++){
      for(int n=0;n<2;n++){
        if(binContentEpd[n][i][j]>=0){ // make sure bin content is not negative to sqrt
          binErrorEpd[n][i][j] *=1./(2.*sqrt(binContentEpd[n][i][j])); // Error proagation;
          std::cout<<Form("profile_correlation_n%d_epd_east%d binNumber%d sqrt binError: ",n+1,i,j+1) << binErrorEpd[n][i][j];
          binContentEpd[n][i][j]= sqrt(binContentEpd[n][i][j]);
          std::cout<<Form("; sqrt binContent: ") << binContentEpd[n][i][j]<<std::endl;
        } else{
          binErrorEpd[n][i][j] =0; // Error proagation;
          std::cout<<Form("profile_correlation_n%d_epd_east%d binNumber%d sqrt binError: ",n+1,i,j+1) << binErrorEpd[n][i][j];
          binContentEpd[n][i][j]=0;
          std::cout<<Form("; sqrt binContent: ") << binContentEpd[n][i][j]<<std::endl;
        }
      }
    }
  }
  for(int i=0;i<4;i++){
    for(int j=0;j<_Ncentralities;j++){
      for(int n=0;n<2;n++){
        if(binContentTpc[n][i][j]>0){ // make sure bin content is not negative to sqrt
          binErrorTpc[n][i][j] *=1./(2.*sqrt(binContentTpc[n][i][j])); // Error proagation;
          std::cout<<Form("profile_correlation_n%d_epd%d_tpc binNumber%d sqrt binError: ",n+1,i+1,j+1) << binErrorTpc[n][i][j];
          binContentTpc[n][i][j]=sqrt(binContentTpc[n][i][j]);
          std::cout<<Form("; sqrt binContent: ") << binContentTpc[n][i][j]<<std::endl;
        } else{
          binErrorTpc[n][i][j] =0; // Error proagation;
          std::cout<<Form("profile_correlation_n%d_epd%d_tpc binNumber%d sqrt binError: ",n+1,i+1,j+1) << binErrorTpc[n][i][j];
          binContentTpc[n][i][j]=0;
          std::cout<<Form("; sqrt binContent: ") << binContentTpc[n][i][j]<<std::endl;
        }
      }
    }
  }

  // ------------------ Fill into historgrams ----------------------------------
  TFile* outFile = new TFile("./res/res_sysErr/sys_etaGap_var2_iter2_CorrResult.root","RECREATE");
  TH1D *hist_correlation_epd_east[2][6], *hist_correlation_epd_tpc[2][4];
  TCanvas* c1[5];
  TLegend *legend[5];
  for(int i=0;i<5;i++){
    c1[i] = new TCanvas(Form("c1_%d",i),Form("Event Plane Resolutions %d",i+1),200,10,700,500);
    c1[i]->GetFrame()->SetFillColor(21);
    c1[i]->GetFrame()->SetBorderSize(12);
    c1[i]->DrawFrame(0., 0.01, 80., 0.7);
    legend[i] = new TLegend(0.1,0.7,0.48,0.9);
  }
  Double_t x[_Ncentralities]  = {2.5,7.5,15,25,35,45,55,65,75};
  Double_t ex[_Ncentralities] = {2.5,2.5,5,5,5,5,5,5,5};
  Double_t y1_1[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y1_2[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y1_3[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey1_1[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey1_2[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey1_3[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y2_1[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y2_2[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y2_3[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey2_1[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey2_2[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey2_3[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y3_1[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y3_2[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y3_3[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey3_1[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey3_2[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey3_3[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y4_1[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y4_2[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y4_3[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey4_1[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey4_2[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey4_3[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y5_1[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y5_2[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t y5_3[2][_Ncentralities]  = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey5_1[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey5_2[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
  Double_t ey5_3[2][_Ncentralities] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};

  TGraphErrors *gr1[2][3],*gr2[2][3],*gr3[2][3],*gr4[2][3],*gr5[2][4];
  for(int i=0;i<6;i++){
    for(int n=0; n<2;n++){
      hist_correlation_epd_east[n][i] = new TH1D(Form("hist_correlation_%d_epd_east%d",n+1,i),Form("hist_correlation_%d_epd_east%d",n+1,i),_Ncentralities,0.5,_Ncentralities+.5);
    }
  }
  for(int i=0;i<4;i++){
    for(int n=0; n<2;n++){
      hist_correlation_epd_tpc[n][i] = new TH1D(Form("hist_correlation_%d_epd_tpc%d",n+1,i),Form("hist_correlation_%d_epd_tpc%d",n+1,i),_Ncentralities,0.5,_Ncentralities+.5);
    }
  }
  for(int n=0; n<2;n++){
    hist_correlation_epd_east[n][0]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-1} #minus #psi_{1}^{EPD-2}))>}", n+1));
    hist_correlation_epd_east[n][1]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-1} #minus #psi_{1}^{EPD-3}))>}", n+1));
    hist_correlation_epd_east[n][2]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-1} #minus #psi_{1}^{EPD-4}))>}", n+1));
    hist_correlation_epd_east[n][3]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-2} #minus #psi_{1}^{EPD-3}))>}", n+1));
    hist_correlation_epd_east[n][4]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-2} #minus #psi_{1}^{EPD-4}))>}", n+1));
    hist_correlation_epd_east[n][5]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-3} #minus #psi_{1}^{EPD-4}))>}", n+1));
    hist_correlation_epd_tpc[n][0]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-1} #minus #psi_{1}^{TPC}))>}", n+1));
    hist_correlation_epd_tpc[n][1]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-2} #minus #psi_{1}^{TPC}))>}", n+1));
    hist_correlation_epd_tpc[n][2]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-3} #minus #psi_{1}^{TPC}))>}", n+1));
    hist_correlation_epd_tpc[n][3]->SetTitle(Form("#sqrt{<cos(%d * (#psi_{1}^{EPD-4} #minus #psi_{1}^{TPC}))>}", n+1));
  }
  for(int i=0;i<6;i++){
    for(int j=0;j<_Ncentralities;j++){
        for(int n=0; n<2;n++){
          if(binErrorEpd[n][i][j]!=0){
          hist_correlation_epd_east[n][i]->SetBinContent(j+1,binContentEpd[n][i][j]);
          hist_correlation_epd_east[n][i]->SetBinError(j+1,binErrorEpd[n][i][j]);
        }
      }
    }
  }
  for(int i=0;i<4;i++){
    for(int j=0;j<_Ncentralities;j++){
        for(int n=0; n<2;n++){
          if(binErrorTpc[n][i][j]!=0){
          hist_correlation_epd_tpc[n][i]->SetBinContent(j+1,binContentTpc[n][i][j]);
          hist_correlation_epd_tpc[n][i]->SetBinError(j+1,binErrorTpc[n][i][j]);
        }
      }
    }
  }
  // EPD ep  resolutions
  //binContentEpd[0,1,2,3,4,5] corresponds to correlations of epd subs {1 2,1 3,1 4,2 3,2 4,3 4}
  //binContentTpc[0,1,2,3] corresponds to correlations of epd subs & tpc {1 t, 2 t, 3 t, 4 t}

  Double_t ep1Reso[2][3][_Ncentralities]; // binContentEpd[0,1,2][j] * binContentTpc[0][j] / binContentTpc[1,2,3][j]
  Double_t  ep1Err[2][3][_Ncentralities]; // binErrorEpd[0,1,2][j] * binErrorTpc[0][j] / binErrorTpc[1,2,3][j]
  Double_t ep2Reso[2][3][_Ncentralities]; // binContentEpd[0,3,4][j] * binContentTpc[1][j] / binContentTpc[0,2,3][j]
  Double_t  ep2Err[2][3][_Ncentralities]; // binErrorEpd[0,3,4][j] * binErrorTpc[1][j] / binErrorTpc[0,2,3][j]
  Double_t ep3Reso[2][3][_Ncentralities]; // binContentEpd[1,3,5][j] * binContentTpc[2][j] / binContentTpc[0,1,3][j]
  Double_t  ep3Err[2][3][_Ncentralities]; // binErrorEpd[1,3,5][j] * binErrorTpc[2][j] / binErrorTpc[0,1,3][j]
  Double_t ep4Reso[2][3][_Ncentralities]; // binContentEpd[2,4,5][j] * binContentTpc[3][j] / binContentTpc[0,1,2][j]
  Double_t  ep4Err[2][3][_Ncentralities]; // binErrorEpd[2,4,5][j] * binErrorTpc[3][j] / binErrorTpc[0,1,2][j]
  Double_t ep5Reso[2][3][_Ncentralities]; // binContentTpc[0,1,2][j] * binContentTpc[1,2,3][j] / binContentEpd[0,3,5][j]
  Double_t  ep5Err[2][3][_Ncentralities]; // binErrorTpc[0,1,2][j] * binErrorTpc[1,2,3][j] / binErrorEpd[0,3,5][j]
  for(int j=0;j<_Ncentralities;j++){
    for(int i=0;i<3;i++){
      int order2_1 = 0; // EPD 2 reso
      int order2_2 = 0; // EPD 2 reso
      int order3_1 = 2 * i + 1; // 1, 3, 5 // EPD 3 reso
      int order3_2 = 0; // EPD 3 reso
      int order4_1 = 2; // EPD 4 reso
      int order4_2 = i; // EPD 4 reso // 0, 1, 2
      int order5_1 = 0; //i; // TPC reso // 0, 1, 2 // TPC VS EPD-1& EPD-2
      int order5_2 = 2; //i+1; // TPC reso // 1, 2, 3 // TPC VS EPD-1& EPD-2
      int order5_3 = 1; //0; // TPC reso // TPC VS EPD-1& EPD-2
      if(i>0){
        order2_1 = i+2; // 0, 3, 4
        order2_2 = i+1; // 0, 2, 3
        order3_2 = 2*i-1; // 0, 1, 3
        order4_1 += i+1; // 2, 4, 5
        order5_3 = 1;//2*i+1; // 0, 3, 5 // TPC VS EPD-1& EPD-2
      }
      for(int n=0; n<2;n++){
        if(binErrorEpd[n][i][j]!=0&&binErrorTpc[n][0][j]!=0&&binErrorTpc[n][i+1][j]!=0){ // EPD 1 VS EPD {2,3,4} & TPC
          ep1Reso[n][i][j] = resoVal(binContentEpd[n][i][j],binContentTpc[n][0][j],binContentTpc[n][i+1][j]);
          ep1Err[n][i][j]= resoErr(binContentEpd[n][i][j],binContentTpc[n][0][j],binContentTpc[n][i+1][j],
                                binErrorEpd[n][i][j],binErrorTpc[n][0][j],binErrorTpc[n][i+1][j]);
        }
        if(binErrorEpd[n][order2_1][j]!=0&&binErrorTpc[n][1][j]!=0&&binErrorTpc[n][order2_2][j]!=0){ // EPD 2 VS EPD {1,3,4} & TPC
          ep2Reso[n][i][j] = resoVal(binContentEpd[n][order2_1][j],binContentTpc[n][1][j],binContentTpc[n][order2_2][j]);
          ep2Err[n][i][j]= resoErr(binContentEpd[n][order2_1][j],binContentTpc[n][1][j],binContentTpc[n][order2_2][j],
                                binErrorEpd[n][order2_1][j],binErrorTpc[n][1][j],binErrorTpc[n][order2_2][j]);
        }
        if(binErrorEpd[n][order3_1][j]!=0&&binErrorTpc[n][2][j]!=0&&binErrorTpc[n][order2_2][j]!=0){ // EPD 3 VS EPD {1,2,4} & TPC
          ep3Reso[n][i][j] = resoVal(binContentEpd[n][order3_1][j],binContentTpc[n][2][j],binContentTpc[n][order2_2][j]);
          ep3Err[n][i][j]= resoErr(binContentEpd[n][order3_1][j],binContentTpc[n][2][j],binContentTpc[n][order2_2][j],
                                binErrorEpd[n][order3_1][j],binErrorTpc[n][2][j],binErrorTpc[n][order2_2][j]);
        }
        if(binErrorEpd[n][order4_1][j]!=0&&binErrorTpc[n][3][j]!=0&&binErrorTpc[n][order4_2][j]!=0){ // EPD 4 VS EPD {1, 2, 3} & TPC
          ep4Reso[n][i][j] = resoVal(binContentEpd[n][order4_1][j],binContentTpc[n][3][j],binContentTpc[n][order4_2][j]);
          ep4Err[n][i][j]= resoErr(binContentEpd[n][order4_1][j],binContentTpc[n][3][j],binContentTpc[n][order4_2][j],
                                binErrorEpd[n][order4_1][j],binErrorTpc[n][3][j],binErrorTpc[n][order4_2][j]);
        }
        if(binErrorTpc[n][order5_1][j]!=0&&binErrorTpc[n][order5_2][j]!=0&&binErrorEpd[n][order5_3][j]!=0){ // TPC VS EPD {1, 2, 3} & EPD {2, 3, 4}
          ep5Reso[n][i][j] = resoVal(binContentTpc[n][order5_1][j],binContentTpc[n][order5_2][j],binContentEpd[n][order5_3][j]);
          ep5Err[n][i][j]= resoErr(binContentTpc[n][order5_1][j],binContentTpc[n][order5_2][j],binContentEpd[n][order5_3][j],
                                binErrorTpc[n][order5_1][j],binErrorTpc[n][order5_2][j],binErrorEpd[n][order5_3][j]);
        }
      }
    }
  }
  cout<<"resolution = {";
  for(int j=0;j<_Ncentralities;j++){
    for(int n=0; n<2;n++){
       y1_1[n][j]=ep1Reso[n][0][j];
      ey1_1[n][j]=ep1Err[n][0][j];
       y2_1[n][j]=ep2Reso[n][0][j];
      ey2_1[n][j]=ep2Err[n][0][j];
       y3_1[n][j]=ep3Reso[n][0][j];
       // if(n==0)cout<<y3_1[n][j]<<","; // EPD 3, 1 TPC
      ey3_1[n][j]=ep3Err[n][0][j];
       y4_1[n][j]=ep4Reso[n][0][j];
      ey4_1[n][j]=ep4Err[n][0][j];
       y5_1[n][j]=ep5Reso[n][0][j];
      ey5_1[n][j]=ep5Err[n][0][j];

       y1_2[n][j]=ep1Reso[n][1][j];
      if(n==0)cout<<y1_2[n][j]<<","; // EPD 1, 3 TPC. n == 0 R1,
     ey1_2[n][j]=ep1Err[n][1][j];
      y2_2[n][j]=ep2Reso[n][1][j];
     ey2_2[n][j]=ep2Err[n][1][j];
      y3_2[n][j]=ep3Reso[n][1][j];
     ey3_2[n][j]=ep3Err[n][1][j];
      y4_2[n][j]=ep4Reso[n][1][j];
     ey4_2[n][j]=ep4Err[n][1][j];
      y5_2[n][j]=ep5Reso[n][1][j];
     ey5_2[n][j]=ep5Err[n][1][j];

      y1_3[n][j]=ep1Reso[n][2][j];
     ey1_3[n][j]=ep1Err[n][2][j];
      y2_3[n][j]=ep2Reso[n][2][j];
     ey2_3[n][j]=ep2Err[n][2][j];
      y3_3[n][j]=ep3Reso[n][2][j];
     ey3_3[n][j]=ep3Err[n][2][j];
      y4_3[n][j]=ep4Reso[n][2][j];
     ey4_3[n][j]=ep4Err[n][2][j];
      y5_3[n][j]=ep5Reso[n][2][j];
     ey5_3[n][j]=ep5Err[n][2][j];
    }
  }
  cout<<"}"<<endl;
  // ey3_1[5]=0;
  for(int n=0; n<2;n++){
    Double_t d_y1_1[_Ncentralities] ={
      y1_1[n][0],y1_1[n][1],y1_1[n][2],
      y1_1[n][3],y1_1[n][4],y1_1[n][5],
      y1_1[n][6],y1_1[n][7],y1_1[n][8],
    };
    Double_t d_ey1_1[_Ncentralities] ={
      ey1_1[n][0],ey1_1[n][1],ey1_1[n][2],
      ey1_1[n][3],ey1_1[n][4],ey1_1[n][5],
      ey1_1[n][6],ey1_1[n][7],ey1_1[n][8],
    };
    gr1[n][0] = new TGraphErrors(_Ncentralities,x,d_y1_1,ex,d_ey1_1);
    gr1[n][0]->SetTitle("EPD sub1 event plane ");
    gr1[n][0]->SetMarkerColor(3*n+1);
    gr1[n][0]->SetMarkerStyle(21);
    Double_t d_y1_2[_Ncentralities] ={
      y1_2[n][0],y1_2[n][1],y1_2[n][2],
      y1_2[n][3],y1_2[n][4],y1_2[n][5],
      y1_2[n][6],y1_2[n][7],y1_2[n][8],
    };
    Double_t d_ey1_2[_Ncentralities] ={
      ey1_2[n][0],ey1_2[n][1],ey1_2[n][2],
      ey1_2[n][3],ey1_2[n][4],ey1_2[n][5],
      ey1_2[n][6],ey1_2[n][7],ey1_2[n][8],
    };
    gr1[n][1] = new TGraphErrors(_Ncentralities,x,d_y1_2,ex,d_ey1_2);
    gr1[n][1]->SetTitle("EPD sub1 event plane ");
    gr1[n][1]->SetMarkerColor(2*n+2);
    gr1[n][1]->SetMarkerStyle(22);
    Double_t d_y1_3[_Ncentralities] ={
      y1_3[n][0],y1_3[n][1],y1_3[n][2],
      y1_3[n][3],y1_3[n][4],y1_3[n][5],
      y1_3[n][6],y1_3[n][7],y1_3[n][8],
    };
    Double_t d_ey1_3[_Ncentralities] ={
      ey1_3[n][0],ey1_3[n][1],ey1_3[n][2],
      ey1_3[n][3],ey1_3[n][4],ey1_3[n][5],
      ey1_3[n][6],ey1_3[n][7],ey1_3[n][8],
    };
    gr1[n][2] = new TGraphErrors(_Ncentralities,x,d_y1_3,ex,d_ey1_3);
    gr1[n][2]->SetTitle("EPD sub1 event plane ");
    gr1[n][2]->SetMarkerColor(3*n+3);
    gr1[n][2]->SetMarkerStyle(23);
    Double_t d_y2_1[_Ncentralities] ={
      y2_1[n][0],y2_1[n][1],y2_1[n][2],
      y2_1[n][3],y2_1[n][4],y2_1[n][5],
      y2_1[n][6],y2_1[n][7],y2_1[n][8],
    };
    Double_t d_ey2_1[_Ncentralities] ={
      ey2_1[n][0],ey2_1[n][1],ey2_1[n][2],
      ey2_1[n][3],ey2_1[n][4],ey2_1[n][5],
      ey2_1[n][6],ey2_1[n][7],ey2_1[n][8],
    };
    gr2[n][0] = new TGraphErrors(_Ncentralities,x,d_y2_1,ex,d_ey2_1);
    gr2[n][0]->SetTitle("EPD sub2 event plane ");
    gr2[n][0]->SetMarkerColor(3*n+1);
    gr2[n][0]->SetMarkerStyle(21);
    Double_t d_y2_2[_Ncentralities] ={
      y2_2[n][0],y2_2[n][1],y2_2[n][2],
      y2_2[n][3],y2_2[n][4],y2_2[n][5],
      y2_2[n][6],y2_2[n][7],y2_2[n][8],
    };
    Double_t d_ey2_2[_Ncentralities] ={
      ey2_2[n][0],ey2_2[n][1],ey2_2[n][2],
      ey2_2[n][3],ey2_2[n][4],ey2_2[n][5],
      ey2_2[n][6],ey2_2[n][7],ey2_2[n][8],
    };
    gr2[n][1] = new TGraphErrors(_Ncentralities,x,d_y2_2,ex,d_ey2_2);
    gr2[n][1]->SetTitle("EPD sub2 event plane ");
    gr2[n][1]->SetMarkerColor(3*n+2);
    gr2[n][1]->SetMarkerStyle(22);
    Double_t d_y2_3[_Ncentralities] ={
      y2_3[n][0],y2_3[n][1],y2_3[n][2],
      y2_3[n][3],y2_3[n][4],y2_3[n][5],
      y2_3[n][6],y2_3[n][7],y2_3[n][8],
    };
    Double_t d_ey2_3[_Ncentralities] ={
      ey2_3[n][0],ey2_3[n][1],ey2_3[n][2],
      ey2_3[n][3],ey2_3[n][4],ey2_3[n][5],
      ey2_3[n][6],ey2_3[n][7],ey2_3[n][8],
    };
    gr2[n][2] = new TGraphErrors(_Ncentralities,x,d_y2_3,ex,d_ey2_3);
    gr2[n][2]->SetTitle("EPD sub2 event plane ");
    gr2[n][2]->SetMarkerColor(3*n+3);
    gr2[n][2]->SetMarkerStyle(23);
    Double_t d_y3_1[_Ncentralities] ={
      y3_1[n][0],y3_1[n][1],y3_1[n][2],
      y3_1[n][3],y3_1[n][4],y3_1[n][5],
      y3_1[n][6],y3_1[n][7],y3_1[n][8],
    };
    Double_t d_ey3_1[_Ncentralities] ={
      ey3_1[n][0],ey3_1[n][1],ey3_1[n][2],
      ey3_1[n][3],ey3_1[n][4],ey3_1[n][5],
      ey3_1[n][6],ey3_1[n][7],ey3_1[n][8],
    };
    gr3[n][0] = new TGraphErrors(_Ncentralities,x,d_y3_1,ex,d_ey3_1);
    gr3[n][0]->SetTitle("EPD sub3 event plane ");
    gr3[n][0]->SetMarkerColor(3*n+1);
    gr3[n][0]->SetMarkerStyle(21);
    Double_t d_y3_2[_Ncentralities] ={
      y3_2[n][0],y3_2[n][1],y3_2[n][2],
      y3_2[n][3],y3_2[n][4],y3_2[n][5],
      y3_2[n][6],y3_2[n][7],y3_2[n][8],
    };
    Double_t d_ey3_2[_Ncentralities] ={
      ey3_2[n][0],ey3_2[n][1],ey3_2[n][2],
      ey3_2[n][3],ey3_2[n][4],ey3_2[n][5],
      ey3_2[n][6],ey3_2[n][7],ey3_2[n][8],
    };
    gr3[n][1] = new TGraphErrors(_Ncentralities,x,d_y3_2,ex,d_ey3_2);
    gr3[n][1]->SetTitle("EPD sub3 event plane ");
    gr3[n][1]->SetMarkerColor(3*n+2);
    gr3[n][1]->SetMarkerStyle(22);
    Double_t d_y3_3[_Ncentralities] ={
      y3_3[n][0],y3_3[n][1],y3_3[n][2],
      y3_3[n][3],y3_3[n][4],y3_3[n][5],
      y3_3[n][6],y3_3[n][7],y3_3[n][8],
    };
    Double_t d_ey3_3[_Ncentralities] ={
      ey3_3[n][0],ey3_3[n][1],ey3_3[n][2],
      ey3_3[n][3],ey3_3[n][4],ey3_3[n][5],
      ey3_3[n][6],ey3_3[n][7],ey3_3[n][8],
    };
    gr3[n][2] = new TGraphErrors(_Ncentralities,x,d_y3_3,ex,d_ey3_3);
    gr3[n][2]->SetTitle("EPD sub3 event plane ");
    gr3[n][2]->SetMarkerColor(3*n+3);
    gr3[n][2]->SetMarkerStyle(23);
    Double_t d_y4_1[_Ncentralities] ={
      y4_1[n][0],y4_1[n][1],y4_1[n][2],
      y4_1[n][3],y4_1[n][4],y4_1[n][5],
      y4_1[n][6],y4_1[n][7],y4_1[n][8],
    };
    Double_t d_ey4_1[_Ncentralities] ={
      ey4_1[n][0],ey4_1[n][1],ey4_1[n][2],
      ey4_1[n][3],ey4_1[n][4],ey4_1[n][5],
      ey4_1[n][6],ey4_1[n][7],ey4_1[n][8],
    };
    gr4[n][0] = new TGraphErrors(_Ncentralities,x,d_y4_1,ex,d_ey4_1);
    gr4[n][0]->SetTitle("EPD sub4 event plane ");
    gr4[n][0]->SetMarkerColor(3*n+1);
    gr4[n][0]->SetMarkerStyle(21);
    Double_t d_y4_2[_Ncentralities] ={
      y4_2[n][0],y4_2[n][1],y4_2[n][2],
      y4_2[n][3],y4_2[n][4],y4_2[n][5],
      y4_2[n][6],y4_2[n][7],y4_2[n][8],
    };
    Double_t d_ey4_2[_Ncentralities] ={
      ey4_2[n][0],ey4_2[n][1],ey4_2[n][2],
      ey4_2[n][3],ey4_2[n][4],ey4_2[n][5],
      ey4_2[n][6],ey4_2[n][7],ey4_2[n][8],
    };
    gr4[n][1] = new TGraphErrors(_Ncentralities,x,d_y4_2,ex,d_ey4_2);
    gr4[n][1]->SetTitle("EPD sub4 event plane ");
    gr4[n][1]->SetMarkerColor(3*n+2);
    gr4[n][1]->SetMarkerStyle(22);
    Double_t d_y4_3[_Ncentralities] ={
      y4_3[n][0],y4_3[n][1],y4_3[n][2],
      y4_3[n][3],y4_3[n][4],y4_3[n][5],
      y4_3[n][6],y4_3[n][7],y4_3[n][8],
    };
    Double_t d_ey4_3[_Ncentralities] ={
      ey4_3[n][0],ey4_3[n][1],ey4_3[n][2],
      ey4_3[n][3],ey4_3[n][4],ey4_3[n][5],
      ey4_3[n][6],ey4_3[n][7],ey4_3[n][8],
    };
    gr4[n][2] = new TGraphErrors(_Ncentralities,x,d_y4_3,ex,d_ey4_3);
    gr4[n][2]->SetTitle("EPD sub4 event plane ");
    gr4[n][2]->SetMarkerColor(3*n+3);
    gr4[n][2]->SetMarkerStyle(23);
    Double_t d_y5_1[_Ncentralities] ={
      y5_1[n][0],y5_1[n][1],y5_1[n][2],
      y5_1[n][3],y5_1[n][4],y5_1[n][5],
      y5_1[n][6],y5_1[n][7],y5_1[n][8],
    };
    Double_t d_ey5_1[_Ncentralities] ={
      ey5_1[n][0],ey5_1[n][1],ey5_1[n][2],
      ey5_1[n][3],ey5_1[n][4],ey5_1[n][5],
      ey5_1[n][6],ey5_1[n][7],ey5_1[n][8],
    };
    gr5[n][0] = new TGraphErrors(_Ncentralities,x,d_y5_1,ex,d_ey5_1);
    gr5[n][0]->SetTitle("TPC event plane ");
    gr5[n][0]->SetMarkerColor(3*n+1);
    gr5[n][0]->SetMarkerStyle(21);
    Double_t d_y5_2[_Ncentralities] ={
      y5_2[n][0],y5_2[n][1],y5_2[n][2],
      y5_2[n][3],y5_2[n][4],y5_2[n][5],
      y5_2[n][6],y5_2[n][7],y5_2[n][8],
    };
    Double_t d_ey5_2[_Ncentralities] ={
      ey5_2[n][0],ey5_2[n][1],ey5_2[n][2],
      ey5_2[n][3],ey5_2[n][4],ey5_2[n][5],
      ey5_2[n][6],ey5_2[n][7],ey5_2[n][8],
    };
    gr5[n][1] = new TGraphErrors(_Ncentralities,x,d_y5_2,ex,d_ey5_2);
    gr5[n][1]->SetTitle("TPC event plane ");
    gr5[n][1]->SetMarkerColor(3*n+2);
    gr5[n][1]->SetMarkerStyle(22);
    Double_t d_y5_3[_Ncentralities] ={
      y5_3[n][0],y5_3[n][1],y5_3[n][2],
      y5_3[n][3],y5_3[n][4],y5_3[n][5],
      y5_3[n][6],y5_3[n][7],y5_3[n][8],
    };
    Double_t d_ey5_3[_Ncentralities] ={
      ey5_3[n][0],ey5_3[n][1],ey5_3[n][2],
      ey5_3[n][3],ey5_3[n][4],ey5_3[n][5],
      ey5_3[n][6],ey5_3[n][7],ey5_3[n][8],
    };
    gr5[n][2] = new TGraphErrors(_Ncentralities,x,d_y5_3,ex,d_ey5_3);
    gr5[n][2]->SetTitle("TPC event plane ");
    gr5[n][2]->SetMarkerColor(3*n+3);
    gr5[n][2]->SetMarkerStyle(23);
  }
  // legend[0]->AddEntry(gr1[0][0],"R_{1} EPD-1 VS EPD-2 & TPC","p");
  legend[0]->AddEntry(gr1[0][1],"R_{1} EPD-1 VS EPD-2 & TPC","p");
  // legend[0]->AddEntry(gr1[0][2],"R_{1} EPD-1 VS EPD-4 & TPC","p");
  legend[1]->AddEntry(gr2[0][0],"R_{1} EPD-2 VS EPD-1 & TPC","p");
  legend[1]->AddEntry(gr2[0][1],"R_{1} EPD-2 VS EPD-3 & TPC","p");
  legend[1]->AddEntry(gr2[0][2],"R_{1} EPD-2 VS EPD-4 & TPC","p");
  legend[2]->AddEntry(gr3[0][0],"R_{1} EPD-3 VS EPD-1 & TPC","p");
  legend[2]->AddEntry(gr3[0][1],"R_{1} EPD-3 VS EPD-2 & TPC","p");
  legend[2]->AddEntry(gr3[0][2],"R_{1} EPD-3 VS EPD-4 & TPC","p");
  legend[3]->AddEntry(gr4[0][0],"R_{1} EPD-4 VS EPD-1 & TPC","p");
  legend[3]->AddEntry(gr4[0][1],"R_{1} EPD-4 VS EPD-2 & TPC","p");
  legend[3]->AddEntry(gr4[0][2],"R_{1} EPD-4 VS EPD-3 & TPC","p");
  legend[4]->AddEntry(gr5[0][0],"R_{1} TPC VS EPD-1 & EPD-2","p");
  legend[4]->AddEntry(gr5[0][1],"R_{1} TPC VS EPD-2 & EPD-3","p");
  legend[4]->AddEntry(gr5[0][2],"R_{1} TPC VS EPD-3 & EPD-4","p");
  // legend[0]->AddEntry(gr1[1][0],"R_{2} EPD-1 VS EPD-2 & TPC","p");
  legend[0]->AddEntry(gr1[1][1],"R_{2} EPD-1 VS EPD-2 & TPC","p");
  // legend[0]->AddEntry(gr1[1][2],"R_{2} EPD-1 VS EPD-4 & TPC","p");
  legend[1]->AddEntry(gr2[1][0],"R_{2} EPD-2 VS EPD-1 & TPC","p");
  legend[1]->AddEntry(gr2[1][1],"R_{2} EPD-2 VS EPD-3 & TPC","p");
  legend[1]->AddEntry(gr2[1][2],"R_{2} EPD-2 VS EPD-4 & TPC","p");
  legend[2]->AddEntry(gr3[1][0],"R_{2} EPD-3 VS EPD-1 & TPC","p");
  legend[2]->AddEntry(gr3[1][1],"R_{2} EPD-3 VS EPD-2 & TPC","p");
  legend[2]->AddEntry(gr3[1][2],"R_{2} EPD-3 VS EPD-4 & TPC","p");
  legend[3]->AddEntry(gr4[1][0],"R_{2} EPD-4 VS EPD-1 & TPC","p");
  legend[3]->AddEntry(gr4[1][1],"R_{2} EPD-4 VS EPD-2 & TPC","p");
  legend[3]->AddEntry(gr4[1][2],"R_{2} EPD-4 VS EPD-3 & TPC","p");
  legend[4]->AddEntry(gr5[1][0],"R_{2} TPC VS EPD-1 & EPD-2","p");
  legend[4]->AddEntry(gr5[1][1],"R_{2} TPC VS EPD-2 & EPD-3","p");
  legend[4]->AddEntry(gr5[1][2],"R_{2} TPC VS EPD-3 & EPD-4","p");
  c1[0]->cd();
  // gr1[0][0]->Draw("P");
  gr1[0][1]->Draw("P");
  // gr1[0][2]->Draw("P");
  // gr1[1][0]->Draw("P");
  gr1[1][1]->Draw("P");
  // gr1[1][2]->Draw("P");
  legend[0]->Draw();
  c1[1]->cd();
  gr2[0][0]->Draw("P");
  gr2[0][1]->Draw("P");
  gr2[0][2]->Draw("P");
  gr2[1][0]->Draw("P");
  gr2[1][1]->Draw("P");
  gr2[1][2]->Draw("P");
  legend[1]->Draw();
  c1[2]->cd();
  gr3[0][0]->Draw("P");
  gr3[0][1]->Draw("P");
  gr3[0][2]->Draw("P");
  gr3[1][0]->Draw("P");
  gr3[1][1]->Draw("P");
  gr3[1][2]->Draw("P");
  legend[2]->Draw();
  c1[3]->cd();
  gr4[0][0]->Draw("P");
  gr4[0][1]->Draw("P");
  gr4[0][2]->Draw("P");
  gr4[1][0]->Draw("P");
  gr4[1][1]->Draw("P");
  gr4[1][2]->Draw("P");
  legend[3]->Draw();
  c1[4]->cd();
  gr5[0][0]->Draw("P");
  gr5[0][1]->Draw("P");
  gr5[0][2]->Draw("P");
  gr5[1][0]->Draw("P");
  gr5[1][1]->Draw("P");
  gr5[1][2]->Draw("P");
  legend[4]->Draw();

  for(int i=0;i<5;i++){
    c1[i]->Write();
  }
  outFile->Write();
  return 0;
}

Double_t resoErr(Double_t corrAB, Double_t corrAC, Double_t corrBC, Double_t errAB, Double_t errAC, Double_t errBC){
  Double_t error = -999.;
  if(corrBC!=0){
    error = corrAC / corrBC * errAB
                 + corrAB / corrBC * errAC
                 - corrAB * corrAC / (corrBC * corrBC) * errBC;
  }
  return error;
}
Double_t resoVal(Double_t corrAB, Double_t corrAC, Double_t corrBC){
  Double_t resolution = -999.;
  if(corrBC!=0){
    resolution = corrAB * corrAC / corrBC;
  }
  return resolution;
}
