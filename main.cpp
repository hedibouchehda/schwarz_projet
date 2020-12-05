#include "Sparse.h"

int main()
{
	std::vector<Triplet*> list; 
	Triplet* triplet= new Triplet(1,2,0.5);
	Triplet* triplet1= new Triplet(1,3,0.5);
	//std::cout<<triplet1->get_num_col()<<" "<<triplet->get_num_col()<<std::endl;
	list.push_back(triplet); 
	list.push_back(triplet1);
	triplet->reset(triplet1);   
	//std::cout<<triplet1->get_num_col()<<" "<<triplet->get_num_col()<<std::endl;
	SparseMatrix* sm = new SparseMatrix(6,6); 
	sm->add(3,1,1.);
	sm->add(2,1,1.);
	sm->add(0,1,2.);
	sm->add(2,0,1.);
	sm->add(0,2,1.);
	sm->add(4,0,1.);
	sm->ranging();
	sm->set();
	//sm->print_verification();
	
	std::vector<double> s1 ,s2; 
	for (int i=0;i<6;i++)
	{
		s1.push_back(1);
		s2.push_back(2);
	}
	std::vector<double> result; 
	result = sm->vector_mult(s1);
	//std::cout<<result.size()<<"****"<<std::endl; 
	double res; 
	res = norm(s1);
	//std::cout<<res<<std::endl;
	
	//for (int i=0;i<result.size();i++)
		//std::cout<<result[i]<<std::endl;
	
	
	//sm->print_verification();
	std::vector<double> vect; 
	for (int i=0;i<sm->get_num_cols();i++) 
		vect.push_back(1);
	CG_solver* solver = new CG_solver(); 
	solver->set_problem(sm,vect);
	solver->solve();	
}
/*
int main() 
{
	std::vector<double> ss,sa,res; 
	ss.resize(2);
	sa.resize(2);
	ss[0] = 1; 
	ss[1] = 2; 
	res = vect_sum(ss,sa);

}
*/