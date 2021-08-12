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
	int my_rank; //
	float arreglo_flotantes[20]={1.3,2.9,0.4,0.3,1.3,4.4,1.7,0.4,3.2,0.3,4.9,2.4,3.1,4.4,3.9,0.4,4.2,4.5,4.9,0.9};

	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	int tareas=comm_sz%2;
	int tamanioDePedazos=(20/comm_sz);
	int recorrido=tamanioDePedazos;
	//Inicializa los elementos
		if(my_rank==MAESTRO){
		int hola=10;
				float arreglo_local[20];
				MPI_Scatter(arreglo_flotantes,20,MPI_FLOAT,arreglo_local,5,MPI_FLOAT,MAESTRO,MPI_COMM_WORLD);
				
				for(int i=0;i<5;i++){
					printf("\nProceso %d El valor de %f \n",my_rank,arreglo_local[i]);			
			    }
		}
		if(my_rank>MAESTRO){
		    int hola_local=0;
			 float arreglo_local[20];
			 
			 MPI_Scatter(arreglo_flotantes,20,MPI_FLOAT,arreglo_local,5,MPI_FLOAT,MAESTRO,MPI_COMM_WORLD);
		
			for(int i=0;i<5;i++){
					printf("\nProceso %d El valor de %f \n",my_rank,arreglo_local[i]);
			}		
		}
	
	MPI_Finalize();
	return 0;
}


