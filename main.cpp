#include "Lattice.h"
#include "Config.h"
#include "Calculation.h"
#include <iostream>

int main(int argc, char *argv[]) {
    //store the argument
    std::vector<std::string> main_arg;
    for (MC_Ising::inttype nl_arg = 0; nl_arg != argc; ++nl_arg) {
        std::string temp_string(argv[nl_arg]);
        main_arg.push_back(temp_string);
    }
    //Parameters
    MC_Ising::inttype num_x = std::stoul(main_arg[1]);
    MC_Ising::inttype num_y = std::stoul(main_arg[2]);
    MC_Ising::floattype beta = std::stod(main_arg[3]);
    MC_Ising::inttype num_sweep = std::stoul(main_arg[4]);
    MC_Ising::inttype num_bin = std::stoul(main_arg[5]);
    MC_Ising::inttype num_warmup = std::stoul(main_arg[6]);
    MC_Ising::inttype num_CPU = std::stoul(main_arg[7]);

    //establish the calculate class
    std::cout << "#parameter:" << std::endl;
    std::cout << "#N_x = " << num_x << std::endl;
    std::cout << "#N_y = " << num_y << std::endl;
    std::cout << "#Beta = " << beta << std::endl;
    std::cout << "#num_warmup = " << num_warmup << std::endl;
    std::cout << "#num_sweep = " << num_sweep << std::endl;
    std::cout << "#num_CPU = " << num_CPU << std::endl;

    auto betavector = std::vector<double>();
    for(double nl_beta = 0.001; nl_beta <=0.01; nl_beta += 0.001) {
        betavector.push_back(nl_beta);
    }
    for(auto nl_beta : betavector){
        beta = nl_beta;
        MC_Ising::Calculation LittleLion("Square", num_x, num_y, beta, num_CPU);

        for (MC_Ising::inttype loop = 0; loop <= num_warmup - 1; loop++) {
            LittleLion.Wolff_Update();
            if (loop / (num_warmup / 10) * (num_warmup / 10) == loop) {
                std::cout << "#warmup " << loop << "/" << num_warmup << std::endl;
            }
        }

        for (MC_Ising::inttype nl_bin = 0; nl_bin <= num_bin - 1; nl_bin++) {
            for (int nl_sweep = 0; nl_sweep <= num_sweep - 1; nl_sweep++) {
                //for (int nl = 0; nl != 10; nl++) {
                LittleLion.Wolff_Update();
                //}
                LittleLion.Measure();
            }
            //test.Measure_BinEnergy(nl_bin);
            //LittleLion.MeasureBin();
            if (nl_bin / (num_bin / 10)* (num_bin / 10) == nl_bin) {
                std::cout << "#bin #" << nl_bin << "/" << num_bin << " measurement process is ongoing!"<< std::endl;
            }
            LittleLion.WriteConfig();
        }
    }


    /*
    //Get the Data
    std::ifstream In_File;
    char file_name[100];
    snprintf(file_name, 100, "Ising_%ld_%ld_%.4f_%ld.txt", num_x, num_y, beta, num_CPU);
    In_File.open(file_name);

    std::vector<MC_Ising::floattype> Bin_Spinm;
    std::vector<MC_Ising::floattype> Bin_Spinm2;
    std::vector<MC_Ising::floattype> Bin_Spinm4;

    while(!In_File.eof()){

        MC_Ising::floattype temp_m = 0;
        MC_Ising::floattype temp_m2 = 0;
        MC_Ising::floattype temp_m4 = 0;

        In_File >> temp_m;
        In_File >> temp_m2;
        In_File >> temp_m4;

        if(temp_m == 0 && temp_m2 == 0 && temp_m4 == 0){
            break;
        }

        Bin_Spinm.push_back(temp_m);
        Bin_Spinm2.push_back(temp_m2);
        Bin_Spinm4.push_back(temp_m4);
    }
    auto average_spinm = std::accumulate(Bin_Spinm.begin(), Bin_Spinm.end(), 0.0) / Bin_Spinm.size();
    auto average_spinm2 = std::accumulate(Bin_Spinm2.begin(), Bin_Spinm2.end(), 0.0) / Bin_Spinm2.size();
    auto average_spinm4 = std::accumulate(Bin_Spinm4.begin(), Bin_Spinm4.end(), 0.0) / Bin_Spinm4.size();

    std::cout << "m = " << average_spinm << "\t exact: " << std::pow(1 - pow(sinh(2 * beta), -4.0), 0.125)<< std::endl;
    std::cout << "m2 = " << average_spinm2 << std::endl;
    std::cout << "m4 = " << average_spinm4 << std::endl;
    */
    return 0;


}