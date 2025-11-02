#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim_bp.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> // for setprecision


using namespace std;


/*  argc holds the number of command line arguments
    argv[] holds the commands themselves

    Example:-
    sim bimodal 6 gcc_trace.txt
    argc = 4
    argv[0] = "sim"
    argv[1] = "bimodal"
    argv[2] = "6"
    ... and so on
*/
int main (int argc, char* argv[])
{
    FILE *FP;               // File handler
    char *trace_file;       // Variable that holds trace file name;
    bp_params params;       // look at sim_bp.h header file for the the definition of struct bp_params
    char outcome;           // Variable holds branch outcome
    unsigned long int addr; // Variable holds the address read from input file

    unsigned long num_predictions = 0; 
    unsigned long num_mispredictions = 0;
    
    if (!(argc == 4 || argc == 5 || argc == 7))
    {
        printf("Error: Wrong number of inputs:%d\n", argc-1);
        exit(EXIT_FAILURE);
    }
    
    params.bp_name  = argv[1];
    
    // strtoul() converts char* to unsigned long. It is included in <stdlib.h>
    if(strcmp(params.bp_name, "bimodal") == 0)              // Bimodal
    {
        if(argc != 4)
        {
            printf("Error: %s wrong number of inputs:%d\n", params.bp_name, argc-1);
            exit(EXIT_FAILURE);
        }
        params.M2       = strtoul(argv[2], NULL, 10);
        trace_file      = argv[3];
        printf("COMMAND\n%s %s %lu %s\n", argv[0], params.bp_name, params.M2, trace_file);
    }
    else if(strcmp(params.bp_name, "gshare") == 0)          // Gshare
    {
        if(argc != 5)
        {
            printf("Error: %s wrong number of inputs:%d\n", params.bp_name, argc-1);
            exit(EXIT_FAILURE);
        }
        params.M1       = strtoul(argv[2], NULL, 10);
        params.N        = strtoul(argv[3], NULL, 10);
        trace_file      = argv[4];
        printf("COMMAND\n%s %s %lu %lu %s\n", argv[0], params.bp_name, params.M1, params.N, trace_file);

    }
    else if(strcmp(params.bp_name, "hybrid") == 0)          // Hybrid
    {
        if(argc != 7)
        {
            printf("Error: %s wrong number of inputs:%d\n", params.bp_name, argc-1);
            exit(EXIT_FAILURE);
        }
        params.K        = strtoul(argv[2], NULL, 10);
        params.M1       = strtoul(argv[3], NULL, 10);
        params.N        = strtoul(argv[4], NULL, 10);
        params.M2       = strtoul(argv[5], NULL, 10);
        trace_file      = argv[6];
        printf("COMMAND\n%s %s %lu %lu %lu %lu %s\n", argv[0], params.bp_name, params.K, params.M1, params.N, params.M2, trace_file);

    }
    else
    {
        printf("Error: Wrong branch predictor name:%s\n", params.bp_name);
        exit(EXIT_FAILURE);
    }
    
    // Open trace_file in read mode
    FP = fopen(trace_file, "r");

    //cout<<params.M2<<endl;
    unsigned long table_size = 1 << params.M2 ;
    //cout<<table_size<<endl;
    vector<int> v(table_size, 2);
    //cout<<v[3]<<endl;


    
    
    if(FP == NULL)
    {
        // Throw error and exit if fopen() failed
        printf("Error: Unable to open file %s\n", trace_file);
        exit(EXIT_FAILURE);
    }
    
    char str[2];
    while(fscanf(FP, "%lx %s", &addr, str) != EOF)
    {
        
        outcome = str[0];
        //if (outcome == 't')
        //    printf("%lx %s\n", addr, "t");           // Print and test if file is read correctly
        //else if (outcome == 'n')
        //    printf("%lx %s\n", addr, "n");          // Print and test if file is read correctly
        ///*************************************
        //    Add branch predictor code here
        //**************************************/

        //cout<<addr<<endl;

        unsigned long shifted_by_2 = addr >> 2;
        
        unsigned long table_index = shifted_by_2 & (table_size -1);

        //cout<<shifted_by_2<<endl;
        //cout<<table_index<<endl;
        //cout<<v[table_index]<<endl;
        //cout<<"XXXXXXXXXXXXXX"<<endl;


        
        num_predictions++;

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

    cout<<"OUTPUT"<<endl;
    cout<<" number of predictions:    "<<num_predictions<<endl;
    cout<<" number of mispredictions: "<<num_mispredictions<<endl;

    double misprediction_rate = (static_cast<double>(num_mispredictions) / num_predictions) * 100.0;
    cout << fixed << setprecision(2);  // show 2 digits after decimal
    cout << " misprediction rate:       " << misprediction_rate << "%" << endl;
    cout << "FINAL BIMODAL CONTENTS"<<endl;
    for ( int i = 0; i < table_size; ++i) {
        {
            std::cout<< i << "\t" << (int)v[i] << std::endl;
        }
    }

    return 0;
}


