
/*
#include "Sparse.h"
#include "partitions.h"
#include "Mesh.h"
*/
/*
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
*/
/*
int main() 
{tif
                    {
                      for (int k=0 ; k<num_lines; k++) 
                        {if (k==0){write_mesh<<j*delta_x<<" "<<k*delta_y<<" "<<0<<" "<<k+j*num_lines<<" "<<boundary_physical<<" "<<0<<endl ;}//bord haut
                          else if (k==num_lines-1){write_mesh<<j*delta_x<<" "<<k*delta_y<<" "<<0<<" "<<k+j*num_lines<<" "<<boundary_physical<<" "<<0<<endl ;}//bord bas
                          else {write_mesh<<j*delta
	ss[0] = 1; 
	ss[1] = 2; 
	res = vect_sum(ss,sa);

}
*/
/*
int main()
{	
	build_meshes("input.txt");
	Mesh* mesh = new Mesh("proc_num_0.In");
	mesh->read_mesh();
	return 0;
}
*/

//#include "Mesh.h"
#include "../HeatProblem_Engine/heatProblem.h" 

int main()
{
	/* verification point class
	std::vector<double> coords; 
	Point* pt = new Point(1.2,2.2,50,0,1,-1,3);
	coords = pt->get_coords() ;
	std::cout<<coords[0]<<" "<<coords[1]<<" "<<pt->get_global_num()<<" "<<pt->get_label()<<" "<<pt->get_num_tags()<<" "
				<<pt->get_to_send()<<" "<<pt->get_to_receive()<<std::endl;
	*/
/*
std::vector<Point*> list_of_points; 
Mesh* mesh = new Mesh("testing.txt");
mesh->read_mesh(); 
std::cout<<mesh->get_num_of_elements()<<std::endl;
list_of_points = mesh->get_list_of_points(); 
for (int i=0;i<list_of_points.size();i++) 
	{
	std::vector<double> coords; 
	coords = list_of_points[i]->get_coords();
	std::cout<<coords[0]<<" "<<coords[1]<<" "<<list_of_points[i]->get_global_num()<<" "<<list_of_points[i]->get_label()<<" "<<list_of_points[i]->get_num_tags()<<" "
				<<list_of_points[i]->get_to_send()<<" "<<list_of_points[i]->get_to_receive()<<std::endl;
	}
*/
	HeatProblem* hp = new HeatProblem("input_problem.txt","proc_num_1.In",1);
	hp->set_problem(); 
	hp->initialize();
	hp->build_matrix();
	hp->build_second_member(0.01);

}