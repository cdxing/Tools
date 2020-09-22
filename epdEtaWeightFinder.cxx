#include <iostream>
#include <fstream>
#include <string>

#include "TFile.h"
#include "TH1.h"
#include "TMath.h"
#include "TPad.h"
const int _Ncentralities = 9;
const double _y_mid = -2.03;
const double _gap = -3.66;
double myFuntion( double *x, double*p);
double myFuntion1( double *x, double*p);
double myFuntion2( double *x, double*p);
void setpad(TPad *pad, float left, float right, float top, float bottom)
{
   pad->SetFillColor(10);
   pad->SetBorderMode(0);
   pad->SetBorderSize(0);
   pad->SetFrameFillColor(10);
   pad->SetFrameBorderMode(0);
   pad->SetFrameBorderSize(0);
   pad->SetLeftMargin(left);
   pad->SetRightMargin(right);
   pad->SetTopMargin(top);
   pad->SetBottomMargin(bottom);
}
int epdEtaWeightFinder(){
  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.15);
  gStyle->SetLabelSize(.06, "XY");

  TFile* inFile = new TFile("./res/Epd_tpc_eta_newEPD_2_new_corrINPUT.root","READ");
  TProfile *ProfileInput[_Ncentralities];
  TH1D     *myHist[_Ncentralities];
  // TCanvas* c1[_Ncentralities];
  TCanvas* c3 = new TCanvas("c3","tc_3",200,10,1920,1080);

  c3->Divide(3,3,0,0);
  // c3->SetFrameBorderMode(0);
  for(int i =0 ;i<_Ncentralities;i++){
    // c1[i] = new TCanvas(Form("c%d",i),Form("c%d",i),800,600);
    ProfileInput[i]=(TProfile*)inFile->Get(Form("profile_v1VsEta_cent%d",i));
    myHist[i] = new TH1D(Form("myHist%d",i),Form("myHist%d",i),40,-7.0,3.0);
  }
  myHist[0]->SetTitle("0-5%");
  myHist[1]->SetTitle("5-10%");
  myHist[2]->SetTitle("10-20%");
  myHist[3]->SetTitle("20-30%");
  myHist[4]->SetTitle("30-40%");
  myHist[5]->SetTitle("40-50%");
  myHist[6]->SetTitle("50-60%");
  myHist[7]->SetTitle("60-70%");
  myHist[8]->SetTitle("70-80%");

  TF1 * tf1_v1VsEta = new TF1("tf1_v1VsEta",myFuntion,-6.0,0.0,2);
  tf1_v1VsEta->SetParameter(0,1.0);
  tf1_v1VsEta->SetParameter(1,-1.0);
  TF1 * tf1_v1VsEtalin = new TF1("tf1_v1VsEtalin",myFuntion,-6.,0.0,2);
  tf1_v1VsEtalin->SetParameter(0,1.0);
  tf1_v1VsEtalin->SetParameter(1,-1.0);
  TF1 * tf1_v1VsEtaCom = new TF1("tf1_v1VsEtaCom",myFuntion,-6.,0.0,2);
  tf1_v1VsEtaCom->SetParameter(0,1.0);
  tf1_v1VsEtaCom->SetParameter(1,-1.0);

  double lin[9];
  double cub[9];

  double pr0[9];
  double pr1[9];
  double pr2[9];
  double pr3[9];
  // double pen[9];

  for(int cent=0;cent<_Ncentralities;cent++){
    for(int i=0;i<40;i++){
      double binN = ProfileInput[cent]->GetBinContent(i+1);
      double binE = ProfileInput[cent]->GetBinError(i+1);
      cout <<Form(" bin%d content = ",i+1) << binN <<"\t"<<" error = " <<binE<<endl;
      if(/*i != 21 && i != 15 && i != 16 && i!= 17 &&*/ binE != 0){
        myHist[cent]->SetBinContent(i+1,binN);
        myHist[cent]->SetBinError(i+1,binE);
      }
    }
  }
  TLine *tl[_Ncentralities];
  TLine *t2[_Ncentralities];
  // setpad(c3->cd(1),0,0.33,1,0.66);
  // c3->cd(2)->setpad(0.33,0.66,1,0.66);
  // c3->cd(3)->setpad(0.66,1,1,0.66);
  // c3->cd(4)->setpad(0,0.33,0.66,0.33);
  // c3->cd(5)->setpad(0.33,0.66,0.66,0.33);
  // c3->cd(6)->setpad(0.66,1,0.66,0.33);
  // c3->cd(7)->setpad(0,0.33,0.33,0);
  // c3->cd(8)->setpad(0.33,0.66,0.33,0);
  // c3->cd(9)->setpad(0.66,1,0.33,0);
  for(int i =0 ;i<_Ncentralities;i++){
    // gROOT->Reset();
    // gStyle->SetOptStat(0);
    // gStyle->SetOptTitle(0);
    // c1[i]->SetGridy();
    // c1[i]->cd();
    c3->cd(i+1);
    // TPad* pad = (TPad*)c3->GetPad(i+1);
    // pad->SetLeftMargin(0.15);
    // pad->SetBottomMargin(0.12);
    // pad->SetTopMargin(0.04);
    // pad->SetRightMargin(0.02);
    // pad->SetFillColor(0);
    // pad->SetBorderMode(1);
    // c3->cd(i+1)->SetGridy();
    // myHist[i]->SetTitle(Form("Cent-%d",i+1));
    if(i == 3||i ==7){
      myHist[i]->GetXaxis()->SetTitle("#eta");
      myHist[i]->GetYaxis()->SetTitle("< #phi - #psi_{1}^{EPD-1}>");
    }
    myHist[i]->GetXaxis()->SetRangeUser(-5.,0.);
    myHist[i]->GetYaxis()->SetRangeUser(-0.03,0.03);
    myHist[i]->GetXaxis()->SetTitleSize(0.08);
    myHist[i]->GetYaxis()->SetTitleSize(0.08);
    myHist[i]->GetXaxis()->SetTitleOffset(0.5);
    myHist[i]->GetYaxis()->SetTitleOffset(0.5);
    myHist[i]->Draw();
    // myHist[i]->Fit(tf1_v1VsEta,"E+","R",-4.75,_y_mid);
    // tf1_v1VsEtalin->SetLineColor(4);
    // myHist[i]->Fit(tf1_v1VsEtalin,"E+","R",_y_mid,0);
    // tf1_v1VsEtaCom->SetLineColor(6);
    // myHist[i]->Fit(tf1_v1VsEtaCom,"E+","R",-4.75,0);
    pr0[i]=tf1_v1VsEta->GetParameter(0);
    pr1[i]=tf1_v1VsEta->GetParameter(1);
    // pr2[i]=tf1_v1VsEtaCom->GetParameter(2);
    // pr3[i]=tf1_v1VsEtaCom->GetParameter(3);

    lin[i]=tf1_v1VsEta->GetParameter(0);
    // lin[i]*=10000;
    cub[i]=tf1_v1VsEta->GetParameter(1);
    // cub[i]*=10000;
    // pen[i]=tf1_v1VsEta->GetParameter(2);
    tl[i] = new TLine(_y_mid,-0.03,_y_mid,0.03);
    tl[i] ->SetLineColor(1);
    tl[i] ->SetLineStyle(2);
    tl[i] ->Draw("same");
    t2[i] = new TLine(-5,0.,0.6,0);
    t2[i] ->SetLineColor(1);
    t2[i] ->SetLineStyle(2);
    t2[i] ->Draw("same");  }
  // string sp0(lin);
  // string sp1(cub);


  std::cout<< "lin[9] =" << "\t" <<"{" ;
  for(int i =0 ;i<_Ncentralities;i++){
    std::cout<< lin[i] << ",";
  }
  std::cout<< "}" <<std::endl;
  std::cout<< "cub[9] =" << "\t" <<"{" ;
  for(int i =0 ;i<_Ncentralities;i++){
    std::cout<< cub[i] << ",";
  }
  std::cout<< "}" <<std::endl;

  // std::cout<< "pr0[9] =" << "\t" <<"{" ;
  // for(int i =0 ;i<_Ncentralities;i++){
  //   std::cout<< pr0[i]*10000 << ",";
  // }
  // std::cout<< "};" <<std::endl;
  //
  // std::cout<< "pr1[9] =" << "\t" <<"{" ;
  // for(int i =0 ;i<_Ncentralities;i++){
  //   std::cout<< pr1[i]*10000 << ",";
  // }
  // std::cout<< "};" <<std::endl;
  // std::cout<< "pr2[9] =" << "\t" <<"{" ;
  // for(int i =0 ;i<_Ncentralities;i++){
  //   std::cout<< pr2[i] << ",";
  // }
  // std::cout<< "};" <<std::endl;
  // std::cout<< "pr3[9] =" << "\t" <<"{" ;
  // for(int i =0 ;i<_Ncentralities;i++){
  //   std::cout<< pr3[i] << ",";
  // }
  // std::cout<< "};" <<std::endl;
  TH2D *v1WtaWt = new TH2D("Order1etaWeight","Order1etaWeight",200,-6.5,-1.5,_Ncentralities,0.5,0.5+_Ncentralities);
  TH1D *v1WtaWtCent[9];
  for(int i = 0;i<_Ncentralities;i++){
    v1WtaWtCent[i] = new TH1D(Form("v1WtaWtCent%d",i),Form("v1WtaWtCent%d",i),200,-6.5,-1.5);
  }

  for (int ix=1; ix<201; ix++){
    for (int iy=1; iy<10; iy++){
      double eta = v1WtaWt->GetXaxis()->GetBinCenter(ix);
      // v1WtaWt->SetBinContent(ix,iy,lin[iy-1]*(eta-_y_mid)+cub[iy-1]*pow((eta-_y_mid),3)/*+pen[iy-1]*pow((eta-_y_mid),5)*/);
      // if(eta>=_gap){
      //   v1WtaWt->SetBinContent(ix,iy,pr3[iy-1]*pow(eta-_y_mid,3) + pr2[iy-1]*pow(eta-_y_mid,1));
      //   v1WtaWtCent[iy-1]->SetBinContent(ix,pr3[iy-1]*pow(eta-_y_mid,3) + pr2[iy-1]*pow(eta-_y_mid,1));
      // } else {
        v1WtaWt->SetBinContent(ix,iy,cub[iy-1]*pow(eta-_y_mid,3) + lin[iy-1]*pow(eta-_y_mid,1));
        v1WtaWtCent[iy-1]->SetBinContent(ix,cub[iy-1]*pow(eta-_y_mid,3) + lin[iy-1]*pow(eta-_y_mid,1));
      // }
      // v1WtaWt->SetBinContent(ix,iy,lin[iy-1]*(eta-_y_mid)+cub[iy-1]*pow((eta-_y_mid),3)/*+pen[iy-1]*pow((eta-_y_mid),5)*/);
    }
  }
  TCanvas *c2 = new TCanvas("tc_2","tc_2",800,600);
  c2->cd();
  v1WtaWt->Draw("colz");
  // TCanvas *c4 = new TCanvas("tc_4","tc_4",1600,1200);
  // c4->Divide(3,3);
  // for(int i=0;i<_Ncentralities;i++){
  //   c4->cd(i+1);
  //   v1WtaWtCent[i]->Draw();
  // }

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
  double directedFlow = /*p[2]*pow(y_CM,5)*/ + p[1]*pow(y_CM,3) + p[0]*pow(y_CM,1);
  return directedFlow;
}
double myFuntion1( double *x, double*p){
  double y_CM = x[0] - _y_mid; // center of mass rapidity
  double directedFlow = /*p[2]*pow(y_CM,5)*/ + p[1]*pow(y_CM,1) + p[0]*pow(y_CM,1);
  return directedFlow;
}
double myFuntion2( double *x, double*p){
  double y_CM = x[0] - _y_mid; // center of mass rapidity
  double directedFlow = /*p[2]*pow(y_CM,5)*/ + p[1]*pow(y_CM,3) + p[0]*pow(y_CM,1);
  return directedFlow;
}
