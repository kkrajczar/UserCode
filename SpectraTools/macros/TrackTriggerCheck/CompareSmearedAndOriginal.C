//Gabor's alternative: have a single fit (to the original, and smear that and compare to the original)

double fitFunctionPtoP(double *x, double *par);
double fitRegion(double *x, double *par);
TF1* fitPtDist(TH1D *hPt);
void pseudoExperiment2(TF1 *fitTot, TH1D* histo);
void pseudoExperimentOrigAndSmeared(TF1 *fitTot, TH1D* h1, TH1D* h2, TH1D* h3);


void CompareSmearedAndOriginal() {

  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
  gStyle->SetOptLogy(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.26);

  bool doSave = true;

  TFile *f_NotSmeared = new TFile("PtSpectraCombination_StagedNormalization_TrackTrigger.root");
  TH1D * hSumPartPt_NotSmeared = (TH1D*)f_NotSmeared->Get("hSumPartPt");

  
  TCanvas *c3 = new TCanvas("c3","c3");
  c3->cd();
  c3->SetLogy();

  TH1D* hSumPartPt_NotSmeared_copy2 = (TH1D*)hSumPartPt_NotSmeared->Clone("hSumPartPt_NotSmeared_copy2");
  TF1 * fFitTot_original = fitPtDist(hSumPartPt_NotSmeared_copy2);

  fFitTot_original->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  fFitTot_original->GetYaxis()->SetTitle("1/N dN/dp_{T} (|#eta_{CM}|<1)");
  fFitTot_original->Draw("rl");
  hSumPartPt_NotSmeared_copy2->SetMarkerStyle(20);
  hSumPartPt_NotSmeared_copy2->Draw("same");

   TLegend *leg3 = new TLegend(0.6,0.65,0.95,0.95,NULL,"brNDC");
   leg3->AddEntry(fFitTot_original,"Combined fit","l");
   leg3->AddEntry(hSumPartPt_NotSmeared_copy2,"Track-triggered spectrum","pl");
   leg3->SetFillStyle(0);
   leg3->SetFillColor(0);
   leg3->SetBorderSize(0);
   leg3->Draw();
   if(doSave) {
      c3->SaveAs("Figs/CompareSmearedAndOriginal_c3.gif");
      c3->SaveAs("Figs/CompareSmearedAndOriginal_c3.eps");
      c3->SaveAs("Figs/CompareSmearedAndOriginal_c3.C");
   }



  TCanvas *c4 = new TCanvas("c4","c4");
  c4->cd();
  TH1D* hSumPartPt_NotSmeared_copy3 = (TH1D*)hSumPartPt_NotSmeared->Clone("hSumPartPt_NotSmeared_copy3");
  TH1D* hSumPartPt_Smeared_copy3 = (TH1D*)hSumPartPt_NotSmeared->Clone("hSumPartPt_Smeared_copy3");
  TH1D* hSumPartPt_Smeared2_copy3 = (TH1D*)hSumPartPt_NotSmeared->Clone("hSumPartPt_Smeared2_copy3");
  hSumPartPt_NotSmeared_copy3->Reset();
  hSumPartPt_Smeared_copy3->Reset();
  hSumPartPt_Smeared2_copy3->Reset();
  pseudoExperimentOrigAndSmeared(fFitTot_original,hSumPartPt_NotSmeared_copy3,hSumPartPt_Smeared_copy3,hSumPartPt_Smeared2_copy3);
  TH1D* hSumPartPt_NotSmeared_copy4 = (TH1D*)hSumPartPt_NotSmeared_copy3->Clone("hSumPartPt_NotSmeared_copy4");
  hSumPartPt_NotSmeared_copy3->Divide(hSumPartPt_Smeared_copy3);
  hSumPartPt_NotSmeared_copy4->Divide(hSumPartPt_Smeared2_copy3);
  hSumPartPt_NotSmeared_copy3->GetYaxis()->SetTitle("Not smeared / Smeared");
  hSumPartPt_NotSmeared_copy3->SetMinimum(0.9);
  hSumPartPt_NotSmeared_copy3->SetMaximum(1.1);
  hSumPartPt_NotSmeared_copy3->SetMarkerStyle(20);
  hSumPartPt_NotSmeared_copy3->Draw();
  hSumPartPt_NotSmeared_copy4->SetLineColor(2);
  hSumPartPt_NotSmeared_copy4->SetMarkerColor(2);
  hSumPartPt_NotSmeared_copy4->SetMarkerStyle(20);
  hSumPartPt_NotSmeared_copy4->Draw("same");
   TLegend *leg4 = new TLegend(0.6,0.65,0.95,0.95,NULL,"brNDC");
   leg4->AddEntry(hSumPartPt_NotSmeared_copy3,"Resolution parameterization","pl");
   leg4->AddEntry(hSumPartPt_NotSmeared_copy4,"Resolution parameterization + 1%","pl");
   leg4->SetFillStyle(0);
   leg4->SetFillColor(0);
   leg4->SetBorderSize(0);
   leg4->Draw();
   if(doSave) {
      c4->SaveAs("Figs/CompareSmearedAndOriginal_c4.gif");
      c4->SaveAs("Figs/CompareSmearedAndOriginal_c4.eps");
      c4->SaveAs("Figs/CompareSmearedAndOriginal_c4.C");
   }
}


