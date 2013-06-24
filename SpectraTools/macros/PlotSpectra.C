#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <fstream>
#include <TLegend.h>
#include <TLatex.h>
#include <TLine.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TMath.h>

TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den);
TH1D* singleReference(TH1D* hPtbased, TH1D* hXtbased);
TGraphErrors* drawErrorBoxes(TH1 *hist);
void drawBox(Double_t y, Double_t err, Double_t x, Double_t width, Int_t color);
std::pair<TGraphErrors*,TGraphErrors*> readInData(char * name);
void drawTickError(TH1 *hist, TGraphErrors *tg);
void drawTick(Double_t Y, Double_t Erru, Double_t Errd, Double_t X, Double_t Tick_x, Double_t Tick_y, Int_t TickColor);
void convertToInvYield(TH1D *hist);
void convertToYield(TH1D* h_ppRef_LogLogpt, float sigma_inel);
TH1D* From_xT_to_pT_histo(TH1D *h_input, TH1D *h_binning, double sqrts, double exp);
TH1D* castRefIntoMeasHist(TH1D* ppRef, TH1D* pPbMeas);
void setupHistProperties(TH1D * hist, Int_t color, Int_t style, double scale);
//------------------------

void PlotSpectra()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.28);
//   gStyle->SetPadRightMargin(0.16);
   gStyle->SetErrorX(0);
