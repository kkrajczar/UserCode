{
  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gStyle->SetOptStat(0);
  gROOT->ForceStyle();

  gStyle->SetErrorX(0);

  TCanvas MyCanvas("MyCanvas","MyCanvas");

   TH1 *dndeta0 = new TH1F("dndeta0","dndeta0",14,-3.5,3.5);
   dndeta0->SetMinimum(0);
   dndeta0->SetMaximum(500);
   dndeta0->SetStats(0);
   dndeta0->GetXaxis()->SetTitle("#eta");
/*
   dndeta0->GetXaxis()->SetNdivisions(508);
   dndeta0->GetXaxis()->SetLabelSize(0.08);
   dndeta0->GetXaxis()->SetTitleSize(0.11);
   dndeta0->GetXaxis()->SetTitleOffset(0.7);
*/
   dndeta0->GetYaxis()->SetTitle("dN/d#eta");
//   dndeta0->GetYaxis()->SetNdivisions(505);
//   dndeta0->GetYaxis()->SetLabelOffset(0.01);
//   dndeta0->GetYaxis()->SetLabelSize(0.08);
//   dndeta0->GetYaxis()->SetTitleSize(0.09);
//   dndeta0->GetYaxis()->SetTitleOffset(0.89);
   dndeta0->Draw("");

  //data
  TChain ntuple1("multProp");
  for(int i = 1; i<=100; i++) {
    ntuple1.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  TChain ntuple2("multProp_looper");
  for(int i = 1; i<=100; i++) {
    ntuple2.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  //sim
  TChain ntuple1_sim("multProp");
  for(int i = 1; i<=100; i++) {
    ntuple1_sim.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  TChain ntuple2_sim("multProp_looper");
  for(int i = 1; i<=100; i++) {
    ntuple2_sim.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  TChain ntuple3_sim("hJustLooper");
  for(int i = 1; i<=100; i++) {
    ntuple3_sim.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  //define multiplicity bins
  int num_mult_bins = 31;
  vector<int> mult_bins;
  int mult_bin_lemma = 0;
  for(int ii = 0; ii<num_mult_bins; ii++) {
//     std::cerr<<" mult_bin_lemma: " << mult_bin_lemma << std::endl;
     mult_bins.push_back(mult_bin_lemma);
     if(ii<10)
        mult_bin_lemma += 50;
     else
        mult_bin_lemma += 500;
  }

  TH1D* hEpsilon = new TH1D("hEpsilon","hEpsilon",10000,-0.5,9999.5);

  TH1D* hNumEv = new TH1D("hNumEv","hNumEv",2,-0.5,1.5);
  TH1D* hTrigger = new TH1D("hTrigger","hTrigger",2,-0.5,1.5);
  TH1D* hTrigger_data = new TH1D("hTrigger_data","hTrigger_data",2,-0.5,1.5);

  TH1D* hclustSizeY_etaP5 = new TH1D("hclustSizeY_etaP5","hclustSizeY_etaP5",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaP4 = new TH1D("hclustSizeY_etaP4","hclustSizeY_etaP4",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaP3 = new TH1D("hclustSizeY_etaP3","hclustSizeY_etaP3",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaP2 = new TH1D("hclustSizeY_etaP2","hclustSizeY_etaP2",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaP1 = new TH1D("hclustSizeY_etaP1","hclustSizeY_etaP1",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN1 = new TH1D("hclustSizeY_etaN1","hclustSizeY_etaN1",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN2 = new TH1D("hclustSizeY_etaN2","hclustSizeY_etaN2",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN3 = new TH1D("hclustSizeY_etaN3","hclustSizeY_etaN3",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN4 = new TH1D("hclustSizeY_etaN4","hclustSizeY_etaN4",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN5 = new TH1D("hclustSizeY_etaN5","hclustSizeY_etaN5",10000,-0.5,9999.5);

  TH1D* hclustSizeY_etaP5_DATA = new TH1D("hclustSizeY_etaP5_DATA","hclustSizeY_etaP5_DATA",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaP4_DATA = new TH1D("hclustSizeY_etaP4_DATA","hclustSizeY_etaP4_DATA",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaP3_DATA = new TH1D("hclustSizeY_etaP3_DATA","hclustSizeY_etaP3_DATA",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaP2_DATA = new TH1D("hclustSizeY_etaP2_DATA","hclustSizeY_etaP2_DATA",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaP1_DATA = new TH1D("hclustSizeY_etaP1_DATA","hclustSizeY_etaP1_DATA",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN1_DATA = new TH1D("hclustSizeY_etaN1_DATA","hclustSizeY_etaN1_DATA",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN2_DATA = new TH1D("hclustSizeY_etaN2_DATA","hclustSizeY_etaN2_DATA",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN3_DATA = new TH1D("hclustSizeY_etaN3_DATA","hclustSizeY_etaN3_DATA",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN4_DATA = new TH1D("hclustSizeY_etaN4_DATA","hclustSizeY_etaN4_DATA",10000,-0.5,9999.5);
  TH1D* hclustSizeY_etaN5_DATA = new TH1D("hclustSizeY_etaN5_DATA","hclustSizeY_etaN5_DATA",10000,-0.5,9999.5);

  TH1D* hT_truth_etaP5 = new TH1D("hT_truth_etaP5","hT_truth_etaP5",10000,-0.5,9999.5);
  TH1D* hT_truth_etaP4 = new TH1D("hT_truth_etaP4","hT_truth_etaP4",10000,-0.5,9999.5);
  TH1D* hT_truth_etaP3 = new TH1D("hT_truth_etaP3","hT_truth_etaP3",10000,-0.5,9999.5);
  TH1D* hT_truth_etaP2 = new TH1D("hT_truth_etaP2","hT_truth_etaP2",10000,-0.5,9999.5);
  TH1D* hT_truth_etaP1 = new TH1D("hT_truth_etaP1","hT_truth_etaP1",10000,-0.5,9999.5);
  TH1D* hT_truth_etaN1 = new TH1D("hT_truth_etaN1","hT_truth_etaN1",10000,-0.5,9999.5);
  TH1D* hT_truth_etaN2 = new TH1D("hT_truth_etaN2","hT_truth_etaN2",10000,-0.5,9999.5);
  TH1D* hT_truth_etaN3 = new TH1D("hT_truth_etaN3","hT_truth_etaN3",10000,-0.5,9999.5);
  TH1D* hT_truth_etaN4 = new TH1D("hT_truth_etaN4","hT_truth_etaN4",10000,-0.5,9999.5);
  TH1D* hT_truth_etaN5 = new TH1D("hT_truth_etaN5","hT_truth_etaN5",10000,-0.5,9999.5);

  // final distribution
  double TEST_noEpsilon = 0.;
  double nevezo = 0.;
  double NumOfRecEvents = 0.;
  //original numerators
  double szamlalo_etaP5 = 0.;
  double szamlalo_etaP4 = 0.;
  double szamlalo_etaP3 = 0.;
  double szamlalo_etaP2 = 0.;
  double szamlalo_etaP1 = 0.;
  double szamlalo_etaN1 = 0.;
  double szamlalo_etaN2 = 0.;
  double szamlalo_etaN3 = 0.;
  double szamlalo_etaN4 = 0.;
  double szamlalo_etaN5 = 0.;
  
  //looper corrected numerators
  double corr_szamlalo_etaP5 = 0.;
  double corr_szamlalo_etaP4 = 0.;
  double corr_szamlalo_etaP3 = 0.;
  double corr_szamlalo_etaP2 = 0.;
  double corr_szamlalo_etaP1 = 0.;
  double corr_szamlalo_etaN1 = 0.;
  double corr_szamlalo_etaN2 = 0.;
  double corr_szamlalo_etaN3 = 0.;
  double corr_szamlalo_etaN4 = 0.;
  double corr_szamlalo_etaN5 = 0.;

  //compute the correction in eta and multiplicity bins
  float correct1_etaP5_DATA[10000];
  float correct1_etaP4_DATA[10000];
  float correct1_etaP3_DATA[10000];
  float correct1_etaP2_DATA[10000];
  float correct1_etaP1_DATA[10000];
  float correct1_etaN1_DATA[10000];
  float correct1_etaN2_DATA[10000];
  float correct1_etaN3_DATA[10000];
  float correct1_etaN4_DATA[10000];
  float correct1_etaN5_DATA[10000];

  ////////////////////////
  //
  // Summation
  //
  ////////////////////////

  int which = 1;
  TH1D * chi_all = new TH1D("chi_all","chi_all",14,-3.5,3.5);
  TH1D * chi_1 = new TH1D("chi_1","chi_1",14,-3.5,3.5);
  TH1D * chi_2 = new TH1D("chi_2","chi_2",14,-3.5,3.5);
  TH1D * chi_3 = new TH1D("chi_3","chi_3",14,-3.5,3.5);
  TH1D * chi_11 = new TH1D("chi_11","chi_11",14,-3.5,3.5);
  TH1D * chi_14 = new TH1D("chi_14","chi_14",14,-3.5,3.5);
  TH1D * chi_29 = new TH1D("chi_29","chi_29",14,-3.5,3.5);

  double P5Hits = 0.;
  double P4Hits = 0.;
  double P3Hits = 0.;
  double P2Hits = 0.;
  double P1Hits = 0.;
  double N1Hits = 0.;
  double N2Hits = 0.;
  double N3Hits = 0.;
  double N4Hits = 0.;
  double N5Hits = 0.;

  double P5Tracks = 0.;
  double P4Tracks = 0.;
  double P3Tracks = 0.;
  double P2Tracks = 0.;
  double P1Tracks = 0.;
  double N1Tracks = 0.;
  double N2Tracks = 0.;
  double N3Tracks = 0.;
  double N4Tracks = 0.;
  double N5Tracks = 0.;

  std::cerr<< std::endl;
  std::cerr<<" summation" << std::endl;
  // compute the dNdeta distribution
  char cond[300], condV[300], condVData[300];
  for(int i = 0; i < num_mult_bins-1; i++) {   //-1 because [i+1]
     std::cerr<< "   "<< i;
     //BEWARE: NUMEV continue stuff!!!

     hNumEv->Reset();
     hTrigger->Reset();  
     hTrigger_data->Reset();
     hclustSizeY_etaP5->Reset();
     hclustSizeY_etaP4->Reset();
     hclustSizeY_etaP3->Reset();
     hclustSizeY_etaP2->Reset();
     hclustSizeY_etaP1->Reset();
     hclustSizeY_etaN1->Reset();
     hclustSizeY_etaN2->Reset();
     hclustSizeY_etaN3->Reset();
     hclustSizeY_etaN4->Reset();
     hclustSizeY_etaN5->Reset();

     hclustSizeY_etaP5_DATA->Reset();
     hclustSizeY_etaP4_DATA->Reset();
     hclustSizeY_etaP3_DATA->Reset();
     hclustSizeY_etaP2_DATA->Reset();
     hclustSizeY_etaP1_DATA->Reset();
     hclustSizeY_etaN1_DATA->Reset();
     hclustSizeY_etaN2_DATA->Reset();
     hclustSizeY_etaN3_DATA->Reset();
     hclustSizeY_etaN4_DATA->Reset();
     hclustSizeY_etaN5_DATA->Reset();

     hT_truth_etaP5->Reset();
     hT_truth_etaP4->Reset();
     hT_truth_etaP3->Reset();
     hT_truth_etaP2->Reset();
     hT_truth_etaP1->Reset();
     hT_truth_etaN1->Reset();
     hT_truth_etaN2->Reset();
     hT_truth_etaN3->Reset();
     hT_truth_etaN4->Reset();
     hT_truth_etaN5->Reset();

     // BEWARE!!! CHECK CONDITIONS
     //mc
     sprintf(cond,"cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(condV,"rver_z!=0 && bit34 && isTrigger_1 && bit36==0 && bit37==0 && bit38==0 && bit39==0 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);

     //data
     sprintf(condVData,"rver_z!=0 && bit34 && isTrigger_1 && bit36==0 && bit37==0 && bit38==0 && bit39==0 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);

     // fill histograms
     ntuple1_sim->Project("hNumEv","numEv",cond);
     double numEv = hNumEv->GetBinContent(hNumEv->FindBin(1.));

     //BEWARE!!!
     if(numEv==0)
       continue;

     ntuple1_sim->Project("hTrigger","numEv",condV);
     ntuple1->Project("hTrigger_data","numEv",condVData);
     ntuple1_sim->Project("hclustSizeY_etaP5","clustSizeY_etaP5",condV);
     ntuple1_sim->Project("hclustSizeY_etaP4","clustSizeY_etaP4",condV);
     ntuple1_sim->Project("hclustSizeY_etaP3","clustSizeY_etaP3",condV);
     ntuple1_sim->Project("hclustSizeY_etaP2","clustSizeY_etaP2",condV);
     ntuple1_sim->Project("hclustSizeY_etaP1","clustSizeY_etaP1",condV);
     ntuple1_sim->Project("hclustSizeY_etaN1","clustSizeY_etaN1",condV);
     ntuple1_sim->Project("hclustSizeY_etaN2","clustSizeY_etaN2",condV);
     ntuple1_sim->Project("hclustSizeY_etaN3","clustSizeY_etaN3",condV);
     ntuple1_sim->Project("hclustSizeY_etaN4","clustSizeY_etaN4",condV);
     ntuple1_sim->Project("hclustSizeY_etaN5","clustSizeY_etaN5",condV);

     ntuple1->Project("hclustSizeY_etaP5_DATA","clustSizeY_etaP5",condVData);
     ntuple1->Project("hclustSizeY_etaP4_DATA","clustSizeY_etaP4",condVData);
     ntuple1->Project("hclustSizeY_etaP3_DATA","clustSizeY_etaP3",condVData);
     ntuple1->Project("hclustSizeY_etaP2_DATA","clustSizeY_etaP2",condVData);
     ntuple1->Project("hclustSizeY_etaP1_DATA","clustSizeY_etaP1",condVData);
     ntuple1->Project("hclustSizeY_etaN1_DATA","clustSizeY_etaN1",condVData);
     ntuple1->Project("hclustSizeY_etaN2_DATA","clustSizeY_etaN2",condVData);
     ntuple1->Project("hclustSizeY_etaN3_DATA","clustSizeY_etaN3",condVData);
     ntuple1->Project("hclustSizeY_etaN4_DATA","clustSizeY_etaN4",condVData);
     ntuple1->Project("hclustSizeY_etaN5_DATA","clustSizeY_etaN5",condVData);

     ntuple1_sim->Project("hT_truth_etaP5","T_truth_etaP5",condV);
     ntuple1_sim->Project("hT_truth_etaP4","T_truth_etaP4",condV);
     ntuple1_sim->Project("hT_truth_etaP3","T_truth_etaP3",condV);
     ntuple1_sim->Project("hT_truth_etaP2","T_truth_etaP2",condV);
     ntuple1_sim->Project("hT_truth_etaP1","T_truth_etaP1",condV);
     ntuple1_sim->Project("hT_truth_etaN1","T_truth_etaN1",condV);
     ntuple1_sim->Project("hT_truth_etaN2","T_truth_etaN2",condV);
     ntuple1_sim->Project("hT_truth_etaN3","T_truth_etaN3",condV);
     ntuple1_sim->Project("hT_truth_etaN4","T_truth_etaN4",condV);
     ntuple1_sim->Project("hT_truth_etaN5","T_truth_etaN5",condV);

     double trackTrigger = hTrigger->GetBinContent(hTrigger->FindBin(1.));
     double trackTrigger_data = hTrigger_data->GetBinContent(hTrigger_data->FindBin(1.));
 
     // original hits
     double vclustSizeY_etaP5 = hclustSizeY_etaP5->GetMean(1);   
     double vclustSizeY_etaP4 = hclustSizeY_etaP4->GetMean(1);
     double vclustSizeY_etaP3 = hclustSizeY_etaP3->GetMean(1);
     double vclustSizeY_etaP2 = hclustSizeY_etaP2->GetMean(1);
     double vclustSizeY_etaP1 = hclustSizeY_etaP1->GetMean(1);
     double vclustSizeY_etaN1 = hclustSizeY_etaN1->GetMean(1);
     double vclustSizeY_etaN2 = hclustSizeY_etaN2->GetMean(1);   
     double vclustSizeY_etaN3 = hclustSizeY_etaN3->GetMean(1);
     double vclustSizeY_etaN4 = hclustSizeY_etaN4->GetMean(1);
     double vclustSizeY_etaN5 = hclustSizeY_etaN5->GetMean(1);

     double vclustSizeY_etaP5_DATA = hclustSizeY_etaP5_DATA->GetMean(1);
     double vclustSizeY_etaP4_DATA = hclustSizeY_etaP4_DATA->GetMean(1);
     double vclustSizeY_etaP3_DATA = hclustSizeY_etaP3_DATA->GetMean(1);
     double vclustSizeY_etaP2_DATA = hclustSizeY_etaP2_DATA->GetMean(1);
     double vclustSizeY_etaP1_DATA = hclustSizeY_etaP1_DATA->GetMean(1);
     double vclustSizeY_etaN1_DATA = hclustSizeY_etaN1_DATA->GetMean(1);
     double vclustSizeY_etaN2_DATA = hclustSizeY_etaN2_DATA->GetMean(1);
     double vclustSizeY_etaN3_DATA = hclustSizeY_etaN3_DATA->GetMean(1);
     double vclustSizeY_etaN4_DATA = hclustSizeY_etaN4_DATA->GetMean(1);
     double vclustSizeY_etaN5_DATA = hclustSizeY_etaN5_DATA->GetMean(1);
/*
     //looper corrected hits: sim (chi) and data
     double corr_vclustSizeY_etaP5 = vclustSizeY_etaP5-failed_etaP5[i]*correct1_etaP5[i];
     double corr_vclustSizeY_etaP4 = vclustSizeY_etaP4-failed_etaP4[i]*correct1_etaP4[i];
     double corr_vclustSizeY_etaP3 = vclustSizeY_etaP3-failed_etaP3[i]*correct1_etaP3[i];
     double corr_vclustSizeY_etaP2 = vclustSizeY_etaP2-failed_etaP2[i]*correct1_etaP2[i];
     double corr_vclustSizeY_etaP1 = vclustSizeY_etaP1-failed_etaP1[i]*correct1_etaP1[i];
     double corr_vclustSizeY_etaN1 = vclustSizeY_etaN1-failed_etaN1[i]*correct1_etaN1[i];
     double corr_vclustSizeY_etaN2 = vclustSizeY_etaN2-failed_etaN2[i]*correct1_etaN2[i];
     double corr_vclustSizeY_etaN3 = vclustSizeY_etaN3-failed_etaN3[i]*correct1_etaN3[i];
     double corr_vclustSizeY_etaN4 = vclustSizeY_etaN4-failed_etaN4[i]*correct1_etaN4[i];
     double corr_vclustSizeY_etaN5 = vclustSizeY_etaN5-failed_etaN5[i]*correct1_etaN5[i];

     double corr_vclustSizeY_etaP5_DATA = vclustSizeY_etaP5_DATA-failed_etaP5_DATA[i]*correct1_etaP5[i];
     double corr_vclustSizeY_etaP4_DATA = vclustSizeY_etaP4_DATA-failed_etaP4_DATA[i]*correct1_etaP4[i];
     double corr_vclustSizeY_etaP3_DATA = vclustSizeY_etaP3_DATA-failed_etaP3_DATA[i]*correct1_etaP3[i];
     double corr_vclustSizeY_etaP2_DATA = vclustSizeY_etaP2_DATA-failed_etaP2_DATA[i]*correct1_etaP2[i];
     double corr_vclustSizeY_etaP1_DATA = vclustSizeY_etaP1_DATA-failed_etaP1_DATA[i]*correct1_etaP1[i];
     double corr_vclustSizeY_etaN1_DATA = vclustSizeY_etaN1_DATA-failed_etaN1_DATA[i]*correct1_etaN1[i];
     double corr_vclustSizeY_etaN2_DATA = vclustSizeY_etaN2_DATA-failed_etaN2_DATA[i]*correct1_etaN2[i];
     double corr_vclustSizeY_etaN3_DATA = vclustSizeY_etaN3_DATA-failed_etaN3_DATA[i]*correct1_etaN3[i];
     double corr_vclustSizeY_etaN4_DATA = vclustSizeY_etaN4_DATA-failed_etaN4_DATA[i]*correct1_etaN4[i];
     double corr_vclustSizeY_etaN5_DATA = vclustSizeY_etaN5_DATA-failed_etaN5_DATA[i]*correct1_etaN5[i];
*/
     //non-looper corrected hits: sim (chi) and data
     double corr_vclustSizeY_etaP5 = vclustSizeY_etaP5;
     double corr_vclustSizeY_etaP4 = vclustSizeY_etaP4;
     double corr_vclustSizeY_etaP3 = vclustSizeY_etaP3;
     double corr_vclustSizeY_etaP2 = vclustSizeY_etaP2;
     double corr_vclustSizeY_etaP1 = vclustSizeY_etaP1;
     double corr_vclustSizeY_etaN1 = vclustSizeY_etaN1;
     double corr_vclustSizeY_etaN2 = vclustSizeY_etaN2;
     double corr_vclustSizeY_etaN3 = vclustSizeY_etaN3;
     double corr_vclustSizeY_etaN4 = vclustSizeY_etaN4;
     double corr_vclustSizeY_etaN5 = vclustSizeY_etaN5;

     double corr_vclustSizeY_etaP5_DATA = vclustSizeY_etaP5_DATA;
     double corr_vclustSizeY_etaP4_DATA = vclustSizeY_etaP4_DATA;
     double corr_vclustSizeY_etaP3_DATA = vclustSizeY_etaP3_DATA;
     double corr_vclustSizeY_etaP2_DATA = vclustSizeY_etaP2_DATA;
     double corr_vclustSizeY_etaP1_DATA = vclustSizeY_etaP1_DATA;
     double corr_vclustSizeY_etaN1_DATA = vclustSizeY_etaN1_DATA;
     double corr_vclustSizeY_etaN2_DATA = vclustSizeY_etaN2_DATA;
     double corr_vclustSizeY_etaN3_DATA = vclustSizeY_etaN3_DATA;
     double corr_vclustSizeY_etaN4_DATA = vclustSizeY_etaN4_DATA;
     double corr_vclustSizeY_etaN5_DATA = vclustSizeY_etaN5_DATA;

     // tracks
     double vT_truth_etaP5 = hT_truth_etaP5->GetMean(1);
     double vT_truth_etaP4 = hT_truth_etaP4->GetMean(1);
     double vT_truth_etaP3 = hT_truth_etaP3->GetMean(1);
     double vT_truth_etaP2 = hT_truth_etaP2->GetMean(1);
     double vT_truth_etaP1 = hT_truth_etaP1->GetMean(1);
     double vT_truth_etaN1 = hT_truth_etaN1->GetMean(1);
     double vT_truth_etaN2 = hT_truth_etaN2->GetMean(1);
     double vT_truth_etaN3 = hT_truth_etaN3->GetMean(1);
     double vT_truth_etaN4 = hT_truth_etaN4->GetMean(1);
     double vT_truth_etaN5 = hT_truth_etaN5->GetMean(1);

     P5Hits += corr_vclustSizeY_etaP5;
     P5Tracks += vT_truth_etaP5;
     P4Hits += corr_vclustSizeY_etaP4;
     P4Tracks += vT_truth_etaP4;
     P3Hits += corr_vclustSizeY_etaP3;
     P3Tracks += vT_truth_etaP3;
     P2Hits += corr_vclustSizeY_etaP2;
     P2Tracks += vT_truth_etaP2;
     P1Hits += corr_vclustSizeY_etaP1;
     P1Tracks += vT_truth_etaP1;
     N1Hits += corr_vclustSizeY_etaN1;
     N1Tracks += vT_truth_etaN1;
     N2Hits += corr_vclustSizeY_etaN2;
     N2Tracks += vT_truth_etaN2;
     N3Hits += corr_vclustSizeY_etaN3;
     N3Tracks += vT_truth_etaN3;
     N4Hits += corr_vclustSizeY_etaN4;
     N4Tracks += vT_truth_etaN4;
     N5Hits += corr_vclustSizeY_etaN5;
     N5Tracks += vT_truth_etaN5;

     //computing alphas
     if(vT_truth_etaP5!=0 && vclustSizeY_etaP5!=0) {
       double vAlpha_etaP5 = vclustSizeY_etaP5/(vT_truth_etaP5);
       double corr_vAlpha_etaP5 = corr_vclustSizeY_etaP5/(vT_truth_etaP5);
       double corr_vAlpha_etaP5_error = corr_vAlpha_etaP5*sqrt((1./corr_vclustSizeY_etaP5));// + (1./vT_truth_etaP5));
     }
     if(i>50 && (vT_truth_etaP5==0 || vclustSizeY_etaP5==0)) {
       double vAlpha_etaP5 = 1.2;
       double corr_vAlpha_etaP5 = 1.2;
     }
     if(i<=50 && (vT_truth_etaP5==0 || vclustSizeY_etaP5==0)) {
       double vAlpha_etaP5 = 1.;
       double corr_vAlpha_etaP5 = 1.;
     }

     if(vT_truth_etaP4!=0 && vclustSizeY_etaP4!=0) {
       double vAlpha_etaP4 = vclustSizeY_etaP4/vT_truth_etaP4;
       double corr_vAlpha_etaP4 = corr_vclustSizeY_etaP4/vT_truth_etaP4;
       double corr_vAlpha_etaP4_error = corr_vAlpha_etaP4*sqrt((1./corr_vclustSizeY_etaP4));// + (1./vT_truth_etaP4));
     }
     if(i>50 && (vT_truth_etaP4==0 || vclustSizeY_etaP4==0)) {
       double vAlpha_etaP4 = 1.2;
       double corr_vAlpha_etaP4 = 1.2;
     }
     if(i<=50 && (vT_truth_etaP4==0 || vclustSizeY_etaP4==0)) {
       double vAlpha_etaP4 = 1.;
       double corr_vAlpha_etaP4 = 1.;
     }

     if(vT_truth_etaP3!=0) {
       double vAlpha_etaP3 = vclustSizeY_etaP3/vT_truth_etaP3;
       double corr_vAlpha_etaP3 = corr_vclustSizeY_etaP3/vT_truth_etaP3;
       double corr_vAlpha_etaP3_error = corr_vAlpha_etaP3*sqrt((1./corr_vclustSizeY_etaP3));// + (1./vT_truth_etaP3));
     }
     if(i>50 && vT_truth_etaP3==0) {
       double vAlpha_etaP3 = 1.2;
       double corr_vAlpha_etaP3 = 1.2;
     }
     if(i<=50 && vT_truth_etaP3==0) {
       double vAlpha_etaP3 = 0.;
       double corr_vAlpha_etaP3 = 0.;
     }

     if(vT_truth_etaP2!=0) {
       double vAlpha_etaP2 = vclustSizeY_etaP2/vT_truth_etaP2;
       double corr_vAlpha_etaP2 = corr_vclustSizeY_etaP2/vT_truth_etaP2;
       double corr_vAlpha_etaP2_error = corr_vAlpha_etaP2*sqrt((1./corr_vclustSizeY_etaP2));// + (1./vT_truth_etaP2));
     } 
     if(i>50 && vT_truth_etaP2==0) {
       double vAlpha_etaP2 = 1.2;
       double corr_vAlpha_etaP2 = 1.2;
     }
     if(i<=50 && vT_truth_etaP2==0) {
       double vAlpha_etaP2 = 0.;
       double corr_vAlpha_etaP2 = 0.;
     }

     if(vT_truth_etaP1!=0) {
       double vAlpha_etaP1 = vclustSizeY_etaP1/vT_truth_etaP1;
       double corr_vAlpha_etaP1 = corr_vclustSizeY_etaP1/vT_truth_etaP1;
       double corr_vAlpha_etaP1_error = corr_vAlpha_etaP1*sqrt((1./corr_vclustSizeY_etaP1));// + (1./vT_truth_etaP1));
     }
     if(i>50 && vT_truth_etaP1==0) {
       double vAlpha_etaP1 = 1.2;
       double corr_vAlpha_etaP1 = 1.2; 
     }
     if(i<=50 && vT_truth_etaP1==0) {
       double vAlpha_etaP1 = 0;
       double corr_vAlpha_etaP1 = 0;
     }

     if(vT_truth_etaN1!=0) {
       double vAlpha_etaN1 = vclustSizeY_etaN1/vT_truth_etaN1;
       double corr_vAlpha_etaN1 = corr_vclustSizeY_etaN1/vT_truth_etaN1;
       double corr_vAlpha_etaN1_error = corr_vAlpha_etaN1*sqrt((1./corr_vclustSizeY_etaN1));// + (1./vT_truth_etaN1));
     }
     if(i>50 && vT_truth_etaN1==0) {
       double vAlpha_etaN1 = 1.2;
       double corr_vAlpha_etaN1 = 1.2;
     }
     if(i<=50 && vT_truth_etaN1==0) {
       double vAlpha_etaN1 = 0.;
       double corr_vAlpha_etaN1 = 0.;
     }    

     if(vT_truth_etaN2!=0) {
       double vAlpha_etaN2 = vclustSizeY_etaN2/vT_truth_etaN2;
       double corr_vAlpha_etaN2 = corr_vclustSizeY_etaN2/vT_truth_etaN2;
       double corr_vAlpha_etaN2_error = corr_vAlpha_etaN2*sqrt((1./corr_vclustSizeY_etaN2));// + (1./vT_truth_etaN2));
     }
     if(i>50 && vT_truth_etaN2==0) {
       double vAlpha_etaN2 = 1.2;
       double corr_vAlpha_etaN2 = 1.2;
     }
     if(i<=50 && vT_truth_etaN2==0) {
       double vAlpha_etaN2 = 0.;
       double corr_vAlpha_etaN2 = 0.;
     }

     if(vT_truth_etaN3!=0) {
       double vAlpha_etaN3 = vclustSizeY_etaN3/vT_truth_etaN3;
       double corr_vAlpha_etaN3 = corr_vclustSizeY_etaN3/vT_truth_etaN3;
       double corr_vAlpha_etaN3_error = corr_vAlpha_etaN3*sqrt((1./corr_vclustSizeY_etaN3));// + (1./vT_truth_etaN3));
     }
     if(i>50 && vT_truth_etaN3==0) {
       double vAlpha_etaN3 = 1.2;
       double corr_vAlpha_etaN3 = 1.2;
     }
     if(i<=50 && vT_truth_etaN3==0) {
       double vAlpha_etaN3 = 0.;
       double corr_vAlpha_etaN3 = 0.;
     }

     if(vT_truth_etaN4!=0) {
       double vAlpha_etaN4 = vclustSizeY_etaN4/vT_truth_etaN4;
       double corr_vAlpha_etaN4 = corr_vclustSizeY_etaN4/vT_truth_etaN4;
       double corr_vAlpha_etaN4_error = corr_vAlpha_etaN4*sqrt((1./corr_vclustSizeY_etaN4));// + (1./vT_truth_etaN4));
     }
     if(i>50 && vT_truth_etaN4==0) {
       double vAlpha_etaN4 = 1.2;
       double corr_vAlpha_etaN4 = 1.2;
     }
     if(i<=50 && vT_truth_etaN4==0) {
       double vAlpha_etaN4 = 0.;
       double corr_vAlpha_etaN4 = 0.;
     }

     if(vT_truth_etaN5!=0) {
       double vAlpha_etaN5 = vclustSizeY_etaN5/(vT_truth_etaN5);
       double corr_vAlpha_etaN5 = corr_vclustSizeY_etaN5/(vT_truth_etaN5);
       double corr_vAlpha_etaN5_error = corr_vAlpha_etaN5*sqrt((1./corr_vclustSizeY_etaN5));// + (1./vT_truth_etaN5));
     }
     if(i>50 && vT_truth_etaN5==0) {
       double vAlpha_etaN5 = 1.2;
       double corr_vAlpha_etaN5 = 1.2;
     }
     if(i<=50 && vT_truth_etaN5==0) {
       double vAlpha_etaN5 = 1.;
       double corr_vAlpha_etaN5 = 1.;
     }  

     if(which == 29) {
        chi_29->SetBinContent(chi_29->FindBin(2.25),corr_vAlpha_etaP5);
        chi_29->SetBinContent(chi_29->FindBin(1.75),corr_vAlpha_etaP4);
        chi_29->SetBinContent(chi_29->FindBin(1.25),corr_vAlpha_etaP3);
        chi_29->SetBinContent(chi_29->FindBin(0.75),corr_vAlpha_etaP2);
        chi_29->SetBinContent(chi_29->FindBin(0.25),corr_vAlpha_etaP1);
        chi_29->SetBinContent(chi_29->FindBin(-0.25),corr_vAlpha_etaN1);
        chi_29->SetBinContent(chi_29->FindBin(-0.75),corr_vAlpha_etaN2);
        chi_29->SetBinContent(chi_29->FindBin(-1.25),corr_vAlpha_etaN3);
        chi_29->SetBinContent(chi_29->FindBin(-1.75),corr_vAlpha_etaN4);
        chi_29->SetBinContent(chi_29->FindBin(-2.25),corr_vAlpha_etaN5);   

        chi_29->SetBinError(chi_29->FindBin(2.25),corr_vAlpha_etaP5_error);
        chi_29->SetBinError(chi_29->FindBin(1.75),corr_vAlpha_etaP4_error);
        chi_29->SetBinError(chi_29->FindBin(1.25),corr_vAlpha_etaP3_error);
        chi_29->SetBinError(chi_29->FindBin(0.75),corr_vAlpha_etaP2_error);
        chi_29->SetBinError(chi_29->FindBin(0.25),corr_vAlpha_etaP1_error);
        chi_29->SetBinError(chi_29->FindBin(-0.25),corr_vAlpha_etaN1_error);
        chi_29->SetBinError(chi_29->FindBin(-0.75),corr_vAlpha_etaN2_error);
        chi_29->SetBinError(chi_29->FindBin(-1.25),corr_vAlpha_etaN3_error);
        chi_29->SetBinError(chi_29->FindBin(-1.75),corr_vAlpha_etaN4_error);
        chi_29->SetBinError(chi_29->FindBin(-2.25),corr_vAlpha_etaN5_error);   
     }
     if(which == 14) {
        chi_14->SetBinContent(chi_14->FindBin(2.25),corr_vAlpha_etaP5);
        chi_14->SetBinContent(chi_14->FindBin(1.75),corr_vAlpha_etaP4);
        chi_14->SetBinContent(chi_14->FindBin(1.25),corr_vAlpha_etaP3);
        chi_14->SetBinContent(chi_14->FindBin(0.75),corr_vAlpha_etaP2);
        chi_14->SetBinContent(chi_14->FindBin(0.25),corr_vAlpha_etaP1);
        chi_14->SetBinContent(chi_14->FindBin(-0.25),corr_vAlpha_etaN1);
        chi_14->SetBinContent(chi_14->FindBin(-0.75),corr_vAlpha_etaN2);
        chi_14->SetBinContent(chi_14->FindBin(-1.25),corr_vAlpha_etaN3);
        chi_14->SetBinContent(chi_14->FindBin(-1.75),corr_vAlpha_etaN4);
        chi_14->SetBinContent(chi_14->FindBin(-2.25),corr_vAlpha_etaN5);   

        chi_14->SetBinError(chi_14->FindBin(2.25),corr_vAlpha_etaP5_error);
        chi_14->SetBinError(chi_14->FindBin(1.75),corr_vAlpha_etaP4_error);
        chi_14->SetBinError(chi_14->FindBin(1.25),corr_vAlpha_etaP3_error);
        chi_14->SetBinError(chi_14->FindBin(0.75),corr_vAlpha_etaP2_error);
        chi_14->SetBinError(chi_14->FindBin(0.25),corr_vAlpha_etaP1_error);
        chi_14->SetBinError(chi_14->FindBin(-0.25),corr_vAlpha_etaN1_error);
        chi_14->SetBinError(chi_14->FindBin(-0.75),corr_vAlpha_etaN2_error);
        chi_14->SetBinError(chi_14->FindBin(-1.25),corr_vAlpha_etaN3_error);
        chi_14->SetBinError(chi_14->FindBin(-1.75),corr_vAlpha_etaN4_error);
        chi_14->SetBinError(chi_14->FindBin(-2.25),corr_vAlpha_etaN5_error);   
     }
     if(which == 11) {
        chi_11->SetBinContent(chi_11->FindBin(2.25),corr_vAlpha_etaP5);
        chi_11->SetBinContent(chi_11->FindBin(1.75),corr_vAlpha_etaP4);
        chi_11->SetBinContent(chi_11->FindBin(1.25),corr_vAlpha_etaP3);
        chi_11->SetBinContent(chi_11->FindBin(0.75),corr_vAlpha_etaP2);
        chi_11->SetBinContent(chi_11->FindBin(0.25),corr_vAlpha_etaP1);
        chi_11->SetBinContent(chi_11->FindBin(-0.25),corr_vAlpha_etaN1);
        chi_11->SetBinContent(chi_11->FindBin(-0.75),corr_vAlpha_etaN2);
        chi_11->SetBinContent(chi_11->FindBin(-1.25),corr_vAlpha_etaN3);
        chi_11->SetBinContent(chi_11->FindBin(-1.75),corr_vAlpha_etaN4);
        chi_11->SetBinContent(chi_11->FindBin(-2.25),corr_vAlpha_etaN5);   

        chi_11->SetBinError(chi_11->FindBin(2.25),corr_vAlpha_etaP5_error);
        chi_11->SetBinError(chi_11->FindBin(1.75),corr_vAlpha_etaP4_error);
        chi_11->SetBinError(chi_11->FindBin(1.25),corr_vAlpha_etaP3_error);
        chi_11->SetBinError(chi_11->FindBin(0.75),corr_vAlpha_etaP2_error);
        chi_11->SetBinError(chi_11->FindBin(0.25),corr_vAlpha_etaP1_error);
        chi_11->SetBinError(chi_11->FindBin(-0.25),corr_vAlpha_etaN1_error);
        chi_11->SetBinError(chi_11->FindBin(-0.75),corr_vAlpha_etaN2_error);
        chi_11->SetBinError(chi_11->FindBin(-1.25),corr_vAlpha_etaN3_error);
        chi_11->SetBinError(chi_11->FindBin(-1.75),corr_vAlpha_etaN4_error);
        chi_11->SetBinError(chi_11->FindBin(-2.25),corr_vAlpha_etaN5_error);   
     }
     if(which == 3) {
        chi_3->SetBinContent(chi_3->FindBin(2.25),corr_vAlpha_etaP5);
        chi_3->SetBinContent(chi_3->FindBin(1.75),corr_vAlpha_etaP4);
        chi_3->SetBinContent(chi_3->FindBin(1.25),corr_vAlpha_etaP3);
        chi_3->SetBinContent(chi_3->FindBin(0.75),corr_vAlpha_etaP2);
        chi_3->SetBinContent(chi_3->FindBin(0.25),corr_vAlpha_etaP1);
        chi_3->SetBinContent(chi_3->FindBin(-0.25),corr_vAlpha_etaN1);
        chi_3->SetBinContent(chi_3->FindBin(-0.75),corr_vAlpha_etaN2);
        chi_3->SetBinContent(chi_3->FindBin(-1.25),corr_vAlpha_etaN3);
        chi_3->SetBinContent(chi_3->FindBin(-1.75),corr_vAlpha_etaN4);
        chi_3->SetBinContent(chi_3->FindBin(-2.25),corr_vAlpha_etaN5);   

        chi_3->SetBinError(chi_3->FindBin(2.25),corr_vAlpha_etaP5_error);
        chi_3->SetBinError(chi_3->FindBin(1.75),corr_vAlpha_etaP4_error);
        chi_3->SetBinError(chi_3->FindBin(1.25),corr_vAlpha_etaP3_error);
        chi_3->SetBinError(chi_3->FindBin(0.75),corr_vAlpha_etaP2_error);
        chi_3->SetBinError(chi_3->FindBin(0.25),corr_vAlpha_etaP1_error);
        chi_3->SetBinError(chi_3->FindBin(-0.25),corr_vAlpha_etaN1_error);
        chi_3->SetBinError(chi_3->FindBin(-0.75),corr_vAlpha_etaN2_error);
        chi_3->SetBinError(chi_3->FindBin(-1.25),corr_vAlpha_etaN3_error);
        chi_3->SetBinError(chi_3->FindBin(-1.75),corr_vAlpha_etaN4_error);
        chi_3->SetBinError(chi_3->FindBin(-2.25),corr_vAlpha_etaN5_error);   
     }
     if(which == 2) {
        chi_2->SetBinContent(chi_2->FindBin(2.25),corr_vAlpha_etaP5);
        chi_2->SetBinContent(chi_2->FindBin(1.75),corr_vAlpha_etaP4);
        chi_2->SetBinContent(chi_2->FindBin(1.25),corr_vAlpha_etaP3);
        chi_2->SetBinContent(chi_2->FindBin(0.75),corr_vAlpha_etaP2);
        chi_2->SetBinContent(chi_2->FindBin(0.25),corr_vAlpha_etaP1);
        chi_2->SetBinContent(chi_2->FindBin(-0.25),corr_vAlpha_etaN1);
        chi_2->SetBinContent(chi_2->FindBin(-0.75),corr_vAlpha_etaN2);
        chi_2->SetBinContent(chi_2->FindBin(-1.25),corr_vAlpha_etaN3);
        chi_2->SetBinContent(chi_2->FindBin(-1.75),corr_vAlpha_etaN4);
        chi_2->SetBinContent(chi_2->FindBin(-2.25),corr_vAlpha_etaN5);   

        chi_2->SetBinError(chi_2->FindBin(2.25),corr_vAlpha_etaP5_error);
        chi_2->SetBinError(chi_2->FindBin(1.75),corr_vAlpha_etaP4_error);
        chi_2->SetBinError(chi_2->FindBin(1.25),corr_vAlpha_etaP3_error);
        chi_2->SetBinError(chi_2->FindBin(0.75),corr_vAlpha_etaP2_error);
        chi_2->SetBinError(chi_2->FindBin(0.25),corr_vAlpha_etaP1_error);
        chi_2->SetBinError(chi_2->FindBin(-0.25),corr_vAlpha_etaN1_error);
        chi_2->SetBinError(chi_2->FindBin(-0.75),corr_vAlpha_etaN2_error);
        chi_2->SetBinError(chi_2->FindBin(-1.25),corr_vAlpha_etaN3_error);
        chi_2->SetBinError(chi_2->FindBin(-1.75),corr_vAlpha_etaN4_error);
        chi_2->SetBinError(chi_2->FindBin(-2.25),corr_vAlpha_etaN5_error);   
     }
     if(which == 1) {
        chi_1->SetBinContent(chi_1->FindBin(2.25),corr_vAlpha_etaP5);
        chi_1->SetBinContent(chi_1->FindBin(1.75),corr_vAlpha_etaP4);
        chi_1->SetBinContent(chi_1->FindBin(1.25),corr_vAlpha_etaP3);
        chi_1->SetBinContent(chi_1->FindBin(0.75),corr_vAlpha_etaP2);
        chi_1->SetBinContent(chi_1->FindBin(0.25),corr_vAlpha_etaP1);
        chi_1->SetBinContent(chi_1->FindBin(-0.25),corr_vAlpha_etaN1);
        chi_1->SetBinContent(chi_1->FindBin(-0.75),corr_vAlpha_etaN2);
        chi_1->SetBinContent(chi_1->FindBin(-1.25),corr_vAlpha_etaN3);
        chi_1->SetBinContent(chi_1->FindBin(-1.75),corr_vAlpha_etaN4);
        chi_1->SetBinContent(chi_1->FindBin(-2.25),corr_vAlpha_etaN5);   

        chi_1->SetBinError(chi_1->FindBin(2.25),corr_vAlpha_etaP5_error);
        chi_1->SetBinError(chi_1->FindBin(1.75),corr_vAlpha_etaP4_error);
        chi_1->SetBinError(chi_1->FindBin(1.25),corr_vAlpha_etaP3_error);
        chi_1->SetBinError(chi_1->FindBin(0.75),corr_vAlpha_etaP2_error);
        chi_1->SetBinError(chi_1->FindBin(0.25),corr_vAlpha_etaP1_error);
        chi_1->SetBinError(chi_1->FindBin(-0.25),corr_vAlpha_etaN1_error);
        chi_1->SetBinError(chi_1->FindBin(-0.75),corr_vAlpha_etaN2_error);
        chi_1->SetBinError(chi_1->FindBin(-1.25),corr_vAlpha_etaN3_error);
        chi_1->SetBinError(chi_1->FindBin(-1.75),corr_vAlpha_etaN4_error);
        chi_1->SetBinError(chi_1->FindBin(-2.25),corr_vAlpha_etaN5_error);   

     }
     which++;
  }

  std::cerr<< std::endl;
  std::cerr<<"plotting results"<<std::endl;

  chi_all->SetBinContent(chi_all->FindBin(2.25),P5Hits/P5Tracks);
  chi_all->SetBinContent(chi_all->FindBin(1.75),P4Hits/P4Tracks);
  chi_all->SetBinContent(chi_all->FindBin(1.25),P3Hits/P3Tracks);
  chi_all->SetBinContent(chi_all->FindBin(0.75),P2Hits/P2Tracks);
  chi_all->SetBinContent(chi_all->FindBin(0.25),P1Hits/P1Tracks);
  chi_all->SetBinContent(chi_all->FindBin(-0.25),N1Hits/N1Tracks);
  chi_all->SetBinContent(chi_all->FindBin(-0.75),N2Hits/N2Tracks);
  chi_all->SetBinContent(chi_all->FindBin(-1.25),N3Hits/N3Tracks);
  chi_all->SetBinContent(chi_all->FindBin(-1.75),N4Hits/N4Tracks);
  chi_all->SetBinContent(chi_all->FindBin(-2.25),N5Hits/N5Tracks);   

  chi_all->SetBinError(chi_all->FindBin(2.25),(P5Hits/P5Tracks)*sqrt((1./P5Hits)));//+(1./P5Tracks)));
  chi_all->SetBinError(chi_all->FindBin(1.75),(P4Hits/P4Tracks)*sqrt((1./P4Hits)));//+(1./P4Tracks)));
  chi_all->SetBinError(chi_all->FindBin(1.25),(P3Hits/P3Tracks)*sqrt((1./P3Hits)));//+(1./P3Tracks)));
  chi_all->SetBinError(chi_all->FindBin(0.75),(P2Hits/P2Tracks)*sqrt((1./P2Hits)));//+(1./P2Tracks)));
  chi_all->SetBinError(chi_all->FindBin(0.25),(P1Hits/P1Tracks)*sqrt((1./P1Hits)));//+(1./P1Tracks)));
  chi_all->SetBinError(chi_all->FindBin(-0.25),(N1Hits/N1Tracks)*sqrt((1./N1Hits)));//+(1./N1Tracks)));
  chi_all->SetBinError(chi_all->FindBin(-0.75),(N2Hits/N2Tracks)*sqrt((1./N2Hits)));//+(1./N2Tracks)));
  chi_all->SetBinError(chi_all->FindBin(-1.25),(N3Hits/N3Tracks)*sqrt((1./N3Hits)));//+(1./N3Tracks)));
  chi_all->SetBinError(chi_all->FindBin(-1.75),(N4Hits/N4Tracks)*sqrt((1./N4Hits)));//+(1./N4Tracks)));
  chi_all->SetBinError(chi_all->FindBin(-2.25),(N5Hits/N5Tracks)*sqrt((1./N5Hits)));//+(1./N5Tracks)));   

  chi_all->GetXaxis()->SetTitle("#eta");
  chi_all->GetYaxis()->SetTitle("#chi");
  chi_1->GetXaxis()->SetTitle("#eta");
  chi_1->GetYaxis()->SetTitle("#chi");

  chi_all->SetMarkerColor(46);
  chi_all->SetMarkerStyle(30);
  chi_all->SetLineColor(46);
  chi_all->SetLineStyle(1);
  chi_all->SetMarkerSize(0.8);
  chi_all->SetTitle(0);
  chi_all->Draw("P");

  chi_1->SetMarkerColor(6);
  chi_1->SetMarkerStyle(34);
  chi_1->SetMarkerSize(0.8);
//  chi_1->Draw("P");

  chi_11->SetMarkerColor(1);
  chi_11->SetLineColor(1);
  chi_11->SetMarkerStyle(20);
  chi_11->SetMarkerSize(0.8);
  chi_11->Draw("Psame");

  chi_14->SetMarkerColor(5);
  chi_14->SetLineColor(5);
  chi_14->SetMarkerStyle(20);
  chi_14->SetMarkerSize(0.8);
  chi_14->Draw("Psame");

  chi_29->SetMarkerColor(29);
  chi_29->SetLineColor(29);
  chi_29->SetMarkerStyle(20);
  chi_29->SetMarkerSize(0.8);
  chi_29->Draw("Psame");

  chi_2->SetMarkerColor(2);
  chi_2->SetMarkerStyle(24);
  chi_2->SetMarkerSize(0.8);
//  chi_2->Draw("Psame");

  chi_3->SetMarkerColor(4);
  chi_3->SetLineColor(4);
  chi_3->SetMarkerStyle(26);
  chi_3->SetMarkerSize(0.8);
  chi_3->Draw("Psame");

  TLatex *l_1 = new TLatex(-1.,1.,"SD_ZeroBias 7 TeV Data");
  l_1->SetTextSize(0.04);
//  l_1->Draw("same");

  TLatex *l_2 = new TLatex(-1.,2.,"CMS Preliminary");
  l_2->SetTextSize(0.04);
//  l_2->Draw("same");

  TLatex *l_3 = new TLatex(-1.,3.,"10 TeV corrections");
  l_3->SetTextSize(0.04);
//  l_3->Draw("same");

  // legend
  TLegend *leg6 = new TLegend(0.25,0.35,0.75,0.65,NULL,"brNDC");
  leg6->AddEntry(chi_all,"all mult.","P");
  leg6->AddEntry(chi_3,"mult. bin: 3","P");
  leg6->AddEntry(chi_11,"mult. bin: 11","P");
  leg6->AddEntry(chi_14,"mult. bin: 14","P");
  leg6->AddEntry(chi_29,"mult. bin: 29","P");

  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
  leg6->Draw();

  MyCanvas.SaveAs("HI_Chi_layer1_plot.C");
}

