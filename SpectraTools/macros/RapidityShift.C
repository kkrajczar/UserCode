void RapidityShift() {

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
//   gStyle->SetPadRightMargin(0.16);

   double eta_P1 = 1.;
   double eta_P05 = 0.5;
   double eta_0 = 0.;
   double eta_N05 = -0.5;
   double eta_N1 = -1.;

   double mom_p = 4000.;
   double mom_Pb = 4000.*(82./208.);

   double mass_p = 0.938;
//   double mass_Pb = 200.*0.938;
   double mass_Pb = 0.938; //Convention

   double E_p = TMath::Sqrt(mom_p*mom_p + mass_p*mass_p);
   double E_Pb = TMath::Sqrt(mom_Pb*mom_Pb + mass_Pb*mass_Pb);

   double p_com = mom_Pb - mom_p;
   //For the collisions energy
   double E_com = TMath::Sqrt((E_p + E_Pb)**2 - (mom_Pb - mom_p)**2);
   std::cerr<<"p_com: " << p_com << std::endl;
   std::cerr<<"E_com: " << E_com << std::endl;

   double E_tot = TMath::Sqrt((E_p + E_Pb)**2);

   double beta_com = p_com/E_tot;
   double gamma_com = 1./TMath::Sqrt(1-beta_com*beta_com);

   std::cerr<<"beta_com: " << beta_com << std::endl;
   std::cerr<<"gamma_com: " << gamma_com << std::endl;

   TH1D * h_eta_prime_pion_eta_P1 = new TH1D("h_eta_prime_pion_eta_P1","h_eta_prime_pion_eta_P1",5000,0.001,5.);
   TH1D * h_eta_prime_pion_eta_P05 = new TH1D("h_eta_prime_pion_eta_P05","h_eta_prime_pion_eta_P05",5000,0.001,5.);
   TH1D * h_eta_prime_pion_eta_0 = new TH1D("h_eta_prime_pion_eta_0","h_eta_prime_pion_eta_0",5000,0.001,5.);
   TH1D * h_eta_prime_pion_eta_N05 = new TH1D("h_eta_prime_pion_eta_N05","h_eta_prime_pion_eta_N05",5000,0.001,5.);
   TH1D * h_eta_prime_pion_eta_N1 = new TH1D("h_eta_prime_pion_eta_N1","h_eta_prime_pion_eta_N1",5000,0.001,5.);

   TH1D * h_eta_prime_proton_eta_P1 = new TH1D("h_eta_prime_proton_eta_P1","h_eta_prime_proton_eta_P1",5000,0.001,5.);
   TH1D * h_eta_prime_proton_eta_P05 = new TH1D("h_eta_prime_proton_eta_P05","h_eta_prime_proton_eta_P05",5000,0.001,5.);
   TH1D * h_eta_prime_proton_eta_0 = new TH1D("h_eta_prime_proton_eta_0","h_eta_prime_proton_eta_0",5000,0.001,5.);
   TH1D * h_eta_prime_proton_eta_N05 = new TH1D("h_eta_prime_proton_eta_N05","h_eta_prime_proton_eta_N05",5000,0.001,5.);
   TH1D * h_eta_prime_proton_eta_N1 = new TH1D("h_eta_prime_proton_eta_N1","h_eta_prime_proton_eta_N1",5000,0.001,5.);

   computeEtaPrim(h_eta_prime_pion_eta_P1,eta_P1,gamma_com,beta_com,1);
   computeEtaPrim(h_eta_prime_pion_eta_P05,eta_P05,gamma_com,beta_com,1);
   computeEtaPrim(h_eta_prime_pion_eta_0,eta_0,gamma_com,beta_com,1);
   computeEtaPrim(h_eta_prime_pion_eta_N05,eta_N05,gamma_com,beta_com,1);
   computeEtaPrim(h_eta_prime_pion_eta_N1,eta_N1,gamma_com,beta_com,1);

   computeEtaPrim(h_eta_prime_proton_eta_P1,eta_P1,gamma_com,beta_com,2);
   computeEtaPrim(h_eta_prime_proton_eta_P05,eta_P05,gamma_com,beta_com,2);
   computeEtaPrim(h_eta_prime_proton_eta_0,eta_0,gamma_com,beta_com,2);
   computeEtaPrim(h_eta_prime_proton_eta_N05,eta_N05,gamma_com,beta_com,2);
   computeEtaPrim(h_eta_prime_proton_eta_N1,eta_N1,gamma_com,beta_com,2);

   TCanvas *c1 = new TCanvas("c1","c1");
   h_eta_prime_pion_eta_P1->SetMaximum(3.);
   h_eta_prime_pion_eta_P1->SetMinimum(-2.);
   h_eta_prime_pion_eta_P1->SetLineColor(2);
   h_eta_prime_pion_eta_P1->SetLineStyle(1);
   h_eta_prime_pion_eta_P1->SetLineWidth(2);
   h_eta_prime_pion_eta_P1->GetXaxis()->CenterTitle();
   h_eta_prime_pion_eta_P1->GetYaxis()->CenterTitle();
   h_eta_prime_pion_eta_P1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   h_eta_prime_pion_eta_P1->GetYaxis()->SetTitle("#eta in the lab frame");
   h_eta_prime_pion_eta_P1->Draw();
   h_eta_prime_pion_eta_P05->SetLineColor(6);
   h_eta_prime_pion_eta_P05->SetLineStyle(2);
   h_eta_prime_pion_eta_P05->SetLineWidth(2);
   h_eta_prime_pion_eta_P05->Draw("same");
   h_eta_prime_pion_eta_0->SetLineColor(kBlack);
   h_eta_prime_pion_eta_0->SetLineStyle(3);
   h_eta_prime_pion_eta_0->SetLineWidth(2);
   h_eta_prime_pion_eta_0->Draw("same");
   h_eta_prime_pion_eta_N05->SetLineColor(40);
   h_eta_prime_pion_eta_N05->SetLineStyle(4);
   h_eta_prime_pion_eta_N05->SetLineWidth(2);
   h_eta_prime_pion_eta_N05->Draw("same");
   h_eta_prime_pion_eta_N1->SetLineColor(4);
   h_eta_prime_pion_eta_N1->SetLineStyle(5);
   h_eta_prime_pion_eta_N1->SetLineWidth(2);
   h_eta_prime_pion_eta_N1->Draw("same");

   TLegend *leg1 = new TLegend(0.25,0.65,0.55,0.90,"Pions","brNDC");
   leg1->AddEntry(h_eta_prime_pion_eta_P1,"#eta_{COM} = 1","l");
   leg1->AddEntry(h_eta_prime_pion_eta_P05,"#eta_{COM} = 0.5","l");
   leg1->AddEntry(h_eta_prime_pion_eta_0,"#eta_{COM} = 0","l");
   leg1->AddEntry(h_eta_prime_pion_eta_N05,"#eta_{COM} = -0.5","l");
   leg1->AddEntry(h_eta_prime_pion_eta_N1,"#eta_{COM} = -1","l");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();

   TPad *c1_zoom = new TPad("c1_zoom","c1_zoom",0.56,0.56,0.94,0.93);
   c1_zoom->SetFillStyle(0);
   c1_zoom->Draw();
   c1_zoom->cd();
   TH1D* h_eta_prime_pion_eta_P1_clone = (TH1D*)h_eta_prime_pion_eta_P1->Clone("h_eta_prime_pion_eta_P1_clone");
   TH1D* h_eta_prime_pion_eta_P05_clone = (TH1D*)h_eta_prime_pion_eta_P05->Clone("h_eta_prime_pion_eta_P05_clone");
   TH1D* h_eta_prime_pion_eta_0_clone = (TH1D*)h_eta_prime_pion_eta_0->Clone("h_eta_prime_pion_eta_0_clone");
   TH1D* h_eta_prime_pion_eta_N1_clone = (TH1D*)h_eta_prime_pion_eta_N1->Clone("h_eta_prime_pion_eta_N1_clone");
   TH1D* h_eta_prime_pion_eta_N05_clone = (TH1D*)h_eta_prime_pion_eta_N05->Clone("h_eta_prime_pion_eta_N05_clone");
   h_eta_prime_pion_eta_P1_clone->GetXaxis()->SetRangeUser(0.,0.6);
   h_eta_prime_pion_eta_P1_clone->SetMaximum(1.);
   h_eta_prime_pion_eta_P1_clone->Draw();
   h_eta_prime_pion_eta_P05_clone->Draw("same");
   h_eta_prime_pion_eta_0_clone->Draw("same");
   h_eta_prime_pion_eta_N05_clone->Draw("same");
   h_eta_prime_pion_eta_N1_clone->Draw("same");


   TCanvas *c2 = new TCanvas("c2","c2");
   h_eta_prime_proton_eta_P1->SetMaximum(3.);
   h_eta_prime_proton_eta_P1->SetMinimum(-2.);
   h_eta_prime_proton_eta_P1->SetLineColor(2);
   h_eta_prime_proton_eta_P1->SetLineStyle(1);
   h_eta_prime_proton_eta_P1->SetLineWidth(2);
   h_eta_prime_proton_eta_P1->GetXaxis()->CenterTitle();
   h_eta_prime_proton_eta_P1->GetYaxis()->CenterTitle();
   h_eta_prime_proton_eta_P1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   h_eta_prime_proton_eta_P1->GetYaxis()->SetTitle("#eta in the lab frame");
   h_eta_prime_proton_eta_P1->Draw();
   h_eta_prime_proton_eta_P05->SetLineColor(6);
   h_eta_prime_proton_eta_P05->SetLineStyle(2);
   h_eta_prime_proton_eta_P05->SetLineWidth(2);
   h_eta_prime_proton_eta_P05->Draw("same");
   h_eta_prime_proton_eta_0->SetLineColor(kBlack);
   h_eta_prime_proton_eta_0->SetLineStyle(3);
   h_eta_prime_proton_eta_0->SetLineWidth(2);
   h_eta_prime_proton_eta_0->Draw("same");
   h_eta_prime_proton_eta_N05->SetLineColor(40);
   h_eta_prime_proton_eta_N05->SetLineStyle(4);
   h_eta_prime_proton_eta_N05->SetLineWidth(2);
   h_eta_prime_proton_eta_N05->Draw("same");
   h_eta_prime_proton_eta_N1->SetLineColor(4);
   h_eta_prime_proton_eta_N1->SetLineStyle(5);
   h_eta_prime_proton_eta_N1->SetLineWidth(2);
   h_eta_prime_proton_eta_N1->Draw("same");

   TLegend *leg2 = new TLegend(0.25,0.65,0.55,0.90,"Protons","brNDC");
   leg2->AddEntry(h_eta_prime_proton_eta_P1,"#eta_{COM} = 1","l");
   leg2->AddEntry(h_eta_prime_proton_eta_P05,"#eta_{COM} = 0.5","l");
   leg2->AddEntry(h_eta_prime_proton_eta_0,"#eta_{COM} = 0","l");
   leg2->AddEntry(h_eta_prime_proton_eta_N05,"#eta_{COM} = -0.5","l");
   leg2->AddEntry(h_eta_prime_proton_eta_N1,"#eta_{COM} = -1","l");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();

   TPad *c2_zoom = new TPad("c2_zoom","c2_zoom",0.56,0.56,0.94,0.93);
   c2_zoom->SetFillStyle(0);
   c2_zoom->Draw();
   c2_zoom->cd();
   TH1D* h_eta_prime_proton_eta_P1_clone = (TH1D*)h_eta_prime_proton_eta_P1->Clone("h_eta_prime_proton_eta_P1_clone");
   TH1D* h_eta_prime_proton_eta_P05_clone = (TH1D*)h_eta_prime_proton_eta_P05->Clone("h_eta_prime_proton_eta_P05_clone");
   TH1D* h_eta_prime_proton_eta_0_clone = (TH1D*)h_eta_prime_proton_eta_0->Clone("h_eta_prime_proton_eta_0_clone");
   TH1D* h_eta_prime_proton_eta_N1_clone = (TH1D*)h_eta_prime_proton_eta_N1->Clone("h_eta_prime_proton_eta_N1_clone");
   TH1D* h_eta_prime_proton_eta_N05_clone = (TH1D*)h_eta_prime_proton_eta_N05->Clone("h_eta_prime_proton_eta_N05_clone");
   h_eta_prime_proton_eta_P1_clone->GetXaxis()->SetRangeUser(0.,1.);
   h_eta_prime_proton_eta_P1_clone->SetMaximum(1.);
   h_eta_prime_proton_eta_P1_clone->Draw();
   h_eta_prime_proton_eta_P05_clone->Draw("same");
   h_eta_prime_proton_eta_0_clone->Draw("same");
   h_eta_prime_proton_eta_N05_clone->Draw("same");
   h_eta_prime_proton_eta_N1_clone->Draw("same");
}

