#include<iostream>
#include<string.h>


string convertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


void Combine_HTBin(){
  
   //========================================Define Variables=================================================================

   TFile* f[21];
   TH1F* Event;
   TH1F* bg[21];
   TH1F* Entry[21];
   TH1F* HistPlot[16][9];
   THStack* Stack[9];
   TCanvas* can[16];
   TCanvas* cMET[16];
   TPad* p[6];
   TLegend* leg;
   string str[9];
   string str2[9];
   Float_t xsecwzjet[16]={   2.109e+06 
                        , 7.785e+04 
                        , 7.401e+03 
                        , 6.824e+02 
                        , 1.606e+02 
                        , 5.545e+01 
                        , 2.428e+01 
                        , 4.945e+00 
                        , 1.563e+00 
                        , 6.254e-01 
                        , 2.905e-01 
                        , 8.535e-02 
                        , 3.261e-02 
                        , 1.310e-03 
                        , 1.464e-04 
                        , 2.075e-05 }; // in pb
   Float_t NormLumi = 1.0; // in fb-1
   Int_t rebin_pt     = 1;
   Int_t rebin_eta    = 1;
   Int_t rebin_delphi = 1;
   Float_t can_w      = 800; // Canvas Size 
   Float_t can_h      = 800;

   //=====================================================String Part======================================================

   string selec  = "Select";
   string selec2 = "Plot_Select";
   string Canvas = "Canvas";
   string Stk    = "Stack";
   string saveAll;
   string proc[] = {"wzjet","tj","tt","BB"};
   string phys[] = {"_MET_","_Jet1_Pt_","_Jet2_Pt_","_Jet1_Eta_","_Jet2_Eta_","_Jetdel_Phi_","_Jet_Multi_","_Jet_Pt_","_Jet_Eta_"};
   Int_t   bin[] = {    3000 , 3000       , 3000       ,   1000     ,      1000  ,    64        ,   20     , 3000     , 1000}; 
   Double_t min[] = {    0.0 ,   0.0      ,   0.0      ,  -5.0      ,      -5.0  ,     0.       ,    0     ,   0.0    , -5.0}; 
   Double_t max[] = { 30000.0, 30000.0    , 30000.0    ,   5.0      ,       5.0  ,   6.4        ,   20     , 30000.0  ,  5.0};

   f[0]=new  TFile("tev100_wzjet_50_100_result.root");
   f[1]=new  TFile("tev100_wzjet_100_200_result.root");
   f[2]=new  TFile("tev100_wzjet_200_400_result.root");
   f[3]=new  TFile("tev100_wzjet_400_600_result.root");
   f[4]=new  TFile("tev100_wzjet_600_800_result.root");
   f[5]=new  TFile("tev100_wzjet_800_1000_result.root");
   f[6]=new  TFile("tev100_wzjet_1000_1500_result.root");
   f[7]=new  TFile("tev100_wzjet_1500_2000_result.root");
   f[8]=new  TFile("tev100_wzjet_2000_2500_result.root");
   f[9]=new  TFile("tev100_wzjet_2500_3000_result.root");
   f[10]=new TFile("tev100_wzjet_3000_4000_result.root");
   f[11]=new TFile("tev100_wzjet_4000_5000_result.root");
   f[12]=new TFile("tev100_wzjet_5000_10000_result.root");
   f[13]=new TFile("tev100_wzjet_10000_15000_result.root");
   f[14]=new TFile("tev100_wzjet_15000_20000_result.root");
   f[15]=new TFile("tev100_wzjet_20000_25000_result.root");

   //==============================================Work Space========================================================

   //===========================================Part 1: Plot=================================================== 

   //  ---------------------------------------------------------------------------------------------------- 
 
   for (Int_t i = 0 ; i < 17 ; i ++ ) {   // index for Selection Cut   

       stringstream ss;
       ss<<i;
       for (Int_t i_stack = 0 ; i_stack < 9 ; i_stack++) {
            stringstream ss2;
            ss2<<i_stack;
            string str_can = Canvas+ss2.str();
            string str_stk = Stk+ss2.str();
            //cout << str_stk << endl;
            can[i_stack] = new TCanvas(str_can.c_str(),str_can.c_str(),can_w,can_h);
            can[i_stack]->SetCanvasSize(can_w,can_h);
            can[i_stack]->SetLogy();
            //can[i_stack]->SetGrid();
            Stack[i_stack] = new THStack(str_stk.c_str(),""); 
            //Stack[i_stack] = new THStack("Stack",""); 
       }

       for (Int_t i_main = 0 ;i_main<16;i_main++ ) {   // index for open each file

         Entry[i_main]=(TH1F*)f[i_main]->Get("Select_MET_0");
         factor = NormLumi*xsecwzjet[i_main]*1000.f/Entry[i_main]->GetEntries();//GetSumOfWeights();
         cout << "Number: " << i_main << " xsec: " << xsecwzjet[i_main] << " factor: " << factor << " Entry: " << Entry[i_main]->GetEntries() << endl;
         for (Int_t i_hist = 0 ; i_hist < 9 ; i_hist++){
            str[i_hist]  = selec+phys[i_hist]+ss.str();
            str2[i_hist] = selec2+phys[i_hist]+ss.str();
            HistPlot[i_main][i_hist]    = new TH1F(str2[i_hist].c_str(),phys[i_hist].c_str(), bin[i_hist], min[i_hist], max[i_hist]);
            bg[i_main]=(TH1F*)f[i_main]->Get(str[i_hist].c_str());
            HistPlot[i_main][i_hist]->Add(bg[i_main],factor);
            //HistPlot[i_main][i_hist]->Draw();

            //Set color
            if (i_main <  5){
                HistPlot[i_main][i_hist]->SetLineColor(604-i_main);
                HistPlot[i_main][i_hist]->SetFillColor(604-i_main);
            } else if (i_main < 9) {
                HistPlot[i_main][i_hist]->SetLineColor(640-i_main);
                HistPlot[i_main][i_hist]->SetFillColor(640-i_main);
            } else if (i_main < 13) {
                HistPlot[i_main][i_hist]->SetLineColor(428-i_main);
                HistPlot[i_main][i_hist]->SetFillColor(428-i_main);
            } else {
                HistPlot[i_main][i_hist]->SetLineColor(632-i_main);
                HistPlot[i_main][i_hist]->SetFillColor(632-i_main);
            }
            // Rebinning
            if (i_hist == 0 || i_hist == 1 ||i_hist == 2 || i_hist == 7 ) {// Rebin PT and MET
                HistPlot[i_main][i_hist]->Rebin(rebin_pt);
            }  

            if (i_hist == 3 || i_hist == 4 || i_hist == 8 ) {// Rebin Eta
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




       gStyle->SetOptStat(0); 
       gStyle->SetOptTitle(0);
       gStyle->SetLegendBorderSize(0); 


       // Plot Parameters
       leg = new TLegend(0.50,0.35,0.8,0.8);
       leg->SetHeader("#splitline{#sqrt{s} = 100 TeV, #int L dt = 1 fb^{-1}}{W^{#pm}/Z^{0} + Jets}");
       //leg->SetHeader("#sqrt{s} = 100 TeV, #int L dt = 10 pb^{-1}");
       leg->AddEntry(HistPlot[0][0] ," ","");
       leg->AddEntry(HistPlot[0][0] ," ","");
       leg->AddEntry(HistPlot[0][0] ,"HTBin 50#rightarrow100     ","f");
       leg->AddEntry(HistPlot[1][0] ,"HTBin 100#rightarrow200    ","f");
       leg->AddEntry(HistPlot[2][0] ,"HTBin 200#rightarrow400    ","f");
       leg->AddEntry(HistPlot[3][0] ,"HTBin 400#rightarrow600    ","f");
       leg->AddEntry(HistPlot[4][0] ,"HTBin 600#rightarrow800    ","f");
       leg->AddEntry(HistPlot[5][0] ,"HTBin 800#rightarrow1000   ","f");
       leg->AddEntry(HistPlot[6][0] ,"HTBin 1000#rightarrow1500  ","f");
       leg->AddEntry(HistPlot[7][0] ,"HTBin 1500#rightarrow2000  ","f");
       leg->AddEntry(HistPlot[8][0] ,"HTBin 2000#rightarrow2500  ","f");
       leg->AddEntry(HistPlot[9][0] ,"HTBin 2500#rightarrow3000  ","f");
       leg->AddEntry(HistPlot[10][0],"HTBin 3000#rightarrow4000  ","f");
       leg->AddEntry(HistPlot[11][0],"HTBin 4000#rightarrow5000  ","f");
       leg->AddEntry(HistPlot[12][0],"HTBin 5000#rightarrow10000 ","f");
       leg->AddEntry(HistPlot[13][0],"HTBin 10000#rightarrow15000","f");
       leg->AddEntry(HistPlot[14][0],"HTBin 15000#rightarrow20000","f");
       leg->AddEntry(HistPlot[15][0],"HTBin 20000#rightarrow25000","f");
       //leg->SetFillColorAlpha(0,0);
       TLegendEntry *header = (TLegendEntry*)leg->GetListOfPrimitives()->First();
       //header->SetTextAlign(22);
       //header->SetTextColor(2);
       header->SetTextSize(0.03);

       //Draw an axis on the right side
       //TGaxis *A1 = new TGaxis(0,5e9,6000,5e9,"",510,"-");



       // MET

       can[0]->cd();
       Stack[0]->Draw();
       Stack[0]->GetXaxis()->SetTitle("E^{Miss}_{T} [GeV]");
       Stack[0]->GetYaxis()->SetTitle("Events/10 GeV");
       Stack[0]->GetYaxis()->SetTitleOffset(1.25);
       Stack[0]->GetXaxis()->SetRangeUser(0,15000);
       Stack[0]->SetMinimum(0.03);
       Stack[0]->Draw();
       leg->Draw("same");
 
       // Jet1 Pt
       can[1]->cd();
       Stack[1]->Draw();
       Stack[1]->GetXaxis()->SetTitle("P_{T} Jet_{1} [GeV/c]");
       Stack[1]->GetYaxis()->SetTitle("Events/10 GeV");
       Stack[1]->GetYaxis()->SetTitleOffset(1.25);
       Stack[1]->GetXaxis()->SetRangeUser(0,15000);
       Stack[1]->SetMinimum(0.03);
       Stack[1]->Draw();
       leg->Draw("same");


       // Jet2 Pt
       can[2]->cd();
       Stack[2]->Draw();
       Stack[2]->GetXaxis()->SetTitle("P_{T} Jet_{2} [GeV/c]");
       Stack[2]->GetYaxis()->SetTitle("Events/10 GeV");
       Stack[2]->GetYaxis()->SetTitleOffset(1.25);
       Stack[2]->GetXaxis()->SetRangeUser(0,15000);
       Stack[2]->SetMinimum(0.03);
       Stack[2]->Draw();
       leg->Draw("same");

       
       // Jet1 Eta
       can[3]->cd();
       Stack[3]->Draw();
       Stack[3]->GetXaxis()->SetTitle("#eta Jet_{1} ");
       Stack[3]->GetYaxis()->SetTitle("Events/0.01 ");
       Stack[3]->GetYaxis()->SetTitleOffset(1.25);
       Stack[3]->GetXaxis()->SetRangeUser(-5,5);
       Stack[3]->SetMinimum(0.3);
       Stack[3]->SetMaximum(10e8);
       Stack[3]->Draw();
       //leg->Draw("same");
       
       
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
       //leg->Draw("same");
       
       // JetDelPhi
       can[5]->cd();
       Stack[5]->Draw();
       Stack[5]->GetXaxis()->SetTitle("#Delta#phi Jet_{1,2}");
       Stack[5]->GetYaxis()->SetTitle("Events/0.1 ");
       Stack[5]->GetYaxis()->SetTitleOffset(1.25);
       Stack[5]->GetXaxis()->SetRangeUser(0,6.4);
       Stack[5]->SetMinimum(0.3);
       Stack[5]->SetMaximum(10e8);
       Stack[5]->Draw();
       //leg->Draw("same");
       
       // JetMulti
       can[6]->cd();
       Stack[6]->Draw();
       Stack[6]->GetXaxis()->SetTitle("Jet Multiplicity");
       Stack[6]->GetYaxis()->SetTitle("Events ");
       Stack[6]->GetYaxis()->SetTitleOffset(1.25);
       Stack[6]->GetXaxis()->SetRangeUser(0,20);
       Stack[6]->SetMinimum(0.3);
       Stack[6]->SetMaximum(10e9);
       Stack[6]->Draw();
       //leg->Draw("same");
       
       // Jet Pt
       can[7]->cd();
       Stack[7]->Draw();
       Stack[7]->GetXaxis()->SetTitle("P_{T} Jet [GeV/c]");
       Stack[7]->GetYaxis()->SetTitle("Events/10 GeV");
       Stack[7]->GetYaxis()->SetTitleOffset(1.25);
       Stack[7]->GetXaxis()->SetRangeUser(0,15000);
       Stack[7]->SetMinimum(0.03);
       Stack[7]->Draw();
       leg->Draw("same");

       
       // Jet Eta
       can[8]->cd();
       Stack[8]->Draw();
       Stack[8]->GetXaxis()->SetTitle("#eta Jet [GeV/c]");
       Stack[8]->GetYaxis()->SetTitle("Events/0.1 ");
       Stack[8]->GetYaxis()->SetTitleOffset(1.25);
       Stack[8]->GetXaxis()->SetRangeUser(-5,5);
       Stack[8]->SetMinimum(0.3);
       Stack[8]->SetMaximum(10e8);
       Stack[8]->Draw();
       //leg->Draw("same");
       
       // Save
       for (Int_t i_hist = 0; i_hist<9 ; i_hist++){ 
            saveAll = str[i_hist]+".pdf";
            can[i_hist]->SaveAs(saveAll.c_str());
            delete can[i_hist];
       }
   }
}
