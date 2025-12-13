#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    char nombre_destino[64];
    int cantidad_solicitada;
    struct Pedido *siguiente;
} Pedido;

typedef struct Node {
    int fecha_vencimiento;   // clave (ej: 20251204)
    int stock_total;
    char nombre_producto[64];
    Pedido *cabeza_pedidos;  // inicio de la cola FIFO (lista de espera de envío)
    struct Node *left, *right;
    int height;
} Node;

/* ---------- AVL utilities ---------- */
static int node_height(Node *n) { return n ? n->height : 0; }
static int max(int a, int b) { return a > b ? a : b; }
static void actualizar_altura(Node *n) { if (n) n->height = 1 + max(node_height(n->left), node_height(n->right)); }

static Node* rotar_derecha(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    actualizar_altura(y);
    actualizar_altura(x);
    return x;
}

static Node* rotar_izquierda(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    actualizar_altura(x);
    actualizar_altura(y);
    return y;
}

static int get_balance(Node *n) { return n ? node_height(n->left) - node_height(n->right) : 0; }

/* ---------- Cola FIFO (Lista de espera) ---------- */
void encolar_pedido(Node *prod, const char *nombre_destino, int cantidad_solicitada) {
    if (!prod) return;
    Pedido *p = malloc(sizeof(Pedido));
    if (!p) { perror("malloc"); exit(EXIT_FAILURE); }
    strncpy(p->nombre_destino, nombre_destino, sizeof(p->nombre_destino)-1);
    p->nombre_destino[sizeof(p->nombre_destino)-1] = '\0';
    p->cantidad_solicitada = cantidad_solicitada;
    p->siguiente = NULL;
    if (!prod->cabeza_pedidos) prod->cabeza_pedidos = p;
    else {
        Pedido *q = prod->cabeza_pedidos;
        while (q->siguiente) q = q->siguiente;
        q->siguiente = p;
    }
}

Pedido* desencolar_pedido(Node *prod) {
    if (!prod || !prod->cabeza_pedidos) return NULL;
    Pedido *p = prod->cabeza_pedidos;
    prod->cabeza_pedidos = p->siguiente;
    p->siguiente = NULL;
    return p;
}

/* elimina el primer pedido que coincida (nombre_destino y cantidad), devuelve 1 si eliminado */
int eliminar_pedido_especifico(Node *prod, const char *nombre_destino, int cantidad_solicitada) {
    if (!prod || !prod->cabeza_pedidos) return 0;
    Pedido *prev = NULL;
    Pedido *curr = prod->cabeza_pedidos;
    while (curr) {
        if (strcmp(curr->nombre_destino, nombre_destino) == 0 && curr->cantidad_solicitada == cantidad_solicitada) {
            if (prev) prev->siguiente = curr->siguiente;
            else prod->cabeza_pedidos = curr->siguiente;
            /* restablecer stock */
            prod->stock_total += curr->cantidad_solicitada;
            free(curr);
            return 1;
        }
        prev = curr;
        curr = curr->siguiente;
    }
    return 0;
}

int contar_pedidos(Pedido *p) {
    int c = 0;
    while (p) { c++; p = p->siguiente; }
    return c;
}

