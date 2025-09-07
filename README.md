# 💻 Taller de Ordenamiento de Números

Este proyecto es parte del curso de **Estructura de Datos**.

### **¿Qué hace?**

El programa ordena 10 números que representan tiempos de soporte.

* **Primero:** Los ordena de **menor a mayor** usando el algoritmo **Selection Sort**.
* **Luego:** Los ordena de **mayor a menor** usando el algoritmo **Insertion Sort**.


### **Integrantes**

* Luis Ernesto Oliveros
* Jaider Stiven Advincula

## PASOS PARA LA SOLUCIÓN DEL TALLER

##  Entrada de datos: `llenarArray`


### ✅ Funcionalidad implementada

Se ha desarrollado la función `llenarArray(int a[], int n)` que permite al usuario ingresar **10 tiempos** (valores enteros) por teclado.

### 🔒 Validaciones incluidas

- Cada tiempo ingresado debe ser un **entero positivo**.
- Si el usuario ingresa un valor no válido (negativo, cero o no entero), se le solicita que lo vuelva a ingresar hasta que cumpla con los requisitos.


### 🧠 Lógica utilizada

La función utiliza un bucle `for` para recorrer el arreglo y solicitar los valores uno por uno. Se incluye una validación dentro de un bucle `while` para asegurar que cada entrada sea válida antes de almacenarla.

### 📌 Ejemplo de uso

```c
int tiempos[10];
llenarArray(tiempos, 10);

# 🧠 Menú Interactivo 
se ha implementado un menú interactivo que permite al usuario elegir entre las siguientes opciones: 


## 🚀 Funcionalidades

1. Mostrar mensaje de bienvenida.
5. Salir del programa (con confirmación).