// Comparision between 2 histograms
// by using Chi square method 
// (Maybe include Kolmogolov method)
// Written by Surapat EK-IN 
// Date: 26-1-2016
// Update:
//
//
//
#include "Analysis_Code.h"
#include ".h"


void Compare_Chi(const char* Input_1, const char* Input_2 ) {

    // Load root file
    TFile* f1 = new TFile(Input_1,"READ");
    TFile* f2 = new TFile(Input_2,"READ");

    // Load Tree
    TTree* tree1 = new TFile(Input_1,"READ");
    TTree* tree2 = new TFile(Input_2,"READ");



}


