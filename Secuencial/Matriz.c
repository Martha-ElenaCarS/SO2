#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
	pid_t pid;
	if ( (pid=fork()) == 0 )
    	{ /* hijo */
	        printf("Proceso que ejecuta el programa: %d\n",getppid());
		printf("Programa que multiplica Matrices\n");
		int Matriz1[16][16];
		int Matriz2[16][16];
		int MatrizC[16][16];
		int i,j,c,valor;
		valor=0;
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				Matriz1[i][j]=valor;
				valor++;
			}
			valor=valor-8;		
		}
		valor=0;
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				Matriz2[i][j]=valor;
				valor++;
			}
			valor=valor-8;		
		}

		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				MatrizC[i][j]=0;
			}		
		}
	
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				for (c=0;c<9;c++)
					 MatrizC[i][j] += Matriz1[i][c] * Matriz2[c][j];

		for(i=0;i<9;i++){
			for(j=0;j<9;j++)
				printf("%d ",Matriz1[i][j]);
			printf("\n");
		}

		/*for(i=0;i<9;i++){
			for(j=0;j<9;j++)
				printf("%d ",MatrizC[i][j]);
			printf("\n");
		}*/
	printf("\n");
	sleep(10);
	return(getppid());
    	}
}
