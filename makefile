CC=gcc

p1:
	$(CC) -o exe proyecto1.c -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

p2:
	$(CC) graficar.c -o exe

clean:
	rm -f *.o exe data.txt graph.png plot.gnuplot
