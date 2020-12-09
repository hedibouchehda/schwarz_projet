#include <vector> 
#include <iostream> 
#include <string> 
#include <cmath> 
#include <fstream> 

class Point
{
  private: 
      std::vector<double>       m_coords; 
      int                       m_global_num; 
      int                       m_label; 
      int                       m_num_tags; 
      int                       m_to_send = -1;
      int                       m_to_receive = -1; 
   public:
      Point(double coord_x,double coord_y,int global_num,int label,int num_tags,int to_send,int to_receive);  
      void set_inner_point();
      std::vector<double> get_coords(){return m_coords;}; 
      int get_global_num(){return m_global_num;};
      int get_label(){return m_label;}; 
      int get_num_tags(){return m_num_tags;}; 
      int get_to_send(){return m_to_send;};
      int get_to_receive(){return m_to_receive;};   
};
class Mesh
{
    private:
        std::vector<Point*>         m_list_of_points;
        std::string                 m_input_file;
        int                         m_num_of_elements;
    public: 
        Mesh(std::string input_file); 
        void read_mesh();
        std::vector<Point*> get_list_of_points(){return m_list_of_points;}; 
        int get_num_of_elements(){return m_num_of_elements;};          
};


