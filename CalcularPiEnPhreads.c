#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int numeroDeHilos;
double suma=0.0;
long long  n=1000000000;
void* SumaDePi(void* rank);
int main(int argc,char* argv[]){
	long hilo;
	pthread_t* manejadorDeHilos;
	numeroDeHilos=strtol(argv[1],NULL,10);
	manejadorDeHilos=malloc(numeroDeHilos*sizeof(pthread_t));
	for(hilo=0;hilo<numeroDeHilos;hilo++){
		pthread_create(&manejadorDeHilos[hilo],NULL,SumaDePi,(void*)hilo);
	}
	for(hilo=0;hilo<numeroDeHilos;hilo++){
		pthread_join(manejadorDeHilos[hilo],NULL);
	}
	double resultado=4*suma;
	printf("Pi=%.42f\n",resultado );
	fflush(stdout);
	free(manejadorDeHilos);
	return 0;	
}
void* SumaDePi(void* rank){
	long my_rank=(long)rank;
	double factor;
	long long i;
	long long my_n=n/numeroDeHilos;
	long long mi_primer_elemento=my_n*my_rank;
	long long mi_ultimo_elemento=mi_primer_elemento+my_n;
	double my_suma=0.0;
	pthread_mutex_t  mutex;
	pthread_mutex_init(&mutex,NULL);
	if(mi_primer_elemento%2==0){
		factor=1.0;
	}else{
		factor=-1.0;
	}
	for(i=mi_primer_elemento;i<mi_ultimo_elemento;i++,factor=-factor){
		my_suma+=factor/(2*i+1);
	}
	pthread_mutex_lock(&mutex);
	suma+=my_suma;
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	return NULL;
}