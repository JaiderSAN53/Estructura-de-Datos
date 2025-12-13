## 🚢 Sistema Logístico Marítimo de Despacho de Mercancía (AVL + FIFO)
Sistema en C para gestionar la recepción de mercancías, el registro de pedidos de despacho a distintos destinos marítimos (ej.: Nuquí, Guapi), la cancelación de lotes o pedidos y la emisión de reportes ordenados por fecha de vencimiento. 
- La lógica combina:

- Árbol AVL (ordenado por YYYYMMDD) para los lotes de productos.
Cola FIFO por lote para mantener la lista de pedidos en orden de llegada.


 - Objetivo operativo: aplicar el principio FEFO (First-Expire, First-Out): los pedidos se atienden desde el lote más próximo a vencer. 

 ## 🧭 Flujo General del Sistema 
 
┌────────────────────────────────────────────────────────────┐
│                        Menú Principal                      │
│ 1) Recepción de mercancía (insertar lote en AVL)           │
│ 2) Registrar pedido de despacho (encolar en FIFO del lote) │
│ 3) Cancelación (baja de lote / cancelar pedido específico) │
│ 4) Reporte In-Order (de fecha más próxima -> más lejana)   │
│ 0) Salir                                                   │
└────────────────────────────────────────────────────────────┘

Estructura:
           Árbol AVL de Lotes (ordenado por fecha de vencimiento)
                          │
                          ├── Nodo Lote (fecha, producto, stock)
                          │        └── Cola FIFO de Pedidos (destino, cantidad)
                          └── ...

## ⚙️ Características Clave

- ✅ Recepción de mercancía: inserta lotes únicos por fecha de vencimiento (formato YYYYMMDD).
- 🚚 Registro de pedidos: selecciona automáticamente el lote más próximo a vencer y encola el pedido a su lista de espera si hay stock suficiente.
- ❌ Cancelación:

* Elimina un lote del AVL por fecha.
* Cancela un pedido específico (por destino y cantidad) dentro de la cola del lote y restaura stock.


- 📊 Reporte: listado In-Order (de fecha más cercana → más lejana).
- 🧹 Memoria: limpieza total del árbol y sus colas al salir. 

##  👨‍💻 INTEGRANTES
- Jaider Stiven Advincula Nuñez 
- Luis Ernesto Oliveros Campos