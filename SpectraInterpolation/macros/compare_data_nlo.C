//plots all NLO spectra together

#include "divide_graph_by_function.C"
#include "scale_graph.C"

void compare_data_nlo(Float_t expo=4.9)
{

	Bool_t xt=kTRUE;
	
	//define dummy histogram and some style parameters
	TH1F *dum;
	dum = new TH1F("dum","",160,2e-5,0.8); 
	dum->SetMinimum(9);
	dum->SetMaximum(1e19);
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
	
	/// NLO ///
	
	//get 7 TeV points
	TGraph *g7000 = nlo_table_to_graph("a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy00.sc100.100.100_nlo",7000,expo);
	g7000->SetMarkerColor(kBlack);
	TGraph *g7000a = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy00.sc200.200.200_nlo",7000,expo);
	g7000a->SetMarkerColor(kBlack);
	TGraph *g7000b = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy00.sc050.050.050_nlo",7000,expo);
	g7000b->SetMarkerColor(kBlack);
	TGraph *g7000c = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.ak8.s07000.y+00.dy00.sc100.100.100_nlo",7000,expo);
	g7000c->SetMarkerColor(kBlack);
	TGraph *g7000d = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy10.sc100.100.100_nlo",7000,expo);
	g7000d->SetMarkerColor(kBlack);
	TGraph *g7000e = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy10.sc200.200.200_nlo",7000,expo);
	g7000e->SetMarkerColor(kBlack);
	TGraph *g7000f = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy24.sc100.100.100_nlo",7000,expo);
	g7000f->SetMarkerColor(kBlack);
	TGraph *g7000g = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy24.sc200.200.200_nlo",7000,expo);
	g7000g->SetMarkerColor(kBlack);
	TGraph *g7000h = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.hkn.s07000.y+00.dy00.sc100.100.100_nlo",7000,expo);
	g7000h->SetMarkerColor(kBlack);
	TGraph *g7000i = nlo_table_to_graph("nlo_test/a001.b001.mstw08_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy00.sc100.100.100_nlo",7000,expo);
	g7000i->SetMarkerColor(kBlack);
	TGraph *g7000j = nlo_table_to_graph("nlo_test/a001.b001.nnpdf0_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy00.sc100.100.100_nlo",7000,expo);
	g7000j->SetMarkerColor(kBlack);
	TGraph *g7000k = nlo_table_to_graph("nlo_test/a001.b001.nnpdf2_00.npdfnsh.omc00.chsum.ho.dss.s07000.y+00.dy00.sc100.100.100_nlo",7000,expo);
	g7000k->SetMarkerColor(kBlack);

	//get 2.75 TeV points
	TGraph *g2750 = nlo_table_to_graph("a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s02750.y+00.dy00.sc100.100.100_nlo",2750,expo);
	g2750->SetMarkerColor(kBlue);

	TGraph *g2750a = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s02750.y+00.dy00.sc200.200.200_nlo",2750,expo);
	g2750a->SetMarkerColor(kBlue);
	TGraph *g2750b = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s02750.y+00.dy00.sc050.050.050_nlo",2750,expo);
	g2750b->SetMarkerColor(kBlue);
	TGraph *g2750c = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.ak8.s02750.y+00.dy00.sc100.100.100_nlo",2750,expo);
	g2750c->SetMarkerColor(kBlue);
	TGraph *g2750d = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.hkn.s02750.y+00.dy00.sc100.100.100_nlo",2750,expo);
        g2750d->SetMarkerColor(kBlue);
	TGraph *g2750e = nlo_table_to_graph("nlo_test/a001.b001.mstw08_00.npdfnsh.omc00.chsum.ho.dss.s02750.y+00.dy00.sc100.100.100_nlo",2750,expo);
        g2750e->SetMarkerColor(kBlue);
	TGraph *g2750f = nlo_table_to_graph("nlo_test/a001.b001.nnpdf0_00.npdfnsh.omc00.chsum.ho.dss.s02750.y+00.dy00.sc100.100.100_nlo",2750,expo);
	g2750f->SetMarkerColor(kBlue);


	//get 1.96 TeV points
	TGraph *g1960 = nlo_table_to_graph("a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s01960.y+00.dy00.sc100.100.100_nlo",1960,expo);
	g1960->SetMarkerColor(kOrange-3);
	TGraph *g1960a = nlo_table_to_graph("nlo_test/a001.b999.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s01960.y+00.dy00.sc200.200.200_nlo",1960,expo);
	g1960a->SetMarkerColor(kOrange-3);
	TGraph *g1960b = nlo_table_to_graph("nlo_test/a001.b999.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s01960.y+00.dy00.sc050.050.050_nlo",1960,expo);
	g1960b->SetMarkerColor(kOrange-3);
	TGraph *g1960c = nlo_table_to_graph("nlo_test/a001.b999.cteq66_00.npdfnsh.omc00.chsum.ho.ak8.s01960.y+00.dy00.sc100.100.100_nlo",1960,expo);
	g1960c->SetMarkerColor(kOrange-3);
	TGraph *g1960d = nlo_table_to_graph("nlo_test/a001.b999.cteq66_00.npdfnsh.omc00.chsum.ho.hkn.s01960.y+00.dy00.sc100.100.100_nlo",1960,expo);
	g1960d->SetMarkerColor(kOrange-3);
	TGraph *g1960e = nlo_table_to_graph("nlo_test/a001.b999.mstw08_00.npdfnsh.omc00.chsum.ho.dss.s01960.y+00.dy00.sc100.100.100_nlo",1960,expo);
	g1960e->SetMarkerColor(kOrange-3);
	TGraph *g1960f = nlo_table_to_graph("nlo_test/a001.b999.nnpdf0_00.npdfnsh.omc00.chsum.ho.dss.s01960.y+00.dy00.sc100.100.100_nlo",1960,expo);
	g1960f->SetMarkerColor(kOrange-3);
	TGraph *g1960g = nlo_table_to_graph("nlo_test/a001.b999.nnpdf2_00.npdfnsh.omc00.chsum.ho.dss.s01960.y+00.dy00.sc100.100.100_nlo",1960,expo);
	g1960g->SetMarkerColor(kOrange-3);

	//get 0.9 TeV points
	TGraph *g900 = nlo_table_to_graph("a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s00900.y+00.dy00.sc100.100.100_nlo",900,expo);
	g900->SetMarkerColor(kRed);
	TGraph *g900a = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s00900.y+00.dy00.sc200.200.200_nlo",900,expo);
	g900a->SetMarkerColor(kRed);
	TGraph *g900b = nlo_table_to_graph("nlo_test/a001.b001.cteq66_00.npdfnsh.omc00.chsum.ho.dss.s00900.y+00.dy00.sc050.050.050_nlo",900,expo);
	g900b->SetMarkerColor(kRed);
	
	/// DATA ///
	
	//get 7 TeV points
	TGraphErrors *cms_7000_g = data_table_to_graph("cms",7000,xt,expo);
	cms_7000_g->SetMarkerColor(kBlack);
	
	//get 2.36 TeV points
	TGraphErrors *cms_2360_g = data_table_to_graph("cms",2360,xt,expo);
	cms_2360_g->SetMarkerColor(kMagenta+3);

	// get 2.76 TeV points
	TGraphErrors *cms_2760_g = data_table_to_graph("cms",2760,xt,expo);
        cms_2760_g->SetMarkerColor(kBlue);
	
	//get 1.96 TeV points
	TGraphErrors *cdf_1960_g = data_table_to_graph("cdf",1960,xt,expo);
	cdf_1960_g->SetMarkerColor(kOrange-3);
	cdf_1960_g->SetMarkerStyle(30);
	
	//get 1.8 TeV points
	TGraphErrors *cdf_1800_g = data_table_to_graph("cdf",1800,xt,expo);
	cdf_1800_g->SetMarkerColor(kGreen+3);
	cdf_1800_g->SetMarkerStyle(28);
	
	//get 0.9 TeV points
	TGraphErrors *cms_900_g = data_table_to_graph("cms",900,xt,expo);
	cms_900_g->SetMarkerColor(kRed);
	
	TGraphErrors *ua1_900_g = data_table_to_graph("ua1",900,xt,expo);
	ua1_900_g->SetMarkerColor(kCyan+1);
	ua1_900_g->SetMarkerStyle(26);
	
	// get 0.63 TeV points
	TGraphErrors *cdf_630_g = data_table_to_graph("cdf",630,xt,expo);
	cdf_630_g->SetMarkerColor(kOrange+3);
	cdf_630_g->SetMarkerStyle(27);
	
	//draw graphs to canvas
	TCanvas *c1 = new TCanvas("c1","NLO interpolation",600,600);
	dum->Draw();
	g1960->Draw("pz");
	g1960a->Draw("pz");
	g1960b->Draw("pz");
	g1960c->Draw("pz");
	g1960d->Draw("pz");
	g1960e->Draw("pz");
	g1960f->Draw("pz");
	g1960g->Draw("pz");
	g900->Draw("pz");
	g900a->Draw("pz");
	g900b->Draw("pz");
	g7000->Draw("pz");
	g7000a->Draw("pz");
	g7000b->Draw("pz");
	g7000c->Draw("pz");
	g7000d->Draw("pz");
	g7000e->Draw("pz");
	g7000f->Draw("pz");
	g7000g->Draw("pz");
	g7000h->Draw("pz");
	g7000i->Draw("pz");
	g7000j->Draw("pz");
	g7000k->Draw("pz");
	g2750->Draw("pz");
	g2750a->Draw("pz");
	g2750b->Draw("pz");
	g2750c->Draw("pz");
	g2750d->Draw("pz");
        g2750e->Draw("pz");
        g2750f->Draw("pz");

	
	cdf_1960_g->Draw("pz");
	cdf_1800_g->Draw("pz");
	if(!xt) ua1_900_g->Draw("pz");   // abs(eta) within 2.5 changes high xt behavior
	cdf_630_g->Draw("pz");
	cms_900_g->Draw("pz");           // draw the CMS points on top
	cms_2360_g->Draw("pz");
	cms_7000_g->Draw("pz");
	
	gPad->SetLogy();
	gPad->SetLogx();
	
	TF1 *fit_PL_xt = new TF1("fit_PL_xt","[0]*pow(1.0+(x/[1]),[2])",0.001,0.1);
	fit_PL_xt->SetParameters(2.59664e+19,0.000745074,-7.0);
	
	fit_PL_xt->Draw("same");
	
	TCanvas *c2 = new TCanvas("c2","Ratio to global power-law fit",600,600);
	TGraphErrors* ratio_cdf_1960_g = divide_graph_by_function(cdf_1960_g,fit_PL_xt);
	TGraphErrors* ratio_cms_900_g = divide_graph_by_function(cms_900_g,fit_PL_xt);
	TGraphErrors* ratio_cms_7000_g = divide_graph_by_function(cms_7000_g,fit_PL_xt);
	TGraphErrors* ratio_cms_2760_g = divide_graph_by_function(cms_2760_g,fit_PL_xt);

	TGraph* ratio_nlo_1960 = divide_graph_by_function(g1960,fit_PL_xt);
	TGraph* ratio_nlo_1960a = divide_graph_by_function(g1960a,fit_PL_xt);
	TGraph* ratio_nlo_1960b = divide_graph_by_function(g1960b,fit_PL_xt);
	TGraph* ratio_nlo_1960c = divide_graph_by_function(g1960c,fit_PL_xt);
	TGraph* ratio_nlo_1960d = divide_graph_by_function(g1960d,fit_PL_xt);
	TGraph* ratio_nlo_1960e = divide_graph_by_function(g1960e,fit_PL_xt);
	TGraph* ratio_nlo_1960f = divide_graph_by_function(g1960f,fit_PL_xt);
	TGraph* ratio_nlo_1960g = divide_graph_by_function(g1960g,fit_PL_xt);
	TGraph* ratio_nlo_900 = divide_graph_by_function(g900,fit_PL_xt);
	TGraph* ratio_nlo_900a = divide_graph_by_function(g900a,fit_PL_xt);
	TGraph* ratio_nlo_900b = divide_graph_by_function(g900b,fit_PL_xt);
	TGraph* ratio_nlo_7000 = divide_graph_by_function(g7000,fit_PL_xt);
	TGraph* ratio_nlo_7000a = divide_graph_by_function(g7000a,fit_PL_xt);
	TGraph* ratio_nlo_7000b = divide_graph_by_function(g7000b,fit_PL_xt);
	TGraph* ratio_nlo_7000c = divide_graph_by_function(g7000c,fit_PL_xt);
	TGraph* ratio_nlo_7000d = divide_graph_by_function(g7000d,fit_PL_xt);
	TGraph* ratio_nlo_7000e = divide_graph_by_function(g7000e,fit_PL_xt);
	TGraph* ratio_nlo_7000f = divide_graph_by_function(g7000f,fit_PL_xt);
	TGraph* ratio_nlo_7000g = divide_graph_by_function(g7000g,fit_PL_xt);
	TGraph* ratio_nlo_7000h = divide_graph_by_function(g7000h,fit_PL_xt);
	TGraph* ratio_nlo_7000i = divide_graph_by_function(g7000i,fit_PL_xt);
	TGraph* ratio_nlo_7000j = divide_graph_by_function(g7000j,fit_PL_xt);
	TGraph* ratio_nlo_7000k = divide_graph_by_function(g7000k,fit_PL_xt);

	TGraph* ratio_nlo_2760 = divide_graph_by_function(g2750,fit_PL_xt);
        TGraph* ratio_nlo_2760a = divide_graph_by_function(g2750a,fit_PL_xt);
        TGraph* ratio_nlo_2760b = divide_graph_by_function(g2750b,fit_PL_xt);
	TGraph* ratio_nlo_2760c = divide_graph_by_function(g2750c,fit_PL_xt);
	TGraph* ratio_nlo_2760d = divide_graph_by_function(g2750d,fit_PL_xt);
        TGraph* ratio_nlo_2760e = divide_graph_by_function(g2750e,fit_PL_xt);
        TGraph* ratio_nlo_2760f = divide_graph_by_function(g2750f,fit_PL_xt);
	
	TH1F *hratio = new TH1F("hratio",";x_{T};ratio",160,0.0003,0.07); 
	hratio->SetMaximum(3.0);
	hratio->SetMinimum(0.0);
	hratio->SetStats(0);
	hratio->Draw();

	ratio_cdf_1960_g->Draw("pz");
	ratio_cms_7000_g->Draw("pz");
	ratio_cms_900_g->Draw("pz");
	ratio_nlo_1960->Draw("pz");
	ratio_nlo_1960a->Draw("pz");
	ratio_nlo_1960b->Draw("pz");
	ratio_nlo_1960c->Draw("pz");
	ratio_nlo_1960d->Draw("pz");
	ratio_nlo_1960e->Draw("pz");
	ratio_nlo_1960f->Draw("pz");
	ratio_nlo_1960g->Draw("pz");
	ratio_nlo_900->Draw("pz");
	ratio_nlo_900a->Draw("pz");
	ratio_nlo_900b->Draw("pz");
	ratio_nlo_7000->Draw("pz");	
	ratio_nlo_7000a->Draw("pz");	
	ratio_nlo_7000b->Draw("pz");	
	ratio_nlo_7000c->Draw("pz");	
	ratio_nlo_7000d->Draw("pz");	
	ratio_nlo_7000e->Draw("pz");	
	ratio_nlo_7000f->Draw("pz");	
	ratio_nlo_7000g->Draw("pz");	
	ratio_nlo_7000h->Draw("pz");	
	ratio_nlo_7000i->Draw("pz");	
	ratio_nlo_7000j->Draw("pz");	
	ratio_nlo_7000k->Draw("pz");	

	ratio_nlo_2760->Draw("pz");
        ratio_nlo_2760a->Draw("pz");
        ratio_nlo_2760b->Draw("pz");
        ratio_nlo_2760c->Draw("pz");
	ratio_nlo_2760d->Draw("pz");
	ratio_nlo_2760e->Draw("pz");
        ratio_nlo_2760f->Draw("pz");
	
	TF1 *logfit1960 = new TF1("logfit1960","[0]+[1]*log(x)+[2]/x/x",0.003,0.04); // was 0.001
	logfit1960->SetLineWidth(2);
	logfit1960->SetLineColor(kOrange-3);
	ratio_cdf_1960_g->Fit(logfit1960,"REMW");
	logfit1960->Draw("same");
	
	TF1 *logfit7000 = new TF1("logfit7000","[0]+[1]*log(x)+[2]/x/x",0.0015,0.1); // was 0.001
	logfit7000->SetLineWidth(2);
	ratio_cms_7000_g->Fit(logfit7000,"REMW");
	
	TF1 *logfit900 = new TF1("logfit900","[0]+[1]*log(x)+[2]/sqrt(x)",0.008,0.05); // was 0.005
	logfit900->SetLineWidth(2);
	logfit900->SetLineColor(2);
	ratio_cms_900_g->Fit(logfit900,"REMW");
	ratio_cms_900_g->SetLineColor(kRed);
	
	TF1 *logfit2760 = new TF1("logfit2760","[0]+[1]*log(x)+[2]/x/x",0.003,0.04); // was 0.001 
        logfit2760->SetLineWidth(2);
        logfit2760->SetLineColor(kBlue);
        ratio_cms_2760_g->Fit(logfit2760,"REMW");
	logfit2760->Draw("same");

	TCanvas *c3 = new TCanvas("c3","Ratio of NLO-to-Data",600,600);
	hratio->Draw();
	TGraph *nlo_to_data_900 = divide_graph_by_function(ratio_nlo_900,logfit900,1);
	TGraph *nlo_to_data_900a = divide_graph_by_function(ratio_nlo_900a,logfit900,1);
	TGraph *nlo_to_data_900b = divide_graph_by_function(ratio_nlo_900b,logfit900,1);
	TGraph *nlo_to_data_1960 = divide_graph_by_function(ratio_nlo_1960,logfit1960,1);
	TGraph *nlo_to_data_1960a = divide_graph_by_function(ratio_nlo_1960a,logfit1960,1);
	TGraph *nlo_to_data_1960b = divide_graph_by_function(ratio_nlo_1960b,logfit1960,1);
	TGraph *nlo_to_data_1960c = divide_graph_by_function(ratio_nlo_1960c,logfit1960,1);
	TGraph *nlo_to_data_1960d = divide_graph_by_function(ratio_nlo_1960d,logfit1960,1);
	TGraph *nlo_to_data_1960e = divide_graph_by_function(ratio_nlo_1960e,logfit1960,1);
	TGraph *nlo_to_data_1960f = divide_graph_by_function(ratio_nlo_1960f,logfit1960,1);
	TGraph *nlo_to_data_1960g = divide_graph_by_function(ratio_nlo_1960g,logfit1960,1);
	TGraph *nlo_to_data_7000 = divide_graph_by_function(ratio_nlo_7000,logfit7000,1);
	TGraph *nlo_to_data_7000a = divide_graph_by_function(ratio_nlo_7000a,logfit7000,1);
	TGraph *nlo_to_data_7000b = divide_graph_by_function(ratio_nlo_7000b,logfit7000,1);
	TGraph *nlo_to_data_7000c = divide_graph_by_function(ratio_nlo_7000c,logfit7000,1);
	TGraph *nlo_to_data_7000d = divide_graph_by_function(ratio_nlo_7000d,logfit7000,1);
	TGraph *nlo_to_data_7000e = divide_graph_by_function(ratio_nlo_7000e,logfit7000,1);
	TGraph *nlo_to_data_7000f = divide_graph_by_function(ratio_nlo_7000f,logfit7000,1);
	TGraph *nlo_to_data_7000g = divide_graph_by_function(ratio_nlo_7000g,logfit7000,1);
	TGraph *nlo_to_data_7000h = divide_graph_by_function(ratio_nlo_7000h,logfit7000,1);
	TGraph *nlo_to_data_7000i = divide_graph_by_function(ratio_nlo_7000i,logfit7000,1);
	TGraph *nlo_to_data_7000j = divide_graph_by_function(ratio_nlo_7000j,logfit7000,1);
	TGraph *nlo_to_data_7000k = divide_graph_by_function(ratio_nlo_7000k,logfit7000,1);

	TGraph *nlo_to_data_2760 = divide_graph_by_function(ratio_nlo_2760,logfit2760,1);
        TGraph *nlo_to_data_2760a = divide_graph_by_function(ratio_nlo_2760a,logfit2760,1);
        TGraph *nlo_to_data_2760b = divide_graph_by_function(ratio_nlo_2760b,logfit2760,1);
	TGraph *nlo_to_data_2760c = divide_graph_by_function(ratio_nlo_2760c,logfit2760,1);
	TGraph *nlo_to_data_2760d = divide_graph_by_function(ratio_nlo_2760d,logfit2760,1);
	TGraph *nlo_to_data_2760e = divide_graph_by_function(ratio_nlo_2760e,logfit2760,1);
	TGraph *nlo_to_data_2760f = divide_graph_by_function(ratio_nlo_2760f,logfit2760,1);


	nlo_to_data_2760->Draw("pz");
        nlo_to_data_2760a->Draw("pz");
	nlo_to_data_2760b->Draw("pz");
        nlo_to_data_2760c->Draw("pz");
	nlo_to_data_2760d->Draw("pz");
        nlo_to_data_2760e->Draw("pz");
        nlo_to_data_2760f->Draw("pz");

	/*
	nlo_to_data_1960->Draw("pz");
	nlo_to_data_1960a->Draw("pz");
	nlo_to_data_1960b->Draw("pz");
	nlo_to_data_1960c->Draw("pz");
	nlo_to_data_1960d->Draw("pz");
	nlo_to_data_1960e->Draw("pz");
	nlo_to_data_1960f->Draw("pz");
	nlo_to_data_1960g->Draw("pz");
	nlo_to_data_900->Draw("pz");
	nlo_to_data_900a->Draw("pz");
	nlo_to_data_900b->Draw("pz");
	nlo_to_data_7000->Draw("pz");
	nlo_to_data_7000a->Draw("pz");
	nlo_to_data_7000b->Draw("pz");
	nlo_to_data_7000c->Draw("pz");
	nlo_to_data_7000d->Draw("pz");
	nlo_to_data_7000e->Draw("pz");
	nlo_to_data_7000f->Draw("pz");
	nlo_to_data_7000g->Draw("pz");
	nlo_to_data_7000h->Draw("pz");
	nlo_to_data_7000i->Draw("pz");
	nlo_to_data_7000j->Draw("pz");
	nlo_to_data_7000k->Draw("pz");
	*/

	TCanvas *c4 = new TCanvas("c4","Ratio of NLO-to-Data vs. pt",600,600);
	TH1F *hratiopt = new TH1F("hratiopt",";p_{T} GeV/c;ratio",160,1,500); 
	hratiopt->SetMaximum(1.5);
	hratiopt->SetMinimum(0.0);
	hratiopt->SetStats(0);
	hratiopt->Draw();
	TGraph* nlo_to_data_900_pt = xt_to_pt(nlo_to_data_900,900.);
	TGraph* nlo_to_data_900a_pt = xt_to_pt(nlo_to_data_900a,900.);
	TGraph* nlo_to_data_900b_pt = xt_to_pt(nlo_to_data_900b,900.);
	TGraph* nlo_to_data_1960_pt = xt_to_pt(nlo_to_data_1960,1960.);
	TGraph* nlo_to_data_1960a_pt = xt_to_pt(nlo_to_data_1960a,1960.);
	TGraph* nlo_to_data_1960b_pt = xt_to_pt(nlo_to_data_1960b,1960.);
	TGraph* nlo_to_data_1960c_pt = xt_to_pt(nlo_to_data_1960c,1960.);
	TGraph* nlo_to_data_1960d_pt = xt_to_pt(nlo_to_data_1960d,1960.);
	TGraph* nlo_to_data_1960e_pt = xt_to_pt(nlo_to_data_1960e,1960.);
	TGraph* nlo_to_data_1960f_pt = xt_to_pt(nlo_to_data_1960f,1960.);
	TGraph* nlo_to_data_1960g_pt = xt_to_pt(nlo_to_data_1960g,1960.);
	TGraph* nlo_to_data_7000_pt = xt_to_pt(nlo_to_data_7000,7000.);
	TGraph* nlo_to_data_7000a_pt = xt_to_pt(nlo_to_data_7000a,7000.);
	TGraph* nlo_to_data_7000b_pt = xt_to_pt(nlo_to_data_7000b,7000.);
	TGraph* nlo_to_data_7000c_pt = xt_to_pt(nlo_to_data_7000c,7000.);
	TGraph* nlo_to_data_7000d_pt = xt_to_pt(nlo_to_data_7000d,7000.);
	TGraph* nlo_to_data_7000e_pt = xt_to_pt(nlo_to_data_7000e,7000.);
	TGraph* nlo_to_data_7000f_pt = xt_to_pt(nlo_to_data_7000f,7000.);
	TGraph* nlo_to_data_7000g_pt = xt_to_pt(nlo_to_data_7000g,7000.);
	TGraph* nlo_to_data_7000h_pt = xt_to_pt(nlo_to_data_7000h,7000.);
	TGraph* nlo_to_data_7000i_pt = xt_to_pt(nlo_to_data_7000i,7000.);
	TGraph* nlo_to_data_7000j_pt = xt_to_pt(nlo_to_data_7000j,7000.);
	TGraph* nlo_to_data_7000k_pt = xt_to_pt(nlo_to_data_7000k,7000.);
	
	nlo_to_data_900_pt->Draw("c");
	nlo_to_data_900a_pt->Draw("c");
	nlo_to_data_900b_pt->Draw("c");
	
	nlo_to_data_1960_pt->Draw("c");
	nlo_to_data_1960a_pt->Draw("c");
	nlo_to_data_1960b_pt->Draw("c");
	nlo_to_data_1960c_pt->Draw("c");
	nlo_to_data_1960d_pt->Draw("c");
	nlo_to_data_1960e_pt->Draw("c");
	nlo_to_data_1960f_pt->Draw("c");
	nlo_to_data_1960g_pt->Draw("c");
	
	nlo_to_data_7000_pt->Draw("c");
	nlo_to_data_7000a_pt->Draw("c");
	nlo_to_data_7000b_pt->Draw("c");
	nlo_to_data_7000c_pt->Draw("c");
	nlo_to_data_7000d_pt->Draw("c");
	nlo_to_data_7000e_pt->Draw("c");
	nlo_to_data_7000f_pt->Draw("c");
	nlo_to_data_7000g_pt->Draw("c");
	nlo_to_data_7000h_pt->Draw("c");
	nlo_to_data_7000i_pt->Draw("c");
	nlo_to_data_7000j_pt->Draw("c");
	nlo_to_data_7000k_pt->Draw("c");
	
	gPad->SetLogx();
}

TGraph* xt_to_pt(TGraph* graph, Double_t roots) {
	
	Double_t *xt,*y;
	Double_t pt[256], ynew[256];
	Int_t n = graph->GetN();
	xt = graph->GetX();
	y = graph->GetY();
	
	Int_t validpoints = 0;
	for(Int_t i=0; i<n; i++) {
		pt[validpoints] = xt[i]*roots/2;
		ynew[validpoints] = y[i];
		if(pt[validpoints]!=0 && ynew[validpoints]!=0 && pt[validpoints]<200 && (pt[validpoints]<50 || roots>2000)) validpoints++;
		else cout << "invalid point at i=" << i << endl;
		cout << "i=" << i << "\tvalidpoints=" << validpoints << "\tpt=" << pt[validpoints] << "\tynew=" << ynew[validpoints]<< endl;
	}
	
	TGraph *out = new TGraph(validpoints,pt,ynew);
	out->SetLineColor(graph->GetMarkerColor());
	out->SetLineStyle(graph->GetLineStyle());
	out->SetMarkerColor(graph->GetMarkerColor());
	out->SetMarkerStyle(graph->GetMarkerStyle());
	return out;
	
}
