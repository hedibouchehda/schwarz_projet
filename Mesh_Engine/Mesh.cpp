#include "Mesh.h" 

Point::Point(double coord_x,double coord_y,int global_num,int label,int num_tags,int to_send,int to_receive)
{
  m_coords.push_back(coord_x); 
  m_coords.push_back(coord_y); 
  m_global_num = global_num; 
  m_label = label;
  m_num_tags = num_tags; 
  m_to_send = to_send; 
  m_to_receive = to_receive; 
}
Mesh::Mesh(std::string input_file)
{
  m_input_file = input_file; 
}
void Mesh::read_mesh() 
{
  std::ifstream read(m_input_file.c_str());
  read>>m_num_of_elements; 
  double coord_x,coord_y,coord_z; 
  int num_global,label,num_tags;
  int tag; 
  for (int i=0;i<m_num_of_elements;i++)
  {
    read>>coord_x; 
    read>>coord_y; 
    read>>coord_z; 
    read>>num_global; 
    read>>label; 
    read>>num_tags;
    //TODO : add Neumann conditions handeling 
    if (num_tags != 0)
    {
      if (label == 7)
      {
        read>>tag;
        m_list_of_points.push_back(new Point(coord_x,coord_y,num_global,label,num_tags,-10,tag)); 
      }
      else if (label == 0)
      {
        read>>tag;
        m_list_of_points.push_back(new Point(coord_x,coord_y,num_global,label,num_tags,tag,-10));
      }
    }
    else 
      m_list_of_points.push_back(new Point(coord_x,coord_y,num_global,label,num_tags,-10,-10));
  } 
}