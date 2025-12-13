#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

struct pasajeros
{
   documento[10]; 
   destino[30]; 
   tipo_pasaje[15]; 
   struct pasajeros*siguiente;
};
struct pasajeros* listaViajeros = NULL; 

int capacidadMaxima = 0;
int tiquetesVendidos = 0;
int abordados = 0; 
int abordajeIniciado = 0;  
int pasajeros = 0;

void establecerCapacidad(); 
void venderTiquetes(); 
void abordarPasajeros();
void verAbordados(); 
void conteototal(); 
void eliminarpasajero();  
void liberarmemoria();

int main() { 
    int opc; 
    do{ 
        printf("\n Bienvenidos a el Paraiso \n  \n ");
        printf("\nMenu de Opciones:\n");
        printf("1. Establecer capacidad de la lancha\n");
        printf("2. Vender tiquetes\n");
        printf("3. Abordar pasajeros\n"); 
        printf("4. Eliminar pasajeros\n");
        printf("5. Hacer conteo de todos los pasajeros\n");
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
                conteototal(); 
                break;
            case 5:
                eliminarpasajero();
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
    printf("Ingrese la capacidad maxima de la lancha: ");
    if (scanf("%d", &capacidadMaxima) != 1 || capacidadMaxima <= 0) {
        printf("Capacidad invalida. Debe ser un numero entero positivo.\n");
        capacidadMaxima = 0;
        while (getchar() != '\n');
        return;
    }
    
    printf("Capacidad de la lancha establecida en %d pasajeros.\n", capacidadMaxima);
}  

void venderTiquetes() { 
    if(capacidadMaxima == 0) {
        printf("Primero debe establecer la capacidad del viaje (Opcion 1).\n");
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
        printf("Ingrese documento: ");
        if (scanf("%9s", nuevoPasajero->documento) != 1) { 
            strcpy(nuevoPasajero->documento, "N/A");
            while (getchar() != '\n');
        }
        
        nuevoPasajero->abordado = 0;
        nuevoPasajero->siguiente = NULL;
    
        
        if (listaViajeros   == NULL) {
            listaViajeros = nuevoPasajero;
        } else {
            struct Pasajero* temp = listaViajeros;
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
    struct Pasajero* actual = listaViajeros;
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

void conteototal() {
    if (abordajeIniciado == 0) {
        printf("El proceso de abordaje aun no ha iniciado.\n");
        return;
    }
    if (abordados == 0) {
        printf("Aun no ha abordado ningun pasajero.\n");
        return;
    }
    
    printf("\n--- Lista de Pasajeros Abordados (%d) ---\n", abordados);
    struct Pasajero* actual = listaViajeros;
    while (actual != NULL) {
        if (actual->abordado) {
            printf("Genero: %s, Apellido: %s, Documento: %d\n", actual->genero, actual->Apellido, actual->documento);
        }
        actual = actual->siguiente;
    }
}

void eliminarpasajero() {
    if (listaViajeros == NULL) {
        printf("No hay pasajeros en la lista.\n");
        return;
    }
    
    char docEliminar[10];
    printf("Ingrese el documento del pasajero a eliminar: ");
    if (scanf("%9s", docEliminar) != 1) { 
        printf("Documento invalido.\n");
        while (getchar() != '\n');
        return;
    }
    
    struct Pasajero* actual = listaViajeros;
    struct Pasajero* anterior = NULL;
    int encontrado = 0;
    
    while (actual != NULL) {
        if (strcmp(actual->documento, docEliminar) == 0) {
            encontrado = 1;
            if (anterior == NULL) {
                listaViajeros = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
            tiquetesVendidos--;
            printf("Pasajero con documento %s eliminado.\n", docEliminar);
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (!encontrado) {
        printf("Pasajero con documento %s no encontrado.\n", docEliminar);
    }
} void liberarmemoria() {
    struct Pasajero* actual = listaViajeros;
    while (actual != NULL) {
        struct Pasajero* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    listaViajeros = NULL;
}

