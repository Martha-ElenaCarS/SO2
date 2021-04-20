#!/usr/bin/gnuplot -persist
#permisos para utilzar este archivo chmod u+x enterosFOX.sh

#gnuplot -e 
plot "datosTiempo.dat" w lp;           #Aqui pones el nombre del archivo a graficar
set xlabel "Tamaño Matriz";			  #Tamaño de la Matriz
#set ylabel "Memoria Utilizada (Kb)";
set ylabel "Tiempo utilizado (s)";              #Datos en Y para verificar comportamiento
#set title "Datos Tiempo Enteros Fox";   #Titulo de la tabla
set title "Datos Tiempo Enteros Fox";
set grid xtics ytics mxtics mytics;		  #Rejilla de datos
replot;						  #Despues solo guardas en png desde la interfaz
exit
 
