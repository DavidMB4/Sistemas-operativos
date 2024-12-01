#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max_particiones 100
#define max_procesos 100

typedef struct {
    int tamano;
    int id_de_proceso; 
} Particion;

void imprime_memoria(Particion particion[], int numero_de_particiones) {
    printf("\nEstado de la memoria:\n");
    for (int i = 0; i < numero_de_particiones; i++) {
        if (particion[i].id_de_proceso == -1) {
            printf("Partición %d: %d KB (Libre)\n", i + 1, particion[i].tamano);
        } else {
            printf("Partición %d: %d KB (Proceso %d)\n", i + 1, particion[i].tamano, particion[i].id_de_proceso);
        }
    }
    printf("\n");
}

void ingresar_tamano(Particion particion[],int particiones, int tamano_particion ){
        for(int i = 0; i<particiones; i++){
        printf("Ingresa el tamaño de la particion:  %d\n", i+1);
        scanf("%d", &particion[i].tamano);
        particion[i].id_de_proceso = -1;
        tamano_particion += particion[i].tamano;
    }
}

int main(){
    int memoria_total, particiones, opcion, tamano_particion = 0;
    Particion particion[max_particiones];

    printf("Ingresa el tamaño de la memoria: \n");
    scanf("%d", &memoria_total);

    printf("Ingresa el numero de particiones: \n");
    scanf("%d", &particiones);

    while (particiones>max_particiones){
        printf("El numero de particiones excedio el limite (100), ingresa otro numero  \n");
        scanf("%d", &particiones);
    }
    
    
    ingresar_tamano(particion, particiones, tamano_particion);

    while (tamano_particion > memoria_total){
        printf("El tamaño total de las particiones excede el tamaño de la memoria.\n");
        printf("Ingresa de nuevo el tamaño.\n");
        tamano_particion = 0;

        ingresar_tamano(particion, particiones, tamano_particion);
    }

    do {       
        printf("1. Asignar proceso\n");
        printf("2. Liberar proceso\n");
        printf("3. Mostrar estado de la memoria\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int id_de_proceso, tam_proceso;
                bool id_igual = false;

                do{
                    id_igual = false;
                    printf("Ingrese el ID del proceso: ");
                    scanf("%d", &id_de_proceso);

                    for (int i = 0; i < particiones; i++) {
                        if (particion[i].id_de_proceso == id_de_proceso) {
                            printf("Ese Id ya esta asignado, prueba con otro. \n ");
                            id_igual = true;
                            break;
                    }
                }
                } while (id_igual == true);

                printf("Ingrese el tamaño del proceso (KB): ");
                scanf("%d", &tam_proceso);

                int asignado = 0;
                for (int i = 0; i < particiones; i++) {
                    if (particion[i].id_de_proceso == -1 && particion[i].tamano >= tam_proceso) {
                        particion[i].id_de_proceso = id_de_proceso;
                        asignado = 1;
                        printf("Proceso %d asignado a la partición %d.\n", id_de_proceso, i + 1);
                        break;
                    }
                }
                if (!asignado) {
                    printf("No se encontró una partición disponible para el proceso %d.\n", id_de_proceso);
                }
                break;
            }
            case 2: {
                int id_de_proceso;
                printf("Ingrese el ID del proceso a liberar: ");
                scanf("%d", &id_de_proceso);

                int libre = 0;
                for (int i = 0; i < particiones; i++) {
                    if (particion[i].id_de_proceso == id_de_proceso) {
                        particion[i].id_de_proceso = -1;
                        libre = 1;
                        printf("Proceso %d liberado de la partición %d.\n", id_de_proceso, i + 1);
                        break;
                    }
                }
                if (!libre) {
                    printf("No se encontró el proceso %d en ninguna partición.\n", id_de_proceso);
                }
                break;
            }
            case 3:
                imprime_memoria(particion, particiones);
                break;
            case 4:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 4);

    return 0;
}