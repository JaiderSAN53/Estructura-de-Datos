#include <stdio.h> 
#define MAX 10 

void llenarArray(int vector[MAX], int n);
void mostrarArray(int vector[MAX], int n); 
void selectionSort(int arreglo[MAX], int n); 
int main() { 
    int vector[MAX]; 
    int opc;  
    char confirm;
    do {
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
            case 2: 
                mostrarArray (vector, MAX);
                break;  
            case 3: 
                selectionSort (vector, MAX);
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
void mostrarArray(int vector[MAX], int n) {
    printf("Posicion cambiada:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
} 

void selectionSort(int arreglo[MAX], int n) {
     for (int i = 0; i < n - 1; i++) {
          int minIndex = i;
          // Encontrar el mínimo en arreglo[i..n-1]
         for (int j = i + 1; j < n; j++) {
             if (arreglo[j] < arreglo[minIndex]) {
                 minIndex = j;
            }
        }
         // Intercambiar el mínimo encontrado con el elemento en i
        int temp = arreglo[i];
        arreglo[i] = arreglo[minIndex];
        arreglo[minIndex] = temp;  
        printf("\nintercambio %d con %d\n", arreglo[minIndex], arreglo[i]);
        mostrarArray(arreglo, n);
    }
}