//   gStyle->SetEndErrorSize(10.);

   //Get pp reference
   TFile *f_ppRef_pt = new TFile("output_interpolation_KK_LogFitForC6.root");
   TFile *f_ppRef_xt = new TFile("output_interpolation_KK_LogFitForC6_TryExtrapolationInXT.root");

   TH1D* h_ppRef_LogLogpt = (TH1D*)f_ppRef_pt->Get("h5020_To100GeV_FromLogFit"); //including CDF data
   convertToYield(h_ppRef_LogLogpt,70.0); // Sigma_inel at 5.02 TeV

   TH1D* h_ppRef_LogLogxt = (TH1D*)f_ppRef_xt->Get("h5020_FromLogFit");
   TH1D *h_ppRef_LogLogxt_pt = From_xT_to_pT_histo(h_ppRef_LogLogxt,h_ppRef_LogLogpt,5020.,4.9);
   convertToYield(h_ppRef_LogLogxt_pt,70.0); // Sigma_inel at 5.02 TeV

   TH1D * combinedRef = singleReference(h_ppRef_LogLogpt,h_ppRef_LogLogxt_pt);

   //Get pPb spectrum
   TFile *f_CombpPbPbp_TrackTriggered_EtaCM_M1_P1 = new TFile("TrackTriggerCheck/PtSpectraCombination_StagedNormalization_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");
   TFile *f_CombpPbPbp_TrackTriggered_EtaCM_M03_M08 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_M03_M08_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");
   TFile *f_CombpPbPbp_TrackTriggered_EtaCM_P03_P08 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_P03_P08_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");
   TFile *f_CombpPbPbp_TrackTriggered_EtaCM_M08_M13 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_M08_M13_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");
   TFile *f_CombpPbPbp_TrackTriggered_EtaCM_P08_P13 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");
   TFile *f_CombpPbPbp_TrackTriggered_EtaCM_M13_M18 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_M13_M18_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");
   TFile *f_CombpPbPbp_TrackTriggered_EtaCM_P13_P18 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_P13_P18_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");

   TFile *f_pPb_TrackTriggered_EtaCM_M1_P1 = new TFile("TrackTriggerCheck/PtSpectraCombination_StagedNormalization_NoOLDAlignmentRuns_TrackTrigger.root");
   TFile *f_pPb_TrackTriggered_EtaCM_M03_M08 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_M03_M08_NoOLDAlignmentRuns_TrackTrigger.root");
   TFile *f_pPb_TrackTriggered_EtaCM_P03_P08 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_P03_P08_NoOLDAlignmentRuns_TrackTrigger.root");
   TFile *f_pPb_TrackTriggered_EtaCM_M08_M13 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_M08_M13_NoOLDAlignmentRuns_TrackTrigger.root");
   TFile *f_pPb_TrackTriggered_EtaCM_P08_P13 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_NoOLDAlignmentRuns_TrackTrigger.root");
   TFile *f_pPb_TrackTriggered_EtaCM_M13_M18 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_M13_M18_NoOLDAlignmentRuns_TrackTrigger.root");
   TFile *f_pPb_TrackTriggered_EtaCM_P13_P18 = new TFile("TrackTriggerCheck/Asym/PtSpectraCombination_StagedNormalization_EtaCM_P13_P18_NoOLDAlignmentRuns_TrackTrigger.root");

   TFile *f_Pbp_TrackTriggered_EtaCM_M1_P1 = new TFile("TrackTriggerCheck/Asym/ReverseBeam/PtSpectraCombination_StagedNormalization_TrackTrigger.root");
   TFile *f_Pbp_TrackTriggered_EtaCM_M03_M08 = new TFile("TrackTriggerCheck/Asym/ReverseBeam/PtSpectraCombination_StagedNormalization_EtaCM_M03_M08_TrackTrigger.root");
   TFile *f_Pbp_TrackTriggered_EtaCM_P03_P08 = new TFile("TrackTriggerCheck/Asym/ReverseBeam/PtSpectraCombination_StagedNormalization_EtaCM_P03_P08_TrackTrigger.root");
   TFile *f_Pbp_TrackTriggered_EtaCM_M08_M13 = new TFile("TrackTriggerCheck/Asym/ReverseBeam/PtSpectraCombination_StagedNormalization_EtaCM_M08_M13_TrackTrigger.root");
   TFile *f_Pbp_TrackTriggered_EtaCM_P08_P13 = new TFile("TrackTriggerCheck/Asym/ReverseBeam/PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_TrackTrigger.root");
   TFile *f_Pbp_TrackTriggered_EtaCM_M13_M18 = new TFile("TrackTriggerCheck/Asym/ReverseBeam/PtSpectraCombination_StagedNormalization_EtaCM_M13_M18_TrackTrigger.root");
   TFile *f_Pbp_TrackTriggered_EtaCM_P13_P18 = new TFile("TrackTriggerCheck/Asym/ReverseBeam/PtSpectraCombination_StagedNormalization_EtaCM_P13_P18_TrackTrigger.root");

   TH1D *hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1 = (TH1D*)f_CombpPbPbp_TrackTriggered_EtaCM_M1_P1->Get("hSumPartPt");
   TH1D *hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08 = (TH1D*)f_CombpPbPbp_TrackTriggered_EtaCM_M03_M08->Get("hSumPartPt");
   TH1D *hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08 = (TH1D*)f_CombpPbPbp_TrackTriggered_EtaCM_P03_P08->Get("hSumPartPt");
   TH1D *hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13 = (TH1D*)f_CombpPbPbp_TrackTriggered_EtaCM_M08_M13->Get("hSumPartPt");
   TH1D *hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13 = (TH1D*)f_CombpPbPbp_TrackTriggered_EtaCM_P08_P13->Get("hSumPartPt");
   TH1D *hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18 = (TH1D*)f_CombpPbPbp_TrackTriggered_EtaCM_M13_M18->Get("hSumPartPt");
   TH1D *hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18 = (TH1D*)f_CombpPbPbp_TrackTriggered_EtaCM_P13_P18->Get("hSumPartPt");

   TH1D *hCombined_pPb_TrackTriggered_EtaCM_M1_P1 = (TH1D*)f_pPb_TrackTriggered_EtaCM_M1_P1->Get("hSumPartPt");
   TH1D *hCombined_pPb_TrackTriggered_EtaCM_M03_M08 = (TH1D*)f_pPb_TrackTriggered_EtaCM_M03_M08->Get("hSumPartPt");
   TH1D *hCombined_pPb_TrackTriggered_EtaCM_P03_P08 = (TH1D*)f_pPb_TrackTriggered_EtaCM_P03_P08->Get("hSumPartPt");
   TH1D *hCombined_pPb_TrackTriggered_EtaCM_M08_M13 = (TH1D*)f_pPb_TrackTriggered_EtaCM_M08_M13->Get("hSumPartPt");
   TH1D *hCombined_pPb_TrackTriggered_EtaCM_P08_P13 = (TH1D*)f_pPb_TrackTriggered_EtaCM_P08_P13->Get("hSumPartPt");
   TH1D *hCombined_pPb_TrackTriggered_EtaCM_M13_M18 = (TH1D*)f_pPb_TrackTriggered_EtaCM_M13_M18->Get("hSumPartPt");
   TH1D *hCombined_pPb_TrackTriggered_EtaCM_P13_P18 = (TH1D*)f_pPb_TrackTriggered_EtaCM_P13_P18->Get("hSumPartPt");

   TH1D *hCombined_Pbp_TrackTriggered_EtaCM_M1_P1 = (TH1D*)f_Pbp_TrackTriggered_EtaCM_M1_P1->Get("hSumPartPt");
   TH1D *hCombined_Pbp_TrackTriggered_EtaCM_M03_M08 = (TH1D*)f_Pbp_TrackTriggered_EtaCM_M03_M08->Get("hSumPartPt");
   TH1D *hCombined_Pbp_TrackTriggered_EtaCM_P03_P08 = (TH1D*)f_Pbp_TrackTriggered_EtaCM_P03_P08->Get("hSumPartPt");
   TH1D *hCombined_Pbp_TrackTriggered_EtaCM_M08_M13 = (TH1D*)f_Pbp_TrackTriggered_EtaCM_M08_M13->Get("hSumPartPt");
   TH1D *hCombined_Pbp_TrackTriggered_EtaCM_P08_P13 = (TH1D*)f_Pbp_TrackTriggered_EtaCM_P08_P13->Get("hSumPartPt");
   TH1D *hCombined_Pbp_TrackTriggered_EtaCM_M13_M18 = (TH1D*)f_Pbp_TrackTriggered_EtaCM_M13_M18->Get("hSumPartPt");
   TH1D *hCombined_Pbp_TrackTriggered_EtaCM_P13_P18 = (TH1D*)f_Pbp_TrackTriggered_EtaCM_P13_P18->Get("hSumPartPt");

   //Get binning and resolution correction
