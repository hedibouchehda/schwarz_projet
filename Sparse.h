#include <vector>
#include <algorithm> 
#include <stdlib.h> 
#include <stdio.h> 
 

class Triplets
{
    private:
        int m_num_cols ,m_num_rows ; 
        int m_triplets_size ; 
        float* m_entry_data ; 
        int* m_IA ; 
        int* m_IJ ; 
        float* m_values ;
        void ranging() ; 
    public: 
        Triplets(int m_num_rows, int m_num_cols) ;  
        void add(int i , int j , float value) ; 
        void settriplet() ;
        int* get_m_IA() {return m_IA ; } ;
        int* get_m_IJ() {return m_IJ ; } ;
        float* get_m_values(){return m_values ; } ; 
};


class SparseMatrix
{
    private: 
        int m_number_rows  , m_number_columns ; 
        Triplets Triplet ;  
        float* m_values ; 
        float* m_IA ; 
        float* m_IJ ; 
    public: 
        SparseMatrix(int number_rows , int number_columns) ; 
        void add_value(int i , int j , float value) ; 
        void set_matrix() ; 
        float* vector_mult(float* vect) ;

};

class Solver
{
protected : 
  SparseMatrix* m_A ;
  float* m_X ;
  float* m_b ; 
public :
  Solver(SparseMatrix* A , float* m_b ) ;
  virtual void solve() ;
  virtual float* get_solution() ; 
};

class CG_solver : public Solver 
{
public :
  CG_solver(SparseMatrix* A, float* m_b) ;
  virtual void solve() ;
};

class BICGSTAB_solver : public Solver
{
public:
  BICGSTAB_solver() ;
  virtual void solve() ; 
};


