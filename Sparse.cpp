#include "Sparse.h" 

Triplets::Triplets(int num_rows, int num_cols)
{
    m_num_rows = num_rows ; 
    m_num_cols = num_cols ; 
    m_entry_data = (float*) calloc(3*sizeof(float)) ;
    m_IA = (float*) calloc((m_num_rows+1)*sizeof(float)) ; 
}

void Triplets::add(int i , int j , float values) 
{
    m_triplets_size++ ; 
    realloc(m_entry_data , sizeof(m_entry_data)+3*sizeof(float)) ; 
    m_entry_data[m_triplets_size-1] = (float) i ;
    m_entry_data[m_triplets_size] = (float) j ;
    m_entry_data[m_triplets_size+1] = values ;  
}

void Triplets::ranging() 
{
    float a1 , a2 , a3 ; 
    float min ; 
    int index ;
    int i ; 
    for  (i = 0 ; i<m_triplets_size ; i++) 
    {
        min = m_entry_data[3*i] ;
	index = i ;
        for (int j=i ; j<m_triplets_size ; j++)
        {
            if (m_entry_data[3*j]< min)
            {
                min = m_entry_data[3*j] ;
                index =  j ; 
                break ;  
            }
        }
        a1 = m_entry_data[3*index] ; 
        a2 = m_entry_data[3*index+1] ; 
        a3 = m_entry_data[3*index+2] ; 
        m_entry_data[3*index] = m_entry_data[3*i] ;
        m_entry_data[3*index+1] = m_entry_data[3*i+1] ;
        m_entry_data[3*index+2] = m_entry_data[3*i+2] ; 
        m_entry_data[3*i] = a1 ; 
        m_entry_data[3*i+1] = a2 ;
        m_entry_data[3*i+2] = a3 ;

    }
}

void Triplets::settriplet() 
{
    ranging() ;
    m_values = (float*) calloc(m_triplets_size*sizeof(float)) ;
    m_IJ = (float*) calloc(m_triplets_size*sizeof(float)) ;
    m_IA[0] = 0 ; 
    int num_elements_per_row;
    int i,j ;
    int index ;  
    i=0 ;
    while (i<m_triplets_size-1)
    {
        j=i+1 ; 
        num_elements_per_row = 1 ;
        while (m_entry_data[3*j] == m_entry_data[3*i])
        {
            num_elements_per_row++ ;
            j++ ;  
        }
        index = (int) m_entry_data[3*i] ;
        i = j ; 
        m_IA[index+1] = num_elements_per_row ; 
    }  
    if (m_entry_data[3*(m_triplets_size-2)] == m_entry_data[3*(m_triplets_size-1)]) 
    {
        index = (int) m_entry_data[3*(m_triplets_size-1)] ; 
        m_IA[index+1] = m_IA[index+1] +1 ; 
    }
    else 
    {
        index = (int) m_entry_data[3*(m_triplets_size-1)] ; 
        m_IA[index+1] = 1 ; 
    }
    for (int i=0 ; i<m_triplets_size ; i++) 
    {
        m_values[i] = m_entry_data[3*i+2] ; 
        m_IJ[i] = (int) m_entry_data[3*i+1] ; 

    }
}

SparseMAtrix::SparseMatrix(int num_rows , int num_cols)
{
  m_num_rows = num_rows ;
  m_num_cols = num_cols ;
  Triplet = Triplets(num_rows , num_cols) ; 
}

void SparseMatrix::add_value(int i , int j , float value)
{
  Triplet.add(i,j,value) ; 
}

void SparseMatrix::set_matrix()
{
  Triplet.settriplet() ;
  m_IA = Triplet.get_m_IA() ;
  m_IJ = Triplet.get_m_IJ() ;
  m_values = Triplet.get_m_values() ; 
}

float* SparseMatrix::vector_mult(float* x)
{
  float* result ;
  result = (float*) calloc(n_num_rows*sizeof(float)) ;

  int num_element_per_row ; 
  int index = 0 ; 
  for (int i=0 ; i<m_num_rows ; i++)
    {
      num_element_per_row = m_IA[i+1] - m_IA[i] ;
      result[i] = 0 ; 
      for (int j=0 ; j<num_element_per_row ; j++)
	{
	  index = index + j ;
	  result[i] += m_values[index]*x[m_IJ[index]] ;
	}
      index++ ; 
    }
  
}






