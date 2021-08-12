#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define  MAESTRO	0
#include <stdlib.h>

const float  MAX_STRING=100;



int distribuye(float a);
void imprime(int arreglo[]);

int main(void){


	int comm_sz; //numero de procesos
	int my_rank; 


	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	
	
		if(my_rank==MAESTRO){
		int hola=10;

				MPI_Bcast(&hola,1,MPI_INT,MAESTRO,MPI_COMM_WORLD);
				printf("\nImprimiendo el broadcast desde el rank %d hola=%d \n",my_rank,hola);
	
		}
		if(my_rank>MAESTRO){
		    int hola_local=0;
		     MPI_Bcast(&hola_local,1,MPI_INT,MAESTRO,MPI_COMM_WORLD);
			 printf("\nImprimiendo el broadcast desde el rank %d hola=%d \n",my_rank,hola_local);

		}	
	MPI_Finalize();

	return 0;
}


