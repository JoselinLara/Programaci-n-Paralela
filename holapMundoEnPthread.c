#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
/*Para compilar $gcc  -g  -Wall  -o  nombreEjecutable nombreDelFuente.c  -lpthread*/
/*Para ejecutar $./nombreEjecutable 4*/
/*Variable global accesible a todos los hilo*/
int numeroDeHilos;
struct datos{
   long rank;
   int suma;
};
void* Hola(void* rank); /*Funcion del Hilo*/
int main(int argc, char*  argv[]){
	long hilo;
	pthread_t* manejadorDeHilos;
	struct datos datosDeEnvio;
	/*obten el numero de hilos d ela linea de comandos*/
	numeroDeHilos=strtol(argv[1],NULL,10);
	manejadorDeHilos=malloc(numeroDeHilos*sizeof(pthread_t));
	for (hilo = 0; hilo < numeroDeHilos; hilo++){
		printf("hilo:%ld\n",hilo);
            	datosDeEnvio.rank=hilo;
		datosDeEnvio.suma=2+hilo;
		pthread_create(&manejadorDeHilos[hilo],NULL,Hola,&datosDeEnvio);
	}
	printf("Hola del hilo principal\n");
	for (hilo = 0; hilo < numeroDeHilos; hilo++){
	       void* regreso;
	       pthread_join(manejadorDeHilos[hilo],&regreso);
	       printf("Regreso %d \n",(int)regreso);
	}
	free(manejadorDeHilos);
	return 0;
}
void* Hola(void* loQueSeRecibe){
    struct datos *datosDeRecibo;
    datosDeRecibo=(struct datos*) loQueSeRecibe;
    long my_rank=datosDeRecibo->rank;
    int valor=datosDeRecibo->suma;
    printf("Hola desde el hilo %ld  de %d con un valor de %d\n",my_rank,numeroDeHilos,valor);
    return (valor*valor);
}
