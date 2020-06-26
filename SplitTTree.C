// C++ headers
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

// ROOT headers
#include "TROOT.h"
#include "TObject.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TSystem.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TString.h"

class st_K : public TObject
{
public:
    st_K(){ reset(); }
    virtual ~st_K(){}
    bool b_pos_charge;
    bool b_bad_TOF;

    unsigned int runNumber;
    unsigned int eventNumber;
    unsigned int nGoodTracks;
    unsigned int nTrkvsCuts;

    float px;
    float py;
    float pz;

    float x_vtx;
    float y_vtx;
    float z_vtx;

    float tofBeta;
    float dEdxFit;
    float d_dEdxTru;
    float DCA_r;

    float d_TPCnSigmaKaon;
    float d_TOFnSigmaKaon;

    void reset()
    {
      b_pos_charge = 0;
      b_bad_TOF = 0;

      runNumber   = 0;
      eventNumber = 0;
      nGoodTracks = 0;
      nTrkvsCuts  = 0;

      px = 0.0;
      py = 0.0;
      pz = 0.0;

      x_vtx = 0.0;
      y_vtx = 0.0;
      z_vtx = 0.0;

      d_TPCnSigmaKaon = 0.0;
      d_TOFnSigmaKaon = 0.0;

      DCA_r = -9999.0;
    }

private:
    ClassDef(st_K,1);
};

using namespace std;

TFile * tf_in = 0;
TChain * t_K   = new TChain("t_K");

void SplitTTree(string FileName,
TString outFile = "test")
{
  if( FileName.find(".list") != string::npos ||
      FileName.find(".lis") != string::npos ) {

    std::ifstream inputStream( FileName.c_str() );

    if(!inputStream) {
      cout << "ERROR: Cannot open list file " << FileName << endl;
    }

  Int_t nFile = 0;
  string file;
  while(getline(inputStream, file)) {
    if(file.find(".root") != string::npos) {
      TFile* ftmp = TFile::Open(file.c_str());
      if(ftmp && !ftmp->IsZombie() && ftmp->GetNkeys()) {
        cout << " Read in picoDst file " << file << endl;
        t_K->Add(file.c_str());
        ++nFile;
      } //if(ftmp && !ftmp->IsZombie() && ftmp->GetNkeys())

      if (ftmp) {
        ftmp->Close();
      } //if (ftmp)
    } //if(file.find(".picoDst.root") != string::npos)
  } //while (getline(inputStream, file))

  cout << " Total " << nFile << " files have been read in. " << endl;
  } //if(FileName.find(".list") != string::npos || FileName.find(".lis" != string::npos))
  else if(FileName.find(".picoDst.result.root") != string::npos) {
    t_K->Add(FileName.c_str());
  }
  else {
    cout << " No good input file to read ... " << endl;
  }

  if( t_K->GetEntries() == 0 ){cout << "Error:Could not find 't_K' in file: " << FileName << endl; return;}

  outFile.Append(".readKTree.result.root");
  // outFile.Prepend("/star/data01/pwg/dchen/Ana/7p2GeV_FXT_2018/KKinvM/SplitKaonTree/");


  TFile *file = new TFile(outFile,"recreate");
  TTree *  t_kaon        = new TTree("t_kaon","t_kaon");
  st_K Kaoninfo;

  // t_kaon        -> Branch("Kaoninfo",&Kaoninfo);

  t_kaon->SetMaxTreeSize(150000);
  int N_entries = (t_K -> GetEntries());
  for( int i_entries = 0; i_entries< 100000; i_entries++)
  {
    t_K -> GetEntry(i_entries);
    t_kaon=t_K->CloneTree(); //loop

  }

  file = t_kaon->GetCurrentFile(); //to get the pointer to the current file
  file->Write();
  file->Close();

}