//   TFile *f_binningAndResol = new TFile("BinningAndResolutionCorrection.root");
   TFile *f_binningAndResol_extendedPt = new TFile("TrackTriggerCheck/BinningAndResolutionCorrection_TrackTrigger.root");
//   TH1D *hBinningAndResol = (TH1D*)f_binningAndResol->Get("hPt_pseudo2_copy1");
   TH1D *hBinningAndResol_extendedPt = (TH1D*)f_binningAndResol_extendedPt->Get("hPt_pseudo2_copy1");

   //Apply binning and resolution correction
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1->Divide(hBinningAndResol_extendedPt);   
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08->Divide(hBinningAndResol_extendedPt);   
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08->Divide(hBinningAndResol_extendedPt);   
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13->Divide(hBinningAndResol_extendedPt);   
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13->Divide(hBinningAndResol_extendedPt);   
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18->Divide(hBinningAndResol_extendedPt);   
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18->Divide(hBinningAndResol_extendedPt);   

   hCombined_pPb_TrackTriggered_EtaCM_M1_P1->Divide(hBinningAndResol_extendedPt);   
   hCombined_pPb_TrackTriggered_EtaCM_M03_M08->Divide(hBinningAndResol_extendedPt);   
   hCombined_pPb_TrackTriggered_EtaCM_P03_P08->Divide(hBinningAndResol_extendedPt);   
   hCombined_pPb_TrackTriggered_EtaCM_M08_M13->Divide(hBinningAndResol_extendedPt);   
   hCombined_pPb_TrackTriggered_EtaCM_P08_P13->Divide(hBinningAndResol_extendedPt);   
   hCombined_pPb_TrackTriggered_EtaCM_M13_M18->Divide(hBinningAndResol_extendedPt);   
   hCombined_pPb_TrackTriggered_EtaCM_P13_P18->Divide(hBinningAndResol_extendedPt);   

   hCombined_Pbp_TrackTriggered_EtaCM_M1_P1->Divide(hBinningAndResol_extendedPt);   
   hCombined_Pbp_TrackTriggered_EtaCM_M03_M08->Divide(hBinningAndResol_extendedPt);   
   hCombined_Pbp_TrackTriggered_EtaCM_P03_P08->Divide(hBinningAndResol_extendedPt);   
   hCombined_Pbp_TrackTriggered_EtaCM_M08_M13->Divide(hBinningAndResol_extendedPt);   
   hCombined_Pbp_TrackTriggered_EtaCM_P08_P13->Divide(hBinningAndResol_extendedPt);   
   hCombined_Pbp_TrackTriggered_EtaCM_M13_M18->Divide(hBinningAndResol_extendedPt);   
   hCombined_Pbp_TrackTriggered_EtaCM_P13_P18->Divide(hBinningAndResol_extendedPt);   

   //Eta normalization
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1->Scale(1./2.);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08->Scale(2.);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08->Scale(2.);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13->Scale(2.);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13->Scale(2.);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18->Scale(2.);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18->Scale(2.);

   hCombined_pPb_TrackTriggered_EtaCM_M1_P1->Scale(1./2.);
   hCombined_pPb_TrackTriggered_EtaCM_M03_M08->Scale(2.);
   hCombined_pPb_TrackTriggered_EtaCM_P03_P08->Scale(2.);
   hCombined_pPb_TrackTriggered_EtaCM_M08_M13->Scale(2.);
   hCombined_pPb_TrackTriggered_EtaCM_P08_P13->Scale(2.);
   hCombined_pPb_TrackTriggered_EtaCM_M13_M18->Scale(2.);
   hCombined_pPb_TrackTriggered_EtaCM_P13_P18->Scale(2.);

   hCombined_Pbp_TrackTriggered_EtaCM_M1_P1->Scale(1./2.);
   hCombined_Pbp_TrackTriggered_EtaCM_M03_M08->Scale(2.);
   hCombined_Pbp_TrackTriggered_EtaCM_P03_P08->Scale(2.);
   hCombined_Pbp_TrackTriggered_EtaCM_M08_M13->Scale(2.);
   hCombined_Pbp_TrackTriggered_EtaCM_P08_P13->Scale(2.);
   hCombined_Pbp_TrackTriggered_EtaCM_M13_M18->Scale(2.);
   hCombined_Pbp_TrackTriggered_EtaCM_P13_P18->Scale(2.);

