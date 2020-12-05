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
		for (int j=i+1;j<m_list_of_triplets.size();j++) 
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
void SparseMatrix::set()
{
	for (int i=0;i<m_list_of_triplets.size();i++)
	{
		m_IA[m_list_of_triplets[i]->get_num_row()+1]++;
		m_JA.push_back(m_list_of_triplets[i]->get_num_col()); 
		m_values.push_back(m_list_of_triplets[i]->get_value());
	}
	for (int i=1;i<m_IA.size();i++)
		m_IA[i]+=m_IA[i-1];
	m_list_of_triplets.clear();
	  
}
std::vector<double> SparseMatrix::vector_mult(std::vector<double>& vect) 
{
	std::vector<double> result;
	result.resize(m_num_rows);
	int num_cols;
	int start_row(0);   
	for (int i=1;i<m_IA.size();i++)
	{
		num_cols = m_IA[i]-m_IA[i-1]; 
		for (int j=0;j<num_cols;j++)
		{
			result[i-1] += m_values[start_row]*vect[m_JA[start_row]];
			start_row++;
		}
	}
	return result;
}
void SparseMatrix::print_verification()
{
	for(int i=0;i<m_IA.size();++i)
	{
		std::cout<<m_IA[i]<<std::endl;
	}
}
double dot_product(std::vector<double>& vect1 ,std::vector<double>& vect2) 
{
	double result(0); 
	for (int i=0;i<vect1.size();i++) 
		result += vect1[i]*vect2[i];  
}
std::vector<double> vect_sum(std::vector<double>& vect1, std::vector<double>& vect2)
{
	std::vector<double> result;   
	for (int i=0;i<vect1.size();i++)
		result.push_back(vect1[i]+vect2[i]); 
	return result;
}
std::vector<double> dot_real_vect(double alpha,std::vector<double>& vect ) 
{
	std::vector<double> result;
	for (int i=0;i<vect.size();i++) 
		result.push_back(alpha*vect[i]); 
	return result;
}
double norm(std::vector<double>& vect) 
{
	return sqrt(dot_product(vect,vect));
}
CG_solver::CG_solver()
{
	m_tolerance = 1e-7;
	m_num_iteration_max = 100000;
}
CG_solver::CG_solver(int num_iteration_max,double tolerance)
{
	m_tolerance = tolerance; 
	m_num_iteration_max = num_iteration_max;
}
void CG_solver::set_problem(SparseMatrix* A,std::vector<double>& b)
{
	m_A = A; 
	m_b = b; 
}
void CG_solver::details()
{
	std::cout<<"la précison : "<<m_precison<<std::endl; 
	std::cout<<"nombre d'itération : "<<m_num_iteration<<std::endl;
}
void CG_solver::solve()
{
	std::vector<double> x0,r0,p0,x1,r1,p1;
	double alpha,beta;
	int k(0); 
	x0.resize(0);
	for (int i=0;i<m_b.size();i++)
	{
		r0.push_back(m_b[i]);
		p0.push_back(m_b[i]);
	}	
	while (k<=m_num_iteration_max && norm(r0)>m_precison)
	{
		std::vector<double> Ap0 = m_A->vector_mult(p0) ;
		alpha = dot_product(r0,r0)/dot_product(p0,Ap0);
		std::vector<double> alpha_p0 = dot_real_vect(alpha,p0); 
		x1 = vect_sum(x0,alpha_p0);
		std::vector<double> alpha_Ap0 = dot_real_vect(-alpha,Ap0);  
		r1 = vect_sum(r0,alpha_Ap0);
		beta = dot_product(r1,r1)/dot_product(r0,r0);
		std::vector<double> beta_p0 = dot_real_vect(beta,p0);
		p1 = vect_sum(r1,beta_p0);
		k++;   	
		r0 = r1;	 
		p0 = p1; 
		x0 = x1;
	}
	m_num_iteration = k; 
	m_precison = norm(r0);
}

