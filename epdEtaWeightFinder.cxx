#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TH1.h"
#include "TMath.h"
const int _Ncentralities = 9;
const double _y_mid = -2.02;
double myFuntion( double *x, double*p);

int epdEtaWeightFinder(){
  TFile* inFile = new TFile("./src/etaWeightEpd3Input.root","READ");
  TProfile *ProfileInput[_Ncentralities];
  TH1D     *myHist[_Ncentralities];
  TCanvas* c1[_Ncentralities];

  for(int i =0 ;i<_Ncentralities;i++){
    c1[i] = new TCanvas(Form("c%d",i),Form("c%d",i),800,600);
    ProfileInput[i]=(TProfile*)inFile->Get(Form("profile_v1VsEta_cent%d",i));
    myHist[i] = new TH1D(Form("myHist%d",i),Form("myHist%d",i),40,-7.0,3.0);
  }
  TF1 * tf1_v1VsEta = new TF1("tf1_v1VsEta",myFuntion,-4.6,1.0,2);
  tf1_v1VsEta->SetParameter(0,1.0);
  tf1_v1VsEta->SetParameter(1,-1.0);
  for(int cent=0;cent<_Ncentralities;cent++){
    for(int i=0;i<40;i++){
      double binN = ProfileInput[cent]->GetBinContent(i+1);
      double binE = ProfileInput[cent]->GetBinContent(i+1);
      // cout <<Form(" bin%d content = ",i+1) << binN <<"\t"<<" error = " <<binE<<endl;
      if(i != 14 && i != 15 && i != 16 && i!= 17 && binE != 0){
        myHist[cent]->SetBinContent(i+1,binN);
        myHist[cent]->SetBinError(i+1,binE);
      }
    }
  }
  for(int i =0 ;i<_Ncentralities;i++){
    c1[i]->cd();
    myHist[i]->Draw();
    myHist[i]->Fit(tf1_v1VsEta,"E+","R",-4.6,1.0);
  }

  double lin[9] = {1.511,  1.408,      1.249, 3.214, 1.337, 2.056, 2.109, 2.125, 1.217};
  double cub[9] = {-0.2699, -0.2437, -0.2074, -0.5790, -0.2940, -0.4732, -0.5391, -0.4841, -0.2564};
  TH2D *v1WtaWt = new TH2D("Order1etaWeight","Order1etaWeight",200,-6.5,-1.5,_Ncentralities,0.5,0.5+_Ncentralities);
  for (int ix=1; ix<201; ix++){
    for (int iy=1; iy<10; iy++){
      double eta = v1WtaWt->GetXaxis()->GetBinCenter(ix);
      v1WtaWt->SetBinContent(ix,iy,lin[iy-1]*(eta-_y_mid)+cub[iy-1]*pow((eta-_y_mid),3));
    }
  }
  TCanvas *c2 = new TCanvas("tc_2","tc_2",800,600);
  c2->cd();
  v1WtaWt->Draw("colz");

  // myHist=(TH1D*)inFile->Get("hist_realTrackMult");
  // Int_t binCenter[Ncentralities];
  // for(int i =0;i<Ncentralities;i++){
  //   binCenter[i]=0;
  // }
  // // Int_t binNumber[Ncentralities];
  // Double_t sections[Ncentralities];
  // Int_t Nentries = 0;
  // Int_t Ncounts = 0;
  // TLine* lines[Ncentralities];
  // for(Int_t i=(Int_t)myHist->FindBin(lowMult);i<=(Int_t)myHist->FindBin(pileUp);i++){
  //   Nentries+=(Int_t)myHist->GetBinContent(i);
  // }
  // for(Int_t cent =0; cent<Ncentralities;cent++){
  //   sections[cent] = (Double_t)(cent+1)*Nentries/Ncentralities;
  // }
  //
  // for(Int_t i=(Int_t)myHist->FindBin(lowMult);i<=(Int_t)myHist->FindBin(pileUp);i++){
  //   Ncounts+=(Int_t)myHist->GetBinContent(i);
  //   for(Int_t cent =Ncentralities-1; cent>=0;cent--){
  //     if(Ncounts>=sections[cent]){
  //       if(binCenter[cent]!=0)break;
  //       binCenter[cent]=i-1;//(Int_t)myHist->GetBinCenter(i);
  //       std::cout<<Form("Ncounts%d Section: ",cent)<< Ncounts <<std::endl; // Array to string?
  //
  //       break;
  //     }
  //   }
  //
  // }
  // std::string str;
  // std::string str1;
  //
  // for(Int_t i : binCenter){
  //   str += std::to_string(i);
  //   str += ",";
  // }
  // for(Int_t i : sections){
  //   str1 += std::to_string(i);
  //   str1 += ",";
  // }
  // std::cout<<"Bin number of pileUp: "<< (Int_t)myHist->FindBin(pileUp) <<std::endl; // Array to string?
  // std::cout<<"Total entries: "<< Nentries <<std::endl; // Array to string?
  // std::cout<<"Entries Section: "<< str1 <<std::endl; // Array to string?
  // std::cout<<"Centrality Section: "<< str <<std::endl; // Array to string?
  //
  // myHist->Draw();
  // for(Int_t cent = 0; cent<Ncentralities;cent++){
  //   lines[cent] = new TLine(binCenter[cent],0,binCenter[cent],myHist->GetMaximum());
  //   lines[cent]->SetLineColor(cent+1);
  //   lines[cent]->Draw("same");
  // }


  return 0;
}

double myFuntion( double *x, double*p){
  double y_CM = x[0] - _y_mid; // center of mass rapidity
  double directedFlow = p[1]*pow(y_CM,3) + p[0]*pow(y_CM,1);
  return directedFlow;
}
