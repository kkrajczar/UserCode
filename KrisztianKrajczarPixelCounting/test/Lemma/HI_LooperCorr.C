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
  for(int i = 1; i<=10; i++) {
    ntuple1.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  TChain ntuple2("multProp_looper");
  for(int i = 1; i<=10; i++) {
    ntuple2.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  //sim
  TChain ntuple1_sim("multProp");
  for(int i = 1; i<=10; i++) {
    ntuple1_sim.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  TChain ntuple2_sim("multProp_looper");
  for(int i = 1; i<=10; i++) {
    ntuple2_sim.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  TChain ntuple3_sim("hJustLooper");
  for(int i = 1; i<=10; i++) {
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

  float correct1_etaP5[1000];
  float correct1_etaP4[1000];
  float correct1_etaP3[1000];
  float correct1_etaP2[1000];
  float correct1_etaP1[1000];
  float correct1_etaN1[1000];
  float correct1_etaN2[1000];
  float correct1_etaN3[1000];
  float correct1_etaN4[1000];
  float correct1_etaN5[1000];

  float correct1_etaP5_error[1000];
  float correct1_etaP4_error[1000];
  float correct1_etaP3_error[1000];
  float correct1_etaP2_error[1000];
  float correct1_etaP1_error[1000];
  float correct1_etaN1_error[1000];
  float correct1_etaN2_error[1000];
  float correct1_etaN3_error[1000];
  float correct1_etaN4_error[1000];
  float correct1_etaN5_error[1000];

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

     if(hLorLP5->GetEntries()!=0 && hAllP5->GetEntries()!=0)
       correct1_etaP5_error[i] = correct1_etaP5[i]*sqrt((1./hLorLP5->GetEntries()) + (1./hAllP5->GetEntries()));
     else
       correct1_etaP5_error[i] = 0;


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

     if(hLorLP2->GetEntries()!=0 && hAllP2->GetEntries()!=0)
       correct1_etaP2_error[i] = correct1_etaP2[i]*sqrt((1./hLorLP2->GetEntries()) + (1./hAllP2->GetEntries()));
     else
       correct1_etaP2_error[i] = 0.;



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

//     std::cerr<<"   correct1_etaP2: " << correct1_etaP2[i] << std::endl;
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

  float failed_etaP5[1000], failed_etaP4[1000], failed_etaP3[1000], failed_etaP2[1000], failed_etaP1[1000];
  float failed_etaN5[1000], failed_etaN4[1000], failed_etaN3[1000], failed_etaN2[1000], failed_etaN1[1000];
  float failed_etaP5_error[1000], failed_etaP4_error[1000], failed_etaP3_error[1000], failed_etaP2_error[1000], failed_etaP1_error[1000];
  float failed_etaN5_error[1000], failed_etaN4_error[1000], failed_etaN3_error[1000], failed_etaN2_error[1000], failed_etaN1_error[1000];

  float failed_etaP5_DATA[1000], failed_etaP4_DATA[1000], failed_etaP3_DATA[1000], failed_etaP2_DATA[1000], failed_etaP1_DATA[1000];
  float failed_etaN5_DATA[1000], failed_etaN4_DATA[1000], failed_etaN3_DATA[1000], failed_etaN2_DATA[1000], failed_etaN1_DATA[1000];

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

     if(hFailedSize_P5->GetMean(1)!=0)
        failed_etaP5_error[i] = sqrt(1./hFailedSize_P5->GetMean(1));
     else
        failed_etaP5_error[i] = 0.;
     if(failed_etaP2_error[i]!=0)
        failed_etaP2_error[i] = sqrt(1./hFailedSize_P2->GetMean(1));
     else
        failed_etaP2_error[i] = 0.;

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

  ////////////////////////
  //
  // Summation
  //
  ////////////////////////

  double AboveLoopersP5 = 0.;
  double AboveLoopersP4 = 0.;
  double AboveLoopersP3 = 0.;
  double AboveLoopersP2 = 0.;
  double AboveLoopersP1 = 0.;
  double AboveLoopersN1 = 0.;
  double AboveLoopersN2 = 0.;
  double AboveLoopersN3 = 0.;
  double AboveLoopersN4 = 0.;
  double AboveLoopersN5 = 0.;

  double AboveAllP5 = 0.;
  double AboveAllP4 = 0.;
  double AboveAllP3 = 0.;
  double AboveAllP2 = 0.;
  double AboveAllP1 = 0.;
  double AboveAllN1 = 0.;
  double AboveAllN2 = 0.;
  double AboveAllN3 = 0.;
  double AboveAllN4 = 0.;
  double AboveAllN5 = 0.;

  TH1D * looper_all = new TH1D("looper_all","looper_all",14,-3.5,3.5);
  TH1D * looper_lemma = new TH1D("looper_lemma","looper_lemma",14,-3.5,3.5);
  TH1D * looper_0 = new TH1D("looper_0","looper_0",14,-3.5,3.5);
  TH1D * looper_1 = new TH1D("looper_1","looper_1",14,-3.5,3.5);
  TH1D * looper_2 = new TH1D("looper_2","looper_2",14,-3.5,3.5);
  TH1D * looper_3 = new TH1D("looper_3","looper_3",14,-3.5,3.5);
  TH1D * looper_4 = new TH1D("looper_4","looper_4",14,-3.5,3.5);
  TH1D * looper_5 = new TH1D("looper_5","looper_5",14,-3.5,3.5);
  TH1D * looper_6 = new TH1D("looper_6","looper_6",14,-3.5,3.5);
  TH1D * looper_7 = new TH1D("looper_7","looper_7",14,-3.5,3.5);
  TH1D * looper_8 = new TH1D("looper_8","looper_8",14,-3.5,3.5);
  TH1D * looper_9 = new TH1D("looper_9","looper_9",14,-3.5,3.5);
  TH1D * looper_10 = new TH1D("looper_10","looper_10",14,-3.5,3.5);
  TH1D * looper_11 = new TH1D("looper_11","looper_11",14,-3.5,3.5);
  TH1D * looper_12 = new TH1D("looper_12","looper_12",14,-3.5,3.5);
  TH1D * looper_13 = new TH1D("looper_13","looper_13",14,-3.5,3.5);
  TH1D * looper_14 = new TH1D("looper_14","looper_14",14,-3.5,3.5);
  TH1D * looper_15 = new TH1D("looper_15","looper_15",14,-3.5,3.5);
  TH1D * looper_16 = new TH1D("looper_16","looper_16",14,-3.5,3.5);
  TH1D * looper_17 = new TH1D("looper_17","looper_17",14,-3.5,3.5);
  TH1D * looper_18 = new TH1D("looper_18","looper_18",14,-3.5,3.5);
  TH1D * looper_19 = new TH1D("looper_19","looper_19",14,-3.5,3.5);
  TH1D * looper_20 = new TH1D("looper_20","looper_20",14,-3.5,3.5);
  TH1D * looper_21 = new TH1D("looper_21","looper_21",14,-3.5,3.5);
  TH1D * looper_22 = new TH1D("looper_22","looper_22",14,-3.5,3.5);
  TH1D * looper_23 = new TH1D("looper_23","looper_23",14,-3.5,3.5);
  TH1D * looper_24 = new TH1D("looper_24","looper_24",14,-3.5,3.5);
  TH1D * looper_25 = new TH1D("looper_25","looper_25",14,-3.5,3.5);
  TH1D * looper_26 = new TH1D("looper_26","looper_26",14,-3.5,3.5);
  TH1D * looper_27 = new TH1D("looper_27","looper_27",14,-3.5,3.5);
  TH1D * looper_28 = new TH1D("looper_28","looper_28",14,-3.5,3.5);
  TH1D * looper_29 = new TH1D("looper_29","looper_29",14,-3.5,3.5);
  TH1D * looper_30 = new TH1D("looper_30","looper_30",14,-3.5,3.5);

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

     double vclustSizeY_etaP5_error = sqrt(1./hclustSizeY_etaP5->GetMean(1));   
     double vclustSizeY_etaP2_error = sqrt(1./hclustSizeY_etaP2->GetMean(1));   

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

     AboveLoopersP5 += failed_etaP5[i]*correct1_etaP5[i];
     AboveLoopersP4 += failed_etaP4[i]*correct1_etaP4[i];
     AboveLoopersP3 += failed_etaP3[i]*correct1_etaP3[i];
     AboveLoopersP2 += failed_etaP2[i]*correct1_etaP2[i];
     AboveLoopersP1 += failed_etaP1[i]*correct1_etaP1[i];
     AboveLoopersN1 += failed_etaN1[i]*correct1_etaN1[i];
     AboveLoopersN2 += failed_etaN2[i]*correct1_etaN2[i];
     AboveLoopersN3 += failed_etaN3[i]*correct1_etaN3[i];
     AboveLoopersN4 += failed_etaN4[i]*correct1_etaN4[i];
     AboveLoopersN5 += failed_etaN5[i]*correct1_etaN5[i];

     AboveAllP5 += vclustSizeY_etaP5;
     AboveAllP4 += vclustSizeY_etaP4;
     AboveAllP3 += vclustSizeY_etaP3;
     AboveAllP2 += vclustSizeY_etaP2;
     AboveAllP1 += vclustSizeY_etaP1;
     AboveAllN1 += vclustSizeY_etaN1;
     AboveAllN2 += vclustSizeY_etaN2;
     AboveAllN3 += vclustSizeY_etaN3;
     AboveAllN4 += vclustSizeY_etaN4;
     AboveAllN5 += vclustSizeY_etaN5;

     looper_lemma->Reset();
     looper_lemma->SetBinContent(looper_lemma->FindBin(2.25),failed_etaP5[i]*correct1_etaP5[i]/vclustSizeY_etaP5);
     looper_lemma->SetBinContent(looper_lemma->FindBin(1.75),failed_etaP4[i]*correct1_etaP4[i]/vclustSizeY_etaP4);
     looper_lemma->SetBinContent(looper_lemma->FindBin(1.25),failed_etaP3[i]*correct1_etaP3[i]/vclustSizeY_etaP3);
     looper_lemma->SetBinContent(looper_lemma->FindBin(0.75),failed_etaP2[i]*correct1_etaP2[i]/vclustSizeY_etaP2);
     looper_lemma->SetBinContent(looper_lemma->FindBin(0.25),failed_etaP1[i]*correct1_etaP1[i]/vclustSizeY_etaP1);
     looper_lemma->SetBinContent(looper_lemma->FindBin(-0.25),failed_etaN1[i]*correct1_etaN1[i]/vclustSizeY_etaN1);
     looper_lemma->SetBinContent(looper_lemma->FindBin(-0.75),failed_etaN2[i]*correct1_etaN2[i]/vclustSizeY_etaN2);
     looper_lemma->SetBinContent(looper_lemma->FindBin(-1.25),failed_etaN3[i]*correct1_etaN3[i]/vclustSizeY_etaN3);
     looper_lemma->SetBinContent(looper_lemma->FindBin(-1.75),failed_etaN4[i]*correct1_etaN4[i]/vclustSizeY_etaN4);
     looper_lemma->SetBinContent(looper_lemma->FindBin(-2.25),failed_etaN5[i]*correct1_etaN5[i]/vclustSizeY_etaN5);

     double looper_lemma_P5 = failed_etaP5[i]*correct1_etaP5[i]/vclustSizeY_etaP5;
     double looper_lemma_P2 = failed_etaP2[i]*correct1_etaP2[i]/vclustSizeY_etaP2;

     if(vclustSizeY_etaP5!=0)
        double looper_lemma_P5_error = looper_lemma_P5*sqrt(failed_etaP5_error[i]*failed_etaP5 + correct1_etaP5_error[i]*correct1_etaP5_error[i] + (1./vclustSizeY_etaP5));
     else
        double looper_lemma_P5_error = 0.;
     if(vclustSizeY_etaP2!=0)
        double looper_lemma_P2_error = looper_lemma_P2*sqrt(failed_etaP2_error[i]*failed_etaP2 + correct1_etaP2_error[i]*correct1_etaP2_error[i] + (1./vclustSizeY_etaP2));
     else
        double looper_lemma_P2_error = 0.;

     looper_lemma->SetBinError(looper_lemma->FindBin(2.25),looper_lemma_P5_error);
//     looper_lemma->SetBinError(looper_lemma->FindBin(1.75),failed_etaP4[i]*correct1_etaP4[i]/vclustSizeY_etaP4);
//     looper_lemma->SetBinError(looper_lemma->FindBin(1.25),failed_etaP3[i]*correct1_etaP3[i]/vclustSizeY_etaP3);
     looper_lemma->SetBinError(looper_lemma->FindBin(0.75),looper_lemma_P2_error);
//     looper_lemma->SetBinError(looper_lemma->FindBin(0.25),failed_etaP1[i]*correct1_etaP1[i]/vclustSizeY_etaP1);
//     looper_lemma->SetBinError(looper_lemma->FindBin(-0.25),failed_etaN1[i]*correct1_etaN1[i]/vclustSizeY_etaN1);
//     looper_lemma->SetBinError(looper_lemma->FindBin(-0.75),failed_etaN2[i]*correct1_etaN2[i]/vclustSizeY_etaN2);
//     looper_lemma->SetBinError(looper_lemma->FindBin(-1.25),failed_etaN3[i]*correct1_etaN3[i]/vclustSizeY_etaN3);
//     looper_lemma->SetBinError(looper_lemma->FindBin(-1.75),failed_etaN4[i]*correct1_etaN4[i]/vclustSizeY_etaN4);
//     looper_lemma->SetBinError(looper_lemma->FindBin(-2.25),failed_etaN5[i]*correct1_etaN5[i]/vclustSizeY_etaN5);

     if(i==0)
       looper_0->Add(looper_lemma);
     if(i==1)
       looper_1->Add(looper_lemma);
     if(i==2)
       looper_2->Add(looper_lemma);
     if(i==3)
       looper_3->Add(looper_lemma);
     if(i==4)
       looper_4->Add(looper_lemma);
     if(i==5)
       looper_5->Add(looper_lemma);
     if(i==6)
       looper_6->Add(looper_lemma);
     if(i==6)
       looper_6->Add(looper_lemma);
     if(i==7)
       looper_7->Add(looper_lemma);
     if(i==8)
       looper_8->Add(looper_lemma);
     if(i==9)
       looper_9->Add(looper_lemma);
     if(i==10)
       looper_10->Add(looper_lemma);
     if(i==11)
       looper_11->Add(looper_lemma);
     if(i==12)
       looper_12->Add(looper_lemma);
     if(i==13)
       looper_13->Add(looper_lemma);
     if(i==14)
       looper_14->Add(looper_lemma);
     if(i==15)
       looper_15->Add(looper_lemma);
     if(i==16)
       looper_16->Add(looper_lemma);
     if(i==17)
       looper_17->Add(looper_lemma);
     if(i==18)
       looper_18->Add(looper_lemma);
     if(i==19)
       looper_19->Add(looper_lemma);
     if(i==20)
       looper_20->Add(looper_lemma);
     if(i==21)
       looper_21->Add(looper_lemma);
     if(i==22)
       looper_22->Add(looper_lemma);
     if(i==23)
       looper_23->Add(looper_lemma);
     if(i==24)
       looper_24->Add(looper_lemma);
     if(i==25)
       looper_25->Add(looper_lemma);
     if(i==26)
       looper_26->Add(looper_lemma);
     if(i==27)
       looper_27->Add(looper_lemma);
     if(i==28)
       looper_28->Add(looper_lemma);
     if(i==29)
       looper_29->Add(looper_lemma);
     if(i==30)
       looper_30->Add(looper_lemma);
  }

  std::cerr<< std::endl;
  std::cerr<<"plotting results"<<std::endl;

  looper_all->SetBinContent(looper_lemma->FindBin(2.25),AboveLoopersP5/AboveAllP5);
  looper_all->SetBinContent(looper_lemma->FindBin(1.75),AboveLoopersP4/AboveAllP4);
  looper_all->SetBinContent(looper_lemma->FindBin(1.25),AboveLoopersP3/AboveAllP3);
  looper_all->SetBinContent(looper_lemma->FindBin(0.75),AboveLoopersP2/AboveAllP2);
  looper_all->SetBinContent(looper_lemma->FindBin(0.25),AboveLoopersP1/AboveAllP1);
  looper_all->SetBinContent(looper_lemma->FindBin(-0.25),AboveLoopersN1/AboveAllN1);
  looper_all->SetBinContent(looper_lemma->FindBin(-0.75),AboveLoopersN2/AboveAllN2);
  looper_all->SetBinContent(looper_lemma->FindBin(-1.25),AboveLoopersN3/AboveAllN3);
  looper_all->SetBinContent(looper_lemma->FindBin(-1.75),AboveLoopersN4/AboveAllN4);
  looper_all->SetBinContent(looper_lemma->FindBin(-2.25),AboveLoopersN5/AboveAllN5);

  looper_all->GetXaxis()->SetTitle("#eta");
  looper_all->GetYaxis()->SetTitle("Looper correction");
  looper_all->SetTitle(0);
  looper_all->SetMarkerColor(1);
  looper_all->SetMarkerStyle(20);
  looper_all->SetMarkerSize(0.8);
  looper_all->Draw("P");

  looper_0->GetXaxis()->SetTitle("#eta");
  looper_0->GetYaxis()->SetTitle("Looper correction");
  looper_0->SetTitle(0);

  looper_0->SetMarkerColor(1);
  looper_0->SetMarkerStyle(20);
  looper_0->SetMarkerSize(0.8);
  looper_1->SetMarkerColor(1);
  looper_1->SetMarkerStyle(20);
  looper_1->SetMarkerSize(0.8);
  looper_2->SetMarkerColor(1);
  looper_2->SetMarkerStyle(20);
  looper_2->SetMarkerSize(0.8);
  looper_3->SetMarkerColor(1);
  looper_3->SetMarkerStyle(20);
  looper_3->SetMarkerSize(0.8);
  looper_4->SetMarkerColor(1);
  looper_4->SetMarkerStyle(20);
  looper_4->SetMarkerSize(0.8);
  looper_5->SetMarkerColor(1);
  looper_5->SetMarkerStyle(20);
  looper_5->SetMarkerSize(0.8);
  looper_6->SetMarkerColor(1);
  looper_6->SetMarkerStyle(20);
  looper_6->SetMarkerSize(0.8);
  looper_7->SetMarkerColor(1);
  looper_7->SetMarkerStyle(20);
  looper_7->SetMarkerSize(0.8);
  looper_8->SetMarkerColor(1);
  looper_8->SetMarkerStyle(20);
  looper_8->SetMarkerSize(0.8);
  looper_9->SetMarkerColor(1);
  looper_9->SetMarkerStyle(20);
  looper_9->SetMarkerSize(0.8);
  looper_10->SetMarkerColor(1);
  looper_10->SetMarkerStyle(20);
  looper_10->SetMarkerSize(0.8);
  looper_11->SetMarkerColor(1);
  looper_11->SetMarkerStyle(20);
  looper_11->SetMarkerSize(0.8);
  looper_12->SetMarkerColor(1);
  looper_12->SetMarkerStyle(20);
  looper_12->SetMarkerSize(0.8);
  looper_13->SetMarkerColor(1);
  looper_13->SetMarkerStyle(20);
  looper_13->SetMarkerSize(0.8);
  looper_14->SetMarkerColor(1);
  looper_14->SetMarkerStyle(20);
  looper_14->SetMarkerSize(0.8);
  looper_15->SetMarkerColor(1);
  looper_15->SetMarkerStyle(20);
  looper_15->SetMarkerSize(0.8);
  looper_16->SetMarkerColor(1);
  looper_16->SetMarkerStyle(20);
  looper_16->SetMarkerSize(0.8);
  looper_17->SetMarkerColor(1);
  looper_17->SetMarkerStyle(20);
  looper_17->SetMarkerSize(0.8);
  looper_18->SetMarkerColor(1);
  looper_18->SetMarkerStyle(20);
  looper_18->SetMarkerSize(0.8);
  looper_19->SetMarkerColor(1);
  looper_19->SetMarkerStyle(20);
  looper_19->SetMarkerSize(0.8);
  looper_20->SetMarkerColor(1);
  looper_20->SetMarkerStyle(20);
  looper_20->SetMarkerSize(0.8);
  looper_21->SetMarkerColor(1);
  looper_21->SetMarkerStyle(20);
  looper_21->SetMarkerSize(0.8);
  looper_22->SetMarkerColor(1);
  looper_22->SetMarkerStyle(20);
  looper_22->SetMarkerSize(0.8);
  looper_23->SetMarkerColor(1);
  looper_23->SetMarkerStyle(20);
  looper_23->SetMarkerSize(0.8);
  looper_24->SetMarkerColor(1);
  looper_24->SetMarkerStyle(20);
  looper_24->SetMarkerSize(0.8);
  looper_25->SetMarkerColor(1);
  looper_25->SetMarkerStyle(20);
  looper_25->SetMarkerSize(0.8);
  looper_26->SetMarkerColor(1);
  looper_26->SetMarkerStyle(20);
  looper_26->SetMarkerSize(0.8);
  looper_27->SetMarkerColor(1);
  looper_27->SetMarkerStyle(20);
  looper_27->SetMarkerSize(0.8);
  looper_28->SetMarkerColor(1);
  looper_28->SetMarkerStyle(20);
  looper_28->SetMarkerSize(0.8);
  looper_29->SetMarkerColor(1);
  looper_29->SetMarkerStyle(20);
  looper_29->SetMarkerSize(0.8);
  looper_30->SetMarkerColor(1);
  looper_30->SetMarkerStyle(20);
  looper_30->SetMarkerSize(0.8);
/*
  looper_0->Draw("P");
  looper_1->Draw("Psame");
  looper_2->Draw("Psame");
  looper_3->Draw("Psame");
  looper_4->Draw("Psame");
  looper_5->Draw("Psame");
  looper_6->Draw("Psame");
  looper_7->Draw("Psame");
  looper_8->Draw("Psame");
  looper_9->Draw("Psame");
  looper_10->Draw("Psame");
  looper_11->Draw("Psame");
  looper_12->Draw("Psame");
  looper_13->Draw("Psame");
  looper_14->Draw("Psame");
  looper_15->Draw("Psame");
  looper_16->Draw("Psame");
  looper_17->Draw("Psame");
  looper_18->Draw("Psame");
  looper_19->Draw("Psame");
  looper_20->Draw("Psame");
  looper_21->Draw("Psame");
  looper_22->Draw("Psame");
  looper_23->Draw("Psame");
  looper_24->Draw("Psame");
  looper_25->Draw("Psame");
  looper_26->Draw("Psame");
  looper_27->Draw("Psame");
  looper_28->Draw("Psame");
  looper_29->Draw("Psame");
  looper_30->Draw("Psame");
*/
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
//  leg6->AddEntry(corr_result,"Rec. dN/d#eta, 1. layer","P");
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

  MyCanvas.SaveAs("HI_LooperCorr_plot.C");
}

