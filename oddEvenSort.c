#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int a[20000];
int i,j,k,aux,n=20000;
int main(int argc, char const *argv[]){
    int num,c;
    int numeroDeHilos=strtol(argv[1],NULL,10);
    for(c = 0; c <n; c++){
        num=1+rand()%(20001-1);
        a[c]=num;
    }
    printf("Números en el arreglo \n");
    for(int b=0;b<n;b++){
		printf(" %d,\t",a[b]);
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
	#pragma omp parallel num_threads(numeroDeHilos) default(none) shared(a,n) private(i,j,aux)
		for (i=0;i<n;i++){
			if(i%2==0){
				#pragma omp for 
				for (j=1;j<n;j+=2){
					if(a[j-1]>a[j]){
						aux=a[j];
						a[j]=a[j-1];
						a[j-1]=aux;
					}
				}
			}else{
				#pragma omp for 
				for (j=1; j<(n-1);j+=2){
					if(a[j]>a[j+1]){
						aux=a[j];
						a[j]=a[j+1];
						a[j+1]=aux;
					}
				}
			}
		}
		printf("Impresión de resultados\n");
		for(k=0;k<n;k++){
			printf("%d,\t",a[k]);
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	return 0;
}