TF1* fitPtDist(TH1D *hPt) {

//   TCanvas *c1 = new TCanvas("c1","c1");
//   c1->cd();
//   c1->SetLogy();

   TString fitFor1, fitFor2, fitFor3, fitFor4;
   fitFor1 = "[0]*exp([1]*x+[2])*pow((x+[3]),[4])";
   fitFor2 = "[0]*exp([1]*x+[2])*pow((x+[3]),[4])";
   fitFor3 = "[0]*exp([1]*x+[2])*pow((x+[3]),[4])";
   fitFor4 = "[0]*exp([1]*x+[2])*pow((x+[3]),[4])";

   TF1 *fFit1 = new TF1("fFit1",fitFor1.Data(),0.4,2.5);
   fFit1->SetParameters(9.06217e+00,9.40093e-02,2.29414e+01,5.10448e+00,-1.26023e+01);
   fFit1->SetLineWidth(3);
   hPt->Fit(fFit1,"RI+","same");
//   hPt->Fit(fFit1,"RI0+","same");

   TF1 *fFit2 = new TF1("fFit2",fitFor2.Data(),2.,7.);
   fFit2->SetParameters(1.10717e-01,-2.26225e-02,6.01220e+00,-5.03866e-01,-4.70703e+00);
   fFit2->SetLineWidth(3);
   fFit2->SetLineColor(4);
//   hPt->Fit(fFit2,"RI+","same");
   hPt->Fit(fFit2,"RI0+","same");

   TF1 *fFit3 = new TF1("fFit3",fitFor3.Data(),5.7,30.);
   fFit3->SetParameters(3.00352e-01,1.18402e-02,6.77614e+00,2.21791e-01,-5.46630e+00);
   fFit3->SetLineWidth(3);
   fFit3->SetLineColor(6);
//   hPt->Fit(fFit3,"RI+","same");
   hPt->Fit(fFit3,"RI0+","same");

   TF1 *fFit4 = new TF1("fFit4",fitFor4.Data(),25.,207.);//25.-100.
   fFit4->SetParameters(3.78254e-03,-1.41810e-02,7.52402e+0,-2.91151e+00,-4.34504e+00);
   fFit4->SetLineWidth(3);
   fFit4->SetLineColor(8);
//   hPt->Fit(fFit4,"RI+","same");
   hPt->Fit(fFit4,"RI0+","same");

   double par[23];
   fFit1->GetParameters(&par[0]);
   fFit2->GetParameters(&par[5]);
   fFit3->GetParameters(&par[10]);
   fFit4->GetParameters(&par[15]);

   //Check where is the difference between the fit functions is the smallest
   //Fit boundaries: 0.4-2.5, 2.-7., 5.7-30., 25.-100.;
   double fit1_r2 = 2.5;
   double fit2_r1 = 2., fit2_r2 = 7.;
   double fit3_r1 = 5.7, fit3_r2 = 30.;
   double fit4_r1 = 25.;

   int intvl = 200;

   double xr12 = 2.3, xr23 = 6.5, xr34 = 27.;
   double diffMin12 = 9999., diffMin23 = 9999., diffMin34 = 9999.;

   for(int i=0;i<intvl;i++) {
     // R12
     double x12 = fit2_r1 + ((i+1)/(float)intvl)*(fit1_r2-fit2_r1); // [fit2_r1,fit2_r1]
     double diff12 = fabs(fFit1->Eval(x12) - fFit2->Eval(x12));
     double deno12 = (fFit1->Eval(x12)>fFit2->Eval(x12)) ? fFit1->Eval(x12) : fFit2->Eval(x12);
     double fdiff12 = diff12/deno12; // fractional difference
     if(fdiff12<diffMin12) diffMin12 = fdiff12, xr12 = x12;

     // R23
     double x23 = fit3_r1 + ((i+1)/(float)intvl)*(fit2_r2-fit3_r1); // [fit3_r1,fit2_r2]
     double diff23 = fabs(fFit2->Eval(x23) - fFit3->Eval(x23));
     double deno23 = (fFit2->Eval(x23)>fFit3->Eval(x23)) ? fFit2->Eval(x23) : fFit3->Eval(x23);
     double fdiff23 = diff23/deno23; // fractional difference
     if(fdiff23<diffMin23) diffMin23 = fdiff23, xr23 = x23;

     // R34
     double x34 = fit4_r1 + ((i+1)/(float)intvl)*(fit3_r2-fit4_r1); // [fit4_r1,fit3_r2]
     double diff34 = fabs(fFit3->Eval(x34) - fFit4->Eval(x34));
     double deno34 = (fFit3->Eval(x34)>fFit4->Eval(x34)) ? fFit3->Eval(x34) : fFit4->Eval(x34);
     double fdiff34 = diff34/deno34; // fractional difference
     if(fdiff34<diffMin34) diffMin34 = fdiff34, xr34 = x34;
   }
   std::cerr<<" Minimum distance R12 " << diffMin12 << " at " << xr12 << std::endl;
   std::cerr<<" Minimum distance R23 " << diffMin23 << " at " << xr23 << std::endl;
   std::cerr<<" Minimum distance R34 " << diffMin34 << " at " << xr34 << std::endl;

   par[20] = xr12;
   par[21] = xr23;
   par[22] = xr34;

   fitTot = new TF1("fitTot",fitFunctionPtoP,0.4,207,23);//0.4,100.
   fitTot->SetParameters(par);
   fitTot->SetLineStyle(7);
   fitTot->SetLineWidth(2);
   fitTot->SetLineColor(1);
//   hPt->Fit(fitTot,"RI+","same");

//   fitTot->Draw("same");

   return fitTot;
}


