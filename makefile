CC=gcc

p1:
	$(CC) -o exe proyecto1.c -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

p2:
	$(CC) proyecto2.c -o exe

clean:
	rm -f *.o exe data.txt grafico_full.png grafico_sub.png datos_full.gnuplot datos_sub.gnuplot
