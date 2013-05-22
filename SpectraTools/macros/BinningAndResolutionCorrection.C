//#include "hiForest.h"
//#include "utilities.h"
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>

TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den);
void RemoveLargeerrorPoints(TH1D *h_input);
double fitFunctionPtoP(double *x, double *par);
double fitRegion(double *x, double *par);
void normalizeByBinWidth(TH1D *histo);
void pseudoExperiment1(TF1 *fitTot, TH1D* histo);
void pseudoExperiment2(TF1 *fitTot, TH1D* histo);
void GaborsCrossCheck(TF1 *fitTot, TH1D* pseudoHist);
//------------------------

void BinningAndResolutionCorrection()
{

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
//   gStyle->SetPadRightMargin(0.16);
   gStyle->SetOptFit(0);

   bool doSave = true;

   TF1 *fRes = new TF1("fRes","[0]*pow(x,[1])/(1+exp([2]*(x+[3])))+ [4]*pow(x,[5])",0.6,90.);
   fRes->FixParameter(0,2.86898e-03);
   fRes->FixParameter(1,4.21716e-01);
   fRes->FixParameter(2,-1.31606e+05);
   fRes->FixParameter(3,2.42378e+00);
   fRes->FixParameter(4,3.83773e-02);
   fRes->FixParameter(5,-9.94852e-01);

   TFile *f_output = new TFile("BinningAndResolutionCorrection.root","recreate");

   TFile *f_input = new TFile("PtSpectraCombination_StagedNormalization.root");
   TH1D *hPt = (TH1D*)f_input->Get("hSumPartPt");

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->cd();
   c1->SetLogy();
   hPt->SetMarkerStyle(20);
   hPt->Draw();

   TString fitFor1, fitFor2, fitFor3, fitFor4;
   fitFor1 = "[0]*exp([1]*x+[2])*pow((x+[3]),[4])";
   fitFor2 = "[0]*exp([1]*x+[2])*pow((x+[3]),[4])";
   fitFor3 = "[0]*exp([1]*x+[2])*pow((x+[3]),[4])";
   fitFor4 = "[0]*exp([1]*x+[2])*pow((x+[3]),[4])";

   TF1 *fFit1 = new TF1("fFit1",fitFor1.Data(),0.4,2.5);
//   fFit1->SetParameters(1.,-1.,1.,0.,1.);
   fFit1->SetParameters(9.06217e+00,9.40093e-02,2.29414e+01,5.10448e+00,-1.26023e+01);
   fFit1->SetLineWidth(3);
   hPt->Fit(fFit1,"RI+","same");

   TF1 *fFit2 = new TF1("fFit2",fitFor2.Data(),2.,7.);
//   fFit2->SetParameters(1.,-1.,0.,0.,1);
   fFit2->SetParameters(1.10717e-01,-2.26225e-02,6.01220e+00,-5.03866e-01,-4.70703e+00);
   fFit2->SetLineWidth(3);
   fFit2->SetLineColor(4);
   hPt->Fit(fFit2,"RI+","same");

   TF1 *fFit3 = new TF1("fFit3",fitFor3.Data(),5.7,30.);
   fFit3->SetParameters(3.00352e-01,1.18402e-02,6.77614e+00,2.21791e-01,-5.46630e+00);
   fFit3->SetLineWidth(3);
   fFit3->SetLineColor(6);
   hPt->Fit(fFit3,"RI+","same");

   TF1 *fFit4 = new TF1("fFit4",fitFor4.Data(),25.,100.);
   fFit4->SetParameters(3.78254e-03,-1.41810e-02,7.52402e+0,-2.91151e+00,-4.34504e+00);
   fFit4->SetLineWidth(3);
   fFit4->SetLineColor(8);
   hPt->Fit(fFit4,"RI+","same");

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

   fitTot = new TF1("fitTot",fitFunctionPtoP,0.4,100,23);
   fitTot->SetParameters(par);
   fitTot->SetLineStyle(7);
   fitTot->SetLineWidth(2);
   fitTot->SetLineColor(1);
//   hPt->Fit(fitTot,"RI+","same");

   fitTot->Draw("same");
   TLegend *leg2 = new TLegend(0.5,0.7,0.8,0.9,NULL,"brNDC");
   leg2->AddEntry(fFit1,"p_{T}: 0.4 - 2.5 GeV/c","l");
   leg2->AddEntry(fFit2,"p_{T}: 2 - 7 GeV/c","l");
   leg2->AddEntry(fFit3,"p_{T}: 5.7 - 30 GeV/c","l");
   leg2->AddEntry(fFit4,"p_{T}: 25 - 100 GeV/c","l");
   leg2->AddEntry(fitTot,"Combined fit","l");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();
   if(doSave) {
      c1->SaveAs("Figs/BinningAndResolutionCorrection_c1.gif");
      c1->SaveAs("Figs/BinningAndResolutionCorrection_c1.eps");
      c1->SaveAs("Figs/BinningAndResolutionCorrection_c1.C");
   }


   TCanvas *c2 = new TCanvas("c2","c2");
   c2->cd();
   c2->SetLogx();
   TH1D *hPt_copy1 = (TH1D*)hPt->Clone("hPt_copy1");
   hPt_copy1->Divide(fitTot);
   hPt_copy1->SetMarkerColor(1);
   hPt_copy1->SetLineColor(1);
   hPt_copy1->GetYaxis()->SetTitle("Binning correction (histogram/fit)");
   hPt_copy1->SetMaximum(1.5);
   hPt_copy1->SetMinimum(0.5);
   hPt_copy1->Draw();
   if(doSave) {
      c2->SaveAs("Figs/BinningAndResolutionCorrection_c2.gif");
      c2->SaveAs("Figs/BinningAndResolutionCorrection_c2.eps");
      c2->SaveAs("Figs/BinningAndResolutionCorrection_c2.C");
   }

   //Run the pseudo experiment1
   TH1D * hPt_pseudo1 = (TH1D*)hPt->Clone("hPt_pseudo1");
   hPt_pseudo1->Reset();
   pseudoExperiment1(fitTot, hPt_pseudo1);   
   normalizeByBinWidth(hPt_pseudo1);
   TCanvas *c_r1 = new TCanvas("c_r1","c_r1");
   c_r1->cd();
   c_r1->SetLogy();
   hPt_pseudo1->Draw();
   if(doSave) {
      c_r1->SaveAs("Figs/BinningAndResolutionCorrection_c_r1.gif");
      c_r1->SaveAs("Figs/BinningAndResolutionCorrection_c_r1.eps");
      c_r1->SaveAs("Figs/BinningAndResolutionCorrection_c_r1.C");
   }

   TCanvas *c_r1_ratio = new TCanvas("c_r1_ratio","c_r1_ratio");
   c_r1_ratio->cd();
   c_r1_ratio->SetLogx();
   TH1D *hPt_pseudo1_copy1 = (TH1D*)hPt_pseudo1->Clone("hPt_pseudo1_copy1");
   hPt_pseudo1_copy1->Divide(fitTot);
   TF1 * fScale = new TF1("fScale","[0]",0.4,1.);
   hPt_pseudo1_copy1->Fit("fScale","R0");
   hPt_pseudo1_copy1->Scale(1./fScale->GetParameter(0));
   hPt_pseudo1_copy1->SetMinimum(0.5);
   hPt_pseudo1_copy1->SetMaximum(1.5);
   hPt_pseudo1_copy1->GetYaxis()->SetTitle("Binning correction from pseudo-exp1");
   hPt_pseudo1_copy1->Draw();
   if(doSave) {
      c_r1_ratio->SaveAs("Figs/BinningAndResolutionCorrection_c_r1_ratio.gif");
      c_r1_ratio->SaveAs("Figs/BinningAndResolutionCorrection_c_r1_ratio.eps");
      c_r1_ratio->SaveAs("Figs/BinningAndResolutionCorrection_c_r1_ratio.C");
   }

   //Run the pseudo experiment2
   TH1D * hPt_pseudo2 = (TH1D*)hPt->Clone("hPt_pseudo2");
   hPt_pseudo2->Reset();
   pseudoExperiment2(fitTot, hPt_pseudo2);   
   normalizeByBinWidth(hPt_pseudo2);
   TCanvas *c_r2 = new TCanvas("c_r2","c_r2");
   c_r2->cd();
   c_r2->SetLogy();
   hPt_pseudo2->Draw();
   if(doSave) {
      c_r2->SaveAs("Figs/BinningAndResolutionCorrection_c_r2.gif");
      c_r2->SaveAs("Figs/BinningAndResolutionCorrection_c_r2.eps");
      c_r2->SaveAs("Figs/BinningAndResolutionCorrection_c_r2.C");
   }

   TCanvas *c_r2_ratio = new TCanvas("c_r2_ratio","c_r2_ratio");
   c_r2_ratio->cd();
   c_r2_ratio->SetLogx();
   TH1D *hPt_pseudo2_copy1 = (TH1D*)hPt_pseudo2->Clone("hPt_pseudo2_copy1");
   hPt_pseudo2_copy1->Divide(fitTot);
   TF1 * fScale = new TF1("fScale","[0]",0.4,1.);
   hPt_pseudo2_copy1->Fit("fScale","R0");
   hPt_pseudo2_copy1->Scale(1./fScale->GetParameter(0));
   hPt_pseudo2_copy1->SetMinimum(0.5);
   hPt_pseudo2_copy1->SetMaximum(1.5);
   hPt_pseudo2_copy1->GetYaxis()->SetTitle("Binning correction from pseudo-exp2");
   hPt_pseudo2_copy1->Draw();
   if(doSave) {
      c_r2_ratio->SaveAs("Figs/BinningAndResolutionCorrection_c_r2_ratio.gif");
      c_r2_ratio->SaveAs("Figs/BinningAndResolutionCorrection_c_r2_ratio.eps");
      c_r2_ratio->SaveAs("Figs/BinningAndResolutionCorrection_c_r2_ratio.C");
   }

   f_output->cd();
   hPt_copy1->Write();
   fitTot->Write();
   hPt_pseudo1_copy1->Write();
   hPt_pseudo2_copy1->Write();
   f_output->Close();
}


TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den) {
   TH1D *h_ratio = (TH1D*)h_Num->Clone("h_ratio");
   h_ratio->Reset();
   for(int i = 1; i <= h_Num->GetNbinsX(); i++) {
      float content = h_Num->GetBinContent(i);
      float error = h_Num->GetBinError(i);
      float center = h_Num->GetBinCenter(i);
      int which_bin_in_h_Den = h_Den->FindBin(center);
      float content_h_Den = h_Den->GetBinContent(which_bin_in_h_Den);

      if(content_h_Den==0)
         continue;

      h_ratio->SetBinContent(i,content/content_h_Den);      
      h_ratio->SetBinError(i,error/content_h_Den);      
   }
   return h_ratio;
}


void convertToYield(TH1D* h_ppRef_LogLogpt, float sigma_inel) {

   for(int i = 1; i <= h_ppRef_LogLogpt->GetNbinsX(); i++) {
      float content_Ed3sigmadp3 = h_ppRef_LogLogpt->GetBinContent(i);
      float bincenter = h_ppRef_LogLogpt->GetBinCenter(i);
      //multiply by 2*pi*pT
      float content_d2sigmadetadpT = content_Ed3sigmadp3*2.*TMath::Pi()*bincenter;
      //multiply by 2: reference pp is for the average of the + and - particles
      content_d2sigmadetadpT *= 2.;
      //convert d2sigmadetadpT to d2NdetadpT
      float content_d2NdetadpT = content_d2sigmadetadpT/sigma_inel;
      //convert d2NdetadpT to dNdpT in |eta|<1
      content_d2NdetadpT *= 2.;
      h_ppRef_LogLogpt->SetBinContent(i,content_d2NdetadpT);
   }
}


