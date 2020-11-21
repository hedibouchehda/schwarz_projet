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
        float* m_IA ; 
        float* m_IJ ; 
        float* m_values ;
        void ranging() ; 
    public: 
        Triplets(int m_num_rows, int m_num_cols) ;  
        void add(int i , int j , float value) ;
        // sequential 
        void settriplet() ;
        //MPI  
        //void MPI_settriplet() ;
        //cuda  
        //void cuda_settriplet() ;

};

/*
class SparseMatrix
{
    private: 
        int m_number_rows  , m_number_columns ; 
        float* m_values ; 
        float* m_IA ; 
        float* m_IJ ; 
    public: 
        SparseMatrix(int number_rows , int number_columns) ; 
        void add_value(int i , int j , float value) ; 
        void set_matrix() ;
        float* cuda_vector_mult(float* vect) ; 
        float* vector_mult(float* vect)

}; 

*/