/* ---------- AVL: crear, insertar (único), buscar, eliminar ---------- */
Node* create_node(int fecha, const char *nombre, int stock) {
    Node *n = malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->fecha_vencimiento = fecha;
    n->stock_total = stock;
    strncpy(n->nombre_producto, nombre, sizeof(n->nombre_producto)-1);
    n->nombre_producto[sizeof(n->nombre_producto)-1] = '\0';
    n->cabeza_pedidos = NULL;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

/* Inserción que falla si la fecha ya existe (inserted = 1 si insertado) */
Node* avl_insert_unique(Node *root, int fecha, const char *nombre, int stock, int *inserted) {
    if (!root) {
        *inserted = 1;
        return create_node(fecha, nombre, stock);
    }
    if (fecha < root->fecha_vencimiento)
        root->left = avl_insert_unique(root->left, fecha, nombre, stock, inserted);
    else if (fecha > root->fecha_vencimiento)
        root->right = avl_insert_unique(root->right, fecha, nombre, stock, inserted);
    else {
        /* ya existe la fecha -> no procesar */
        *inserted = 0;
        return root;
    }

    actualizar_altura(root);
    int balance = get_balance(root);

    if (balance > 1 && fecha < root->left->fecha_vencimiento) return rotar_derecha(root);
    if (balance < -1 && fecha > root->right->fecha_vencimiento) return rotar_izquierda(root);
    if (balance > 1 && fecha > root->left->fecha_vencimiento) {
        root->left = rotar_izquierda(root->left);
        return rotar_derecha(root);
    }
    if (balance < -1 && fecha < root->right->fecha_vencimiento) {
        root->right = rotar_derecha(root->right);
        return rotar_izquierda(root);
    }
    return root;
}

Node* avl_search(Node *root, int fecha) {
    if (!root) return NULL;
    if (fecha == root->fecha_vencimiento) return root;
    if (fecha < root->fecha_vencimiento) return avl_search(root->left, fecha);
    return avl_search(root->right, fecha);
}

/* encuentra el nodo con fecha más cercana a vencer (mínima fecha) */
Node* encontrar_mas_cerca_vencer(Node *root) {
    if (!root) return NULL;
    Node *n = root;
    while (n->left) n = n->left;
    return n;
}

Node* find_min_node(Node *n) { while (n && n->left) n = n->left; return n; }

Node* avl_delete(Node *root, int fecha) {
    if (!root) return NULL;
    if (fecha < root->fecha_vencimiento) root->left = avl_delete(root->left, fecha);
    else if (fecha > root->fecha_vencimiento) root->right = avl_delete(root->right, fecha);
    else {
        /* liberar cola de pedidos */
        Pedido *p = root->cabeza_pedidos;
        while (p) { Pedido *tmp = p->siguiente; free(p); p = tmp; }
        if (!root->left || !root->right) {
            Node *temp = root->left ? root->left : root->right;
            if (!temp) { free(root); return NULL; }
            else {
                *root = *temp;
                free(temp);
            }
        } else {
            Node *succ = find_min_node(root->right);
            root->fecha_vencimiento = succ->fecha_vencimiento;
            strncpy(root->nombre_producto, succ->nombre_producto, sizeof(root->nombre_producto));
            root->stock_total = succ->stock_total;
            /* mover cola de pedidos */
            root->cabeza_pedidos = succ->cabeza_pedidos;
            succ->cabeza_pedidos = NULL;
            root->right = avl_delete(root->right, succ->fecha_vencimiento);
        }
    }

    if (!root) return root;

    actualizar_altura(root);
    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0) return rotar_derecha(root);
    if (balance > 1 && get_balance(root->left) < 0) { root->left = rotar_izquierda(root->left); return rotar_derecha(root); }
    if (balance < -1 && get_balance(root->right) <= 0) return rotar_izquierda(root);
    if (balance < -1 && get_balance(root->right) > 0) { root->right = rotar_derecha(root->right); return rotar_izquierda(root); }
    return root;
}

/* ---------- Impresión / reportes ---------- */
void imprimir_pedidos(Pedido *p) {
    if (!p) { printf("    Pedidos en espera: 0\n"); return; }
    int c = 0;
    while (p) { c++; p = p->siguiente; }
    printf("    Pedidos en espera: %d\n", c);
}

void inorder_informe(Node *root) {
    if (!root) return;
    inorder_informe(root->left);
    printf("Fecha: %d | Producto: %s | Stock disponible: %d\n",
           root->fecha_vencimiento, root->nombre_producto, root->stock_total);
    imprimir_pedidos(root->cabeza_pedidos);
    inorder_informe(root->right);
}

/* liberar todo */
void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    Pedido *p = root->cabeza_pedidos;
    while (p) { Pedido *tmp = p->siguiente; free(p); p = tmp; }
    free(root);
}

