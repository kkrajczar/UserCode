{
 TChain ntuple_1("multProp");
 TChain ntuple_2("nd_multProp");
 TChain ntuple_3("rd_multProp");
 TChain ntuple_4("multProp_looper");
 TChain ntuple_5("nd_multProp_looper");
 TChain ntuple_6("rd_multProp_looper");
 TChain ntuple_7("hJustLooper");
 TChain ntuple_8("nd_hJustLooper");
 TChain ntuple_9("rd_hJustLooper");
 for(int i = 1; i<=100; i++) {
/*
    Long_t *id,*size,*flags,*mt;
    if(gSystem->GetPathInfo(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i),id,size,flags,mt)==1) {
       std::cerr<<" >>>>> NO FILE: " << i << std::endl;
       continue;
    }
*/
    TFile f(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
    if(!f.IsOpen() || f.IsZombie()) {
       std::cerr<<" >>>>> ZOMBIE : " << i << std::endl;
       continue;
    }

   std::cerr<<" [File: " << i << "]" << std::endl;
   ntuple_1.Add(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
   ntuple_2.Add(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
   ntuple_3.Add(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
   ntuple_4.Add(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
   ntuple_5.Add(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
   ntuple_6.Add(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
   ntuple_7.Add(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
   ntuple_8.Add(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
   ntuple_9.Add(Form("~krajczar/HI/CMSSW_3_9_0/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101027_085235/res/test_%i_1.root",i));
 }

 TFile resultFile("test.root","recreate");
 ntuple_1.Write();
 ntuple_2.Write();
 ntuple_3.Write();
 ntuple_4.Write();
 ntuple_5.Write();
 ntuple_6.Write();
 ntuple_7.Write();
 ntuple_8.Write();
 ntuple_9.Write();
 resultFile.Close();
}

