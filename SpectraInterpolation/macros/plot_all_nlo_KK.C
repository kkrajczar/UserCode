//plots all NLO spectra together

#include "divide_graph_by_function.C"
#include "scale_graph.C"

void plot_all_nlo_KK(Float_t expo=4.9, Int_t mu=100)
{

	//define dummy histogram and some style parameters
	TH1F *dum;
	dum = new TH1F("dum","",160,2e-5,0.8); 
	dum->SetMinimum(1e12);
	dum->SetMaximum(9e28);
	dum->SetTitle(Form(";x_{T};#sqrt{s}^{%0.1f}  E d^{3}#sigma/dp^{3}",expo));
	
	dum->SetLineWidth(0);
	dum->SetStats(0);
	dum->GetXaxis()->CenterTitle();
	dum->GetYaxis()->CenterTitle();
	dum->GetXaxis()->SetTitleSize(0.05);
	dum->GetYaxis()->SetTitleSize(0.05);
	dum->GetXaxis()->SetTitleOffset(1.17);
	dum->GetYaxis()->SetTitleOffset(1.3);
	
	gROOT->LoadMacro("data_table_to_graph.C");
	
	//TString dir=".";
	TString dir="nlo_test";
	
	//get 7 TeV points
	TGraph *g7000 = nlo_table_to_graph(Form("%s/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy00.sc%03d.%03d.%03d_nlo",dir.Data(),mu,mu,mu),7000,expo);
	g7000->SetMarkerColor(kBlack);
	
	//get 2.75 TeV points
	TGraph *g2750 = nlo_table_to_graph(Form("%s/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s02750.y+00.dy00.sc%03d.%03d.%03d_nlo",dir.Data(),mu,mu,mu),2750,expo);
	g2750->SetMarkerColor(kBlue);
	
	//get 1.96 TeV points
	//TGraph *g1960 = nlo_table_to_graph(Form("%s/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s01960.y+00.dy00.sc%03d.%03d.%03d_nlo",dir.Data(),mu,mu,mu),1960,expo);
	TGraph *g1960 = nlo_table_to_graph(Form("%s/a001.b999.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s01960.y+00.dy00.sc%03d.%03d.%03d_nlo",dir.Data(),mu,mu,mu),1960,expo);
	g1960->SetMarkerColor(kOrange-3);
	
	//get 0.9 TeV points
	TGraph *g900 = nlo_table_to_graph(Form("%s/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s00900.y+00.dy00.sc%03d.%03d.%03d_nlo",dir.Data(),mu,mu,mu),900,expo);
	g900->SetMarkerColor(kRed);
	
	//draw graphs to canvas
	TCanvas *c1 = new TCanvas("c1","NLO interpolation",600,600);
	dum->Draw();
	g1960->Draw("pz");
	g900->Draw("pz");
	g7000->Draw("pz");
	g2750->Draw("pz");
	
	gPad->SetLogy();
	gPad->SetLogx();
	
	//*******************************************
	
	TCanvas *c2 = new TCanvas("c2","fit to all",600,500);
	TList *list = new TList();
	list->Add(g1960);
	list->Add(g900);
	list->Add(g2750);
	
	TGraphErrors *merge_g = (TGraphErrors*) g7000->Clone("merge_g");
	merge_g->Merge(list);
	merge_g->Sort();
	
	dum->Draw();
	merge_g->Draw("pz");
	
	TF1 *merge_fit = new TF1("merge_fit","[0]*pow(1.0+(x/[1]),[2])",1e-2,0.06);
	merge_fit->SetParameters(1.4e30,6e-4,-7);
	//merge_fit->FixParameter(2,-7);
	merge_fit->SetLineColor(4);
	merge_fit->SetLineWidth(3);
	merge_g->Fit(merge_fit,"RW");
	
	gPad->SetLogy();
	gPad->SetLogx();
	
	//*******************************************

	TCanvas *c3 = new TCanvas("c3","ratio to global fit",600,500);
	TH1F *hratio = new TH1F("hratio",";x_{T};ratio",160,0.001,0.07); //was 0.003-0.04
	hratio->SetMaximum(2.0);
	hratio->SetMinimum(0.0);
	hratio->SetStats(0);
	hratio->Draw();
	
	TGraph* ratio_1960_g = divide_graph_by_function(g1960,merge_fit);
	ratio_1960_g->SetName("ratio_1960_g");
	ratio_1960_g->SetLineColor(kOrange-3);
	ratio_1960_g->Draw("p");
	
	TGraph* ratio_900_g = divide_graph_by_function(g900,merge_fit);
	ratio_900_g->SetName("ratio_900_g");
	ratio_900_g->SetLineColor(kRed);
	ratio_900_g->Draw("p");
	
	TGraph* ratio_7000_g = divide_graph_by_function(g7000,merge_fit);
	ratio_7000_g->SetName("ratio_7000_g");
	ratio_7000_g->SetLineColor(kBlack);
	ratio_7000_g->Draw("p");
	
	TGraph* ratio_2750_g = divide_graph_by_function(g2750,merge_fit);
	ratio_2750_g->SetLineColor(kBlue);
	ratio_2750_g->SetName("ratio_2750_g");
	ratio_2750_g->Draw("p");
	
	TSpline3 *spline_2750 = new TSpline3("spline_2750",ratio_2750_g->GetX(),ratio_2750_g->GetY(),ratio_2750_g->GetN());
	TSpline3 *spline_1960 = new TSpline3("spline_1960",ratio_1960_g->GetX(),ratio_1960_g->GetY(),ratio_1960_g->GetN());
	TSpline3 *spline_7000 = new TSpline3("spline_7000",ratio_7000_g->GetX(),ratio_7000_g->GetY(),ratio_7000_g->GetN());
	TSpline3 *spline_900 = new TSpline3("spline_900",ratio_900_g->GetX(),ratio_900_g->GetY(),ratio_900_g->GetN());
	
	TH1F *h2750 = new TH1F("h2750","h2750",10000,0.001,0.07);
	TH1F *h1960 = new TH1F("h1960","h1960",10000,0.001,0.07);
	TH1F *h7000 = new TH1F("h7000","h7000",10000,0.001,0.07);
	TH1F *h900 = new TH1F("h900","h900",10000,0.001,0.07);

	for(Int_t i=1; i<=h2750->GetNbinsX(); i++) {
		h2750->SetBinContent(i,spline_2750->Eval(h2750->GetBinCenter(i)));
		h1960->SetBinContent(i,spline_1960->Eval(h1960->GetBinCenter(i)));
		h7000->SetBinContent(i,spline_7000->Eval(h7000->GetBinCenter(i)));
		h900->SetBinContent(i,spline_900->Eval(h900->GetBinCenter(i)));
	}
	
	TCanvas *c4 = new TCanvas("c4","nlo ratios to 2.75 TeV",600,500);
	h900->Divide(h2750);
	h1960->Divide(h2750);
	h7000->Divide(h2750);
	h2750->Divide(h2750);

	TH1F *dum = new TH1F("hdum",";x_{T};NLO ratio to 2.75 TeV",10000,0.001,0.07);
	dum->SetMaximum(1.24);  dum->SetMinimum(0.88); dum->SetStats(0);
	dum->Draw();
	h2750->SetLineColor(kBlue);
	h2750->Draw("csame");
	h1960->SetLineColor(kOrange-3);
	h1960->Draw("csame");
	h7000->SetLineColor(kBlack);
	h7000->Draw("csame");
	h900->SetLineColor(kRed);
	h900->Draw("csame");
	
	TCanvas *c5 = new TCanvas("c5","nlo ratios as graphs",600,500);
	TGraph* scale900 = divide_graph_by_function(ratio_900_g,spline_2750);
	scale900->SetName("scale900");
	TGraph* scale1960 = divide_graph_by_function(ratio_1960_g,spline_2750);
	scale1960->SetName("scale1960");
	TGraph* scale7000 = divide_graph_by_function(ratio_7000_g,spline_2750);
	scale7000->SetName("scale7000");
	TGraph* scale2750 = divide_graph_by_function(ratio_2750_g,spline_2750);
	scale2750->SetName("scale2750");
	dum->Draw();
	scale900->Draw("psame");
	scale1960->Draw("psame");
	scale2750->Draw("psame");
	scale7000->Draw("psame");

	
	// OUTPUT
	
	TFile *output = new TFile(Form("output_nlo_%03d_KK.root",mu),"RECREATE");
	ratio_1960_g->Write();
	ratio_900_g->Write();
	ratio_7000_g->Write();
	ratio_2750_g->Write();
	
	merge_fit->Write();
	
	h2750->Write();
	h900->Write();
	h7000->Write();
	h1960->Write();
	
	scale900->Write();
	scale1960->Write();
	scale2750->Write();
	scale7000->Write();
	
	output->ls();
	output->Close();
	
	
}