TH1D* computeEtaPrim(TH1D* h_result, double eta, double gamma, double beta, int particle) {

    double mass_p = 0.938;
    double mass_pion = 0.13957;
    double mass = 0.;
 
   if(particle==1)
       mass = mass_pion;
    else if(particle==2)
       mass = mass_p;
    else
       std::cerr<<" [Warning] 0 mass! " << std::endl;

   //pT loop
   for(int i = 1.; i<=5000; i++) {

      double pT = (double)i/1000.;

      //give the eta and pT of the particle
      double pz = pT*TMath::SinH(eta);
      double E = TMath::Sqrt(pz*pz + pT*pT + mass*mass);

      //what I want is to transform something from center-of-mass eta to lab eta'
      //what is being transformed is pz, pT stays fix
      double pT_prime = pT;

      //Lorentz transformation: note that we use -beta, because we transform out from the com system!
      double pz_prime = gamma*pz - (-1.*beta)*gamma*E;

      double theta = atan2(pT_prime,pz_prime);
      double eta_prime = -TMath::Log(TMath::Tan(theta/2.));
//      double eta_prime = TMath::ASinH(pT_prime/pz_prime); //This gives wrong results. Why?

      h_result->SetBinContent(h_result->FindBin(pT),eta_prime);      
   }

   return h_result;
}
