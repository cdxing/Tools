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
// Read and generate correlation and resolution of event planes version 2 for psi2
//
////////////////////////////////////////
using namespace std;

const int _Ncentralities = 9;
void corrFinder2(const TString TsInfile = "/mnt/c/Users/pjska/ana/27gev_Phi_flow/Tools/src/merged_EpCorrection_OUTPUT_sys_primary_var0_iter3_E138C24844B7DDCEED96CC428F859D64_.root",
                Int_t   inputp2 = 0, // sysErr cut Indexes 0-15
                Int_t   inputp3 = 0, // sysErr cut variations, each systematic check has 2 or 3 vertions
                Int_t   inputp4 = 3 // Iteration of the analysis is. In this analysis, 2 iterations is enough

)
{
  // gStyle->SetOptStat(0);
  // gStyle->SetOptDate(0);
  // gStyle->SetEndErrorSize(6);
  // gStyle->SetOptTitle(0);
  Int_t sys_cutN = inputp2; // sysErr cut Indexes 0-15
  Int_t sys_varN = inputp3; // sysErr cut variations, each systematic check has 2 or 3 vertions
  Int_t sys_iterN = inputp4; // Iteration of the analysis is. In this analysis, 2 iterations is enough
  string sys_object[17]  = {"primary", "etaGap", "etaRange",
                            "vz", "vr", "dedx", "dca",
                            "nHitsFit", "ratio", "nSigK", "mass2",
                            "pT", "dipAngle", "vtxDiff", "mthdDiff",
                            "binning",
                            "TPCpid"};
  TFile* inFile = new TFile(TsInfile,"READ");
  std::cout << "sys_cutN == "<< sys_cutN <<": "<< sys_object[sys_cutN] << std::endl;
  if (inFile->IsZombie())  cout << "Error opening file" << endl;
  TString outTxt = "./out_resolution/Resolution_INPUT_sys_";
  outTxt.Append(sys_object[sys_cutN]);
  outTxt.Append(Form("_var%d_iter%d_", sys_varN, sys_iterN));
  TString TsOutFile = outTxt;
  outTxt.Append(".txt");
  std::ofstream reso_file(outTxt,ofstream::out);

  TsOutFile.Append(".picoDst.result.root");
  // TsOutFile.Prepend("./res_v2p1_pTrange/");
  TFile* outFile = new TFile(TsOutFile,"RECREATE");

  TProfile *profile_correlation_psi2_tpcAB, *profile_correlation_psi2_epd_tpc_2,
   *profile_correlation_psi2_epd_tpc_1;
   TH1D *h_correlation_psi2_tpcAB, *h_correlation_psi2_epd_tpc_2,
    *h_correlation_psi2_epd_tpc_1;
   profile_correlation_psi2_tpcAB = (TProfile*)inFile->Get(Form("profile_correlation_n2_tpc_A_tpc_B"));
   h_correlation_psi2_tpcAB = new TH1D("h_correlation_psi2_tpcAB","h_correlation_psi2_tpcAB",9,0,9);
   for(int i=1;i<=_Ncentralities;i++){
     h_correlation_psi2_tpcAB->SetBinContent(i,(double)profile_correlation_psi2_tpcAB->GetBinContent(i));
     h_correlation_psi2_tpcAB->SetBinError(i,(double)profile_correlation_psi2_tpcAB->GetBinError(i));
   }
   // TPC A
   TH1D *h_correlation_psi2_tpcAB_clone = (TH1D*)h_correlation_psi2_tpcAB->Clone("h_correlation_psi2_tpcAB");
   h_correlation_psi2_tpcAB_clone->Draw();


   TH1D *h_resolution_A, *h_resolution_B, *h_resolution_C;
   h_resolution_A = new TH1D("h_resolution_A","resolution TPC A",9,0,9);

   // reso_file<<"psi_2^TPC-A resolution:" << endl << "{";
   for(int i=1;i<=_Ncentralities;i++){ // TPC-A
     double content = h_correlation_psi2_tpcAB_clone->GetBinContent(i);
     double error = h_correlation_psi2_tpcAB_clone->GetBinError(i);
     if (content > 0){
       content = sqrt(content);
       error = 0.5 / content * error;
       cout << ", " << content;
       reso_file<< content <<endl ;
       h_resolution_A->SetBinContent(i,content);
       h_resolution_A->SetBinError(i,error);
     } else{
       reso_file<< 1. <<endl ;
     }
   }
   cout<< endl;
   // reso_file<< "}" << endl << endl;
   h_resolution_A->Draw();

   // reso_file<<"psi_2^EPD resolution:" << endl << "{";
   outFile->Write();
   reso_file.close();

}
