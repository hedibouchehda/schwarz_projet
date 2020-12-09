#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class Triplet
{
private:
    int 		m_num_row , m_num_col; 
	double 		m_value; 
public:
    Triplet(int,int,double);
    Triplet(){}; 
    void reset(Triplet*);
    int get_num_row(){return m_num_row;}; 
    int get_num_col(){return m_num_col;};
    double get_value(){return m_value;};
};
class SparseMatrix
{
private:
    int 							m_num_rows, m_num_cols;
    std::vector<Triplet*> 		    m_list_of_triplets;
    std::vector<double>    		    m_values;
    std::vector<int>      			m_IA,m_JA;  
public:
    SparseMatrix(int,int);
    void add(int,int,double);
    void set_matrix();
    void print_verification();
    void ranging(); 
    void set();
    std::vector<double> vector_mult(std::vector<double>&);
    int get_num_rows(){return m_num_rows;};
    int get_num_cols(){return m_num_cols;};
};
class CG_solver
{
private:
    SparseMatrix* 				m_A;
    std::vector<double>         m_X;
    std::vector<double>         m_b;
    double          			m_tolerance;
    double                      m_precison; 
    int            				m_num_iteration_max;
    int                         m_num_iteration; 
    
public:
    CG_solver();
    CG_solver(int,double);
    void set_problem(SparseMatrix*,std::vector<double>&);
    void solve();
    std::vector<double> get_solution(){return m_b;};
    void details(); 
};
/*
class BICGSTAB_solver
{
private:
    SparseMatrix* 				 m_A;
    std::vector<double>*         m_X;
    std::vector<double>*         m_b;
    double                      tolerance;
    int                         num_iteration_max;
public:
    BICGSTAB_solver(SparseMatrix*,std::vector<double>*);
    void solve();
    std::vector<double>* get_solution(){return m_b;};
};
*/
double dot_product (std::vector<double>&,std::vector<double>&);
std::vector<double> vect_sum(std::vector<double>&,std::vector<double>&);
std::vector<double> dot_real_vect (double,std::vector<double>&);
double norm(std::vector<double>&);


