#include <stdio.h>
#include <mpi.h>
double suma=0.0;
long long  n=1000000000;
int main (int argc, char* argv[]){
    int rank, size, i;
    double factor;
    double pi=0.0, result=0.0, sum=0.0;
    MPI_Init(NULL,NULL);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    
    long long my_n=n/size;
	long long mi_primer_elemento=my_n*rank;
	long long mi_ultimo_elemento=mi_primer_elemento+my_n;
	double my_suma=0.0;
	if(mi_primer_elemento%2==0){
		factor=1.0;
	}else{
		factor=-1.0;
	}
	for(i=mi_primer_elemento;i<mi_ultimo_elemento;i++,factor=-factor){
		my_suma+=factor/(2*i+1);
	}
	suma+=my_suma;
    MPI_Reduce(&suma, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank==0){
        pi=4*sum;
        printf("PI=%.40f\n",pi);
        fflush(stdout);
    }
    MPI_Finalize();
    
    return 0;
}
