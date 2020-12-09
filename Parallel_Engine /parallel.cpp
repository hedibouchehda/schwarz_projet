
#include <mpi.h>
#include <vector> 
//#include "heatProblem.h" 


int main(int argc,char** argv) 
{
    int nproc,rank,err; 
    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&nproc); 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    std::vector<double> vect; 
        
    double l,l1; 
     if (rank == 0) {
        // Création d'un tableau statique de taille 4 double
        std::vector<double> i;
        i.resize(4);
        i[0] = 1 ;
        i[1] = 1 ;
        i[2] = 1 ;
        i[3] = 1 ; 

        // Boucle pour envoyer à tous les procs autres que 0
       // for (int p=1; p<nproc; ++p) {
            // Envoi d'une donnée de taille 4, de type MPI_DOUBLE, commençant à l'adresse &i
            MPI_Send(&i[0], 4, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        //}
    }
    else 
    {
        std::vector<double> vect3 ;
        vect3.resize(4);
        MPI_Recv(&vect3[0], 4, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        std::cout<<rank<<" "<<vect3[0]<<" "<<vect3[1]<<" "<<vect3[2]<<std::endl;         
    }
    MPI_Finalize();
}

/*
#include <cstdio>
#include <cstdlib>

#include <mpi.h>


int main(int argc, char ** argv)
{
    int nproc, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // La portion de code suivante n'est exécutée que par le proc de rang 0.
    if (rank == 0) {
        // Création d'un tableau statique de taille 4 double
        double i[4] = {1., 2., 3., 4.};
        // Boucle pour envoyer à tous les procs autres que 0
        for (int p=1; p<nproc; ++p) {
            // Envoi d'une donnée de taille 4, de type MPI_DOUBLE, commençant à l'adresse &i
            MPI_Send(&i, 4, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
        }
    }
    // La portion de code suivante est exécutée par les proc de rang > 0.
    else {
        // Création d'un tableau statique de taille 4 double initialisé par des 0
        double j[4] = {0.};
        // Réception d'une donnée de taille 4, de type MPI_DOUBLE, 
        //   dans un tableau commençant à l'adresse &i
        MPI_Recv(&j, 4, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("On proc %d j=[%1.1f %1.1f %1.1f %1.1f]\n", rank, j[0], j[1], j[2], j[3]);
    }

    MPI_Finalize();

    return 0;
}
*/