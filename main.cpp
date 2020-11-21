#include "partitions.h"

int main()
{
    /*std::string str ; 
    str = std::to_string(1.0) ; 
    std::cout<<str<<std::endl ;
    */
    build_meshes("input.txt") ;
    int* nx_local ; 
    int* indices_to_send_right=new int[10] ; 
    int* indices_to_send_left=new int[10] ;
    read_mesh(3,0,nx_local,indices_to_send_right,indices_to_send_left) ;
    for (int i=0 ; i<10 ; i++) 
    {
        std::cout<<indices_to_send_right[i]<<std::endl ;
    }
    std::cout<<std::endl<<std::endl<<std::endl ; 
    
    read_mesh(3,1,nx_local,indices_to_send_right,indices_to_send_left) ;
    for (int i=0 ; i<10 ; i++) 
    {
    
        std::cout<<indices_to_send_left[i]<<std::endl ;
    }
    std::cout<<"**********"<<std::endl ;
    for (int i=0 ; i<10 ; i++) 
    {
        std::cout<<indices_to_send_right[i]<<std::endl ;
    } 
    std::cout<<std::endl<<std::endl<<std::endl ;

    read_mesh(3,1,nx_local,indices_to_send_right,indices_to_send_left) ; 
    for (int i=0 ; i<10 ; i++) 
    {
        std::cout<<indices_to_send_left[i]<<std::endl ;
    }

}