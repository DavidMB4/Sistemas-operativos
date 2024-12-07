# Repositorio Sistemas Operativos
### 3.1 Política y filosofia
###### 1. ¿Cuál es la diferencia entre fragmentación interna y externa?
La __fragmentación interna__ ocurre cuando un bloque de memoria es más grande que el tamaño solicitado y se desperdicia el exceso de espacio.
Por ejemplo: digamos que un asignador solo puede proporcionar memoria en fragmentos de 4 bytes. Si un programa solicita 29 bytes de memoria, en realidad recibirá una porción de 32 bytes. Dado que el programa utiliza sólo 29 de los 32 bytes disponibles, los 3 bytes sobrantes de memoria se desperdician.

Esta memoria que no se usa, queda inservible para otros procesos y limita la cantidad que se pueden ejecutar al mismo tiempo. Ya que reduce la memoria funcional óptima. Esto puede aumentar el tiempo de procesamiento ya que debe buscar un bloque adecuado para reducir la fragmentación.

La __fragmentación externa__ ocurre cuando hay espacios entre los bloques asignados y la memoria no se puede usar para solicitudes más grandes. 
Por ejemplo: digamos que el asignador asigna varios bloques de memoria en una línea continua. Si uno de los bloques intermedios se libera porque el proceso que lo estaba usando dejó de ejecutarse, el bloque libre se fragmenta.

Esto hace que solo se pueda usar ese bloque aislado solo si hay una solicitud que quepa dentro, pero no puede usarse para solicitudes de memoria mayores. Y no puede unirse como los bloques libres.

Entonces la __fragmentación interna__ ocurre dentro del espacio del bloque que se solicita, mientras que la __fragmentación externa__ ocurre en los bloques contiguos o espacios entre los bloques.


######  2. Investiga y explica las políticas de reemplazo de páginas en sistemas operativos. ¿Cuál consideras más eficiente y por qué?
Las __políticas de reemplazo de páginas__ son algoritmos utilizados en sistemas operativos para decidir qué página en la memoria debe ser reemplazada cuando se necesita liberar espacio para cargar una nueva página.

Una página es una unidad de memoria fija en la que se divide el espacio de direcciones de un proceso. Cada página puede tener un tamaño de 4 KB, 8 KB o más, dependiendo de la arquitectura del sistema.

La memoria física (RAM) se divide en bloques de tamaño fijo llamados marcos de página, que son del mismo tamaño que las páginas.

Hay varios algoritmos de reemplazo de páginas, cada uno con sus propias características y estrategias:

1. __FIFO (First-In, First-Out)__: Este algoritmo reemplaza la página más antigua en la memoria. Se usa una cola, al cargar una página nueva se ingresa en el último lugar. Aunque las colas FIFO son simples e intuitivas, no se comportan de manera aceptable en la aplicación práctica, por lo que es raro su uso en su forma simple. 

Una desventaja es la anomalía Belady, consiste en que podemos quitar de memoria una página de memoria muy usada, solo porque es la más antigua.

2. __LRU (Least Recently Used)__: Reemplaza la página que no ha sido utilizada durante el periodo más largo de tiempo. Este algoritmo utiliza la idea de que las páginas que han sido accedidas recientemente tienen más probabilidad de ser accedidas nuevamente en el futuro.

La desventaja es que gasta recursos para rastrear el orden de uso de las páginas.

3. __Optimal__: Este es un algoritmo teórico que reemplaza la página que no será utilizada por el mayor periodo de tiempo en el futuro.  Para esto el sistema operativo debería ver en cuánto tiempo será usada cada página en memoria y elegir la que está más distante.

El problema de este método es que necesita conocimiento del futuro, por lo que es difícil de implementar.

4. __Algoritmo de reloj__: Es una variación de FIFO que utiliza un "bit de referencia" para decidir qué páginas reemplazar. En caso de estar fijado (en 1) se cambia el bit a 0 y se lo coloca al final de la obstrucción, actualizando su tiempo de carga como si recién hubiera llegado al procesador. De esta forma, se le da una segunda oportunidad. Si el bit se encuentra sin fijar(en 0), la página se saca de memoria.

La desventaja es que en algunos casos suele ser menos precisa que LRU.

