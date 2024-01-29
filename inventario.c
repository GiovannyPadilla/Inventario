#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 10
#define MAX_NAME_LEN 50
#define FILE_NAME "inventario.txt"

struct Producto {
    int id;
    char nombre[MAX_NAME_LEN];
    float precio_compra;
    float precio_venta;
    int cantidad;
};

struct Producto inventario[MAX_PRODUCTS];
int contador_productos = 0;

void agregar_producto() {
    if (contador_productos >= MAX_PRODUCTS) {
        printf("Inventario lleno.\n");
        return;
    }

    struct Producto p;
    printf("Introduce ID del producto: ");
    scanf("%d", &p.id);
    printf("Introduce nombre del producto: ");
    scanf("%s", p.nombre);
    printf("Introduce precio de compra: ");
    scanf("%f", &p.precio_compra);
    printf("Introduce precio de venta: ");
    scanf("%f", &p.precio_venta);
    printf("Introduce cantidad: ");
    scanf("%d", &p.cantidad);

    inventario[contador_productos] = p;
    contador_productos++;
    printf("Producto agregado.\n");
}

void mostrar_inventario() {
    printf("Inventario:\n");
    for (int i = 0; i < contador_productos; i++) {
        struct Producto p = inventario[i];
        printf("%d - %s - Compra: %.2f, Venta: %.2f, Cantidad: %d\n", 
               p.id, p.nombre, p.precio_compra, p.precio_venta, p.cantidad);
    }
}

void guardar_inventario() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error al guardar.\n");
        return;
    }

    for (int i = 0; i < contador_productos; i++) {
        struct Producto p = inventario[i];
        fprintf(file, "%d %s %.2f %.2f %d\n", p.id, p.nombre, p.precio_compra, p.precio_venta, p.cantidad);
    }

    fclose(file);
    printf("Inventario guardado.\n");
}

void cargar_inventario() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Archivo no encontrado.\n");
        return;
    }

    struct Producto p;
    contador_productos = 0;
    while (fscanf(file, "%d %s %f %f %d", &p.id, p.nombre, &p.precio_compra, &p.precio_venta, &p.cantidad) == 5) {
        inventario[contador_productos] = p;
        contador_productos++;
    }

    fclose(file);
    printf("Inventario cargado.\n");
}

int main() {
    cargar_inventario();

    int opcion;
    do {
        printf("\nMenu:\n");
        printf("1. Agregar Producto\n");
        printf("2. Mostrar Inventario\n");
        printf("3. Guardar y Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregar_producto();
                break;
            case 2:
                mostrar_inventario();
                break;
            case 3:
                guardar_inventario();
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 3);

    return 0;
}
