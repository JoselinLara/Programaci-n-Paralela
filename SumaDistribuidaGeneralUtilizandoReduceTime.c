#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define  MAESTRO	0
#include <stdlib.h>

const int MAX_STRING=10000;

int main(void){



	int arreglo_enteros[MAX_STRING];
	int comm_sz; //numero de procesos
	int my_rank; //
	int resultado=0;
	double inicio,fin;
		for(int i=0;i<MAX_STRING;i++){
		arreglo_enteros[i]=i;
	}
	
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
 	 int tareas=MAX_STRING%comm_sz;
	 int tamanioDePedazos=(MAX_STRING/comm_sz);
	 int recorrido=tamanioDePedazos;
	
	if(tareas!=0){
			 if (my_rank == MAESTRO){
				printf("Saliendo del sistema. Se necesita un numero par de tareas: numero de tares=%d\n", comm_sz);
			}
		}
	else {
	  
		if(my_rank==MAESTRO){
		
		         inicio=MPI_Wtime();
				int suma=0;
				//realizamos las operaciones que le corresponden al maestro
				for(int i=0;i<tamanioDePedazos;i++){
				suma+=arreglo_enteros[i];
				}
				printf("Suma del proceso maestro %d \n",suma);
				
				for(int q=1;q<comm_sz;q++){
						MPI_Send(&recorrido,1,MPI_INT,q,0,MPI_COMM_WORLD);
				        MPI_Send(&arreglo_enteros[recorrido],tamanioDePedazos,MPI_INT,q,0,MPI_COMM_WORLD);
						recorrido=recorrido+tamanioDePedazos;
				}
				
				
				//int resultados_de_las_tareas=0;
				//for(int q=1;q<comm_sz;q++){
				//        MPI_Recv(&resultados_de_las_tareas,1,MPI_INT,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				//		suma+=resultados_de_las_tareas;
				//}
				
				MPI_Reduce(&suma,&resultado,1,MPI_INT,MPI_SUM,MAESTRO,MPI_COMM_WORLD);
				fin=MPI_Wtime();
				printf("suma total %d  \n",resultado);
				printf("tiempo total transcurrido  %e  segundos \n",fin-inicio);
				
				
				
		}
		if(my_rank>MAESTRO){
			int suma=0;
			MPI_Recv(&recorrido,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&arreglo_enteros[recorrido],tamanioDePedazos,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			    for(int i=0;i<tamanioDePedazos;i++){
					suma+=arreglo_enteros[recorrido+i];
				}
				
			
			printf("Suma Parcial del proceso %d es %d  \n",suma,my_rank);
			MPI_Reduce(&suma,&resultado,1,MPI_INT,MPI_SUM,MAESTRO,MPI_COMM_WORLD);
		}
	
	}
	

	MPI_Finalize();

	return 0;
}