#include <stdio.h> 
#define NUM_ESTUDIANTES 5
#define NUM_NOTAS 1 


struct Estudiante 
{
    int codigo; 
    float notas[NUM_NOTAS]; 
    float promedio;
};

int main() { 
    struct  Estudiante estudiantes[NUM_ESTUDIANTES] =
    {
        {2021,{0}},
        {2022,{0}},
        {2023,{0}},
        {2024,{0}},
        {2025,{0}}
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
    
        printf("Codigo: %d - Notas: ", estudiantes[i].codigo);
        for (int j = 0; j < NUM_NOTAS; j++){
    
        
            printf("%.2f ", estudiantes[i].notas[j]);
        }
        printf("\n");
    }
    return 0;
}