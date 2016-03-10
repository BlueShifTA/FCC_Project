/*
 * Analysis Code used for Prospect of Monojet at 100 TeV
 * Written by Surapat Ek-in 
 * Contact: surapat.eki@gmail.com
 * root -l
 * .L Analysis_code("filename")
 * */

// =-=-2/11/2015 Begin writing codes
// =-=-6/11/2015 initiate structures -> use tree to collect data (and create histogram as well) -> More usable
// =-=-"1/11/2016" Plan to add other objects, e.g. electron, muon, tau, GenJet  
//                                           Event, Photon, ScalarHT
// "1/14/2016" Plan to modify the code -> Add N-1 plot convention
// -----------"1/20/2016" Plan to write a function -> Fill All
// -----------"3/01/2016" Add diff in wzjet process -> Default-> proc = 0
//------------------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void Analysis_Code(const char *inputFile, Int_t plot_num, Int_t proc ) {

  gSystem->Load("libDelphes.so");
  // Open file & read tree structure
  TFile *inFile = new TFile(inputFile, "READ");
  TTree *tree   = (TTree*)(inFile->Get("Delphes"));

  // Open tree reader & use the following branches
  ExRootTreeReader *treeReader  = new ExRootTreeReader(tree);

  // Point branch
  TClonesArray *branchEvent     = treeReader->UseBranch("Event");
  TClonesArray *branchParticle  = treeReader->UseBranch("Particle");  
  TClonesArray *branchJet       = treeReader->UseBranch("Jet");  
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");  
  TClonesArray *branchMuon      = treeReader->UseBranch("Muon");  
  TClonesArray *branchElectron  = treeReader->UseBranch("Electron");  

  //=============================Declear variables===============================
  // Collect data variables 
  Int_t Cuts[20] = {}; // For collect data
  Float_t weight;
  string filename = "";
  Int_t count_Z = 0;
  Int_t count_W = 0;
  Int_t count_test = 0 ;

  // Variable as leafs
  std::vector<Double_t> vJet;	 
  std::vector<Double_t> vMissingET;	 
  std::vector<Double_t> vElectron;	 
  std::vector<Double_t> vMuon;	 
  std::vector<Double_t> vTau;	 

  // Declear root file and tree
  if (proc > 0 ) {
    stringstream proc_num;
    proc_num << proc;
    string monojet  = "Monojet_wzjet_"+proc_num.str()+".root";
    string monojetx = "Monojet_wzjet_"+proc_num.str()+".txt";
    TFile *f            = new TFile(monojet.c_str(),"recreate");
    fstream myfile;
    myfile.open(monojetx.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  } else {
    TFile *f            = new TFile("Monojet.root","recreate");
    fstream myfile;
    myfile.open("Monojet.txt", std::fstream::in | std::fstream::out | std::fstream::app);

  }

  TTree *SelectionCut = new TTree("SelectionCut","Tree for collect data"); 
  // Add branches
  SelectionCut->Branch("Jet",&vJet);
  SelectionCut->Branch("MissingET",&vMissingET);
  SelectionCut->Branch("Electron",&vElectron);
  SelectionCut->Branch("Muon",&vMuon);
  SelectionCut->Branch("Tau",&vTau);


  //=============================Declear Histogram===============================
  TH1F* HistPlot[17][15];

  Double_t pi = 3.14159265;
  string selec  = "Select";
  string phys[] = {"_MET_","_Jet1_Pt_","_Jet2_Pt_","_Jet1_Eta_","_Jet2_Eta_","_Jetdel_Phi_","_Jet_Multi_","_Jet_Pt_","_Jet_Eta_","_Elec_Pt_","_Elec_Eta_","_Muon_Pt_","_Muon_Eta_" ,"_tau_Pt_","_tau_Eta_"      };
  Int_t   bin[] = {    3000 , 3000       , 3000       ,   1000     ,      1000  ,    64        ,   20     , 3000     , 1000   , 3000     , 1000   , 3000     , 1000   , 3000     , 1000            }; 
  Double_t min[] = {    0.0 ,   0.0      ,   0.0      ,  -5.0      ,      -5.0  ,     0.       ,    0     ,   0.0    , -5.0   ,   0.0    , -5.0   ,   0.0    , -5.0   ,   0.0    , -5.0             }; 
  Double_t max[] = { 30000.0, 30000.0    , 30000.0    ,   5.0      ,       5.0  ,   6.4        ,   20     , 30000.0  ,  5.0   , 30000.0  ,  5.0   , 30000.0  ,  5.0   , 30000.0  ,  5.0             }; 



  for (Int_t i = 0 ; i < 17 ; i ++ ) {
      stringstream ss;
      string str[15];

      ss<<i;

      for (Int_t j = 0 ; j < 15 ; j ++){
          str[j] = selec+phys[j]+ss.str();
        //  cout << str[j] << endl;
          HistPlot[i][j]    = new TH1F(str[j].c_str(),phys[j].c_str(), bin[j], min[j], max[j]);
      }

  }


//========================================Begin of Loop Event============================================

  for (auto iEvent=0; iEvent<tree->GetEntries(); iEvent++) {
      Init:
      if (iEvent == tree->GetEntries()) break;
      // Read Events
      treeReader->ReadEntry(iEvent);

      // Load entries 
      Int_t numberGen      =  branchParticle->GetEntriesFast();
      Int_t numberMET      =  branchMissingET->GetEntriesFast();
      Int_t numberJet      =  branchJet->GetEntriesFast();
      Int_t numberMuon     =  branchMuon->GetEntriesFast();
      Int_t numberElectron =  branchElectron->GetEntriesFast();

      // Variables in Loop 
      Int_t countJet=0;       
      Int_t countCuts=0; 

      // Workout event
      HepMCEvent* event = (HepMCEvent*)(branchEvent->At(0));
      if (event->Weight==0) { 
    	  weight=1.f;
      } else {
           weight = event->Weight;
      }

      // Test of Particle variable 
      //count_Z = 0;
      //count_W = 0;

      //for (int iPart=0; iPart<branchParticle->GetEntries(); iPart++) {
      //  GenParticle* part = (GenParticle*)(branchParticle->At(iPart));
      //  if (TMath::Abs(part->PID) ==  23 && (TMath::Abs(part->Status) == 44 || TMath::Abs(part->Status) == 62) && count_Z == 0) count_Z++; 
      //  if (TMath::Abs(part->PID) ==  24 && (TMath::Abs(part->Status) == 44 || TMath::Abs(part->Status) == 62) && count_W == 0) count_W++; 
      //  //cout << "PID: " << part->PID << " Status: " << part->Status << " D1: " << part->D1 << " D2: " << part->D2 << " IsPU: " << part->IsPU << endl;
  //  //    }
      //}
      //cout << "===========================================" << endl;
      // TEST Events

      //if (proc == 1 &&(count_Z != 1 || count_W != 0)) continue; // Z case; 
      //if (proc == 2 &&(count_Z != 0 || count_W != 1)) continue; // W case; 
      //if (proc == 3 &&(count_Z != 1 || count_W != 1)) continue; // WZ case; 
      //cout << "Z: " << count_Z << " W: "  << count_W << " iEvent: " << iEvent << " tree->GetEntries(): " << tree->GetEntries() << endl; 
      // MET 
      MissingET* met = (MissingET*)(branchMissingET->At(0));
      count_test++;

// ========================================================Pre-Selection Cuts ===================================================
//=======================================================0.) No applying cuts==============================================    

    // count jet 
    Cuts[countCuts]++;
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
      Jet* jet = (Jet*) branchJet->At(ijet);
      if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
      countJet++;
      if (countJet == 1) {
         Jet* jet1 = (Jet*) branchJet->At(ijet);
         HistPlot[countCuts][1]->Fill(jet1->PT,weight);
         HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
      }
      if (countJet == 2) {
         Jet* jet2 = (Jet*) branchJet->At(ijet);
         // Edit the deltaphi limitation 21/12/2015   
         deltaphi = TMath::Abs(jet1->Phi - jet2->Phi); 
         if (deltaphi > pi) {deltaphi  = 2*pi - deltaphi;} 
         HistPlot[countCuts][2]->Fill(jet2->PT,weight);
         HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
         HistPlot[countCuts][5]->Fill(deltaphi,weight);
      }
      HistPlot[countCuts][7]->Fill(jet->PT,weight);
      HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }

    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);

    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }
    if (countJet < 1 ) continue; 



