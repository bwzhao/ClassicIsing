//
// Created by Bowen Zhao on 2/10/17.
//
#pragma once

#include <array>
#include <vector>
#include <string>
#include "Config.h"
#include "Lattice.h"
#include <stack>
#include <numeric>
#include <cmath>
#include <fstream>

namespace MC_Ising{
    class Calculation {
    private:
        //lattice info
        std::string Lattice_Name;

        //system parameters
        floattype Beta;
        Lattice This_Lattice;
        inttype X_Num;
        inttype Y_Num;

        floattype Flip_Ratio;

        inttype Num_CPU;

        //warehouse
        std::vector<floattype> Sweep_Spinm;
        std::vector<floattype> Sweep_Spinm2;
        std::vector<floattype> Sweep_Spinm4;

    public:
        Calculation(std::string lattice_name, inttype x_num, inttype y_num, floattype beta, inttype num_CPU);

        void Wolff_Update();

        void Measure();

        void MeasureBin();

        void WriteConfig();

    };
}