5. __NRU (Not Recently Used)__: Cuándo una página es referenciada, fija el bit de referencia para esa página. Similarmente, cuando una página es modificada, fija su bit de modificación.
Cuando una página debe ser reemplazada, el sistema operativo divide las páginas en cuatro categorías:
    * Categoría 0: No referenciada, No modificada
    * Categoría 1: No referenciada, modificada
    * Categoría 2: referenciada, No modificada
    * Categoría 3: referenciada, modificada

Las mejores páginas para cambiar son las que se encuentran en la categoría 0, mientras que las peores son las de la categoría 3.
En algunos casos es más óptimo LRU o reloj.

El más eficiente podría ser el optimal, pero solo de forma teórica ya que es el más difícil de llevarlo a la practica, asi que yo elegiría LRU como el más eficiente, ya que aunque puede gastar más recursos que otros algoritmos, es el que mejor referencia el estado de las páginas en los sistemas para ser reemplazados.

### 3.2 Memoria real 
###### 1.Escribe un programa en C o Python que simule la administración de memoria mediante particiones fijas.
###### 2. Diseña un algoritmo para calcular qué procesos pueden ser asignados  a un sistema con memoria real limitada utilizando el algoritmo de "primera cabida".

Para el programa se uso como base el codigo compartido por el profesor en la seccion de Administraciono de memoria en las respuestas del ejercicio. El codigo simula la administracion de memoria con particiones fijas al preguntarle al usuario el tamaño de la memoria y el numero de particiones que quieres.
~~~
int main(){
    int memoria_total, particiones, opcion, tamano_particion = 0;
    Particion particion[max_particiones];

    printf("Ingresa el tamaño de la memoria: \n");
    scanf("%d", &memoria_total);

    printf("Ingresa el numero de particiones: \n");
    scanf("%d", &particiones);
~~~

El usuario le asigna el tamaño a cada particion, luego puede asignar un proceso a cada particion mientras cumpla con los requisitos de tamaño, el codigo tambien utiliza la primera cabida ya que recorre el arreglo de particion para ver cual cumple con el tamaño indicado en la asignacion del proceso, la primera particion que encuentre que cumpla los requisitos le asigna el proceso.

~~~
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
~~~

Codigo completo:
~~~
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
~~~

### 3.3 Organizacion de memoria virtual
###### 1. Investiga y explica el concepto de "paginación" y "segmentación". ¿Cuáles son las ventajas y desventajas de cada técnica?

La __paginación__ es una estrategia de organización de la memoria física que consiste en dividir la memoria en porciones de igual tamaño. A dichas porciones se las conoce como páginas físicas o marcos. La división de la memoria en páginas facilita la gestión de la memoria física. Los marcos se identifican con un número que se denomina «número de página física. A su vez, cada página física se asigna a un proceso de forma exclusiva.

Tanto el tamaño de las páginas como de los marcos de páginas es definido por el hardware y suele ser una potencia de 2. Permite que las páginas de un proceso puedan cargarse en cualquier marco de página disponible, sin necesidad de que estén contiguos en la memoria.

El sistema operativo mantiene una tabla de páginas para cada proceso, que mapea cada página lógica a su marco físico correspondiente. Esta tabla se utiliza para traducir las direcciones lógicas (del proceso) a direcciones físicas (de la memoria). Cuando el proceso necesita acceder a una dirección lógica, el traductor de memoria paginada toma la dirección lógica y, por medio de la tabla de página, obtiene la dirección física real.

Ejemplo:
Supongamos un tamaño de página de 4 KB. Un proceso tiene 16 KB de memoria lógica, dividido en 4 páginas. La memoria física tiene 8 marcos disponibles.
Las páginas del proceso se asignan a marcos libres como sigue:
![Tabla de paginacion](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Administraci%C3%B3n_de_memoria/tabla_paginacion.jpg?raw=true)

La tabla de páginas almacenará esta información. Cuando el proceso necesita acceder a una dirección lógica, se consulta esta tabla para determinar su ubicación física.

__Ventajas:__
* Fácil de usar gestión de la memoria algoritmo
* No hay necesidad de fragmentación externa
* El intercambio es fácil entre páginas y marcos de página del mismo tamaño.

__Desventajas:__
* Puede causar fragmentación interna.
* Las tablas de páginas consumen memoria adicional.
* La paginación multinivel puede generar una sobrecarga de referencia de memoria.


__La segmentación__ es una técnica que asigna segmentos contiguos de memoria para las áreas de memoria de un proceso. De esta forma, logra acomodarse más a la visión de la memoria por parte del usuario. Un segmento de programa representa su parte lógica e incluye la función principal del programa, las estructuras de datos, las funciones de utilidad, etc. Cada segmento tiene un nombre y una longitud.

El sistema operativo mantiene una tabla de mapas de segmentos para todos los procesos. También incluye una lista de bloques de memoria libres junto con su tamaño, números de segmento y ubicaciones de memoria en la memoria principal o memoria virtual.

Las direcciones virtuales se componen de un número de segmento y el desplazamiento dentro del segmento. El desplazamiento debe ser menor que el largo asociado al segmento.

Cada segmento puede asignarse en cualquier parte de la memoria física.
La segmentación no requiere que los segmentos sean contiguos en memoria física.

Ejemplo:
Supongamos que un programa tiene las siguientes secciones:
![Tabla de segmentacion](https://github.com/DavidMB4/Sistemas-operativos/blob/master/Administraci%C3%B3n_de_memoria/tabla_segmentacion.jpg?raw=true)

Si se usa segmentación, cada sección se asigna a un segmento diferente. Una dirección lógica en el segmento 1 (código) con un desplazamiento de 500 se traduce a una dirección física en la memoria donde ese segmento está cargado.


__Ventajas:__
* Ofrecer protección dentro de los segmentos.
* Puede lograr compartir segmentando y haciendo referencia a múltiples procesos.
* No ofrece fragmentación interna.
* Las tablas de segmentos usan menos memoria que la paginación

__Desventajas:__
* En el método de segmentación, los procesos se cargan o eliminan de la memoria principal. Por tanto, el espacio libre de memoria se separa en pequeños trozos, lo que puede crear un problema de fragmentación externa.
* Algoritmo costoso de gestión de memoria

###### 2. Escribe un programa que simule una tabla de páginas para procesos con acceso aleatorio a memoria virtual.

Para el el codigo de la tabla de paginas se usa un arreglo que ocntiene todas las paginas, hay 100 y solo puede haber 10 procesos, al momento de asignar un proceso se pide el su ID y el tamaño del proceso, se simula con una formula para calcular la cantidad de paginas que se va a utilizar, como el acceso debe ser aleatorio la forma en que se asigna tambien es aleatoria asi que se usa un random que da un numero aleatorio para la acceder a la posicion del arreglo de las paginas (0-19). Esto se puede hacer por la forma en que funciona la paginacion, ya que no necesitan ser ocntinuos los espacios donde almacenan los procesos.
~~~            
    if paginas_disponibles >= num_paginas:
        while paginas_asignadas < num_paginas:
            pagina = random.randint(0, len(tabla_paginas) - 1)  
            if tabla_paginas[pagina] == -1: 
                tabla_paginas[pagina] = id_proceso 
                paginas_asignadas += 1
    else:
        print(f"No hay suficiente memoria para asignar el proceso {id_proceso}.")
~~~

Se peude ver toda la tabla en forma de arreglo con la opcion 3, pero se puede acceder de forma aleatoria a varias paginas con la opcion 2.
~~~
def acceso_aleatorio(num_acceso):
    print("\nAccesos aleatorios a la memoria:")
    for _ in range(num_acceso):
        pagina = random.randint(0, len(tabla_paginas) - 1)
        if tabla_paginas[pagina] == -1:
            print(f"Página {pagina} está libre.")
        else:
            print(f"Página {pagina} es parte del proceso {tabla_paginas[pagina]}.")
~~~

__Codigo completo:__
~~~
import random

max_paginas = 100
max_procesos = 10
tam_pagina = 4

tabla_paginas = []
for i in range (max_paginas):
    tabla_paginas.append(-1)
    
def asignar_proceso(id_proceso, tamano_proceso):    
    num_paginas = (tamano_proceso + tam_pagina - 1) // tam_pagina
    paginas_asignadas = 0
    paginas_disponibles = 0
    
    for i in range (max_paginas):
        if tabla_paginas[i] == -1:
            paginas_disponibles = paginas_disponibles + 1
            
    if paginas_disponibles >= num_paginas:
        while paginas_asignadas < num_paginas:
            pagina = random.randint(0, len(tabla_paginas) - 1)  
            if tabla_paginas[pagina] == -1: 
                tabla_paginas[pagina] = id_proceso 
                paginas_asignadas += 1
    else:
        print(f"No hay suficiente memoria para asignar el proceso {id_proceso}.")
    
def mostrar_tabla():
    print("\n Tabla de paginas")
    for i in range(max_paginas):
        if tabla_paginas[i] == -1:
            print(f"Página {i}: Libre")
        else:
            print(f"Página {i}: Proceso {tabla_paginas[i]}")
            
def liberar_proceso():
    id_proceso = int(input("\n Ingresa el id del proceso a liberar: "))     
    liberado = False
    for i in range(max_paginas):
        if tabla_paginas[i] == id_proceso:
            tabla_paginas[i] = -1 
            liberado = True
    if liberado == True:
            print(f"Proceso {id_proceso} liberado.")
    else:
            print(f"Proceso {id_proceso} no encontrado.")        
            
def acceso_aleatorio(num_acceso):
    print("\nAccesos aleatorios a la memoria:")
    for _ in range(num_acceso):
        pagina = random.randint(0, len(tabla_paginas) - 1)
        if tabla_paginas[pagina] == -1:
            print(f"Página {pagina} está libre.")
        else:
            print(f"Página {pagina} es parte del proceso {tabla_paginas[pagina]}.")
    
def main():
    while True:
        print("\n1. Asignar proceso")
        print("2. Acceso aleatorio")
        print("3. Mostrar estado de la tabla de páginas")
        print("4. Liberar proceso")
        print("5. Salir")
        opcion = int(input("Seleccione una opción: "))

        if opcion == 1:
            id_proceso = int(input("Ingrese el ID del proceso: "))
            tamano_proceso = int(input("Ingrese el tamaño del proceso (KB): "))
            asignar_proceso(id_proceso, tamano_proceso)
        elif opcion == 2:
            num_acceso = int(input("Ingrese el numero de accesos aleatorios: "))
            acceso_aleatorio(num_acceso)
        elif opcion == 3:
            mostrar_tabla()
        elif opcion == 4:
            liberar_proceso()
        elif opcion == 5:
            print("Saliendo del programa.")
            break
        else:
            print("Opción no válida.")
            
if __name__ == "__main__":
    main()
~~~

### 3.4 Administración de memoria virtual
###### 1. Escribe un código que implemente el algoritmo de reemplazo de página "Least Recently Used" (LRU).
En el codigo primero pide al usuario ingresar el numero de marcos, numero de paginas, y la secuencia de las paginas. Se usa la funcion remplazo y empieza a poner los marcos como libres con un -1, y con un tiempo de 0 para cada uno. Empieza a buscar cada una de las paginas en los marcos de acuerdo a la secuencia, si no encuentra una usa la funcion encontrar_menos_reciente para buscar el marco que contiene a la pagina menos reciente utilizada revisando el tiempo de cada pagina, si encuentra un marco de pagina con un tiempo menor al del anterior lo toma como referencia para el siguiente marco hasata comprobar que es el menor, y lo returna.
~~~
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
~~~
~~~
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
~~~
De volvera la primera posicion de los marcos ya que aun no se habian utilizado ninguno, agregara la pagina al marco y le sumara al contador de tiempo, ademas de que sumara a la variable fallos por no haber encontrado la pagina dentro de los marcos. Y asi ira realizando el ciclo for hasta haber acabado la secuencia de las paginas.
~~~
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
~~~

__codigo completo:__
~~~
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

~~~


###### 2. Diseña un diagrama que represente el proceso de traducción de direcciones virtuales a físicas en un sistema con memoria virtual.
El diagrama muestra que la direccion virtual está dividida en el número de página y el desplazamiento (Offset). Tiene un buffer de traducción adelantada (TLB), que muestra cómo se verifica si la dirección virtual tiene una entrada correspondiente en la TLB. Si la TLB no muestra ninguna coincidencia, se recurre a la tabla de páginas para obtener el marco físico correspondiente. Por ultimo la direccion fisica sale al combinar el marco físico con el desplazamiento.

![Diagrama de traduccion de direcciones]()