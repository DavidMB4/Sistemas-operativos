#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *buffer;       
    int tamano_buffer;  
    int posicion;       
} Dispositivo_virtual;

Dispositivo_virtual* iniciar_dispositivo(int size) {
    Dispositivo_virtual *dispositivo = (Dispositivo_virtual *)malloc(sizeof(Dispositivo_virtual));
    if (dispositivo == NULL) {
        perror("Error al asignar memoria para el dispositivo");
        return NULL;
    }
    dispositivo->buffer = (char *)malloc(size);
    if (dispositivo->buffer == NULL) {
        perror("Error al asignar memoria para el búfer del dispositivo");
        free(dispositivo);
        return NULL;
    }
    dispositivo->tamano_buffer = size;
    dispositivo->posicion = 0;
    memset(dispositivo->buffer, 0, size); 
    printf("Dispositivo inicializado con un búfer de %d bytes.\n", size);
    return dispositivo;
}


void escribir_dispositivo(Dispositivo_virtual *dispositivo, const char *data) {
    if (dispositivo == NULL || dispositivo->buffer == NULL) {
        printf("Error: Dispositivo no inicializado.\n");
        return;
    }
    int data_length = strlen(data);
    if (dispositivo->posicion + data_length >= dispositivo->tamano_buffer) {
        printf("Error: No hay suficiente espacio en el búfer del dispositivo.\n");
        return;
    }
    memcpy(&dispositivo->buffer[dispositivo->posicion], data, data_length);
    dispositivo->posicion += data_length;
    printf("Datos escritos al dispositivo: %s\n", data);
}


void leer_dispositivo(Dispositivo_virtual *dispositivo) {
    if (dispositivo == NULL || dispositivo->buffer == NULL) {
        printf("Error: Dispositivo no inicializado.\n");
        return;
    }
    printf("Datos en el dispositivo: %s\n", dispositivo->buffer);
}

void liberar_dispositivo(Dispositivo_virtual *dispositivo) {
    if (dispositivo == NULL) {
        return;
    }
    free(dispositivo->buffer);
    free(dispositivo);
    printf("Dispositivo liberado correctamente.\n");
}


int main() {
    Dispositivo_virtual *dispositivo = iniciar_dispositivo(BUFFER_SIZE);
    if (dispositivo == NULL) {
        return 1;
    }

    int opcion;
    char mensaje[BUFFER_SIZE];

    do {
        printf("\n--- Menú ---\n");
        printf("1. Escribir un mensaje\n");
        printf("2. Leer los datos del dispositivo\n");
        printf("3. Liberar el dispositivo y salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);
        getchar(); 

        switch (opcion) {
            case 1:
                printf("Escribe tu mensaje: ");
                fgets(mensaje, BUFFER_SIZE, stdin);
                mensaje[strcspn(mensaje, "\n")] = '\0';
                escribir_dispositivo(dispositivo, mensaje);
                break;
            case 2:
                leer_dispositivo(dispositivo);
                break;
            case 3:
                liberar_dispositivo(dispositivo);
                printf("Desconectado\n");
                break;
            default:
                printf("Opción no válida. Inténtalo de nuevo.\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}
