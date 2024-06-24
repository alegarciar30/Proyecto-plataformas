#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Funciones para evaluar las funciones cuadráticas
double f1(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

double f2(double x, double d, double e, double f) {
    return d * x * x + e * x + f;
}

// Función para generar los datos en un archivo
void generate_data(const char *filename, double a, double b, double c, double d, double e, double f, double step, double start, double end) {
    FILE *file = fopen(filename, "w");
    for (double x = start; x <= end; x += step) {
        fprintf(file, "%lf %lf %lf\n", x, f1(x, a, b, c), f2(x, d, e, f));
    }
    fclose(file);
}

int main() {
    double a, b, c, d, e, f;
    double error_percentage;

    // Entrada de datos
    printf("Ingrese los coeficientes de la primera funcion cuadratica (a, b, c):\n");
    scanf("%lf %lf %lf", &a, &b, &c);

    printf("Ingrese los coeficientes de la segunda funcion cuadratica (d, e, f):\n");
    scanf("%lf %lf %lf", &d, &e, &f);

    printf("Ingrese el porcentaje de error permitido (0 a 100):\n");
    scanf("%lf", &error_percentage);

    double x_start = -100000;
    double x_end = 100000;
    double step = 0.1;
    double x;
    double subdomain_start = x_start, subdomain_end = x_end;
    int found = 0;

    // Cálculo del subdominio
    for (x = x_start; x <= x_end; x += step) {
        double f1_val = f1(x, a, b, c);
        double f2_val = f2(x, d, e, f);
        double error = fabs(f1_val - f2_val) / fabs(f1_val) * 100;

        if (error <= error_percentage) {
            if (!found) {
                subdomain_start = x;
                found = 1;
            }
            subdomain_end = x;
        } else if (found) {
            break;
        }
    }

    printf("Subdominio encontrado: [%lf, %lf]\n", subdomain_start, subdomain_end);

    // Generar los datos para la gráfica
    generate_data("data.txt", a, b, c, d, e, f, step, x_start, x_end);

    // Crear el script de Gnuplot para el dominio completo
    FILE *gnuplotScript = fopen("datos_full.gnuplot", "w");
    fprintf(gnuplotScript, "set terminal png\n");
    fprintf(gnuplotScript, "set output 'grafico_full.png'\n");
    fprintf(gnuplotScript, "set title 'Comparacion de Funciones Cuadraticas - Dominio Completo'\n");
    fprintf(gnuplotScript, "set xlabel 'X'\n");
    fprintf(gnuplotScript, "set ylabel 'Y'\n");
    fprintf(gnuplotScript, "plot 'data.txt' using 1:2 with lines title 'Funcion 1', \\\n");
    fprintf(gnuplotScript, "     'data.txt' using 1:3 with lines title 'Funcion 2', \\\n");
    fprintf(gnuplotScript, "     '-' using 1:2 with lines lt rgb 'red' title 'Subdominio Inicio', \\\n");
    fprintf(gnuplotScript, "     '-' using 1:2 with lines lt rgb 'red' title 'Subdominio Fin'\n");
    fprintf(gnuplotScript, "%lf %lf\n", subdomain_start, -100.0);
    fprintf(gnuplotScript, "%lf %lf\n", subdomain_start, 100.0);
    fprintf(gnuplotScript, "e\n");
    fprintf(gnuplotScript, "%lf %lf\n", subdomain_end, -100.0);
    fprintf(gnuplotScript, "%lf %lf\n", subdomain_end, 100.0);
    fprintf(gnuplotScript, "e\n");
    fclose(gnuplotScript);

    // Crear el script de Gnuplot para el subdominio
    double narrow_start = subdomain_start - 1.0;
    double narrow_end = subdomain_end + 1.0;
    gnuplotScript = fopen("datos_sub.gnuplot", "w");
    fprintf(gnuplotScript, "set terminal png\n");
    fprintf(gnuplotScript, "set output 'grafico_sub.png'\n");
    fprintf(gnuplotScript, "set title 'Comparacion de Funciones Cuadraticas - Subdominio'\n");
    fprintf(gnuplotScript, "set xlabel 'X'\n");
    fprintf(gnuplotScript, "set ylabel 'Y'\n");
    fprintf(gnuplotScript, "set xrange [%lf:%lf]\n", narrow_start, narrow_end);
    fprintf(gnuplotScript, "plot 'data.txt' using 1:2 with lines title 'Funcion 1', \\\n");
    fprintf(gnuplotScript, "     'data.txt' using 1:3 with lines title 'Funcion 2', \\\n");
    fprintf(gnuplotScript, "     '-' using 1:2 with lines lt rgb 'red' title 'Subdominio Inicio', \\\n");
    fprintf(gnuplotScript, "     '-' using 1:2 with lines lt rgb 'yellow' title 'Subdominio Fin'\n");
    fprintf(gnuplotScript, "%lf %lf\n", subdomain_start, -100.0);
    fprintf(gnuplotScript, "%lf %lf\n", subdomain_start, 300.0);
    fprintf(gnuplotScript, "e\n");
    fprintf(gnuplotScript, "%lf %lf\n", subdomain_end, -100.0);
    fprintf(gnuplotScript, "%lf %lf\n", subdomain_end, 300.0);
    fprintf(gnuplotScript, "e\n");
    fclose(gnuplotScript);

    // Ejecutar Gnuplot para ambas gráficas
    system("gnuplot datos_full.gnuplot");
    system("gnuplot datos_sub.gnuplot");

    return 0;
}