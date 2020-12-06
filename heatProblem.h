#include "Mesh.h"
#include "Sparse.h" 

class HeatProblem
{
    private: 
        SparseMatrix*                   m_matrix;
        std::vector<double>             m_u1,m_u2; 
        std::vector<double>             m_second_member; 
        std::vector<double>             m_to_send_right,m_to_send_left; 
        std::vector<double>             m_to_receive_right,m_to_receive_left; 
        int                             m_studied_case,m_size_of_col; 
        std::string                     m_input_problem,m_mesh_file_name;
        Mesh*                           m_mesh;
        double                          m_delta_x,m_delta_y,m_delta_t,m_D; 
    public:
        HeatProblem(std::string,std::string); 
        void set_mesh(); 
        void set_params(); 
        void set_problem();
        void build_matrix();
        void get_received_values(std::vector<double>&,std::vector<double>&);
        double boundary_physical_function(double,double); 
        double second_member_physical_function(double,double,double); 
        void build_second_memeber();
        std::vector<double> get_to_send_right(){return m_to_send_right;};
        std::vector<double> get_to_send_left(){return m_to_send_left;};
};