//
// Created by Bowen Zhao on 2/10/17.
//
#pragma once

#include <string>
#include "Config.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <array>
#include <numeric>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

namespace MC_Ising{
    class Calculation;

    class Lattice {
    public:

    private:

        //lattice info
        std::string Lattice_Name;
        inttype Site_Num;
        inttype X_Num;
        inttype Y_Num;

        std::vector<inttype> spin_config;

    public:
        //insturctor and destructor
        Lattice(std::string lattice_name, inttype x_num, inttype y_num);
        ~Lattice(){};

        //Find the nearest spins
        std::vector<MC_Ising::LatticePair> Find_Nearest(LatticePair this_pair, inttype nl_type);

        //Get the spin config
        inttype Get_Spin(LatticePair this_pair);

        //random choosing a site
        LatticePair Ran_Site(inttype seed);

        //Flip one spin
        void Flip_Spin(LatticePair this_pair);

        //set one spin
        void Set_Spin(LatticePair this_pair, inttype nl_type);

        //Get total spin
        floattype Get_TolSpin();

        friend class Calculation;
    };
}




