#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	double memoria,total=0,repeticones=0,subtotal=0;
	FILE *file; 
	file = fopen("datosMemoria.txt", "rb");
	if(file == NULL){
		printf("ERROR\n");
	}else{
		while (!feof(file)) {
	        fread(&memoria,sizeof(double), 1, file);
	        //printf ("Memoria: %f \n", memoria);
	        subtotal = subtotal + memoria;
	        repeticones++;
    	}
    	total = subtotal/repeticones;
    	printf ("Memoria promedio: %f \n", total);
	}
	printf("\n");
	double tiempo;
	total = 0;
	subtotal = 0;
	repeticones = 0;
	file =fopen("datosTiempo.txt", "rb");
	if(file == NULL){
		printf("ERROR\n");
	}else{
		while (!feof(file)) {
	        fread(&tiempo,sizeof(double), 1, file);
	        //printf ("Tiempo: %f \n", tiempo);
	        subtotal = subtotal + tiempo;
	        repeticones++;
    	}
    	total = subtotal/repeticones;
    	printf ("Tiempo promedio: %f \n", total);
	}
	return 0;
}