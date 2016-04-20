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
  Double_t  MD[8]  = {250,  300,  350,  400,  450,  500,  550,  600};
  Double_t  dMD[8] = {1999., 1999., 1999., 1999., 1999., 1999., 1999., 1999.};
  //char  *title[8]  = {"> 250", "> 300", "> 350", "> 400", "> 450", "> 500", "> 550", "> 600"};
  TGraph    *axis  = new TGraph(8, MD, dMD);
  
  axis->SetLineWidth(4); 
  axis->SetLineStyle(1);	
  axis->SetLineColor(kBlue);
  //axis_k->SetLineWidth(4); 
  //axis_k->SetLineStyle(2);
  //axis_k->SetLineColor(kBlue);
	
  axis->GetYaxis()->SetRangeUser(0.003,1);
  axis->GetYaxis()->SetMoreLogLabels(false);
  axis->GetXaxis()->SetRangeUser(250.,600.);
  axis->GetXaxis()->CenterLabels(true);
  axis->GetXaxis()->SetTitleSize(0.05); 
  axis->GetXaxis()->SetTitleOffset(1.1);
  axis->GetXaxis()->SetLabelSize(0.04); 
  axis->GetXaxis()->SetTitle("E_{T}^{miss} Threshold [GeV]");
  axis->GetYaxis()->SetTitleSize(0.05);
  axis->GetYaxis()->SetTitleOffset(1.1);
  axis->GetYaxis()->SetLabelSize(0.04); 
  axis->GetYaxis()->SetTitle("#sigma^{BSM}_{vis} = #sigma #times A #times #varepsilon [pb]");
  axis->GetYaxis()->SetNdivisions(510);
  axis->GetXaxis()->SetNdivisions(8);
  //axis->GetXaxis()->SetBinLabel(1,"MMM");
  axis->Draw("AC"); 

  //TText *t = new TText();
  //for (Int_t i=0;i<8;i++) {
  //t->DrawText(-0.42,MD[i],title[i]);
  //}
  
  //-----------------------
  const Int_t n = 2;

  Double_t obs250 = 0.228757;
  Double_t med250 = 0.215443;
  Double_t med250_1D = 0.145807;
  Double_t med250_1U = 0.301425;
  Double_t med250_2D = 0.120881;
  Double_t med250_2U = 0.402018;
  
  Double_t obs300 = 0.0982648;
  Double_t med300 = 0.0914901;
  Double_t med300_1D = 0.0646621;
  Double_t med300_1U = 0.125314;
  Double_t med300_2D = 0.0468959;
  Double_t med300_2U = 0.171086;
  
  Double_t obs350 = 0.0487699;
  Double_t med350 = 0.0461648;
  Double_t med350_1D = 0.032357;
  Double_t med350_1U = 0.060997;
  Double_t med350_2D = 0.0269538;
  Double_t med350_2U = 0.0855081;
  
  Double_t obs400 = 0.0201462;
  Double_t med400 = 0.0229144;
  Double_t med400_1D = 0.0181088;
  Double_t med400_1U = 0.0324378;
  Double_t med400_2D = 0.0115174;
  Double_t med400_2U = 0.0440747;
  
  Double_t obs450 = 0.00782152;
  Double_t med450 = 0.0135195;
  Double_t med450_1D = 0.00852083;
  Double_t med450_1U = 0.0207783;
  Double_t med450_2D = 0.00682082;
  Double_t med450_2U = 0.041;
  
  Double_t obs500 = 0.00609151;
  Double_t med500 = 0.00878939;
  Double_t med500_1D = 0.00622711;
  Double_t med500_1U = 0.0112008;
  Double_t med500_2D = 0.00324168;
  Double_t med500_2U = 0.0233033;
  
  Double_t obs550 = 0.00721492;
  Double_t med550 = 0.00693897;
  Double_t med550_1D = 0.00529933;
  Double_t med550_1U = 0.00949755;
  Double_t med550_2D = 0.00419694;
  Double_t med550_2U = 0.0123211;
  
