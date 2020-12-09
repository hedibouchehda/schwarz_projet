#include <fstream> 
#include <iostream>
#include <string>

int main()
{
    int physical_boundary,fictional_boundary,num_lines,num_cols,recovery,studied_case,num_procs; 
    double Lx,Ly,D,delta_t;
    std::string label;  
    std::ifstream read_inputs; 
    read_inputs.open("inputs.txt");
    read_inputs>>label;
    read_inputs>>Lx;
    read_inputs>>label;
    read_inputs>>Ly; 
    read_inputs>>label;
    read_inputs>>num_lines;
    read_inputs>>label;
    read_inputs>>num_cols;
    read_inputs>>label; 
    read_inputs>>num_procs;
    read_inputs>>label;
    read_inputs>>recovery;
    read_inputs>>label;
    read_inputs>>physical_boundary;
    read_inputs>>label;
    read_inputs>>fictional_boundary;
    read_inputs>>label;
    read_inputs>>studied_case;
    read_inputs>>label;
    read_inputs>>D;
    read_inputs>>label; 
    read_inputs>>delta_t; 
    read_inputs.close(); 
    //filling the input file for partitionning 
    std::ofstream write_input_partitionning; 
    write_input_partitionning.open("../Partitionning_Engine/input.txt");
    write_input_partitionning<<"Lx"<<std::endl;
    write_input_partitionning<<Lx<<std::endl;
    write_input_partitionning<<"Ly"<<std::endl;
    write_input_partitionning<<Ly<<std::endl;
    write_input_partitionning<<"num_lines"<<std::endl;
    write_input_partitionning<<num_lines<<std::endl;
    write_input_partitionning<<"num_cols"<<std::endl;
    write_input_partitionning<<num_cols<<std::endl;
    write_input_partitionning<<"num_procs"<<std::endl;
    write_input_partitionning<<num_procs<<std::endl;
    write_input_partitionning<<"recovery"<<std::endl;
    write_input_partitionning<<recovery<<std::endl;
    write_input_partitionning<<"physical_boundary"<<std::endl;
    write_input_partitionning<<physical_boundary<<std::endl;
    write_input_partitionning<<"fictional_boundary"<<std::endl;
    write_input_partitionning<<fictional_boundary<<std::endl;
    write_input_partitionning.close();
    //filling the input file for heat problem 
    std::ofstream write_input_HeatProblem; 
    write_input_HeatProblem.open("../HeatProblem_Engine/input_problem.txt"); 
    write_input_HeatProblem<<"Lx"<<std::endl;
    write_input_HeatProblem<<Lx<<std::endl;
    write_input_HeatProblem<<"Ly"<<std::endl;
    write_input_HeatProblem<<Ly<<std::endl;
    write_input_HeatProblem<<"case"<<std::endl;
    write_input_HeatProblem<<studied_case<<std::endl;
    write_input_HeatProblem<<"num_lines"<<std::endl;
    write_input_HeatProblem<<num_lines<<std::endl;
    write_input_HeatProblem<<"num_cols"<<std::endl;
    write_input_HeatProblem<<num_cols<<std::endl;
    write_input_HeatProblem<<"D"<<std::endl;
    write_input_HeatProblem<<D<<std::endl;
    write_input_HeatProblem<<"delta_t"<<std::endl;
    write_input_HeatProblem<<delta_t<<std::endl;
    write_input_HeatProblem.close();
}