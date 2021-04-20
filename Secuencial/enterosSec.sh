echo "Matriz 64" 
rm datosTiempo.dat
rm datosMemoria.dat
touch datosTiempo.dat
touch datosMemoria.dat
for ((i=0;i<35;i++))
do
mpirun -np 4 ./enterosSec 64
done
./promedio 4 Memoria.txt Tiempo.txt 64

