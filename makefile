CC=gcc

p2:
	$(CC) graficar.c -o exe

clean:
	rm -f *.o exe data.txt graph.png plot.gnuplot
