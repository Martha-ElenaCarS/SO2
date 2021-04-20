#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#define TAM 100

double valor_memoria(int nu_datos);
double valor_tiempo(int nu_datos);
void guardar(char nombre[], double total_final, int nu_matriz);

int main(int argc, char const *argv[])
{
	int nu_datos = atoi(argv[1]);
  int nu_matriz = atoi(argv[4]);
  char nombre1[TAM], nombre2[TAM];
  double totalmemoria, totaltiempo;

  strcpy(nombre1, argv[2]);
  strcpy(nombre2, argv[3]);
  
  totalmemoria = valor_memoria(nu_datos);
  guardar(nombre1, totalmemoria, nu_matriz);

  totaltiempo = valor_tiempo(nu_datos);
  guardar(nombre2, totaltiempo, nu_matriz);

	return 0;
}

double valor_memoria(int nu_datos){
  double numero = 0, total = 0, total_final = 0;
  FILE *file;
  file = fopen("datosMemoria.dat", "rb");

  if(file != NULL){
    for(int i = 0; i < nu_datos; i++){
      fread(&numero,sizeof(double),1,file);
      total = total + numero;
    }
  }
  fflush(file);
  fclose(file);

  total_final = total/nu_datos;

  return total_final;
}

double valor_tiempo(int nu_datos){
  double numero = 0, total = 0, total_final = 0;
  FILE *file;
  file = fopen("datosTiempo.dat", "rb");

  if(file != NULL){
    for(int i = 0; i < nu_datos; i++){
      fread(&numero,sizeof(double),1,file);
      total = total + numero;
    }
  }
  fflush(file);
  fclose(file);

  total_final = total/nu_datos;

  return total_final;
}

void guardar(char nombre[], double total_final, int nu_matriz){
  FILE *file;
  file = fopen(nombre,"a");
  if(file != NULL){
    fprintf(file, "Matriz %d " , nu_matriz);
    fprintf(file, "%lf \n" , total_final);
  }
  fflush(file);
  fclose(file);
}
