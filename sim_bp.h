#ifndef SIM_BP_H
#define SIM_BP_H
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip> // for setprecision


using namespace std;

typedef struct bp_params{
    unsigned long int K;
    unsigned long int M1;
    unsigned long int M2;
    unsigned long int N;
    char*             bp_name;
}bp_params;

// Put additional data structures here as per your requirement
void btb_walker(vector<int>& v, unsigned long table_index, char outcome, unsigned long& num_mispredictions) {
    switch (v[table_index])
    {
        case 0:
        
            if (outcome =='n')
                {
                    
                }
            else{
                    num_mispredictions++;
                    v[table_index]++;
                }
            break;
            
        case 1:
            if (outcome =='n')
                {
                    v[table_index]--;
                }
            else{
                    num_mispredictions++;
                    v[table_index]++;
                }
            break;

        case 2:
            if (outcome =='t')
                {
                    
                    v[table_index]++;
                }
                else{
                    num_mispredictions++;
                    v[table_index]--;
                }
            break;

        case 3:
                if (outcome =='t')
                {
                    
                }
                else{
                    num_mispredictions++;
                    v[table_index]--;
                }
            break;
    }
}

void final_printer_bi_gs( unsigned long num_predictions, unsigned long num_mispredictions,vector<int>& v,char* bp_name,unsigned long table_size){

    cout<<"OUTPUT"<<endl;
    cout<<" number of predictions:    "<<num_predictions<<endl;
    cout<<" number of mispredictions: "<<num_mispredictions<<endl;

    double misprediction_rate = (static_cast<double>(num_mispredictions) / num_predictions) * 100.0;
    cout << fixed << setprecision(2);  // show 2 digits after decimal
    cout << " misprediction rate:       " << misprediction_rate << "%" << endl;
    if(strcmp(bp_name, "bimodal") == 0) {
        cout << "FINAL BIMODAL CONTENTS"<<endl;
    }
    if(strcmp(bp_name, "gshare") == 0) {
        cout << "FINAL GSHARE CONTENTS"<<endl;
    }
    if(strcmp(bp_name, "hybrid") == 0) {
        cout << "FINAL CHOOSER CONTENTS"<<endl;
    }

    for ( int i = 0; i < table_size; ++i) 
        {
            std::cout<< i << "\t" << (int)v[i] << std::endl;
        }
}

unsigned long table_index_caluc(unsigned long int addr,unsigned long table_size){
    unsigned long shifted_by_2 = addr >> 2;
    unsigned long table_index = shifted_by_2 & (table_size -1);

    return table_index;
}

void k_table_trainer(vector<int>& trainer_table, unsigned long trainer_index, char outcome){
    
    int trainer_counter = trainer_table[trainer_index];

    if (outcome == 't') {
        if (trainer_counter < 3) trainer_table[trainer_index]++;
    } 

    else {
        if (trainer_counter > 0) trainer_table[trainer_index]--;
    }
}

#endif


