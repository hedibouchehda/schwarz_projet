#include "Sparse.h"

using namespace std;

Triplet::Triplet(int num_row,int num_col,double value)
{
    m_num_row= num_row;
    m_num_col= num_col;
    m_value = value;
}
void Triplet::reset(Triplet* triplet)
{
	m_num_row = triplet->get_num_row(); 
	m_num_col = triplet->get_num_col(); 
	m_value = triplet->get_value();
}
SparseMatrix::SparseMatrix(int num_rows,int num_cols)
{
	m_num_rows = num_rows; 
	m_num_cols = num_cols;
	m_IA.resize(m_num_rows+1);
}
void SparseMatrix::add(int i,int j,double value)
{
	m_list_of_triplets.push_back(new Triplet(i,j,value));
}
void SparseMatrix::ranging()
{
	Triplet* min = new Triplet();
	int min_position; 
	for (int i=0;i<m_list_of_triplets.size();++i)
	{
		min->reset(m_list_of_triplets[i]);
		min_position = i; 
		m_IA[m_list_of_triplets[i]->get_num_row()+1]++;
		for (int j=i+1;j<m_list_of_triplets.size();i++) 
		{
			if (m_list_of_triplets[j]->get_num_row()<=min->get_num_row())
				{
					min->reset(m_list_of_triplets[j]);
					min_position = j;
				}
		}
		m_list_of_triplets[min_position]->reset(m_list_of_triplets[i]); 
		m_list_of_triplets[i]->reset(min);
	}
}
