// Plot 1 File
// Written by Surapat EK-IN 
// Date: 22-2-2016
// Update:
//
//
//

void Plot_Matching(const char* Input1) {

    // Load root file
    TFile* file = new TFile(Input1,"READ");

    // Save to root file
    //TFile* f_save = new TFile(Output,"RECREATE");

    // Declear variables for Histograms
    TCanvas* canvas[16][15];
    TH1F* HistPlot[16][15]; 
    TH1F* HistPlot2[16][15]; 
    TGraph* Graph[15];
    //TH1F* Hist_Get;

    // Declear Variables for plot
    Float_t can_w    =   800 ;  // Canvas size 
    Float_t can_h    =   800 ;
    Int_t rebin_pt     = 10;
    Int_t rebin_eta    = 20;
    Int_t rebin_delphi = 2;
    string str_can; 
    string str_get;
    string str_plot;
    string str_plot2;
    string str_pad[2];

    // Chi2 Test part 
    const Int_t n = 100;
    Double_t res[n];

    // Plot compare part
    Float_t data1[100], data2[100];
    Float_t dataX[100];
    TPad* pad[16][15][2];
    Double_t xlow  = 0.000;
    Double_t ylow  = 0.020;
    Double_t xup   = 1.000;
    Double_t yup   = 1.000;
    Double_t xdef  = 1.000; // No define and no use
    Double_t ydef  = 0.265;

    // =======================================================String Part==============================================
    string selec  = "Select";
    string selec2 = "Plot_Select";
    string selec3 = "Plot2_Select";
    string Canvas = "Canvas";
    string Pad    = "Pad";
    string phys[] = {"_MET_","_Jet1_Pt_","_Jet2_Pt_","_Jet1_Eta_","_Jet2_Eta_","_Jetdel_Phi_","_Jet_Multi_" ,"_Jet_Pt_","_Jet_Eta_"  ,"_Elec_Pt_",      "_Elec_Eta_"  ,"_Muon_Pt_","_Muon_Eta_"  ,"_tau_Pt_","_tau_Eta_"  };  
    Int_t   bin[] = {    3000 , 3000       , 3000       ,   1000     ,      1000  ,    64        ,   20     , 3000     , 1000        , 3000     ,       1000        , 3000     , 1000        , 3000     , 1000        };
    Double_t min[] = {    0.0 ,   0.0      ,   0.0      ,  -5.0      ,      -5.0  ,     0.       ,    0     ,   0.0    , -5.0        ,   0.0    , -5.   0        ,   0.0    , -5.0        ,   0.0    , -5.0        };
    Double_t max[] = { 30000.0, 30000.0    , 30000.0    ,   5.0      ,       5.0  ,   6.4        ,   20     , 30000.0  ,  5.0        , 30000.0  ,  5.   0        , 30000.0  ,  5.0        , 30000.0  ,  5.0        };


    //=================================================================================================================

    for (Int_t i_main = 0 ; i_main < 1 ; i_main++){   // Index for Selection Cut  Max-> 16
    
        stringstream ss;
        ss<<i_main; 

        for (Int_t i_hist = 0  ; i_hist < 15 ; i_hist++) {  // Index for Histogram   Max-> 15
            // String -> Get data and define canvas 
            str_can  = Canvas+phys[i_hist]+ss.str();
            str_get  =  selec+phys[i_hist]+ss.str(); 
            str_plot = selec2+phys[i_hist]+ss.str(); 
            str_plot2= selec3+phys[i_hist]+ss.str(); 

            str_pad[0] = Pad+phys[i_hist]+ss.str()+"0";
            str_pad[1] = Pad+phys[i_hist]+ss.str()+"1";

            // Canvas
            canvas[i_main][i_hist] = new TCanvas(str_can.c_str(),str_can.c_str(), can_w, can_h); 
            canvas[i_main][i_hist]->SetCanvasSize(can_w,can_h);

            // Pad
            pad[i_main][i_hist][0] = new TPad(str_pad[0].c_str(), str_pad[0].c_str(), xlow, ydef, xup, yup); // Upper 
            pad[i_main][i_hist][0]->SetLogy();
            pad[i_main][i_hist][0]->SetGridx();
            pad[i_main][i_hist][0]->SetGridy();
            pad[i_main][i_hist][1] = new TPad(str_pad[1].c_str(), str_pad[1].c_str(), xlow, ylow, xup, ydef+0.025); // Lower 
            //pad[i_main][i_hist][1]->SetLogy();
            pad[i_main][i_hist][1]->SetGridx();
            pad[i_main][i_hist][1]->SetGridy();

            // Histograms 
            HistPlot[i_main][i_hist]  = new TH1F(str_plot.c_str(), str_plot.c_str(), bin[i_hist], min[i_hist], max[i_hist]);
            HistPlot2[i_main][i_hist] = new TH1F(str_plot2.c_str(), str_plot2.c_str(), bin[i_hist], min[i_hist], max[i_hist]);
            //HistPlot[i_main][i_hist]->Add(Hist_Get);
            //Hist_Get = (TH1F*)f1->Get(str_get.c_str());
            HistPlot[i_main][i_hist]  = (TH1F*)file_0->Get(str_get.c_str());
            //cout << "TEST" << endl;
            HistPlot2[i_main][i_hist] = (TH1F*)file_1->Get(str_get.c_str());

            // Set Histogram 1
            HistPlot[i_main][i_hist]->SetLineColor(kBlack);
            HistPlot[i_main][i_hist]->SetFillColor(kYellow);

            // Set Histogram 2
            HistPlot2[i_main][i_hist]->SetMarkerStyle(20);
            //HistPlot2[i_main][i_hist]->Set

            // Rebinning

            if (i_hist == 0 || i_hist == 1 ||i_hist == 2 || i_hist == 7 || i_hist == 9 || i_hist == 11 || i_hist == 13 ) {// Rebin PT and MET
                HistPlot[i_main][i_hist]->Rebin(rebin_pt);
                HistPlot2[i_main][i_hist]->Rebin(rebin_pt);
            }   

            if (i_hist == 3 || i_hist == 4 || i_hist == 8 || i_hist == 10 || i_hist == 12 || i_hist == 14 ) {// Rebin Eta
                HistPlot[i_main][i_hist]->Rebin(rebin_eta); 
                HistPlot2[i_main][i_hist]->Rebin(rebin_eta); 
            }   
        
            if (i_hist == 5 ) {// Rebin DelPhi
                HistPlot[i_main][i_hist]->Rebin(rebin_delphi);
                HistPlot2[i_main][i_hist]->Rebin(rebin_delphi);
            }   
 
        } // Histogram

        gStyle->SetOptFit(111111);
        gStyle->SetOptStat(0);
        gStyle->SetOptTitle(0);
        gStyle->SetLegendBorderSize(1);

        // Legend
        TLegend *leg = new TLegend(0.69,0.74,0.89,0.89);

        //leg->SetHeader("");
        leg->AddEntry(HistPlot[i_main][0]  , "HEPSIM"  , "f");
        leg->AddEntry(HistPlot2[i_main][0] , "Data"  , "lep");

        // MET
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 20 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][0]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][0]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][0]->GetBinCenter(i_get+1);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][0]->GetXaxis()->SetRangeUser(0,1900);
        HistPlot2[i_main][0]->GetXaxis()->SetRangeUser(0,1900);
        HistPlot[i_main][0]->Chi2Test(HistPlot2[i_main][0],"UU P",res);

            // Plot part
            // Plot Hist
        canvas[i_main][0]->cd();
        pad[i_main][0][0]->Draw();
        pad[i_main][0][1]->Draw();

        pad[i_main][0][0]->cd();
        //TPaveText *textMET = new TPaveText(0.55,0.65,0.85,0.82);
        //textMET->AddText("TEST TEST");
        HistPlot[i_main][0]->Draw();
        HistPlot[i_main][0]->GetXaxis()->SetTitle("E^{Miss}_{T} [GeV]");
        HistPlot[i_main][0]->GetXaxis()->SetRangeUser(0,2000);
        HistPlot[i_main][0]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][0]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][0]->GetYaxis()->SetTitle("Events/100 GeV");
        HistPlot[i_main][0]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][0]->SetMinimum(0.3);
        HistPlot[i_main][0]->SetMaximum(10e4);
        HistPlot[i_main][0]->Draw();
        HistPlot2[i_main][0]->GetXaxis()->SetRangeUser(0,2000);
        HistPlot2[i_main][0]->Draw("E same");
        leg->Draw("same");
        //textMET->Draw("same");

            // Plot Compare Graph
        pad[i_main][0][1]->cd();
        Graph[0] = new TGraph(20, dataX, data2);
        Graph[0]->SetMarkerStyle(20);
        Graph[0]->GetXaxis()->SetTitle("E^{Miss}_{T} [GeV]");
        Graph[0]->GetXaxis()->SetTitleOffset(1.05);
        Graph[0]->GetXaxis()->SetTitleSize(0.045);
        Graph[0]->GetXaxis()->SetLabelSize(0.05);
        Graph[0]->GetXaxis()->SetRangeUser(0,1950);
        Graph[0]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[0]->GetYaxis()->SetTitleOffset(0.5);
        Graph[0]->GetYaxis()->SetTitleSize(0.06);
        Graph[0]->GetYaxis()->SetLabelSize(0.06);
        Graph[0]->SetMinimum(-2.2);
        Graph[0]->SetMaximum(2.2);
        Graph[0]->Draw("ALP");

        // Jet 1 pt 
        canvas[i_main][1]->cd();
        pad[i_main][1][0]->Draw();
        pad[i_main][1][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 35 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][1]->GetBinContent(i_get+2);        
            data2[i_get] = HistPlot2[i_main][1]->GetBinContent(i_get+2);        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][1]->GetBinCenter(i_get+2);
        }
            // Chi square part
        HistPlot[i_main][1]->GetXaxis()->SetRangeUser(0,3500);
        HistPlot2[i_main][1]->GetXaxis()->SetRangeUser(0,3500);
        HistPlot[i_main][1]->Chi2Test(HistPlot2[i_main][1],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][1][0]->cd();
        HistPlot[i_main][1]->GetXaxis()->SetTitle("P_{T} Jet_{1} [GeV/c]");
        HistPlot[i_main][1]->GetXaxis()->SetRangeUser(0,3500);
        HistPlot[i_main][1]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][1]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][1]->GetYaxis()->SetTitle("Events/100 GeV");
        HistPlot[i_main][1]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][1]->SetMinimum(0.3);
        HistPlot[i_main][1]->SetMaximum(10e4);
        HistPlot[i_main][1]->Draw();
        HistPlot2[i_main][1]->GetXaxis()->SetRangeUser(0,3500);
        HistPlot2[i_main][1]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][1][1]->cd();
        Graph[1] = new TGraph(34, dataX, data2);
        Graph[1]->SetMarkerStyle(20);
        Graph[1]->GetXaxis()->SetTitle("P_{T} Jet_{1} [GeV/c]");
        Graph[1]->GetXaxis()->SetTitleOffset(1.05);
        Graph[1]->GetXaxis()->SetTitleSize(0.045);
        Graph[1]->GetXaxis()->SetLabelSize(0.05);
        Graph[1]->GetXaxis()->SetRangeUser(0,3550);
        Graph[1]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[1]->GetYaxis()->SetTitleOffset(0.5);
        Graph[1]->GetYaxis()->SetTitleSize(0.06);
        Graph[1]->GetYaxis()->SetLabelSize(0.06);
        Graph[1]->SetMinimum(-.7);
        Graph[1]->SetMaximum(.7);
        Graph[1]->Draw("ALP");

        // Jet 2 pt 
        canvas[i_main][2]->cd();
        pad[i_main][2][0]->Draw();
        pad[i_main][2][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 30 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][2]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][2]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][2]->GetBinCenter(i_get+1);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][2]->GetXaxis()->SetRangeUser(0,2900);
        HistPlot2[i_main][2]->GetXaxis()->SetRangeUser(0,2900);
        HistPlot[i_main][2]->Chi2Test(HistPlot2[i_main][2],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][2][0]->cd();
        HistPlot[i_main][2]->GetXaxis()->SetTitle("P_{T} Jet_{2} [GeV/c]");
        HistPlot[i_main][2]->GetXaxis()->SetRangeUser(0,3000);
        HistPlot[i_main][2]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][2]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][2]->GetYaxis()->SetTitle("Events/100 GeV");
        HistPlot[i_main][2]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][2]->SetMinimum(0.3);
        HistPlot[i_main][2]->SetMaximum(10e4);
        HistPlot[i_main][2]->Draw();
        HistPlot2[i_main][2]->GetXaxis()->SetRangeUser(0,3000);
        HistPlot2[i_main][2]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][2][1]->cd();
        Graph[2] = new TGraph(30, dataX, data2);
        Graph[2]->SetMarkerStyle(20);
        Graph[2]->GetXaxis()->SetTitle("P_{T} Jet_{2} [GeV/c]");
        Graph[2]->GetXaxis()->SetTitleOffset(1.05);
        Graph[2]->GetXaxis()->SetTitleSize(0.045);
        Graph[2]->GetXaxis()->SetLabelSize(0.05);
        Graph[2]->GetXaxis()->SetRangeUser(0,3000);
        Graph[2]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[2]->GetYaxis()->SetTitleOffset(0.5);
        Graph[2]->GetYaxis()->SetTitleSize(0.06);
        Graph[2]->GetYaxis()->SetLabelSize(0.06);
        Graph[2]->SetMinimum(-1.2);
        Graph[2]->SetMaximum(1.2);
        Graph[2]->Draw("ALP");

        // Jet 1 Eta 
        canvas[i_main][3]->cd();
        pad[i_main][3][0]->Draw();
        pad[i_main][3][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 42 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][3]->GetBinContent(i_get+5);        
            data2[i_get] = HistPlot2[i_main][3]->GetBinContent(i_get+5);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][3]->GetBinCenter(i_get+5);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][3]->GetXaxis()->SetRangeUser(-4.,3.8);
        HistPlot2[i_main][3]->GetXaxis()->SetRangeUser(-4.,3.8);
        HistPlot[i_main][3]->Chi2Test(HistPlot2[i_main][3],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][3][0]->cd();
        HistPlot[i_main][3]->GetXaxis()->SetTitle("#eta Jet_{1}");
        HistPlot[i_main][3]->GetXaxis()->SetRangeUser(-4.5,4.5);
        HistPlot[i_main][3]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][3]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][3]->GetYaxis()->SetTitle("Events/0.2");
        HistPlot[i_main][3]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][3]->SetMinimum(0.3);
        HistPlot[i_main][3]->SetMaximum(10e4);
        HistPlot[i_main][3]->Draw();
        HistPlot2[i_main][3]->GetXaxis()->SetRangeUser(-5,5);
        HistPlot2[i_main][3]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][3][1]->cd();
        Graph[3] = new TGraph(41, dataX, data2);
        Graph[3]->SetMarkerStyle(20);
        Graph[3]->GetXaxis()->SetTitle("#eta Jet_{1}");
        Graph[3]->GetXaxis()->SetTitleOffset(1.05);
        Graph[3]->GetXaxis()->SetTitleSize(0.045);
        Graph[3]->GetXaxis()->SetLabelSize(0.05);
        Graph[3]->GetXaxis()->SetRangeUser(-4.5,4.5);
        Graph[3]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[3]->GetYaxis()->SetTitleOffset(0.5);
        Graph[3]->GetYaxis()->SetTitleSize(0.06);
        Graph[3]->GetYaxis()->SetLabelSize(0.06);
        Graph[3]->SetMinimum(-.5);
        Graph[3]->SetMaximum(.5);
        Graph[3]->Draw("ALP");

        // Jet 2 Eta 
        canvas[i_main][4]->cd();
        pad[i_main][4][0]->Draw();
        pad[i_main][4][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 46 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][4]->GetBinContent(i_get+3);        
            data2[i_get] = HistPlot2[i_main][4]->GetBinContent(i_get+3);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][4]->GetBinCenter(i_get+3);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][4]->GetXaxis()->SetRangeUser(-4.4,4.4);
        HistPlot2[i_main][4]->GetXaxis()->SetRangeUser(-4.4,4.4);
        HistPlot[i_main][4]->Chi2Test(HistPlot2[i_main][4],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][4][0]->cd();
        HistPlot[i_main][4]->GetXaxis()->SetTitle("#eta Jet_{2}");
        HistPlot[i_main][4]->GetXaxis()->SetRangeUser(-4.6,4.6);
        HistPlot[i_main][4]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][4]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][4]->GetYaxis()->SetTitle("Events/0.2");
        HistPlot[i_main][4]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][4]->SetMinimum(0.3);
        HistPlot[i_main][4]->SetMaximum(10e4);
        HistPlot[i_main][4]->Draw();
        HistPlot2[i_main][4]->GetXaxis()->SetRangeUser(-5,5);
        HistPlot2[i_main][4]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][4][1]->cd();
        Graph[4] = new TGraph(46, dataX, data2);
        Graph[4]->SetMarkerStyle(20);
        Graph[4]->GetXaxis()->SetTitle("#eta Jet_{2}");
        Graph[4]->GetXaxis()->SetTitleOffset(1.05);
        Graph[4]->GetXaxis()->SetTitleSize(0.045);
        Graph[4]->GetXaxis()->SetLabelSize(0.05);
        Graph[4]->GetXaxis()->SetRangeUser(-4.8,4.8);
        Graph[4]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[4]->GetYaxis()->SetTitleOffset(0.5);
        Graph[4]->GetYaxis()->SetTitleSize(0.06);
        Graph[4]->GetYaxis()->SetLabelSize(0.06);
        Graph[4]->SetMinimum(-1.);
        Graph[4]->SetMaximum(1.);
        Graph[4]->Draw("ALP");

        // Jet Delta Phi 
        canvas[i_main][5]->cd();
        pad[i_main][5][0]->Draw();
        pad[i_main][5][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 16 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][5]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][5]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][5]->GetBinCenter(i_get+1);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][5]->GetXaxis()->SetRangeUser(.0,3.0);
        HistPlot2[i_main][5]->GetXaxis()->SetRangeUser(.0,3.0);
        HistPlot[i_main][5]->Chi2Test(HistPlot2[i_main][5],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][5][0]->cd();
        HistPlot[i_main][5]->GetXaxis()->SetTitle("#Delta#phi");
        HistPlot[i_main][5]->GetXaxis()->SetRangeUser(.0,3.4);
        HistPlot[i_main][5]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][5]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][5]->GetYaxis()->SetTitle("Events/0.2");
        HistPlot[i_main][5]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][5]->SetMinimum(0.3);
        HistPlot[i_main][5]->SetMaximum(10e5);
        HistPlot[i_main][5]->Draw();
        HistPlot2[i_main][5]->GetXaxis()->SetRangeUser(0.,3.4);
        HistPlot2[i_main][5]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][5][1]->cd();
        Graph[5] = new TGraph(16, dataX, data2);
        Graph[5]->SetMarkerStyle(20);
        Graph[5]->GetXaxis()->SetTitle("#Delta#phi");
        Graph[5]->GetXaxis()->SetTitleOffset(.9);
        Graph[5]->GetXaxis()->SetTitleSize(0.055);
        Graph[5]->GetXaxis()->SetLabelSize(0.05);
        Graph[5]->GetXaxis()->SetRangeUser(0.,3.3);
        Graph[5]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[5]->GetYaxis()->SetTitleOffset(0.5);
        Graph[5]->GetYaxis()->SetTitleSize(0.06);
        Graph[5]->GetYaxis()->SetLabelSize(0.06);
        Graph[5]->SetMinimum(-.4);
        Graph[5]->SetMaximum(.4);
        Graph[5]->Draw("ALP");

        // Jet Multiplicity
        canvas[i_main][6]->cd();
        pad[i_main][6][0]->Draw();
        pad[i_main][6][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 16 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][6]->GetBinContent(i_get+2);        
            data2[i_get] = HistPlot2[i_main][6]->GetBinContent(i_get+2);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][6]->GetBinCenter(i_get+2);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][6]->GetXaxis()->SetRangeUser(1,17);
        HistPlot2[i_main][6]->GetXaxis()->SetRangeUser(1,17);
        HistPlot[i_main][6]->Chi2Test(HistPlot2[i_main][6],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][6][0]->cd();
        HistPlot[i_main][6]->GetXaxis()->SetTitle("Jet Multiplicity");
        HistPlot[i_main][6]->GetXaxis()->SetRangeUser(.0,19);
        HistPlot[i_main][6]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][6]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][6]->GetYaxis()->SetTitle("Events");
        HistPlot[i_main][6]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][6]->SetMinimum(0.3);
        HistPlot[i_main][6]->SetMaximum(10e4);
        HistPlot[i_main][6]->Draw();
        HistPlot2[i_main][6]->GetXaxis()->SetRangeUser(0,19);
        HistPlot2[i_main][6]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][6][1]->cd();
        Graph[6] = new TGraph(16, dataX, data2);
        Graph[6]->SetMarkerStyle(20);
        Graph[6]->GetXaxis()->SetTitle("Jet Multiplicity");
        Graph[6]->GetXaxis()->SetTitleOffset(.9);
        Graph[6]->GetXaxis()->SetTitleSize(0.055);
        Graph[6]->GetXaxis()->SetLabelSize(0.05);
        Graph[6]->GetXaxis()->SetRangeUser(0.,19);
        Graph[6]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[6]->GetYaxis()->SetTitleOffset(0.5);
        Graph[6]->GetYaxis()->SetTitleSize(0.06);
        Graph[6]->GetYaxis()->SetLabelSize(0.06);
        Graph[6]->SetMinimum(-1.2);
        Graph[6]->SetMaximum(1.2);
        Graph[6]->Draw("ALP");

        // Jet PT 
        canvas[i_main][7]->cd();
        pad[i_main][7][0]->Draw();
        pad[i_main][7][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 35 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][7]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][7]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][7]->GetBinCenter(i_get+1);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][7]->GetXaxis()->SetRangeUser(0,3500);
        HistPlot2[i_main][7]->GetXaxis()->SetRangeUser(0,3500);
        HistPlot[i_main][7]->Chi2Test(HistPlot2[i_main][7],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][7][0]->cd();
        HistPlot[i_main][7]->GetXaxis()->SetTitle("P_{T} Jet [GeV/c]");
        HistPlot[i_main][7]->GetXaxis()->SetRangeUser(.0,3500);
        HistPlot[i_main][7]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][7]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][7]->GetYaxis()->SetTitle("Events/100");
        HistPlot[i_main][7]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][7]->SetMinimum(0.3);
        HistPlot[i_main][7]->SetMaximum(10e4);
        HistPlot[i_main][7]->Draw();
        HistPlot2[i_main][7]->GetXaxis()->SetRangeUser(0,3500);
        HistPlot2[i_main][7]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][7][1]->cd();
        Graph[7] = new TGraph(35, dataX, data2);
        Graph[7]->SetMarkerStyle(20);
        Graph[7]->GetXaxis()->SetTitle("P_{T} Jet [GeV/c]");
        Graph[7]->GetXaxis()->SetTitleOffset(.9);
        Graph[7]->GetXaxis()->SetTitleSize(0.055);
        Graph[7]->GetXaxis()->SetLabelSize(0.05);
        Graph[7]->GetXaxis()->SetRangeUser(0.,3500);
        Graph[7]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[7]->GetYaxis()->SetTitleOffset(0.5);
        Graph[7]->GetYaxis()->SetTitleSize(0.06);
        Graph[7]->GetYaxis()->SetLabelSize(0.06);
        Graph[7]->SetMinimum(-1.2);
        Graph[7]->SetMaximum(1.2);
        Graph[7]->Draw("ALP");

        // Jet Eta 
        canvas[i_main][8]->cd();
        pad[i_main][8][0]->Draw();
        pad[i_main][8][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 46 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][8]->GetBinContent(i_get+3);        
            data2[i_get] = HistPlot2[i_main][8]->GetBinContent(i_get+3);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][8]->GetBinCenter(i_get+3);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][8]->GetXaxis()->SetRangeUser(-4.4,4.4);
        HistPlot2[i_main][8]->GetXaxis()->SetRangeUser(-4.4,4.4);
        HistPlot[i_main][8]->Chi2Test(HistPlot2[i_main][8],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][8][0]->cd();
        HistPlot[i_main][8]->GetXaxis()->SetTitle("#eta Jet");
        HistPlot[i_main][8]->GetXaxis()->SetRangeUser(-4.8,4.8);
        HistPlot[i_main][8]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][8]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][8]->GetYaxis()->SetTitle("Events/0.2");
        HistPlot[i_main][8]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][8]->SetMinimum(0.3);
        HistPlot[i_main][8]->SetMaximum(10e4);
        HistPlot[i_main][8]->Draw();
        HistPlot2[i_main][8]->GetXaxis()->SetRangeUser(-5,5);
        HistPlot2[i_main][8]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][8][1]->cd();
        Graph[8] = new TGraph(46, dataX, data2);
        Graph[8]->SetMarkerStyle(20);
        Graph[8]->GetXaxis()->SetTitle("#eta Jet");
        Graph[8]->GetXaxis()->SetTitleOffset(1.05);
        Graph[8]->GetXaxis()->SetTitleSize(0.045);
        Graph[8]->GetXaxis()->SetLabelSize(0.05);
        Graph[8]->GetXaxis()->SetRangeUser(-4.8,4.8);
        Graph[8]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[8]->GetYaxis()->SetTitleOffset(0.5);
        Graph[8]->GetYaxis()->SetTitleSize(0.06);
        Graph[8]->GetYaxis()->SetLabelSize(0.06);
        Graph[8]->SetMinimum(-1.);
        Graph[8]->SetMaximum(1.);
        Graph[8]->Draw("ALP");

        // Elec PT 
        canvas[i_main][9]->cd();
        pad[i_main][9][0]->Draw();
        pad[i_main][9][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 13 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][9]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][9]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][9]->GetBinCenter(i_get+1);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][9]->GetXaxis()->SetRangeUser(0,1300);
        HistPlot2[i_main][9]->GetXaxis()->SetRangeUser(0,1300);
        HistPlot[i_main][9]->Chi2Test(HistPlot2[i_main][9],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][9][0]->cd();
        HistPlot[i_main][9]->GetXaxis()->SetTitle("P_{T} Electron [GeV/c]");
        HistPlot[i_main][9]->GetXaxis()->SetRangeUser(.0,1300);
        HistPlot[i_main][9]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][9]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][9]->GetYaxis()->SetTitle("Events/100");
        HistPlot[i_main][9]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][9]->SetMinimum(0.3);
        HistPlot[i_main][9]->SetMaximum(10e4);
        HistPlot[i_main][9]->Draw();
        HistPlot2[i_main][9]->GetXaxis()->SetRangeUser(0,1300);
        HistPlot2[i_main][9]->Draw("E same");
        leg->Draw("same");


            // Plot Compare Graph
        pad[i_main][9][1]->cd();
        Graph[9] = new TGraph(13, dataX, data2);
        Graph[9]->SetMarkerStyle(20);
        Graph[9]->GetXaxis()->SetTitle("P_{T} Electron [GeV/c]");
        Graph[9]->GetXaxis()->SetTitleOffset(.9);
        Graph[9]->GetXaxis()->SetTitleSize(0.055);
        Graph[9]->GetXaxis()->SetLabelSize(0.05);
        Graph[9]->GetXaxis()->SetRangeUser(0.,1300);
        Graph[9]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[9]->GetYaxis()->SetTitleOffset(0.5);
        Graph[9]->GetYaxis()->SetTitleSize(0.06);
        Graph[9]->GetYaxis()->SetLabelSize(0.06);
        Graph[9]->SetMinimum(-2.);
        Graph[9]->SetMaximum(2.);
        Graph[9]->Draw("ALP");
        canvas[i_main][9]->SaveAs("Elec_PT.pdf");

        // Elec Eta 
        canvas[i_main][10]->cd();
        pad[i_main][10][0]->Draw();
        pad[i_main][10][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 50 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][10]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][10]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][10]->GetBinCenter(i_get+1);
            if (data1[i_get]==0) {data2[i_get]=0.;}
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][10]->GetXaxis()->SetRangeUser(-5.0,4.8);
        HistPlot2[i_main][10]->GetXaxis()->SetRangeUser(-5.0,4.8);
        HistPlot[i_main][10]->Chi2Test(HistPlot2[i_main][10],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][10][0]->cd();
        HistPlot[i_main][10]->GetXaxis()->SetTitle("#eta Electron");
        HistPlot[i_main][10]->GetXaxis()->SetRangeUser(-5.0,5.0);
        HistPlot[i_main][10]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][10]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][10]->GetYaxis()->SetTitle("Events/0.2");
        HistPlot[i_main][10]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][10]->SetMinimum(0.3);
        HistPlot[i_main][10]->SetMaximum(10e4);
        HistPlot[i_main][10]->Draw();
        HistPlot2[i_main][10]->GetXaxis()->SetRangeUser(-5,5);
        HistPlot2[i_main][10]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][10][1]->cd();
        Graph[10] = new TGraph(50, dataX, data2);
        Graph[10]->SetMarkerStyle(20);
        Graph[10]->GetXaxis()->SetTitle("#eta Electron");
        Graph[10]->GetXaxis()->SetTitleOffset(1.05);
        Graph[10]->GetXaxis()->SetTitleSize(0.045);
        Graph[10]->GetXaxis()->SetLabelSize(0.05);
        Graph[10]->GetXaxis()->SetRangeUser(-5.0,5.0);
        Graph[10]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[10]->GetYaxis()->SetTitleOffset(0.5);
        Graph[10]->GetYaxis()->SetTitleSize(0.06);
        Graph[10]->GetYaxis()->SetLabelSize(0.06);
        Graph[10]->SetMinimum(-1.2);
        Graph[10]->SetMaximum(1.2);
        Graph[10]->Draw("ALP");

        // Muon PT 
        canvas[i_main][11]->cd();
        pad[i_main][11][0]->Draw();
        pad[i_main][11][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 15 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][11]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][11]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][11]->GetBinCenter(i_get+1);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][11]->GetXaxis()->SetRangeUser(0,1500);
        HistPlot2[i_main][11]->GetXaxis()->SetRangeUser(0,1500);
        HistPlot[i_main][11]->Chi2Test(HistPlot2[i_main][11],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][11][0]->cd();
        HistPlot[i_main][11]->GetXaxis()->SetTitle("P_{T} Muon [GeV/c]");
        HistPlot[i_main][11]->GetXaxis()->SetRangeUser(.0,1500);
        HistPlot[i_main][11]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][11]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][11]->GetYaxis()->SetTitle("Events/100");
        HistPlot[i_main][11]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][11]->SetMinimum(0.3);
        HistPlot[i_main][11]->SetMaximum(10e4);
        HistPlot[i_main][11]->Draw();
        HistPlot2[i_main][11]->GetXaxis()->SetRangeUser(0,1500);
        HistPlot2[i_main][11]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][11][1]->cd();
        Graph[11] = new TGraph(15, dataX, data2);
        Graph[11]->SetMarkerStyle(20);
        Graph[11]->GetXaxis()->SetTitle("P_{T} Muon [GeV/c]");
        Graph[11]->GetXaxis()->SetTitleOffset(.9);
        Graph[11]->GetXaxis()->SetTitleSize(0.055);
        Graph[11]->GetXaxis()->SetLabelSize(0.05);
        Graph[11]->GetXaxis()->SetRangeUser(0.,1500);
        Graph[11]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[11]->GetYaxis()->SetTitleOffset(0.5);
        Graph[11]->GetYaxis()->SetTitleSize(0.06);
        Graph[11]->GetYaxis()->SetLabelSize(0.06);
        Graph[11]->SetMinimum(-2.);
        Graph[11]->SetMaximum(2.);
        Graph[11]->Draw("ALP");

        // Muon Eta 
        canvas[i_main][12]->cd();
        pad[i_main][12][0]->Draw();
        pad[i_main][12][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 50 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][12]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][12]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][12]->GetBinCenter(i_get+1);
            if (data1[i_get]==0) {data2[i_get]=0.;}
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][12]->GetXaxis()->SetRangeUser(-5.0,4.8);
        HistPlot2[i_main][12]->GetXaxis()->SetRangeUser(-5.0,4.8);
        HistPlot[i_main][12]->Chi2Test(HistPlot2[i_main][12],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][12][0]->cd();
        HistPlot[i_main][12]->GetXaxis()->SetTitle("#eta Muon");
        HistPlot[i_main][12]->GetXaxis()->SetRangeUser(-5.0,5.0);
        HistPlot[i_main][12]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][12]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][12]->GetYaxis()->SetTitle("Events/0.2");
        HistPlot[i_main][12]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][12]->SetMinimum(0.3);
        HistPlot[i_main][12]->SetMaximum(10e4);
        HistPlot[i_main][12]->Draw();
        HistPlot2[i_main][12]->GetXaxis()->SetRangeUser(-5,5);
        HistPlot2[i_main][12]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][12][1]->cd();
        Graph[12] = new TGraph(50, dataX, data2);
        Graph[12]->SetMarkerStyle(20);
        Graph[12]->GetXaxis()->SetTitle("#eta Muon");
        Graph[12]->GetXaxis()->SetTitleOffset(1.05);
        Graph[12]->GetXaxis()->SetTitleSize(0.045);
        Graph[12]->GetXaxis()->SetLabelSize(0.05);
        Graph[12]->GetXaxis()->SetRangeUser(-5.0,5.0);
        Graph[12]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[12]->GetYaxis()->SetTitleOffset(0.5);
        Graph[12]->GetYaxis()->SetTitleSize(0.06);
        Graph[12]->GetYaxis()->SetLabelSize(0.06);
        Graph[12]->SetMinimum(-1.2);
        Graph[12]->SetMaximum(1.2);
        Graph[12]->Draw("ALP");

        // Tau PT 
        canvas[i_main][13]->cd();
        pad[i_main][13][0]->Draw();
        pad[i_main][13][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 16 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][13]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][13]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][13]->GetBinCenter(i_get+1);
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][13]->GetXaxis()->SetRangeUser(0,1600);
        HistPlot2[i_main][13]->GetXaxis()->SetRangeUser(0,1600);
        HistPlot[i_main][13]->Chi2Test(HistPlot2[i_main][13],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][13][0]->cd();
        HistPlot[i_main][13]->GetXaxis()->SetTitle("P_{T} Tau [GeV/c]");
        HistPlot[i_main][13]->GetXaxis()->SetRangeUser(.0,1600);
        HistPlot[i_main][13]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][13]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][13]->GetYaxis()->SetTitle("Events/100");
        HistPlot[i_main][13]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][13]->SetMinimum(0.3);
        HistPlot[i_main][13]->SetMaximum(10e4);
        HistPlot[i_main][13]->Draw();
        HistPlot2[i_main][13]->GetXaxis()->SetRangeUser(0,1600);
        HistPlot2[i_main][13]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][13][1]->cd();
        Graph[13] = new TGraph(16, dataX, data2);
        Graph[13]->SetMarkerStyle(20);
        Graph[13]->GetXaxis()->SetTitle("P_{T} Tau [GeV/c]");
        Graph[13]->GetXaxis()->SetTitleOffset(.9);
        Graph[13]->GetXaxis()->SetTitleSize(0.055);
        Graph[13]->GetXaxis()->SetLabelSize(0.05);
        Graph[13]->GetXaxis()->SetRangeUser(0.,1600);
        Graph[13]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[13]->GetYaxis()->SetTitleOffset(0.5);
        Graph[13]->GetYaxis()->SetTitleSize(0.06);
        Graph[13]->GetYaxis()->SetLabelSize(0.06);
        Graph[13]->SetMinimum(-1.);
        Graph[13]->SetMaximum(1.);
        Graph[13]->Draw("ALP");

        // Tau Eta 
        canvas[i_main][14]->cd();
        pad[i_main][14][0]->Draw();
        pad[i_main][14][1]->Draw();
            // Plot compare part
        for (Int_t i_get = 0 ; i_get < 50 ; i_get++ ) {
            data1[i_get] = HistPlot[i_main][14]->GetBinContent(i_get+1);        
            data2[i_get] = HistPlot2[i_main][14]->GetBinContent(i_get+1);        
            //cout << "Data: " << data1[i_get] << "  " << data2[i_get]<< endl;;        
            data2[i_get] = (data2[i_get]-data1[i_get])/data1[i_get]; 
            dataX[i_get] = HistPlot[i_main][14]->GetBinCenter(i_get+1);
            if (data1[i_get]==0) {data2[i_get]=0.;}
            //cout << "BIN: " << dataX[i_get] << " Data: " << data2[i_get]<< endl;;        
            //cout << "================================" << endl;
        }
            // Chi square part
        HistPlot[i_main][14]->GetXaxis()->SetRangeUser(-5.0,4.8);
        HistPlot2[i_main][14]->GetXaxis()->SetRangeUser(-5.0,4.8);
        HistPlot[i_main][14]->Chi2Test(HistPlot2[i_main][14],"UU P",res);

            // Plot part
            // Plot Hist
        pad[i_main][14][0]->cd();
        HistPlot[i_main][14]->GetXaxis()->SetTitle("#eta Tau");
        HistPlot[i_main][14]->GetXaxis()->SetRangeUser(-5.0,5.0);
        HistPlot[i_main][14]->GetXaxis()->SetLabelSize(0.03);
        HistPlot[i_main][14]->GetXaxis()->SetTitleSize(0.03);
        HistPlot[i_main][14]->GetYaxis()->SetTitle("Events/0.2");
        HistPlot[i_main][14]->GetYaxis()->SetTitleOffset(1.25);
        HistPlot[i_main][14]->SetMinimum(0.3);
        HistPlot[i_main][14]->SetMaximum(10e4);
        HistPlot[i_main][14]->Draw();
        HistPlot2[i_main][14]->GetXaxis()->SetRangeUser(-5,5);
        HistPlot2[i_main][14]->Draw("E same");
        leg->Draw("same");

            // Plot Compare Graph
        pad[i_main][14][1]->cd();
        Graph[14] = new TGraph(50, dataX, data2);
        Graph[14]->SetMarkerStyle(20);
        Graph[14]->GetXaxis()->SetTitle("#eta Tau");
        Graph[14]->GetXaxis()->SetTitleOffset(1.05);
        Graph[14]->GetXaxis()->SetTitleSize(0.045);
        Graph[14]->GetXaxis()->SetLabelSize(0.05);
        Graph[14]->GetXaxis()->SetRangeUser(-5.0,5.0);
        Graph[14]->GetYaxis()->SetTitle("#frac{Data-HEPSIM}{HEPSIM}");
        Graph[14]->GetYaxis()->SetTitleOffset(0.5);
        Graph[14]->GetYaxis()->SetTitleSize(0.06);
        Graph[14]->GetYaxis()->SetLabelSize(0.06);
        Graph[14]->SetMinimum(-1.0);
        Graph[14]->SetMaximum(1.0);
        Graph[14]->Draw("ALP");

        // Jet Delta Phi 
        // Jet Delta Phi 
        // Jet Delta Phi 

        // Jet Delta Phi 

        //// Jet Pt
        //canvas[i_main][7]->cd();
        //HistPlot[i_main][7]->Draw();
        //HistPlot[i_main][7]->GetXaxis()->SetTitle("P_{T} Jet [GeV/c]");
        //HistPlot[i_main][7]->GetYaxis()->SetTitle("Events/100 GeV");
        //HistPlot[i_main][7]->GetYaxis()->SetTitleOffset(1.25);
        //HistPlot[i_main][7]->GetXaxis()->SetRangeUser(0,6000);
        //HistPlot[i_main][7]->SetMinimum(0.03);
        //HistPlot[i_main][7]->Draw();

        //// Jet Eta
        //canvas[i_main][8]->cd();
        //HistPlot[i_main][8]->Draw();
        //HistPlot[i_main][8]->GetXaxis()->SetTitle("#eta Jet [GeV/c]");
        //HistPlot[i_main][8]->GetYaxis()->SetTitle("Events/0.2 ");
        //HistPlot[i_main][8]->GetYaxis()->SetTitleOffset(1.25);
        //HistPlot[i_main][8]->GetXaxis()->SetRangeUser(-5,5);
        //HistPlot[i_main][8]->SetMinimum(0.3);
        //HistPlot[i_main][8]->SetMaximum(10e8);
        //HistPlot[i_main][8]->Draw();

        //// Elec Pt
        //canvas[i_main][9]->cd();
        //HistPlot[i_main][9]->Draw();
        //HistPlot[i_main][9]->GetXaxis()->SetTitle("P_{T} Electron [GeV/c]");
        //HistPlot[i_main][9]->GetYaxis()->SetTitle("Events/100 GeV");
        //HistPlot[i_main][9]->GetYaxis()->SetTitleOffset(1.25);
        //HistPlot[i_main][9]->GetXaxis()->SetRangeUser(0,6000);
        //HistPlot[i_main][9]->SetMinimum(0.03);
        //HistPlot[i_main][9]->Draw();

        //// Elec Eta
        //canvas[i_main][10]->cd();
        //HistPlot[i_main][10]->Draw();
        //HistPlot[i_main][10]->GetXaxis()->SetTitle("#eta Elec [GeV/c]");
        //HistPlot[i_main][10]->GetYaxis()->SetTitle("Events/0.2 ");
        //HistPlot[i_main][10]->GetYaxis()->SetTitleOffset(1.25);
        //HistPlot[i_main][10]->GetXaxis()->SetRangeUser(-5,5);
        //HistPlot[i_main][10]->SetMinimum(0.3);
        //HistPlot[i_main][10]->SetMaximum(10e8);
        //HistPlot[i_main][10]->Draw();

        //// Muon Pt
        //canvas[i_main][11]->cd();
        //HistPlot[i_main][11]->Draw();
        //HistPlot[i_main][11]->GetXaxis()->SetTitle("P_{T} Muon [GeV/c]");
        //HistPlot[i_main][11]->GetYaxis()->SetTitle("Events/100 GeV");
        //HistPlot[i_main][11]->GetYaxis()->SetTitleOffset(1.25);
        //HistPlot[i_main][11]->GetXaxis()->SetRangeUser(0,6000);
        //HistPlot[i_main][11]->SetMinimum(0.03);
        //HistPlot[i_main][11]->Draw();

        //// Muon Eta
        //canvas[i_main][12]->cd();
        //HistPlot[i_main][12]->Draw();
        //HistPlot[i_main][12]->GetXaxis()->SetTitle("#eta Muon [GeV/c]");
        //HistPlot[i_main][12]->GetYaxis()->SetTitle("Events/0.2 ");
        //HistPlot[i_main][12]->GetYaxis()->SetTitleOffset(1.25);
        //HistPlot[i_main][12]->GetXaxis()->SetRangeUser(-5,5);
        //HistPlot[i_main][12]->SetMinimum(0.3);
        //HistPlot[i_main][12]->SetMaximum(10e8);
        //HistPlot[i_main][12]->Draw();

        //// tau Pt
        //canvas[i_main][13]->cd();
        //HistPlot[i_main][13]->Draw();
        //HistPlot[i_main][13]->GetXaxis()->SetTitle("P_{T} tau [GeV/c]");
        //HistPlot[i_main][13]->GetYaxis()->SetTitle("Events/100 GeV");
        //HistPlot[i_main][13]->GetYaxis()->SetTitleOffset(1.25);
        //HistPlot[i_main][13]->GetXaxis()->SetRangeUser(0,6000);
        //HistPlot[i_main][13]->SetMinimum(0.03);
        //HistPlot[i_main][13]->Draw();

        //// tau Eta
        //canvas[i_main][14]->cd();
        //HistPlot[i_main][14]->Draw();
        //HistPlot[i_main][14]->GetXaxis()->SetTitle("#eta tau [GeV/c]");
        //HistPlot[i_main][14]->GetYaxis()->SetTitle("Events/0.2 ");
        //HistPlot[i_main][14]->GetYaxis()->SetTitleOffset(1.25);
        //HistPlot[i_main][14]->GetXaxis()->SetRangeUser(-5,5);
        //HistPlot[i_main][14]->SetMinimum(0.3);
        //HistPlot[i_main][14]->SetMaximum(10e8);
        //HistPlot[i_main][14]->Draw();
    
    }



    //f_save->Write();
    //f_save->Close();
   
   
   


}


