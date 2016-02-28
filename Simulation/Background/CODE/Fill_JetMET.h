#ifndef Fill_JETMET_H
#define Fill_JETMET_H

#include "TH1.h"

gSystem->Load("libDelphes.so");
void Fill_JET(Int_t size, TClonesArray* Branch , Float_t value[], TH1F* Histogram[]);

#endif

