////////////////////////////
//
// ALWAYS CHECK MULTIPLICITY
//
////////////////////////////

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

  //histograms
  TH1D* hMult_sim = new TH1D("hMult_sim","hMult_sim",15000,-0.5,14999.5);
  ntuple1_sim->Project("hMult_sim","cluster_counter");
  double nonzeromultiplicity_sim = hMult_sim->GetEntries() - hMult_sim->GetBinContent(hMult_sim->FindBin(0.));
  double multiplicityRatio_sim = hMult_sim->GetBinContent(hMult_sim->FindBin(0.))/nonzeromultiplicity_sim;

  std::cerr<<"multiplicityRatio_sim: " << multiplicityRatio_sim << std::endl;

  TH1D* hMult = new TH1D("hMult","hMult",15000,-0.5,14999.5);
  ntuple1->Project("hMult","cluster_counter");
  double nonzeromultiplicity = hMult->GetEntries() - hMult->GetBinContent(hMult->FindBin(0.));
  double multiplicityRatio = hMult->GetBinContent(hMult->FindBin(0.))/nonzeromultiplicity;

  //define multiplicity bins
  int num_mult_bins = 31;
  vector<int> mult_bins;
  int mult_bin_lemma = 0;
  for(int ii = 0; ii<num_mult_bins; ii++) {
//     std::cerr<<" mult_bin_lemma: " << mult_bin_lemma << std::endl;
     mult_bins.push_back(mult_bin_lemma);
     if(ii<10)
        mult_bin_lemma += 50;
     else if(ii<29)
        mult_bin_lemma += 500;
     else
        mult_bin_lemma += 5000;
  }

  TH1D* hEpsilon = new TH1D("hEpsilon","hEpsilon",15000,-0.5,14999.5);

  TH1D* hNumEv = new TH1D("hNumEv","hNumEv",2,-0.5,1.5);
  TH1D* hTrigger = new TH1D("hTrigger","hTrigger",2,-0.5,1.5);
  TH1D* hTrigger_data = new TH1D("hTrigger_data","hTrigger_data",2,-0.5,1.5);

  TH1D* hclustSizeY_etaP5 = new TH1D("hclustSizeY_etaP5","hclustSizeY_etaP5",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaP4 = new TH1D("hclustSizeY_etaP4","hclustSizeY_etaP4",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaP3 = new TH1D("hclustSizeY_etaP3","hclustSizeY_etaP3",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaP2 = new TH1D("hclustSizeY_etaP2","hclustSizeY_etaP2",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaP1 = new TH1D("hclustSizeY_etaP1","hclustSizeY_etaP1",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN1 = new TH1D("hclustSizeY_etaN1","hclustSizeY_etaN1",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN2 = new TH1D("hclustSizeY_etaN2","hclustSizeY_etaN2",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN3 = new TH1D("hclustSizeY_etaN3","hclustSizeY_etaN3",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN4 = new TH1D("hclustSizeY_etaN4","hclustSizeY_etaN4",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN5 = new TH1D("hclustSizeY_etaN5","hclustSizeY_etaN5",15000,-0.5,14999.5);

  TH1D* hclustSizeY_etaP5_DATA = new TH1D("hclustSizeY_etaP5_DATA","hclustSizeY_etaP5_DATA",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaP4_DATA = new TH1D("hclustSizeY_etaP4_DATA","hclustSizeY_etaP4_DATA",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaP3_DATA = new TH1D("hclustSizeY_etaP3_DATA","hclustSizeY_etaP3_DATA",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaP2_DATA = new TH1D("hclustSizeY_etaP2_DATA","hclustSizeY_etaP2_DATA",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaP1_DATA = new TH1D("hclustSizeY_etaP1_DATA","hclustSizeY_etaP1_DATA",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN1_DATA = new TH1D("hclustSizeY_etaN1_DATA","hclustSizeY_etaN1_DATA",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN2_DATA = new TH1D("hclustSizeY_etaN2_DATA","hclustSizeY_etaN2_DATA",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN3_DATA = new TH1D("hclustSizeY_etaN3_DATA","hclustSizeY_etaN3_DATA",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN4_DATA = new TH1D("hclustSizeY_etaN4_DATA","hclustSizeY_etaN4_DATA",15000,-0.5,14999.5);
  TH1D* hclustSizeY_etaN5_DATA = new TH1D("hclustSizeY_etaN5_DATA","hclustSizeY_etaN5_DATA",15000,-0.5,14999.5);

  TH1D* hT_truth_etaP5 = new TH1D("hT_truth_etaP5","hT_truth_etaP5",15000,-0.5,14999.5);
  TH1D* hT_truth_etaP4 = new TH1D("hT_truth_etaP4","hT_truth_etaP4",15000,-0.5,14999.5);
  TH1D* hT_truth_etaP3 = new TH1D("hT_truth_etaP3","hT_truth_etaP3",15000,-0.5,14999.5);
  TH1D* hT_truth_etaP2 = new TH1D("hT_truth_etaP2","hT_truth_etaP2",15000,-0.5,14999.5);
  TH1D* hT_truth_etaP1 = new TH1D("hT_truth_etaP1","hT_truth_etaP1",15000,-0.5,14999.5);
  TH1D* hT_truth_etaN1 = new TH1D("hT_truth_etaN1","hT_truth_etaN1",15000,-0.5,14999.5);
  TH1D* hT_truth_etaN2 = new TH1D("hT_truth_etaN2","hT_truth_etaN2",15000,-0.5,14999.5);
  TH1D* hT_truth_etaN3 = new TH1D("hT_truth_etaN3","hT_truth_etaN3",15000,-0.5,14999.5);
  TH1D* hT_truth_etaN4 = new TH1D("hT_truth_etaN4","hT_truth_etaN4",15000,-0.5,14999.5);
  TH1D* hT_truth_etaN5 = new TH1D("hT_truth_etaN5","hT_truth_etaN5",15000,-0.5,14999.5);

  ////////////////////////
  //
  //loopers -first part- 
  //
  ////////////////////////

  TH1D* hAllP5 = new TH1D("hAllP5","hAllP5",100,-0.5,999.5);
  TH1D* hAllP5_DATA = new TH1D("hAllP5_DATA","hAllP5_DATA",100,-0.5,999.5);
  TH1D* hLorLP5 = new TH1D("hLorLP5","hLorLP5",100,-0.5,999.5);

  TH1D* hAllP4 = new TH1D("hAllP4","hAllP4",100,-0.5,999.5);
  TH1D* hAllP4_DATA = new TH1D("hAllP4_DATA","hAllP4_DATA",100,-0.5,999.5);  
  TH1D* hLorLP4 = new TH1D("hLorLP4","hLorLP4",100,-0.5,999.5);

  TH1D* hAllP3 = new TH1D("hAllP3","hAllP3",100,-0.5,999.5);
  TH1D* hAllP3_DATA = new TH1D("hAllP3_DATA","hAllP3_DATA",100,-0.5,999.5);  
  TH1D* hLorLP3 = new TH1D("hLorLP3","hLorLP3",100,-0.5,999.5);

  TH1D* hAllP2 = new TH1D("hAllP2","hAllP2",100,-0.5,999.5);
  TH1D* hAllP2_DATA = new TH1D("hAllP2_DATA","hAllP2_DATA",100,-0.5,999.5);  
  TH1D* hLorLP2 = new TH1D("hLorLP2","hLorLP2",100,-0.5,999.5);

  TH1D* hAllP1 = new TH1D("hAllP1","hAllP1",100,-0.5,999.5);
  TH1D* hAllP1_DATA = new TH1D("hAllP1_DATA","hAllP1_DATA",100,-0.5,999.5);  
  TH1D* hLorLP1 = new TH1D("hLorLP1","hLorLP1",100,-0.5,999.5);

  TH1D* hAllN1 = new TH1D("hAllN1","hAllN1",100,-0.5,999.5);
  TH1D* hAllN1_DATA = new TH1D("hAllN1_DATA","hAllN1_DATA",100,-0.5,999.5);  
  TH1D* hLorLN1 = new TH1D("hLorLN1","hLorLN1",100,-0.5,999.5);

  TH1D* hAllN2 = new TH1D("hAllN2","hAllN2",100,-0.5,999.5);
  TH1D* hAllN2_DATA = new TH1D("hAllN2_DATA","hAllN2_DATA",100,-0.5,999.5);  
  TH1D* hLorLN2 = new TH1D("hLorLN2","hLorLN2",100,-0.5,999.5);

  TH1D* hAllN3 = new TH1D("hAllN3","hAllN3",100,-0.5,999.5);
  TH1D* hAllN3_DATA = new TH1D("hAllN3_DATA","hAllN3_DATA",100,-0.5,999.5);  
  TH1D* hLorLN3 = new TH1D("hLorLN3","hLorLN3",100,-0.5,999.5);

  TH1D* hAllN4 = new TH1D("hAllN4","hAllN4",100,-0.5,999.5);
  TH1D* hAllN4_DATA = new TH1D("hAllN4_DATA","hAllN4_DATA",100,-0.5,999.5);  
  TH1D* hLorLN4 = new TH1D("hLorLN4","hLorLN4",100,-0.5,999.5);

  TH1D* hAllN5 = new TH1D("hAllN5","hAllN5",100,-0.5,999.5);
  TH1D* hAllN5_DATA = new TH1D("hAllN5_DATA","hAllN5_DATA",100,-0.5,999.5);  
  TH1D* hLorLN5 = new TH1D("hLorLN5","hLorLN5",100,-0.5,999.5);

  char felt_P5[200], felt_P5lemma1[200];
  char felt_P4[200], felt_P4lemma1[200];
  char felt_P3[200], felt_P3lemma1[200];
  char felt_P2[200], felt_P2lemma1[200];
  char felt_P1[200], felt_P1lemma1[200];
  char felt_N1[200], felt_N1lemma1[200];
  char felt_N2[200], felt_N2lemma1[200];
  char felt_N3[200], felt_N3lemma1[200];
  char felt_N4[200], felt_N4lemma1[200];
  char felt_N5[200], felt_N5lemma1[200];

  float correct1_etaP5[15000];
  float correct1_etaP4[15000];
  float correct1_etaP3[15000];
  float correct1_etaP2[15000];
  float correct1_etaP1[15000];
  float correct1_etaN1[15000];
  float correct1_etaN2[15000];
  float correct1_etaN3[15000];
  float correct1_etaN4[15000];
  float correct1_etaN5[15000];

  std::cerr<<" loopers: first part" << std::endl;
  //computation: above the cut (looper)/below the cut (all) ratio
  for(int i = 0; i < num_mult_bins-1; i++) {   //-1 because [i+1]
     std::cerr<< "   "<< i;

     hAllP5->Reset();
     hLorLP5->Reset();
     hAllP4->Reset();
     hLorLP4->Reset();
     hAllP3->Reset();
     hLorLP3->Reset();
     hAllP2->Reset();
     hLorLP2->Reset();
     hAllP1->Reset();
     hLorLP1->Reset();
     hAllN1->Reset();
     hLorLN1->Reset();
     hAllN2->Reset();
     hLorLN2->Reset();
     hAllN3->Reset();
     hLorLN3->Reset();
     hAllN4->Reset();
     hLorLN4->Reset();
     hAllN5->Reset();
     hLorLN5->Reset();

     //event selection not imposed (only a ratio os computed; nevertheless, might have some small effect)

     sprintf(felt_P5,"eta<2.5 && eta>2.0 && clustSizeY<5.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P5lemma1,"eta<2.5 && eta>2.0 && clustSizeY>5.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P4,"eta<=2.0 && eta>1.5 && clustSizeY<3.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P4lemma1,"eta<=2.0 && eta>1.5 && clustSizeY>3.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P3,"eta<=1.5 && eta>1.0 && clustSizeY<2.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P3lemma1,"eta<=1.5 && eta>1.0 && clustSizeY>2.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P2,"eta<=1.0 && eta>0.5 && clustSizeY<1.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P2lemma1,"eta<=1.0 && eta>0.5 && clustSizeY>1.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P1,"eta<=0.5 && eta>0.0 && clustSizeY<0.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);  
     sprintf(felt_P1lemma1,"eta<=0.5 && eta>0.0 && clustSizeY>0.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N1,"eta<=0.0 && eta>-0.5 && clustSizeY<0.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]); 
     sprintf(felt_N1lemma1,"eta<=0.0 && eta>-0.5 && clustSizeY>0.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N2,"eta<=-0.5 && eta>-1.0 && clustSizeY<1.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N2lemma1,"eta<=-0.5 && eta>-1.0 && clustSizeY>1.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N3,"eta<=-1.0 && eta>-1.5 && clustSizeY<2.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N3lemma1,"eta<=-1.0 && eta>-1.5 && clustSizeY>2.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N4,"eta<=-1.5 && eta>-2.0 && clustSizeY<3.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N4lemma1,"eta<=-1.5 && eta>-2.0 && clustSizeY>3.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N5,"eta<=-2.0 && eta>-2.5 && clustSizeY<5.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N5lemma1,"eta<=-2.0 && eta>-2.5 && clustSizeY>5.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);

     //ntuple3: only loopers
     //ntuple2: all
     //felt_XY: below the cut
     //felt_XYlemma1: above the cut

     //aim: loopers above / all below

     ntuple3_sim->Project("hLorLP5","clustSizeY",felt_P5lemma1);
     ntuple2_sim->Project("hAllP5","clustSizeY",felt_P5);

     ntuple3_sim->Project("hLorLP4","clustSizeY",felt_P4lemma1);
     ntuple2_sim->Project("hAllP4","clustSizeY",felt_P4);

     ntuple3_sim->Project("hLorLP3","clustSizeY",felt_P3lemma1);
     ntuple2_sim->Project("hAllP3","clustSizeY",felt_P3);

     ntuple3_sim->Project("hLorLP2","clustSizeY",felt_P2lemma1);
     ntuple2_sim->Project("hAllP2","clustSizeY",felt_P2);

     ntuple3_sim->Project("hLorLP1","clustSizeY",felt_P1lemma1);
     ntuple2_sim->Project("hAllP1","clustSizeY",felt_P1);

     ntuple3_sim->Project("hLorLN1","clustSizeY",felt_N1lemma1);
     ntuple2_sim->Project("hAllN1","clustSizeY",felt_N1);

     ntuple3_sim->Project("hLorLN2","clustSizeY",felt_N2lemma1);
     ntuple2_sim->Project("hAllN2","clustSizeY",felt_N2);

     ntuple3_sim->Project("hLorLN3","clustSizeY",felt_N3lemma1);
     ntuple2_sim->Project("hAllN3","clustSizeY",felt_N3);

     ntuple3_sim->Project("hLorLN4","clustSizeY",felt_N4lemma1);
     ntuple2_sim->Project("hAllN4","clustSizeY",felt_N4);

     ntuple3_sim->Project("hLorLN5","clustSizeY",felt_N5lemma1);
     ntuple2_sim->Project("hAllN5","clustSizeY",felt_N5);

     // Do I need entries below? Or integral?
     if((hAllP5->GetEntries())==0)
       correct1_etaP5[i] = 0;
     else
       correct1_etaP5[i] = hLorLP5->GetEntries()/hAllP5->GetEntries();

     if((hAllP4->GetEntries())==0)
       correct1_etaP4[i] = 0;
     else
       correct1_etaP4[i] = hLorLP4->GetEntries()/hAllP4->GetEntries();

     if((hAllP3->GetEntries())==0)
       correct1_etaP3[i] = 0;
     else
       correct1_etaP3[i] = hLorLP3->GetEntries()/hAllP3->GetEntries();

     if((hAllP2->GetEntries())==0)
       correct1_etaP2[i] = 0;
     else
       correct1_etaP2[i] = hLorLP2->GetEntries()/hAllP2->GetEntries();

     if((hAllP1->GetEntries())==0)
       correct1_etaP1[i] = 0;
     else
       correct1_etaP1[i] = hLorLP1->GetEntries()/hAllP1->GetEntries();

     if((hAllN1->GetEntries())==0)
       correct1_etaN1[i] = 0;
     else
       correct1_etaN1[i] = hLorLN1->GetEntries()/hAllN1->GetEntries();

     if((hAllN2->GetEntries())==0)
       correct1_etaN2[i] = 0;
     else
       correct1_etaN2[i] = hLorLN2->GetEntries()/hAllN2->GetEntries();

     if((hAllN3->GetEntries())==0)
       correct1_etaN3[i] = 0;
     else
       correct1_etaN3[i] = hLorLN3->GetEntries()/hAllN3->GetEntries();

     if((hAllN4->GetEntries())==0)
       correct1_etaN4[i] = 0;
     else
       correct1_etaN4[i] = hLorLN4->GetEntries()/hAllN4->GetEntries();

     if((hAllN5->GetEntries())==0)
       correct1_etaN5[i] = 0;
     else
       correct1_etaN5[i] = hLorLN5->GetEntries()/hAllN5->GetEntries();
  }

  ////////////////////////
  //
  //loopers -second part- 
  //
  ////////////////////////

  TH1D* hFailedSize_P5 = new TH1D("hFailedSize_P5","hFailedSize_P5",1000,-0.5,999.5);
  TH1D* hFailedSize_P4 = new TH1D("hFailedSize_P4","hFailedSize_P4",1000,-0.5,999.5);
  TH1D* hFailedSize_P3 = new TH1D("hFailedSize_P3","hFailedSize_P3",1000,-0.5,999.5);
  TH1D* hFailedSize_P2 = new TH1D("hFailedSize_P2","hFailedSize_P2",1000,-0.5,999.5);
  TH1D* hFailedSize_P1 = new TH1D("hFailedSize_P1","hFailedSize_P1",1000,-0.5,999.5);
  TH1D* hFailedSize_N1 = new TH1D("hFailedSize_N1","hFailedSize_N1",1000,-0.5,999.5);
  TH1D* hFailedSize_N2 = new TH1D("hFailedSize_N2","hFailedSize_N2",1000,-0.5,999.5);
  TH1D* hFailedSize_N3 = new TH1D("hFailedSize_N3","hFailedSize_N3",1000,-0.5,999.5);
  TH1D* hFailedSize_N4 = new TH1D("hFailedSize_N4","hFailedSize_N4",1000,-0.5,999.5);
  TH1D* hFailedSize_N5 = new TH1D("hFailedSize_N5","hFailedSize_N5",1000,-0.5,999.5);

  TH1D* hFailedSize_P5_DATA = new TH1D("hFailedSize_P5_DATA","hFailedSize_P5_DATA",1000,-0.5,999.5);
  TH1D* hFailedSize_P4_DATA = new TH1D("hFailedSize_P4_DATA","hFailedSize_P4_DATA",1000,-0.5,999.5);
  TH1D* hFailedSize_P3_DATA = new TH1D("hFailedSize_P3_DATA","hFailedSize_P3_DATA",1000,-0.5,999.5);
  TH1D* hFailedSize_P2_DATA = new TH1D("hFailedSize_P2_DATA","hFailedSize_P2_DATA",1000,-0.5,999.5);
  TH1D* hFailedSize_P1_DATA = new TH1D("hFailedSize_P1_DATA","hFailedSize_P1_DATA",1000,-0.5,999.5);
  TH1D* hFailedSize_N1_DATA = new TH1D("hFailedSize_N1_DATA","hFailedSize_N1_DATA",1000,-0.5,999.5);
  TH1D* hFailedSize_N2_DATA = new TH1D("hFailedSize_N2_DATA","hFailedSize_N2_DATA",1000,-0.5,999.5);
  TH1D* hFailedSize_N3_DATA = new TH1D("hFailedSize_N3_DATA","hFailedSize_N3_DATA",1000,-0.5,999.5);
  TH1D* hFailedSize_N4_DATA = new TH1D("hFailedSize_N4_DATA","hFailedSize_N4_DATA",1000,-0.5,999.5);
  TH1D* hFailedSize_N5_DATA = new TH1D("hFailedSize_N5_DATA","hFailedSize_N5_DATA",1000,-0.5,999.5);

  float failed_etaP5[15000], failed_etaP4[15000], failed_etaP3[15000], failed_etaP2[15000], failed_etaP1[15000];
  float failed_etaN5[15000], failed_etaN4[15000], failed_etaN3[15000], failed_etaN2[15000], failed_etaN1[15000];

  float failed_etaP5_DATA[15000], failed_etaP4_DATA[15000], failed_etaP3_DATA[15000], failed_etaP2_DATA[15000], failed_etaP1_DATA[15000];
  float failed_etaN5_DATA[15000], failed_etaN4_DATA[15000], failed_etaN3_DATA[15000], failed_etaN2_DATA[15000], failed_etaN1_DATA[15000];

  char felt_P5lemma2[200], felt_P4lemma2[200], felt_P3lemma2[200], felt_P2lemma2[200], felt_P1lemma2[200];
  char felt_N5lemma2[200], felt_N4lemma2[200], felt_N3lemma2[200], felt_N2lemma2[200], felt_N1lemma2[200];

  std::cerr << std::endl;
  std::cerr<<" loopers: second part" << std::endl;
  //aim: number of clusters are to be removed are computed
  for(int i = 0; i < num_mult_bins-1; i++) {   //-1 because [i+1]
     std::cerr<< "   "<< i;

     hFailedSize_P5->Reset();
     hFailedSize_P4->Reset();
     hFailedSize_P3->Reset();
     hFailedSize_P2->Reset();
     hFailedSize_P1->Reset();
     hFailedSize_N1->Reset();
     hFailedSize_N2->Reset();
     hFailedSize_N3->Reset();
     hFailedSize_N4->Reset();
     hFailedSize_N5->Reset();

     hFailedSize_P5_DATA->Reset();
     hFailedSize_P4_DATA->Reset();
     hFailedSize_P3_DATA->Reset();
     hFailedSize_P2_DATA->Reset();
     hFailedSize_P1_DATA->Reset();
     hFailedSize_N1_DATA->Reset();
     hFailedSize_N2_DATA->Reset();
     hFailedSize_N3_DATA->Reset();
     hFailedSize_N4_DATA->Reset();
     hFailedSize_N5_DATA->Reset();

     sprintf(felt_P5lemma2,"eta<2.5 && eta>2.0 && clustSizeY<5.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P4lemma2,"eta<=2.0 && eta>1.5 && clustSizeY<3.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P3lemma2,"eta<=1.5 && eta>1.0 && clustSizeY>2.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P2lemma2,"eta<=1.0 && eta>0.5 && clustSizeY<1.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_P1lemma2,"eta<=0.5 && eta>0.0 && clustSizeY<0.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N1lemma2,"eta<=0.0 && eta>-0.5 && clustSizeY<0.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N2lemma2,"eta<=-0.5 && eta>-1.0 && clustSizeY<1.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N3lemma2,"eta<=-1.0 && eta>-1.5 && clustSizeY<2.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N4lemma2,"eta<=-1.5 && eta>-2.0 && clustSizeY<3.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);
     sprintf(felt_N5lemma2,"eta<=-2.0 && eta>-2.5 && clustSizeY<5.5 && cluster_counter>=%i && cluster_counter<%i",mult_bins[i],mult_bins[i+1]);

     //felt_XYlemma2: below the cut
     ntuple2_sim->Project("hFailedSize_P5","clustSizeY",felt_P5lemma2);
     ntuple2_sim->Project("hFailedSize_P4","clustSizeY",felt_P4lemma2);
     ntuple2_sim->Project("hFailedSize_P3","clustSizeY",felt_P3lemma2);
     ntuple2_sim->Project("hFailedSize_P2","clustSizeY",felt_P2lemma2);
     ntuple2_sim->Project("hFailedSize_P1","clustSizeY",felt_P1lemma2);
     ntuple2_sim->Project("hFailedSize_N1","clustSizeY",felt_N1lemma2);
     ntuple2_sim->Project("hFailedSize_N2","clustSizeY",felt_N2lemma2);
     ntuple2_sim->Project("hFailedSize_N3","clustSizeY",felt_N3lemma2);
     ntuple2_sim->Project("hFailedSize_N4","clustSizeY",felt_N4lemma2);
     ntuple2_sim->Project("hFailedSize_N5","clustSizeY",felt_N5lemma2);

     ntuple2->Project("hFailedSize_P5_DATA","clustSizeY",felt_P5lemma2);
     ntuple2->Project("hFailedSize_P4_DATA","clustSizeY",felt_P4lemma2);
     ntuple2->Project("hFailedSize_P3_DATA","clustSizeY",felt_P3lemma2);
     ntuple2->Project("hFailedSize_P2_DATA","clustSizeY",felt_P2lemma2);
     ntuple2->Project("hFailedSize_P1_DATA","clustSizeY",felt_P1lemma2);
     ntuple2->Project("hFailedSize_N1_DATA","clustSizeY",felt_N1lemma2);
     ntuple2->Project("hFailedSize_N2_DATA","clustSizeY",felt_N2lemma2);
     ntuple2->Project("hFailedSize_N3_DATA","clustSizeY",felt_N3lemma2);
     ntuple2->Project("hFailedSize_N4_DATA","clustSizeY",felt_N4lemma2);
     ntuple2->Project("hFailedSize_N5_DATA","clustSizeY",felt_N5lemma2);

     failed_etaP5[i] = hFailedSize_P5->GetMean(1);
     failed_etaP4[i] = hFailedSize_P4->GetMean(1);
     failed_etaP3[i] = hFailedSize_P3->GetMean(1);
     failed_etaP2[i] = hFailedSize_P2->GetMean(1);
     failed_etaP1[i] = hFailedSize_P1->GetMean(1);
     failed_etaN1[i] = hFailedSize_N1->GetMean(1);
     failed_etaN2[i] = hFailedSize_N2->GetMean(1);
     failed_etaN3[i] = hFailedSize_N3->GetMean(1);
     failed_etaN4[i] = hFailedSize_N4->GetMean(1);
     failed_etaN5[i] = hFailedSize_N5->GetMean(1);

     failed_etaP5_DATA[i] = hFailedSize_P5_DATA->GetMean(1);
     failed_etaP4_DATA[i] = hFailedSize_P4_DATA->GetMean(1);
     failed_etaP3_DATA[i] = hFailedSize_P3_DATA->GetMean(1);
     failed_etaP2_DATA[i] = hFailedSize_P2_DATA->GetMean(1);
     failed_etaP1_DATA[i] = hFailedSize_P1_DATA->GetMean(1);
     failed_etaN1_DATA[i] = hFailedSize_N1_DATA->GetMean(1);
     failed_etaN2_DATA[i] = hFailedSize_N2_DATA->GetMean(1);
     failed_etaN3_DATA[i] = hFailedSize_N3_DATA->GetMean(1);
     failed_etaN4_DATA[i] = hFailedSize_N4_DATA->GetMean(1);
     failed_etaN5_DATA[i] = hFailedSize_N5_DATA->GetMean(1);
  }

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
  float correct1_etaP5_DATA[15000];
  float correct1_etaP4_DATA[15000];
  float correct1_etaP3_DATA[15000];
  float correct1_etaP2_DATA[15000];
  float correct1_etaP1_DATA[15000];
  float correct1_etaN1_DATA[15000];
  float correct1_etaN2_DATA[15000];
  float correct1_etaN3_DATA[15000];
  float correct1_etaN4_DATA[15000];
  float correct1_etaN5_DATA[15000];

  ////////////////////////
  //
  // Summation
  //
  ////////////////////////

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
/*
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
*/
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

     //computing alphas
     if(vT_truth_etaP5!=0 && vclustSizeY_etaP5!=0) {
       double vAlpha_etaP5 = vclustSizeY_etaP5/(vT_truth_etaP5);
       double corr_vAlpha_etaP5 = corr_vclustSizeY_etaP5/(vT_truth_etaP5);
//       std::cerr<<"corr_vAlpha_etaP5: "<<corr_vAlpha_etaP5<<endl;;
     }
     if(i>50 && (vT_truth_etaP5==0 || vclustSizeY_etaP5==0)) {
       double vAlpha_etaP5 = 1.2;
       double corr_vAlpha_etaP5 = 1.2;
     }
     if(i<=50 && (vT_truth_etaP5==0 || vclustSizeY_etaP5==0)) {
       double vAlpha_etaP5 = 1.;
       double corr_vAlpha_etaP5 = 1.;
     }

//     corr_vAlpha_etaP5 = 1.2;

     if(vT_truth_etaP4!=0 && vclustSizeY_etaP4!=0) {
       double vAlpha_etaP4 = vclustSizeY_etaP4/vT_truth_etaP4;
       double corr_vAlpha_etaP4 = corr_vclustSizeY_etaP4/vT_truth_etaP4;
     }
     if(i>50 && (vT_truth_etaP4==0 || vclustSizeY_etaP4==0)) {
       double vAlpha_etaP4 = 1.2;
       double corr_vAlpha_etaP4 = 1.2;
     }
     if(i<=50 && (vT_truth_etaP4==0 || vclustSizeY_etaP4==0)) {
       double vAlpha_etaP4 = 1.;
       double corr_vAlpha_etaP4 = 1.;
     }

//     corr_vAlpha_etaP4 = 1.2;

     if(vT_truth_etaP3!=0) {
       double vAlpha_etaP3 = vclustSizeY_etaP3/vT_truth_etaP3;
       double corr_vAlpha_etaP3 = corr_vclustSizeY_etaP3/vT_truth_etaP3;
     }
     if(i>50 && vT_truth_etaP3==0) {
       double vAlpha_etaP3 = 1.2;
       double corr_vAlpha_etaP3 = 1.2;
     }
     if(i<=50 && vT_truth_etaP3==0) {
       double vAlpha_etaP3 = 0.;
       double corr_vAlpha_etaP3 = 0.;
     }

//     corr_vAlpha_etaP3 = 1.2;

     if(vT_truth_etaP2!=0) {
       double vAlpha_etaP2 = vclustSizeY_etaP2/vT_truth_etaP2;
       double corr_vAlpha_etaP2 = corr_vclustSizeY_etaP2/vT_truth_etaP2;
     } 
     if(i>50 && vT_truth_etaP2==0) {
       double vAlpha_etaP2 = 1.2;
       double corr_vAlpha_etaP2 = 1.2;
     }
     if(i<=50 && vT_truth_etaP2==0) {
       double vAlpha_etaP2 = 0.;
       double corr_vAlpha_etaP2 = 0.;
     }

//     corr_vAlpha_etaP2 = 1.2;

     if(vT_truth_etaP1!=0) {
       double vAlpha_etaP1 = vclustSizeY_etaP1/vT_truth_etaP1;
       double corr_vAlpha_etaP1 = corr_vclustSizeY_etaP1/vT_truth_etaP1;
     }
     if(i>50 && vT_truth_etaP1==0) {
       double vAlpha_etaP1 = 1.2;
       double corr_vAlpha_etaP1 = 1.2; 
     }
     if(i<=50 && vT_truth_etaP1==0) {
       double vAlpha_etaP1 = 0;
       double corr_vAlpha_etaP1 = 0;
     }

//     corr_vAlpha_etaP1 = 1.2;

     if(vT_truth_etaN1!=0) {
       double vAlpha_etaN1 = vclustSizeY_etaN1/vT_truth_etaN1;
       double corr_vAlpha_etaN1 = corr_vclustSizeY_etaN1/vT_truth_etaN1;
     }
     if(i>50 && vT_truth_etaN1==0) {
       double vAlpha_etaN1 = 1.2;
       double corr_vAlpha_etaN1 = 1.2;
     }
     if(i<=50 && vT_truth_etaN1==0) {
       double vAlpha_etaN1 = 0.;
       double corr_vAlpha_etaN1 = 0.;
     }    

//     corr_vAlpha_etaN1 = 1.2;

     if(vT_truth_etaN2!=0) {
       double vAlpha_etaN2 = vclustSizeY_etaN2/vT_truth_etaN2;
       double corr_vAlpha_etaN2 = corr_vclustSizeY_etaN2/vT_truth_etaN2;
     }
     if(i>50 && vT_truth_etaN2==0) {
       double vAlpha_etaN2 = 1.2;
       double corr_vAlpha_etaN2 = 1.2;
     }
     if(i<=50 && vT_truth_etaN2==0) {
       double vAlpha_etaN2 = 0.;
       double corr_vAlpha_etaN2 = 0.;
     }

//     corr_vAlpha_etaN2 = 1.2;

     if(vT_truth_etaN3!=0) {
       double vAlpha_etaN3 = vclustSizeY_etaN3/vT_truth_etaN3;
       double corr_vAlpha_etaN3 = corr_vclustSizeY_etaN3/vT_truth_etaN3;
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
     }
     if(i>50 && vT_truth_etaN4==0) {
       double vAlpha_etaN4 = 1.2;
       double corr_vAlpha_etaN4 = 1.2;
     }
     if(i<=50 && vT_truth_etaN4==0) {
       double vAlpha_etaN4 = 0.;
       double corr_vAlpha_etaN4 = 0.;
     }

//     corr_vAlpha_etaN4 = 1.2;

     if(vT_truth_etaN5!=0) {
       double vAlpha_etaN5 = vclustSizeY_etaN5/(vT_truth_etaN5);
       double corr_vAlpha_etaN5 = corr_vclustSizeY_etaN5/(vT_truth_etaN5);
     }
     if(i>50 && vT_truth_etaN5==0) {
       double vAlpha_etaN5 = 1.2;
       double corr_vAlpha_etaN5 = 1.2;
     }
     if(i<=50 && vT_truth_etaN5==0) {
       double vAlpha_etaN5 = 1.;
       double corr_vAlpha_etaN5 = 1.;
     }  

//     corr_vAlpha_etaN5 = 1.2;

     double epsilon;
     if(numEv>0) {
       epsilon = trackTrigger/numEv;
     }
     if(numEv==0 && i <=50)
       continue;
     //Tricky epsilon
     if(trackTrigger==0 || numEv==0)
       epsilon = 1.;

     hEpsilon->SetBinContent(hEpsilon->FindBin(i),epsilon);

     //looper corrected dNdeta
     if(corr_vAlpha_etaP5==0)
       double corr_vN_etaP5 = 0;
     else 
       double corr_vN_etaP5 = (1./corr_vAlpha_etaP5)*(corr_vclustSizeY_etaP5_DATA/1.);  //mean of trackTrigger is 1.

     if(corr_vAlpha_etaP4==0)
       double corr_vN_etaP4 = 0;
     else
       double corr_vN_etaP4 = (1./corr_vAlpha_etaP4)*(corr_vclustSizeY_etaP4_DATA/1.);  //mean of trackTrigger is 1.

     if(corr_vAlpha_etaP3==0)
       double corr_vN_etaP3 = 0;
     else
       double corr_vN_etaP3 = (1./corr_vAlpha_etaP3)*(corr_vclustSizeY_etaP3_DATA/1.);  //mean of trackTrigger is 1.

     if(corr_vAlpha_etaP2==0)
       double corr_vN_etaP2 = 0;
     else
       double corr_vN_etaP2 = (1./corr_vAlpha_etaP2)*(corr_vclustSizeY_etaP2_DATA/1.);  //mean of trackTrigger is 1.

     if(corr_vAlpha_etaP1==0)
       double corr_vN_etaP1 = 0;
     else
       double corr_vN_etaP1 = (1./corr_vAlpha_etaP1)*(corr_vclustSizeY_etaP1_DATA/1.);  //mean of trackTrigger is 1.

     if(corr_vAlpha_etaN1==0)
       double corr_vN_etaN1 = 0;
     else
       double corr_vN_etaN1 = (1./corr_vAlpha_etaN1)*(corr_vclustSizeY_etaN1_DATA/1.);  //mean of trackTrigger is 1.

     if(corr_vAlpha_etaN2==0)
       double corr_vN_etaN2 = 0;
     else
       double corr_vN_etaN2 = (1./corr_vAlpha_etaN2)*(corr_vclustSizeY_etaN2_DATA/1.);  //mean of trackTrigger is 1.

     if(corr_vAlpha_etaN3==0)
       double corr_vN_etaN3 = 0;
     else
       double corr_vN_etaN3 = (1./corr_vAlpha_etaN3)*(corr_vclustSizeY_etaN3_DATA/1.);  //mean of trackTrigger is 1.

     if(corr_vAlpha_etaN4==0)
       double corr_vN_etaN4 = 0;
     else
       double corr_vN_etaN4 = (1./corr_vAlpha_etaN4)*(corr_vclustSizeY_etaN4_DATA/1.);  //mean of trackTrigger is 1.
 
     if(corr_vAlpha_etaN5==0)
       double corr_vN_etaN5 = 0;
     else
       double corr_vN_etaN5 = (1./corr_vAlpha_etaN5)*(corr_vclustSizeY_etaN5_DATA/1.);  //mean of trackTrigger is 1.

     //trying to sum up the multiplicity distribution
     nevezo += (trackTrigger_data/epsilon);
     TEST_noEpsilon += trackTrigger_data;

     corr_szamlalo_etaP5 += (trackTrigger_data/epsilon)*corr_vN_etaP5;  //With vertex??
     corr_szamlalo_etaP4 += (trackTrigger_data/epsilon)*corr_vN_etaP4;  //With vertex??
     corr_szamlalo_etaP3 += (trackTrigger_data/epsilon)*corr_vN_etaP3;  //With vertex??
     corr_szamlalo_etaP2 += (trackTrigger_data/epsilon)*corr_vN_etaP2;  //With vertex??
     corr_szamlalo_etaP1 += (trackTrigger_data/epsilon)*corr_vN_etaP1;  //With vertex??
     corr_szamlalo_etaN1 += (trackTrigger_data/epsilon)*corr_vN_etaN1;  //With vertex??
     corr_szamlalo_etaN2 += (trackTrigger_data/epsilon)*corr_vN_etaN2;  //With vertex??
     corr_szamlalo_etaN3 += (trackTrigger_data/epsilon)*corr_vN_etaN3;  //With vertex??
     corr_szamlalo_etaN4 += (trackTrigger_data/epsilon)*corr_vN_etaN4;  //With vertex??
     corr_szamlalo_etaN5 += (trackTrigger_data/epsilon)*corr_vN_etaN5;  //With vertex??

     NumOfRecEvents += (1./epsilon)*trackTrigger_data;
  }

  std::cerr<< std::endl;
  std::cerr<<"plotting results"<<std::endl;
  
  //zero multiplicity correction
  std::cerr<<"nevezo_1: " << nevezo << std::endl;
  nevezo+= multiplicityRatio_sim*nevezo;
  std::cerr<<"nevezo_2: " << nevezo << std::endl;

  // draw
  // looper corrected result
/*
  std::cerr<<"RESULT P5: "<<(corr_szamlalo_etaP5/nevezo)/0.5<<std::endl;
  std::cerr<<"RESULT P4: "<<(corr_szamlalo_etaP4/nevezo)/0.5<<std::endl;
  std::cerr<<"RESULT P3: "<<(corr_szamlalo_etaP3/nevezo)/0.5<<std::endl;
  std::cerr<<"RESULT P2: "<<(corr_szamlalo_etaP2/nevezo)/0.5<<std::endl;
  std::cerr<<"RESULT P1: "<<(corr_szamlalo_etaP1/nevezo)/0.5<<std::endl;
  std::cerr<<"RESULT N1: "<<(corr_szamlalo_etaN1/nevezo)/0.5<<std::endl;
  std::cerr<<"RESULT N2: "<<(corr_szamlalo_etaN2/nevezo)/0.5<<std::endl;
  std::cerr<<"RESULT N3: "<<(corr_szamlalo_etaN3/nevezo)/0.5<<std::endl;
  std::cerr<<"RESULT N4: "<<(corr_szamlalo_etaN4/nevezo)/0.5<<std::endl;
  std::cerr<<"RESULT N5: "<<(corr_szamlalo_etaN5/nevezo)/0.5<<std::endl;

  std::cerr<<"NumOfRecEvents: "<<NumOfRecEvents<<std::endl;
*/

  TH1D * corr_result = new TH1D("corr_result","corr_result",14,-3.5,3.5);
  corr_result->SetBinContent(corr_result->FindBin(2.25),(corr_szamlalo_etaP5/nevezo)/0.5);
  corr_result->SetBinContent(corr_result->FindBin(1.75),(corr_szamlalo_etaP4/nevezo)/0.5);
  corr_result->SetBinContent(corr_result->FindBin(1.25),(corr_szamlalo_etaP3/nevezo)/0.5);
  corr_result->SetBinContent(corr_result->FindBin(0.75),(corr_szamlalo_etaP2/nevezo)/0.5);
  corr_result->SetBinContent(corr_result->FindBin(0.25),(corr_szamlalo_etaP1/nevezo)/0.5);
  corr_result->SetBinContent(corr_result->FindBin(-0.25),(corr_szamlalo_etaN1/nevezo)/0.5);
  corr_result->SetBinContent(corr_result->FindBin(-0.75),(corr_szamlalo_etaN2/nevezo)/0.5);
  corr_result->SetBinContent(corr_result->FindBin(-1.25),(corr_szamlalo_etaN3/nevezo)/0.5);
  corr_result->SetBinContent(corr_result->FindBin(-1.75),(corr_szamlalo_etaN4/nevezo)/0.5);
  corr_result->SetBinContent(corr_result->FindBin(-2.25),(corr_szamlalo_etaN5/nevezo)/0.5);

  // errors
  corr_result->SetBinError(corr_result->FindBin(2.25),(corr_szamlalo_etaP5/nevezo)*0.08/0.5);
  corr_result->SetBinError(corr_result->FindBin(1.75),(corr_szamlalo_etaP4/nevezo)*0.08/0.5);
  corr_result->SetBinError(corr_result->FindBin(1.25),(corr_szamlalo_etaP3/nevezo)*0.08/0.5);
  corr_result->SetBinError(corr_result->FindBin(0.75),(corr_szamlalo_etaP2/nevezo)*0.08/0.5);
  corr_result->SetBinError(corr_result->FindBin(0.25),(corr_szamlalo_etaP1/nevezo)*0.08/0.5);
  corr_result->SetBinError(corr_result->FindBin(-0.25),(corr_szamlalo_etaN1/nevezo)*0.08/0.5);
  corr_result->SetBinError(corr_result->FindBin(-0.75),(corr_szamlalo_etaN2/nevezo)*0.08/0.5);
  corr_result->SetBinError(corr_result->FindBin(-1.25),(corr_szamlalo_etaN3/nevezo)*0.08/0.5);
  corr_result->SetBinError(corr_result->FindBin(-1.75),(corr_szamlalo_etaN4/nevezo)*0.08/0.5);
  corr_result->SetBinError(corr_result->FindBin(-2.25),(corr_szamlalo_etaN5/nevezo)*0.08/0.5);

  corr_result->GetXaxis()->SetTitle("#eta");
  corr_result->GetYaxis()->SetTitle("dN/d#eta");

  corr_result->SetLineColor(1);
  corr_result->SetMarkerStyle(20);
  corr_result->SetMarkerSize(1.8);

  corr_result->Draw("sameP");

  //simulated dNdeta
  hSim = new TH1D("hSim","hSim",14,-3.5,3.5);
  hSim_lemma = new TH1D("hSim_lemma","hSim_lemma",14,-3.5,3.5);
  
  for(int i = 1; i<=100; i++) {
    hSim_lemma->Reset();
    TFile f(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));

    hSim_lemma = (TH1D*)f.Get("hTestEtaFull");
    hSim->Add(hSim_lemma);
  }

  hSim->Scale(1./(100.*hSim->GetBinWidth(0)));
  hSim->SetLineColor(2);
  hSim->Draw("same");

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
//  leg6->AddEntry(hSim,"Sim. dN/d#eta","L");
  leg6->AddEntry(corr_result,"Rec. dN/d#eta, 1. layer","P");
//  leg6->AddEntry(corr_result_lemma,"Rec. dN/d#eta w/o vertex, 2. layer","P");
//  leg6->AddEntry(corr_result_rd,"Rec. dN/d#eta w/o vertex, 3. layer","P");
//  leg6->AddEntry(hSimV,"Sim. dN/d#eta with 1 rec. vertex","L");
//  leg6->AddEntry(SimVBinned,"Sim. dN/d#eta with 1 rec. v. / rec. dN/d#eta with 1 rec. v.","L");
//  leg6->AddEntry(SimBinned,"Sim dNd#eta / Rec. dN/d#eta with 1 rec vertex","L");
//  leg6->SetHeader("Multiplicity from herwig was increased");
//  leg6->SetHeader("p distribution from herwig has been modified: p -> 0.5*p");

  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
//  leg6->Draw();

  MyCanvas.SaveAs("HI_MC_layer1_Loopers_plot.C");
}

