//
// Created by Bowen Zhao on 2/10/17.
//

#include "Calculation.h"

namespace MC_Ising{
    Calculation::Calculation(std::string lattice_name, inttype x_num, inttype y_num, floattype beta, inttype num_CPU):
            Lattice_Name(lattice_name),
            X_Num(x_num),
            Y_Num(y_num),
            Beta(beta),
            Num_CPU(num_CPU),
            This_Lattice(Lattice_Name, x_num, y_num)
    {
        Flip_Ratio = 1 - std::exp(- 2 * Beta);
    }

    void Calculation::Wolff_Update() {
        //Random choosing a site
        const auto ini_site = This_Lattice.Ran_Site(Num_CPU);
        const auto ini_spin = This_Lattice.Get_Spin(ini_site);
        const auto inverse_spin = (ini_spin + 1) % 2;

        This_Lattice.Set_Spin(ini_site, inverse_spin);

        //initializing a stack
        std::stack<LatticePair> pair_stack;
        //put the first element into it
        pair_stack.push(ini_site);

        while(!pair_stack.empty()){
            //Get the element on the top
            LatticePair current_ele;
            current_ele = pair_stack.top();
            pair_stack.pop();

            //find next spin
            static boost::random::mt19937 e((unsigned)(time(NULL) + Num_CPU));
            static boost::random::uniform_real_distribution<floattype> Ran_Ifflip(0, 1);

            auto nearest_array = This_Lattice.Find_Nearest(current_ele, ini_spin);
            for (auto element : nearest_array) {
                if (Ran_Ifflip(e) < Flip_Ratio) {
                    pair_stack.push(element);
                    //flip this spin
                    This_Lattice.Set_Spin(element, inverse_spin);
                }
            }
        }

    }

    void Calculation::Measure() {
        auto temp_m = This_Lattice.Get_TolSpin();
        Sweep_Spinm.push_back(std::abs(temp_m));
        Sweep_Spinm2.push_back(temp_m * temp_m);
        Sweep_Spinm4.push_back(temp_m * temp_m * temp_m * temp_m);
    }

    void Calculation::MeasureBin() {
        auto temp_spinm = std::accumulate(Sweep_Spinm.begin(), Sweep_Spinm.end(), 0.0) / Sweep_Spinm.size();
        Sweep_Spinm.clear();

        auto temp_spinm2 = std::accumulate(Sweep_Spinm2.begin(), Sweep_Spinm2.end(), 0.0) / Sweep_Spinm2.size();
        Sweep_Spinm2.clear();

        auto temp_spinm4 = std::accumulate(Sweep_Spinm4.begin(), Sweep_Spinm4.end(), 0.0) / Sweep_Spinm4.size();
        Sweep_Spinm4.clear();

        char file_data[100];
        snprintf(file_data, 100, "Ising_%ld_%ld_%.4f_%ld.txt", X_Num, Y_Num, Beta, Num_CPU);
        std::ofstream outfile;
        outfile.open(file_data, std::ofstream::out | std::ofstream::app);
        outfile.setf(std::ios::fixed);
        outfile.precision(16);
        outfile << temp_spinm << "\t"
                << temp_spinm2 << "\t"
                << temp_spinm4 << std::endl;
        outfile.close();
    }

    void Calculation::WriteConfig() {
        //char config_data[100];
        //snprintf(config_data, 100, "IsingConfig_%ld_%ld_%.4f_%ld.txt", X_Num, Y_Num, Beta, Num_CPU);
        std::ofstream OutConfig;

        OutConfig.open("TrainConfig.txt", std::ofstream::out | std::ofstream::app);
        for(auto spin : This_Lattice.spin_config){
            OutConfig << spin << "\t";
        }
        OutConfig << std::endl;
        OutConfig.close();

        std::ofstream OutLabel;

        OutLabel.open("TrainLabel.txt", std::ofstream::out | std::ofstream::app);
        //Higher T disordered phase
        if(this->Beta <= 0.4407){
            OutLabel << 1 << "\t" << Beta <<std::endl;
        }
        //Lower T ordered phase
        else{
            OutLabel << 0 << "\t" << Beta <<std::endl;
        }

        OutLabel.close();
    }

}