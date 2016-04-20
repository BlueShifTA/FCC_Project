#include "tdrStyle.C"


void limit() {
  //Settings:
  gROOT->Reset();
  gROOT->ProcessLine("setTDRStyle()");
  
  TLatex l; l.SetTextSize(0.05);
  TCanvas *c1 = new TCanvas("ModelIndependent", "Model Independent");
  //c1->SetGrid();
  c1->SetLogy();
		
  //-----------------------
  //Float_t kf=1.5;
  Double_t  MD[7]  = { 2500 ,   3000  ,  3500  ,  4000  ,  4500  ,  5000, 5500};
  Double_t  dMD[7] = {19999., 19999., 19999., 19999., 19999., 19999. , 19999.};
  //char  *title[9]  = {"> 1000", "> 1500", "> 2000", "> 2500", "> 3000", "> 3500", "> 4000", "> 600"};
  TGraph    *axis  = new TGraph(7, MD, dMD);
  
  axis->SetLineWidth(4); 
  axis->SetLineStyle(1);	
  axis->SetLineColor(kBlue);
  //axis_k->SetLineWidth(4); 
  //axis_k->SetLineStyle(2);
  //axis_k->SetLineColor(kBlue);
	
  axis->GetYaxis()->SetRangeUser(0.000015,0.02);
  axis->GetYaxis()->SetMoreLogLabels(false);
  axis->GetXaxis()->SetRangeUser(2500.,5500.);
  axis->GetXaxis()->CenterLabels(true);
  axis->GetXaxis()->SetTitleSize(0.05); 
  axis->GetXaxis()->SetTitleOffset(1.1);
  axis->GetXaxis()->SetLabelSize(0.04); 
  axis->GetXaxis()->SetTitle("E_{T}^{miss} Threshold [GeV]");
  axis->GetYaxis()->SetTitleSize(0.05);
  axis->GetYaxis()->SetTitleOffset(1.3);
  axis->GetYaxis()->SetLabelSize(0.04); 
  axis->GetYaxis()->SetTitle("#sigma^{BSM}_{vis} = #sigma #times A #times #varepsilon [pb]");
  axis->GetYaxis()->SetNdivisions(510);
  axis->GetXaxis()->SetNdivisions(7);
  //axis->GetXaxis()->SetBinLabel(1,"MMM");
  axis->Draw("AC"); 

  //TText *t = new TText();
  //for (Int_t i=0;i<8;i++) {
  //t->DrawText(-0.42,MD[i],title[i]);
  //}
  
  //-----------------------
  const Int_t n = 2;

  //Double_t med1000    = 3.14E-03;
  //Double_t med1000_1D = 2.26E-03;
  //Double_t med1000_1U = 4.31E-03;
  //Double_t med1000_2D = 1.66E-03;
  //Double_t med1000_2U = 5.74E-03;

  //Double_t med1500    = 1.11E-03;
  //Double_t med1500_1D = 8.34E-04;
  //Double_t med1500_1U = 1.55E-03;
  //Double_t med1500_2D = 4.83E-04;
  //Double_t med1500_2U = 2.07E-03;

  //Double_t med2000    = 3.30E-03;
  //Double_t med2000_1D = 2.43E-03;
  //Double_t med2000_1U = 4.56E-03;
  //Double_t med2000_2D = 2.03E-03;
  //Double_t med2000_2U = 6.04E-03;

  Double_t med2500    = 2.05E-03;
  Double_t med2500_1D = 1.51E-03;
  Double_t med2500_1U = 2.78E-03;
  Double_t med2500_2D = 1.20E-03;
  Double_t med2500_2U = 3.61E-03;

  Double_t med3000    = 5.89E-04;
  Double_t med3000_1D = 4.39E-04;
  Double_t med3000_1U = 7.83E-04;
  Double_t med3000_2D = 3.43E-04;
  Double_t med3000_2U = 1.01E-03;

  Double_t med3500    = 2.72E-04;
  Double_t med3500_1D = 1.97E-04;
  Double_t med3500_1U = 3.54E-04;
  Double_t med3500_2D = 1.53E-04;
  Double_t med3500_2U = 4.70E-04;

  Double_t med4000    = 1.20E-04;
  Double_t med4000_1D = 9.10E-05;
  Double_t med4000_1U = 1.60E-04;
  Double_t med4000_2D = 7.02E-05;
  Double_t med4000_2U = 2.13E-04;
 
  Double_t med4500    = 6.61E-05;
  Double_t med4500_1D = 4.98E-05;
  Double_t med4500_1U = 9.10E-05;
  Double_t med4500_2D = 3.86E-05;
  Double_t med4500_2U = 1.21E-04;
  
  Double_t med5000    = 3.58E-05;
  Double_t med5000_1D = 2.75E-05;
  Double_t med5000_1U = 4.98E-05;
  Double_t med5000_2D = 2.09E-05;
  Double_t med5000_2U = 6.69E-05;
  
/*
  Double_t obs1000 = 0.228757;
  Double_t obs1500 = 0.0982648;
  Double_t obs2000 = 0.0487699;
  Double_t obs2500 = 0.0201462;
  Double_t obs3000 = 0.00782152;
  Double_t obs3500 = 0.00609151;
  Double_t obs4000 = 0.00721492;

  Double_t med1000 = 0.215443;
  Double_t med1500 = 0.0914901;
  Double_t med2000 = 0.0461648;
  Double_t med2500 = 0.0229144;
  Double_t med3000 = 0.0135195;
  Double_t med3500 = 0.00878939;
  Double_t med4000 = 0.00693897;

  Double_t med1000_1D = 0.145807;
  Double_t med1500_1D = 0.0646621;
  Double_t med2000_1D = 0.032357;
  Double_t med2500_1D = 0.0181088;
  Double_t med3000_1D = 0.00852083;
  Double_t med3500_1D = 0.00622711;
  Double_t med4000_1D = 0.00529933;
 
  Double_t med1000_1U = 0.301425;
  Double_t med1500_1U = 0.125314;
  Double_t med2000_1U = 0.060997;
  Double_t med2500_1U = 0.0324378;
  Double_t med3000_1U = 0.0207783;
  Double_t med3500_1U = 0.0112008;
  Double_t med4000_1U = 0.00949755;

  Double_t med1000_2D = 0.120881;
  Double_t med1500_2D = 0.0468959;
  Double_t med2000_2D = 0.0269538;
  Double_t med2500_2D = 0.0115174;
  Double_t med3000_2D = 0.00682082;
  Double_t med3500_2D = 0.00324168;
  Double_t med4000_2D = 0.00419694;

  Double_t med1000_2U = 0.402018;
  Double_t med1500_2U = 0.171086;
  Double_t med2000_2U = 0.08400081;
  Double_t med2500_2U = 0.0440747;
  Double_t med3000_2U = 0.041;
  Double_t med3500_2U = 0.0233033;
  Double_t med4000_2U = 0.0123211;
*/  
/*
  Double_t MET1000[n]={1000, 1500};
  Double_t Expect_1000[n]={med1000,med1000};
  Double_t Expect_1000_1D[n]={med1000_1D,med1000_1D};
  Double_t Expect_1000_1U[n]={med1000_1U,med1000_1U};
  Double_t Expect_1000_2D[n]={med1000_2D,med1000_2D};
  Double_t Expect_1000_2U[n]={med1000_2U,med1000_2U};

  Double_t MET1500[n]={1500, 2000};
  Double_t Expect_1500[n]={med1500,med1500};
  Double_t Expect_1500_1D[n]={med1500_1D,med1500_1D};
  Double_t Expect_1500_1U[n]={med1500_1U,med1500_1U};
  Double_t Expect_1500_2D[n]={med1500_2D,med1500_2D};
  Double_t Expect_1500_2U[n]={med1500_2U,med1500_2U};

  Double_t MET2000[n]={2000, 2500};
  Double_t Expect_2000[n]={med2000,med2000};
  Double_t Expect_2000_1D[n]={med2000_1D,med2000_1D};
  Double_t Expect_2000_1U[n]={med2000_1U,med2000_1U};
  Double_t Expect_2000_2D[n]={med2000_2D,med2000_2D};
  Double_t Expect_2000_2U[n]={med2000_2U,med2000_2U};
*/
  Double_t MET2500[n]={2500, 3000};
  Double_t Expect_2500[n]={med2500,med2500};
  Double_t Expect_2500_1D[n]={med2500_1D,med2500_1D};
  Double_t Expect_2500_1U[n]={med2500_1U,med2500_1U};
  Double_t Expect_2500_2D[n]={med2500_2D,med2500_2D};
  Double_t Expect_2500_2U[n]={med2500_2U,med2500_2U};

  Double_t MET3000[n]={3000, 3500};
  Double_t Expect_3000[n]={med3000,med3000};
  Double_t Expect_3000_1D[n]={med3000_1D,med3000_1D};
  Double_t Expect_3000_1U[n]={med3000_1U,med3000_1U};
  Double_t Expect_3000_2D[n]={med3000_2D,med3000_2D};
  Double_t Expect_3000_2U[n]={med3000_2U,med3000_2U};

  Double_t MET3500[n]={3500, 4000};
  Double_t Expect_3500[n]={med3500,med3500};
  Double_t Expect_3500_1D[n]={med3500_1D,med3500_1D};
  Double_t Expect_3500_1U[n]={med3500_1U,med3500_1U};
  Double_t Expect_3500_2D[n]={med3500_2D,med3500_2D};
  Double_t Expect_3500_2U[n]={med3500_2U,med3500_2U};

  Double_t MET4000[n]={4000, 4500};
  Double_t Expect_4000[n]={med4000,med4000};
  Double_t Expect_4000_1D[n]={med4000_1D,med4000_1D};
  Double_t Expect_4000_1U[n]={med4000_1U,med4000_1U};
  Double_t Expect_4000_2D[n]={med4000_2D,med4000_2D};
  Double_t Expect_4000_2U[n]={med4000_2U,med4000_2U};

  Double_t MET4500[n]={4500, 5000};
  Double_t Expect_4500[n]={med4500,med4500};
  Double_t Expect_4500_1D[n]={med4500_1D,med4500_1D};
  Double_t Expect_4500_1U[n]={med4500_1U,med4500_1U};
  Double_t Expect_4500_2D[n]={med4500_2D,med4500_2D};
  Double_t Expect_4500_2U[n]={med4500_2U,med4500_2U};

  Double_t MET5000[n]={5000, 5500};
  Double_t Expect_5000[n]={med5000,med5000};
  Double_t Expect_5000_1D[n]={med5000_1D,med5000_1D};
  Double_t Expect_5000_1U[n]={med5000_1U,med5000_1U};
  Double_t Expect_5000_2D[n]={med5000_2D,med5000_2D};
  Double_t Expect_5000_2U[n]={med5000_2U,med5000_2U};

  ////1000
  //TGraph *G_Expect_1000    = new TGraph(n,MET1000,Expect_1000);
  //TGraph *G_Expect_1000_1D = new TGraph(n,MET1000,Expect_1000_1D);
  //TGraph *G_Expect_1000_1U = new TGraph(n,MET1000,Expect_1000_1U);
  //TGraph *G_Expect_1000_2D = new TGraph(n,MET1000,Expect_1000_2D);
  //TGraph *G_Expect_1000_2U = new TGraph(n,MET1000,Expect_1000_2U);
  //TGraph *grshade_1000_1 = new TGraph(2*n);
  //TGraph *grshade_1000_2 = new TGraph(2*n);
  //for (int i=0;i<n;i++)
  //{
  //  grshade_1000_1->SetPoint(i,   MET1000[i],     Expect_1000_1U[i] );
  //  grshade_1000_1->SetPoint(n+i, MET1000[n-i-1], Expect_1000_1D[n-i-1]);
  //  grshade_1000_2->SetPoint(i,   MET1000[i],     Expect_1000_2U[i] );
  //  grshade_1000_2->SetPoint(n+i, MET1000[n-i-1], Expect_1000_2D[n-i-1]);
  //}
  //grshade_1000_2->SetFillColor(kYellow);
  //grshade_1000_2->Draw("f");
  //grshade_1000_1->SetFillColor(kGreen);
  //grshade_1000_1->Draw("f");
  //G_Expect_1000->SetLineWidth(4); 
  //G_Expect_1000->SetLineStyle(2); 
  //G_Expect_1000->SetLineColor(kBlack);
  //G_Expect_1000->Draw("C");

  ////1500
  //TGraph *G_Expect_1500    = new TGraph(n,MET1500,Expect_1500);
  //TGraph *G_Expect_1500_1D = new TGraph(n,MET1500,Expect_1500_1D);
  //TGraph *G_Expect_1500_1U = new TGraph(n,MET1500,Expect_1500_1U);
  //TGraph *G_Expect_1500_2D = new TGraph(n,MET1500,Expect_1500_2D);
  //TGraph *G_Expect_1500_2U = new TGraph(n,MET1500,Expect_1500_2U);
  //TGraph *grshade_1500_1 = new TGraph(2*n);
  //TGraph *grshade_1500_2 = new TGraph(2*n);
  //for (int i=0;i<n;i++)
  //{
  //  grshade_1500_1->SetPoint(i,   MET1500[i],     Expect_1500_1U[i] );
  //  grshade_1500_1->SetPoint(n+i, MET1500[n-i-1], Expect_1500_1D[n-i-1]);
  //  grshade_1500_2->SetPoint(i,   MET1500[i],     Expect_1500_2U[i] );
  //  grshade_1500_2->SetPoint(n+i, MET1500[n-i-1], Expect_1500_2D[n-i-1]);
  //}
  //grshade_1500_2->SetFillColor(kYellow);
  //grshade_1500_2->Draw("f");
  //grshade_1500_1->SetFillColor(kGreen);
  //grshade_1500_1->Draw("f");
  //G_Expect_1500->SetLineWidth(4); 
  //G_Expect_1500->SetLineStyle(2); 
  //G_Expect_1500->SetLineColor(kBlack);
  //G_Expect_1500->Draw("C");

  //2000
  //TGraph *G_Expect_2000    = new TGraph(n,MET2000,Expect_2000);
  //TGraph *G_Expect_2000_1D = new TGraph(n,MET2000,Expect_2000_1D);
  //TGraph *G_Expect_2000_1U = new TGraph(n,MET2000,Expect_2000_1U);
  //TGraph *G_Expect_2000_2D = new TGraph(n,MET2000,Expect_2000_2D);
  //TGraph *G_Expect_2000_2U = new TGraph(n,MET2000,Expect_2000_2U);
  //TGraph *grshade_2000_1 = new TGraph(2*n);
  //TGraph *grshade_2000_2 = new TGraph(2*n);
  //for (int i=0;i<n;i++)
  //{
  //  grshade_2000_1->SetPoint(i,   MET2000[i],     Expect_2000_1U[i] );
  //  grshade_2000_1->SetPoint(n+i, MET2000[n-i-1], Expect_2000_1D[n-i-1]);
  //  grshade_2000_2->SetPoint(i,   MET2000[i],     Expect_2000_2U[i] );
  //  grshade_2000_2->SetPoint(n+i, MET2000[n-i-1], Expect_2000_2D[n-i-1]);
  //}
  //grshade_2000_2->SetFillColor(kYellow);
  //grshade_2000_2->Draw("f");
  //grshade_2000_1->SetFillColor(kGreen);
  //grshade_2000_1->Draw("f");
  //G_Expect_2000->SetLineWidth(4); 
  //G_Expect_2000->SetLineStyle(2); 
  //G_Expect_2000->SetLineColor(kBlack);
  //G_Expect_2000->Draw("C");
  
  //2500
  TGraph *G_Expect_2500    = new TGraph(n,MET2500,Expect_2500);
  TGraph *G_Expect_2500_1D = new TGraph(n,MET2500,Expect_2500_1D);
  TGraph *G_Expect_2500_1U = new TGraph(n,MET2500,Expect_2500_1U);
  TGraph *G_Expect_2500_2D = new TGraph(n,MET2500,Expect_2500_2D);
  TGraph *G_Expect_2500_2U = new TGraph(n,MET2500,Expect_2500_2U);
  TGraph *grshade_2500_1 = new TGraph(2*n);
  TGraph *grshade_2500_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_2500_1->SetPoint(i,   MET2500[i],     Expect_2500_1U[i] );
    grshade_2500_1->SetPoint(n+i, MET2500[n-i-1], Expect_2500_1D[n-i-1]);
    grshade_2500_2->SetPoint(i,   MET2500[i],     Expect_2500_2U[i] );
    grshade_2500_2->SetPoint(n+i, MET2500[n-i-1], Expect_2500_2D[n-i-1]);
  }
  grshade_2500_2->SetFillColor(kYellow);
  grshade_2500_2->Draw("f");
  grshade_2500_1->SetFillColor(kGreen);
  grshade_2500_1->Draw("f");
  G_Expect_2500->SetLineWidth(4); 
  G_Expect_2500->SetLineStyle(2); 
  G_Expect_2500->SetLineColor(kBlack);
  G_Expect_2500->Draw("C");

  //3000
  TGraph *G_Expect_3000    = new TGraph(n,MET3000,Expect_3000);
  TGraph *G_Expect_3000_1D = new TGraph(n,MET3000,Expect_3000_1D);
  TGraph *G_Expect_3000_1U = new TGraph(n,MET3000,Expect_3000_1U);
  TGraph *G_Expect_3000_2D = new TGraph(n,MET3000,Expect_3000_2D);
  TGraph *G_Expect_3000_2U = new TGraph(n,MET3000,Expect_3000_2U);
  TGraph *grshade_3000_1 = new TGraph(2*n);
  TGraph *grshade_3000_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_3000_1->SetPoint(i,   MET3000[i],     Expect_3000_1U[i] );
    grshade_3000_1->SetPoint(n+i, MET3000[n-i-1], Expect_3000_1D[n-i-1]);
    grshade_3000_2->SetPoint(i,   MET3000[i],     Expect_3000_2U[i] );
    grshade_3000_2->SetPoint(n+i, MET3000[n-i-1], Expect_3000_2D[n-i-1]);
  }
  grshade_3000_2->SetFillColor(kYellow);
  grshade_3000_2->Draw("f");
  grshade_3000_1->SetFillColor(kGreen);
  grshade_3000_1->Draw("f");
  G_Expect_3000->SetLineWidth(4); 
  G_Expect_3000->SetLineStyle(2); 
  G_Expect_3000->SetLineColor(kBlack);
  G_Expect_3000->Draw("C");

  //3500
  TGraph *G_Expect_3500    = new TGraph(n,MET3500,Expect_3500);
  TGraph *G_Expect_3500_1D = new TGraph(n,MET3500,Expect_3500_1D);
  TGraph *G_Expect_3500_1U = new TGraph(n,MET3500,Expect_3500_1U);
  TGraph *G_Expect_3500_2D = new TGraph(n,MET3500,Expect_3500_2D);
  TGraph *G_Expect_3500_2U = new TGraph(n,MET3500,Expect_3500_2U);
  TGraph *grshade_3500_1 = new TGraph(2*n);
  TGraph *grshade_3500_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_3500_1->SetPoint(i,   MET3500[i],     Expect_3500_1U[i] );
    grshade_3500_1->SetPoint(n+i, MET3500[n-i-1], Expect_3500_1D[n-i-1]);
    grshade_3500_2->SetPoint(i,   MET3500[i],     Expect_3500_2U[i] );
    grshade_3500_2->SetPoint(n+i, MET3500[n-i-1], Expect_3500_2D[n-i-1]);
  }
  grshade_3500_2->SetFillColor(kYellow);
  grshade_3500_2->Draw("f");
  grshade_3500_1->SetFillColor(kGreen);
  grshade_3500_1->Draw("f");
  G_Expect_3500->SetLineWidth(4); 
  G_Expect_3500->SetLineStyle(2); 
  G_Expect_3500->SetLineColor(kBlack);
  G_Expect_3500->Draw("C");

  //4000
  TGraph *G_Expect_4000    = new TGraph(n,MET4000,Expect_4000);
  TGraph *G_Expect_4000_1D = new TGraph(n,MET4000,Expect_4000_1D);
  TGraph *G_Expect_4000_1U = new TGraph(n,MET4000,Expect_4000_1U);
  TGraph *G_Expect_4000_2D = new TGraph(n,MET4000,Expect_4000_2D);
  TGraph *G_Expect_4000_2U = new TGraph(n,MET4000,Expect_4000_2U);
  TGraph *grshade_4000_1 = new TGraph(2*n);
  TGraph *grshade_4000_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_4000_1->SetPoint(i,   MET4000[i],     Expect_4000_1U[i] );
    grshade_4000_1->SetPoint(n+i, MET4000[n-i-1], Expect_4000_1D[n-i-1]);
    grshade_4000_2->SetPoint(i,   MET4000[i],     Expect_4000_2U[i] );
    grshade_4000_2->SetPoint(n+i, MET4000[n-i-1], Expect_4000_2D[n-i-1]);
  }
  grshade_4000_2->SetFillColor(kYellow);
  grshade_4000_2->Draw("f");
  grshade_4000_1->SetFillColor(kGreen);
  grshade_4000_1->Draw("f");
  G_Expect_4000->SetLineWidth(4); 
  G_Expect_4000->SetLineStyle(2); 
  G_Expect_4000->SetLineColor(kBlack);
  G_Expect_4000->Draw("C");

  //4500
  TGraph *G_Expect_4500    = new TGraph(n,MET4500,Expect_4500);
  TGraph *G_Expect_4500_1D = new TGraph(n,MET4500,Expect_4500_1D);
  TGraph *G_Expect_4500_1U = new TGraph(n,MET4500,Expect_4500_1U);
  TGraph *G_Expect_4500_2D = new TGraph(n,MET4500,Expect_4500_2D);
  TGraph *G_Expect_4500_2U = new TGraph(n,MET4500,Expect_4500_2U);
  TGraph *grshade_4500_1 = new TGraph(2*n);
  TGraph *grshade_4500_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_4500_1->SetPoint(i,   MET4500[i],     Expect_4500_1U[i] );
    grshade_4500_1->SetPoint(n+i, MET4500[n-i-1], Expect_4500_1D[n-i-1]);
    grshade_4500_2->SetPoint(i,   MET4500[i],     Expect_4500_2U[i] );
    grshade_4500_2->SetPoint(n+i, MET4500[n-i-1], Expect_4500_2D[n-i-1]);
  }
  grshade_4500_2->SetFillColor(kYellow);
  grshade_4500_2->Draw("f");
  grshade_4500_1->SetFillColor(kGreen);
  grshade_4500_1->Draw("f");
  G_Expect_4500->SetLineWidth(4); 
  G_Expect_4500->SetLineStyle(2); 
  G_Expect_4500->SetLineColor(kBlack);
  G_Expect_4500->Draw("C");

  //5000
  TGraph *G_Expect_5000    = new TGraph(n,MET5000,Expect_5000);
  TGraph *G_Expect_5000_1D = new TGraph(n,MET5000,Expect_5000_1D);
  TGraph *G_Expect_5000_1U = new TGraph(n,MET5000,Expect_5000_1U);
  TGraph *G_Expect_5000_2D = new TGraph(n,MET5000,Expect_5000_2D);
  TGraph *G_Expect_5000_2U = new TGraph(n,MET5000,Expect_5000_2U);
  TGraph *grshade_5000_1 = new TGraph(2*n);
  TGraph *grshade_5000_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_5000_1->SetPoint(i,   MET5000[i],     Expect_5000_1U[i] );
    grshade_5000_1->SetPoint(n+i, MET5000[n-i-1], Expect_5000_1D[n-i-1]);
    grshade_5000_2->SetPoint(i,   MET5000[i],     Expect_5000_2U[i] );
    grshade_5000_2->SetPoint(n+i, MET5000[n-i-1], Expect_5000_2D[n-i-1]);
  }
  grshade_5000_2->SetFillColor(kYellow);
  grshade_5000_2->Draw("f");
  grshade_5000_1->SetFillColor(kGreen);
  grshade_5000_1->Draw("f");
  G_Expect_5000->SetLineWidth(4); 
  G_Expect_5000->SetLineStyle(2); 
  G_Expect_5000->SetLineColor(kBlack);
  G_Expect_5000->Draw("C");

  TLegend *l2 = new TLegend(0.58,0.7,0.93,0.90);
  l2->AddEntry(G_Expect_4000,"95% CL Expected limits","l");
  l2->AddEntry(grshade_4000_1,"#pm 1#sigma_{exp}","f");
  l2->AddEntry(grshade_4000_2,"#pm 2#sigma_{exp}","f");
  l2->SetFillColor(0); 
  l2->SetShadowColor(0);
  l2->SetBorderSize(0); 
  l2->SetTextFont(42.);
  l2->Draw(); 
  
  TLatex *text1, *text2, *text3; 
  text1 = new TLatex(3.570061,23.08044,"FCC-hh");
  text1->SetNDC();
  text1->SetTextAlign(13);
  text1->SetX(0.18);
  text1->SetY(0.92);
  //text1->SetLineWidth(2);
  text1->SetTextFont(42);
  text1->SetTextSizePixels(24);// dflt=28
  text1->Draw();
  
  text2 = new TLatex(3.570061,23.08044,"1.0 ab^{ -1} (100 TeV)");
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.72);
  text2->SetY(0.99);
  //text2->SetLineWidth(2);
  text2->SetTextFont(42);
  text2->SetTextSize(0.035);// dflt=28
  text2->Draw();

  text3 = new TLatex(3.570061,23.08044,"BG Uncertainity 10\% ");
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(0.16);
  text3->SetY(0.99);
  //text3->SetLineWidth(2);
  text3->SetTextFont(42);
  text3->SetTextSize(0.035);// dflt=28
  text3->Draw();
  
  TLatex *cut1, *cut2, *cut3, *cut4, *cut5; 
  cut1 = new TLatex(3.570061,23.08044,"1. Jet1 P_{T} > 110 GeV/c");
  cut2 = new TLatex(3.570061,23.08044,"2. NJet(P_{T} > 30 GeV/c) #leq 2");
  cut3 = new TLatex(3.570061,23.08044,"3. #Delta#phi(Jet1, Jet2) < 2.5");
  cut4 = new TLatex(3.570061,23.08044,"4. Veto on isolated electron, muon (P_{T} > 10 GeV/c)");
  cut5 = new TLatex(3.570061,23.08044,"5. Veto on tau (P_{T} > 20 GeV/c)");

  cut1->SetNDC();
  cut1->SetTextAlign(13);
  cut1->SetX(0.2);
  cut1->SetY(0.34);
  //cut1->SetLineWidth(2);
  cut1->SetTextFont(42);
  cut1->SetTextSize(0.03);// dflt=28
  //cut1->Draw();

  cut2->SetNDC();
  cut2->SetTextAlign(13);
  cut2->SetX(0.2);
  cut2->SetY(0.30);
  //cut2->SetLineWidth(2);
  cut2->SetTextFont(42);
  cut2->SetTextSize(0.03);// dflt=28
  //cut2->Draw();

  cut3->SetNDC();
  cut3->SetTextAlign(13);
  cut3->SetX(0.2);
  cut3->SetY(0.26);
  //cut2->SetLineWidth(2);
  cut3->SetTextFont(42);
  cut3->SetTextSize(0.03);// dflt=28
  //cut3->Draw();

  cut4->SetNDC();
  cut4->SetTextAlign(13);
  cut4->SetX(0.2);
  cut4->SetY(0.22);
  //cut4->SetLineWidth(2);
  cut4->SetTextFont(42);
  cut4->SetTextSize(0.03);// dflt=28
  //cut4->Draw();

  cut5->SetNDC();
  cut5->SetTextAlign(13);
  cut5->SetX(0.2);
  cut5->SetY(0.18);
  //cut5->SetLineWidth(2);
  cut5->SetTextFont(42);
  cut5->SetTextSize(0.03);// dflt=28
  //cut5->Draw();
  
  //c1->SaveAs("LimitsXsec_ADD_d2_2011_MET200.eps");
  //c1->SaveAs("LimitsXsec_ADD_d2_2011_MET200.gif");  
}
