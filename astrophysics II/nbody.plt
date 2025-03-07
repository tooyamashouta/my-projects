reset
set terminal png size 640,480
set yrange[-1:1]
set xrange[-1:1]
set zrange[-1:1]
set view equal xyz
set xlabel "x"
set ylabel "y"
set zlabel "z"

set output "62153d0.png"
splot "output0000.dat" u 3:4:5

set output "62153d1.png"
splot "output0001.dat" u 3:4:5

set output "62153d2.png"
splot "output0002.dat" u 3:4:5

set output "62153d3.png"
splot "output0003.dat" u 3:4:5

set output "62153d4.png"
splot "output0004.dat" u 3:4:5

set output "62153d5.png"
splot "output0005.dat" u 3:4:5

set output "62153d6.png"
splot "output0006.dat" u 3:4:5

set output "62153d7.png"
splot "output0007.dat" u 3:4:5

set output "62153d8.png"
splot "output0008.dat" u 3:4:5

set output "62153d9.png"
splot "output0009.dat" u 3:4:5

set output "62153d10.png"
splot "output0010.dat" u 3:4:5

set output "62153d11.png"
splot "output0011.dat" u 3:4:5

set output "62153d12.png"
splot "output0012.dat" u 3:4:5

set output "62153d13.png"
splot "output0013.dat" u 3:4:5

set output "62153d14.png"
splot "output0014.dat" u 3:4:5

set output "62153d15.png"
splot "output0015.dat" u 3:4:5

set output "62153d16.png"
splot "output0016.dat" u 3:4:5

unset output
set terminal qt
reset