//   float ncoll = 7.9; //Anna's original number for 0-100% DS
   float ncoll = 6.9; //ALICE, this seems to be the pure Glauber number, but not(!) DS

   //PLOTTING
   bool DoSave = true;


   TCanvas *c1 = new TCanvas("c1","c1");
   c1->cd();
   c1->SetLogx();
   c1->SetLogy();
/*
   hCombined_pPb_JetTriggered_EtaCM_M1_P1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hCombined_pPb_JetTriggered_EtaCM_M1_P1->GetYaxis()->SetTitle("1/N_{ev} d^{2}N/d#etadp_{T} (|#eta_{CM}|<1)");
   hCombined_pPb_JetTriggered_EtaCM_M1_P1->SetMarkerStyle(20);
   hCombined_pPb_JetTriggered_EtaCM_M1_P1->SetMinimum(2.*1e-10);
   hCombined_pPb_JetTriggered_EtaCM_M1_P1->Draw();
*/
   TH1D * hDum = new TH1D("hDum","hDum",1000.,0.3,260.);
   hDum->GetXaxis()->CenterTitle();
   hDum->GetYaxis()->CenterTitle();
   hDum->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hDum->GetYaxis()->SetTitle("1/N_{ev} 1/(2#pip_{T}) d^{2}N/d#etadp_{T}");
   hDum->SetMaximum(3000.);
   hDum->SetMinimum(5e-17);
   hDum->Draw();

   TH1D* recastedppRef = castRefIntoMeasHist(combinedRef,hCombined_pPb_TrackTriggered_EtaCM_M1_P1);
   convertToInvYield(recastedppRef);
   recastedppRef->SetLineColor(1);
   recastedppRef->Scale(1./2.); //divide by the eta bin width
   recastedppRef->Scale(ncoll); //multiply by ncoll
   recastedppRef->Draw("histsame");

   convertToInvYield(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1); //convert to inv yield
   setupHistProperties(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1,1,20,1.);
   TGraphErrors* hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1_sys_lemma = drawErrorBoxes(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1);
   drawTickError(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1,hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1_sys_lemma);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1->Draw("same");

   convertToInvYield(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08); //convert to inv yield
   setupHistProperties(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08,2,21,4.);
   TGraphErrors* hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08_sys_lemma = drawErrorBoxes(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08);
   drawTickError(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08,hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08_sys_lemma);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08->Draw("same");

   convertToInvYield(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08); //convert to inv yield
   setupHistProperties(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08,2,25,1./4.);
   TGraphErrors* hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08_sys_lemma = drawErrorBoxes(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08);
   drawTickError(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08,hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08_sys_lemma);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08->Draw("same");

   convertToInvYield(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13); //convert to inv yield
   setupHistProperties(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13,4,33,16.);
   TGraphErrors* hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13_sys_lemma = drawErrorBoxes(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13);
   drawTickError(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13,hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13_sys_lemma);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13->Draw("same");

   convertToInvYield(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13); //convert to inv yield
   setupHistProperties(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13,4,27,1./16.);
   TGraphErrors* hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13_sys_lemma = drawErrorBoxes(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13);
   drawTickError(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13,hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13_sys_lemma);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13->Draw("same");

   convertToInvYield(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18); //convert to inv yield
   setupHistProperties(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18,8,34,64.);
   TGraphErrors* hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18_sys_lemma = drawErrorBoxes(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18);
   drawTickError(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18,hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18_sys_lemma);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18->Draw("same");

   convertToInvYield(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18); //convert to inv yield
   setupHistProperties(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18,8,28,1./64.);
   TGraphErrors* hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18_sys_lemma = drawErrorBoxes(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18);
   drawTickError(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18,hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18_sys_lemma);
   hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18->Draw("same");

