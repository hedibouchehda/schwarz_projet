#include "heatProblem.h" 

HeatProblem::HeatProblem(std::string input_problem,std::string mesh_file_name)
{
    m_input_problem = input_problem; 
    m_mesh_file_name = mesh_file_name;
}
void HeatProblem::set_mesh()
{
    m_mesh  = new Mesh(m_mesh_file_name); 
    m_mesh->read_mesh();
}
void HeatProblem::set_params()
{
    std::ifstream read_input(m_input_problem.c_str()); 
    std::string label;
    int num_cols_global,num_lines_global; 
    read_input>>label; 
    read_input>>m_studied_case; 
    read_input>>label; 
    read_input>>num_lines_global; 
    read_input>> label; 
    read_input>>num_cols_global; 
    read_input>>label;
    read_input>>m_D; 
    read_input>>label; 
    read_input>>m_delta_t;
    m_delta_x = 1./(num_cols_global-1); 
    m_delta_y = 1./(num_lines_global-1);  
    m_size_of_col = num_lines_global;
}
void HeatProblem::set_problem()
{
    set_mesh(); 
    set_params();
}
void HeatProblem::build_matrix()
{
    double diagonal_value = 1 + 2*m_D*m_delta_t*(1./pow(m_delta_x,2) + 1./pow(m_delta_y,2));
    double same_col_value = -m_delta_t*m_D/pow(m_delta_x,2); 
    double different_col_value = -m_delta_t*m_D/pow(m_delta_y,2);
    int size = m_mesh->get_num_of_elements(); 
    m_matrix = new SparseMatrix(size,size); 
    std::vector<Point*> list_of_points = m_mesh->get_list_of_points(); 
    for (int i=0;i<size;i++)
    {
        if (list_of_points[i]->get_label()==0)//inner point
        {
            m_matrix->add(i,i,diagonal_value);
            m_matrix->add(i,i+1,same_col_value);
            m_matrix->add(i,i-1,same_col_value);
            m_matrix->add(i,i+m_size_of_col,different_col_value);  
            m_matrix->add(i,i-m_size_of_col,different_col_value);
        }
        else //boundary dirichlet (fictional and physical)
        {
            m_matrix->add(i,i,1.);
        }
    }
    m_matrix->set();
}
double HeatProblem::second_member_physical_function(double x,double y,double t)
{
    double result;
    switch (m_studied_case)
    {
    case 1:
        result = 2*(x-x*x+y-y*y);
        break;
    case 2:
        result = sin(x)+cos(y);
        break;
    case 3: 
        result = exp(pow(x-1./2,2))*exp(pow(y-1./2,2))*cos(2*atan(1)*t);
    default:
        break;
    }
    return result;
}
double HeatProblem::boundary_physical_function(double x,double y)
{
    double result; 
    switch (m_studied_case)
    {
    case 1:
        
        break;
    
    default:
        break;
    }
}