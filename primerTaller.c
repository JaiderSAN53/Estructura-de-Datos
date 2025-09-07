#include <stdio.h> 
#define MAX 10 

void llenarArray(int vector[MAX], int n);

int main() { 
    int vector[MAX]; 
    int opc;  
    char confirm;
    do{ 
        printf("HOLA BIENVENID@S ;)\n");
        printf("Menu:\n");
        printf("1. Llenar array\n");
        printf("2. Mostrar array\n");
        printf("3. Ordenar array select Sort\n"); 
        printf("4. Ordenar array insertion Sort\n");
        printf("5. Salir\n"); 
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);
        switch(opc) { 
            case 1: 
                llenarArray (vector, MAX); 
                break;  
             case 5: {
                char confirm;
                printf(" Esta seguro que desea salir? (s/n): ");
                scanf(" %c", &confirm);
                if (confirm == 's' || confirm == 'S') {
                    opc = 5; // salir
                } else {
                    opc = 0; // volver al menú
                }
                break;
            }
        }
    }while (opc!=5); 
    printf("Hasta la proxima...\n");
   return 0;
}

void llenarArray(int vector[MAX], int n) {
    for (int i = 0; i < n; i++) {
        printf("Ingrese el valor de la posicion %d: ", i + 1);
        scanf("%d", &vector[i]);
        while (vector[i] < 0) {
            printf("Valor invalido. Ingrese un valor positivo %d: ", i + 1);
            scanf("%d", &vector[i]);
        }
        
    }
}