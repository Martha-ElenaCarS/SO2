
Código

Encontrara en esta carpeta los archivos:

- cortosFoxOMP.c 
- enterosFoxOMP.c 
- flotantesFoxOMP.c 
- doublesFoxOMP.c 

Lo unico que va a cambiar en cada archivo sera el tipo de dato (short,
int, float, double)

En cada una de ellas encontrara el algoritmo de Fox el cual es:

**************************TROZO DE CODIGO**************************

void Fox(
        int              n         , 
        GRID_INFO_T*     grid      , 
        LOCAL_MATRIX_T*  local_A   ,
        LOCAL_MATRIX_T*  local_B   ,
        LOCAL_MATRIX_T*  local_C    ) {

    LOCAL_MATRIX_T*  temp_A; 
    int              stage;
    int              bcast_root;
    int              n_bar;  /* Orden de la matrix local : n/sqrt(p) */
    int              source;
    int              dest;
    MPI_Status       status;

    n_bar = n/grid->q;
    Set_to_zero(local_C);

	/* Calcula las direccciones para el desplazamiento circular de B */
    source = (grid->my_row + 1) % grid->q;
    dest = (grid->my_row + grid->q - 1) % grid->q;

	/* Aloca el espacio para el envio del bloque de A */
    temp_A = Local_matrix_allocate(n_bar);

    for (stage = 0; stage < grid->q; stage++) {
        bcast_root = (grid->my_row + stage) % grid->q;
        if (bcast_root == grid->my_col) {
            MPI_Bcast(local_A, 1, local_matrix_mpi_t, bcast_root, grid->row_comm);
            Local_matrix_multiply(local_A, local_B, local_C);
        } else {
            MPI_Bcast(temp_A, 1, local_matrix_mpi_t, bcast_root, grid->row_comm);
            Local_matrix_multiply(temp_A, local_B, local_C);
        }
        MPI_Sendrecv_replace(local_B, 1, local_matrix_mpi_t, dest, 0, source, 0, grid->col_comm, &status);
    } /* for */
    
} /* Fox */

**************************TROZO DE CODIGO**************************

Asu vez llama a la funcion Local_matrix_multiply() el cual hemos paralelizado con OpenMP que multiplica cada submatriz

**************************TROZO DE CODIGO**************************

/*********************************************************/
/* Multiplica las matrices locales local_A y local_B de cada procesador y luego lo almacena en local_C  */
void Local_matrix_multiply(LOCAL_MATRIX_T* local_A, LOCAL_MATRIX_T* local_B,LOCAL_MATRIX_T* local_C) {
    int i, j, k;
    #pragma omp parallel for private(i,j,k) shared(local_A, local_B, local_C) num_threads(NUM_THREADS)
    for (i = 0; i < Order(local_A); i++)
        for (j = 0; j < Order(local_A); j++)
            for (k = 0; k < Order(local_B); k++)
                Entry(local_C,i,j) = Entry(local_C,i,j) + Entry(local_A,i,k)*Entry(local_B,k,j);

}  /* Local_matrix_multiply */


**************************TROZO DE CODIGO**************************

Hemos medido el tiempo con las siguientes funcion: omp_get_wtime();


Hemos medido la memoria con la funcion: 

**************************TROZO DE CODIGO**************************

long obtener_memoria() {
    struct rusage myusage;

    getrusage(RUSAGE_SELF, &myusage);

    return myusage.ru_maxrss;
}

**************************TROZO DE CODIGO**************************

El cual se encuentra en la libreria: <sys/resource.h>

Guardamos los datos de tiempo y memoria de la siguiente forma

**************************TROZO DE CODIGO**************************

		FILE *file1;
	    file1 = fopen("datosTiempo.dat","ab+");
	    if(file1 != NULL){
	        fwrite(&tiempo,sizeof(double), 1, file1);
	    }
	    fflush(file1);
	    fclose(file1);

	    FILE *file2;
	    file2 = fopen("datosMemoria.dat","ab+");
	    if(file2 != NULL){
	        fwrite(&memoria,sizeof(double), 1, file2);
	    }
	    fflush(file2);
	    fclose(file2);

**************************TROZO DE CODIGO**************************
