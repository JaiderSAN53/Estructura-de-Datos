#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct Pasajero
{ 
    char genero [1]; 
    char Apellido[20]; 
    int abordodados; 
    int no_abordodados;
    struct Pasajero *siguiente;
}; 

struct Pasajero* listaPasajeros = NULL; 

int capacidadMaxima =0; 
int tiquetesVendidos =0; 
int personasAbordadas =0; 
int capacidadVentana =0; 
int personasNoAbordadas =0; 

void establecerCapacidad(); 
void venderTiquetes(); 
void abordarPasajeros();
void mostrarEstadoVuelo();
void verNoAbordados(); 
void liberarMemoria();

int main() { 
    int opc; 
    do{  
        printf("\nMenu de Opciones:\n");
        printf("1. Establecer capacidad del vuelo\n");
        printf("2. Vender tiquetes\n");
        printf("3. Abordar pasajeros\n");
        printf("4. Mostrar estado del vuelo\n");
        printf("5. Ver pasajeros no abordados\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);
        
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
                mostrarEstadoVuelo();
                break;
            case 5:
                verNoAbordados();
                break;
            case 6:
                liberarMemoria();
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }

    }while(opc != 6); 
    return 0;
}

void establecerCapacidad() { 
    printf("Ingrese la capacidad maxima del vuelo: ");
    scanf("%d", &capacidadMaxima);
    capacidadVentana = capacidadMaxima * 0.1; 
    printf("Capacidad del vuelo establecida en %d pasajeros.\n", capacidadMaxima);
} 
void venderTiquetes() { 
    if(capacidadMaxima == 0) {
        printf("Primero debe establecer la capacidad del vuelo.\n");
        return;
    }
    int tiquetes;
    printf("Ingrese el numero de tiquetes a vender: ");
    scanf("%d", &tiquetes);
    if(tiquetesVendidos + tiquetes > capacidadMaxima) {
        tiquetesVendidos += tiquetes;
        printf("Tiquetes vendidos exitosamente. Total de tiquetes vendidos: %d\n", tiquetesVendidos);
    }
}
