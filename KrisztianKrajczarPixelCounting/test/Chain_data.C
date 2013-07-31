{
 TChain ntuple_1("multProp");
 TChain ntuple_2("nd_multProp");
 TChain ntuple_3("rd_multProp");
 TChain ntuple_4("multProp_looper");
 TChain ntuple_5("nd_multProp_looper");
 TChain ntuple_6("rd_multProp_looper");
 for(int i = 1; i<=120; i++) {

    TFile f(Form("/net/hidsk0001/d00/scratch/krajczar/16x16_NEWCENT_SELECTION/test_nosiminfo_express_collisions_HLTfilter%i_1.root",i));
    if(!f.IsOpen() || f.IsZombie()) {
       std::cerr<<" >>>>> ZOMBIE : " << i << std::endl;
       continue;
    }

   std::cerr<<" [File: " << i << "]" << std::endl;
   ntuple_1.Add(Form("/net/hidsk0001/d00/scratch/krajczar/16x16_NEWCENT_SELECTION/test_nosiminfo_express_collisions_HLTfilter%i_1.root",i));
   ntuple_2.Add(Form("/net/hidsk0001/d00/scratch/krajczar/16x16_NEWCENT_SELECTION/test_nosiminfo_express_collisions_HLTfilter%i_1.root",i));
   ntuple_3.Add(Form("/net/hidsk0001/d00/scratch/krajczar/16x16_NEWCENT_SELECTION/test_nosiminfo_express_collisions_HLTfilter%i_1.root",i));
   ntuple_4.Add(Form("/net/hidsk0001/d00/scratch/krajczar/16x16_NEWCENT_SELECTION/test_nosiminfo_express_collisions_HLTfilter%i_1.root",i));
   ntuple_5.Add(Form("/net/hidsk0001/d00/scratch/krajczar/16x16_NEWCENT_SELECTION/test_nosiminfo_express_collisions_HLTfilter%i_1.root",i));
   ntuple_6.Add(Form("/net/hidsk0001/d00/scratch/krajczar/16x16_NEWCENT_SELECTION/test_nosiminfo_express_collisions_HLTfilter%i_1.root",i));
 }

 TFile resultFile("test_data.root","recreate");
 ntuple_1.Write();
 ntuple_2.Write();
 ntuple_3.Write();
 ntuple_4.Write();
 ntuple_5.Write();
 ntuple_6.Write();
 resultFile.Close();
}

