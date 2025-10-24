#include <stdio.h>  
#include <string.h>
#define NUM_ESTUDIANTES 5
#define NUM_NOTAS 1 


struct Estudiante 
{
    int codigo; 
    float notas[NUM_NOTAS]; 
    float promedio; 
    char nombre[30]; // <-- Agrega este campo 
    char confirm;
};

int main() { 
    struct  Estudiante estudiantes[NUM_ESTUDIANTES] =
    {
        {2021,{0},0,"Angie Patricia"},
        {2022,{0},0,"Juan Perez"},
        {2023,{0},0,"Maria Lopez"},
        {2024,{0},0,"Carlos Sanchez"},
        {2025,{0},0,"Laura Garcia"}
    };
    for (int i = 0; i < NUM_ESTUDIANTES; i++)
    {
        printf("Ingrese la nota del estudiante %d:\n", estudiantes[i].codigo);
        for (int j = 0; j < NUM_NOTAS; j++)
        {
            printf("Nota %d: ", j + 1);
            scanf("%f", &estudiantes[i].notas[j]);
        }
    } 
    printf("\n listado de estudiantes y sus notas:\n");
    for (int i = 0; i < NUM_ESTUDIANTES; i++){

        printf("Codigo: %d Nombre: %s - Notas: ", estudiantes[i].codigo, estudiantes[i].nombre);
        for (int j = 0; j < NUM_NOTAS; j++){
            printf("%.2f ", estudiantes[i].notas[j]);
        }
        printf("\n");
    }

    int opcion;
    do {
        printf("Menu de opciones:\n");
        printf("1. Mostrar nota maxima\n");
        printf("2. Mostrar promedio\n");
        printf("3. Ordenar lista por codigo (Selection Sort Recursivo)\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: {
                // Mostrar nota maxima
                for (int i = 0; i < NUM_ESTUDIANTES; i++) {
                    float max = estudiantes[i].notas[0];
                    for (int j = 1; j < NUM_NOTAS; j++) {
                        if (estudiantes[i].notas[j] > max) {
                            max = estudiantes[i].notas[j];
                        }
                    }
                    printf("La nota maxima de %s es: %.2f\n", estudiantes[i].nombre, max);
                }
                break;
            }
            case 2: {
                // Mostrar promedio
                for (int i = 0; i < NUM_ESTUDIANTES; i++) {
                    float suma = 0;
                    for (int j = 0; j < NUM_NOTAS; j++) {
                        suma += estudiantes[i].notas[j];
                    }
                    estudiantes[i].promedio = suma / NUM_NOTAS;
                    printf("El promedio de %s es: %.2f\n", estudiantes[i].nombre, estudiantes[i].promedio);
                }
                break;
            }
            case 3: {
                // Ordenar lista por codigo (Selection Sort Recursivo)
                for (int i = 0; i < NUM_ESTUDIANTES - 1; i++) {
                    int minIndex = i;
                    for (int j = i + 1; j < NUM_ESTUDIANTES; j++) {
                        if (estudiantes[j].codigo < estudiantes[minIndex].codigo) {
                            minIndex = j;
                        }
                    }
                    if (minIndex != i) {
                        struct Estudiante temp = estudiantes[i];
                        estudiantes[i] = estudiantes[minIndex];
                        estudiantes[minIndex] = temp;
                    }
                }
                printf("\nLista ordenada por codigo:\n");
                for (int i = 0; i < NUM_ESTUDIANTES; i++) {
                    printf("Codigo: %d - Nombre: %s - Promedio: %.2f\n", 
                           estudiantes[i].codigo, estudiantes[i].nombre, estudiantes[i].promedio);
                }
                break; 
                
            } 
            case 4: {
                char confirm;
                printf(" Esta seguro que desea salir? (s/n): ");
                scanf(" %c", &confirm);
                if (confirm == 's' || confirm == 'S') {
                    opcion = 4; // salir
                } else {
                    opcion = 0; // volver al menú
                }
                break;
            }
            default:
                printf("Opcion no valida\n"); 
        }
    } while (opcion != 4);
    printf("Hasta la proxima...\n");
    return 0;
}