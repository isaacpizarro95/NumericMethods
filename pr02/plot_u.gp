set title "Velocitat u en funció de x"
set xlabel "x"
set ylabel "u"
set grid
set term png
set output "u_plot.png"
plot "u.txt" using 1:2 with lines title "u(x)"
