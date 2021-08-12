#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define  MAESTRO	0

const int MAX_STRING=2000;

int main(void){
	int arreglo_enteros[MAX_STRING];
	int comm_sz; 
	int my_rank;
	int p=0;	
	for(int i=0;i<MAX_STRING;i++){
		arreglo_enteros[i]=i;
	}
	for(int i=0;i<MAX_STRING;i++){
		p+=arreglo_enteros[i]=i;
	}
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
 	 int tareas=comm_sz%2;
	 int tDePedazos=(MAX_STRING/comm_sz);
	 int r=tDePedazos;
	
	if(tareas!=0){
		if (my_rank == MAESTRO){
			printf("Se necesita un numero par de tareas\n", comm_sz);
		}
	}else{
	  if(my_rank==MAESTRO){
			int suma=0;
			for(int i=0;i<tDePedazos;i++){
				suma+=arreglo_enteros[i];
			}
			printf("Suma del proceso maestro %d \n",suma);
			printf("Se enviarán pedazos de %d a otros procesos\n",r);
			for(int q=1;q<comm_sz;q++){
				MPI_Send(&r,1,MPI_INT,q,0,MPI_COMM_WORLD);
				MPI_Send(&arreglo_enteros[r],tDePedazos,MPI_INT,q,0,MPI_COMM_WORLD);
				r=r+tDePedazos;
			}
			int resultados_de_las_tareas=0;
			for(int q=1;q<comm_sz;q++){
				MPI_Recv(&resultados_de_las_tareas,1,MPI_INT,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				suma+=resultados_de_las_tareas;
			}
			printf("suma total %d  \n",suma);
			printf("Suma total (verificación) %d\n",p);		
		}
		if(my_rank>MAESTRO){
			int suma=0;
			MPI_Recv(&r,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&arreglo_enteros[r],tDePedazos,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			    for(int i=0;i<tDePedazos;i++){
					suma+=arreglo_enteros[r+i];
				}
			printf("Suma Parcial del proceso %d es %d  \n",my_rank,suma);
			MPI_Send(&suma,1,MPI_INT,0,0,MPI_COMM_WORLD);
		}
	
	}
	

	MPI_Finalize();

	return 0;
}