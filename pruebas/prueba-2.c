#include <stdio.h>
#include <string.h>

#define N 3  // Número de estudiantes

typedef struct {
    int codigo;
    float nota;
    char nombre[50];
} Elemento;

// Función para intercambiar dos elementos
void swap(Elemento *a, Elemento *b) {
    Elemento temp = *a;
    *a = *b;
    *b = temp;
}

// Encuentra el índice del mínimo código en el rango [inicio, N)
int indiceMinimo(Elemento lista[], int inicio, int n) {
    int min = inicio;
    for (int i = inicio + 1; i < n; i++) {
        if (lista[i].codigo < lista[min].codigo) {
            min = i;
        }
    }
    return min;
}

// Selection Sort recursivo
void selectionSortRecursivo(Elemento lista[], int inicio, int n) {
    if (inicio >= n - 1) return;  // Caso base

    int min = indiceMinimo(lista, inicio, n);

    if (min != inicio) {
        swap(&lista[inicio], &lista[min]);
    }

    selectionSortRecursivo(lista, inicio + 1, n);
}

int main() {
    Elemento lista[N] = {
        {1003, 9.2, "Luis Torres"},
        {1001, 8.5, "Juan Perez"},
        {1002, 7.0, "Ana Gomez"}
    };

    int opcion;
    printf("Menu de opciones:\n");
    printf("1. Mostrar nota maxima\n");
    printf("2. Mostrar promedio\n");
    printf("3. Ordenar lista por codigo (Selection Sort Recursivo)\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        float nota_max = lista[0].nota;
        int pos = 0;
        for (int i = 1; i < N; i++) {
            if (lista[i].nota > nota_max) {
                nota_max = lista[i].nota;
                pos = i;
            }
        }
        printf("La nota maxima es %.1f, de %s (codigo %d)\n",
               lista[pos].nota, lista[pos].nombre, lista[pos].codigo);

    } else if (opcion == 2) {
        float suma = 0.0;
        for (int i = 0; i < N; i++) {
            suma += lista[i].nota;
        }
        float promedio = suma / N;
        printf("El promedio del curso es %.2f\n", promedio);

    } else if (opcion == 3) {
        printf("\nLista original:\n");
        for (int i = 0; i < N; i++) {
            printf("%d - %s (nota: %.1f)\n", lista[i].codigo, lista[i].nombre, lista[i].nota);
        }

        selectionSortRecursivo(lista, 0, N);

        printf("\nLista ordenada por codigo (ascendente):\n");
        for (int i = 0; i < N; i++) {
            printf("%d - %s (nota: %.1f)\n", lista[i].codigo, lista[i].nombre, lista[i].nota);
        }

    } else {
        printf("Opcion no valida.\n");
    }

    return 0;
}