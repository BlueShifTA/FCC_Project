#include<iostream>
#include<string.h>
#include<algorithm>

// 18/4/2016 -- Edit this program to get acceptance 
// 19/4/2016 -- Finish add program to print out the number of event

string convertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


void Get_Numb(string filename){
  
   //========================================Define Variables=================================================================

   TFile* f[5];
   TH1F* bg[20];
   THStack* Stack[15];
   TCanvas* can[16];
   TCanvas* cMET[16];
   TPad* p[6];
   TLegend* leg;
   string str[20];
   Float_t Cuts[17];
   Float_t NormLumi = 1000.0; // in 1000 fb-1
   Int_t rebin_pt     = 10;
   Int_t rebin_eta    = 20;
   Int_t rebin_delphi = 2;
   Float_t can_w      = 800; // Canvas Size 
   Float_t can_h      = 800;
   Int_t bins[100];

   //=====================================================String Part======================================================

   string selec  = "Select";
   string selec2 = "Plot_Select";
   string Canvas = "Canvas";
   string Stk    = "Stack";
   string saveAll;
   string proc[] = {"wzjet","tj","tt","BB"};
   string phys[] = {"_MET_","_Jet1_Pt_","_Jet2_Pt_","_Jet1_Eta_","_Jet2_Eta_","_Jetdel_Phi_","_Jet_Multi_" ,"_Jet_Pt_","_Jet_Eta_"  ,"_Elec_Pt_","_Elec_Eta_"  ,"_Muon_Pt_","_Muon_Eta_"  ,"_tau_Pt_","_tau_Eta_"  };
   Int_t   bin[] = {    3000 , 3000       , 3000       ,   1400     ,      1400  ,    64        ,   20     , 3000     , 1400        , 3000     , 1400        , 3000     , 1400        , 3000     , 1400        }; 
   Double_t min[] = {    0.0 ,   0.0      ,   0.0      ,  -7.0      ,      -7.0  ,     0.       ,    0     ,   0.0    , -7.0        ,   0.0    , -7.0        ,   0.0    , -7.0        ,   0.0    , -7.0        }; 
   Double_t max[] = { 30000.0, 30000.0    , 30000.0    ,   7.0      ,       7.0  ,   6.4        ,   20     , 30000.0  ,  7.0        , 30000.0  ,  7.0        , 30000.0  ,  7.0        , 30000.0  ,  7.0        };

   f[0]=new  TFile(filename.c_str());

   //==============================================Work Space========================================================
    // Clear Cut
    for (Int_t i_clear = 0 ; i_clear < 17 ; i_clear++) {
        Cuts[i_clear] = 0;
    }

   //===========================================Part 1: Plot=================================================== 

   //  ---------------------------------------------------------------------------------------------------- 
 
   for (Int_t i = 0 ; i < 8 ; i ++ ) {   // index for Selection Cut   

       stringstream ss;
       ss<<i;
       string str_can = Canvas+ss.str();
       can[i] = new TCanvas(str_can.c_str(),str_can.c_str(),can_w,can_h);
       can[i]->SetCanvasSize(can_w,can_h);
       can[i]->SetLogy();


       str[i]  = selec+phys[0]+ss.str();
       bg[i]=(TH1F*)f[0]->Get(str[i].c_str());
       //cout << str[i] << endl;
       // Rebinning
       bg[i]->Rebin(rebin_pt);
       bg[i]->Draw();
       // Collect Result must add in each step
       // Collect
       Cuts[i] += bg[i]->GetEntries();

       if (i == 7) {
           Int_t sum = 0 ;
           Int_t i_MET = 9;
           for (Int_t i_arr=99;i_arr>=10;i_arr--) {
               // bins[i_arr] = 0.;
               bins[i_arr] = bg[i]->GetBinContent(i_arr+1);
               //cout << "TEST Bin: " << i_arr*100. << " " << bins[i_arr] << endl;
               sum += bins[i_arr];
               //cout << sum << endl;
               if (i_arr <= 50 && i_arr >= 10 && i_arr%5 == 0 ){
                    Cuts[i_MET+i] += sum;
                    //cout << "i_MET " << i_MET << "count: " << Cuts[i_MET+i] << endl;
                    i_MET--;
               }
                   
           }

       }
       // ================================================================================================
       //Write the MET Threshold case -> Start with 1000 GeV  500 GeV step to 
       //for (Int_t test = 0 ; test < 17 ; test++ ) {
       //    cout << "TEST: " << Cuts[test] << endl; 
       //} 
       delete can[i];
 
   }
   
   // Print Results 
   // Create file for data aquisition

   fstream myfile;
   myfile.open("Results.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
   
   for (Int_t j = 0 ; j < 17 ; j++) { 
       myfile << "Selection Cuts " << j << " : " << Cuts[j] << " ";
       myfile << endl;
   }
   myfile.close(); 
}