double fitFunctionPtoP(double *x, double *par) {

  double y = 0.0;
  if(x[0]<par[20]) y = fitRegion(x,par);
  else if(x[0]<par[21]) y = fitRegion(x,&par[5]);
  else if(x[0]<par[22]) y = fitRegion(x,&par[10]);
  else y = fitRegion(x,&par[15]);

  return y;
}


double fitRegion(double *x, double *par) {
  return par[0]*exp(par[1]*x[0]+par[2])*pow((x[0]+par[3]),par[4]);
}


void pseudoExperiment2(TF1 *fitTot, TH1D* histo) {
  Int_t until = 1e+7;
  Int_t printout = 1e+6;
  for(int r = 0; r<=until; r++) {
     if (r % printout == 0) cout << r <<" / "<< until <<endl;
     Float_t random = gRandom->Uniform(0.4,207.);//0.4,104.
     double weight = fitTot->Eval(random);
     histo->Fill(random, weight);
  }
}


void pseudoExperimentOrigAndSmeared(TF1 *fitTot, TH1D* h1, TH1D* h2, TH1D* h3) {

  TF1 *fRes_original = new TF1("fRes_original","[0]*pow(x,[1])/(1+exp([2]*(x+[3])))+ [4]*pow(x,[5])");
  fRes_original->FixParameter(0,6.91047e-03);
  fRes_original->FixParameter(1,1.62838e-01);
  fRes_original->FixParameter(2,-7.82497e+03);
  fRes_original->FixParameter(3,7.09137e+03);
  fRes_original->FixParameter(4,5.12914e-03);
  fRes_original->FixParameter(5,-1.23678e+00);

  Int_t until = 1e+7;
  Int_t printout = 1e+6;
  for(int r = 0; r<=until; r++) {
     if (r % printout == 0) cout << r <<" / "<< until <<endl;

     //pt
     Float_t random = gRandom->Uniform(0.4,207.);//0.4,104.
     double weight = fitTot->Eval(random);
     h1->Fill(random, weight);

     //smeared pt, smearing overestimated for now
     Float_t random_smeared = gRandom->Gaus(random,random*fRes_original->Eval(random));
     Float_t random_smeared2 = gRandom->Gaus(random,random*(0.01+fRes_original->Eval(random)));
     double weight_smeared = fitTot->Eval(random_smeared);
     double weight_smeared2 = fitTot->Eval(random_smeared2);
     //smear the weight and keep the pt
     h2->Fill(random, weight_smeared);
     h3->Fill(random, weight_smeared2);
  }
}
