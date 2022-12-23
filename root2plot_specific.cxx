// Define a function with three parameters.
double fitf(double *x,double *par) {
   //double arg = 0;
   //if (par[2]!=0) arg = (x[0] - par[1])/par[2];
   double fitval = par[0] + par[1] * x[0];
   return fitval;
}

void root2plot_specific(TString file = "Normal.picoDst.result.combined.root") {
   gStyle->SetOptFit(1);
   TFile *f1 = TFile::Open(file);
   TString fpdf = ".pdf" ;
   TString fout = file + fpdf;
   TIter keyList(f1->GetListOfKeys());
   TKey *key;
   TCanvas c1;
   c1.SetLogz();
   c1.Print(fout+'[');
   while ((key = (TKey*)keyList())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      TString ti = key->GetName();
      //cout << "title = " << ti <<endl;
      //if (cl->InheritsFrom("TH1")){ 
      if (ti=="AveZdcEastVsRunNum"){
      		TH1 *h = (TH1*)key->ReadObj();
      		h->Draw("colz");
      		c1.Print(fout);
      } else  
      if (ti=="AveBbcEastultVsRunNum"){
      		TH1 *h = (TH1*)key->ReadObj();
      		h->Draw("colz");
      		c1.Print(fout);
      } else  
      if (ti=="AveRefMultVsZdcEast_c"){
      		TH1 *h = (TH1*)key->ReadObj();
		h->Fit("pol1");
      		h->Draw("colz");
      		c1.Print(fout);
      } else  
      //if (cl->InheritsFrom("TH2")){
      if (ti=="AveRefMultVsBbcEast_c"){
      	TH1 *h = (TH2*)key->ReadObj();
		h->Fit("pol1");
      	h->Draw("colz");
      	c1.Print(fout);
      } else
      //if (cl->InheritsFrom("TH3")){
      if (ti=="h2_ZdcEastVsBbcEast_c"){
      	TH2 *h = (TH2*)key->ReadObj();
      	h->GetXaxis()->SetRangeUser(0,5000000);
      	h->Draw("colz");
	c1.SaveAs(file+"h2_ZdcEastVsBbcEast_c.png");
      	c1.Print(fout);
      } else continue;
      //if (cl->InheritsFrom("TTree")){
      //	TTree *t = (TTree*)key->ReadObj();
      //	TObjArray * branchList = t->GetListOfBranches();
      //	for(int i = 0; i < branchList->GetEntries() ; i++)
      //	  {
      //	  	 t->Draw(branchList->At(i)->GetName());
      //			 c1.Print(fout);
      //	  }
      //} else continue;
   }
   c1.Print(fout+']');
}
