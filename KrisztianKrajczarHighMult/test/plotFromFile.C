{
  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonKK.C");
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.25);

  TFile f("particles_DATA.root");
  nEvent = (TNtuple*)f.Get("nEvent");

  TH2F * h2D = new TH2F("h2D","h2D",50,0.,3.3,50.,0.,5.);
  nEvent->Project("h2D","ratio_pt:angle","recTracks>1");
  
  h2D->GetXaxis()->SetTitle("Angle [rad]");
  h2D->GetYaxis()->SetTitle("p_{1,T}/p_{2,T}");
  h2D->Draw("box");
}
