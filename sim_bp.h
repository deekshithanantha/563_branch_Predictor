#ifndef SIM_BP_H
#define SIM_BP_H
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>

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

#endif


