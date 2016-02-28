#include "TH1F.h"
#include "Fill_All.h"


void Fill_All(Int_t size, Float_t value[]){

    for (Int_t i =1; i<size ; i++){
        cout << "Value" << value[i] << endl;
    }
}
