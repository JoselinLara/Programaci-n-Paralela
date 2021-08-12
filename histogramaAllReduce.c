#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define  MAESTRO	0
#include <stdlib.h>

const int  MAX_STRING=20;



int distribuye(float a);
void imprime(int arreglo[]);

int main(void){



	float arreglo_flotantes[20]={1.3,2.9,0.4,0.3,1.3,4.4,1.7,0.4,3.2,0.3,4.9,2.4,3.1,4.4,3.9,0.4,4.2,4.5,4.9,0.9};
	int elementos[5]={0,0,0,0,0};
	int elementos_final[5]={0,0,0,0,0};
	int comm_sz; //numero de procesos
	int my_rank; //
	int resultado=0;
	double inicio,fin;

	
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	int tareas=MAX_STRING%comm_sz;
	int tamanioDePedazos=(20/comm_sz);
	int recorrido=tamanioDePedazos;
	//Inicializa los elementos

	if(tareas!=0){
			 if (my_rank == MAESTRO){
				printf("Saliendo del sistema. Se necesita un numero par de tareas: numero de tares=%d\n", comm_sz);
			}
		}
	else {
	  
		if(my_rank==MAESTRO){
		         
			
				//realizamos las operaciones que le corresponden al maestro
				for(int i=0;i<tamanioDePedazos;i++){
							elementos[distribuye(arreglo_flotantes[i])]+=1;
				}
			
				
				for(int q=1;q<comm_sz;q++){
						MPI_Send(&recorrido,1,MPI_INT,q,0,MPI_COMM_WORLD);
				        MPI_Send(&arreglo_flotantes[recorrido],tamanioDePedazos,MPI_INT,q,0,MPI_COMM_WORLD);
						recorrido=recorrido+tamanioDePedazos;
				}

				MPI_Allreduce(&elementos,&elementos_final,5,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
				printf("estos son los elementos del rank: %d \n 0->%d \n 1->%d \n2->%d \n3->%d \n4->%d \n",my_rank,elementos_final[0],elementos_final[1],elementos_final[2],elementos_final[3],elementos_final[4]);
				imprime(elementos_final);
				
				
		}
		if(my_rank>MAESTRO){
			int elementos_locales[5]={0,0,0,0,0};
			MPI_Recv(&recorrido,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&arreglo_flotantes[recorrido],tamanioDePedazos,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			    for(int i=0;i<tamanioDePedazos;i++){

					elementos_locales[distribuye(arreglo_flotantes[recorrido+i])]+=1;
				}
				
	        MPI_Allreduce(&elementos_locales,&elementos_final,5,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
			printf("estos son los elementos del rank: %d \n 0->%d \n 1->%d \n2->%d \n3->%d \n4->%d \n",my_rank,elementos_final[0],elementos_final[1],elementos_final[2],elementos_final[3],elementos_final[4]);
				imprime(elementos_final);
			
		}
	
	}
	


	MPI_Finalize();

	
				
	
	return 0;
}




int distribuye(float a){
	
	
	if(a<1){
		return 0;
	}
	if((a<2)&&(a>=1)){
	    return 1;
	}
	if((a<3)&&(a>=2)){
	    return 2;
	}
	if((a<4)&&(a>=3)){
	    return 3;
	}
	if((a<5)&&(a>=4)){
	    return 4;
	}
	

}



void imprime(int arreglo[]){

   
   for(int i=0;i<5;i++){
		printf("%d",i);
		for(int j=0;j<arreglo[i];j++){
		printf("  |",arreglo[i]);
		}
		printf("\n");
   }
}



