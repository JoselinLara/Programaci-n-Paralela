#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//gcc -g -Wall -fopenmp -o pi piomp.c
long long  n=1000000000;
int main(int argc, char const *argv[]){
	double sum=0.0,pi;
	int k;
	double factor;
	int id=strtol(argv[1],NULL,10);
	#pragma omp parallel for  num_threads(id)\
		reduction(+:sum) private(factor)
		for(k=0;k<n;k++){
			if(k%2==0)
				factor=1.0;
			else
				factor=-1.0;
			sum+=factor/(2*k+1);
		}
	pi=4*sum;
	printf("Pi=%.40f\n",pi);
	return 0;
}