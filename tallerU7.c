#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct Pasajero
{ 
    char genero[15]; // Aumentado para almacenar "Femenino" o "Masculino"
    char Apellido[20]; 
    int abordado;    
    struct Pasajero *siguiente;
}; 

struct Pasajero* listaPasajeros = NULL; 


int capacidadMaxima = 0; 
int tiquetesVendidos = 0; 
int abordados = 0;        
int abordajeIniciado = 0;   


void establecerCapacidad(); 
void venderTiquetes(); 
void abordarPasajeros();
void verAbordados();
void verNoAbordados(); 
void liberarMemoria();

int main() { 
    int opc; 
    do{ 
        printf("\nMenu de Opciones:\n");
        printf("1. Establecer capacidad del vuelo\n");
        printf("2. Vender tiquetes\n");
        printf("3. Abordar pasajeros\n"); 
        printf("4. Ver pasajeros abordados\n");
        printf("5. Ver pasajeros no abordados\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        
        
        if (scanf("%d", &opc) != 1) {
            opc = 0; 
            while (getchar() != '\n'); 
        }
        
        switch(opc) {
            case 1:
                establecerCapacidad();
                break;
            case 2:
                venderTiquetes();
                break;
            case 3:
                abordarPasajeros();
                break;
            case 4:
                verAbordados();
                break;
            case 5:
                verNoAbordados();
                break;
            case 6:
                liberarMemoria();
                printf("Saliendo del programa. Memoria liberada.\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }

    }while(opc != 6); 
    return 0;
}



void establecerCapacidad() { 
    printf("Ingrese la capacidad maxima del vuelo: ");
    if (scanf("%d", &capacidadMaxima) != 1 || capacidadMaxima <= 0) {
        printf("Capacidad invalida. Debe ser un numero entero positivo.\n");
        capacidadMaxima = 0;
        while (getchar() != '\n');
        return;
    }
    
    printf("Capacidad del vuelo establecida en %d pasajeros.\n", capacidadMaxima);
} 



void venderTiquetes() { 
    if(capacidadMaxima == 0) {
        printf("Primero debe establecer la capacidad del vuelo (Opcion 1).\n");
        return;
    }
    
    int tiquetes;
    printf("Ingrese el numero de tiquetes a vender: ");
    if (scanf("%d", &tiquetes) != 1 || tiquetes <= 0) {
        printf("Numero de tiquetes a vender invalido.\n");
        while (getchar() != '\n');
        return;
    }

    
    if(tiquetesVendidos + tiquetes > capacidadMaxima) {
         printf("ADVERTENCIA: Se superara la capacidad maxima del vuelo (%d).\n", capacidadMaxima);
    } 

    for (int i = 0; i < tiquetes; i++) {
        struct Pasajero* nuevoPasajero = (struct Pasajero*)malloc(sizeof(struct Pasajero));
        if (nuevoPasajero == NULL) {
            printf("Error de memoria. No se pudo vender el resto de tiquetes.\n");
            return;
        }
        
        printf("\n--- Datos Pasajero #%d ---\n", tiquetesVendidos + 1);
        
        
        printf("Ingrese genero (Ej: M, F, Otro): ");
        if (scanf("%14s", nuevoPasajero->genero) != 1) { 
             strcpy(nuevoPasajero->genero, "N/A");
             while (getchar() != '\n');
        }
        
        printf("Ingrese primer apellido: ");
        if (scanf("%19s", nuevoPasajero->Apellido) != 1) { 
            strcpy(nuevoPasajero->Apellido, "N/A");
            while (getchar() != '\n');
        }
        
        
        nuevoPasajero->abordado = 0;
        nuevoPasajero->siguiente = NULL;
    
        
        if (listaPasajeros == NULL) {
            listaPasajeros = nuevoPasajero;
        } else {
            struct Pasajero* temp = listaPasajeros;
            while (temp->siguiente != NULL) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoPasajero;
        } 
        
        tiquetesVendidos++;
    }

    printf("Venta finalizada. Total de tiquetes vendidos: %d\n", tiquetesVendidos);
}



void abordarPasajeros() {
    if (capacidadMaxima == 0) {
        printf("Primero debe establecer la capacidad del avion.\n");
        return;
    }
    if (abordajeIniciado) {
        printf("El abordaje ya ha sido iniciado. Pasajeros abordados: %d.\n", abordados);
        return;
    }
    if (tiquetesVendidos == 0) {
         printf("No hay tiquetes vendidos para abordar.\n");
        return;
    }
    
    abordajeIniciado = 1;
    struct Pasajero* actual = listaPasajeros;
    abordados = 0; 
    
    printf("Iniciando proceso de abordaje...\n");

    while (actual != NULL && abordados < capacidadMaxima) {
        actual->abordado = 1;
        abordados++;
        actual = actual->siguiente;
    }
    
    printf("Proceso de abordaje finalizado.\n");
    printf("Pasajeros abordados: %d\n", abordados);
    printf("Pasajeros que no abordaron (debido a sobreventa): %d\n", tiquetesVendidos - abordados);
} 



void verAbordados() {
    if (abordajeIniciado == 0) {
        printf("El proceso de abordaje aun no ha iniciado.\n");
        return;
    }
    if (abordados == 0) {
        printf("Aun no ha abordado ningun pasajero.\n");
        return;
    }
    
    printf("\n--- Lista de Pasajeros Abordados (%d) ---\n", abordados);
    struct Pasajero* actual = listaPasajeros;
    while (actual != NULL) {
        if (actual->abordado) {
            printf("Genero: %s, Apellido: %s\n", actual->genero, actual->Apellido);
        }
        actual = actual->siguiente;
    }
}



void verNoAbordados(){
    if (abordajeIniciado == 0) {
        printf("El proceso de abordaje aun no ha iniciado. Todos los pasajeros estan en espera.\n");
        return;
    }
    int noAbordados = tiquetesVendidos - abordados;
    if (noAbordados <= 0) {
        printf("Todos los pasajeros con tiquete lograron abordar.\n");
        return;
    }
    
    printf("\n--- Lista de Pasajeros No Abordados (%d) ---\n", noAbordados);
    struct Pasajero* actual = listaPasajeros;
    while (actual != NULL) {
        if (!actual->abordado) {
            printf("Genero: %s, Apellido: %s\n", actual->genero, actual->Apellido);
        }
        actual = actual->siguiente;
    }
}



void liberarMemoria() {
    struct Pasajero* actual = listaPasajeros;
    struct Pasajero* siguiente;
    
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    listaPasajeros = NULL; 
}