/*
  Double_t obs250 = 0.228757;
  Double_t obs300 = 0.0982648;
  Double_t obs350 = 0.0487699;
  Double_t obs400 = 0.0201462;
  Double_t obs450 = 0.00782152;
  Double_t obs500 = 0.00609151;
  Double_t obs550 = 0.00721492;

  Double_t med250 = 0.215443;
  Double_t med300 = 0.0914901;
  Double_t med350 = 0.0461648;
  Double_t med400 = 0.0229144;
  Double_t med450 = 0.0135195;
  Double_t med500 = 0.00878939;
  Double_t med550 = 0.00693897;

  Double_t med250_1D = 0.145807;
  Double_t med300_1D = 0.0646621;
  Double_t med350_1D = 0.032357;
  Double_t med400_1D = 0.0181088;
  Double_t med450_1D = 0.00852083;
  Double_t med500_1D = 0.00622711;
  Double_t med550_1D = 0.00529933;
 
  Double_t med250_1U = 0.301425;
  Double_t med300_1U = 0.125314;
  Double_t med350_1U = 0.060997;
  Double_t med400_1U = 0.0324378;
  Double_t med450_1U = 0.0207783;
  Double_t med500_1U = 0.0112008;
  Double_t med550_1U = 0.00949755;

  Double_t med250_2D = 0.120881;
  Double_t med300_2D = 0.0468959;
  Double_t med350_2D = 0.0269538;
  Double_t med400_2D = 0.0115174;
  Double_t med450_2D = 0.00682082;
  Double_t med500_2D = 0.00324168;
  Double_t med550_2D = 0.00419694;

  Double_t med250_2U = 0.402018;
  Double_t med300_2U = 0.171086;
  Double_t med350_2U = 0.0855081;
  Double_t med400_2U = 0.0440747;
  Double_t med450_2U = 0.041;
  Double_t med500_2U = 0.0233033;
  Double_t med550_2U = 0.0123211;
*/  
 
  Double_t MET250[n]={250, 300};
  Double_t Observ_250[n]={obs250,obs250}; 
  Double_t Expect_250[n]={med250,med250};
  Double_t Expect_250_1D[n]={med250_1D,med250_1D};
  Double_t Expect_250_1U[n]={med250_1U,med250_1U};
  Double_t Expect_250_2D[n]={med250_2D,med250_2D};
  Double_t Expect_250_2U[n]={med250_2U,med250_2U};

  Double_t MET300[n]={300, 350};
  Double_t Observ_300[n]={obs300,obs300}; 
  Double_t Expect_300[n]={med300,med300};
  Double_t Expect_300_1D[n]={med300_1D,med300_1D};
  Double_t Expect_300_1U[n]={med300_1U,med300_1U};
  Double_t Expect_300_2D[n]={med300_2D,med300_2D};
  Double_t Expect_300_2U[n]={med300_2U,med300_2U};

  Double_t MET350[n]={350, 400};
  Double_t Observ_350[n]={obs350,obs350}; 
  Double_t Expect_350[n]={med350,med350};
  Double_t Expect_350_1D[n]={med350_1D,med350_1D};
  Double_t Expect_350_1U[n]={med350_1U,med350_1U};
  Double_t Expect_350_2D[n]={med350_2D,med350_2D};
  Double_t Expect_350_2U[n]={med350_2U,med350_2U};

  Double_t MET400[n]={400, 450};
  Double_t Observ_400[n]={obs400,obs400}; 
  Double_t Expect_400[n]={med400,med400};
  Double_t Expect_400_1D[n]={med400_1D,med400_1D};
  Double_t Expect_400_1U[n]={med400_1U,med400_1U};
  Double_t Expect_400_2D[n]={med400_2D,med400_2D};
  Double_t Expect_400_2U[n]={med400_2U,med400_2U};

  Double_t MET450[n]={450, 500};
  Double_t Observ_450[n]={obs450,obs450}; 
  Double_t Expect_450[n]={med450,med450};
  Double_t Expect_450_1D[n]={med450_1D,med450_1D};
  Double_t Expect_450_1U[n]={med450_1U,med450_1U};
  Double_t Expect_450_2D[n]={med450_2D,med450_2D};
  Double_t Expect_450_2U[n]={med450_2U,med450_2U};

  Double_t MET500[n]={500, 550};
  Double_t Observ_500[n]={obs500,obs500}; 
  Double_t Expect_500[n]={med500,med500};
  Double_t Expect_500_1D[n]={med500_1D,med500_1D};
  Double_t Expect_500_1U[n]={med500_1U,med500_1U};
  Double_t Expect_500_2D[n]={med500_2D,med500_2D};
  Double_t Expect_500_2U[n]={med500_2U,med500_2U};

  Double_t MET550[n]={550, 600};
  Double_t Observ_550[n]={obs550,obs550}; 
  Double_t Expect_550[n]={med550,med550};
  Double_t Expect_550_1D[n]={med550_1D,med550_1D};
  Double_t Expect_550_1U[n]={med550_1U,med550_1U};
  Double_t Expect_550_2D[n]={med550_2D,med550_2D};
  Double_t Expect_550_2U[n]={med550_2U,med550_2U};

  //250
  TGraph *G_Observ_250    = new TGraph(n,MET250,Observ_250);
  TGraph *G_Expect_250    = new TGraph(n,MET250,Expect_250);
  TGraph *G_Expect_250_1D = new TGraph(n,MET250,Expect_250_1D);
  TGraph *G_Expect_250_1U = new TGraph(n,MET250,Expect_250_1U);
  TGraph *G_Expect_250_2D = new TGraph(n,MET250,Expect_250_2D);
  TGraph *G_Expect_250_2U = new TGraph(n,MET250,Expect_250_2U);
  TGraph *grshade_250_1 = new TGraph(2*n);
  TGraph *grshade_250_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_250_1->SetPoint(i,   MET250[i],     Expect_250_1U[i] );
    grshade_250_1->SetPoint(n+i, MET250[n-i-1], Expect_250_1D[n-i-1]);
    grshade_250_2->SetPoint(i,   MET250[i],     Expect_250_2U[i] );
    grshade_250_2->SetPoint(n+i, MET250[n-i-1], Expect_250_2D[n-i-1]);
  }
  grshade_250_2->SetFillColor(kYellow);
  grshade_250_2->Draw("f");
  grshade_250_1->SetFillColor(kGreen);
  grshade_250_1->Draw("f");
  G_Expect_250->SetLineWidth(4); 
  G_Expect_250->SetLineStyle(2); 
  G_Expect_250->SetLineColor(kBlack);
  G_Expect_250->Draw("C");
  G_Observ_250->SetLineWidth(4); 
  G_Observ_250->SetLineStyle(1); 
  G_Observ_250->SetLineColor(kBlack);
  G_Observ_250->Draw("C");

  //300
  TGraph *G_Observ_300    = new TGraph(n,MET300,Observ_300);
  TGraph *G_Expect_300    = new TGraph(n,MET300,Expect_300);
  TGraph *G_Expect_300_1D = new TGraph(n,MET300,Expect_300_1D);
  TGraph *G_Expect_300_1U = new TGraph(n,MET300,Expect_300_1U);
  TGraph *G_Expect_300_2D = new TGraph(n,MET300,Expect_300_2D);
  TGraph *G_Expect_300_2U = new TGraph(n,MET300,Expect_300_2U);
  TGraph *grshade_300_1 = new TGraph(2*n);
  TGraph *grshade_300_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_300_1->SetPoint(i,   MET300[i],     Expect_300_1U[i] );
    grshade_300_1->SetPoint(n+i, MET300[n-i-1], Expect_300_1D[n-i-1]);
    grshade_300_2->SetPoint(i,   MET300[i],     Expect_300_2U[i] );
    grshade_300_2->SetPoint(n+i, MET300[n-i-1], Expect_300_2D[n-i-1]);
  }
  grshade_300_2->SetFillColor(kYellow);
  grshade_300_2->Draw("f");
  grshade_300_1->SetFillColor(kGreen);
  grshade_300_1->Draw("f");
  G_Expect_300->SetLineWidth(4); 
  G_Expect_300->SetLineStyle(2); 
  G_Expect_300->SetLineColor(kBlack);
  G_Expect_300->Draw("C");
  G_Observ_300->SetLineWidth(4); 
  G_Observ_300->SetLineStyle(1); 
  G_Observ_300->SetLineColor(kBlack);
  G_Observ_300->Draw("C");

  //350
  TGraph *G_Observ_350    = new TGraph(n,MET350,Observ_350);
  TGraph *G_Expect_350    = new TGraph(n,MET350,Expect_350);
  TGraph *G_Expect_350_1D = new TGraph(n,MET350,Expect_350_1D);
  TGraph *G_Expect_350_1U = new TGraph(n,MET350,Expect_350_1U);
  TGraph *G_Expect_350_2D = new TGraph(n,MET350,Expect_350_2D);
  TGraph *G_Expect_350_2U = new TGraph(n,MET350,Expect_350_2U);
  TGraph *grshade_350_1 = new TGraph(2*n);
  TGraph *grshade_350_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_350_1->SetPoint(i,   MET350[i],     Expect_350_1U[i] );
    grshade_350_1->SetPoint(n+i, MET350[n-i-1], Expect_350_1D[n-i-1]);
    grshade_350_2->SetPoint(i,   MET350[i],     Expect_350_2U[i] );
    grshade_350_2->SetPoint(n+i, MET350[n-i-1], Expect_350_2D[n-i-1]);
  }
  grshade_350_2->SetFillColor(kYellow);
  grshade_350_2->Draw("f");
  grshade_350_1->SetFillColor(kGreen);
  grshade_350_1->Draw("f");
  G_Expect_350->SetLineWidth(4); 
  G_Expect_350->SetLineStyle(2); 
  G_Expect_350->SetLineColor(kBlack);
  G_Expect_350->Draw("C");
  G_Observ_350->SetLineWidth(4); 
  G_Observ_350->SetLineStyle(1); 
  G_Observ_350->SetLineColor(kBlack);
  G_Observ_350->Draw("C");
  
  //400
  TGraph *G_Observ_400    = new TGraph(n,MET400,Observ_400);
  TGraph *G_Expect_400    = new TGraph(n,MET400,Expect_400);
  TGraph *G_Expect_400_1D = new TGraph(n,MET400,Expect_400_1D);
  TGraph *G_Expect_400_1U = new TGraph(n,MET400,Expect_400_1U);
  TGraph *G_Expect_400_2D = new TGraph(n,MET400,Expect_400_2D);
  TGraph *G_Expect_400_2U = new TGraph(n,MET400,Expect_400_2U);
  TGraph *grshade_400_1 = new TGraph(2*n);
  TGraph *grshade_400_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_400_1->SetPoint(i,   MET400[i],     Expect_400_1U[i] );
    grshade_400_1->SetPoint(n+i, MET400[n-i-1], Expect_400_1D[n-i-1]);
    grshade_400_2->SetPoint(i,   MET400[i],     Expect_400_2U[i] );
    grshade_400_2->SetPoint(n+i, MET400[n-i-1], Expect_400_2D[n-i-1]);
  }
  grshade_400_2->SetFillColor(kYellow);
  grshade_400_2->Draw("f");
  grshade_400_1->SetFillColor(kGreen);
  grshade_400_1->Draw("f");
  G_Expect_400->SetLineWidth(4); 
  G_Expect_400->SetLineStyle(2); 
  G_Expect_400->SetLineColor(kBlack);
  G_Expect_400->Draw("C");
  G_Observ_400->SetLineWidth(4); 
  G_Observ_400->SetLineStyle(1); 
  G_Observ_400->SetLineColor(kBlack);
  G_Observ_400->Draw("C");

  //450
  TGraph *G_Observ_450    = new TGraph(n,MET450,Observ_450);
  TGraph *G_Expect_450    = new TGraph(n,MET450,Expect_450);
  TGraph *G_Expect_450_1D = new TGraph(n,MET450,Expect_450_1D);
  TGraph *G_Expect_450_1U = new TGraph(n,MET450,Expect_450_1U);
  TGraph *G_Expect_450_2D = new TGraph(n,MET450,Expect_450_2D);
  TGraph *G_Expect_450_2U = new TGraph(n,MET450,Expect_450_2U);
  TGraph *grshade_450_1 = new TGraph(2*n);
  TGraph *grshade_450_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_450_1->SetPoint(i,   MET450[i],     Expect_450_1U[i] );
    grshade_450_1->SetPoint(n+i, MET450[n-i-1], Expect_450_1D[n-i-1]);
    grshade_450_2->SetPoint(i,   MET450[i],     Expect_450_2U[i] );
    grshade_450_2->SetPoint(n+i, MET450[n-i-1], Expect_450_2D[n-i-1]);
  }
  grshade_450_2->SetFillColor(kYellow);
  grshade_450_2->Draw("f");
  grshade_450_1->SetFillColor(kGreen);
  grshade_450_1->Draw("f");
  G_Expect_450->SetLineWidth(4); 
  G_Expect_450->SetLineStyle(2); 
  G_Expect_450->SetLineColor(kBlack);
  G_Expect_450->Draw("C");
  G_Observ_450->SetLineWidth(4); 
  G_Observ_450->SetLineStyle(1); 
  G_Observ_450->SetLineColor(kBlack);
  G_Observ_450->Draw("C");

  //500
  TGraph *G_Observ_500    = new TGraph(n,MET500,Observ_500);
  TGraph *G_Expect_500    = new TGraph(n,MET500,Expect_500);
  TGraph *G_Expect_500_1D = new TGraph(n,MET500,Expect_500_1D);
  TGraph *G_Expect_500_1U = new TGraph(n,MET500,Expect_500_1U);
  TGraph *G_Expect_500_2D = new TGraph(n,MET500,Expect_500_2D);
  TGraph *G_Expect_500_2U = new TGraph(n,MET500,Expect_500_2U);
  TGraph *grshade_500_1 = new TGraph(2*n);
  TGraph *grshade_500_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_500_1->SetPoint(i,   MET500[i],     Expect_500_1U[i] );
    grshade_500_1->SetPoint(n+i, MET500[n-i-1], Expect_500_1D[n-i-1]);
    grshade_500_2->SetPoint(i,   MET500[i],     Expect_500_2U[i] );
    grshade_500_2->SetPoint(n+i, MET500[n-i-1], Expect_500_2D[n-i-1]);
  }
  grshade_500_2->SetFillColor(kYellow);
  grshade_500_2->Draw("f");
  grshade_500_1->SetFillColor(kGreen);
  grshade_500_1->Draw("f");
  G_Expect_500->SetLineWidth(4); 
  G_Expect_500->SetLineStyle(2); 
  G_Expect_500->SetLineColor(kBlack);
  G_Expect_500->Draw("C");
  G_Observ_500->SetLineWidth(4); 
  G_Observ_500->SetLineStyle(1); 
  G_Observ_500->SetLineColor(kBlack);
  G_Observ_500->Draw("C");

  //550
  TGraph *G_Observ_550    = new TGraph(n,MET550,Observ_550);
  TGraph *G_Expect_550    = new TGraph(n,MET550,Expect_550);
  TGraph *G_Expect_550_1D = new TGraph(n,MET550,Expect_550_1D);
  TGraph *G_Expect_550_1U = new TGraph(n,MET550,Expect_550_1U);
  TGraph *G_Expect_550_2D = new TGraph(n,MET550,Expect_550_2D);
  TGraph *G_Expect_550_2U = new TGraph(n,MET550,Expect_550_2U);
  TGraph *grshade_550_1 = new TGraph(2*n);
  TGraph *grshade_550_2 = new TGraph(2*n);
  for (int i=0;i<n;i++)
  {
    grshade_550_1->SetPoint(i,   MET550[i],     Expect_550_1U[i] );
    grshade_550_1->SetPoint(n+i, MET550[n-i-1], Expect_550_1D[n-i-1]);
    grshade_550_2->SetPoint(i,   MET550[i],     Expect_550_2U[i] );
    grshade_550_2->SetPoint(n+i, MET550[n-i-1], Expect_550_2D[n-i-1]);
  }
  grshade_550_2->SetFillColor(kYellow);
  grshade_550_2->Draw("f");
  grshade_550_1->SetFillColor(kGreen);
  grshade_550_1->Draw("f");
  G_Expect_550->SetLineWidth(4); 
  G_Expect_550->SetLineStyle(2); 
  G_Expect_550->SetLineColor(kBlack);
  G_Expect_550->Draw("C");
  G_Observ_550->SetLineWidth(4); 
  G_Observ_550->SetLineStyle(1); 
  G_Observ_550->SetLineColor(kBlack);
  G_Observ_550->Draw("C");

  TLegend *l2 = new TLegend(0.58,0.7,0.93,0.90);
  l2->AddEntry(G_Expect_550,"95% CL Expected limits","l");
  l2->AddEntry(G_Observ_550,"95% CL Observed limits","l");
  l2->AddEntry(grshade_550_1,"#pm 1#sigma_{exp}","f");
  l2->AddEntry(grshade_550_2,"#pm 2#sigma_{exp}","f");
  l2->SetFillColor(0); 
  l2->SetShadowColor(0);
  l2->SetBorderSize(0); 
  l2->SetTextFont(42.);
  l2->Draw(); 
  
  TLatex *text1, *text2; 
  text1 = new TLatex(3.570061,23.08044,"CMS");
  text1->SetNDC();
  text1->SetTextAlign(13);
  text1->SetX(0.18);
  text1->SetY(0.92);
  //text1->SetLineWidth(2);
  text1->SetTextFont(42);
  text1->SetTextSizePixels(24);// dflt=28
  text1->Draw();
  
  text2 = new TLatex(3.570061,23.08044,"19.7 fb^{ -1} (8 TeV)");
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.76);
  text2->SetY(0.99);
  //text2->SetLineWidth(2);
  text2->SetTextFont(42);
  text2->SetTextSize(0.035);// dflt=28
  text2->Draw();

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