//==========================================================================================================================
// =================================================Begin Selection Cuts ===================================================
    // Selection Cut:1==========================================================================================================
    // 1.) Initial MET cut: MET > 200 GeV
    if (plot_num != 1) {
        if (met->MET < 200) continue;
    }
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }


    //==========================================================================================================================
    // Selection Cut:2==========================================================================================================
    // 2.) Leading jet PT > 110 GeV && Eta < 2.4

    if (plot_num != 2) {
        if (jet1->PT <= 110 || TMath::Abs(jet1->Eta) > 2.4) continue;
    }
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }

    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:3==========================================================================================================
    // 3.) Jet Multiplicity Cut 
    if (plot_num != 3) {
        if (countJet > 2) continue;
    }
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:4==========================================================================================================
    // 4.) Angular Separation
    if (plot_num != 4) {
        if (countJet == 2) {
            if (deltaphi >= 2.5) continue;
        }
    }
    countCuts++;
    Cuts[countCuts]++;
 
    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }


    //==========================================================================================================================

    //==========================================================================================================================
    // Selection Cut:5==========================================================================================================
    // 5.) Electron Veto 
    if (plot_num != 5) {
        for (Int_t ielec = 0 ; ielec < numberElectron; ielec++){
          Electron* elec = (Electron*) branchElectron->At(ielec);
          if (elec->PT > 10 && TMath::Abs(elec->Eta) < 2.1 ) {
             ++iEvent;
             goto Init;
          }
        }
    }
    countCuts++;
    Cuts[countCuts]++;
    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:6==========================================================================================================
    if (plot_num != 6) {
        for (Int_t imuon = 0 ; imuon < numberMuon; imuon++){
          Muon* muon = (Muon*) branchMuon->At(imuon);
          if (muon->PT > 10 && TMath::Abs(muon->Eta) < 2.4) {++iEvent;goto Init;}
        }
    }
    countCuts++;
    Cuts[countCuts]++;
    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:7==========================================================================================================
    // 7.) Tau Veto 
    if (plot_num != 7) {
        for (Int_t ip = 0; ip < numberGen; ip++){
          Particle  = (GenParticle*) branchParticle->At(ip);
          if (TMath::Abs(Particle->PID) == 15 ) {
             if (Particle->PT > 20 && TMath::Abs(Particle->Eta) < 2.3) {++iEvent;goto Init;}
          }
        }    
    }
    countCuts++;
    Cuts[countCuts]++;
    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:8==========================================================================================================
    // MET Cut > 400 GeV
    if (met->MET < 400) continue;
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:9==========================================================================================================
    // MET Cut > 600 GeV
    if (met->MET < 600) continue;
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:10==========================================================================================================
    // MET Cut > 800 GeV
    if (met->MET < 800) continue;
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:11==========================================================================================================
    // MET Cut > 1000 GeV
    if (met->MET < 1000) continue;
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:12==========================================================================================================
    // MET Cut > 1200 GeV
    if (met->MET < 1200) continue;
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:13==========================================================================================================
    // MET Cut > 1400 GeV
    if (met->MET < 1400) continue;
    countCuts++;
    Cuts[countCuts]++;
    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }

    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:14==========================================================================================================
    // MET Cut > 1600 GeV
    if (met->MET < 1600) continue;
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:15==========================================================================================================
    // MET Cut > 1800 GeV
    if (met->MET < 1800) continue;
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }
    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    // Selection Cut:16==========================================================================================================
    // MET Cut > 2000 GeV
    if (met->MET < 2000) continue;
    countCuts++;
    Cuts[countCuts]++;

    // Fill session
    HistPlot[countCuts][0]->Fill(met->MET,weight);
    HistPlot[countCuts][6]->Fill(countJet,weight);
    if (countJet > 0 ) {
        HistPlot[countCuts][1]->Fill(jet1->PT,weight);
        HistPlot[countCuts][3]->Fill(jet1->Eta,weight);
    }
    if (countJet > 1 ) {
        HistPlot[countCuts][2]->Fill(jet2->PT,weight);
        HistPlot[countCuts][4]->Fill(jet2->Eta,weight);
        HistPlot[countCuts][5]->Fill(deltaphi,weight);
    }
    for (Int_t ijet = 0 ; ijet < numberJet; ijet++){
        Jet* jet = (Jet*) branchJet->At(ijet);
        if (jet->PT <= 30 || TMath::Abs(jet->Eta) >= 4.5) continue;
        HistPlot[countCuts][7]->Fill(jet->PT,weight);
        HistPlot[countCuts][8]->Fill(jet->Eta,weight);
    }

    for (Int_t ielec = 0; ielec <  numberElectron ; ielec++) {
        Electron* elec = (Electron*) branchElectron->At(ielec);
        HistPlot[countCuts][9]->Fill(elec->PT,weight);
        HistPlot[countCuts][10]->Fill(elec->Eta,weight);
    }
    for (Int_t imuon = 0; imuon <  numberMuon ; imuon++) {
        Muon* muon = (Muon*) branchMuon->At(imuon);
        HistPlot[countCuts][11]->Fill(muon->PT,weight);
        HistPlot[countCuts][12]->Fill(muon->Eta,weight);
    }
    for (Int_t ipar = 0; ipar <  numberGen ; ipar++) {
        GenParticle* par = (GenParticle*) branchParticle->At(ipar);
        if (TMath::Abs(par->PID) != 15) continue;
        HistPlot[countCuts][13]->Fill(par->PT,weight);
        HistPlot[countCuts][14]->Fill(par->Eta,weight);
    }

    //==========================================================================================================================
    
    
    Cuts[countCuts]++;
    countCuts++;



  // Write to tree 
  SelectionCut->Fill();

  }

//========================================End of Loop Event============================================

// Create file for data aquisition


  //myfile << "    #Z  Boson: " << countZ << endl;
  //myfile << "#Znunu  Boson: " << countZnunu << endl;
  //myfile << "#Zlep   Boson: " << countZlep << endl;  
  //myfile << "    #W  Boson: " << countW << endl;
  //myfile << "#Wlepnu Boson: " << countWlepnu << endl;

  for (Int_t i = 0; i < 17 ; i++) {
    myfile << "Selection Cut " << i << " : " << Cuts[i] << endl;
  }  

  myfile.close();

  //Write and Save to Root file
  f->Write();
  f->Close();
  cout << "Count: " << count_test << endl; 

}
