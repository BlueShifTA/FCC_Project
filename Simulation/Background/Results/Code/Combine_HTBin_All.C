#include<iostream>
#include<string.h>
#include<algorithm>


string convertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


void Combine_HTBin(){
  
   //========================================Define Variables=================================================================

   TFile* f[64];
   TH1F* Event;
   TH1F* bg[64];
   TH1F* Entry[64];
   TH1F* HistPlot[64][15];
   THStack* Stack[15];
   TCanvas* can[16];
   TCanvas* cMET[16];
   TPad* p[6];
   TLegend* leg;
   string str[64];
   string str2[64];
   Float_t Cuts[17];
   Float_t xseczjet[16]={ 5.23728000e+05    
                        ,  3.18564600e+04    
                        ,  2.55386600e+03    
                        ,  2.34160400e+02    
                        ,  5.49338000e+01    
                        ,  1.93732200e+01    
                        ,  8.09117000e+00    
                        ,  1.70780500e+00    
                        ,  5.60359900e-01    
                        ,  2.26810500e-01    
                        ,  1.03779000e-01    
                        ,  3.05021100e-02    
                        ,  1.14733300e-02    
                        ,  4.13330000e-04    
                        ,  4.48121000e-05    
                        ,  7.07986300e-06    }; // in pb

   Float_t xsecwjet[16]={ 1.58470000e+06    
                        ,  4.58195500e+04    
                        ,  4.83750000e+03    
                        ,  4.46309300e+02    
                        ,  1.04878000e+02    
                        ,  3.59030000e+01    
                        ,  1.60525800e+01    
                        ,  3.18190000e+00    
                        ,  9.78030000e-01    
                        ,  3.84980000e-01    
                        ,  1.79901100e-01    
                        ,  5.13310000e-02    
                        ,  1.88280000e-02    
                        ,  6.59720000e-04    
                        ,  6.99137000e-05    
                        ,  1.04291700e-05                }; // in pb

   Float_t xsecwzonlyjet[16]={  0.00000000e+00
                            ,   4.15400000e+01
                            ,   0.00000000e+00
                            ,   0.00000000e+00
                            ,   1.86000000e-01
                            ,   4.07600000e-02
                            ,   3.96600000e-02
                            ,   5.95300000e-03
                            ,   2.48400000e-03
                            ,   1.04100000e-03
                            ,   4.18500000e-04
                            ,   1.10200000e-04
                            ,   2.44000000e-05
                            ,   0.00000000e+00
                            ,   0.00000000e+00
                            ,   0.00000000e+00}; // in pb

   Float_t xsecttbar[16]={ 1.952e+04   
                        ,  1.636e+04   
                        ,  5.257e+03   
                        ,  6.067e+02   
                        ,  1.203e+02   
                        ,  3.400e+01   
                        ,  1.325e+01   
                        ,  1.898e+00   
                        ,  4.655e-01   
                        ,  1.456e-01   
                        ,  5.447e-02   
                        ,  1.125e-02   
                        ,  3.039e-03   
                        ,  2.840e-05   
                        ,  7.689e-07   
                        ,  2.554e-08   }; // in pb

   Int_t sizezjet      = 16;
   Int_t sizewjet      = 16;
   Int_t sizewzonlyjet = 16;
   Int_t sizettbar     = 16;

   Float_t * xsec = new Float_t[sizezjet +sizewjet +sizewzonlyjet +sizettbar];
   copy(xseczjet     , xseczjet      + sizezjet     , xsec                                      );
   copy(xsecwjet     , xsecwjet      + sizewjet     , xsec  + sizezjet                          );
   copy(xsecwzonlyjet, xsecwzonlyjet + sizewzonlyjet, xsec  + sizezjet +sizewjet                );
   copy(xsecttbar    , xsecttbar     + sizettbar    , xsec  + sizezjet +sizewjet +sizewzonlyjet );


   Float_t NormLumi = 1.0; // in fb-1
   Int_t rebin_pt     = 10;
   Int_t rebin_eta    = 20;
   Int_t rebin_delphi = 2;
   Float_t can_w      = 800; // Canvas Size 
   Float_t can_h      = 800;

   //=====================================================String Part======================================================

   string selec  = "Select";
   string selec2 = "Plot_Select";
   string Canvas = "Canvas";
   string Stk    = "Stack";
   string saveAll;
   string proc[] = {"wzjet","tj","tt","BB"};
   string phys[] = {"_MET_","_Jet1_Pt_","_Jet2_Pt_","_Jet1_Eta_","_Jet2_Eta_","_Jetdel_Phi_","_Jet_Multi_" ,"_Jet_Pt_","_Jet_Eta_"  ,"_Elec_Pt_","_Elec_Eta_"  ,"_Muon_Pt_","_Muon_Eta_"  ,"_tau_Pt_","_tau_Eta_"  };
   Int_t   bin[] = {    3000 , 3000       , 3000       ,   1000     ,      1000  ,    64        ,   20     , 3000     , 1000        , 3000     , 1000        , 3000     , 1000        , 3000     , 1000        }; 
   Double_t min[] = {    0.0 ,   0.0      ,   0.0      ,  -5.0      ,      -5.0  ,     0.       ,    0     ,   0.0    , -5.0        ,   0.0    , -5.0        ,   0.0    , -5.0        ,   0.0    , -5.0        }; 
   Double_t max[] = { 30000.0, 30000.0    , 30000.0    ,   5.0      ,       5.0  ,   6.4        ,   20     , 30000.0  ,  5.0        , 30000.0  ,  5.0        , 30000.0  ,  5.0        , 30000.0  ,  5.0        };

   f[0]=new  TFile("tev100_wzjet_50_100_result_0_1.root");
   f[1]=new  TFile("tev100_wzjet_100_200_result_0_1.root");
   f[2]=new  TFile("tev100_wzjet_200_400_result_0_1.root");
   f[3]=new  TFile("tev100_wzjet_400_600_result_0_1.root");
   f[4]=new  TFile("tev100_wzjet_600_800_result_0_1.root");
   f[5]=new  TFile("tev100_wzjet_800_1000_result_0_1.root");
   f[6]=new  TFile("tev100_wzjet_1000_1500_result_0_1.root");
   f[7]=new  TFile("tev100_wzjet_1500_2000_result_0_1.root");
   f[8]=new  TFile("tev100_wzjet_2000_2500_result_0_1.root");
   f[9]=new  TFile("tev100_wzjet_2500_3000_result_0_1.root");
   f[10]=new TFile("tev100_wzjet_3000_4000_result_0_1.root");
   f[11]=new TFile("tev100_wzjet_4000_5000_result_0_1.root");
   f[12]=new TFile("tev100_wzjet_5000_10000_result_0_1.root");
   f[13]=new TFile("tev100_wzjet_10000_15000_result_0_1.root");
   f[14]=new TFile("tev100_wzjet_15000_20000_result_0_1.root");
   f[15]=new TFile("tev100_wzjet_20000_25000_result_0_1.root");

   f[16]=new TFile("tev100_wzjet_50_100_result_0_2.root");
   f[17]=new TFile("tev100_wzjet_100_200_result_0_2.root");
   f[18]=new TFile("tev100_wzjet_200_400_result_0_2.root");
   f[19]=new TFile("tev100_wzjet_400_600_result_0_2.root");
   f[20]=new TFile("tev100_wzjet_600_800_result_0_2.root");
   f[21]=new TFile("tev100_wzjet_800_1000_result_0_2.root");
   f[22]=new TFile("tev100_wzjet_1000_1500_result_0_2.root");
   f[23]=new TFile("tev100_wzjet_1500_2000_result_0_2.root");
   f[24]=new TFile("tev100_wzjet_2000_2500_result_0_2.root");
   f[25]=new TFile("tev100_wzjet_2500_3000_result_0_2.root");
   f[26]=new TFile("tev100_wzjet_3000_4000_result_0_2.root");
   f[27]=new TFile("tev100_wzjet_4000_5000_result_0_2.root");
   f[28]=new TFile("tev100_wzjet_5000_10000_result_0_2.root");
   f[29]=new TFile("tev100_wzjet_10000_15000_result_0_2.root");
   f[30]=new TFile("tev100_wzjet_15000_20000_result_0_2.root");
   f[31]=new TFile("tev100_wzjet_20000_25000_result_0_2.root");

   f[32]=new TFile("tev100_wzjet_50_100_result_0_3.root");
   f[33]=new TFile("tev100_wzjet_100_200_result_0_3.root");
   f[34]=new TFile("tev100_wzjet_200_400_result_0_3.root");
   f[35]=new TFile("tev100_wzjet_400_600_result_0_3.root");
   f[36]=new TFile("tev100_wzjet_600_800_result_0_3.root");
   f[37]=new TFile("tev100_wzjet_800_1000_result_0_3.root");
   f[38]=new TFile("tev100_wzjet_1000_1500_result_0_3.root");
   f[39]=new TFile("tev100_wzjet_1500_2000_result_0_3.root");
   f[40]=new TFile("tev100_wzjet_2000_2500_result_0_3.root");
   f[41]=new TFile("tev100_wzjet_2500_3000_result_0_3.root");
   f[42]=new TFile("tev100_wzjet_3000_4000_result_0_3.root");
   f[43]=new TFile("tev100_wzjet_4000_5000_result_0_3.root");
   f[44]=new TFile("tev100_wzjet_5000_10000_result_0_3.root");
   f[45]=new TFile("tev100_wzjet_10000_15000_result_0_3.root");
   f[46]=new TFile("tev100_wzjet_15000_20000_result_0_3.root");
   f[47]=new TFile("tev100_wzjet_20000_25000_result_0_3.root");
      
   f[48]=new TFile("tev100_ttbar_50_100_result_0.root");
   f[49]=new TFile("tev100_ttbar_100_200_result_0.root");
   f[50]=new TFile("tev100_ttbar_200_400_result_0.root");
   f[51]=new TFile("tev100_ttbar_400_600_result_0.root");
   f[52]=new TFile("tev100_ttbar_600_800_result_0.root");
   f[53]=new TFile("tev100_ttbar_800_1000_result_0.root");
   f[54]=new TFile("tev100_ttbar_1000_1500_result_0.root");
   f[55]=new TFile("tev100_ttbar_1500_2000_result_0.root");
   f[56]=new TFile("tev100_ttbar_2000_2500_result_0.root");
   f[57]=new TFile("tev100_ttbar_2500_3000_result_0.root");
   f[58]=new TFile("tev100_ttbar_3000_4000_result_0.root");
   f[59]=new TFile("tev100_ttbar_4000_5000_result_0.root");
   f[60]=new TFile("tev100_ttbar_5000_10000_result_0.root");
   f[61]=new TFile("tev100_ttbar_10000_15000_result_0.root");
   f[62]=new TFile("tev100_ttbar_15000_20000_result_0.root");
   f[63]=new TFile("tev100_ttbar_20000_25000_result_0.root");
   
   //==============================================Work Space========================================================
   
   //===========================================Part 1: Plot=================================================== 

   //  ---------------------------------------------------------------------------------------------------- 
 
   for (Int_t i = 0 ; i < 16 ; i ++ ) {   // index for Selection Cut   

       stringstream ss;
       ss<<i;
       for (Int_t i_stack = 0 ; i_stack < 15 ; i_stack++) {
            stringstream ss2;
            ss2<<i_stack;
            //cout << Canvas+ss2.str() << endl;
            string str_can = Canvas+ss2.str();
            string str_stk = Stk+ss2.str();
            //cout << str_stk << endl;
            can[i_stack] = new TCanvas(str_can.c_str(),str_can.c_str(),can_w,can_h);
            can[i_stack]->SetCanvasSize(can_w,can_h);
            can[i_stack]->SetLogy();
            //can[i_stack]->SetGrid();
            Stack[i_stack] = new THStack(str_stk.c_str(),""); 
            Stack[i_stack] = new THStack("Stack",""); 
       }

       for (Int_t i_main = 63 ;i_main>=0 ;i_main-- ) {   // index for open each file


         Entry[i_main]=(TH1F*)f[i_main]->Get("Select_MET_0");
         factor = NormLumi*xsec[i_main]*1000.f/Entry[i_main]->GetEntries();//GetSumOfWeights();
         //cout << "Number: " << i_main << " xsec: " << xsec[i_main] << " factor: " << factor << " Entry: " << Entry[i_main]->GetEntries() << endl;

         for (Int_t i_hist = 0 ; i_hist < 15 ; i_hist++){ // index for histogram
            str[i_hist]  = selec+phys[i_hist]+ss.str();
            str2[i_hist] = selec2+phys[i_hist]+ss.str();
            HistPlot[i_main][i_hist]    = new TH1F(str2[i_hist].c_str(),phys[i_hist].c_str(), bin[i_hist], min[i_hist], max[i_hist]);
            bg[i_main]=(TH1F*)f[i_main]->Get(str[i_hist].c_str());
            HistPlot[i_main][i_hist]->Add(bg[i_main],factor);
            //HistPlot[i_main][i_hist]->Draw();

            //Set color
            if (i_main <  16){
                HistPlot[i_main][i_hist]->SetLineColor(kBlack);
                HistPlot[i_main][i_hist]->SetFillColor(kBlack);
            } else if (i_main < 32) {
                HistPlot[i_main][i_hist]->SetLineColor(kBlue);
                HistPlot[i_main][i_hist]->SetFillColor(kBlue);
            } else if (i_main < 48) {
                HistPlot[i_main][i_hist]->SetLineColor(kGreen);
                HistPlot[i_main][i_hist]->SetFillColor(kGreen);
            } else {
                HistPlot[i_main][i_hist]->SetLineColor(kRed);
                HistPlot[i_main][i_hist]->SetFillColor(kRed);
            }
            // Rebinning
            if (i_hist == 0 || i_hist == 1 ||i_hist == 2 || i_hist == 7 || i_hist == 9 || i_hist == 11 || i_hist == 13 ) {// Rebin PT and MET
                HistPlot[i_main][i_hist]->Rebin(rebin_pt);
            }  

            if (i_hist == 3 || i_hist == 4 || i_hist == 8 || i_hist == 10 || i_hist == 12 || i_hist == 14 ) {// Rebin Eta
                HistPlot[i_main][i_hist]->Rebin(rebin_eta);
            }  

            if (i_hist == 5 ) {// Rebin DelPhi
                HistPlot[i_main][i_hist]->Rebin(rebin_delphi);
            }  
            // Add to Hist Stack
            Stack[i_hist]->Add(HistPlot[i_main][i_hist]);
         }
       }
       // ================================================================================================
       Cuts[i] = ((TH1*)(Stack[0]->GetStack()->Last()))->GetEntries();
       //cout << "Entries: " << Cuts[i] << endl; 

       gStyle->SetOptStat(0); 
       gStyle->SetOptTitle(0);
       gStyle->SetLegendBorderSize(0); 


       // Plot Parameters
       leg = new TLegend(0.60,0.65,0.87,0.87);
       //leg->SetHeader("#splitline{#sqrt{s} = 100 TeV, #int L dt = 1 fb^{-1}}{Z^{0} + Jets}");
       leg->SetHeader("#sqrt{s} = 100 TeV, #int L dt = 1 fb^{-1}");
       //leg->SetHeader("#sqrt{s} = 100 TeV, #int L dt = 10 pb^{-1}");
       //leg->AddEntry(HistPlot[0][0] ," ","");
       //leg->AddEntry(HistPlot[0][0] ," ","");
       leg->AddEntry(HistPlot[0][0]  ,"Z^{0} + jets    ","f");
       leg->AddEntry(HistPlot[16][0] ,"W^{#pm} + jets    ","f");
       leg->AddEntry(HistPlot[32][0] ,"Z^{0}W^{#pm}    ","f");
       leg->AddEntry(HistPlot[48][0] ,"t#bar{t}    ","f");
       //leg->AddEntry(HistPlot[4][0] ,"HTBin 600#rightarrow800    ","f");
       //leg->AddEntry(HistPlot[5][0] ,"HTBin 800#rightarrow1000   ","f");
       //leg->AddEntry(HistPlot[6][0] ,"HTBin 1000#rightarrow1500  ","f");
       //leg->AddEntry(HistPlot[7][0] ,"HTBin 1500#rightarrow2000  ","f");
       //leg->AddEntry(HistPlot[8][0] ,"HTBin 2000#rightarrow2500  ","f");
       //leg->AddEntry(HistPlot[9][0] ,"HTBin 2500#rightarrow3000  ","f");
       //leg->AddEntry(HistPlot[10][0],"HTBin 3000#rightarrow4000  ","f");
       //leg->AddEntry(HistPlot[11][0],"HTBin 4000#rightarrow5000  ","f");
       //leg->AddEntry(HistPlot[12][0],"HTBin 5000#rightarrow10000 ","f");
       //leg->AddEntry(HistPlot[13][0],"HTBin 10000#rightarrow15000","f");
       //leg->AddEntry(HistPlot[14][0],"HTBin 15000#rightarrow20000","f");
       //leg->AddEntry(HistPlot[15][0],"HTBin 20000#rightarrow25000","f");
       //leg->SetFillColorAlpha(0,0);
       TLegendEntry *header = (TLegendEntry*)leg->GetListOfPrimitives()->First();
       //header->SetTextAlign(22);
       //header->SetTextColor(2);
       header->SetTextSize(0.02);

       //Draw an axis on the right side
       //TGaxis *A1 = new TGaxis(0,5e9,6000,5e9,"",510,"-");


       // MET

       can[0]->cd();
       Stack[0]->Draw();
       Stack[0]->GetXaxis()->SetTitle("E^{Miss}_{T} [GeV]");
       Stack[0]->GetYaxis()->SetTitle("Events/100 GeV");
       Stack[0]->GetYaxis()->SetTitleOffset(1.25);
       Stack[0]->GetXaxis()->SetRangeUser(0,6000);
       Stack[0]->SetMinimum(0.3);
       Stack[0]->SetMaximum(10e8);
       Stack[0]->Draw();
       leg->Draw("same");
 
       // Jet1 Pt
       can[1]->cd();
       Stack[1]->Draw();
       Stack[1]->GetXaxis()->SetTitle("P_{T} Jet_{1} [GeV/c]");
       Stack[1]->GetYaxis()->SetTitle("Events/100 GeV");
       Stack[1]->GetYaxis()->SetTitleOffset(1.25);
       Stack[1]->GetXaxis()->SetRangeUser(0,6000);
       Stack[1]->SetMinimum(0.3);
       Stack[1]->SetMaximum(10e8);
       Stack[1]->Draw();
       leg->Draw("same");

       // Jet2 Pt
       can[2]->cd();
       Stack[2]->Draw();
       Stack[2]->GetXaxis()->SetTitle("P_{T} Jet_{2} [GeV/c]");
       Stack[2]->GetYaxis()->SetTitle("Events/100 GeV");
       Stack[2]->GetYaxis()->SetTitleOffset(1.25);
       Stack[2]->GetXaxis()->SetRangeUser(0,6000);
       Stack[2]->SetMaximum(10e8);
       Stack[2]->SetMinimum(0.3);
       Stack[2]->Draw();
       leg->Draw("same");

       
       // Jet1 Eta
       can[3]->cd();
       Stack[3]->Draw();
       Stack[3]->GetXaxis()->SetTitle("#eta Jet_{1} ");
       Stack[3]->GetYaxis()->SetTitle("Events/0.2 ");
       Stack[3]->GetYaxis()->SetTitleOffset(1.25);
       Stack[3]->GetXaxis()->SetRangeUser(-5,5);
       Stack[3]->SetMinimum(0.3);
       Stack[3]->SetMaximum(10e8);
       Stack[3]->Draw();
       leg->Draw("same");
       
       
       // Jet2 Eta
       can[4]->cd();
       Stack[4]->Draw();
       Stack[4]->GetXaxis()->SetTitle("#eta Jet_{2} ");
       Stack[4]->GetYaxis()->SetTitle("Events/0.01 ");
       Stack[4]->GetYaxis()->SetTitleOffset(1.25);
       Stack[4]->GetXaxis()->SetRangeUser(-5,5);
       Stack[4]->SetMinimum(0.3);
       Stack[4]->SetMaximum(10e8);
       Stack[4]->Draw();
       leg->Draw("same");
       
       // JetDelPhi
       can[5]->cd();
       Stack[5]->Draw();
       Stack[5]->GetXaxis()->SetTitle("#Delta#phi Jet_{1,2}");
       Stack[5]->GetYaxis()->SetTitle("Events/0.2 ");
       Stack[5]->GetYaxis()->SetTitleOffset(1.25);
       Stack[5]->GetXaxis()->SetRangeUser(0,6.4);
       Stack[5]->SetMinimum(0.3);
       Stack[5]->SetMaximum(10e8);
       Stack[5]->Draw();
       leg->Draw("same");
       
       // JetMulti
       can[6]->cd();
       Stack[6]->Draw();
       Stack[6]->GetXaxis()->SetTitle("Jet Multiplicity");
       Stack[6]->GetYaxis()->SetTitle("Events ");
       Stack[6]->GetYaxis()->SetTitleOffset(1.40);
       Stack[6]->GetXaxis()->SetRangeUser(0,20);
       Stack[6]->SetMinimum(0.3);
       Stack[6]->SetMaximum(10e9);
       Stack[6]->Draw();
       leg->Draw("same");
       
       // Jet Pt
       can[7]->cd();
       Stack[7]->Draw();
       Stack[7]->GetXaxis()->SetTitle("P_{T} Jet [GeV/c]");
       Stack[7]->GetYaxis()->SetTitle("Events/100 GeV");
       Stack[7]->GetYaxis()->SetTitleOffset(1.25);
       Stack[7]->GetXaxis()->SetRangeUser(0,6000);
       Stack[7]->SetMinimum(0.03);
       Stack[7]->Draw();
       leg->Draw("same");

       
       // Jet Eta
       can[8]->cd();
       Stack[8]->Draw();
       Stack[8]->GetXaxis()->SetTitle("#eta Jet [GeV/c]");
       Stack[8]->GetYaxis()->SetTitle("Events/0.2 ");
       Stack[8]->GetYaxis()->SetTitleOffset(1.25);
       Stack[8]->GetXaxis()->SetRangeUser(-5,5);
       Stack[8]->SetMinimum(0.3);
       Stack[8]->SetMaximum(10e8);
       Stack[8]->Draw();
       leg->Draw("same");

       // Elec Pt
       can[9]->cd();
       Stack[9]->Draw();
       Stack[9]->GetXaxis()->SetTitle("P_{T} Electron [GeV/c]");
       Stack[9]->GetYaxis()->SetTitle("Events/100 GeV");
       Stack[9]->GetYaxis()->SetTitleOffset(1.25);
       Stack[9]->GetXaxis()->SetRangeUser(0,6000);
       Stack[9]->SetMinimum(0.03);
       Stack[9]->Draw();
       leg->Draw("same");

       
       // Elec Eta
       can[10]->cd();
       Stack[10]->Draw();
       Stack[10]->GetXaxis()->SetTitle("#eta Elec [GeV/c]");
       Stack[10]->GetYaxis()->SetTitle("Events/0.2 ");
       Stack[10]->GetYaxis()->SetTitleOffset(1.25);
       Stack[10]->GetXaxis()->SetRangeUser(-5,5);
       Stack[10]->SetMinimum(0.3);
       Stack[10]->SetMaximum(10e8);
       Stack[10]->Draw();
       leg->Draw("same");

       // Muon Pt
       can[11]->cd();
       Stack[11]->Draw();
       Stack[11]->GetXaxis()->SetTitle("P_{T} Muon [GeV/c]");
       Stack[11]->GetYaxis()->SetTitle("Events/100 GeV");
       Stack[11]->GetYaxis()->SetTitleOffset(1.25);
       Stack[11]->GetXaxis()->SetRangeUser(0,6000);
       Stack[11]->SetMinimum(0.03);
       Stack[11]->Draw();
       leg->Draw("same");

       
       // Muon Eta
       can[12]->cd();
       Stack[12]->Draw();
       Stack[12]->GetXaxis()->SetTitle("#eta Muon [GeV/c]");
       Stack[12]->GetYaxis()->SetTitle("Events/0.2 ");
       Stack[12]->GetYaxis()->SetTitleOffset(1.25);
       Stack[12]->GetXaxis()->SetRangeUser(-5,5);
       Stack[12]->SetMinimum(0.3);
       Stack[12]->SetMaximum(10e8);
       Stack[12]->Draw();
       leg->Draw("same");

       // tau Pt
       can[13]->cd();
       Stack[13]->Draw();
       Stack[13]->GetXaxis()->SetTitle("P_{T} tau [GeV/c]");
       Stack[13]->GetYaxis()->SetTitle("Events/100 GeV");
       Stack[13]->GetYaxis()->SetTitleOffset(1.25);
       Stack[13]->GetXaxis()->SetRangeUser(0,6000);
       Stack[13]->SetMinimum(0.03);
       Stack[13]->Draw();
       leg->Draw("same");

       
       // tau Eta
       can[14]->cd();
       Stack[14]->Draw();
       Stack[14]->GetXaxis()->SetTitle("#eta tau [GeV/c]");
       Stack[14]->GetYaxis()->SetTitle("Events/0.2 ");
       Stack[14]->GetYaxis()->SetTitleOffset(1.25);
       Stack[14]->GetXaxis()->SetRangeUser(-5,5);
       Stack[14]->SetMinimum(0.3);
       Stack[14]->SetMaximum(10e8);
       Stack[14]->Draw();
       leg->Draw("same");

       
       // Save
       for (Int_t i_hist = 0; i_hist<15 ; i_hist++){ 
            saveAll = str[i_hist]+".pdf";
            can[i_hist]->SaveAs(saveAll.c_str());
            delete can[i_hist];
       }
   }
   // Print Results 
   // Create file for data aquisition

   fstream myfile;
   myfile.open("Results.txt", std::fstream::in | std::fstream::out | std::fstream::app);
   
   for (Int_t i = 0; i < 17 ; i++) {
     myfile << "Selection Cut " << i << " : " << Cuts[i] << endl;
   }   
   
   myfile.close(); 


}
