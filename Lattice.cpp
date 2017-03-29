//
// Created by Bowen Zhao on 2/10/17.
//

#include "Lattice.h"

namespace MC_Ising{
    Lattice::Lattice(std::string lattice_name, inttype x_num, inttype y_num):
            Lattice_Name(lattice_name),
            X_Num(x_num),
            Y_Num(y_num)
    {
        //The Lattice info
        if (Lattice_Name == "Square") {
            Site_Num = X_Num * Y_Num;
            spin_config = std::vector<inttype>((size_t)Site_Num, 0);
            //std::cout << "number of sites: " << Site_Num << std::endl;
        }
        else{
            //Site_Num = 0;
            throw std::runtime_error("Invalid Lattice Name");
        }

        //initializing the spins
        static boost::random::mt19937 e((unsigned)(time(0)));
        static boost::random::uniform_int_distribution<inttype> Ran_Inispin(0, 1);

        for(auto & spin : spin_config){
            spin = Ran_Inispin(e);
        }


    }

    inttype Lattice::Get_Spin(LatticePair this_pair) {
        inttype this_site = this_pair.first + this_pair.second * X_Num;

        return spin_config[this_site];
    }

    std::vector<MC_Ising::LatticePair> Lattice::Find_Nearest(LatticePair this_pair, inttype nl_type) {
        //temp return vector
        std::vector<LatticePair> temp_return;

        //if (Lattice_Name == "Square") {
            //find the nearest spins
            std::array<inttype, 2> add_array = {-1, 1};

            for(auto add : add_array){
                LatticePair temp_x = std::make_pair((this_pair.first + add + X_Num) % X_Num, this_pair.second);
                //if it has the right spin
                if(this->Get_Spin(temp_x) == nl_type){
                    //add to the return vector
                    temp_return.push_back(temp_x);
                }
            }

            for(auto add : add_array){
                LatticePair temp_y = std::make_pair(this_pair.first, (this_pair.second + add + Y_Num) % Y_Num);
                //if it has the right spin
                if(this->Get_Spin(temp_y) == nl_type){
                    //add to the return vector
                    temp_return.push_back(temp_y);
                }
            }
        //}

        return temp_return;
    }

    LatticePair Lattice::Ran_Site(inttype seed) {
        LatticePair temp_pair;
        //if(Lattice_Name == "Square"){
            static boost::random::mt19937 e((unsigned)(time(NULL) + seed));
            static boost::random::uniform_int_distribution<inttype> Ran_WhichSite(0, Site_Num - 1);

            inttype temp_site = Ran_WhichSite(e);
            temp_pair = std::make_pair(temp_site % X_Num, temp_site / X_Num);
        //}
        return temp_pair;

    }

    void Lattice::Flip_Spin(LatticePair this_pair) {
        //if (Lattice_Name == "Square") {
            auto temp_site = this_pair.first + this_pair.second * X_Num;

            spin_config[temp_site] = (spin_config[temp_site] + 1) % 2;
        //}
    }

    floattype Lattice::Get_TolSpin() {
        floattype temp_spinm =
                static_cast<floattype>(std::accumulate(spin_config.begin(), spin_config.end(), 0.0)) / spin_config.size() * 2.0 - 1.0;

        return temp_spinm;
    }

    void Lattice::Set_Spin(LatticePair this_pair, inttype nl_type) {
        //if (Lattice_Name == "Square") {
            auto temp_site = this_pair.first + this_pair.second * X_Num;

            spin_config[temp_site] = nl_type;
        //}
    }

}