void RemoveLargeerrorPoints(TH1D *h_input) {
  for(int i=1; i<=h_input->GetNbinsX(); i++) {
     if((h_input->GetBinError(i)/h_input->GetBinContent(i))>0.3) {
        h_input->SetBinContent(i,0);
        h_input->SetBinError(i,0);
     }
  }
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

void normalizeByBinWidth(TH1D *histo) {
   for(int i = 1; i <= histo->GetNbinsX(); i++) {
      float content = histo->GetBinContent(i);
      float error = histo->GetBinError(i);
      histo->SetBinContent(i,content/histo->GetBinWidth(i));
      histo->SetBinError(i,error/histo->GetBinWidth(i));
   }
}

void pseudoExperiment1(TF1 *fitTot, TH1D* histo) {
  Int_t until = 1e+8;
  Int_t printout = 1e+7;
  for(int r = 0; r<=until; r++) {
     if (r % printout == 0) cout << r <<" / "<< until <<endl;
     Float_t random = fitTot->GetRandom();
     histo->Fill(random);
  }
}

void pseudoExperiment2(TF1 *fitTot, TH1D* histo) {
  Int_t until = 1e+8;
  Int_t printout = 1e+7;
  for(int r = 0; r<=until; r++) {
     if (r % printout == 0) cout << r <<" / "<< until <<endl;
     Float_t random = gRandom->Uniform(0.4,104.);
     double weight = fitTot->Eval(random);
     histo->Fill(random, weight);
  }
}

void GaborsCrossCheck(TF1 *fitTot, TH1D* pseudoHist) {

}