/* ---------- Interfaz consola ---------- */
int main(void) {
    Node *root = NULL;
    int opc = -1;
    while (opc != 0) {
        printf("\n--- Sistema (AVL por fecha) + Cola FIFO (Lista de espera) ---\n");
        printf("1) Recepcion de mercancia\n");
        printf("2) Registrar pedido de despacho (Encolar FIFO)\n");
        printf("3) Cancelacion\n");
        printf("4) Reporte de estado (In-Order: fecha mas proxima -> mas lejana)\n");
        printf("0) Salir\nOpcion: ");
        if (scanf("%d", &opc) != 1) break;

        if (opc == 1) {
            int fecha, stock;
            char nombre[64];
            printf("Fecha vencimiento (YYYYMMDD): "); scanf("%d", &fecha);
            /* verificar existencia */
            if (avl_search(root, fecha)) {
                printf("Error: ya existe un lote con esa fecha. No se puede procesar.\n");
                continue;
            }
            printf("Nombre producto: "); scanf(" %63[^\n]", nombre);
            printf("Stock total del lote: "); scanf("%d", &stock);
            int inserted = 0;
            root = avl_insert_unique(root, fecha, nombre, stock, &inserted);
            if (inserted) printf("Lote insertado correctamente.\n");
            else printf("No se pudo insertar el lote.\n");
        } else if (opc == 2) {
            /* buscar lote con fecha mas cercana a vencer */
            Node *lote = encontrar_mas_cerca_vencer(root);
            if (!lote) { printf("No hay productos registrados.\n"); continue; }
            printf("Lote seleccionado (más próximo a vencer): Fecha %d | Producto: %s | Stock: %d\n",
                   lote->fecha_vencimiento, lote->nombre_producto, lote->stock_total);
            char destino[64];
            int cant;
            printf("Nombre destino (ej: Nuqui, Guapi): "); scanf(" %63[^\n]", destino);
            printf("Cantidad solicitada: "); scanf("%d", &cant);
            if (cant <= 0) { printf("Cantidad inválida.\n"); continue; }
            if (lote->stock_total >= cant) {
                encolar_pedido(lote, destino, cant);
                lote->stock_total -= cant;
                printf("Pedido encolado y stock descontado. Stock restante: %d\n", lote->stock_total);
            } else {
                printf("Stock insuficiente para atender pedido. Pedido NO encolado.\n");
            }
        } else if (opc == 3) {
            int sub;
            printf("3.1) Baja de producto (eliminar lote)\n");
            printf("3.2) Cancelar pedido en lista de espera\n");
            printf("Elija opcion (1=Eliminar lote, 2=Cancelar pedido): "); scanf("%d", &sub);
            if (sub == 1) {
                int fecha;
                printf("Fecha del lote a eliminar: "); scanf("%d", &fecha);
                if (!avl_search(root, fecha)) {
                    printf("No existe lote con esa fecha.\n");
                } else {
                    root = avl_delete(root, fecha);
                    printf("Lote eliminado (si existia).\n");
                }
            } else if (sub == 2) {
                int fecha;
                char destino[64];
                int cantidad;
                printf("Fecha del lote donde buscar pedido: "); scanf("%d", &fecha);
                Node *n = avl_search(root, fecha);
                if (!n) { printf("No existe lote con esa fecha.\n"); continue; }
                printf("Nombre destino del pedido a cancelar: "); scanf(" %63[^\n]", destino);
                printf("Cantidad solicitada del pedido a cancelar: "); scanf("%d", &cantidad);
                int eliminado = eliminar_pedido_especifico(n, destino, cantidad);
                if (eliminado) printf("Pedido cancelado y stock restablecido.\n");
                else printf("No se encontró pedido con esos datos en la lista de espera.\n");
            } else {
                printf("Opcion invalida.\n");
            }
        } else if (opc == 4) {
            if (!root) { printf("No hay productos registrados.\n"); continue; }
            printf("Reporte In-Order (fecha más proxima -> más lejana):\n");
            inorder_informe(root);
        }
    }

    free_tree(root);
    return 0;
} 
