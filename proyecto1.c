#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

// INICIALIZACION DE VARIABLES PARA CADA PARTE DE LA INTERFAZ
GtkWidget *window;
GtkWidget *grid;

GtkWidget *a1; // Botones primera fila
GtkWidget *b1;
GtkWidget *c1;

GtkWidget *a2; // Segunda
GtkWidget *b2;
GtkWidget *c2;

GtkWidget *a3; // Tercera
GtkWidget *b3;
GtkWidget *c3;

GtkBuilder *builder;

// INICIALIZACION FUNCIONES
void imprimir_mensaje(char mensaje[]);
void cambiar_letra(GtkWidget *boton);
bool revisar_gane();
void revisar_empate();
void turno_completo(GtkWidget *boton);

// Contador turnos
int turno = 1;

// MAIN
int main(int argc, char *argv[]){
    gtk_init(&argc, &argv); // Iniciar GTK

    // Leer codigo .xml de Glade
    builder = gtk_builder_new_from_file ("proyecto1.glade");
    
    window = GTK_WIDGET (gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    // Se asignan variables a cada parte de la interfaz
    grid = GTK_WIDGET(gtk_builder_get_object(builder, "grid"));

    a1 = GTK_WIDGET(gtk_builder_get_object(builder, "a1"));
    b1 = GTK_WIDGET(gtk_builder_get_object(builder, "b1"));
    c1 = GTK_WIDGET(gtk_builder_get_object(builder, "c1"));

    a2 = GTK_WIDGET(gtk_builder_get_object(builder, "a2"));
    b2 = GTK_WIDGET(gtk_builder_get_object(builder, "b2"));
    c2 = GTK_WIDGET(gtk_builder_get_object(builder, "c2"));

    a3 = GTK_WIDGET(gtk_builder_get_object(builder, "a3"));
    b3 = GTK_WIDGET(gtk_builder_get_object(builder, "b3"));
    c3 = GTK_WIDGET(gtk_builder_get_object(builder, "c3"));

    gtk_widget_show(window);
    gtk_main();

    // Terminar el programa
    return EXIT_SUCCESS;
}

// FUNCIONES //
void imprimir_mensaje(char mensaje[]){
    // Vacia todas las casillas. Despliega mensaje en la del centro
    gtk_button_set_label(GTK_BUTTON(a1), " ");
    gtk_button_set_label(GTK_BUTTON(b1), " ");
    gtk_button_set_label(GTK_BUTTON(c1), " ");
    gtk_button_set_label(GTK_BUTTON(a2), " ");
    gtk_button_set_label(GTK_BUTTON(b2), mensaje);
    gtk_button_set_label(GTK_BUTTON(c2), " ");
    gtk_button_set_label(GTK_BUTTON(a3), " ");
    gtk_button_set_label(GTK_BUTTON(b3), " ");
    gtk_button_set_label(GTK_BUTTON(c3), " ");
}

void cambiar_letra(GtkWidget *boton){
    // Cambia la etiqueta del boton elegido. Notar que comienzan el programa siendo NULL.
    // En cada turno alterna entre X y O.

    const gchar *etiqueta = gtk_button_get_label (GTK_BUTTON(boton));

    if (etiqueta == NULL){ // Solo la cambia si no se ha cambiado antes
        if (turno % 2 == 0){
            gtk_button_set_label(GTK_BUTTON(boton), "O");
        }
        else {
            gtk_button_set_label(GTK_BUTTON(boton), "X");
        }
        turno ++; // Solo se cuenta el turno si se hizo clic en un espacio valido
    }
}

bool revisar_gane(){
    // Revisa las 8 combinaciones posibles para ganar el juego
    // Revisa tambien que las casillas no esten vacias (sino se ganaria inmediatamente comienza el juego)
    // Retorna true o false

    const gchar *etiq_a1 = gtk_button_get_label (GTK_BUTTON(a1));
    const gchar *etiq_a2 = gtk_button_get_label (GTK_BUTTON(a2));
    const gchar *etiq_a3 = gtk_button_get_label (GTK_BUTTON(a3));

    const gchar *etiq_b1 = gtk_button_get_label (GTK_BUTTON(b1));
    const gchar *etiq_b2 = gtk_button_get_label (GTK_BUTTON(b2));
    const gchar *etiq_b3 = gtk_button_get_label (GTK_BUTTON(b3));

    const gchar *etiq_c1 = gtk_button_get_label (GTK_BUTTON(c1));
    const gchar *etiq_c2 = gtk_button_get_label (GTK_BUTTON(c2));
    const gchar *etiq_c3 = gtk_button_get_label (GTK_BUTTON(c3));

    // Columna izq
    if ((g_strcmp0(etiq_a1,etiq_a2) == 0) && (g_strcmp0(etiq_a1,etiq_a3) == 0) && (etiq_a1 != NULL)){
        if(g_strcmp0(etiq_a1,"X") == 0){
            imprimir_mensaje("Gana X");
        }
        else if(g_strcmp0(etiq_a3,"O") == 0){
            imprimir_mensaje("Gana O");
        } 
        return true;
    }

    // Columna centro
    if ((g_strcmp0(etiq_b1,etiq_b2) == 0) && (g_strcmp0(etiq_b1,etiq_b3) == 0) && (etiq_b1 != NULL)){
        if(g_strcmp0(etiq_b1,"X") == 0){
            imprimir_mensaje("Gana X");
        }
        else if(g_strcmp0(etiq_a3,"O") == 0){
            imprimir_mensaje("Gana O");
        } 
        return true;
    }

    // Columna der
    if ((g_strcmp0(etiq_c1,etiq_c2) == 0) && (g_strcmp0(etiq_c1,etiq_c3) == 0) && (etiq_c1 != NULL)){
        if(g_strcmp0(etiq_c1,"X") == 0){
            imprimir_mensaje("Gana X");
        }
        else if(g_strcmp0(etiq_a3,"O") == 0){
            imprimir_mensaje("Gana O");
        } 
        return true;
    }

    // Fila arriba
    if ((g_strcmp0(etiq_a1,etiq_b1) == 0) && (g_strcmp0(etiq_a1,etiq_c1) == 0) && (etiq_a1 != NULL)){
        if(g_strcmp0(etiq_a1,"X") == 0){
            imprimir_mensaje("Gana X");
        }
        else if(g_strcmp0(etiq_a3,"O") == 0){
            imprimir_mensaje("Gana O");
        } 
        return true;
    }
    
    // Fila centro
    if ((g_strcmp0(etiq_a2,etiq_b2) == 0) && (g_strcmp0(etiq_a2,etiq_c2) == 0) && (etiq_a2 != NULL)){
        if(g_strcmp0(etiq_a2,"X") == 0){
            imprimir_mensaje("Gana X");
        }
        else if(g_strcmp0(etiq_a3,"O") == 0){
            imprimir_mensaje("Gana O");
        } 
        return true;
    }

    // Fila abajo
    if ((g_strcmp0(etiq_a3,etiq_b3) == 0) && (g_strcmp0(etiq_a3,etiq_c3) == 0) && (etiq_a3 != NULL)){
        if(g_strcmp0(etiq_a3,"X") == 0){
            imprimir_mensaje("Gana X");
        }
        else if(g_strcmp0(etiq_a3,"O") == 0){
            imprimir_mensaje("Gana O");
        } 
        return true;
    }

    // Diag izq
    if ((g_strcmp0(etiq_a1,etiq_b2) == 0) && (g_strcmp0(etiq_a1,etiq_c3) == 0) && (etiq_a1 != NULL)){
        if(g_strcmp0(etiq_a1,"X") == 0){
            imprimir_mensaje("Gana X");
        }
        else if(g_strcmp0(etiq_a3,"O") == 0){
            imprimir_mensaje("Gana O");
        } 
        return true;
    }

    // Diag der
    if ((g_strcmp0(etiq_a3,etiq_b2) == 0) && (g_strcmp0(etiq_a3,etiq_c1) == 0) && (etiq_a3 != NULL)){
        if(g_strcmp0(etiq_a3,"X") == 0){
            imprimir_mensaje("Gana X");
        }
        else if(g_strcmp0(etiq_a3,"O") == 0){
            imprimir_mensaje("Gana O");
        } 
        return true;
    }

    return false; // Si nadie gana
}

void revisar_empate(){
    // Revisa que ninguna casilla sea NULL
    // Por orden, se revisa fila por fila

    const gchar *etiq_a1 = gtk_button_get_label (GTK_BUTTON(a1));
    const gchar *etiq_a2 = gtk_button_get_label (GTK_BUTTON(a2));
    const gchar *etiq_a3 = gtk_button_get_label (GTK_BUTTON(a3));

    const gchar *etiq_b1 = gtk_button_get_label (GTK_BUTTON(b1));
    const gchar *etiq_b2 = gtk_button_get_label (GTK_BUTTON(b2));
    const gchar *etiq_b3 = gtk_button_get_label (GTK_BUTTON(b3));

    const gchar *etiq_c1 = gtk_button_get_label (GTK_BUTTON(c1));
    const gchar *etiq_c2 = gtk_button_get_label (GTK_BUTTON(c2));
    const gchar *etiq_c3 = gtk_button_get_label (GTK_BUTTON(c3));

    bool fila1 = false;
    bool fila2 = false;
    bool fila3 = false;

    if ((etiq_a1 != NULL) && (etiq_b1 != NULL) && (etiq_c1 != NULL)){
        fila1 = true;
    }

    if ((etiq_a2 != NULL) && (etiq_b2 != NULL) && (etiq_c2 != NULL)){
        fila2 = true;
    }

    if ((etiq_a3 != NULL) && (etiq_b3 != NULL) && (etiq_c3 != NULL)){
        fila3 = true;
    }

    if (fila1 && fila2 && fila3){
        imprimir_mensaje("Empate");
    }
}

void turno_completo(GtkWidget *boton){
    // Las acciones que se hacen en cada turno
    cambiar_letra(boton);
    bool gana = revisar_gane();
    if (gana == false) revisar_empate(); // Solo se revisa empate si nadie gano
}

// BOTONES //
void on_a1_clicked (GtkButton *b){
    turno_completo(a1);
}

void on_b1_clicked (GtkButton *b){
    turno_completo(b1);
}

void on_c1_clicked (GtkButton *b){
    turno_completo(c1);
}

void on_a2_clicked (GtkButton *b){
    turno_completo(a2);
}

void on_b2_clicked (GtkButton *b){
    turno_completo(b2);
}

void on_c2_clicked (GtkButton *b){
    turno_completo(c2);
}

void on_a3_clicked (GtkButton *b){
    turno_completo(a3);
}

void on_b3_clicked (GtkButton *b){
    turno_completo(b3);
}

void on_c3_clicked (GtkButton *b){
    turno_completo(c3);
}