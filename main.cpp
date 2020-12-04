#include "Sparse.h"

int main()
{
	std::vector<Triplet*> list; 
	Triplet* triplet= new Triplet(1,2,0.5);
	Triplet* triplet1= new Triplet(1,3,0.5);
	std::cout<<triplet1->get_num_col()<<" "<<triplet->get_num_col()<<std::endl;
	list.push_back(triplet); 
	list.push_back(triplet1);
	triplet->reset(triplet1);   
	std::cout<<triplet1->get_num_col()<<" "<<triplet->get_num_col()<<std::endl;
	SparseMatrix* sm = new SparseMatrix(5,6); 
	sm->add(3,1,5.4);
	sm->add(2,1,5.4);
	sm->add(1,1,5.4);
	sm->add(2,1,5.4);
	sm->ranging();
	

}

