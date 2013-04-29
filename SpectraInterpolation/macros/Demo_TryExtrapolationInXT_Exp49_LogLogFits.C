//plots all spectra together

#include "/net/hidsk0001/d00/scratch/krajczar/ppRefForpPb_PilotRun/interpolation_HIN10005_kk/divide_graph_by_function.C"
#include "/net/hidsk0001/d00/scratch/krajczar/ppRefForpPb_PilotRun/interpolation_HIN10005_kk/scale_graph.C"

void Demo_TryExtrapolationInXT_Exp49_LogLogFits(Bool_t xt=kTRUE, Float_t expo=4.9)
{
        SetStyle();
        gStyle->SetOptFile(0);
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(0);
 
        xt=kTRUE;

	//define dummy histogram and some style parameters
	TH1F *dum;
 	dum = new TH1F("dum","",160,5e-4,0.3); 
	dum->SetMinimum(1e4);
	dum->SetMaximum(1e18);
	dum->SetTitle(Form(";x_{T};#sqrt{s}^{%0.1f}  E d^{3}#sigma/dp^{3}",expo));
	dum->SetLineWidth(0);
	dum->SetStats(0);
	dum->GetXaxis()->CenterTitle();
	dum->GetYaxis()->CenterTitle();
	dum->GetXaxis()->SetTitleSize(0.05);
	dum->GetYaxis()->SetTitleSize(0.05);
	dum->GetXaxis()->SetTitleOffset(1.17);
	dum->GetYaxis()->SetTitleOffset(1.3);

	gROOT->LoadMacro("/net/hidsk0001/d00/scratch/krajczar/ppRefForpPb_PilotRun/interpolation_HIN10005_kk/data_table_to_graph.C");

	//get 7 TeV points
	TGraphErrors *cms_7000_g = data_table_to_graph("cms",7000,xt,expo);
	cms_7000_g->SetMarkerColor(kBlack);
	
	TF1 *cms_7000_fit = new TF1("cms_7000_fit","[0]*pow(1.0+(x/[1]),[2])",10.*2./7000.,0.1);//Fit from 10 GeV/c
	cms_7000_fit->SetLineWidth(1);
	cms_7000_fit->SetParameters(3e22,2.5e-4,-7);
	cms_7000_g->Fit(cms_7000_fit,"REMW0");
	
	//get 2.36 TeV points
//	TGraphErrors *cms_2360_g = data_table_to_graph("cms",2360,xt,expo);
//	cms_2360_g->SetMarkerColor(kMagenta+3);
	
//	TF1 *cms_2360_fit = new TF1("cms_2360_fit","[0]*pow(1.0+(x/[1]),[2])",2e-3,0.1);
//	cms_2360_fit->SetLineWidth(1);
//	cms_2360_fit->SetParameters(3e22,2.5e-4,-7);
//	cms_2360_g->Fit(cms_2360_fit,"REMW0");

	//get 2.76 TeV points (KK using existing txt files)
	TGraphErrors *cms_2760_g = data_table_to_graph("cms",2760,xt,expo);
	cms_2760_g->SetMarkerColor(kMagenta+3);
	TF1 *cms_2760_fit = new TF1("cms_2760_fit","[0]*pow(1.0+(x/[1]),[2])",10.*2./2760.,0.1);//Fit from 10 GeV/c
	cms_2760_fit->SetLineColor(kMagenta+3);
	cms_2760_fit->SetLineWidth(1);
	cms_2760_fit->SetParameters(3e22,2.5e-4,-7);
	cms_2760_g->Fit(cms_2760_fit,"REMW0");
	
	//get 1.96 TeV points
	TGraphErrors *cdf_1960_g = data_table_to_graph("cdf",1960,xt,expo);
	cdf_1960_g->SetMarkerColor(kOrange-3);
	cdf_1960_g->SetMarkerStyle(30);
	
	//TGraphErrors *cdfold_1960_g = data_table_to_graph("cdfold",1960,xt);
	//cdfold_1960_g->SetMarkerColor(kBlue);
	//cdfold_1960_g->SetMarkerStyle(30);
	
	TF1 *cdf_1960_fit = new TF1("cdf_1960_fit","[0]*pow(1.0+(x/[1]),[2])",2.*10./1960.,0.1);//Fit from 10 GeV/c
	cdf_1960_fit->SetLineColor(kOrange-3);
	cdf_1960_fit->SetLineWidth(1);
	cdf_1960_fit->SetParameters(3e22,2.5e-4,-7);
	cdf_1960_g->Fit(cdf_1960_fit,"REMW0");
	
	//get 1.8 TeV points
	TGraphErrors *cdf_1800_g = data_table_to_graph("cdf",1800,xt,expo);
	cdf_1800_g->SetMarkerColor(kGreen+3);
	cdf_1800_g->SetMarkerStyle(28);

	TF1 *cdf_1800_fit = new TF1("cdf_1800_fit","[0]*pow(1.0+(x/[1]),[2])",2.*10./1800.,0.1);//Fit from 10 GeV/c
	cdf_1800_fit->SetLineColor(kGreen+3);
	cdf_1800_fit->SetLineWidth(1);
	cdf_1800_fit->SetParameters(3e22,2.5e-4,-7.2);
	cdf_1800_fit->FixParameter(2,-7.2);
	cdf_1800_g->Fit(cdf_1800_fit,"REMW0");
	
	//get 0.9 TeV points
	TGraphErrors *cms_900_g = data_table_to_graph("cms",900,xt,expo);
	cms_900_g->SetMarkerColor(kRed);
	
	TF1 *cms_900_fit = new TF1("cms_900_fit","[0]*pow(1.0+(x/[1]),[2])",2.*10./900.,0.01);//Fit from 10 GeV/c
	cms_900_fit->SetLineColor(kRed);
	cms_900_fit->SetLineWidth(1);
	cms_900_fit->SetParameters(3e22,2.5e-4,-7);
	cms_900_g->Fit(cms_900_fit,"REMW0");
	
//	TGraphErrors *ua1_900_g = data_table_to_graph("ua1",900,xt,expo);
//	ua1_900_g->SetMarkerColor(kCyan+1);
//	ua1_900_g->SetMarkerStyle(26);

	// get 0.63 TeV points
	TGraphErrors *cdf_630_g = data_table_to_graph("cdf",630,xt,expo);
	cdf_630_g->SetMarkerColor(kOrange+3);
	cdf_630_g->SetMarkerStyle(27);

	//draw graphs to canvas
	TCanvas *c1 = new TCanvas("c1","spectra interpolation",600,600);
	dum->Draw();
        //Fits are already drawn, no draw the points on top of the fits
	cdf_1960_g->Draw("pz");
	//cdfold_1960_g->Draw("pz");
//	cdf_1800_g->Draw("pz");
//	if(!xt) ua1_900_g->Draw("pz"); // abs(eta) within 2.5 changes high xt behavior
//	cdf_630_g->Draw("pz");
	cms_900_g->Draw("pz");         // draw the CMS points on top
//	cms_2360_g->Draw("pz");
	cms_2760_g->Draw("pz"); //KK
	cms_7000_g->Draw("pz");

	//make legend
	TLegend *leg1 = new TLegend(0.2,0.21,0.50,0.51,"p+p(#bar{p})");
	leg1->SetBorderSize(0);
	leg1->SetFillStyle(1);
	leg1->SetFillColor(0);
	leg1->AddEntry(cms_7000_g,"7 TeV  (CMS)","lp");
	leg1->AddEntry(cms_2760_g,"2.76 TeV (CMS)","lp");
//	leg1->AddEntry(cms_2360_g,"2.36 TeV (CMS)","lp");
	leg1->AddEntry(cdf_1960_g,"1.96 TeV  (CDF)","lp");
//	leg1->AddEntry(cdf_1800_g,"1.8 TeV  (CDF)","lp");
	leg1->AddEntry(cms_900_g,"0.9 TeV  (CMS)","lp");
//	if(!xt) leg1->AddEntry(ua1_900_g,"0.9 TeV  (UA1)  |#eta|<2.5","lp");
//	leg1->AddEntry(cdf_630_g,"0.63 TeV  (CDF)","lp");
	leg1->Draw();
	
	gPad->SetLogy();
	//if(xt) gPad->SetLogx();
	gPad->SetLogx();
	
	cms_7000_fit->Draw("same");
	cms_2760_fit->Draw("same");
	cdf_1960_fit->Draw("same");
//	cdf_1800_fit->Draw("same");
	cms_900_fit->Draw("same");

	TCanvas *c3 = new TCanvas("c3","Individual xT fits, residuals",600,500);
	TH1F *hratio = new TH1F("hratio",";x_{T};ratio",160,0.0003,0.07); //was 0.003-0.04
	hratio->SetMaximum(2.0);
	hratio->SetMinimum(0.0);
	hratio->SetStats(0);
	hratio->Draw();
		
	TGraphErrors* ratio_cdf_1960_g = divide_graph_by_function(cdf_1960_g,cdf_1960_fit);
	ratio_cdf_1960_g->SetName("ratio_cdf_1960_g");
	ratio_cdf_1960_g->SetLineColor(kOrange-9);
	ratio_cdf_1960_g->SetMarkerSize(0.9);
	ratio_cdf_1960_g->Draw("samepz");
		
	TF1 *fit1960 = new TF1("fit1960","[0]+[1]*log(x)+[2]/x/x",0.001,0.035);
	fit1960->SetLineWidth(2);
	fit1960->SetLineColor(kOrange-3);
	ratio_cdf_1960_g->Fit(fit1960,"REMW");
	fit1960->Draw("same");
		
//	TGraphErrors* ratio_cdf_1800_g = divide_graph_by_function(cdf_1800_g,cdf_1800_fit);
//	ratio_cdf_1800_g->Draw("samepz");
		
//	TGraphErrors* ratio_cdf_630_g = divide_graph_by_function(cdf_630_g,merge_fit);
	//ratio_cdf_630_g->Draw("pz");
	
	TGraphErrors* ratio_cms_7000_g = divide_graph_by_function(cms_7000_g,cms_7000_fit);
	ratio_cms_7000_g->SetName("ratio_cms_7000_g");
	ratio_cms_7000_g->Draw("samepz");
		
	TF1 *fit7000 = new TF1("fit7000","[0]+[1]*x+[2]*x*x+[3]*x*x*x",0.001,0.1);
	fit7000->SetLineWidth(2);
	ratio_cms_7000_g->Fit(fit7000,"REMW");

	TGraphErrors* ratio_cms_2760_g = divide_graph_by_function(cms_2760_g,cms_2760_fit);
	ratio_cms_2760_g->SetName("ratio_cms_2760_g");
	ratio_cms_2760_g->SetLineColor(kMagenta+3);
	ratio_cms_2760_g->Draw("samepz");
		
        TF1 *fit2760 = new TF1("fit2760","[0]+[1]*x+[2]*x*x+[3]*x*x*x",0.001,0.1);
	fit2760->SetLineWidth(2);
	fit2760->SetLineColor(kMagenta+3);
	ratio_cms_2760_g->Fit(fit2760,"REM");//REMW
		
	TGraphErrors* ratio_cms_900_g = divide_graph_by_function(cms_900_g,cms_900_fit);
	ratio_cms_900_g->SetName("ratio_cms_900_g");
	ratio_cms_900_g->Draw("samepz");
		
        TF1 *fit900 = new TF1("fit900","[0]+[1]*x+[2]*x*x+[3]*x*x*x",0.007,0.1);
        fit900->SetParameters(5.61766e-01,5.24904e+01,-2.27817e+03,3.43955e+04);
	fit900->SetLineWidth(2);
	fit900->SetLineColor(2);
	ratio_cms_900_g->Fit(fit900,"REM");//REMW
	ratio_cms_900_g->SetLineColor(kRed);
		
	TGaxis *A1 = new TGaxis(0.0003,2.0,0.07,2.0,2510*0.0003,2510*0.07,410,"-");
	A1->SetTitle("p_{T} for #sqrt{s}=5.02 TeV");
	A1->Draw();

        //Real fit should be the fit*resid
	TH1D *h900 = new TH1D("h900","900 GeV fitted spectra;x_{T}",30400,0.005,0.05);
	h900->SetLineColor(kRed);
	TH1D *h1960 = new TH1D("h1960","1.96 TeV fitted spectra;x_{T}",30400,0.005,0.05);
	h1960->SetLineColor(kOrange-3);
	TH1D *h7000 = new TH1D("h7000","7 TeV fitted spectra;x_{T}",30400,0.005,0.05);
	TH1D *h1800 = new TH1D("h1800","1.8 TeV fitted spectra;x_{T}",30400,0.005,0.05);
	h1800->SetLineColor(kGreen+3);
	TH1D *h630 = new TH1D("h630","0.63 TeV fitted spectra;x_{T}",30400,0.005,0.05);
	h630->SetLineColor(kOrange+3);
	TH1D *h2760_EdTxt = new TH1D("h2760_EdTxt","2.76 TeV fitted spectra;x_{T}",30400,0.005,0.05);
	h2760_EdTxt->SetLineColor(kMagenta+3);

	for(int hbin=1; hbin<=30400; hbin++) {
		float xtbin = h900->GetBinCenter(hbin);
		h900->SetBinContent(hbin,cms_900_fit->Eval(xtbin)*fit900->Eval(xtbin));
		h1960->SetBinContent(hbin,cdf_1960_fit->Eval(xtbin)*fit1960->Eval(xtbin));
		h7000->SetBinContent(hbin,cms_7000_fit->Eval(xtbin)*fit7000->Eval(xtbin));
		h2760_EdTxt->SetBinContent(hbin,cms_2760_fit->Eval(xtbin)*fit2760->Eval(xtbin));
	}

	TCanvas *c5 = new TCanvas("c5","final x_{T} fits",600,500);
	TH1D* dumDirectInt = new TH1D("dumDirectInt","Final fits; x_{T} (GeV/c)",120,5e-4,0.3);
	dumDirectInt->SetMaximum(1e18);
	dumDirectInt->SetMinimum(1e4);
	dumDirectInt->GetXaxis()->SetRangeUser(0.5,120.);
	dumDirectInt->SetStats(0);
	dumDirectInt->GetYaxis()->SetTitle("Ed^{3}#sigma/dp^{3}");
	dumDirectInt->Draw();
	h900->Draw("same");
	h1960->Draw("same");
	h7000->Draw("same");
	h2760_EdTxt->Draw("same");
	gPad->SetLogy();
	gPad->SetLogx();

	// inspect direct interpolations
	TCanvas *c6 = new TCanvas("c6","interpolations",600,500);
	c6->Divide(3,4);
	float s[6]; float xs[6]; float es[6]={0.0,0.0,0.0,0.0,0.0,0.0}; float exs[6];   TGraphErrors *gXS[12];
        float s_log[6]; float xs_log[6]; float es_log[6]={0.0,0.0,0.0,0.0,0.0,0.0}; float exs_log[6];
        TGraphErrors *gXS_log[12]; //KK test
        TGraphErrors *gXS_log_lemma[12]; //KK test
	float s1[1]={2.76}; float xs1[1]; float ex1[1]={0.0}; float ey1[1]; 		TGraphErrors *gXS1[12];
	float s1_5020[1]={5.02}; float xs1_5020[1]; float ex1_5020[1]={0.0}; float ey1_5020[1]; TGraphErrors *gXS1_5020[12];
	float s2[1]={2.76}; float xs2[1]; float ex2[1]={0.0}; float ey2[1]; 		TGraphErrors *gXS2[12];
	float s2_5020[1]={5.02}; float xs2_5020[1]; float ex2_5020[1]={0.0}; float ey2_5020[1]; TGraphErrors *gXS2_5020[12];
	float s900[1]={0.9}; float xs900[1]; float ex900[1]={0.0}; float ey900[1]; TGraphErrors *gXS900[12];
	float s1960[1]={1.96}; float xs1960[1]; float ex1960[1]={0.0}; float ey1960[1]; TGraphErrors *gXS1960[12];
	float s2760[1]={2.76}; float xs2760[1]; float ex2760[1]={0.0}; float ey2760[1]; TGraphErrors *gXS2760[12];
	float s7000[1]={7.0}; float xs7000[1]; float ex7000[1]={0.0}; float ey7000[1]; TGraphErrors *gXS7000[12];

	TF1 *fitXS[12];  TH1F *dumXS[12];
        TF1 *fitXS_log[12];
	float xtbins[12]={0.0051,0.007,0.01,0.015,0.02,0.025,0.03,0.035,0.04,0.042,0.045,0.049};
        //2pT/sqrt(s) = xT ==>> xT=0.0051 -> pT=12.8 GeV/c; xT=0.049 -> pT=123 GeV/c

        //errors        
        TMVA::TSpline1 *err_cms_900_xt = errors_from_graph(cms_900_g,0.115);
        TMVA::TSpline1 *err_cms_2760_xt = errors_from_graph(cms_2760_g,0.11);
        TMVA::TSpline1 *err_cms_7000_xt = errors_from_graph(cms_7000_g,0.04);	
        TMVA::TSpline1 *err_cdf_1960_xt = errors_from_graph(cdf_1960_g,0.06);

	for(Int_t ipt=0; ipt<=11; ipt++) {
						
		c6->cd(ipt+1);
		int npoints=0;

		xs[npoints]=h900->GetBinContent(h900->FindBin(xtbins[ipt])); s[npoints]=0.9; exs[npoints]=err_cms_900_xt->Eval(xtbins[ipt])*xs[npoints]; xs900[0]=xs[npoints]; ey900[0]=exs[npoints];
		xs_log[npoints]=log10(xs[npoints]); s_log[npoints]=log10(s[npoints]); exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
                npoints++;

		xs[npoints]=h1960->GetBinContent(h1960->FindBin(xtbins[ipt])); s[npoints]=1.96; exs[npoints]=err_cdf_1960_xt->Eval(xtbins[ipt])*xs[npoints]; xs1960[0]=xs[npoints]; ey1960[0]=exs[npoints];
		xs_log[npoints]=log10(xs[npoints]); s_log[npoints]=log10(s[npoints]); exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
                npoints++;
 
		xs[npoints]=h2760_EdTxt->GetBinContent(h2760_EdTxt->FindBin(xtbins[ipt])); s[npoints]=2.76; exs[npoints]=err_cms_2760_xt->Eval(xtbins[ipt])*xs[npoints]; xs2760[0]=xs[npoints]; ey2760[0]=exs[npoints];
		xs_log[npoints]=log10(xs[npoints]); s_log[npoints]=log10(s[npoints]); exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
                npoints++;

		xs[npoints]=h7000->GetBinContent(h7000->FindBin(xtbins[ipt])); s[npoints]=7.0; exs[npoints]=err_cms_7000_xt->Eval(xtbins[ipt])*xs[npoints]; xs7000[0]=xs[npoints]; ey7000[0]=exs[npoints];
		xs_log[npoints]=log10(xs[npoints]); s_log[npoints]=log10(s[npoints]); exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
                npoints++;
			
		dumXS[ipt] = new TH1F(Form("dumXS%d",ipt),Form("p_{T} = %0.0f GeV/c;#sqrt{s} [TeV]",xtbins[ipt]),100,0,20);
		dumXS[ipt]->SetMinimum(0.25*xs[npoints-1]);
		dumXS[ipt]->SetMaximum(4.0*xs[0]);
		dumXS[ipt]->SetStats(0);
		dumXS[ipt]->GetXaxis()->SetRangeUser(0.5,10.0);
              	dumXS[ipt]->GetXaxis()->CenterTitle();
               	dumXS[ipt]->GetYaxis()->CenterTitle();
               	dumXS[ipt]->GetYaxis()->SetTitle("Ed#sigma^{3}/dp^{3}");
               	dumXS[ipt]->GetXaxis()->SetTitleSize(0.10);
               	dumXS[ipt]->GetYaxis()->SetTitleSize(0.10);
               	dumXS[ipt]->GetYaxis()->SetLabelSize(0.10);
               	dumXS[ipt]->GetXaxis()->SetLabelSize(0.10);
               	dumXS[ipt]->GetXaxis()->SetTitleOffset(0.6);
               	dumXS[ipt]->GetYaxis()->SetTitleOffset(0.8);
		dumXS[ipt]->Draw();
		gPad->SetLogy();  
                gPad->SetLogx();

                std::cerr<< "npoints: " << npoints << std::endl;

		gXS[ipt] = new TGraphErrors(npoints,s,xs,es,exs);  gXS[ipt]->SetName(Form("gXS%d",ipt));
		gXS[ipt]->SetMarkerStyle(20);
		gXS_log[ipt] = new TGraphErrors(npoints,s_log,xs_log,es_log,exs_log); gXS_log[ipt]->SetName(Form("gXS_log%d",ipt));

		gXS900[ipt] = new TGraphErrors(1,s900,xs900,ex900,ey900); gXS900[ipt]->SetName(Form("gXS900_%d",ipt)); 
		gXS900[ipt]->SetMarkerStyle(20);  gXS900[ipt]->SetMarkerColor(kRed); gXS900[ipt]->Draw("pz");

		gXS1960[ipt] = new TGraphErrors(1,s1960,xs1960,ex1960,ey1960); gXS1960[ipt]->SetName(Form("gXS1960_%d",ipt)); 
		gXS1960[ipt]->SetMarkerStyle(30);  gXS1960[ipt]->SetMarkerColor(kOrange-3); gXS1960[ipt]->Draw("pz");

		gXS2760[ipt] = new TGraphErrors(1,s2760,xs2760,ex2760,ey2760); gXS2760[ipt]->SetName(Form("gXS2760_%d",ipt)); 
		gXS2760[ipt]->SetMarkerStyle(20);  gXS2760[ipt]->SetMarkerColor(kMagenta+3); gXS2760[ipt]->Draw("pz");	

		gXS7000[ipt] = new TGraphErrors(1,s7000,xs7000,ex7000,ey7000); gXS7000[ipt]->SetName(Form("gXS7000_%d",ipt)); 
		gXS7000[ipt]->SetMarkerStyle(20);  gXS7000[ipt]->SetMarkerColor(kBlack); gXS7000[ipt]->Draw("pz");	
			
		fitXS_log[ipt] = new TF1(Form("fitXS_log%d",ipt),"pol2",-0.52288,0.85733);
		gXS_log[ipt]->Fit(fitXS_log[ipt], "REM0"); //"REMW");

		// full covariance errors on fit
		TVirtualFitter *fitter = TVirtualFitter::GetFitter();
		TMatrixD matrix(3,3,fitter->GetCovarianceMatrix());
		Double_t e00 = fitter->GetCovarianceMatrixElement(0,0);
		Double_t e11 = fitter->GetCovarianceMatrixElement(1,1);
		Double_t e22 = fitter->GetCovarianceMatrixElement(2,2);
		Double_t e01 = fitter->GetCovarianceMatrixElement(0,1);
		Double_t e02 = fitter->GetCovarianceMatrixElement(0,2);
		Double_t e12 = fitter->GetCovarianceMatrixElement(1,2);

                //Due to properties of the covariance matrix:
                Double_t e10 = e01;
                Double_t e20 = e02;
                Double_t e21 = e12;

                gXS_log_lemma[ipt] = new TGraphErrors(); gXS_log_lemma[ipt]->SetName(Form("gXS_log_lemma%d",ipt));
                int kkk = 0;
                for(int kk = log10(0.8*s[0])*10000.; kk <= log10(1.3*s[npoints-1])*10000.; kk++) {
                      float kk_lemma = kk/10000.;
                      float value = fitXS_log[ipt]->Eval(kk_lemma);
                      gXS_log_lemma[ipt]->SetPoint(kkk,TMath::Power(10,kk_lemma),TMath::Power(10,value));
                      kkk++;
                }
                gXS_log_lemma[ipt]->SetLineColor(2);
                gXS_log_lemma[ipt]->Draw("same");
			
		cout << "cov(0,0) = " << e00 
		<< "\ncov(1,1) = " << e11 
		<< "\ncov(2,2) = " << e22 
		<< "\ncov(0,1) = " << e01 
		<< "\ncov(0,2) = " << e02 
		<< "\ncov(1,2) = " << e12 
		<< endl;
			
                //0.7007 = log10(5.02)
		Double_t fullerr2 = e00 + e11*0.7007*0.7007 + e22*0.7007*0.7007*0.7007*0.7007 + 2*e01*0.7007 + 2*e02*0.7007*0.7007 + 2*e12*0.7007*0.7007*0.7007;
                //Plan (1.,0.7007,0.7007^2)(COV)(1.,0.7007,0.7007^2):
                Double_t where = 0.7007;
                Double_t fullerr2_alternative = e00 + 2.*e01*where + 2.*e02*where*where + 2.*e12*where*where*where + e11*where*where + e22*where*where*where*where;
			
		cout << "full covariance error = " << TMath::Sqrt(fullerr2) << endl;
		cout << "full covariance error alternative: = " << TMath::Sqrt(fullerr2_alternative) << endl;
                float error_in_percentage = 100.*(TMath::Power(10,TMath::Sqrt(fullerr2))-1.);
                cout << "   on " << fitXS_log[ipt]->Eval(0.7007) << std::endl;
                cout << "   error in percentage: " << error_in_percentage << std::endl;

                //5020
		xs2_5020[0] = TMath::Power(10,fitXS_log[ipt]->Eval(0.7007));
		ey2_5020[0] = error_in_percentage*0.01*xs2_5020[0];
		gXS2_5020[ipt] = new TGraphErrors(1,s2_5020,xs2_5020,ex2_5020,ey2_5020); gXS2_5020[ipt]->SetName(Form("gXS2_5020_%d",ipt));
		gXS2_5020[ipt]->SetMarkerColor(7);
		gXS2_5020[ipt]->SetLineColor(7);
		gXS2_5020[ipt]->SetMarkerStyle(kOpenSquare);
		gXS2_5020[ipt]->Draw("pz");
	}
}

