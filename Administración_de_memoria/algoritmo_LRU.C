#include <stdio.h>
#include <limits.h>

void mostrar_marcos(int marcos[], int num_marcos) {
    for (int i = 0; i < num_marcos; i++) {
        if (marcos[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", marcos[i]);
        }
    }
    printf("\n");
}

int encontrar_menos_reciente(int tiempo[], int num_marcos) {
    int min_tiempo = INT_MAX;
    int menos_reciente = 0;

    for (int i = 0; i < num_marcos; i++) {
        if (tiempo[i] < min_tiempo) {
            min_tiempo = tiempo[i];
            menos_reciente = i;
        }
    }
    return menos_reciente;
}

void remplazo(int paginas[], int num_paginas, int num_marcos) {
    int marcos[num_marcos];
    int tiempo[num_marcos];
    int contador = 0;  
    int fallos = 0;

    for (int i = 0; i < num_marcos; i++) {
        marcos[i] = -1;
        tiempo[i] = 0;
    }

    printf("Secuencia de reemplazo:\n");

    for (int i = 0; i < num_paginas; i++) {
        int pagina = paginas[i];
        int encontrado = false;

        for (int j = 0; j < num_marcos; j++) {
            if (marcos[j] == pagina) {
                encontrado = true;
                tiempo[j] = ++contador; 
                break;
            }
        }

        if (encontrado == false) {
            int menos_reciente = encontrar_menos_reciente(tiempo, num_marcos);

            marcos[menos_reciente] = pagina;
            tiempo[menos_reciente] = ++contador;
            fallos++;

            mostrar_marcos(marcos, num_marcos);
        }
    }

    printf("\nTotal de fallos de página: %d\n", fallos);
}

int main() {
    int num_paginas, num_marcos;

    printf("Ingresa el número de marcos: ");
    scanf("%d", &num_marcos);

    printf("Ingresa el número de páginas: ");
    scanf("%d", &num_paginas);

    int paginas[num_paginas];
    printf("Ingresa la secuencia de uso de páginas:\n");
    for (int i = 0; i < num_paginas; i++) {
        scanf("%d", &paginas[i]);
    }

    remplazo(paginas, num_paginas, num_marcos);

    return 0;
}
