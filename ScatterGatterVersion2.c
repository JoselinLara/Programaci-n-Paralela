#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define  MAESTRO	0
#include <stdlib.h>

const int  MAX_STRING=20;

int main(void){


	int comm_sz; //numero de procesos
	int my_rank; //

	
	float arreglo_flotantes[20]={1.3,2.9,0.4,0.3,1.3,4.4,1.7,0.4,3.2,0.3,4.9,2.4,3.1,4.4,3.9,0.4,4.2,4.5,4.9,0.9};
	float arreglo_resultado[20];

	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	int tareas=MAX_STRING%comm_sz;
	int elementosPorProceso=(MAX_STRING/comm_sz);
		//Inicializa los elementos

	
	    if(tareas!=0){
			if(my_rank==0){
			printf("No es un factor que se pueda dividir");
			}
		}
		else{
        
			if(my_rank==MAESTRO){
			
				float arreglo_local[elementosPorProceso];
				MPI_Scatter(arreglo_flotantes,elementosPorProceso,MPI_FLOAT,arreglo_local,elementosPorProceso,MPI_FLOAT,MAESTRO,MPI_COMM_WORLD);
				
				
				for(int i=0;i<elementosPorProceso;i++){
					arreglo_local[i]=arreglo_local[i]+1;
					//printf("\nProceso %d El valor de %f \n",my_rank,arreglo_local[i]);
				
			
			    }
				 MPI_Gather(arreglo_local,elementosPorProceso,MPI_FLOAT,arreglo_resultado,elementosPorProceso,MPI_FLOAT,MAESTRO,MPI_COMM_WORLD);

                    for(int i=0;i<MAX_STRING;i++){
						
						printf("\nProceso %d El valor de %f \n",my_rank,arreglo_resultado[i]);
					
				
				}
				
		}
		if(my_rank>MAESTRO){
					
			float arreglo_local[elementosPorProceso];
			 MPI_Scatter(arreglo_flotantes,elementosPorProceso,MPI_FLOAT,arreglo_local,elementosPorProceso,MPI_FLOAT,MAESTRO,MPI_COMM_WORLD);
		    
				for(int i=0;i<elementosPorProceso;i++){
						arreglo_local[i]=arreglo_local[i]+1;
						//printf("\nProceso %d El valor de %f \n",my_rank,arreglo_local[i]);
			
				}
				
			 MPI_Gather(arreglo_local,elementosPorProceso,MPI_FLOAT,arreglo_resultado,MAX_STRING,MPI_FLOAT,MAESTRO,MPI_COMM_WORLD);
	
			}

		}		

	MPI_Finalize();

	return 0;
}