void SetStyle() {

   gStyle->SetErrorX(0);
   gStyle->SetPalette(1,0);
   gStyle->SetPadColor(0);
   gStyle->SetPadBorderSize(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetFrameBorderMode(0);
   gStyle->SetFrameLineColor(0);
   gStyle->SetTitleColor(0);
   gStyle->SetTitleBorderSize(0);

   gStyle->SetPalette(1,0);

   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetPadColor(0);
   gStyle->SetPadBorderSize(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetFrameBorderMode(0);
   gStyle->SetFrameLineColor(0);
   gStyle->SetTextFont(62);
   gStyle->SetLabelFont(42,"XYZ");
   gStyle->SetTitleFont(42,"XYZ");
   gStyle->SetTitleColor(0);
   gStyle->SetTitleBorderSize(0);
   gStyle->SetTitleXSize(.045);
   gStyle->SetTitleYSize(.045);
   //gStyle->SetTitleXOffset(1.0);
   //gStyle->SetTitleYOffset(1.6);
   gStyle->SetTitleXOffset(1.2);
   //gStyle->SetTitleYOffset(2.2);
   gStyle->SetTitleYOffset(1.8);
   gStyle->SetLabelSize(0.040,"XYZ");
   gStyle->SetLabelOffset(0.01,"X");
   gStyle->SetLabelOffset(0.01,"Y");
   gStyle->SetTitleColor(1,"XYZ");
   gStyle->SetHistFillColor(1);
   gStyle->SetHistFillStyle(0);
   gStyle->SetHistLineColor(1);
   gStyle->SetHistLineStyle(0);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistLineWidth(1);
   gStyle->SetEndErrorSize(0);
   gStyle->SetErrorX(0);
   gStyle->SetMarkerStyle(20);
   //gStyle->SetMarkerSize(1.25);
   gStyle->SetMarkerSize(1.5);

   gStyle->SetOptFit(1111);
   gStyle->SetStatColor(0);
   gStyle->SetStatBorderSize(1);
   gStyle->SetOptTitle(0);
   //gStyle->SetOptStat(1111);
   //gStyle->SetOptStat(0);


   gStyle->SetPadLeftMargin(0.17);
   //gStyle->SetPadLeftMargin(0.21);
   gStyle->SetPadBottomMargin(0.14);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadRightMargin(0.04);


   const Int_t NRGBs = 5;
   //const Int_t NCont = 255;
   const Int_t NCont = 200;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   //gStyle->CreateColorGradientTable(NRGBs, stops, red, green, blue, NCont);

   gStyle->SetNumberContours(NCont);

   gROOT->ForceStyle();
}