//   TLegend *leg1 = new TLegend(0.55,0.74,0.92,0.93,NULL,"brNDC");
   TLegend *leg1 = new TLegend(0.21,0.145,0.7,0.48,NULL,"brNDC");
//   leg1->AddEntry(hCombined_CombpPbPbp_JetTriggered_EtaCM_M1_P1,"Data: pPb, jet-triggered","pl");
   leg1->AddEntry(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P13_P18,"1.3<#eta_{CM}<1.8 (x64)","pl");
   leg1->AddEntry(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P08_P13,"0.8<#eta_{CM}<1.3 (x16)","pl");
   leg1->AddEntry(hCombined_CombpPbPbp_TrackTriggered_EtaCM_P03_P08,"0.3<#eta_{CM}<0.8 (x4)","pl");
   leg1->AddEntry(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M1_P1,"|#eta_{CM}|<1","pl");
   leg1->AddEntry(recastedppRef,"pp reference, |#eta_{CM}|<1 (x6.9)","pl");
   leg1->AddEntry(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M03_M08,"-0.8<#eta_{CM}<-0.3 (/4)","pl");
   leg1->AddEntry(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M08_M13,"-1.3<#eta_{CM}<-0.8 (/16)","pl");
   leg1->AddEntry(hCombined_CombpPbPbp_TrackTriggered_EtaCM_M13_M18,"-1.8<#eta_{CM}<-1.3 (/64)","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   TLatex *collen = new TLatex(0.62,0.85,"pPb #sqrt{s_{NN}} = 5.02 TeV");
   collen->SetNDC();
   collen->SetTextSize(0.035);
   collen->Draw();
   TLatex *prel = new TLatex(0.66,0.8,"CMS Preliminary");
   prel->SetNDC();
   prel->SetTextSize(0.035);
   prel->Draw();
   if(DoSave) {
      c1->SaveAs("Figs/PlotSpectra_c1.gif");
      c1->SaveAs("Figs/PlotSpectra_c1.eps");
      c1->SaveAs("Figs/PlotSpectra_c1.C");
   }


   TCanvas *c2 = new TCanvas("c2","c2");
   c2->cd();
   c2->SetLogx();
   c2->SetLogy();
   hDum->Draw();

   convertToInvYield(hCombined_pPb_TrackTriggered_EtaCM_M1_P1); //convert to inv yield
   setupHistProperties(hCombined_pPb_TrackTriggered_EtaCM_M1_P1,4,20,1.);
   hCombined_pPb_TrackTriggered_EtaCM_M1_P1->Draw("same");

   convertToInvYield(hCombined_pPb_TrackTriggered_EtaCM_P03_P08); //convert to inv yield
   setupHistProperties(hCombined_pPb_TrackTriggered_EtaCM_P03_P08,4,21,4.);
   hCombined_pPb_TrackTriggered_EtaCM_P03_P08->Draw("same");

   convertToInvYield(hCombined_pPb_TrackTriggered_EtaCM_P08_P13); //convert to inv yield
   setupHistProperties(hCombined_pPb_TrackTriggered_EtaCM_P08_P13,4,33,16.);
   hCombined_pPb_TrackTriggered_EtaCM_P08_P13->Draw("same");

   convertToInvYield(hCombined_pPb_TrackTriggered_EtaCM_P13_P18); //convert to inv yield
   setupHistProperties(hCombined_pPb_TrackTriggered_EtaCM_P13_P18,4,34,64.);
   hCombined_pPb_TrackTriggered_EtaCM_P13_P18->Draw("same");

   convertToInvYield(hCombined_Pbp_TrackTriggered_EtaCM_M1_P1); //convert to inv yield
   setupHistProperties(hCombined_Pbp_TrackTriggered_EtaCM_M1_P1,6,24,1.);
   hCombined_Pbp_TrackTriggered_EtaCM_M1_P1->Draw("same");

   convertToInvYield(hCombined_Pbp_TrackTriggered_EtaCM_M03_M08); //convert to inv yield
   setupHistProperties(hCombined_Pbp_TrackTriggered_EtaCM_M03_M08,6,25,4.);
   hCombined_Pbp_TrackTriggered_EtaCM_M03_M08->Draw("same");

   convertToInvYield(hCombined_Pbp_TrackTriggered_EtaCM_M08_M13); //convert to inv yield
   setupHistProperties(hCombined_Pbp_TrackTriggered_EtaCM_M08_M13,6,27,16.);
   hCombined_Pbp_TrackTriggered_EtaCM_M08_M13->Draw("same");

   convertToInvYield(hCombined_Pbp_TrackTriggered_EtaCM_M13_M18); //convert to inv yield
   setupHistProperties(hCombined_Pbp_TrackTriggered_EtaCM_M13_M18,6,28,64.);
   hCombined_Pbp_TrackTriggered_EtaCM_M13_M18->Draw("same");

   convertToInvYield(hCombined_pPb_TrackTriggered_EtaCM_M03_M08); //convert to inv yield
   setupHistProperties(hCombined_pPb_TrackTriggered_EtaCM_M03_M08,4,22,1./4.);
   hCombined_pPb_TrackTriggered_EtaCM_M03_M08->Draw("same");

   convertToInvYield(hCombined_pPb_TrackTriggered_EtaCM_M08_M13); //convert to inv yield
   setupHistProperties(hCombined_pPb_TrackTriggered_EtaCM_M08_M13,4,23,1./16.);
   hCombined_pPb_TrackTriggered_EtaCM_M08_M13->Draw("same");

   convertToInvYield(hCombined_pPb_TrackTriggered_EtaCM_M13_M18); //convert to inv yield
   setupHistProperties(hCombined_pPb_TrackTriggered_EtaCM_M13_M18,4,29,1./64.);
   hCombined_pPb_TrackTriggered_EtaCM_M13_M18->Draw("same");

   convertToInvYield(hCombined_Pbp_TrackTriggered_EtaCM_P03_P08); //convert to inv yield
   setupHistProperties(hCombined_Pbp_TrackTriggered_EtaCM_P03_P08,6,26,1./4.);
   hCombined_Pbp_TrackTriggered_EtaCM_P03_P08->Draw("same");

   convertToInvYield(hCombined_Pbp_TrackTriggered_EtaCM_P08_P13); //convert to inv yield
   setupHistProperties(hCombined_Pbp_TrackTriggered_EtaCM_P08_P13,6,32,1./16.);
   hCombined_Pbp_TrackTriggered_EtaCM_P08_P13->Draw("same");

   convertToInvYield(hCombined_Pbp_TrackTriggered_EtaCM_P13_P18); //convert to inv yield
   setupHistProperties(hCombined_Pbp_TrackTriggered_EtaCM_P13_P18,6,30,1./64.);
   hCombined_Pbp_TrackTriggered_EtaCM_P13_P18->Draw("same");

   TLegend *leg2 = new TLegend(0.6,0.64,0.92,0.93,NULL,"brNDC");
   leg2->AddEntry(hCombined_pPb_TrackTriggered_EtaCM_M1_P1,"pPb, |#eta_{CM}|<1","pl");
   leg2->AddEntry(hCombined_pPb_TrackTriggered_EtaCM_P03_P08,"pPb, 0.3<#eta_{CM}<0.8","pl");
   leg2->AddEntry(hCombined_pPb_TrackTriggered_EtaCM_P08_P13,"pPb, 0.8<#eta_{CM}<1.3","pl");
   leg2->AddEntry(hCombined_pPb_TrackTriggered_EtaCM_P13_P18,"pPb, 1.3<#eta_{CM}<1.8","pl");
   leg2->AddEntry(hCombined_Pbp_TrackTriggered_EtaCM_M1_P1,"Pbp, |#eta_{CM}|<1","pl");
   leg2->AddEntry(hCombined_Pbp_TrackTriggered_EtaCM_M03_M08,"Pbp, -0.8<#eta_{CM}<-0.3","pl");
   leg2->AddEntry(hCombined_Pbp_TrackTriggered_EtaCM_M08_M13,"Pbp, -1.3<#eta_{CM}<-0.8","pl");
   leg2->AddEntry(hCombined_Pbp_TrackTriggered_EtaCM_M13_M18,"Pbp, -1.8<#eta_{CM}<-1.3","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();

   TLegend *leg22 = new TLegend(0.2,0.24,0.52,0.53,NULL,"brNDC");
   leg22->AddEntry(hCombined_pPb_TrackTriggered_EtaCM_M03_M08,"pPb, -0.8<#eta_{CM}<-0.3","pl");
   leg22->AddEntry(hCombined_pPb_TrackTriggered_EtaCM_M08_M13,"pPb, -1.3<#eta_{CM}<-0.8","pl");
   leg22->AddEntry(hCombined_pPb_TrackTriggered_EtaCM_M13_M18,"pPb, -1.8<#eta_{CM}<-1.3","pl");
   leg22->AddEntry(hCombined_Pbp_TrackTriggered_EtaCM_P03_P08,"Pbp, 0.3<#eta_{CM}<0.8","pl");
   leg22->AddEntry(hCombined_Pbp_TrackTriggered_EtaCM_P08_P13,"Pbp, 0.8<#eta_{CM}<1.3","pl");
   leg22->AddEntry(hCombined_Pbp_TrackTriggered_EtaCM_P13_P18,"Pbp, 1.3<#eta_{CM}<1.8","pl");
   leg22->SetFillStyle(0);
   leg22->SetFillColor(0);
   leg22->SetBorderSize(0);
   leg22->Draw();

   if(DoSave) {
      c2->SaveAs("Figs/PlotSpectra_c2.gif");
      c2->SaveAs("Figs/PlotSpectra_c2.eps");
      c2->SaveAs("Figs/PlotSpectra_c2.C");
   }
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


TH1D* singleReference(TH1D* hPtbased, TH1D* hXtbased) {
  TH1D* hNewRef = (TH1D*)hXtbased->Clone("hNewRef");
  hNewRef->Reset();
  for(int i=1; i<=hXtbased->GetNbinsX(); i++) {
     double pt = hXtbased->GetBinCenter(i);

     double content_ptbased = hPtbased->GetBinContent(i);
     double error_ptbased = hPtbased->GetBinError(i);

     double content_xtbased = hXtbased->GetBinContent(i);
     double error_xtbased = hXtbased->GetBinError(i);

     double low_th = 12.5;
     double high_th = 13.5;//20.

     if(pt < low_th) {
       hNewRef->SetBinContent(i,content_ptbased);
       hNewRef->SetBinError(i,error_ptbased);
     }
     else if(pt >= high_th) {
       hNewRef->SetBinContent(i,content_xtbased);
       hNewRef->SetBinError(i,error_xtbased);
     }
     else {
       double newContent = content_ptbased*(high_th-pt)/(high_th-low_th) + (content_xtbased)*(pt-low_th)/(high_th-low_th);
       double newError = error_ptbased*(high_th-pt)/(high_th-low_th) + (error_xtbased)*(pt-low_th)/(high_th-low_th);
       hNewRef->SetBinContent(i,newContent);
       hNewRef->SetBinError(i,newError);
     }
  }
  return hNewRef;
}


TGraphErrors* drawErrorBoxes(TH1 *hist) {

  Float_t pt[hist->GetNbinsX()], yield[hist->GetNbinsX()], pterror[hist->GetNbinsX()], yielderror[hist->GetNbinsX()];
  for(int i=1;i <= hist->GetNbinsX();i++){
     double x = hist->GetBinCenter(i);
     double y = hist->GetBinContent(i);
     double w = hist->GetBinWidth(i);

     Double_t err = 0.;

     if(x<1.0)
       err = 0.02;
     else if(x<2.0)
       err = 0.035;
     else if(x<3.2)
       err = 0.063;
     else if(x<24.)
       err = 0.102;
     else
       err = 0.102;

     drawBox(y,err,x,w*0.6,5);

     pt[i-1]=x;
     pterror[i-1]=0.;
     yield[i-1]=y;
     yielderror[i-1]=err*yield[i-1];//err is relative error here
  }
  TGraphErrors *sys = new TGraphErrors(hist->GetNbinsX(),pt,yield,pterror,yielderror);
  return sys;
}


void drawBox(Double_t y, Double_t err, Double_t x, Double_t width, Int_t color) {
  TGraphErrors *tg = new TGraphErrors();

  double xvalue[2];
  double yvalue[2];
  double xerror[2];
  double yerror[2];

  xvalue[0] = x - 0.5*width;
  xvalue[1] = x + 0.5*width;

  yvalue[0] = y;
  yvalue[1] = y;

  xerror[0] = 0.0;
  xerror[1] = 0.0;

  yerror[0] = err*yvalue[0];
  yerror[1] = err*yvalue[0];

  tg = new TGraphErrors(2,xvalue,yvalue,xerror,yerror);

  tg->SetFillColor(color);
  tg->SetLineColor(color);

  tg->SetFillStyle(1001);
  tg->Draw("3");
}


std::pair<TGraphErrors*,TGraphErrors*> readInData(char * name) {

  std::ifstream data(name,ios_base::in);
  if(data.is_open())
     cout << "Reading..." << endl;

  Float_t pt[45], yield[45], pterror[45], yielderror_stat[45], yielderror_syst[45];
  Float_t pt_lemma, yield_lemma, yielderror_stat_lemma, yielderror_syst_lemma;
  for(Int_t j=0;j<45;j++) {
     data >> pt_lemma;
     pt[j] = pt_lemma;
     data >> yield_lemma;
     yield[j] = yield_lemma;
     data >> yielderror_stat_lemma;
     yielderror_stat[j] = yielderror_stat_lemma;
     data >> yielderror_syst_lemma;
     yielderror_syst[j] = yielderror_syst_lemma;

     pterror[j] = 0.;
  }

  TGraphErrors *gALICE_stat = new TGraphErrors(45,pt,yield,pterror,yielderror_stat);
  TGraphErrors *gALICE_syst = new TGraphErrors(45,pt,yield,pterror,yielderror_syst);
  return std::pair<TGraphErrors*,TGraphErrors*>(gALICE_stat,gALICE_syst);
}


void drawTickError(TH1 *hist, TGraphErrors *tg) {

  for(int i=0;i<hist->GetNbinsX();i++){
    double x = hist->GetBinCenter(i+1);
    double y = hist->GetBinContent(i+1);
    double w = hist->GetBinWidth(i+1);
//    drawTick(Double_t Y, Double_t Erru, Double_t Errd, Double_t X, Double_t Tick_x, Double_t Tick_y, Int_t TickColor)
    if(y>0.) //not to draw lines for empty bins
//       drawTick(y,tg->GetErrorY(i),tg->GetErrorY(i),x,0.015,0.3*w,1);
       drawTick(y,tg->GetErrorY(i),tg->GetErrorY(i),x,y*0.05,0.3*w,1);
  }
}


void drawTick(Double_t Y, Double_t Erru, Double_t Errd, Double_t X, Double_t Tick_x, Double_t Tick_y, Int_t TickColor) {

  Int_t tcolor[13]={kViolet+2,kBlue,kAzure+6,kGreen-3,kOrange-5,kOrange-3,kOrange+4,kRed-3,kRed,kRed+2,kMagenta,kOrange,1};

  if(TickColor>13){
    TickColor = tcolor[TickColor-14];
  }

  TLine *line;
  line = new TLine(X-Tick_y,Y+Erru,X-Tick_y,Y+Erru-Tick_x);
  line->SetLineColor(TickColor);
  line->Draw();
  line = new TLine(X+Tick_y,Y+Erru,X+Tick_y,Y+Erru-Tick_x);
  line->SetLineColor(TickColor);
  line->Draw();
  line = new TLine(X-Tick_y,Y+Erru,X+Tick_y,Y+Erru);
  line->SetLineColor(TickColor);
  line->Draw();

  line = new TLine(X-Tick_y,Y-Errd,X-Tick_y,Y-Errd+Tick_x);
  line->SetLineColor(TickColor);
  line->Draw();
  line = new TLine(X+Tick_y,Y-Errd,X+Tick_y,Y-Errd+Tick_x);
  line->SetLineColor(TickColor);
  line->Draw();
  line = new TLine(X-Tick_y,Y-Errd,X+Tick_y,Y-Errd);
  line->SetLineColor(TickColor);
  line->Draw();
}


void convertToInvYield(TH1D *hist) {
  for(int i = 1; i<=hist->GetNbinsX(); i++) {
     double content = hist->GetBinContent(i);
     double pt = hist->GetBinCenter(i);
     double error = hist->GetBinError(i);

     double new_content = content/(2.*TMath::Pi()*pt);
     double new_error = error/(2.*TMath::Pi()*pt);

     hist->SetBinContent(i,new_content);
     hist->SetBinError(i,new_error);
  }
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


TH1D* From_xT_to_pT_histo(TH1D *h_input, TH1D *h_binning, double sqrts, double exp) {

  TH1D *h_pt = (TH1D*)h_binning->Clone("h_pt");
  h_pt->Reset();

  for(int i=1; i<=h_input->GetNbinsX(); i++) {
     double xT = h_input->GetBinCenter(i);
     double content = h_input->GetBinContent(i)/TMath::Power(sqrts,exp);
     double pT = 5020.*xT/2.;
     if(pT>120) break;
     h_pt->SetBinContent(h_pt->FindBin(pT),content);
  }

  return h_pt;
}


TH1D* castRefIntoMeasHist(TH1D* ppRef, TH1D* pPbMeas) {
   TH1D *pPbMeas_copy = (TH1D*)pPbMeas->Clone("pPbMeas_copy");
   pPbMeas_copy->Reset();
   for(int i = 1; i<=pPbMeas_copy->GetNbinsX(); i++) {
      double pT = pPbMeas_copy->GetBinCenter(i);
      double bin = ppRef->FindBin(pT);
      double refYield = ppRef->GetBinContent(bin);

      pPbMeas_copy->SetBinContent(i,refYield);
   }
   return pPbMeas_copy;
}


void setupHistProperties(TH1D * hist, Int_t color, Int_t style, double scale) {

   hist->SetMarkerStyle(style);
   hist->SetMarkerColor(color);
   hist->SetLineColor(color);
   hist->Scale(scale);;

}
