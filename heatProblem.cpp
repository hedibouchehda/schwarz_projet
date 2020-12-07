#include "heatProblem.h" 

HeatProblem::HeatProblem(std::string input_problem,std::string mesh_file_name,int proc_rank)
{
    m_input_problem = input_problem; 
    m_mesh_file_name = mesh_file_name;
    m_proc_rank = proc_rank;
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
    read_input>>m_Lx; 
    read_input>>label; 
    read_input>>m_Ly;
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
    m_delta_x = m_Lx/(num_cols_global-1); 
    m_delta_y = m_Ly/(num_lines_global-1);  
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
        result = exp(pow(x-m_Lx/2,2))*exp(pow(y-m_Ly/2,2))*cos(2*atan(1)*t);
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
        result = 0;    
        break;
    case 2:
        result = sin(x)+cos(y);
        break;
    case 3:
        if (y==0 || y==m_Ly)
            result = 0;
        else 
            result = 1;
        break;  
    default:
        break;
    }
}
void HeatProblem::get_received_values(std::vector<double>& received_right,std::vector<double>& received_left)
{
    m_to_receive_right = received_right; 
    m_to_receive_left = received_left; 
}
void HeatProblem::build_second_member(double t)
{
    std::vector<Point*> list_of_points = m_mesh->get_list_of_points();
    int index_received_right(0),index_received_left(0); 
    std::vector<double> coords; 
    int label; 
    for (int i=0;list_of_points.size();i++)
    {
        coords = list_of_points[i]->get_coords();
        label = list_of_points[i]->get_label();
        if (label==5)//physical dirichlet   
            m_second_member.push_back(boundary_physical_function(coords[0],coords[1])); 
        else if (label==7)//fictional dirichlet
        {
            if (list_of_points[i]->get_to_receive() == m_proc_rank-1)
            {
                m_second_member.push_back(m_to_receive_left[index_received_left]); 
                index_received_left++; 
            }
            else if (list_of_points[i]->get_to_receive() == m_proc_rank+1)
            {
                m_second_member.push_back(m_to_receive_right[index_received_right]); 
                index_received_right++; 
            }
        }
        else //inner points 
            m_second_member.push_back(second_member_physical_function(coords[0],coords[1],t)+m_u1[i]);
    }
}
void HeatProblem::prepare_sending()
{
    std::vector<Point*> list_of_points = m_mesh->get_list_of_points(); 
    for (int i=0;i<list_of_points.size();i++)
    {
        if (list_of_points[i]->get_label() == 0 && list_of_points[i]->get_num_tags() != 0)
        {
            if (list_of_points[i]->get_to_send() == m_proc_rank+1)
                m_to_send_right.push_back(m_u1[i]); 
            else if (list_of_points[i]->get_to_send() == m_proc_rank-1)
                m_to_send_left.push_back(m_u1[i]); 
        }
    }   
}
